#ifndef CONTAINERWINDOW_H
#define CONTAINERWINDOW_H

#include <QMainWindow>

class QQmlEngine;
class UiModule;
class QQuickWidget;

class ContainerWindow : public QMainWindow
{
    Q_OBJECT

    //TODO: make this inline when VS2015 is supported
    static const QStringList MODULE_SRC_PATHS;
public:
    explicit ContainerWindow(QWidget *parent = 0);

signals:

public slots:
    void setupUi();

private:
    QQmlEngine* m_engine;

    QQuickWidget* 	createWidget(const QString &path);
    UiModule* 		createModule(QQuickWidget *widget);
    QDockWidget* 	createDock(UiModule *module, QQuickWidget *widget);
    QAction* 		createAction(QMenu *views, UiModule *module);
};

#endif // CONTAINERWINDOW_H
