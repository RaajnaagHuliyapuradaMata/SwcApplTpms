#ifndef _statistics_H
#define _statistics_H

#include "tss_stdx.hpp"

typedef struct{
  bitfield bWUFDActive              : 1;
  bitfield bActivateWUFDTimerRun    : 1;
  bitfield bProceedWUFDTimerRun     : 1;
  bitfield bDeactivateWUFDTimerRun  : 1;
  bitfield bExceedVThres            : 1;
  bitfield                          :11;
}WUFD;

void InitSTATISTICS(void);
uint8 ResetCounterInSlotSTATISTICS(uint8 ucSlot);
uint16 GETusFolgeAusfallCntSTATISTICS(uint8 ucSlot);
void PUTusFolgeAusfallCntSTATISTICS(uint16 ucFolgeAusfallCnt, uint8 ucSlot);
uint16 GETushGutEmpfCntSTATISTICS(uint8 ucSlot);
uint16 GETushMissedCntSTATISTICS(uint8 ucSlot);
uint8 GETucAusbeuteSTATISTICS(uint8 ucSlot);
void ReloadSTATISTICS(void);
void StoreSTATISTICS(void);
uint8 CountValidDatagramSTATISTICS(uint8 ucSlot);
uint8 CountInvalidDatagramSTATISTICS(uint8 ucSlot);
void ExceedVThresSTATISTICS(void);
void UnderrunVThresSTATISTICS(void);
void ActivateWUFDSTATISTICS(void);
void DeactivateWUFDSTATISTICS(void);
void ProceedWUFDSTATISTICS(void);
void CheckWUFDVThresSTATISTICS(void);
void MissedCntStatistics(void);
void PUTucMarkReceivedDatagramSTATISTICS(boolean Value, uint8 Col);

#endif
