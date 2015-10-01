#ifndef PROJECTCONTEXT_H
#define PROJECTCONTEXT_H

#include "bonus-source.h"

#include <QObject>

class PB_SHARED_EXPORT ProjectContext : public QObject
{
    Q_OBJECT

public:
    using ResourceList = QQmlListProperty<Resource>;

    explicit ProjectContext(QObject *parent = 0);
    ~ProjectContext();

    void setCharacterRoot(QObject *root);
    Resource::List allResources();

    template <typename T>
    static void populateInstancesOf(QObject *obj, QList<T*> &res);

private:
    Resource::List m_resources;
};

template <typename T>
void ProjectContext::populateInstancesOf(QObject *obj, QList<T*> &res) {
    res = obj->findChildren<T*>();
}

#endif // PROJECTCONTEXT_H
