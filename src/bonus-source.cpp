#include "bonus-source.h"

BonusSource::BonusSource(QObject *parent) : QObject(parent)
{

}

BonusSource::~BonusSource()
{

}

QString BonusSource::name() const
{
    return m_name;
}

QString BonusSource::uri() const
{
    return m_uri;
}

void BonusSource::setName(QString arg)
{
    if (m_name == arg)
        return;

    m_name = arg;
    emit nameChanged(arg);
}

void BonusSource::setUri(QString arg)
{
    if (m_uri == arg)
        return;

    m_uri = arg;
    emit uriChanged(arg);
}

