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
    bool fetchProperty(QString propName, T &ret);
    template <typename T>
    bool writeProperty(QString propName, const T &val);

    bool fetchId(const QString &uri);

private:
    int m_id;
    QString m_tableName;
};

template <typename T>
bool DbHelper::fetchProperty(QString propName, T &ret)
{
    QSqlQuery query;
    QString str = QStringLiteral("SELECT %1 FROM %2 WHERE id = :id");

    query.prepare(str.arg(propName).arg(tableName()));
    query.bindValue(":id", id());

    bool success = DBAttribute::executeQuery(query);
    if (success &= query.next()) {
        ret = qvariant_cast<T>(query.value(0));
    }

    return success;
}

template <typename T>
bool DbHelper::writeProperty(QString propName, const T &val)
{
    QSqlQuery query;
    auto qstr = QStringLiteral("UPDATE %2 SET %1 = :val WHERE id = :id");

    query.prepare(qstr.arg(propName).arg(tableName()));
    query.bindValue(":val", val);
    query.bindValue(":id", id());

    return DBAttribute::executeQuery(query);
}

#endif // DBHELPER_H
