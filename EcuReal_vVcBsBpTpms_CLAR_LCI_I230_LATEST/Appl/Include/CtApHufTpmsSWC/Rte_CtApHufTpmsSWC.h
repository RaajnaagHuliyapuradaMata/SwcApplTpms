#ifndef Rte_CtApHufTpmsSWC_h
#define Rte_CtApHufTpmsSWC_h

#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************/
/* File   : Rte_CtApHufTpmsSWC.h                                              */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Rte_CtApHufTpmsSWC_Type.h"
#include "Rte_DataHandleType.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct Rte_PDS_CtApHufTpmsSWC_NvMService_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetDataIndex) (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) DataIndex);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetErrorStatus) (P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorStatus);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_ReadBlock) (P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_SetDataIndex) (uint8 DataIndex);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_SetRamBlockStatus) (boolean BlockStatus);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_WriteBlock) (P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data);
};

typedef P2CONST(ImpTypeRecCRdciErfsReifenEco, AUTOMATIC, RTE_CONST_DEFAULT_RTE_CALPRM_GROUP) Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciErfsReifenEco_FncRetPtrType;
typedef P2CONST(uint8, AUTOMATIC, RTE_CONST_DEFAULT_RTE_CALPRM_GROUP) Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciLearnLocateConfig_FncRetPtrType;
typedef P2CONST(uint8, AUTOMATIC, RTE_CONST_DEFAULT_RTE_CALPRM_GROUP) Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciTrefSeasAdjConfig_FncRetPtrType;

struct Rte_PDS_CtApHufTpmsSWC_PiCalPrmRDCi_R{
   P2FUNC(ImpTypeValCRdciCorHoldOffTime,                                                 RTE_CODE, Prm_CRdciCorHoldOffTime                      )(void);
   P2FUNC(ImpTypeValCRdciDefaultLoadCond,                                                RTE_CODE, Prm_CRdciDefaultLoadCond                     )(void);
   P2FUNC(ImpTypeValCRdciDefaultMenuSel,                                                 RTE_CODE, Prm_CRdciDefaultMenuSel                      )(void);
   P2FUNC(ImpTypeValCRdciDeltaPLR,                                                       RTE_CODE, Prm_CRdciDeltaPLR                            )(void);
   P2FUNC(ImpTypeValCRdciDispConfTimeout,                                                RTE_CODE, Prm_CRdciDispConfTimeout                     )(void);
   P2FUNC(ImpTypeValCRdciDispReset,                                                      RTE_CODE, Prm_CRdciDispReset                           )(void);
   P2FUNC(ImpTypeValCRdciDpToIPmin,                                                      RTE_CODE, Prm_CRdciDpToIPmin                           )(void);
   P2FUNC(ImpTypeValCRdciDtAmbPrewarn,                                                   RTE_CODE, Prm_CRdciDtAmbPrewarn                        )(void);
   P2FUNC(ImpTypeValCRdciEcoRcpEnable,                                                   RTE_CODE, Prm_CRdciEcoRcpEnable                        )(void);
   P2FUNC(ImpTypeValCRdciErfsEnable,                                                     RTE_CODE, Prm_CRdciErfsEnable                          )(void);
   P2FUNC(ImpTypeValCRdciErfsPlacardSource,                                              RTE_CODE, Prm_CRdciErfsPlacardSource                   )(void);
   P2FUNC(Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciErfsReifenEco_FncRetPtrType,     RTE_CODE, Prm_CRdciErfsReifenEco                       )(void);
   P2FUNC(ImpTypeValCRdciFastDeflateEnable,                                              RTE_CODE, Prm_CRdciFastDeflateEnable                   )(void);
   P2FUNC(Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciLearnLocateConfig_FncRetPtrType, RTE_CODE, Prm_CRdciLearnLocateConfig                   )(void);
   P2FUNC(ImpTypeValCRdciLongHoldTime,                                                   RTE_CODE, Prm_CRdciLongHoldTime                        )(void);
   P2FUNC(ImpTypeValCRdciMaxCorRcp,                                                      RTE_CODE, Prm_CRdciMaxCorRcp                           )(void);
   P2FUNC(ImpTypeValCRdciMaxCorTime,                                                     RTE_CODE, Prm_CRdciMaxCorTime                          )(void);
   P2FUNC(ImpTypeValCRdciMaxThreshold,                                                   RTE_CODE, Prm_CRdciMaxThreshold                        )(void);
   P2FUNC(ImpTypeValCRdciMinRcpFa,                                                       RTE_CODE, Prm_CRdciMinRcpFa                            )(void);
   P2FUNC(ImpTypeValCRdciMinRcpRa,                                                       RTE_CODE, Prm_CRdciMinRcpRa                            )(void);
   P2FUNC(ImpTypeValCRdciNumPrewarnDetect,                                               RTE_CODE, Prm_CRdciNumPrewarnDetect                    )(void);
   P2FUNC(ImpTypeValCRdciPInitRangeMax,                                                  RTE_CODE, Prm_CRdciPInitRangeMax                       )(void);
   P2FUNC(ImpTypeValCRdciPanneBefPos,                                                    RTE_CODE, Prm_CRdciPanneBefPos                         )(void);
   P2FUNC(ImpTypeValCRdciPanneTh,                                                        RTE_CODE, Prm_CRdciPanneTh                             )(void);
   P2FUNC(ImpTypeValCRdciParkSupExtParkSupConfig,                                        RTE_CODE, Prm_CRdciParkSupExtParkSupConfig             )(void);
   P2FUNC(ImpTypeValCRdciParkSupMobilityLossThresholdValue,                              RTE_CODE, Prm_CRdciParkSupMobilityLossThresholdValue   )(void);
   P2FUNC(ImpTypeValCRdciParkSupNotificationThresholdValueC,                             RTE_CODE, Prm_CRdciParkSupNotificationThresholdValueC  )(void);
   P2FUNC(ImpTypeValCRdciParkSupNotificationThresholdValueNc,                            RTE_CODE, Prm_CRdciParkSupNotificationThresholdValueNc )(void);
   P2FUNC(ImpTypeValCRdciParkSupTolNoTempComp,                                           RTE_CODE, Prm_CRdciParkSupTolNoTempComp                )(void);
   P2FUNC(ImpTypeValCRdciParkSupTolTempComp,                                             RTE_CODE, Prm_CRdciParkSupTolTempComp                  )(void);
   P2FUNC(ImpTypeValCRdciParkSupWarningThresholdValueC,                                  RTE_CODE, Prm_CRdciParkSupWarningThresholdValueC       )(void);
   P2FUNC(ImpTypeValCRdciParkSupWarningThresholdValueNc,                                 RTE_CODE, Prm_CRdciParkSupWarningThresholdValueNc      )(void);
   P2FUNC(ImpTypeValCRdciPrewarnEnable,                                                  RTE_CODE, Prm_CRdciPrewarnEnable                       )(void);
   P2FUNC(ImpTypeValCRdciPrewarnIgnition,                                                RTE_CODE, Prm_CRdciPrewarnIgnition                     )(void);
   P2FUNC(ImpTypeValCRdciResetPlausi,                                                    RTE_CODE, Prm_CRdciResetPlausi                         )(void);
   P2FUNC(ImpTypeValCRdciRidEnable,                                                      RTE_CODE, Prm_CRdciRidEnable                           )(void);
   P2FUNC(ImpTypeValCRdciSensorForeignAkRdk,                                             RTE_CODE, Prm_CRdciSensorForeignAkRdk                  )(void);
   P2FUNC(ImpTypeValCRdciSensorLocSync,                                                  RTE_CODE, Prm_CRdciSensorLocSync                       )(void);
   P2FUNC(ImpTypeValCRdciShortHoldTime,                                                  RTE_CODE, Prm_CRdciShortHoldTime                       )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmEnable,                                                 RTE_CODE, Prm_CRdciSpeedCcmEnable                      )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmHyst,                                                   RTE_CODE, Prm_CRdciSpeedCcmHyst                        )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmPressOffsetFa,                                          RTE_CODE, Prm_CRdciSpeedCcmPressOffsetFa               )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmPressOffsetRa,                                          RTE_CODE, Prm_CRdciSpeedCcmPressOffsetRa               )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmTh,                                                     RTE_CODE, Prm_CRdciSpeedCcmTh                          )(void);
   P2FUNC(ImpTypeValCRdciSpeedCcmTime,                                                   RTE_CODE, Prm_CRdciSpeedCcmTime                        )(void);
   P2FUNC(ImpTypeValCRdciStatInit,                                                       RTE_CODE, Prm_CRdciStatInit                            )(void);
   P2FUNC(ImpTypeValCRdciTPrewarnNc,                                                     RTE_CODE, Prm_CRdciTPrewarnNc                          )(void);
   P2FUNC(ImpTypeValCRdciTRefShift,                                                      RTE_CODE, Prm_CRdciTRefShift                           )(void);
   P2FUNC(ImpTypeValCRdciThCTol,                                                         RTE_CODE, Prm_CRdciThCTol                              )(void);
   P2FUNC(ImpTypeValCRdciThNCTol,                                                        RTE_CODE, Prm_CRdciThNCTol                             )(void);
   P2FUNC(ImpTypeValCRdciTimeoutPrewarn,                                                 RTE_CODE, Prm_CRdciTimeoutPrewarn                      )(void);
   P2FUNC(ImpTypeValCRdciTpmsMarket,                                                     RTE_CODE, Prm_CRdciTpmsMarket                          )(void);
   P2FUNC(Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciTrefSeasAdjConfig_FncRetPtrType, RTE_CODE, Prm_CRdciTrefSeasAdjConfig                   )(void);
   P2FUNC(ImpTypeValCRdciTrefSeasonalAdjustment,                                         RTE_CODE, Prm_CRdciTrefSeasonalAdjustment              )(void);
   P2FUNC(ImpTypeValCRdciTyrIdFiltGw,                                                    RTE_CODE, Prm_CRdciTyrIdFiltGw                         )(void);
   P2FUNC(ImpTypeValCRdciUiaThC,                                                         RTE_CODE, Prm_CRdciUiaThC                              )(void);
   P2FUNC(ImpTypeValCRdciUiaThNc,                                                        RTE_CODE, Prm_CRdciUiaThNc                             )(void);
   P2FUNC(ImpTypeValCRdciUiwThC,                                                         RTE_CODE, Prm_CRdciUiwThC                              )(void);
   P2FUNC(ImpTypeValCRdciUiwThNc,                                                        RTE_CODE, Prm_CRdciUiwThNc                             )(void);
   P2FUNC(ImpTypeValCRdciXminCoolTire,                                                   RTE_CODE, Prm_CRdciXminCoolTire                        )(void);
   P2FUNC(ImpTypeVal_C_Funktion_ReifenPannenerkennung_aktiv_e,                           RTE_CODE, Prm_C_Funktion_ReifenPannenerkennung_aktiv_e )(void);
};

struct Rte_PDS_CtApHufTpmsSWC_PiCcm_DISP_CC_BYPA_00_P{
   P2FUNC(Std_ReturnType, RTE_CODE, Send_DeCcm_DISP_CC_BYPA_00) (P2CONST(ImpTypeRecCcm_DISP_CC_BYPA_00, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA));
};

struct Rte_PDS_CtApHufTpmsSWC_PiCddAbsData_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Receive_DeCddAbsData) (P2VAR(ImpTypeRecCddAbsData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiCddRdcData_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Receive_DeCddRdcData) (P2VAR(ImpTypeRecCddRdcData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_A_TEMP_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_TEMP_EX) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_TEMP_EX) (P2VAR(Rdci_TEMP_EX_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_BEDIENUNG_FAHRWERK_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_OP_IDR_SLCTN) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_OP_SLCTN_TYR_AVLB) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_OP_TAR_P_LOCO_TPCT) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_OP_TPCT) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_OP_TYR_SEA_TPCT) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_RQ_OL_TPCT) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_ST_IDR_MSGC) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_OP_IDR_SLCTN) (P2VAR(Rdci_OP_IDR_SLCTN_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_OP_SLCTN_TYR_AVLB) (P2VAR(Rdci_OP_SLCTN_TYR_AVLB_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_OP_TAR_P_LOCO_TPCT) (P2VAR(Rdci_OP_TAR_P_LOCO_TPCT_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_OP_TPCT) (P2VAR(Rdci_OP_TPCT_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_OP_TYR_SEA_TPCT) (P2VAR(Rdci_OP_TYR_SEA_TPCT_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_RQ_OL_TPCT) (P2VAR(Rdci_RQ_OL_TPCT_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_ST_IDR_MSGC) (P2VAR(Rdci_ST_IDR_MSGC_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_CON_VEH_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_CON_VEH) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_CON_VEH) (P2VAR(Rdci_CON_VEH_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_DT_PT_1_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_AIP_ENG_DRV) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_AIP_ENG_DRV) (P2VAR(Rdci_AIP_ENG_DRV_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_EINHEITEN_BN2020_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_UN_AIP) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_UN_MILE) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_UN_TEMP) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_UN_AIP) (P2VAR(Rdci_UN_AIP_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_UN_MILE) (P2VAR(Rdci_UN_MILE_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_UN_TEMP) (P2VAR(Rdci_UN_TEMP_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_FZZSTD_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_ST_ENERG_FZM) (void);
   P2FUNC(boolean, RTE_CODE, IsUpdated_ST_ILK_ERRM_FZM) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_ST_ENERG_FZM) (P2VAR(Rdci_ST_ENERG_FZM_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
   P2FUNC(Std_ReturnType, RTE_CODE, Read_ST_ILK_ERRM_FZM) (P2VAR(Rdci_ST_ILK_ERRM_FZM_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_KILOMETERSTAND_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_MILE_KM) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_MILE_KM) (P2VAR(Rdci_MILE_KM_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_NMEARawData2Part2_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_GNSSPositionAltitude) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_GNSSPositionAltitude) (P2VAR(Rdci_GNSSPositionAltitude_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_NMEARawData2Part3_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_GNSSErrorAltitudeMeters) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_GNSSErrorAltitudeMeters) (P2VAR(Rdci_GNSSErrorAltitudeMeters_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_RELATIVZEIT_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_T_SEC_COU_REL) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_T_SEC_COU_REL) (P2VAR(Rdci_T_SEC_COU_REL_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_ST_TYR_P{
   P2FUNC(Std_ReturnType, RTE_CODE, Send_ST_TYR) (P2CONST(Rdci_ST_TYR_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_UHRZEIT_DATUM_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_UHRZEIT_DATUM) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_UHRZEIT_DATUM) (P2VAR(Rdci_UHRZEIT_DATUM_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_V_VEH_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_V_VEH) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_V_VEH) (P2VAR(Rdci_V_VEH_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_WMOM_DRV_4_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_WMOM_DRV_4) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_WMOM_DRV_4) (P2VAR(Rdci_WMOM_DRV_4_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiRdci_FrBusState_R{
   P2FUNC(boolean, RTE_CODE, IsUpdated_FrBusState) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Read_FrBusState) (P2VAR(ImpTypeValFrBusState, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
};

struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetEventStatus) (P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte);
};

struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Call_ResetEventStatus) (void);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_SetEventStatus) (ImpTypeRefDem_EventStatusType EventStatus);
};

struct Rte_PDS_CtApHufTpmsSWC_StbMB_AbsoluteTimeBaseValue_R{
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetAbsoluteTime) (P2VAR(StbMB_SystemTimeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) systemTime);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetGlobalTime) (P2VAR(StbMB_TickType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ticks);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetSyncState) (P2VAR(StbMB_SyncStatusType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) syncState);
   P2FUNC(Std_ReturnType, RTE_CODE, Call_GetTickDuration) (P2VAR(uint32, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) tickDuration);
};

struct Rte_CDS_CtApHufTpmsSWC{
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AA_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_BAX_TYP_TYR_ID2_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_CAC_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_BAX_TYP_TYR_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_BAX_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_BAX_TYP_TYR_Type,                          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_BAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_1_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_1_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_1_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_2_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_2_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_2_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_3_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_3_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_3_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_4_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_4_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_4_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31;
   P2VAR(Rte_DE_Rdci_AA_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_FTAX_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_IDX_LCC_FTAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_FTAX_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_FTAX_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_TYP_TYR_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OL_AVLB_TYP_TYR_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_RAD_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_TYR_OL_ID_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID;
   P2VAR(Rte_DE_Rdci_WID_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ACTVN_PM_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_PM_ACTVN_PM;
   P2VAR(Rte_DE_Rdci_PM_ID2_Type,                                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_PM_PM_ID2;
   P2VAR(Rte_DE_Rdci_RQ_PM_DT_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_PM_RQ_PM_DT;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId3;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId4;
   P2VAR(Rte_DE_Rdci_QrCodePositionId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId3;
   P2VAR(Rte_DE_Rdci_QrCodePositionId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId3_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId4_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId2;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId1;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId2;
   P2VAR(Rte_DE_Rdci_QrCodePositionId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId1;
   P2VAR(Rte_DE_Rdci_QrCodePositionId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId1_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId2_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId2;
   P2VAR(Rte_DE_Rdci_CAC_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_SUTR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_SUTR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_SUTR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SOTR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_WID_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_L_OL_TYP_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OP_IDR_MSGC_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_OP_IDR_MSGC;
   P2VAR(Rte_DE_Rdci_QU_RDC_INIT_DISP_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP;
   P2VAR(Rte_DE_Rdci_ST_MAN_SLCTN_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_SUTR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_WITR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_TAR_P_LOCO_TPCT_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT;
   P2VAR(Rte_DE_Rdci_ST_TYR_SEA_TPCT_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangeDetection_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangePosition_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId1_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId2_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId3_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId4_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId1_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId2_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId3_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId4_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId1_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId2_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId3_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId4_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId1_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId2_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId3_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId4_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId1_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId2_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId1_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId2_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId3_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId4_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId3_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId4_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientPressure_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientTemperature_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationCalibrationType_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationDate_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationMileage_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationNoOfCalibrations_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPlausibility_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId1_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId2_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId3_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId4_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTime_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth;
   P2VAR(Rte_DE_Rdci_ExtParkSupConfig_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_ExtParkSupConfig;
   P2VAR(Rte_DE_Rdci_LastReceivedAmbientPressure_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure;
   P2VAR(Rte_DE_Rdci_MobilityLossThresholdValue_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueC_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueNc_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc;
   P2VAR(Rte_DE_Rdci_PwfChange_Type,                                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_PwfChange;
   P2VAR(Rte_DE_Rdci_RDCSystemReferenceTemp_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureFrontAxle_Type,   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureRearAxle_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle;
   P2VAR(Rte_DE_Rdci_TolNoTempComp_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolNoTempComp;
   P2VAR(Rte_DE_Rdci_TolTempComp_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolTempComp;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueC_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueC;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueNc_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc;
   P2VAR(Rte_DE_Rdci_CAC_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_WITR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_WITR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_WITR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WITR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AA_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_BAX_TYP_TYR_ID2_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_CAC_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_BAX_TYP_TYR_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_BAX_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_BAX_TYP_TYR_Type,                          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_BAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_1_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_1_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_1_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_2_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_2_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_2_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_3_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_3_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_3_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_4_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_4_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_4_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31;
   P2VAR(Rte_DE_Rdci_AA_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_FTAX_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_IDX_LCC_FTAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_FTAX_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_FTAX_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_TYP_TYR_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OL_AVLB_TYP_TYR_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_RAD_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_TYR_OL_ID_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID;
   P2VAR(Rte_DE_Rdci_WID_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ACTVN_PM_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_PM_ACTVN_PM;
   P2VAR(Rte_DE_Rdci_PM_ID2_Type,                                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_PM_PM_ID2;
   P2VAR(Rte_DE_Rdci_RQ_PM_DT_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId3;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId4;
   P2VAR(Rte_DE_Rdci_QrCodePositionId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId3;
   P2VAR(Rte_DE_Rdci_QrCodePositionId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId3_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId4_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId2;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId1;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId2;
   P2VAR(Rte_DE_Rdci_QrCodePositionId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId1;
   P2VAR(Rte_DE_Rdci_QrCodePositionId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId1_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId2_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId2;
   P2VAR(Rte_DE_Rdci_CAC_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_SUTR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_SUTR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_SUTR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SOTR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_WID_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_L_OL_TYP_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OP_IDR_MSGC_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC;
   P2VAR(Rte_DE_Rdci_QU_RDC_INIT_DISP_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP;
   P2VAR(Rte_DE_Rdci_ST_MAN_SLCTN_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_SUTR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_WITR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_TAR_P_LOCO_TPCT_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT;
   P2VAR(Rte_DE_Rdci_ST_TYR_SEA_TPCT_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangeDetection_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangePosition_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId1_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId2_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId3_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId4_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId1_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId2_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId3_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId4_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId1_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId2_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId3_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId4_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId1_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId2_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId3_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId4_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId1_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId2_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId1_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId2_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId3_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId4_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId3_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId4_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientPressure_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientTemperature_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationCalibrationType_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationDate_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationMileage_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationNoOfCalibrations_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPlausibility_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId1_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId2_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId3_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId4_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTime_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth;
   P2VAR(Rte_DE_Rdci_ExtParkSupConfig_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_ExtParkSupConfig;
   P2VAR(Rte_DE_Rdci_LastReceivedAmbientPressure_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure;
   P2VAR(Rte_DE_Rdci_MobilityLossThresholdValue_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueC_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueNc_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc;
   P2VAR(Rte_DE_Rdci_PwfChange_Type,                                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_PwfChange;
   P2VAR(Rte_DE_Rdci_RDCSystemReferenceTemp_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureFrontAxle_Type,   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureRearAxle_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle;
   P2VAR(Rte_DE_Rdci_TolNoTempComp_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolNoTempComp;
   P2VAR(Rte_DE_Rdci_TolTempComp_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolTempComp;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueC_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueC;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueNc_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc;
   P2VAR(Rte_DE_Rdci_CAC_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_WITR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_WITR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_WITR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WITR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_FRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RLH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH;
   P2VAR(Rte_DE_Rdci_AVL_TEMP_TYR_RRH_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH;
   P2VAR(Rte_DE_Rdci_AA_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_BAX_TYP_TYR_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_BAX_TYP_TYR_ID2_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_CAC_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_BAX_TYP_TYR_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_BAX_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_BAX_TYP_TYR_Type,                          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_BAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_BAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_1_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_1_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_1_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_2_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_2_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_2_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_3_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_3_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_3_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3;
   P2VAR(Rte_DE_Rdci_CNTR_FBD_TPMS_4_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2;
   P2VAR(Rte_DE_Rdci_CTR_FIL_ACTV_4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4;
   P2VAR(Rte_DE_Rdci_CTR_SUPP_ID_4_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4;
   P2VAR(Rte_DE_Rdci_CTR_TYR_ID_4_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30;
   P2VAR(Rte_DE_Rdci_DEBUG_DATA_Type,                                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31;
   P2VAR(Rte_DE_Rdci_AA_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_AG_FTAX_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_FTAX_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_IDX_LCC_FTAX_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_FTAX_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_LOR_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_FTAX_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_FTAX_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR;
   P2VAR(Rte_DE_Rdci_CAC_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_TYP_TYR_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_TYP_TYR_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OL_AVLB_TYP_TYR_ID2_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_RAD_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_TYP_TYR_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ST_TYR_OL_ID_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID;
   P2VAR(Rte_DE_Rdci_WID_TYP_TYR_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR;
   P2VAR(Rte_DE_Rdci_ACTVN_PM_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_PM_ACTVN_PM;
   P2VAR(Rte_DE_Rdci_PM_ID2_Type,                                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_PM_PM_ID2;
   P2VAR(Rte_DE_Rdci_RQ_PM_DT_Type,                                       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_PM_RQ_PM_DT;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId3_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId4_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId3_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId4_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId3;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId4;
   P2VAR(Rte_DE_Rdci_QrCodePositionId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId3;
   P2VAR(Rte_DE_Rdci_QrCodePositionId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId3_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId4_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId3_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId4_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId3_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId3;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId4_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId4;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId1_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotNoId2_Type,                                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId1;
   P2VAR(Rte_DE_Rdci_QrCodeDotProdDateId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId2;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId1_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId1;
   P2VAR(Rte_DE_Rdci_QrCodeInventoryNoId2_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId2;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId1;
   P2VAR(Rte_DE_Rdci_QrCodeMountingStateId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId2;
   P2VAR(Rte_DE_Rdci_QrCodePositionId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId1;
   P2VAR(Rte_DE_Rdci_QrCodePositionId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartAId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId1_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1;
   P2VAR(Rte_DE_Rdci_QrCodeRubberSerialNoPartBId2_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId1_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireDimensionsId2_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId1_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId1;
   P2VAR(Rte_DE_Rdci_QrCodeTireTypeId2_Type,                              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId2;
   P2VAR(Rte_DE_Rdci_CAC_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_SUTR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_SUTR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_SUTR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SOTR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2;
   P2VAR(Rte_DE_Rdci_WID_SUTR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_L_OL_TYP_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR;
   P2VAR(Rte_DE_Rdci_OP_IDR_MSGC_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_OP_IDR_MSGC;
   P2VAR(Rte_DE_Rdci_QU_RDC_INIT_DISP_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP;
   P2VAR(Rte_DE_Rdci_ST_MAN_SLCTN_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_SUTR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_TYR_Type,                                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR;
   P2VAR(Rte_DE_Rdci_ST_SLCTN_WITR_AVLB_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB;
   P2VAR(Rte_DE_Rdci_ST_TAR_P_LOCO_TPCT_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT;
   P2VAR(Rte_DE_Rdci_ST_TYR_SEA_TPCT_Type,                                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangeDetection_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection;
   P2VAR(Rte_DE_Rdci_StatusWheelTypeChangePosition_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_FRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RLH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH;
   P2VAR(Rte_DE_Rdci_TAR_P_TYR_RRH_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastBatteryStatusId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId1_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId2_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId3_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPositionId4_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId1_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId2_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId3_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastPressureMbarId4_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId1_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId2_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId3_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionRssiId4_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastReceptionYieldId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastSensorSerNoId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId1_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId2_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId3_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTargetPressureMbarId4_Type,          TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId1_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId2_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId3_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3;
   P2VAR(Rte_DE_Rdci_TpmsInternalLastTemperatureDegCId4_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId1_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId2_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId1_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId2_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId1_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId2_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId1_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId2_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId1_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId2_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId3_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3;
   P2VAR(Rte_DE_Rdci_TireMileageInventoryNoId4_Type,                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId3_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyDateId4_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId3_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastAssemblyVehicleMileageId4_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId3_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyDateId4_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3;
   P2VAR(Rte_DE_Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId3_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3;
   P2VAR(Rte_DE_Rdci_TireMileagePositionId4_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3;
   P2VAR(Rte_DE_Rdci_TireMileageTotalTireMileageOnVehicleId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTirePressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId1_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId2_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId3_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationActualTireTemperatureId4_Type,        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientPressure_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationAmbientTemperature_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationCalibrationType_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationDate_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationMileage_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationNoOfCalibrations_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPlausibility_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId1_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId2_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId3_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationPositionId4_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTime_Type,                            TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId1_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId2_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId3_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3;
   P2VAR(Rte_DE_Rdci_TpmsCalibrationTireTargetPressureId4_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimSummerWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCarcass_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterCrossSection_Type,           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterDiameter_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterLoadIndex_Type,              TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMounted_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterMountedInFactory_Type,       TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterPosition_Type,               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterRunflat_Type,                TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSeason_Type,                 TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterSpeedIndex_Type,             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup0_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup1_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup2_Type, TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2;
   P2VAR(Rte_DE_Rdci_TpmsErfsActTireDimWinterWidth_Type,                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth;
   P2VAR(Rte_DE_Rdci_ExtParkSupConfig_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_ExtParkSupConfig;
   P2VAR(Rte_DE_Rdci_LastReceivedAmbientPressure_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure;
   P2VAR(Rte_DE_Rdci_MobilityLossThresholdValue_Type,                     TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueC_Type,                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC;
   P2VAR(Rte_DE_Rdci_NotificationThresholdValueNc_Type,                   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc;
   P2VAR(Rte_DE_Rdci_PwfChange_Type,                                      TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_PwfChange;
   P2VAR(Rte_DE_Rdci_RDCSystemReferenceTemp_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureFrontAxle_Type,   TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle;
   P2VAR(Rte_DE_Rdci_RelRecommendedColdInflationPressureRearAxle_Type,    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle;
   P2VAR(Rte_DE_Rdci_TolNoTempComp_Type,                                  TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolNoTempComp;
   P2VAR(Rte_DE_Rdci_TolTempComp_Type,                                    TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolTempComp;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueC_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueC;
   P2VAR(Rte_DE_Rdci_WarningThresholdValueNc_Type,                        TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc;
   P2VAR(Rte_DE_Rdci_CAC_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_LCC_WITR_TYP_TYR_Type,                           TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_IDX_V_WITR_TYP_TYR_Type,                             TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RAD_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RELA_SIDE_WITR_TYP_TYR_Type,                         TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_RFL_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_SEA_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WID_WITR_TYP_TYR_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR;
   P2VAR(Rte_DE_Rdci_WITR_TYP_TYR_ID2_Type,                               TYPEDEF, RTE_CTAPHUFTPMSSWC_APPL_VAR) RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciCommonBlockType,               TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock1Type,                TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock2Type,                TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsBlockType,                 TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsEcoBlockType,              TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsTsaBlockType,              TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock1Type,               TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock2Type,               TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciWarnStatusBlockType,           TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciZoHistoryBlockType,            TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock1Type,                 TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock;
   P2VAR(Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock2Type,                 TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciCommonBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciDiagBlock1;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciDiagBlock2;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciErfsBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciErfsEcoBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciErfsTsaBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciRidQrBlock1;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciRidQrBlock2;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciWarnStatusBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciZoHistoryBlock;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciZomBlock1;
   struct Rte_PDS_CtApHufTpmsSWC_NvMService_R                  CpNvmRdciZomBlock2;
   struct Rte_PDS_CtApHufTpmsSWC_PiCalPrmRDCi_R                RpCalPrmRDCi;
   struct Rte_PDS_CtApHufTpmsSWC_PiCcm_DISP_CC_BYPA_00_P       PpCcm_DISP_CC_BYPA_00;
   struct Rte_PDS_CtApHufTpmsSWC_PiCddAbsData_R                RpCddAbsData;
   struct Rte_PDS_CtApHufTpmsSWC_PiCddRdcData_R                RpCddRdcData;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_A_TEMP_R              RpFrPdu_A_TEMP;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_BEDIENUNG_FAHRWERK_R  RpFrPdu_BEDIENUNG_FAHRWERK;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_CON_VEH_R             RpFrPdu_CON_VEH;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_DT_PT_1_R             RpFrPdu_DT_PT_1;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_EINHEITEN_BN2020_R    RpFrPdu_EINHEITEN_BN2020;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_FZZSTD_R              RpFrPdu_FZZSTD;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_KILOMETERSTAND_R      RpFrPdu_KILOMETERSTAND;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_NMEARawData2Part2_R   RpFrPdu_NMEARawData2Part2;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_NMEARawData2Part3_R   RpFrPdu_NMEARawData2Part3;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_RELATIVZEIT_R         RpFrPdu_RELATIVZEIT;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_ST_TYR_P              PpFrPdu_ST_TYR;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_UHRZEIT_DATUM_R       RpFrPdu_UHRZEIT_DATUM;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_V_VEH_R               RpFrPdu_V_VEH;
   struct Rte_PDS_CtApHufTpmsSWC_PiFrPdu_WMOM_DRV_4_R          RpFrPdu_WMOM_DRV_4;
   struct Rte_PDS_CtApHufTpmsSWC_PiRdci_FrBusState_R           RpRdci_FrBusState;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdci1To3WrongWuMountedInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdci4WrongWuMountedInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciATempInvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciATempTimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciAusfallInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciAutoLearningFailedInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciBefuellhinweisInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciConVehAliveInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciConVehCrcInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciConVehInvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciConVehTimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciDruckwarnungInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciEinheitenBn2020InvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciEinheitenBn2020TimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciErfsCodingDataInconsistentInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciGatewayOrAntennaErrorInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciKalibrierungInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciOtherWuSensorTypeInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciPannenwarnungInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciPartialSystemAvailabilityInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRdcDtPckg1AliveInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRdcDtPckg1InvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRdcDtPckg1TimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRelativzeitInvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRelativzeitTimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciRfExternalInterferenceInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciSystemNotAvailableInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciTpmsManufactoryModeInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciUnspecifiedWfcDefectInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciUnspecifiedWuMuteInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciVVehAliveFailureInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciVVehCogInvalidInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciVVehCogQualifierInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciVVehCrcFailureInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciVVehTimeoutInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWarnruecknahmeInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuDefectFlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuDefectFrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuDefectRlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuDefectRrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuLocalisationFailedInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuLowBatteryFlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuLowBatteryFrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuLowBatteryRlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuLowBatteryRrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuMuteFlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuMuteFrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuMuteRlInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemInfo_R            DemErrorRdciWuMuteRrInfo;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdci1To3WrongWuMounted;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdci4WrongWuMounted;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciATempInvalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciATempTimeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciAusfall;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciAutoLearningFailed;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciBefuellhinweis;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciConVehAlive;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciConVehCrc;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciConVehInvalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciConVehTimeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciDruckwarnung;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciEinheitenBn2020Invalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciEinheitenBn2020Timeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciErfsCodingDataInconsistent;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciGatewayOrAntennaError;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciKalibrierung;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciOtherWuSensorType;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciPannenwarnung;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciPartialSystemAvailability;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRdcDtPckg1Alive;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRdcDtPckg1Invalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRdcDtPckg1Timeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRelativzeitInvalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRelativzeitTimeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciRfExternalInterference;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciSystemNotAvailable;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciTpmsManufactoryMode;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciUnspecifiedWfcDefect;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciUnspecifiedWuMute;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciVVehAliveFailure;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciVVehCogInvalid;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciVVehCogQualifier;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciVVehCrcFailure;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciVVehTimeout;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWarnruecknahme;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuDefectFl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuDefectFr;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuDefectRl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuDefectRr;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuLocalisationFailed;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuLowBatteryFl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuLowBatteryFr;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuLowBatteryRl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuLowBatteryRr;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuMuteFl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuMuteFr;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuMuteRl;
   struct Rte_PDS_CtApHufTpmsSWC_PiServiceDemMonitor_R         DemErrorRdciWuMuteRr;
   struct Rte_PDS_CtApHufTpmsSWC_StbMB_AbsoluteTimeBaseValue_R StbMB_AbsoluteTimeBaseValue;
#ifdef _EcuVirtual
#else
   uint8 Instance_Id;
#endif
};

extern CONSTP2CONST(struct Rte_CDS_CtApHufTpmsSWC, RTE_CONST, RTE_CONST) Rte_Inst_CtApHufTpmsSWC;

typedef P2CONST(struct Rte_CDS_CtApHufTpmsSWC, TYPEDEF, RTE_CONST) Rte_Instance;

#define Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH (65535U)
#define Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH (65535U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2 (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR (1U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR (16U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1 (4294967295U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2 (4294967295U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3 (4294967295U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4 (255U)
#define Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4 (4294967295U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30 (255U)
#define Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31 (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2 (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR (1U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR (16U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2 (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID (255U)
#define Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR (16U)
#define Rte_InitValue_PpFrPdu_PM_ACTVN_PM (255U)
#define Rte_InitValue_PpFrPdu_PM_PM_ID2 (255U)
#define Rte_InitValue_PpFrPdu_PM_RQ_PM_DT (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeDotNoId1 (72057594037927935ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeDotNoId2 (72057594037927935ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeDotProdDateId1 (65535U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeDotProdDateId2 (65535U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeInventoryNoId1 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeInventoryNoId2 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeMountingStateId1 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeMountingStateId2 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodePositionId1 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodePositionId2 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1 (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2 (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1 (16777215U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2 (16777215U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1 (281474976910655ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2 (281474976910655ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeTireTypeId1 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData_QrCodeTireTypeId2 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeDotNoId3 (72057594037927935ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeDotNoId4 (72057594037927935ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3 (65535U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4 (65535U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeMountingStateId3 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeMountingStateId4 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodePositionId3 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodePositionId4 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3 (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4 (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3 (16777215U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4 (16777215U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3 (281474976910655ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4 (281474976910655ULL)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeTireTypeId3 (255U)
#define Rte_InitValue_PpFrPdu_QrCodeData2_QrCodeTireTypeId4 (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2 (255U)
#define Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR (16U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_OP_IDR_MSGC (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT (255U)
#define Rte_InitValue_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT (255U)
#define Rte_InitValue_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection (255U)
#define Rte_InitValue_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition (255U)
#define Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH (65535U)
#define Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH (65535U)
#define Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH (65535U)
#define Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1 (4294967295U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2 (4294967295U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3 (4294967295U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4 (4294967295U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4 (65535U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3 (255U)
#define Rte_InitValue_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4 (281474976710655ULL)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4 (255U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3 (4294967295U)
#define Rte_InitValue_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4 (4294967295U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage (4294967295U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4 (255U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime (18446744073709551615ULL)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4 (65535U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2 (255U)
#define Rte_InitValue_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_ExtParkSupConfig (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_PwfChange (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_TolNoTempComp (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_TolTempComp (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_WarningThresholdValueC (255U)
#define Rte_InitValue_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR (255U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR (16U)
#define Rte_InitValue_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2 (255U)
#define Rte_InitValue_RpFrPdu_A_TEMP_TEMP_EX (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_OP_IDR_SLCTN (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_OP_SLCTN_TYR_AVLB (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TAR_P_LOCO_TPCT (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TPCT (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TYR_SEA_TPCT (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_RQ_OL_TPCT (255U)
#define Rte_InitValue_RpFrPdu_BEDIENUNG_FAHRWERK_ST_IDR_MSGC (255U)
#define Rte_InitValue_RpFrPdu_DT_PT_1_AIP_ENG_DRV (255U)
#define Rte_InitValue_RpFrPdu_EINHEITEN_BN2020_UN_AIP (255U)
#define Rte_InitValue_RpFrPdu_EINHEITEN_BN2020_UN_MILE (255U)
#define Rte_InitValue_RpFrPdu_EINHEITEN_BN2020_UN_TEMP (255U)
#define Rte_InitValue_RpFrPdu_FZZSTD_ST_ENERG_FZM (255U)
#define Rte_InitValue_RpFrPdu_FZZSTD_ST_ILK_ERRM_FZM (255U)
#define Rte_InitValue_RpFrPdu_KILOMETERSTAND_MILE_KM (16777215U)
#define Rte_InitValue_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude (65535U)
#define Rte_InitValue_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters (65535U)
#define Rte_InitValue_RpFrPdu_RELATIVZEIT_T_SEC_COU_REL (4294967295U)
#define Rte_InitValue_RpRdci_FrBusState_FrBusState (255U)

#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR(self, data)                                             ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR(self, data)                                             ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self, data)                                       ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31(self, data)                                         ((self)->RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_ACTVN_PM(self, data)                                                            ((self)->RCyclicRDCiTask_PpFrPdu_PM_ACTVN_PM->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_PM_ID2(self, data)                                                              ((self)->RCyclicRDCiTask_PpFrPdu_PM_PM_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_RQ_PM_DT(self, data)                                                            ((self)->RCyclicRDCiTask_PpFrPdu_PM_RQ_PM_DT->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId1(self, data)                                              ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId2(self, data)                                              ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId1(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId2(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self, data)                                     ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self, data)                                     ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self, data)                                           ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self, data)                                             ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self, data)                                             ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self, data)                                       ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self, data)                                       ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self, data)                                       ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self, data)                                       ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self, data)                                     ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self, data)                                     ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId3(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId4(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self, data)                               ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self, data)                               ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self, data)                               ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self, data)                               ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR(self, data)                                                  ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_OP_IDR_MSGC(self, data)                                                   ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_OP_IDR_MSGC->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self, data)                                              ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN(self, data)                                                  ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR(self, data)                                                  ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT(self, data)                                            ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT(self, data)                                               ((self)->RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection(self, data)                   ((self)->RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH(self, data)                                                ((self)->RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self, data)          ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self, data)          ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self, data)       ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self, data)       ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self, data)                            ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self, data)                            ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self, data)          ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self, data)          ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self, data)       ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self, data)       ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self, data)                            ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self, data)                            ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self, data)                             ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self, data)                    ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self, data)                        ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self, data)                                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self, data)        ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self, data)                   ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self, data)            ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self, data)        ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self, data)  ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self, data)                   ((self)->RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4(self, data)                     ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4(self, data)                 ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4(self, data)                ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4(self, data)               ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4(self, data)                  ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4(self, data)           ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4(self, data)              ((self)->RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_ExtParkSupConfig(self, data)                                   ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_ExtParkSupConfig->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure(self, data)                        ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue(self, data)                         ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC(self, data)                        ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc(self, data)                       ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_PwfChange(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_PwfChange->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp(self, data)                             ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle(self, data)       ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle(self, data)        ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolNoTempComp(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolNoTempComp->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolTempComp(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolTempComp->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueC(self, data)                             ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueC->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc(self, data)                            ((self)->RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR(self, data)                                      ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR(self, data)                                        ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR(self, data)                                    ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2(self, data)                                          ((self)->RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR(self, data)                                                ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR(self, data)                                                ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self, data)                                          ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31(self, data)                                            ((self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_ACTVN_PM(self, data)                                                               ((self)->RExitRDCiBye_PpFrPdu_PM_ACTVN_PM->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_PM_ID2(self, data)                                                                 ((self)->RExitRDCiBye_PpFrPdu_PM_PM_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT(self, data)                                                               ((self)->RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId1(self, data)                                                 ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId2(self, data)                                                 ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId1(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId2(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self, data)                                        ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self, data)                                        ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self, data)                                              ((self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self, data)                                                ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self, data)                                                ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self, data)                                          ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self, data)                                          ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self, data)                                          ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self, data)                                          ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self, data)                                        ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self, data)                                        ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId3(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId4(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self, data)                                  ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self, data)                                  ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self, data)                                  ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self, data)                                  ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR(self, data)                                                     ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC(self, data)                                                      ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self, data)                                                 ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN(self, data)                                                     ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR(self, data)                                                     ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT(self, data)                                               ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT(self, data)                                                  ((self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection(self, data)                      ((self)->RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH(self, data)                                                   ((self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self, data)             ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self, data)             ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self, data)          ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self, data)          ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self, data)                               ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self, data)                               ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self, data)             ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self, data)             ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self, data)          ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self, data)          ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self, data)                               ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self, data)                               ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self, data)                                ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self, data)                       ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self, data)                           ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self, data)                                   ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self, data)           ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self, data)                      ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self, data)               ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self, data)           ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self, data)     ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self, data)                      ((self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4(self, data)                        ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4(self, data)                    ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4(self, data)                   ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4(self, data)                  ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4(self, data)                     ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4(self, data)              ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4(self, data)                 ((self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_ExtParkSupConfig(self, data)                                      ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_ExtParkSupConfig->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure(self, data)                           ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue(self, data)                            ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC(self, data)                           ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc(self, data)                          ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_PwfChange(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_PwfChange->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp(self, data)                                ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle(self, data)          ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle(self, data)           ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolNoTempComp(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolNoTempComp->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolTempComp(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolTempComp->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueC(self, data)                                ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueC->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc(self, data)                               ((self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR(self, data)                                         ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR(self, data)                                           ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR(self, data)                                       ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2(self, data)                                             ((self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR(self, data)                                            ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR(self, data)                                            ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self, data)                                      ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31(self, data)                                        ((self)->RInitRDCiStartup_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_PM_ACTVN_PM(self, data)                                                           ((self)->RInitRDCiStartup_PpFrPdu_PM_ACTVN_PM->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_PM_PM_ID2(self, data)                                                             ((self)->RInitRDCiStartup_PpFrPdu_PM_PM_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_PM_RQ_PM_DT(self, data)                                                           ((self)->RInitRDCiStartup_PpFrPdu_PM_RQ_PM_DT->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId1(self, data)                                             ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId2(self, data)                                             ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotNoId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeDotProdDateId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeInventoryNoId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeMountingStateId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId1(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId2(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodePositionId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self, data)                                    ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self, data)                                    ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self, data)                                          ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData_QrCodeTireTypeId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self, data)                                            ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self, data)                                            ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotNoId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self, data)                                      ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self, data)                                      ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self, data)                                      ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self, data)                                      ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self, data)                                    ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self, data)                                    ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeMountingStateId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId3(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId4(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodePositionId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self, data)                              ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self, data)                              ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self, data)                              ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self, data)                              ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_QrCodeData2_QrCodeTireTypeId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR(self, data)                                                 ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_OP_IDR_MSGC(self, data)                                                  ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_OP_IDR_MSGC->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self, data)                                             ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN(self, data)                                                 ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR(self, data)                                                 ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT(self, data)                                           ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT(self, data)                                              ((self)->RInitRDCiStartup_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection(self, data)                  ((self)->RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH(self, data)                                               ((self)->RInitRDCiStartup_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self, data)         ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self, data)         ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self, data)      ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self, data)      ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self, data)                           ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self, data)                           ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self, data)         ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self, data)         ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self, data)      ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self, data)      ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self, data)                           ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self, data)                           ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self, data)                            ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self, data)                   ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self, data)                       ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self, data)                               ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self, data)       ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self, data)                  ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self, data)           ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self, data)       ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self, data) ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self, data)                  ((self)->RInitRDCiStartup_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4(self, data)                    ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4(self, data)                ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4(self, data)               ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4(self, data)              ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4(self, data)                 ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4(self, data)          ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4(self, data)             ((self)->RInitRDCiStartup_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_ExtParkSupConfig(self, data)                                  ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_ExtParkSupConfig->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure(self, data)                       ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue(self, data)                        ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC(self, data)                       ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc(self, data)                      ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_PwfChange(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_PwfChange->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp(self, data)                            ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle(self, data)      ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle(self, data)       ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolNoTempComp(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolNoTempComp->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolTempComp(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_TolTempComp->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueC(self, data)                            ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueC->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc(self, data)                           ((self)->RInitRDCiStartup_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR(self, data)                                     ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR(self, data)                                       ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR(self, data)                                   ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR->value = (data))
#define Rte_IWrite_RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2(self, data)                                         ((self)->RInitRDCiStartup_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2->value = (data))
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR(self)                                                   (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR(self)                                                   (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self)                                             (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31(self)                                               (&(self)->RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_PM_ACTVN_PM(self)                                                                  (&(self)->RExitRDCiBye_PpFrPdu_PM_ACTVN_PM->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_PM_PM_ID2(self)                                                                    (&(self)->RExitRDCiBye_PpFrPdu_PM_PM_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT(self)                                                                  (&(self)->RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId1(self)                                                    (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId2(self)                                                    (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotNoId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeDotProdDateId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeInventoryNoId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeMountingStateId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId1(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId2(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodePositionId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self)                                           (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self)                                           (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self)                                                 (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData_QrCodeTireTypeId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self)                                                   (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self)                                                   (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotNoId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self)                                             (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self)                                             (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self)                                             (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self)                                             (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self)                                           (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self)                                           (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeMountingStateId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId3(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId4(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodePositionId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self)                                     (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self)                                     (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self)                                     (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self)                                     (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_QrCodeData2_QrCodeTireTypeId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR(self)                                                        (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC(self)                                                         (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self)                                                    (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN(self)                                                        (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR(self)                                                        (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT(self)                                                  (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT(self)                                                     (&(self)->RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection(self)                         (&(self)->RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(self)                          (&(self)->RExitRDCiBye_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH(self)                                                      (&(self)->RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self)                          (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self)                          (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self)                (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self)                (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self)             (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self)             (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self)                                  (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self)                                  (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self)                          (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self)                          (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self)                (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self)                (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self)             (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self)             (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self)                                  (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self)                                  (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self)                                   (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self)                          (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self)                              (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self)                                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self)              (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self)                         (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self)                  (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self)              (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self)        (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self)                         (&(self)->RExitRDCiBye_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4(self)                           (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4(self)                       (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4(self)                      (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4(self)                     (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4(self)                        (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4(self)                 (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4(self)                    (&(self)->RExitRDCiBye_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_ExtParkSupConfig(self)                                         (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_ExtParkSupConfig->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure(self)                              (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue(self)                               (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC(self)                              (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc(self)                             (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_PwfChange(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_PwfChange->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp(self)                                   (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle(self)             (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle(self)              (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolNoTempComp(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolNoTempComp->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolTempComp(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_TolTempComp->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueC(self)                                   (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueC->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc(self)                                  (&(self)->RExitRDCiBye_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR(self)                                            (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR(self)                                              (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR(self)                                          (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR->value)
#define Rte_IWriteRef_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2(self)                                                (&(self)->RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2->value)

#define Rte_Receive_RpCddAbsData_DeCddAbsData(self, data) ((self)->RpCddAbsData.Receive_DeCddAbsData(data))
#define Rte_Receive_RpCddRdcData_DeCddRdcData(self, data) ((self)->RpCddRdcData.Receive_DeCddRdcData(data))

#define Rte_Read_RpFrPdu_A_TEMP_TEMP_EX(self, data) ((self)->RpFrPdu_A_TEMP.Read_TEMP_EX(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_IDR_SLCTN(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_OP_IDR_SLCTN(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_SLCTN_TYR_AVLB(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_OP_SLCTN_TYR_AVLB(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TAR_P_LOCO_TPCT(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_OP_TAR_P_LOCO_TPCT(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TPCT(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_OP_TPCT(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TYR_SEA_TPCT(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_OP_TYR_SEA_TPCT(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_RQ_OL_TPCT(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_RQ_OL_TPCT(data))
#define Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_ST_IDR_MSGC(self, data) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.Read_ST_IDR_MSGC(data))
#define Rte_Read_RpFrPdu_CON_VEH_CON_VEH(self, data) ((self)->RpFrPdu_CON_VEH.Read_CON_VEH(data))
#define Rte_Read_RpFrPdu_DT_PT_1_AIP_ENG_DRV(self, data) ((self)->RpFrPdu_DT_PT_1.Read_AIP_ENG_DRV(data))
#define Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_AIP(self, data) ((self)->RpFrPdu_EINHEITEN_BN2020.Read_UN_AIP(data))
#define Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_MILE(self, data) ((self)->RpFrPdu_EINHEITEN_BN2020.Read_UN_MILE(data))
#define Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_TEMP(self, data) ((self)->RpFrPdu_EINHEITEN_BN2020.Read_UN_TEMP(data))
#define Rte_Read_RpFrPdu_FZZSTD_ST_ENERG_FZM(self, data) ((self)->RpFrPdu_FZZSTD.Read_ST_ENERG_FZM(data))
#define Rte_Read_RpFrPdu_FZZSTD_ST_ILK_ERRM_FZM(self, data) ((self)->RpFrPdu_FZZSTD.Read_ST_ILK_ERRM_FZM(data))
#define Rte_Read_RpFrPdu_KILOMETERSTAND_MILE_KM(self, data) ((self)->RpFrPdu_KILOMETERSTAND.Read_MILE_KM(data))
#define Rte_Read_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude(self, data) ((self)->RpFrPdu_NMEARawData2Part2.Read_GNSSPositionAltitude(data))
#define Rte_Read_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters(self, data) ((self)->RpFrPdu_NMEARawData2Part3.Read_GNSSErrorAltitudeMeters(data))
#define Rte_Read_RpFrPdu_RELATIVZEIT_T_SEC_COU_REL(self, data) ((self)->RpFrPdu_RELATIVZEIT.Read_T_SEC_COU_REL(data))
#define Rte_Read_RpFrPdu_UHRZEIT_DATUM_UHRZEIT_DATUM(self, data) ((self)->RpFrPdu_UHRZEIT_DATUM.Read_UHRZEIT_DATUM(data))
#define Rte_Read_RpFrPdu_V_VEH_V_VEH(self, data) ((self)->RpFrPdu_V_VEH.Read_V_VEH(data))
#define Rte_Read_RpFrPdu_WMOM_DRV_4_WMOM_DRV_4(self, data) ((self)->RpFrPdu_WMOM_DRV_4.Read_WMOM_DRV_4(data))
#define Rte_Read_RpRdci_FrBusState_FrBusState(self, data) ((self)->RpRdci_FrBusState.Read_FrBusState(data))

#define Rte_IsUpdated_RpFrPdu_A_TEMP_TEMP_EX(self) ((self)->RpFrPdu_A_TEMP.IsUpdated_TEMP_EX())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_IDR_SLCTN(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_OP_IDR_SLCTN())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_SLCTN_TYR_AVLB(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_OP_SLCTN_TYR_AVLB())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TAR_P_LOCO_TPCT(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_OP_TAR_P_LOCO_TPCT())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TPCT(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_OP_TPCT())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TYR_SEA_TPCT(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_OP_TYR_SEA_TPCT())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_RQ_OL_TPCT(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_RQ_OL_TPCT())
#define Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_ST_IDR_MSGC(self) ((self)->RpFrPdu_BEDIENUNG_FAHRWERK.IsUpdated_ST_IDR_MSGC())
#define Rte_IsUpdated_RpFrPdu_CON_VEH_CON_VEH(self) ((self)->RpFrPdu_CON_VEH.IsUpdated_CON_VEH())
#define Rte_IsUpdated_RpFrPdu_DT_PT_1_AIP_ENG_DRV(self) ((self)->RpFrPdu_DT_PT_1.IsUpdated_AIP_ENG_DRV())
#define Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_AIP(self) ((self)->RpFrPdu_EINHEITEN_BN2020.IsUpdated_UN_AIP())
#define Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_MILE(self) ((self)->RpFrPdu_EINHEITEN_BN2020.IsUpdated_UN_MILE())
#define Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_TEMP(self) ((self)->RpFrPdu_EINHEITEN_BN2020.IsUpdated_UN_TEMP())
#define Rte_IsUpdated_RpFrPdu_FZZSTD_ST_ENERG_FZM(self) ((self)->RpFrPdu_FZZSTD.IsUpdated_ST_ENERG_FZM())
#define Rte_IsUpdated_RpFrPdu_FZZSTD_ST_ILK_ERRM_FZM(self) ((self)->RpFrPdu_FZZSTD.IsUpdated_ST_ILK_ERRM_FZM())
#define Rte_IsUpdated_RpFrPdu_KILOMETERSTAND_MILE_KM(self) ((self)->RpFrPdu_KILOMETERSTAND.IsUpdated_MILE_KM())
#define Rte_IsUpdated_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude(self) ((self)->RpFrPdu_NMEARawData2Part2.IsUpdated_GNSSPositionAltitude())
#define Rte_IsUpdated_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters(self) ((self)->RpFrPdu_NMEARawData2Part3.IsUpdated_GNSSErrorAltitudeMeters())
#define Rte_IsUpdated_RpFrPdu_RELATIVZEIT_T_SEC_COU_REL(self) ((self)->RpFrPdu_RELATIVZEIT.IsUpdated_T_SEC_COU_REL())
#define Rte_IsUpdated_RpFrPdu_UHRZEIT_DATUM_UHRZEIT_DATUM(self) ((self)->RpFrPdu_UHRZEIT_DATUM.IsUpdated_UHRZEIT_DATUM())
#define Rte_IsUpdated_RpFrPdu_V_VEH_V_VEH(self) ((self)->RpFrPdu_V_VEH.IsUpdated_V_VEH())
#define Rte_IsUpdated_RpFrPdu_WMOM_DRV_4_WMOM_DRV_4(self) ((self)->RpFrPdu_WMOM_DRV_4.IsUpdated_WMOM_DRV_4())
#define Rte_IsUpdated_RpRdci_FrBusState_FrBusState(self) ((self)->RpRdci_FrBusState.IsUpdated_FrBusState())

#define Rte_Send_PpCcm_DISP_CC_BYPA_00_DeCcm_DISP_CC_BYPA_00(self, data) ((self)->PpCcm_DISP_CC_BYPA_00.Send_DeCcm_DISP_CC_BYPA_00(data))
#define Rte_Send_PpFrPdu_ST_TYR_ST_TYR(self, data) ((self)->PpFrPdu_ST_TYR.Send_ST_TYR(data))

#define Rte_Call_CpNvmRdciCommonBlock_GetDataIndex(self, arg1)                         ((self)->CpNvmRdciCommonBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciCommonBlock_GetErrorStatus(self, arg1)                       ((self)->CpNvmRdciCommonBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciCommonBlock_ReadBlock(self, arg1)                            ((self)->CpNvmRdciCommonBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciCommonBlock_SetDataIndex(self, arg1)                         ((self)->CpNvmRdciCommonBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciCommonBlock_SetRamBlockStatus(self, arg1)                    ((self)->CpNvmRdciCommonBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciCommonBlock_WriteBlock(self, arg1)                           ((self)->CpNvmRdciCommonBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_GetDataIndex(self, arg1)                          ((self)->CpNvmRdciDiagBlock1.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_GetErrorStatus(self, arg1)                        ((self)->CpNvmRdciDiagBlock1.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_ReadBlock(self, arg1)                             ((self)->CpNvmRdciDiagBlock1.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_SetDataIndex(self, arg1)                          ((self)->CpNvmRdciDiagBlock1.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_SetRamBlockStatus(self, arg1)                     ((self)->CpNvmRdciDiagBlock1.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciDiagBlock1_WriteBlock(self, arg1)                            ((self)->CpNvmRdciDiagBlock1.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_GetDataIndex(self, arg1)                          ((self)->CpNvmRdciDiagBlock2.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_GetErrorStatus(self, arg1)                        ((self)->CpNvmRdciDiagBlock2.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_ReadBlock(self, arg1)                             ((self)->CpNvmRdciDiagBlock2.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_SetDataIndex(self, arg1)                          ((self)->CpNvmRdciDiagBlock2.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_SetRamBlockStatus(self, arg1)                     ((self)->CpNvmRdciDiagBlock2.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciDiagBlock2_WriteBlock(self, arg1)                            ((self)->CpNvmRdciDiagBlock2.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_GetDataIndex(self, arg1)                           ((self)->CpNvmRdciErfsBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_GetErrorStatus(self, arg1)                         ((self)->CpNvmRdciErfsBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_ReadBlock(self, arg1)                              ((self)->CpNvmRdciErfsBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_SetDataIndex(self, arg1)                           ((self)->CpNvmRdciErfsBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_SetRamBlockStatus(self, arg1)                      ((self)->CpNvmRdciErfsBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciErfsBlock_WriteBlock(self, arg1)                             ((self)->CpNvmRdciErfsBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_GetDataIndex(self, arg1)                        ((self)->CpNvmRdciErfsEcoBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_GetErrorStatus(self, arg1)                      ((self)->CpNvmRdciErfsEcoBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_ReadBlock(self, arg1)                           ((self)->CpNvmRdciErfsEcoBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_SetDataIndex(self, arg1)                        ((self)->CpNvmRdciErfsEcoBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_SetRamBlockStatus(self, arg1)                   ((self)->CpNvmRdciErfsEcoBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciErfsEcoBlock_WriteBlock(self, arg1)                          ((self)->CpNvmRdciErfsEcoBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_GetDataIndex(self, arg1)                        ((self)->CpNvmRdciErfsTsaBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_GetErrorStatus(self, arg1)                      ((self)->CpNvmRdciErfsTsaBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_ReadBlock(self, arg1)                           ((self)->CpNvmRdciErfsTsaBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_SetDataIndex(self, arg1)                        ((self)->CpNvmRdciErfsTsaBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_SetRamBlockStatus(self, arg1)                   ((self)->CpNvmRdciErfsTsaBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciErfsTsaBlock_WriteBlock(self, arg1)                          ((self)->CpNvmRdciErfsTsaBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_GetDataIndex(self, arg1)                         ((self)->CpNvmRdciRidQrBlock1.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_GetErrorStatus(self, arg1)                       ((self)->CpNvmRdciRidQrBlock1.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_ReadBlock(self, arg1)                            ((self)->CpNvmRdciRidQrBlock1.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_SetDataIndex(self, arg1)                         ((self)->CpNvmRdciRidQrBlock1.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_SetRamBlockStatus(self, arg1)                    ((self)->CpNvmRdciRidQrBlock1.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock1_WriteBlock(self, arg1)                           ((self)->CpNvmRdciRidQrBlock1.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_GetDataIndex(self, arg1)                         ((self)->CpNvmRdciRidQrBlock2.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_GetErrorStatus(self, arg1)                       ((self)->CpNvmRdciRidQrBlock2.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_ReadBlock(self, arg1)                            ((self)->CpNvmRdciRidQrBlock2.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_SetDataIndex(self, arg1)                         ((self)->CpNvmRdciRidQrBlock2.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_SetRamBlockStatus(self, arg1)                    ((self)->CpNvmRdciRidQrBlock2.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciRidQrBlock2_WriteBlock(self, arg1)                           ((self)->CpNvmRdciRidQrBlock2.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_GetDataIndex(self, arg1)                     ((self)->CpNvmRdciWarnStatusBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_GetErrorStatus(self, arg1)                   ((self)->CpNvmRdciWarnStatusBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_ReadBlock(self, arg1)                        ((self)->CpNvmRdciWarnStatusBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_SetDataIndex(self, arg1)                     ((self)->CpNvmRdciWarnStatusBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_SetRamBlockStatus(self, arg1)                ((self)->CpNvmRdciWarnStatusBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciWarnStatusBlock_WriteBlock(self, arg1)                       ((self)->CpNvmRdciWarnStatusBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_GetDataIndex(self, arg1)                      ((self)->CpNvmRdciZoHistoryBlock.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_GetErrorStatus(self, arg1)                    ((self)->CpNvmRdciZoHistoryBlock.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_ReadBlock(self, arg1)                         ((self)->CpNvmRdciZoHistoryBlock.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_SetDataIndex(self, arg1)                      ((self)->CpNvmRdciZoHistoryBlock.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_SetRamBlockStatus(self, arg1)                 ((self)->CpNvmRdciZoHistoryBlock.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciZoHistoryBlock_WriteBlock(self, arg1)                        ((self)->CpNvmRdciZoHistoryBlock.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_GetDataIndex(self, arg1)                           ((self)->CpNvmRdciZomBlock1.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_GetErrorStatus(self, arg1)                         ((self)->CpNvmRdciZomBlock1.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_ReadBlock(self, arg1)                              ((self)->CpNvmRdciZomBlock1.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_SetDataIndex(self, arg1)                           ((self)->CpNvmRdciZomBlock1.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_SetRamBlockStatus(self, arg1)                      ((self)->CpNvmRdciZomBlock1.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciZomBlock1_WriteBlock(self, arg1)                             ((self)->CpNvmRdciZomBlock1.Call_WriteBlock(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_GetDataIndex(self, arg1)                           ((self)->CpNvmRdciZomBlock2.Call_GetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_GetErrorStatus(self, arg1)                         ((self)->CpNvmRdciZomBlock2.Call_GetErrorStatus(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_ReadBlock(self, arg1)                              ((self)->CpNvmRdciZomBlock2.Call_ReadBlock(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_SetDataIndex(self, arg1)                           ((self)->CpNvmRdciZomBlock2.Call_SetDataIndex(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_SetRamBlockStatus(self, arg1)                      ((self)->CpNvmRdciZomBlock2.Call_SetRamBlockStatus(arg1))
#define Rte_Call_CpNvmRdciZomBlock2_WriteBlock(self, arg1)                             ((self)->CpNvmRdciZomBlock2.Call_WriteBlock(arg1))
#define Rte_Call_DemErrorRdci1To3WrongWuMounted_ResetEventStatus(self)                 ((self)->DemErrorRdci1To3WrongWuMounted.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdci1To3WrongWuMounted_SetEventStatus(self, arg1)             ((self)->DemErrorRdci1To3WrongWuMounted.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdci1To3WrongWuMountedInfo_GetEventStatus(self, arg1)         ((self)->DemErrorRdci1To3WrongWuMountedInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdci4WrongWuMounted_ResetEventStatus(self)                    ((self)->DemErrorRdci4WrongWuMounted.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdci4WrongWuMounted_SetEventStatus(self, arg1)                ((self)->DemErrorRdci4WrongWuMounted.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdci4WrongWuMountedInfo_GetEventStatus(self, arg1)            ((self)->DemErrorRdci4WrongWuMountedInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciATempInvalid_ResetEventStatus(self)                       ((self)->DemErrorRdciATempInvalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciATempInvalid_SetEventStatus(self, arg1)                   ((self)->DemErrorRdciATempInvalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciATempInvalidInfo_GetEventStatus(self, arg1)               ((self)->DemErrorRdciATempInvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciATempTimeout_ResetEventStatus(self)                       ((self)->DemErrorRdciATempTimeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciATempTimeout_SetEventStatus(self, arg1)                   ((self)->DemErrorRdciATempTimeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciATempTimeoutInfo_GetEventStatus(self, arg1)               ((self)->DemErrorRdciATempTimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciAusfall_ResetEventStatus(self)                            ((self)->DemErrorRdciAusfall.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciAusfall_SetEventStatus(self, arg1)                        ((self)->DemErrorRdciAusfall.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciAusfallInfo_GetEventStatus(self, arg1)                    ((self)->DemErrorRdciAusfallInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciAutoLearningFailed_ResetEventStatus(self)                 ((self)->DemErrorRdciAutoLearningFailed.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciAutoLearningFailed_SetEventStatus(self, arg1)             ((self)->DemErrorRdciAutoLearningFailed.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciAutoLearningFailedInfo_GetEventStatus(self, arg1)         ((self)->DemErrorRdciAutoLearningFailedInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciBefuellhinweis_ResetEventStatus(self)                     ((self)->DemErrorRdciBefuellhinweis.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciBefuellhinweis_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciBefuellhinweis.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciBefuellhinweisInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciBefuellhinweisInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehAlive_ResetEventStatus(self)                        ((self)->DemErrorRdciConVehAlive.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciConVehAlive_SetEventStatus(self, arg1)                    ((self)->DemErrorRdciConVehAlive.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehAliveInfo_GetEventStatus(self, arg1)                ((self)->DemErrorRdciConVehAliveInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehCrc_ResetEventStatus(self)                          ((self)->DemErrorRdciConVehCrc.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciConVehCrc_SetEventStatus(self, arg1)                      ((self)->DemErrorRdciConVehCrc.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehCrcInfo_GetEventStatus(self, arg1)                  ((self)->DemErrorRdciConVehCrcInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehInvalid_ResetEventStatus(self)                      ((self)->DemErrorRdciConVehInvalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciConVehInvalid_SetEventStatus(self, arg1)                  ((self)->DemErrorRdciConVehInvalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehInvalidInfo_GetEventStatus(self, arg1)              ((self)->DemErrorRdciConVehInvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehTimeout_ResetEventStatus(self)                      ((self)->DemErrorRdciConVehTimeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciConVehTimeout_SetEventStatus(self, arg1)                  ((self)->DemErrorRdciConVehTimeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciConVehTimeoutInfo_GetEventStatus(self, arg1)              ((self)->DemErrorRdciConVehTimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciDruckwarnung_ResetEventStatus(self)                       ((self)->DemErrorRdciDruckwarnung.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciDruckwarnung_SetEventStatus(self, arg1)                   ((self)->DemErrorRdciDruckwarnung.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciDruckwarnungInfo_GetEventStatus(self, arg1)               ((self)->DemErrorRdciDruckwarnungInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciEinheitenBn2020Invalid_ResetEventStatus(self)             ((self)->DemErrorRdciEinheitenBn2020Invalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciEinheitenBn2020Invalid_SetEventStatus(self, arg1)         ((self)->DemErrorRdciEinheitenBn2020Invalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciEinheitenBn2020InvalidInfo_GetEventStatus(self, arg1)     ((self)->DemErrorRdciEinheitenBn2020InvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciEinheitenBn2020Timeout_ResetEventStatus(self)             ((self)->DemErrorRdciEinheitenBn2020Timeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciEinheitenBn2020Timeout_SetEventStatus(self, arg1)         ((self)->DemErrorRdciEinheitenBn2020Timeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciEinheitenBn2020TimeoutInfo_GetEventStatus(self, arg1)     ((self)->DemErrorRdciEinheitenBn2020TimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciErfsCodingDataInconsistent_ResetEventStatus(self)         ((self)->DemErrorRdciErfsCodingDataInconsistent.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciErfsCodingDataInconsistent_SetEventStatus(self, arg1)     ((self)->DemErrorRdciErfsCodingDataInconsistent.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciErfsCodingDataInconsistentInfo_GetEventStatus(self, arg1) ((self)->DemErrorRdciErfsCodingDataInconsistentInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciGatewayOrAntennaError_ResetEventStatus(self)              ((self)->DemErrorRdciGatewayOrAntennaError.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciGatewayOrAntennaError_SetEventStatus(self, arg1)          ((self)->DemErrorRdciGatewayOrAntennaError.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciGatewayOrAntennaErrorInfo_GetEventStatus(self, arg1)      ((self)->DemErrorRdciGatewayOrAntennaErrorInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciKalibrierung_ResetEventStatus(self)                       ((self)->DemErrorRdciKalibrierung.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciKalibrierung_SetEventStatus(self, arg1)                   ((self)->DemErrorRdciKalibrierung.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciKalibrierungInfo_GetEventStatus(self, arg1)               ((self)->DemErrorRdciKalibrierungInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciOtherWuSensorType_ResetEventStatus(self)                  ((self)->DemErrorRdciOtherWuSensorType.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciOtherWuSensorType_SetEventStatus(self, arg1)              ((self)->DemErrorRdciOtherWuSensorType.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciOtherWuSensorTypeInfo_GetEventStatus(self, arg1)          ((self)->DemErrorRdciOtherWuSensorTypeInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciPannenwarnung_ResetEventStatus(self)                      ((self)->DemErrorRdciPannenwarnung.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciPannenwarnung_SetEventStatus(self, arg1)                  ((self)->DemErrorRdciPannenwarnung.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciPannenwarnungInfo_GetEventStatus(self, arg1)              ((self)->DemErrorRdciPannenwarnungInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciPartialSystemAvailability_ResetEventStatus(self)          ((self)->DemErrorRdciPartialSystemAvailability.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciPartialSystemAvailability_SetEventStatus(self, arg1)      ((self)->DemErrorRdciPartialSystemAvailability.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciPartialSystemAvailabilityInfo_GetEventStatus(self, arg1)  ((self)->DemErrorRdciPartialSystemAvailabilityInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1Alive_ResetEventStatus(self)                    ((self)->DemErrorRdciRdcDtPckg1Alive.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRdcDtPckg1Alive_SetEventStatus(self, arg1)                ((self)->DemErrorRdciRdcDtPckg1Alive.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1AliveInfo_GetEventStatus(self, arg1)            ((self)->DemErrorRdciRdcDtPckg1AliveInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1Invalid_ResetEventStatus(self)                  ((self)->DemErrorRdciRdcDtPckg1Invalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRdcDtPckg1Invalid_SetEventStatus(self, arg1)              ((self)->DemErrorRdciRdcDtPckg1Invalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1InvalidInfo_GetEventStatus(self, arg1)          ((self)->DemErrorRdciRdcDtPckg1InvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1Timeout_ResetEventStatus(self)                  ((self)->DemErrorRdciRdcDtPckg1Timeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRdcDtPckg1Timeout_SetEventStatus(self, arg1)              ((self)->DemErrorRdciRdcDtPckg1Timeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRdcDtPckg1TimeoutInfo_GetEventStatus(self, arg1)          ((self)->DemErrorRdciRdcDtPckg1TimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRelativzeitInvalid_ResetEventStatus(self)                 ((self)->DemErrorRdciRelativzeitInvalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRelativzeitInvalid_SetEventStatus(self, arg1)             ((self)->DemErrorRdciRelativzeitInvalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRelativzeitInvalidInfo_GetEventStatus(self, arg1)         ((self)->DemErrorRdciRelativzeitInvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRelativzeitTimeout_ResetEventStatus(self)                 ((self)->DemErrorRdciRelativzeitTimeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRelativzeitTimeout_SetEventStatus(self, arg1)             ((self)->DemErrorRdciRelativzeitTimeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRelativzeitTimeoutInfo_GetEventStatus(self, arg1)         ((self)->DemErrorRdciRelativzeitTimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRfExternalInterference_ResetEventStatus(self)             ((self)->DemErrorRdciRfExternalInterference.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciRfExternalInterference_SetEventStatus(self, arg1)         ((self)->DemErrorRdciRfExternalInterference.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciRfExternalInterferenceInfo_GetEventStatus(self, arg1)     ((self)->DemErrorRdciRfExternalInterferenceInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciSystemNotAvailable_ResetEventStatus(self)                 ((self)->DemErrorRdciSystemNotAvailable.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciSystemNotAvailable_SetEventStatus(self, arg1)             ((self)->DemErrorRdciSystemNotAvailable.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciSystemNotAvailableInfo_GetEventStatus(self, arg1)         ((self)->DemErrorRdciSystemNotAvailableInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciTpmsManufactoryMode_ResetEventStatus(self)                ((self)->DemErrorRdciTpmsManufactoryMode.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciTpmsManufactoryMode_SetEventStatus(self, arg1)            ((self)->DemErrorRdciTpmsManufactoryMode.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciTpmsManufactoryModeInfo_GetEventStatus(self, arg1)        ((self)->DemErrorRdciTpmsManufactoryModeInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciUnspecifiedWfcDefect_ResetEventStatus(self)               ((self)->DemErrorRdciUnspecifiedWfcDefect.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciUnspecifiedWfcDefect_SetEventStatus(self, arg1)           ((self)->DemErrorRdciUnspecifiedWfcDefect.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciUnspecifiedWfcDefectInfo_GetEventStatus(self, arg1)       ((self)->DemErrorRdciUnspecifiedWfcDefectInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciUnspecifiedWuMute_ResetEventStatus(self)                  ((self)->DemErrorRdciUnspecifiedWuMute.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciUnspecifiedWuMute_SetEventStatus(self, arg1)              ((self)->DemErrorRdciUnspecifiedWuMute.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciUnspecifiedWuMuteInfo_GetEventStatus(self, arg1)          ((self)->DemErrorRdciUnspecifiedWuMuteInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehAliveFailure_ResetEventStatus(self)                   ((self)->DemErrorRdciVVehAliveFailure.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciVVehAliveFailure_SetEventStatus(self, arg1)               ((self)->DemErrorRdciVVehAliveFailure.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehAliveFailureInfo_GetEventStatus(self, arg1)           ((self)->DemErrorRdciVVehAliveFailureInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCogInvalid_ResetEventStatus(self)                     ((self)->DemErrorRdciVVehCogInvalid.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciVVehCogInvalid_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciVVehCogInvalid.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCogInvalidInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciVVehCogInvalidInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCogQualifier_ResetEventStatus(self)                   ((self)->DemErrorRdciVVehCogQualifier.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciVVehCogQualifier_SetEventStatus(self, arg1)               ((self)->DemErrorRdciVVehCogQualifier.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCogQualifierInfo_GetEventStatus(self, arg1)           ((self)->DemErrorRdciVVehCogQualifierInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCrcFailure_ResetEventStatus(self)                     ((self)->DemErrorRdciVVehCrcFailure.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciVVehCrcFailure_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciVVehCrcFailure.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehCrcFailureInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciVVehCrcFailureInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehTimeout_ResetEventStatus(self)                        ((self)->DemErrorRdciVVehTimeout.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciVVehTimeout_SetEventStatus(self, arg1)                    ((self)->DemErrorRdciVVehTimeout.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciVVehTimeoutInfo_GetEventStatus(self, arg1)                ((self)->DemErrorRdciVVehTimeoutInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWarnruecknahme_ResetEventStatus(self)                     ((self)->DemErrorRdciWarnruecknahme.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWarnruecknahme_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciWarnruecknahme.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWarnruecknahmeInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciWarnruecknahmeInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectFl_ResetEventStatus(self)                         ((self)->DemErrorRdciWuDefectFl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuDefectFl_SetEventStatus(self, arg1)                     ((self)->DemErrorRdciWuDefectFl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectFlInfo_GetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuDefectFlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectFr_ResetEventStatus(self)                         ((self)->DemErrorRdciWuDefectFr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuDefectFr_SetEventStatus(self, arg1)                     ((self)->DemErrorRdciWuDefectFr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectFrInfo_GetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuDefectFrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectRl_ResetEventStatus(self)                         ((self)->DemErrorRdciWuDefectRl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuDefectRl_SetEventStatus(self, arg1)                     ((self)->DemErrorRdciWuDefectRl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectRlInfo_GetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuDefectRlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectRr_ResetEventStatus(self)                         ((self)->DemErrorRdciWuDefectRr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuDefectRr_SetEventStatus(self, arg1)                     ((self)->DemErrorRdciWuDefectRr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuDefectRrInfo_GetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuDefectRrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLocalisationFailed_ResetEventStatus(self)               ((self)->DemErrorRdciWuLocalisationFailed.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuLocalisationFailed_SetEventStatus(self, arg1)           ((self)->DemErrorRdciWuLocalisationFailed.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLocalisationFailedInfo_GetEventStatus(self, arg1)       ((self)->DemErrorRdciWuLocalisationFailedInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryFl_ResetEventStatus(self)                     ((self)->DemErrorRdciWuLowBatteryFl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuLowBatteryFl_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuLowBatteryFl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryFlInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciWuLowBatteryFlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryFr_ResetEventStatus(self)                     ((self)->DemErrorRdciWuLowBatteryFr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuLowBatteryFr_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuLowBatteryFr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryFrInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciWuLowBatteryFrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryRl_ResetEventStatus(self)                     ((self)->DemErrorRdciWuLowBatteryRl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuLowBatteryRl_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuLowBatteryRl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryRlInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciWuLowBatteryRlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryRr_ResetEventStatus(self)                     ((self)->DemErrorRdciWuLowBatteryRr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuLowBatteryRr_SetEventStatus(self, arg1)                 ((self)->DemErrorRdciWuLowBatteryRr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuLowBatteryRrInfo_GetEventStatus(self, arg1)             ((self)->DemErrorRdciWuLowBatteryRrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteFl_ResetEventStatus(self)                           ((self)->DemErrorRdciWuMuteFl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuMuteFl_SetEventStatus(self, arg1)                       ((self)->DemErrorRdciWuMuteFl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteFlInfo_GetEventStatus(self, arg1)                   ((self)->DemErrorRdciWuMuteFlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteFr_ResetEventStatus(self)                           ((self)->DemErrorRdciWuMuteFr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuMuteFr_SetEventStatus(self, arg1)                       ((self)->DemErrorRdciWuMuteFr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteFrInfo_GetEventStatus(self, arg1)                   ((self)->DemErrorRdciWuMuteFrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteRl_ResetEventStatus(self)                           ((self)->DemErrorRdciWuMuteRl.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuMuteRl_SetEventStatus(self, arg1)                       ((self)->DemErrorRdciWuMuteRl.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteRlInfo_GetEventStatus(self, arg1)                   ((self)->DemErrorRdciWuMuteRlInfo.Call_GetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteRr_ResetEventStatus(self)                           ((self)->DemErrorRdciWuMuteRr.Call_ResetEventStatus())
#define Rte_Call_DemErrorRdciWuMuteRr_SetEventStatus(self, arg1)                       ((self)->DemErrorRdciWuMuteRr.Call_SetEventStatus(arg1))
#define Rte_Call_DemErrorRdciWuMuteRrInfo_GetEventStatus(self, arg1)                   ((self)->DemErrorRdciWuMuteRrInfo.Call_GetEventStatus(arg1))
#define Rte_Call_StbMB_AbsoluteTimeBaseValue_GetAbsoluteTime(self, arg1)               ((self)->StbMB_AbsoluteTimeBaseValue.Call_GetAbsoluteTime(arg1))
#define Rte_Call_StbMB_AbsoluteTimeBaseValue_GetGlobalTime(self, arg1)                 ((self)->StbMB_AbsoluteTimeBaseValue.Call_GetGlobalTime(arg1))
#define Rte_Call_StbMB_AbsoluteTimeBaseValue_GetSyncState(self, arg1)                  ((self)->StbMB_AbsoluteTimeBaseValue.Call_GetSyncState(arg1))
#define Rte_Call_StbMB_AbsoluteTimeBaseValue_GetTickDuration(self, arg1)               ((self)->StbMB_AbsoluteTimeBaseValue.Call_GetTickDuration(arg1))
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmTh(self)                                     ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmTh())
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmPressOffsetFa(self)                          ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmPressOffsetFa())
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmPressOffsetRa(self)                          ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmPressOffsetRa())
#define Rte_Prm_RpCalPrmRDCi_CRdciCorHoldOffTime(self)                                 ((self)->RpCalPrmRDCi.Prm_CRdciCorHoldOffTime())
#define Rte_Prm_RpCalPrmRDCi_CRdciDefaultLoadCond(self)                                ((self)->RpCalPrmRDCi.Prm_CRdciDefaultLoadCond())
#define Rte_Prm_RpCalPrmRDCi_CRdciDefaultMenuSel(self)                                 ((self)->RpCalPrmRDCi.Prm_CRdciDefaultMenuSel())
#define Rte_Prm_RpCalPrmRDCi_CRdciDeltaPLR(self)                                       ((self)->RpCalPrmRDCi.Prm_CRdciDeltaPLR())
#define Rte_Prm_RpCalPrmRDCi_CRdciDispConfTimeout(self)                                ((self)->RpCalPrmRDCi.Prm_CRdciDispConfTimeout())
#define Rte_Prm_RpCalPrmRDCi_CRdciDispReset(self)                                      ((self)->RpCalPrmRDCi.Prm_CRdciDispReset())
#define Rte_Prm_RpCalPrmRDCi_CRdciDpToIPmin(self)                                      ((self)->RpCalPrmRDCi.Prm_CRdciDpToIPmin())
#define Rte_Prm_RpCalPrmRDCi_CRdciDtAmbPrewarn(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciDtAmbPrewarn())
#define Rte_Prm_RpCalPrmRDCi_CRdciEcoRcpEnable(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciEcoRcpEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciErfsEnable(self)                                     ((self)->RpCalPrmRDCi.Prm_CRdciErfsEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciErfsPlacardSource(self)                              ((self)->RpCalPrmRDCi.Prm_CRdciErfsPlacardSource())
#define Rte_Prm_RpCalPrmRDCi_CRdciFastDeflateEnable(self)                              ((self)->RpCalPrmRDCi.Prm_CRdciFastDeflateEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciLongHoldTime(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciLongHoldTime())
#define Rte_Prm_RpCalPrmRDCi_CRdciMaxCorRcp(self)                                      ((self)->RpCalPrmRDCi.Prm_CRdciMaxCorRcp())
#define Rte_Prm_RpCalPrmRDCi_CRdciMaxCorTime(self)                                     ((self)->RpCalPrmRDCi.Prm_CRdciMaxCorTime())
#define Rte_Prm_RpCalPrmRDCi_CRdciMaxThreshold(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciMaxThreshold())
#define Rte_Prm_RpCalPrmRDCi_CRdciMinRcpFa(self)                                       ((self)->RpCalPrmRDCi.Prm_CRdciMinRcpFa())
#define Rte_Prm_RpCalPrmRDCi_CRdciMinRcpRa(self)                                       ((self)->RpCalPrmRDCi.Prm_CRdciMinRcpRa())
#define Rte_Prm_RpCalPrmRDCi_CRdciNumPrewarnDetect(self)                               ((self)->RpCalPrmRDCi.Prm_CRdciNumPrewarnDetect())
#define Rte_Prm_RpCalPrmRDCi_CRdciPInitRangeMax(self)                                  ((self)->RpCalPrmRDCi.Prm_CRdciPInitRangeMax())
#define Rte_Prm_RpCalPrmRDCi_CRdciPanneBefPos(self)                                    ((self)->RpCalPrmRDCi.Prm_CRdciPanneBefPos())
#define Rte_Prm_RpCalPrmRDCi_CRdciPanneTh(self)                                        ((self)->RpCalPrmRDCi.Prm_CRdciPanneTh())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupExtParkSupConfig(self)                        ((self)->RpCalPrmRDCi.Prm_CRdciParkSupExtParkSupConfig())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupMobilityLossThresholdValue(self)              ((self)->RpCalPrmRDCi.Prm_CRdciParkSupMobilityLossThresholdValue())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupNotificationThresholdValueC(self)             ((self)->RpCalPrmRDCi.Prm_CRdciParkSupNotificationThresholdValueC())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupNotificationThresholdValueNc(self)            ((self)->RpCalPrmRDCi.Prm_CRdciParkSupNotificationThresholdValueNc())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupTolNoTempComp(self)                           ((self)->RpCalPrmRDCi.Prm_CRdciParkSupTolNoTempComp())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupTolTempComp(self)                             ((self)->RpCalPrmRDCi.Prm_CRdciParkSupTolTempComp())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupWarningThresholdValueC(self)                  ((self)->RpCalPrmRDCi.Prm_CRdciParkSupWarningThresholdValueC())
#define Rte_Prm_RpCalPrmRDCi_CRdciParkSupWarningThresholdValueNc(self)                 ((self)->RpCalPrmRDCi.Prm_CRdciParkSupWarningThresholdValueNc())
#define Rte_Prm_RpCalPrmRDCi_CRdciPrewarnEnable(self)                                  ((self)->RpCalPrmRDCi.Prm_CRdciPrewarnEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciPrewarnIgnition(self)                                ((self)->RpCalPrmRDCi.Prm_CRdciPrewarnIgnition())
#define Rte_Prm_RpCalPrmRDCi_CRdciResetPlausi(self)                                    ((self)->RpCalPrmRDCi.Prm_CRdciResetPlausi())
#define Rte_Prm_RpCalPrmRDCi_CRdciRidEnable(self)                                      ((self)->RpCalPrmRDCi.Prm_CRdciRidEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciSensorForeignAkRdk(self)                             ((self)->RpCalPrmRDCi.Prm_CRdciSensorForeignAkRdk())
#define Rte_Prm_RpCalPrmRDCi_CRdciSensorLocSync(self)                                  ((self)->RpCalPrmRDCi.Prm_CRdciSensorLocSync())
#define Rte_Prm_RpCalPrmRDCi_CRdciShortHoldTime(self)                                  ((self)->RpCalPrmRDCi.Prm_CRdciShortHoldTime())
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmEnable(self)                                 ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmEnable())
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmHyst(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmHyst())
#define Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmTime(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciSpeedCcmTime())
#define Rte_Prm_RpCalPrmRDCi_CRdciStatInit(self)                                       ((self)->RpCalPrmRDCi.Prm_CRdciStatInit())
#define Rte_Prm_RpCalPrmRDCi_CRdciTPrewarnNc(self)                                     ((self)->RpCalPrmRDCi.Prm_CRdciTPrewarnNc())
#define Rte_Prm_RpCalPrmRDCi_CRdciTRefShift(self)                                      ((self)->RpCalPrmRDCi.Prm_CRdciTRefShift())
#define Rte_Prm_RpCalPrmRDCi_CRdciThCTol(self)                                         ((self)->RpCalPrmRDCi.Prm_CRdciThCTol())
#define Rte_Prm_RpCalPrmRDCi_CRdciThNCTol(self)                                        ((self)->RpCalPrmRDCi.Prm_CRdciThNCTol())
#define Rte_Prm_RpCalPrmRDCi_CRdciTimeoutPrewarn(self)                                 ((self)->RpCalPrmRDCi.Prm_CRdciTimeoutPrewarn())
#define Rte_Prm_RpCalPrmRDCi_CRdciTpmsMarket(self)                                     ((self)->RpCalPrmRDCi.Prm_CRdciTpmsMarket())
#define Rte_Prm_RpCalPrmRDCi_CRdciTrefSeasonalAdjustment(self)                         ((self)->RpCalPrmRDCi.Prm_CRdciTrefSeasonalAdjustment())
#define Rte_Prm_RpCalPrmRDCi_CRdciTyrIdFiltGw(self)                                    ((self)->RpCalPrmRDCi.Prm_CRdciTyrIdFiltGw())
#define Rte_Prm_RpCalPrmRDCi_CRdciUiaThC(self)                                         ((self)->RpCalPrmRDCi.Prm_CRdciUiaThC())
#define Rte_Prm_RpCalPrmRDCi_CRdciUiaThNc(self)                                        ((self)->RpCalPrmRDCi.Prm_CRdciUiaThNc())
#define Rte_Prm_RpCalPrmRDCi_CRdciUiwThC(self)                                         ((self)->RpCalPrmRDCi.Prm_CRdciUiwThC())
#define Rte_Prm_RpCalPrmRDCi_CRdciUiwThNc(self)                                        ((self)->RpCalPrmRDCi.Prm_CRdciUiwThNc())
#define Rte_Prm_RpCalPrmRDCi_CRdciXminCoolTire(self)                                   ((self)->RpCalPrmRDCi.Prm_CRdciXminCoolTire())
#define Rte_Prm_RpCalPrmRDCi_CRdciLearnLocateConfig(self)                              ((self)->RpCalPrmRDCi.Prm_CRdciLearnLocateConfig())
#define Rte_Prm_RpCalPrmRDCi_CRdciTrefSeasAdjConfig(self)                              ((self)->RpCalPrmRDCi.Prm_CRdciTrefSeasAdjConfig())
#define Rte_Prm_RpCalPrmRDCi_CRdciErfsReifenEco(self)                                  ((self)->RpCalPrmRDCi.Prm_CRdciErfsReifenEco())

typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciCommonBlockType     NvmRdciCommonBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock1Type      NvmRdciDiagBlock1Type;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock2Type      NvmRdciDiagBlock2Type;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsBlockType       NvmRdciErfsBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsEcoBlockType    NvmRdciErfsEcoBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsTsaBlockType    NvmRdciErfsTsaBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock1Type     NvmRdciRidQrBlock1Type;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock2Type     NvmRdciRidQrBlock2Type;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciWarnStatusBlockType NvmRdciWarnStatusBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciZoHistoryBlockType  NvmRdciZoHistoryBlockType;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock1Type       NvmRdciZomBlock1Type;
typedef Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock2Type       NvmRdciZomBlock2Type;

#define Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)     ((self)->Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)      ((self)->Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)      ((self)->Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)       ((self)->Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)    ((self)->Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self)    ((self)->Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self)     ((self)->Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self)     ((self)->Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock(self) ((self)->Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)  ((self)->Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock(self)       ((self)->Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock)
#define Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock(self)       ((self)->Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock)

#define RTE_RUNNABLE_RCyclicRDCiTask RCyclicRDCiTask
FUNC(void, CtApHufTpmsSWC_CODE) RCyclicRDCiTask(Rte_Instance self);

#define RTE_RUNNABLE_RExitRDCiBye RExitRDCiBye
FUNC(void, CtApHufTpmsSWC_CODE) RExitRDCiBye(Rte_Instance self);

#define RTE_RUNNABLE_RInitRDCiStartup RInitRDCiStartup
FUNC(void, CtApHufTpmsSWC_CODE) RInitRDCiStartup(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_FunktionenReifendruckkontrolleReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcAktuelleAussentemperaturReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcAussendruck_ConditionCheckRead ROpInvDcmDiagRdcAussendruck_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAussendruck_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcAussendruck_ReadData ROpInvDcmDiagRdcAussendruck_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAussendruck_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcInaktivStatus_ReadData ROpInvDcmDiagRdcInaktivStatus_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcInaktivStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcInaktivStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcKalibrierungStatus_ReadData ROpInvDcmDiagRdcKalibrierungStatus_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKalibrierungStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcKalibrierungStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcKonfiguration_ReadData ROpInvDcmDiagRdcKonfiguration_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKonfiguration_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcKonfigurationReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcPosition_ConditionCheckRead ROpInvDcmDiagRdcPosition_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcPosition_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcPosition_ReadData ROpInvDcmDiagRdcPosition_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcPosition_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcPositionReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReferenzAussentemperaturReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckHl_ReadData ROpInvDcmDiagRdcReifendruckHl_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHl_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckHr_ReadData ROpInvDcmDiagRdcReifendruckHr_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHr_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckVl_ReadData ROpInvDcmDiagRdcReifendruckVl_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVl_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifendruckVr_ReadData ROpInvDcmDiagRdcReifendruckVr_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVr_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturHl_ReadData ROpInvDcmDiagRdcReifentemperaturHl_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHl_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturHlReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturHr_ReadData ROpInvDcmDiagRdcReifentemperaturHr_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHr_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturHrReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturVl_ReadData ROpInvDcmDiagRdcReifentemperaturVl_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVl_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturVlReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcReifentemperaturVr_ReadData ROpInvDcmDiagRdcReifentemperaturVr_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVr_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturVrReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSensorHersteller_ReadData ROpInvDcmDiagRdcSensorHersteller_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSensorHersteller_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcSensorHerstellerReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSolldruckHinten_ReadData ROpInvDcmDiagRdcSolldruckHinten_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckHinten_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcSolldruckVorn_ReadData ROpInvDcmDiagRdcSolldruckVorn_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckVorn_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcStatus_ConditionCheckRead ROpInvDcmDiagRdcStatus_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmDiagRdcStatus_ReadData ROpInvDcmDiagRdcStatus_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcErfsEcoTabelleLesen_ReadData ROpInvDcmRdcErfsEcoTabelleLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcErfsEcoTabelleLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsInaktivereignis_ReadData ROpInvDcmRdcHsInaktivereignis_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsInaktivereignis_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsKalibrierereignis_ReadData ROpInvDcmRdcHsKalibrierereignis_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsKalibrierereignis_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis1_ReadData ROpInvDcmRdcHsWarnereignis1_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis2_ReadData ROpInvDcmRdcHsWarnereignis2_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignis3_ReadData ROpInvDcmRdcHsWarnereignis3_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich1_ReadData ROpInvDcmRdcHsWarnereignisWeich1_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich2_ReadData ROpInvDcmRdcHsWarnereignisWeich2_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcHsWarnereignisWeich3_ReadData ROpInvDcmRdcHsWarnereignisWeich3_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock1_ConditionCheckRead ROpInvDcmRdcMessdatenblock1_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock1_ReadData ROpInvDcmRdcMessdatenblock1_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock2_ConditionCheckRead ROpInvDcmRdcMessdatenblock2_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock2_ReadData ROpInvDcmRdcMessdatenblock2_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock3_ConditionCheckRead ROpInvDcmRdcMessdatenblock3_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock3_ReadData ROpInvDcmRdcMessdatenblock3_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock4_ConditionCheckRead ROpInvDcmRdcMessdatenblock4_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock4_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcMessdatenblock4_ReadData ROpInvDcmRdcMessdatenblock4_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock4_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcDeveloperDataLesen_ReadData ROpInvDcmStatusRdcDeveloperDataLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcDeveloperDataLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsTsaDatenLesen_ConditionCheckRead ROpInvDcmStatusRdcErfsTsaDatenLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsTsaDatenLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcErfsTsaDatenLesen_ReadData ROpInvDcmStatusRdcErfsTsaDatenLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsTsaDatenLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcLesen_ConditionCheckRead ROpInvDcmStatusRdcLesen_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcLesen_ReadData ROpInvDcmStatusRdcLesen_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcVersion_ConditionCheckRead ROpInvDcmStatusRdcVersion_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcVersion_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusRdcVersion_ReadData ROpInvDcmStatusRdcVersion_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcVersion_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmStatusReLesenDruckcodierung_ReadData ROpInvDcmStatusReLesenDruckcodierung_ReadData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusReLesenDruckcodierung_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data);

#define RTE_RUNNABLE_ROpInvDcmSteuernDigitalRdc_WriteData ROpInvDcmSteuernDigitalRdc_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernDigitalRdc_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRadelektronikVorgeben_WriteData ROpInvDcmSteuernRadelektronikVorgeben_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRadelektronikVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcDeveloperConfig_WriteData ROpInvDcmSteuernRdcDeveloperConfig_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcDeveloperConfig_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, ImpTypeRefDcm_OpStatusType OpStatus, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, ImpTypeRefDcm_OpStatusType OpStatus, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDcmSteuernRdcErfsTsaDatenVorgeben_WriteData ROpInvDcmSteuernRdcErfsTsaDatenVorgeben_WriteData
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsTsaDatenVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode);

#define RTE_RUNNABLE_ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciAusfall_InitMonitorForEvent ROpInvDemErrorRdciAusfall_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciAusfall_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciPartialSystemAvailability_InitMonitorForEvent ROpInvDemErrorRdciPartialSystemAvailability_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciPartialSystemAvailability_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciSystemNotAvailable_InitMonitorForEvent ROpInvDemErrorRdciSystemNotAvailable_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciSystemNotAvailable_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent
FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason);

#define RTE_RUNNABLE_ROpInvNvmRdciCommonBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciCommonBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciCommonBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciCommonBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciCommonBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciCommonBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciDiagBlock1_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciDiagBlock1_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciDiagBlock1_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciDiagBlock1_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciDiagBlock2_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciDiagBlock2_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciDiagBlock2_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciDiagBlock2_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciErfsBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciErfsBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsEcoBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciErfsEcoBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsEcoBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsEcoBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciErfsEcoBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsEcoBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsTsaBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciErfsTsaBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsTsaBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciErfsTsaBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciErfsTsaBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsTsaBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciRidQrBlock1_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciRidQrBlock1_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciRidQrBlock1_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciRidQrBlock1_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciRidQrBlock2_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciRidQrBlock2_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciRidQrBlock2_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciRidQrBlock2_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciWarnStatusBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciWarnStatusBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciWarnStatusBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciWarnStatusBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciWarnStatusBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciWarnStatusBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciZoHistoryBlock_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciZoHistoryBlock_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZoHistoryBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciZoHistoryBlock_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciZoHistoryBlock_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZoHistoryBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciZomBlock1_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciZomBlock1_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciZomBlock1_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciZomBlock1_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_RUNNABLE_ROpInvNvmRdciZomBlock2_NvMNotifyInitBlock_InitBlock ROpInvNvmRdciZomBlock2_NvMNotifyInitBlock_InitBlock
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self);

#define RTE_RUNNABLE_ROpInvNvmRdciZomBlock2_NvMNotifyJobFinished_JobFinished ROpInvNvmRdciZomBlock2_NvMNotifyJobFinished_JobFinished
FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define RTE_E_NvMService_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmFunktionenReifendruckkontrolle_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcAktuelleAussentemperatur_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcAnlernenLokalisierungLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcAussendruck_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcErfsEcoTabelleLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsInaktivereignis_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsKalibrierereignis_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignis1_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignis2_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignis3_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignisRuecknahme_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignisWeich1_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignisWeich2_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcHsWarnereignisWeich3_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcInaktivStatus_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcKalibrierungStatus_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcKonfiguration_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcMessdatenblock1_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcMessdatenblock2_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcMessdatenblock3_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcMessdatenblock4_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcPosition_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReferenzAussentemperatur_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifendruckHl_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifendruckHr_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifendruckVl_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifendruckVr_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifentemperaturHl_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifentemperaturHr_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifentemperaturVl_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcReifentemperaturVr_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcRidAktReifenLaufstreckeLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcRidAktReifenQrCodeLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcRidAlteReifenLaufstreckeLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcRidAlteReifenQrCodeLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcSensorHersteller_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcSolldruckHinten_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcSolldruckVorn_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmRdcStatus_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcDeveloperDataLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcErfsAktReifenEcoLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcErfsAktReifenLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcErfsTsaDatenLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcExtParkSupervisionLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcLesen_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusRdcVersion_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmStatusReLesenDruckcodierung_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernDigitalRdc_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRadelektronikVorgeben_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcDeveloperConfig_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcErfsDeveloperConfig_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcErfsEcoAktReifenPosVorgeben_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_DCM_E_PENDING (10U)
#define RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcErfsEcoReifentabelleVorgeben_DCM_E_PENDING (10U)
#define RTE_E_PiServiceDcmSteuernRdcErfsEcoReifentabelleVorgeben_E_NOT_OK (1U)
#define RTE_E_PiServiceDcmSteuernRdcErfsTsaDatenVorgeben_E_NOT_OK (1U)
#define RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK (1U)
#define RTE_E_PiServiceDemInfo_E_NOT_OK (1U)
#define RTE_E_PiServiceDemMonitor_E_NOT_OK (1U)
#define RTE_E_StbMB_AbsoluteTimeBaseValue_E_NOT_OK (1U)

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
