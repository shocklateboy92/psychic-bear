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

