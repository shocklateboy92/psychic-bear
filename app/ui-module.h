#ifndef UIMODULE_H
#define UIMODULE_H

#include <QQuickItem>

#include "resource.h"

class UiModule : public QQuickItem
{
    using ResourceList = QQmlListProperty<Resource>;

    Q_OBJECT
    Q_PROPERTY(QStringList requiredResources READ requiredResources
               WRITE setRequiredResources NOTIFY requiredResourcesChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString moduleId READ moduleId WRITE setModuleId NOTIFY moduleIdChanged)
    Q_PROPERTY(QQmlListProperty<Resource> matchingResources READ matchingResources
               NOTIFY matchingResourcesChanged)

public:
    UiModule(QQuickItem *parent = nullptr);

    QString      moduleId() const;
    QString      name() const;
    QStringList  requiredResources() const;
    ResourceList matchingResources();

signals:
    void matchingResourcesChanged(ResourceList matchingResources);
    void moduleIdChanged(QString moduleId);
    void nameChanged(QString name);
    void requiredResourcesChanged(QStringList requiredResources);

public slots:
    void setModuleId(QString moduleId);
    void setName(QString name);
    void setRequiredResources(QStringList requiredResources);
    void updateMatchingResources(Resource::List list);

private:
    Resource::List m_resources;
    QString m_moduleId;
    QString m_name;
    QStringList m_requiredResources;
};

#endif // UIMODULE_H
