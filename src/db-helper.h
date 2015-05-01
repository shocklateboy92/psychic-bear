#ifndef DBHELPER_H
#define DBHELPER_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "db-attribute.h"

class DbHelper
{
public:
    DbHelper();
    ~DbHelper();

    int 	id() const;
    bool 	isValid() const;
    QString tableName() const;

    void setTableName(const QString &tableName);

    template <typename T>
    bool fetchProperty(QByteArray propName, T &ret);
    template <typename T>
    bool writeProperty(QByteArray propName, const T &val);

    bool fetchId(const QString &uri);

private:
    int m_id;
    QString m_tableName;
};

template <typename T>
bool DbHelper::fetchProperty(QByteArray propName, T &ret)
{
    QSqlQuery query;
    query.prepare("SELECT :prop FROM :table WHERE id = :id");
    query.bindValue(":table", tableName());
    query.bindValue(":prop", propName);
    query.bindValue(":id", id());

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

#endif // DBHELPER_H
