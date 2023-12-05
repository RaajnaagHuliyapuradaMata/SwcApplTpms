#ifndef datamanagerX_h
#define datamanagerX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"
#include "Rte_CtApHufTpmsSWC_Type.h"

#define cReAkPresError        ((RawSensorTyrePresType) 0x00)
#define cReAkPresUnderflow    ((RawSensorTyrePresType) 0x01)
#define cReAkPresOverflow     ((RawSensorTyrePresType) 0xff)
#define cReAkPresMaxVal       ((RawSensorTyrePresType) 0xFC)
#define cReAkTempError        ((RawSensorTyreTempType) 0x00)
#define cReAkTempUnderflow    ((RawSensorTyreTempType) 0x01)
#define cReAkTempOverflow     ((RawSensorTyreTempType) 0xf0)
#define cReHufAkTempUnderflow ((RawSensorTyreTempType) 0x0C)
#define cReHufAkTempOverflow  ((RawSensorTyreTempType) 0xB1)
#define cBATTERY_STATUS_MASK_PAL    0x3C
#define cBATTERY_STATUS_MASK_OTHER  0x7F
#define cBATTERY_STATUS_UNKNOWN     0xffU
#define cRdcDataAvailable     0x00
#define cQueueBusy            0xffU
#define cAGS_AipSigRec          ((uint8)  0x01u)
#define cAGS_AipSigValid        ((uint8)  0x02u)
#define cAGS_GpsAltSigRec       ((uint8)  0x04u)
#define cAGS_GpsAltSigValid     ((uint8)  0x08u)
#define cAGS_GpsErrAltSigRec    ((uint8)  0x10u)
#define cAGS_GpsErrAltSigValid  ((uint8)  0x20u)
#define cAGS_GpsAltSigTio       ((uint8)  0x80u)
#define cAGS_TioTimerTicksSec   ((uint16)  1800)
#define cAGS_AccuracyThresDm    ((uint16) 20000)
#define cAGS_AipDefaultVal      ((uint8)     40)
#define cAGS_0Mtr               ((uint16)     0)
#define cAGS_2500Mtr            ((uint16)  2500)
#define cAGS_5000Mtr            ((uint16)  5000)
#define cAGS_Pat0Mtr            ((uint16)  1013)
#define cAGS_Pat2500Mtr         ((uint16)   750)
#define cAGS_Pat5000Mtr         ((uint16)   540)

typedef enum{
  eParkenWohnen         = 0,
  eWohnenFahren         = 1,
  eFahrenWohnen         = 2,
  eWohnenParken         = 3,
  eParkenStandfunktion  = 4,
  eStandFktParken       = 5,
  ePWFInvalid           = 0xff
}ePWFStateTransitions;

extern void InitRDCiEepromDM(Rte_Instance self);
extern void InitRDCiFunctionsPartOneDM(Rte_Instance self);
extern void InitRDCiFunctionsPartTwoDM(Rte_Instance self);
extern void CyclicRDCiFunctionDM(Rte_Instance self);
extern uint8 ucNewReDataDM(Rte_Instance self, ImpTypeRecCddRdcData tReData);
extern uint8 ucCalcBatteryLevelDM( const ImpTypeRecCddRdcData* rdcData);
extern boolean CheckPrepareTyreSelectionDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow, const uint8 ucSeason, const uint8 Selection);
extern void SetSolldruckDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow);
extern void SetLoadStateDM( const uint8 LoadState);
extern uint8 GetLoadStateDM(void);
extern void SetSeasonDM( const uint8 Season);
extern uint8 GetSeasonDM(void);
extern void SetSummerTyreIndexDM( const uint8 Index);
extern uint8 GetSummerTyreIndexDM(void);
extern void SetWinterTyreIndexDM( const uint8 Index);
extern uint8 GetWinterTyreIndexDM(void);
extern void SetLengthOfTyreListDM( const uint8 Length);
extern uint8 GetLengthOfTyreListDM(void);
extern void SetSelectedTyreIndexDM( const uint8 Index);
extern uint8 GetSelectedTyreIndexDM(void);
extern void SetIDRMessageCenterDM( const uint8 Idr);
extern uint8 GetIDRMessageCenterDM(void);
extern void SetStatusManSelectionDM( const uint8 MaSel);
extern uint8 GetStatusManSelectionDM(void);
extern boolean CompareReDimErfsDM(Rte_Instance self, const uint8* ConvRidData);
extern void SaveRidWeDataDM(Rte_Instance self, ImpTypeRecCddRdcData tReData);
extern uint8 GetSizeOfTyreListElementDM(void);
extern uint8 GetDefaultLoadCondDM(void);
extern uint8  ucGetRePckgIdDM( uint8 ucSlotNo);
extern uint32 ulGetReIdDM( uint8 ucSlotNo);
extern uint8  ucGetReSuppIdDM( uint8 ucSlotNo);
extern PhySensorTyrePresType ucGetRePressureRelDM( uint8 ucSlotNo);
extern PhySensorTyreTempType scGetReTemperatureCentDM( uint8 ucSlotNo);
extern uint8 ucGetRePalLookBackTimeDM( uint8 ucSlotNo);
extern uint16 ushGetRePalStatusDM( uint8 ucSlotNo);
extern uint8 ucGetTelRssiLevelDM( uint8 ucSlotNo);
extern uint8 ucGetReBatteryLevelDM( uint8 ucSlotNo);
extern uint8 ucGetRfBackgroundNoiseLevelDM(void);
extern void PutRePckgIdDM( uint8 ucSlotNo, uint8 ucPckgId);
extern void PutReIdDM( uint8 ucSlotNo, uint32 ulId);
extern void PutReSuppIdDM( uint8 ucSlotNo, uint8 ucSuppId);
extern void PutRePressureRelDM( uint8 ucSlotNo, PhySensorTyrePresType ucPressure);
extern void PutReTemperatureCentDM( uint8 ucSlotNo, PhySensorTyreTempType scTemperature);
extern void PutRePalLookBackTimeDM( uint8 ucSlotNo, uint8 ucPalLookBackTime);
extern void PutRePalStatusDM( uint8 ucSlotNo, uint16 ushPalStatus);
extern void PutTelRssiLevelDM( uint8 ucSlotNo, uint8 ucRssi);
extern void PutReBatteryLevelDM( uint8 ucSlotNo, uint8 ucBatLevel);
extern void PutRfBackgroundNoiseLevelDM( const ImpTypeRecCddRdcData* rdcData);
extern PhySensorTyrePresType ucGetValidTyrePressureRelAtWheelPosDM( uint8 ucWheelPos);
extern PhySensorTyreTempType scGetValidTyreTemperatureAtWheelPosDM( uint8 ucRadPos);
extern void GetWarnThresDM( uint8 ucHistSlot, uint8 ucWarnType, uint8* ucSetLevel, uint8* ucResetLevel);
extern uint8 SetParkenWohnenFahrenDM( Rdci_CON_VEH_Type tPWF);
extern void SetExternalTemperatureDM(Rte_Instance self, uint8 tempEx);
extern void SetExternalPressureDM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type pressEx, uint8 ucError);
extern void SetUnitMileDM(Rte_Instance self, uint8 unitMile);
extern void SetUnitTempDM(Rte_Instance self, uint8 unitTemp);
extern void SetUnitAipDM(Rte_Instance self, uint8 unitAip);
extern void SetTimeDateDM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type currentTimeDate);
extern void SetStopTimeDM(Rte_Instance self, StbMB_SystemTimeType currentTimestamp);
extern void SetStbMBSyncStateDM( boolean bSync);
extern void SetMileageDM(Rte_Instance self, Rdci_MILE_KM_Type mileKm);
extern void SetGNSSPositionAltitudeDM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude, uint8 ucError);
extern void SetGNSSErrorAltitudeMetersDM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters, uint8 ucError);
extern uint8 ucSetRdcDataDM( const ImpTypeRecCddRdcData* data, uint8 ucType);
extern uint8 ucGetRdcDataDM( ImpTypeRecCddRdcData* data, uint8* ucType);
extern void RdcDataWaitingTimerTickDM(void);
extern void ExternalTemperatureTimerTickDM(void);
extern void CopyPressAndTempFromZOMDM(Rte_Instance self);
extern void SetHistoryChangeBitsDM(Rte_Instance self);
extern void InitAfterKl15OnDM(void);
extern void InitAfterKl15OffDM(void);
extern void SetTarPTyrDisplayValueDM(Rte_Instance self, const uint8 LoadState, const uint8 TyreListRow, const uint8 IdrSel);
extern uint16 GetTarPTyrDisplayValueDM( uint8 WheelPos);
extern void CheckTyreChangedDM(Rte_Instance self);
extern void SaveCurrentTyreSelectionDM(Rte_Instance self);
extern void ResetCurrentTyreSelectionDM(Rte_Instance self);
extern void GetDateStringDM( uint16 ushYearHex, uint8 ucMonthHex, uint8 ucDayHex, uint8* szDate, uint8 ucSize);
extern void GetTimeStringDM( uint8 ucHourHex, uint8 ucMinutesHex, uint8 ucSecondsHex, uint8* szTime, uint8 ucSize);
extern uint8 ChangeHpaTo25mBar( uint16 ushHectopascal);
extern uint16 Change25mBarToHpa( uint8 ucHex);
extern void ClearStopTimeDM(void);
extern uint32 ulGetStopTimeDM(void);
extern boolean bGetStbMBSyncStateDM(void);
extern void IncreaseRdcEventCounterDM(void);
extern uint8 ucGetRdcEventCounterDM(void);
extern void ClearLastReceivedReDataArraysDM(void);
extern void DegradeToManSelectionDM(Rte_Instance self, boolean bOtherTyre);
extern uint16 ushGetMaxValueDM( uint16 ushVal1, uint16 ushVal2);
extern boolean CheckTyreChangedOnRearAxleDM(void);
extern void SaveCurTyreListDataInNvmDM(Rte_Instance self, uint8 Season, uint8 TyreListRow);
extern void PutStWheelTypeChangeEventDM(uint8 Det, uint8 Pos);
extern uint8 GetStWheelTypeChangeDetEventDM(uint8 index);
extern uint8 GetStWheelTypeChangePosDM(void);
extern void CopyStWheelTypeChangeBufAndRestartTimerDM(void);
extern void ClearStWheelTypeChangeBuf(void);
extern void SetStWheelTypeChangedAtLocDM(uint8 IdChangedBits, uint8 ucWpChangedBits);
extern uint8 GetStWheelTypeChangedDetStateDM(void);
extern void GetAipGpsValDM_debug(Rte_Instance self, uint8 * pucAipEngDrv, uint16 * pushPositionAltitude, uint16 * pushErrorAltitudeMeters, uint16 * pushGpsTioTicks, uint8 * pucAipGpsState);
extern void   SetSysTimeDM( uint32 ulSysTime);
extern uint32 ulGetSysTimeDM(void);
extern boolean CheckReIdLatelyProcBufDM(const uint32 ReID);
extern void DeleteReIdLatelyProcBufDM(void);
extern void WriteReIdLatelyProcBufDM(const uint32 ReID);
#ifdef __cplusplus
}
#endif

#endif
