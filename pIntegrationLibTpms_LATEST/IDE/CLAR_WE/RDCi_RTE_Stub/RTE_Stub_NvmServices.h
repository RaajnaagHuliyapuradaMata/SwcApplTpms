#ifndef __RTE_STUB_NVM_SERVICES_H
#define __RTE_STUB_NVM_SERVICES_H

#include "Rte_CtApHufTpmsSWC_Type.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "RTE_Stub_NvmServicesX.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void NVM_ReadAll(void);
extern void NVM_WriteAll(void);

#ifdef __cplusplus
}
#endif

#endif

