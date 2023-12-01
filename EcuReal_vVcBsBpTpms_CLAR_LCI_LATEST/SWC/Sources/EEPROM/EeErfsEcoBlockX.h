#ifndef _ee_erfs_eco_block_X_H
#define _ee_erfs_eco_block_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void PutErfsEcoNeuerReifenEE(Rte_Instance self, const uint8* pucData);
extern void PutErfsEcoReifenTabelleEE(Rte_Instance self, const uint8* pucData, const uint8 ucElement);

#ifdef __cplusplus
}
#endif

#endif
