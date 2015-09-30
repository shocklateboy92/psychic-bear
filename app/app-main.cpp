#include <QApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <core_plugin.h>

#include <src/resource-filter.h>

#include <app/container-window.h>

#include <src/attribute-manager.h>
#include <src/bonus-source.h>
#include <src/project-context.h>
#include "db.h"
#include "ui-module.h"

static const char * PB_UI_NAMESPACE = "org.lasath.psychic_bear.ui";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Lasath Foundation");
    app.setOrganizationDomain("lasath.org");
    app.setApplicationName("Psychic Bear");

    QQmlApplicationEngine engine;
    QQmlComponent character(&engine);
    ProjectContext context(&engine);

    CorePlugin().registerTypes(CorePlugin::PB_NAMESPACE);

    if (argc < 2) {
        qWarning() << "usage:" << argv[0] << "<character_name>";
        return 2;
    }

    db::initialize();

    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/%1.qml").arg(argv[1])));
    if (character.isError()) {
        qWarning() << character.errors();
    } else {
        auto charObject = character.create();
        context.setCharacterRoot(charObject);
    }

    for (Resource *a : context.allResources()) {
        if (a->isDynamic()) {
            bool success = a->initDb();
            if (!success) {
                qWarning() << "failed to initialize DB for" << a->name();
            }
        }
    }

    engine.rootContext()->setContextProperty("psychic_bear", &context);

    qmlRegisterType<UiModule>(PB_UI_NAMESPACE, 1, 0, "Module");

    ContainerWindow root(nullptr);
    root.setProjectContext(&context);
    root.setupUi();
    root.setVisible(true);

    return app.exec();
}
