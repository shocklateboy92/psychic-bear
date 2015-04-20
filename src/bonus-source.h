#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include <QObject>

class BonusSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit BonusSource(QObject *parent = 0);
    ~BonusSource();

    QString name() const;

signals:
    void nameChanged(QString arg);

public slots:
    void setName(QString arg);

private:
    QString m_name;
};

#endif // BONUSSOURCE_H
