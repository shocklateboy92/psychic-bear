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

const QString DB_PATH = "psychic_bear.db";

void check_db(QSqlDatabase &db);
void create_db(QSqlDatabase &db);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

    bool createTables = !QFile(DB_PATH).exists();

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Failed to open database");
    }

    if (createTables) {
        create_db(db);
    }

    check_db(db);

    return 0;
}

void create_db(QSqlDatabase &db) {
    auto all = AttributeManager::instance().attributes();
    AttributeManager::AttributeList writable;
    std::copy_if(all.begin(), all.end(), std::back_inserter(writable),
                 [](Attribute* a) {return !a->readOnly();});

    qDebug() << "Total Attribtues :" << all.length();
    qDebug() << "Read Only Attributes :" << all.length() - writable.length();

    if (writable.isEmpty()) {
        qDebug() << "Nothing to do.";
        return;
    }

    QStringList paths;
    std::transform(writable.begin(), writable.end(),
                   std::back_inserter(paths),
                   [](Attribute *a) {return a->uri();});

    Q_ASSERT(db.isOpen());

    QSqlQuery query;
    query.prepare("INSERT INTO Attributes VALUES (:uri)");
    query.bindValue(":uri", paths);

    if(!query.execBatch()) {
        qWarning() << query.lastError();
        qFatal("Database Error");
    }
}

void check_db(QSqlDatabase &db) {
}
