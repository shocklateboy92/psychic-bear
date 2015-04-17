#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Bonus.h"

#include <QQuickItem>
#include <QAbstractListModel>
#include <memory>

class Attribute : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Bonus> modifiers READ modifiers NOTIFY modifiersChanged)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)

    using ModelType = QList<QString>;
    using ModelPointer = ModelType;
public:
    Attribute(QQuickItem *parent = nullptr);
    ~Attribute();

    QQmlListProperty<Bonus> modifiers();
    int value() const;

signals:
    void modifiersChanged(QQmlListProperty<Bonus> arg);
    void valueChanged(int arg);

public slots:
    void onModifierChanged(Bonus *m);

private:
    QList<Bonus*> m_modifiers;
};

#endif // ATTRIBUTE_H
