#include "ui-module.h"
#include "resource.h"

UiModule::UiModule(QQuickItem *parent)
    : QQuickItem(parent), m_refList(new ResourceRefList(this))
{
    connect(m_refList, &ResourceRefList::uriFilterChanged,
            this, &UiModule::requiredResourcesChanged);
}

UiModule::ResourceList UiModule::matchingResources()
{
    return m_refList;
}

QString UiModule::moduleId() const
{
    return m_moduleId;
}

QString UiModule::name() const
{
    return m_name;
}

QStringList UiModule::requiredResources() const
{
    return m_refList->uriFilter();
}

void UiModule::setModuleId(QString moduleId)
{
    if (m_moduleId == moduleId)
        return;

    m_moduleId = moduleId;
    emit moduleIdChanged(moduleId);
}

void UiModule::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void UiModule::setRequiredResources(QStringList requiredResources)
{
    m_refList->setUriFilter(requiredResources);
}
