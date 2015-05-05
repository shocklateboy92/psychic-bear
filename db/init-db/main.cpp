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


template <typename T>
void populate_db(QSqlDatabase &db, QList<T*> input);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 2) {
        qWarning() << "Usage:" << argv[0] << " <db_name>";
        return 2;
    }

    const QString dbPath = argv[1];

    CorePlugin plugin;
    plugin.registerTypes(CorePlugin::PB_NAMESPACE);

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

    populate_db<Attribute>(db, AttributeManager::instance().attributes());

    return 0;
}

template <typename T> struct ResourceInfo {
    static std::function<bool()> enabled;
    static const QString tableName;
};

template <>
const QString ResourceInfo<Attribute>::tableName = "Attributes";

template <typename T>
void populate_db(QSqlDatabase &db, QList<T*> input) {

    QList<T*> writable;
    std::copy_if(input.begin(), input.end(), std::back_inserter(writable),
                 [](T* a) {return !a->readOnly();});

    QList<T*> nonDb;
    std::copy_if(writable.begin(), writable.end(), std::back_inserter(nonDb),
                 [](T *a) {return !a->fetchId();});

    qDebug() << "Total Attribtues :" << input.length();
    qDebug() << "Read Only Ts :" << input.length() - writable.length();
    qDebug() << "Ts in Databse :" << writable.length() - nonDb.length();

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
    }
    qDebug() << query.executedQuery();
    db.commit();

    qDebug() << "Added" << nonDb.length() << " Ts to Databse";
}
