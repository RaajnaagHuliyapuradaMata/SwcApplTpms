#ifndef _jump_table_H
#define _jump_table_H

#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************/
/* File   : JumpTable.h                                                       */
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
/* All rights reserved. Copyright ? 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Rte_CtApHufTpmsSWC.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
#if defined( WIN32) || defined( QAC_MISRA_CHECK)
typedef const struct Rte_CDS_CtApHufTpmsSWC* CDS_InstanceHandle;
#else
typedef const        Rte_CDS_CtApHufTpmsSWC* CDS_InstanceHandle;
#endif

typedef struct{
  	void           (*const RDCi_RCyclicRDCiTask_001                                                  )(CDS_InstanceHandle);
  	void           (*const RDCi_RInitRDCiStartup_002                                                 )(CDS_InstanceHandle);
  	void           (*const RDCi_RExitRDCiBye_003                                                     )(CDS_InstanceHandle);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead_004   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData_005             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead_006      )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData_007                )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcAussendruck_ConditionCheckRead_008                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcAussendruck_ReadData_009                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead_010                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcInaktivStatus_ReadData_011                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead_012            )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcKalibrierungStatus_ReadData_013                      )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead_014                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcKonfiguration_ReadData_015                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcPosition_ConditionCheckRead_016                      )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcPosition_ReadData_017                                )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead_018      )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData_019                )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead_020                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckHl_ReadData_021                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead_022                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckHr_ReadData_023                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead_024                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckVl_ReadData_025                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead_026                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifendruckVr_ReadData_027                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead_028            )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturHl_ReadData_029                      )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead_030            )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturHr_ReadData_031                      )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead_032            )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturVl_ReadData_033                      )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead_034            )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcReifentemperaturVr_ReadData_035                      )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead_036              )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSensorHersteller_ReadData_037                        )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead_038               )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSolldruckHinten_ReadData_039                         )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead_040                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcSolldruckVorn_ReadData_041                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcStatus_ConditionCheckRead_042                        )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmDiagRdcStatus_ReadData_043                                  )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead_044        )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData_045                  )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead_046               )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcErfsEcoTabelleLesen_ReadData_047                         )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead_048                 )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsInaktivereignis_ReadData_049                           )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead_050               )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsKalibrierereignis_ReadData_051                         )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead_052                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis1_ReadData_053                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead_054                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis2_ReadData_055                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead_056                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignis3_ReadData_057                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead_058          )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData_059                    )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead_060              )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich1_ReadData_061                        )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead_062              )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich2_ReadData_063                        )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead_064              )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcHsWarnereignisWeich3_ReadData_065                        )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock1_ConditionCheckRead_066                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock1_ReadData_067                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock2_ConditionCheckRead_068                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock2_ReadData_069                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock3_ConditionCheckRead_070                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock3_ReadData_071                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock4_ConditionCheckRead_072                   )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcMessdatenblock4_ReadData_073                             )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead_074      )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData_075                )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead_076           )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData_077                     )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead_078     )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData_079               )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead_080          )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData_081                    )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead_082          )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcDeveloperDataLesen_ReadData_083                    )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead_084       )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData_085                 )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead_086          )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData_087                    )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsTsaDatenLesen_ConditionCheckRead_088           )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcErfsTsaDatenLesen_ReadData_089                     )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcLesen_ConditionCheckRead_090                       )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcLesen_ReadData_091                                 )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcVersion_ConditionCheckRead_092                     )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcVersion_ReadData_093                               )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead_094          )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusReLesenDruckcodierung_ReadData_095                    )(CDS_InstanceHandle, uint8* Data);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernDigitalRdc_WriteData_096                             )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRadelektronikVorgeben_WriteData_097                  )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcDeveloperConfig_WriteData_098                     )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData_099                 )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData_100         )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData_101           )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_OpStatusType OpStatus, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData_102        )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_OpStatusType OpStatus, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmSteuernRdcErfsTsaDatenVorgeben_WriteData_103                )(CDS_InstanceHandle, const uint8* Data, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent_104         )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent_105            )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent_106               )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent_107               )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciAusfall_InitMonitorForEvent_108                    )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent_109         )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent_110             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent_111                )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent_112                  )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent_113              )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent_114              )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent_115               )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent_116     )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent_117     )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent_118 )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent_119      )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent_120               )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent_121          )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent_122              )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciPartialSystemAvailability_InitMonitorForEvent_123  )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent_124            )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent_125          )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent_126          )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent_127         )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent_128         )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent_129     )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciSystemNotAvailable_InitMonitorForEvent_130         )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent_131        )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent_132       )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent_133          )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent_134           )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent_135             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent_136           )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent_137             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent_138                )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent_139             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent_140                 )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent_141                 )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent_142                 )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent_143                 )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent_144       )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent_145             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent_146             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent_147             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent_148             )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent_149                   )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent_150                   )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent_151                   )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	Std_ReturnType (*const RDCi_ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent_152                   )(CDS_InstanceHandle, ImpTypeRefDem_InitMonitorReasonType);
  	void           (*const RDCi_ROpInvNvmRdciCommonBlock_NvMNotifyJobFinished_JobFinished_153        )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciDiagBlock1_NvMNotifyJobFinished_JobFinished_154         )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciDiagBlock2_NvMNotifyJobFinished_JobFinished_155         )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciErfsBlock_NvMNotifyJobFinished_JobFinished_156          )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciErfsEcoBlock_NvMNotifyJobFinished_JobFinished_157       )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciErfsTsaBlock_NvMNotifyJobFinished_JobFinished_158       )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciRidQrBlock1_NvMNotifyJobFinished_JobFinished_159        )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciRidQrBlock2_NvMNotifyJobFinished_JobFinished_160        )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciWarnStatusBlock_NvMNotifyJobFinished_JobFinished_161    )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciZoHistoryBlock_NvMNotifyJobFinished_JobFinished_162     )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciZomBlock1_NvMNotifyJobFinished_JobFinished_163          )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciZomBlock2_NvMNotifyJobFinished_JobFinished_164          )(CDS_InstanceHandle, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
  	void           (*const RDCi_ROpInvNvmRdciCommonBlock_NvMNotifyInitBlock_InitBlock_165            )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciDiagBlock1_NvMNotifyInitBlock_InitBlock_166             )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciDiagBlock2_NvMNotifyInitBlock_InitBlock_167             )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciErfsBlock_NvMNotifyInitBlock_InitBlock_168              )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciErfsEcoBlock_NvMNotifyInitBlock_InitBlock_169           )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciErfsTsaBlock_NvMNotifyInitBlock_InitBlock_170           )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciRidQrBlock1_NvMNotifyInitBlock_InitBlock_171            )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciRidQrBlock2_NvMNotifyInitBlock_InitBlock_172            )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciWarnStatusBlock_NvMNotifyInitBlock_InitBlock_173        )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciZoHistoryBlock_NvMNotifyInitBlock_InitBlock_174         )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciZomBlock1_NvMNotifyInitBlock_InitBlock_175              )(CDS_InstanceHandle);
  	void           (*const RDCi_ROpInvNvmRdciZomBlock2_NvMNotifyInitBlock_InitBlock_176              )(CDS_InstanceHandle);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead_177     )(CDS_InstanceHandle, ImpTypeRefDcm_NegativeResponseCodeType* ErrorCode);
  	Std_ReturnType (*const RDCi_ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData_178               )(CDS_InstanceHandle, uint8* Data);
}RDCi_FunctiontableType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern const RDCi_FunctiontableType* const RDCi_FunctiontablePtr;

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
