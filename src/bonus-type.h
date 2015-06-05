#ifndef BONUSTYPE_H
#define BONUSTYPE_H

#include <QObject>

class BonusType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool stacking READ stacking WRITE setStacking NOTIFY stackingChanged)

public:
    explicit BonusType(QObject *parent = 0);

    QString name() const;
    bool stacking() const;

    static BonusType* noneType();

signals:
    void nameChanged(QString name);
    void stackingChanged(bool stacking);

public slots:
    void setName(QString name);
    void setStacking(bool stacking);

private:
    QString m_name;
    bool m_stacking;
    static BonusType* s_noneType;
};

#endif // BONUSTYPE_H
