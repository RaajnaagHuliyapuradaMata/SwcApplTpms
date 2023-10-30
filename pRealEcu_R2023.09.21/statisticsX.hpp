#ifndef _statistics_X_H
#define _statistics_X_H

#include "tss_stdx.hpp"

extern void InitSTATISTICS(void);
extern uint8 ResetCounterInSlotSTATISTICS(uint8 ucSlot);

extern uint16 GETusFolgeAusfallCntSTATISTICS(uint8 ucSlot);
extern void PUTusFolgeAusfallCntSTATISTICS(uint16 ucFolgeAusfallCnt, uint8 ucSlot);

extern uint16 GETushMissedCntSTATISTICS(uint8 ucSlot);

extern void ReloadSTATISTICS(void);
extern void StoreSTATISTICS(void);

extern uint8 CountValidDatagramSTATISTICS(uint8 ucSlot);
extern uint8 CountInvalidDatagramSTATISTICS(uint8 ucSlot);

extern void ExceedVThresSTATISTICS(void);
extern void UnderrunVThresSTATISTICS(void);
extern void ActivateWUFDSTATISTICS(void);
extern void DeactivateWUFDSTATISTICS(void);
extern void ProceedWUFDSTATISTICS(void);
extern void CheckWUFDVThresSTATISTICS(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void TransmitIntervalCompleteSTATISTICS(void);
extern uint8 GETucAusbeuteSTATISTICS(uint8 ucSlot);
#endif

extern uint16 GETushGutEmpfCntSTATISTICS(uint8 ucSlot);
extern void MissedCntStatistics(void);
extern void PUTucMarkReceivedDatagramSTATISTICS(boolean Value, uint8 Col);

extern boolean GETbStatisticActiveSTATISTICS(const uint8 col);

extern boolean GETbWUFDActive(void);
extern boolean GETbActivateWUFDTimerRun(void);
extern boolean GETbProceedWUFDTimerRun(void);
extern boolean GETbDeactivateWUFDTimerRun(void);

extern void PutMissingErrCnt (uint8 ucCurrentValue);
extern uint8 ucGetMissingErrorCnt(void);
extern boolean bGetPossibleRfInterf(void);

#endif
