#include "db-info.h"

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        qWarning() << "Usage:" << argv[0] << "<db_name>.db [<character_id>]";
        return 1;
    }

    bool newDb = (!QFile(argv[1]).exists());

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(argv[1]);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Database Error.");
    }

    DbInfo info;
//    if (newDb) {
//        info.setCharacterId(argv[2]);
        info.initializeDb(db);
        info.setVersion(0);
        info.write(db);
//    }

//    return a.exec();
    return 0;
}
