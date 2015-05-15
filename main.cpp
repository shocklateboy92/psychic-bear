#include <QApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <core_plugin.h>

#include <src/filtered-attribute-list.h>

#include <src/attribute-manager.h>
#include <src/bonus-source.h>
#include <src/project-context.h>
#include "db.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlComponent character(&engine);
    ProjectContext context(&engine);

    CorePlugin().registerTypes(CorePlugin::PB_NAMESPACE);

    db::initialize();

    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/fernie/Character.qml")));
    if (character.isError()) {
        qWarning() << character.errors();
    } else {
        auto charObject = character.create();
        context.setCharacterRoot(charObject);
    }

    for (Attribute *a : AttributeManager::instance().attributes()) {
        a->fetchId();
    }

    engine.rootContext()->setContextProperty("psychic_bear", &context);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
