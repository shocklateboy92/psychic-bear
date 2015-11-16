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
    Q_PROPERTY(Attribute* totalCasts READ totalCasts
               WRITE setTotalCasts NOTIFY totalCastsChanged)
    Q_PROPERTY(Attribute* remainingCasts READ remainingCasts
               WRITE setRemainingCasts NOTIFY remainingCastsChanged)
    Q_PROPERTY(Attribute* saveDc READ saveDc
               WRITE setSaveDc NOTIFY saveDcChanged)
    Q_PROPERTY(bool complete READ complete
               WRITE setComplete NOTIFY completeChanged)
public:
    class Model;

    SpellList(QQuickItem *parent = nullptr);

    QString className() const;
    int 	level() const;
    bool    complete() const;

    Model* 	model()	const;

    Attribute* totalCasts() const;
    Attribute* remainingCasts() const;
    Attribute* saveDc() const;

    // Resource interface
public:
    bool isDynamic() const;
    bool initDb();

signals:
    void classNameChanged(QString className);
    void levelChanged(int level);
    void completeChanged(bool complete);

    void modelChanged(Model* model);

    void totalCastsChanged(Attribute* totalCasts);
    void remainingCastsChanged(Attribute* remainingCasts);
    void saveDcChanged(Attribute* saveDc);

public slots:
    void setClassName(QString className);
    void setLevel(int level);
    void setComplete(bool complete);

    void createNewSlot();
    void updateSpellSlot(int slot, int spellId);

    void setTotalCasts(Attribute* totalCasts);
    void setRemainingCasts(Attribute* remainingCasts);
    void setSaveDc(Attribute* saveDc);

private:
    class Entry;

    void populate();

    QString m_className;
    int 	m_level;
    bool    m_complete;
    Model* 	m_model;
    Model*  m_availableSpells;
    Attribute* m_totalCasts;
    Attribute* m_remainingCasts;
    Attribute* m_saveDc;
};

// I choose to split this into a separate class, and use
// composition, because I didn't want to have to deal with
// the diamond inheritence problem with QObject
class SpellList::Model : public QAbstractListModel {

    Q_OBJECT
public:
    Model(SpellList *parent);

    QList<SpellList::Entry> spellIds() const;
    void setSpells(const QList<SpellList::Entry> &spellIds);

    Q_INVOKABLE int getIdOf(int index);

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

    int spellId() const;

private:
    int m_level;
    int m_spellId;
    DbUtil m_db;
};

#endif // SPELLLIST_H
