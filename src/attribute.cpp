#include "Attribute.h"
#include <algorithm>

static void qlist_append(QQmlListProperty<Bonus> *p, Bonus *v);
static int qlist_count(QQmlListProperty<Bonus> *p);
static Bonus *qlist_at(QQmlListProperty<Bonus> *p, int idx);
static void qlist_clear(QQmlListProperty<Bonus> *p);

Attribute::Attribute(QQuickItem *parent)
    : QQuickItem(parent)
{
}

Attribute::~Attribute()
{

}

QQmlListProperty<Bonus> Attribute::modifiers()
{
    return {this, &m_modifiers, qlist_append, qlist_count, qlist_at, qlist_clear};
}

int Attribute::value() const
{
    return std::accumulate(m_modifiers.begin(), m_modifiers.end(), 0, Bonus::add);
}

void Attribute::onModifierChanged(Bonus *m)
{
    Q_UNUSED(m)
    emit valueChanged(value());
}

static void qlist_append(QQmlListProperty<Bonus> *p, Bonus *v) {
    reinterpret_cast<QList<Bonus *> *>(p->data)->append(v);
    auto atr = qobject_cast<Attribute*>(p->object);
    atr->onModifierChanged(v);
    QObject::connect(v, &Bonus::amountChanged,
                     atr, &Attribute::valueChanged);
}
static int qlist_count(QQmlListProperty<Bonus> *p) {
    return reinterpret_cast<QList<Bonus *> *>(p->data)->count();
}
static Bonus *qlist_at(QQmlListProperty<Bonus> *p, int idx) {
    return reinterpret_cast<QList<Bonus *> *>(p->data)->at(idx);
}
static void qlist_clear(QQmlListProperty<Bonus> *p) {
    return reinterpret_cast<QList<Bonus *> *>(p->data)->clear();
    Attribute* atr = qobject_cast<Attribute*>(p->object);
    atr->valueChanged(atr->value());
}
