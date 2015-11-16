#ifndef RESOURCEREFLIST_H
#define RESOURCEREFLIST_H

#include <QAbstractListModel>

#include "resource.h"

class ResourceRefList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList uriFilter READ uriFilter
               WRITE setUriFilter NOTIFY uriFilterChanged)

    // QAbstractItemModel interface
    QStringList m_uriFilter;

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    ResourceRefList(QObject *parent = nullptr);

    QStringList uriFilter() const;

public slots:
    void onResourceCreated(Resource* res);
    void onResourceDestroyed(Resource* res);
    void setUriFilter(QStringList uriFilter);

signals:
    void uriFilterChanged(QStringList uriFilter);

private:
    Resource::List m_data;
};

#endif // RESOURCEREFLIST_H
