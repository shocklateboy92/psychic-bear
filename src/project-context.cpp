#include "project-context.h"
#include "attribute-ref.h"
#include "resource-filter.h"

ProjectContext::ProjectContext(QObject *parent)
    : QObject(parent), m_resources()
{
}

ProjectContext::~ProjectContext()
{

}

void ProjectContext::setCharacterRoot(QObject *root)
{
    QHash<QString, Attribute*> attributeUriMap;
    QList<Attribute*> attributeList;

    populateInstancesOf<Attribute>(root, attributeList);

    for (Attribute *a : attributeList) {
        attributeUriMap[a->uri()] = a;
    }

    QList<AttributeRef*> attributeRefList;
    populateInstancesOf<AttributeRef>(root, attributeRefList);

    for (AttributeRef *a : attributeRefList) {
        if (attributeUriMap[a->targetUri()] != nullptr) {
            a->setTarget(attributeUriMap[a->targetUri()]);
        }
    }

    populateInstancesOf<Resource>(root, m_resources);
}

Resource::List ProjectContext::allResources()
{
    return m_resources;
}
