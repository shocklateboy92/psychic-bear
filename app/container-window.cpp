#include "container-window.h"
#include "ui-module.h"

#include <QtQuickWidgets/QQuickWidget>

#include <QDockWidget>

const QStringList ContainerWindow::MODULE_SRC_PATHS = {
    "qrc:/ui/scores/AbilityScoresModule.qml",
    "qrc:/ui/scores/AbilityScoresModule.qml",
    "qrc:/ui/scores/AbilityScoresModule.qml"
};

ContainerWindow::ContainerWindow(QWidget *parent) : QMainWindow(parent)
{

}

void ContainerWindow::setupUi()
{
    setWindowTitle("Hello World");
    setDockOptions(QMainWindow::AllowNestedDocks
                   | QMainWindow::AllowTabbedDocks
                   | QMainWindow::AnimatedDocks);

    for (QString path : MODULE_SRC_PATHS) {
        QQuickWidget *widget = new QQuickWidget;
        widget->setSource(QUrl(path));
        widget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        UiModule *module = qobject_cast<UiModule*>(widget->rootObject());
        Q_ASSERT(module);

        QDockWidget *dock = new QDockWidget(module->name());
        dock->setWidget(widget);

        addDockWidget(Qt::LeftDockWidgetArea, dock);
    }
}
