#ifndef ERP_QC_GLOBAL_H
#define ERP_QC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ERP_QC_LIBRARY)
#  define ERP_QCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ERP_QCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ERP_QC_GLOBAL_H
