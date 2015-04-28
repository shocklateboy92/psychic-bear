#ifndef DBINFO_H
#define DBINFO_H

#include <QSqlDatabase>
#include <QString>

class DbInfo
{
public:
    DbInfo();
    ~DbInfo();

    QString characterId() const;
    int 	version() const;

    void setCharacterId(const QString &characterId);
    void setVersion(int version);

    void read(QSqlDatabase &db);
    void write(QSqlDatabase &db);
    bool initializeDb(QSqlDatabase &db);

    static bool execute(QSqlQuery &query);
private:
    template <typename T>
    static bool writeProperty(QSqlDatabase &db,
                              const QString &name,
                              const T &value);
    template <typename T>
    static bool readProperty(QSqlDatabase &db,
                             const QString &name,
                             T &value);

    int m_version;
    QString m_characterId;
};

#endif // DBINFO_H
