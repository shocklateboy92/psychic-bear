#ifndef RESOURCE
#define RESOURCE

#include "db-util.h"
#include "pb-core.h"

#include <QQuickItem>

class PB_SHARED_EXPORT Resource : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)

public:
    Resource(QString tableName, QQuickItem *parent = nullptr);
    QString name() const;
    QString uri() const;
    DbUtil &db();

public slots:
    void setName(QString name);
    void setUri(QString uri);

signals:
    void nameChanged(QString name);
    void uriChanged(QString uri);

private:
    QString m_name;
    QString m_uri;
    DbUtil m_db;
};

#endif // RESOURCE

