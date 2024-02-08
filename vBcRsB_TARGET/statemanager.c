#define STATEMANAGER_C
/******************************************************************************/
/* File   : statemanager.c                                                    */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Tpms_Rte_Data_Type.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_DTC_If.hpp"
#include "uswarnX.hpp"
#include "Uswarn_IfX.hpp"
#include "procdatX.hpp"
#include "wallocX.hpp"
#include "statisticsX.hpp"
#include "rediagX.hpp"
#include "IDOM_X.hpp"
#include "statemanager.hpp"
#include "statemanagerX.hpp"
#include "cd_decoder_X.hpp"
#include "multiframeX.hpp"
#include "State_FzzX.hpp"
#include "State_BzX.hpp"
#include "State_ZkX.hpp"
#include "global.hpp"
#include "WatcfX.hpp"
#include "WnTypePar.hpp"
#include "abs_linX.hpp"
#include "CfgSwcApplTpms.hpp"
#include "BusMsgX.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "SwcApplTpms_LearnEOL.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define MAX_CNT_VALUE_TO_RESET_ERR                                           35U
#define cCallsFor10Minutes                                                 3000U
#define c10MinutesBCMTime                                                600000U
#define cCallsFor8Minutes                                                  2400U
#define c8MinutesBCMTime                                                 480000U
#define c1MinuteBCMTime                                                   60000U
#define cTPMSCyclicCallPeriod                                               200U
#define cEvalSpeedValueMissingThreshold                        ((uint16)0x0A8CU)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8         ucWheelPos = cRadPosUndef;
static uint8         ucHistSlot = cAnzRad;
static uint8         ucMinutenCnt;
static uint8         ucTrefControl;
static sint8         scTrefRxTemp;
static uint16        ush5minTimer1;
static boolean       bSpeedSubstituteValInUseStatus;
static uint16        ushTimerIn200MsForContinuousSpeedStatus;
static unsigned long ulBCMTimePrevious   = 0;
static uint8         u8WUDefectErrStatus = 0;
static uint8 aucPosRecCounter[cAnzRad] = {
      0
   ,  0
   ,  0
   ,  0
};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void CountPositionReception(uint8 ucRecWheelPos);

void InitSM(void){
   InitBZ();
   InitFZZ();
   InitZK();
   InitWATCF();
   SM_ResetStatusForSpeedValueInUse();
   Init_AxImbSuppressionCounter();
   Start_AxImbSuppressionCounter();
   ucTrefControl       = LOCKED;
   scTrefRxTemp        = GETscAdaptedTrefEE();
   ucMinutenCnt        = 0x00U;
   ucWUMode3DiagActive = 0x00U;
   ush5minTimer1       = 0;
}

void InitAfterKl15OnSM(void){
   InitBZ();
   ClearBitZustandskennungZK(cPOS_CHANGED_VL);
   ClearBitZustandskennungZK(cPOS_CHANGED_VR);
   ClearBitZustandskennungZK(cPOS_CHANGED_HL);
   ClearBitZustandskennungZK(cPOS_CHANGED_HR);
   InitIDOM();
   ReloadSTATISTICS();
   InitAddZomDataSM();
   SM_ResetStatusForSpeedValueInUse();
   UpdateHistoryFromRAMWIthTheOneFromNVM();
   u8WUDefectErrStatus = 0;
}

void InitAfterKl15OffSM(void){
   StoreSTATISTICS();
   PUTucPatmoEE(
      GETucPatmoPD()
   );
   PUTscAdaptedTrefEE(scTrefRxTemp);
   StopWallocTOAlarm();
   InitSM();
}

static void CheckForStoersenderZeit(void){
   boolean l_bFlag;
   boolean l_bSensorMissFlag;
   l_bSensorMissFlag = bGetPossibleRfInterf();
   l_bFlag = GETbStoersenderZeit();
   if(
         (TRUE == l_bFlag)
      && (TRUE == l_bSensorMissFlag)
   ){
      SetCurrentErrorERR(cZO_ERR_RF_INTERFERENCE);
      PUTbHfIntLatchEE(TRUE);
   }
   else{
      if(
            (FALSE == GETbHfIntLatchEE())
         && (FALSE == l_bSensorMissFlag)
      ){
         DeleteCurrentErrorERR(cZO_ERR_RF_INTERFERENCE);
      }
   }
}

void EvIDOMTimeoutSM(void){
   SetRFinTime();
}

void SequenceControlSM(void){
   boolean bSpeedValid = FALSE;
   CheckForStoersenderZeit();
   OperateTrefTemperature();
   bSpeedValid = ReceiveGetVehicleSpeedValidity();
   if(
         (TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT))
      && (TRUE == bSpeedValid)
   ){
      IncrHistProtectTimer();
      ulBCMTimePrevious = 0;
   }
   else{
      ulBCMTimePrevious = 0;
   }
}

void EvReDataSM(void){
   static  uint8 ucFrameType;
   uint32  ulReID;
   uint8   ucTelType;
   uint8   ucSuppIdent = (uint8)(ulGetReDataIdPD() >> 28);

   ucTelType = ucGetReDataTelTypePD();
   RSSIBalancePD(GETucOffset());
   ulReID = ulGetReDataIdPD();
   ucHistSlot = ucGetColOfID(&ulReID);
   SaveReDataAtBufferPD(ucHistSlot);

   if(
         cTelTypeRotatS
      == ucTelType
   )    {ucFrameType = ucCheckForMultiFrameMF(ulReID, ucGetReDataTGCounter(), cMF_MAX_FILTER_TIME_ROTATS);}
   else {ucFrameType = ucCheckForMultiFrameMF(ulReID, ucGetReDataTGCounter(), cMF_MAX_FILTER_TIME);}

   if(cTelTypeRotatS == ucTelType){
      ucWheelPos = ucGetWheelPosSM();
      SaveRotatS();
   }
   if(
         TRUE
      == bCheckSuppIdentAndTelTypeSM(
               ucSuppIdent
            ,  ucTelType
         )
   ){
      if(
            (
                  TRUE
               == LearningWheelPosActiveSM()
            )
         && (
                  (cFT_SINGLE_FRAME == ucFrameType)
               || (cTelTypeRotatS   == ucTelType)
            )
      ){
         if(
               cTelTypeRotatS
            != ucTelType
         ){
            SetAddZomDataSM();
         }
         ucLearningWheelPosSM();
      }
      else{
      }
      if(
            (cFT_SINGLE_FRAME == ucFrameType)
         && (
                  TRUE
               == bGetBitBetriebszustandBZ(
                        cEIGENRAD
                     |  cTEILEIGENRAD
                  )
            )
         && (cTelTypeRotatS != ucTelType)
      ){
         ucWheelPos = ucGetWheelPosSM();
         if(
               (cRadPosFR != ucWheelPos)
            && (ucHistSlot < cAnzRad)
         ){
            SaveReDataInSlotSM(ucHistSlot);
#ifdef FILTER_SYMC_CAN_MSGS
            CheckStateOf_ER_PressureRx();
#endif
                 if(TRUE  == ucIsReHwDefectPD(ucHistSlot)){SensorErrorDiagSM(TRUE,  ucHistSlot);}
            else if(FALSE == ucIsReHwDefectPD(ucHistSlot)){SensorErrorDiagSM(FALSE, ucHistSlot);}
            else{}

            if(TRUE == bIsReOverTempPD(ucHistSlot)){SensorTemperatureDiagSM(TRUE,  ucHistSlot);}
            else                                   {SensorTemperatureDiagSM(FALSE, ucHistSlot);}

            if(TRUE == bIsReLowLifeTimePD(ucHistSlot)){SensorLowLifeTimeDiagSM(TRUE,  ucHistSlot);}
            else                                      {SensorLowLifeTimeDiagSM(FALSE, ucHistSlot);}

            if(
                  TRUE
               == ucIsReHwDefectPD(
                     ucHistSlot
                  )
            ){
            }
            else{
               InitResetWarnPressRefSM(
                     ucHistSlot
                  ,  GETucReifendruckPD(ucHistSlot)
               );

               if(1U == ucGetProbeCt(ucHistSlot)
               ){tWnState = tCheckForFlatTyreSM(ucHistSlot, ucWheelPos);}
                 tWnState = tCheckForFlatTyreSM(ucHistSlot, ucWheelPos);
            }
         }
      }
      if(TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
         PUTucMarkReceivedDatagramSTATISTICS(
               TRUE
            ,  ucHistSlot
         );
         (void)CountValidDatagramSTATISTICS(ucHistSlot);
      }
      CountPositionReception(ucWheelPos);
   }
}

static void ucLearningWheelPosSM(void){
   static struct InputWA tWaData;
   uint8 i          = 0;
   uint8 ucWaState  = 0;
   tWaData.ulID     = ulGetReDataPreProcIdPD();
   tWaData.ucRssi   = ucGetReDataRssiAvgPD();
   tWaData.ucStatus = 0x00;
   if(
         cRE_AK_TM_MODE_LEARNDRIVE
      == (
               ucGetReDataPreProcTransModePD()
            &  cRE_AK_TM_MODE_LEARNDRIVE
         )
   ){
      tWaData.ucStatus |= cIDStateM4;
   }
   else if(
         cRE_AK_TM_MODE_DRIVE
      == (
               ucGetReDataPreProcTransModePD()
            &  cRE_AK_TM_MODE_DRIVE
         )
   ){
      tWaData.ucStatus |= cIDStateDrive;
   }
   else{
      tWaData.ucStatus &= (uint8)((cIDStateM4 | cIDStateDrive) ^ 0xFF);
   }
   if(FALSE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
      tWaData.ucStatus &= (uint8)(0x40 ^ 0xff);
      tWaData.ucStatus |= (uint8)0x80;
   }
   else{
      if(FALSE == bGetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT)){
         tWaData.ucStatus &= (uint8)(0xC0 ^ 0xff);
      }
      else{
         tWaData.ucStatus |= 0x40;
         tWaData.ucStatus &= (uint8)(0x80 ^ 0xff);
      }
   }
   ucWaState = ucLearnID(&tWaData);
   if(
          cWAStateZO
      == (cWAStateZO & ucWaState)
   ){
      SetBitBetriebszustandBZ(
            cER_FINISH
         |  cZO_FINISH
      );
      ClearBitBetriebszustandBZ(cTEILEIGENRAD);
      CheckStateOf_ER_PressureRx_after_Allocation();
      for(
         i = 0;
         i < cMaxLR;
         i ++
      ){
         if(
               ((uint8)(0x10 << i) & ucWaState)
            ==  (uint8)(0x10 << i)
         ){
            SetChangedBit4WP(
               ucGetWPOfCol(i)
            );
         }
      }
      EntryWAStateFinishedSM();
   }
   else{
      if(
             cWAStateER
         == (cWAStateER & ucWaState)
      ){
         SetBitBetriebszustandBZ(cER_FINISH);
         ClearBitBetriebszustandBZ(cZO_FINISH);
         ClearBitBetriebszustandBZ(cTEILEIGENRAD);
         for(
            i = 0;
            i < cMaxLR;
            i ++
         ){
            if(
                   (uint8)(0x10 << i)
               == ((uint8)(0x10 << i) & ucWaState)
            ){
               SetChangedBit4WP(
                  ucGetWPOfCol(i)
               );
            }
         }
         EntryWAStateUnassignedSM();
      }
      else{
         ClearBitBetriebszustandBZ(
               cER_FINISH
            |  cZO_FINISH
         );
         if(
                cWAStateActive
            == (cWAStateActive & ucWaState)
         ){
            ClearBitBetriebszustandBZ(cER_LEARNING);
         }
         else{
            SetBitBetriebszustandBZ(cER_LEARNING);
         }
      }
   }
}

boolean LearningWheelPosActiveSM(void){
   boolean bLearnActive = FALSE;
   if(
         (TRUE  == bGetBitBetriebszustandBZ(cWA_STARTED))
      && (TRUE  == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT))
      && (FALSE == bGetBitBetriebszustandBZ(cWA_FINISH))
   ){
           if(FALSE == bGetBitBetriebszustandBZ(cZO_TIMEOUT)) {bLearnActive = TRUE;}
      else if(TRUE  == bGetBitBetriebszustandBZ(cER_FINISH))  {bLearnActive = TRUE;}
      else{}
   }
   return bLearnActive;
}

static void EntryWAStateUnassignedSM(void){
   uint8 ucHistCol;
   boolean bChangeState = FALSE;
   uint32 ulReID;
   (void)DeleteCurrentErrorERR(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);
   (void)DeleteCurrentErrorERR(cZO_ERR_DETECT_TO0_MANY_SENSORS);
   PUTbHfIntLatchEE(FALSE);
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      for(
         ucHistCol = 0;
         ucHistCol < cMaxLR;
         ucHistCol ++
      ){
         if(
               ucGetWPOfCol(ucHistCol)
            >= cMaxLR
         ){
            bChangeState = TRUE;
            PreloadFromAddZomDataSM(ucHistCol);
         }
      }
      if(TRUE == bChangeState){
         ClearBitBetriebszustandBZ(cZUGEORDNET);
         (void)ClearPosUSWIF();
      }
   }
   else{
      if(bGetBitBetriebszustandBZ(cEIGENRAD) == FALSE){
         for(
            ucHistCol = 0;
            ucHistCol < cMaxLR;
            ucHistCol ++
         ){
            PreloadFromAddZomDataSM(ucHistCol);
         }
         bChangeState = TRUE;
      }
   }
   if(bChangeState == TRUE){
      InitSTATISTICS();
      ulReID = ulGetReDataPreProcIdPD();
      Check4FastWarnOutputSM(
         ucGetColOfID(&ulReID)
      );
   }
   SetBitBetriebszustandBZ(cEIGENRAD);
   ClearBitBetriebszustandBZ(
         cWA_FINISH
      |  cER_LEARNING
   );
}

static void EntryWAStateFinishedSM(void){
   uint32  ulReID;
   DeleteErrorsOnZugeordnetSM();
   ClearBitBetriebszustandBZ(cER_LEARNING);
   if(FALSE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      SetBitBetriebszustandBZ(
            cZUGEORDNET
         |  cEIGENRAD
      );
      (void)NewPositionsUSWIF(
         GETpucStartAdrWP()
      );
      ulReID = ulGetReDataPreProcIdPD();
      Check4FastWarnOutputSM(
         ucGetColOfID(&ulReID)
      );
   }
   SetBitBetriebszustandBZ(cWA_FINISH);
}

static uint8 ucGetWheelPosSM(void){
   uint32 ulReID    = ulGetReDataPreProcIdPD();
   uint8  ucHistPos = ucGetColOfID(&ulReID);
   uint8  ucLocalWheelPos;
   uint8  ucRetVal;
   if(
         ucHistPos
      <  cAnzRad
   ){
      ucLocalWheelPos = ucGetWPOfCol(ucHistPos);
      if(
            ucLocalWheelPos
         <  cAnzRad
      )    {ucRetVal = ucLocalWheelPos;}
      else {ucRetVal = cRadPosUndef;}
   }
   else    {ucRetVal = cRadPosFR;}
   return ucRetVal;
}

static tWnStateType tCheckForFlatTyreSM(
      uint8 l_ucZomSlot
   ,  uint8 l_ucWheelPos
){
   struct HFTel tHFTel;
   struct TssMsg tTssMsg;
   tWnStateType tRetWnState;
   uint8 ucLocalReifendruck;
   tHFTel.ucId        = l_ucZomSlot;
   ucLocalReifendruck = GETucReifendruckPD(l_ucZomSlot);

   if(
         (ucLocalReifendruck > 0x04)
      && (ucLocalReifendruck < 0xFF)
   )   {tHFTel.ucP = ucLocalReifendruck;}
   else{tHFTel.ucP = 0;}

   tHFTel.scTWE = GETscTemperaturPD(l_ucZomSlot);
   tHFTel.ucLifeTime = 200;

        if(0 != ( cRE_AK_TM_EVENT_DP                                & ucGetReDataPreProcTransModePD())){tHFTel.ucState = 0x02;}
   else if(0 != ((cRE_AK_TM_MODE_DRIVE | cRE_AK_TM_MODE_LEARNDRIVE) & ucGetReDataPreProcTransModePD())){tHFTel.ucState = 0x01;}
   else                                                                                                {tHFTel.ucState = 0x00;}

   tHFTel.ushVehicleSpeed = GETushSpeedFZZ();
   tHFTel.scTa            = GETscOutdoorTemperatureFZZ();
   tHFTel.scTref          = scChooseTrefTemperature();
   tHFTel.ucKLState       = 0x00;

   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN   )){tHFTel.ucKLState |= 0x01;}
   if(TRUE == bGetBitFahrzeugzustandFZZ(cMOTOR_LAEUFT)){tHFTel.ucKLState |= 0x02;}

   tTssMsg.ucWarning = ucWarnManagerWN(
         ucComparec
      ,  (uint8*)&tHFTel
   );
   tTssMsg.ucId          = tHFTel.ucId;
   tTssMsg.ucSystemState = tHFTel.ucKLState;
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){tTssMsg.ucPos = l_ucWheelPos; tTssMsg.ucSystemState |= (uint8)0x80;}
   else                                             {tTssMsg.ucPos = ucWPUNc;}

   (void)ucTSSMsgManagerTM(
         ucTssMsgOutc
      ,  (uint8*)&tTssMsg
   );
   tRetWnState = WN_STATE_NO_WARNING;
   return tRetWnState;
}

static void DeleteErrorsOnZugeordnetSM(void){
   (void)DeleteCurrentErrorERR(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);
   (void)DeleteCurrentErrorERR(cZO_ERR_DETECT_TO0_MANY_SENSORS);
   (void)DeleteCurrentErrorERR(cZO_ERR_AXIS_LOCATION);
   (void)DeleteCurrentErrorERR(cZO_ERR_WS_DEFECT_XX);
   (void)DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_XX);
   (void)DeleteCurrentErrorERR(cZO_ERR_FAILED_TRIES);
   NvM3_PUTucAutolocationFailedCounter(ucDefAutolocationFailedCounterInit);
   if(TRUE == bGetBitZustandskennungZK(cPOS_CHANGED_VL)){
      (void)ResetWULowLifeTimeCounter(0);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_DEFECT_FL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_FL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_BATTERY_LOW_FL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_OVERTEMPERATURE_FL);
      PUTucReErrorStatusEE(
            GETucReErrorStatusEE()
         &  (uint8)(
                  (uint8)(
                        0x10
                     << cRadPosVL
                  )
               ^  0xFF
            )
      );
   }
   if(TRUE == bGetBitZustandskennungZK(cPOS_CHANGED_VR)){
      (void)ResetWULowLifeTimeCounter(1);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_DEFECT_FR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_FR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_BATTERY_LOW_FR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_OVERTEMPERATURE_FR);
      PUTucReErrorStatusEE(
            GETucReErrorStatusEE()
         &  (uint8)(
                  (uint8)(
                        0x10
                     << cRadPosVR
                  )
               ^  0xFF
            )
      );
   }
   if(TRUE == bGetBitZustandskennungZK(cPOS_CHANGED_HL)){
      (void)ResetWULowLifeTimeCounter(2);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_DEFECT_RL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_RL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_BATTERY_LOW_RL);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_OVERTEMPERATURE_RL);
      PUTucReErrorStatusEE(
            GETucReErrorStatusEE()
         &  (uint8)(
                  (uint8)(
                        0x10
                     << cRadPosHL
                  )
               ^  0xFF
            )
      );
   }
   if(TRUE == bGetBitZustandskennungZK(cPOS_CHANGED_HR)){
      (void)ResetWULowLifeTimeCounter(3);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_DEFECT_RR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_RR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_BATTERY_LOW_RR);
      (void)DeleteCurrentErrorERR(cZO_ERR_WS_OVERTEMPERATURE_RR);
      PUTucReErrorStatusEE(
            GETucReErrorStatusEE()
         &  (uint8)(
                  (uint8)(
                        0x10
                     << cRadPosHR
                  )
               ^  0xFF
            )
      );
   }
}

void EvZOTimeoutSM(void){
   uint8 ucWATOResult = ucWATO();
   if(0 == (ucWATOResult & 0x0f)){
      ClearBitBetriebszustandBZ(
            cTO_MUCH_RE
         |  cZO_TIMEOUT
      );
   }
   else{
      if(
            (FALSE == bGetBitBetriebszustandBZ(cEIGENRAD))
         || (
                  (TRUE  == bGetBitBetriebszustandBZ(cHIST_PRELOAD))
               && (FALSE == bGetBitBetriebszustandBZ(cER_FINISH))
            )
      ){
         if(0x01 == (ucWATOResult & 0x0f)){(void)SetCurrentErrorERR(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);}
         if(0x05 == (ucWATOResult & 0x0f)){(void)SetCurrentErrorERR(cZO_ERR_DETECT_TO0_MANY_SENSORS); SetBitBetriebszustandBZ(cTO_MUCH_RE);}
         if(0x09 == (ucWATOResult & 0x0f)){(void)SetCurrentErrorERR(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);}
      }
      else{
         if(FALSE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
            if(0x02 == (ucWATOResult & 0x0f)){
               (void)SetCurrentErrorERR(cZO_ERR_AXIS_LOCATION);
            }
            else if(0x04 == (ucWATOResult & 0x0f)){
               uint8 ucAutolocationFailedCounter = NvM3_GETucAutolocationFailedCounter();
               if(ucAutolocationFailedCounter > 0U){
                  ucAutolocationFailedCounter--;
                  NvM3_PUTucAutolocationFailedCounter(
                     ucAutolocationFailedCounter);
               }
               else{
                  (void)SetCurrentErrorERR(cZO_ERR_FAILED_TRIES);
               }
               (void)SetCurrentErrorERR(cZO_ERR_AXIS_LOCATION);
            }
            else{
            }
         }
      }
      SetBitBetriebszustandBZ(cZO_TIMEOUT);
   }
}

static void SensorErrorDiagSM(
      boolean bHwDefect
   ,  uint8   ucZomPos
){
   if(bHwDefect == TRUE){  CntWUDefectRD(ucZomPos);}
   else                 {ResetWUDefectRD(ucZomPos);}
}

static void SensorTemperatureDiagSM(
      boolean bReTempExceed
   ,  uint8   ucZomPos
){
   ucWUMode3DiagActive |= (uint8)(0x01 << ucZomPos);
   if(TRUE == bReTempExceed){  CntWUHighTempRD(ucZomPos);}
   else                     {ResetWUHighTempRD(ucZomPos);
   }
}

static void SensorLowLifeTimeDiagSM(
      boolean bReLowLifeTime
   ,  uint8   ucZomPos
){
   if(TRUE == bReLowLifeTime){  CntWULowLifeTimeRD(ucZomPos);}
   else                      {ResetWULowLifeTimeRD(ucZomPos);}
}

void EvalWUDefektSM(
   uint8 u8ZOMPosition
){
         uint8 l_ucWheelPos;
         uint8 l_u8ErrorStatusFromEE;
   const uint8 cWUDefectLimit = 5;
   l_u8ErrorStatusFromEE = GETucReErrorStatusEE();

   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){l_ucWheelPos = GETucRadpositionPD(u8ZOMPosition);}
   else                                             {l_ucWheelPos = cRadPosRR;}

   if(
         GetWUDefectRD(u8ZOMPosition)
      >= cWUDefectLimit
   ){
      SetCurrentErrorERR(ucWUDefectERRc[l_ucWheelPos]);
      if(
            l_ucWheelPos
         <  cAnzRad
      ){
         l_u8ErrorStatusFromEE |= (uint8)((uint8)(0x10 << l_ucWheelPos) & 0xF0);
      }
      else{
         l_u8ErrorStatusFromEE |= (uint8)0xF0;
         DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosVL]);
         DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosVR]);
         DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosHL]);
         DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosHR]);
      }
   }
   else{
      if(0x00 == GetWUDefectRD(u8ZOMPosition)){
         if(
               l_ucWheelPos
            <  cAnzRad
         ){
            DeleteCurrentErrorERR(ucWUDefectERRc[l_ucWheelPos]);
            l_u8ErrorStatusFromEE &= (uint8)(((uint8)(0x10 << l_ucWheelPos) ^ 0xFF));
         }
         else{
         }
         u8WUDefectErrStatus |= (uint8)(0x01 << u8ZOMPosition);
      }
   }
   if(0x0F == u8WUDefectErrStatus){
      DeleteCurrentErrorERR(ucWUDefectERRc[cAnzRad]);
      l_u8ErrorStatusFromEE &= 0x0F;
      u8WUDefectErrStatus = 0;
   }
   PUTucReErrorStatusEE(l_u8ErrorStatusFromEE);
}

void EvalWUNoRecSM(uint8 ucIx){
   uint8   l_ucWheelPos;
   boolean bSensorMissingErrorAllowed = FALSE;
   boolean bInvalidSpeedErrorToBeSet = FALSE;
   uint8   ucSetUnspecificPositionMissing = 0;
   boolean l_bSensorStillMissFlag;
   uint8   ucAutoLearnDTCState = 0;
   uint16  ushFolgeAusfallCount;
   uint8   ucWuDefect;
   uint8   ucEolRoutineActive;
   uint8   l_u8ErrorStatusFromEE = GETucReErrorStatusEE();
   uint16  ushThresholdForContinuousSpeedStatusIn200ms  = cEvalSpeedValueMissingThreshold;
   uint8   ucErrCount  = ucGetMissingErrorCnt();
   boolean bAutoLearnStopped = (
         0
      != bGetBitBetriebszustandBZ(
               cZO_TIMEOUT
            |  cER_FINISH
            |  cER_LEARNING
         )
   );

   if(
         (FALSE == bSpeedSubstituteValInUseStatus)
      && (ushTimerIn200MsForContinuousSpeedStatus >= ushThresholdForContinuousSpeedStatusIn200ms)
   ){
      bSensorMissingErrorAllowed = TRUE;
   }
   else{
   }
   ucAutoLearnDTCState = DTC_GetActiveStatusOfDTC(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);
   ucSetUnspecificPositionMissing = ucCheckPotentialErInZom();
   if(
      TRUE == GETbStatisticActiveSTATISTICS(ucIx)
   ){
      if(
            (TRUE  == bGetBitBetriebszustandBZ(cZUGEORDNET))
         && (FALSE == ucSetUnspecificPositionMissing)
      )    {l_ucWheelPos = GETucRadpositionPD(ucIx);}
      else {l_ucWheelPos = cRadPosRR;}

      if(l_ucWheelPos > cAnzRad){
         l_ucWheelPos = cAnzRad;
      }

      if(
            GETusFolgeAusfallCntSTATISTICS(ucIx)
         >= GETusMaxFolgeAusfallEE()
      ){
         if(TRUE == bSensorMissingErrorAllowed){
            if(TRUE == bAutoLearnStopped){
               SetCurrentErrorERR(ucWUFailERRc[l_ucWheelPos]);
            }
         }
         else{
            bInvalidSpeedErrorToBeSet = TRUE;
         }
         if(
               l_ucWheelPos
            <  cAnzRad
         ){
            l_u8ErrorStatusFromEE |= (uint8)((uint8)(0x01 << l_ucWheelPos) & 0x0F);
         }
         else{
            l_u8ErrorStatusFromEE |= 0x0F;
            DeleteCurrentErrorERR(ucWUFailERRc[cRadPosVL]);
            DeleteCurrentErrorERR(ucWUFailERRc[cRadPosVR]);
            DeleteCurrentErrorERR(ucWUFailERRc[cRadPosHL]);
            DeleteCurrentErrorERR(ucWUFailERRc[cRadPosHR]);
         }
      }
      else{
         ushFolgeAusfallCount = GETusFolgeAusfallCntSTATISTICS(ucIx);
         ucWuDefect           = GetWUDefectRD(ucIx);
         ucEolRoutineActive   = EOL_GetEOLRoutineActive();

         if(
               (ushFolgeAusfallCount <= MAX_CNT_VALUE_TO_RESET_ERR)
            && (0x00 == ucWuDefect)
            && (EOL_ROUTINE_INACTIVE == ucEolRoutineActive)
         ){
            if(
                  (l_ucWheelPos < cAnzRad)
               && (0 == ucAutoLearnDTCState)
            ){
               DeleteCurrentErrorERR(ucWUFailERRc[l_ucWheelPos]);
               l_u8ErrorStatusFromEE &= (uint8)((uint8)(0x01 << l_ucWheelPos) ^ 0xFF);
               ucErrCount--;
            }
            else{
               ucErrCount--;
            }
            PutMissingErrCnt(ucErrCount);
         }
      }
   }
   if(0 == ucErrCount){
      l_bSensorStillMissFlag = bGetPossibleRfInterf();
      if(
            (FALSE == GETbStoersenderZeit())
         && (FALSE == l_bSensorStillMissFlag)
      ){
         PUTbHfIntLatchEE(FALSE);
      }
      if(0 == ucAutoLearnDTCState){
         DeleteCurrentErrorERR(ucWUFailERRc[cAnzRad]);
         l_u8ErrorStatusFromEE &= (uint8)0xF0;
      }
      else{
      }
   }
   PUTucReErrorStatusEE(l_u8ErrorStatusFromEE);
   if(TRUE == bInvalidSpeedErrorToBeSet){
      if(
            (FALSE != bSpeedSubstituteValInUseStatus)
         && (ushTimerIn200MsForContinuousSpeedStatus >= ushThresholdForContinuousSpeedStatusIn200ms)
      ){
         SetCurrentErrorERR(cCANSpeedSignalInvalidError);
      }
      else{
      }
   }
   else{
   }
   if(FALSE == bSpeedSubstituteValInUseStatus){
      DeleteCurrentErrorERR(cCANSpeedSignalInvalidError);
   }
   else{
   }
}

void EvalWUHighTempSM(void){
   uint8 ucErrCount = cAnzRad;
   uint8 i;
   uint8 l_ucWheelPos;
   uint8 l_u8OverTempStatusEE;
   uint16 ushHelp;
   const uint8 cWUHighTempLimit = 2;
   const uint8 cOverTempErrorTimeLimit = 9;
   l_u8OverTempStatusEE = GETucReHeatUpStatusEE();
   for(
      i = 0;
      i < cAnzRad;
      i ++
   ){
      if(
             (uint8)(0x01 << i)
         == ((uint8)(0x01 << i) & ucWUMode3DiagActive)
      ){
         if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){l_ucWheelPos = GETucRadpositionPD(i);}
         else                                             {l_ucWheelPos = cRadPosRR;}

         if(
               GetWUHighTempRD(i)
            >= cWUHighTempLimit
         ){
            if(FALSE == GetAlarmAlMinuteCntOS(&ushHelp)){
               CancelAlarmAlMinuteCntOS();
               SetRelAlarmAlMinuteCntOS(60, 60);
            }
            if(
                  ucMinutenCnt
               >= cOverTempErrorTimeLimit
            ){
               SetCurrentErrorERR(ucWUTemperatureERRc[l_ucWheelPos]);
               if(
                     l_ucWheelPos
                  <  cAnzRad
               ){
                  l_u8OverTempStatusEE |= (uint8)((uint8)(0x01 << l_ucWheelPos) & 0x0F);
               }
               else{
                  l_u8OverTempStatusEE |= (uint8)0x0F;
                  DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosVL]);
                  DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosVR]);
                  DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosHL]);
                  DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosHR]);
               }
            }
         }
         else{
            if(0x00 == GetWUHighTempRD(i)){
               if(
                     l_ucWheelPos
                  <  cAnzRad
               ){
                  DeleteCurrentErrorERR(ucWUTemperatureERRc[l_ucWheelPos]);
                  l_u8OverTempStatusEE &= (uint8)(((uint8)(0x01 << l_ucWheelPos) ^ 0xFF));
               }
               else{
               }
               ucErrCount--;
            }
         }
      }
   }
   if(0 == ucErrCount){
      DeleteCurrentErrorERR(ucWUTemperatureERRc[cAnzRad]);
      l_u8OverTempStatusEE &= (uint8)0xF0;
      CancelAlarmAlMinuteCntOS();
      ucMinutenCnt = 0;
   }
   PUTucReHeatUpStatusEE(l_u8OverTempStatusEE);
}

void EvalWULowLifeTimeSM(
   uint8 u8ZomPos
){
         uint8 l_ucWheelPos;
   const uint8 cWULowLifeTimeCount = 10;

   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){l_ucWheelPos = GETucRadpositionPD(u8ZomPos);}
   else                                             {l_ucWheelPos = cRadPosRR;}

   if(
         GetWULowLifeTimeRD(u8ZomPos)
      >= cWULowLifeTimeCount
   ){
      SetCurrentErrorERR(ucWULowLifeTimeERRc[l_ucWheelPos]);
   }
   else{
      if(0x00 == GetWULowLifeTimeRD(u8ZomPos)){
         DeleteCurrentErrorERR(ucWULowLifeTimeERRc[l_ucWheelPos]);
      }
   }
}

void EvMinuteCntSM(void){
   if(
         ucMinutenCnt
      <  (uint8)255
   ){
      ucMinutenCnt++;
   }
}

static void InitResetWarnPressRefSM(
      const uint8 l_ucZomSlot
   ,  const uint8 ucActPress
){
   uint8 aucWarnAtId[4];
   (void)GetWarnOfIdUSWIF(&aucWarnAtId[0]);
   if(
         l_ucZomSlot
      <  cAnzRad
   ){
      if(0x00 == aucWarnAtId[l_ucZomSlot]){
         if(
               GETucResetWarnPressRefEE(l_ucZomSlot)
            != cInvalidREpressure
         ){
            PUTucResetWarnPressRefEE(
                  l_ucZomSlot
               ,  cInvalidREpressure
            );
         }
      }
      else{
         if(
               GETucResetWarnPressRefEE(l_ucZomSlot)
            == cInvalidREpressure
         ){
            PUTucResetWarnPressRefEE(
                  l_ucZomSlot
               ,  ucActPress
            );
         }
      }
   }
}

static void SaveReDataInSlotSM(
   uint8 ucParamZomSlot
){
   PUTucReifendruckPD     (ucGetReDataPreProcPressurePD(),          ucParamZomSlot);
   PUTscTemperaturPD      (scGetReDataPreProcTemperaturePD(),       ucParamZomSlot);
   PUTucRestlebensdauerPD (ucGetReDataPreProcRemainingLifeTimePD(), ucParamZomSlot);
   PUTucTransModePD       (ucGetReDataPreProcTransModePD(),         ucParamZomSlot);
   PUTucTelTypePD         (ucGetReDataTelTypePD(),                  ucParamZomSlot);
   PUTushSensorDefectPD   (CheckSensorDefectSM(ucParamZomSlot),     ucParamZomSlot);
   PUTucRSSIsumPD         (ucGetReDataRssiAvgPD(),                  ucParamZomSlot);
}

static uint16 CheckSensorDefectSM(
   uint8 ucParamZomSlot
){
   uint16 ushSensorDefect = GETushSensorDefectPD(ucParamZomSlot);
   uint16 ushHelp;
   if(
         0x0000
      == (
               ushGetReDataPreProcSensorDefectPD()
            &  RE_AK_SF_PRES_NOT_RECEIVED
         )
   ){
      ushHelp = (
            ushSensorDefect
         &  (
                  RE_AK_SF_MOTION_NOT_RECEIVED
               |  RE_AK_SF_TEMP_NOT_RECEIVED
               |  RE_AK_SF_RS_RL_FAIL
               |  RE_AK_SF_TEMP_FAIL
            )
      );
      ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_PRES_FAIL);
      ushSensorDefect |= ushHelp;
   }
   else{
      ushSensorDefect |= RE_AK_SF_PRES_NOT_RECEIVED;
   }

   if(
         0x0000
      == (
               ushGetReDataPreProcSensorDefectPD()
            &  RE_AK_SF_TEMP_NOT_RECEIVED
         )
   ){
      ushHelp = (
            ushSensorDefect
         &  (
                  RE_AK_SF_MOTION_NOT_RECEIVED
               |  RE_AK_SF_PRES_NOT_RECEIVED
               |  RE_AK_SF_RS_RL_FAIL
               |  RE_AK_SF_PRES_FAIL
            )
      );
      ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_TEMP_FAIL);
      ushSensorDefect |= ushHelp;
   }
   else{
      ushSensorDefect |= RE_AK_SF_TEMP_NOT_RECEIVED;
   }

   if(
         0x0000
      == (
               ushGetReDataPreProcSensorDefectPD()
            &  RE_AK_SF_MOTION_NOT_RECEIVED
         )
   ){
      ushHelp = (
            ushSensorDefect
         &  (
                  RE_AK_SF_TEMP_NOT_RECEIVED
               |  RE_AK_SF_PRES_NOT_RECEIVED
               |  RE_AK_SF_PRES_FAIL
               |  RE_AK_SF_TEMP_FAIL
            )
      );
      ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_RS_RL_FAIL);
      ushSensorDefect |= ushHelp;
   }
   else{
      ushSensorDefect |= RE_AK_SF_MOTION_NOT_RECEIVED;
   }
   return ushSensorDefect;
}

STATIC void Check4FastWarnOutputSM(
   uint8 ignoreCol
){
   uint8 ucHistCol;
   uint8 ucRadPosition;
   for(
      ucHistCol = 0;
      ucHistCol < cAnzRad;
      ucHistCol ++
   ){
      if(
            ucHistCol
         != ignoreCol
      ){
         if(
               ulGetID(ucHistCol)
            != cInitHistID
         ){
            if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){ucRadPosition = GETucRadpositionPD(ucHistCol);}
            else                                             {ucRadPosition = cRadPosRR;}

            (void)tCheckForFlatTyreSM(
                  ucHistCol
               ,  ucRadPosition
            );
         }
      }
   }
}

void PunctureWarningReset(void){
   uint8 i;
   uint8 ucCnt = 0;
   for(
      i = 0;
      i < ucSumWEc;
      i ++
   ){
      if(1 == ucGetWarnBitWN(i, ucDHWIxc)){
         ClearWarnBitWN(i, ucDHWIxc);
         ResetM1Pressure(i);
         ucCnt++;
      }
   }
   if(ucCnt > 0){
      Check4FastWarnOutputSM(cAnzRad);
   }
}

void InformWarnHandlerSM(
            boolean ResetWarn
   ,  const uint8   PressFA
   ,  const uint8   PressRA
){
   uint8 ucHelp = 0x00;
   uint8 ucHistCol;
   uint8 ucRadPosition;
   uint8 ucPWarnMin;
   if(TRUE == ResetWarn){
      (void)ResetWarnVectorUSWIF(cAnzRad);
      (void)ClearWarnOfIdUSWIF(cAnzRad);
   }
   ucPWarnMin = (GETucVarCodMinPressThresEE());
   (void)ucWAlgoPrePara(
         ucPWarnMin
      ,  GETucPSollMinVaEE()
      ,  GETucPSollMinHaEE()
   );
   for(
      ucHistCol = 0;
      ucHistCol < cAnzRad;
      ucHistCol ++
   ){
      if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){ucRadPosition = GETucRadpositionPD(ucHistCol);}
      else                                             {ucRadPosition = cRadPosRR;}

      if(
            ucRadPosition
         <  cRadPosHL
      ){
         ucHelp = PressFA;
      }
      else{
         if(
               ucRadPosition
            <  cRadPosRR
         )    {ucHelp = PressRA;}
         else {ucHelp = PressFA;}
      }
      (void)CfgReInitSingleUSWIF(
            ucHelp
         ,  20
         ,  ucHistCol
      );
   }
}

static void InitAddZomDataSM(void){
   uint8 i;
   for(
      i = 0;
      i < cSumWE;
      i ++
   ){
      tAddZomData[i].ulID          = 0x0000;
      tAddZomData[i].ucPressure    = cInvalidREpressure;
      tAddZomData[i].scTemperature = cInvalidREtemperature;
   }
}

static void SetAddZomDataSM(void){
   uint8 i;
   uint8 ucZomCol = cSumWE;

   for(
      i = 0;
      i < cSumWE;
      i ++
   ){
      if(ulGetZOMID(i) == ulGetReDataPreProcIdPD()){
         ucZomCol = i;
      }
   }
   if(
         ucZomCol
      <  cSumWE
   ){
      tAddZomData[ucZomCol].ulID          = ulGetReDataPreProcIdPD();
      tAddZomData[ucZomCol].ucPressure    = ucGetReDataPreProcPressurePD();
      tAddZomData[ucZomCol].scTemperature = scGetReDataPreProcTemperaturePD();
   }
}

static void PreloadFromAddZomDataSM(uint8 ucHistCol){
   uint8 i;
   for(
      i = 0;
      i < cSumWE;
      i ++
   ){
      if(tAddZomData[i].ulID == ulGetID(ucHistCol)){
         PUTucReifendruckPD( tAddZomData[i].ucPressure,    ucHistCol);
         PUTscTemperaturPD(  tAddZomData[i].scTemperature, ucHistCol);
      }
   }
}

boolean bCheckSuppIdentAndTelTypeSM(
      uint8 SuppIdent
   ,  uint8 TelType
){
   boolean bHelp = FALSE;
   if(0x02 != SuppIdent){
      if(
             (uint16)(0x01 << (SuppIdent & 0x0f))
         == ((uint16)(0x01 << (SuppIdent & 0x0f)) & GETushSuppIdentFilterEE())
      ){
         if(
               (TelType == cTelTypeAK35def)
            || (TelType == 0x20)
            || (TelType == cTelTypeStandstill)
         ){
            bHelp = TRUE;
         }
      }
   }
   else{
      bHelp = TRUE;
   }
   return bHelp;
}

void SM_ResetStatusForSpeedValueInUse(void){
   bSpeedSubstituteValInUseStatus          = TRUE;
   ushTimerIn200MsForContinuousSpeedStatus = 0;
}

extern void SM_TimerProcessForSpeedValueInUseStatus(void){
   boolean bNewSpeedSubstituteValInUseStatus;
   if(TRUE == ReceiveGetVehicleSpeedValidity()){bNewSpeedSubstituteValInUseStatus = FALSE;}
   else                                        {bNewSpeedSubstituteValInUseStatus = TRUE;}

   if(bSpeedSubstituteValInUseStatus != bNewSpeedSubstituteValInUseStatus){
      bSpeedSubstituteValInUseStatus = bNewSpeedSubstituteValInUseStatus;
      ushTimerIn200MsForContinuousSpeedStatus = 0;
   }
   else{
      if(ushTimerIn200MsForContinuousSpeedStatus < 0xFFFF){
         ushTimerIn200MsForContinuousSpeedStatus++;
      }
      else{
      }
   }
}

static void OperateTrefTemperature(void){
   uint16 ushVehSpeed = 0;
   if(ush5minTimer1 >= TIME_5MIN_OVER){
      if(ush5minTimer1 != TIME_5MIN_DONE){
         if(TRUE == bGetBitBetriebszustandBZ(cER_FINISH)){
            if(TRUE == bCheckActPresEnoughPplacardSM()){ucTrefControl = ENABLE_ADAPT;}
            else                                       {ucTrefControl = NO_ADAPT;}
            ush5minTimer1 = TIME_5MIN_DONE;
         }
      }
   }
   else{
      (void)ReceiveGetVehicleSpeed(&ushVehSpeed);
      if(ushVehSpeed >= SPEED_10KMH){
         ush5minTimer1++;
      }
   }
}

static sint8 scChooseTrefTemperature(void){
   uint16 ushVehSpeed = 0;
   sint8  scRet;
   if(LOCKED == ucTrefControl){
      scRet = scLockEuFbyTref;
   }
   else{
      if(NO_ADAPT == ucTrefControl){
         scRet = GETscAdaptedTrefEE();
      }
      else{
         if(ENABLE_ADAPT == ucTrefControl){
            (void)ReceiveGetVehicleSpeed(&ushVehSpeed);
            if(
                  ushVehSpeed
               >= SPEED_10KMH
            ){
               (void)ReceiveGetTrefTemperature(&scTrefRxTemp);
            }
            scRet = scTrefRxTemp;
         }
         else{
            scRet = RECEIVE_TEMP20_SUBSTVAL;
         }
      }
   }
   return scRet;
}

static boolean bCheckActPresEnoughPplacardSM(void){
   uint8   i;
   boolean bRet = FALSE;
   uint8   ucLocalReifendruck;
   uint16  ushCalcLimit = (uint16)(0xFF & GETucVarCodPlacardPressEE());
   ushCalcLimit *= 95;
   ushCalcLimit += 50;
   ushCalcLimit /= 100;
   for(
      i = 0;
      i < cAnzRad;
      i ++
   ){
      ucLocalReifendruck = GETucReifendruckPD(i);
      if(
            (ucLocalReifendruck >= ushCalcLimit)
         && (ucLocalReifendruck < 0xFE)
      )    {bRet = TRUE;}
      else {bRet = FALSE; break;}
   }
   return bRet;
}

#ifdef FILTER_SYMC_CAN_MSGS
void CheckStateOf_ER_PressureRx(void){
   uint8   l_ucLoop;
   uint8   l_ucRadPos;
   uint8   l_ucTemp;
   uint8   l_ucPressure;
   uint8   l_ucCount;
   boolean l_bDoIt;
   uint8   l_ucZomSlot;
   uint8   l_ucDefectWsCnt = 0;
   boolean l_bState = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
   if(FALSE == l_bState){
      l_ucCount = 0x01;
      l_ucTemp = GETucReErrorStatusEE();
      l_ucTemp |= GETucReHeatUpStatusEE();
      l_bDoIt = TRUE;
      for(
         l_ucRadPos = 0;
         l_ucRadPos < cAnzRad;
         l_ucRadPos ++
      ){
         if(
               ((l_ucTemp & (l_ucCount * 0x01)) == (l_ucCount * 0x01))
            || ((l_ucTemp & (l_ucCount * 0x10)) == (l_ucCount * 0x10))
         ){
            l_ucDefectWsCnt++;
            if(l_ucDefectWsCnt > 1){
               l_bDoIt = FALSE;
            }
         }
         else{
            l_ucZomSlot = cAnzRad;
            for(
               l_ucLoop = 0;
               (l_ucLoop < cAnzRad) && (l_ucZomSlot == cAnzRad);
               l_ucLoop++
            ){
               if(GETucRadpositionPD(l_ucLoop) == l_ucRadPos){
                  l_ucZomSlot = l_ucLoop;
               }
            }
            if(
                  l_ucZomSlot
               <  cAnzRad
            )    {l_ucPressure = GETucReifendruckPD(l_ucZomSlot);}
            else {l_ucPressure = cInvalidPressureCAN;}

            if((l_ucPressure == cInvalidPressureCAN)){
               l_bDoIt = FALSE;
               break;
            }
         }
         l_ucCount <<= 1;
      }
      if(TRUE == l_bDoIt){
         SetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
      }
   }
}

void CheckStateOf_ER_PressureRx_after_Allocation(void){
   uint8 l_ucZomSlot;
   uint8 l_ucAddZomSlot;
   uint32 l_ulZomID;
   uint8 l_ucHistCol;
   uint8 l_ucPressure = 0;
   boolean l_bDoIt    = TRUE;
   boolean l_bState   = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
   if(FALSE == l_bState){
      for(
         l_ucZomSlot = 0;
         l_ucZomSlot < cAnzRad;
         l_ucZomSlot ++
      ){
         l_ulZomID = ulGetZOMID(l_ucZomSlot);
         for(
            l_ucAddZomSlot = 0;
            l_ucAddZomSlot < cSumWE;
            l_ucAddZomSlot ++
         ){
            if(
                  tAddZomData[l_ucAddZomSlot].ulID
               == l_ulZomID
            ){
               l_ucPressure = tAddZomData[l_ucAddZomSlot].ucPressure;
            }
            if(cInvalidPressureCAN == l_ucPressure){
               l_bDoIt = FALSE;
               break;
            }
         }
         if(FALSE == l_bDoIt){
            break;
         }
      }
   }
   if(TRUE == l_bDoIt){
      for(
         l_ucHistCol = 0;
         l_ucHistCol < cMaxLR;
         l_ucHistCol ++
      ){
         PreloadFromAddZomDataSM(l_ucHistCol);
      }
      SetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
   }
}

boolean SendRealReData(void){
   boolean l_bState_BZ;
   boolean l_bRet;
   boolean l_bStatus = bGetBitBetriebszustandBZ(cSEND_RE_DATA_ON_CAN);
   if(FALSE == l_bStatus){
      l_bState_BZ = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
      if(TRUE == l_bState_BZ){
         SetBitBetriebszustandBZ(cSEND_RE_DATA_ON_CAN);
         l_bRet = TRUE;
      }
      else{
         l_bRet = FALSE;
      }
   }
   else{
      l_bRet = TRUE;
   }
   return l_bRet;
}
#endif

void CountPositionReception(
   uint8 ucRecWheelPos
){
   if(
         ucRecWheelPos
      <  cAnzRad
   ){
      aucPosRecCounter[ucRecWheelPos]++;
   }
}

uint8 DCM_InvIf_WheelPosReceptionCounter(
   uint8 ucRecWheelPos
){
   return aucPosRecCounter[ucRecWheelPos];
}

uint8 DCM_InvIf_WheelPosCurrIDGetValue(void){
   return ucGetWheelPosSM();
}

static void ucControlCyclicCallPeriod(void){
          boolean       bRestartCnt            = FALSE;
          boolean       bDeleteDtc             = FALSE;
          unsigned long ulBCMTimeNow           = 0;
          unsigned long ulTimeDifference       = 0;
          signed long   slPeriodDelta          = 0;
          unsigned long ulRealRunTime          = 0;
   static signed long   slCumulativPeriodDelta = 0;
   static unsigned long ulCallsCnt             = 0;

   ClientIf_GetECUTimeStampValue(&ulBCMTimeNow);
   ulCallsCnt++;
   ulCallsCnt %= 0xFFFFFFFFU;
   if(0 == ulBCMTimePrevious){
      ulBCMTimePrevious = ulBCMTimeNow;
   }
   else{
      if(
            ulBCMTimeNow
         >= ulBCMTimePrevious
      )    {ulTimeDifference = ulBCMTimeNow - ulBCMTimePrevious;}
      else {ulTimeDifference = cTPMSCyclicCallPeriod;}

      ulBCMTimePrevious       = ulBCMTimeNow;
      slPeriodDelta           = ulTimeDifference - cTPMSCyclicCallPeriod;
      slCumulativPeriodDelta += slPeriodDelta;
   }
   ulRealRunTime = ((ulCallsCnt * cTPMSCyclicCallPeriod) + slCumulativPeriodDelta);
   if(
         ulRealRunTime
      >= c10MinutesBCMTime
   ){
      NvM_WriteData_ECUDefect(U8_ECU_DEFECT_CYCLIC_TASK);
      SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
      bRestartCnt = TRUE;
   }
   else if(
         (ulCallsCnt >= cCallsFor10Minutes)
      && (ulRealRunTime <= c8MinutesBCMTime)
   ){
      NvM_WriteData_ECUDefect(U8_ECU_DEFECT_CYCLIC_TASK);
      SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
      bRestartCnt = TRUE;
   }
   else{
      if(slCumulativPeriodDelta >= 0){
         if(
               (ulCallsCnt >= cCallsFor8Minutes)
            && (slCumulativPeriodDelta <= c1MinuteBCMTime)
         ){
            bRestartCnt = TRUE;
            bDeleteDtc  = TRUE;
         }
      }
      else{
         if(
               ((ulCallsCnt * cTPMSCyclicCallPeriod) >= c10MinutesBCMTime)
            && ((-1 * slCumulativPeriodDelta) < c1MinuteBCMTime)
         ){
            bRestartCnt = TRUE;
            bDeleteDtc  = TRUE;
         }
      }
      if((ulCallsCnt * cTPMSCyclicCallPeriod) >= (c10MinutesBCMTime + c1MinuteBCMTime)){
         bRestartCnt = TRUE;
         bDeleteDtc  = TRUE;
      }
   }
   if(TRUE == bRestartCnt){
      ulCallsCnt             = 0;
      slCumulativPeriodDelta = 0;
      ulBCMTimePrevious      = 0;
   }
   if(TRUE == bDeleteDtc){
      DeleteCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
      NvM_WriteData_ECUDefect(U8_ECU_NOT_DEFECT);
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

