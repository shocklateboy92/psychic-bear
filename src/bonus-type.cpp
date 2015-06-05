#include "bonus-type.h"

BonusType::BonusType(QObject *parent) : QObject(parent)
{


}

QString BonusType::name() const
{
    return m_name;
}

bool BonusType::stacking() const
{
    return m_stacking;
}

void BonusType::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void BonusType::setStacking(bool stacking)
{
    if (m_stacking == stacking)
        return;

    m_stacking = stacking;
    emit stackingChanged(stacking);
}

QString BonusType::uri() const
{
    return m_uri;
}

void BonusType::setUri(QString uri)
{
    if (m_uri == uri)
        return;

    m_uri = uri;
    emit uriChanged(uri);
}

