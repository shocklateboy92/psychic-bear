#include "core_plugin.h"
#include "attribute.h"
#include "resource-filter.h"
#include "bonus-source.h"
#include "bonus-type.h"
#include "attribute-ref.h"

#include <qqml.h>

void CorePlugin::registerTypes(const char *uri)
{
    // @uri org.lasath.psychic_bear
    qmlRegisterType<Attribute>(uri, 1, 0, "Attribute");
    qmlRegisterType<Bonus>(uri, 1, 0, "Bonus");
    qmlRegisterUncreatableType<Resource>(uri, 1, 0, "Resource", "Please instanciate BonusSource/Attribute directly.");
    qmlRegisterType<BonusSource>(uri, 1, 0, "BonusSource");
    qmlRegisterType<ResourceFilter>(uri, 1, 0, "ResourceFilter");
    qmlRegisterType<BonusType>(uri, 1, 0, "BonusType");
    qmlRegisterType<AttributeRef>(uri, 1, 0, "AttributeRef");
}

const char * CorePlugin::PB_NAMESPACE = "org.lasath.psychic_bear";
