#ifndef HYPERIONCHECKSERVICE_GLOBAL_H
#define HYPERIONCHECKSERVICE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef HYPERIONCHECKSERVICE_LIB
# define HYPERIONCHECKSERVICE_EXPORT Q_DECL_EXPORT
#else
# define HYPERIONCHECKSERVICE_EXPORT Q_DECL_IMPORT
#endif

#endif // HYPERIONCHECKSERVICE_GLOBAL_H