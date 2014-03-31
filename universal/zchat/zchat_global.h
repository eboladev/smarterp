#ifndef ZCHAT_GLOBAL_H
#define ZCHAT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZCHAT_LIBRARY)
#  define ZCHATSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZCHATSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZCHAT_GLOBAL_H
