#ifndef CUSTOMMODELS_GLOBAL_H
#define CUSTOMMODELS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CUSTOMMODELS_LIBRARY)
#  define CUSTOMMODELSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CUSTOMMODELSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CUSTOMMODELS_GLOBAL_H
