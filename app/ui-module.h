#ifndef UIMODULE_H
#define UIMODULE_H

#include <QQuickItem>
#include <resource-ref-list.h>

#include "resource.h"

class UiModule : public QQuickItem
{
    using ResourceList = ResourceRefList*;

    Q_OBJECT
    Q_PROPERTY(QStringList requiredResources READ requiredResources
               WRITE setRequiredResources NOTIFY requiredResourcesChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString moduleId READ moduleId WRITE setModuleId NOTIFY moduleIdChanged)
    Q_PROPERTY(QAbstractListModel* matchingResources
               READ matchingResources NOTIFY matchingResourcesChanged)

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

private:
    QString m_moduleId;
    QString m_name;

    ResourceList m_refList;
};

#endif // UIMODULE_H
