#include "spell-list.h"

#include <QJsonDocument>
#include <QJsonArray>

static const QString SPELL_INFO_SRC = QStringLiteral(":/doc/spel/spell_full.json");
class SpellInfo {
public:
    SpellInfo() {
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
            m_headers.insert(index, header.toString().toLatin1());
        }

        for (auto row : doc.array()) {
            Q_ASSERT(row.isArray());
            m_data.push_back(row.toArray().toVariantList());
        }
    }

    QVariant getInfoFor(int spellId, int role) {
        return m_data.at(spellId).at(role);
    }

    const QHash<int, QByteArray>& getHeaders() const
    {
        return m_headers;
    }

private:
    QList<QVariantList> m_data;
    QHash<int, QByteArray> m_headers;
};

Q_GLOBAL_STATIC(SpellInfo, allSpells)

SpellList::SpellList(QQuickItem *parent)
    : Resource(QStringLiteral("SpellLists"), parent), m_model(new Model(this))
{
    allSpells->getInfoFor(0, 0);
}

QString SpellList::className() const
{
    return m_className;
}

SpellList::Model *SpellList::model() const
{
    return m_model;
}

SpellList::AttributeList SpellList::slotCounts() const
{
    return m_slotCounts;
}

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);
}

void SpellList::setSlotCounts(SpellList::AttributeList slotCounts)
{
    qDebug();
    QList<Spell> spellSlots;
    for (int i = 0; i < slotCounts.count(); i++) {
        auto attr = qobject_cast<Attribute*>(slotCounts.at(i));
        if (!attr) {
            qWarning() << "Error: got slot count object of type" << slotCounts.listElementType() << "when expecting 'Attribute'";
        }

        int slotsForLevel = attr->value();
        for (int j = 0; j < slotsForLevel; j++) {
            spellSlots.push_back({i + 1});
        }
        qDebug() << slotsForLevel;
    }

    m_model->setSpells(spellSlots);

    m_slotCounts = slotCounts;
    emit slotCountsChanged(slotCounts);
}

SpellList::Model::Model(SpellList *parent)
    : QAbstractListModel(parent)
{

}
void SpellList::Model::setSpells(const QList<SpellList::Spell> &spellIds)
{
    m_spellIds = spellIds;
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

SpellList::Spell::Spell(int level)
    : m_level(level), m_id(-1)
{
}

QVariant SpellList::Spell::dataFor(int role) const
{
    if (m_id >= 0) {
        return allSpells->getInfoFor(m_id, role);
    }

    return QVariant();
}
