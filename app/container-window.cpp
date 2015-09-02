#include "container-window.h"
#include "ui-module.h"

#include <QtQuickWidgets/QQuickWidget>

#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>

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

    QMenu *file = new QMenu("File");
    menuBar()->addMenu(file);

    QMenu *views = new QMenu("View");
    menuBar()->addMenu(views);

    QAction *quit = new QAction(this);
    quit->setText("Exit");
    quit->setShortcut(QKeySequence::Quit);
    connect(quit, &QAction::triggered, this, &ContainerWindow::close);
    file->addAction(quit);

    QMenu *help = new QMenu("Help");
    help->addAction("Lol No!");
    menuBar()->addMenu(help);

    for (QString path : MODULE_SRC_PATHS) {
        QQuickWidget *widget = new QQuickWidget;
        widget->setSource(QUrl(path));
        widget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        UiModule *module = qobject_cast<UiModule*>(widget->rootObject());
        Q_ASSERT(module);

        QDockWidget *dock = new QDockWidget(module->name());
        dock->setWidget(widget);

        QAction *action = new QAction(this);
        action->setText(module->name());
        action->setCheckable(true);
        views->addAction(action);

        connect(action, &QAction::triggered, [=](){
            dock->setVisible(action->isChecked());
        });
        connect(dock, &QDockWidget::visibilityChanged, [=](){
            action->setChecked(dock->isVisible());
        });

        addDockWidget(Qt::LeftDockWidgetArea, dock);
    }
}
