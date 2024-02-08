#pragma once
/******************************************************************************/
/* File   : iTpms_Interface.hpp                                               */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
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
#define MAX_SIZE_WS_TELEGRAM                                                 16U
#define CAN_MSG_DEBUG_REQ                                                     0U
#define CAN_MSG_DEBUG_RES                                                     1U
#define CAN_MSG_Debug_CYCLIC                                                  2U
#define CAN_MSG_HMI_CYCLIC                                                    3U
#define CAN_MSG_HMI_TEMP_CYCLIC                                               4U
#define CAN_MSG_TPMS_Software_ID_CYCLIC                                       5U
#define NVM_BLOCK_SIZE                                                        4U
#define NVM_BLOCK_TYPE                                                    uint32
#define NVM_HUF_DATA_MAX_BYTE_SIZE                                          400U
#define NVM_MAX_CATEGORYS                                                    10U
#define NVM_MAX_AMOUNT_BLOCKS        (NVM_HUF_DATA_MAX_BYTE_SIZE/NVM_BLOCK_SIZE)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      SwcApplTpms_eError_WS_LIFE_TIME_FL_CNT_LOW
   ,  SwcApplTpms_eError_WS_LIFE_TIME_FR_CNT_LOW
   ,  SwcApplTpms_eError_WS_LIFE_TIME_RR_CNT_LOW
   ,  SwcApplTpms_eError_WS_LIFE_TIME_RL_CNT_LOW
   ,  SwcApplTpms_eError_WS_DEFECT_FL
   ,  SwcApplTpms_eError_WS_DEFECT_FR
   ,  SwcApplTpms_eError_WS_DEFECT_RR
   ,  SwcApplTpms_eError_WS_DEFECT_RL
   ,  SwcApplTpms_eError_WS_DEFECT_UNKNOWN_POS
   ,  SwcApplTpms_eError_WS_MISSING_FL
   ,  SwcApplTpms_eError_WS_MISSING_FR
   ,  SwcApplTpms_eError_WS_MISSING_RR
   ,  SwcApplTpms_eError_WS_MISSING_RL
   ,  SwcApplTpms_eError_WS_MISSING_UNKNOWN_POS
   ,  SwcApplTpms_eError_WS_OVER_TEMP_FL
   ,  SwcApplTpms_eError_WS_OVER_TEMP_FR
   ,  SwcApplTpms_eError_WS_OVER_TEMP_RR
   ,  SwcApplTpms_eError_WS_OVER_TEMP_RL
   ,  SwcApplTpms_eError_AXLE_LOCATE_FAIL
   ,  SwcApplTpms_eError_NO_QUALIFIED_SENSOR_SIGNALS
   ,  SwcApplTpms_eError_DETECTED_TOO_MANY_SENSORS
   ,  SwcApplTpms_eError_NOT_FUNCTIONING_DUE_TO_ECU_INTERNAL_FAULT
   ,  SwcApplTpms_eError_WS_MISSING_DURING_CONTINUOUS_INVALID_SPEED
   ,  SwcApplTpms_eError_RF_INTERFERENCE
   ,  SwcApplTpms_eError_AUTOLOCATION_FAILED
   ,  SwcApplTpms_eError_MAX_NUMBER
}Type_SwcApplTpms_eErrors;

typedef struct{
   uint8 ucaApplVersionHuf[9];
   uint8 ucaApplVersionCst[7];
   uint8 ucaApplVersionCDD[20];
   uint8 ucaCompilerName[6];
   uint8 ucaCompilerVersion[6];
   uint8 ucaBuild_Date[20];
}Type_SwcApplTpms_stVersion;

typedef struct{
   uint32 ulRxTimeStamp;
   uint16 uiRxRSSI;
   uint8  ucaTelegram[MAX_SIZE_WS_TELEGRAM];
}Type_SwcApplTpms_stTelegramWS;

typedef struct{
   uint16  uiVehSpeed;
   uint8   ucIgnition;
   uint8   ucAmbTemperature;
   uint8   ucAthmosPressure;
   uint8   ucVehDirection;
   boolean bECU_Fault;
   uint16  uiNvmBlockConsistence;
   uint16  uiNoiseRSSI;
   boolean bRoadMode;
}Type_SwcApplTpms_stStatusBody;

typedef struct{
   bitfield bTPS_FR                  : 3;
   bitfield bTPV_FR                  : 1;
   bitfield bTPS_FL                  : 3;
   bitfield bTPV_FL                  : 1;
   bitfield bTPS_RR                  : 3;
   bitfield bTPV_RR                  : 1;
   bitfield bTPS_RL                  : 3;
   bitfield bTPV_RL                  : 1;
   bitfield ucTP_FL                  : 8;
   bitfield ucTP_FR                  : 8;
   bitfield ucTP_RL                  : 8;
   bitfield ucTP_RR                  : 8;
   bitfield bTPMS_Locate_Status      : 1;
   bitfield bTPMS_Learn_Status       : 1;
   bitfield b6Gap1                   : 6;
   bitfield bTMP_S                   : 4;
   bitfield bTemp_Warning_FL         : 1;
   bitfield bTemp_Warning_FR         : 1;
   bitfield bTemp_Warning_RL         : 1;
   bitfield bTemp_Warning_RR         : 1;
}Type_SwcApplTpms_stPressure;

typedef struct{
   uint8  u8MajorRelease;
   uint8  u8MinorRelease;
   uint16 u16MicroRelease;
   uint32 u32Crc;
}Type_SwcApplTpms_stIdSoftware;

typedef struct{
   uint8 ucTT_FL;
   uint8 ucTT_FR;
   uint8 ucTT_RL;
   uint8 ucTT_RR;
   uint8 ucRP_FL;
   uint8 ucRP_FR;
   uint8 ucRP_RL;
   uint8 ucRP_RR;
}Type_SwcApplTpms_stTempAndRefPress;

typedef struct{
   uint32 ulAbsTimeStamp;
   uint16 uiPulseCtrFL;
   uint16 uiPulseCtrFR;
   uint16 uiPulseCtrRL;
   uint16 uiPulseCtrRR;
   uint16 uiSimTimeStamp;
   uint8  ucAge;
}Type_SwcApplTpms_stWheelPulseStamped;

typedef struct{
   uint8 lptru8Data0;
   uint8 lptru8Data1;
   uint8 lptru8Data2;
   uint8 lptru8Data3;
   uint8 lptru8Data4;
   uint8 lptru8Data5;
   uint8 lptru8Data6;
   uint8 lptru8Data7;
}Type_SwcApplTpms_stMessageCan;

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
extern boolean SwcApplTpms_bIsFunctioning                                (void);
extern boolean infSwcApplTpmsSwcServiceComM_bIsEnabledMessageCyclic      (void);
extern boolean infSwcApplTpmsSwcServiceDem_bIsFinishedAutolocation       (void);
extern boolean SwcApplTpms_bIsActiveModeDeveloper                        (void);
extern boolean SwcApplTpms_bIsFinishedAutolearn                          (void);
extern void    InfSwcApplTpmsSwcServiceOs_vInitFunction                  (void);
extern void    SwcApplTpms_vRunnableUpdateStatus                         (void);

extern void    HufIf_Init_Huf_SWC                               (void);
extern void    HufIf_RCtSaReTelDec                              (       Type_SwcApplTpms_stTelegramWS*        spRxDataIn, const Type_SwcApplTpms_stStatusBody* spEnvDataIn);
extern void    HufIf_RCtSaEnvData                               (const  Type_SwcApplTpms_stStatusBody*        spRxEnvDataIn);
extern void    HufIf_RCtAbsEnvData                              (const  Type_SwcApplTpms_stWheelPulseStamped* spRxEnvAbsDataIn);
extern void    HufIf_RCtSaTpmsData                              (const  Type_SwcApplTpms_stStatusBody*        spEnvData);
extern void    HufIf_GetVersion                                 (       Type_SwcApplTpms_stVersion*           sVersion);
extern boolean HufIf_CheckCRC8                                  (const  uint8*                                pucAkTel, const uint8 lu8Len);
extern uint8   ClientIf_NvM_ReadBlock                           (       uint16                                uiBlockNr, uint16 uiLen,       NVM_BLOCK_TYPE* ulpDestPtr);
extern uint8   ClientIf_NvM_WriteBlock                          (       uint16                                uiBlockNr, uint16 uiLen, const NVM_BLOCK_TYPE* ulpSrcPtr);
extern void    ClientIf_SetCurrentErrorERR                      (       Type_SwcApplTpms_eErrors              eErrorType);
extern void    ClientIf_DeleteCurrentErrorERR                   (       Type_SwcApplTpms_eErrors              eErrorType);
extern void    ClientIf_GetECUTimeStampValue                    (       uint32*                               ulpECUTimeStamp);
extern uint8   infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan   (       uint16                                ltIdCan, Type_SwcApplTpms_stMessageCan* lptrstMessage);
extern uint8   infSwcApplTpmsSwcServiceCom_tCalloutRxMessage    (       uint16                                uiCanMsgID, const Type_SwcApplTpms_stMessageCan* spCAN_Message);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

