#ifndef SecondaryDTCX_h
#define SecondaryDTCX_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cSecondaryNoError                 (uint32)0x00
#define cSecondaryRdciKalibrierung        (uint32)0x01
#define cSecondaryRdciAusfall             (uint32)0x02
#define cSecondaryRdciBefuellhinweis      (uint32)0x04
#define cSecondaryRdciDruckwarnung        (uint32)0x08
#define cSecondaryRdciPannenwarnung       (uint32)0x10
#define cSecondaryRdciWarnruecknahme      (uint32)0x20
#define cRDC_SENSOR_HERSTELLER            (uint32)0x00001u
#define cRDC_REFERENZ_AUSSENTEMPERATUR    (uint32)0x00002u
#define cRDC_AUSSENDRUCK                  (uint32)0x00004u
#define cRDC_REIFENDRUCK_VL               (uint32)0x00008u
#define cRDC_REIFENDRUCK_VR               (uint32)0x00010u
#define cRDC_REIFENDRUCK_HL               (uint32)0x00020u
#define cRDC_REIFENDRUCK_HR               (uint32)0x00040u
#define cRDC_REIFENTEMPERATUR_VL          (uint32)0x00080u
#define cRDC_REIFENTEMPERATUR_VR          (uint32)0x00100u
#define cRDC_REIFENTEMPERATUR_HL          (uint32)0x00200u
#define cRDC_REIFENTEMPERATUR_HR          (uint32)0x00400u
#define cRDC_AKTUELLE_AUSSENTEMPERATUR    (uint32)0x00800u
#define cRDC_INAKTIV_STATUS               (uint32)0x01000u
#define cRDC_KALIBRIERUNG_STATUS          (uint32)0x02000u
#define cRDC_STATUS                       (uint32)0x04000u
#define cRDC_KONFIGURATION                (uint32)0x08000u
#define cRDC_SOLLDRUCK_VORN               (uint32)0x10000u
#define cRDC_SOLLDRUCK_HINTEN             (uint32)0x20000u
#define cRDC_POSITION                     (uint32)0x40000u

typedef struct{
  uint8 ucErrorNumber;
  uint8 ucCausingWheelPos;
}strSecondaryDtcFiFo;

extern uint8 GetSecondaryErrorsSCD(void);
extern void SetSecondaryErrorSCD( uint8 ucError);
extern void ClearSecondaryErrorSCD( uint8 ucError);
extern void SetSecondaryErrChangedFlagSCD( uint8 ucError);
extern void ClearSecondaryErrChangedFlagSCD( uint8 ucError);
extern void ClearSecondaryErrChangedFlagsSCD(void);
extern uint8 GetSecondaryErrChangedFlagsSCD(void);
extern void InitSecondaryDtcFiFoSCD(void);
extern void SecondaryDtcFiFoShiftSCD(uint8* pucError, uint8* pucWheelPos);
extern void SecondaryDtcFiFoGetFirstEntrySCD( uint8* pucError, uint8* pucWheelPos);
extern void SecondaryDtcFiFoWriteEntrySCD( uint8 ucDtc, uint8 ucPos);

#ifdef __cplusplus
}
#endif

#endif
