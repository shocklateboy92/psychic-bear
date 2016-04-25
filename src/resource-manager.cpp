#include "resource-manager.h"
#include <QCollator>

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

Resource::List ResourceManager::existingResources()
{
    std::sort(m_resources.begin(), m_resources.end(), [](const Resource * r1, const Resource * r2) -> bool {
        QCollator qc = QCollator();
        qc.setNumericMode(true);
        return qc(r1->name(), r2->name());
    });
    return m_resources;
}

