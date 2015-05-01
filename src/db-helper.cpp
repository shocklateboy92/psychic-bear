#include "db-attribute.h"
#include "db-helper.h"

#include <QByteArray>
#include <QSqlQuery>
#include <QVariant>

DbHelper::DbHelper()
    : m_id(-1)
{
}

DbHelper::~DbHelper()
{

}

int DbHelper::id() const
{
    return m_id;
}

bool DbHelper::isValid() const
{
    return m_id != -1;
}

QString DbHelper::tableName() const
{
    return m_tableName;
}

void DbHelper::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

bool DbHelper::fetchId(const QString &uri)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM :table WHERE uri = :uri");

    query.bindValue(":table", tableName());
    query.bindValue(":uri", uri);

    return DBAttribute::executeQuery(query);
}
