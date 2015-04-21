#ifndef DBATTRIBUTE_H
#define DBATTRIBUTE_H

class QString;
class QSqlQuery;
template<typename T>
class QList;

class Bonus;

class DBAttribute
{
public:
    DBAttribute();
    ~DBAttribute();

    bool fetchId(const QString &uri);
    QList<Bonus *> readModifiers(QObject *parent);

    bool error() const;

private:
    int m_id;
    bool m_error;

    static bool executeQuery(QSqlQuery &query);
};

#endif // DBATTRIBUTE_H
