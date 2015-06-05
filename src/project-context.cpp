#include "project-context.h"
#include "attribute-ref.h"

ProjectContext::ProjectContext(QObject *parent)
    : QObject(parent)
{
}

ProjectContext::~ProjectContext()
{

}

ProjectContext::AttributeList ProjectContext::all_attributes()
{
    return AttributeList(this, AttributeManager::instance().attributes());
}

ProjectContext::BonusSourceList ProjectContext::all_bonus_sources()
{
    return BonusSourceList(this, m_bonusSrcList);
}

void ProjectContext::setCharacterRoot(QObject *root)
{
    populateInstancesOf(root, m_bonusSrcList);
    for (BonusSource *msrc : m_bonusSrcList) {
        msrc->fetchDbValues();
    }

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
}

template <typename T>
void ProjectContext::populateInstancesOf(QObject *obj, QList<T*> &res) {
    auto cast = qobject_cast<T*>(obj);
    if (cast) {
        res.append(cast);
    }

    for (QObject *child : obj->children()) {
        populateInstancesOf(child, res);
    }
}
