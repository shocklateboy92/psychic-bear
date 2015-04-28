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

QStringList DEFAULT_CHARACTERS = {
    "qrc:/sheet/fernie/Character.qml",
//    "qrc:/sheet/zedestructor/Anya.qml"
};


void populate_db(QSqlDatabase &db);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 2) {
        qWarning() << "Usage:" << argv[0] << " <db_name>";
        return 2;
    }

    const QString dbPath = argv[1];

    CorePlugin plugin;
    plugin.registerTypes("org.lasath.psychic_bear");

    QQmlEngine engine;
    for (QString path : DEFAULT_CHARACTERS) {
        QQmlComponent component(&engine, QUrl(path));
        component.create();

        if (component.isError()) {
            for (QQmlError err : component.errors()) {
                qWarning() << err.toString();
            }

            qFatal("Character Errors Occured. Exiting");
        }
    }

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Failed to open database");
    }

    populate_db(db);

    return 0;
}

void populate_db(QSqlDatabase &db) {
    auto all = AttributeManager::instance().attributes();

    AttributeManager::AttributeList writable;
    std::copy_if(all.begin(), all.end(), std::back_inserter(writable),
                 [](Attribute* a) {return !a->readOnly();});

    AttributeManager::AttributeList nonDb;
    std::copy_if(writable.begin(), writable.end(), std::back_inserter(nonDb),
                 [](Attribute *a) {return !a->fetchId();});

    qDebug() << "Total Attribtues :" << all.length();
    qDebug() << "Read Only Attributes :" << all.length() - writable.length();
    qDebug() << "Attributes in Databse :" << writable.length() - nonDb.length();

    if (nonDb.isEmpty()) {
        qDebug() << "Nothing to do.";
        return;
    }

    QVariantList paths;
    std::transform(nonDb.begin(), nonDb.end(), std::back_inserter(paths),
                   [](Attribute *a) {return a->uri();});

    Q_ASSERT(db.isOpen());

    QSqlQuery query;
    query.prepare("INSERT INTO Attributes (uri) VALUES (:uri)");
    query.bindValue(":uri", paths);

    db.transaction();
    if(!query.execBatch()) {
        qWarning() << query.lastError();
        qFatal("Database Error");
    }
    qDebug() << query.executedQuery();
    db.commit();

    qDebug() << "Added" << nonDb.length() << " Attributes to Databse";
}
