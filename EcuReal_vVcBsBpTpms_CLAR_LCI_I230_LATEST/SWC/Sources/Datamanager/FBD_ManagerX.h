

#ifndef _fbd_manager_X_H
#define _fbd_manager_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void GetDataFBD(uint8 ucPos, uint32* pulTyreId, uint8* pucSuppId);
extern void PmStartDataAllocTimerFBD(void);
extern void PmStopDataAllocTimerFBD(void);
extern uint8 PmDataAllocTimerTickFBD(void);

#ifdef __cplusplus
}
#endif

#endif
