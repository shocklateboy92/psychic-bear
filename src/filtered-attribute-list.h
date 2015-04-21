#ifndef FILTEREDATTRIBUTELIST_H
#define FILTEREDATTRIBUTELIST_H

#include "project-context.h"

#include <QQuickItem>

class FilteredAttributeList : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern
               WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QQmlListProperty<Attribute> attributes
               READ attribtues NOTIFY attributesChanged)

public:
    FilteredAttributeList();
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
