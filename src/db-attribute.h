#ifndef DBATTRIBUTE_H
#define DBATTRIBUTE_H

class QString;
class QSqlQuery;
template<typename T>
class QList;
class QObject;

class Bonus;

class DBAttribute
{
public:
    DBAttribute();
    ~DBAttribute();

    bool fetchId(const QString &uri);
    QList<Bonus *> readModifiers(QObject *parent);
    bool createModifier(int amount, const QString &name);

    bool error() const;

    static bool executeQuery(QSqlQuery &query);

private:
    int m_id;
    bool m_error;
};

#endif // DBATTRIBUTE_H
