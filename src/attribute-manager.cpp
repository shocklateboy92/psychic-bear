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
    return m_attributes;
}

void AttributeManager::addAttribute(Attribute *attr)
{
    m_attributes.append(attr);
}
