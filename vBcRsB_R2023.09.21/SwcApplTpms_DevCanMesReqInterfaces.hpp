

#ifndef Huf_DevCanMesReqInterfaces_H
#define Huf_DevCanMesReqInterfaces_H

#include "Tpms_Rte_Data_Type.hpp"

// system functions
extern uint8 DCM_InvIf_AbsGetResetCntValue(void);              // ECU_C_ABS_ResetCounter        Huf_DevCanMessages.c
extern uint8 DCM_InvIf_GearReverseGetCntValue(void);           // ECU_C_ReverseGr               state_fzz.c
extern uint8 DCM_InvIf_AutoLocGetTimeoutCntValue(void);        // ECU_C_ZOM_Tio                 Walloc.c
extern void DCM_InvIf_HistoryIDReadValue(uint8 u8_Possition, uint8 *u8_IDValue);                // ECU_Hist_ID_x            Walloc.c
extern void DCM_InvIf_HistoryWPReadValue(uint8 u8_Possition, uint8 *u8_WPValue);                // ECU_Hist_WP_x            Walloc.c
extern uint8 DCM_InvIf_RecepMissedGetCntValue(uint8 u8_HistoryIDValue);                         // ECU_Missed_Cnt_x         statistics.c
extern uint8 DCM_InvIf_NoiseLevelGetValue(void);               // ECU_Noiselevel                Huf_Vehstate.c
extern uint8 DCM_InvIf_PressRefCurrIDGetValue(void);           // ECU_P_Ref_Curr_ID             Huf_DevCanMessages.c
extern boolean DCM_InvIf_RfJammerGetStatus(void);              // ECU_RF_Interfer_Stat          Huf_DevCanMessages.c
extern uint8 DCM_InvIf_StopEventsGetCntValue(void);            // ECU_Stop_Cntr                 Huf_Vehstate.c
extern uint16 DCM_InvIf_TPMSStateGetStatus(void);              // ECU_Syst_Stat                 state_bz.c
extern uint8 DCM_InvIf_TempWarnGetStatus(void);                // ECU_T_Warn_Stat               Huf_DevCanMessages.c
extern uint8 DCM_InvIf_VehicleStatusGetValue(void);            // ECU_Vehicle_Status            state_fzz.c
extern void DCM_InvIf_WarnVectReadHistoryStatus(uint8 u8_Possition, uint8 *u8_WarningValue);    // ECU_Warn_VectX           TSSMsg.c
extern void DCM_InvIf_ZomWuIDGetFromMemory(uint8 u8_ZomPossition, uint8 *u8_IDValue);           // ECU_ZOM_x_WU_ID          Walloc.c
extern uint8 DCM_InvIf_ZomStatusGetFromMemory(uint8 u8_ZomPossition);                           // ECU_ZOM_x_Stat           Walloc.c
extern uint8 DCM_InvIf_ZomTelCntGetFromMemory(uint8 u8_ZomPossition);                           // ECU_ZOM_x_TelCnt         Walloc.c
extern uint8 DCM_InvIf_VehDirectionGetValue(void);                                              // ECU_VehDirection         Huf_Vehstate.c

// environment functions
//extern uint8 DCM_InvIf_AbsTicsOverflow_FL_GetCntValue(void);    // ECU_C_Oflow_FL                abs_lin.c
//extern uint8 DCM_InvIf_AbsTicsOverflow_FR_GetCntValue(void);    // ECU_C_Oflow_FR                abs_lin.c
//extern uint8 DCM_InvIf_AbsTicsOverflow_RL_GetCntValue(void);    // ECU_C_Oflow_RL                abs_lin.c
//extern uint8 DCM_InvIf_AbsTicsOverflow_RR_GetCntValue(void);    // ECU_C_Oflow_RR                abs_lin.c
extern uint8 DCM_InvIf_WheelPosReceptionCounter(uint8 ucRecWheelPos);

extern uint8 DCM_InvIf_AbsCorrGetCntValueFL(uint8 u8_IDPossition);             // ECU_C_Sum_Corr_FL                         FPA.c
extern uint8 DCM_InvIf_AbsCorrGetCntValueFR(uint8 u8_IDPossition);             // ECU_C_Sum_Corr_FR                         FPA.c
extern uint8 DCM_InvIf_AbsCorrGetCntValueRL(uint8 u8_IDPossition);             // ECU_C_Sum_Corr_RL                         FPA.c
extern uint8 DCM_InvIf_AbsCorrGetCntValueRR(uint8 u8_IDPossition);             // ECU_C_Sum_Corr_RR                         FPA.c
extern uint8 DCM_InvIf_DebugAllocType(void);                   // ECU_Alloc_Type              FPA.c

extern uint8 DCM_InvIf_AbsLinAngle_FL_GetHistoryValue(void);     // ECU_Hist_ABS_FL               abs_lin.c
extern uint8 DCM_InvIf_AbsLinAngle_FR_GetHistoryValue(void);     // ECU_Hist_ABS_FR               abs_lin.c
extern uint8 DCM_InvIf_AbsLinAngle_RL_GetHistoryValue(void);     // ECU_Hist_ABS_RL               abs_lin.c
extern uint8 DCM_InvIf_AbsLinAngle_RR_GetHistoryValue(void);     // ECU_Hist_ABS_RR               abs_lin.c

extern uint8 DCM_InvIf_AbsLinGetCntValueFL(void);              // ECU_LinABS_FL                 abs_lin.c
extern uint8 DCM_InvIf_AbsLinGetCntValueFR(void);              // ECU_LinABS_FR                 abs_lin.c
extern uint8 DCM_InvIf_AbsLinGetCntValueRL(void);              // ECU_LinABS_RL                 abs_lin.c
extern uint8 DCM_InvIf_AbsLinGetCntValueRR(void);              // ECU_LinABS_RR                 abs_lin.c

extern uint8 DCM_InvIf_RawRSSIGetValue(void);                  // ECU_Receiver_Baselevel        procdat.c
extern uint8 DCM_InvIf_RecEventGetCntValue(void);              // ECU_RecEvent                  procdat.c
extern uint8 DCM_InvIf_TelTypeCurrIDGetValue(void);            // ECU_TelType_Curr_ID           procdat.c
extern uint8 DCM_InvIf_AllReceivedTelegGetValue(void);         // ECU_AllRecEvent               procdat.c

extern void DCM_InvIf_RFTimeStampGetValue(uint8 *u8_TimeStampValue);                            // ECU_TimeStamp            procdat.c
extern uint8 DCM_InvIf_WheelPosCurrIDGetValue(void);           // ECU_Wheel_Pos_Curr_ID         statemanager.c
extern uint8 DCM_InvIf_ZomPosCurrIDGetValue(void);             // ECU_ZomPos_Curr_ID            Walloc.c
extern uint8 DCM_InvIf_PressAmbientGetValue(void);             // VEH_P_ambient                 Huf_Vehstate.c
extern uint16 DCM_InvIf_SpeedVehicGetValue(void);              // VEH_Speed                     Huf_Vehstate.c
extern uint8 DCM_InvIf_TempAmbientGetValue(void);              // VEH_T_Ambient                 state_fzz.c

extern void DCM_InvIf_LastRxIDGetValue(uint8 *u8_LastIdReceived);              // WU_ID                         procdat.c

extern void DCM_InvIf_RxStatusFieldGetValue(uint8 *u8_StatusFieldValue);       // WU_Status_fields              procdat.c
extern void DCM_InvIf_RawRfTelGetValue(uint8 u8_StartPosition, uint8 u8_NumberOfBytesToCopy, uint8 u8_RxTelegBytesValues[]);   // WU_Raw_ByteX          procdat.c

extern uint8 DCM_InvIf_PressLastRxIDGetValue(void);            // WU_Tire_P                     procdat.c
extern sint8 DCM_InvIf_TempLastRxIDGetValue(void);             // WU_Tire_T                     procdat.c

extern uint8 DCM_InvIf_AxImbWarnSetThresholdGetValue(void);         // ECU_tCmp_AxImb                 USWarn.c
extern uint8 DCM_InvIf_DHWWarnSetThresholdGetValue(void);           // ECU_tCmp_DHW                   USWarn.c
extern uint8 DCM_InvIf_EuFWarnSetThresholdGetValue(void);           // ECU_tCmp_EuF                   USWarn.c
extern uint8 DCM_InvIf_FTWarnSetThresholdGetValue(void);            // ECU_tCmp_FT                    USWarn.c
extern uint8 DCM_InvIf_HardTDRWarnSetThresholdGetValue(void);       // ECU_tCmp_HardTDR               USWarn.c
extern uint8 DCM_InvIf_HiPWarnSetThresholdGetValue(void);           // ECU_tCmp_HiP                   USWarn.c
extern uint8 DCM_InvIf_LowPWarnSetThresholdGetValue(void);          // ECU_tCmp_LowP                  USWarn.c
extern uint8 DCM_InvIf_PminDRWarnSetThresholdGetValue(void);        // ECU_tCmp_PminDR                USWarn.c

#ifdef DEBUG_AUTOLOCATION

extern void DCM_InvIf_ulDebugRfTimeStampGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ulAbsTimeStampPreviousGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ulAbsTimeStampNextGetValue(uint8 *u8_DebugTimeStampValue);
extern void DCM_InvIf_ushMVdNfromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue);
extern void DCM_InvIf_ushMVdN2fromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue);
extern uint8 DCM_InvIf_ucABSReffromZOM(uint8 u8ZOMSlot, uint8 u8Position);
extern uint8 DCM_InvIf_ucAlgoTelEvtCntfromZOM(uint8 u8ZOMSlot);

// RST Debug: additional information concerning timestamps of telegrams
extern uint8 DCM_InvIf_GetNumberOfE7withInvalidTs(void);        // ucE7withInvalidTimestamp     Huf_Rte.c
extern uint8 DCM_InvIf_GetNumberOfE7withOutdatedTs(void);       // ucE7withOutdatedTimestamp    Huf_Rte.c
// RST Debug: newst and oldest ABS matrix timestamp
extern void DCM_InvIf_ulAbsTimeStampGetNewestValue(uint8 *u8_DebugTimeStampValue);        // abs_lin.c
extern void DCM_InvIf_ulAbsTimeStampGetOldestValue(uint8 *u8_DebugTimeStampValue);        // abs_lin.c

#endif

#ifdef NVM_DEBUG
extern uint8 DCM_InvIf_NvmReadResult(void);
extern uint8 DCM_InvIf_NvmWriteResult(void);
extern void DCM_InvIf_NvmBlockConsistence(uint8 *u8_NvMBuffer);
extern uint8 DCM_InvIf_DebugABSTicksFront(void);
extern uint8 DCM_InvIf_DebugABSTicksRear(void);
#endif

#endif
