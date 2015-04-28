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

    bool write(QSqlDatabase &db);

private:
    int m_version;
    QString m_characterId;
};

#endif // DBINFO_H
