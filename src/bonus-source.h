#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include "db-util.h"
#include "pb-core.h"
#include "resource.h"

#include <QQuickItem>

class Bonus;

class PB_SHARED_EXPORT BonusSource : public Resource
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool conditional READ isEffectivelyConditional
               WRITE setConditional NOTIFY conditionalChanged)
    Q_PROPERTY(QQmlListProperty<Bonus> effects READ effects NOTIFY effectsChanged)

public:
    using List = QList<BonusSource*>;

    explicit BonusSource(QQuickItem *parent = 0);
    ~BonusSource();

    bool isActive() const;
    bool isConditional() const;
    bool isEffectivelyConditional() const;
    QQmlListProperty<Bonus> effects();

    bool isDynamic() const override;
    bool initDb() override;

signals:
    void activeChanged(bool active);
    void conditionalChanged(bool conditional);
    void effectsChanged(QQmlListProperty<Bonus> effects);

public slots:
    bool fetchDbValues();

    void setActive(bool active);
    void setConditional(bool conditional);

private:
    bool m_active;
    bool m_conditional;
    QList<Bonus*> m_effects;
};

#endif // BONUSSOURCE_H
