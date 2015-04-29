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
    static const char* PB_NAMESPACE;
};

#endif // CORE_PLUGIN_H

