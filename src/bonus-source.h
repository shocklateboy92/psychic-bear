#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include <QObject>

class BonusSource : public QObject
{
    Q_OBJECT
public:
    explicit BonusSource(QObject *parent = 0);
    ~BonusSource();

signals:

public slots:
};

#endif // BONUSSOURCE_H
