#ifndef SPELLLIST_H
#define SPELLLIST_H

#include "resource.h"

#include <QAbstractListModel>

class SpellList : public Resource
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)

public:
    SpellList(QQuickItem *parent = nullptr);

    QString className() const;

signals:
    void classNameChanged(QString className);

public slots:
    void setClassName(QString className);

private:
    QString m_className;
};

#endif // SPELLLIST_H
