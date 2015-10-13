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
      m_model(new Model(this)), m_level(0)
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

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);
}

void SpellList::setLevel(int level)
{
    if (m_level == level)
        return;

    m_level = level;
    emit levelChanged(level);
}

void SpellList::createNewSlot()
{
    m_model->insertRow(m_model->rowCount());
}

bool SpellList::isDynamic() const
{
    // all spell lists are dynamic - I don't see much
    // point in having a spell-list of hardcoded spells.
    return true;
}

bool SpellList::initDb()
{
    bool success = db().fetchId(uri());

    if (success) {
        auto members = db().readRelationProperties(
                    "spellList",
                    "SpellListMembers",
                    {
                        "level",
                        "spellId"
                    });

        QList<Spell> spells;
        for (QVariantList props : members) {
            spells.push_back({
                                 props.at(0).toInt(),
                                 props.at(1).toInt()
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

void SpellList::Model::setSpells(const QList<SpellList::Spell> &spellIds)
{
    // in case there's a view already attached, we need
    // to tell it that everything is going to change.
    beginResetModel();
    m_spellIds = spellIds;
    endResetModel();
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


// SpellList::Spell implementation
SpellList::Spell::Spell(int level, int id)
    : m_level(level), m_id(id)
{
}

SpellList::Spell::Spell(const DbUtil &db, int level, int id)
    : Spell(level, id)
{

}

QVariant SpellList::Spell::dataFor(int role) const
{
    if (m_id >= 0) {
        return allSpells->getInfoFor(m_id, role);
    }

    return QVariant();
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


bool SpellList::Model::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(parent, row, row + count);
    for (int i = 0; i < count; i++) {
        auto db = m_parent->db().createRelationRecord(
                    "spellList",
                    "SpellListMembers",
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
