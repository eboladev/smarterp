#ifndef ERP_CUSTOMERS_GLOBAL_H
#define ERP_CUSTOMERS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ERP_CUSTOMERS_LIBRARY)
#  define ERP_CUSTOMERSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ERP_CUSTOMERSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ERP_CUSTOMERS_GLOBAL_H