

#ifndef _RTE_STUB_OUTPUT_H
#define _RTE_STUB_OUTPUT_H

#include "Rte_Type.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void RTE_Stub_CyclicOutputFunction(void);

extern void GetRDCiOutputDataTAR_P_TYR_FLH( Rdci_TAR_P_TYR_FLH_Type *ptOutputData);
extern void GetRDCiOutputDataTAR_P_TYR_FRH( Rdci_TAR_P_TYR_FRH_Type *ptOutputData);
extern void GetRDCiOutputDataTAR_P_TYR_RLH( Rdci_TAR_P_TYR_RLH_Type *ptOutputData);
extern void GetRDCiOutputDataTAR_P_TYR_RRH( Rdci_TAR_P_TYR_RRH_Type *ptOutputData);

extern void GetRDCiOutputDataAVL_T_TYR_FLH( Rdci_AVL_TEMP_TYR_FLH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_T_TYR_FRH( Rdci_AVL_TEMP_TYR_FRH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_T_TYR_RLH( Rdci_AVL_TEMP_TYR_RLH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_T_TYR_RRH( Rdci_AVL_TEMP_TYR_RRH_Type *ptOutputData);

extern void GetRDCiOutputDataAVL_P_TYR_FLH( Rdci_AVL_P_TYR_FLH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_P_TYR_FRH( Rdci_AVL_P_TYR_FRH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_P_TYR_RLH( Rdci_AVL_P_TYR_RLH_Type *ptOutputData);
extern void GetRDCiOutputDataAVL_P_TYR_RRH( Rdci_AVL_P_TYR_RRH_Type *ptOutputData);

extern void GetRDCiOutputDataST_TYR( Rdci_ST_TYR_Type *ptOutputData);

extern void GetRDCiOutputDataLOL_TYP_TYR( Rdci_L_OL_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataQU_RDC_INIT_DISP( Rdci_QU_RDC_INIT_DISP_Type *ptOutputData);
extern void GetRDCiOutputDataST_SLCTN_SUTR_AVLB( Rdci_ST_SLCTN_SUTR_AVLB_Type *ptOutputData);
extern void GetRDCiOutputDataST_SLCTN_WITR_AVLB( Rdci_ST_SLCTN_WITR_AVLB_Type *ptOutputData);
extern void GetRDCiOutputDataST_SLCTN_TYR( Rdci_ST_SLCTN_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataST_TAR_P_LOCO_TPCT( Rdci_ST_TAR_P_LOCO_TPCT_Type *ptOutputData);
extern void GetRDCiOutputDataST_TYR_SEA_TPCT( Rdci_ST_TYR_SEA_TPCT_Type *ptOutputData);

extern void GetRDCiOutputDataOP_IDR_MSGC( Rdci_OP_IDR_MSGC_Type *ptOutputData);

extern void GetRDCiOutputDataST_MAN_SLCTN( Rdci_ST_MAN_SLCTN_Type *ptOutputData);

extern void GetRDCiOutputDataCAC_SUTR( Rdci_CAC_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_LCC_SUTR( Rdci_IDX_LCC_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_V_SUTR( Rdci_IDX_V_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRAD_SUTR( Rdci_RAD_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRELA_SIDE_SUTR( Rdci_RELA_SIDE_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRFL_SUTR( Rdci_RFL_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataSEA_SUTR( Rdci_SEA_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataWID_SUTR( Rdci_WID_SUTR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataCAC_WITR( Rdci_CAC_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_LCC_WITR( Rdci_IDX_LCC_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_V_WITR( Rdci_IDX_V_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRAD_WITR( Rdci_RAD_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRELA_SIDE_WITR( Rdci_RELA_SIDE_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRFL_WITR( Rdci_RFL_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataSEA_WITR( Rdci_SEA_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataWID_WITR( Rdci_WID_WITR_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataCAC_BAX( Rdci_CAC_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_LCC_BAX( Rdci_IDX_LCC_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_V_BAX( Rdci_IDX_V_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRAD_BAX( Rdci_RAD_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRELA_SIDE_BAX( Rdci_RELA_SIDE_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRFL_BAX( Rdci_RFL_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataSEA_BAX( Rdci_SEA_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataWID_BAX( Rdci_WID_BAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataST_SLCTN_BAX_TYP_TYR( Rdci_ST_SLCTN_BAX_TYP_TYR_Type  *ptOutputData);
extern void GetRDCiOutputDataCAC_FTAX( Rdci_CAC_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_LCC_FTAX( Rdci_IDX_LCC_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_V_FTAX( Rdci_IDX_V_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRAD_FTAX( Rdci_RAD_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRELA_SIDE_FTAX( Rdci_RELA_SIDE_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRFL_FTAX( Rdci_RFL_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataSEA_FTAX( Rdci_SEA_FTAX_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataWID_FTAX( Rdci_WID_FTAX_TYP_TYR_Type *ptOutputData);

extern void GetRDCiOutputDataCAC_TYTR( Rdci_CAC_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_LCC_TYTR( Rdci_IDX_LCC_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataIDX_V_TYTR( Rdci_IDX_V_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRAD_TYTR( Rdci_RAD_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRELA_SIDE_TYTR( Rdci_RELA_SIDE_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataRFL_TYTR( Rdci_RFL_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataSEA_TYTR( Rdci_SEA_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataWID_TYTR( Rdci_WID_TYP_TYR_Type *ptOutputData);
extern void GetRDCiOutputDataOL_ID_TYTR( Rdci_ST_TYR_OL_ID_Type *ptOutputData);

extern void GetRDCiOutputDataStatusWheelTypeChangeDetection(Rdci_StatusWheelTypeChangeDetection_Type *ptOutputData);
extern void GetRDCiOutputDataStatusWheelTypeChangePosition(Rdci_StatusWheelTypeChangePosition_Type *ptOutputData);

extern void GetRDCiOutputDataLastReceivedAmbientPressure( Rdci_LastReceivedAmbientPressure_Type *ptOutputData);
extern void GetRDCiOutputDataMobilityLossThresholdValue( Rdci_MobilityLossThresholdValue_Type *ptOutputData);
extern void GetRDCiOutputDataNotificationThresholdValueC( Rdci_NotificationThresholdValueC_Type *ptOutputData);
extern void GetRDCiOutputDataNotificationThresholdValueNc( Rdci_NotificationThresholdValueNc_Type *ptOutputData);
extern void GetRDCiOutputDataRDCSystemReferenceTemp( Rdci_RDCSystemReferenceTemp_Type *ptOutputData);
extern void GetRDCiOutputDataPwfChange( Rdci_PwfChange_Type *ptOutputData);
extern void GetRDCiOutputDataRelRecommendedColdInflationPressureFrontAxle( Rdci_RelRecommendedColdInflationPressureFrontAxle_Type *ptOutputData);
extern void GetRDCiOutputDataRelRecommendedColdInflationPressureRearAxle( Rdci_RelRecommendedColdInflationPressureRearAxle_Type *ptOutputData);
extern void GetRDCiOutputDataTolNoTempComp( Rdci_TolNoTempComp_Type *ptOutputData);
extern void GetRDCiOutputDataTolTempComp( Rdci_TolTempComp_Type *ptOutputData);
extern void GetRDCiOutputDataWarningThresholdValueC( Rdci_WarningThresholdValueC_Type *ptOutputData);
extern void GetRDCiOutputDataWarningThresholdValueNc( Rdci_WarningThresholdValueNc_Type *ptOutputData);
extern void GetRDCiOutputDataExtParkSupConfig( Rdci_ExtParkSupConfig_Type *ptOutputData);

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Send_ST_TYR( P2CONST(Rdci_ST_TYR_Type, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA));

#ifdef __cplusplus
}
#endif

#endif
