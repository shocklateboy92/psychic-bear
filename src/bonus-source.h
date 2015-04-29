#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include "pb-core.h"

#include <QObject>

class PB_SHARED_EXPORT BonusSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)

public:
    using List = QList<BonusSource*>;

    explicit BonusSource(QObject *parent = 0);
    ~BonusSource();

    QString name() const;
    QString uri() const;

signals:
    void nameChanged(QString arg);
    void uriChanged(QString arg);

public slots:
    void setName(QString arg);
    void setUri(QString arg);

private:
    QString m_name;
    QString m_uri;
};

#endif // BONUSSOURCE_H
