#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "bonus.h"
#include "db-attribute.h"

#include <QQuickItem>
#include <QAbstractListModel>
#include <memory>

class Attribute : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Bonus> modifiers READ modifiers NOTIFY modifiersChanged)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly NOTIFY readOnlyChanged)

    using ModelType = QList<QString>;
    using ModelPointer = ModelType;
public:
    Attribute(QQuickItem *parent = nullptr);
    ~Attribute();

    bool fetchId();

    QQmlListProperty<Bonus> modifiers();
    int value() const;
    QString name() const;
    QString uri() const;
    bool readOnly() const;

signals:
    void modifiersChanged(QQmlListProperty<Bonus> arg);
    void valueChanged(int arg);
    void nameChanged(QString arg);
    void uriChanged(QString arg);
    void readOnlyChanged(bool arg);

public slots:
    void onModifierChanged(Bonus *m);
    void setName(QString arg);
    void setUri(QString arg);
    void setReadOnly(bool arg);

    void updateStaticModifiers();
    bool createStaticModifier(int amount, const QString &name);

private:
    QList<Bonus*> m_modifiers;
    QString m_name;
    QString m_uri;
    DBAttribute m_db;
    bool m_readOnly;
    QList<Bonus*> m_static_modifiers;

    static void qlist_append(QQmlListProperty<Bonus> *p, Bonus *v);
    static int qlist_count(QQmlListProperty<Bonus> *p);
    static Bonus *qlist_at(QQmlListProperty<Bonus> *p, int idx);
    static void qlist_clear(QQmlListProperty<Bonus> *p);
};

#endif // ATTRIBUTE_H
