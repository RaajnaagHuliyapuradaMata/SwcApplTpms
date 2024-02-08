#define WALLOC_INT

#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "WallocX.hpp"
#include "Walloc_IF.hpp"
#include "walloc.hpp"
#include "FPA.hpp"
#include "CfgSwcApplTpms.hpp"
#include "procdatx.hpp"
#include "state_bzX.hpp"
#include "statemanagerX.hpp"
#include "global.hpp"
#include "uswarn_Ifx.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

#define cWPER                                                               0x10

static const unsigned char ucWACtrlFixc = 0x01;
static const unsigned char ucWACtrlBreakc = 0x02;
static unsigned char ucWAState;
static unsigned long aulHistoryID[cMaxLR];
static unsigned char aucHistoryWP[cMaxLR];
static unsigned char ucNrOfTOs;
static unsigned short ushHistProtecTimeCnt;

WAABSTicksInOneRevolution tABSTicksOneRevol;

#ifdef DETECT_SYMC_WALLOC_DTC
static uint8 sm_ucWPConsistentErrCnt = 0;
static uint8 sm_ucAxisDetectionErrCnt = 0;
static uint8 sm_ucDirDetectionErrCnt = 0;

struct ZOMSlot tZOM[cSumWE];
WAParameter tWAPar;

void IncAxisDetectionError(
   void);
uint8 CheckForDetailed_ZO_Error(
   void);
#endif

static unsigned short ushIDSetInHist(
   unsigned long* ptHistSet,
   unsigned char ucMinProbeCt,
   unsigned char ucSlots2Search);
static unsigned char ucNrOfBitSet(
   unsigned short ushTarget);

static boolean bCheckIfNewTelAllowed(
   struct InputWA* ptInputWA,
   unsigned char ucIx);
static void CheckAndMarkNewIdER(
   unsigned char ucIx);
static boolean bGetZomPotentStatusOfID(
   unsigned char ucIx);

#pragma PRQA_NO_SIDE_EFFECTS bGetZomPotentStatusOfID
static boolean bGetZomOwnStatusOfID(
   unsigned char ucIx);
#pragma PRQA_NO_SIDE_EFFECTS bGetZomOwnStatusOfID

static unsigned char ucGetHistoryState(
   void);
#pragma PRQA_NO_SIDE_EFFECTS ucGetHistoryState

static void SetWActiveState(
   unsigned char ucVal);
static unsigned char ucGetWActiveState(
   void);
static void SetERState(
   unsigned char ucVal);
static void SetZOState(
   unsigned char ucVal);
static unsigned char ucGetZOState(
   void);
static void SetWAStateZOChange(
   unsigned char ucChangedPos);
static void ResetWP(
   void);
static void PutulID(
   unsigned char ucIx,
   unsigned long* p2ID);
static unsigned char ucGetFreeZOMPos(
   void);
static unsigned char ucStartWA(
   void);
static unsigned char ucLowestProbe(
   unsigned short ushException);
static unsigned short ushCheckERState(
   unsigned char ucZomID);
static unsigned char ucCheckWheelPos(
   void);
static void SafeData(
   struct InputWA* ptInputWA,
   unsigned char ucIx);
static void DriveDir(
   unsigned char* pucStatus);
static unsigned char ucActualize(
   struct InputWA* ptInputWA,
   WAParameter* ptWAPar);
static void RestoreHistory(
   void);
static unsigned short ushSumPotenAndERWheels(
   void);

static void SetWActiveState(
   unsigned char ucVal){
   if(ucVal == 0){
      ucWAState &= NEGATE_UCHAR(
         cWAStateActive);
   }
   else{
      ucWAState |= cWAStateActive;
   }
}

static unsigned char ucGetWActiveState(
   void){
   return (
         ((ucWAState & cWAStateActive) == cWAStateActive) ? (unsigned char)1 : (unsigned char)0);
}

static void SetERState(
   unsigned char ucVal){
   if(ucVal == 0){
      ucWAState &= NEGATE_UCHAR(
         cWAStateER);
   }
   else{
      ucWAState |= cWAStateER;
   }
}

unsigned char ucGetERState(
   void){
   return (
         ((ucWAState & cWAStateER) == cWAStateER) ? (unsigned char)1 : (unsigned char)0);
}

static void SetZOState(
   unsigned char ucVal){
   if(ucVal == 0){
      ucWAState &= NEGATE_UCHAR(
         cWAStateZO);
   }
   else{
      ucWAState |= cWAStateZO;
   }
}

static unsigned char ucGetZOState(
   void){
   return (
         ((ucWAState & cWAStateZO) == cWAStateZO) ? (unsigned char)1 : (unsigned char)0);
}

static void SetWAStateZOChange(
   unsigned char ucChangedPos){
   ucWAState &= 0x0F;
   ucWAState |= ucChangedPos;
}

void ClearZOM(
   unsigned char ucIx){
   unsigned char i, j;
   if(ucIx > cSumWE){
   }
   else{
      if(ucIx == (unsigned char) cSumWE){
         for(i = 0; i < ucIx; i++){
            for(j = 0; j < (unsigned char)sizeof(struct ZOMSlot); j++){
               *((unsigned char*)&tZOM[i] + j) = 0;
            }
         }
      }
      else{
         for(j = 0; j < (unsigned char)sizeof(struct ZOMSlot); j++){
            *((unsigned char*)&tZOM[ucIx] + j) = 0;
         }
      }
   }
}

static void ResetWP(
   void){
   unsigned char i;
   for(i = 0; i < cMaxLR; i++){
      tZOM[i].ucStatus &= cNoWPos;
   }
}

unsigned long ulGetZOMID(
   unsigned char ucIx){
   if(ucIx < cSumWE){
      return (tZOM[ucIx].ulID);
   }
   else{
      return ((unsigned char)0);
   }
}

unsigned long ulGetID(
   unsigned char ucIx){
   if(ucIx < cMaxLR){
      return (aulHistoryID[ucIx]);
   }
   else{
      return ((unsigned char)0);
   }
}

static void PutulID(
   unsigned char ucIx,
   unsigned long* p2ID){
   if(ucIx < cSumWE){
      tZOM[ucIx].ulID = *p2ID;
   }
}

unsigned char ucGetProbeCt(
   unsigned char ucIx){
   if(ucIx < cSumWE){
      return (tZOM[ucIx].ucProbeCt);
   }
   else{
      return ((unsigned char)0);
   }
}

unsigned char ucGetZOMWP(
   unsigned char ucIx){
   uint8 u8ReturnValue;
   if(ucIx < cMaxLR){
      switch(tZOM[ucIx].ucStatus & (0xFF & ~cNoWPos )){
         case 0x01: {
            u8ReturnValue = 0U;
            break;
         }
         case 0x02: {
            u8ReturnValue = 1U;
            break;
         }
         case 0x04: {
            u8ReturnValue = 2U;
            break;
         }
         case 0x08: {
            u8ReturnValue = 3U;
            break;
         }
         default: {
            u8ReturnValue = 4U;
            break;
         }
      }
   }
   else{
      u8ReturnValue = 4U;
   }
   return u8ReturnValue;
}

void SetZOMWP(
   unsigned char ucIx,
   unsigned char ucWP){
   if(ucIx < cMaxLR){
      tZOM[ucIx].ucStatus &= cNoWPos;
      if(ucWP < cMaxLR){
         tZOM[ucIx].ucStatus |= (unsigned char)(0x01 << ucWP);
      }
   }
}

unsigned short ushGetMeanRssiSum(
   unsigned char ucIx){
   unsigned long ulTmp;
   if(ucIx < cSumWE){
      if(tZOM[ucIx].ucProbeCt != 0){
         ulTmp = ((((unsigned long)tZOM[ucIx].ushRssiSum * 10) / tZOM[ucIx].ucProbeCt) + (unsigned char)5) / (unsigned char)10;
      }
      else{
         ulTmp = 0U;
      }
   }
   else{
      ulTmp = 0U;
   }
   return ((unsigned short)ulTmp);
}

unsigned char ucGetRssiDifference(
   unsigned char ucFirstIx,
   unsigned char ucSecondIx){
   unsigned char ucFirstRssi = 0;
   unsigned char ucSecondRssi = 0;
   ucFirstRssi = (unsigned char)ushGetMeanRssiSum(
      ucFirstIx);
   ucSecondRssi = (unsigned char)ushGetMeanRssiSum(
      ucSecondIx);
   if(ucFirstRssi > ucSecondRssi){
      return ucFirstRssi - ucSecondRssi;
   }
   else{
      return ucSecondRssi - ucFirstRssi;
   }
}

unsigned char ucGetZOMPosOfID(
   unsigned long* pt2ID){
   unsigned char i;
   for(i = 0; i < cSumWE; i++){
      if(*pt2ID == tZOM[i].ulID){
         break;
      }
   }
   return (i);
}

static boolean bGetZomPotentStatusOfID(
   unsigned char ucIx){
   if(tZOM[ucIx].bPotNewID == 0x01U){
      return TRUE;
   }
   else{
      return FALSE;
   }
}

static boolean bGetZomOwnStatusOfID(
   unsigned char ucIx){
   if(tZOM[ucIx].bOwnID == 0x01U){
      return TRUE;
   }
   else{
      return FALSE;
   }
}

unsigned char ucGetColOfID(
   unsigned long* pt2ID){
   unsigned char i;
   for(i = 0; i < cMaxLR; i++){
      if(*pt2ID == aulHistoryID[i]){
         break;
      }
   }
   return (i);
}

unsigned char ucGetWPOfCol(
   unsigned char ucIx){
   if(ucIx < cMaxLR){
      return (aucHistoryWP[ucIx]);
   }
   else{
      return ((unsigned char)4);
   }
}

unsigned char ucGetIndexOfHistoryWP(
   unsigned char ucWPNumber){
   unsigned char i;
   for(i = 0; i < cMaxLR; i++){
      if(ucWPNumber == aucHistoryWP[i]){
         break;
      }
   }
   return i;
}

static unsigned char ucGetFreeZOMPos(
   void){
   unsigned char i;
   for(i = 0; i < cSumWE; i++){
      if(tZOM[i].ulID == (unsigned long)0){
         break;
      }
   }
   return (i);
}

static unsigned char ucStartWA(
   void){
   unsigned char i, ucRet = 0;
   for(i = 0; i < cSumWE; i++){
      if(tZOM[i].ucProbeCt > 0){
         ucRet++;
      }
   }
   ucRet = (ucRet == cMaxLR) ? (unsigned char)1 : (unsigned char)0;
   return (ucRet);
}

void AlignZOM(
   unsigned short ushERSlot){
   unsigned char i, j, k, ucCt = 0;
   for(i = 0; i < cSumWE; i++){
      if((((unsigned short)(1 << i)) & ushERSlot) > 0){
         ucCt++;
      }
      else{
         for(j = i + 1; j < cSumWE; j++){
            if((((unsigned short)(1 << j)) & ushERSlot) > 0){
               ucCt++;
               for(k = 0; k < (unsigned char)sizeof(struct ZOMSlot); k++){
                  *(((unsigned char*)&tZOM[i]) + k) = *(((unsigned char*)&tZOM[j]) + k);
               }
               ushERSlot |= (1 << i);
               ushERSlot &= ~(1 << j);
               ClearZOM(
                  j);
               break;
            }
         }
      }
      if(ucCt == cMaxLR){
         break;
      }
   }
}

static unsigned char ucLowestProbe(
   unsigned short ushException){
   unsigned char i, ucMinIx = 0x80;
   for(i = 0; i < cSumWE; i++){
      if(((unsigned short)(0x01 << i) & ushException) == 0){
         if(ucMinIx == 0x80){
            ucMinIx = i;
         }
         else{
            if(ucGetProbeCt(
               i) < ucGetProbeCt(
               ucMinIx)){
               ucMinIx = i;
            }
         }
      }
   }
   return ((ucMinIx & 0x7F));
}

unsigned char ucSumCtID(
   unsigned char ucMinCt,
   unsigned char ucMinRssi){
   unsigned char i, ucCt = 0;
   for(i = 0; i < cSumWE; i++){
      if((ucGetProbeCt(
         i) >= ucMinCt) && (ushGetMeanRssiSum(
         i) >= ucMinRssi)){
         ucCt++;
      }
   }
   return (ucCt);
}

static unsigned short ushCheckERState(
   unsigned char ucZomID){
   unsigned short ushRet = 0;
   unsigned char i;
   CheckAndMarkNewIdER(
      ucZomID);
   ushRet = ushSumPotenAndERWheels();
   if(ucSumCtID(
      tWAPar.ucMinCt4ZomReset,
      tWAPar.ucMinERMeanRssiLevel) > cMaxLR){
      ClearZOM(
         cSumWE);
      ushRet = 0;
   }
   if(ucNrOfBitSet(
      ushRet) == cMaxLR){
      for(i = 0; i < cSumWE; i++){
         if(tZOM[i].bPotNewID == 0x01U){
            tZOM[i].bPotNewID = FALSE;
            tZOM[i].bOwnID = TRUE;
         }
      }
   }
   else{
      ushRet = 0;
   }
   return (ushRet);
}

static void CheckAndMarkNewIdER(
   unsigned char ucIx){
   unsigned char i, ucRet = 0;
   boolean bHistID;
   for(i = 0; i < cMaxLR; i++){
      if(aulHistoryID[i] == ulGetZOMID(
         ucIx)){
         if(ucGetProbeCt(
            ucIx) >= tWAPar.ucMinCt4HistER){
            tZOM[ucIx].bOwnID = TRUE;
         }
         bHistID = TRUE;
         break;
      }
      else{
         bHistID = FALSE;
      }
   }
   if(FALSE == bHistID){
      if((FALSE == ucGetHistoryState()) || (TRUE == bGetHistProtecTimeOver())){
         for(i = 0; i < cSumWE; i++){
            tZOM[i].bPotNewID = TRUE;
            if(!((tZOM[i].ucProbeCt >= tWAPar.ucMinCt4ER) && (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt))){
               tZOM[i].bPotNewID = FALSE;
            }
            if(tZOM[i].bPotNewID == TRUE){
               if((tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 4]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]]) < tWAPar.ucnMinA){
                  tZOM[i].bPotNewID = FALSE;
                  if(ushGetMeanRssiSum(
                     i) > tWAPar.ucMinERMeanRssiLevel){
                     tZOM[i].bPotNewID = TRUE;
                  }
               }
               if(ushGetMeanRssiSum(
                  i) < tWAPar.ucMinERMeanRssiLevel){
                  tZOM[i].bPotNewID = FALSE;
               }
            }
         }
      }
   }
}

static unsigned short ushSumPotenAndERWheels(
   void){
   unsigned char i;
   unsigned short ushRet = 0;
   for(i = 0; i < cSumWE; i++){
      if((TRUE == (bGetZomPotentStatusOfID(
         i))) || (TRUE == (bGetZomOwnStatusOfID(
         i)))){
         ushRet |= (unsigned short)(1 << i);
      }
   }
   return ushRet;
}

static unsigned char ucCheckWheelPos(
   void){
   unsigned short ushRet = 0;
   ushRet = ucConceptFixPos0();
   if(ushRet == 0){
      ResetWP();
   }
   return ((unsigned char)ushRet);
}

static unsigned char ucNrOfBitSet(
   unsigned short ushTarget){
   unsigned char i, ucHits = 0;
   for(i = 0; i < 16; i++){
      if((ushTarget & (1 << i)) > 0){
         ucHits++;
      }
   }
   return (ucHits);
}

static unsigned short ushIDSetInHist(
   unsigned long* ptHistSet,
   unsigned char ucMinProbeCt,
   unsigned char ucSlots2Search){
   unsigned char i, j;
   unsigned short ushRet = 0;
   for(i = 0; i < cMaxLR; i++){
      if(ptHistSet[i] == cInitHistID){
         ushRet = 0;
         break;
      }
      else{
         for(j = 0; j < ucSlots2Search; j++){
            if((ptHistSet[i] == ulGetZOMID(
               j)) && (ucGetProbeCt(
               j) >= ucMinProbeCt)){
               ushRet |= (1 << j);
               break;
            }
            else{
               if(ulGetZOMID(
                  j) == (unsigned long)0){
                  break;
               }
            }
         }
      }
   }
   return (ushRet);
}

static void SafeData(
   struct InputWA* ptInputWA,
   unsigned char ucIx){
   if(ucIx < cSumWE){
      if(tZOM[ucIx].ulID > (unsigned long)0){
         tZOM[ucIx].ushVariation +=
               (tZOM[ucIx].ucLastRssi > ptInputWA->ucRssi) ? (tZOM[ucIx].ucLastRssi - ptInputWA->ucRssi) : (ptInputWA->ucRssi - tZOM[ucIx].ucLastRssi);
      }
      else{
         tZOM[ucIx].ulID = ptInputWA->ulID;
      }
      tZOM[ucIx].ucLastRssi = ptInputWA->ucRssi;
      tZOM[ucIx].ucSkipNewTelTimerInSec = 9;
      if((tZOM[ucIx].ucProbeCt < (unsigned char)255)){
         if(((unsigned short)65535 - tZOM[ucIx].ushRssiSum) > ptInputWA->ucRssi){
            tZOM[ucIx].ushRssiSum += ptInputWA->ucRssi;
            tZOM[ucIx].ucProbeCt++;
            if((tZOM[ucIx].ucProbeCt == (unsigned char)255)){
               tWAPar.ucWACtrl |= ucWACtrlFixc;
            }
         }
         else{
            tWAPar.ucWACtrl |= ucWACtrlFixc;
         }
      }
      else{
         tWAPar.ucWACtrl |= ucWACtrlFixc;
      }
   }
   else{
   }
}

static void DriveDir(
   unsigned char* pucStatus){
   if(((*pucStatus) & cIDStateSpinning) > 0){
      if(((*pucStatus) & cIDStateSpinning) != cIDStateSpinning){
         if(((*pucStatus) & cIDStateNoDrvInfo) == cIDStateNoDrvInfo){
            *pucStatus |= cIDStateSpinning;
         }
         else{
            if(((*pucStatus) & cIDStateDrvBack) == cIDStateDrvBack){
               *pucStatus = (unsigned char)~(*pucStatus);
            }
         }
      }
   }
   *pucStatus &= cIDStateSpinning;
}

static unsigned char ucActualize(
   struct InputWA* ptInputWA,
   WAParameter* ptWAPar){
   unsigned char ucRetVal = cSumWE;
   unsigned char ucIx = cSumWE;
   boolean bTelAllowed = FALSE;
   unsigned char ucNewAPCData = FALSE;
   ucIx = ucGetZOMPosOfID(
      &ptInputWA->ulID);
   bTelAllowed = bCheckIfNewTelAllowed(
      ptInputWA,
      ucIx);
   if(TRUE == bTelAllowed){
      DriveDir(
         (unsigned char*)&(ptInputWA->ucStatus));
      if(ucIx < cSumWE){
         if(ptInputWA->ucRssi > 0){
            SafeData(
               ptInputWA,
               ucIx);
         }
         else{
            bTelAllowed = FALSE;
         }
      }
      else{
         ucIx = ucGetFreeZOMPos();
         if(ucIx < cSumWE){
            if(ptInputWA->ucRssi >= ptWAPar->ucMinRssiLevel){
               SafeData(
                  ptInputWA,
                  ucIx);
            }
            else{
               bTelAllowed = FALSE;
            }
         }
         else{
            if(ucGetERState() == 0){
               ucIx = ucLowestProbe(
                  ushIDSetInHist(
                     aulHistoryID,
                     (unsigned char)1,
                     cSumWE));
               if(ptInputWA->ucRssi >= ptWAPar->ucMinRssiLevel){
                  ClearZOM(
                     ucIx);
                  SafeData(
                     ptInputWA,
                     ucIx);
               }
               else{
                  bTelAllowed = FALSE;
               }
            }
            else{
               bTelAllowed = FALSE;
            }
         }
      }
   }
   else{
      bTelAllowed = FALSE;
   }
   if(ucIx < cSumWE){
      ucNewAPCData = CounterPreparation(
         ucIx,
         pGetCurTel());
   }
   else{
   }
   if((FALSE != bTelAllowed) || (FALSE != ucNewAPCData)){
      ucRetVal = ucIx;
   }
   else{
      ucRetVal = cSumWE;
   }
   return (ucRetVal);
}

unsigned char ucSetHistory(
   unsigned char ucType){
   unsigned char i, j, ucRet = 0x0f;
   GetWADataEE(
      cHistorySet1,
      (unsigned char*)aulHistoryID);
   GetWADataEE(
      cHistoryWPSet1,
      aucHistoryWP);
   for(i = 0; i < cMaxLR; i++){
      for(j = 0; j < cMaxLR; j++){
         if(aulHistoryID[i] == ulGetZOMID(
            j)){
            ucRet &= (NEGATE_UCHAR(
               (0x01 << j)));
            if(ucType == cWAStateZO){
               if(ucGetZOMWP(
                  j) == aucHistoryWP[i]){
               }
               else{
                  aucHistoryWP[i] = ucGetZOMWP(
                     j);
                  ucRet |= (unsigned char)(0x10 << i);
               }
            }
            break;
         }
      }
      if(j == cMaxLR){
         aucHistoryWP[i] = ucGetZOMWP(
            j);
         ucRet |= (unsigned char)(0x10 << i);
      }
   }
   if(ucRet > 0){
      if(ucType == cWAStateZO){
         ucRet &= (unsigned char)0xF0;
      }
      else{
         ucType = ucRet & 0xF0;
         for(i = 0; i < cMaxLR; i++){
            if((ucRet & (0x01 << i)) > 0){
               for(j = 0; j < cMaxLR; j++){
                  if((ucRet & ((unsigned char)(0x10 << j))) > 0){
                     if(ulGetZOMID(
                        i) != 0x00000000){
                        aulHistoryID[j] = ulGetZOMID(
                           i);
                     }
                     else{
                        aulHistoryID[j] = cInitHistID;
                     }
                     ucRet &= (NEGATE_UCHAR(
                        (0x10 << j)));
                     break;
                  }
               }
            }
         }
         ucRet = ucType;
      }
      PutWADataEE(
         cHistorySet1,
         (unsigned char*)aulHistoryID);
      PutWADataEE(
         cHistoryWPSet1,
         aucHistoryWP);
   }
   return (ucRet);
}

static void RestoreHistory(
   void){
   unsigned char i, j, ucCt = 0;
   if(aulHistoryID[0] < cInitHistID){
      if(ucGetERState() == 1){
         for(i = 0; i < cMaxLR; i++){
            for(j = 0; j < cMaxLR; j++){
               if((aulHistoryID[j] == ulGetZOMID(
                  i)) && (aucHistoryWP[j] < 4)){
                  SetZOMWP(
                     i,
                     aucHistoryWP[j]);
                  ucCt++;
               }
            }
         }
      }
      else{
         for(i = 0; i < cMaxLR; i++){
            PutulID(
               i,
               &aulHistoryID[i]);
            if(aucHistoryWP[i] < 4){
               SetZOMWP(
                  i,
                  aucHistoryWP[i]);
               ucCt++;
            }
         }
         SetERState(
            1);
      }
      if(ucCt < cMaxLR){
         for(i = 0; i < cMaxLR; i++){
            SetZOMWP(
               i,
               cWPER);
         }
      }
      else{
         SetZOState(
            1);
      }
   }
}

unsigned char ucLearnID(
   struct InputWA* ptInputWA){
   unsigned short ushHelp;
   unsigned char ucCurID;
   if(ucGetZOState() == 1){
   }
   else{
      if((tWAPar.ucWACtrl & ucWACtrlFixc) > 0){
         RestoreHistory();
      }
      else{
         if((tWAPar.ucWACtrl & ucWACtrlBreakc) == 0){
            ucCurID = ucActualize(
               ptInputWA,
               &tWAPar);
            if(ucCurID < cSumWE){
               if(ucGetWActiveState() == 0){
                  if(ucStartWA() == 1){
                     SetWActiveState(
                        1);
                     StartWATO(
                        tWAPar.WATOTimeInSec);
                  }
               }
               if(ucGetERState() == 0){
                  ushHelp = ushCheckERState(
                     ucCurID);
                  if(ushHelp > 0){
                     SetERState(
                        1);
                     AlignZOM(
                        ushHelp);
                     SetWAStateZOChange(
                        ucSetHistory(
                           (unsigned char)cWAStateER));
                     ResetOldWarningsByNewEr(
                        ucWAState,
                        cMaxLR);
                     if(ucCheckWheelPos() == 1){
                        CancelWATO();
                        SetWAStateZOChange(
                           ucSetHistory(
                              (unsigned char)cWAStateZO));
                        SetZOState(
                           1);
                     }
                  }
               }
               else{
                  if(ucCheckWheelPos() == 1){
                     CancelWATO();
                     SetWAStateZOChange(
                        ucSetHistory(
                           (unsigned char)cWAStateZO));
                     SetZOState(
                        1);
                  }
               }
            }
            else{
            }
         }
      }
   }
   return (ucWAState);
}

unsigned char ucWATO(
   void){
   unsigned short ushHelp = 0;
   unsigned char ucRet = 0;
   if(ucGetZOState() < 1){
      ushHelp = ushIDSetInHist(
         aulHistoryID,
         tWAPar.ucMinCt4HistER,
         cSumWE);
      if(cMaxLR == ucNrOfBitSet(
         ushHelp)){
         if(ucGetERState() < 1){
            AlignZOM(
               ushHelp);
            SetERState(
               1);
         }
         if(ucNrOfTOs >= (tWAPar.ucTimeoutAutoLoc - 1)){
            RestoreHistory();
         }
      }
      if(ucGetZOState() != 0){
         CancelWATO();
         SaveDebugAllocType(
            0x80);
      }
      else{
         if(ucNrOfTOs >= (tWAPar.ucTimeoutAutoLoc - 1)){
            if(ucGetERState() < 1){
               if(ucGetFreeZOMPos() > cMaxLR){
                  ucRet = 5;
               }
               else{
                  if(ucGetFreeZOMPos() < cMaxLR){
                     ucRet = 9;
                  }
                  else{
                     ucRet = 1;
                  }
               }
            }
            else{
               ucRet = CheckForDetailed_ZO_Error();
            }
         }
         else{
            StartWATO(
               tWAPar.WATOTimeInSec);
         }
      }
   }
   else{
      CancelWATO();
   }
   if(ucNrOfTOs < 0xFF){
      ucNrOfTOs++;
   }
   return (ucRet);
}

uint8 ucSetID(
   uint32* pt2ID,
   uint8* pt2Pos){
   uint8 u8IndexFromPos, u8IndexFromID, ucStoredIDPosition, u8ReturnValue;
   u8ReturnValue = 0;
   if((pt2ID[0] == (uint32)0x00000000U) || (pt2ID[0] == cInitHistID)){
      ResetHistoryToDefault();
      (void)WAInit();
      u8ReturnValue = 0x0F;
   }
   else{
      GetWADataEE(
         cHistorySet1,
         (uint8*)aulHistoryID);
      GetWADataEE(
         cHistoryWPSet1,
         aucHistoryWP);
      if(pt2Pos[0] < cMaxLR){
         u8IndexFromID = ucGetColOfID(
            pt2ID);
         if(u8IndexFromID == cMaxLR){
            for(u8IndexFromPos = 0; u8IndexFromPos < cMaxLR; u8IndexFromPos++){
               if(pt2Pos[0] == aucHistoryWP[u8IndexFromPos]){
                  break;
               }
            }
            if(u8IndexFromPos == cMaxLR){
               ucStoredIDPosition = pt2Pos[0];
               aulHistoryID[ucStoredIDPosition] = pt2ID[0];
               aucHistoryWP[ucStoredIDPosition] = pt2Pos[0];
               u8ReturnValue |= (0x10 << pt2Pos[0]);
            }
            else{
               aulHistoryID[u8IndexFromPos] = pt2ID[0];
               aucHistoryWP[u8IndexFromPos] = pt2Pos[0];
               u8ReturnValue |= (0x10 << pt2Pos[0]);
            }
            if(ucGetZOState() == 1){
               ucStoredIDPosition = ucGetZOMPosOfID(
                  &pt2ID[0]);
               tZOM[ucStoredIDPosition].ulID = pt2ID[0];
               SetZOMWP(
                  ucStoredIDPosition,
                  pt2Pos[0]);
               u8ReturnValue |= (1 << ucStoredIDPosition);
            }
            else{
               u8ReturnValue |= (1 << pt2Pos[0]);
            }
         }
         else{
            if(pt2Pos[0] == aucHistoryWP[u8IndexFromID]){
               u8ReturnValue = 0;
            }
            else{
               for(u8IndexFromPos = 0; u8IndexFromPos < cMaxLR;
                     u8IndexFromPos++){
                  if(pt2Pos[0] == aucHistoryWP[u8IndexFromPos]){
                     break;
                  }
               }
               if(u8IndexFromPos < cMaxLR){
                  ucStoredIDPosition = aucHistoryWP[u8IndexFromID];
                  aucHistoryWP[u8IndexFromID] = pt2Pos[0];
                  aucHistoryWP[u8IndexFromPos] = ucStoredIDPosition;
                  u8ReturnValue |= (0x10 << pt2Pos[0]);
               }
               else{
                  if(cMaxLR <= aucHistoryWP[u8IndexFromID]){
                     aucHistoryWP[u8IndexFromID] = pt2Pos[0];
                     u8ReturnValue |= (0x10 << pt2Pos[0]);
                  }
               }
               if(ucGetZOState() == 1){
                  ucStoredIDPosition = ucGetZOMPosOfID(
                     &pt2ID[0]);
                  tZOM[ucStoredIDPosition].ulID = pt2ID[0];
                  SetZOMWP(
                     ucStoredIDPosition,
                     pt2Pos[0]);
                  u8ReturnValue |= (1 << ucStoredIDPosition);
               }
               else{
                  u8ReturnValue |= (1 << pt2Pos[0]);
               }
            }
         }
         if(u8ReturnValue > 0){
            PutWADataEE(
               cHistorySet1,
               (uint8*)aulHistoryID);
            PutWADataEE(
               cHistoryWPSet1,
               aucHistoryWP);
         }
      }
      else{
         u8ReturnValue = 0;
      }
   }
   return u8ReturnValue;
}

static unsigned char ucGetHistoryState(
   void){
   unsigned char i, ucRet = 0;
   if(aulHistoryID[0] < cInitHistID){
      ucRet |= (cHiStateER | cHiStateZG );
      for(i = 0; i < cMaxLR; i++){
         if(aucHistoryWP[i] > cWheelPos_RR){
            ucRet &= ~cHiStateZG;
         }
      }
   }
   return (ucRet);
}

unsigned char WAInit(
   void){
   unsigned char i;
   SetZOState(
      0);
   SetERState(
      0);
   SetWActiveState(
      0);
   SetWAStateZOChange(
      0);
   CancelWATO();
   ClearZOM(
      cSumWE);
   ResetAllocType();
   ResetAllocErrorCnt();
   GetWADataEE(
      cWAABSTicksInOneRevolution,
      (unsigned char*)&tABSTicksOneRevol);
   GetWADataEE(
      cWAParameter,
      (unsigned char*)&tWAPar);
   if((tWAPar.ucEcuPosition != ucECUPosFront ) && (tWAPar.ucEcuPosition != ucECUPosRear ) && (tWAPar.ucEcuPosition != ucECUPosNeutral )){
      tWAPar.ucWACtrl = ucDefWACtrl;
      tWAPar.ucMinRssiLevel = ucDefMinRssiLevel;
      tWAPar.ucMinRssiDistance = ucDefMinRssiDistance;
      tWAPar.ucMinVariationDistance = ucDefMinVariationDistance;
      tWAPar.ucLeRiMinDistance = ucDefLeRiMinDistance;
      tWAPar.ucEcuPosition = ucECUPosNeutral;
      tWAPar.ucMinCt4ER = ucDefMinCt4ER;
      tWAPar.ucMinCt4HistER = ucDefMinCt4HistER;
      tWAPar.ucMinCt4ZomReset = ucDefMinCt4ZomReset;
      tWAPar.ucMinERMeanRssiLevel = ucDefMinERMeanRssiLevel;
      tWAPar.WATOTimeInSec = ucDefWATOTimeInSec;
      tWAPar.ucTimeoutAutoLoc = ucDefTimeoutAutoLoc;
      tWAPar.ucMinTimeProtectER = ucDefMinTimeProtectER;
      tWAPar.ucnMinRxTGRF = ucnDefMinRxTGRF;
      tWAPar.ucNewMinCntEvt = ucDefNewMinCntEvt;
      tWAPar.ucnRelValMinDiff = ucDefnRelValMinDiff;
      tWAPar.ucnRelValMidDiff = ucDefnRelValMidDiff;
      tWAPar.ucnRelValCompetDiff = ucDefnRelValCompetDiff;
      tWAPar.ucMaxZOnorm = ucDefMaxZOnorm;
      tWAPar.ucnMinA = ucDefnMinA;
      tWAPar.ucMinSpeedAutoLearnStart = ucDefMinSpeedAutoLearnStart;
      tWAPar.ucOffsetOverlapsGXe = ucDefOffsetOverlapsGXe;
      tWAPar.ucnVweight = ucDefnVweight;
      tWAPar.ucMinOffsetGXe = ucDefMinOffsetGXe;
      tWAPar.ucSufficientRssiDistance = ucDefSufficientRssiDistance;
      for(i = 0; i < cMaxLR; i++){
         aulHistoryID[i] = cInitHistID;
         aucHistoryWP[i] = cNoWPos;
      }
      PutWADataEE(
         cWAParameter,
         (unsigned char*)&tWAPar);
      PutWADataEE(
         cHistorySet1,
         (unsigned char*)aulHistoryID);
      PutWADataEE(
         cHistoryWPSet1,
         aucHistoryWP);
   }
   else{
      GetWADataEE(
         cHistorySet1,
         (unsigned char*)aulHistoryID);
      GetWADataEE(
         cHistoryWPSet1,
         aucHistoryWP);
      if((tWAPar.ucWACtrl & ucWACtrlFixc) > 0){
         RestoreHistory();
      }
      tWAPar.ucWACtrl &= ~ucWACtrlBreakc;
   }
   ucNrOfTOs = 0;
   ushHistProtecTimeCnt = 0;
#ifdef FPA
   Very1stABSTickIinit();
#endif
   return (ucGetHistoryState());
}

unsigned char* GETpucStartAdrWP(
   void){
   return (aucHistoryWP);
}

void SetWAModeFix(
   void){
   tWAPar.ucWACtrl |= ucWACtrlFixc;
   PutWADataEE(
      cWAParameter,
      (unsigned char*)&tWAPar);
}

void SetWAModeLearn(
   void){
   tWAPar.ucWACtrl &= ~ucWACtrlFixc;
   PutWADataEE(
      cWAParameter,
      (unsigned char*)&tWAPar);
}

#ifdef DETECT_SYMC_WALLOC_DTC
void IncAxisDetectionError(
   void){
   if(sm_ucAxisDetectionErrCnt < 250){
      sm_ucAxisDetectionErrCnt++;
   }
}

uint8 CheckForDetailed_ZO_Error(
   void){
   uint8 l_ucRet = 0;
   if((sm_ucAxisDetectionErrCnt == 0) && (sm_ucDirDetectionErrCnt == 0)){
      l_ucRet = 2;
   }
   else if(sm_ucWPConsistentErrCnt > sm_ucAxisDetectionErrCnt){
      if(sm_ucWPConsistentErrCnt > sm_ucDirDetectionErrCnt){
      }
      else{
         l_ucRet = 3;
      }
   }
   else{
      if(sm_ucAxisDetectionErrCnt > sm_ucDirDetectionErrCnt){
         l_ucRet = 4;
      }
      else{
         l_ucRet = 3;
      }
   }
   return (l_ucRet);
}
#endif

void IncrHistProtectTimer(
   void){
   if(ushHistProtecTimeCnt < (tWAPar.ucMinTimeProtectER * 60 * 5)){
      if(ushHistProtecTimeCnt < 0xFFFF){
         ushHistProtecTimeCnt++;
      }
   }
}

boolean bGetHistProtecTimeOver(
   void){
   if(ushHistProtecTimeCnt < (tWAPar.ucMinTimeProtectER * 60 * 5)){
      return FALSE;
   }
   else{
      return TRUE;
   }
}

static boolean bCheckIfNewTelAllowed(
   struct InputWA* ptInputWA,
   unsigned char ucIx){
   boolean bTelAllowed = TRUE;
   if(cMaxLR > ucGetColOfID(
      &ptInputWA->ulID)){
      if(0 == (ptInputWA->ucStatus & (cIDStateM4 | cIDStateDrive))){
         bTelAllowed = FALSE;
      }
      else{
      }
   }
   else{
      if(0 == (ptInputWA->ucStatus & cIDStateM4)){
         bTelAllowed = FALSE;
      }
      else{
      }
   }
   if((TRUE == bTelAllowed) && (ucIx < cSumWE)){
      if(0 != tZOM[ucIx].ucSkipNewTelTimerInSec){
         bTelAllowed = FALSE;
      }
   }
   return bTelAllowed;
}

void WALLOC_UpdateTelegramSkipTimer(
   void){
   unsigned char ucIdx = 0;
   for(ucIdx = 0; ucIdx < cSumWE; ucIdx++){
      if(0 != tZOM[ucIdx].ucSkipNewTelTimerInSec){
         tZOM[ucIdx].ucSkipNewTelTimerInSec--;
      }
   }
}

unsigned char WALLOC_ucGetMinSpeedAutoLearnStart(
   void){
   return tWAPar.ucMinSpeedAutoLearnStart;
}

void ResetHistoryToDefault(
   void){
   uint8 LocalLoopCnt;
   for(LocalLoopCnt = 0; LocalLoopCnt < cMaxLR; LocalLoopCnt++){
      aulHistoryID[LocalLoopCnt] = cInitHistID;
      aucHistoryWP[LocalLoopCnt] = cNoWPos;
   }
   PutWADataEE(
      cHistorySet1,
      (unsigned char*)aulHistoryID);
   PutWADataEE(
      cHistoryWPSet1,
      aucHistoryWP);
}

unsigned char ucGetABSTicksFullRevolFrontAx(
   void){
   if(tABSTicksOneRevol.ucFrontAxisABSTicks > 0){
      return tABSTicksOneRevol.ucFrontAxisABSTicks;
   }
   else{
      return (unsigned char) cDefaultABSCountNr;
   }
}

unsigned char ucGetABSTicksFullRevolRearAx(
   void){
   if(tABSTicksOneRevol.ucRearAxisABSTicks > 0){
      return tABSTicksOneRevol.ucRearAxisABSTicks;
   }
   else{
      return (unsigned char) cDefaultABSCountNr;
   }
}

uint8 DCM_InvIf_ZomStatusGetFromMemory(
   uint8 u8_ZomPossition){
   if(u8_ZomPossition < cSumWE){
      return (tZOM[u8_ZomPossition].ucStatus);
   }
   else{
      return ((unsigned char)0);
   }
}

void DCM_InvIf_ZomWuIDGetFromMemory(
   uint8 u8_ZomPossition,
   uint8* u8_IDValue){
   uint32 LocalZomIDValue;
   LocalZomIDValue = ulGetZOMID(
      u8_ZomPossition);
   u8_IDValue[0] = (uint8)((LocalZomIDValue >> 24) & 0x000000FF);
   u8_IDValue[1] = (uint8)((LocalZomIDValue >> 16) & 0x000000FF);
   u8_IDValue[2] = (uint8)((LocalZomIDValue >> 8) & 0x000000FF);
   u8_IDValue[3] = (uint8)(LocalZomIDValue & 0x000000FF);
}

void DCM_InvIf_HistoryIDReadValue(
   uint8 u8_Possition,
   uint8* u8_IDValue){
   uint32 LocalHistIDValue;
   LocalHistIDValue = ulGetID(
      u8_Possition);
   u8_IDValue[0] = (uint8)((LocalHistIDValue >> 24) & 0x000000FF);
   u8_IDValue[1] = (uint8)((LocalHistIDValue >> 16) & 0x000000FF);
   u8_IDValue[2] = (uint8)((LocalHistIDValue >> 8) & 0x000000FF);
   u8_IDValue[3] = (uint8)(LocalHistIDValue & 0x000000FF);
}

uint8 DCM_InvIf_AutoLocGetTimeoutCntValue(
   void){
   return ucNrOfTOs;
}

void DCM_InvIf_HistoryWPReadValue(
   uint8 u8_Possition,
   uint8* u8_WPValue){
   *u8_WPValue = ucGetWPOfCol(
      u8_Possition);
}

uint8 DCM_InvIf_ZomTelCntGetFromMemory(
   uint8 u8_ZomPossition){
   return ucGetProbeCt(
      u8_ZomPossition);
}

uint8 DCM_InvIf_ZomPosCurrIDGetValue(
   void){
   uint32 LocalIdValue;
   LocalIdValue = ulGetReDataIdPD();
   return ucGetZOMPosOfID(
      &LocalIdValue);
}

void UpdateHistoryFromRAMWIthTheOneFromNVM(
   void){
   GetWADataEE(
      cHistorySet1,
      (unsigned char*)aulHistoryID);
   GetWADataEE(
      cHistoryWPSet1,
      aucHistoryWP);
}

void ResetNrOfTOs(
   void){
   ucNrOfTOs = 0;
}

unsigned char ucCheckPotentialErInZom(
   void){
   unsigned char i, j;
   unsigned char ucRet = 0;
   unsigned char ucNrPotentialErZom = 0;
   unsigned char ucNrHistoryErZom = 0;
   ucNrPotentialErZom = ucNrOfBitSet(
      ushSumPotenAndERWheels());
   for(i = 0; i < cMaxLR; i++){
      for(j = 0; j < cSumWE; j++){
         if(aulHistoryID[i] == ulGetZOMID(
            j)){
            ucNrHistoryErZom++;
         }
      }
   }
   if(ucNrPotentialErZom < cMaxLR){
      if(ucNrHistoryErZom < ucNrPotentialErZom){
         ucRet = 1;
      }
   }
   return ucRet;
}

void ResetAllocErrorCnt(
   void){
   sm_ucWPConsistentErrCnt = 0;
   sm_ucAxisDetectionErrCnt = 0;
   sm_ucDirDetectionErrCnt = 0;
}
