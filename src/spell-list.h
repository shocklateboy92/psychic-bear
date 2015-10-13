#ifndef SPELLLIST_H
#define SPELLLIST_H

#include "attribute.h"
#include "resource.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class SpellList : public Resource
{
    Q_OBJECT
    Q_PROPERTY(QString className READ className
               WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(Model model READ model NOTIFY modelChanged)
public:
    class Model;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    Model* 	model()	const;

    // Resource interface
public:
    bool isDynamic() const;
    bool initDb();

signals:
    void classNameChanged(QString className);
    void modelChanged(Model* model);

public slots:
    void setClassName(QString className);

private:
    class Spell;
    QString m_className;

    Model* m_model;
};

// I choose to split this into a separate class, and use
// composition, because I didn't want to have to deal with
// the diamond inheritence problem with QObject
class SpellList::Model : public QAbstractListModel {

public:
    Model(SpellList *parent);

    void setSpells(const QList<SpellList::Spell> &spellIds);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QList<SpellList::Spell> m_spellIds;
};

class SpellList::Spell {
public:
    Spell(int level, int id);
    QVariant dataFor(int role) const;

private:
    int m_level;
    int m_id;
};

#endif // SPELLLIST_H
