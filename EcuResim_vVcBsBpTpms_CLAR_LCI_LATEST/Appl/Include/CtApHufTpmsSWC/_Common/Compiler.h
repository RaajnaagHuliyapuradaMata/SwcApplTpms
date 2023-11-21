

#ifndef COMPILER_H
#define COMPILER_H

#include "Compiler_Cfg.h"

#define COMMONASR_CANOEEMU_IMPL_COMPABSTRACT_ANSI_VERSION 0x0403
#define COMMONASR_CANOEEMU_IMPL_COMPABSTRACT_ANSI_RELEASE_VERSION 0x00

#define COMPILER_VENDOR_ID    30u

#   define COMPILER_AR_RELEASE_MAJOR_VERSION       (4u)
#   define COMPILER_AR_RELEASE_MINOR_VERSION       (0u)
#   define COMPILER_AR_RELEASE_PATCH_VERSION       (3u)

#define COMPILER_SW_MAJOR_VERSION       (4u)
#define COMPILER_SW_MINOR_VERSION       (3u)
#define COMPILER_SW_PATCH_VERSION       (0u)

#define _MICROSOFT_C_CANOE_

#define AUTOMATIC

#define TYPEDEF

# ifndef NULL_PTR
   #define NULL_PTR  ((void *)0)
# endif

#define INLINE _inline

#define LOCAL_INLINE static _inline

#define FUNC(rettype, memclass) rettype memclass

#define FUNC_P2CONST(rettype, ptrclass, memclass) const memclass rettype ptrclass *

#define FUNC_P2VAR(rettype, ptrclass, memclass) memclass rettype ptrclass *

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * memclass

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * memclass

#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * const memclass

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * const memclass

#define P2FUNC(rettype, ptrclass, fctname) rettype (ptrclass * fctname)

#ifdef _EcuVirtual
#ifndef CONST
#define CONST(type, memclass) const type memclass
#endif
#else
#define CONST(type, memclass) const type memclass
#endif

#define VAR(vartype, memclass) vartype memclass

#endif

