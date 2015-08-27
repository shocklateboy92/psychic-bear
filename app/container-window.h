#ifndef CONTAINERWINDOW_H
#define CONTAINERWINDOW_H

#include <QMainWindow>

class UiModule;

class ContainerWindow : public QMainWindow
{
    Q_OBJECT

    //TODO: make this inline when VS2015 is supported
    static const QString VIEW_PATH_PATTERN;
public:
    explicit ContainerWindow(QWidget *parent = 0);

signals:

public slots:
    void setupUi();

private:
    static QList<QDockWidget*> createViews(QList<UiModule*> modules);
    static QList<UiModule*> createModules(QStringList paths);
};

#endif // CONTAINERWINDOW_H
