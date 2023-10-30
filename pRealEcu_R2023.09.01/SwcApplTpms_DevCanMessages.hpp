

#ifndef Huf_DevCanMessages_H
#define Huf_DevCanMessages_H

#include "Tpms_Rte_Data_Type.hpp"
#include "iTpms_Interface.hpp"

#define SIZE_ARRAY(ARRAY_SIZE, STRUCT_SIZE)   (uint8) ( sizeof(ARRAY_SIZE) / sizeof(STRUCT_SIZE) ) // get the size of an array of structures

#define DCM_MAX_SIZE_ENV_BUF 248U //  with 8 multiplex ID for Event there can be stored 31 complete packages

#ifdef NVM_DEBUG
#define DCM_MAX_SIZE_SYS_BUF  16U //  with 16 multiplex ID for System there can be stored 1 complete package
#else
#define DCM_MAX_SIZE_SYS_BUF  15U //  with 15 multiplex ID for System there can be stored 1 complete package
#endif

#define DCM_MULTIPLEX_0     0U
#define DCM_MULTIPLEX_1     1U
#define DCM_MULTIPLEX_2     2U
#define DCM_MULTIPLEX_3     3U
#define DCM_MULTIPLEX_4     4U
#define DCM_MULTIPLEX_5     5U

#define DCM_MULTIPLEX_6     6U
#define DCM_MULTIPLEX_7     7U
#define DCM_MULTIPLEX_8     8U
#define DCM_MULTIPLEX_9     9U
#define DCM_MULTIPLEX_10   10U
#define DCM_MULTIPLEX_11   11U
#define DCM_MULTIPLEX_12   12U
#define DCM_MULTIPLEX_13   13U
#define DCM_MULTIPLEX_14   14U
#define DCM_MULTIPLEX_15   15U
#define DCM_MULTIPLEX_16   16U
#define DCM_MULTIPLEX_17   17U

#define DCM_MULTIPLEX_20   20U
#define DCM_MULTIPLEX_21   21U
#define DCM_MULTIPLEX_22   22U
#define DCM_MULTIPLEX_23   23U
#define DCM_MULTIPLEX_24   24U

#define DCM_MULTIPLEX_25   25U

#define DCM_MULTIPLEX_30   30U
#define DCM_MULTIPLEX_31   31U
#define DCM_MULTIPLEX_32   32U
#define DCM_MULTIPLEX_33   33U
#define DCM_MULTIPLEX_40   40U
#define DCM_MULTIPLEX_41   41U
#define DCM_MULTIPLEX_42   42U
#define DCM_MULTIPLEX_43   43U
#define DCM_MULTIPLEX_44   44U
#define DCM_MULTIPLEX_45   45U
#define DCM_MULTIPLEX_46   46U
#define DCM_MULTIPLEX_47   47U

//typedef uint8 DCM_HufCanMessageByte;
//
//typedef struct
//{
//  DCM_HufCanMessageByte Byte0;
//  DCM_HufCanMessageByte Byte1;
//  DCM_HufCanMessageByte Byte2;
//  DCM_HufCanMessageByte Byte3;
//  DCM_HufCanMessageByte Byte4;
//  DCM_HufCanMessageByte Byte5;
//  DCM_HufCanMessageByte Byte6;
//  DCM_HufCanMessageByte Byte7;
//}DCM_HufCanMessage;

typedef union
{
  tsCAN_Message MessageMultiplex_00;
  struct DCM_S_MultiplexMessage_00
  {
   uint8 u8_MultiplexID;
   uint8 u8_RFTelegramTimeStamp[3];
   uint8 u8_IDLastRF[4];
  }Struct_MessageMultiplex_00;
}DCM_U_MultiplexMessage_00;

typedef union
{
  tsCAN_Message MessageMultiplex_01;
  struct DCM_S_MultiplexMessage_01
  {
   uint8 u8_MultiplexID;                // byte 0
    //uint8 u8_AbsTicsOverflowCntFL;       // byte 1
    //uint8 u8_AbsTicsOverflowCntFR;       // byte 2
    //uint8 u8_AbsTicsOverflowCntRL;       // byte 3
    //uint8 u8_AbsTicsOverflowCntRR;       // byte 4

   uint8 u8_PositionRecCntFL;       // byte 1
   uint8 u8_PositionRecCntFR;       // byte 2
   uint8 u8_PositionRecCntRL;       // byte 3
   uint8 u8_PositionRecCntRR;       // byte 4

#ifdef DEBUG_AUTOLOCATION
   uint8 u8_ulDebugRfTimeStamp[3];
#else
   uint8 u8_ReservedM1B7[3];            // byte 5-7
#endif
  }Struct_MessageMultiplex_01;
}DCM_U_MultiplexMessage_01;

typedef union
{
  tsCAN_Message MessageMultiplex_02;
  struct DCM_S_MultiplexMessage_02
  {
   uint8 u8_MultiplexID;
   uint8 u8_AbsLinCntFL;
   uint8 u8_AbsLinCntFR;
   uint8 u8_AbsLinCntRL;
   uint8 u8_AbsLinCntRR;
#ifdef DEBUG_AUTOLOCATION
   uint8 u8_ulTimePreviousfromPutABS[3];
#else
   uint8 u8_ReservedM2B5_7[3];            // byte 5-7
#endif
  }Struct_MessageMultiplex_02;
}DCM_U_MultiplexMessage_02;

typedef union
{
  tsCAN_Message MessageMultiplex_03;
  struct DCM_S_MultiplexMessage_03
  {
   uint8 u8_MultiplexID;
   uint8 u8_AbsCorrCntFL;              // Correlation counter for wheel position FL of last valid sensor ID        ECU_C_Sum_Corr_FL
   uint8 u8_AbsCorrCntFR;              // Correlation counter for wheel position FR of last valid sensor ID        ECU_C_Sum_Corr_FR
   uint8 u8_AbsCorrCntRL;              // Correlation counter for wheel position RL of last valid sensor ID        ECU_C_Sum_Corr_RL
   uint8 u8_AbsCorrCntRR;              // Correlation counter for wheel position RR of last valid sensor ID        ECU_C_Sum_Corr_RR
   uint8 u8_ReservedM3B5;
   uint8 u8_AbsLinAngleFL;           // Linearized reception angle in ABS tics FL for specific correlation telegrams         ECU_Hist_ABS_FL
   uint8 u8_AbsLinAngleFR;           // Linearized reception angle in ABS tics FR for specific correlation telegrams         ECU_Hist_ABS_FR
  }Struct_MessageMultiplex_03;
}DCM_U_MultiplexMessage_03;

typedef union
{
  tsCAN_Message MessageMultiplex_04;
  struct DCM_S_MultiplexMessage_04
  {
   uint8 u8_MultiplexID;
   uint8 u8_RfTelByteValue[7];
  }Struct_MessageMultiplex_04;
}DCM_U_MultiplexMessage_04;

typedef union
{
  tsCAN_Message MessageMultiplex_05;
  struct DCM_S_MultiplexMessage_05
  {
   uint8 u8_MultiplexID;
   uint8 u8_RfTelByteValue[4];
#ifdef DEBUG_AUTOLOCATION
   uint8 u8_ucABSRef_0_0;
   uint8 u8_ucABSRef_0_1;
   uint8 u8_ucABSRef_0_2;
#else
   uint8 u8_ReservedM5B5_7[3];
#endif
  }Struct_MessageMultiplex_05;
}DCM_U_MultiplexMessage_05;

#ifdef DEBUG_AUTOLOCATION

typedef union
{
  tsCAN_Message MessageMultiplex_06;
  struct DCM_S_MultiplexMessage_06
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_0_0[2];
   uint8 u8_ushMVdN_0_1[2];
   uint8 u8_ushMVdN_0_2[2];
   uint8 u8_ucABSRef_0_3;
  }Struct_MessageMultiplex_06;
}DCM_U_MultiplexMessage_06;

typedef union
{
  tsCAN_Message MessageMultiplex_07;
  struct DCM_S_MultiplexMessage_07
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_0_3[2];
   uint8 u8_ushMVdN_1_0[2];
   uint8 u8_ushMVdN_1_1[2];
   uint8 u8_ucABSRef_1_0;
  }Struct_MessageMultiplex_07;
}DCM_U_MultiplexMessage_07;

typedef union
{
  tsCAN_Message MessageMultiplex_08;
  struct DCM_S_MultiplexMessage_08
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_1_2[2];
   uint8 u8_ushMVdN_1_3[2];
   uint8 u8_ushMVdN_2_0[2];
   uint8 u8_ucABSRef_1_1;
  }Struct_MessageMultiplex_08;
}DCM_U_MultiplexMessage_08;

typedef union
{
  tsCAN_Message MessageMultiplex_09;
  struct DCM_S_MultiplexMessage_09
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_2_1[2];
   uint8 u8_ushMVdN_2_2[2];
   uint8 u8_ushMVdN_2_3[2];
   uint8 u8_ucABSRef_1_2;
  }Struct_MessageMultiplex_09;
}DCM_U_MultiplexMessage_09;

typedef union
{
  tsCAN_Message MessageMultiplex_10;
  struct DCM_S_MultiplexMessage_10
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_3_0[2];
   uint8 u8_ushMVdN_3_1[2];
   uint8 u8_ushMVdN_3_2[2];
   uint8 u8_ucABSRef_1_3;
  }Struct_MessageMultiplex_10;
}DCM_U_MultiplexMessage_10;

typedef union
{
  tsCAN_Message MessageMultiplex_11;
  struct DCM_S_MultiplexMessage_11
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN_3_3[2];
   uint8 u8_ushMVdN2_0_0[2];
   uint8 u8_ushMVdN2_0_1[2];
   uint8 u8_ucABSRef_2_0;
  }Struct_MessageMultiplex_11;
}DCM_U_MultiplexMessage_11;

typedef union
{
  tsCAN_Message MessageMultiplex_12;
  struct DCM_S_MultiplexMessage_12
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN2_0_2[2];
   uint8 u8_ushMVdN2_0_3[2];
   uint8 u8_ushMVdN2_1_0[2];
   uint8 u8_ucABSRef_2_1;
  }Struct_MessageMultiplex_12;
}DCM_U_MultiplexMessage_12;

typedef union
{
  tsCAN_Message MessageMultiplex_13;
  struct DCM_S_MultiplexMessage_13
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN2_1_1[2];
   uint8 u8_ushMVdN2_1_2[2];
   uint8 u8_ushMVdN2_1_3[2];
   uint8 u8_ucABSRef_2_2;
  }Struct_MessageMultiplex_13;
}DCM_U_MultiplexMessage_13;

typedef union
{
  tsCAN_Message MessageMultiplex_14;
  struct DCM_S_MultiplexMessage_14
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN2_2_0[2];
   uint8 u8_ushMVdN2_2_1[2];
   uint8 u8_ushMVdN2_2_2[2];
   uint8 u8_ucABSRef_2_3;
  }Struct_MessageMultiplex_14;
}DCM_U_MultiplexMessage_14;

typedef union
{
  tsCAN_Message MessageMultiplex_15;
  struct DCM_S_MultiplexMessage_15
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN2_2_3[2];
   uint8 u8_ushMVdN2_3_0[2];
   uint8 u8_ushMVdN2_3_1[2];
   uint8 u8_ucABSRef_3_0;
  }Struct_MessageMultiplex_15;
}DCM_U_MultiplexMessage_15;

typedef union
{
  tsCAN_Message MessageMultiplex_16;
  struct DCM_S_MultiplexMessage_16
  {
   uint8 u8_MultiplexID;
   uint8 u8_ushMVdN2_3_2[2];
   uint8 u8_ushMVdN2_3_3[2];
   uint8 u8_ucABSRef_3_1;
   uint8 u8_ucABSRef_3_2;
   uint8 u8_ucABSRef_3_3;
  }Struct_MessageMultiplex_16;
}DCM_U_MultiplexMessage_16;

typedef union
{
  tsCAN_Message MessageMultiplex_17;
  struct DCM_S_MultiplexMessage_17
  {
   uint8 u8_MultiplexID;
   uint8 u8_ucAlgoTelEvtCnt_0;
   uint8 u8_ucAlgoTelEvtCnt_1;
   uint8 u8_ucAlgoTelEvtCnt_2;
   uint8 u8_ucAlgoTelEvtCnt_3;
   uint8 u8_ulTimeNextfromPutABS[3];
  }Struct_MessageMultiplex_17;
}DCM_U_MultiplexMessage_17;

#endif

typedef union
{
  tsCAN_Message MessageMultiplex_20;
  struct DCM_S_MultiplexMessage_20
  {
   bitfield u8_MultiplexID : 8;          // byte 0
   bitfield u8_PressAmbient : 8;         // byte 1     Ambient pressure provided by vehicle CAN         VEH_P_ambient
   bitfield u8_TempAmbient : 8;          // byte 2     Ambient temperature provided by vehicle CAN        VEH_T_Ambient
   bitfield u8_SpeedVehicleMsbits : 8;   // byte 3
#ifdef _WINDLL
   bitfield u4_ZomCurrIDPosition : 4;    // byte 4, bits 0-3
   bitfield u2_ReservedM20B4b4_5 : 2;    // byte 4, bits 4-5
   bitfield u2_SpeedVehicleLsbits : 2;   // byte 4, bits 6-7
#else
   bitfield u4_ZomCurrIDPosition : 4;    // byte 4, bits 0-3
   bitfield u2_ReservedM20B4b4_5 : 2;    // byte 4, bits 4-5
   bitfield u2_SpeedVehicleLsbits : 2;   // byte 4, bits 6-7
#endif
   bitfield u8_WheelPosCurrID : 8;       // byte 5
   bitfield u8_AbsLinAngleRL : 8;        // byte 6
   bitfield u8_AbsLinAngleRR : 8;        // byte 7
  }Struct_MessageMultiplex_20;
}DCM_U_MultiplexMessage_20;

typedef union
{
  tsCAN_Message MessageMultiplex_21;
  struct DCM_S_MultiplexMessage_21
  {
   uint8 u8_MultiplexID;
   uint8 u8_RxRSSIRawValue;
   uint8 u8_TelTypeCurrID;
   uint8 u8_PressLastRx;
   sint8 s8_TempLastRx;
   uint8 u8_RxStatusFields[2];
   uint8 u8_RecEvent;
  }Struct_MessageMultiplex_21;
}DCM_U_MultiplexMessage_21;

// system

typedef union
{
  tsCAN_Message MessageMultiplex_22;
  struct DCM_S_MultiplexMessage_22
  {
   bitfield u8_MultiplexID : 8;        // byte 0
   bitfield u8_NoiseLevel : 8;         // byte 1
   bitfield u8_TPMSStateMsbits : 8;    // byte 2
   bitfield u8_TPMSStateLsbits : 8;    // byte 3
   bitfield u8_WAllocTimeoutCnt : 8;   // byte 4
#ifdef _WINDLL
   bitfield u4_RevGearCnt : 4;         // byte 5, bits 0-3
   bitfield u4_AbsResetCnt : 4;        // byte 5, bits 4-7
   bitfield u4_VehiculeStatus : 4;     // byte 6, bits 0-3
   bitfield u4_StopEventCnt : 4;       // byte 6, bit 4-7
#else
   bitfield u4_RevGearCnt : 4;         // byte 5, bits 0-3
   bitfield u4_AbsResetCnt : 4;        // byte 5, bits 4-7
   bitfield u4_VehiculeStatus : 4;     // byte 6, bits 0-3
   bitfield u4_StopEventCnt : 4;       // byte 6, bit 4-7
#endif //_WINDLL

   bitfield u8_PressRefCurrID : 8;     // byte 7
  }Struct_MessageMultiplex_22;
}DCM_U_MultiplexMessage_22;

typedef union
{
  tsCAN_Message MessageMultiplex_23;
  struct DCM_S_MultiplexMessage_23
  {
   bitfield u8_MultiplexID : 8;
#ifdef _WINDLL
   bitfield u3_ReservedM23B1b0_2 : 3;  // byte 1, bit 0-2
   bitfield u1_RFJammerStatus : 1;     // byte 1, bit 3
   bitfield u4_TempWarnStatus : 4;     // byte 1, bit 4-7
#else
   bitfield u3_ReservedM23B1b0_2 : 3;  // byte 1, bit 0-2
   bitfield u1_RFJammerStatus : 1;     // byte 1, bit 3
   bitfield u4_TempWarnStatus : 4;     // byte 1, bit 4-7
#endif
   bitfield u8_tCmp_AxImb : 8;             // byte 2
   bitfield u8_tCmp_DHW : 8;               // byte 3
   bitfield u8_tCmp_EuF : 8;               // byte 4
   bitfield u8_tCmp_FT : 8;                // byte 5
   bitfield u8_tCmp_HardTDR : 8;           // byte 6
   bitfield u8_DebugAllocType : 8;         // byte 7
  }Struct_MessageMultiplex_23;
}DCM_U_MultiplexMessage_23;

typedef union
{
  tsCAN_Message MessageMultiplex_24;
  struct DCM_S_MultiplexMessage_24
  {
   uint8 u8_MultiplexID;
   uint8 u8_tCmp_HiP;              // byte 1
   uint8 u8_tCmp_LowP;             // byte 2
   uint8 u8_tCmp_PminDR;           // byte 3
   uint8 u8_ReservedM24B4_6[2];
   uint8 u8_VehDirection;
   uint8 u8_AllRecEventCnt;
  }Struct_MessageMultiplex_24;
}DCM_U_MultiplexMessage_24;

#ifdef NVM_DEBUG

typedef union
{
  tsCAN_Message MessageMultiplex_25;
  struct DCM_S_MultiplexMessage_25
  {
   uint8 u8_MultiplexID;
   uint8 u8_NvM_uiNvmBlockConsistence[2];              // byte 1 and 2
   uint8 u8_NvM_WriteReturn;             // byte 3
   uint8 u8_NvM_ReadReturn;           // byte 4
   uint8 u8_NvM_ucABSTicksFrontAx;
   uint8 u8_NvM_ucABSTicksRearAx;
   uint8 u8_Reserved;
  }Struct_MessageMultiplex_25;
}DCM_U_MultiplexMessage_25;

#endif

typedef union
{
  tsCAN_Message MessageMultiplex_30;
  struct DCM_S_MultiplexMessage_30
  {
   uint8 u8_MultiplexID;
   uint8 u8_HistoryID0[4];
   uint8 u8_HistoryWP0;
   uint8 u8_NoRxCntHistoryID0;
   uint8 u8_WarnVeCtorHist0;
  }Struct_MessageMultiplex_30;
}DCM_U_MultiplexMessage_30;

typedef union
{
  tsCAN_Message MessageMultiplex_31;
  struct DCM_S_MultiplexMessage_31
  {
   uint8 u8_MultiplexID;
   uint8 u8_HistoryID1[4];
   uint8 u8_HistoryWP1;
   uint8 u8_NoRxCntHistoryID1;
   uint8 u8_WarnVeCtorHist1;
  }Struct_MessageMultiplex_31;
}DCM_U_MultiplexMessage_31;

typedef union
{
  tsCAN_Message MessageMultiplex_32;
  struct DCM_S_MultiplexMessage_32
  {
   uint8 u8_MultiplexID;
   uint8 u8_HistoryID2[4];
   uint8 u8_HistoryWP2;
   uint8 u8_NoRxCntHistoryID2;
   uint8 u8_WarnVeCtorHist2;
  }Struct_MessageMultiplex_32;
}DCM_U_MultiplexMessage_32;

typedef union
{
  tsCAN_Message MessageMultiplex_33;
  struct DCM_S_MultiplexMessage_33
  {
   uint8 u8_MultiplexID;
   uint8 u8_HistoryID3[4];
   uint8 u8_HistoryWP3;
   uint8 u8_NoRxCntHistoryID3;
   uint8 u8_WarnVeCtorHist3;
  }Struct_MessageMultiplex_33;
}DCM_U_MultiplexMessage_33;

typedef union
{
  tsCAN_Message MessageMultiplex_40;
  struct DCM_S_MultiplexMessage_40
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID0[4];
   uint8 u8_ZomAutolocStatus0;
   uint8 u8_ZomTelCnt0;
   uint8 u8_ReservedM40B7;
  }Struct_MessageMultiplex_40;
}DCM_U_MultiplexMessage_40;

typedef union
{
  tsCAN_Message MessageMultiplex_41;
  struct DCM_S_MultiplexMessage_41
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID1[4];
   uint8 u8_ZomAutolocStatus1;
   uint8 u8_ZomTelCnt1;
   uint8 u8_ReservedM41B7;
  }Struct_MessageMultiplex_41;
}DCM_U_MultiplexMessage_41;

typedef union
{
  tsCAN_Message MessageMultiplex_42;
  struct DCM_S_MultiplexMessage_42
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID2[4];
   uint8 u8_ZomAutolocStatus2;
   uint8 u8_ZomTelCnt2;
   uint8 u8_ReservedM42B7;
  }Struct_MessageMultiplex_42;
}DCM_U_MultiplexMessage_42;

typedef union
{
  tsCAN_Message MessageMultiplex_43;
  struct DCM_S_MultiplexMessage_43
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID3[4];
   uint8 u8_ZomAutolocStatus3;
   uint8 u8_ZomTelCnt3;
   uint8 u8_ReservedM43B7;
  }Struct_MessageMultiplex_43;
}DCM_U_MultiplexMessage_43;

typedef union
{
  tsCAN_Message MessageMultiplex_44;
  struct DCM_S_MultiplexMessage_44
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID4[4];
   uint8 u8_ZomAutolocStatus4;
   uint8 u8_ZomTelCnt4;
   uint8 u8_ReservedM44B7;
  }Struct_MessageMultiplex_44;
}DCM_U_MultiplexMessage_44;

typedef union
{
  tsCAN_Message MessageMultiplex_45;
  struct DCM_S_MultiplexMessage_45
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID5[8];
   uint8 u8_ZomAutolocStatus5;
   uint8 u8_ZomTelCnt5;
   uint8 u8_ReservedM45B7;
  }Struct_MessageMultiplex_45;
}DCM_U_MultiplexMessage_45;

typedef union
{
  tsCAN_Message MessageMultiplex_46;
  struct DCM_S_MultiplexMessage_46
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID6[4];
   uint8 u8_ZomAutolocStatus6;
   uint8 u8_ZomTelCnt6;
   uint8 u8_ReservedM46B7;
  }Struct_MessageMultiplex_46;
}DCM_U_MultiplexMessage_46;

typedef union
{
  tsCAN_Message MessageMultiplex_47;
  struct DCM_S_MultiplexMessage_47
  {
   uint8 u8_MultiplexID;
   uint8 u8_ZomWuID7[4];
   uint8 u8_ZomAutolocStatus7;
   uint8 u8_ZomTelCnt7;
   uint8 u8_ReservedM47B7;
  }Struct_MessageMultiplex_47;
}DCM_U_MultiplexMessage_47;

//Structure which keep the whole multiplex messages Event + System
typedef struct{
  DCM_U_MultiplexMessage_00 DCM_S_MultiPlexMess_00;
  DCM_U_MultiplexMessage_01 DCM_S_MultiPlexMess_01;
  DCM_U_MultiplexMessage_02 DCM_S_MultiPlexMess_02;
  DCM_U_MultiplexMessage_03 DCM_S_MultiPlexMess_03;
  DCM_U_MultiplexMessage_04 DCM_S_MultiPlexMess_04;
  DCM_U_MultiplexMessage_05 DCM_S_MultiPlexMess_05;
#ifdef DEBUG_AUTOLOCATION
  DCM_U_MultiplexMessage_06 DCM_S_MultiPlexMess_06;
  DCM_U_MultiplexMessage_07 DCM_S_MultiPlexMess_07;
  DCM_U_MultiplexMessage_08 DCM_S_MultiPlexMess_08;
  DCM_U_MultiplexMessage_09 DCM_S_MultiPlexMess_09;
  DCM_U_MultiplexMessage_10 DCM_S_MultiPlexMess_10;
  DCM_U_MultiplexMessage_11 DCM_S_MultiPlexMess_11;
  DCM_U_MultiplexMessage_12 DCM_S_MultiPlexMess_12;
  DCM_U_MultiplexMessage_13 DCM_S_MultiPlexMess_13;
  DCM_U_MultiplexMessage_14 DCM_S_MultiPlexMess_14;
  DCM_U_MultiplexMessage_15 DCM_S_MultiPlexMess_15;
  DCM_U_MultiplexMessage_16 DCM_S_MultiPlexMess_16;
  DCM_U_MultiplexMessage_17 DCM_S_MultiPlexMess_17;
#endif
  DCM_U_MultiplexMessage_20 DCM_S_MultiPlexMess_20;
  DCM_U_MultiplexMessage_21 DCM_S_MultiPlexMess_21;
  DCM_U_MultiplexMessage_22 DCM_S_MultiPlexMess_22;
  DCM_U_MultiplexMessage_23 DCM_S_MultiPlexMess_23;
  DCM_U_MultiplexMessage_24 DCM_S_MultiPlexMess_24;
#ifdef NVM_DEBUG
  DCM_U_MultiplexMessage_25 DCM_S_MultiPlexMess_25;
#endif
  DCM_U_MultiplexMessage_30 DCM_S_MultiPlexMess_30;
  DCM_U_MultiplexMessage_31 DCM_S_MultiPlexMess_31;
  DCM_U_MultiplexMessage_32 DCM_S_MultiPlexMess_32;
  DCM_U_MultiplexMessage_33 DCM_S_MultiPlexMess_33;
  DCM_U_MultiplexMessage_40 DCM_S_MultiPlexMess_40;
  DCM_U_MultiplexMessage_41 DCM_S_MultiPlexMess_41;
  DCM_U_MultiplexMessage_42 DCM_S_MultiPlexMess_42;
  DCM_U_MultiplexMessage_43 DCM_S_MultiPlexMess_43;
  DCM_U_MultiplexMessage_44 DCM_S_MultiPlexMess_44;
  DCM_U_MultiplexMessage_45 DCM_S_MultiPlexMess_45;
  DCM_U_MultiplexMessage_46 DCM_S_MultiPlexMess_46;
  DCM_U_MultiplexMessage_47 DCM_S_MultiPlexMess_47;
}DCM_StructMultiplexMessageIDs;

// extern functions

extern void DCM_DataToTransmitOnCAN(tsCAN_Message* spCAN_Message);
extern void DCM_CyclicDebugSystemDataUpdate(void);
extern void DCM_EventDataUpdateOnRx(void);
extern void DCM_InitCanDebug(void);

#endif
