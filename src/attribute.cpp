#include "attribute.h"
#include "attribute-manager.h"
#include "bonus-type.h"
#include <algorithm>
#include <numeric>

Attribute::Attribute(QQuickItem *parent)
    : QQuickItem(parent), m_readOnly(true)
{
    AttributeManager::instance().addAttribute(this);
}

Attribute::~Attribute()
{

}

bool Attribute::fetchId()
{
    bool success = m_db.fetchId(uri());
    if (!success) {
        qWarning() << "Failed to find Database entry for "
                   << name() << ":" << uri();
    }

    return success;
}

QQmlListProperty<Bonus> Attribute::modifiers()
{
    return {this, &m_modifiers, qlist_append, qlist_count, qlist_at, qlist_clear};
}

int Attribute::value() const
{
    QHash<BonusType*, int> typeMap;

    for (Bonus* b : m_modifiers) {
        if (!typeMap.contains(b->type())) {
            typeMap.insert(b->type(), b->amount());
        } else {
            if (b->type()->stacking()){
                typeMap[b->type()] += b->amount();
            } else {
                typeMap[b->type()] = std::max(typeMap[b->type()], b->amount());
            }

        }
    }

    auto a = typeMap.values();

    return std::accumulate(
                m_static_modifiers.begin(),
                m_static_modifiers.end(),
                std::accumulate(
                    a.begin(),
                    a.end(),
                    0),
                Bonus::add);
}

QString Attribute::name() const
{
    return m_name;
}

QString Attribute::uri() const
{
    return m_uri;
}

bool Attribute::readOnly() const
{
    return m_readOnly || m_db.error();
}

void Attribute::onModifierChanged(Bonus *m)
{
    Q_UNUSED(m)
    emit valueChanged(value());
}

void Attribute::setName(QString arg)
{
    if (m_name == arg)
        return;

    m_name = arg;
    emit nameChanged(arg);
}

void Attribute::setUri(QString arg)
{
    if (m_uri == arg)
        return;

    m_uri = arg;
    emit uriChanged(arg);
}

void Attribute::setReadOnly(bool arg)
{
    if (m_readOnly == arg)
        return;

    m_readOnly = arg;
    emit readOnlyChanged(readOnly());
}

void Attribute::addModifier(Bonus *arg)
{
    m_modifiers.append(arg);
    onModifierChanged(arg);
    QObject::connect(arg, &Bonus::amountChanged,
                     this, &Attribute::valueChanged);
}

void Attribute::updateStaticModifiers()
{
    if (m_db.error()) {
        qWarning() << "Static modifiers disabled on"
                   << uri() << "due to previous errors";
        return;
    }

    for (Bonus *b : m_static_modifiers) {
        b->deleteLater();
    }
    m_static_modifiers.clear();
    m_static_modifiers = m_db.readModifiers(this);

    emit modifiersChanged(modifiers());
    emit valueChanged(value());
}

bool Attribute::createStaticModifier(int amount, const QString &name)
{
    bool success = m_db.createModifier(amount, name);

    // Refresh view whether update was successful or not
    updateStaticModifiers();

    return success;
}

void Attribute::qlist_append(QQmlListProperty<Bonus> *p, Bonus *v) {
    auto atr = qobject_cast<Attribute*>(p->object);
    atr->addModifier(v);
}
int Attribute::qlist_count(QQmlListProperty<Bonus> *p) {
    auto attr = qobject_cast<Attribute*>(p->object);
    return attr->m_modifiers.count() + attr->m_static_modifiers.count();
}
Bonus* Attribute::qlist_at(QQmlListProperty<Bonus> *p, int idx) {
    auto attr = qobject_cast<Attribute*>(p->object);
    int split = attr->m_modifiers.count();
    return idx < split
            ? attr->m_modifiers.at(idx)
            : attr->m_static_modifiers.at(idx - split);
}
void Attribute::qlist_clear(QQmlListProperty<Bonus> *p) {
    Attribute* atr = qobject_cast<Attribute*>(p->object);
    atr->valueChanged(atr->value());
    return reinterpret_cast<QList<Bonus *> *>(p->data)->clear();
}
