#include "container-window.h"
#include "ui-module.h"
#include "project-context.h"

#include <QtQuickWidgets/QQuickWidget>

#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QQmlEngine>
#include <QSettings>
#include <resource-filter.h>

const QStringList ContainerWindow::MODULE_SRC_PATHS = {
    "qrc:/ui/scores/AbilityScoresModule.qml",
    "qrc:/ui/info/AttributeInfoModule.qml",
    "qrc:/ui/attrs/CombatAttributesModule.qml",
    "qrc:/ui/attrs/SkillAttributesModule.qml",
    "qrc:/ui/conds/ConditionsModule.qml",
    "qrc:/ui/spells/SpontaneousSpellsModule.qml",
    "qrc:/ui/spells/PreparedSpellsModule.qml",
    "qrc:/ui/attrs/CastingAttributesModule.qml",
    "qrc:/ui/attrs/RiddleAttribute.qml",
    "qrc:/ui/attrs/RiddleSaps.qml"
};

static const int SETTINGS_VERSION = 8;

ContainerWindow::ContainerWindow(QWidget *parent)
    : QMainWindow(parent), m_engine(new QQmlEngine(this)),
      m_context(nullptr)
{

}

void ContainerWindow::setProjectContext(ProjectContext *context)
{
    m_context = context;
}

QQuickWidget* ContainerWindow::createWidget(const QString &path) {
    // I think the dock will take ownership of this later
    QQuickWidget *widget = new QQuickWidget(m_engine, this);

    widget->setSource(QUrl(path));
    widget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    for (auto err : widget->errors()) {
        qWarning() << err;
    }

    return widget;
}

UiModule * ContainerWindow::createModule(QQuickWidget* widget)
{
    UiModule *module = qobject_cast<UiModule*>(widget->rootObject());
    Q_ASSERT(module);
    Q_ASSERT(!module->moduleId().isEmpty());


    return module;
}

QDockWidget * ContainerWindow::createDock(UiModule *module, QQuickWidget* widget)
{
    QDockWidget *dock = new QDockWidget(module->name());
    dock->setObjectName(module->moduleId());
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

    readSettings();
}

void ContainerWindow::readSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray(), SETTINGS_VERSION);
}

void ContainerWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState(SETTINGS_VERSION));
    settings.sync();
}
ProjectContext *ContainerWindow::context() const
{
    return m_context;
}


void ContainerWindow::closeEvent(QCloseEvent *e)
{
    writeSettings();

    e->accept();
}
