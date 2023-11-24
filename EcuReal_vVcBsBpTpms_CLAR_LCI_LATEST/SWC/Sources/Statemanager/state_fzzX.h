#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cKL_15_EIN                ((uint16) 0x0001u)
#define cRS_VTHRES                ((uint16) 0x0002u)
#define cFAHRZEUG_FAEHRT          ((uint16) 0x0004u)
#define cRUECKWAERTSFAHRT         ((uint16) 0x0008u)
#define cFAHRZEUG_LERNT           ((uint16) 0x0010u)
#define cMP_VTHRES                ((uint16) 0x0020u)
#define cNW_DTC_LOCKED            ((uint16) 0x0040u)
#define cTAMBIENT_RED             ((uint16) 0x0100u)
#define cLONG_PARK                ((uint16) 0x0200u)
#define cBM_VTHRES                ((uint16) 0x0400u)
#define cFZZ_ALLE_BITS            ((uint16) 0xFFFFu)
#define cV_MAX_PAL                 (uint8) 150
#define cV_MIN_PAL                 (uint8) 25
#define cV_MIN_BM                  (uint8) 10
#define cV_HYST_BM                 (uint8) 0
#define cV_TH_FAHRZEUG_FAEHRT_SET  (uint8) 2
#define cV_TH_FAHRZEUG_LERNT_SET   (uint8) 20
#define cLONG_PARK_TIME            (uint32) 300
#define GEAR_INIT         (0U)
#define GEAR_NEUTRAL      (2U)
#define GEAR_FORWARD      (4U)
#define GEAR_REVERSE      (5U)
#define GEAR_INVALID      (0xff)
#define cFzzBusState          (uint8)0x01
#define cFzzFSSperre          (uint8)0x02

extern void InitFZZ(void);
extern void SetBitFahrzeugzustandFZZ( uint16 ushBitMask);
extern void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask);
extern boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask);
extern uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask);
extern void EvTerminal15OnFZZ(void);
extern void EvTerminal15OffFZZ(void);
extern void EvVehicleRollingFZZ(void);
extern void EvVehicleStandsStillFZZ(void);
extern void EvReDiagActiveFZZ(void);
extern void EvReDiagInactiveFZZ(void);
extern void EvDriveDirectionForwardFZZ(void);
extern void EvDriveDirectionBackwardFZZ(void);
extern void SETOutdoorTemperatureFZZ( sint8 temperature);
extern sint8 GETscOutdoorTemperatureFZZ(void);
extern void SETSpeedFZZ( uint16 speed);
extern uint16 GETushSpeedFZZ(void);
extern void SetGearFZZ( uint8 gear);
extern uint8 GETucGearFZZ(void);
extern void SETBusStateFZZ( ImpTypeValFrBusState busstate);
extern void SETFehlerspeicherSperreFZZ( Rdci_ST_ILK_ERRM_FZM_Type fssperre);
extern uint8 ucGetFlexrayStatusFZZ(void);
extern uint8 ucGetStatusConditionVehicleFZZ(void);
extern void PutStatusConditionVehicleFZZ( uint8);
extern uint8 ucGetStatusLastConditionVehicleFZZ(void);
extern void ClearStatusLastConditionVehicleFZZ(void);
extern boolean bPwfIsFahrenFZZ(void);

#ifdef __cplusplus
}
#endif
