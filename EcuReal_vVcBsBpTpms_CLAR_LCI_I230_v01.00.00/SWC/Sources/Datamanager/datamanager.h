#ifndef datamanager_h
#define datamanager_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "DataManagerX.h"
#include "WallocX.h"
#include "abs_linX.h"

#define cInit     (uint8)0
#define cCarStop  (uint8)1
#define cCarDrive (uint8)2
#define cTEL_WAIT_TIME  (cTelegramWaitingTime / 10)
#define cReIdProcBufTimeLimit (uint8)100

typedef struct{
  ImpTypeRecCddRdcData tRdcData;
  uint8 ucType;
  uint8 ucWaitingTime;
}tRdcDataQueue;

typedef struct{
  uint32 ulReId;
  uint8 ucTimeCt;
}tProcIdBufType;

static uint8 ucConvAkAbsPressureInRelDM( uint8 ucRawPres, PhySensorTyrePresType* pucPhyPres, uint8 ucPamb);
static uint8 ucConvAkTemperatureInCentDM( uint8 ucRawTemp, PhySensorTyreTempType* pscPhyTemp);
static uint8 ucCalcSignalToNoiseRatio(uint8 ucTelRssi, uint8 ucBackgroundNoise);
static boolean CompareAllDataToErfsDM(const uint8* pConvRidData, uint8* pIxArray);
static void CompareTyreDimToErfsDM(const uint8* pConvRidData, uint8* pIxArray);
static void CompareLoadIxToErfsDM(const uint8* pConvRidData, uint8* pIxArray);
static void CompareSpeedIxToErfsDM(const uint8* pConvRidData, uint8* pIxArray);
static boolean ComparePressValOfMatchingErfsEntriesDM(const uint8* pIxArray);
void CheckTirePressureDM( Rte_Instance self, uint8 ucSlotNo, uint8 ucWheelPos, PhySensorTyrePresType ucPressure, sint8 scTemperature);
void TransferWarnStateToTpmsMsgManOnCycEventDM( Rte_Instance self);

# ifdef __cplusplus
}
# endif

#endif
