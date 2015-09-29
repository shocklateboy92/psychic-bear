#ifndef CONTAINERWINDOW_H
#define CONTAINERWINDOW_H

#include <QMainWindow>

class QQmlEngine;
class UiModule;
class QQuickWidget;
class ProjectContext;

class ContainerWindow : public QMainWindow
{
    Q_OBJECT

    //TODO: make this inline when VS2015 is supported
    static const QStringList MODULE_SRC_PATHS;
public:
    explicit ContainerWindow(QWidget *parent = 0);

    ProjectContext *context() const;
    void setProjectContext(ProjectContext *context);

public slots:
    void setupUi();

    void readSettings();
    void writeSettings();

private:
    QQmlEngine* m_engine;
    ProjectContext *m_context;

    QQuickWidget* 	createWidget(const QString &path);
    UiModule* 		createModule(QQuickWidget *widget);
    QDockWidget* 	createDock(UiModule *module, QQuickWidget *widget);
    QAction* 		createAction(QMenu *views, UiModule *module);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);
};

#endif // CONTAINERWINDOW_H
