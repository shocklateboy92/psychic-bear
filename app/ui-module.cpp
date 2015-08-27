#include "ui-module.h"
#include "resource.h"

UiModule::UiModule()
{

}

UiModule::ResourceList UiModule::resources() const
{
    return m_resources;
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
    return m_requiredResources;
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
    if (m_requiredResources == requiredResources)
        return;

    m_requiredResources = requiredResources;
    emit requiredResourcesChanged(requiredResources);
}

