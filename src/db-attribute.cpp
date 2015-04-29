#include "bonus.h"
#include "db-attribute.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DBAttribute::DBAttribute()
    : m_id(-1), m_error(true)
{

}

DBAttribute::~DBAttribute()
{

}

bool DBAttribute::executeQuery(QSqlQuery &query)
{
    bool result = query.exec();
    if (!result) {
        qWarning() << "Failed to execute query "
                 << query.executedQuery()
                 << ":" << query.lastError();
    }
    return result;
}

bool DBAttribute::fetchId(const QString &uri)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Attributes WHERE Uri = :uri");
    query.bindValue(":uri", uri);

    bool result = executeQuery(query);

    result &= query.next();
    if (result) {
        m_id = query.value(0).toInt(&result);
    }

    m_error = !result;
    return result;
}

QList<Bonus*> DBAttribute::readModifiers(QObject *parent)
{
    QList<Bonus*> ret;

    QSqlQuery query;
    query.prepare("SELECT name, amount FROM Modifiers WHERE attribute = :attr");
    query.bindValue(":attr", m_id);

    if (executeQuery(query)) {
        while (query.next()) {
            Bonus *b = new Bonus(parent);
            b->setName(query.value(0).toString());
            b->setAmount(query.value(1).toInt());
            ret.append(b);
        }
    } else {
        m_error = true;
    }

    return ret;
}

bool DBAttribute::createModifier(int amount, const QString &name)
{
    Q_ASSERT(amount != 0);
    Q_ASSERT(!name.isEmpty());

    QSqlQuery query;
    query.prepare("INSERT INTO Modifiers (attribute, name, amount) "
                  "VALUES (:attribute, :name, :amount)");
    query.bindValue(":attribute", m_id);
    query.bindValue(":name", name);
    query.bindValue(":amount", amount);

    return executeQuery(query);
}

bool DBAttribute::error() const
{
    return m_error;
}

