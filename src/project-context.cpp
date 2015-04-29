#include "project-context.h"

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

void ProjectContext::populateWith(QObject *root)
{
    populateInstancesOf(root, m_bonusSrcList);
}

template <typename T>
void ProjectContext::populateInstancesOf(QObject *obj, QList<T> &res) {
    auto cast = qobject_cast<T>(obj);
    if (cast) {
        res.append(cast);
    }

    for (QObject *child : obj->children()) {
        populateInstancesOf(child, res);
    }
}
