#ifndef ERP_CRM_GLOBAL_H
#define ERP_CRM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ERP_CRM_LIBRARY)
#  define ERP_CRMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ERP_CRMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ERP_CRM_GLOBAL_H
