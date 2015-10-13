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
    Q_PROPERTY(int maxLevel READ maxLevel
               WRITE setMaxLevel NOTIFY maxLevelChanged)
    Q_PROPERTY(QQmlListProperty<Model> model READ model NOTIFY modelChanged)
public:
    class Model;
    class Spell;
    using ModelList = QQmlListProperty<Model>;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    ModelList 	model();

    int maxLevel() const;

signals:
    void classNameChanged(QString className);
    void modelChanged(Model* model);

    void maxLevelChanged(int maxLevel);

public slots:
    void setClassName(QString className);

    void setMaxLevel(int maxLevel);

private:
    QString m_className;
    QList<Model*> m_modelList;

    int m_maxLevel;

    // Resource interface
public:
    bool isDynamic() const;
    bool initDb();
};

// TODO: Maybe make this a proxy model?
class SpellList::Model : public QAbstractListModel {

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Model(SpellList *parent, int level);

    void setSpells(const QList<SpellList::Spell> &spellIds);

private:
    int m_level;
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
