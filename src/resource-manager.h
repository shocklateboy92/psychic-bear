#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "resource.h"

class ResourceManager : public QObject
{
    Q_OBJECT
public:
    explicit ResourceManager(QObject *parent = 0);

    static ResourceManager* instance();
    Resource::List existingResources();

signals:
    void resourceCreated(Resource *res);

public slots:
    void registerResource(Resource* res);

private:
    Resource::List m_resources;
};

#endif // RESOURCEMANAGER_H
