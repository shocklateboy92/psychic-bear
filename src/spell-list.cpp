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
    : Resource(QStringLiteral("SpellLists"), parent)
{
}

QString SpellList::className() const
{
    return m_className;
}

SpellList::ModelList SpellList::model()
{
    return {this, m_modelList};
}

int SpellList::maxLevel() const
{
    return m_maxLevel;
}

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);
}

void SpellList::setMaxLevel(int maxLevel)
{
    if (m_maxLevel == maxLevel)
        return;

    m_maxLevel = maxLevel;

    // in case this isn't during initialization,
    // and there are already other models.
    for (auto model : m_modelList) {
        model->deleteLater();
    }
    m_modelList.clear();

    for (int i = 0; i < maxLevel; i++) {
        m_modelList.push_back(new Model(this, i));
    }

    emit maxLevelChanged(maxLevel);
}

SpellList::Model::Model(SpellList *parent, int level)
    : QAbstractListModel(parent), m_level(level)
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

SpellList::Spell::Spell(int level, int id)
    : m_level(level), m_id(id)
{
}

QVariant SpellList::Spell::dataFor(int role) const
{
    if (m_id >= 0) {
        return allSpells->getInfoFor(m_id, role);
    }

    return QVariant();
}


bool SpellList::isDynamic() const
{
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

    }

    return success;
}
