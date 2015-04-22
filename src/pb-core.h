#ifndef PBCORE_H
#define PBCORE_H

#include <QtCore/QtGlobal>

#if defined(PB_CORE_LIBRARY)
    #define PB_SHARED_EXPORT Q_DECL_EXPORT
#else
    #define PB_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PBCORE_H

