#include "container-window.h"
#include "ui-module.h"

#include <QtQuickWidgets/QQuickWidget>

#include <QDockWidget>

const QString ContainerWindow::VIEW_PATH_PATTERN
                = QStringLiteral("qrc:/ui/*View.qml");

const QStringList ContainerWindow::MODULE_SRC_PATHS = {
    "qrc:/ui/modules/AbilityScoresModule.qml"
};

ContainerWindow::ContainerWindow(QWidget *parent) : QMainWindow(parent)
{

}

void ContainerWindow::setupUi()
{
    setWindowTitle("Hello World");

    for (QString path : MODULE_SRC_PATHS) {
        QQuickWidget *widget = new QQuickWidget;
        widget->setSource(QUrl(path));

        UiModule *module = qobject_cast<UiModule*>(widget->rootObject());
        Q_ASSERT(module);

        QDockWidget *dock = new QDockWidget(module->name());
        dock->setWidget(widget);

        addDockWidget(Qt::LeftDockWidgetArea, dock);
    }
}

QList<QDockWidget *> ContainerWindow::createViews(QList<UiModule *> modules)
{
    return {};
}

QList<UiModule *> ContainerWindow::createModules(QStringList paths)
{
    return {};
}

