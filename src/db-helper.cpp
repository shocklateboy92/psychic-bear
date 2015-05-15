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
    auto qstr = QStringLiteral("SELECT id FROM %1 WHERE uri = :uri");
    query.prepare(qstr.arg(tableName()));

    query.bindValue(":uri", uri);

    bool success = DBAttribute::executeQuery(query);
    success &= query.next();
    if (success) {
        m_id = query.value(0).toInt(&success);
    }

    return success;
}
