#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <src/attribute-manager.h>
#include <src/bonus-source.h>
#include <src/project-context.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("psychic_bear",
                                             new ProjectContext(&engine));

    qmlRegisterType<Attribute>("org.lasath.psychic_bear", 1, 0, "Attribute");
    qmlRegisterType<Bonus>("org.lasath.psychic_bear", 1, 0, "Bonus");
    qmlRegisterType<BonusSource>("org.lasath.psychic_bear", 1, 0, "BonusSource");

    QQmlComponent character(&engine);
    character.loadUrl(QUrl(QStringLiteral("qrc:/sheet/Character.qml")));
    character.create();

    for (Attribute* a : AttributeManager::instance().attributes()) {
        qDebug() << a->name();
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    engine.load(QUrl(QStringLiteral("qrc:/Character.qml")));

    return app.exec();
}
