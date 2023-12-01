#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "TAmbFiltX.h"

typedef struct CommonNvmBlock{
  uint8                         ucInitialize;
  uint8                         ucUnitTemperature;
  uint8                         ucUnitPressure;
  uint8                         ucUnitSpeed;
  Rdci_MILE_KM_Type             ulKm;
  Rdci_UHRZEIT_DATUM_Type       tUhrzeitDatum;
  uint32                        ulTimestamp;
  uint16                        aushCntGoodTel[cAnzRad];
  uint16                        aushCntMissTel[cAnzRad];
  uint16                        aushBlockFailTimer[cAnzRad];
  uint16                        aushSingleFailTimer[cAnzRad];
  uint16                        ushFbd4AliveTimer;
  TAmbientValueType             scTAmbientValue;
  TAmbientFilterValueType       sshTAmbientFilterValue;
  TAmbientFilterFactorValueType ucTAmbientFilterFactorValue;
  uint8                         ucPAmbientValue;
  uint16                        aushFilDetMIso[cAnzRad];
  uint8                         ucFilDetActive;
  uint8                         aucFilDetRecFlag[cAnzRad];
  uint16                        ushCrcCodingData;
  uint8                         aucWheelSensorStatus[cAnzRad];
  uint8                         aucLastTelegramType[cAnzRad];
  uint16                        aushLastPalStatus[cAnzRad];
  uint8                         aucLastBatState[cAnzRad];
  uint8                         aucLastSNR[cAnzRad];
  uint8                         aucTimeSinceLastRecEv[cAnzRad];
  uint8                         ucLastIdChangedInfo;
  uint8                         ucAipEngDrv;
  uint16                        ushPositionAltitude;
  uint16                        ushErrorAltitudeMeters;
  uint16                        ushGpsTioTicks;
  uint8                         ucAipGpsState;
  uint8                         ucFBD4Count;
  sint32                        slOATavg;
}tCommonNvmBlockType;

typedef enum{
  ePRESSURE_UNIT_DEFAULT  = UN_AIP_Default,
  ePRESSURE_UNIT_BAR      = UN_AIP_bar,
  ePRESSURE_UNIT_KPA      = UN_AIP_kPa,
  ePRESSURE_UNIT_PSI      = UN_AIP_psi,
  ePRESSURE_UNIT_INVALID  = UN_AIP_SignalUngueltig
}tPressureUnitType;

typedef enum{
  eTEMPERATURE_UNIT_DEFAULT     = UN_TEMP_Default,
  eTEMPERATURE_UNIT_CELSIUS     = UN_TEMP_DegreeC,
  eTEMPERATURE_UNIT_FAHRENHEIT  = UN_TEMP_DegreeF,
  eTEMPERATURE_UNIT_INVALID     = UN_TEMP_SignalUngueltig
}tTemperatureUnitType;

typedef enum{
  eMILEAGE_UNIT_DEFAULT   = UN_MILE_Default,
  eMILEAGE_UNIT_KILOMETER = UN_MILE_Kilometer,
  eMILEAGE_UNIT_MEILEN    = UN_MILE_Meilen,
  eMILEAGE_UNIT_INVALID   = UN_MILE_SignalUngueltig
}tMileageUnitType;

extern void InitCommonBlockEE(Rte_Instance self);
extern void ClearCommonBlockUpdateFlagEE(void);
extern void SetCommonBlockUpdateFlagEE( void) ;
extern boolean bGetCommonBlockUpdateFlagEE(void);
extern uint8 GETucCommonBlockInitializeEE(Rte_Instance self);
extern void PUTucCommonBlockInitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern tPressureUnitType GETucUnAipEE(Rte_Instance self);
extern void PUTucUnAipEE(Rte_Instance self, tPressureUnitType ucLastUnAip);
extern tTemperatureUnitType GETucUnTempEE(Rte_Instance self);
extern void PUTucUnTempEE(Rte_Instance self, tTemperatureUnitType ucLastUnTemp);
extern tMileageUnitType GETucUnMileEE(Rte_Instance self);
extern void PUTucUnMileEE(Rte_Instance self, tMileageUnitType ucLastUnMile);
extern Rdci_MILE_KM_Type GETulMileKmEE(Rte_Instance self);
extern void PUTulMileKmEE(Rte_Instance self, Rdci_MILE_KM_Type ulLastMileKm);
extern Rdci_UHRZEIT_DATUM_Type GETtTimeDateEE(Rte_Instance self);
extern void PUTtTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x);
extern uint32 GETulTimestampEE(Rte_Instance self);
extern void PUTulTimestampEE(Rte_Instance self, uint32 ulValue);
extern uint16 GETushCntGoodTelEE(Rte_Instance self, uint8 i);
extern void PUTushCntGoodTelEE(Rte_Instance self, uint16 x, uint8 i);
extern uint16 GETushCntMissTelEE(Rte_Instance self, uint8 i);
extern void PUTushCntMissTelEE(Rte_Instance self, uint16 x, uint8 i);
extern uint16 GETushBlockFailTimerEE(Rte_Instance self, uint8 i);
extern void PUTushBlockFailTimerEE(Rte_Instance self, uint16 x, uint8 i);
extern void PUTushSingleFailTimerEE(Rte_Instance self, uint16 x, uint8 i);
extern uint16 GETushFbd4AliveTimerEE(Rte_Instance self);
extern void PUTushFbd4AliveTimerEE(Rte_Instance self, uint16 x);
extern TAmbientValueType GETscTAmbValEE(Rte_Instance self);
extern void   PUTscTAmbValEE(Rte_Instance self, TAmbientValueType x);
extern TAmbientFilterValueType GETsshTAmbFiltValEE(Rte_Instance self);
extern void   PUTsshTAmbFiltValEE(Rte_Instance self, TAmbientFilterValueType x);
extern TAmbientFilterFactorValueType  GETucTAmbFiltFactValEE(Rte_Instance self);
extern void   PUTucTAmbFiltFactValEE(Rte_Instance self, TAmbientFilterFactorValueType x);
extern uint8  GETucPAmbValEE(Rte_Instance self);
extern void   PUTucPAmbValEE(Rte_Instance self, uint8 x);
extern uint8 GETucFilDetActiveEE(Rte_Instance self);
extern void PUTucFilDetActiveEE(Rte_Instance self, uint8 x);
extern uint8 GETucFilDetRecFlag(Rte_Instance self, uint8 i);
extern void PUTucFilDetRecFlag(Rte_Instance self, uint8 x, uint8 i);
extern uint16 GETushCrcCodingDataEE(Rte_Instance self);
extern void PUTushCrcCodingDataEE(Rte_Instance self, uint16 x);
extern uint8 GETucWheelSensorStatusFromNvmMirrorEE(Rte_Instance self, uint8 i);
extern void PUTucWheelSensorStatusToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucLastTelegramTypeFromNvmMirrorEE(Rte_Instance self, uint8 i);
extern void PUTucLastTelegramTypeToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucLastBatteryStateFromNvmMirrorEE(Rte_Instance self, uint8 i);
extern void PUTucLastBatteryStateToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucLastSNRFromNvmMirrorEE(Rte_Instance self, uint8 i);
extern void PUTucLastSNRToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucTimeSinceLastRecEventFromNvmMirrorEE(Rte_Instance self, uint8 i);
extern void PUTucTimeSinceLastRecEventToNvmMirrorEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucLastPosChangedInfoFromNvmMirrorEE(Rte_Instance self);
extern void PUTucLastPosChangedInformationToNvmMirrorEE(Rte_Instance self, uint8 ucLastIdChangedInfo);
extern uint16 GETushLastPalStatusEE(Rte_Instance self, uint8 i);
extern void PUTushLastPalStatusEE(Rte_Instance self, uint16 x, uint8 i);
extern uint16 GETushFilDetMIsoEE(Rte_Instance self, uint8 i);
extern void PUTushFilDetMIsoEE(Rte_Instance self, uint16 x, uint8 i);
extern uint8  GETucAipEngDrvEE(Rte_Instance self);
extern void   PUTucAipEngDrvEE(Rte_Instance self, Rdci_AIP_ENG_DRV_Type x);
extern uint16 GETushPositionAltitudeEE(Rte_Instance self);
extern void   PUTushPositionAltitudeEE(Rte_Instance self, Rdci_GNSSPositionAltitude_Type x);
extern uint16 GETushErrorAltitudeMetersEE(Rte_Instance self);
extern void   PUTushErrorAltitudeMetersEE(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type x);
extern uint16 GETushGpsTioTicksEE(Rte_Instance self);
extern void   PUTushGpsTioTicksEE(Rte_Instance self, uint16 x);
extern uint8  GETucAipGpsStateEE(Rte_Instance self);
extern void   PUTucAipGpsStateEE(Rte_Instance self, uint8 x);
extern uint8  GETucFBD4CountEE(Rte_Instance self);
extern void   PUTucFBD4CountEE(Rte_Instance self, uint8 x);
extern sint32  GETslOATavgEE(Rte_Instance self);
extern void   PUTslOATavgEE(Rte_Instance self, sint32 x);

#ifdef __cplusplus
}
#endif
