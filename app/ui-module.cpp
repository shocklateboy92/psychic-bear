#include "ui-module.h"
#include "resource.h"

UiModule::UiModule(QQuickItem *parent)
    : QQuickItem(parent)
{

}

UiModule::ResourceList UiModule::matchingResources()
{
    return ResourceList(dynamic_cast<QObject*>(this), m_resources);
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

void UiModule::updateMatchingResources(Resource::List list)
{
    m_resources.clear();

    for (QString &pattern : requiredResources()) {
        QRegExp regex(pattern, Qt::CaseInsensitive, QRegExp::Wildcard);
        for (Resource *res : list) {
            if (regex.exactMatch(res->uri())) {
                m_resources.append(res);
            }
        }
    }

    emit matchingResourcesChanged(matchingResources());
}

