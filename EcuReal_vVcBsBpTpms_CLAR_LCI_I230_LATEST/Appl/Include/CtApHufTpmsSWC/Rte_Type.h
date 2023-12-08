#ifndef _RTE_TYPE_H
#define _RTE_TYPE_H
/******************************************************************************/
/* File   : Rte_Type.h                                                        */
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
#include "Rte.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8  ImpTypeValCRdciDeltaPLR;
typedef uint8  ImpTypeValCRdciDispConfTimeout;
typedef uint8  ImpTypeValCRdciDpToIPmin;
typedef uint8  ImpTypeValCRdciDtAmbPrewarn;
typedef uint8  ImpTypeValCRdciLongHoldTime;
typedef uint8  ImpTypeValCRdciMaxCorRcp;
typedef uint8  ImpTypeValCRdciMaxCorTime;
typedef uint8  ImpTypeValCRdciMinRcpFa;
typedef uint8  ImpTypeValCRdciMinRcpRa;
typedef uint8  ImpTypeValCRdciPInitRangeMax;
typedef uint8  ImpTypeValCRdciPanneTh;
typedef uint8  ImpTypeValCRdciParkSupExtParkSupConfig;
typedef uint8  ImpTypeValCRdciParkSupMobilityLossThresholdValue;
typedef uint8  ImpTypeValCRdciParkSupNotificationThresholdValueC;
typedef uint8  ImpTypeValCRdciParkSupNotificationThresholdValueNc;
typedef uint8  ImpTypeValCRdciParkSupTolNoTempComp;
typedef uint8  ImpTypeValCRdciParkSupTolTempComp;
typedef uint8  ImpTypeValCRdciParkSupWarningThresholdValueC;
typedef uint8  ImpTypeValCRdciParkSupWarningThresholdValueNc;
typedef uint8  ImpTypeValCRdciShortHoldTime;
typedef uint8  ImpTypeValCRdciSpeedCcmHyst;
typedef sint16 ImpTypeValCRdciSpeedCcmPressOffsetFa;
typedef sint16 ImpTypeValCRdciSpeedCcmPressOffsetRa;
typedef uint16 ImpTypeValCRdciSpeedCcmTh;
typedef uint8  ImpTypeValCRdciSpeedCcmTime;
typedef uint8  ImpTypeValCRdciTRefShift;
typedef uint8  ImpTypeValCRdciThCTol;
typedef uint8  ImpTypeValCRdciThNCTol;
typedef uint8  ImpTypeValCRdciTimeoutPrewarn;
typedef uint8  ImpTypeValCRdciUiaThC;
typedef uint8  ImpTypeValCRdciUiaThNc;
typedef uint8  ImpTypeValCRdciUiwThC;
typedef uint8  ImpTypeValCRdciUiwThNc;
typedef uint8  ImpTypeValCRdciXminCoolTire;
typedef uint8  ImpTypeValDcm_RdcAktuelleAussentemperaturReadDataType;
typedef uint8  ImpTypeValDcm_RdcReferenzAussentemperaturReadDataType;
typedef uint8  ImpTypeValDcm_RdcReifentemperaturHlReadDataType;
typedef uint8  ImpTypeValDcm_RdcReifentemperaturHrReadDataType;
typedef uint8  ImpTypeValDcm_RdcReifentemperaturVlReadDataType;
typedef uint8  ImpTypeValDcm_RdcReifentemperaturVrReadDataType;
typedef uint8  Rdci_AA_BAX_TYP_TYR_Type;
typedef uint8  Rdci_AA_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_AG_BAX_TYP_TYR_Type;
typedef uint8  Rdci_AG_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_BAX_TYP_TYR_ID2_Type;
typedef uint8  Rdci_CNTR_FBD_TPMS_1_ID2_Type;
typedef uint8  Rdci_CNTR_FBD_TPMS_2_ID2_Type;
typedef uint8  Rdci_CNTR_FBD_TPMS_3_ID2_Type;
typedef uint8  Rdci_CNTR_FBD_TPMS_4_ID2_Type;
typedef uint32 Rdci_CTR_TYR_ID_1_Type;
typedef uint32 Rdci_CTR_TYR_ID_2_Type;
typedef uint32 Rdci_CTR_TYR_ID_3_Type;
typedef uint32 Rdci_CTR_TYR_ID_4_Type;
typedef uint8  Rdci_DEBUG_DATA_Type;
typedef uint8  Rdci_FTAX_TYP_TYR_ID2_Type;
typedef uint8  Rdci_IDX_LCC_BAX_TYP_TYR_Type;
typedef uint8  Rdci_IDX_LCC_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_IDX_LCC_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_IDX_LCC_TYP_TYR_Type;
typedef uint8  Rdci_IDX_LCC_WITR_TYP_TYR_Type;
typedef uint8  Rdci_LOR_BAX_TYP_TYR_Type;
typedef uint8  Rdci_LOR_FTAX_TYP_TYR_Type;
typedef uint32 Rdci_MILE_KM_Type;
typedef uint8  Rdci_OL_AVLB_TYP_TYR_ID2_Type;
typedef uint8  Rdci_PM_ID2_Type;
typedef uint8  Rdci_QrCodeMountingStateId2_Type;
typedef uint8  Rdci_QrCodeMountingStateId3_Type;
typedef uint8  Rdci_QrCodeMountingStateId4_Type;
typedef uint8  Rdci_QrCodePositionId2_Type;
typedef uint8  Rdci_QrCodePositionId3_Type;
typedef uint8  Rdci_QrCodePositionId4_Type;
typedef uint8  Rdci_RAD_BAX_TYP_TYR_Type;
typedef uint8  Rdci_RAD_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_RAD_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_RAD_TYP_TYR_Type;
typedef uint8  Rdci_RAD_WITR_TYP_TYR_Type;
typedef uint8  Rdci_RELA_SIDE_BAX_TYP_TYR_Type;
typedef uint8  Rdci_RELA_SIDE_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_RELA_SIDE_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_RELA_SIDE_TYP_TYR_Type;
typedef uint8  Rdci_RELA_SIDE_WITR_TYP_TYR_Type;
typedef uint8  Rdci_SOTR_TYP_TYR_ID2_Type;
typedef uint8  Rdci_ST_TYR_OL_ID_Type;
typedef uint8  Rdci_TEMP_EX_Type;
typedef uint32 Rdci_T_SEC_COU_REL_Type;
typedef uint8  Rdci_WID_BAX_TYP_TYR_Type;
typedef uint8  Rdci_WID_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_WID_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_WID_TYP_TYR_Type;
typedef uint8  Rdci_WID_WITR_TYP_TYR_Type;
typedef uint8  Rdci_WITR_TYP_TYR_ID2_Type;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_3;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_5;
typedef uint16 Rte_DT_Rdci_UHRZEIT_DATUM_Type_6;
typedef uint8  ImpTypeValCRdciCorHoldOffTime;
typedef uint8  ImpTypeValCRdciDefaultLoadCond;
typedef uint8  ImpTypeValCRdciDefaultMenuSel;
typedef uint8  ImpTypeValCRdciDispReset;
typedef uint8  ImpTypeValCRdciEcoRcpEnable;
typedef uint8  ImpTypeValCRdciErfsEnable;
typedef uint8  ImpTypeValCRdciErfsPlacardSource;
typedef uint8  ImpTypeValCRdciFastDeflateEnable;
typedef uint8  ImpTypeValCRdciMaxThreshold;
typedef uint8  ImpTypeValCRdciNumPrewarnDetect;
typedef uint8  ImpTypeValCRdciPanneBefPos;
typedef uint8  ImpTypeValCRdciPrewarnEnable;
typedef uint8  ImpTypeValCRdciPrewarnIgnition;
typedef uint8  ImpTypeValCRdciResetPlausi;
typedef uint8  ImpTypeValCRdciRidEnable;
typedef uint8  ImpTypeValCRdciSensorForeignAkRdk;
typedef uint8  ImpTypeValCRdciSensorLocSync;
typedef uint8  ImpTypeValCRdciSpeedCcmEnable;
typedef uint8  ImpTypeValCRdciStatInit;
typedef uint8  ImpTypeValCRdciTPrewarnNc;
typedef uint8  ImpTypeValCRdciTpmsMarket;
typedef uint8  ImpTypeValCRdciTrefSeasonalAdjustment;
typedef uint8  ImpTypeValCRdciTyrIdFiltGw;
typedef uint8  ImpTypeValDcm_FunktionenReifendruckkontrolleReadDataType;
typedef uint8  ImpTypeValDcm_RdcInaktivStatusReadDataType;
typedef uint8  ImpTypeValDcm_RdcKalibrierungStatusReadDataType;
typedef uint8  ImpTypeValDcm_RdcKonfigurationReadDataType;
typedef uint8  ImpTypeValDcm_RdcPositionReadDataType;
typedef uint8  ImpTypeValDcm_RdcSensorHerstellerReadDataType;
typedef uint8  ImpTypeValDcm_RdcStatusReadDataType;
typedef uint8  ImpTypeValFrBusState;
typedef uint8  ImpTypeVal_C_Funktion_ReifenPannenerkennung_aktiv_e;
typedef uint8  Rdci_ACTVN_PM_Type;
typedef uint8  Rdci_AIP_ENG_DRV_Type;
typedef uint16 Rdci_AVL_P_TYR_FLH_Type;
typedef uint16 Rdci_AVL_P_TYR_FRH_Type;
typedef uint16 Rdci_AVL_P_TYR_RLH_Type;
typedef uint16 Rdci_AVL_P_TYR_RRH_Type;
typedef uint16 Rdci_AVL_TEMP_TYR_FLH_Type;
typedef uint16 Rdci_AVL_TEMP_TYR_FRH_Type;
typedef uint16 Rdci_AVL_TEMP_TYR_RLH_Type;
typedef uint16 Rdci_AVL_TEMP_TYR_RRH_Type;
typedef uint8  Rdci_CAC_BAX_TYP_TYR_Type;
typedef uint8  Rdci_CAC_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_CAC_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_CAC_TYP_TYR_Type;
typedef uint8  Rdci_CAC_WITR_TYP_TYR_Type;
typedef uint8  Rdci_CTR_FIL_ACTV_1_Type;
typedef uint8  Rdci_CTR_FIL_ACTV_2_Type;
typedef uint8  Rdci_CTR_FIL_ACTV_3_Type;
typedef uint8  Rdci_CTR_FIL_ACTV_4_Type;
typedef uint8  Rdci_CTR_SUPP_ID_1_Type;
typedef uint8  Rdci_CTR_SUPP_ID_2_Type;
typedef uint8  Rdci_CTR_SUPP_ID_3_Type;
typedef uint8  Rdci_CTR_SUPP_ID_4_Type;
typedef uint8  Rdci_ExtParkSupConfig_Type;
typedef uint16 Rdci_GNSSErrorAltitudeMeters_Type;
typedef uint16 Rdci_GNSSPositionAltitude_Type;
typedef uint8  Rdci_IDX_V_BAX_TYP_TYR_Type;
typedef uint8  Rdci_IDX_V_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_IDX_V_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_IDX_V_TYP_TYR_Type;
typedef uint8  Rdci_IDX_V_WITR_TYP_TYR_Type;
typedef uint8  Rdci_L_OL_TYP_TYR_Type;
typedef uint8  Rdci_LastReceivedAmbientPressure_Type;
typedef uint8  Rdci_MobilityLossThresholdValue_Type;
typedef uint8  Rdci_NotificationThresholdValueC_Type;
typedef uint8  Rdci_NotificationThresholdValueNc_Type;
typedef uint8  Rdci_OP_IDR_MSGC_Type;
typedef uint8  Rdci_OP_IDR_SLCTN_Type;
typedef uint8  Rdci_OP_SLCTN_TYR_AVLB_Type;
typedef uint8  Rdci_OP_TAR_P_LOCO_TPCT_Type;
typedef uint8  Rdci_OP_TPCT_Type;
typedef uint8  Rdci_OP_TYR_SEA_TPCT_Type;
typedef uint8  Rdci_PwfChange_Type;
typedef uint8  Rdci_QU_RDC_INIT_DISP_Type;
typedef uint64 Rdci_QrCodeDotNoId1_Type;
typedef uint64 Rdci_QrCodeDotNoId2_Type;
typedef uint64 Rdci_QrCodeDotNoId3_Type;
typedef uint64 Rdci_QrCodeDotNoId4_Type;
typedef uint16 Rdci_QrCodeDotProdDateId1_Type;
typedef uint16 Rdci_QrCodeDotProdDateId2_Type;
typedef uint16 Rdci_QrCodeDotProdDateId3_Type;
typedef uint16 Rdci_QrCodeDotProdDateId4_Type;
typedef uint8  Rdci_QrCodeInventoryNoId1_Type;
typedef uint8  Rdci_QrCodeInventoryNoId2_Type;
typedef uint8  Rdci_QrCodeInventoryNoId3_Type;
typedef uint8  Rdci_QrCodeInventoryNoId4_Type;
typedef uint8  Rdci_QrCodeMountingStateId1_Type;
typedef uint8  Rdci_QrCodePositionId1_Type;
typedef uint64 Rdci_QrCodeRubberSerialNoPartAId1_Type;
typedef uint64 Rdci_QrCodeRubberSerialNoPartAId2_Type;
typedef uint64 Rdci_QrCodeRubberSerialNoPartAId3_Type;
typedef uint64 Rdci_QrCodeRubberSerialNoPartAId4_Type;
typedef uint32 Rdci_QrCodeRubberSerialNoPartBId1_Type;
typedef uint32 Rdci_QrCodeRubberSerialNoPartBId2_Type;
typedef uint32 Rdci_QrCodeRubberSerialNoPartBId3_Type;
typedef uint32 Rdci_QrCodeRubberSerialNoPartBId4_Type;
typedef uint64 Rdci_QrCodeTireDimensionsId1_Type;
typedef uint64 Rdci_QrCodeTireDimensionsId2_Type;
typedef uint64 Rdci_QrCodeTireDimensionsId3_Type;
typedef uint64 Rdci_QrCodeTireDimensionsId4_Type;
typedef uint8  Rdci_QrCodeTireTypeId1_Type;
typedef uint8  Rdci_QrCodeTireTypeId2_Type;
typedef uint8  Rdci_QrCodeTireTypeId3_Type;
typedef uint8  Rdci_QrCodeTireTypeId4_Type;
typedef uint8  Rdci_RDCSystemReferenceTemp_Type;
typedef uint8  Rdci_RFL_BAX_TYP_TYR_Type;
typedef uint8  Rdci_RFL_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_RFL_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_RFL_TYP_TYR_Type;
typedef uint8  Rdci_RFL_WITR_TYP_TYR_Type;
typedef uint8  Rdci_RQ_OL_TPCT_Type;
typedef uint8  Rdci_RQ_PM_DT_Type;
typedef uint8  Rdci_RelRecommendedColdInflationPressureFrontAxle_Type;
typedef uint8  Rdci_RelRecommendedColdInflationPressureRearAxle_Type;
typedef uint8  Rdci_SEA_BAX_TYP_TYR_Type;
typedef uint8  Rdci_SEA_FTAX_TYP_TYR_Type;
typedef uint8  Rdci_SEA_SUTR_TYP_TYR_Type;
typedef uint8  Rdci_SEA_TYP_TYR_Type;
typedef uint8  Rdci_SEA_WITR_TYP_TYR_Type;
typedef uint8  Rdci_ST_ENERG_FZM_Type;
typedef uint8  Rdci_ST_IDR_MSGC_Type;
typedef uint8  Rdci_ST_ILK_ERRM_FZM_Type;
typedef uint8  Rdci_ST_MAN_SLCTN_Type;
typedef uint8  Rdci_ST_SLCTN_BAX_TYP_TYR_Type;
typedef uint8  Rdci_ST_SLCTN_SUTR_AVLB_Type;
typedef uint8  Rdci_ST_SLCTN_TYR_Type;
typedef uint8  Rdci_ST_SLCTN_WITR_AVLB_Type;
typedef uint8  Rdci_ST_TAR_P_LOCO_TPCT_Type;
typedef uint8  Rdci_ST_TYR_SEA_TPCT_Type;
typedef uint8  Rdci_StatusWheelTypeChangeDetection_Type;
typedef uint8  Rdci_StatusWheelTypeChangePosition_Type;
typedef uint16 Rdci_TAR_P_TYR_FLH_Type;
typedef uint16 Rdci_TAR_P_TYR_FRH_Type;
typedef uint16 Rdci_TAR_P_TYR_RLH_Type;
typedef uint16 Rdci_TAR_P_TYR_RRH_Type;
typedef uint8  Rdci_TireMileageInventoryNoId1_Type;
typedef uint8  Rdci_TireMileageInventoryNoId2_Type;
typedef uint8  Rdci_TireMileageInventoryNoId3_Type;
typedef uint8  Rdci_TireMileageInventoryNoId4_Type;
typedef uint64 Rdci_TireMileageLastAssemblyDateId1_Type;
typedef uint64 Rdci_TireMileageLastAssemblyDateId2_Type;
typedef uint64 Rdci_TireMileageLastAssemblyDateId3_Type;
typedef uint64 Rdci_TireMileageLastAssemblyDateId4_Type;
typedef uint32 Rdci_TireMileageLastAssemblyVehicleMileageId1_Type;
typedef uint32 Rdci_TireMileageLastAssemblyVehicleMileageId2_Type;
typedef uint32 Rdci_TireMileageLastAssemblyVehicleMileageId3_Type;
typedef uint32 Rdci_TireMileageLastAssemblyVehicleMileageId4_Type;
typedef uint64 Rdci_TireMileageLastDisassemblyDateId1_Type;
typedef uint64 Rdci_TireMileageLastDisassemblyDateId2_Type;
typedef uint64 Rdci_TireMileageLastDisassemblyDateId3_Type;
typedef uint64 Rdci_TireMileageLastDisassemblyDateId4_Type;
typedef uint32 Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type;
typedef uint32 Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type;
typedef uint32 Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type;
typedef uint32 Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type;
typedef uint8  Rdci_TireMileagePositionId1_Type;
typedef uint8  Rdci_TireMileagePositionId2_Type;
typedef uint8  Rdci_TireMileagePositionId3_Type;
typedef uint8  Rdci_TireMileagePositionId4_Type;
typedef uint32 Rdci_TireMileageTotalTireMileageOnVehicleId1_Type;
typedef uint32 Rdci_TireMileageTotalTireMileageOnVehicleId2_Type;
typedef uint32 Rdci_TireMileageTotalTireMileageOnVehicleId3_Type;
typedef uint32 Rdci_TireMileageTotalTireMileageOnVehicleId4_Type;
typedef uint8  Rdci_TolNoTempComp_Type;
typedef uint8  Rdci_TolTempComp_Type;
typedef uint16 Rdci_TpmsCalibrationActualTirePressureId1_Type;
typedef uint16 Rdci_TpmsCalibrationActualTirePressureId2_Type;
typedef uint16 Rdci_TpmsCalibrationActualTirePressureId3_Type;
typedef uint16 Rdci_TpmsCalibrationActualTirePressureId4_Type;
typedef uint8  Rdci_TpmsCalibrationActualTireTemperatureId1_Type;
typedef uint8  Rdci_TpmsCalibrationActualTireTemperatureId2_Type;
typedef uint8  Rdci_TpmsCalibrationActualTireTemperatureId3_Type;
typedef uint8  Rdci_TpmsCalibrationActualTireTemperatureId4_Type;
typedef uint16 Rdci_TpmsCalibrationAmbientPressure_Type;
typedef uint8  Rdci_TpmsCalibrationAmbientTemperature_Type;
typedef uint8  Rdci_TpmsCalibrationCalibrationType_Type;
typedef uint64 Rdci_TpmsCalibrationDate_Type;
typedef uint32 Rdci_TpmsCalibrationMileage_Type;
typedef uint8  Rdci_TpmsCalibrationNoOfCalibrations_Type;
typedef uint8  Rdci_TpmsCalibrationPlausibility_Type;
typedef uint8  Rdci_TpmsCalibrationPositionId1_Type;
typedef uint8  Rdci_TpmsCalibrationPositionId2_Type;
typedef uint8  Rdci_TpmsCalibrationPositionId3_Type;
typedef uint8  Rdci_TpmsCalibrationPositionId4_Type;
typedef uint64 Rdci_TpmsCalibrationTime_Type;
typedef uint16 Rdci_TpmsCalibrationTireTargetPressureId1_Type;
typedef uint16 Rdci_TpmsCalibrationTireTargetPressureId2_Type;
typedef uint16 Rdci_TpmsCalibrationTireTargetPressureId3_Type;
typedef uint16 Rdci_TpmsCalibrationTireTargetPressureId4_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerCarcass_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerCrossSection_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerDiameter_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerLoadIndex_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerMountedInFactory_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerMounted_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerPosition_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerRunflat_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerSeason_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerSpeedIndex_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup0_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup1_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup2_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup0_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup1_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup2_Type;
typedef uint8  Rdci_TpmsErfsActTireDimSummerWidth_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterCarcass_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterCrossSection_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterDiameter_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterLoadIndex_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterMountedInFactory_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterMounted_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterPosition_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterRunflat_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterSeason_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterSpeedIndex_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup0_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup1_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup2_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup0_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup1_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup2_Type;
typedef uint8  Rdci_TpmsErfsActTireDimWinterWidth_Type;
typedef uint8  Rdci_TpmsInternalLastBatteryStatusId1_Type;
typedef uint8  Rdci_TpmsInternalLastBatteryStatusId2_Type;
typedef uint8  Rdci_TpmsInternalLastBatteryStatusId3_Type;
typedef uint8  Rdci_TpmsInternalLastBatteryStatusId4_Type;
typedef uint8  Rdci_TpmsInternalLastPositionId1_Type;
typedef uint8  Rdci_TpmsInternalLastPositionId2_Type;
typedef uint8  Rdci_TpmsInternalLastPositionId3_Type;
typedef uint8  Rdci_TpmsInternalLastPositionId4_Type;
typedef uint16 Rdci_TpmsInternalLastPressureMbarId1_Type;
typedef uint16 Rdci_TpmsInternalLastPressureMbarId2_Type;
typedef uint16 Rdci_TpmsInternalLastPressureMbarId3_Type;
typedef uint16 Rdci_TpmsInternalLastPressureMbarId4_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionRssiId1_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionRssiId2_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionRssiId3_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionRssiId4_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionYieldId1_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionYieldId2_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionYieldId3_Type;
typedef uint8  Rdci_TpmsInternalLastReceptionYieldId4_Type;
typedef uint32 Rdci_TpmsInternalLastSensorSerNoId1_Type;
typedef uint32 Rdci_TpmsInternalLastSensorSerNoId2_Type;
typedef uint32 Rdci_TpmsInternalLastSensorSerNoId3_Type;
typedef uint32 Rdci_TpmsInternalLastSensorSerNoId4_Type;
typedef uint16 Rdci_TpmsInternalLastTargetPressureMbarId1_Type;
typedef uint16 Rdci_TpmsInternalLastTargetPressureMbarId2_Type;
typedef uint16 Rdci_TpmsInternalLastTargetPressureMbarId3_Type;
typedef uint16 Rdci_TpmsInternalLastTargetPressureMbarId4_Type;
typedef uint8  Rdci_TpmsInternalLastTemperatureDegCId1_Type;
typedef uint8  Rdci_TpmsInternalLastTemperatureDegCId2_Type;
typedef uint8  Rdci_TpmsInternalLastTemperatureDegCId3_Type;
typedef uint8  Rdci_TpmsInternalLastTemperatureDegCId4_Type;
typedef uint8  Rdci_UN_AIP_Type;
typedef uint8  Rdci_UN_MILE_Type;
typedef uint8  Rdci_UN_TEMP_Type;
typedef uint8  Rdci_WarningThresholdValueC_Type;
typedef uint8  Rdci_WarningThresholdValueNc_Type;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_0;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_1;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_2;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_4;
typedef uint8  Rte_DT_Rdci_UHRZEIT_DATUM_Type_7;
typedef uint8  ImpTypeArrayCRdciLearnLocateConfig[2];
typedef uint8  ImpTypeArrayCRdciTrefSeasAdjConfig[4];
typedef uint8  ImpTypeArrayDcm_RdcAnlernenLokalisierungLesenReadDataType[200];
typedef uint8  ImpTypeArrayDcm_RdcAussendruckReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcErfsEcoTabelleLesenReadDataType[163];
typedef uint8  ImpTypeArrayDcm_RdcErfsTsaDatenLesenReadDataType[104];
typedef uint8  ImpTypeArrayDcm_RdcHsInaktivereignisReadDataType[66];
typedef uint8  ImpTypeArrayDcm_RdcHsKalibrierereignisReadDataType[150];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignis1ReadDataType[58];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignis2ReadDataType[58];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignis3ReadDataType[58];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignisRuecknahmeReadDataType[51];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignisWeich1ReadDataType[51];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignisWeich2ReadDataType[51];
typedef uint8  ImpTypeArrayDcm_RdcHsWarnereignisWeich3ReadDataType[51];
typedef uint8  ImpTypeArrayDcm_RdcMessdatenblock1ReadDataType[24];
typedef uint8  ImpTypeArrayDcm_RdcMessdatenblock2ReadDataType[24];
typedef uint8  ImpTypeArrayDcm_RdcMessdatenblock3ReadDataType[24];
typedef uint8  ImpTypeArrayDcm_RdcMessdatenblock4ReadDataType[24];
typedef uint8  ImpTypeArrayDcm_RdcReifendruckHlReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcReifendruckHrReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcReifendruckVlReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcReifendruckVrReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcRidAktReifenLaufstreckeLesenReadDataType[100];
typedef uint8  ImpTypeArrayDcm_RdcRidAktReifenQrCodeLesenReadDataType[120];
typedef uint8  ImpTypeArrayDcm_RdcRidAlteReifenLaufstreckeLesenReadDataType[200];
typedef uint8  ImpTypeArrayDcm_RdcRidAlteReifenQrCodeLesenReadDataType[240];
typedef uint8  ImpTypeArrayDcm_RdcSolldruckHintenReadDataType[2];
typedef uint8  ImpTypeArrayDcm_RdcSolldruckVornReadDataType[2];
typedef uint8  ImpTypeArrayDcm_StatusRdcDeveloperDataLesenReadDataType[21];
typedef uint8  ImpTypeArrayDcm_StatusRdcErfsAktReifenEcoLesenReadDataType[34];
typedef uint8  ImpTypeArrayDcm_StatusRdcErfsAktReifenLesenReadDataType[30];
typedef uint8  ImpTypeArrayDcm_StatusRdcExtParkSupervisionLesenType[77];
typedef uint8  ImpTypeArrayDcm_StatusRdcLesenReadDataType[17];
typedef uint8  ImpTypeArrayDcm_StatusRdcVersionReadDataType[2];
typedef uint8  ImpTypeArrayDcm_StatusReLesenDruckcodierungReadDataType[72];
typedef uint8  ImpTypeArrayDcm_SteuernDigitalRdcWriteDataType[2];
typedef uint8  ImpTypeArrayDcm_SteuernRadelektronikVorgebenWriteDataType[5];
typedef uint8  ImpTypeArrayDcm_SteuernRdcDeveloperConfigWriteDataType[51];
typedef uint8  ImpTypeArrayDcm_SteuernRdcErfsDeveloperConfigWriteDataType[16];
typedef uint8  ImpTypeArrayDcm_SteuernRdcErfsEcoAktReifenPosVorgebenWriteDataType[9];
typedef uint8  ImpTypeArrayDcm_SteuernRdcErfsEcoNeueReifenVorgebenWriteDataType[9];
typedef uint8  ImpTypeArrayDcm_SteuernRdcErfsEcoReifentabelleVorgebenWriteDataType[162];
typedef uint8  ImpTypeArrayDcm_SteuernRdcErfsTsaDatenVorgebenWriteDataType[104];
typedef uint8  NvM_BlockDataType[1];
typedef uint8  Rte_DT_ImpTypeRecCRdciErfsReifenEco_0[160];

typedef struct{
   uint16 NO_CC_BYPA_00;
   uint8  ST_CC_BYPA_00;
   uint8  ST_IDC_CC_BYPA_00;
   uint8  TRANF_CC_BYPA_00;
}ImpTypeRecCcm_DISP_CC_BYPA_00;

typedef struct{
   uint16 ABS_EDGE_CNT_FL;
   uint8  ABS_SPIN_DIR_FL;
   uint8  ABS_QU_SIG_FL;
   uint16 ABS_EDGE_CNT_FR;
   uint8  ABS_SPIN_DIR_FR;
   uint8  ABS_QU_SIG_FR;
   uint16 ABS_EDGE_CNT_RL;
   uint8  ABS_SPIN_DIR_RL;
   uint8  ABS_QU_SIG_RL;
   uint16 ABS_EDGE_CNT_RR;
   uint8  ABS_SPIN_DIR_RR;
   uint8  ABS_QU_SIG_RR;
   uint32 ABS_SYNC_TSTMP_LO;
   uint32 ABS_SYNC_TSTMP_HI;
}ImpTypeRecCddAbsData;

typedef struct{
   uint16 RDC_MES_TSTMP;
   uint8  SUPP_ID;
   uint32 TYR_ID;
   uint8  PCKG_ID;
   uint8  RDC_DT_1;
   uint8  RDC_DT_2;
   uint8  RDC_DT_3;
   uint8  RDC_DT_4;
   uint8  RDC_DT_5;
   uint8  RDC_DT_6;
   uint8  RDC_DT_7;
   uint8  RDC_DT_8;
   uint8  ALIV_RDC_DT_PCK_1;
   uint8  ALIV_RDC_DT_PCK_2;
   uint32 RDC_SYNC_TSTMP_LO;
   uint32 RDC_SYNC_TSTMP_HI;
   uint8  DP_NO;
}ImpTypeRecCddRdcData;

typedef struct{
   uint8  CRC_CON_VEH;
   uint8  ALIV_CON_VEH;
   uint8  CTR_BS_PRTNT;
   uint32 CTR_FKTN_PRTNT;
   uint8  ST_CON_VEH;
   uint8  QU_ST_CON_VEH;
   uint8  CON_VEH_dummy_56_63;
}Rdci_CON_VEH_Type;

typedef struct{
   uint8  CRC_ST_TYR;
   uint8  ALIV_ST_TYR;
   uint8  ST_TYR_dummy_12_15;
   uint8  QU_FN_TYR_INFO;
   uint8  QU_TPL;
   uint8  QU_TFAI;
}Rdci_ST_TYR_Type;

typedef struct{
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_0 DISP_HR;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_1 DISP_MN;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_2 DISP_SEC;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_3 DISP_DATE_DAY;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_4 DISP_DATE_WDAY;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_5 DISP_DATE_MON;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_6 DISP_DATE_YR;
   Rte_DT_Rdci_UHRZEIT_DATUM_Type_7 ST_DISP_CTI_DATE;
}Rdci_UHRZEIT_DATUM_Type;

typedef struct{
   uint8  CRC_V_VEH;
   uint8  ALIV_V_VEH;
   uint8  V_VEH_dummy_12_15;
   uint16 V_VEH_COG;
   uint8  QU_V_VEH_COG;
   uint8  V_VEH_dummy_36_39;
}Rdci_V_VEH_Type;

typedef struct{
   uint8  CRC_WMOM_DRV_4;
   uint8  ALIV_WMOM_DRV_4;
   uint8  WMOM_DRV_4_dummy_12_15;
   uint8  ST_DRVDIR_DVCH;
   uint16 WMOM_DRV_4_dummy_20_39;
   uint8  ST_PENG_PT;
   uint8  WMOM_DRV_4_dummy_44_47;
}Rdci_WMOM_DRV_4_Type;

typedef uint32 StbMB_TickType;
typedef uint8  ImpTypeRefDcm_NegativeResponseCodeType;
typedef uint8  ImpTypeRefDcm_OpStatusType;
typedef uint8  ImpTypeRefDem_EventStatusType;
typedef uint8  ImpTypeRefDem_InitMonitorReasonType;
typedef uint8  ImpTypeRefDem_UdsStatusByteType;
typedef uint8  NvM_RequestResultType;
typedef uint8  NvM_ServiceIdType;
typedef uint8  StbMB_SyncStatusType;

typedef struct{
   Rte_DT_ImpTypeRecCRdciErfsReifenEco_0 DeData;
   uint16                                DeCrc;
}ImpTypeRecCRdciErfsReifenEco;

typedef struct{
   uint32         systemTicks;
   uint16         systemTicksHi;
   uint32         tickDuration;
   StbMB_TickType ticks;
}StbMB_SystemTimeType;

#ifndef RTE_SUPPRESS_UNUSED_DATATYPES
typedef       void* dtRef_VOID;
typedef const void* dtRef_const_VOID;
#endif

typedef struct{uint16 Chksum; uint16 Version; uint8 Data[200];} Rte_PimType_CtApHufTpmsSWC_NvmRdciCommonBlockType;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[450];} Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock1Type;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[350];} Rte_PimType_CtApHufTpmsSWC_NvmRdciDiagBlock2Type;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[110];} Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsBlockType;
typedef struct{uint16 Version; uint8 Data[10];} Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsEcoBlockType;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[104];} Rte_PimType_CtApHufTpmsSWC_NvmRdciErfsTsaBlockType;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[350];} Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock1Type;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[350];} Rte_PimType_CtApHufTpmsSWC_NvmRdciRidQrBlock2Type;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[240];} Rte_PimType_CtApHufTpmsSWC_NvmRdciWarnStatusBlockType;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[120];} Rte_PimType_CtApHufTpmsSWC_NvmRdciZoHistoryBlockType;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[450];} Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock1Type;
typedef struct{uint16 Chksum; uint16 Version; uint8 Data[450];} Rte_PimType_CtApHufTpmsSWC_NvmRdciZomBlock2Type;

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
#endif
