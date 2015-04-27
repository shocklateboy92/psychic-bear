#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include <QQmlExtensionPlugin>
#include <pb-core.h>

class PB_SHARED_EXPORT CorePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

constexpr const char* PB_NAMESPACE = "org.lasath.psychic_bear";

#endif // CORE_PLUGIN_H

