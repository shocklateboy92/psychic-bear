#ifndef PROJECTCONTEXT_H
#define PROJECTCONTEXT_H

#include "attribute-manager.h"
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
    auto cast = qobject_cast<T*>(obj);
    if (cast) {
        res.append(cast);
    }

    for (QObject *child : obj->children()) {
        populateInstancesOf(child, res);
    }
}

#endif // PROJECTCONTEXT_H
