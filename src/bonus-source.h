#ifndef BONUSSOURCE_H
#define BONUSSOURCE_H

#include "db-helper.h"
#include "pb-core.h"

#include <QObject>

class PB_SHARED_EXPORT BonusSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)

public:
    using List = QList<BonusSource*>;

    explicit BonusSource(QObject *parent = 0);
    ~BonusSource();

    QString name() const;
    QString uri() const;
    bool isActive() const;

signals:
    void nameChanged(QString arg);
    void uriChanged(QString arg);
    void activeChanged(bool active);

public slots:
    void setName(QString arg);
    void setUri(QString arg);
    void setActive(bool active);

    bool fetchDbValues();

private:
    QString m_name;
    QString m_uri;
    bool m_active;
    DbHelper m_db;
};

#endif // BONUSSOURCE_H
