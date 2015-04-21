#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <src/filtered-attribute-list.h>

#include <src/attribute-manager.h>
#include <src/bonus-source.h>
#include <src/project-context.h>
#include "db.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("psychic_bear",
                                             new ProjectContext(&engine));

    qmlRegisterType<Attribute>("org.lasath.psychic_bear", 1, 0, "Attribute");
    qmlRegisterType<Bonus>("org.lasath.psychic_bear", 1, 0, "Bonus");
    qmlRegisterType<BonusSource>("org.lasath.psychic_bear", 1, 0, "BonusSource");
    qmlRegisterType<FilteredAttributeList>("org.lasath.psychic_bear", 1, 0, "FilteredAttributeList");

    QQmlComponent character(&engine);
    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/Character.qml")));
    character.create();

    db::initialize();

    for (Attribute *a : AttributeManager::instance().attributes()) {
        a->fetchId();
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
