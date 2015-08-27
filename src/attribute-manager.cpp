#include "attribute-manager.h"

AttributeManager::AttributeManager()
{

}

AttributeManager::~AttributeManager()
{

}

AttributeManager AttributeManager::m_instance = AttributeManager();

AttributeManager &AttributeManager::instance()
{
    return m_instance;
}

AttributeManager::AttributeList &AttributeManager::attributes()
{
    qSort(m_attributes.begin(), m_attributes.end(), [](const Attribute* v1, const Attribute* v2){return v1->name() < v2->name();});
    return m_attributes;
}

void AttributeManager::addAttribute(Attribute *attr)
{
    m_attributes.append(attr);
}
