

#ifndef _nw_monitoring_X_H
#define _nw_monitoring_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#include "datamanagerX.h"

#define cNetworkNoError                           (uint32)0x00000000U
#define cNetwork_RDC_DT_PCKG_MsgMissing           (uint32)0x00000001U
#define cNetwork_RDC_DT_PCKG_AliveError           (uint32)0x00000002U
#define cNetwork_RDC_DT_PCKG_SignalError          (uint32)0x00000004U
#define cNetwork_A_TEMP_MsgMissing                (uint32)0x00000008U
#define cNetwork_A_TEMP_SignalError               (uint32)0x00000010U
#define cNetwork_EINHEITEN_MsgMissing             (uint32)0x00000020U
#define cNetwork_EINHEITEN_SignalError            (uint32)0x00000040U
#define cNetwork_CON_VEH_MsgMissing               (uint32)0x00000080U
#define cNetwork_CON_VEH_CrcError                 (uint32)0x00000100U
#define cNetwork_CON_VEH_AliveError               (uint32)0x00000200U
#define cNetwork_CON_VEH_SignalError              (uint32)0x00000400U
#define cNetwork_RELATIVZEIT_MsgMissing           (uint32)0x00000800U
#define cNetwork_RELATIVZEIT_SignalError          (uint32)0x00001000U
#define cNetwork_ErfsCodingDataInconsistent       (uint32)0x00002000U
#define cNetwork_V_VEH_MsgMissing                 (uint32)0x00100000U
#define cNetwork_V_VEH_CrcError                   (uint32)0x00200000U
#define cNetwork_V_VEH_AliveError                 (uint32)0x00400000U
#define cNetwork_V_VEH_SigQualifError             (uint32)0x00800000U

#define cNetwork_DT_PT_1_MsgMissing               (uint32)0x00004000U
#define cNetwork_DT_PT_1_SignalError              (uint32)0x00008000U
#define cNetwork_UHRZEIT_DATUM_SignalError        (uint32)0x00010000U
#define cNetwork_WMOM_DRV_4_MsgMissing            (uint32)0x00020000U
#define cNetwork_WMOM_DRV_4_SignalError           (uint32)0x00040000U
#define cNetwork_KILOMETERSTAND_SignalError       (uint32)0x00080000U
#define cNetwork_NMEARawData2Part2_MsgMissing     (uint32)0x01000000U
#define cNetwork_NMEARawData2Part2_SignalError    (uint32)0x02000000U
#define cNetwork_NMEARawData2Part3_MsgMissing     (uint32)0x04000000U
#define cNetwork_NMEARawData2Part3_SignalError    (uint32)0x08000000U

#define cPTC_A_TEMP_Missing          (uint8)  0
#define cPTC_A_TEMP_Signal           (uint8)  1
#define cPTC_EINHEITEN_Missing       (uint8)  2
#define cPTC_EINHEITEN_Signal        (uint8)  3
#define cPTC_CON_VEH_Missing         (uint8)  4
#define cPTC_CON_VEH_Crc             (uint8)  5
#define cPTC_CON_VEH_Alive           (uint8)  6
#define cPTC_CON_VEH_Signal          (uint8)  7
#define cPTC_RELATIVZEIT_Missing     (uint8)  8
#define cPTC_RELATIVZEIT_Signal      (uint8)  9
#define cPTC_RDC_DT_Missing          (uint8) 10
#define cPTC_RDC_DT_Alive            (uint8) 11
#define cPTC_RDC_DT_Signal           (uint8) 12
#define cPTC_V_VEH_Missing           (uint8) 13
#define cPTC_V_VEH_Crc               (uint8) 14
#define cPTC_V_VEH_Alive             (uint8) 15
#define cPTC_V_VEH_SigQualif         (uint8) 16

#define cNoError      0
#define cAliveError   1
#define cSignalError  2
#define cCrcError     4

#define cDataPackage12Ix    (uint8)0
#define cDataPackage34Ix    (uint8)1
#define cDP_DUALERROR_MASK  (uint8)0x03
#define cDP_SINGLERROR_MASK (uint8)0x01
#define cGA_SHIFT           (uint8)0x00
#define cDP_AE_SHIFT        (uint8)0x01
#define cDP_SE_SHIFT        (uint8)0x02
#define cDP_TO_SHIFT        (uint8)0x03

typedef struct{
  uint16 ushMsgTimeout;
  uint16 ushSignalErrorTimeout;
  uint8  ucAliveErrorCounter;
  uint8  ucAlvErrGoodCounter;
}tMonitorRDC_DT_PCKG12;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorA_TEMP;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorCounter;
}tMonitorEINHEITEN_BN2020;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucCrcErrorCounter;
  uint8 ucAliveErrorCounter;
  uint8 ucSignalErrorCounter;
}tMonitorCON_VEH;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucCrcErrorTimeout;
  uint8 ucAliveErrorTimeout;
  uint8 ucSigQualifErrorTimeout;
}tMonitorV_VEH;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorBN2020_RELATIVZEIT;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorDT_PT_1;

typedef struct{
  uint8 ucSignalErrorCounter;
}tMonitorFZZSTD;

typedef struct{
  uint16 ushSignalErrorTimeout;
}tMonitorKILOMETERSTAND;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorNMEARawData2Part2;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorNMEARawData2Part3;

typedef struct{
  uint16 ushSignalErrorTimeout;
}tMonitorUHRZEIT_DATUM;

typedef struct{
  uint8 ucMsgTimeout;
  uint8 ucSignalErrorTimeout;
}tMonitorWMOM_DRV_4;

typedef struct{
  tMonitorRDC_DT_PCKG12 tMonRDC_DT_PCKG[2];
  tMonitorA_TEMP tMonA_TEMP;
  tMonitorEINHEITEN_BN2020 tMonEINH_BN2020;
  tMonitorCON_VEH tMonCON_VEH;
  tMonitorBN2020_RELATIVZEIT tMonRELATIVZEIT;
  tMonitorDT_PT_1 tMonDT_PT_1;
  tMonitorFZZSTD tMonFZZSTD;
  tMonitorKILOMETERSTAND tMonKILOMETERSTAND;
  tMonitorNMEARawData2Part2 tMonNMEARawData2Part2;
  tMonitorNMEARawData2Part3 tMonNMEARawData2Part3;
  tMonitorUHRZEIT_DATUM tMonUHRZEIT_DATUM;
  tMonitorWMOM_DRV_4 tMonWMOM_DRV_4;
  tMonitorV_VEH tMonV_VEH;
}tNwMonitoringData;

extern void InitNWM( Rte_Instance self);

extern void TimerTickNWM( Rte_Instance self);

extern uint8 CheckRDC_DT_PCKG12_MsgNWM( Rte_Instance self, const ImpTypeRecCddRdcData* rdcData);

extern uint8 CheckA_TEMP_MsgNWM( Rte_Instance self, Rdci_TEMP_EX_Type tempEx);

extern uint8 CheckEINHEITEN_BN2020_MsgNWM( Rte_Instance self, Rdci_UN_AIP_Type unitAipData, Rdci_UN_TEMP_Type unitTempData);

extern uint8 CheckCON_VEH_MsgNWM( Rte_Instance self, Rdci_CON_VEH_Type conVeh);

extern uint8 CheckV_VEH_MsgNWM( Rte_Instance self, Rdci_V_VEH_Type vVeh);

extern uint8 CheckBN2020_RELATIVZEIT_MsgNWM( Rte_Instance self, Rdci_T_SEC_COU_REL_Type relTime);

extern uint8 CheckUHRZEIT_DATUM_MsgNWM( Rte_Instance self, Rdci_UHRZEIT_DATUM_Type timeDate);

extern uint8 CheckDT_PT_1_MsgNWM( Rte_Instance self, Rdci_AIP_ENG_DRV_Type aip);

extern uint8 CheckNMEARawData2Part2_MsgNWM( Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude);

extern uint8 CheckNMEARawData2Part3_MsgNWM( Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters);

extern uint8 CheckWMOM_DRV_4_MsgNWM( Rte_Instance self, Rdci_WMOM_DRV_4_Type wmom);

extern uint8 CheckFZZSTD_MsgNWM( Rdci_ST_ILK_ERRM_FZM_Type fzzstd);

extern uint8 CheckKILOMETERSTAND_MsgNWM( Rte_Instance self, Rdci_MILE_KM_Type mileKm);

extern uint32 ulGetNetworkErrorsNWM(void);

extern uint32 ulGetNetworkErrChangedFlagsNWM(void);

extern void ClearNetworkErrChangedFlagNWM( uint32 ulDtcBit);

extern void ClearNetworkErrChangedFlagsNWM(void);

extern void ClearNetworkErrorNWM( Rte_Instance self, uint32 ulDtcBit);

extern boolean bGetNetworkErrorNWM( uint32 ulDtcBit);

extern void GetNwMonitoringDataNWM( tNwMonitoringData* data);

extern void SetNetworkErrorNWM( Rte_Instance self, uint32 ulDtcBit);

extern void ClearErrorConditionsNWM( uint8 ucParamToClear);

extern boolean bPrio1ErrorIsSetNWM(void);

extern boolean bRdcDataErrorIsSetNWM(void);

extern boolean bSystemErrorIsSetNWM(void);

extern boolean bRelativzeitMessageFailNWM(void);

extern boolean ResetDataPackageErrorIndNWM(Rte_Instance self, uint8 ShiftValue, uint8 Ix);
extern void SetDataPackageErrorIndNWM(uint8 ShiftValue, uint8 Ix);
extern uint8 GetDataPackageErrorIndNWM(Rte_Instance self, uint8 ShiftValue);

# ifdef __cplusplus
}
# endif

#endif
