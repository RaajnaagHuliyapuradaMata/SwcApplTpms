#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "cd_decoder_x.h"
#include "WallocX.h"

#ifdef FPA
#define cMinStretch  (uint8) 0x30
#define cMinCt4Dec   (uint8) 14
#define SPEEDWEIGHT
#define cSPW_THRESHOLD  (uint8) 60
#define cDELTAMIN           5
#define cDELTAMIN_STEP2     4
#define cDELTAMIN_STEP3     3
#define cDELTAFIGHT         10
#define cABSOLUTEMIN        18
#define cDELTAMIN_FOR_LEARN 8
#define cLocSyncAngleMask       0x0C
#define cLocSyncAngleNoSupport  0x00
#define cLocSyncAngleFailed     0x04
#define cLocSyncAngle1          0x08
#define cLocSyncAngle2          0x0C
#define cLocSyncFrameMask       0x03
#define cLocSyncFrameNotUsed    0x00
#define cLocSyncFrame1          0x01
#define cLocSyncFrame2          0x02
#define cLocSyncFrame3          0x03
#define cLocSyncNoAngleNoFrame  0xf0U

extern void  RebuildABSRef(uint8 ucWP);
extern void  ReNewABSRef(void);
extern uint8 ucGetRefPointResetCounter(void);
extern uint8 ucGetZomLowestMetricsValueFPA(uint8 ucSlot);
extern uint8 ucTriggerFixPointAllocationFPA(uint8 ucZomIndex, const tRFTelType * ptInputWA);
extern uint8 ucLocateWheelPositionsFPA(boolean bUseForcedAlloc);
extern uint8 ucLocateWheelPositionsPartialFPA(uint8 ucNoOfSlots);
extern void  CalcInfoZomMinDistFPA(void);
extern void  SetAllocMinDeltaValueFPA(uint8 ucValue);
extern void  SetAllocAbsoluteMinValueFPA(uint8 ucValue);
extern uint8 ucGetAllocMinDeltaValueFPA(void);
extern uint8 ucGetAllocAbsoluteMinValueFPA(void);
#endif

# ifdef __cplusplus
}
# endif
