#ifndef REPORTGENERATOR_GLOBAL_H
#define REPORTGENERATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(REPORTGENERATOR_LIBRARY)
#  define REPORTGENERATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define REPORTGENERATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // REPORTGENERATOR_GLOBAL_H
