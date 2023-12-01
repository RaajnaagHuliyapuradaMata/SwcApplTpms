#ifndef _hs_inaktivereignis_X_H
#define _hs_inaktivereignis_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cMaxSizeIeFiFo 3
#define cIeFiFoEmpty   (uint8)0xFE

 #define cDtcInvalid ( (uint8) 255u)

typedef enum{
  cDtcWuMuteFl = 0,
  cDtcWuMuteFr,
  cDtcWuMuteRl,
  cDtcWuMuteRr,
  cDtcUnspecifiedWuMute,
  cDtcWuDefectFl,
  cDtcWuDefectFr,
  cDtcWuDefectRl,
  cDtcWuDefectRr,
  cDtcBandmode,
  cDtcAutoLearningFailed,
  cDtcGatewayOrAntennaError,
  cDtcInputMissing,
  cDtcInputInvalid,
  cDtcInputAliveError,
  cDtcInputCrcError,
  cDtcRdciRfExternalInterference,
  cDtcSpeedSignalFailure,
  cDtcUnspecifiedWfcDefect,
  cDtcGatewayOrAntennaError2ndFBD,
  cDtcGatewayOrAntennaErrorAllFBD,
  cDtcDataPackageError1stFBD,
  cDtcDataPackageError2ndFBD,
  cDtcDataPackageErrorAllFBD,
  cDtc4WrongWuMounted,
  cDtc1To3WrongWuMounted,
  cDtcWuLocalisationFailed,
  cDtcRdciOtherWuSensorType,
  cDtcWuLowBatteryFl,
  cDtcWuLowBatteryFr,
  cDtcWuLowBatteryRl,
  cDtcWuLowBatteryRr
}tWuErrors;

typedef struct{
  uint8 ucErrorNumber;
  uint8 ucIeSent;
}strIeFiFo;

extern void ReadInaktivereignisDS(Rte_Instance self, uint8 * paucData);
extern void ProcessIeFiFoDS(Rte_Instance self);
extern void InitIeFiFoDS(Rte_Instance self);
extern void IeFiFoWriteEntryDS(Rte_Instance self, uint8 ucErrorNumber);
extern void ClearIeFifoDS(Rte_Instance self);
extern uint8 GetCurrentInactiveReasonDS(void);

#ifdef __cplusplus
}
#endif

#endif

