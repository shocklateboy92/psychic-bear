#include <QApplication>
#include <QQmlApplicationEngine>
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


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
