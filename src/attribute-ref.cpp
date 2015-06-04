#include "attribute-ref.h"

AttributeRef::AttributeRef()
{

}

QString AttributeRef::uri() const
{
    return m_uri;
}

QString AttributeRef::target() const
{
    return m_target;
}

void AttributeRef::setUri(QString uri)
{
    if (m_uri == uri)
        return;

    m_uri = uri;
    emit uriChanged(uri);
}

