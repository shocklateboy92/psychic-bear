#include "attribute-ref.h"
#include "attribute.h"

AttributeRef::AttributeRef(QObject *parent)
    : QObject(parent), m_target(nullptr)
{

}

AttributeRef::~AttributeRef()
{

}

QString AttributeRef::targetUri() const
{
    return m_targetUri;
}

Attribute* AttributeRef::target() const
{
    return m_target;
}

void AttributeRef::setTargetUri(QString arg)
{
    if (m_targetUri == arg)
        return;

    m_targetUri = arg;
    emit targetUriChanged(arg);
}

void AttributeRef::setTarget(Attribute* arg)
{
    if (m_target == arg)
        return;

    m_target = arg;
    emit targetChanged(arg);
}
