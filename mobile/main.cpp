#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlError>
#include <core_plugin.h>
#include <project-context.h>
#include "../app/ui-module.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CorePlugin().registerTypes("org.lasath.psychic_bear");
    qmlRegisterType<UiModule>("org.lasath.psychic_bear.ui", 1, 0, "Module");

    ProjectContext context;
    context.createCharacter(QUrl(QStringLiteral("qrc:/sheet/%1.qml").arg("fernie/Character")));


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (argc > 1) {
        db.setDatabaseName(argv[1]);
    } else {
        db.setDatabaseName("/sdcard/Download/psychic_bear.db");
    }
    bool open = db.open();
    if (!open) {
        qWarning() << "Failed to open database :" << db.lastError();
        qWarning() << "Runtime Static Modifiers are disabled";
    }

    QSqlQuery().exec("PRAGMA foreign_keys = ON;");

    for (Resource *a : context.allResources()) {
        if (a->isDynamic()) {
            bool success = a->initDb();
            if (!success) {
                qWarning() << "failed to initialize DB for" << a->name();
            }
        }
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
