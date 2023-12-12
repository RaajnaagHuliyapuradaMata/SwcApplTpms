

#ifndef _RTE_H
#define _RTE_H

#define RTE_SW_MAJOR_VERSION (0x03U)
#define RTE_SW_MINOR_VERSION (0x0eU)
#define RTE_SW_PATCH_VERSION (0x00U)

#define RTE_VENDOR_ID (0x0001U)
#define RTE_MODULE_ID (0x0002U)

#define RTE_AR_RELEASE_MAJOR_VERSION     (0x04U)
#define RTE_AR_RELEASE_MINOR_VERSION     (0x02U)
#define RTE_AR_RELEASE_REVISION_VERSION  (0x02U)

#include "Std_Types.h"

# ifdef RTE_ENABLE_USER_DATATYPES
#  include "Rte_UserTypes.h"
# endif

# if !defined (TYPEDEF) && defined (AUTOMATIC)
#  define TYPEDEF AUTOMATIC
# endif

# if !defined (FUNC_P2CONST)
#  define FUNC_P2CONST(rettype, ptrclass, memclass) FUNC(P2CONST(rettype, AUTOMATIC, ptrclass), memclass)
# endif

# if !defined (FUNC_P2VAR)
#  define FUNC_P2VAR(rettype, ptrclass, memclass) FUNC(P2VAR(rettype, AUTOMATIC, ptrclass), memclass)
# endif

#define RTE_E_OK               (0U)
#define RTE_E_INVALID          (1U)

#define RTE_E_LOST_DATA        (64U)
#define RTE_E_MAX_AGE_EXCEEDED (64U)

#define Rte_HasOverlayedError(status) (((status) & 64U) != 0)

#define RTE_E_COM_STOPPED      (128U)
#define RTE_E_TIMEOUT          (129U)
#define RTE_E_LIMIT            (130U)
#define RTE_E_NO_DATA          (131U)
#define RTE_E_TRANSMIT_ACK     (132U)
#define RTE_E_NEVER_RECEIVED   (133U)
#define RTE_E_UNCONNECTED            (134U)
#define RTE_E_IN_EXCLUSIVE_AREA      (135U)
#define RTE_E_SEG_FAULT              (136U)
#define RTE_E_OUT_OF_RANGE           (137U)
#define RTE_E_SERIALIZATION_ERROR    (138U)
#define RTE_E_HARD_TRANSFORMER_ERROR (138U)
#define RTE_E_SERIALIZATION_LIMIT    (139U)
#define RTE_E_TRANSFORMER_LIMIT      (139U)
#define RTE_E_SOFT_TRANSFORMER_ERROR (140U)
#define RTE_E_COM_BUSY               (141U)

#define SCHM_E_OK                    (0U)
#define SCHM_E_TIMEOUT               (129U)
#define SCHM_E_LIMIT                 (130U)
#define SCHM_E_NO_DATA               (131U)
#define SCHM_E_TRANSMIT_ACK          (132U)
#define SCHM_E_IN_EXCLUSIVE_AREA     (135U)

#define Rte_IsInfrastructureError(status) (((status) & 128U) != 0)
#define Rte_ApplicationError(status) ((status) & 63U)

#endif
