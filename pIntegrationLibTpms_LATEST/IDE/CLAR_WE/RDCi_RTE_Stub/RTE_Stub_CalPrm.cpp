/******************************************************************************/
/* File   : RTE_Stub_CalPrm.cpp                                               */
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
#include "RTE_Stub_CalPrm.h"
#include "RTE_Stub_CalPrmNvmBlock.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#ifdef _EcuVirtual
ImpTypeRecCRdciErfsReifenEco ErfsReifenEcoTyreList = {{0}, 0};
#else
ImpTypeRecCRdciErfsReifenEco ErfsReifenEcoTyreList = {0};
#endif
ImpTypeArrayCRdciLearnLocateConfig LearnLocateConfig;
ImpTypeArrayCRdciTrefSeasAdjConfig TrefSeasAdjConfig;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(ImpTypeVal_C_Funktion_ReifenPannenerkennung_aktiv_e, RTE_CODE) Stub_Rte_Prm_C_Funktion_ReifenPannenerkennung_aktiv_e(void)
{
  ImpTypeVal_C_Funktion_ReifenPannenerkennung_aktiv_e ucRetVal;

  ucRetVal = NvmDscCodierdatenAllgemein_ReadByte( C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_BYTE, C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTPrewarnNc, RTE_CODE) Stub_Rte_Prm_CRdciTPrewarnNc(void)
{
  ImpTypeValCRdciTPrewarnNc ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_T_PREWARN_NC_BYTE, C_RDCI_T_PREWARN_NC_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciMaxThreshold, RTE_CODE) Stub_Rte_Prm_CRdciMaxThreshold(void)
{
  ImpTypeValCRdciMaxThreshold ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_MAX_THRESHOLD_BYTE, C_RDCI_MAX_THRESHOLD_MASK) >> 1);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciPrewarnEnable, RTE_CODE) Stub_Rte_Prm_CRdciPrewarnEnable(void)
{
  ImpTypeValCRdciPrewarnEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PREWARN_ENABLE_BYTE, C_RDCI_PREWARN_ENABLE_MASK) >> 2);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciStatInit, RTE_CODE) Stub_Rte_Prm_CRdciStatInit(void)
{
  ImpTypeValCRdciStatInit ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_STAT_INIT_BYTE, C_RDCI_STAT_INIT_MASK) >> 3);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciNumPrewarnDetect, RTE_CODE) Stub_Rte_Prm_CRdciNumPrewarnDetect(void)
{
  ImpTypeValCRdciNumPrewarnDetect ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_NUM_PREWARN_DETECT_BYTE, C_RDCI_NUM_PREWARN_DETECT_MASK) >> 4);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciPrewarnIgnition, RTE_CODE) Stub_Rte_Prm_CRdciPrewarnIgnition(void)
{
  ImpTypeValCRdciPrewarnIgnition ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PREWARN_IGNITION_BYTE, C_RDCI_PREWARN_IGNITION_MASK) >> 5);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciPanneBefPos, RTE_CODE) Stub_Rte_Prm_CRdciPanneBefPos(void)
{
  ImpTypeValCRdciPanneBefPos ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PANNE_BEF_POS_BYTE, C_RDCI_PANNE_BEF_POS_MASK) >> 6);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciFastDeflateEnable, RTE_CODE) Stub_Rte_Prm_CRdciFastDeflateEnable(void)
{
  ImpTypeValCRdciFastDeflateEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_FAST_DEFLATE_ENABLE_BYTE, C_RDCI_FAST_DEFLATE_ENABLE_MASK) >> 7);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTyrIdFiltGw, RTE_CODE) Stub_Rte_Prm_CRdciTyrIdFiltGw(void)
{
  ImpTypeValCRdciTyrIdFiltGw ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TYR_ID_FILT_GW_BYTE, C_RDCI_TYR_ID_FILT_GW_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciResetPlausi, RTE_CODE) Stub_Rte_Prm_CRdciResetPlausi(void)
{
  ImpTypeValCRdciResetPlausi ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_RESET_PLAUSI_BYTE, C_RDCI_RESET_PLAUSI_MASK) >> 1);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTpmsMarket, RTE_CODE) Stub_Rte_Prm_CRdciTpmsMarket(void)
{
  ImpTypeValCRdciTpmsMarket ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TPMS_MARKET_BYTE, C_RDCI_TPMS_MARKET_MASK) >> 2);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciSensorForeignAkRdk, RTE_CODE) Stub_Rte_Prm_CRdciSensorForeignAkRdk(void)
{
  ImpTypeValCRdciSensorForeignAkRdk ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SENSOR_FOREIGN_AK_RDK_BYTE, C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK) >> 5);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciSensorLocSync, RTE_CODE) Stub_Rte_Prm_CRdciSensorLocSync(void)
{
  ImpTypeValCRdciSensorLocSync ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SENSOR_LOC_SYNC_BYTE, C_RDCI_SENSOR_LOC_SYNC_MASK) >> 6);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciErfsEnable, RTE_CODE) Stub_Rte_Prm_CRdciErfsEnable(void)
{
  ImpTypeValCRdciErfsEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_ERFS_ENABLE_BYTE, C_RDCI_ERFS_ENABLE_MASK) >> 7);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTrefSeasonalAdjustment, RTE_CODE) Stub_Rte_Prm_CRdciTrefSeasonalAdjustment(void)
{
  ImpTypeValCRdciTrefSeasonalAdjustment ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_BYTE, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK) >> 0);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDispReset, RTE_CODE) Stub_Rte_Prm_CRdciDispReset(void)
{
  ImpTypeValCRdciDispReset ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DISP_RESET_BYTE, C_RDCI_DISP_RESET_MASK) >> 4);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciCorHoldOffTime, RTE_CODE) Stub_Rte_Prm_CRdciCorHoldOffTime(void)
{
  ImpTypeValCRdciCorHoldOffTime ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_COR_HOLD_OFF_TIME_BYTE, C_RDCI_COR_HOLD_OFF_TIME_MASK) >> 5);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTRefShift, RTE_CODE) Stub_Rte_Prm_CRdciTRefShift(void)
{
  ImpTypeValCRdciTRefShift ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_T_REF_SHIFT_BYTE, C_RDCI_T_REF_SHIFT_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciUiaThC, RTE_CODE) Stub_Rte_Prm_CRdciUiaThC(void)
{
  ImpTypeValCRdciUiaThC ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_UIA_TH_C_BYTE, C_RDCI_UIA_TH_C_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciUiwThC, RTE_CODE) Stub_Rte_Prm_CRdciUiwThC(void)
{
  ImpTypeValCRdciUiwThC ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_UIW_TH_C_BYTE, C_RDCI_UIW_TH_C_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciUiaThNc, RTE_CODE) Stub_Rte_Prm_CRdciUiaThNc(void)
{
  ImpTypeValCRdciUiaThNc ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_UIA_TH_NC_BYTE, C_RDCI_UIA_TH_NC_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciUiwThNc, RTE_CODE) Stub_Rte_Prm_CRdciUiwThNc(void)
{
  ImpTypeValCRdciUiwThNc ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_UIW_TH_NC_BYTE, C_RDCI_UIW_TH_NC_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciPanneTh, RTE_CODE) Stub_Rte_Prm_CRdciPanneTh(void)
{
  ImpTypeValCRdciPanneTh ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PANNE_TH_BYTE, C_RDCI_PANNE_TH_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciMinRcpFa, RTE_CODE) Stub_Rte_Prm_CRdciMinRcpFa(void)
{
  ImpTypeValCRdciMinRcpFa ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_MIN_RCP_FA_BYTE, C_RDCI_MIN_RCP_FA_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciMinRcpRa, RTE_CODE) Stub_Rte_Prm_CRdciMinRcpRa(void)
{
  ImpTypeValCRdciMinRcpRa ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_MIN_RCP_RA_BYTE, C_RDCI_MIN_RCP_RA_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDeltaPLR, RTE_CODE) Stub_Rte_Prm_CRdciDeltaPLR(void)
{
  ImpTypeValCRdciDeltaPLR ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DELTA_P_L_R_BYTE, C_RDCI_DELTA_P_L_R_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciPInitRangeMax, RTE_CODE) Stub_Rte_Prm_CRdciPInitRangeMax(void)
{
  ImpTypeValCRdciPInitRangeMax ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_P_INIT_RANGE_MAX_BYTE, C_RDCI_P_INIT_RANGE_MAX_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciTimeoutPrewarn, RTE_CODE) Stub_Rte_Prm_CRdciTimeoutPrewarn(void)
{
  ImpTypeValCRdciTimeoutPrewarn ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TIMEOUT_PREWARN_BYTE, C_RDCI_TIMEOUT_PREWARN_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDtAmbPrewarn, RTE_CODE) Stub_Rte_Prm_CRdciDtAmbPrewarn(void)
{
  ImpTypeValCRdciDtAmbPrewarn ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DT_AMB_PREWARN_BYTE, C_RDCI_DT_AMB_PREWARN_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDpToIPmin, RTE_CODE) Stub_Rte_Prm_CRdciDpToIPmin(void)
{
  ImpTypeValCRdciDpToIPmin ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DP_TO_I_PMIN_BYTE, C_RDCI_DP_TO_I_PMIN_MASK);

  return ucRetVal;
}

Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciLearnLocateConfig_FncRetPtrType Stub_Rte_Prm_CRdciLearnLocateConfig(void)
{
  LearnLocateConfig[0] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_0, C_RDCI_LEARN_LOCATE_CONFIG_MASK_0);
  LearnLocateConfig[1] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_1, C_RDCI_LEARN_LOCATE_CONFIG_MASK_1);

  return LearnLocateConfig;
}

FUNC(ImpTypeValCRdciXminCoolTire, RTE_CODE) Stub_Rte_Prm_CRdciXminCoolTire(void)
{
  ImpTypeValCRdciXminCoolTire ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_XMIN_COOL_TIRE_BYTE, C_RDCI_XMIN_COOL_TIRE_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciMaxCorTime, RTE_CODE) Stub_Rte_Prm_CRdciMaxCorTime(void)
{
  ImpTypeValCRdciMaxCorTime ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_MAX_COR_TIME_BYTE, C_RDCI_MAX_COR_TIME_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciMaxCorRcp, RTE_CODE) Stub_Rte_Prm_CRdciMaxCorRcp(void)
{
  ImpTypeValCRdciMaxCorRcp ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_MAX_COR_RCP_BYTE, C_RDCI_MAX_COR_RCP_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciThCTol, RTE_CODE) Stub_Rte_Prm_CRdciThCTol(void)
{
  ImpTypeValCRdciThCTol ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TH_C_TOL_BYTE, C_RDCI_TH_C_TOL_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciThNCTol, RTE_CODE) Stub_Rte_Prm_CRdciThNCTol(void)
{
  ImpTypeValCRdciThNCTol ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TH_NC_TOL_BYTE, C_RDCI_TH_NC_TOL_MASK) >> 4);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciLongHoldTime, RTE_CODE) Stub_Rte_Prm_CRdciLongHoldTime(void)
{
  ImpTypeValCRdciLongHoldTime ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_LONG_HOLD_TIME_BYTE, C_RDCI_LONG_HOLD_TIME_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciShortHoldTime, RTE_CODE) Stub_Rte_Prm_CRdciShortHoldTime(void)
{
  ImpTypeValCRdciShortHoldTime ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SHORT_HOLD_TIME_BYTE, C_RDCI_SHORT_HOLD_TIME_MASK) >> 4);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciEcoRcpEnable, RTE_CODE) Stub_Rte_Prm_CRdciEcoRcpEnable(void)
{
  ImpTypeValCRdciEcoRcpEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_ECO_RCP_ENABLE_BYTE, C_RDCI_ECO_RCP_ENABLE_MASK) >> 7);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDefaultLoadCond, RTE_CODE) Stub_Rte_Prm_CRdciDefaultLoadCond(void)
{
  ImpTypeValCRdciDefaultLoadCond ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DEFAULT_LOAD_COND_BYTE, C_RDCI_DEFAULT_LOAD_COND_MASK) >> 0);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciErfsPlacardSource, RTE_CODE) Stub_Rte_Prm_CRdciErfsPlacardSource(void)
{
  ImpTypeValCRdciErfsPlacardSource ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_ERFS_PLACARD_SOURCE_BYTE, C_RDCI_ERFS_PLACARD_SOURCE_MASK) >> 1);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDefaultMenuSel, RTE_CODE) Stub_Rte_Prm_CRdciDefaultMenuSel(void)
{
  ImpTypeValCRdciDefaultMenuSel ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DEFAULT_MENU_SEL_BYTE, C_RDCI_DEFAULT_MENU_SEL_MASK) >> 3);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciDispConfTimeout, RTE_CODE) Stub_Rte_Prm_CRdciDispConfTimeout(void)
{
  ImpTypeValCRdciDispConfTimeout ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_DISP_CONF_TIMEOUT_BYTE, C_RDCI_DISP_CONF_TIMEOUT_MASK) >> 4);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciRidEnable, RTE_CODE) Stub_Rte_Prm_CRdciRidEnable(void)
{
  ImpTypeValCRdciRidEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_RID_ENABLE_BYTE, C_RDCI_RID_ENABLE_MASK) >> 0);

  return ucRetVal;
}

Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciTrefSeasAdjConfig_FncRetPtrType Stub_Rte_Prm_CRdciTrefSeasAdjConfig(void)
{
  TrefSeasAdjConfig[0] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_0, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_0);
  TrefSeasAdjConfig[1] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_1, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_1);
  TrefSeasAdjConfig[2] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_2, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_2);
  TrefSeasAdjConfig[3] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_3, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_3);

  return TrefSeasAdjConfig;
}

FUNC(ImpTypeValCRdciSpeedCcmEnable, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmEnable(void)
{
  ImpTypeValCRdciSpeedCcmEnable ucRetVal;

  ucRetVal = (NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_ENABLE_BYTE, C_RDCI_SPEED_CCM_ENABLE_MASK) >> 0);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciSpeedCcmHyst, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmHyst(void)
{
  ImpTypeValCRdciSpeedCcmHyst ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_HYST_BYTE, C_RDCI_SPEED_CCM_HYST_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciSpeedCcmPressOffsetFa, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmPressOffsetFa(void)
{
  union
  {
    ImpTypeValCRdciSpeedCcmPressOffsetFa SpeedCcmPressOffsetFa;
    uint8                                aucSpeedCcmPressOffsetFa[sizeof(ImpTypeValCRdciSpeedCcmPressOffsetFa)];
  } tSpeedCcmPressOffsetFa;

  tSpeedCcmPressOffsetFa.aucSpeedCcmPressOffsetFa[0] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_0);
  tSpeedCcmPressOffsetFa.aucSpeedCcmPressOffsetFa[1] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_1);

  return tSpeedCcmPressOffsetFa.SpeedCcmPressOffsetFa;
}

FUNC(ImpTypeValCRdciSpeedCcmPressOffsetRa, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmPressOffsetRa(void)
{
  union
  {
    ImpTypeValCRdciSpeedCcmPressOffsetRa SpeedCcmPressOffsetRa;
    uint8                                aucSpeedCcmPressOffsetRa[sizeof(ImpTypeValCRdciSpeedCcmPressOffsetRa)];
  } tSpeedCcmPressOffsetRa;

  tSpeedCcmPressOffsetRa.aucSpeedCcmPressOffsetRa[0] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_0);
  tSpeedCcmPressOffsetRa.aucSpeedCcmPressOffsetRa[1] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_1);

  return tSpeedCcmPressOffsetRa.SpeedCcmPressOffsetRa;
}

FUNC(ImpTypeValCRdciSpeedCcmTh, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmTh(void)
{
  union
  {
    ImpTypeValCRdciSpeedCcmTh SpeedCcmTh;
    uint8                     aucSpeedCcmTh[sizeof(ImpTypeValCRdciSpeedCcmTh)];
  } tSpeedCcmTh;

  tSpeedCcmTh.aucSpeedCcmTh[0] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_TH_BYTE_0, C_RDCI_SPEED_CCM_TH_MASK_0);
  tSpeedCcmTh.aucSpeedCcmTh[1] = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_TH_BYTE_1, C_RDCI_SPEED_CCM_TH_MASK_1);

  return tSpeedCcmTh.SpeedCcmTh;
}

FUNC(ImpTypeValCRdciSpeedCcmTime, RTE_CODE) Stub_Rte_Prm_CRdciSpeedCcmTime(void)
{
  ImpTypeValCRdciSpeedCcmTime ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_SPEED_CCM_TIME_BYTE, C_RDCI_SPEED_CCM_TIME_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupExtParkSupConfig, RTE_CODE) Stub_Rte_Prm_CRdciParkSupExtParkSupConfig(void)
{
  ImpTypeValCRdciParkSupExtParkSupConfig ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_BYTE, C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupMobilityLossThresholdValue, RTE_CODE) Stub_Rte_Prm_CRdciParkSupMobilityLossThresholdValue(void)
{
  ImpTypeValCRdciParkSupMobilityLossThresholdValue ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_BYTE, C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupNotificationThresholdValueC, RTE_CODE) Stub_Rte_Prm_CRdciParkSupNotificationThresholdValueC(void)
{
  ImpTypeValCRdciParkSupNotificationThresholdValueC ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupNotificationThresholdValueNc, RTE_CODE) Stub_Rte_Prm_CRdciParkSupNotificationThresholdValueNc(void)
{
  ImpTypeValCRdciParkSupNotificationThresholdValueNc ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupTolNoTempComp, RTE_CODE) Stub_Rte_Prm_CRdciParkSupTolNoTempComp(void)
{
  ImpTypeValCRdciParkSupTolNoTempComp ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupTolTempComp, RTE_CODE) Stub_Rte_Prm_CRdciParkSupTolTempComp(void)
{
  ImpTypeValCRdciParkSupTolTempComp ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_TOL_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_TEMP_COMP_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupWarningThresholdValueC, RTE_CODE) Stub_Rte_Prm_CRdciParkSupWarningThresholdValueC(void)
{
  ImpTypeValCRdciParkSupWarningThresholdValueC ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_MASK);

  return ucRetVal;
}

FUNC(ImpTypeValCRdciParkSupWarningThresholdValueNc, RTE_CODE) Stub_Rte_Prm_CRdciParkSupWarningThresholdValueNc(void)
{
  ImpTypeValCRdciParkSupWarningThresholdValueNc ucRetVal;

  ucRetVal = NvmDscCodierdatenRDCi_ReadByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_MASK);

  return ucRetVal;
}

Rte_CtApHufTpmsSWC_PiCalPrmRDCi_R_Calprm_CRdciErfsReifenEco_FncRetPtrType Stub_Rte_Prm_CRdciErfsReifenEco(void)
{
  static const ImpTypeRecCRdciErfsReifenEco aucTyreListDefaultVal  = {
                                                {

                                                      0x5A, 0x52, 0x4C, 0x54, 0x22, 0x5A, 0x77, 0x1F,
                                                      0x6A, 0x42, 0x5E, 0x5C, 0x22, 0x49, 0x77, 0x36,
                                                      0x6A, 0x3A, 0x6E, 0x50, 0x22, 0x49, 0x77, 0x72,
                                                      0x82, 0x32, 0x6E, 0x60, 0x22, 0x47, 0x77, 0xAC,
                                                      0x82, 0x2A, 0x7E, 0x54, 0x22, 0x49, 0x77, 0x9E,
                                                      0x82, 0x22, 0x8E, 0x44, 0x22, 0xAF, 0x77, 0x90,
                                                      0x5A, 0x52, 0x49, 0x55, 0x22, 0x5A, 0x77, 0x1B,
                                                      0x6A, 0x42, 0x59, 0x5E, 0x22, 0x49, 0x77, 0x33,
                                                      0x6A, 0x3A, 0x69, 0x51, 0x22, 0x49, 0x77, 0x74,
                                                      0x82, 0x32, 0x6A, 0x61, 0x22, 0x47, 0x77, 0xA9,
                                                      0x82, 0x32, 0x6A, 0x61, 0x24, 0x47, 0x77, 0xAF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
                                                                       },
                                                     { 0x5D02 }
                                                                     };

  ErfsReifenEcoTyreList = aucTyreListDefaultVal;

  return( &ErfsReifenEcoTyreList);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

