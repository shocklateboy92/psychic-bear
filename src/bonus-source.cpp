#include "bonus-source.h"
#include "bonus.h"

BonusSource::BonusSource(QQuickItem *parent)
    : Resource("BonusSources", parent), m_active(true), m_conditional(false)
{

}

BonusSource::~BonusSource()
{

}

bool BonusSource::isActive() const
{
    return m_active;
}

bool BonusSource::isConditional() const
{
    return m_conditional;
}

bool BonusSource::isEffectivelyConditional()
{
    return m_conditional && db().isValid();
}

QQmlListProperty<Bonus> BonusSource::effects()
{
    return {
        this,
        &m_effects,
        [](QQmlListProperty<Bonus> *p, Bonus *v) { // append
            auto src = qobject_cast<BonusSource*>(p->object);
            Q_ASSERT (src);
            v->setSource(src);
        },
        [](QQmlListProperty<Bonus> *p) { // count
            auto src = qobject_cast<BonusSource*>(p->object);
            return src->m_effects.count();
        },
        [](QQmlListProperty<Bonus> *p, int idx) { // at
            auto src = qobject_cast<BonusSource*>(p->object);
            return src->m_effects.at(idx);
        },
        [](QQmlListProperty<Bonus> *p) { // clear
            return reinterpret_cast<QList<Bonus *> *>(p->data)->clear();
        }
    };
}

void BonusSource::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active = active;
    if (db().isValid()) {
        db().writeProperty("active", m_active);
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
    db().setTableName("BonusSources");
    bool ret = db().fetchId(uri())
            && db().fetchProperty("active", m_active);

    if (ret)
        emit activeChanged(isActive());

    return ret;
}

