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

    CorePlugin().registerTypes(CorePlugin::PB_NAMESPACE);
    engine.rootContext()->setContextProperty("psychic_bear",
                                             new ProjectContext(&engine));

    QQmlComponent character(&engine);
    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/fernie/Character.qml")));
    if (character.isError()) {
        qWarning() << character.errors();
    } else {
        character.create();
    }

    db::initialize();

    for (Attribute *a : AttributeManager::instance().attributes()) {
        a->fetchId();
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
