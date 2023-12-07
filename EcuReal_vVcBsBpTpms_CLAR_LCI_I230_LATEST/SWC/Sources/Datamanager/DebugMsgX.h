

#ifndef _debugmsg_X_H
#define _debugmsg_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define USE_DEBUG_MESSAGE  1
#define DEBUG_MESSAGE_SIZE 32

extern uint8 CreateSetOfEventSpecificDataDBG( const ImpTypeRecCddRdcData* rdcData);

extern void GetDebugMessageContentDBG(Rte_Instance self, uint8* pucBuffer);

extern void SetSwcRunTimeDBG(uint8 ucRunTime);

extern void IncreaseRCyclicCallCounter(void);

extern void IncreaseWriteErrorCounterForNvmWarnstatusBlock(void);

#ifdef __cplusplus
}
#endif

#endif
