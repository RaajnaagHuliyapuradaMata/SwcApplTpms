#include "EeCommonBlockX.h"
#include "WallocX.h"
#include "WuMonitoringX.h"

static boolean bBlockNeedsUpdate = FALSE;

static void CompareValuesAndSetUpdateFlagEE(uint8 ucOld, uint8 ucNew);

void InitCommonBlockEE(Rte_Instance self){
   uint8 ucLoop;
   Rdci_UHRZEIT_DATUM_Type tTimeDate = {0, 0, 0, 0, 0, 0, 0, 0};
   PUTucCommonBlockInitializeEE(self, 0xffu);
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      PUTushFilDetMIsoEE                       (self, 0, ucLoop);
      PUTucFilDetRecFlag                       (self, 0, ucLoop);
   }
   PUTucUnAipEE                                (self, ePRESSURE_UNIT_BAR);
   PUTucUnTempEE                               (self, eTEMPERATURE_UNIT_CELSIUS);
   PUTucUnMileEE                               (self, eMILEAGE_UNIT_KILOMETER);
   PUTulMileKmEE                               (self, 0);
   PUTtTimeDateEE                              (self, tTimeDate);
   PUTulTimestampEE                            (self, 0);
   for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
      PUTushCntGoodTelEE                       (self, 0, ucLoop);
      PUTushCntMissTelEE                       (self, 0, ucLoop);
      PUTushBlockFailTimerEE                   (self, cWU_BLOCK_FAIL_TIME, ucLoop);
      PUTushSingleFailTimerEE                  (self, cWU_TIMER_STOPPED, ucLoop);
      PUTucWheelSensorStatusToNvmMirrorEE      (self, cRE_STATUS_NOT_REC, ucLoop);
      PUTucLastTelegramTypeToNvmMirrorEE       (self, cInvalidTelType, ucLoop);
      PUTucLastSNRToNvmMirrorEE                (self, cInvalidSignalToNoiseRatio, ucLoop);
      PUTushLastPalStatusEE                    (self, cInvalidRePalStatusMdb, ucLoop);
      PUTucTimeSinceLastRecEventToNvmMirrorEE  (self, 0, ucLoop);
      PUTucLastBatteryStateToNvmMirrorEE       (self, cInvalidBatteryLevel, ucLoop);
   }
   PUTushFbd4AliveTimerEE                      (self, cALIVE_TEL_TIMEOUT);
   PUTscTAmbValEE                              (self, cInitTemperature);
   PUTsshTAmbFiltValEE                         (self, cInvalidTemperatureWord);
   PUTucTAmbFiltFactValEE                      (self, cTAmbientFilterFactorDefaultValue);
   PUTucPAmbValEE                              (self, cInitAmbientPressure);
   PUTucFilDetActiveEE                         (self, 0);
   PUTushCrcCodingDataEE                       (self, 0xffffu);
   PUTucLastPosChangedInformationToNvmMirrorEE (self, 0);
   PUTucAipEngDrvEE                            (self, (Rdci_AIP_ENG_DRV_Type)               0xffu);
   PUTushPositionAltitudeEE                    (self, (Rdci_GNSSPositionAltitude_Type)    0xffffu);
   PUTushErrorAltitudeMetersEE                 (self, (Rdci_GNSSErrorAltitudeMeters_Type) 0xffffu);
   PUTushGpsTioTicksEE                         (self, 0);
   PUTucAipGpsStateEE                          (self, 0);
   PUTucFBD4CountEE                            (self, 1);
   PUTslOATavgEE                               (self, (cInitTemperature*1000));
   PUTucCommonBlockInitializeEE                (self, cNvmInitialized);
}

uint8                GETucCommonBlockInitializeEE(Rte_Instance self                                       ){return(                        ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucInitialize);}
tPressureUnitType    GETucUnAipEE(                 Rte_Instance self                                       ){return((tPressureUnitType)     ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitPressure);}
tTemperatureUnitType GETucUnTempEE(                Rte_Instance self                                       ){return((tTemperatureUnitType)  ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitTemperature);}
tMileageUnitType     GETucUnMileEE(                Rte_Instance self                                       ){return((tMileageUnitType)      ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitSpeed);}
Rdci_MILE_KM_Type    GETulMileKmEE(                Rte_Instance self                                       ){return(                        ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ulKm);}
void                 PUTucCommonBlockInitializeEE(Rte_Instance self, uint8                ucNvmInitialize ){                               ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucInitialize      =         ucNvmInitialize;}
void                 PUTucUnAipEE(                 Rte_Instance self, tPressureUnitType    ucLastUnAip     ){                               ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitPressure    = (uint8) ucLastUnAip;}
void                 PUTucUnTempEE(                Rte_Instance self, tTemperatureUnitType ucLastUnTemp    ){                               ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitTemperature = (uint8) ucLastUnTemp;}
void                 PUTucUnMileEE(                Rte_Instance self, tMileageUnitType     ucLastUnMile    ){                               ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucUnitSpeed       = (uint8) ucLastUnMile;}
void                 PUTulMileKmEE(                Rte_Instance self, Rdci_MILE_KM_Type    ulLastMileKm    ){                               ((tCommonNvmBlockType*) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ulKm              =         ulLastMileKm;}

Rdci_UHRZEIT_DATUM_Type GETtTimeDateEE(Rte_Instance self)
{
  Rdci_UHRZEIT_DATUM_Type cUhrzeitDatumInitVal = { 0, 0, 0, 0, 0, 0, 0, 0 };
   uint8 ucStDispCtiDate;

   ucStDispCtiDate = ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->tUhrzeitDatum.ST_DISP_CTI_DATE;
   if(((ucStDispCtiDate & 0x01) == 0) || (ucStDispCtiDate == 0x0f)){
      return( cUhrzeitDatumInitVal);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->tUhrzeitDatum);
   }
}

void PUTtTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->tUhrzeitDatum = (x);
}

uint32 GETulTimestampEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ulTimestamp);
}

void PUTulTimestampEE(Rte_Instance self, uint32 ulValue)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ulTimestamp = ulValue;
}

uint16 GETushCntGoodTelEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntGoodTel[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntGoodTel[0]);
   }
}

void PUTushCntGoodTelEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntGoodTel[(i)] = (x);
   }
   else{
   }
}

uint16 GETushCntMissTelEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntMissTel[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntMissTel[0]);
   }
}

void PUTushCntMissTelEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushCntMissTel[(i)] = (x);
   }
   else{
   }
}

uint16 GETushBlockFailTimerEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushBlockFailTimer[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushBlockFailTimer[0]);
   }
}

void PUTushBlockFailTimerEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushBlockFailTimer[(i)] = (x);
   }
   else{
   }
}

void PUTushSingleFailTimerEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushSingleFailTimer[(i)] = (x);
   }
   else{
   }
}

uint16 GETushFbd4AliveTimerEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushFbd4AliveTimer);
}

void PUTushFbd4AliveTimerEE(Rte_Instance self, uint16 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushFbd4AliveTimer = (x);
}

uint16 GETushCrcCodingDataEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushCrcCodingData);
}

void PUTushCrcCodingDataEE(Rte_Instance self, uint16 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushCrcCodingData = (x);
}

uint16 GETushLastPalStatusEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushLastPalStatus[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushLastPalStatus[0]);
   }
}

void PUTushLastPalStatusEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushLastPalStatus[(i)] = (x);
   }
   else{
   }
}

uint8 GETucWheelSensorStatusFromNvmMirrorEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucWheelSensorStatus[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucWheelSensorStatus[0]);
   }
}

void PUTucWheelSensorStatusToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucWheelSensorStatus[(i)] = (x);
   }
   else{
   }
}

uint8 GETucLastTelegramTypeFromNvmMirrorEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastTelegramType[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastTelegramType[0]);
   }
}

void PUTucLastTelegramTypeToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastTelegramType[(i)] = (x);
   }
   else{
   }
}

uint8 GETucLastBatteryStateFromNvmMirrorEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastBatState[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastBatState[0]);
   }
}

void PUTucLastBatteryStateToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastBatState[(i)] = (x);
   }
   else{
   }
}

uint8 GETucLastSNRFromNvmMirrorEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastSNR[(i)]);
   }
   else{

      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastSNR[0]);
   }
}

void PUTucLastSNRToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucLastSNR[(i)] = (x);
   }
   else{
   }
}

uint8 GETucTimeSinceLastRecEventFromNvmMirrorEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucTimeSinceLastRecEv[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucTimeSinceLastRecEv[0]);
   }
}

void PUTucTimeSinceLastRecEventToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucTimeSinceLastRecEv[(i)] = (x);
   }
   else{
   }
}

uint8 GETucLastPosChangedInfoFromNvmMirrorEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucLastIdChangedInfo);
}

void PUTucLastPosChangedInformationToNvmMirrorEE(Rte_Instance self, uint8 ucLastIdChangedInfo)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucLastIdChangedInfo = ucLastIdChangedInfo;
}

TAmbientValueType GETscTAmbValEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->scTAmbientValue);
}

void PUTscTAmbValEE(Rte_Instance self, TAmbientValueType x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->scTAmbientValue = (x);
}

TAmbientFilterValueType GETsshTAmbFiltValEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->sshTAmbientFilterValue);
}

void PUTsshTAmbFiltValEE(Rte_Instance self, TAmbientFilterValueType x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->sshTAmbientFilterValue = (x);
}

TAmbientFilterFactorValueType GETucTAmbFiltFactValEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucTAmbientFilterFactorValue);
}

void PUTucTAmbFiltFactValEE(Rte_Instance self, TAmbientFilterFactorValueType x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucTAmbientFilterFactorValue = (x);
}

uint8 GETucPAmbValEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucPAmbientValue);
}

void PUTucPAmbValEE(Rte_Instance self, uint8 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucPAmbientValue = (x);
}

uint8 GETucAipEngDrvEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucAipEngDrv);
}

void PUTucAipEngDrvEE(Rte_Instance self, Rdci_AIP_ENG_DRV_Type x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucAipEngDrv = (x);
}

uint16 GETushPositionAltitudeEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushPositionAltitude);
}

void PUTushPositionAltitudeEE(Rte_Instance self, Rdci_GNSSPositionAltitude_Type x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushPositionAltitude = (x);
}

uint16 GETushErrorAltitudeMetersEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushErrorAltitudeMeters);
}

void PUTushErrorAltitudeMetersEE(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushErrorAltitudeMeters = (x);
}

uint16 GETushGpsTioTicksEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushGpsTioTicks);
}

void PUTushGpsTioTicksEE(Rte_Instance self, uint16 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ushGpsTioTicks = (x);
}

uint8 GETucAipGpsStateEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucAipGpsState);
}

void PUTucAipGpsStateEE(Rte_Instance self, uint8 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucAipGpsState = (x);
}

uint16 GETushFilDetMIsoEE(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushFilDetMIso[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushFilDetMIso[0]);
   }
}

void PUTushFilDetMIsoEE(Rte_Instance self, uint16 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aushFilDetMIso[(i)] = (x);
   }
   else{
   }
}

uint8 GETucFilDetActiveEE(Rte_Instance self)
{
   return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucFilDetActive);
}

void PUTucFilDetActiveEE(Rte_Instance self, uint8 x)
{
   ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucFilDetActive = (x);
}

uint8 GETucFilDetRecFlag(Rte_Instance self, uint8 i)
{
   if(i < cAnzRad){
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucFilDetRecFlag[(i)]);
   }
   else{
      return( ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucFilDetRecFlag[0]);
   }
}

void PUTucFilDetRecFlag(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cAnzRad){
    ((tCommonNvmBlockType *) (void*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->aucFilDetRecFlag[(i)] = (x);
   }
   else{
   }
}

uint8 GETucFBD4CountEE(Rte_Instance self)
{
   return(((tCommonNvmBlockType *)(void*)Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucFBD4Count);
}

void PUTucFBD4CountEE(Rte_Instance self, uint8 x)
{
   ((tCommonNvmBlockType *)(void*)Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->ucFBD4Count = (x);
}

sint32 GETslOATavgEE(Rte_Instance self)
{
   return(((tCommonNvmBlockType *)(void*)Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->slOATavg);
}

void PUTslOATavgEE(Rte_Instance self, sint32 x)
{
   ((tCommonNvmBlockType *)(void*)Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data)->slOATavg = (x);
}

boolean bGetCommonBlockUpdateFlagEE(void)
{
   return bBlockNeedsUpdate;
}

void SetCommonBlockUpdateFlagEE(void)
{
   bBlockNeedsUpdate = TRUE;
}

void ClearCommonBlockUpdateFlagEE(void)
{
   bBlockNeedsUpdate = FALSE;
}

static void CompareValuesAndSetUpdateFlagEE(uint8 ucOld, uint8 ucNew)
{
   if(ucNew != ucOld){
    bBlockNeedsUpdate = TRUE;
   }
}

