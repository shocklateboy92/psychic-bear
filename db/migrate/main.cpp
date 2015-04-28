#include "db-info.h"

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QSqlDriver>
#include <QSqlQuery>

static const int CURRENT_VERSION = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        qWarning() << "Usage:" << argv[0] << "<db_name>.db [<character_id>]";
        return 1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(argv[1]);
    if (!db.open()) {
        qWarning() << db.lastError();
        qFatal("Database Error.");
    }

    Q_ASSERT(db.driver()->hasFeature(QSqlDriver::Transactions));

    DbInfo info;
    info.initializeDb(db);
    info.read(db);

    if (info.characterId().isNull()) {
        info.setCharacterId(argv[2]);
    }
    if (info.characterId() != argv[2]) {
        qFatal("Database belongs to different character.");
    }

    bool success = db.transaction();
    Q_ASSERT(success);

    for (int version = info.version(); version < CURRENT_VERSION; version++) {
        auto f = QStringLiteral(":/schema/%1.sql").arg(version + 1);
        QFile schemaFile(f);
        Q_ASSERT(schemaFile.exists());

        success = schemaFile.open(QFile::ReadOnly);
        Q_ASSERT(success);

        // Ghetto parser because SQLITE doesn't allow executing
        // multiple statements for <air_quotes>security</air_quotes>
        auto statements = schemaFile.readAll().split(';');
        for (QString stmt : statements) {
            // skip the trailing whitespace, effectively
            if (stmt.trimmed().isEmpty()) {
                continue;
            }

            QSqlQuery query(db);
            query.prepare(stmt);
            if (!DbInfo::execute(query)) {
                qFatal("SQL Error in Schema.");
            }
        }
    }

    info.setVersion(CURRENT_VERSION);
    info.write(db);

    db.commit();

    return 0;
}
