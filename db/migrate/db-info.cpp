#include "db-info.h"

#include <QSqlQuery>

DbInfo::DbInfo()
    : m_version(0)
{

}

DbInfo::~DbInfo()
{

}
QString DbInfo::characterId() const
{
    return m_characterId;
}

void DbInfo::setCharacterId(const QString &characterId)
{
    m_characterId = characterId;
}
int DbInfo::version() const
{
    return m_version;
}

void DbInfo::setVersion(int version)
{
    m_version = version;
}

bool DbInfo::write(QSqlDatabase &db)
{
    QSqlQuery query;
//    query.prepare();
}

