#include "resource-manager.h"

Q_GLOBAL_STATIC(ResourceManager, singleton)

ResourceManager::ResourceManager(QObject *parent) : QObject(parent)
{
}

ResourceManager *ResourceManager::instance()
{
    return singleton;
}

void ResourceManager::registerResource(Resource *res)
{
    // to remind future me that this end is not thread-safe
    Q_ASSERT(res->thread() == this->thread());

    m_resources.append(res);
    emit resourceCreated(res);
}

Resource::List ResourceManager::existingResources() const
{
    return m_resources;
}

