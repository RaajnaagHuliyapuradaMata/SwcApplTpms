/******************************************************************************/
/* File   : HS_Inaktivereignis.c                                              */
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
#include "HS_InaktivereignisX.h"

#include "DatamanagerX.h"
#include "EeCommonBlockX.h"
#include "EeDiagBlockX.h"
#include "SecondaryDtcX.h"
#include "WuMonitoringX.h"
#include "NwMonitoringX.h"
#include "state_BZX.h"

#ifndef TESSY
#ifdef WIN32
#include "assert.h"
#endif
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cErrorNoAction  0x00
#define cErrorNotActive 0x01
#define cErrorUnknown   0x03

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8  ucStatDatumText[8];
   uint8  ucStatUhrzeitText[8];
   uint32 ulStatKilometerstandWert;
   uint8  ucStatInternerFehlercode;
   uint8  ucStatZaehlerInaktivWert;
}tHsInaktivereignisType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static strIeFiFo tIEFifo[cMaxSizeIeFiFo];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static uint8 SaveInaktivereignisDS(Rte_Instance self, uint8 ucErrorCode);
static void  IeFiFoShiftDS(Rte_Instance self);

static uint8 SaveInaktivereignisDS(Rte_Instance self, uint8 ucErrorCode){
   Rdci_UHRZEIT_DATUM_Type timeDate;
   Rdci_MILE_KM_Type mileKm;
   uint8 cTempBuffer[9];
   uint8 cData[cSizeInaktivereignis];
   uint8 i;
   uint8 ucPosType = 0;
   uint8 ucRetVal = 0xff;
   uint8 ucCounterInactive;

#ifndef TESSY
#ifdef WIN32
      assert(sizeof(ImpTypeArrayDcm_RdcHsInaktivereignisReadDataType) == (3 * cSizeInaktivereignis));
#endif
#endif

   ucCounterInactive = GetHsInaktivereignis_1_CounterEE(self);
   if(ucCounterInactive == 0xff){
      ucCounterInactive = 1;
   }
   else if(ucCounterInactive < 0xfe){
      ucCounterInactive++;
   }
   else{}

   SetSecondaryErrorSCD(cSecondaryRdciAusfall);

   if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE){
      ucPosType = 4;
   }
   else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE){
      ucPosType = 4;
   }
   else{
      ucPosType = 0;
   }

   switch(ucErrorCode){
      case (uint8)cDtcWuMuteFl:
      case (uint8)cDtcWuDefectFl:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_FL<<ucPosType);
      break;

      case (uint8)cDtcWuMuteFr:
      case (uint8)cDtcWuDefectFr:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_FR<<ucPosType);
      break;

      case (uint8)cDtcWuMuteRl:
      case (uint8)cDtcWuDefectRl:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_RL<<ucPosType);
      break;

      case (uint8)cDtcWuMuteRr:
      case (uint8)cDtcWuDefectRr:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_RR<<ucPosType);
      break;

      case (uint8)cDtcUnspecifiedWuMute:
      case (uint8)cDtcUnspecifiedWfcDefect:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_NO_POS);
      break;

      default:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciAusfall, RDC_TAB_POSITION_SENSOR_INVALID);
      break;
   }

   timeDate = GETtTimeDateEE(self);
  GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i] = cTempBuffer[i];
   }
  GetTimeStringDM(timeDate.DISP_HR, timeDate.DISP_MN, timeDate.DISP_SEC, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i+8] = cTempBuffer[i];
   }

  mileKm = GETulMileKmEE(self);

  cData[16] = (uint8)((mileKm >> 24) & 0xffU);
  cData[17] = (uint8)((mileKm >> 16) & 0xffU);
  cData[18] = (uint8)((mileKm >> 8) & 0xffU);
  cData[19] = (uint8)(mileKm & 0xffU);
  cData[20] = ucErrorCode;
  cData[21] = ucCounterInactive;

   for(i=0; i<sizeof(cData); i++){
    PutHsInaktivereignis_3_EE(self, GetHsInaktivereignis_2_EE(self, i), i);
   }

   for(i=0; i<sizeof(cData); i++){
    PutHsInaktivereignis_2_EE(self, GetHsInaktivereignis_1_EE(self, i), i);
   }

   for(i=0; i<sizeof(cData); i++){
    PutHsInaktivereignis_1_EE(self, cData[i], i);
   }

   ucRetVal = 0;
   return ucRetVal;
}

void ReadInaktivereignisDS(Rte_Instance self, uint8* paucData){
   uint8 i;

   for(i = 0; i < cSizeInaktivereignis; i++){
    paucData[i] = GetHsInaktivereignis_1_EE(self, i);
   }

   for(i = 0; i < cSizeInaktivereignis; i++){
    paucData[cSizeInaktivereignis + i] = GetHsInaktivereignis_2_EE(self, i);
   }

   for(i = 0; i < cSizeInaktivereignis; i++){
    paucData[(2 * cSizeInaktivereignis) + i] = GetHsInaktivereignis_3_EE(self, i);
   }
}

void InitIeFiFoDS(Rte_Instance self){
  GetIeFiFoFromNvmEE(self, tIEFifo);
}

void IeFiFoWriteEntryDS(Rte_Instance self, uint8 ucErrorNumber){
   uint8 i = 0;

  while ((tIEFifo[i].ucErrorNumber != cIeFiFoEmpty) && (i < cMaxSizeIeFiFo)){
      if(tIEFifo[i].ucErrorNumber == ucErrorNumber){
      i = cMaxSizeIeFiFo;
      }
      else{
      i++;
      }
   }

   if(i < cMaxSizeIeFiFo){
    tIEFifo[i].ucErrorNumber = ucErrorNumber;
    tIEFifo[i].ucIeSent = 0;
    PutIeFiFoToNvmEE(self, tIEFifo);
   }
}

static void IeFiFoShiftDS(Rte_Instance self){
   uint8 i;

   for(i = 0; i < (cMaxSizeIeFiFo - 1); i++){
    tIEFifo[i].ucErrorNumber = tIEFifo[i+1].ucErrorNumber;
    tIEFifo[i].ucIeSent = tIEFifo[i+1].ucIeSent;
   }
   tIEFifo[cMaxSizeIeFiFo-1].ucErrorNumber = cIeFiFoEmpty;
   tIEFifo[cMaxSizeIeFiFo-1].ucIeSent = cIeFiFoEmpty;

   PutIeFiFoToNvmEE(self, tIEFifo);
}

void ProcessIeFiFoDS(Rte_Instance self){
   uint8 ucErrorStatus = cErrorNoAction;
   switch(tIEFifo[0].ucErrorNumber){
      case (uint8)cDtcWuMuteFl:                     if(bGetWheelUnitErrorWUM(cAllocWuMuteFl) == FALSE)                   { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuMuteFr:                     if(bGetWheelUnitErrorWUM(cAllocWuMuteFr) == FALSE)                   { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuMuteRl:                     if(bGetWheelUnitErrorWUM(cAllocWuMuteRl) == FALSE)                   { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuMuteRr:                     if(bGetWheelUnitErrorWUM(cAllocWuMuteRr) == FALSE)                   { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcUnspecifiedWuMute:            if(bGetWheelUnitErrorWUM(cAllocUnspecifiedWuMute) == FALSE)          { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuDefectFl:                   if(bGetWheelUnitErrorWUM(cAllocWuDefectFl) == FALSE)                 { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuDefectFr:                   if(bGetWheelUnitErrorWUM(cAllocWuDefectFr) == FALSE)                 { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuDefectRl:                   if(bGetWheelUnitErrorWUM(cAllocWuDefectRl) == FALSE)                 { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcWuDefectRr:                   if(bGetWheelUnitErrorWUM(cAllocWuDefectRr) == FALSE)                 { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcUnspecifiedWfcDefect:         if(bGetWheelUnitErrorWUM(cAllocUnspecifiedWfcDefect) == FALSE)       { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcAutoLearningFailed:           if(bGetWheelUnitErrorWUM(cAllocAutoLearningFailed) == FALSE)         { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcGatewayOrAntennaError:        if(bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError) == FALSE)      { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcGatewayOrAntennaError2ndFBD:  if(bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError) == FALSE)      { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcGatewayOrAntennaErrorAllFBD:  if(bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError) == FALSE)      { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcInputMissing:                 if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_MsgMissing) == FALSE)    { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcInputInvalid:                 if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_SignalError) == FALSE)   { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcInputAliveError:              if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_AliveError) == FALSE)    { ucErrorStatus = cErrorNotActive; } break;

      case (uint8)cDtcDataPackageError1stFBD:
      case (uint8)cDtcDataPackageError2ndFBD:
      case (uint8)cDtcDataPackageErrorAllFBD:
      if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_MsgMissing) == TRUE)       { ucErrorStatus = cErrorNoAction; }
      else if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_SignalError) == TRUE) { ucErrorStatus = cErrorNoAction; }
      else if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_AliveError) == TRUE)  { ucErrorStatus = cErrorNoAction; }
      else                                                                    { ucErrorStatus = cErrorNotActive; }
      break;

      case (uint8)cDtcRdciRfExternalInterference:   if(bGetWheelUnitErrorWUM(cAllocRdciRfExternalInterference) == FALSE) { ucErrorStatus = cErrorNotActive; } break;
      case (uint8)cDtcSpeedSignalFailure:
       if      (bGetNetworkErrorNWM(cNetwork_V_VEH_SigQualifError) == TRUE)  { ucErrorStatus = cErrorNoAction; }
       else if(bGetNetworkErrorNWM(cNetwork_V_VEH_MsgMissing) == TRUE)      { ucErrorStatus = cErrorNoAction; }
       else if(bGetNetworkErrorNWM(cNetwork_V_VEH_AliveError) == TRUE)      { ucErrorStatus = cErrorNoAction; }
       else if(bGetNetworkErrorNWM(cNetwork_V_VEH_CrcError) == TRUE)        { ucErrorStatus = cErrorNoAction; }
       else                                                                  { ucErrorStatus = cErrorNotActive; }
       break;

      case cIeFiFoEmpty:
       ucErrorStatus = cErrorNoAction;
       break;

      default:
       ucErrorStatus = cErrorUnknown;
       break;
   }

   if(cErrorUnknown == ucErrorStatus){
    IeFiFoShiftDS(self);
   }
   else{
      if(0 == tIEFifo[0].ucIeSent){
      (void)SaveInaktivereignisDS(self, tIEFifo[0].ucErrorNumber);
      tIEFifo[0].ucIeSent = 1;
      PutIeFiFoToNvmEE(self, tIEFifo);
      }
      if(ucErrorStatus == cErrorNotActive){
      IeFiFoShiftDS(self);
      }
   }
}

void ClearIeFifoDS(Rte_Instance self){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cMaxSizeIeFiFo; ucLoop++){
    tIEFifo[ucLoop].ucErrorNumber = cIeFiFoEmpty;
    tIEFifo[ucLoop].ucIeSent = cIeFiFoEmpty;
   }
   PutIeFiFoToNvmEE(self, tIEFifo);
}

uint8 GetCurrentInactiveReasonDS(void){
   if(tIEFifo[0].ucErrorNumber == cIeFiFoEmpty){
      return cDtcInvalid;
   }
   else{
      return tIEFifo[0].ucErrorNumber;
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

