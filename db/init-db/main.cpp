#include <QCoreApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <attribute.h>

#include <QSqlQuery>
#include <core_plugin.h>
#include <functional>
#include <project-context.h>
#include <bonus-source.h>
#include <attribute.h>

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

    QString path = QStringLiteral("qrc:/sheet/%1.qml").arg(argv[2]);
    ProjectContext context;

    if (!context.createCharacter(path)) {
        qFatal("Character Errors Occured. Exiting");
        return 2;
    }

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Failed to open database");
    }

    populate_db<Resource>(db,context.allResources());

    return 0;
}

template <typename T>
void populate_db(QSqlDatabase &db, QList<T*> input) {

    QList<T*> writable;
    std::copy_if(input.begin(), input.end(), std::back_inserter(writable),
                 std::bind(&Resource::isDynamic, std::placeholders::_1));

    QList<T*> nonDb;
    std::remove_copy_if(writable.begin(), writable.end(),
                        std::back_inserter(nonDb),
                        std::bind(&Resource::initDb, std::placeholders::_1));

    qDebug() << "Processing All Resources";
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

    db.transaction();

    for (Resource *res : nonDb) {
        QSqlQuery query;
        auto qstr = QStringLiteral("INSERT INTO %1 (uri) VALUES (:uri)")
                .arg(res->db().tableName());
        query.prepare(qstr);

        query.bindValue(":uri", res->uri());
        if(!DbUtil::executeQuery(query)) {
            db.rollback();
            qFatal("Database Error");
        }
        qDebug() << query.executedQuery();

    }
    db.commit();

    qDebug() << "Added" << nonDb.length() << "to Databse";
}
