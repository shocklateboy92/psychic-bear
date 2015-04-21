#include "db.h"

#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

void db::initialize()
{
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(DB_FILE);
        bool open = db.open();
        if (!open) {
            qWarning() << "Failed to open database " << DB_FILE << ":" << db.lastError();
            qWarning() << "Runtime Static Modifiers are disabled";
        }

//    if (!QFile(DB_FILE).exists()) {

//        QFile schemaFile(":/db/schema.sql");
//        bool fileOpen = schemaFile.open(QIODevice::ReadOnly);
//        Q_ASSERT(fileOpen);

//        for (auto &statement : schemaFile.readAll().split(';')) {
//            QSqlQuery query;
//            query.prepare(schemaFile.readAll());

//            bool success = query.exec();
//            if (!success) {
//                qWarning() << "Error creating database";
//                qWarning() << "Could not execute '"
//                           << statement
//                           << "': "
//                           << query.lastError();
//            }
//        }
//    }
}
