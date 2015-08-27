#ifndef UIMODULE_H
#define UIMODULE_H

#include <QQuickItem>

class Resource;

class UiModule : public QQuickItem
{
    using ResourceList = QList<Resource*>;

    Q_OBJECT
    Q_PROPERTY(QStringList requiredResources READ requiredResources
               WRITE setRequiredResources NOTIFY requiredResourcesChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString moduleId READ moduleId WRITE setModuleId NOTIFY moduleIdChanged)
    Q_PROPERTY(ResourceList resources READ resources NOTIFY resourcesChanged)

public:
    UiModule();

    QString      moduleId() const;
    QString      name() const;
    QStringList  requiredResources() const;
    ResourceList resources() const;

signals:
    void resourcesChanged(ResourceList resources);
    void moduleIdChanged(QString moduleId);
    void nameChanged(QString name);
    void requiredResourcesChanged(QStringList requiredResources);

public slots:
    void setModuleId(QString moduleId);
    void setName(QString name);
    void setRequiredResources(QStringList requiredResources);

private:
    ResourceList m_resources;
    QString m_moduleId;
    QString m_name;
    QStringList m_requiredResources;
};

#endif // UIMODULE_H
