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

    for (QString &pattern : uriFilter()) {

        QRegExp regex(pattern, Qt::CaseInsensitive, QRegExp::Wildcard);
        if (regex.exactMatch(res->uri())) {

            beginInsertRows(QModelIndex(), m_data.length(), m_data.length());
            m_data.append(res);
            endInsertRows();
        }
    }
}

void ResourceRefList::onResourceDestroyed(Resource *res)
{
    m_data.removeOne(res);
}

void ResourceRefList::setUriFilter(QStringList uriFilter)
{
    if (m_uriFilter == uriFilter)
        return;

    m_uriFilter = uriFilter;
    emit uriFilterChanged(uriFilter);

    // TODO: register with manager here
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
        { Qt::UserRole, "modelData" }
    };
}
