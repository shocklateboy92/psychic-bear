#include "resource-manager.h"
#include "resource-ref-list.h"

ResourceRefList::ResourceRefList(QObject *parent)
    : QAbstractListModel(parent)
{

}

QStringList ResourceRefList::uriFilter() const
{
    return m_uriFilter;
}

void ResourceRefList::onResourceCreated(Resource *res)
{
    // We shouldn't be getting events before we have constraints
    Q_ASSERT(!uriFilter().isEmpty());

    // We're doing all the filtering receiver side
    for (QString &pattern : uriFilter()) {
        QRegExp regex(pattern, Qt::CaseInsensitive, QRegExp::Wildcard);
        if (regex.exactMatch(res->uri())) {

            beginInsertRows(QModelIndex(), m_data.length(), m_data.length());

            m_data.append(res);
            connect(res, &Resource::destroyed,
                    this, &ResourceRefList::onResourceDestroyed);

            // This shouldn't happen
            connect(res, &Resource::uriChanged,
                    [=](const QString &uri) {
                qWarning() << "Uri changed after initialization: " << uri;

                if (!regex.exactMatch(uri)) {
                    onResourceDestroyed(res);
                }
            });

            endInsertRows();
        }
    }
}

void ResourceRefList::onResourceDestroyed(QObject *obj)
{
    auto res = qobject_cast<Resource*>(obj);

    bool index = m_data.indexOf(res);
    // we shouldn't get events about resources that aren't ours
    Q_ASSERT(index);

    beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    endRemoveRows();
}

void ResourceRefList::setUriFilter(QStringList uriFilter)
{
    if (m_uriFilter == uriFilter)
        return;

    m_uriFilter = uriFilter;
    emit uriFilterChanged(uriFilter);

    connect(ResourceManager::instance(), &ResourceManager::resourceCreated,
            this, &ResourceRefList::onResourceCreated);

    for (Resource *res : ResourceManager::instance()->existingResources()) {
        onResourceCreated(res);
    }
}

int ResourceRefList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.length();
}

QVariant ResourceRefList::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(role == Qt::UserRole && index.isValid());
    return QVariant::fromValue(m_data.at(index.row()));
}

QHash<int, QByteArray> ResourceRefList::roleNames() const
{
    return {
        { Qt::UserRole, "modelData" },
        { Qt::UserRole, "model" }
    };
}
