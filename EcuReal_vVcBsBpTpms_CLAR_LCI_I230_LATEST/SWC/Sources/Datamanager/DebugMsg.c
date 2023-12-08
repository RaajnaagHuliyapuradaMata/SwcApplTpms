/******************************************************************************/
/* File   : DebugMsg.c                                                        */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "DebugMsgX.h"

#include "datamanagerX.h"
#include "WallocX.h"
#include "Walloc_If.h"
#include "abs_linX.h"
#include "WuMonitoringX.h"
#include "NwMonitoringX.h"
#include "uswarn_ifX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "state_zkX.h"
#include "fpa_x.h"
#include "walloc_managerX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeErfsBlockX.h"
#include "EeDiagBlockX.h"
#include "EeGlobalFunctionsX.h"
#include "Rid_X.h"
#include "BreakTireX.h"
#include "SeasRcpAdjX.h"
#include "EeWarnStatusBlockX.h"
#include "WarningLampX.h"
#include "ccmX.h"
#include "SecondaryDTCX.h"
#include "InfoTyreX.h"
#include "SpeedCcmX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define EV_SPEC_DATA_SIZE  39
#define START_MPX_ID_SYS_SPEC_DATA  2

#define NO_OF_EV_SPEC_DATASETS 15

#define TRANSMIT_EVENT_SPEC_DATA  (uint8)0
#define TRANSMIT_SYS_SPEC_DATA    (uint8)1
#define REPEAT_EVENT_SPEC_DATA    (uint8)2

#define SPEC_NORM   0
#define SPEC_MIRR   1

#define cNoDataAvailable      0x00
#define cDataAvailable        0x01

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
static uint8  aucEvSpecData[NO_OF_EV_SPEC_DATASETS][EV_SPEC_DATA_SIZE];
static uint8  ucEvSpecDatasetWritePointer = 0xffu;
static uint8  ucEvSpecDatasetReadPointer = 0xffu;
static uint8  ucSwcRunTime;
static uint16 ushRCyclicCallCounter = 0;
static uint8  ucWriteErrorCounterForNvmWarnstatusBlock;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static uint8 CreateSetOfEventSpecificData32DBG   (const ImpTypeRecCddRdcData* rdcData);
static uint8 ucSelectNextEventSpecificDataSetDBG (void);
static void  GetNextEventSpecificDataBlock32DBG  (uint8*  pucBuffer, uint8* ucMuxID, uint8* ucTransmitState);
static uint8 GetNextSystemSpecificDataBlockDBG   (Rte_Instance self, uint8* pucBuffer);
static uint8 GetNextSystemSpecificDataBlock32DBG (Rte_Instance self, uint8* pucBuffer);

#if(DEBUG_MESSAGE_SIZE == 16)
static uint8 CreateSetOfEventSpecificData16DBG(ImpTypeRecCddRdcData rdcData);
static uint8 GetNextSystemSpecificDataBlock16DBG(uint8* pucBuffer);
#endif

void SetSwcRunTimeDBG(uint8 ucRunTime){
   ucSwcRunTime = ucRunTime;
}

void IncreaseRCyclicCallCounter(void){
   if(ushRCyclicCallCounter < 0xffffu){
      ushRCyclicCallCounter++;
   }
}

void IncreaseWriteErrorCounterForNvmWarnstatusBlock(void){
   ucWriteErrorCounterForNvmWarnstatusBlock++;
}

uint8 CreateSetOfEventSpecificDataDBG(const ImpTypeRecCddRdcData* rdcData){
#if(DEBUG_MESSAGE_SIZE == 16)
   return (CreateSetOfEventSpecificData16DBG(rdcData));
#endif

#if(DEBUG_MESSAGE_SIZE == 32)
   return (CreateSetOfEventSpecificData32DBG(rdcData));
#endif
}

void GetDebugMessageContentDBG(Rte_Instance self, uint8* pucBuffer){
   static uint8 ucMuxID = 0;
   static uint8 ucTransmitState = TRANSMIT_EVENT_SPEC_DATA;
   static uint8 ucEvSpecDataAvailable = cNoDataAvailable;
   if(ucMuxID == 0){
      ucEvSpecDataAvailable = ucSelectNextEventSpecificDataSetDBG();
      if(ucEvSpecDataAvailable == cNoDataAvailable){
      ucMuxID = START_MPX_ID_SYS_SPEC_DATA;
      ucTransmitState = TRANSMIT_SYS_SPEC_DATA;
      }
   }
   if(ucTransmitState == TRANSMIT_EVENT_SPEC_DATA){

    GetNextEventSpecificDataBlock32DBG(pucBuffer, &ucMuxID, &ucTransmitState);
   }
   else if(ucTransmitState == TRANSMIT_SYS_SPEC_DATA){
    pucBuffer[0] = ucMuxID;
    pucBuffer[16] = ucMuxID;
      if(GetNextSystemSpecificDataBlockDBG(self, pucBuffer) == 0){
      if(ucEvSpecDataAvailable == cDataAvailable){
        ucTransmitState = REPEAT_EVENT_SPEC_DATA;
        ucMuxID++;
      }
      else{
        ucTransmitState = TRANSMIT_EVENT_SPEC_DATA;
        ucMuxID = 0;
      }
      }
      else{
      ucMuxID++;
      }
   }
   else if(ucTransmitState == REPEAT_EVENT_SPEC_DATA){
    GetNextEventSpecificDataBlock32DBG(pucBuffer, &ucMuxID, &ucTransmitState);
      if(ucTransmitState == TRANSMIT_SYS_SPEC_DATA){
      ucTransmitState = TRANSMIT_EVENT_SPEC_DATA;
      ucMuxID = 0;
      ucEvSpecDataAvailable = cNoDataAvailable;
      }
   }
   else {}
}

#if(DEBUG_MESSAGE_SIZE == 32)
static uint8 CreateSetOfEventSpecificData32DBG(const ImpTypeRecCddRdcData* rdcData)
{
   static boolean bLockPosition = FALSE;
   uint8 queueFillStatus = 0;

   uint32 ulValue;
   uint16 ushValue;
   uint8  ucZomPos;

   if(ucEvSpecDatasetWritePointer == 0xFFU){
      ucEvSpecDatasetWritePointer = 0;
      bLockPosition = FALSE;
      queueFillStatus = 1;
   }
   else{
      if(((ucEvSpecDatasetWritePointer + 1) % NO_OF_EV_SPEC_DATASETS) == ucEvSpecDatasetReadPointer){

      bLockPosition = TRUE;
      queueFillStatus = NO_OF_EV_SPEC_DATASETS;
      }
      else{

      ucEvSpecDatasetWritePointer++;
      ucEvSpecDatasetWritePointer %= NO_OF_EV_SPEC_DATASETS;
      bLockPosition = FALSE;

      if(ucEvSpecDatasetReadPointer == 0xFFU){
        queueFillStatus = ucEvSpecDatasetWritePointer;
      }
      else{
          if(ucEvSpecDatasetWritePointer > ucEvSpecDatasetReadPointer){
          queueFillStatus = ucEvSpecDatasetWritePointer - ucEvSpecDatasetReadPointer;
        }
        else{
          queueFillStatus = NO_OF_EV_SPEC_DATASETS - (ucEvSpecDatasetReadPointer - ucEvSpecDatasetWritePointer);
        }
      }
      }
   }

   if(bLockPosition == FALSE){

      ulValue = (uint32)((uint32)rdcData->TYR_ID | ((uint32)rdcData->SUPP_ID << 28));
      ucZomPos = ucGetZOMPosOfID(&ulValue);

    aucEvSpecData[ucEvSpecDatasetWritePointer][0] = (uint8)((rdcData->RDC_SYNC_TSTMP_HI >> 24) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][1] = (uint8)((rdcData->RDC_SYNC_TSTMP_HI >> 16) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][2] = (uint8)((rdcData->RDC_SYNC_TSTMP_HI >>  8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][3] = (uint8)((rdcData->RDC_SYNC_TSTMP_HI >>  0) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][4] = (uint8)((rdcData->RDC_SYNC_TSTMP_LO >> 24) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][5] = (uint8)((rdcData->RDC_SYNC_TSTMP_LO >> 16) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][6] = (uint8)((rdcData->RDC_SYNC_TSTMP_LO >>  8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][7] = (uint8)((rdcData->RDC_SYNC_TSTMP_LO >>  0) & 0xff);

    aucEvSpecData[ucEvSpecDatasetWritePointer][8] = (uint8)((rdcData->RDC_MES_TSTMP >>  8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][9] = (uint8)((rdcData->RDC_MES_TSTMP >>  0) & 0xff);

    aucEvSpecData[ucEvSpecDatasetWritePointer][10] = (uint8)((rdcData->TYR_ID >> 24) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][11] = (uint8)((rdcData->TYR_ID >> 16) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][12] = (uint8)((rdcData->TYR_ID >>  8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][13] = (uint8)((rdcData->TYR_ID >>  0) & 0xff);

    aucEvSpecData[ucEvSpecDatasetWritePointer][14] = (uint8)ucSwcRunTime;

    aucEvSpecData[ucEvSpecDatasetWritePointer][15] = (uint8)rdcData->SUPP_ID;
    aucEvSpecData[ucEvSpecDatasetWritePointer][16] = (uint8)rdcData->PCKG_ID;
    aucEvSpecData[ucEvSpecDatasetWritePointer][17] = (uint8)rdcData->RDC_DT_1;
    aucEvSpecData[ucEvSpecDatasetWritePointer][18] = (uint8)rdcData->RDC_DT_2;
    aucEvSpecData[ucEvSpecDatasetWritePointer][19] = (uint8)rdcData->RDC_DT_3;
    aucEvSpecData[ucEvSpecDatasetWritePointer][20] = (uint8)rdcData->RDC_DT_4;
    aucEvSpecData[ucEvSpecDatasetWritePointer][21] = (uint8)rdcData->RDC_DT_5;
    aucEvSpecData[ucEvSpecDatasetWritePointer][22] = (uint8)rdcData->RDC_DT_6;
    aucEvSpecData[ucEvSpecDatasetWritePointer][23] = (uint8)rdcData->RDC_DT_7;
    aucEvSpecData[ucEvSpecDatasetWritePointer][24] = (uint8)rdcData->RDC_DT_8;

    aucEvSpecData[ucEvSpecDatasetWritePointer][25] = (uint8)ucZomPos;

      ushValue = ushGetLinABSValue(0);
    aucEvSpecData[ucEvSpecDatasetWritePointer][26] = (uint8)((ushValue >> 8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][27] = (uint8)((ushValue >> 0) & 0xff);

      ushValue = ushGetLinABSValue(1);
    aucEvSpecData[ucEvSpecDatasetWritePointer][28] = (uint8)((ushValue >> 8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][29] = (uint8)((ushValue >> 0) & 0xff);

      ushValue = ushGetLinABSValue(2);
    aucEvSpecData[ucEvSpecDatasetWritePointer][30] = (uint8)((ushValue >> 8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][31] = (uint8)((ushValue >> 0) & 0xff);

      ushValue = ushGetLinABSValue(3);
    aucEvSpecData[ucEvSpecDatasetWritePointer][32] = (uint8)((ushValue >> 8) & 0xff);
    aucEvSpecData[ucEvSpecDatasetWritePointer][33] = (uint8)((ushValue >> 0) & 0xff);

    aucEvSpecData[ucEvSpecDatasetWritePointer][34] = (uint8)ucGetZomToothTelCtCorrLearnBit(ucZomPos);
    aucEvSpecData[ucEvSpecDatasetWritePointer][35] = (uint8)ucGetZomToothTelCtCorrNoLearnBit(ucZomPos);
    aucEvSpecData[ucEvSpecDatasetWritePointer][36] = (uint8)ucGetZomToothTelCtrNoCorr(ucZomPos);
    aucEvSpecData[ucEvSpecDatasetWritePointer][37] = (uint8)ucGetZomToothTelCtNoLearnMode(ucZomPos);
    aucEvSpecData[ucEvSpecDatasetWritePointer][38] = (uint8)ucGetRdcEventCounterDM();

   }

   return queueFillStatus;
}
#endif

static uint8 ucSelectNextEventSpecificDataSetDBG(void)
{
   uint8 ucReturnValue = cNoDataAvailable;
   boolean bReadQueueData = TRUE;

   if(ucEvSpecDatasetWritePointer != 0xFFU){

      if(ucEvSpecDatasetReadPointer == 0xFFU){
      ucEvSpecDatasetReadPointer = 0;
      }

      else{
      if(ucEvSpecDatasetReadPointer == ucEvSpecDatasetWritePointer){

        bReadQueueData = FALSE;
      }
      else{

        ucEvSpecDatasetReadPointer++;
        ucEvSpecDatasetReadPointer %= NO_OF_EV_SPEC_DATASETS;
      }
      }

      if(bReadQueueData == TRUE){
      ucReturnValue = cDataAvailable;
      }
   }

   return ucReturnValue;
}

static void GetNextEventSpecificDataBlock32DBG(uint8* pucBuffer, uint8* ucMuxID, uint8* ucTransmitState)
{
   uint8 ucMessageBufferPointer = 0;
   static uint8 ucEvSpecDataPointer = 0;

  pucBuffer[ucMessageBufferPointer] = *ucMuxID;
#if(DEBUG_MESSAGE_SIZE == 32)
  pucBuffer[ucMessageBufferPointer+16] = *ucMuxID;
#endif
   ucMessageBufferPointer++;

  while ((ucMessageBufferPointer < DEBUG_MESSAGE_SIZE)
      && (ucEvSpecDataPointer < EV_SPEC_DATA_SIZE)){
    pucBuffer[ucMessageBufferPointer] = aucEvSpecData[ucEvSpecDatasetReadPointer][ucEvSpecDataPointer];
      ucEvSpecDataPointer++;
      ucMessageBufferPointer++;

    #if(DEBUG_MESSAGE_SIZE == 32)
      if(ucMessageBufferPointer == 16){
      ucMessageBufferPointer++;
      }
    #endif
   }

   ucMessageBufferPointer = 0;
   (*ucMuxID)++;

   if(ucEvSpecDataPointer == EV_SPEC_DATA_SIZE){
      ucEvSpecDataPointer = 0;
    *ucTransmitState = TRANSMIT_SYS_SPEC_DATA;
   }
}

static uint8 GetNextSystemSpecificDataBlockDBG(Rte_Instance self, uint8* pucBuffer)
{
#if(DEBUG_MESSAGE_SIZE == 16)
   return (GetNextSystemSpecificDataBlock16DBG(pucBuffer));
#endif

#if(DEBUG_MESSAGE_SIZE == 32)
   return ( GetNextSystemSpecificDataBlock32DBG(self, pucBuffer));
#endif

}

#if(DEBUG_MESSAGE_SIZE == 32)
static uint8  GetNextSystemSpecificDataBlock32DBG(Rte_Instance self, uint8* pucBuffer)
{
   uint32  ulValue,  ulValue1;
   uint16  ushValue, ushValue1;
   uint8   ucValue,  ucValue1, ucValue2;
   sint8   scValue,  scValue1;

   uint8 aucValue[4];
   tNwMonitoringData tNwMonData;

   uint8  ucTimerState;

   sint16 sshAltMeter;

   static uint8 ucMessageNr = 0;
   static uint8 ucZomSlot = 0;
   uint8 i;

   uint8 ucRetVal = 1;

   switch(ucMessageNr){
      case (uint8)0:
      ulValue = ulGetIDOfColWAL(0);
    pucBuffer[1] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[2] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[3] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[4] = (uint8)((ulValue >>  0) & 0xff);
    pucBuffer[5] = ucGetWPOfColWAL(0);

      ulValue = ulGetIDOfColWAL(1);
    pucBuffer[6] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[7] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[8] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[9] = (uint8)((ulValue >>  0) & 0xff);
    pucBuffer[10] = ucGetWPOfColWAL(1);

      ulValue = ulGetIDOfColWAL(2);
    pucBuffer[11] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[12] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[13] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[14] = (uint8)((ulValue >>  0) & 0xff);
    pucBuffer[15] = ucGetWPOfColWAL(2);

      ulValue = ulGetIDOfColWAL(3);
    pucBuffer[17] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[18] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[19] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[20] = (uint8)((ulValue >>  0) & 0xff);
    pucBuffer[21] = ucGetWPOfColWAL(3);

      ushValue = ushGetWheelUnitMissingCounterWUM(0);
    pucBuffer[22] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[23] = (uint8)((ushValue >>  0) & 0xff);

      ushValue = ushGetWheelUnitMissingCounterWUM(1);
    pucBuffer[24] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[25] = (uint8)((ushValue >>  0) & 0xff);

      ushValue = ushGetWheelUnitMissingCounterWUM(2);
    pucBuffer[26] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[27] = (uint8)((ushValue >>  0) & 0xff);

      ushValue = ushGetWheelUnitMissingCounterWUM(3);
    pucBuffer[28] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[29] = (uint8)((ushValue >>  0) & 0xff);

    pucBuffer[30] = (uint8)ucSwcRunTime;

    pucBuffer[31] = GetRidManAutoFLagRID();

      ucMessageNr++;
      break;

      case (uint8)1:

      (void) ucGetWarnVectorIdExtIFH(self, aucValue);
      for(i = 0; i < cAnzRad; i++){
        pucBuffer[1 + i] = aucValue[i];
      }

      for(i = 0; i < cAnzRad; i++){
        (void) ucGetPTSollUSWIF(self, &ucValue, &scValue, &ucValue1, &scValue1, &ushValue, &ucValue1, i);
        pucBuffer[5 + i] = ucValue;
      }

      ushValue = ushGetBetriebszustandBZ(cBZ_ALLE_BITS);
      pucBuffer[9] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[10] = (uint8)((ushValue >>  0) & 0xff);

      ushValue = ushGetFahrzeugzustandFZZ(cFZZ_ALLE_BITS);
      pucBuffer[11] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[12] = (uint8)((ushValue >>  0) & 0xff);

      ushValue = ushGetZustandskennungZK(cZK_ALLE_BITS);
      pucBuffer[13] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[14] = (uint8)((ushValue >>  0) & 0xff);

      pucBuffer[15] = ucGetStopCounter();

      pucBuffer[17] = ucGetRefPointResetCounter();

      ulValue = ulGetStopTimeDM();
      pucBuffer[18] = (uint8)((ulValue >> 24) & 0xff);
      pucBuffer[19] = (uint8)((ulValue >> 16) & 0xff);
      pucBuffer[20] = (uint8)((ulValue >>  8) & 0xff);
      pucBuffer[21] = (uint8)((ulValue >>  0) & 0xff);

      ushValue = ushGetWatoTimeoutValueWAM();
      pucBuffer[22] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[23] = (uint8)((ushValue >>  0) & 0xff);

      pucBuffer[24] = GETucPAmbValEE(self);

      ushValue = GETushSpeedFZZ();
      pucBuffer[25] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[26] = (uint8)((ushValue >>  0) & 0xff);

      pucBuffer[27] = (uint8) GETscTAmbValEE(self);

      pucBuffer[28]= ucGetStatusLastConditionVehicleFZZ();
      pucBuffer[29]= ucGetStatusConditionVehicleFZZ();

      pucBuffer[30]= (uint8)((ushRCyclicCallCounter >> 8) & 0xffu);
      pucBuffer[31]= (uint8)(ushRCyclicCallCounter & 0xffu);

      ucMessageNr++;
      break;

      case (uint8)2:
      case (uint8)3:
      case (uint8)4:
      case (uint8)5:
      case (uint8)6:
      case (uint8)7:
      case (uint8)8:
      case (uint8)9:

      ulValue = ulGetZOMID(ucZomSlot);
    pucBuffer[1] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[2] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[3] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[4] = (uint8)((ulValue >>  0) & 0xff);

    pucBuffer[5] = ucGetZomAbsoluteProbeCt(ucZomSlot);
    pucBuffer[6] = ucGetZomStatus(ucZomSlot);

      for(i=0; i<cMaxLR; i++){
      pucBuffer[7+i] = ucGetZomAbsRefStartValue(ucZomSlot, i);
      }

      for(i=0; i<cMaxLR; i++){
      ushValue = ucGetZomDistanceValue(SPEC_NORM, ucZomSlot, i);
      pucBuffer[11+i] = (uint8)(ushValue & 0xff);
      }

      for(i=0; i<cMaxLR; i++){
      ushValue = ucGetZomDistanceValue(SPEC_MIRR, ucZomSlot, i);
      pucBuffer[17+i] = (uint8)(ushValue & 0xff);
      }

      for(i=0; i<cMaxLR; i++){
      pucBuffer[21+i] = ucGetZomAbsComp(ucZomSlot, i);
      }

      for(i=0; i<cMaxLR; i++){
      ucValue = ucGetZomAbsMetrics(ucZomSlot, i);
      pucBuffer[25+i] = ucValue;
      }
    pucBuffer[29] = ucGetZomDeltaMin(ucZomSlot);
    pucBuffer[30] = ucGetZomLearnProbeCt(ucZomSlot);
    pucBuffer[31] = ucGetZomLocateProbeCt(ucZomSlot);
      ucZomSlot++;
      ucMessageNr++;
      if(ucZomSlot > 7){
      ucZomSlot = 0;
      }
      break;

      case (uint8)10:
      ulValue = ulGetWheelUnitErrorsWUM(FALSE);
    pucBuffer[1] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[2] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[3] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[4] = (uint8)((ulValue >>  0) & 0xff);
      ulValue = ulGetWheelUnitErrorsWUM(TRUE);
    pucBuffer[5] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[6] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[7] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[8] = (uint8)((ulValue >>  0) & 0xff);
      ulValue = ulGetNetworkErrorsNWM();
    pucBuffer[9] = (uint8)((ulValue >> 24) & 0xff);
    pucBuffer[10] = (uint8)((ulValue >> 16) & 0xff);
    pucBuffer[11] = (uint8)((ulValue >>  8) & 0xff);
    pucBuffer[12] = (uint8)((ulValue >>  0) & 0xff);
      ushValue = GETushFbd4AliveTimerEE(self);
    pucBuffer[13] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[14] = (uint8)((ushValue >>  0) & 0xff);
    pucBuffer[15] = GetRfIfStateMachineFromNvmZOMirrorblockEE(self);
      ushValue = ushGetMuteTimerValueWUM(0);
    pucBuffer[17] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[18] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetMuteTimerValueWUM(1);
    pucBuffer[19] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[20] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetMuteTimerValueWUM(2);
    pucBuffer[21] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[22] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetMuteTimerValueWUM(3);
    pucBuffer[23] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[24] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetReDefectCounterBySlotWUM(0);
    pucBuffer[25] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[26] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetReDefectCounterBySlotWUM(1);
    pucBuffer[27] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[28] = (uint8)((ushValue >>  0) & 0xff);
      ushValue = ushGetReDefectCounterBySlotWUM(2);
    pucBuffer[29] = (uint8)((ushValue >>  8) & 0xff);
    pucBuffer[30] = (uint8)((ushValue >>  0) & 0xff);
    pucBuffer[31] = ucGetAutoLocFailedCounterWUM();
      ucMessageNr++;
      break;

      case (uint8)11:
      ushValue = ushGetReDefectCounterBySlotWUM(3);
      pucBuffer[1] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[2] = (uint8)((ushValue >>  0) & 0xff);
      pucBuffer[3] = ucGetLoBatCounterValueWUM(0);
      pucBuffer[4] = ucGetLoBatCounterValueWUM(1);
      pucBuffer[5] = ucGetLoBatCounterValueWUM(2);
      pucBuffer[6] = ucGetLoBatCounterValueWUM(3);
      GetNwMonitoringDataNWM(&tNwMonData);
      pucBuffer[7] = tNwMonData.tMonCON_VEH.ucMsgTimeout;
      pucBuffer[8] = tNwMonData.tMonA_TEMP.ucMsgTimeout;
      pucBuffer[9] = tNwMonData.tMonEINH_BN2020.ucMsgTimeout;
      if(tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout < tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout){
        ushValue = tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout;
      }
      else{
        ushValue = tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout;
      }
      pucBuffer[10] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[11] = (uint8)((ushValue >>  0) & 0xff);
      pucBuffer[12] = tNwMonData.tMonRELATIVZEIT.ucMsgTimeout;
      pucBuffer[13] = GETSelectedTyreIndexEE(self);
      pucBuffer[14] = GETSelectedSuTyreIndexEE(self);
      pucBuffer[15] = GETSelectedWiTyreIndexEE(self);
      for(i = 0; i < cAnzRad; i++){
        GetTimerValPWARN( i, &ucTimerState, &ushValue);
        pucBuffer[17 + (2 * i)] = (uint8)((ushValue >>  8) & 0xff);
        pucBuffer[18 + (2 * i)] = (uint8)((ushValue >>  0) & 0xff);
      }
      (void) ucGetWarnBitIdIntIFH(self, aucValue);
      for(i = 0; i < cAnzRad; i++){
        pucBuffer[25 + i] = aucValue[i];
      }
      scValue = GETscTAinitValEE(self);
      pucBuffer[29] = (uint8) scValue;
      pucBuffer[30] = ucGetBreakTireStateBT();
      pucBuffer[31] = GetSecondaryErrorsSCD();
      ucMessageNr++;
      break;

      case (uint8)12:
      for(i = 0; i < cAnzRad; i++){
        GetTimerValPVORW( i, &ucValue, &ushValue);
        pucBuffer[1 + (3 * i)] = (uint8)((ushValue >>  8) & 0xff);
        pucBuffer[2 + (3 * i)] = (uint8)((ushValue >>  0) & 0xff);
        pucBuffer[3 + (3 * i)] = ucValue;
      }
      ushValue = ushGetInvalidAbsTstmpCounterWAM();
      pucBuffer[13] = (uint8)((ushValue >>  8) & 0xff);
      pucBuffer[14] = (uint8)((ushValue >>  0) & 0xff);
      pucBuffer[15] = ucGetInvalidRdcTstmpCounterWAM();
      for(i = 0; i < cAnzRad; i++){
        GetTimerValPWARNTOL( i, &ucTimerState, &ushValue);
        pucBuffer[17 + (2 * i)] = (uint8)((ushValue >>  8) & 0xff);
        pucBuffer[18 + (2 * i)] = (uint8)((ushValue >>  0) & 0xff);
      }
      for(i = 0; i < cAnzRad; i++){
        (void) ucGetPTSollUSWIF(self, &ucValue, &scValue, &ucValue1, &scValue1, &ushValue, &ucValue1, i);
        pucBuffer[25 + i] = (uint8) scValue;
      }
      pucBuffer[29] = ucWriteErrorCounterForNvmWarnstatusBlock;
      pucBuffer[30] = ucGetStateSCC( 0xffu);
      pucBuffer[31] = ucGetFlexrayStatusFZZ();
      ucMessageNr++;
      break;

      case (uint8)13:
      GetInternalLowerDataSRA( &ucValue, &ucValue1, &ulValue, &ulValue1, (boolean *) &ucValue2);
      pucBuffer[1]  = ucValue;
      pucBuffer[2]  = ucValue1;
      pucBuffer[3]  = (uint8) ((ulValue  >> 24) & 0xff);
      pucBuffer[4]  = (uint8) ((ulValue  >> 16) & 0xff);
      pucBuffer[5]  = (uint8) ((ulValue  >>  8) & 0xff);
      pucBuffer[6]  = (uint8) ((ulValue  >>  0) & 0xff);
      pucBuffer[7]  = (uint8) ((ulValue1 >> 24) & 0xff);
      pucBuffer[8]  = (uint8) ((ulValue1 >> 16) & 0xff);
      pucBuffer[9]  = (uint8) ((ulValue1 >>  8) & 0xff);
      pucBuffer[10] = (uint8) ((ulValue1 >>  0) & 0xff);
      pucBuffer[11] = ucValue2;
      for(i = 0; i < cAnzRad; i++){
        (void) ucGetPTSollUSWIF(self, &ucValue, &scValue, &ucValue1, &scValue1, &ushValue, &ucValue2, i);
        pucBuffer[12 + i] = ucValue1;
      }
      (void) ucGetWarnBitTonnageIdIntIFH(self, aucValue);
      for(i = 0; i < cAnzRad; i++){
        pucBuffer[17 + i] = aucValue[i];
      }
      (void) ucGetWarnBitAirMassIdIntIFH(self, aucValue);
      for(i = 0; i < cAnzRad; i++){
        pucBuffer[21 + i] = aucValue[i];
      }
      GetTimerValDHW( 0, &ucValue, &ucValue1, &ushValue, &ushValue1);
      pucBuffer[25] = ucValue;
      pucBuffer[26] = ucValue1;
      pucBuffer[27] = (uint8) ((ushValue >>  8) & 0xff);
      pucBuffer[28] = (uint8) ((ushValue >>  0) & 0xff);
      pucBuffer[29] = (uint8) ((ushValue1 >>  8) & 0xff);
      pucBuffer[30] = (uint8) ((ushValue1 >>  0) & 0xff);
      pucBuffer[31] = ucGetRfBackgroundNoiseLevelDM();
      ucMessageNr++;
      break;

      case (uint8)14:
      GetInternalHigherDataSRA( &ucValue, &ucValue1, &ulValue, &ulValue1, (boolean *) &ucValue2);
      pucBuffer[1]  = ucValue;
      pucBuffer[2]  = ucValue1;
      pucBuffer[3]  = (uint8) ((ulValue  >> 24) & 0xff);
      pucBuffer[4]  = (uint8) ((ulValue  >> 16) & 0xff);
      pucBuffer[5]  = (uint8) ((ulValue  >>  8) & 0xff);
      pucBuffer[6]  = (uint8) ((ulValue  >>  0) & 0xff);
      pucBuffer[7]  = (uint8) ((ulValue1 >> 24) & 0xff);
      pucBuffer[8]  = (uint8) ((ulValue1 >> 16) & 0xff);
      pucBuffer[9]  = (uint8) ((ulValue1 >>  8) & 0xff);
      pucBuffer[10] = (uint8) ((ulValue1 >>  0) & 0xff);
      pucBuffer[11] = ucValue2;
      for(i = 0; i < cAnzRad; i++){
        (void) ucGetPTSollUSWIF(self, &ucValue, &scValue, &ucValue1, &scValue1, &ushValue, &ucValue2, i);
        pucBuffer[12 + i] = (uint8) scValue1;
      }
      GetTimerValDHW( 1, &ucValue, &ucValue1, &ushValue, &ushValue1);
      pucBuffer[17] = ucValue;
      pucBuffer[18] = ucValue1;
      pucBuffer[19] = (uint8) ((ushValue >>  8) & 0xff);
      pucBuffer[20] = (uint8) ((ushValue >>  0) & 0xff);
      pucBuffer[21] = (uint8) ((ushValue1 >>  8) & 0xff);
      pucBuffer[22] = (uint8) ((ushValue1 >>  0) & 0xff);
      GetTimerValDHW( 2, &ucValue, &ucValue1, &ushValue, &ushValue1);
      pucBuffer[23] = ucValue;
      pucBuffer[24] = ucValue1;
      pucBuffer[25] = (uint8) ((ushValue >>  8) & 0xff);
      pucBuffer[26] = (uint8) ((ushValue >>  0) & 0xff);
      pucBuffer[27] = (uint8) ((ushValue1 >>  8) & 0xff);
      pucBuffer[28] = (uint8) ((ushValue1 >>  0) & 0xff);
      pucBuffer[29] = (uint8) (ushGetWheelUnitGoodCounterWUM(0) & 0xffu);
      pucBuffer[30] = (uint8) (ushGetWheelUnitGoodCounterWUM(1) & 0xffu);
      pucBuffer[31] = (uint8) (ushGetWheelUnitGoodCounterWUM(2) & 0xffu);
      ucMessageNr++;
      break;

      default:
      pucBuffer[1] = (uint8) (ushGetWheelUnitGoodCounterWUM(3) & 0xffu);
      GetAvlPTyreCoolingValITY( 0, &ucValue, &scValue, &ucValue, &scValue, &ucValue, &scValue, &ucValue, &ucValue, &scValue, &ucValue, &ushValue, &ushValue, &ulValue);
      if(ulValue == 0xFFFFFFFFu){
        pucBuffer[2] =  0xff;
        pucBuffer[3] =  0xff;
      }
      else{
        ushValue = (uint16) (ulGetStopTimeDM() - ulValue);
        pucBuffer[2] = (uint8) ((ushValue >>  8) & 0xff);
        pucBuffer[3] = (uint8) ((ushValue >>  0) & 0xff);
      }
      if(cInvalidTemperatureWord != GETsshTAmbFiltValEE(self)){
          if(GETsshTAmbFiltValEE(self) < 0){
          pucBuffer[4] = (uint8) ((GETsshTAmbFiltValEE(self) - 50) / 100);
         }
         else{
          pucBuffer[4] = (uint8) ((GETsshTAmbFiltValEE(self) + 50) / 100);
        }
      }
      else{
        pucBuffer[4] = cInvalidREtemperature;
      }
      pucBuffer[5] = GETucAipGpsStateEE(self);
      ushValue = GETushGpsTioTicksEE(self);
      pucBuffer[6] = (uint8) ((ushValue >>  8) & 0xffu);
      pucBuffer[7] = (uint8) ((ushValue >>  0) & 0xffu);
      sshAltMeter = (sint16) ((GETushPositionAltitudeEE(self) + 5) / 10) - 1000;
      if(sshAltMeter < 0){
        sshAltMeter = 0;
      }
      if(sshAltMeter < (sint16) cAGS_2500Mtr){
        pucBuffer[8] = (uint8) ((((cAGS_Pat0Mtr - (((cAGS_Pat0Mtr - cAGS_Pat2500Mtr) * 4 * (uint16) sshAltMeter) / 10000)) * 10) + 125) / 259);
      }
      else{
        pucBuffer[8] = (uint8) ((((cAGS_Pat2500Mtr - (((cAGS_Pat2500Mtr - cAGS_Pat5000Mtr) * 4 * ((uint16) sshAltMeter - cAGS_2500Mtr)) / 10000)) * 10) + 125) / 250);
      }
      GetWADataEE(self, cPermutationState, &ucValue, sizeof(ucValue));
      pucBuffer[9] = ucValue;
      ulValue = (uint32)GETslOATavgEE(self);
      ulValue /= 10;
      pucBuffer[10] = (uint8)((ulValue >> 8) & 0xFFu);
      pucBuffer[11] = (uint8)(ulValue & 0xFFu);
      pucBuffer[12] = 0xff;
      pucBuffer[13] = 0xff;
      pucBuffer[14] = 0xff;
      pucBuffer[15] = 0xff;
      GetTimerValDHW( 3, &ucValue, &ucValue1, &ushValue, &ushValue1);
      pucBuffer[17] = ucValue;
      pucBuffer[18] = ucValue1;
      pucBuffer[19] = (uint8) ((ushValue >>  8) & 0xff);
      pucBuffer[20] = (uint8) ((ushValue >>  0) & 0xff);
      pucBuffer[21] = (uint8) ((ushValue1 >>  8) & 0xff);
      pucBuffer[22] = (uint8) ((ushValue1 >>  0) & 0xff);
      ulValue = ulGetStartedStateOfVklCCM();
      pucBuffer[23] = (uint8) ((ulValue >> 24) & 0xff);
      pucBuffer[24] = (uint8) ((ulValue >> 16) & 0xff);
      pucBuffer[25] = (uint8) ((ulValue >>  8) & 0xff);
      pucBuffer[26] = (uint8) ((ulValue >>  0) & 0xff);
      pucBuffer[27] = ucGetActualStateWL();
      pucBuffer[28] = ucGetNokCounterCCM();
      pucBuffer[29] = ucGetInitByContiEventCounterEE(self);
      pucBuffer[30] = ucGetInitByHufEventCounterEE(self);
      pucBuffer[31] = ucGetCodingDataChangeEventCounterEE(self);
      ucMessageNr = 0;
      ucRetVal = 0;
      break;
   }
   return ucRetVal;
}
#endif

#if(DEBUG_MESSAGE_SIZE == 16)
static uint8 CreateSetOfEventSpecificData16DBG(ImpTypeRecCddRdcData rdcData){
   uint32 ulValue;
   uint16 ushValue;
   uint8  ucZomPos;
   uint8  ucTemp = ucEvSpecDatasetWritePointer;
   static uint8 ucRxEventCounter = 0;
   ucRxEventCounter++;
   ucEvSpecDatasetWritePointer++;
   ucEvSpecDatasetWritePointer %= NO_OF_EV_SPEC_DATASETS;
   if(ucEvSpecDatasetWritePointer == ucEvSpecDatasetReadPointer){
      ucEvSpecDatasetWritePointer = ucTemp;
      return 0xff;
   }
   ulValue = (uint32)((uint32)rdcData.TYR_ID | ((uint32)rdcData.SUPP_ID << 28));
   ucZomPos = ucGetZOMPosOfID(&ulValue);
  aucEvSpecData[ucEvSpecDatasetWritePointer][0] = (rdcData.RDC_SYNC_TSTMP_HI >> 24) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][1] = (rdcData.RDC_SYNC_TSTMP_HI >> 16) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][2] = (rdcData.RDC_SYNC_TSTMP_HI >>  8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][3] = (rdcData.RDC_SYNC_TSTMP_HI >>  0) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][4] = (rdcData.RDC_SYNC_TSTMP_LO >> 24) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][5] = (rdcData.RDC_SYNC_TSTMP_LO >> 16) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][6] = (rdcData.RDC_SYNC_TSTMP_LO >>  8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][7] = (rdcData.RDC_SYNC_TSTMP_LO >>  0) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][8] = (rdcData.RDC_MES_TSTMP >>  8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][9] = (rdcData.RDC_MES_TSTMP >>  0) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][10] = (rdcData.TYR_ID >> 24) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][11] = (rdcData.TYR_ID >> 16) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][12] = (rdcData.TYR_ID >>  8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][13] = (rdcData.TYR_ID >>  0) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][14] = rdcData.SUPP_ID;
  aucEvSpecData[ucEvSpecDatasetWritePointer][15] = rdcData.PCKG_ID;
  aucEvSpecData[ucEvSpecDatasetWritePointer][16] = rdcData.RDC_DT_1;
  aucEvSpecData[ucEvSpecDatasetWritePointer][17] = rdcData.RDC_DT_2;
  aucEvSpecData[ucEvSpecDatasetWritePointer][18] = rdcData.RDC_DT_3;
  aucEvSpecData[ucEvSpecDatasetWritePointer][19] = rdcData.RDC_DT_4;
  aucEvSpecData[ucEvSpecDatasetWritePointer][20] = rdcData.RDC_DT_5;
   ushValue = ushGetLinABSValue(0);
  aucEvSpecData[ucEvSpecDatasetWritePointer][21] = (ushValue >> 8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][22] = (ushValue >> 0) & 0xff;
   ushValue = ushGetLinABSValue(1);
  aucEvSpecData[ucEvSpecDatasetWritePointer][23] = (ushValue >> 8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][24] = (ushValue >> 0) & 0xff;
   ushValue = ushGetLinABSValue(2);
  aucEvSpecData[ucEvSpecDatasetWritePointer][25] = (ushValue >> 8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][26] = (ushValue >> 0) & 0xff;
   ushValue = ushGetLinABSValue(3);
  aucEvSpecData[ucEvSpecDatasetWritePointer][27] = (ushValue >> 8) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][28] = (ushValue >> 0) & 0xff;
  aucEvSpecData[ucEvSpecDatasetWritePointer][29] = ucZomPos;
  aucEvSpecData[ucEvSpecDatasetWritePointer][30] = ucGetZomToothTelCtCorrLearnBit(ucZomPos);
  aucEvSpecData[ucEvSpecDatasetWritePointer][31] = ucGetZomToothTelCtCorrNoLearnBit(ucZomPos);
  aucEvSpecData[ucEvSpecDatasetWritePointer][32] = ucGetZomToothTelCtrNoCorr(ucZomPos);
  aucEvSpecData[ucEvSpecDatasetWritePointer][33] = ucGetZomToothTelCtNoLearnMode(ucZomPos);
  aucEvSpecData[ucEvSpecDatasetWritePointer][34] = ucRxEventCounter;

   return 0x00;
}

static uint8  GetNextSystemSpecificDataBlock16DBG(uint8* pucBuffer){
   uint32 ulValue;
   uint16 ushValue;
   uint8  ucRetVal = 1;
   static uint8  ucMessageNr = 0;

   switch(ucMessageNr){
      case 0:
      ulValue = ulGetIDOfColWAL(0);
    pucBuffer[1] = (ulValue >> 24) & 0xff;
    pucBuffer[2] = (ulValue >> 16) & 0xff;
    pucBuffer[3] = (ulValue >>  8) & 0xff;
    pucBuffer[4] = (ulValue >>  0) & 0xff;
    pucBuffer[5] = ucGetWPOfColWAL(0);
      ulValue = ulGetIDOfColWAL(1);
    pucBuffer[6] = (ulValue >> 24) & 0xff;
    pucBuffer[7] = (ulValue >> 16) & 0xff;
    pucBuffer[8] = (ulValue >>  8) & 0xff;
    pucBuffer[9] = (ulValue >>  0) & 0xff;
    pucBuffer[10] = ucGetWPOfColWAL(1);
      ulValue = ulGetIDOfColWAL(2);
    pucBuffer[11] = (ulValue >> 24) & 0xff;
    pucBuffer[12] = (ulValue >> 16) & 0xff;
    pucBuffer[13] = (ulValue >>  8) & 0xff;
    pucBuffer[14] = (ulValue >>  0) & 0xff;
    pucBuffer[15] = ucGetWPOfColWAL(2);
      break;

      case 1:
      ulValue = ulGetIDOfColWAL(3);
    pucBuffer[1] = (ulValue >> 24) &0xff;
    pucBuffer[2] = (ulValue >> 16) &0xff;
    pucBuffer[3] = (ulValue >>  8) &0xff;
    pucBuffer[4] = (ulValue >>  0) &0xff;
    pucBuffer[5] = ucGetWPOfColWAL(3);
      ushValue = ushGetWheelUnitMissingCounterWUM(0);
    pucBuffer[6] = (ushValue >>  8) & 0xff;
    pucBuffer[7] = (ushValue >>  0) & 0xff;
      ucMessageNr = 0;
      ucRetVal = 0;
      break;
   }

   return ucRetVal;

}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

