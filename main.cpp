#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include <src/attribute-manager.h>
#include <bonus-source.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Attribute>("org.lasath.psychic_bear", 1, 0, "Attribute");
    qmlRegisterType<Bonus>("org.lasath.psychic_bear", 1, 0, "Bonus");
    qmlRegisterType<BonusSource>("org.lasath.psychic_bear", 1, 0, "BonusSource");

    QQmlComponent character(&engine);
    character.loadUrl(QUrl(QStringLiteral("qrc:/Character.qml")));

    for (Attribute* a : AttributeManager::instance().attributes()) {
        qDebug() << a->objectName();
    }

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Character.qml")));

    return app.exec();
}
