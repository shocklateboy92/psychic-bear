#include "bonus-type.h"

BonusType::BonusType(QObject *parent)
    : QObject(parent), m_stacking(false)
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
BonusType *BonusType::noneType()
{
    if (s_noneType == nullptr) {
        s_noneType = new BonusType;
        s_noneType->setStacking(true);
    }
    return s_noneType;
}

BonusType* BonusType::s_noneType = nullptr;
