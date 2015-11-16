#include "spell-list.h"

#include <QJsonDocument>
#include <QJsonArray>

static const QString SPELL_INFO_SRC = QStringLiteral(":/doc/spel/spell_full.json");
/**
 * @brief The SpellInfo class keeps the giant database of spells in memory
 * and provides convinient access to each role's details.
 *
 * @note This should be used with the singleton instance allSpells
 */
class SpellInfo {
public:
    SpellInfo();
    QVariant getInfoFor(int spellId, int role);

    const QHash<int, QByteArray>& getHeaders() const;
    const QList<QVariantList>& getData() const;

private:
    QList<QVariantList> m_data;
    QHash<int, QByteArray> m_headers;
};

// Qt will handle the singleton magic for us,
// and make an instance called 'allSpells'
Q_GLOBAL_STATIC(SpellInfo, allSpells)


// SpellList implementation
SpellList::SpellList(QQuickItem *parent)
    : Resource(QStringLiteral("SpellLists"), parent),
      m_level(-1),
      m_complete(false),
      m_model(new Model(this)),
      m_availableSpells(new Model(this)),
      m_totalCasts(nullptr),
      m_remainingCasts(nullptr)
{
}

QString SpellList::className() const
{
    return m_className;
}

SpellList::Model *SpellList::model() const
{
    return m_model;
}

int SpellList::level() const
{
    return m_level;
}

bool SpellList::complete() const
{
    return m_complete;
}

Attribute *SpellList::totalCasts() const
{
    return m_totalCasts;
}

Attribute *SpellList::remainingCasts() const
{
    return m_remainingCasts;
}

Attribute *SpellList::saveDc() const
{
    return m_saveDc;
}

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);

    populate();
}

void SpellList::setLevel(int level)
{
    if (m_level == level)
        return;

    m_level = level;
    emit levelChanged(level);

    populate();
}

void SpellList::setComplete(bool complete)
{
    if (m_complete == complete)
        return;

    m_complete = complete;
    populate();

    emit completeChanged(complete);
}

void SpellList::createNewSlot()
{
    m_model->insertRow(m_model->rowCount());
}

void SpellList::updateSpellSlot(int slot, int spellId)
{
    m_model->updateSpell(slot, spellId);
}

void SpellList::setTotalCasts(Attribute *totalCasts)
{
    if (m_totalCasts == totalCasts)
        return;

    m_totalCasts = totalCasts;
    emit totalCastsChanged(totalCasts);
}

void SpellList::setRemainingCasts(Attribute *remainingCasts)
{
    if (m_remainingCasts == remainingCasts)
        return;

    m_remainingCasts = remainingCasts;
    emit remainingCastsChanged(remainingCasts);
}

void SpellList::setSaveDc(Attribute *saveDc)
{
    if (m_saveDc == saveDc)
        return;

    m_saveDc = saveDc;
    emit saveDcChanged(saveDc);
}

void SpellList::populate()
{
    if (!complete() || level() < 0 || className().isEmpty()) {
        return;
    }

    int role = allSpells->getHeaders().key(className().toLatin1(), -1);
    if (role < 0) {
        qWarning() << className() << "is not a valid class name";
        return;
    }

    QList<Entry> available;
    int count = 0;
    for (QVariant spell : allSpells->getData()) {
        if (spell.toList().at(role) == level()) {
            available.push_back({{""}, level(), count});
        }
        count++;
    }
    model()->setSpells(available);
}

bool SpellList::isDynamic() const
{
    return !complete();
}

bool SpellList::initDb()
{
    bool success = db().fetchId(uri());

    if (success) {
        auto members = db().readRelationProperties(
                    "spellList",
                    Entry::TABLE_NAME,
                    {
                        "level",
                        "spellId",
                        "id"
                    });

        QList<Entry> spells;
        for (QVariantList props : members) {
            spells.push_back({
                                 DbUtil(Entry::TABLE_NAME, props.at(2).toInt()),
                                 props.at(0).toInt(),
                                 props.at(1).toInt(),
                             });
        }
        m_model->setSpells(spells);
    }

    return success;
}


// SpellList::Model implementation
SpellList::Model::Model(SpellList *parent)
    : QAbstractListModel(parent), m_parent(parent)
{
}

void SpellList::Model::setSpells(const QList<SpellList::Entry> &spellIds)
{
    // in case there's a view already attached, we need
    // to tell it that everything is going to change.
    beginResetModel();
    m_spellIds = spellIds;
    endResetModel();
}

int SpellList::Model::getIdOf(int index)
{
    if (index < 0 || index > m_spellIds.count()) {
        return -1;
    }

    return m_spellIds.at(index).spellId();
}

int SpellList::Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_spellIds.size();
}

QVariant SpellList::Model::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.isValid());
    return m_spellIds.at(index.row()).dataFor(role);
}

QHash<int, QByteArray> SpellList::Model::roleNames() const
{
    return allSpells->getHeaders();
}

bool SpellList::Model::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(parent, row, row + count -1);
    for (int i = 0; i < count; i++) {
        auto db = m_parent->db().createRelationRecord(
                    "spellList",
                    Entry::TABLE_NAME,
                    {
                        "level",
                        "spellId"
                    },
                    {
                        m_parent->level(),
                        -1
                    });

        m_spellIds.insert(row, {db, m_parent->level(), -1});
    }
    endInsertRows();

    return true;
}

void SpellList::Model::updateSpell(int slot, int spellId)
{
    m_spellIds[slot].updateSpell(spellId);
    dataChanged(index(slot), index(slot));
}

QList<SpellList::Entry> SpellList::Model::spellIds() const
{
    return m_spellIds;
}


// SpellList::Entry implementation
const QString SpellList::Entry::TABLE_NAME =
        QStringLiteral("SpellListMembers");

SpellList::Entry::Entry(const DbUtil &db, int level, int spellId)
    : m_level(level), m_db(db), m_spellId(spellId)
{
}

QVariant SpellList::Entry::dataFor(int role) const
{
    if (m_spellId >= 0) {
        return allSpells->getInfoFor(m_spellId, role);
    }

    return QVariant();
}

void SpellList::Entry::updateSpell(int spellId)
{
    m_spellId = spellId;
    m_db.writeProperty("spellId", m_spellId);
}

int SpellList::Entry::spellId() const
{
    return m_spellId;
}


// SpellInfo implementation
SpellInfo::SpellInfo() {

    QFile input(SPELL_INFO_SRC);
    input.open(QIODevice::Text | QIODevice::ReadOnly);
    if (!input.isOpen()) {
        qWarning() << "Failed to open" << SPELL_INFO_SRC << ':' << input.errorString();
    }
    Q_ASSERT(input.isOpen());

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(input.readAll(), &error);
    if (error.error) {
        qWarning() << "Unable to read spells database" << ':' << error.errorString();
    }
    Q_ASSERT(doc.isArray());

    auto array = doc.array();
    int index = 0;
    for (auto header : array.first().toArray()) {
        Q_ASSERT(!m_headers.contains(index));
        m_headers.insert(index, header.toString().toLatin1());
        index++;
    }

    for (auto row : doc.array()) {
        Q_ASSERT(row.isArray());
        m_data.push_back(row.toArray().toVariantList());
    }
}

QVariant SpellInfo::getInfoFor(int spellId, int role) {
    return m_data.at(spellId).at(role);
}

const QHash<int, QByteArray> &SpellInfo::getHeaders() const
{
    return m_headers;
}

const QList<QVariantList> &SpellInfo::getData() const
{
return m_data;
}

