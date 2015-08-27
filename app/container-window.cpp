#include "container-window.h"

const QString ContainerWindow::VIEW_PATH_PATTERN
                = QStringLiteral("qrc:/ui/*View.qml");

ContainerWindow::ContainerWindow(QWidget *parent) : QMainWindow(parent)
{

}

void ContainerWindow::setupUi()
{
    setWindowTitle("Hello World");
}

QList<QDockWidget *> ContainerWindow::createViews(QList<UiModule *> modules)
{
    return {};
}

QList<UiModule *> ContainerWindow::createModules(QStringList paths)
{
    return {};
}

