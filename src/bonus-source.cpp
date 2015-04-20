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

void BonusSource::setName(QString arg)
{
    if (m_name == arg)
        return;

    m_name = arg;
    emit nameChanged(arg);
}

