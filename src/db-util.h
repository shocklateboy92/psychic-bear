#ifndef DBATTRIBUTE_H
#define DBATTRIBUTE_H

#include <QSqlQuery>
#include<QString>
#include<QVariant>

template<typename T>
class QList;
class QQuickItem;

class Bonus;

class DbUtil
{
public:
    DbUtil(QString tableName);
    ~DbUtil();

    bool fetchId(const QString &uri);

    void setTableName(const QString &tableName);

    bool createModifier(int amount, const QString &name);

    static bool executeQuery(QSqlQuery &query);

    QList<Bonus *> readModifiers(QObject *parent) const;

    int 	id() const;
    bool 	isValid() const;
    bool error() const;
    QString tableName() const;

    template <typename T>
    bool fetchProperty(QString propName, T &ret) const;
    template <typename T>
    bool writeProperty(QString propName, const T &val);

    QList<QVariantList> readRelationProperties(QString relation,
            QString table,
            QStringList properties);

private:
    int m_id;
    bool m_error;
    QString m_tableName;
};

template <typename T>
bool DbUtil::fetchProperty(QString propName, T &ret) const
{
    QSqlQuery query;
    QString str = QStringLiteral("SELECT %1 FROM %2 WHERE id = :id");

    query.prepare(str.arg(propName).arg(tableName()));
    query.bindValue(":id", id());

    bool success = DbUtil::executeQuery(query);
    if (success &= query.next()) {
        ret = qvariant_cast<T>(query.value(0));
    }

    return success;
}

template <typename T>
bool DbUtil::writeProperty(QString propName, const T &val)
{
    QSqlQuery query;
    auto qstr = QStringLiteral("UPDATE %2 SET %1 = :val WHERE id = :id");

    query.prepare(qstr.arg(propName).arg(tableName()));
    query.bindValue(":val", val);
    query.bindValue(":id", id());

    return DbUtil::executeQuery(query);
}

#endif // DBATTRIBUTE_H
