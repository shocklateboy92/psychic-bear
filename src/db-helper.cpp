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

void DbHelper::setId(int id)
{
    m_id = id;
}
QString DbHelper::tableName() const
{
    return m_tableName;
}

void DbHelper::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}


template <typename T>
bool DbHelper::fetchProperty(QByteArray propName, T &ret)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT %1 FROM %2 WHERE id = :id")
                  .arg(propName).arg(tableName()));
    query.bindValue(":id", QVariant::fromValue(id()));

    bool success = DBAttribute::executeQuery(query);
    if (success) {
        ret = qvariant_cast<T>(query.value(0));
    }

    return success;
}

template <typename T>
bool DbHelper::writeProperty(QByteArray propName, const T &val)
{
    QSqlQuery query;
    query.prepare("UPDATE :table SET :prop = :val WHERE id = :id");

    query.bindValue(":table", tableName());
    query.bindValue(":prop", propName);
    query.bindValue(":val", val);
    query.bindValue(":id", id());

    return DBAttribute::executeQuery(query);
}
