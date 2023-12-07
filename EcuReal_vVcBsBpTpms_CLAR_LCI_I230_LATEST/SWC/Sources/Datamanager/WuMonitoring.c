#include "WuMonitoring.h"
#include "NwMonitoringX.h"
#include "wallocX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "state_zkX.h"
#include "EeHistoryBlockX.h"
#include "EeCommonBlockX.h"
#include "EeDiagBlockX.h"
#include "walloc_managerX.h"
#include "datamanagerX.h"

static uint32 ulWheelUnitErrors = cAllocNoError;
static uint32 ulWheelUnitErrChangedFlags = cAllocNoError;
static uint8  ucAllocFailedCounter = 0;
static uint16 ushAliveTelTimeout[2] = { cALIVE_TEL_TIMEOUT,cALIVE_TEL_TIMEOUT };
static uint8  ucRfIfStateMachine = cNoRfIf;

static tWuMonitoringData tWuMonitoring[cMaxLR] = {
   {cWU_BLOCK_FAIL_TIME,    cWU_TIMER_STOPPED,      0,      0,       0,     0,      1,        0  },
   {cWU_BLOCK_FAIL_TIME,    cWU_TIMER_STOPPED,      0,      0,       0,     0,      1,        0  },
   {cWU_BLOCK_FAIL_TIME,    cWU_TIMER_STOPPED,      0,      0,       0,     0,      1,        0  },
   {cWU_BLOCK_FAIL_TIME,    cWU_TIMER_STOPPED,      0,      0,       0,     0,      1,        0  }
};

static uint8   ucWumActivityStatus = cWUM_ENABLED;
static uint8   ucDefectThreshold = 3;
static uint16  ushTimeSinceLastRecEvent[4];

void InitWUM(Rte_Instance self){
   uint8 i;
   uint32 j;
   uint32 ulLastWumErrorState;
   for(i=0; i<cMaxLR; i++){
    tWuMonitoring[i].ushCountGood       = GETushCntGoodTelEE(self, i);
    tWuMonitoring[i].ushCountMissing    = GETushCntMissTelEE(self, i);
    tWuMonitoring[i].ushTimerBlockFail  = GETushBlockFailTimerEE(self, i);
    GETSensorDefectCounterFromNvmMirrorEE(self, (uint16*) &tWuMonitoring[i].ushCountDefect, i);
    tWuMonitoring[i].ushTimerSingleFail = cWU_TIMER_STOPPED;
    tWuMonitoring[i].ucCountLoBat = GetCntLoBatFromNvmZOMirrorblockEE(self, i);
      ushTimeSinceLastRecEvent[i] = GETucTimeSinceLastRecEventFromNvmMirrorEE(self, i) * 5;
   }
   ucAllocFailedCounter = GetAllocFailCounterFromNvmZOMirrorblockEE(self);
   if(ucAllocFailedCounter > 10){
      ucAllocFailedCounter = 0;
   }
   ushAliveTelTimeout[cDataPackage12Ix] = GETushFbd4AliveTimerEE(self);
   if(ushAliveTelTimeout[cDataPackage12Ix] > cALIVE_TEL_TIMEOUT){
      ushAliveTelTimeout[cDataPackage12Ix] = cALIVE_TEL_TIMEOUT;
   }
   if(GETucFBD4CountEE(self) > 1){
      ushAliveTelTimeout[cDataPackage34Ix] = GETushFbd4AliveTimerEE(self);
      if(ushAliveTelTimeout[cDataPackage34Ix] > cALIVE_TEL_TIMEOUT){
      ushAliveTelTimeout[cDataPackage34Ix] = cALIVE_TEL_TIMEOUT;
      }
   }
   ucRfIfStateMachine = GetRfIfStateMachineFromNvmZOMirrorblockEE(self);
   if(ucRfIfStateMachine == cRfIfIsActive){
    RfInterferenceInLastCycleDetectedWUM(self);
   }
   ulLastWumErrorState = GETulWumErrorsEE(self);
   for(j=0; j<32; j++){
      if((ulLastWumErrorState & (uint32)(1<<j)) == (uint32)(1<<j)){
      if((ulWheelUnitErrors & (uint32)(1<<j)) == 0){
        ulWheelUnitErrChangedFlags |= (uint32)(1<<j);
      }
      }
   }
   ulWheelUnitErrors |= ulLastWumErrorState;
}

void ResetWUM(Rte_Instance self, uint8 ucSlots, uint8 ucWLowBatt, uint8 ucWDtcs){
   uint8 i;
   for(i=0; i<cMaxLR; i++){
      if((ucSlots & (1u << i)) == (1u << i)){
      SetWheelUnitGoodCounterWUM(i, 0);
      SetWheelUnitMissingCounterWUM(i, 0);
      tWuMonitoring[i].ushTimerBlockFail = cWU_BLOCK_FAIL_TIME;
      tWuMonitoring[i].ushTimerSingleFail = cWU_TIMER_STOPPED;
      tWuMonitoring[i].ushCountDefect = 0;
      tWuMonitoring[i].ucLocPossible = 1;
      tWuMonitoring[i].ucForeignSupplier = 0;
      if(ucWLowBatt == cWithLowBat){
        tWuMonitoring[i].ucCountLoBat = 0;
      }
      PUTushCntGoodTelEE(self, tWuMonitoring[i].ushCountGood, i);
      PUTushCntMissTelEE(self, tWuMonitoring[i].ushCountMissing, i);
      PutCntLoBatToNvmZOMirrorblockEE(self, tWuMonitoring[i].ucCountLoBat, i);
      PUTushBlockFailTimerEE(self, tWuMonitoring[i].ushTimerBlockFail, i);
      if(ucWDtcs == cWithWuRelatedDtcs){
          if(ucSlots == cAllSlots){
          ClearMuteWUM(self, i, i);
          ClearDefectWUM(self, i, i);
        }
        else{
          ClearMuteWUM(self, i, ucGetWPOfColWAL(i));
          ClearDefectWUM(self, i, ucGetWPOfColWAL(i));
        }
      }
      ClearTimeSinceLastRecEventWUM(self, i);
      ClearRFInterferenceWUM(self);
      CheckWrongWuMountedWUM(self);
      CheckForeignSupplierWUM(self);
      }
   }
   if((ucSlots > 0) && (ucWLowBatt == cWithLowBat)){
    ClearLowBatWUM(self);
   }
}

void SwitchUnspecificToSpecificErrorsWUM(Rte_Instance self){
   uint8 i;
   if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
    ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute);
    ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
    ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
    ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
    ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
      for(i=0; i<cMaxLR; i++){
      switch(ucGetWPOfColWAL(i)){
        case cWheelPos_FL:
          if(tWuMonitoring[i].ushCountDefect > 2){
            SetWheelUnitErrorWUM(self, cAllocWuDefectFl);
          }
          if(tWuMonitoring[i].ucCountLoBat >= cNO_OF_LO_BAT_TELEGRAMS){
            SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFl);
          }
        break;

        case cWheelPos_FR:
          if(tWuMonitoring[i].ushCountDefect > 2){
            SetWheelUnitErrorWUM(self, cAllocWuDefectFr);
          }
          if(tWuMonitoring[i].ucCountLoBat >= cNO_OF_LO_BAT_TELEGRAMS){
            SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFr);
          }
        break;

        case cWheelPos_RL:
          if(tWuMonitoring[i].ushCountDefect > 2){
            SetWheelUnitErrorWUM(self, cAllocWuDefectRl);
          }
          if(tWuMonitoring[i].ucCountLoBat >= cNO_OF_LO_BAT_TELEGRAMS){
            SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRl);
          }
        break;

        case cWheelPos_RR:
          if(tWuMonitoring[i].ushCountDefect > 2){
            SetWheelUnitErrorWUM(self, cAllocWuDefectRr);
          }
          if(tWuMonitoring[i].ucCountLoBat >= cNO_OF_LO_BAT_TELEGRAMS){
            SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRr);
          }
        break;

        default:
        break;
      }
      }
   }
}

void SwitchSpecificToUnspecificErrorsWUM(Rte_Instance self)
{
   uint8 ucNoOfSetDtcs = 0;

   if(bGetWheelUnitErrorWUM(cAllocWuMuteFl) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuMuteFr) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuMuteRl) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuMuteRr) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
      ucNoOfSetDtcs++;
   }

   ucNoOfSetDtcs = 0;

   if(bGetWheelUnitErrorWUM(cAllocWuDefectFl) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuDefectFl);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuDefectFr) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuDefectFr);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuDefectRl) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuDefectRl);
      ucNoOfSetDtcs++;
   }
   if(bGetWheelUnitErrorWUM(cAllocWuDefectRr) == TRUE){
    ClearWheelUnitErrorWUM(self, cAllocWuDefectRr);
      ucNoOfSetDtcs++;
   }

   if(ucNoOfSetDtcs > 0){
    SetWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
   }
}

void ProcessWuMonitoringWUM(Rte_Instance self, ImpTypeRecCddRdcData rdcData, uint8 ucTelType)
{
   uint32  ulTyrID;
   uint8   ucCol;
   uint8   ucWP;

   if(ucWumActivityStatus == cWUM_DISABLED){
    return;
   }

   if((ucTelType & TELTYPE_FBD4_ALIVE) == TELTYPE_FBD4_ALIVE){
    ClearGatewayAntennaWUM(self, rdcData.DP_NO);
    return;
   }

   ulTyrID = (uint32)rdcData.TYR_ID | ((uint32)rdcData.SUPP_ID << 28);
   ucCol = ucGetColOfID((const uint32*)&ulTyrID);

   if(ucCol >= cMaxLR){
    return;
   }

  ClearTimeSinceLastRecEventWUM(self, ucCol);

   ucWP = ucGetWPOfColWAL(ucCol);

   if((ucTelType & TELTYPE_FOREIGN_SUPPLIER) == TELTYPE_FOREIGN_SUPPLIER){
    tWuMonitoring[ucCol].ucForeignSupplier = 1;
   }
   else{
    tWuMonitoring[ucCol].ucForeignSupplier = 0;
   }

   if((ucTelType & TELTYPE_RID) == TELTYPE_RID){

    ClearMuteWUM(self, ucCol, ucWP);
    ClearRFInterferenceWUM(self);
    CheckForeignSupplierWUM(self);
   }

   else{

      if((ucTelType & TELTYPE_ALLOCATABLE) == TELTYPE_ALLOCATABLE){
      tWuMonitoring[ucCol].ucLocPossible = 1;
      }
      else{
      tWuMonitoring[ucCol].ucLocPossible = 0;
      }

    CheckDefectWUM(self, &rdcData, ucCol, ucWP);

      if(ucWumActivityStatus == cWUM_ENABLED){
      CheckLowBatWUM(self, &rdcData, ucCol, ucWP);
      ClearMuteWUM(self, ucCol, ucWP);
      ClearRFInterferenceWUM(self);
      CheckWrongWuMountedWUM(self);
      CheckForeignSupplierWUM(self);
      }
   }

   if(bGoodCounterReachedMaximumWUM() == FALSE){
      if(((bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE) && (ucWumActivityStatus == cWUM_BM_DIENST_START))
     || (ucWumActivityStatus == cWUM_ENABLED)){
      tWuMonitoring[ucCol].ushCountGood++;
      PUTushCntGoodTelEE(self, tWuMonitoring[ucCol].ushCountGood, ucCol);
      }
   }

   tWuMonitoring[ucCol].ushTimerSingleFail = cWU_SINGLE_FAIL_TIME_1;
}

void WuMonitoringTimerTickWUM(Rte_Instance self)
{
   uint8 i;
   uint8 ucNoOfMissingWUs = 0;

   uint8 ucNoOfDelayedWUs = 0;

   if(ucWumActivityStatus == cWUM_ENABLED){

      if((bGetBitFahrzeugzustandFZZ( cNW_DTC_LOCKED) == FALSE) && (ucGetStatusConditionVehicleFZZ() >= ST_CON_VEH_Pruefen_Analyse_Diagnose)){

      if(ushAliveTelTimeout[cDataPackage12Ix] > 0){
        ushAliveTelTimeout[cDataPackage12Ix]--;

          if(ushAliveTelTimeout[cDataPackage12Ix] < ushAliveTelTimeout[cDataPackage34Ix]){
          PUTushFbd4AliveTimerEE(self, ushAliveTelTimeout[cDataPackage12Ix]);
        }
        else{
          PUTushFbd4AliveTimerEE(self, ushAliveTelTimeout[cDataPackage34Ix]);
        }
          if(ushAliveTelTimeout[cDataPackage12Ix] == 0){
          SetWheelUnitErrorWUM(self, cAllocGatewayOrAntennaError);
        }
      }
      if(GETucFBD4CountEE(self) > 1){

          if(ushAliveTelTimeout[cDataPackage34Ix] > 0){
          ushAliveTelTimeout[cDataPackage34Ix]--;

          if(ushAliveTelTimeout[cDataPackage12Ix] < ushAliveTelTimeout[cDataPackage34Ix]){
            PUTushFbd4AliveTimerEE(self, ushAliveTelTimeout[cDataPackage12Ix]);
          }
          else{
            PUTushFbd4AliveTimerEE(self, ushAliveTelTimeout[cDataPackage34Ix]);
          }
          if(ushAliveTelTimeout[cDataPackage34Ix] == 0){
            SetWheelUnitErrorWUM(self, cAllocGatewayOrAntennaError);
          }
        }
      }
      }

      if(bCheckMuteMonitorActive() == TRUE){

      for(i=0; i<cMaxLR; i++){

          if((tWuMonitoring[i].ushTimerBlockFail != cWU_TIMER_STOPPED) && (tWuMonitoring[i].ushTimerBlockFail > 0)){
          tWuMonitoring[i].ushTimerBlockFail--;
          PUTushBlockFailTimerEE(self, tWuMonitoring[i].ushTimerBlockFail, i);
        }

          if((tWuMonitoring[i].ushTimerSingleFail != cWU_TIMER_STOPPED) && (tWuMonitoring[i].ushTimerSingleFail > 0)){
          tWuMonitoring[i].ushTimerSingleFail--;
        }

        IncTimeSinceLastRecEventWUM(self, i);

          if(tWuMonitoring[i].ushTimerSingleFail == 0){
          if(tWuMonitoring[i].ushCountMissing < 0xFFFFU){
            if((bGoodCounterReachedMaximumWUM() == FALSE)
              && (tWuMonitoring[i].ushTimerBlockFail != 0)){
              tWuMonitoring[i].ushCountMissing++;
              PUTushCntMissTelEE(self, tWuMonitoring[i].ushCountMissing, i);
            }
          }
          tWuMonitoring[i].ushTimerSingleFail = cWU_SINGLE_FAIL_TIME_2;
        }

          if(tWuMonitoring[i].ushTimerBlockFail == 0){
          ucNoOfMissingWUs++;
        }
      }

      if(ucNoOfMissingWUs > 0){

          if((ulGetWheelUnitErrorsWUM(cNoFilter) & (cAllocWuMuteFl | cAllocWuMuteFr |cAllocWuMuteRl | cAllocWuMuteRr | cAllocUnspecifiedWuMute)) > 0){

          SetMuteErrorStatusWUM(self);
        }

        else{

          if(bGetWheelUnitErrorWUM(cAllocRdciRfExternalInterference) == FALSE){

            if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE){

              if(ucNoOfMissingWUs > 1){
                SetWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference);
                ucRfIfStateMachine = cRfIfIsActive;
                PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
              }

              else{
                for(i=0; i<cMaxLR; i++){
                  if(bWuIsDownForCountWUM(i) == TRUE)
                  {
                    ucNoOfDelayedWUs++;
                  }
                }

                if(ucNoOfDelayedWUs > 0){
                  SetWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference);
                  ucRfIfStateMachine = cRfIfIsActive;
                  PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
                }

                else
                {
                  SetMuteErrorStatusWUM(self);
                }
              }
            }

            else
            {
              SetMuteErrorStatusWUM(self);
            }
          }
        }
      }
      }
   }

}

void SetAutoLearnErrorStatusWUM(Rte_Instance self, uint8 ucStatus)
{
   if(ucStatus == cAUTOLEARN_FAILED){
    SetWheelUnitErrorWUM(self, cAllocAutoLearningFailed);

      if(ucRfIfStateMachine == cLastDrvCycEndedWithRfIf){
      ClearWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference);
      ucRfIfStateMachine = cNoRfIf;
      PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
      }
   }
   else if(ucStatus == cAUTOLEARN_SUCCESSFUL){
    ClearWheelUnitErrorWUM(self, cAllocAutoLearningFailed);
    ClearRFInterferenceWUM(self);
    CheckWrongWuMountedWUM(self);
    CheckForeignSupplierWUM(self);
   }
   else{
   }
}

uint8 ucSetAutolocErrorStatusWUM(Rte_Instance self, uint8 ucStatus)
{
   if(ucStatus == cAUTOLOC_FAILED){
      ucAllocFailedCounter++;
      if(ucAllocFailedCounter >= cXCLOC_FALSE){
      ucAllocFailedCounter = cXCLOC_FALSE;
      SetWheelUnitErrorWUM(self, cAllocWuLocalisationFailed);
      }
   }
   else if(ucStatus == cAUTOLOC_SUCCESSFUL){
      ucAllocFailedCounter = 0;
    ClearWheelUnitErrorWUM(self, cAllocWuLocalisationFailed);
   }
   else{
   }

   PutAllocFailCounterToNvmZOMirrorblockEE(self, ucAllocFailedCounter);

   return ucAllocFailedCounter;
}

uint8 ucGetAutoLocFailedCounterWUM(void)
{
   return ucAllocFailedCounter;
}

static boolean bWuIsDownForCountWUM(uint8 ucCol)
{
   boolean bRetVal = FALSE;

   if(ushGetMuteTimerValueWUM(ucCol) > 0){
      if(ushGetTimeSinceLastRxWUM(ucCol) >= cWU_DOUBLE_FAIL_TIME){
      bRetVal = TRUE;
      }
   }
   return bRetVal;
}

static void SetMuteErrorStatusWUM(Rte_Instance self)
{
   uint8 i;

   for(i=0; i<cMaxLR; i++){
      switch(ucGetWPOfColWAL(i)){
      case cWheelPos_FL:
      if(ushGetMuteTimerValueWUM(i) == 0){
        SetWheelUnitErrorWUM(self, cAllocWuMuteFl);
      }
      break;

      case cWheelPos_FR:
      if(ushGetMuteTimerValueWUM(i) == 0){
        SetWheelUnitErrorWUM(self, cAllocWuMuteFr);
      }
      break;

      case cWheelPos_RL:
      if(ushGetMuteTimerValueWUM(i) == 0){
        SetWheelUnitErrorWUM(self, cAllocWuMuteRl);
      }
      break;

      case cWheelPos_RR:
      if(ushGetMuteTimerValueWUM(i) == 0){
        SetWheelUnitErrorWUM(self, cAllocWuMuteRr);
      }
      break;

      case cWheelPos_NA:
      if(ushGetMuteTimerValueWUM(i) == 0){
          if(bGetBitBetriebszustandBZ(cTEILEIGENRAD) == FALSE){
          SetWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute);
          ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
          ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
          ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
          ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
        }
      }
      break;

      default:
      break;

      }

      if(ushGetMuteTimerValueWUM(i) == 0){
      PUTucWheelSensorStatusToNvmMirrorEE(self, cRE_STATUS_MUTE, i);
      }
   }
}

static boolean bCheckMuteMonitorActive(void)
{
   boolean bRetVal;

   if((bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_MsgMissing) == FALSE)
   && ((ulWheelUnitErrors & cAllocGatewayOrAntennaError) != cAllocGatewayOrAntennaError)){

      if(bGetBitFahrzeugzustandFZZ(cRS_VTHRES) == TRUE){
      bRetVal = TRUE;
      }
      else{
      bRetVal = FALSE;
      }
   }
   else{
    bRetVal = FALSE;
   }

   return bRetVal;
}

static void CheckLowBatWUM(Rte_Instance self, const ImpTypeRecCddRdcData* rdcData, uint8 ucCol, uint8 ucWP)
{
   uint8 ucBatLevel;
   uint8 ucBatStatus;
   boolean bRestoreCounter = FALSE;

   ucBatLevel = ucCalcBatteryLevelDM(rdcData);
   if(ucBatLevel <= 10){
      if((rdcData->RDC_DT_2 >= 52) && (rdcData->RDC_DT_2 < 0xF0)){
      ucBatStatus = cBAT_LOW;
      }
      else{
      ucBatStatus = cBAT_UNKNOWN;
      }
   }
   else{
      ucBatStatus = cBAT_OK;
   }

   switch(ucWP){
      case cWheelPos_FL:
      if(bGetWheelUnitErrorWUM(cAllocWuLowBatteryFl) == TRUE){
      bRestoreCounter = TRUE;
      }
      break;

      case cWheelPos_FR:
      if(bGetWheelUnitErrorWUM(cAllocWuLowBatteryFr) == TRUE){
      bRestoreCounter = TRUE;
      }
      break;

      case cWheelPos_RL:
      if(bGetWheelUnitErrorWUM(cAllocWuLowBatteryRl) == TRUE){
      bRestoreCounter = TRUE;
      }
      break;

      case cWheelPos_RR:
      if(bGetWheelUnitErrorWUM(cAllocWuLowBatteryRr) == TRUE){
      bRestoreCounter = TRUE;
      }
      break;

      default:
      break;
   }
   if(bRestoreCounter == TRUE){
      if(tWuMonitoring[ucCol].ucCountLoBat < cNO_OF_LO_BAT_TELEGRAMS){
      tWuMonitoring[ucCol].ucCountLoBat = cNO_OF_LO_BAT_TELEGRAMS;
      }
   }

   if(ucBatStatus == cBAT_LOW){
      if(tWuMonitoring[ucCol].ucCountLoBat < cNO_OF_LO_BAT_TELEGRAMS){
      tWuMonitoring[ucCol].ucCountLoBat++;
      }

      if(tWuMonitoring[ucCol].ucCountLoBat >= cNO_OF_LO_BAT_TELEGRAMS){
      tWuMonitoring[ucCol].ucCountLoBat = cNO_OF_LO_BAT_TELEGRAMS;
      switch(ucWP){
        case cWheelPos_FL:
          SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFl);
        break;
        case cWheelPos_FR:
          SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFr);
        break;
        case cWheelPos_RL:
          SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRl);
        break;
        case cWheelPos_RR:
          SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRr);
        break;
        default:
        break;
      }
      }
   }

   else if(ucBatStatus == cBAT_OK){
      if(tWuMonitoring[ucCol].ucCountLoBat < cNO_OF_LO_BAT_TELEGRAMS){
      tWuMonitoring[ucCol].ucCountLoBat = 0;
      }
      else{
      tWuMonitoring[ucCol].ucCountLoBat++;
      if(tWuMonitoring[ucCol].ucCountLoBat >= (2 * cNO_OF_LO_BAT_TELEGRAMS)){
        switch(ucWP){
          case cWheelPos_FL:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFl);
          break;
          case cWheelPos_FR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFr);
          break;
          case cWheelPos_RL:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRl);
          break;
          case cWheelPos_RR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRr);
          break;
          default:
          break;
        }
        tWuMonitoring[ucCol].ucCountLoBat = 0;
      }
      }
   }
   else {}

   PutCntLoBatToNvmZOMirrorblockEE(self, tWuMonitoring[ucCol].ucCountLoBat, ucCol);
}

static void CheckWrongWuMountedWUM(Rte_Instance self)
{
   uint8 ucNoOfWUsWithoutLocPossibility = 0;
   uint8 i;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ucLocPossible == 0){
      ucNoOfWUsWithoutLocPossibility++;
      }
   }

   if(ucNoOfWUsWithoutLocPossibility == cMaxLR){
    SetWheelUnitErrorWUM(self, cAlloc4WrongWuMounted);
   }
   else if(ucNoOfWUsWithoutLocPossibility > 0){
    SetWheelUnitErrorWUM(self, cAlloc1To3WrongWuMounted);
   }
   else{
    ClearWheelUnitErrorWUM(self, cAlloc1To3WrongWuMounted);
    ClearWheelUnitErrorWUM(self, cAlloc4WrongWuMounted);
   }
}

static void CheckForeignSupplierWUM(Rte_Instance self)
{
   uint8 ucWUsFromForeignSupplier = 0;
   uint8 i;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ucForeignSupplier == 1){
      ucWUsFromForeignSupplier++;
      }
   }

   if(ucWUsFromForeignSupplier > 0){
    SetWheelUnitErrorWUM(self, cAllocRdciOtherWuSensorType);
   }
   else{
    ClearWheelUnitErrorWUM(self, cAllocRdciOtherWuSensorType);
   }
}

void ClearMuteWUM(Rte_Instance self, uint8 ucCol, uint8 ucWP)
{

   tWuMonitoring[ucCol].ushTimerBlockFail = cWU_BLOCK_FAIL_TIME;
   PUTushBlockFailTimerEE(self, tWuMonitoring[ucCol].ushTimerBlockFail, ucCol);

   if((tWuMonitoring[0].ushTimerBlockFail > 0)
   && (tWuMonitoring[1].ushTimerBlockFail > 0)
   && (tWuMonitoring[2].ushTimerBlockFail > 0)
   && (tWuMonitoring[3].ushTimerBlockFail > 0)){
    ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute);
   }

   switch(ucWP){
      case cWheelPos_FL:
      ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
      break;

      case cWheelPos_FR:
      ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
      break;

      case cWheelPos_RL:
      ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
      break;

      case cWheelPos_RR:
      ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
      break;

      case cWheelPos_NA:
      default:
      break;
   }
}

void ClearAllSpecificMutesWUM(Rte_Instance self)
{
  ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
  ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
  ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
  ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
}

static void ClearDefectWUM(Rte_Instance self, uint8 ucCol, uint8 ucWP)
{

   tWuMonitoring[ucCol].ushCountDefect = 0;

   if((tWuMonitoring[0].ushCountDefect == 0)
   && (tWuMonitoring[1].ushCountDefect == 0)
   && (tWuMonitoring[2].ushCountDefect == 0)
   && (tWuMonitoring[3].ushCountDefect == 0)){
    ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
   }

   switch(ucWP){
      case cWheelPos_FL:
      ClearWheelUnitErrorWUM(self, cAllocWuDefectFl);
      break;

      case cWheelPos_FR:
      ClearWheelUnitErrorWUM(self, cAllocWuDefectFr);
      break;

      case cWheelPos_RL:
      ClearWheelUnitErrorWUM(self, cAllocWuDefectRl);
      break;

      case cWheelPos_RR:
      ClearWheelUnitErrorWUM(self, cAllocWuDefectRr);
      break;

      case cWheelPos_NA:
      default:
      break;
   }
}

static void ClearLowBatWUM(Rte_Instance self)
{
    ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFl);
    ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFr);
    ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRl);
    ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRr);
}

static void ClearGatewayAntennaWUM(Rte_Instance self, uint8 DpNo)
{
   uint8 i,DpIx;

   if(0x34 == DpNo){
    DpIx = cDataPackage34Ix;
   }
   else{
    DpIx = cDataPackage12Ix;
   }

   ushAliveTelTimeout[DpIx] = cALIVE_TEL_TIMEOUT;

   if((ulGetWheelUnitErrorsWUM(cFilterSubseqErr) & cAllocGatewayOrAntennaError) == cAllocGatewayOrAntennaError){
      if(ResetDataPackageErrorIndNWM(self, cGA_SHIFT, DpIx) == TRUE){
      ClearWheelUnitErrorWUM(self, cAllocGatewayOrAntennaError);
      }
      for(i=0; i<cMaxLR; i++){
      if(bGetReMuteStatusBySlotWUM(i) == FALSE){
        ClearMuteWUM(self, i, ucGetWPOfColWAL(i));
      }
      }
   }
}

static void ClearRFInterferenceWUM(Rte_Instance self)
{
   boolean bCondition = TRUE;
   uint8 i;

   if(ucWumActivityStatus == cWUM_ENABLED){
      for(i=0; i<cMaxLR; i++){
      if(ushGetTimeSinceLastRxWUM(i) >= cWU_DOUBLE_FAIL_TIME){
        bCondition = FALSE;
      }
      }

      if(bCondition == TRUE)

      {
      ClearWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference);
      ucRfIfStateMachine = cNoRfIf;
      PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
      }
   }
}

static void CheckDefectWUM(Rte_Instance self, const ImpTypeRecCddRdcData* rdcData, uint8 ucCol, uint8 ucWP)
{
   static uint8 ucUnspecDefectQualifier = 0;

   uint8 ucBasicState = (uint8)(rdcData->RDC_DT_4 & (uint8)0xE0) >> (uint8)5;

   if(((rdcData->RDC_DT_1 == 0x00)
   ||  (rdcData->RDC_DT_2 == 0x00))
   || ((rdcData->RDC_DT_3 == 0xff)
   &&  ((ucBasicState == cNormalDriveWMotion) || (ucBasicState == cNormalDriveWoMotion))
   &&  (rdcData->SUPP_ID == cSupplCodeHuf))){
      if(tWuMonitoring[ucCol].ushCountDefect < ucDefectThreshold){
      tWuMonitoring[ucCol].ushCountDefect++;
      PUTSensorDefectCounterToNvmMirrorEE(self, tWuMonitoring[ucCol].ushCountDefect, ucCol);
      }

      if(tWuMonitoring[ucCol].ushCountDefect >= ucDefectThreshold){
      switch(ucWP){
        case cWheelPos_FL:
          SetWheelUnitErrorWUM(self, cAllocWuDefectFl);
          ucUnspecDefectQualifier &= (uint8)~(uint8)(1 << ucCol);
        break;

        case cWheelPos_FR:
          SetWheelUnitErrorWUM(self, cAllocWuDefectFr);
          ucUnspecDefectQualifier &= (uint8)~(uint8)(1 << ucCol);
        break;

        case cWheelPos_RL:
          SetWheelUnitErrorWUM(self, cAllocWuDefectRl);
          ucUnspecDefectQualifier &= (uint8)~(uint8)(1 << ucCol);
        break;

        case cWheelPos_RR:
          SetWheelUnitErrorWUM(self, cAllocWuDefectRr);
          ucUnspecDefectQualifier &= (uint8)~(uint8)(1 << ucCol);
        break;

        case cWheelPos_NA:
          SetWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
          ucUnspecDefectQualifier |= (uint8)(1 << ucCol);
          ClearWheelUnitErrorWUM(self, cAllocWuDefectFl);
          ClearWheelUnitErrorWUM(self, cAllocWuDefectFr);
          ClearWheelUnitErrorWUM(self, cAllocWuDefectRl);
          ClearWheelUnitErrorWUM(self, cAllocWuDefectRr);
        break;

        default:
        break;
      }

      PUTucWheelSensorStatusToNvmMirrorEE(self, cRE_STATUS_DEFECT, ucCol);
      }

      if((ucUnspecDefectQualifier & 0x0f) == 0){
      ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
      }
   }

   else{
    tWuMonitoring[ucCol].ushCountDefect = 0;
    PUTSensorDefectCounterToNvmMirrorEE(self, tWuMonitoring[ucCol].ushCountDefect, ucCol);
    PUTucWheelSensorStatusToNvmMirrorEE(self, cRE_STATUS_IO, ucCol);
      ucUnspecDefectQualifier &= (uint8)~(uint8)(1 << ucCol);

      if((ucUnspecDefectQualifier & 0x0f) == 0){
      ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
      }

      switch(ucWP){
      case cWheelPos_FL:
        ClearWheelUnitErrorWUM(self, cAllocWuDefectFl);
      break;

      case cWheelPos_FR:
        ClearWheelUnitErrorWUM(self, cAllocWuDefectFr);
      break;

      case cWheelPos_RL:
        ClearWheelUnitErrorWUM(self, cAllocWuDefectRl);
      break;

      case cWheelPos_RR:
        ClearWheelUnitErrorWUM(self, cAllocWuDefectRr);
      break;

      case cWheelPos_NA:
      default:
      break;
      }
   }
}

static boolean bGoodCounterReachedMaximumWUM(void)
{
   uint8 i;
   boolean retVal = FALSE;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ushCountGood == 0xFFFFU){
      retVal = TRUE;
      }
   }

   return retVal;
}

static uint32 FilterSubsequentErrorsWUM(uint32 ulErrorBits)
{
   uint32 ulRetVal = ulErrorBits;
   static uint32 ulLastErrorState = 0;
   uint32 ulErrorChanges;

   if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_MsgMissing) == TRUE){
      ulRetVal &= ~ (cAllocGatewayOrAntennaError
                 | cAllocAutoLearningFailed
                 | cAllocWuMuteFl
                 | cAllocWuMuteFr
                 | cAllocWuMuteRl
                 | cAllocWuMuteRr
                 | cAllocUnspecifiedWuMute
                 | cAllocRdciRfExternalInterference);
   }

   if((ulErrorBits & cAllocAutoLearningFailed) == cAllocAutoLearningFailed){
      ulRetVal &= ~ cAllocWuLocalisationFailed;
   }

   if((ulErrorBits & cAllocRdciRfExternalInterference) == cAllocRdciRfExternalInterference){
      ulRetVal &= ~ (cAllocWuMuteFl
                 | cAllocWuMuteFr
                 | cAllocWuMuteRl
                 | cAllocWuMuteRr
                 | cAllocUnspecifiedWuMute);
   }

   if((ulErrorBits & cAlloc4WrongWuMounted) == cAlloc4WrongWuMounted){
      ulRetVal &= ~ (cAlloc1To3WrongWuMounted
                 | cAllocWuLocalisationFailed);
   }

   if((ulErrorBits & cAlloc1To3WrongWuMounted) == cAlloc1To3WrongWuMounted){
      ulRetVal &= ~ (cAllocWuLocalisationFailed);
   }

   if(bGetBitBetriebszustandBZ(cEIGENRAD) == FALSE){
      if(bGetBitBetriebszustandBZ(cTOO_MUCH_RE) == TRUE){
      ulRetVal &= ~ (cAllocUnspecifiedWuMute);
      }
   }

   ulErrorChanges = ulLastErrorState ^ ulRetVal;
   ulWheelUnitErrChangedFlags |= ulErrorChanges;
   ulLastErrorState = ulRetVal;

   return ulRetVal;
}

void SetWheelUnitGoodCounterWUM(uint8 ucCol, uint16 ushVal)
{
   tWuMonitoring[ucCol].ushCountGood = ushVal;
}

void SetWheelUnitMissingCounterWUM(uint8 ucCol, uint16 ushVal)
{
   tWuMonitoring[ucCol].ushCountMissing = ushVal;
}

uint16 ushGetWheelUnitGoodCounterWUM(uint8 ucCol)
{
   return tWuMonitoring[ucCol].ushCountGood;
}

uint16 ushGetWheelUnitMissingCounterWUM(uint8 ucCol)
{
   return tWuMonitoring[ucCol].ushCountMissing;
}

uint8 ucGetSingleFailTimerValueWUM(uint8 ucCol)
{
   return (uint8)(tWuMonitoring[ucCol].ushTimerSingleFail & 0xff);
}

void SetWheelUnitErrorWUM(Rte_Instance self, uint32 ulDtcBit)
{
   if((ulWheelUnitErrors & ulDtcBit) == 0){
      ulWheelUnitErrors |= ulDtcBit;
    PUTulWumErrorsEE(self, ulWheelUnitErrors);
   }
}

void ClearWheelUnitErrorWUM(Rte_Instance self, uint32 ulDtcBit)
{
   if((ulWheelUnitErrors & ulDtcBit) == ulDtcBit){
      ulWheelUnitErrors ^= ulDtcBit;
    PUTulWumErrorsEE(self, ulWheelUnitErrors);
   }
}

void ClearWheelUnitErrChangedFlagWUM(uint32 ulDtcBit)
{
   if((ulWheelUnitErrChangedFlags & ulDtcBit) == ulDtcBit){
      ulWheelUnitErrChangedFlags ^= ulDtcBit;
   }
}

void ClearWheelUnitErrChangedFlagsWUM(void)
{
   ulWheelUnitErrChangedFlags = cAllocNoError;
}

uint32 ulGetWheelUnitErrorsWUM(boolean bUseFilter)
{
   uint32 ulRetVal;

   if(bUseFilter == cFilterSubseqErr){
      ulRetVal = FilterSubsequentErrorsWUM(ulWheelUnitErrors);
   }
   else{
      ulRetVal = ulWheelUnitErrors;
   }

   return ulRetVal;
}

uint32 ulGetWheelUnitErrChangedFlagsWUM(void)
{
   return ulWheelUnitErrChangedFlags;
}

boolean bGetWheelUnitErrorWUM(uint32 ulErrorBit)
{
   if((ulWheelUnitErrors & ulErrorBit) == ulErrorBit){
    return TRUE;
   }
   else{
    return FALSE;
   }
}

uint8 ucGetReMuteStatusWUM(void)
{
   uint8 i;
   uint8 ucRetVal = 0;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ushTimerBlockFail == 0){
      ucRetVal |= (uint8)((uint8)0x01 << i);
      switch(ucGetWPOfColWAL(i)){
        case cWheelPos_FL:
          ucRetVal |= 0x10;
        break;

        case cWheelPos_FR:
          ucRetVal |= 0x20;
        break;

        case cWheelPos_RL:
          ucRetVal |= 0x40;
        break;

        case cWheelPos_RR:
          ucRetVal |= (uint8)0x80;
        break;

        case cWheelPos_NA:
        default:
        break;
      }
      }
   }

   return ucRetVal;
}

boolean bGetReMuteStatusBySlotWUM(uint8 ucSlot)
{
   boolean ucRetVal;

   if(tWuMonitoring[ucSlot].ushTimerBlockFail == 0){
      ucRetVal = TRUE;
   }
   else{
      ucRetVal = FALSE;
   }
   return ucRetVal;
}

uint8 ucGetReDefectStatusWUM(void)
{
   uint8 i;
   uint8 ucRetVal = 0;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ushCountDefect >= ucDefectThreshold){
      ucRetVal |= (uint8)((uint8)0x01 << i);
      switch(ucGetWPOfColWAL(i)){
        case cWheelPos_FL:
          ucRetVal |= (uint8)0x10;
        break;

        case cWheelPos_FR:
          ucRetVal |= (uint8)0x20;
        break;

        case cWheelPos_RL:
          ucRetVal |= (uint8)0x40;
        break;

        case cWheelPos_RR:
          ucRetVal |= (uint8)0x80;
        break;

        case cWheelPos_NA:
        default:
        break;
      }
      }
   }

   return ucRetVal;
}

boolean bGetReDefectStatusBySlotWUM(uint8 ucSlot)
{
   boolean ucRetVal;
   if(tWuMonitoring[ucSlot].ushCountDefect >= ucDefectThreshold){
      ucRetVal = TRUE;
   }
   else{
      ucRetVal = FALSE;
   }
   return ucRetVal;
}

uint16 ushGetReDefectCounterBySlotWUM(uint8 ucSlot)
{
   return tWuMonitoring[ucSlot].ushCountDefect;
}

uint8 ucGetYieldRateWUM(uint8 ucCol)
{
   uint32 ulYield = 0;

   if((tWuMonitoring[ucCol].ushCountGood) > 0){
      ulYield = ((uint32)(tWuMonitoring[ucCol].ushCountGood * 1000) / ((uint32)tWuMonitoring[ucCol].ushCountGood + (uint32)tWuMonitoring[ucCol].ushCountMissing));
      ulYield += 5;
      ulYield /= 10;
   }
   return (uint8)(ulYield & 0xff);
}

boolean bGetLocalisationPossibilityWUM(void)
{
   uint8 ucNoOfWUsWithoutLocPossibility = 0;
   uint8 i;

   for(i=0; i<cMaxLR; i++){
      if(tWuMonitoring[i].ucLocPossible == 0){
      ucNoOfWUsWithoutLocPossibility++;
      }
   }

   if(ucNoOfWUsWithoutLocPossibility > 1){
    return FALSE;
   }
   else{
    return TRUE;
   }
}

void SetWumActivityStatusWUM(Rte_Instance self, uint8 ucStatus, uint8 ucEvaluation)
{
   uint8 i;

   if(ucStatus != ucWumActivityStatus){
      switch(ucStatus){
      case cWUM_BM_DIENST_START:
      SetWheelUnitGoodCounterWUM(0, 0);
      SetWheelUnitGoodCounterWUM(1, 0);
      SetWheelUnitGoodCounterWUM(2, 0);
      SetWheelUnitGoodCounterWUM(3, 0);
      ucDefectThreshold = 1;
      ucWumActivityStatus = ucStatus;
      break;

      case cWUM_BM_DIENST_RUN:
      ucDefectThreshold = 1;
      ucWumActivityStatus = ucStatus;
      break;

      case cWUM_ENABLED:
      ucDefectThreshold = 3;
      ucWumActivityStatus = ucStatus;
      break;

      case cWUM_DISABLED:
      if(ucEvaluation == cDO_EVALUATION){
        for(i=0; i<cMaxLR; i++){
          if(tWuMonitoring[i].ushCountGood > 0){
            tWuMonitoring[i].ushTimerBlockFail = cWU_BLOCK_FAIL_TIME;
          }
        }
      }
      else{
        for(i=0; i<cMaxLR; i++){
          ClearMuteWUM(self, i, i);
          ClearDefectWUM(self, i, i);
        }
      }

      ucWumActivityStatus = ucStatus;
      break;

      default:
      break;
      }
   }
}

void RfInterferenceInLastCycleDetectedWUM(Rte_Instance self)
{
   ucRfIfStateMachine = cLastDrvCycEndedWithRfIf;
   PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
}

boolean bPrio1ErrorIsSetWUM(void)
{
   boolean bRetVal = FALSE;
   uint32 ulPrio1Errors =    cAllocAutoLearningFailed
                          | cAllocWuMuteFl
                          | cAllocWuMuteFr
                          | cAllocWuMuteRl
                          | cAllocWuMuteRr
                          | cAllocUnspecifiedWuMute
                          | cAllocWuDefectFl
                          | cAllocWuDefectFr
                          | cAllocWuDefectRl
                          | cAllocWuDefectRr
                          | cAllocUnspecifiedWfcDefect
                          | cAllocGatewayOrAntennaError;

   if((ulWheelUnitErrors & ulPrio1Errors) == 0){
    bRetVal = FALSE;
   }
   else{

    bRetVal = TRUE;
   }

   return bRetVal;
}

boolean bSystemInactiveByRfInterferenceWUM(void)
{
   boolean bRetVal = FALSE;
   uint32 ulPrio1Errors =    cAllocAutoLearningFailed

                          | cAllocWuDefectFl
                          | cAllocWuDefectFr
                          | cAllocWuDefectRl
                          | cAllocWuDefectRr
                          | cAllocUnspecifiedWfcDefect
                          | cAllocGatewayOrAntennaError;

   if((ulWheelUnitErrors & cAllocRdciRfExternalInterference) == cAllocRdciRfExternalInterference){

      if((ulWheelUnitErrors & ulPrio1Errors) == 0){

      bRetVal = TRUE;
      }
      else{

      bRetVal = FALSE;
      }
   }
   else{
    bRetVal = FALSE;
   }

   return bRetVal;
}

void ClearErrorConditionsWUM(Rte_Instance self, uint8 ucWP, uint8 ucParamToClear)
{
   uint8 ucSlot;

   ucSlot = ucGetColOfWP(ucWP);

   switch(ucParamToClear){
      case cPTC_Mute:
      if(ucSlot < cMaxLR){
      tWuMonitoring[ucSlot].ushTimerBlockFail = cWU_BLOCK_FAIL_TIME;
      PUTushBlockFailTimerEE(self, tWuMonitoring[ucSlot].ushTimerBlockFail, ucSlot);
      }
      else{
      for(ucSlot=0; ucSlot<cMaxLR; ucSlot++){
        tWuMonitoring[ucSlot].ushTimerBlockFail = cWU_BLOCK_FAIL_TIME;
        PUTushBlockFailTimerEE(self, tWuMonitoring[ucSlot].ushTimerBlockFail, ucSlot);
      }
      }
      break;

      case cPTC_Defect:
      if(ucSlot < cMaxLR){
      tWuMonitoring[ucSlot].ushCountDefect = 0;
      PUTSensorDefectCounterToNvmMirrorEE(self, tWuMonitoring[ucSlot].ushCountDefect, ucSlot);
      }
      else{
      for(ucSlot=0; ucSlot<cMaxLR; ucSlot++){
        tWuMonitoring[ucSlot].ushCountDefect = 0;
        PUTSensorDefectCounterToNvmMirrorEE(self, tWuMonitoring[ucSlot].ushCountDefect, ucSlot);
      }
      }
      break;

      case cPTC_LowBat:
      if(ucSlot < cMaxLR){
      tWuMonitoring[ucSlot].ucCountLoBat = 0;
      PutCntLoBatToNvmZOMirrorblockEE(self, tWuMonitoring[ucSlot].ucCountLoBat, ucSlot);
      }
      else{
      for(ucSlot=0; ucSlot<cMaxLR; ucSlot++){
        tWuMonitoring[ucSlot].ucCountLoBat = 0;
        PutCntLoBatToNvmZOMirrorblockEE(self, tWuMonitoring[ucSlot].ucCountLoBat, ucSlot);
      }
      }
      break;

      case cPTC_WrongMounted:
      for(ucSlot=0; ucSlot<cMaxLR; ucSlot++){
      tWuMonitoring[ucSlot].ucLocPossible = 1;
      }
      break;

      case cPTC_WrongSupplier:
      for(ucSlot=0; ucSlot<cMaxLR; ucSlot++){
      tWuMonitoring[ucSlot].ucForeignSupplier = 0;
      }
      break;

      case cPTC_AntennaGateway:
      ushAliveTelTimeout[cDataPackage12Ix] = cALIVE_TEL_TIMEOUT;
      ushAliveTelTimeout[cDataPackage34Ix] = cALIVE_TEL_TIMEOUT;
    PUTushFbd4AliveTimerEE(self, cALIVE_TEL_TIMEOUT);
      break;

      case cPTC_LocalisationFailed:
      ucAllocFailedCounter = 0;
    PutAllocFailCounterToNvmZOMirrorblockEE(self, ucAllocFailedCounter);
      break;

      case cPTC_RfInterference:
      ucRfIfStateMachine = cNoRfIf;
    PutRfIfStateMachineToNvmZOMirrorblockEE(self, ucRfIfStateMachine);
      break;

      default:
      break;
   }

}

uint16 ushGetGatewayAntennaTimerValueWUM(void)
{
   uint16 ushRetVal;

   if(ushAliveTelTimeout[cDataPackage12Ix] < ushAliveTelTimeout[cDataPackage34Ix]){
      ushRetVal = ushAliveTelTimeout[cDataPackage12Ix];
   }
   else{
      ushRetVal = ushAliveTelTimeout[cDataPackage34Ix];
   }
   return ushRetVal;
}

static void IncTimeSinceLastRecEventWUM(Rte_Instance self, uint8 ucCol)
{
   if(ushTimeSinceLastRecEvent[ucCol] < (0x4ffu)){
      ushTimeSinceLastRecEvent[ucCol]++;
    PUTucTimeSinceLastRecEventToNvmMirrorEE(self, (uint8)(ushTimeSinceLastRecEvent[ucCol] / ((uint16)5)), ucCol);
   }
}

static void ClearTimeSinceLastRecEventWUM(Rte_Instance self, uint8 ucCol){
      ushTimeSinceLastRecEvent[ucCol] = 0;
    PUTucTimeSinceLastRecEventToNvmMirrorEE(self, (uint8)(ushTimeSinceLastRecEvent[ucCol]), ucCol);
}

static uint16 ushGetTimeSinceLastRxWUM(uint8 ucCol)
{
   uint16 ushRet;

   if(ushTimeSinceLastRecEvent[ucCol] >= cWU_BLOCK_FAIL_TIME){
      ushRet = cWU_BLOCK_FAIL_TIME;
   }
   else{
      ushRet = ushTimeSinceLastRecEvent[ucCol];
   }

   return ushRet;
}

uint16 ushGetMuteTimerValueWUM(uint8 ucCol)
{
   return tWuMonitoring[ucCol].ushTimerBlockFail;
}

uint8 ucGetLoBatCounterValueWUM(uint8 ucCol)
{
   return tWuMonitoring[ucCol].ucCountLoBat;
}

uint8 ucGetWumActivityStatusWUM(void)
{
   return ucWumActivityStatus;
}

