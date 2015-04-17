#ifndef BONUS_H
#define BONUS_H

#include <QQuickItem>

class Bonus : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int amount READ amount WRITE setAmount NOTIFY amountChanged)
public:
    Bonus(QQuickItem *parent = nullptr);
    ~Bonus();

    int amount() const;
    QString name() const;

    static int add(int acc, const Bonus *a);

signals:
    void amountChanged(int arg);
    void nameChanged(QString arg);

public slots:
    void setAmount(int arg);
    void setName(QString arg);

private:
    int m_amount;
    QString m_name;
};

#endif // BONUS_H
