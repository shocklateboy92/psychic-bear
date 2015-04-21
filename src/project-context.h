#ifndef PROJECTCONTEXT_H
#define PROJECTCONTEXT_H

#include "attribute-manager.h"

#include <QObject>

class ProjectContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Attribute> all_attributes READ all_attributes)

public:
    using AttributeList = QQmlListProperty<Attribute>;

    explicit ProjectContext(QObject *parent = 0);
    ~ProjectContext();

    AttributeList all_attributes();

signals:

public slots:

private:
};

#endif // PROJECTCONTEXT_H
