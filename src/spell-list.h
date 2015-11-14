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
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(QAbstractItemModel* model READ model NOTIFY modelChanged)
public:
    class Model;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    Model* 	model()	const;
    int 	level() const;

    // Resource interface
public:
    bool isDynamic() const;
    bool initDb();

signals:
    void classNameChanged(QString className);
    void modelChanged(Model* model);
    void levelChanged(int level);

public slots:
    void setClassName(QString className);
    void setLevel(int level);

    void createNewSlot();
    void updateSpellSlot(int slot, int spellId);

private:
    class Entry;

    QString m_className;
    Model* 	m_model;
    int 	m_level;
};

// I choose to split this into a separate class, and use
// composition, because I didn't want to have to deal with
// the diamond inheritence problem with QObject
class SpellList::Model : public QAbstractListModel {

public:
    Model(SpellList *parent);

    QList<SpellList::Entry> spellIds() const;
    void setSpells(const QList<SpellList::Entry> &spellIds);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    void updateSpell(int slot, int spellId);

private:
    QList<SpellList::Entry> m_spellIds;
    SpellList *m_parent;
};

class SpellList::Entry {
public:
    Entry(const DbUtil &db, int level, int spellId);
    QVariant dataFor(int role) const;
    void updateSpell(int spellId);

    static const QString TABLE_NAME;

private:
    int m_level;
    int m_spellId;
    DbUtil m_db;
};

#endif // SPELLLIST_H
