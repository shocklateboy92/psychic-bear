#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "pb-core.h"
#include "bonus.h"
#include "db-util.h"
#include "resource.h"

#include <QQuickItem>
#include <QAbstractListModel>
#include <memory>

class PB_SHARED_EXPORT Attribute : public Resource
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Bonus> modifiers READ modifiers NOTIFY modifiersChanged)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly NOTIFY readOnlyChanged)

    using ModelType = QList<QString>;
    using ModelPointer = ModelType;
public:
    using List = QList<Attribute*>;

    Attribute(QQuickItem *parent = nullptr);
    ~Attribute();

    bool fetchId();

    QQmlListProperty<Bonus> modifiers();
    int value() const;
    bool readOnly() const;

    bool isDynamic() const override;
    bool initDb() override;

signals:
    void modifiersChanged(QQmlListProperty<Bonus> arg);
    void valueChanged(int arg);
    void readOnlyChanged(bool arg);

public slots:
    void onModifierChanged(Bonus *m);
    void setReadOnly(bool arg);

    void addModifier(Bonus *arg);

    void updateStaticModifiers();
    bool createStaticModifier(int amount, const QString &name);

private:
    QList<Bonus*> m_modifiers;
    bool m_readOnly;
    QList<Bonus*> m_static_modifiers;

    static void qlist_append(QQmlListProperty<Bonus> *p, Bonus *v);
    static int qlist_count(QQmlListProperty<Bonus> *p);
    static Bonus *qlist_at(QQmlListProperty<Bonus> *p, int idx);
    static void qlist_clear(QQmlListProperty<Bonus> *p);
};

#endif // ATTRIBUTE_H
