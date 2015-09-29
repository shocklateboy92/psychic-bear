#ifndef FILTEREDATTRIBUTELIST_H
#define FILTEREDATTRIBUTELIST_H

#include "pb-core.h"
#include "project-context.h"

#include <QQuickItem>

// TODO: move into app.pro
class PB_SHARED_EXPORT ResourceFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern
               WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QQmlListProperty<Resource> matches
               READ matches NOTIFY matchesChanged)

public:
    ResourceFilter(QObject *parent = 0);
    ~ResourceFilter();

    QString pattern() const;
    ProjectContext::ResourceList matches();

signals:
    void patternChanged(QString arg);
    void matchesChanged(ProjectContext::ResourceList arg);

public slots:
    void setPattern(QString arg);
    void updateResources(Resource::List availableResources);

private:
    QString m_pattern;
    Resource::List m_matches;
};

#endif // FILTEREDATTRIBUTELIST_H
