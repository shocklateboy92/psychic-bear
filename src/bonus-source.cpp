#include "bonus-source.h"

BonusSource::BonusSource(QObject *parent)
    : QObject(parent), m_conditional(false)
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

bool BonusSource::isActive() const
{
    return m_active;
}

bool BonusSource::isConditional() const
{
    return m_conditional;
}

bool BonusSource::isEffectivelyConditional() const
{
    return m_conditional && m_db.isValid();
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

void BonusSource::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active = active;
    if (m_db.isValid()) {
        m_db.writeProperty("active", m_active);
    }

    emit activeChanged(active);
}

void BonusSource::setConditional(bool conditional)
{
    if (m_conditional == conditional)
        return;

    m_conditional = conditional;
    emit conditionalChanged(conditional);
}

bool BonusSource::fetchDbValues()
{
    m_db.setTableName("BonusSources");
    bool ret = m_db.fetchId(uri())
            && m_db.fetchProperty("active", m_active);

    if (ret)
        emit activeChanged(isActive());

    return ret;
}

