/******************************************************************************/
/* File   : SwcApplTpms_DevCanMessages.c                                      */
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
#include "Std_Types.hpp"

#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"
#include "DevCanHandling.hpp"

#include "global.hpp"
#include "WallocX.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "USCS.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DCM__MAXSIZE_U8_BUFFER     250U
#define DMC__HISTORY_POSITION_0    0x00U
#define DMC__HISTORY_POSITION_1    0x01U
#define DMC__HISTORY_POSITION_2    0x02U
#define DMC__HISTORY_POSITION_3    0x03U
#define DMC__ZOM_POSITION_0       0x00U
#define DMC__ZOM_POSITION_1       0x01U
#define DMC__ZOM_POSITION_2       0x02U
#define DMC__ZOM_POSITION_3       0x03U
#define DMC__ZOM_POSITION_4       0x04U
#define DMC__ZOM_POSITION_5       0x05U
#define DMC__ZOM_POSITION_6       0x06U
#define DMC__ZOM_POSITION_7       0x07U
#define StructAccesMultiplex_00     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_00.Struct_MessageMultiplex_00
#define StructAccesMultiplex_01     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_01.Struct_MessageMultiplex_01
#define StructAccesMultiplex_02     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_02.Struct_MessageMultiplex_02
#define StructAccesMultiplex_03     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_03.Struct_MessageMultiplex_03
#define StructAccesMultiplex_04     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_04.Struct_MessageMultiplex_04
#define StructAccesMultiplex_05     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_05.Struct_MessageMultiplex_05

#ifdef DEBUG_AUTOLOCATION
#define StructAccesMultiplex_06     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_06.Struct_MessageMultiplex_06
#define StructAccesMultiplex_07     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_07.Struct_MessageMultiplex_07
#define StructAccesMultiplex_08     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_08.Struct_MessageMultiplex_08
#define StructAccesMultiplex_09     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_09.Struct_MessageMultiplex_09
#define StructAccesMultiplex_10     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_10.Struct_MessageMultiplex_10
#define StructAccesMultiplex_11     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_11.Struct_MessageMultiplex_11
#define StructAccesMultiplex_12     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_12.Struct_MessageMultiplex_12
#define StructAccesMultiplex_13     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_13.Struct_MessageMultiplex_13
#define StructAccesMultiplex_14     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_14.Struct_MessageMultiplex_14
#define StructAccesMultiplex_15     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_15.Struct_MessageMultiplex_15
#define StructAccesMultiplex_16     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_16.Struct_MessageMultiplex_16
#define StructAccesMultiplex_17     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_17.Struct_MessageMultiplex_17
#endif

#define StructAccesMultiplex_20     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_20.Struct_MessageMultiplex_20
#define StructAccesMultiplex_21     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_21.Struct_MessageMultiplex_21
#define StructAccesMultiplex_22     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_22.Struct_MessageMultiplex_22
#define StructAccesMultiplex_23     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_23.Struct_MessageMultiplex_23
#define StructAccesMultiplex_24     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_24.Struct_MessageMultiplex_24

#ifdef NVM_DEBUG
#define StructAccesMultiplex_25     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_25.Struct_MessageMultiplex_25
#endif

#define StructAccesMultiplex_30     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_30.Struct_MessageMultiplex_30
#define StructAccesMultiplex_31     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_31.Struct_MessageMultiplex_31
#define StructAccesMultiplex_32     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_32.Struct_MessageMultiplex_32
#define StructAccesMultiplex_33     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_33.Struct_MessageMultiplex_33
#define StructAccesMultiplex_40     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_40.Struct_MessageMultiplex_40
#define StructAccesMultiplex_41     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_41.Struct_MessageMultiplex_41
#define StructAccesMultiplex_42     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_42.Struct_MessageMultiplex_42
#define StructAccesMultiplex_43     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_43.Struct_MessageMultiplex_43
#define StructAccesMultiplex_44     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_44.Struct_MessageMultiplex_44
#define StructAccesMultiplex_45     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_45.Struct_MessageMultiplex_45
#define StructAccesMultiplex_46     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_46.Struct_MessageMultiplex_46
#define StructAccesMultiplex_47     DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_47.Struct_MessageMultiplex_47

#define DCM__BUFFER_READ_START_MSG4     5U
#define DCM__BUFFER_READ_LENGTH_MSG4             7U
#define DCM__BUFFER_READ_START_MSG5     12U
#define DCM__BUFFER_READ_LENGTH_MSG5             4U

#ifdef NVM_DEBUG
#define DCM_SYSTEM_MULTIPLEX_SIZE   16U
#else
#define DCM_SYSTEM_MULTIPLEX_SIZE   15U
#endif

#ifdef DEBUG_AUTOLOCATION
#define DCM_EVENT_MULTIPLEX_SIZE    20U
#else
#define DCM_EVENT_MULTIPLEX_SIZE    8U
#endif

#define DCM_SIZEOF_EVENT_MULTIPLEXES      SIZE_ARRAY(DCM_AS_ConfigureEventMultiplexMsg, DCM_Struct_MultiplexDataType)
#define DCM_SIZEOF_SYSTEM_MULTIPLEXES     SIZE_ARRAY(DCM_AS_ConfigureSystemMultiplexMsg, DCM_Struct_MultiplexDataType)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
  DCM__E_EventMultiType
   ,  DCM__E_SystemMultiType
}DCM_Enum_MultiTypes;

typedef void (*tBuildMsg)(uint8 Param);

typedef struct{
  uint8 DCM_U8_MultiplexId;
  const tBuildMsg DCM_pfnBuildMsg;
}DCM_Struct_MultiplexDataType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
static const DCM_Struct_MultiplexDataType DCM_AS_ConfigureEventMultiplexMsg[DCM_EVENT_MULTIPLEX_SIZE] = {
  {DCM_MULTIPLEX_0,   &DCM_MessageUpdateMultiplex_00     }
   ,  {DCM_MULTIPLEX_1,   &DCM_MessageUpdateMultiplex_01     }
   ,  {DCM_MULTIPLEX_2,   &DCM_MessageUpdateMultiplex_02     }
   ,  {DCM_MULTIPLEX_3,   &DCM_MessageUpdateMultiplex_03     }
   ,  {DCM_MULTIPLEX_4,   &DCM_MessageUpdateMultiplex_04     }
   ,  {DCM_MULTIPLEX_5,   &DCM_MessageUpdateMultiplex_05     },
#ifdef DEBUG_AUTOLOCATION
  {DCM_MULTIPLEX_6,   &DCM_MessageUpdateMultiplex_06     }
   ,  {DCM_MULTIPLEX_7,   &DCM_MessageUpdateMultiplex_07     }
   ,  {DCM_MULTIPLEX_8,   &DCM_MessageUpdateMultiplex_08     }
   ,  {DCM_MULTIPLEX_9,   &DCM_MessageUpdateMultiplex_09     }
   ,  {DCM_MULTIPLEX_10,  &DCM_MessageUpdateMultiplex_10     }
   ,  {DCM_MULTIPLEX_11,  &DCM_MessageUpdateMultiplex_11     }
   ,  {DCM_MULTIPLEX_12,  &DCM_MessageUpdateMultiplex_12     }
   ,  {DCM_MULTIPLEX_13,  &DCM_MessageUpdateMultiplex_13     }
   ,  {DCM_MULTIPLEX_14,  &DCM_MessageUpdateMultiplex_14     }
   ,  {DCM_MULTIPLEX_15,  &DCM_MessageUpdateMultiplex_15     }
   ,  {DCM_MULTIPLEX_16,  &DCM_MessageUpdateMultiplex_16     }
   ,  {DCM_MULTIPLEX_17,  &DCM_MessageUpdateMultiplex_17     },
#endif
  {DCM_MULTIPLEX_20,  &DCM_MessageUpdateMultiplex_20     }
   ,  {DCM_MULTIPLEX_21,  &DCM_MessageUpdateMultiplex_21     },
};

static const DCM_Struct_MultiplexDataType DCM_AS_ConfigureSystemMultiplexMsg[DCM_SYSTEM_MULTIPLEX_SIZE] = {
  {DCM_MULTIPLEX_22,  &DCM_MessageUpdateMultiplex_22     }
   ,  {DCM_MULTIPLEX_23,  &DCM_MessageUpdateMultiplex_23     }
   ,  {DCM_MULTIPLEX_24,  &DCM_MessageUpdateMultiplex_24     },
#ifdef NVM_DEBUG
  {DCM_MULTIPLEX_25,  &DCM_MessageUpdateMultiplex_25     },
#endif
  {DCM_MULTIPLEX_30,  &DCM_MessageUpdateMultiplex_30     }
   ,  {DCM_MULTIPLEX_31,  &DCM_MessageUpdateMultiplex_31     }
   ,  {DCM_MULTIPLEX_32,  &DCM_MessageUpdateMultiplex_32     }
   ,  {DCM_MULTIPLEX_33,  &DCM_MessageUpdateMultiplex_33     }
   ,  {DCM_MULTIPLEX_40,  &DCM_MessageUpdateMultiplex_40     }
   ,  {DCM_MULTIPLEX_41,  &DCM_MessageUpdateMultiplex_41     }
   ,  {DCM_MULTIPLEX_42,  &DCM_MessageUpdateMultiplex_42     }
   ,  {DCM_MULTIPLEX_43,  &DCM_MessageUpdateMultiplex_43     }
   ,  {DCM_MULTIPLEX_44,  &DCM_MessageUpdateMultiplex_44     }
   ,  {DCM_MULTIPLEX_45,  &DCM_MessageUpdateMultiplex_45     }
   ,  {DCM_MULTIPLEX_46,  &DCM_MessageUpdateMultiplex_46     }
   ,  {DCM_MULTIPLEX_47,  &DCM_MessageUpdateMultiplex_47     },
};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static boolean bo_StructSystemMultiLast;
static uint8 u8_EnvReadCnt;
static uint8 u8_SysReadCnt;
static uint8 u8_EnvWriteCnt;
static uint8 u8_SysWriteCnt;
static uint8 DCM_U8_EventDataMaxMultiplexNr;
static uint8 DCM_U8_SystemDataMaxMultiplexNr;
static Type_SwcApplTpms_stMessageCan S_HufEnvMsgBuf[DCM_MAX_SIZE_ENV_BUF];
static Type_SwcApplTpms_stMessageCan S_HufSysMsgBuf[DCM_MAX_SIZE_SYS_BUF];
static DCM_StructMultiplexMessageIDs DCM_S_MultiplexMessageIDs;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void DCM_SystemDataPutToQueue(void);
static void DCM_PutSystemData2Buffer(Type_SwcApplTpms_stMessageCan S_SysDataMultiplex);
static void DCM_SystemDataGetFromBuffer(Type_SwcApplTpms_stMessageCan* tHufDisplay);
static void DCM_StoreMaxMultiplexSystemNr(uint8 U8_CurrentMultiplexNr);
static void DCM_EventDataPutToQueue(void);
static void DCM_PutEventData2Buffer(Type_SwcApplTpms_stMessageCan S_EnvDataMultiplex);
static boolean DCM_EventDataGetFromBuffer(Type_SwcApplTpms_stMessageCan* tHufDisplay);
static void DCM_StoreMaxMultiplexEventNr(uint8 U8_CurrentMultiplexNr);
static void DCM_MessageUpdateMultiplex_00(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_01(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_02(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_03(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_04(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_05(uint8 U8_CfgArrPosition);

#ifdef DEBUG_AUTOLOCATION
static void DCM_MessageUpdateMultiplex_06(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_07(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_08(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_09(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_10(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_11(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_12(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_13(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_14(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_15(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_16(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_17(uint8 U8_CfgArrPosition);
#endif

static void DCM_MessageUpdateMultiplex_20(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_21(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_22(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_23(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_24(uint8 U8_CfgArrPosition);

#ifdef NVM_DEBUG
static void DCM_MessageUpdateMultiplex_25(uint8 U8_CfgArrPosition);
#endif

static void DCM_MessageUpdateMultiplex_30(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_31(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_32(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_33(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_40(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_41(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_42(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_43(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_44(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_45(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_46(uint8 U8_CfgArrPosition);
static void DCM_MessageUpdateMultiplex_47(uint8 U8_CfgArrPosition);

static uint8 DCM_AU8_EventMultiplexActiveStatus[DCM_SIZEOF_EVENT_MULTIPLEXES];
static uint8 DCM_AU8_SystemMultiplexActiveStatus[DCM_SIZEOF_SYSTEM_MULTIPLEXES];
static Type_SwcApplTpms_stMessageCan DCM_S_LastEventDataReceivedOnMultiplex[DCM_SIZEOF_EVENT_MULTIPLEXES];
static Type_SwcApplTpms_stMessageCan DCM_S_LastSystemDataReceivedOnMultiplex[DCM_SIZEOF_SYSTEM_MULTIPLEXES];

static void DCM_MessageUpdateMultiplex_00(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_00.u8_MultiplexID = DCM_MULTIPLEX_0;
  DCM_InvIf_RFTimeStampGetValue(&StructAccesMultiplex_00.u8_RFTelegramTimeStamp[0]);
  DCM_InvIf_LastRxIDGetValue(&StructAccesMultiplex_00.u8_IDLastRF[0]);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_00.MessageMultiplex_00;
}

static void DCM_MessageUpdateMultiplex_01(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_01.u8_MultiplexID = DCM_MULTIPLEX_1;
  StructAccesMultiplex_01.u8_PositionRecCntFL = DCM_InvIf_WheelPosReceptionCounter(0);
  StructAccesMultiplex_01.u8_PositionRecCntFR = DCM_InvIf_WheelPosReceptionCounter(1);
  StructAccesMultiplex_01.u8_PositionRecCntRL = DCM_InvIf_WheelPosReceptionCounter(2);
  StructAccesMultiplex_01.u8_PositionRecCntRR = DCM_InvIf_WheelPosReceptionCounter(3);

#ifdef DEBUG_AUTOLOCATION
  DCM_InvIf_ulDebugRfTimeStampGetValue(&StructAccesMultiplex_01.u8_ulDebugRfTimeStamp[0]);
#endif

  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_01.MessageMultiplex_01;
}

static void DCM_MessageUpdateMultiplex_02(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_02.u8_MultiplexID = DCM_MULTIPLEX_2;
  StructAccesMultiplex_02.u8_AbsLinCntFL = DCM_InvIf_AbsLinGetCntValueFL();
  StructAccesMultiplex_02.u8_AbsLinCntFR = DCM_InvIf_AbsLinGetCntValueFR();
  StructAccesMultiplex_02.u8_AbsLinCntRL = DCM_InvIf_AbsLinGetCntValueRL();
  StructAccesMultiplex_02.u8_AbsLinCntRR = DCM_InvIf_AbsLinGetCntValueRR();
#ifdef DEBUG_AUTOLOCATION
  DCM_InvIf_ulAbsTimeStampGetOldestValue(&StructAccesMultiplex_02.u8_ulTimePreviousfromPutABS[0]);
#endif

  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_02.MessageMultiplex_02;
}

static void DCM_MessageUpdateMultiplex_03(uint8 U8_CfgArrPosition){
  uint8 U8_ZomPositionCurrentID;
  U8_ZomPositionCurrentID = DCM_InvIf_ZomPosCurrIDGetValue();
  StructAccesMultiplex_03.u8_MultiplexID = DCM_MULTIPLEX_3;
  StructAccesMultiplex_03.u8_AbsCorrCntFL = DCM_InvIf_AbsCorrGetCntValueFL(U8_ZomPositionCurrentID);
  StructAccesMultiplex_03.u8_AbsCorrCntFR = DCM_InvIf_AbsCorrGetCntValueFR(U8_ZomPositionCurrentID);
  StructAccesMultiplex_03.u8_AbsCorrCntRL = DCM_InvIf_AbsCorrGetCntValueRL(U8_ZomPositionCurrentID);
  StructAccesMultiplex_03.u8_AbsCorrCntRR = DCM_InvIf_AbsCorrGetCntValueRR(U8_ZomPositionCurrentID);
  StructAccesMultiplex_03.u8_AbsLinAngleFL = DCM_InvIf_AbsLinAngle_FL_GetHistoryValue();
  StructAccesMultiplex_03.u8_AbsLinAngleFR = DCM_InvIf_AbsLinAngle_FR_GetHistoryValue();
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_03.MessageMultiplex_03;
}

static void DCM_MessageUpdateMultiplex_04(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_04.u8_MultiplexID = DCM_MULTIPLEX_4;
  DCM_InvIf_RawRfTelGetValue( DCM__BUFFER_READ_START_MSG4, DCM__BUFFER_READ_LENGTH_MSG4, &StructAccesMultiplex_04.u8_RfTelByteValue[0]);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_04.MessageMultiplex_04;
}

static void DCM_MessageUpdateMultiplex_05(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_05.u8_MultiplexID = DCM_MULTIPLEX_5;
  DCM_InvIf_RawRfTelGetValue( DCM__BUFFER_READ_START_MSG5, DCM__BUFFER_READ_LENGTH_MSG5, &StructAccesMultiplex_05.u8_RfTelByteValue[0]);

#ifdef DEBUG_AUTOLOCATION
  StructAccesMultiplex_05.u8_ucABSRef_0_0 = DCM_InvIf_GetNumberOfE7withInvalidTs();
  StructAccesMultiplex_05.u8_ucABSRef_0_1 = DCM_InvIf_GetNumberOfE7withOutdatedTs();
  StructAccesMultiplex_05.u8_ucABSRef_0_2 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_0, 2);
#endif

  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_05.MessageMultiplex_05;
}

#ifdef DEBUG_AUTOLOCATION
static void DCM_MessageUpdateMultiplex_06(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_06.u8_MultiplexID = DCM_MULTIPLEX_6;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_0, 0,&StructAccesMultiplex_06.u8_ushMVdN_0_0[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_0, 1,&StructAccesMultiplex_06.u8_ushMVdN_0_1[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_0, 2,&StructAccesMultiplex_06.u8_ushMVdN_0_2[0]);
  StructAccesMultiplex_06.u8_ucABSRef_0_3 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_0,3);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_06.MessageMultiplex_06;
}

static void DCM_MessageUpdateMultiplex_07(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_07.u8_MultiplexID = DCM_MULTIPLEX_7;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_0, 3,&StructAccesMultiplex_07.u8_ushMVdN_0_3[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_1, 0,&StructAccesMultiplex_07.u8_ushMVdN_1_0[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_1, 1,&StructAccesMultiplex_07.u8_ushMVdN_1_1[0]);
  StructAccesMultiplex_07.u8_ucABSRef_1_0 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_1, 0);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_07.MessageMultiplex_07;
}

static void DCM_MessageUpdateMultiplex_08(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_08.u8_MultiplexID = DCM_MULTIPLEX_8;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_1, 2,&StructAccesMultiplex_08.u8_ushMVdN_1_2[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_1, 3,&StructAccesMultiplex_08.u8_ushMVdN_1_3[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_2, 0,&StructAccesMultiplex_08.u8_ushMVdN_2_0[0]);
  StructAccesMultiplex_08.u8_ucABSRef_1_1 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_1, 1);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_08.MessageMultiplex_08;
}

static void DCM_MessageUpdateMultiplex_09(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_09.u8_MultiplexID = DCM_MULTIPLEX_9;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_2, 1,&StructAccesMultiplex_09.u8_ushMVdN_2_1[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_2, 2,&StructAccesMultiplex_09.u8_ushMVdN_2_2[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_2, 3,&StructAccesMultiplex_09.u8_ushMVdN_2_3[0]);
  StructAccesMultiplex_09.u8_ucABSRef_1_2 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_1, 2);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_09.MessageMultiplex_09;
}

static void DCM_MessageUpdateMultiplex_10(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_10.u8_MultiplexID = DCM_MULTIPLEX_10;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_3, 0,&StructAccesMultiplex_10.u8_ushMVdN_3_0[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_3, 1,&StructAccesMultiplex_10.u8_ushMVdN_3_1[0]);
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_3, 2,&StructAccesMultiplex_10.u8_ushMVdN_3_2[0]);
  StructAccesMultiplex_10.u8_ucABSRef_1_3 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_1, 3);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_10.MessageMultiplex_10;
}

static void DCM_MessageUpdateMultiplex_11(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_11.u8_MultiplexID = DCM_MULTIPLEX_11;
  DCM_InvIf_ushMVdNfromZOM(DMC__ZOM_POSITION_3, 3,&StructAccesMultiplex_11.u8_ushMVdN_3_3[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_0, 0,&StructAccesMultiplex_11.u8_ushMVdN2_0_0[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_0, 1,&StructAccesMultiplex_11.u8_ushMVdN2_0_1[0]);
  StructAccesMultiplex_11.u8_ucABSRef_2_0 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_2, 0);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_11.MessageMultiplex_11;
}

static void DCM_MessageUpdateMultiplex_12(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_12.u8_MultiplexID = DCM_MULTIPLEX_12;
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_0, 2,&StructAccesMultiplex_12.u8_ushMVdN2_0_2[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_0, 3,&StructAccesMultiplex_12.u8_ushMVdN2_0_3[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_1, 0,&StructAccesMultiplex_12.u8_ushMVdN2_1_0[0]);
  StructAccesMultiplex_12.u8_ucABSRef_2_1 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_2, 1);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_12.MessageMultiplex_12;
}

static void DCM_MessageUpdateMultiplex_13(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_13.u8_MultiplexID = DCM_MULTIPLEX_13;
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_1, 1,&StructAccesMultiplex_13.u8_ushMVdN2_1_1[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_1, 2,&StructAccesMultiplex_13.u8_ushMVdN2_1_2[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_1, 3,&StructAccesMultiplex_13.u8_ushMVdN2_1_3[0]);
  StructAccesMultiplex_13.u8_ucABSRef_2_2 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_2, 2);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_13.MessageMultiplex_13;
}

static void DCM_MessageUpdateMultiplex_14(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_14.u8_MultiplexID = DCM_MULTIPLEX_14;
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_2, 0,&StructAccesMultiplex_14.u8_ushMVdN2_2_0[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_2, 1,&StructAccesMultiplex_14.u8_ushMVdN2_2_1[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_2, 2,&StructAccesMultiplex_14.u8_ushMVdN2_2_2[0]);
  StructAccesMultiplex_14.u8_ucABSRef_2_3 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_2, 3);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_14.MessageMultiplex_14;
}

static void DCM_MessageUpdateMultiplex_15(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_15.u8_MultiplexID = DCM_MULTIPLEX_15;
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_2, 3,&StructAccesMultiplex_15.u8_ushMVdN2_2_3[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_3, 0,&StructAccesMultiplex_15.u8_ushMVdN2_3_0[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_3, 1,&StructAccesMultiplex_15.u8_ushMVdN2_3_1[0]);
  StructAccesMultiplex_15.u8_ucABSRef_3_0 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_3, 0);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_15.MessageMultiplex_15;
}

static void DCM_MessageUpdateMultiplex_16(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_16.u8_MultiplexID = DCM_MULTIPLEX_16;
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_3, 2,&StructAccesMultiplex_16.u8_ushMVdN2_3_2[0]);
  DCM_InvIf_ushMVdN2fromZOM(DMC__ZOM_POSITION_3, 3,&StructAccesMultiplex_16.u8_ushMVdN2_3_3[0]);
  StructAccesMultiplex_16.u8_ucABSRef_3_1 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_3, 1);
  StructAccesMultiplex_16.u8_ucABSRef_3_2 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_3, 2);
  StructAccesMultiplex_16.u8_ucABSRef_3_3 = DCM_InvIf_ucABSReffromZOM(DMC__ZOM_POSITION_3, 3);

  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_16.MessageMultiplex_16;
}

static void DCM_MessageUpdateMultiplex_17(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_17.u8_MultiplexID = DCM_MULTIPLEX_17;
  StructAccesMultiplex_17.u8_ucAlgoTelEvtCnt_0 = DCM_InvIf_ucAlgoTelEvtCntfromZOM(DMC__ZOM_POSITION_0);
  StructAccesMultiplex_17.u8_ucAlgoTelEvtCnt_1 = DCM_InvIf_ucAlgoTelEvtCntfromZOM(DMC__ZOM_POSITION_1);
  StructAccesMultiplex_17.u8_ucAlgoTelEvtCnt_2 = DCM_InvIf_ucAlgoTelEvtCntfromZOM(DMC__ZOM_POSITION_2);
  StructAccesMultiplex_17.u8_ucAlgoTelEvtCnt_3 = DCM_InvIf_ucAlgoTelEvtCntfromZOM(DMC__ZOM_POSITION_3);
  DCM_InvIf_ulAbsTimeStampGetNewestValue(&StructAccesMultiplex_17.u8_ulTimeNextfromPutABS[0]);
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_17.MessageMultiplex_17;
}
#endif

static void DCM_MessageUpdateMultiplex_20(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_20.u8_MultiplexID = DCM_MULTIPLEX_20;
  StructAccesMultiplex_20.u8_PressAmbient =  DCM_InvIf_PressAmbientGetValue();
  StructAccesMultiplex_20.u8_TempAmbient = DCM_InvIf_TempAmbientGetValue();
  StructAccesMultiplex_20.u8_SpeedVehicleMsbits = (uint8)( 0x00FFu & ( DCM_InvIf_SpeedVehicGetValue()>> 2 ) );
  StructAccesMultiplex_20.u2_SpeedVehicleLsbits = (uint8)( 0x0003u & ( DCM_InvIf_SpeedVehicGetValue() ) );
  StructAccesMultiplex_20.u4_ZomCurrIDPosition = (uint8)(0x0Fu & DCM_InvIf_ZomPosCurrIDGetValue());
  StructAccesMultiplex_20.u8_WheelPosCurrID = DCM_InvIf_WheelPosCurrIDGetValue();
  StructAccesMultiplex_20.u8_AbsLinAngleRL = DCM_InvIf_AbsLinAngle_RL_GetHistoryValue();
  StructAccesMultiplex_20.u8_AbsLinAngleRR = DCM_InvIf_AbsLinAngle_RR_GetHistoryValue();
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_20.MessageMultiplex_20;
}

static void DCM_MessageUpdateMultiplex_21(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_21.u8_MultiplexID = DCM_MULTIPLEX_21;
  StructAccesMultiplex_21.u8_RxRSSIRawValue = DCM_InvIf_RawRSSIGetValue();
  StructAccesMultiplex_21.u8_TelTypeCurrID = DCM_InvIf_TelTypeCurrIDGetValue();
  StructAccesMultiplex_21.u8_PressLastRx = DCM_InvIf_PressLastRxIDGetValue();
  StructAccesMultiplex_21.s8_TempLastRx = DCM_InvIf_TempLastRxIDGetValue();
  DCM_InvIf_RxStatusFieldGetValue(&StructAccesMultiplex_21.u8_RxStatusFields[0]);
  StructAccesMultiplex_21.u8_RecEvent = DCM_InvIf_RecEventGetCntValue();
  DCM_S_LastEventDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_21.MessageMultiplex_21;
}

static void DCM_MessageUpdateMultiplex_22(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_22.u8_MultiplexID = DCM_MULTIPLEX_22;
  StructAccesMultiplex_22.u8_NoiseLevel = DCM_InvIf_NoiseLevelGetValue();
  StructAccesMultiplex_22.u8_TPMSStateMsbits = (uint8)(0x00FFu & (DCM_InvIf_TPMSStateGetStatus()>>8 ) );
  StructAccesMultiplex_22.u8_TPMSStateLsbits = (uint8)(0x00FFu & DCM_InvIf_TPMSStateGetStatus() );
  StructAccesMultiplex_22.u8_WAllocTimeoutCnt = DCM_InvIf_AutoLocGetTimeoutCntValue();
  StructAccesMultiplex_22.u4_AbsResetCnt = (uint8)(0x0Fu & DCM_InvIf_AbsGetResetCntValue() );
  StructAccesMultiplex_22.u4_RevGearCnt = (uint8)(0x0Fu & DCM_InvIf_GearReverseGetCntValue() );
  StructAccesMultiplex_22.u4_StopEventCnt = (uint8)(0x0Fu & DCM_InvIf_StopEventsGetCntValue() );
  StructAccesMultiplex_22.u4_VehiculeStatus = (uint8)(0x0Fu & DCM_InvIf_VehicleStatusGetValue() );
  StructAccesMultiplex_22.u8_PressRefCurrID = DCM_InvIf_PressRefCurrIDGetValue();
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_22.MessageMultiplex_22;
}

static void DCM_MessageUpdateMultiplex_23(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_23.u8_MultiplexID = DCM_MULTIPLEX_23;
  StructAccesMultiplex_23.u4_TempWarnStatus = (uint8)(0x0Fu & DCM_InvIf_TempWarnGetStatus() );
  StructAccesMultiplex_23.u1_RFJammerStatus = (uint8)(0x01u & DCM_InvIf_RfJammerGetStatus() );
  StructAccesMultiplex_23.u8_tCmp_AxImb = (uint8)(0xFFu & DCM_InvIf_AxImbWarnSetThresholdGetValue() );
  StructAccesMultiplex_23.u8_tCmp_DHW = (uint8)(0xFFu & DCM_InvIf_DHWWarnSetThresholdGetValue() );
  StructAccesMultiplex_23.u8_tCmp_EuF = (uint8)(0xFFu & DCM_InvIf_EuFWarnSetThresholdGetValue() );
  StructAccesMultiplex_23.u8_tCmp_FT = (uint8)(0xFFu & DCM_InvIf_FTWarnSetThresholdGetValue() );
  StructAccesMultiplex_23.u8_tCmp_HardTDR = (uint8)(0xFFu & DCM_InvIf_HardTDRWarnSetThresholdGetValue() );
  StructAccesMultiplex_23.u8_DebugAllocType = (uint8)(0xFFu & DCM_InvIf_DebugAllocType());
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_23.MessageMultiplex_23;
}

static void DCM_MessageUpdateMultiplex_24(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_24.u8_MultiplexID = DCM_MULTIPLEX_24;
  StructAccesMultiplex_24.u8_tCmp_HiP = DCM_InvIf_HiPWarnSetThresholdGetValue();
  StructAccesMultiplex_24.u8_tCmp_LowP = DCM_InvIf_LowPWarnSetThresholdGetValue();
  StructAccesMultiplex_24.u8_tCmp_PminDR = DCM_InvIf_PminDRWarnSetThresholdGetValue();
  StructAccesMultiplex_24.u8_VehDirection = DCM_InvIf_VehDirectionGetValue();
  StructAccesMultiplex_24.u8_AllRecEventCnt = DCM_InvIf_AllReceivedTelegGetValue();
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_24.MessageMultiplex_24;
}

#ifdef NVM_DEBUG
static void DCM_MessageUpdateMultiplex_25(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_25.u8_MultiplexID = DCM_MULTIPLEX_25;
  DCM_InvIf_NvmBlockConsistence(&StructAccesMultiplex_25.u8_NvM_uiNvmBlockConsistence[0]);
  StructAccesMultiplex_25.u8_NvM_WriteReturn = DCM_InvIf_NvmWriteResult();
  StructAccesMultiplex_25.u8_NvM_ReadReturn = DCM_InvIf_NvmReadResult();
  StructAccesMultiplex_25.u8_NvM_ucABSTicksFrontAx = DCM_InvIf_DebugABSTicksFront();
  StructAccesMultiplex_25.u8_NvM_ucABSTicksRearAx = DCM_InvIf_DebugABSTicksRear();
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_25.MessageMultiplex_25;
}
#endif

static void DCM_MessageUpdateMultiplex_30(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_30.u8_MultiplexID = DCM_MULTIPLEX_30;
  DCM_InvIf_HistoryIDReadValue( DMC__HISTORY_POSITION_0, &StructAccesMultiplex_30.u8_HistoryID0[0]);
  DCM_InvIf_HistoryWPReadValue(DMC__HISTORY_POSITION_0, &StructAccesMultiplex_30.u8_HistoryWP0);
  StructAccesMultiplex_30.u8_NoRxCntHistoryID0 = DCM_InvIf_RecepMissedGetCntValue(DMC__HISTORY_POSITION_0);
  DCM_InvIf_WarnVectReadHistoryStatus(DMC__HISTORY_POSITION_0, &StructAccesMultiplex_30.u8_WarnVeCtorHist0);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_30.MessageMultiplex_30;
}

static void DCM_MessageUpdateMultiplex_31(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_31.u8_MultiplexID = DCM_MULTIPLEX_31;
  DCM_InvIf_HistoryIDReadValue( DMC__HISTORY_POSITION_1, &StructAccesMultiplex_31.u8_HistoryID1[0]);
  DCM_InvIf_HistoryWPReadValue(DMC__HISTORY_POSITION_1, &StructAccesMultiplex_31.u8_HistoryWP1);
  StructAccesMultiplex_31.u8_NoRxCntHistoryID1 = DCM_InvIf_RecepMissedGetCntValue(DMC__HISTORY_POSITION_1);
  DCM_InvIf_WarnVectReadHistoryStatus(DMC__HISTORY_POSITION_1, &StructAccesMultiplex_31.u8_WarnVeCtorHist1);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_31.MessageMultiplex_31;
}

static void DCM_MessageUpdateMultiplex_32(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_32.u8_MultiplexID = DCM_MULTIPLEX_32;
  DCM_InvIf_HistoryIDReadValue( DMC__HISTORY_POSITION_2, &StructAccesMultiplex_32.u8_HistoryID2[0]);
  DCM_InvIf_HistoryWPReadValue(DMC__HISTORY_POSITION_2, &StructAccesMultiplex_32.u8_HistoryWP2);
  StructAccesMultiplex_32.u8_NoRxCntHistoryID2 = DCM_InvIf_RecepMissedGetCntValue(DMC__HISTORY_POSITION_2);
  DCM_InvIf_WarnVectReadHistoryStatus(DMC__HISTORY_POSITION_2, &StructAccesMultiplex_32.u8_WarnVeCtorHist2);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_32.MessageMultiplex_32;
}

static void DCM_MessageUpdateMultiplex_33(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_33.u8_MultiplexID = DCM_MULTIPLEX_33;
  DCM_InvIf_HistoryIDReadValue( DMC__HISTORY_POSITION_3, &StructAccesMultiplex_33.u8_HistoryID3[0]);
  DCM_InvIf_HistoryWPReadValue(DMC__HISTORY_POSITION_3, &StructAccesMultiplex_33.u8_HistoryWP3);
  StructAccesMultiplex_33.u8_NoRxCntHistoryID3 = DCM_InvIf_RecepMissedGetCntValue(DMC__HISTORY_POSITION_3);
  DCM_InvIf_WarnVectReadHistoryStatus(DMC__HISTORY_POSITION_3, &StructAccesMultiplex_33.u8_WarnVeCtorHist3);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_33.MessageMultiplex_33;
}

static void DCM_MessageUpdateMultiplex_40(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_40.u8_MultiplexID = DCM_MULTIPLEX_40;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_0, &StructAccesMultiplex_40.u8_ZomWuID0[0]);
  StructAccesMultiplex_40.u8_ZomAutolocStatus0 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_0);
  StructAccesMultiplex_40.u8_ZomTelCnt0 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_0);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_40.MessageMultiplex_40;
}

static void DCM_MessageUpdateMultiplex_41(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_41.u8_MultiplexID = DCM_MULTIPLEX_41;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_1, &StructAccesMultiplex_41.u8_ZomWuID1[0]);
  StructAccesMultiplex_41.u8_ZomAutolocStatus1 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_1);
  StructAccesMultiplex_41.u8_ZomTelCnt1 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_1);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_41.MessageMultiplex_41;
}

static void DCM_MessageUpdateMultiplex_42(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_42.u8_MultiplexID = DCM_MULTIPLEX_42;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_2, &StructAccesMultiplex_42.u8_ZomWuID2[0]);
  StructAccesMultiplex_42.u8_ZomAutolocStatus2 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_2);
  StructAccesMultiplex_42.u8_ZomTelCnt2 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_2);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_42.MessageMultiplex_42;
}

static void DCM_MessageUpdateMultiplex_43(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_43.u8_MultiplexID = DCM_MULTIPLEX_43;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_3, &StructAccesMultiplex_43.u8_ZomWuID3[0]);
  StructAccesMultiplex_43.u8_ZomAutolocStatus3 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_3);
  StructAccesMultiplex_43.u8_ZomTelCnt3 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_3);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_43.MessageMultiplex_43;
}

static void DCM_MessageUpdateMultiplex_44(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_44.u8_MultiplexID = DCM_MULTIPLEX_44;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_4, &StructAccesMultiplex_44.u8_ZomWuID4[0]);
  StructAccesMultiplex_44.u8_ZomAutolocStatus4 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_4);
  StructAccesMultiplex_44.u8_ZomTelCnt4 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_4);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_44.MessageMultiplex_44;
}

static void DCM_MessageUpdateMultiplex_45(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_45.u8_MultiplexID = DCM_MULTIPLEX_45;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_5, &StructAccesMultiplex_45.u8_ZomWuID5[0]);
  StructAccesMultiplex_45.u8_ZomAutolocStatus5 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_5);
  StructAccesMultiplex_45.u8_ZomTelCnt5 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_5);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_45.MessageMultiplex_45;
}

static void DCM_MessageUpdateMultiplex_46(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_46.u8_MultiplexID = DCM_MULTIPLEX_46;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_6, &StructAccesMultiplex_46.u8_ZomWuID6[0]);
  StructAccesMultiplex_46.u8_ZomAutolocStatus6 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_6);
  StructAccesMultiplex_46.u8_ZomTelCnt6 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_6);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_46.MessageMultiplex_46;
}

static void DCM_MessageUpdateMultiplex_47(uint8 U8_CfgArrPosition){
  StructAccesMultiplex_47.u8_MultiplexID = DCM_MULTIPLEX_47;
  DCM_InvIf_ZomWuIDGetFromMemory(DMC__ZOM_POSITION_7, &StructAccesMultiplex_47.u8_ZomWuID7[0]);
  StructAccesMultiplex_47.u8_ZomAutolocStatus7 = DCM_InvIf_ZomStatusGetFromMemory(DMC__ZOM_POSITION_7);
  StructAccesMultiplex_47.u8_ZomTelCnt7 = DCM_InvIf_ZomTelCntGetFromMemory(DMC__ZOM_POSITION_7);
  DCM_S_LastSystemDataReceivedOnMultiplex[U8_CfgArrPosition] = DCM_S_MultiplexMessageIDs.DCM_S_MultiPlexMess_47.MessageMultiplex_47;
}

void DCM_EventDataUpdateOnRx(void){
  DCM_EventDataPutToQueue();
}

static void DCM_EventDataPutToQueue(void){
  uint8 U8_LocalCnt;
  if((0u != DCH_IsCanDebugEnabled()) && (0u != DCH_SubmultiplexConfigGetStatus())){
   for( U8_LocalCnt = 0; U8_LocalCnt < DCM_SIZEOF_EVENT_MULTIPLEXES; U8_LocalCnt++ ){
      DCM_AS_ConfigureEventMultiplexMsg[U8_LocalCnt].DCM_pfnBuildMsg(U8_LocalCnt);
      DCM_PutEventData2Buffer( DCM_S_LastEventDataReceivedOnMultiplex[U8_LocalCnt]);
   }
  }
  else{
  }
}

void DCM_CyclicDebugSystemDataUpdate(void){
  DCM_SystemDataPutToQueue();
}

static void DCM_SystemDataPutToQueue(void){
  uint8 U8_LocalCnt;
  if((0u != DCH_IsCanDebugEnabled()) && (0u != DCH_SubmultiplexConfigGetStatus())){
   for( U8_LocalCnt = 0; U8_LocalCnt < DCM_SIZEOF_SYSTEM_MULTIPLEXES; U8_LocalCnt++ ){
      DCM_AS_ConfigureSystemMultiplexMsg[U8_LocalCnt].DCM_pfnBuildMsg(U8_LocalCnt);
      DCM_PutSystemData2Buffer( DCM_S_LastSystemDataReceivedOnMultiplex[U8_LocalCnt]);
   }
  }
  else{
  }
}

uint8 DCM_InvIf_PressRefCurrIDGetValue(void){
  return ucGetPSollCS(DCM_InvIf_ZomPosCurrIDGetValue());
}

boolean DCM_InvIf_RfJammerGetStatus(void){
  return GETbHfIntLatchEE();
}

uint8 DCM_InvIf_TempWarnGetStatus(void){
  return (uint8)(GETucReHeatUpStatusEE() & (uint8)0x0F);
}

static void DCM_StoreMaxMultiplexEventNr(uint8 U8_CurrentMultiplexNr){
  if( DCM_U8_EventDataMaxMultiplexNr < U8_CurrentMultiplexNr ){
    DCM_U8_EventDataMaxMultiplexNr = U8_CurrentMultiplexNr;
  }
  else{}
}

static void DCM_StoreMaxMultiplexSystemNr(uint8 U8_CurrentMultiplexNr){
  if( DCM_U8_SystemDataMaxMultiplexNr < U8_CurrentMultiplexNr ){
    DCM_U8_SystemDataMaxMultiplexNr = U8_CurrentMultiplexNr;
  }
  else{}
}

void DCM_InitCanDebug(void){
  uint16 ArrayCnt,StructureCnt;
  DCM_U8_EventDataMaxMultiplexNr = 0;
  DCM_U8_SystemDataMaxMultiplexNr = 0;
  u8_EnvReadCnt = 0;
  u8_EnvWriteCnt = 0;
  u8_SysReadCnt = 0;
  u8_SysWriteCnt = 0;
  bo_StructSystemMultiLast = FALSE;

  for( ArrayCnt = 0; ArrayCnt < sizeof(DCM_StructMultiplexMessageIDs); ArrayCnt++){
    *((uint8*)&DCM_S_MultiplexMessageIDs + ArrayCnt) = 0;
  }
  for( ArrayCnt = 0; ArrayCnt< SIZE_ARRAY(S_HufSysMsgBuf, Type_SwcApplTpms_stMessageCan); ArrayCnt++ ){
   for( StructureCnt = 0; StructureCnt < sizeof(Type_SwcApplTpms_stMessageCan); StructureCnt++ ){
      *((uint8*)&S_HufSysMsgBuf[ArrayCnt] + StructureCnt ) = 0;
   }
  }
  for( ArrayCnt = 0; ArrayCnt < SIZE_ARRAY(S_HufEnvMsgBuf, Type_SwcApplTpms_stMessageCan); ArrayCnt++ ){
   for( StructureCnt = 0; StructureCnt < sizeof(Type_SwcApplTpms_stMessageCan); StructureCnt++ ){
      *((uint8*)&S_HufEnvMsgBuf[ArrayCnt] + StructureCnt ) = 0;
   }
  }
}

static void DCM_PutEventData2Buffer(Type_SwcApplTpms_stMessageCan S_EnvDataMultiplex){
  if(FALSE != DCH_MultiplexMsgGetActiveStatus(S_EnvDataMultiplex.ucData0)){
   if(u8_EnvWriteCnt >= DCM_MAX_SIZE_ENV_BUF){
      u8_EnvWriteCnt = 0;
   }
    DCM_StoreMaxMultiplexEventNr(S_EnvDataMultiplex.ucData0);
    S_HufEnvMsgBuf[u8_EnvWriteCnt] = S_EnvDataMultiplex;
   u8_EnvWriteCnt++;
  }
  else{
  }
}

static void DCM_PutSystemData2Buffer(Type_SwcApplTpms_stMessageCan S_SysDataMultiplex){
  if(FALSE != DCH_MultiplexMsgGetActiveStatus(S_SysDataMultiplex.ucData0)){
   if(u8_SysWriteCnt >= DCM_MAX_SIZE_SYS_BUF){
      u8_SysWriteCnt = 0;
   }
    DCM_StoreMaxMultiplexSystemNr(S_SysDataMultiplex.ucData0);
    S_HufSysMsgBuf[u8_SysWriteCnt] = S_SysDataMultiplex;
   u8_SysWriteCnt++;

  }
  else{
  }
}

void DCM_DataToTransmitOnCAN(Type_SwcApplTpms_stMessageCan* spCAN_Message){
  if( FALSE != bo_StructSystemMultiLast){
   boolean EventDataReturnValue;
    EventDataReturnValue = DCM_EventDataGetFromBuffer(spCAN_Message);
   if(FALSE == EventDataReturnValue){
      DCM_SystemDataGetFromBuffer(spCAN_Message);
   }
  }
  else{
    DCM_SystemDataGetFromBuffer(spCAN_Message);
  }
}

static boolean DCM_EventDataGetFromBuffer(Type_SwcApplTpms_stMessageCan* tHufDisplay){
  boolean ucRet;

  if(u8_EnvWriteCnt != u8_EnvReadCnt){
   if(u8_EnvReadCnt >= DCM_MAX_SIZE_ENV_BUF){
      u8_EnvReadCnt = 0;
   }
   else{
   }
    *tHufDisplay = S_HufEnvMsgBuf[u8_EnvReadCnt];
   u8_EnvReadCnt++;
   ucRet = TRUE;
  }
  else
  {
   ucRet = FALSE;
  }
  return ucRet;
}

static void DCM_SystemDataGetFromBuffer(Type_SwcApplTpms_stMessageCan* tHufDisplay){
  if(u8_SysReadCnt >= DCM_MAX_SIZE_SYS_BUF){
   u8_SysReadCnt = 0;
  }

  *tHufDisplay = S_HufSysMsgBuf[u8_SysReadCnt];

  if( DCM_U8_SystemDataMaxMultiplexNr == S_HufSysMsgBuf[u8_SysReadCnt].ucData0){
   bo_StructSystemMultiLast = TRUE;
  }
  else{
   bo_StructSystemMultiLast = FALSE;
  }

  u8_SysReadCnt++;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

