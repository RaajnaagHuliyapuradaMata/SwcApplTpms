

#ifndef _seasrcpadj_X_H
#define _seasrcpadj_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void InitSRA(Rte_Instance self);
extern void StartSRA(Rte_Instance self);
extern void CyclicSRA(Rte_Instance self);

extern void GetInternalLowerDataSRA( uint8* pucDeltaTinitTh, uint8* pucSlowTimeConst, uint32* pulTinitOatTimeTicks, uint32* pulTinitOatTime, boolean* pbCorrTinitEvent);
extern void GetInternalHigherDataSRA( uint8* pucDeltaTinitTh, uint8* pucFastTimeConst, uint32* pulTinitOatTimeTicks, uint32* pulTinitOatTime, boolean* pbCorrTinitEvent);

#ifdef __cplusplus
}
#endif

#endif
