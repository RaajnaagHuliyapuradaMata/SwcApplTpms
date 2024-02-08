#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "TSS_StdX.hpp"
#include "statistics.hpp"
#include "statistics_if.hpp"
#include "statisticsx.hpp"
#include "procdatx.hpp"
#include "uswarn_Ifx.hpp"
#include "ReDiagX.hpp"
#include "State_BzX.hpp"
#include "CfgSwcApplTpms_IDOM.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "SwcApplTpms_DTC_If.hpp"

const uint8 cAccMeasInt1a = 3;
const uint8 cAccMeasInt1b = 60;

static uint16 ushGutEmpfCntSTATISTICS[cAnzRad];
static uint16 ushMissedCntSTATISTICS[cAnzRad];
static uint16 usFolgeAusfallCntSTATISTICS[cAnzRad];
static uint8 ucAusbeuteSTATISTICS[cAnzRad];
static WUFD WUFDState;
static uint8 ucMarkReceivedDatagram = 0;
static uint8 ucStatisticActive;
static uint8 ucMissingErrCnt = 4;

static void CalcAusbeuteSTATISTICS(
   uint8 ucSlot);
static void PUTbWUFDActive(
   boolean value);
static void PUTbActivateWUFDTimerRun(
   boolean value);
static void PUTbProceedWUFDTimerRun(
   boolean value);
static void PUTbDeactivateWUFDTimerRun(
   boolean value);
static boolean GETbExceedVThres(
   void);
static void PUTbExceedVThres(
   boolean value);
static void PUTbStatisticActive(
   uint8 ZomPos,
   boolean value);
static void STT__InitWUFDBits(
   void);

static void PUTbWUFDActive(
   boolean value){
   WUFDState.bWUFDActive = value;
}

static void PUTbActivateWUFDTimerRun(
   boolean value){
   WUFDState.bActivateWUFDTimerRun = value;
}

static void PUTbProceedWUFDTimerRun(
   boolean value){
   WUFDState.bProceedWUFDTimerRun = value;
}

static void PUTbDeactivateWUFDTimerRun(
   boolean value){
   WUFDState.bDeactivateWUFDTimerRun = value;
}

static boolean GETbExceedVThres(
   void){
   return (boolean)(WUFDState.bExceedVThres);
}

static void PUTbExceedVThres(
   boolean value){
   WUFDState.bExceedVThres = value;
}

static void PUTbStatisticActive(
   uint8 ZomPos,
   boolean value){
   if(value == TRUE){
      ucStatisticActive |= (uint8)(1u << ZomPos);
   }
   else{
      ucStatisticActive &= ((uint8)(1u << ZomPos) ^ (uint8)0xFF);
   }
}

static void STT__InitWUFDBits(
   void){
   WUFDState.bWUFDActive = FALSE;
   WUFDState.bActivateWUFDTimerRun = FALSE;
   WUFDState.bDeactivateWUFDTimerRun = FALSE;
   WUFDState.bProceedWUFDTimerRun = FALSE;
   WUFDState.bExceedVThres = FALSE;
}

boolean GETbWUFDActive(
   void){
   return (boolean)(WUFDState.bWUFDActive);
}

boolean GETbActivateWUFDTimerRun(
   void){
   return (boolean)(WUFDState.bActivateWUFDTimerRun);
}

boolean GETbProceedWUFDTimerRun(
   void){
   return (boolean)(WUFDState.bProceedWUFDTimerRun);
}

boolean GETbDeactivateWUFDTimerRun(
   void){
   return (boolean)(WUFDState.bDeactivateWUFDTimerRun);
}

void InitSTATISTICS(
   void){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      (void)ResetCounterInSlotSTATISTICS(
         ucLoop);
   }
   STT__InitWUFDBits();
}

uint8 ResetCounterInSlotSTATISTICS(
   uint8 ucSlot){
   uint8 ucRet = cRetOk;
   if(ucSlot < cAnzRad){
      ushGutEmpfCntSTATISTICS[ucSlot] = 0;
      ushMissedCntSTATISTICS[ucSlot] = 0;
      usFolgeAusfallCntSTATISTICS[ucSlot] = 0;
      ucAusbeuteSTATISTICS[ucSlot] = 0;
      SetRecCounterInEE(
         0,
         ucSlot);
      SetMissCounterInEE(
         0,
         ucSlot);
      SetFailCounterInEE(
         0,
         ucSlot);
   }
   else{
      ucRet = cRetError;
   }
   return ucRet;
}

uint16 GETusFolgeAusfallCntSTATISTICS(
   uint8 ucSlot){
   return usFolgeAusfallCntSTATISTICS[ucSlot];
}

void PUTusFolgeAusfallCntSTATISTICS(
   uint16 ucFolgeAusfallCnt,
   uint8 ucSlot){
   usFolgeAusfallCntSTATISTICS[ucSlot] = ucFolgeAusfallCnt;
}

uint16 GETushGutEmpfCntSTATISTICS(
   uint8 ucSlot){
   return ushGutEmpfCntSTATISTICS[ucSlot];
}

uint16 GETushMissedCntSTATISTICS(
   uint8 ucSlot){
   return ushMissedCntSTATISTICS[ucSlot];
}

void ReloadSTATISTICS(
   void){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      ushGutEmpfCntSTATISTICS[ucLoop] = GetRecCounterInEE(
         ucLoop);
      ushMissedCntSTATISTICS[ucLoop] = GetMissCounterInEE(
         ucLoop);
      usFolgeAusfallCntSTATISTICS[ucLoop] = GetFailCounterInEE(
         ucLoop);
      if((usFolgeAusfallCntSTATISTICS[ucLoop] < GETusMaxFolgeAusfallEE()) && (DTC_GetActiveStatusOfDTC(
         ucWUFailERRc[ucLoop]) == 0)){
         if((usFolgeAusfallCntSTATISTICS[ucLoop] <= ucMaxFF4RFInterference) && (DTC_GetActiveStatusOfDTC(
            cZO_ERR_RF_INTERFERENCE) == 0)){
            usFolgeAusfallCntSTATISTICS[ucLoop] = 0;
         }
      }

      CalcAusbeuteSTATISTICS(
         ucLoop);
   }
   STT__InitWUFDBits();
}

void StoreSTATISTICS(
   void){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      SetRecCounterInEE(
         ushGutEmpfCntSTATISTICS[ucLoop],
         ucLoop);
      SetMissCounterInEE(
         ushMissedCntSTATISTICS[ucLoop],
         ucLoop);
      SetFailCounterInEE(
         usFolgeAusfallCntSTATISTICS[ucLoop],
         ucLoop);
   }
}

static void CalcAusbeuteSTATISTICS(
   uint8 ucSlot){
   uint32 ulSum;
   ulSum = (uint32)ushGutEmpfCntSTATISTICS[ucSlot] + (uint32)ushMissedCntSTATISTICS[ucSlot];
   if(ulSum >= 100){
      uint16 l_uiGutRx;
      l_uiGutRx = ushGutEmpfCntSTATISTICS[ucSlot];
      ucAusbeuteSTATISTICS[ucSlot] = (uint8)(((uint32)l_uiGutRx * (uint32)100U) / ulSum);
   }
   else{
      ucAusbeuteSTATISTICS[ucSlot] = 0;
   }
}

uint8 CountValidDatagramSTATISTICS(
   uint8 ucSlot){
   uint8 ucRet = cRetOk;
   if(ucSlot < cAnzRad){
      ushGutEmpfCntSTATISTICS[ucSlot]++;
      PUTusFolgeAusfallCntSTATISTICS(
         0,
         ucSlot);
      PUTbStatisticActive(
         ucSlot,
         TRUE);
      CalcAusbeuteSTATISTICS(
         ucSlot);
   }
   else{
      ucRet = cRetError;
   }
   return ucRet;
}

uint8 CountInvalidDatagramSTATISTICS(
   uint8 ucSlot){
   uint8 ucRet = cRetOk;
   if(ucSlot < cAnzRad){
      ushMissedCntSTATISTICS[ucSlot]++;
      CalcAusbeuteSTATISTICS(
         ucSlot);
   }
   else{
      ucRet = cRetError;
   }
   return ucRet;
}

void ExceedVThresSTATISTICS(
   void){
   if(GETbWUFDActive() == FALSE){
      if(GETbActivateWUFDTimerRun() == FALSE){
         SetRelAlarmAlActivateWUFDOS(
            cAccMeasInt1a,
            0);
         PUTbActivateWUFDTimerRun(
            TRUE);
      }
   }
   if(GETbProceedWUFDTimerRun() == FALSE){
      SetRelAlarmAlProceedWUFDOS(
         cAccMeasInt1b,
         0);
      PUTbProceedWUFDTimerRun(
         TRUE);
   }
}

void UnderrunVThresSTATISTICS(
   void){
   CancelAlarmAlActivateWUFDOS();
   PUTbActivateWUFDTimerRun(
      FALSE);
   CancelAlarmAlProceedWUFDOS();
   PUTbProceedWUFDTimerRun(
      FALSE);
   if(GETbWUFDActive() == TRUE){
      if(CarIsDriving() == TRUE){
         if(GETbDeactivateWUFDTimerRun() == FALSE){
            SetRelAlarmAlDeactivateWUFDOS(
               5 * cAccMeasInt1b,
               0);
            PUTbDeactivateWUFDTimerRun(
               TRUE);
         }
         else{
         }
      }
      else{
      }
   }
   else{
   }
}

void ActivateWUFDSTATISTICS(
   void){
   PUTbWUFDActive(
      TRUE);
   PUTbActivateWUFDTimerRun(
      FALSE);
}

void DeactivateWUFDSTATISTICS(
   void){
   if(GETbWUFDActive() == TRUE){
      PUTbWUFDActive(
         FALSE);
      PUTbDeactivateWUFDTimerRun(
         FALSE);
   }
   else{
   }
}

void ProceedWUFDSTATISTICS(
   void){
   if(GETbWUFDActive() == TRUE){
      CancelAlarmAlDeactivateWUFDOS();
      PUTbDeactivateWUFDTimerRun(
         FALSE);
   }
   else{
      ActivateWUFDSTATISTICS();
   }
   PUTbProceedWUFDTimerRun(
      FALSE);
}

void CheckWUFDVThresSTATISTICS(
   void){
   if(ReDiagActive() == TRUE){
      if(GETbExceedVThres() == FALSE){
         PUTbExceedVThres(
            TRUE);
         SetEventEvExceedVThresOS();
      }
   }
   else{
      if(CarIsDriving() == TRUE){
         if(GETbExceedVThres() == TRUE){
            SetEventEvUnderrunVThresOS();
         }
      }
      else{
         if(GETbWUFDActive() == TRUE){
            SetEventEvUnderrunVThresOS();
         }
      }
      PUTbExceedVThres(
         FALSE);
   }
}

void MissedCntStatistics(
   void){
   uint8 ucLoop;
   uint16 usLocalCntValue;
   boolean bPossibleRfInterference = FALSE;
   ucMissingErrCnt = cAnzRad;
   if( FALSE != bGetBitBetriebszustandBZ(
      cER_FINISH | cEIGENRAD)){
      for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
         if((ucMarkReceivedDatagram & (uint8)(1u << ucLoop)) != 0x00){
            PUTusFolgeAusfallCntSTATISTICS(
               0,
               ucLoop);
         }
         else{
            usLocalCntValue = GETusFolgeAusfallCntSTATISTICS(
               ucLoop);
            if((usLocalCntValue != 0u) && ((usLocalCntValue % 33u) == 0)){
               (void)CountInvalidDatagramSTATISTICS(
                  ucLoop);
            }
            else{
            }
            if(GETbWUFDActive() == TRUE){
               PUTbStatisticActive(
                  ucLoop,
                  TRUE);
               if((RfInterferenceActive() == TRUE) || (GetWUHighTempRD(
                  ucLoop) > 2)){
                  if(GETusFolgeAusfallCntSTATISTICS(
                     ucLoop) < ucMaxFF4RFInterference){
                     PUTusFolgeAusfallCntSTATISTICS(
                        GETusFolgeAusfallCntSTATISTICS(
                           ucLoop) + 1u,
                        ucLoop);
                  }
               }
               else{
                  if(GETusFolgeAusfallCntSTATISTICS(
                     ucLoop) < 8000u){
                     PUTusFolgeAusfallCntSTATISTICS(
                        GETusFolgeAusfallCntSTATISTICS(
                           ucLoop) + 1u,
                        ucLoop);
                  }
               }
            }
         }
         if(CheckWUFDErr(
            GETusFolgeAusfallCntSTATISTICS(
               ucLoop),
            ucLoop) == TRUE){
            ClearReDataInSlotPD(
               ucLoop);
            (void)ResetWarnVectorUSWIF(
               ucLoop);
            (void)ClearWarnOfIdUSWIF(
               ucLoop);
         }
      }
      bPossibleRfInterference = bGetPossibleRfInterf();
      if(bPossibleRfInterference == FALSE){
         PUTbHfIntLatchEE(
            FALSE);
      }
      if(CarIsDriving() == FALSE){
         PUTbWUFDActive(
            FALSE);
         CancelAlarmAlMissedRxCntOS();
      }
   }
   else{
   }
   ucMarkReceivedDatagram = 0;
}

void PUTucMarkReceivedDatagramSTATISTICS(
   boolean Value,
   uint8 Col){
   if(Col < cAnzRad){
      if(Value == TRUE){
         ucMarkReceivedDatagram |= (uint8)(0x01u << Col);
      }
      else{
         ucMarkReceivedDatagram &= ((uint8)(0x01u << Col) ^ (uint8)0xFF);
      }
   }
}

boolean GETbStatisticActiveSTATISTICS(
   const uint8 col){
   boolean bRet = FALSE;
   if(col < cAnzRad){
      if((ucStatisticActive & (uint8)(0x01u << col)) == (uint8)(0x01u << col)){
         bRet = TRUE;
      }
   }
   return (bRet);
}

uint8 DCM_InvIf_RecepMissedGetCntValue(
   uint8 u8_HistoryIDValue){
   return (uint8)(0x00FFu & (GETusFolgeAusfallCntSTATISTICS(
      u8_HistoryIDValue) >> 2));
}

void PutMissingErrCnt(
   uint8 ucCurrentValue){
   ucMissingErrCnt = ucCurrentValue;
}

uint8 ucGetMissingErrorCnt(
   void){
   return ucMissingErrCnt;
}

boolean bGetPossibleRfInterf(
   void){
   uint8 ucLoop = 0;
   boolean bTmpReturn = FALSE;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(GETusFolgeAusfallCntSTATISTICS(
         ucLoop) >= ucMaxFF4RFInterference){
         bTmpReturn = TRUE;
         break;
      }
      else{
      }
   }
   return bTmpReturn;
}

