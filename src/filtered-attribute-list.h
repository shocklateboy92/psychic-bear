#ifndef FILTEREDATTRIBUTELIST_H
#define FILTEREDATTRIBUTELIST_H

#include "pb-core.h"
#include "project-context.h"

#include <QQuickItem>

class PB_SHARED_EXPORT FilteredAttributeList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern
               WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QQmlListProperty<Attribute> attributes
               READ attribtues NOTIFY attributesChanged)

public:
    FilteredAttributeList(QObject *parent = 0);
    ~FilteredAttributeList();

    QString pattern() const;
    ProjectContext::AttributeList attribtues();

signals:
    void patternChanged(QString arg);
    void attributesChanged(ProjectContext::AttributeList arg);

public slots:
    void setPattern(QString arg);

private:
    QString m_pattern;
    AttributeManager::AttributeList m_attributes;
};

#endif // FILTEREDATTRIBUTELIST_H
