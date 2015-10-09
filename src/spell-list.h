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
    Q_PROPERTY(QQmlListReference slotCounts READ slotCounts
               WRITE setSlotCounts NOTIFY slotCountsChanged)
    using AttributeList = QQmlListReference;
public:
    class Model;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    Model* 	model()	const;

    AttributeList slotCounts() const;

signals:
    void classNameChanged(QString className);
    void modelChanged(Model* model);

    void slotCountsChanged(AttributeList slotCounts);

public slots:
    void setClassName(QString className);

    void setSlotCounts(AttributeList slotCounts);

private:
    QString m_className;
    Model* m_model;

    class Spell;
    AttributeList m_slotCounts;
};

// TODO: Maybe make this a proxy model?
class SpellList::Model : public QAbstractListModel {

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Model(SpellList *parent);

    void setSpells(const QList<SpellList::Spell> &spellIds);

private:
    QList<SpellList::Spell> m_spellIds;
};

class SpellList::Spell {
public:
    Spell(int level);
    QVariant dataFor(int role) const;

private:
    int m_level;
    int m_id;
};

#endif // SPELLLIST_H
