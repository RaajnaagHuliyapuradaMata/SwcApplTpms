#ifndef _statistics_H
#define _statistics_H

#include "tss_stdx.hpp"

#ifdef IBTCM_SW_ANPASSUNGEN
typedef struct{
  bitfield bWUFDActive              : 1;
  bitfield bActivateWUFDTimerRun    : 1;
  bitfield bProceedWUFDTimerRun     : 1;
  bitfield bDeactivateWUFDTimerRun  : 1;

  bitfield bExceedVThres            : 1;
  bitfield                          :11;
}WUFD;
#else
typedef struct{
  boolean bWUFDActive              :1;
  boolean bActivateWUFDTimerRun    :1;
  boolean bProceedWUFDTimerRun     :1;
  boolean bDeactivateWUFDTimerRun  :1;

  boolean bExceedVThres            :1;
  boolean                          :3;
}WUFD;
#endif

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
#ifdef BUILD_WITH_UNUSED_FUNCTION
void TransmitIntervalCompleteSTATISTICS(void);
#endif
void MissedCntStatistics(void);
void PUTucMarkReceivedDatagramSTATISTICS(boolean Value, uint8 Col);

#endif
