#ifndef ATTRIBUTEREF_H
#define ATTRIBUTEREF_H

#include <QQuickItem>

class Attribute;

class AttributeRef : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(Attribute target READ target NOTIFY targetChanged)
public:
    using Pointer = Attribute*;

    AttributeRef();

    QString uri() const;
    Pointer target() const;

signals:
    void uriChanged(QString uri);
    void targetChanged(Pointer target);

public slots:
    void setUri(QString uri);

private:
    QString m_uri;
    Pointer m_target;
};

#endif // ATTRIBUTEREF_H
