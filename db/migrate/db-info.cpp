#include "db-info.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

DbInfo::DbInfo()
    : m_version(-1)
{

}

DbInfo::~DbInfo()
{

}
QString DbInfo::characterId() const
{
    return m_characterId;
}

void DbInfo::setCharacterId(const QString &characterId)
{
    m_characterId = characterId;
}
int DbInfo::version() const
{
    return m_version;
}

void DbInfo::setVersion(int version)
{
    m_version = version;
}

void DbInfo::read(QSqlDatabase &db)
{
    readProperty(db, "version", m_version);
    readProperty(db, "characterId", m_characterId);
}

void DbInfo::write(QSqlDatabase &db)
{
    writeProperty(db, "version", m_version);
    writeProperty(db, "characterId", m_characterId);
}

bool DbInfo::execute(QSqlQuery &query) {
    bool success = query.exec();
    qDebug() << "Executing" << query.lastQuery();
    if (!success) {
        qWarning() << query.lastError();
    }
    return success;
}

bool DbInfo::initializeDb(QSqlDatabase &db)
{
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS DbInfo ("
                  "key TEXT,"
                  "value"
                  ");");
    return execute(query);
}

template <typename T>
bool DbInfo::writeProperty(QSqlDatabase &db, const QString &name, const T &value)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM DbInfo WHERE key = :name");
    query.bindValue(":name", name);

    if (!execute(query)) {
        qWarning() << "DbInfo didn't contain" << name;
    }

    query.prepare("INSERT INTO DbInfo (key, value) VALUES (:name, :value)");
    query.bindValue(":name", name);
    query.bindValue(":value", QVariant::fromValue(value));

    return execute(query);
}

template <typename T>
bool DbInfo::readProperty(QSqlDatabase &db, const QString &name, T &value)
{
    QSqlQuery query(db);
    query.prepare("SELECT value FROM DbInfo WHERE key = :name");
    query.bindValue(":name", name);

    execute(query);
    if (!query.next()) {
        qWarning() << "DbInfo didn't contain" << name;
        return false;
    }

    value = qvariant_cast<T>(query.value(0));
    return true;
}
