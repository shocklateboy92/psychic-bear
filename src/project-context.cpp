#include "project-context.h"

ProjectContext::ProjectContext(QObject *parent) : QObject(parent)
{

}

ProjectContext::~ProjectContext()
{

}

AttributeManager::AttributeList ProjectContext::all_attributes() const
{
    return m_all_attributes;
}

