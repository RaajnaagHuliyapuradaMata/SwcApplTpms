

#ifndef _nw_monitoring_H
#define _nw_monitoring_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "NwMonitoringX.h"

#define cRDC_DT_PCKG12_MSG_TOUT     360
#define cRDC_DT_PCKG12_SIG_TOUT     360
#define cA_TEMP_MSG_TOUT             60
#define cA_TEMP_SIG_TOUT             60
#define cEINHEITEN_BN2020_MSG_TOUT   60
#define cCON_VEH_MSG_TOUT             3
#define cBN2020_RELATIVZEIT_MSG_TOUT 30
#define cBN2020_RELATIVZEIT_SIG_TOUT 30
#define cDT_PT_1_MSG_TOUT            60
#define cDT_PT_1_SIG_TOUT            60
#define cNMEARawData2Part2_MSG_TOUT  60
#define cNMEARawData2Part2_SIG_TOUT  60
#define cNMEARawData2Part3_MSG_TOUT  60
#define cNMEARawData2Part3_SIG_TOUT  60
#define cUHRZEIT_DATUM_SIG_TOUT     300
#define cKILOMETERSTAND_SIG_TOUT    300
#define cWMOM_DRV_4_MSG_TOUT          3
#define cWMOM_DRV_4_SIG_TOUT          3
#define cV_VEH_MSG_TOUT              30
#define cV_VEH_ALIVE_TOUT            30
#define cV_VEH_CRC_TOUT              30
#define cV_VEH_SIGQUALIF_TOUT        30

#define cUHRZEIT_DATUM_SIG_TOUT_OFF   0xffffU
#define cKILOMETERSTAND_SIG_TOUT_OFF  0xffffU

#define cEINHEITEN_BN2020_SIG_CNT    50
#define cCON_VEH_SIG_CNT             15
#define cCON_VEH_CRC_CNT             15
#define cCON_VEH_ALV_CNT             15
#define cRDC_DT_PCKG12_ALV_CNT        4
#define cRDC_DT_PCKG12_ALV_GOOD_CNT   2

#define E2E_STATUS_OK              0x00
#define E2E_STATUS_NO_NEW_DATA     0x01
#define E2E_STATUS_WRONG_CRC       0x02
#define E2E_STATUS_SYNC            0x03
#define E2E_STATUS_INITIAL         0x04
#define E2E_STATUS_REPEATED        0x08
#define E2E_STATUS_OK_SOME_LOST    0x20
#define E2E_STATUS_WRONG_SEQUENCE  0x40
#define E2E_STATUS_DATA_INVALID    0x80

#ifdef _EcuVirtual
#else
static uint32 FilterSubsequentErrorsNWM(uint32 ulErrorBits);

static uint8 CheckRDC_DT_PCKG12_AliveNWM(Rte_Instance self, uint8 ucAlive1, uint8 ucAlive2, uint8 DpNo);
static uint8 CheckRDC_DT_PCKG12_SignalNWM(Rte_Instance self, uint16 ushRdcMesTstmp, uint8 DpNo);
static uint8 CheckA_TEMP_SignalNWM(Rte_Instance self, Rdci_TEMP_EX_Type tempEx);
static uint8 CheckEINHEITEN_BN2020_SignalNWM(Rte_Instance self, Rdci_UN_AIP_Type unitAip, Rdci_UN_TEMP_Type unitTemp);
static uint8 CheckCON_VEH_SignalNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh);
static uint8 CheckCON_VEH_CrcNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh);
static uint8 CheckCON_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive);
static uint8 CheckBN2020_RELATIVZEIT_SignalNWM(Rte_Instance self, Rdci_T_SEC_COU_REL_Type relTime);
static uint8 CheckDT_PT_1_SignalNWM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type aip);
static uint8 CheckUHRZEIT_DATUM_SignalNWM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type timeDate);
static uint8 CheckWMOM_DRV_4_SignalNWM(Rte_Instance self, Rdci_WMOM_DRV_4_Type wmom);
static uint8 CheckKILOMETERSTAND_SignalNWM(Rte_Instance self, Rdci_MILE_KM_Type mileKm);
static uint8 CheckNMEARawData2Part2_SignalNWM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude);
static uint8 CheckNMEARawData2Part3_SignalNWM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters);
static uint8 CheckV_VEH_SigQualifNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh);
static uint8 CheckV_VEH_CrcNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh);
static uint8 CheckV_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive);
#endif

#ifdef __cplusplus
}
#endif

#endif
