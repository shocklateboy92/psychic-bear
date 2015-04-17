#ifndef PROJECTCONTEXT_H
#define PROJECTCONTEXT_H

#include "attribute-manager.h"

#include <QObject>

class ProjectContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AttributeManager::AttributeList all_attributes READ all_attributes NOTIFY all_attributesChanged)

public:
    explicit ProjectContext(QObject *parent = 0);
    ~ProjectContext();

AttributeManager::AttributeList all_attributes() const;

signals:
    void all_attributesChanged(AttributeManager::AttributeList arg);

public slots:

private:
    AttributeManager::AttributeList m_all_attributes;
};

#endif // PROJECTCONTEXT_H
