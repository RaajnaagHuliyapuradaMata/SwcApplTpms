#ifndef _wu_monitoring_H
#define _wu_monitoring_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "WuMonitoringX.h"

#define cBAT_UNKNOWN                0
#define cBAT_LOW                    1
#define cBAT_OK                     2

typedef struct{
  uint16    ushTimerBlockFail;
  uint16    ushTimerSingleFail;
  uint16    ushCountGood;
  uint16    ushCountMissing;
  uint16    ushCountDefect;
  uint8     ucCountLoBat;

  uint8     ucLocPossible;
  uint8     ucForeignSupplier;
}tWuMonitoringData;

static uint8 ucWheelUnitMonitoringIsActiveWUM(void);
static boolean bGoodCounterReachedMaximumWUM(void);
static uint32 FilterSubsequentErrorsWUM( uint32 ulErrorBits);
static void CheckLowBatWUM(Rte_Instance self, const ImpTypeRecCddRdcData* rdcData, uint8 ucCol, uint8 ucWP);
static void CheckDefectWUM(Rte_Instance self, const ImpTypeRecCddRdcData* rdcData, uint8 ucCol, uint8 ucWP);
static void CheckWrongWuMountedWUM(Rte_Instance self);
static void CheckForeignSupplierWUM(Rte_Instance self);
static void ClearRFInterferenceWUM(Rte_Instance self);
static void ClearGatewayAntennaWUM(Rte_Instance self, uint8 DpNo);
static void ClearDefectWUM(Rte_Instance self, uint8 ucCol, uint8 ucWP);
static void ClearLowBatWUM(Rte_Instance self);
static void SetMuteErrorStatusWUM(Rte_Instance self);
static boolean bWuIsDownForCountWUM( uint8 ucCol);
static boolean bCheckMuteMonitorActive(void);
static void ClearTimeSinceLastRecEventWUM(Rte_Instance self, uint8 ucCol);
static void IncTimeSinceLastRecEventWUM(Rte_Instance self, uint8 ucCol);
static uint16 ushGetTimeSinceLastRxWUM( uint8 ucCol);

#ifdef __cplusplus
}
#endif

#endif
