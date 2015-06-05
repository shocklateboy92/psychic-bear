#ifndef ATTRIBUTEREF_H
#define ATTRIBUTEREF_H

#include <QObject>
#include "pb-core.h"

class Attribute;

class AttributeRef : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString targetUri READ targetUri WRITE setTargetUri NOTIFY targetUriChanged)
    Q_PROPERTY(Attribute* target READ target WRITE setTarget NOTIFY targetChanged)

public:
    explicit AttributeRef(QObject *parent = 0);
    ~AttributeRef();

    QString targetUri() const;
    Attribute* target() const;

signals:
    void targetUriChanged(QString arg);
    void targetChanged(Attribute* arg);

public slots:
    void setTargetUri(QString arg);
    void setTarget(Attribute* arg);

private:
    QString m_targetUri;
    Attribute* m_target;
};



#endif // ATTRIBUTEREF_H
