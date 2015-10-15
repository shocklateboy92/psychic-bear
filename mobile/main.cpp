#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <core_plugin.h>
#include <project-context.h>

#include "../app/ui-module.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CorePlugin().registerTypes("org.lasath.psychic_bear");
    qmlRegisterType<UiModule>("org.lasath.psychic_bear.ui", 1, 0, "Module");

    QQmlApplicationEngine engine;
    QQmlComponent character(&engine);
    ProjectContext context(&engine);

    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/%1.qml").arg("fernie/Character")));
    if (character.isError()) {
        qWarning() << character.errors();
    } else {
        auto charObject = character.create();
        context.setCharacterRoot(charObject);
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    for (QObject *obj : engine.rootObjects()) {
        for (UiModule *module : obj->findChildren<UiModule*>()) {
            module->updateMatchingResources(context.allResources());
        }
    }

    return app.exec();
}
