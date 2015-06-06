#ifndef BONUS_H
#define BONUS_H

#include <QObject>
#include "pb-core.h"

class BonusSource;
class Attribute;
class BonusType;

class PB_SHARED_EXPORT Bonus : public QObject
{
    using Source = BonusSource*;

    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(BonusSource* source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(Attribute* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(BonusType* type READ type WRITE setType NOTIFY typeChanged)

public:
    Bonus(QObject *parent = nullptr);
    ~Bonus();

    int amount() const;
    QString name() const;
    Source source() const;
    Attribute* target() const;
    BonusType* type() const;

    static int add(int acc, const Bonus *a);

signals:
    void amountChanged(int arg);
    void nameChanged(QString arg);
    void sourceChanged(Source arg);
    void targetChanged(Attribute* arg);
    void typeChanged(BonusType* type);

public slots:
    void setAmount(int arg);
    void setName(QString arg);
    void setSource(Source arg);
    void setTarget(Attribute* arg);
    void setType(BonusType* type);

private:
    int m_amount;
    QString m_name;
    Attribute* m_target;
    Source m_source;
    BonusType* m_type;
};

#endif // BONUS_H
