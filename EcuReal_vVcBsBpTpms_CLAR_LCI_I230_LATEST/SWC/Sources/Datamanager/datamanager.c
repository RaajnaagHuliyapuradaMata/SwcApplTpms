#include "datamanager.h"
#include "CodingDataX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "state_zkX.h"
#include "BreakTireX.h"
#include "CcmX.h"
#include "USWarn_IfX.h"
#include "WnTypePar.h"
#include "eRFS_X.h"
#include "RID_X.h"
#include "walloc_managerX.h"
#include "WallocX.h"
#include "WarningLampX.h"
#include "InfoTyreX.h"
#include "EeWarnStatusBlockX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeDiagBlockX.h"
#include "EeErfsBlockX.h"
#include "EeErfsEcoBlockX.h"
#include "EeErfsTsaBlockX.h"
#include "EeRidQrBlockX.h"
#include "EeZomBlockX.h"
#include "EeGlobalFunctionsX.h"
#include "BandmodeX.h"
#include "InitializationX.h"
#include "WuMonitoringX.h"
#include "NwMonitoringX.h"
#include "FBD_ManagerX.h"
#include "HS_WarnereignisX.h"
#include "HS_KalibrierereignisX.h"
#include "TAmbFiltX.h"
#include "StatusbarX.h"
#include "FillingDetectX.h"
#include "StatusReLesenDruckcodierungX.h"
#include "SecondaryDTCX.h"
#include "SeasRcpAdjX.h"
#include "SpeedCcmX.h"

#define TELEGRAM_QUEUE_SIZE 10
#define WIDTH_IX         (uint8)0
#define SIDEREL_IX       (uint8)1
#define DIA_SPEED_IX     (uint8)2
#define LOAD_SEAS_IX     (uint8)3
#define PRESS_BYTE_1_IX  (uint8)4
#define PRESS_BYTE_2_IX  (uint8)5
#define PRESS_BYTE_3_IX  (uint8)6

static uint8                  ucRePckgIdDM[cAnzRad]           = { cInvalidTelType,            cInvalidTelType,            cInvalidTelType,            cInvalidTelType           };
static uint32                 ulReIdDM[cAnzRad]               = { cInvalidREid,               cInvalidREid,               cInvalidREid,               cInvalidREid              };
static uint8                  ucReSuppIdDM[cAnzRad]           = { cInvalidREsuppId,           cInvalidREsuppId,           cInvalidREsuppId,           cInvalidREsuppId          };
static PhySensorTyrePresType  ucRePressureRelDM[cAnzRad]      = { cInvalidREpressure,         cInvalidREpressure,         cInvalidREpressure,         cInvalidREpressure        };
static PhySensorTyreTempType  scReTemperatureCentDM[cAnzRad]  = { cInvalidREtemperature,      cInvalidREtemperature,      cInvalidREtemperature,      cInvalidREtemperature     };
static uint8                  ucRePalLookBackTimeDM[cAnzRad]  = { cInvalidRePalLookBackTime,  cInvalidRePalLookBackTime,  cInvalidRePalLookBackTime,  cInvalidRePalLookBackTime };
static uint16                 ushRePalStatusDM[cAnzRad]       = { cInvalidRePalStatus,        cInvalidRePalStatus,        cInvalidRePalStatus,        cInvalidRePalStatus       };
static uint8                  ucTelRssiLevelDM[cAnzRad]       = { cInvalidRSSIsum,            cInvalidRSSIsum,            cInvalidRSSIsum,            cInvalidRSSIsum           };
static uint8                  ucReBatteryLevel[cAnzRad]       = { cInvalidBatteryLevel,       cInvalidBatteryLevel,       cInvalidBatteryLevel,       cInvalidBatteryLevel      };

static uint8 ucSetLevelDW[cAnzRad][ucMaxWarnTypeWNc]   = {
      {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
};

static uint8 ucResetLevelDW[cAnzRad][ucMaxWarnTypeWNc] = {
      {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure, cInvalidREpressure}
};

static InfoTyrePresType ushTarPTyrDisplayValDM[cAnzRad] = {TAR_P_TYR_SignalUngueltig, TAR_P_TYR_SignalUngueltig, TAR_P_TYR_SignalUngueltig, TAR_P_TYR_SignalUngueltig};
static tRdcDataQueue    RdcDataQueue[TELEGRAM_QUEUE_SIZE];
static uint8            ucStWheelTypeChangeDet[2] = {StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar,StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar };
static uint8            ucStWheelTypeChangePos[2] = {StatusWheelTypeChangePosition_Position_Unbekannt,StatusWheelTypeChangePosition_Position_Unbekannt };
static uint8            ucRfBgNoiseLevel         = 0xff;
static uint32           ulStopTime               = 0;
static boolean          bStbMBSyncState          = FALSE;
static uint8            ucRxEventCounter         = 0;
static uint8            ucExtTemperatureTimer    = 0;
static uint8            ucRdcQueueWritePos       = 0xFFU;
static uint8            ucRdcQueueReadPos        = 0xFFU;
static uint32           ulRelTimeSinceSysStartDM = 0xffffffffu;

static tProcIdBufType ProcIdBuf[TELEGRAM_QUEUE_SIZE] = {
      {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
   ,  {cInvalidREid,cReIdProcBufTimeLimit}
};

static uint8 ucReIdBufTimeCt = 0x00;

uint8 SetParkenWohnenFahrenDM(Rdci_CON_VEH_Type tPWF){
   uint8 retVal = ePWFInvalid;
   static uint8 ucLastCond = ST_CON_VEH_Parken_BN_iO;
   if(tPWF.ST_CON_VEH != ucGetStatusConditionVehicleFZZ()){
      PutStatusConditionVehicleFZZ( (uint8) tPWF.ST_CON_VEH);
      if(ucLastCond < ST_CON_VEH_Standfunktionen_Kunde_nicht_im_FZG){
              if(ST_CON_VEH_Standfunktionen_Kunde_nicht_im_FZG == tPWF.ST_CON_VEH){retVal = eParkenStandfunktion;}
         else if(ST_CON_VEH_Wohnen                             == tPWF.ST_CON_VEH){retVal = eParkenWohnen;}
         else{}
      }
      else if(ucLastCond < ST_CON_VEH_Wohnen){
              if(ST_CON_VEH_Wohnen == tPWF.ST_CON_VEH)                                                         {retVal = eParkenWohnen;}
         else if((ST_CON_VEH_Parken_BN_iO == tPWF.ST_CON_VEH) || (ST_CON_VEH_Parken_BN_niO == tPWF.ST_CON_VEH)){retVal = eStandFktParken;}
         else{}
      }
      else if(ST_CON_VEH_Wohnen == ucLastCond){
              if(tPWF.ST_CON_VEH < ST_CON_VEH_Wohnen){retVal = eWohnenParken;}
         else if(tPWF.ST_CON_VEH > ST_CON_VEH_Wohnen){retVal = eWohnenFahren;}
         else{}
      }
      else{
         if(ST_CON_VEH_Wohnen == tPWF.ST_CON_VEH){
            retVal = eFahrenWohnen;
         }
      }
      ucLastCond = tPWF.ST_CON_VEH;
   }
   return retVal;
}

void SetExternalTemperatureDM(Rte_Instance self, uint8 tempEx){
   sint8 sctemperature;
   sctemperature = ((sint8)(tempEx >> 1)) - 40;
   SETOutdoorTemperatureFZZ(sctemperature);
   if(30 == ucExtTemperatureTimer){
      PUTscTAmbValEE(self, sctemperature);
   }
}

void ExternalTemperatureTimerTickDM(void){
   uint16 ushSpeed;
   ushSpeed = GETushSpeedFZZ();
   if((0xffffU != ushSpeed) && (ushSpeed >= 20)){
      if(ucExtTemperatureTimer < 30){
         ucExtTemperatureTimer++;
      }
   }
   else{
      ucExtTemperatureTimer = 0;
   }
}

void SetExternalPressureDM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type pressEx, uint8 ucError){
   uint16 ushPrs;
   uint8  ucPrs;
   uint8  ucState;
   ucState = GETucAipGpsStateEE(self);
   ucState |= cAGS_AipSigRec;
   if(cNoError == ucError){
      ucState |= cAGS_AipSigValid;
      PUTushGpsTioTicksEE(self, 0);
      ucState &= (uint8) ~cAGS_GpsAltSigTio;
      ushPrs = ((uint16) pressEx * 2) + (uint16) 598;
      ucPrs = ChangeHpaTo25mBar(ushPrs);
      PUTucPAmbValEE(self, ucPrs);
   }
   else{
      pressEx = cInvalidREpressure;
      ucState &= (uint8) ~cAGS_AipSigValid;
   }
   PUTucAipGpsStateEE(self, ucState);
   PUTucAipEngDrvEE(self, pressEx);
}

void SetGNSSPositionAltitudeDM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude, uint8 ucError){
   uint16 ushPrs;
   uint8  ucPrs;
   uint8  ucState;
   sint16 sshAltMeter;

   ucState = GETucAipGpsStateEE(self);
   ucState |= cAGS_GpsAltSigRec;
   if(ucError == cNoError){
      ucState |= cAGS_GpsAltSigValid;
      if((ucState & cAGS_AipSigValid) != cAGS_AipSigValid){
         if((ucState & cAGS_GpsAltSigTio) != cAGS_GpsAltSigTio){
            sshAltMeter = (sint16) ((GNSSPositionAltitude + 5) / 10) - 1000;
            if(sshAltMeter < 0){
               sshAltMeter = 0;
            }
            if(sshAltMeter < (sint16) cAGS_2500Mtr){
               ushPrs = cAGS_Pat0Mtr - (((cAGS_Pat0Mtr - cAGS_Pat2500Mtr) * 4 * (uint16) sshAltMeter) / 10000);
               ucPrs  = ChangeHpaTo25mBar(ushPrs);
               PUTucPAmbValEE(self, ucPrs);
            }
            else{
               ushPrs = cAGS_Pat2500Mtr - (((cAGS_Pat2500Mtr - cAGS_Pat5000Mtr) * 4 * ((uint16) sshAltMeter - cAGS_2500Mtr)) / 10000);
               ucPrs  = ChangeHpaTo25mBar(ushPrs);
               PUTucPAmbValEE(self, ucPrs);
            }
         }
      }
   }
   else{
      ucState &= (uint8) ~cAGS_GpsAltSigValid;
      if((ucState & cAGS_GpsAltSigTio) != cAGS_GpsAltSigTio){
         PUTushGpsTioTicksEE(self, cAGS_TioTimerTicksSec);
         ucState |= cAGS_GpsAltSigTio;
      }
   }
   PUTucAipGpsStateEE(self, ucState);
   PUTushPositionAltitudeEE(self, GNSSPositionAltitude);
}

void SetGNSSErrorAltitudeMetersDM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters, uint8 ucError){
   uint8  ucState;
   uint16 ushTimerTicks;

   ucState = GETucAipGpsStateEE(self);
   ushTimerTicks = GETushGpsTioTicksEE(self);
   ucState |= cAGS_GpsErrAltSigRec;
   if(cNoError == ucError){
      ucState |= cAGS_GpsErrAltSigValid;
      if(GNSSErrorAltitudeMeters > cAGS_AccuracyThresDm){
         if(cAGS_GpsAltSigTio != (ucState & cAGS_GpsAltSigTio)){
            ushTimerTicks = cAGS_TioTimerTicksSec;
            ucState |= cAGS_GpsAltSigTio;
         }
      }
      else{
         if(cAGS_GpsAltSigValid == (ucState & cAGS_GpsAltSigValid)){
            ushTimerTicks = 0;
            ucState &= (uint8) ~cAGS_GpsAltSigTio;
         }
      }
   }
   else{
      ucState &= (uint8) ~cAGS_GpsErrAltSigValid;
      if(cAGS_GpsAltSigTio != (ucState & cAGS_GpsAltSigTio)){
         ushTimerTicks = cAGS_TioTimerTicksSec;
         ucState |= cAGS_GpsAltSigTio;
      }
   }
   PUTushGpsTioTicksEE(self, ushTimerTicks);
   PUTucAipGpsStateEE(self, ucState);
   PUTushErrorAltitudeMetersEE(self, GNSSErrorAltitudeMeters);
}

void SetUnitMileDM(Rte_Instance self, uint8 unitMile){
   if(
         (eMILEAGE_UNIT_MEILEN    == unitMile)
      || (eMILEAGE_UNIT_KILOMETER == unitMile)
   ){
      PUTucUnMileEE(self, (tMileageUnitType) unitMile);
   }
}

void SetUnitTempDM(Rte_Instance self, uint8 unitTemp){
   if(
         (eTEMPERATURE_UNIT_FAHRENHEIT == unitTemp)
      || (eTEMPERATURE_UNIT_CELSIUS    == unitTemp)
   ){
      PUTucUnTempEE(self, (tTemperatureUnitType) unitTemp);
   }
}

void SetUnitAipDM(Rte_Instance self, uint8 unitAip){
   if(
         (ePRESSURE_UNIT_PSI == unitAip)
      || (ePRESSURE_UNIT_KPA == unitAip)
      || (ePRESSURE_UNIT_BAR == unitAip)
   ){
      PUTucUnAipEE(self, (tPressureUnitType) unitAip);
   }
}

void SetTimeDateDM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type currentTimeDate){
   PUTtTimeDateEE(self, currentTimeDate);
}

void SetMileageDM(Rte_Instance self, Rdci_MILE_KM_Type mileKm){
   PUTulMileKmEE(self, mileKm);
}

void SetStopTimeDM(Rte_Instance self, StbMB_SystemTimeType currentTimestamp){
   static uint8 ucStateMachine = cInit;
   static uint8 ucInitTimeout = 4;
   uint8  ucTempVar;
   switch(ucStateMachine){
      case cInit:
         if(0xffffffffu != currentTimestamp.systemTicks){
            ulStopTime = currentTimestamp.systemTicks - GETulTimestampEE(self);
            if(ulStopTime >= cLONG_PARK_TIME){
               SetBitFahrzeugzustandFZZ(cLONG_PARK);
            }
            InitRDCiFunctionsPartTwoDM(self);
            ucStateMachine = cCarStop;
         }
         else{
            ucInitTimeout--;
            if(0 == ucInitTimeout){
               ulStopTime = cLONG_PARK_TIME;
               SetBitFahrzeugzustandFZZ(cLONG_PARK);
               InitRDCiFunctionsPartTwoDM(self);
               ucStateMachine = cCarStop;
            }
         }
         break;

      case cCarStop:
         if(TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
            ucStateMachine = cCarDrive;
         }
         else{
            if(0xffffffffu == currentTimestamp.systemTicks){
              ulStopTime++;
            }
            else{
              ulStopTime = currentTimestamp.systemTicks - GETulTimestampEE(self);
            }
            if(FALSE == bGetBitFahrzeugzustandFZZ(cLONG_PARK)){
                if(ulStopTime >= cLONG_PARK_TIME){
                  SetBitFahrzeugzustandFZZ(cLONG_PARK);
                  StartLearnLocateWAM(self);
                  InitRidDataRID(self);
                  ucTempVar = GETTyreSelectionBckgrdEE(self);
                  ucTempVar |= GETTyreSelectionActiveEE(self);
                  if(0 != ucTempVar){
                     InitRatedValuesDM(self);
                  }
               }
            }
         }
         break;

      case cCarDrive:
         PUTulTimestampEE(self, currentTimestamp.systemTicks);
         if(FALSE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
         ucStateMachine = cCarStop;
         StartFillingDetectionFID(self);
         }
         break;

      default: break;
   }
}

void    SetSysTimeDM         (uint32 ulSysTime){ulRelTimeSinceSysStartDM = ulSysTime;}
uint32  ulGetSysTimeDM       (void)            {return ulRelTimeSinceSysStartDM;}
void    SetStbMBSyncStateDM  (boolean bSync)   {bStbMBSyncState = bSync;}
boolean bGetStbMBSyncStateDM (void)            {return bStbMBSyncState;}
uint32  ulGetStopTimeDM      (void)            {return ulStopTime;}
void    ClearStopTimeDM      (void)            {ulStopTime = 0;}

void IncreaseRdcEventCounterDM(void){
   if(ucRxEventCounter < 255){ucRxEventCounter++;}
   else                      {ucRxEventCounter = 0;}
}

uint8 ucGetRdcEventCounterDM(void){return ucRxEventCounter;}

uint8 ucSetRdcDataDM(const ImpTypeRecCddRdcData* data, uint8 ucType){
   static boolean bLockPosition = FALSE;
   uint8 queueFillStatus = 0;

   if(0xFFU == ucRdcQueueWritePos){
      ucRdcQueueWritePos = 0;
      bLockPosition = FALSE;
      queueFillStatus = 1;
   }
   else{
      if(((ucRdcQueueWritePos + 1) % TELEGRAM_QUEUE_SIZE) == ucRdcQueueReadPos){
         bLockPosition = TRUE;
         queueFillStatus = TELEGRAM_QUEUE_SIZE;
      }
      else{
         ucRdcQueueWritePos++;
         ucRdcQueueWritePos %= TELEGRAM_QUEUE_SIZE;
         bLockPosition = FALSE;
         if(0xFFU == ucRdcQueueReadPos){
            queueFillStatus = ucRdcQueueWritePos;
         }
         else{
            if(ucRdcQueueWritePos > ucRdcQueueReadPos){queueFillStatus = ucRdcQueueWritePos - ucRdcQueueReadPos;}
           else                                       {queueFillStatus = TELEGRAM_QUEUE_SIZE - (ucRdcQueueReadPos - ucRdcQueueWritePos);}
         }
      }
   }
   if(FALSE == bLockPosition){
      RdcDataQueue[ucRdcQueueWritePos].tRdcData      = *data;
      RdcDataQueue[ucRdcQueueWritePos].ucType        = ucType;
      RdcDataQueue[ucRdcQueueWritePos].ucWaitingTime = 1;
   }
   return queueFillStatus;
}

uint8 ucGetRdcDataDM(ImpTypeRecCddRdcData* data, uint8* ucType){
   uint8 ucReturnValue = cQueueBusy;
   boolean bReadQueueData = TRUE;
   if(0xFFU != ucRdcQueueWritePos){
      if(0xFFU == ucRdcQueueReadPos){
         if(RdcDataQueue[0].ucWaitingTime <= cTEL_WAIT_TIME){bReadQueueData    = FALSE;}
         else                                               {ucRdcQueueReadPos = 0;}
      }
      else{
              if(ucRdcQueueReadPos == ucRdcQueueWritePos)                                                    {bReadQueueData = FALSE;}
         else if(RdcDataQueue[(ucRdcQueueReadPos + 1) % TELEGRAM_QUEUE_SIZE].ucWaitingTime <= cTEL_WAIT_TIME){bReadQueueData = FALSE;}
         else{
            ucRdcQueueReadPos++;
            ucRdcQueueReadPos %= TELEGRAM_QUEUE_SIZE;
         }
      }
      if(TRUE == bReadQueueData){
         *data = RdcDataQueue[ucRdcQueueReadPos].tRdcData;
         *ucType = RdcDataQueue[ucRdcQueueReadPos].ucType;
         RdcDataQueue[ucRdcQueueReadPos].ucWaitingTime = 0;
         IncreaseRdcEventCounterDM();
         ucReturnValue = cRdcDataAvailable;
      }
   }
   return ucReturnValue;
}

void CopyPressAndTempFromZOMDM(Rte_Instance self){
   uint32                ulREID;
   uint8                 ZomIx = cSumWE;
   uint8                 ucHisCol;
   uint8                 ucWheelPos;
   PhySensorTyrePresType ucPhyPress;
   PhySensorTyreTempType scPhyTemp;
   for(ucHisCol = 0; ucHisCol < cAnzRad; ucHisCol++){
      ulREID = ulGetIDOfColWAL(ucHisCol);
      ZomIx  = ucGetZOMPosOfID(&ulREID);
      if(ZomIx < cSumWE){
         ucWheelPos = ucGetWPOfColWAL(ucHisCol);
         if(ucWheelPos >= cAnzRad){
            ucWheelPos = cRadPosUndef;
         }
   (void)ucConvAkAbsPressureInRelDM  (ucGetZomPressure(ZomIx),    &ucPhyPress,      GETucPAmbValEE(self));
         PutRePressureRelDM          (ucHisCol,                   ucPhyPress);
   (void)ucConvAkTemperatureInCentDM (ucGetZomTemperature(ZomIx), &scPhyTemp);
         PutReTemperatureCentDM      (ucHisCol,                   scPhyTemp);
         PUTucLastWuPressureEE       (self,                       ucPhyPress,       ucHisCol);
         PUTscLastWuTemperatureEE    (self,                       scPhyTemp,        ucHisCol);
         CheckTirePressureDM         (self,                       ucHisCol,         ucWheelPos, ucGetRePressureRelDM(ucHisCol), scGetReTemperatureCentDM(ucHisCol));
         NotificationITY             (self,                       cNotifyTelRecITY, ucHisCol);
      }
   }
}

void RdcDataWaitingTimerTickDM(void){
   for(uint8 i = 0; i < TELEGRAM_QUEUE_SIZE; i++){
      if(RdcDataQueue[i].ucWaitingTime > 0){
         RdcDataQueue[i].ucWaitingTime ++;
         if(RdcDataQueue[i].ucWaitingTime >= (cTEL_WAIT_TIME + 1)){
            RdcDataQueue[i].ucWaitingTime = (cTEL_WAIT_TIME + 1);
         }
      }
   }
}

void ClearLastReceivedReDataArraysDM(void){
   for(uint8 i = 0; i < cAnzRad; i++){
      ucRePckgIdDM[i]          = cInvalidTelType;
      ulReIdDM[i]              = cInvalidREid;
      ucReSuppIdDM[i]          = cInvalidREsuppId;
      ucRePressureRelDM[i]     = cInvalidREpressure;
      scReTemperatureCentDM[i] = cInvalidREtemperature;
      ucRePalLookBackTimeDM[i] = cInvalidRePalLookBackTime;
      ushRePalStatusDM[i]      = cInvalidRePalStatus;
      ucTelRssiLevelDM[i]      = cInvalidRSSIsum;
      ucReBatteryLevel[i]      = cInvalidBatteryLevel;
   }
}

void InitRDCiEepromDM(Rte_Instance self){
   uint8 ucState;
   if(cNvmInitialized != GETucCommonBlockInitializeEE(self)){
      InitCommonBlockEE(self);
   }
   else{
      ucState = GETucAipGpsStateEE(self);
      ucState &= (uint8) ~(cAGS_AipSigRec | cAGS_GpsAltSigRec | cAGS_GpsErrAltSigRec);
      PUTucAipGpsStateEE(self, ucState);
   }
   if(cNvmInitialized != GETucErfsInitializerEE(self)){
      InitErfsTsaBlockEE  (self);
      InitRidQrBlock1u2EE (self);
      InitErfsBlockEE     (self);
   }
   if(cNvmInitialized != GETucDiagBlock1InitializeEE      (self)){InitDiagBlock1EE      (self);}
   if(cNvmInitialized != GETucDiagBlock2InitializeEE      (self)){InitDiagBlock2EE      (self);}
   if(cNvmInitialized != GETucWarnStatusBlockInitializeEE (self)){InitWarnStatusBlockEE (self);}
   if(cNvmInitialized != GETucHistoryBlockInitializeEE    (self)){InitZoHistoryBlockEE  (self);}
   if(cNvmInitialized != GETucZomBlock1InitializeEE(self)){
      InitZomBlock1EE(self);
      InitZomBlock2EE(self);
   }
   if(cNvmInitialized != GETucZomBlock2InitializeEE(self)){
      InitZomBlock1EE(self);
      InitZomBlock2EE(self);
   }
   CheckMemoryReserveEE(self);
}

void InitRDCiFunctionsPartOneDM(Rte_Instance self){
   InitBM(GETushBandmodeStateEE(self));
   InitBZ(self, TRUE);
   InitFZZ();
   InitZK();
   InitTAF(self);
   InitSRA(self);
   InitSCC();
   InitWUM(self);
   InitNWM(self);
   InitIeFiFoDS(self);
   InitSecondaryDtcFiFoSCD();
   InitRatedValuesDM(self);
   InitUSWIF(self);
   InitFastaWarnEventsDS(self);
   for(uint8 ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      PutRePressureRelDM     (ucLoop, GETucLastWuPressureEE    (self, ucLoop));
      PutReTemperatureCentDM (ucLoop, GETscLastWuTemperatureEE (self, ucLoop));
   }
   InitITY(self);
   InitBT(self);
   InitCCM();
   InitWL();
   InitSBR(self);
   InitRidDataRID(self);
   InitStatusReLesenDruckcodierungDS();
   if(TRUE == bGetBandmodeBM()){
           if(TRUE == bGetStateBitBM(cushTestEigenradFahrtBM       )){SetWumActivityStatusWUM(self, cWUM_BM_DIENST_RUN, cNO_EVALUATION);}
      else if(TRUE == bGetStateBitBM(cushTestEigenradFahrtNoSpeedBM)){SetWumActivityStatusWUM(self, cWUM_BM_DIENST_RUN, cNO_EVALUATION);}
      else                                                           {SetWumActivityStatusWUM(self, cWUM_DISABLED,      cNO_EVALUATION);}
   }
   else                                                              {SetWumActivityStatusWUM(self, cWUM_ENABLED,       cNO_EVALUATION);}
}

void InitRDCiFunctionsPartTwoDM(Rte_Instance self){
   if(TRUE == GETTyreSelectionActiveEE(self)){
    ContinueSBR(self);
   }
   if(TRUE == bGetBitFahrzeugzustandFZZ(cLONG_PARK)){
    StartLearnLocateWAM(self);
    InitRidDataRID(self);
   }
   else{
      if(FALSE == bGetBitBetriebszustandBZ(cZO_FINISH)){
      if(FALSE == bGetBitBetriebszustandBZ(cZO_TIMEOUT)){
        WatoRunWAM(self, cWatoContinue);
      }
      }
   }
}

void InitAfterKl15OnDM(void){
   StartCycleCCM();
}

void InitAfterKl15OffDM(void){
}

void CyclicRDCiFunctionDM(Rte_Instance self){
   TimerWT(self, ucCountc);
   TransferWarnStateToTpmsMsgManOnCycEventDM(self);
   SetBreakTireStateBT(self);
   MainFunctionCCM(self);
   MainFunctionWL();
   MainFunctionITY(self);
}

uint8 ucNewReDataDM(Rte_Instance self, ImpTypeRecCddRdcData tReData){
   uint8  ucRet = cRetOk;
   uint8  ucWarnType;
   uint8  ucSetLevel, ucResetLevel;
   uint8  ucWheelPos;
   uint8  ucSlotNo;
   uint32 ulReID = cInvalidREid;
   PhySensorTyrePresType ucPres = cInvalidREpressure;
   PhySensorTyreTempType scTemp = cInvalidREtemperature;
   uint8  ucPSollKalt;
   sint8  scTSollKalt;
   uint8  ucPSollWarm;
   sint8  scTSollWarm;
   uint16 ushMSoll_l;
   uint8  ucEnvP_l;
   uint8  i;
   uint8 ucBattState = cBATTERY_STATUS_UNKNOWN;
   uint8 ucPresState = cPresSensorOk;
   uint8 ucSNR;
   ulReID      = tReData.TYR_ID + ((uint32) tReData.SUPP_ID << 28);
   ucSlotNo    = ucGetColOfID((const uint32*) &ulReID);
   ucEnvP_l    = GETucPAmbValEE(self);
   ucPresState = ucConvAkAbsPressureInRelDM(tReData.RDC_DT_1, &ucPres, ucEnvP_l);
   (void) ucConvAkTemperatureInCentDM(tReData.RDC_DT_2, &scTemp);
   ucBattState = ucCalcBatteryLevelDM((const ImpTypeRecCddRdcData*) &tReData);
   if(ucSlotNo < cAnzRad){
      ucWheelPos = ucGetWPOfColWAL(ucSlotNo);
      if(ucWheelPos >= cAnzRad){
         ucWheelPos = cRadPosUndef;
      }
      PutRePckgIdDM                      (ucSlotNo, tReData.PCKG_ID);
      PutReSuppIdDM                      (ucSlotNo, tReData.SUPP_ID);
      PutReIdDM                          (ucSlotNo, tReData.TYR_ID);
      PutRePressureRelDM                 (ucSlotNo, ucPres);
      PutReTemperatureCentDM             (ucSlotNo, scTemp);
      PutTelRssiLevelDM                  (ucSlotNo, tReData.RDC_DT_7);
      PutReBatteryLevelDM                (ucSlotNo, ucBattState);
      PUTucLastTelegramTypeToNvmMirrorEE (self, ucGetRePckgIdDM(ucSlotNo), ucSlotNo);
      PUTucLastBatteryStateToNvmMirrorEE (self, ucGetReBatteryLevelDM(ucSlotNo), ucSlotNo);
      ucSNR = ucCalcSignalToNoiseRatio   (ucGetTelRssiLevelDM(ucSlotNo), ucGetRfBackgroundNoiseLevelDM());
      PUTucLastSNRToNvmMirrorEE          (self, ucSNR, ucSlotNo);
      if((tReData.PCKG_ID == cTelTypeSELPAL) || (tReData.PCKG_ID == cTelTypeSELPAL1)){
         PutRePalLookBackTimeDM (ucSlotNo, tReData.RDC_DT_3);
         PutRePalStatusDM       (ucSlotNo, (uint16)(((uint16) tReData.RDC_DT_4 << 8) + (uint16) tReData.RDC_DT_5));
         PUTushLastPalStatusEE  (self, ushGetRePalStatusDM(ucSlotNo), ucSlotNo);
      }
      if(TRUE == bGetBitBetriebszustandBZ(cEIGENRAD)){
         PUTucLastWuPressureEE    (self, ucGetRePressureRelDM(ucSlotNo), ucSlotNo);
         PUTscLastWuTemperatureEE (self, scGetReTemperatureCentDM(ucSlotNo), ucSlotNo);
         if(TRUE == ProcessFillingDetectionFID(self, ucSlotNo)){
            for(i = 0; i < cAnzRad; i++){
               (void)ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, i);
               scTSollKalt = GETscTAmbValEE(self);
               PUTscTAinitValEE(self, scTSollKalt);
               (void) ucCfgReInitSingleUSWIF(self, ucPSollKalt, scTSollKalt, i, cRadPosUndef);
               NotificationITY(self, cNotifyRcpChangedITY, ucSlotNo);
            }
            if(FALSE == GETTyreSelectionBckgrdEE(self)){
               SetCalibrationRootCauseDS(self, cCalFilDetRe0 + ucSlotNo);
               (void)SaveCalibrationEventDS(self);
            }
            StartSRA(self);
         }
         if(0 == ushGetReDefectCounterBySlotWUM(ucSlotNo)){
            CheckTirePressureDM(self, ucSlotNo, ucWheelPos, ucGetRePressureRelDM(ucSlotNo), scGetReTemperatureCentDM(ucSlotNo));
            for(ucWarnType = 0; ucWarnType < ucMaxWarnTypeWNc; ucWarnType++){
               (void) ucGetWThresUSWIF(self, ucWarnType, &ucSetLevel, &ucResetLevel);
               ucSetLevelDW[ucSlotNo][ucWarnType] = ucSetLevel;
               ucResetLevelDW[ucSlotNo][ucWarnType] = ucResetLevel;
            }
         }
         NotificationITY(self, cNotifyTelRecITY, ucSlotNo);
         ProcessFastaWarnEventsDS(self);
         if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
            CountWheelElectronicDataBM(ucWheelPos);
         }
      }
   }
   PutStatusReLesenDruckcodierungDataDS(ulReID, ucPres, ucPresState, ucBattState);
   return ucRet;
}

void CheckTirePressureDM(Rte_Instance self, uint8 ucSlotNo, uint8 ucWheelPos, PhySensorTyrePresType ucPressure, sint8 scTemperature){
   tHFTelDat tHFTel;
   tTPMSMsgData tTssMsg;
   tHFTel.ucId  = ucSlotNo;
   tHFTel.ucP   = ucPressure;
   tHFTel.scTWE = scTemperature;
   tHFTel.ucLifeTime = 200;
   tHFTel.ushVehicleSpeed = GETushSpeedFZZ();
   tHFTel.scTa = GETscTAmbValEE(self);
   tHFTel.ucEnvP = GETucPAmbValEE(self);
   (void) ucWarnManagerWN(self, ucComparec, (uint8*) (void*) &tHFTel);
   tTssMsg.ucWarnState = tHFTel.ucWarnState;
   tTssMsg.ucWarnAttr = tHFTel.ucWarnAttr;
   tTssMsg.ucId = tHFTel.ucId;
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      tTssMsg.ucPos = ucWheelPos;
      tTssMsg.ucSystemState = ucPosDepWarnc;
   }
   else{
      tTssMsg.ucSystemState = 0x00;
      tTssMsg.ucPos = cRadPosUndef;
   }
   (void) ucTPMSMsgManagerTM(self, ucTPMSMsgOutc, (uint8*) (void*) &tTssMsg);
}

void TransferWarnStateToTpmsMsgManOnCycEventDM(Rte_Instance self){
   uint8 ucWheelPos;
   uint8 ucWState[cAnzRad];
   uint8 ucWAttr[cAnzRad];
   tTPMSMsgData tTssMsg;
   (void) ucGetWarnBitIdIntIFH(self, ucWState);
   (void) ucGetWarnBitTonnageIdIntIFH(self, ucWAttr);
   for(uint8 ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      tTssMsg.ucWarnState = ucWState[ucLoop];
      tTssMsg.ucWarnAttr = ucWAttr[ucLoop];
      tTssMsg.ucId = ucLoop;
      ucWheelPos = ucGetWPOfColWAL(ucLoop);
      if(ucWheelPos < cAnzRad){
         tTssMsg.ucPos = ucWheelPos;
         tTssMsg.ucSystemState = ucPosDepWarnc;
      }
      else{
         tTssMsg.ucPos = cRadPosUndef;
         tTssMsg.ucSystemState = 0x00;
      }
      (void) ucTPMSMsgManagerTM(self, ucTPMSMsgOutc, (uint8*) (void*) &tTssMsg);
   }
}

uint8 ucCalcBatteryLevelDM(const ImpTypeRecCddRdcData* rdcData){
   uint8   ucBatStatus;
   switch(rdcData->PCKG_ID){
      case cTelTypeSELPAL:
      case cTelTypeSELPAL1:
         ucBatStatus = (rdcData->RDC_DT_5 & cBATTERY_STATUS_MASK_PAL) >> 2;
         ucBatStatus *= 10;
              if((ucBatStatus == 0) || (ucBatStatus > 110)){ucBatStatus = cBATTERY_STATUS_UNKNOWN;}
         else if(ucBatStatus > 100)                        {ucBatStatus = 100;}
         else{}
         break;

      case cTelTypeContiFP:
      case cTelTypeBeruLong:
         ucBatStatus = rdcData->RDC_DT_3 & cBATTERY_STATUS_MASK_OTHER;
         if(ucBatStatus <= 120){ucBatStatus = (uint8)(((uint16)ucBatStatus * 100) / 120);}
         else                  {ucBatStatus = cBATTERY_STATUS_UNKNOWN;}
         break;

      default:
         ucBatStatus = cBATTERY_STATUS_UNKNOWN;
   }
   return ucBatStatus;
}

boolean CheckPrepareTyreSelectionDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow, const uint8 ucSeason, const uint8 Selection){
   uint8                 MaxLoadStateVal;
   boolean               bRet       = FALSE;
   boolean               bStartInit = FALSE;
   uint8                 ucHisCol, ucWheelPos;
   PhySensorTyrePresType ucPress;
   PhySensorTyreTempType scTemp;
   if(TRUE == bGetCRdciEcoRcpEnableCD()){MaxLoadStateVal = REQ_ECO_LOAD;}
   else                                 {MaxLoadStateVal = REQ_FULL_LOAD;}

   if((LoadState <= MaxLoadStateVal) && (ucSeason <= CSEASON_WINTER)){
      if(FALSE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
         if(FALSE == bGetBandmodeBM()){
            if(FALSE == bSystemErrorIsSetNWM()){
               bStartInit = TRUE;
            }
         }
      }
   }
   if(TRUE == bStartInit){
      bStartInit = FALSE;
      if((TyreListRow < GetLengthOfTyreListDM()) || (OP_SLCTN_TYR_AVLB_AndererReifen == TyreListRow)){
         SetTarPTyrDisplayValueDM(self, LoadState, TyreListRow, Selection);
         if(OP_SLCTN_TYR_AVLB_AndererReifen == TyreListRow){
            bStartInit = TRUE;
         }
         else{
            if(GETSelectedTyreIndexEE(self) != TyreListRow){
               bStartInit = TRUE;
            }
            else{
               if(GETSelectedSeasonEE(self) != ucSeason){
                  bStartInit = TRUE;
               }
               else{
                  if(GETSelectedLoadStateEE(self) == LoadState){
                     bStartInit = TRUE;
                  }
               }
            }
         }
         if(TRUE == bStartInit){
            StartInitializationProcessDM(self);
            if(TRUE == bGetBitFahrzeugzustandFZZ(cLONG_PARK)){
               StartLearnLocateWAM(self);
            }
            else if(TRUE == bGetBitBetriebszustandBZ(cZO_FINISH | cLOC_INTERRUPTED | cLOC_NOT_POSSIBLE | cZO_TIMEOUT)){
               StartLearnLocateWAM(self);
            }
            else if(TRUE == bGetBitBetriebszustandBZ(cER_FINISH)){
               ContinueLocateWAM(self);
            }
            else{
               ContinueLearnWAM(self);
            }
            ClearErrorConditionsWUM(self, cMaxLR, cPTC_Mute);
            PUTTyreSelectionActiveEE(self, TRUE);
            PUTTyreSelectionBckgrdEE(self, TRUE);
            SetCalibrationRootCauseDS(self, cCalByHMI);
            StartSBR(self);
            StartSRA(self);
         }
         else{
            if(FALSE == GETTyreSelectionActiveEE(self)){
               SetSolldruckDM(self, LoadState,TyreListRow);
               (void) ZoPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cZUGEORDNET), TyreListRow);
               SetCalibrationRootCauseDS(self, cCalByHMI);
               (void)SaveCalibrationEventDS(self);
               if(OP_TAR_P_LOCO_TPCT_Teilbeladen == LoadState){
                  for(ucHisCol = 0; ucHisCol < cAnzRad; ucHisCol++){
                     ucPress     = GETucLastWuPressureEE(self, ucHisCol);
                     scTemp      = GETscLastWuTemperatureEE(self, ucHisCol);
                     ucWheelPos  = ucGetWPOfColWAL(ucHisCol);
                     if((cInvalidREpressure != ucPress) && (cInvalidREtemperature != scTemp)){
                        CheckTirePressureDM(self, ucHisCol, ucWheelPos, ucPress, scTemp);
                     }
                  }
               }
               NotificationITY(self, cNotifyBeladungChangedITY, cAnzRad);
            }
         }
         PUTPlausiInitErrorEE(self, FALSE);
         PUTTyreChangedEE(self, FALSE);
         PUTAutomaticSelectionFailedStatusEE(self, FALSE);
         bRet = TRUE;
      }
   }
   return(bRet);
}

void SaveCurrentTyreSelectionDM(Rte_Instance self){
   PUTSelectedLoadStateEE(self, GetLoadStateDM());
   PUTStManSelectionEE(self, GetStatusManSelectionDM());
   if(ST_MAN_SLCTN_Manuelle_Reifenauswahl == GetStatusManSelectionDM()){
      PUTSelectedSeasonEE(self, GetSeasonDM());
      PUTSelectedTyreIndexEE(self, GetSelectedTyreIndexDM());
      PUTSelectedSuTyreIndexEE(self, GetSummerTyreIndexDM());
      PUTSelectedWiTyreIndexEE(self, GetWinterTyreIndexDM());
      SaveCurTyreListDataInNvmDM(self, GetSeasonDM(), GetSelectedTyreIndexDM());
   }
   else{
      SetSeasonDM(GETSelectedSeasonEE(self));
      SetSelectedTyreIndexDM(GETSelectedTyreIndexEE(self));
      SetSummerTyreIndexDM(GETSelectedSuTyreIndexEE(self));
      SetWinterTyreIndexDM(GETSelectedWiTyreIndexEE(self));
   }
}

void ResetCurrentTyreSelectionDM(Rte_Instance self){
   SetSeasonDM(GETSelectedSeasonEE(self));
   SetLoadStateDM(GETSelectedLoadStateEE(self));
   SetSelectedTyreIndexDM(GETSelectedTyreIndexEE(self));
   SetSummerTyreIndexDM(GETSelectedSuTyreIndexEE(self));
   SetWinterTyreIndexDM(GETSelectedWiTyreIndexEE(self));
   SetStatusManSelectionDM(GETStManSelectionEE(self));
}

void SetSolldruckDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow){
   uint8 ucFrontAxlePressure;
   uint8 ucRearAxlePressure;
   sint8 scTAmb;
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      if((TyreListRow < GetLengthOfTyreListDM()) && (TyreListRow != OP_SLCTN_TYR_AVLB_AndererReifen)){
         ucFrontAxlePressure = GetFrontAxleSetPressTyreList(LoadState, TyreListRow);
         ucRearAxlePressure = GetRearAxleSetPressTyreList(LoadState, TyreListRow);
         scTAmb = GETscTAmbValEE(self);
         PUTscTAinitValEE(self, scTAmb);
         InitRatedValuesDM(self);
         SetNewRatedValueDM(self, ucFrontAxlePressure, scTAmb, ucGetColOfWP(cRadPosVL));
         SetNewRatedValueDM(self, ucFrontAxlePressure, scTAmb, ucGetColOfWP(cRadPosVR));
         SetNewRatedValueDM(self, ucRearAxlePressure,  scTAmb, ucGetColOfWP(cRadPosHL));
         SetNewRatedValueDM(self, ucRearAxlePressure,  scTAmb, ucGetColOfWP(cRadPosHR));
      }
   }
}

void SetTarPTyrDisplayValueDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow, const uint8 IdrSel){
   uint8   ucFrontAxlePressure;
   uint8   ucRearAxlePressure;
   boolean bViewAxleSetPress;

   if((TRUE == GETTyreSelectionActiveEE(self)) && (IdrSel == OP_IDR_SLCTN_Automatische_Auswahl)){
      ushTarPTyrDisplayValDM[cRadPosVL] = (TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar+1);
      ushTarPTyrDisplayValDM[cRadPosVR] = (TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar+1);
      ushTarPTyrDisplayValDM[cRadPosHL] = (TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar+1);
      ushTarPTyrDisplayValDM[cRadPosHR] = (TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar+1);
   }
   else{
      if(TyreListRow < GetLengthOfTyreListDM()){
         if(OP_SLCTN_TYR_AVLB_AndererReifen != TyreListRow){
            if(FALSE == GETInvalidTyreListEE(self)){bViewAxleSetPress = TRUE;}
            else                                   {bViewAxleSetPress = FALSE;}
         }
         else                                      {bViewAxleSetPress = FALSE;}
      }
      else                                         {bViewAxleSetPress = FALSE;}
      if(TRUE == bViewAxleSetPress){
         ucFrontAxlePressure = GetFrontAxleSetPressTyreList(LoadState, TyreListRow);
         ucRearAxlePressure = GetRearAxleSetPressTyreList(LoadState, TyreListRow);
         ushTarPTyrDisplayValDM[cRadPosVL] = (uint16) ucFrontAxlePressure;
         ushTarPTyrDisplayValDM[cRadPosVR] = (uint16) ucFrontAxlePressure;
         ushTarPTyrDisplayValDM[cRadPosHL] = (uint16) ucRearAxlePressure;
         ushTarPTyrDisplayValDM[cRadPosHR] = (uint16) ucRearAxlePressure;
      }
      else{
         ushTarPTyrDisplayValDM[cRadPosVL] = TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar;
         ushTarPTyrDisplayValDM[cRadPosVR] = TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar;
         ushTarPTyrDisplayValDM[cRadPosHL] = TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar;
         ushTarPTyrDisplayValDM[cRadPosHR] = TAR_P_TYR_Funktionsschnittstelle_ist_nicht_verfuegbar;
      }
   }
}

InfoTyrePresType GetTarPTyrDisplayValueDM(uint8 WheelPos){
   return ushTarPTyrDisplayValDM[WheelPos];
}

void SetLoadStateDM(const uint8 LoadState){
	uint8 MaxLoadStateVal;
	if(TRUE == bGetCRdciEcoRcpEnableCD()){MaxLoadStateVal = OP_TAR_P_LOCO_TPCT_Signal_ungueltig;}
	else                                 {MaxLoadStateVal = OP_TAR_P_LOCO_TPCT_ECO_Solldruck;}

	if(LoadState < MaxLoadStateVal){
		ucLoadStateOut = LoadState;
	}
}

void SetSeasonDM(const uint8 Season){
	if(Season < OP_TYR_SEA_TPCT_KeineAenderung){
		ucSeasonOut = Season;
	}
}

uint8 GetLoadStateDM          (void){return ucLoadStateOut;}
uint8 GetSeasonDM             (void){return ucSeasonOut;}
void  SetWinterTyreIndexDM    (const uint8 Index){ucWITRIndex = Index;}
uint8 GetWinterTyreIndexDM    (void){return ucWITRIndex;}
void  SetSummerTyreIndexDM    (const uint8 Index){ucSUTRIndex = Index;}
uint8 GetSummerTyreIndexDM    (void){return ucSUTRIndex;}
void  SetIDRMessageCenterDM   (const uint8 Idr){ucIDRMSGC = Idr;}
uint8 GetIDRMessageCenterDM   (void){return ucIDRMSGC;}
void  SetStatusManSelectionDM (const uint8 MaSel){ucSTMANSLCTN = MaSel;}
uint8 GetStatusManSelectionDM (void){return ucSTMANSLCTN;}
void  SetLengthOfTyreListDM   (const uint8 Length){ucLengthOfTyreList = Length;}
uint8 GetLengthOfTyreListDM   (void){return ucLengthOfTyreList;}
uint8 GetSelectedTyreIndexDM  (void){return ucSLCTNTRIndex;}

void SetSelectedTyreIndexDM(const uint8 Index){
	if((Index < GetLengthOfTyreListDM()) || (OP_SLCTN_TYR_AVLB_AndererReifen == Index)){
		ucSLCTNTRIndex = Index;
	}
}

void SaveRidWeDataDM(Rte_Instance self, ImpTypeRecCddRdcData tReData){
	switch(tReData.PCKG_ID){
		case cTelTypeTyreDIM:
		{
			SaveTyreDimensionDataRID(tReData);
			break;
		}
		case cTelTypeTyreDOT:
		{
			SaveTyreDOTDataRID(tReData);
			break;
		}
		case cTelTypeTyreDataOE1:
		{
			SaveTyreOE1DataRID(tReData);
			break;
		}
		case cTelTypeTyreDataOE2:
      {
			SaveTyreOE2DataRID(tReData);
			break;
      }
		case cTelTypeTyreStatus:
		{
			CheckTyreStatusRID(self, tReData);
      break;
		}
		default:
      {
			break;
		}
	}
}

boolean CompareReDimErfsDM(Rte_Instance self, const uint8* ConvRidData){
   uint8   i, j;
   boolean bRet = FALSE;
   uint8   IxArray[TYRE_LIST_MAX_ELEMENTS];
   if(FALSE == CompareAllDataToErfsDM(ConvRidData, &IxArray[0])){
      CompareTyreDimToErfsDM(ConvRidData, &IxArray[0]);
      CompareLoadIxToErfsDM(ConvRidData, &IxArray[0]);
      CompareSpeedIxToErfsDM(ConvRidData, &IxArray[0]);
   }
   if(TRUE == ComparePressValOfMatchingErfsEntriesDM(&IxArray[0])){
      for(i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
         if(IxArray[i] < TYRE_LIST_MAX_ELEMENTS){
            if(FALSE == bRet){
               j = CheckTyreChangedOnRearAxleDM();
               if((i != GETSelectedTyreIndexEE(self)) || (TRUE == j)){
                  PUTTyreSelectionActiveEE(self, TRUE);
                  StartSRA(self);
                  PUTSelectedTyreIndexEE(self, i);
                  SetSelectedTyreIndexDM(i);
                  if(cCalInvalid == ucGetCalibrationRootCauseDS(self)){
                     SetCalibrationRootCauseDS(self, cCalRidNoStatusbar);
                  }
               }
               if(ST_MAN_SLCTN_Manuelle_Reifenauswahl == GETStManSelectionEE(self)){
                  SetIDRMessageCenterDM(OP_IDR_MSGC_MZ_Aktivieren);
                  PUTIdrMessageEE(self, OP_IDR_MSGC_MZ_Aktivieren);
               }
               PUTTyreChangedEE(self, FALSE);
               PUTAutomaticSelectionFailedStatusEE(self, FALSE);
               PUTSelectedAutoTyreIndexEE(self, i);
               SetStatusManSelectionDM(ST_MAN_SLCTN_Automatische_Reifenauswahl);
               PUTStManSelectionEE(self, ST_MAN_SLCTN_Automatische_Reifenauswahl);
               PUTStSelectTyreEE(self, ST_SLCTN_TYR_Verbaut_Felgensensor);
               SaveCurTyreListDataInNvmDM(self, CSEASON_NOCHANGE, i);
               bRet = TRUE;
            }
         }
      }
   }
   return bRet;
}

static boolean CompareAllDataToErfsDM(const uint8* pConvRidData, uint8* pIxArray){
   uint8 MemValue, CheckMask;
   boolean bComp;
   boolean bRet = FALSE;
   for(uint8 i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
      bComp = TRUE;
      for(uint8 j = 0; j < 4; j++){
         MemValue = GetTyreListMember(i, j);
         if(WIDTH_IX == j){
            CheckMask = 0xF8;
            if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
               bComp = FALSE;
            }
         }
         else{
            if(SIDEREL_IX == j){
               CheckMask = 0xF8;
               if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
                  bComp = FALSE;
               }
            }
            else{
               if(DIA_SPEED_IX == j){
                  CheckMask = 0xFF;
                  if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
                     bComp = FALSE;
                  }
               }
               else{
                  CheckMask = 0xFC;
                  if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
                     bComp = FALSE;
                  }
                  CheckMask = 0x03;
                  if(CSEASON_SUMMER == (pConvRidData[j] & CheckMask)){
                     if(CSEASON_SUMMER != (MemValue & CheckMask)){
                        bComp = FALSE;
                     }
                  }
                  else{
                     if(CSEASON_SUMMER == (MemValue & CheckMask)){
                        bComp = FALSE;
                     }
                  }
               }
            }
         }
      }
      if(TRUE == bComp){
         pIxArray[i] = i;
         bRet = TRUE;
      }
      else{
         pIxArray[i] = 0xFF;
      }
   }
   return(bRet);
}

static void CompareTyreDimToErfsDM(const uint8* pConvRidData, uint8* pIxArray){
   uint8 MemValue, CheckMask;
   boolean bComp;
   for(uint8 i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
      bComp = TRUE;
      for(uint8 j = 0; j < 4; j++){
         MemValue = GetTyreListMember (i, j);
         if(WIDTH_IX == j){
            CheckMask = 0xF8;
            if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
               bComp = FALSE;
            }
         }
         else{
            if(SIDEREL_IX == j){
               CheckMask = 0xF8;
               if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
                  bComp = FALSE;
               }
            }
            else{
               if(DIA_SPEED_IX == j){
                  CheckMask = 0xF0;
                  if((pConvRidData[j] & CheckMask) != (MemValue & CheckMask)){
                     bComp = FALSE;
                  }
               }
               else{
                  CheckMask = 0x03;
                  if(CSEASON_SUMMER == (pConvRidData[j] & CheckMask)){
                     if(CSEASON_SUMMER != (MemValue & CheckMask)){
                        bComp = FALSE;
                     }
                  }
                  else{
                     if(CSEASON_SUMMER == (MemValue & CheckMask)){
                        bComp = FALSE;
                     }
                  }
               }
            }
         }
      }
      if(TRUE == bComp){pIxArray[i] = i;}
      else             {pIxArray[i] = 0xFF;}
   }
}

static void CompareLoadIxToErfsDM(const uint8* pConvRidData, uint8* pIxArray){
   uint8 MemValue,CheckMask;
   for(uint8 i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
      if(0xFF != pIxArray[i]){
         MemValue  = GetTyreListMember(i, LOAD_SEAS_IX);
         CheckMask = 0xFC;
         if((pConvRidData[LOAD_SEAS_IX] & CheckMask) < (MemValue & CheckMask)){
            pIxArray[i] = 0xFF;
         }
      }
   }
}

static void CompareSpeedIxToErfsDM(const uint8* pConvRidData, uint8* pIxArray){
   uint8 MemValue, CheckMask;
   for(uint8 i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
      if(0xFF != pIxArray[i]){
         MemValue = GetTyreListMember (i, DIA_SPEED_IX);
         CheckMask = 0x0F;
         if(CSEASON_SUMMER == (GetTyreListMember(i, LOAD_SEAS_IX) & 0x03)){
            if((pConvRidData[DIA_SPEED_IX] & CheckMask) < (MemValue & CheckMask)){
               pIxArray[i] = 0xFF;
            }
         }
         else{
            if((pConvRidData[DIA_SPEED_IX] & CheckMask) > (MemValue & CheckMask)){
               pIxArray[i] = 0xFF;
            }
         }
      }
   }
}

static boolean ComparePressValOfMatchingErfsEntriesDM(const uint8* pIxArray){
   uint8 uc1stPressByte[3] = {0xFF,0xFF,0xFF};
   boolean bComp = TRUE;
   for(uint8 i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
      if(0xFF != pIxArray[i]){
         if(0xFF == uc1stPressByte[0]){
            uc1stPressByte[0] = GetTyreListMember(i, PRESS_BYTE_1_IX);
            uc1stPressByte[1] = GetTyreListMember(i, PRESS_BYTE_2_IX);
            uc1stPressByte[2] = GetTyreListMember(i, PRESS_BYTE_3_IX);
         }
         else{
            if(uc1stPressByte[0] != GetTyreListMember(i, PRESS_BYTE_1_IX)){bComp = FALSE;}
            if(uc1stPressByte[1] != GetTyreListMember(i, PRESS_BYTE_2_IX)){bComp = FALSE;}
            if(uc1stPressByte[2] != GetTyreListMember(i, PRESS_BYTE_3_IX)){bComp = FALSE;}
         }
      }
   }
   return bComp;
}

uint8 GetSizeOfTyreListElementDM(void){
   return TYRE_DATA_BYTES;
}

uint8 GetDefaultLoadCondDM(void){
   uint8 DefLoadCon;
   if(TRUE == bGetCRdciEcoRcpEnableCD()){
      if(TRUE == bGetCRdciDefaultLoadCondCD()){DefLoadCon = REQ_ECO_LOAD;}
      else                                    {DefLoadCon = REQ_PART_LOAD;}
   }
   else                                       {DefLoadCon = REQ_PART_LOAD;}
   return DefLoadCon;
}

uint8                 ucGetRePckgIdDM          (uint8 ucSlotNo){return ucRePckgIdDM          [ucSlotNo];}
uint32                ulGetReIdDM              (uint8 ucSlotNo){return ulReIdDM              [ucSlotNo];}
uint8                 ucGetReSuppIdDM          (uint8 ucSlotNo){return ucReSuppIdDM          [ucSlotNo];}
PhySensorTyrePresType ucGetRePressureRelDM     (uint8 ucSlotNo){return ucRePressureRelDM     [ucSlotNo];}
PhySensorTyreTempType scGetReTemperatureCentDM (uint8 ucSlotNo){return scReTemperatureCentDM [ucSlotNo];}
uint8                 ucGetRePalLookBackTimeDM (uint8 ucSlotNo){return ucRePalLookBackTimeDM [ucSlotNo];}
uint16                ushGetRePalStatusDM      (uint8 ucSlotNo){return ushRePalStatusDM      [ucSlotNo];}
uint8                 ucGetTelRssiLevelDM      (uint8 ucSlotNo){return ucTelRssiLevelDM      [ucSlotNo];}
uint8                 ucGetReBatteryLevelDM    (uint8 ucSlotNo){return ucReBatteryLevel      [ucSlotNo];}

void PutRePckgIdDM          (uint8 ucSlotNo, uint8                 ucPckgId)          {if(ucSlotNo < cAnzRad){ucRePckgIdDM          [ucSlotNo] = ucPckgId;}}
void PutReIdDM              (uint8 ucSlotNo, uint32                ulId)              {if(ucSlotNo < cAnzRad){ulReIdDM              [ucSlotNo] = ulId;}}
void PutReSuppIdDM          (uint8 ucSlotNo, uint8                 ucSuppId)          {if(ucSlotNo < cAnzRad){ucReSuppIdDM          [ucSlotNo] = ucSuppId;}}
void PutRePressureRelDM     (uint8 ucSlotNo, PhySensorTyrePresType ucPressure)        {if(ucSlotNo < cAnzRad){ucRePressureRelDM     [ucSlotNo] = ucPressure;}}
void PutReTemperatureCentDM (uint8 ucSlotNo, PhySensorTyreTempType scTemperature)     {if(ucSlotNo < cAnzRad){scReTemperatureCentDM [ucSlotNo] = scTemperature;}}
void PutRePalLookBackTimeDM (uint8 ucSlotNo, uint8                 ucPalLookBackTime) {if(ucSlotNo < cAnzRad){ucRePalLookBackTimeDM [ucSlotNo] = ucPalLookBackTime;}}
void PutRePalStatusDM       (uint8 ucSlotNo, uint16                ushPalStatus)      {if(ucSlotNo < cAnzRad){ushRePalStatusDM      [ucSlotNo] = ushPalStatus;}}
void PutTelRssiLevelDM      (uint8 ucSlotNo, uint8                 ucRssi)            {if(ucSlotNo < cAnzRad){ucTelRssiLevelDM      [ucSlotNo] = ucRssi;}}
void PutReBatteryLevelDM    (uint8 ucSlotNo, uint8                 ucBatLevel)        {if(ucSlotNo < cAnzRad){ucReBatteryLevel      [ucSlotNo] = ucBatLevel;}}

void PutRfBackgroundNoiseLevelDM(const ImpTypeRecCddRdcData* rdcData){
   ucRfBgNoiseLevel = rdcData->RDC_DT_4;
}

uint8 ucGetRfBackgroundNoiseLevelDM(void){
   return ucRfBgNoiseLevel;
}

static uint8 ucConvAkAbsPressureInRelDM(uint8 ucRawPres, PhySensorTyrePresType* pucPhyPres, uint8 ucPamb){
   uint8  ucError = cPresSensorOk;
   uint16 ushPsensorAbs;

   switch(ucRawPres){
      case cReAkPresError:
         *pucPhyPres = cInvalidREpressure;
         ucError = cPresSensorError;
         break;

      case cReAkPresUnderflow:
         *pucPhyPres = 0;
         ucError = cPresSensorUnderflow;
         break;

      case cReAkPresOverflow:
         *pucPhyPres = 252;
         ucError = cPresSensorOverflow;
         break;

      default:
      if(ucPamb == 255){
         ucPamb = 40;
      }
      ushPsensorAbs = ((uint16) ucRawPres + 40) - 2;
      if(ushPsensorAbs > ucPamb){
         if((ushPsensorAbs - (uint16) ucPamb) > (uint16) 252){*pucPhyPres = 252;                                              ucError = cPresSensorOverflow;}
         else                                                {*pucPhyPres = (PhySensorTyrePresType) (ushPsensorAbs - ucPamb); ucError = cPresSensorOk;}
      }
      else                                                   {*pucPhyPres = 0;                                                ucError = cPresSensorUnderflow;}
      break;
   }
   return ucError;
}

static uint8 ucConvAkTemperatureInCentDM(uint8 ucRawTemp, PhySensorTyreTempType* pscPhyTemp){
   uint8 ucError = cTempSensorOk;
        if(cReAkTempError == ucRawTemp)      {*pscPhyTemp = cInvalidREtemperature;                ucError = cTempSensorError;}
   else if(ucRawTemp < cReHufAkTempUnderflow){*pscPhyTemp = (sint8) (cReHufAkTempUnderflow - 52); ucError = cTempSensorUnderflow;}
   else if(ucRawTemp > cReHufAkTempOverflow) {*pscPhyTemp = (sint8) (cReHufAkTempOverflow  - 52); ucError = cTempSensorOverflow;}
   else                                      {*pscPhyTemp = (sint8) (ucRawTemp             - 52); ucError = cTempSensorOk;}
   return ucError;
}

PhySensorTyrePresType ucGetValidTyrePressureRelAtWheelPosDM(uint8 ucWheelPos){
   PhySensorTyrePresType ucRet;
   uint8 ucHisPos;
   ucHisPos = ucGetColOfWP(ucWheelPos);
   if(ucHisPos < cAnzRad){ucRet = ucGetRePressureRelDM(ucHisPos);}
   else                  {ucRet = cInvalidREpressure;}
   return ucRet;
}

sint8 scGetValidTyreTemperatureAtWheelPosDM(uint8 ucRadPos){
   PhySensorTyreTempType scRet;
   uint8 ucHisPos;
   ucHisPos = ucGetColOfWP(ucRadPos);
   if(ucHisPos < cAnzRad){scRet = scGetReTemperatureCentDM(ucHisPos);}
   else                  {scRet = cInvalidREtemperature;}
   return scRet;
}

void GetWarnThresDM(uint8 ucHistSlot, uint8 ucWarnType, uint8* ucSetLevel, uint8* ucResetLevel){
  *ucSetLevel   = ucSetLevelDW[ucHistSlot][ucWarnType];
  *ucResetLevel = ucResetLevelDW[ucHistSlot][ucWarnType];
}

void SetHistoryChangeBitsDM(Rte_Instance self){
   uint8 ucNewWheelPos;
   uint8 ucTemp1;
   uint8 ucTemp2;
   ucTemp1 = ucGetHistoryIdChangedBitsWAL();
   if(ucTemp1 > 0){
      SetIdChangedBitsZK(ucTemp1);
   }

   ucTemp2 = ucGetHistoryWpChangedBits();
   if((ucTemp2 & 0x01) == 0x01){
      ucNewWheelPos = ucGetWPOfColWAL(0);
      SetWpChangedBitZK(ucNewWheelPos);
      (void) ucSetPTSollAfterWpChangedUSWIF(self, 0, ucNewWheelPos);
   }

   if((ucTemp2 & 0x02) == 0x02){
      ucNewWheelPos = ucGetWPOfColWAL(1);
      SetWpChangedBitZK(ucNewWheelPos);
      (void) ucSetPTSollAfterWpChangedUSWIF(self, 1, ucNewWheelPos);
   }

   if((ucTemp2 & 0x04) == 0x04){
      ucNewWheelPos = ucGetWPOfColWAL(2);
      SetWpChangedBitZK(ucNewWheelPos);
      (void) ucSetPTSollAfterWpChangedUSWIF(self, 2, ucNewWheelPos);
   }

   if((ucTemp2 & 0x08) == 0x08){
      ucNewWheelPos = ucGetWPOfColWAL(3);
      SetWpChangedBitZK(ucNewWheelPos);
      (void) ucSetPTSollAfterWpChangedUSWIF(self, 3, ucNewWheelPos);
   }
}

void CheckTyreChangedDM(Rte_Instance self){
   uint8 IdChangeBits, WpChangeBits, BitCt = 0x00;
   IdChangeBits = ucGetIdChangedBitsZK();
   WpChangeBits = ucGetWpChangedBitsZK();
   if(ST_MAN_SLCTN_Manuelle_Reifenauswahl == GETStManSelectionEE(self)){
      for(uint8 i = 0; i < cAnzRad; i++){
         if((IdChangeBits & (uint8)(1<<i)) == ((uint8)(1<<i))){BitCt+=0x01;}
         if((WpChangeBits & (uint8)(1<<i)) == ((uint8)(1<<i))){BitCt+=0x10;}
      }
      if(((BitCt & 0x0F) > 0x01) || ((BitCt & 0xF0) > 0x10)){
         PUTTyreChangedEE(self, TRUE);
      }
   }
}

void GetDateStringDM(uint16 ushYearHex, uint8 ucMonthHex, uint8 ucDayHex, uint8* szDate, uint8 ucSize){
   uint8 ucYear;
   if(ucSize >= 9){
      if((ucDayHex < 1) || (ucDayHex > 31) || (ucMonthHex < 1) || (ucMonthHex > 12) || (ushYearHex < 2016) || (ushYearHex > 2100)){
         szDate[0] = '9';
         szDate[1] = '9';
         szDate[2] = '.';
         szDate[3] = '9';
         szDate[4] = '9';
         szDate[5] = '.';
         szDate[6] = '9';
         szDate[7] = '9';
         szDate[8] = 0x00;
      }
      else{
         szDate[0] = ((uint8) (ucDayHex / 10) + 0x30);
         szDate[1] = ((uint8) (ucDayHex % 10) + 0x30);
         szDate[2] = '.';
         szDate[3] = ((uint8) (ucMonthHex / 10) + 0x30);
         szDate[4] = ((uint8) (ucMonthHex % 10) + 0x30);
         szDate[5] = '.';
         ucYear = (uint8)(ushYearHex % 100);
         szDate[6] = ((uint8) (ucYear / 10) + 0x30);
         szDate[7] = ((uint8) (ucYear % 10) + 0x30);
         szDate[8] = 0x00;
      }
   }
   else{
   }
}

void GetTimeStringDM(uint8 ucHourHex, uint8 ucMinutesHex, uint8 ucSecondsHex, uint8* szTime, uint8 ucSize){
   if(ucSize >= 9){
      if((ucHourHex > 23) || (ucMinutesHex > 59) || (ucSecondsHex > 59)){
         szTime[0] = '9';
         szTime[1] = '9';
         szTime[2] = ':';
         szTime[3] = '9';
         szTime[4] = '9';
         szTime[5] = ':';
         szTime[6] = '9';
         szTime[7] = '9';
         szTime[8] = 0x00;
      }
      else{
         szTime[0] = ((uint8) (ucHourHex / 10) + 0x30);
         szTime[1] = ((uint8) (ucHourHex % 10) + 0x30);
         szTime[2] = ':';
         szTime[3] = ((uint8) (ucMinutesHex / 10) + 0x30);
         szTime[4] = ((uint8) (ucMinutesHex % 10) + 0x30);
         szTime[5] = ':';
         szTime[6] = ((uint8) (ucSecondsHex / 10) + 0x30);
         szTime[7] = ((uint8) (ucSecondsHex % 10) + 0x30);
         szTime[8] = 0x00;
      }
   }
   else{
   }
}

uint8 ChangeHpaTo25mBar(uint16 ushHectopascal){
   uint8 ucRetVal;
   if(ushHectopascal <= 6350){
      ucRetVal = (uint8)(((ushHectopascal * 10) + 125) / 250);
   }
   else{
      ucRetVal = 255;
   }
   return ucRetVal;
}

uint16 Change25mBarToHpa(uint8 ucHex){
   return (uint16)((uint16)ucHex * 25);
}

void DegradeToManSelectionDM (Rte_Instance self, boolean bOtherTyre){
   if(OP_IDR_SLCTN_Automatische_Auswahl == GETStManSelectionEE(self)){
      if(TRUE == bOtherTyre){
         SetStatusManSelectionDM(ST_MAN_SLCTN_Manuelle_Reifenauswahl);
         PUTStSelectTyreEE(self, ST_SLCTN_TYR_Auswahl);
         SetSelectedTyreIndexDM(OP_SLCTN_TYR_AVLB_AndererReifen);
         PUTTyreSelectionBckgrdEE(self, TRUE);
         if(CSEASON_SUMMER == GETSelectedSeasonEE(self)){SetSummerTyreIndexDM(OP_SLCTN_TYR_AVLB_AndererReifen);}
         else                                           {SetWinterTyreIndexDM(OP_SLCTN_TYR_AVLB_AndererReifen);}
      }
      else{
         SetStatusManSelectionDM(ST_MAN_SLCTN_Manuelle_Reifenauswahl);
         PUTStSelectTyreEE(self, ST_SLCTN_TYR_Auswahl);
         PUTTyreSelectionBckgrdEE(self, TRUE);
         if(CSEASON_SUMMER == GETSelectedSeasonEE(self)){SetSelectedTyreIndexDM(GETSelectedSuTyreIndexEE(self));}
         else                                           {SetSelectedTyreIndexDM(GETSelectedWiTyreIndexEE(self));}
      }
      PUTAutomaticSelectionFailedStatusEE(self, TRUE);
      SaveCurrentTyreSelectionDM(self);
   }
}

uint16 ushGetMaxValueDM(uint16 ushVal1, uint16 ushVal2){
   uint16 ushRetVal;
   if(ushVal1 >= ushVal2){ushRetVal = ushVal1;}
   else                  {ushRetVal = ushVal2;}
   return ushRetVal;
}

static uint8 ucCalcSignalToNoiseRatio(uint8 ucTelRssi, uint8 ucBackgroundNoise){
   uint8 ucRet;
        if(0xff == ucBackgroundNoise)     {ucRet = 0xff;}
   else if(ucBackgroundNoise > ucTelRssi) {ucRet = 0xff;}
   else                                   {ucRet = ucTelRssi - ucBackgroundNoise;}
   return ucRet;
}

boolean CheckTyreChangedOnRearAxleDM(void){
   uint8 IdChangeBits, WpChangeBits, ucColRL, ucColRR, ucRAxMask;
   boolean bRet=FALSE;
   ucRAxMask = 0x00;
   IdChangeBits = ucGetIdChangedBitsZK();
   WpChangeBits = ucGetWpChangedBitsZK();
   ucColRL = ucGetColOfWP(cRadPosHL);
   ucColRR = ucGetColOfWP(cRadPosHR);
   if((ucColRL != cAnzRad) && (ucColRR != cAnzRad)){
      ucRAxMask |= (uint8)(0x01<<ucColRL);
      ucRAxMask |= (uint8)(0x01<<ucColRR);
   }
   if(((IdChangeBits & ucRAxMask) != 0x00) || ((WpChangeBits & ucRAxMask) != 0x00)){
      bRet = TRUE;
   }
   return bRet;
}

void SaveCurTyreListDataInNvmDM(Rte_Instance self, uint8 Season, uint8 TyreListRow){
   uint8 i,j;
   uint8 ucSave = 0x07;
   if(TyreListRow < GetLengthOfTyreListDM()){
      for(j = CSEASON_SUMMER; j <= CSEASON_NOCHANGE; j++){
         for(i = 0; i < TYRE_DATA_BYTES; i++){
            if((ucSave & (uint8)(0x01<<j)) == ((uint8)(0x01<<j))){
               if(GETCurErfsTyreDataEE(self,i,j) != GetTyreListMember(TyreListRow,i)){
                  ucSave ^= (uint8)(0x01<<j);
               }
            }
         }
      }
      for(j = CSEASON_SUMMER; j <= CSEASON_NOCHANGE; j++){
         if((ucSave & (uint8)(0x01<<j)) == ((uint8)(0x01<<j))){
            for(i = 0; i < TYRE_DATA_BYTES; i++){
               PUTCurErfsTyreDataEE(self, i, 0xFF, j);
            }
         }
      }
      for(i = 0; i < TYRE_DATA_BYTES; i++){
         PUTCurErfsTyreDataEE(self, i, GetTyreListMember(TyreListRow, i), Season);
      }
   }
}

void PutStWheelTypeChangeEventDM(uint8 Det, uint8 Pos){
   if((Det > StatusWheelTypeChangeDetection_Algorithmus_Raderkennung_laeuft) &&
      (Det < StatusWheelTypeChangeDetection_Radidentifikation_abgeschlossen)){
      if(StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar == ucStWheelTypeChangeDet[0]){
         ucStWheelTypeChangeDet[0] = Det;
         ucStWheelTypeChangePos[0] = Pos;
         StartStChangeTimeITY(2);
      }
      else{
         ucStWheelTypeChangeDet[1] = Det;
         ucStWheelTypeChangePos[1] = Pos;
      }
   }
}

uint8 GetStWheelTypeChangeDetEventDM(uint8 index){
   uint8 RetVal = StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar;
   if(2 > index){
      RetVal = ucStWheelTypeChangeDet[index];
   }
   return (RetVal);
}

void CopyStWheelTypeChangeBufAndRestartTimerDM(void){
   ucStWheelTypeChangeDet[0] = ucStWheelTypeChangeDet[1];
   ucStWheelTypeChangePos[0] = ucStWheelTypeChangePos[1];
   ucStWheelTypeChangeDet[1] = StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar;
   ucStWheelTypeChangePos[1] = StatusWheelTypeChangePosition_Position_Unbekannt;
   StartStChangeTimeITY(2);
}

void ClearStWheelTypeChangeBuf(void){
   ucStWheelTypeChangeDet[0] = StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar;
   ucStWheelTypeChangePos[0] = StatusWheelTypeChangePosition_Position_Unbekannt;
   ucStWheelTypeChangeDet[1] = StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar;
   ucStWheelTypeChangePos[1] = StatusWheelTypeChangePosition_Position_Unbekannt;
}

uint8 GetStWheelTypeChangePosDM(void){
   return ucStWheelTypeChangePos[0];
}

void SetStWheelTypeChangedAtLocDM(uint8 IdChangedBits, uint8 ucWpChangedBits){
   uint8 i, HelpPos, ChangePos = 0x00;
   if(0x00 != IdChangedBits){
      for(i = 0; i < cAnzRad; i++){
         if((IdChangedBits & (uint8)(1<<i)) == ((uint8)(1<<i))){
            HelpPos = ucGetWPOfColWAL(i);
            if(HelpPos < cAnzRad){
               ChangePos |= (0x08 >> HelpPos);
            }
            else{
               ChangePos = 0x10;
            }
         }
      }
      PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Neuer_Reifen, ChangePos);
   }
   else{
      if(0x00 != ucWpChangedBits){
         for(i = 0; i < cAnzRad; i++){
            if((ucWpChangedBits & (uint8)(1<<i)) == ((uint8)(1<<i))){
               ChangePos |= (0x08 >> i);
            }
         }
         PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Permutation, ChangePos);
      }
   }
}

uint8 GetStWheelTypeChangedDetStateDM(void){
   uint8 ucRetState;
   uint16 ushBZ;
   ClearStWheelTypeChangeBuf();
   ushBZ = ushGetBetriebszustandBZ(cBZ_ALLE_BITS);
        if(0 != (ushBZ & (cLOC_INTERRUPTED | cLOC_NOT_POSSIBLE | cZO_TIMEOUT))){ucRetState = StatusWheelTypeChangeDetection_Algorithmus_Raderkennung_aZ6Y7PL;}
   else if(cZO_FINISH == (ushBZ & cZO_FINISH)                                 ){ucRetState = StatusWheelTypeChangeDetection_Positionsbestimmung_abgesc2IYJF8;}
   else if(cER_FINISH == (ushBZ & cER_FINISH)                                 ){ucRetState = StatusWheelTypeChangeDetection_Radidentifikation_abgeschlossen;}
   else                                                                        {ucRetState = StatusWheelTypeChangeDetection_Algorithmus_Raderkennung_laeuft;}
   return ucRetState;
}

void GetAipGpsValDM_debug(Rte_Instance self, uint8* pucAipEngDrv, uint16* pushPositionAltitude, uint16* pushErrorAltitudeMeters, uint16* pushGpsTioTicks, uint8* pucAipGpsState){
   *pucAipEngDrv            = GETucAipEngDrvEE(self);
   *pushPositionAltitude    = GETushPositionAltitudeEE(self);
   *pushErrorAltitudeMeters = GETushErrorAltitudeMetersEE(self);
   *pushGpsTioTicks         = GETushGpsTioTicksEE(self);
   *pucAipGpsState          = GETucAipGpsStateEE(self);
}

boolean CheckReIdLatelyProcBufDM(const uint32 ReID){
   uint8 i;
   boolean bRet = FALSE;
   for(i = 0; i < TELEGRAM_QUEUE_SIZE; i++){
      if((ProcIdBuf[i].ulReId < cInvalidREid) && (ProcIdBuf[i].ulReId == ReID)){
         bRet = TRUE;
      }
   }
   return bRet;
}

void DeleteReIdLatelyProcBufDM(void){
   uint8 BufTime;
   const uint8 cMaxTime = 5;
   for(uint8 i = 0; i < TELEGRAM_QUEUE_SIZE; i++){
      if(cReIdProcBufTimeLimit != ProcIdBuf[i].ucTimeCt){
         BufTime = ProcIdBuf[i].ucTimeCt;
         if(ucReIdBufTimeCt >= BufTime){
            if((ucReIdBufTimeCt - BufTime) > cMaxTime){
               ProcIdBuf[i].ulReId   = cInvalidREid;
               ProcIdBuf[i].ucTimeCt = cReIdProcBufTimeLimit;
            }
         }
         else{
            if((ucReIdBufTimeCt + (cReIdProcBufTimeLimit - BufTime)) > cMaxTime){
               ProcIdBuf[i].ulReId   = cInvalidREid;
               ProcIdBuf[i].ucTimeCt = cReIdProcBufTimeLimit;
            }
         }
      }
   }
   if(ucReIdBufTimeCt == (cReIdProcBufTimeLimit - 1)){ucReIdBufTimeCt = 0x00;}
   else                                              {ucReIdBufTimeCt++;}
}

void WriteReIdLatelyProcBufDM(const uint32 ReID){
   static uint8 ucWriteProcReIdBufIx = TELEGRAM_QUEUE_SIZE;
   if(TELEGRAM_QUEUE_SIZE == ucWriteProcReIdBufIx){
      ucWriteProcReIdBufIx = 0x00;
   }
   ProcIdBuf[ucWriteProcReIdBufIx].ulReId = ReID;
   ProcIdBuf[ucWriteProcReIdBufIx].ucTimeCt = ucReIdBufTimeCt;
   ucWriteProcReIdBufIx++;
}
