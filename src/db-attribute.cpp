#include "db-attribute.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DBAttribute::DBAttribute()
    : m_id(-1), m_error(false)
{

}

DBAttribute::~DBAttribute()
{

}

bool DBAttribute::fetchId(const QString &uri)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Attributes WHERE Uri = :uri");
    query.bindValue(":uri", uri);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Failed to execute query "
                 << query.executedQuery()
                 << ":" << query.lastError();
    }

    result &= query.next();
    if (query.next()) {
        m_id = query.value(0).toInt(&result);
    }

    return result;
}
bool DBAttribute::error() const
{
    return m_error;
}

