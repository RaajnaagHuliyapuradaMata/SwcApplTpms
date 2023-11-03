#ifndef __RTE_STUB_DTC_NVM_BLOCK_H
#define __RTE_STUB_DTC_NVM_BLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Rte_CtApHufTpmsSWC_Type.h"

extern void NVM_ReadAllDTC(void);
extern void NVM_WriteAllDTC(void);

extern uint8 ucNvmDTC_ReadByte( uint32 ulIx);
extern void NvmDTC_WriteByte( uint32 ulIx, uint8 ucNvmByte);

#ifdef __cplusplus
}
#endif

#endif

