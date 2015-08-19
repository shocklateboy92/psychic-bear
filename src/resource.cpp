#include "resource.h"

Resource::Resource(QString table, QQuickItem *parent)
    : QQuickItem(parent), m_db(table)
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

DbUtil& Resource::db()
{
    return m_db;
}

const DbUtil& Resource::db() const
{
    return m_db;
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
