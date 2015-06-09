#include "bonus.h"
#include "bonus-source.h"
#include "bonus-type.h"
#include "attribute.h"

Bonus::Bonus(QQuickItem *parent)
    : Resource(parent), m_amount(0), m_target(nullptr),
      m_source(nullptr), m_type(BonusType::noneType())
{
}

Bonus::~Bonus()
{

}

int Bonus::amount() const
{
    if (m_source != nullptr && !m_source->isActive()){
        return 0;
    }
    return m_amount;
}

QString Bonus::name() const
{
    if (Resource::name().isNull() && m_source != nullptr) {
        return m_source->name();
    }

    return Resource::name();
}

Bonus::Source Bonus::source() const
{
    return m_source;
}

Attribute *Bonus::target() const
{
    return m_target;
}

int Bonus::add(int acc, const Bonus *a)
{
    return acc + a->amount();
}

BonusType* Bonus::type() const
{
    return m_type;
}

void Bonus::setAmount(int arg)
{
    if (m_amount == arg)
        return;

    m_amount = arg;
    emit amountChanged(arg);
}

void Bonus::setSource(Source arg)
{
    if (m_source == arg)
        return;

    m_source = arg;
    QObject::connect(arg, &BonusSource::activeChanged, this, &Bonus::amountChanged);
    emit sourceChanged(arg);
}

void Bonus::setTarget(Attribute *arg)
{
    if (m_target == arg)
        return;

    m_target = arg;
    emit targetChanged(arg);

    m_target->addModifier(this);
}

void Bonus::setType(BonusType* type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

