#include "walloc.h"
#include "Walloc_IF.h"
#include "EeZomBlockX.h"
#include "FPA_X.h"
#include "abs_linX.h"
#include "DebugMsgX.h"

#define macro_ucGetSupplierCode(ulID)           (uint8)(((ulID) >> 28) & 0x0Fu)
#define macro_ucGetWuBasicState(ushStatusField) (uint8)(((ushStatusField) >> 13) & 0x7u)

struct ZOMSlot      tZOM[cSumWE];
struct ZOMInfoSlot  tZOMInfo[cSumWE];
static uint8        aucNewWheelPosOfIdWAL[cMaxLR] = {cRadPosUndef, cRadPosUndef, cRadPosUndef, cRadPosUndef};
static uint8        ucWAState;
static uint8        ucHistoryIdChanges = 0;
static uint32       aulHistoryID[cMaxLR];
static uint8        aucHistoryWP[cMaxLR];
static tWAParameter tWAPar;

static void SetWAStateZOChange(uint8 ucChangedPos){
   ucWAState &= 0x0F;
   ucWAState |= ucChangedPos;
}

static void ClearZomWAL(uint8 ucIx){
   uint8 i,j;
   if(ucIx > cSumWE){
   }
   else{
      if(ucIx == (uint8) cSumWE){
         for(i = 0; i < ucIx; i++){
            for(j = 0; j < (uint8) sizeof(struct ZOMSlot); j++){
               *((uint8*)(&tZOM[i]) + j) = 0;
            }
            for(j = 0; j < (uint8) sizeof(struct ZOMInfoSlot); j++){
               *((uint8*)(&tZOMInfo[i]) + j) = 0;
            }
         }
      }
      else{
         for(j = 0; j < (uint8) sizeof(struct ZOMSlot); j++){
            *((uint8*)(&tZOM[ucIx]) + j) = 0;
         }
         for(j = 0; j < (uint8) sizeof(struct ZOMInfoSlot); j++){
            *((uint8*)(&tZOMInfo[ucIx]) + j) = 0;
         }
      }
   }
}

#ifdef AEC
static uint8 ucSetWP(void)
{
   uint8 i, ucRet = 1;
   for(i = 0; i < cMaxLR; i++){
    tZOM[i].ucStatus &= cNoWPos;
      switch(tZOM[i].ucStatus){
      case 0x50U:
          tZOM[i].ucStatus |= cWP_FR;
      break;
      case 0x60U:
          tZOM[i].ucStatus |= cWP_RR;
      break;
      case 0x90U:
          tZOM[i].ucStatus |= cWP_FL;
      break;
      case 0xA0U:
          tZOM[i].ucStatus |= cWP_RL;
      break;
      default:
      {

        ucRet = 0;
        break;
      }
      }
   }
   return(ucRet);
}

static void ResetWP(void)
{
   uint8 i;

   for(i = 0; i < cMaxLR; i++){
    tZOM[i].ucStatus &= cNoWPos;
   }
}

static void ResetAxis(void)
{
   uint8 i;
   for(i = 0; i < cSumWE; i++){
    tZOM[i].ucStatus &= cNoAxis;
#ifdef CONCEPT4
    tZOM[i].ushLECt = 0;
    tZOM[i].ushSECt = 0;
    tZOM[i].ucFCt = 0;
#endif
   }
   ucWAState &= (uint8) ~(cWAStateER);
}
#endif

static void PutIDToZOM(uint8 ucIx, const uint32 *p2ID){
   if(ucIx < cSumWE){
      tZOM[ucIx].ulID = *p2ID;
   }
}

static uint8 ucGetZOMWP(uint8 ucIx){
   if(ucIx < cMaxLR){
      switch(tZOM[ucIx].ucStatus & (uint8)~cNoWPos){
         case 0x01: return ((uint8) 0);
         case 0x02: return ((uint8) 1);
         case 0x04: return ((uint8) 2);
         case 0x08: return ((uint8) 3);
         default:   return ((uint8) 4);
      }
   }
   else{
      return ((uint8) 4);
   }
}

static uint8 ucGetFreeZOMPos(void)
{
   uint8 i;
   for(i = 0; i < cSumWE; i++){
      if(tZOM[i].ulID == (uint32) 0){
      break;
      }
   }
   return(i);
}

static boolean bGetERState(void)
{
   boolean bRetVal;
   if((ucWAState & cWAStateER) == cWAStateER){
    bRetVal = TRUE;
   }
   else{
    bRetVal = FALSE;
   }

   return bRetVal;
}

static boolean bGetZOState(void)
{
   boolean bRetVal;
   if((ucWAState & cWAStateZO) == cWAStateZO){
    bRetVal = TRUE;
   }
   else{
    bRetVal = FALSE;
   }

   return bRetVal;
}

static void AlignZomWAL(uint16 ushERSlot)
{
   uint8 i, j, k, ucCt = 0;
   struct ZOMSlot tempZom;

   for(i = 0; i < cSumWE; i++){
      if((((uint16)(1<<i)) & ushERSlot) > 0){
      ucCt++;
      }
      else{
      for(j = i+1; j < cSumWE; j++){
          if((((uint16) (1<<j)) & ushERSlot) > 0){
          ucCt++;
          for(k = 0; k < (uint8) sizeof(struct ZOMSlot); k++){

			      *(((uint8*) &tempZom) + k) = *(((uint8*) &tZOM[i]) + k);

            *(((uint8*) &tZOM[i]) + k) = *(((uint8*) &tZOM[j]) + k);

            *(((uint8*) &tZOM[j]) + k) = *(((uint8*) &tempZom) + k);

          }
          ushERSlot |= (1U<<i);
          ushERSlot &= ~(1U<<j);

          #ifdef AEC
          ResetACM();
          #endif
          break;
        }
      }
      }
      if(ucCt == cMaxLR){
      break;
      }
   }
}

static void AlignInfoZomWAL(uint16 ushERSlot)
{
   uint8 i, j, k, ucCt = 0;
   struct ZOMInfoSlot tempInfoZom;

   for(i = 0; i < cSumWE; i++){
      if((((uint16)(1<<i)) & ushERSlot) > 0){
      ucCt++;
      }
      else{
      for(j = i + 1; j < cSumWE; j++){
          if((((uint16)(1<<j)) & ushERSlot) > 0){
          ucCt++;
          for(k = 0; k < (uint8) sizeof(struct ZOMInfoSlot); k++){

			      *(((uint8*) &tempInfoZom) + k) = *(((uint8*) &tZOMInfo[i]) + k);

            *(((uint8*) &tZOMInfo[i]) + k) = *(((uint8*) &tZOMInfo[j]) + k);

			      *(((uint8*) &tZOMInfo[j]) + k) = *(((uint8*) &tempInfoZom) + k);
          }
          ushERSlot |= (1U<<i);
          ushERSlot &= ~(1U<<j);
          break;
        }
      }
      }
      if(ucCt == cMaxLR){
      break;
      }
   }
}

static uint8 ucLowestProbe(uint16 ushException)
{
   uint8 i;
   uint8 ucMinIx = cSumWE;

   i = 0;
  while ((i < cSumWE) && (ucMinIx == cSumWE)){
      if(((0x01U<<i) & ushException) == 0){
      ucMinIx = i;
      }
      else{
      i++;
      }
   }

   for(i = (ucMinIx + 1); i < cSumWE; i++){
      if(((0x01U<<i) & ushException) == 0){
      if(ucGetZomLearnProbeCt(i) < ucGetZomLearnProbeCt(ucMinIx)){
        ucMinIx = i;
      }
      }
   }

   return(ucMinIx);
}

static uint8 ucSumCtID(uint8 ucMinCt, uint16 *ushRet)
{
   uint8 i, ucCt= 0;
  *ushRet = 0;
   for(i = 0; i < cSumWE; i++){
      if(ucGetZomLearnProbeCt(i) >= ucMinCt){
      ucCt++;
      *ushRet |= (uint16) (1 << i);
      }
   }
   return(ucCt);
}

static boolean bSearchEigenraederWAL(uint16* ushErSlots)
{
   boolean bRetVal = FALSE;

  *ushErSlots = ushFindIdSetInZomWAL(aulHistoryID, tWAPar.ucMinCt4HistER, cSumWE);

   if(ucNrOfBitSet16(*ushErSlots) == cMaxLR){
    bRetVal = TRUE;
   }

   else{

      if(ucSumCtID(ucMinCt4ERReset, ushErSlots) > cMaxLR){
      bRetVal = FALSE;
      }

      else if(ucSumCtID(tWAPar.ucMinCt4ER, ushErSlots) == cMaxLR){

      if(tWAPar.LEARNTime == 0){
        bRetVal = TRUE;
      }
      else{
        bRetVal = FALSE;
      }
      }

      else{
      bRetVal = FALSE;
      }
   }

   return bRetVal;
}

static uint8 ucSearchWheelPositionsWAL(uint8 ucID, const tRFTelType * ptInputWA)
{
   uint8 ucRet = 0;

  #ifdef AEC
   if(ptInputWA->Header .ucTType == cTelTypePeak)
    Concept5pb8(ucID, ptInputWA);
   else
  #endif

  #ifdef FPA
      ucRet = ucTriggerFixPointAllocationFPA(ucID, ptInputWA);
  #endif

  #ifdef AEC
   if  (ucDirectionDetection((uint8) 1) == 0x0F){

  #ifdef CONCEPT4
   if(((tZOM[ucID].ucStatus & 0x30) == 0) && (ptInputWA->Header .ucTType == cTelTypeEdgeCnt))
    Concept4Op2(ucID,ushGetTruECt(ptInputWA,ucID));
  #endif

      if(ucAxisDetection() == 1){
      if(ucWPConsistent() == 1){

          if(ucSetWP() == 1){
          ucRet = 1;
        }
        else{

          ResetAxis();
        }
      }
      else{
        ResetAxis();
      }
      }
   }
   else{
      if(ucRet == 0)
      ResetWP();
   }
  #endif
   return((uint8) ucRet);
}

static void Put2Slot(const tRFTelType *ptInputWA, uint8 ucIx)
{

   if(ucIx < cSumWE){
    tZOM[ucIx].ulID = ptInputWA->SchraderFP.ucHeader.ulID;
    tZOM[ucIx].ucP = ptInputWA->SchraderFP.ucP;
    tZOM[ucIx].ucT = ptInputWA->SchraderFP.ucT;

      if(tZOM[ucIx].ucAbsoluteProbeCt < 0xffu){
      if((0xffffu - tZOM[ucIx].ushRssiSum) >= (uint16)ptInputWA->Header.ucAvg){
        tZOM[ucIx].ushRssiSum += (uint16)ptInputWA->Header.ucAvg;
      }
      tZOM[ucIx].ucAbsoluteProbeCt++;

      switch(ptInputWA->Header.ucTType){
        case cTelTypeSELPAL1:
        tZOM[ucIx].ucLearnProbeCt++;
        break;

        case cTelTypeSELPAL:
          if(ucGetColOfID((const uint32*)&ptInputWA->Header.ulID) < cMaxLR){
          tZOM[ucIx].ucLearnProbeCt++;
          if(((ptInputWA->SchraderFP.ushStatusField & (uint16)0xE000u) == (uint16)(cNormalDriveWMotion << 13))
           || ((ptInputWA->SchraderFP.ushStatusField & (uint16)0xE000u) == (uint16)(cNormalDriveWoMotion << 13))){
            tZOM[ucIx].ucStatus |= cWuInDriveMode;
          }
        }
        break;

        case cTelTypeContiFP:
          if(tZOM[ucIx].ucLearnTimer == 0){
          tZOM[ucIx].ucLearnProbeCt++;
          tZOM[ucIx].ucLearnTimer = cTelegramLearnTimerValue;
        }
        break;

        case cTelTypeAK35defLMA:
        tZOM[ucIx].ucLearnProbeCt++;
        break;

        case cTelTypeAK35def:
          if(ucGetColOfID((const uint32*)&ptInputWA->Header.ulID) < cMaxLR){
          tZOM[ucIx].ucLearnProbeCt++;
        }
        break;

        case cTelTypeBeruLong:
        case cTelTypeBeruMed:
        case cTelTypeG4Standard:
          if(tZOM[ucIx].ucLearnTimer == 0){
          tZOM[ucIx].ucLearnProbeCt++;
          tZOM[ucIx].ucLearnTimer = cTelegramLearnTimerValue;
        }
        break;

        default:
        break;
      }
      }
   }
   return;
}

static uint8 ucPutInZOM(const tRFTelType *ptInputWA)
{
   uint8 ucIx;

   ucIx = ucGetZOMPosOfID(&ptInputWA->Header.ulID);

   if(ucIx < cSumWE){
    Put2Slot(ptInputWA, ucIx);
   }
   else{
      ucIx = ucGetFreeZOMPos();
      if(ucIx < cSumWE){
      Put2Slot(ptInputWA, ucIx);
      }
      else{
      if(bGetERState() == FALSE){
        ucIx = ucLowestProbe(ushFindIdSetInZomWAL(aulHistoryID,(uint8) 1,cSumWE));
          if(ucIx < cSumWE){
          ClearZomWAL(ucIx);
#ifdef AEC
          ResetACM();
#endif
          Put2Slot(ptInputWA, ucIx);
        }
        else{
          ucIx = cSumWE;
        }
      }
      else{
        ucIx = cSumWE;
      }
      }
   }
   return(ucIx);
}

static uint8 ucSetHistory(Rte_Instance self, uint8 ucType){
   uint8  i, j;
   uint8  ucRet = 0x0f;
   uint8  ucZomIdChanges = 0;
   uint8  ucPermState = 0;
   uint8  ucPermStateEE;
   uint32 ulTemp;

   GetWADataEE(self, cHistoryIDSet, (uint8*)aulHistoryID, (uint8)sizeof(aulHistoryID));
   GetWADataEE(self, cHistoryWPSet,         aucHistoryWP, (uint8)sizeof(aucHistoryWP));

   for(i = 0; i < cMaxLR; i++){
      for(j = 0; j < cMaxLR; j++){
         if(aulHistoryID[i] == ulGetZOMID(j)){
            ucRet &= (uint8) (~(uint8) (0x01 << j));
            if(cWAStateZO == ucType){
               if(ucGetZOMWP(j) == aucHistoryWP[i]){
               }
               else{
                  aucHistoryWP[i] = ucGetZOMWP(j);
                  ucRet |= (uint8) (0x10 << i);
               }
            }
            break;
         }
      }
      if(cMaxLR == j){
         ucRet |= (uint8) (0x10 << i);
      }
   }
   if(ucNrOfBitSet8(ucRet & 0x0f) > 1){
      for(i = 0; i<cMaxLR; i++){
         aucHistoryWP[i] = cWheelPos_NA;
      }
   }
   if(cWAStateER == ucType){
      ucZomIdChanges = (uint8) (ucRet & 0x0f);
   }
   if(ucRet > 0){
      if(cWAStateZO == ucType){
         ucRet &= (uint8) 0xF0;
         ucPermState = ucCheckPermutationWAL(self, aulHistoryID, aucHistoryWP);
         if(ucPermState != 0){
            GetWADataEE(self, cPermutationState, &ucPermStateEE, sizeof(ucPermStateEE));
            if(ucPermState == ucPermStateEE){
               ucPermState = 0x00;
               PutWADataEE(self, cPermutationState, &ucPermState, sizeof(ucPermState));
            }
            else{
               GetWADataEE(self, cHistoryIDSet, (uint8*)aulHistoryID, (uint8) sizeof(aulHistoryID));
               GetWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
               PutWADataEE(self, cPermutationState, &ucPermState, sizeof(ucPermState));
               ucRet = 0x00;
            }
         }
         else{
            PutWADataEE(self, cPermutationState, &ucPermState, sizeof(ucPermState));
         }
      }
      else{
         ucType = ucRet & 0xF0U;
         for(i = 0; i < cMaxLR; i++){
            if((ucRet & (0x01U << i)) > 0){
               for(j = 0; j < cMaxLR; j++){
                  if((ucRet & ((uint8) (0x10 << j))) > 0){
                     aulHistoryID[j] = ulGetZOMID(i);
                     ucRet &= (uint8) (~(uint8) (0x10 << j));
                     break;
                  }
               }
            }
         }
         ucRet = ucType;
      }
      PutWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
      PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
      for(i=0; i<cMaxLR; i++){
         if((ucZomIdChanges & (uint8)(1 << i)) == (uint8)(1 << i)){
            ulTemp = ulGetZOMID(i);
            j = ucGetColOfID(&ulTemp);
            ucHistoryIdChanges |= (uint8)(1 << j);
         }
      }
   }
   else{
      if(cWAStateZO == ucType){
         SetNewWheelPosOfIdToUnchangedValWAL();
         PutWADataEE(self, cPermutationState, &ucPermState, sizeof(ucPermState));
      }
   }
   return ucRet;
}

static uint8 ucCheckPermutationWAL(Rte_Instance self, const uint32 aulNewHistoryID[], const uint8 aucNewHistoryWP[]){
   const uint8 aucCompareArrayForInvalidPermutation[cMaxInvalidPermutation][cMaxLR] = {
         {cRadPosHR, cRadPosVR, cRadPosHL, cRadPosVL}
      ,  {cRadPosVL, cRadPosHL, cRadPosVR, cRadPosHR}
      ,  {cRadPosHL, cRadPosVR, cRadPosVL, cRadPosHR}
      ,  {cRadPosVL, cRadPosHR, cRadPosHL, cRadPosVR}
   };

   boolean bValidPermutation = FALSE;
   uint8   ucNewHistLoop, ucOldHistLoop, ucLoop;
   uint8   ucRet = 0;
   uint32  aulOldHistoryID[cMaxLR];
   uint8   aucOldHistoryWP[cMaxLR];

   GetWADataEE(self, cHistoryIDSet, (uint8*) aulOldHistoryID, (uint8) sizeof(aulOldHistoryID));
   GetWADataEE(self, cHistoryWPSet, aucOldHistoryWP, (uint8) sizeof(aucOldHistoryWP));

   for(ucOldHistLoop = 0; ucOldHistLoop < cMaxLR; ucOldHistLoop++){
      for(ucNewHistLoop = 0; ucNewHistLoop < cMaxLR; ucNewHistLoop++){
         if(aulNewHistoryID[ucNewHistLoop] == aulOldHistoryID[ucOldHistLoop]){
            aucNewWheelPosOfIdWAL[aucOldHistoryWP[ucOldHistLoop]] = aucNewHistoryWP[ucNewHistLoop];
         }
      }
   }

   for(ucLoop = 0; ((ucLoop < cMaxInvalidPermutation) && (ucRet == 0)); ucLoop++){
      bValidPermutation = FALSE;
      for(ucNewHistLoop = 0; ((ucNewHistLoop < cMaxLR) && (bValidPermutation == FALSE)); ucNewHistLoop++){
         if(aucNewWheelPosOfIdWAL[ucNewHistLoop] != aucCompareArrayForInvalidPermutation[ucLoop][ucNewHistLoop]){
            bValidPermutation = TRUE;
         }
      }
      if(bValidPermutation == FALSE){
         ucRet = (ucLoop + 1);
      }
   }
   return ucRet;
}

static void SetNewWheelPosOfIdToDefaultValWAL(void)
{
   uint8 ucLoop;

   for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
    aucNewWheelPosOfIdWAL[ucLoop] = cRadPosUndef;
   }
}

static void SetNewWheelPosOfIdToUnchangedValWAL(void)
{
   uint8 ucLoop;

   for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
    aucNewWheelPosOfIdWAL[ucLoop] = cRadPosVL + ucLoop;
   }
}

uint8* pucGetNewWheelPosOfIdWAL_debug(Rte_Instance self, uint8* pucPermState)
{
  GetWADataEE(self, cPermutationState, pucPermState, sizeof(uint8));

   return &aucNewWheelPosOfIdWAL[0];
}

static uint8 ucSetHistoryPartialWAL(Rte_Instance self, uint8 ucType, uint8 ucNoOfErs)
{
   uint8 i,j;
   uint8 ucRet = 0x0f;
   uint8 ucZomIdChanges=0;
   uint32 ulTemp;

  GetWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
  GetWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));

   for(i = 0; i < cMaxLR; i++){
      for(j = 0; j < ucNoOfErs; j++){
      if(aulHistoryID[i] == ulGetZOMID(j)){
        ucRet &= (uint8) (~(uint8) (0x01 << j));
          if(ucType == cWAStateZO){
          if(ucGetZOMWP(j) == aucHistoryWP[i]){

          }
          else{
            aucHistoryWP[i] = ucGetZOMWP(j);
            ucRet |= (uint8) (0x10 << i);
          }
        }
        break;
      }
      }
      if(j == ucNoOfErs){
      aucHistoryWP[i] = cWheelPos_NA;
      ucRet |= (uint8) (0x10 << i);
      }
   }

   if(ucType == cWAStateER){
      ucZomIdChanges = (uint8) (ucRet & 0x0f);
   }

   if(ucRet > 0){
      if(ucType == cWAStateZO){
      ucRet &= (uint8) 0xF0;
      }
      else{
      ucType = ucRet & 0xF0U;
      for(i = 0; i < ucNoOfErs; i++){
          if((ucRet & (0x01U << i)) > 0){
          for(j = 0; j < cMaxLR; j++){
            if((ucRet & ((uint8) (0x10 << j))) > 0){
              aulHistoryID[j] = ulGetZOMID(i);
              ucRet &= (uint8) (~(uint8) (0x10 << j));
              break;
            }
          }
        }
      }
      ucRet = ucType;
      }

    PutWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));

      for(i=0; i<cMaxLR; i++){
      if((ucZomIdChanges & (uint8)(1 << i)) == (uint8)(1 << i)){
        ulTemp = ulGetZOMID(i);
        j = ucGetColOfID(&ulTemp);
        ucHistoryIdChanges |= (uint8)(1 << j);
      }
      }
   }
   return (ucRet);
}

static uint8 ucIdsAreHistoricWAL(uint16 ushSlots)
{
   uint8 i;
   uint8 ucNoOfHistoricWheels = 0;
   uint32 ulId;

   for(i=0; i<cSumWE; i++){
      if((ushSlots & (uint16)(1u<<i)) == (uint16)(1u<<i)){
      ulId = ulGetZOMID(i);
      if(ucGetColOfID(&ulId) < cMaxLR){
        ucNoOfHistoricWheels++;
      }
      }
   }
   return ucNoOfHistoricWheels;
}

static void RestoreHistory(void)
{
   uint8 i,j,ucCt = 0;

   if(aulHistoryID[0] > (uint32) 0){
      if(bGetERState() == TRUE){
      for(i = 0; i < cMaxLR; i++){
        for(j = 0; j < cMaxLR; j++){
          if(aulHistoryID[j] == ulGetZOMID(i)){
            #ifdef AEC
            if(ucHWPfitSpin(aucHistoryWP[j], i) == 1)
            #endif
            {
              SetZOMWP(i, aucHistoryWP[j]);
              ucCt++;
            }
          }
        }
      }
      }
      else{
      for(i = 0; i < cMaxLR; i++){
        PutIDToZOM(i,&aulHistoryID[i]);
          if(aucHistoryWP[i] < cMaxLR){
          SetZOMWP(i, aucHistoryWP[i]);
          ucCt++;
        }
      }
      ucWAState |= cWAStateER;
      }

      if(ucCt < cMaxLR){
      for(i = 0; i < cMaxLR; i++){
        SetZOMWP(i, cWheelPos_NA);
      }
      }
      else{
      ucWAState |= cWAStateZO;
      }
   }
}

#ifdef AEC
static uint8 ucHWPfitSpin(uint8 ucWP, uint8 ucZOMIx)
{
   if((tZOM[ucZOMIx].ucStatus & cLeftSpin) == cLeftSpin){
      if((ucWP == cFL) || (ucWP == cRL)){
      return ((uint8) 1);
      }
      else{
      return ((uint8) 0);
      }
   }
   else if((tZOM[ucZOMIx].ucStatus & cRightSpin) == cRightSpin){
      if((ucWP == cFR) || (ucWP == cRR)){
      return ((uint8) 1);
      }
      else{
      return ((uint8) 0);
      }
   }
   else{
      if(ucWP < 4){
      return ((uint8) 1);
      }
      else{
      return ((uint8) 0);
      }
   }
}
#endif

uint8 ucGetZomLearnProbeCt(uint8 ucIdx){
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucLearnProbeCt);
   }
   else{
    return 0;
   }
}

uint8 ucGetZomPressure(uint8 ucIdx){
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucP);
   }
   else{
    return 0;
   }
}

uint8 ucGetZomTemperature(uint8 ucIdx){
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucT);
   }
   else{
    return 0;
   }
}

uint8 ucGetZOMPosOfID(const uint32* pt2ID){
   uint8 i;
   for(i = 0; i < cSumWE; i++){
      if(*pt2ID == tZOM[i].ulID){
      break;
      }
   }
   return(i);
}

uint8 ucGetZomPalFrameCounter(uint8 ucIx){
   if(ucIx < cSumWE){
    return (tZOM[ucIx].ucFrameCounter);
   }
   else{
    return ( (uint8) 0);
   }
}

void SetZOMWP(uint8 ucIx, uint8 ucWP){
   if(ucIx < cMaxLR){
    tZOM[ucIx].ucStatus &= cNoWPos;
      if(ucWP < cMaxLR){
      tZOM[ucIx].ucStatus |= (uint8) (0x01 << ucWP);
      }
   }
}

uint32 ulGetZOMID(uint8 ucIx){
   if(ucIx < cSumWE){
    return (tZOM[ucIx].ulID);
   }
   else{
    return ( (uint32) 0);
   }
}

uint32 ulGetIDOfColWAL(uint8 ucIx){
   if(ucIx < cMaxLR){
    return (aulHistoryID[ucIx]);
   }
   else{
    return ( (uint8) 0);
   }
}

uint8 ucGetWPOfColWAL(uint8 ucIx){
   if(ucIx < cMaxLR){
    return (aucHistoryWP[ucIx]);
   }
   else{
    return ((uint8) cMaxLR);
   }
}

uint8 ucGetSuppIdOfColWAL(uint8 ucIx){
   if(ucIx < cMaxLR){
    return ((uint8)(aulHistoryID[ucIx] >> 28) & 0x0fu);
   }
   else{
    return ((uint8) 0xff);
   }
}

uint8 ucGetColOfID(const uint32* pt2ID){
   uint8 i;
   for(i = 0; i < cMaxLR; i++){
      if(*pt2ID == aulHistoryID[i]){
      break;
      }
   }
   return(i);
}

uint8 ucGetColOfWP(uint8 ucWP){
   uint8 ucRetVal = 0;
   uint8 i = 0;
   if(ucWP > cWheelPos_RR){
      ucRetVal = cMaxLR;
   }
   else{
    while ((aucHistoryWP[i] != ucWP) && (i < cMaxLR)){
      i++;
      }
      ucRetVal = i;
   }
   return ucRetVal;
}

static uint8 ucGetNextFreeCol(void)
{
   uint8 i = 0;

  while ((aucHistoryWP[i] < cMaxLR) && (i < cMaxLR)){
    i++;
   }
   return i;
}

uint16 ushFindIdSetInZomWAL(const uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search){
   uint8 i,j;
   uint16 ushRet = 0;
   uint8 ucBreak = 0;
   for(i = 0; i < cMaxLR; i++){
      if(ptHistSet[i] == (uint32) 0){
      ushRet = 0;
      break;
      }
      else{
      ucBreak = 0;
      for(j = 0; j < ucSlots2Search; j++){
          if((ptHistSet[i] == ulGetZOMID(j))){
          if(ucGetZomLearnProbeCt(j) >= ucMinProbeCt){
            ushRet |= (1U<<j);
            ucBreak = 1;
          }
        }
        else{
          if(ulGetZOMID(j) == (uint32) 0){
            ucBreak = 1;
          }
        }
          if(ucBreak == 1){
          break;
        }
      }
      }
   }
   return (ushRet);
}

uint8 ucGetWATOTimeWAL(void){
	return(tWAPar.WATOTime);
}

void PutWATOTimeWAL(uint8 ucTime){
   tWAPar.WATOTime = ucTime;
}

uint8 ucGetLEARNTimeWAL(void){
	return(tWAPar.LEARNTime);
}

void PutLEARNTimeWAL(uint8 ucTime){
   tWAPar.LEARNTime = ucTime;
}

uint32* GetPointerToHistoryIdSetWAL(void){
   return (aulHistoryID);
}

void ClearHistoryWPs(Rte_Instance self){
   uint8 i;
   for(i=0; i<cMaxLR; i++){
    aucHistoryWP[i] = cWheelPos_NA;
      ucWAState |= (uint8)(0x10 << i);
   }
   PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
}

uint8 ucSetHistoryID(Rte_Instance self, uint32 ulID, uint8 ucWP){
   uint8 i;
   uint8 ucSlot;
   uint8 ucOldWP;
   uint8 ucSlot2;
   uint8 ucRetVal = 0;
   if(ucWP > cWheelPos_RR){
      ucRetVal = 0xff;
   }
   else{
      if((ulID == 0) && (ucWP == 0)){
      for(i=0; i<cMaxLR; i++){
        aulHistoryID[i] = 0;
        aucHistoryWP[i] = cWheelPos_NA;
      }
      PutWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
      PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
      ucWAState = 0xf0;
      ucRetVal = 0xff;
      }
      else{
      ucSlot = ucGetColOfID(&ulID);
      if(ucSlot < cMaxLR){
        ucOldWP = aucHistoryWP[ucSlot];
        ucSlot2 = ucGetColOfWP(ucWP);
        aucHistoryWP[ucSlot] = ucWP;
        i=0;
          if(ucSlot2 < cMaxLR){
          aucHistoryWP[ucSlot2] = ucOldWP;
          i = (uint8)(0x10 << ucSlot2);
        }
        i |= (uint8)(0x10 << ucSlot);
        ucWAState |= i;
        ucWAState &= (uint8)~cWAStateZO;
        ucRetVal = i;
      }
      else{
        ucSlot = ucGetColOfWP(ucWP);
          if(ucSlot < cMaxLR){
          aulHistoryID[ucSlot] = ulID;
          ucWAState |= (uint8)(0x10 << ucSlot);
          ucWAState &= (uint8)~cWAStateZO;
          ucRetVal = (uint8)(0x01 << ucSlot);
        }
        else{
          ucSlot = ucGetNextFreeCol();
          aulHistoryID[ucSlot] = ulID;
          aucHistoryWP[ucSlot] = ucWP;
          ucWAState |= (uint8)(0x10 << ucSlot);
          ucWAState &= (uint8)~cWAStateZO;
          i =  (uint8)(0x10 << ucSlot);
          i |= (uint8)(0x01 << ucSlot);
          ucRetVal = i;
        }
        ucHistoryIdChanges = ucRetVal;
      }
      PutWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
      PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
      }
   }
   return ucRetVal;
}

uint8 ucGetHistoryState(void){
   uint8 i;
   uint8 j;
   uint8 ucRet = 0;
  j=0;
   for(i=0; i<cMaxLR; i++){
      if(aulHistoryID[i] > 0){
      j++;
      }
   }
   if(j == 4){
      ucRet |= cHiStateER;
      for(i=0; i<cMaxLR; i++){
      if(aucHistoryWP[i] < cMaxLR){
        j++;
      }
      }
      if(j == 8){
      ucRet |= cHiStateZG;
      }
   }
   return ucRet;
}

uint8 ucGetWAState(void){
   return (ucWAState);
}

uint8 ucGetHistoryWpChangedBits(void){
   return ((ucWAState >> 4) & 0x0fU);
}

uint8 ucGetHistoryIdChangedBitsWAL(void){
   uint8 ucRetVal = ucHistoryIdChanges;
   ucHistoryIdChanges = 0;
   return ucRetVal;
}

void SetbackLocateProbeCountersWAL(void){
   uint8 i;
   for(i=0; i<cSumWE; i++){
      if(tZOM[i].ucLocateProbeCt > 13){
      tZOM[i].ucLocateProbeCt = 13;
      }
   }
}

void SetbackLearnProbeCountersWAL(void){
   uint8 i;
   for(i=0; i<cSumWE; i++){
      if(ucGetColOfID(&tZOM[i].ulID) < cMaxLR){
      if(tZOM[i].ucLearnProbeCt > 2){
        tZOM[i].ucLearnProbeCt = 2;
      }
      }
      else{
      if(tZOM[i].ucLearnProbeCt > 6){
        tZOM[i].ucLearnProbeCt = 6;
      }
      }
   }
}

void ClearReDriveModeStateWAL(void){
   uint8 i;
   for(i=0; i<cSumWE; i++){
    tZOM[i].ucStatus &= (uint8)(~cWuInDriveMode);
   }
   ucWAState &= (uint8)(~cWAStateBreak);
}

void TickSingleRELearnTimerWAL(void){
   uint8 i;
   for(i=0; i<cSumWE; i++){
      if(tZOM[i].ucLearnTimer > 0){
      tZOM[i].ucLearnTimer--;
      }
   }
}

void TickAbsoluteLearnTimerWAL(void){
   if(tWAPar.LEARNTime > 0){
    tWAPar.LEARNTime--;
   }
}

uint8 ucLearnID(Rte_Instance self, const tRFTelType* ptInputWA){
   uint16 ushHelp;
   uint8  ucZomPos;
   boolean bHelp = FALSE;
   if(bGetZOState() == TRUE){
      if((tWAPar.ucWACtrl & cWACtrlCyclic) > 0){
		  (void)InitWAL(self, cRestartLearnLocate);
	  }

#ifdef Test_LOG_ENABLE
      ucZomPos = ucPutInZOM(ptInputWA);
	  if(ucZomPos < cSumWE){
	    (void)ucSearchWheelPositionsWAL(ucZomPos, ptInputWA);
	  }
#endif
   }
   else{
      if((tWAPar.ucWACtrl & cWACtrlFixc) > 0){
      RestoreHistory();
      }
      else{
      if((tWAPar.ucWACtrl & cWACtrlBreakc) == 0){
        ucZomPos = ucPutInZOM(ptInputWA);
          if(ucZomPos < cSumWE){
          if(bGetERState() == FALSE){
            if(bSearchEigenraederWAL(&ushHelp) == TRUE){
              ucWAState |= cWAStateER;
              AlignZomWAL(ushHelp);
              AlignInfoZomWAL(ushHelp);
				      ucZomPos = ucGetZOMPosOfID(&ptInputWA->Header.ulID);
              SetWAStateZOChange(ucSetHistory(self, (uint8)cWAStateER));
            }
          }
          if(bGetERState() == TRUE){
            bHelp = bFinishIfWheelsAreInDriveMode();
          }
          if(bHelp == FALSE){
            if(ucSearchWheelPositionsWAL(ucZomPos, ptInputWA) == 1){
              if(bGetERState() == TRUE){
                CancelWATO();
                SetWAStateZOChange(ucSetHistory(self, (uint8)cWAStateZO));
                ucWAState |= cWAStateZO;
              }
            }
          }
        }
        else{
        }
      }
      }
   }
   PutWADataEE(self, cAllocState, (uint8*)&ucWAState, sizeof(ucWAState));
   PutWADataEE(self, cIDChangeBits, (uint8*)&ucHistoryIdChanges, sizeof(ucHistoryIdChanges));
   PutWADataEE(self, cZOMContent, (uint8*)&tZOM, (uint16)sizeof(tZOM));
   return(ucWAState);
}

static boolean bFinishIfWheelsAreInDriveMode(void){
   uint8 i;
   uint32 ulHistId;
   uint8 ucPos;
   uint8 ucNoOfWheelsInDriveMode = 0;
   boolean bRetVal = FALSE;
   if((ucGetHistoryState() & cHiStateZG) == cHiStateZG){
      for(i=0; i<cMaxLR; i++){
      ulHistId = ulGetIDOfColWAL(i);
      ucPos = ucGetZOMPosOfID(&ulHistId);
      if(ucPos < cMaxLR){
          if((tZOM[ucPos].ucStatus & cWuInDriveMode) == cWuInDriveMode){
          ucNoOfWheelsInDriveMode++;
        }
      }
      }
      if(ucNoOfWheelsInDriveMode == cMaxLR){
      RestoreHistory();
      ucWAState &= (uint8)~cWAStateZO;
      ucWAState |= cWAStateBreak;
      bRetVal = TRUE;
      }
   }
   return bRetVal;
}

uint8 ucWATO(Rte_Instance self, uint8* ucOpenPositions){
   uint8 ucRet = 0;
   uint16 ushSlots = 0;
   uint8 ucNrOfErs;
   if(bGetERState() == FALSE){
    (void) bSearchEigenraederWAL(&ushSlots);
      ucNrOfErs = ucNrOfBitSet16(ushSlots);
      if(ucNrOfErs == 0){
      *ucOpenPositions = cMaxLR;
      ucRet = 0x11;
      }
      else if(ucNrOfErs < cMaxLR){
      if(ucIdsAreHistoricWAL(ushSlots) < ucNrOfErs){
        PartialAllocationWAL(self, ushSlots, ucNrOfErs, ucOpenPositions);
      }
      ucRet = 0x09;
      }
      else if(ucNrOfErs > cMaxLR){
      DeleteForeignWheelsWAL();
      if(bSearchEigenraederWAL(&ushSlots) == TRUE){
        ucWAState |= cWAStateER;
        AlignZomWAL(ushSlots);
        AlignInfoZomWAL(ushSlots);
        SetWAStateZOChange(ucSetHistory(self, (uint8)cWAStateER));
        PutWADataEE(self, cAllocState,   (uint8*)&ucWAState,                  sizeof(ucWAState));
        PutWADataEE(self, cIDChangeBits, (uint8*)&ucHistoryIdChanges,         sizeof(ucHistoryIdChanges));
        PutWADataEE(self, cZOMContent,   (uint8*)&tZOM,               (uint16)sizeof(tZOM));
          if(1 == ucForceAutolocationWAL(self)){
          ucRet = 0x00;
        }
        else{
          ucRet = 0x02;
        }
      }
      else{
        ucNrOfErs = ucNrOfBitSet16(ushSlots);
          if(ucNrOfErs == 0){
          *ucOpenPositions = cMaxLR;
          ucRet = 0x11;
        }
        else if(ucNrOfErs > cMaxLR){
          return 0x05;
        }
        else{
          if(ucIdsAreHistoricWAL(ushSlots) < ucNrOfErs){
            PartialAllocationWAL(self, ushSlots, ucNrOfErs, ucOpenPositions);
          }
          ucRet = 0x09;
        }
      }
      }
      else {  }
   }
   else{
      if(ucForceAutolocationWAL(self) == 1){
      ucRet = 0x00;
      }
      else{
      ucRet = 0x02;
      }
   }
  CancelWATO();
   return (ucRet);
}

static uint8 ucForceAutolocationWAL(Rte_Instance self){
   uint8 ucRetVal;
   ucRetVal = ucLocateWheelPositionsFPA(TRUE);
   if(1 == ucRetVal){
      SetWAStateZOChange(ucSetHistory(self, (uint8)cWAStateZO));
      ucWAState |= cWAStateZO;
      PutWADataEE(self, cAllocState,   (uint8*)&ucWAState,                  sizeof(ucWAState));
      PutWADataEE(self, cIDChangeBits, (uint8*)&ucHistoryIdChanges,         sizeof(ucHistoryIdChanges));
      PutWADataEE(self, cZOMContent,   (uint8*)&tZOM,               (uint16)sizeof(tZOM));
   }
   return ucRetVal;
}

static void PartialAllocationWAL(Rte_Instance self, uint16 ushSlots, uint8 ucNrOfErs, uint8* ucOpenPositions){
  AlignZomWAL(ushSlots);
  AlignInfoZomWAL(ushSlots);
   (void) ucSetHistoryPartialWAL(self, cWAStateER, ucNrOfErs);
   if((ucGetHistoryState() & cHiStateZG) != cHiStateZG){
    *ucOpenPositions = ucLocateWheelPositionsPartialFPA(ucNrOfBitSet16(ushSlots));
      if(*ucOpenPositions > 0){
      (void) ucSetHistoryPartialWAL(self, cWAStateZO, ucNrOfErs);
      }
   }
}

static void DeleteForeignWheelsWAL(void){
   uint8 i;
   (void)ucLocateWheelPositionsFPA(FALSE);
  CalcInfoZomMinDistFPA();
   for(i=0; i<cSumWE; i++){
      if(tZOM[i].ucAbsoluteProbeCt > 0){
      if(tZOMInfo[i].ucDeltaMin < cDELTAMIN_FOR_LEARN){
        ClearZomWAL(i);
      }
      }
   }
}

uint8 InitWAL(Rte_Instance self, boolean bClearZom){
   uint8 i;
   if(bClearZom == cRestartLearnLocate){
      ucWAState &= (uint8) ~(cWAStateZO);
      ucWAState &= (uint8) ~(cWAStateER);
      ucWAState &= (uint8) ~(cWAStateActive);
      ucWAState &= (uint8) ~(cWAStateBreak);
    SetWAStateZOChange(0);
      ucHistoryIdChanges = 0;
    CancelWATO();
    ClearZomWAL(cSumWE);
    PutWADataEE(self, cZOMContent, (const uint8*)tZOM, (uint16)sizeof(tZOM));
    PutWADataEE(self, cAllocState, (const uint8*)&ucWAState, (uint8)sizeof(ucWAState));
    PutWADataEE(self, cIDChangeBits, (const uint8*)&ucHistoryIdChanges, (uint8)sizeof(ucHistoryIdChanges));
   }
   else{
    GetWADataEE(self, cZOMContent, (uint8*) &tZOM, (uint16) sizeof(tZOM));
    GetWADataEE(self, cAllocState, &ucWAState, sizeof(ucWAState));
    GetWADataEE(self, cIDChangeBits, &ucHistoryIdChanges, sizeof(ucHistoryIdChanges));
    InitABS();
   }
  GetWADataEE(self, cWAParameter, (uint8*) &tWAPar , (uint8) sizeof(tWAParameter));
   if(tWAPar.ucWAParInitialized != cWAParInitialized){
    tWAPar.ucWACtrl = ucDefWACtrl;
    tWAPar.ucWAParInitialized = cWAParInitialized;
    tWAPar.ucMinCt4ER = ucDefMinCt4ER;
    tWAPar.ucMinCt4HistER = ucDefMinCt4HistER;
    tWAPar.ucMinERMeanRssiLevel = ucDefMinERMeanRssiLevel;
    tWAPar.WATOTime = ucDefWATOTime;
    tWAPar.LEARNTime = ucDefLEARNTime;

      for(i = 0; i < cMaxLR; i++){
      aulHistoryID[i] = 0;
      aucHistoryWP[i] = cWheelPos_NA;
      }
    PutWADataEE(self, cWAParameter, (uint8*) &tWAPar , (uint8) sizeof(tWAParameter));
    PutWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
    PutWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
   }
   else{
    GetWADataEE(self, cHistoryIDSet, (uint8*) aulHistoryID, (uint8) sizeof(aulHistoryID));
    GetWADataEE(self, cHistoryWPSet, aucHistoryWP, (uint8) sizeof(aucHistoryWP));
      if((tWAPar.ucWACtrl & cWACtrlFixc) > 0){
      RestoreHistory();
      }
    tWAPar.ucWACtrl &= (uint8)~cWACtrlBreakc;
   }
   SetNewWheelPosOfIdToDefaultValWAL();
   return (ucGetHistoryState());
}

uint8 ucGetZomStatus(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucStatus);
   }
   else{
    return ((uint8) cNoWPos);
   }
}

uint8 ucGetZomToothTelCtCorrLearnBit(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucToothTelCtCorrLearnBit);
   }
   else{
    return ((uint8) 0);
   }
}

uint8 ucGetZomToothTelCtCorrNoLearnBit(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucToothTelCtCorrNoLearnBit);
   }
   else{
    return ((uint8) 0);
   }
}

uint8 ucGetZomToothTelCtrNoCorr(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucToothTelCtNoCorr);
   }
   else{
    return ((uint8) 0);
   }
}

uint8 ucGetZomToothTelCtNoLearnMode(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucToothTelCtNoLearnMode);
   }
   else{
    return ((uint8) 0);
   }
}

uint8 ucGetZomLocateProbeCt(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucLocateProbeCt);
   }
   else{
    return ((uint8)0);
   }
}

uint8 ucGetZomResetAbsRefFlag(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucResetABSRefFlag);
   }
   else{
    return ((uint8) 0);
   }
}

uint8 ucGetZomDeltaMin(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucDeltaMin);
   }
   else{
    return ((uint8) 0);
   }
}

uint16 ushGetZomDeltaSum(uint8 ucIdx, uint8 ucWP, uint8 ucSpec)
{
   if((ucIdx < cSumWE) && (ucWP < cMaxLR)){
      if(ucSpec == 0){
      return (tZOM[ucIdx].ushPosCompVal[ucWP]);
      }
      else{
      return (tZOM[ucIdx].ushPosCompVal2[ucWP]);
      }
   }
   else{
    return 0;
   }
}

uint8 ucGetZomAbsComp(uint8 ucIdx, uint8 ucPos)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucABSComp[ucPos]);
   }
   else{
    return (0);
   }
}

uint8 ucGetZomAbsMetrics(uint8 ucIdx, uint8 ucPos)
{
   if(ucIdx < cSumWE){
    return (tZOMInfo[ucIdx].ucRelCmpVal[ucPos]);
   }
   else{
    return (0);
   }
}

uint8 ucGetZomAbsRefStartValue(uint8 ucIdx, uint8 ucPos)
{
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucABSRef[ucPos]);
   }
   else{
    return 0;
   }
}

uint16 ushGetZomAbsRefValue(uint8 ucSpectrum, uint8 ucIdx, uint8 ucPos)
{
   if((ucIdx < cSumWE) && (ucPos < cMaxLR)){
      if(ucSpectrum == 0){
      return (tZOM[ucIdx].ushMVdN[ucPos]);
      }
      else{
      return (tZOM[ucIdx].ushMVdN2[ucPos]);
      }
   }
   else{
    return 0xffffU;
   }
}

uint8 ucGetZomAbsoluteProbeCt(uint8 ucIdx)
{
   if(ucIdx < cSumWE){
    return (tZOM[ucIdx].ucAbsoluteProbeCt);
   }
   else{
    return 0;
   }
}

uint8 ucGetZomDistanceValue(uint8 ucSpectrum, uint8 ucIdx, uint8 ucPos)
{
   if((ucIdx < cSumWE) && (ucPos < cMaxLR)){
      if(ucSpectrum == 0){
      return (tZOMInfo[ucIdx].ucDistanceStandard[ucPos]);
      }
      else{
      return (tZOMInfo[ucIdx].ucDistanceShadow[ucPos]);
      }
   }
   else{
    return 0xffU;
   }
}

uint8 ucNrOfBitSet16(uint16 ushTarget)
{
   uint8 i;
   uint8 ucHits= 0;

   for(i=0; i<16; i++){
      if((ushTarget & (1U<<i)) > 0){
      ucHits++;
      }
   }
   return (ucHits);
}

uint8 ucNrOfBitSet8(uint8 ucTarget)
{
   uint8 i;
   uint8 ucHits = 0;

   for(i=0; i<8; i++){
      if((ucTarget & (1U<<i)) > 0){
      ucHits++;
      }
   }
   return (ucHits);
}

