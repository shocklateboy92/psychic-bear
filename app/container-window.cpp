#include "container-window.h"
#include "ui-module.h"

#include <QtQuickWidgets/QQuickWidget>

#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QQmlEngine>

const QStringList ContainerWindow::MODULE_SRC_PATHS = {
    "qrc:/ui/scores/AbilityScoresModule.qml",
    "qrc:/ui/info/AttributeInfoModule.qml"
};

ContainerWindow::ContainerWindow(QWidget *parent)
    : QMainWindow(parent), m_engine(new QQmlEngine(this))
{

}

QQuickWidget* ContainerWindow::createWidget(const QString &path) {
    // I think the dock will take ownership of this later
    QQuickWidget *widget = new QQuickWidget(m_engine, this);

    widget->setSource(QUrl(path));
    widget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    return widget;
}

UiModule * ContainerWindow::createModule(QQuickWidget* widget)
{
    UiModule *module = qobject_cast<UiModule*>(widget->rootObject());
    Q_ASSERT(module);

    return module;
}

QDockWidget * ContainerWindow::createDock(UiModule *module, QQuickWidget* widget)
{
    QDockWidget *dock = new QDockWidget(module->name());
    dock->setWidget(widget);

    return dock;
}

QAction * ContainerWindow::createAction(QMenu *views, UiModule *module)
{
    QAction *action = new QAction(this);
    action->setText(module->name());
    action->setCheckable(true);
    views->addAction(action);

    return action;
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
        QQuickWidget *widget = createWidget(path);

        UiModule *module = createModule(widget);

        QDockWidget *dock = createDock(module, widget);

        QAction *action = createAction(views, module);

        connect(action, &QAction::triggered, [=](){
            dock->setVisible(action->isChecked());
        });
        connect(dock, &QDockWidget::visibilityChanged, [=](){
            action->setChecked(dock->isVisible());
        });

        addDockWidget(Qt::LeftDockWidgetArea, dock);
    }
}
