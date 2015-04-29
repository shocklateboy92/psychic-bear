#ifndef PROJECTCONTEXT_H
#define PROJECTCONTEXT_H

#include "attribute-manager.h"
#include "bonus-source.h"

#include <QObject>

class PB_SHARED_EXPORT ProjectContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Attribute> all_attributes READ all_attributes)
    Q_PROPERTY(QQmlListProperty<BonusSource> all_bonus_sources READ all_bonus_sources)

public:
    using AttributeList = QQmlListProperty<Attribute>;
    using BonusSourceList = QQmlListProperty<BonusSource>;

    explicit ProjectContext(QObject *parent = 0);
    ~ProjectContext();

    AttributeList all_attributes();
    BonusSourceList all_bonus_sources();

    void populateWith(QObject *root);

private:
    BonusSource::List m_bonusSrcList;

    template <typename T>
    static void populateInstancesOf(QObject *obj, QList<T> &res);
};

#endif // PROJECTCONTEXT_H
