#include "bonus.h"
#include "bonus-source.h"

Bonus::Bonus(QQuickItem *parent)
    : QQuickItem(parent), m_amount(0)
{
}

Bonus::~Bonus()
{

}

int Bonus::amount() const
{
    return m_amount;
}

QString Bonus::name() const
{
    if (m_name.isNull() && m_source != nullptr) {
        return m_source->name();
    }

    return m_name;
}

Bonus::Source Bonus::source() const
{
    return m_source;
}

int Bonus::add(int acc, const Bonus *a)
{
    return acc + a->amount();
}

void Bonus::setAmount(int arg)
{
    if (m_amount == arg)
        return;

    m_amount = arg;
    emit amountChanged(arg);
}

void Bonus::setName(QString arg)
{
    if (m_name == arg)
        return;

    m_name = arg;
    emit nameChanged(arg);
}

void Bonus::setSource(Source arg)
{
    if (m_source == arg)
        return;

    m_source = arg;
    emit sourceChanged(arg);
}

