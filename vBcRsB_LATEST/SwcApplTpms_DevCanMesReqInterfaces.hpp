#pragma once
/******************************************************************************/
/* File   : SwcApplTpms_DevCanMesReqInterfaces.hpp                            */
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
#include "Tpms_Rte_Data_Type.hpp"

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern uint8 DCM_InvIf_AbsGetResetCntValue(void);
extern uint8 DCM_InvIf_GearReverseGetCntValue(void);
extern uint8 DCM_InvIf_AutoLocGetTimeoutCntValue(void);
extern void DCM_InvIf_HistoryIDReadValue(uint8 u8_Possition, uint8 *u8_IDValue);
extern void DCM_InvIf_HistoryWPReadValue(uint8 u8_Possition, uint8 *u8_WPValue);
extern uint8 DCM_InvIf_RecepMissedGetCntValue(uint8 u8_HistoryIDValue);
extern uint8 DCM_InvIf_NoiseLevelGetValue(void);
extern uint8 DCM_InvIf_PressRefCurrIDGetValue(void);
extern boolean DCM_InvIf_RfJammerGetStatus(void);
extern uint8 DCM_InvIf_StopEventsGetCntValue(void);
extern uint16 DCM_InvIf_TPMSStateGetStatus(void);
extern uint8 DCM_InvIf_TempWarnGetStatus(void);
extern uint8 DCM_InvIf_VehicleStatusGetValue(void);
extern void DCM_InvIf_WarnVectReadHistoryStatus(uint8 u8_Possition, uint8 *u8_WarningValue);
extern void DCM_InvIf_ZomWuIDGetFromMemory(uint8 u8_ZomPossition, uint8 *u8_IDValue);
extern uint8 DCM_InvIf_ZomStatusGetFromMemory(uint8 u8_ZomPossition);
extern uint8 DCM_InvIf_ZomTelCntGetFromMemory(uint8 u8_ZomPossition);
extern uint8 DCM_InvIf_VehDirectionGetValue(void);
extern uint8 DCM_InvIf_WheelPosReceptionCounter(uint8 ucRecWheelPos);
extern uint8 DCM_InvIf_AbsCorrGetCntValueFL(uint8 u8_IDPossition);
extern uint8 DCM_InvIf_AbsCorrGetCntValueFR(uint8 u8_IDPossition);
extern uint8 DCM_InvIf_AbsCorrGetCntValueRL(uint8 u8_IDPossition);
extern uint8 DCM_InvIf_AbsCorrGetCntValueRR(uint8 u8_IDPossition);
extern uint8 DCM_InvIf_DebugAllocType(void);
extern uint8 DCM_InvIf_AbsLinAngle_FL_GetHistoryValue(void);
extern uint8 DCM_InvIf_AbsLinAngle_FR_GetHistoryValue(void);
extern uint8 DCM_InvIf_AbsLinAngle_RL_GetHistoryValue(void);
extern uint8 DCM_InvIf_AbsLinAngle_RR_GetHistoryValue(void);
extern uint8 DCM_InvIf_AbsLinGetCntValueFL(void);
extern uint8 DCM_InvIf_AbsLinGetCntValueFR(void);
extern uint8 DCM_InvIf_AbsLinGetCntValueRL(void);
extern uint8 DCM_InvIf_AbsLinGetCntValueRR(void);
extern uint8 DCM_InvIf_RawRSSIGetValue(void);
extern uint8 DCM_InvIf_RecEventGetCntValue(void);
extern uint8 DCM_InvIf_TelTypeCurrIDGetValue(void);
extern uint8 DCM_InvIf_AllReceivedTelegGetValue(void);
extern void DCM_InvIf_RFTimeStampGetValue(uint8 *u8_TimeStampValue);
extern uint8 DCM_InvIf_WheelPosCurrIDGetValue(void);
extern uint8 DCM_InvIf_ZomPosCurrIDGetValue(void);
extern uint8 DCM_InvIf_PressAmbientGetValue(void);
extern uint16 DCM_InvIf_SpeedVehicGetValue(void);
extern uint8 DCM_InvIf_TempAmbientGetValue(void);
extern void DCM_InvIf_LastRxIDGetValue(uint8 *u8_LastIdReceived);
extern void DCM_InvIf_RxStatusFieldGetValue(uint8 *u8_StatusFieldValue);
extern void DCM_InvIf_RawRfTelGetValue(uint8 u8_StartPosition, uint8 u8_NumberOfBytesToCopy, uint8 u8_RxTelegBytesValues[]);
extern uint8 DCM_InvIf_PressLastRxIDGetValue(void);
extern sint8 DCM_InvIf_TempLastRxIDGetValue(void);
extern uint8 DCM_InvIf_AxImbWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_DHWWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_EuFWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_FTWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_HardTDRWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_HiPWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_LowPWarnSetThresholdGetValue(void);
extern uint8 DCM_InvIf_PminDRWarnSetThresholdGetValue(void);

#ifdef DEBUG_AUTOLOCATION
extern void DCM_InvIf_ulDebugRfTimeStampGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ulAbsTimeStampPreviousGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ulAbsTimeStampNextGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ushMVdNfromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue);
extern void DCM_InvIf_ushMVdN2fromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue);
extern uint8 DCM_InvIf_ucABSReffromZOM(uint8 u8ZOMSlot, uint8 u8Position);
extern uint8 DCM_InvIf_ucAlgoTelEvtCntfromZOM(uint8 u8ZOMSlot);
extern uint8 DCM_InvIf_GetNumberOfE7withInvalidTs(void);
extern uint8 DCM_InvIf_GetNumberOfE7withOutdatedTs(void);
extern void DCM_InvIf_ulAbsTimeStampGetNewestValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ulAbsTimeStampGetOldestValue(uint8 *u8_DebugTimeStampValue);
#endif

#ifdef NVM_DEBUG
extern uint8 DCM_InvIf_NvmReadResult(void);
extern uint8 DCM_InvIf_NvmWriteResult(void);
extern void DCM_InvIf_NvmBlockConsistence(uint8 *u8_NvMBuffer);
extern uint8 DCM_InvIf_DebugABSTicksFront(void);
extern uint8 DCM_InvIf_DebugABSTicksRear(void);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

