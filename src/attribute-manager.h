#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include "attribute.h"

class AttributeManager
{
public:
    using AttributeList = QList<Attribute*>;

    ~AttributeManager();

    static AttributeManager& instance();

    AttributeList& attributes();
    void addAttribute(Attribute* attr);

private:
    AttributeManager();
    static AttributeManager m_instance;

    AttributeList m_attributes;
};

#endif // ATTRIBUTEMANAGER_H
