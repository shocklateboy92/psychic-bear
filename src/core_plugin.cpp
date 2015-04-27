#include "core_plugin.h"
#include "attribute.h"
#include "filtered-attribute-list.h"
#include "bonus-source.h"

#include <qqml.h>

void CorePlugin::registerTypes(const char *uri)
{
    // @uri org.lasath.psychic_bear
    qmlRegisterType<Attribute>(uri, 1, 0, "Attribute");
    qmlRegisterType<Bonus>(uri, 1, 0, "Bonus");
    qmlRegisterType<BonusSource>(uri, 1, 0, "BonusSource");
    qmlRegisterType<FilteredAttributeList>(uri, 1, 0, "FilteredAttributeList");
}


