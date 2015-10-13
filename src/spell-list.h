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
    using ModelList = QQmlListProperty<Model>;

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
    Spell(int level, int id);
    QVariant dataFor(int role) const;

private:
    int m_level;
    int m_id;
};

#endif // SPELLLIST_H
