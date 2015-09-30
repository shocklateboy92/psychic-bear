#include <QCoreApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <attribute.h>

#include <QSqlQuery>
#include <attribute-manager.h>
#include <core_plugin.h>
#include <functional>
#include <project-context.h>
#include <bonus-source.h>

template <typename T>
void populate_db(QSqlDatabase &db, QList<T*> input);

template <typename T> struct ResourceInfo {
    static std::function<bool(T*)> enabled;
    static std::function<bool(T*)> valid;
    static const QString tableName;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 3) {
        qWarning() << "Usage:" << argv[0] << " <db_name> <character_name>";
        return 2;
    }

    const QString dbPath = argv[1];

    CorePlugin plugin;
    plugin.registerTypes(CorePlugin::PB_NAMESPACE);

    QQmlEngine engine;
    QString path = QStringLiteral("qrc:/sheet/%1.qml").arg(argv[2]);
    QQmlComponent component(&engine, QUrl(path));
    auto character = component.create();

    if (component.isError()) {
        for (QQmlError err : component.errors()) {
            qWarning() << err.toString();
        }

        qFatal("Character Errors Occured. Exiting");
        return 2;
    }

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Failed to open database");
    }

    Attribute::List attributes;
    ProjectContext::populateInstancesOf<Attribute>(character, attributes);
    populate_db<Attribute>(db, attributes);

    BonusSource::List bonusSources;
    ProjectContext::populateInstancesOf<BonusSource>(character, bonusSources);
    populate_db<BonusSource>(db, bonusSources);

    return 0;
}

template <>
const QString ResourceInfo<Attribute>::tableName = "Attributes";

template <>
std::function<bool(Attribute*)> ResourceInfo<Attribute>::enabled =
        [](Attribute *a) -> bool { return !a->readOnly(); };

template <>
std::function<bool(Attribute*)> ResourceInfo<Attribute>::valid =
        std::bind(&Attribute::fetchId, std::placeholders::_1);

template <>
const QString ResourceInfo<BonusSource>::tableName = "BonusSources";

template <>
std::function<bool(BonusSource*)> ResourceInfo<BonusSource>::enabled =
        std::bind(&BonusSource::isConditional, std::placeholders::_1);

template <>
std::function<bool(BonusSource*)> ResourceInfo<BonusSource>::valid =
        std::bind(&BonusSource::fetchDbValues, std::placeholders::_1);

template <typename T>
void populate_db(QSqlDatabase &db, QList<T*> input) {

    QList<T*> writable;
    std::copy_if(input.begin(), input.end(), std::back_inserter(writable),
                 ResourceInfo<T>::enabled);

    QList<T*> nonDb;
    std::remove_copy_if(writable.begin(), writable.end(),
                        std::back_inserter(nonDb), ResourceInfo<T>::valid);

    qDebug() << "Processing" << ResourceInfo<T>::tableName;
    qDebug() << "Total :" << input.length();
    qDebug() << "Read Only :" << input.length() - writable.length();
    qDebug() << "Already in Database :" << writable.length() - nonDb.length();

    if (nonDb.isEmpty()) {
        qDebug() << "Nothing to do.";
        return;
    }

    QVariantList paths;
    std::transform(nonDb.begin(), nonDb.end(), std::back_inserter(paths),
                   [](T *a) {return a->uri();});

    Q_ASSERT(db.isOpen());

    QSqlQuery query;
    auto qstr = QStringLiteral("INSERT INTO %1 (uri) VALUES (:uri)")
            .arg(ResourceInfo<T>::tableName);
    query.prepare(qstr);
    query.bindValue(":uri", paths);

    db.transaction();
    if(!query.execBatch()) {
        qWarning() << query.lastError();
        qFatal("Database Error");
        db.rollback();
    }
    qDebug() << query.executedQuery();
    db.commit();

    qDebug() << "Added" << nonDb.length() << "to Databse";
}
