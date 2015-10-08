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
        qDebug() << error.errorString();
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

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);
}

SpellList::Model::Model(SpellList *parent)
    : QAbstractListModel(parent)
{

}
void SpellList::Model::setSpells(const QList<int> &spellIds)
{
    m_spellIds = spellIds;
}

int SpellList::Model::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant SpellList::Model::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> SpellList::Model::roleNames() const
{
    return allSpells->getHeaders();
}




