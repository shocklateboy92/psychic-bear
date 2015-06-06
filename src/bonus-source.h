#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include "db-helper.h"
#include "pb-core.h"

#include <QQuickItem>

class Bonus;

class PB_SHARED_EXPORT BonusSource : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool conditional READ isEffectivelyConditional
               WRITE setConditional NOTIFY conditionalChanged)

public:
    using List = QList<BonusSource*>;

    explicit BonusSource(QQuickItem *parent = 0);
    ~BonusSource();

    QString name() const;
    QString uri() const;
    bool isActive() const;
    bool isConditional() const;
    bool isEffectivelyConditional() const;

signals:
    void nameChanged(QString arg);
    void uriChanged(QString arg);
    void activeChanged(bool active);
    void conditionalChanged(bool conditional);

public slots:
    bool fetchDbValues();

    void setName(QString arg);
    void setUri(QString arg);
    void setActive(bool active);
    void setConditional(bool conditional);

private:
    QString m_name;
    QString m_uri;
    bool m_active;
    DbHelper m_db;
    bool m_conditional;
};

#endif // BONUSSOURCE_H
