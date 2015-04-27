#include <QCoreApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QDebug>
#include <QFile>

#include <core_plugin.h>

QStringList DEFAULT_CHARACTERS = {
    "qrc:/sheet/fernie/Character.qml",
//    "qrc:/sheet/zedestructor/Anya.qml"
};

const QString DB_PATH = "psychic_bear.db";

void check_db();
void create_db();

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

    if (QFile(DB_PATH).exists()) {
        check_db();
    } else {
        create_db();
    }

    return a.exec();
}

void create_db() {

}

void check_db() {

}
