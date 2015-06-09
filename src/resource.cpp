#include "resource.h"

Resource::Resource(QObject *parent) : QObject(parent)
{
}

QString Resource::name() const
{
    return m_name;
}

QString Resource::uri() const
{
    return m_uri;
}

void Resource::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Resource::setUri(QString uri)
{
    if (m_uri == uri)
        return;

    m_uri = uri;
    emit uriChanged(uri);
}
