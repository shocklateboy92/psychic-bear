#ifndef SPELLLIST_H
#define SPELLLIST_H

#include "resource.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class SpellList : public Resource
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(Model model READ model NOTIFY modelChanged)

public:
    class Model;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    Model* 	model()	const;

signals:
    void classNameChanged(QString className);
    void modelChanged(Model* model);

public slots:
    void setClassName(QString className);

private:
    QString m_className;
    Model* m_model;

    class Spell;
};

// TODO: Maybe make this a proxy model?
class SpellList::Model : public QAbstractListModel {

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Model(SpellList *parent);

    void setSpells(const QList<int> &spellIds);

private:
    QList<int> m_spellIds;
};

class SpellList::Spell {
    QVariant dataFor(int role) const;
};

#endif // SPELLLIST_H
