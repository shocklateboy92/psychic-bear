#include "db-util.h"
#include "bonus.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DbUtil::DbUtil(QString tableName)
    : m_id(-1), m_error(false), m_tableName(tableName)
{

}

DbUtil::~DbUtil()
{

}

bool DbUtil::executeQuery(QSqlQuery &query)
{
    bool result = query.exec();
    if (!result) {
        qWarning() << "Failed to execute query "
                 << query.lastQuery()
                 << ":" << query.lastError()
                 << "," << query.boundValues();
    }
    return result;
}

QList<Bonus*> DbUtil::readModifiers(QObject *parent) const
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
    }

    return ret;
}

bool DbUtil::createModifier(int amount, const QString &name)
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

bool DbUtil::error() const
{
    return m_error;
}


int DbUtil::id() const
{
    return m_id;
}

bool DbUtil::isValid() const
{
    return m_id != -1;
}

QString DbUtil::tableName() const
{
    return m_tableName;
}

QList<QVariantList> DbUtil::readRelationProperties(
        QString relation,
        QString table,
        QStringList properties)
{
    QList<QVariantList> ret;
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT %2 FROM %3 WHERE %1 = :id")
                  .arg(relation).arg(properties.join(", ")).arg(table));
    query.bindValue(":id", id());

    executeQuery(query);

    while (query.next()) {
        QVariantList row;
        for (int i = 0; i < properties.size(); i++) {
            row.push_back(query.value(i));
        }
        ret.push_back(row);
    }

    return ret;
}

void DbUtil::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

bool DbUtil::fetchId(const QString &uri)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT id FROM %1 WHERE Uri = :uri").arg(m_tableName));
    query.bindValue(":uri", uri);

    bool result = executeQuery(query);

    result &= query.next();
    if (result) {
        m_id = query.value(0).toInt(&result);
    }

    m_error = !result;
    return result;
}


