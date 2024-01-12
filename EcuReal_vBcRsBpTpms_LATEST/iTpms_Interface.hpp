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

#define DLL_IMEXPORT

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum TPMSErrorType{
      E_TPMS_ERROR_WS_LIFE_TIME_FL_CNT_LOW
   ,  E_TPMS_ERROR_WS_LIFE_TIME_FR_CNT_LOW
   ,  E_TPMS_ERROR_WS_LIFE_TIME_RR_CNT_LOW
   ,  E_TPMS_ERROR_WS_LIFE_TIME_RL_CNT_LOW
   ,  E_TPMS_ERROR_WS_DEFECT_FL
   ,  E_TPMS_ERROR_WS_DEFECT_FR
   ,  E_TPMS_ERROR_WS_DEFECT_RR
   ,  E_TPMS_ERROR_WS_DEFECT_RL
   ,  E_TPMS_ERROR_WS_DEFECT_UNKNOWN_POS
   ,  E_TPMS_ERROR_WS_MISSING_FL
   ,  E_TPMS_ERROR_WS_MISSING_FR
   ,  E_TPMS_ERROR_WS_MISSING_RR
   ,  E_TPMS_ERROR_WS_MISSING_RL
   ,  E_TPMS_ERROR_WS_MISSING_UNKNOWN_POS
   ,  E_TPMS_ERROR_WS_OVER_TEMP_FL
   ,  E_TPMS_ERROR_WS_OVER_TEMP_FR
   ,  E_TPMS_ERROR_WS_OVER_TEMP_RR
   ,  E_TPMS_ERROR_WS_OVER_TEMP_RL
   ,  E_TPMS_ERROR_AXLE_LOCATE_FAIL
   ,  E_TPMS_ERROR_NO_QUALIFIED_SENSOR_SIGNALS
   ,  E_TPMS_ERROR_DETECTED_TOO_MANY_SENSORS
   ,  E_TPMS_ERROR_NOT_FUNCTIONING_DUE_TO_ECU_INTERNAL_FAULT
   ,  E_TPMS_ERROR_WS_MISSING_DURING_CONTINUOUS_INVALID_SPEED
   ,  E_TPMS_ERROR_RF_INTERFERENCE
   ,  E_TPMS_ERROR_AUTOLOCATION_FAILED
   ,  E_TPMS_ERROR_MAX_NUMBER
}enum_TPMSErrorType;

typedef enum TPMSDiagnosticRequest{
      E_TPMS_DIAG_READ_WS_ID1
   ,  E_TPMS_DIAG_READ_WS_ID2
   ,  E_TPMS_DIAG_READ_WS_ID3
   ,  E_TPMS_DIAG_READ_WS_ID4
   ,  E_TPMS_DIAG_READ_ID_FL
   ,  E_TPMS_DIAG_READ_ID_FR
   ,  E_TPMS_DIAG_READ_ID_RR
   ,  E_TPMS_DIAG_READ_ID_RL
   ,  E_TPMS_DIAG_READ_LAST_RECEIVED_WS
   ,  E_TPMS_DIAG_WRITE_WS_ID1
   ,  E_TPMS_DIAG_WRITE_WS_ID2
   ,  E_TPMS_DIAG_WRITE_WS_ID3
   ,  E_TPMS_DIAG_WRITE_WS_ID4
   ,  E_TPMS_DIAG_READ_WS_IDS
   ,  E_TPMS_DIAG_WRITE_WS_IDS
   ,  E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS
   ,  E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS
   ,  E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS
   ,  E_TPMS_DIAG_WRITE_AUTO_LEARN_WS_PARAMETERS
   ,  E_TPMS_DIAG_READ_PRESSURE_OF_MIN_PRESS
   ,  E_TPMS_DIAG_WRITE_PRESSURE_OF_MIN_PRESS
   ,  E_TPMS_DIAG_START_TPMS_EOL
   ,  E_TPMS_DIAG_STOP_TPMS_EOL
   ,  E_TPMS_DIAG_RESULT_TPMS_EOL
   ,  E_TPMS_DIAG_READ_ECU_FAULT_REASON
   ,  E_TPMS_DIAG_WRITE_ECU_FAULT_REASON
   ,  E_TPMS_DIAG_READ_ECU_POSITION
   ,  E_TPMS_DIAG_WRITE_ECU_POSITION
   ,  E_TPMS_DIAG_READ_ABS_TICKS
   ,  E_TPMS_DIAG_WRITE_ABS_TICKS
   ,  E_TPMS_DIAG_READ_NOISE_LEVEL
   ,  E_TPMS_DIAG_WRITE_NOISE_LEVEL
   ,  E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR
   ,  E_TPMS_DIAG_WRITE_TEMPERATURE_WARNING_THR
   ,  E_TPMS_DIAG_MAX_NUMBER
}enum_TPMSDiagnosticRequest;

struct struct_Version{
   uint8 ucaApplVersionHuf[9];
   uint8 ucaApplVersionCst[7];
   uint8 ucaApplVersionCDD[20];
   uint8 ucaCompilerName[6];
   uint8 ucaCompilerVersion[6];
   uint8 ucaBuild_Date[20];
};

typedef struct{
   uint32 ulRxTimeStamp;
   uint16 uiRxRSSI;
   uint8  ucaTelegram[MAX_SIZE_WS_TELEGRAM];
}tsWS_RxDataIn;

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
}tsEnv_Data;

typedef struct{
   bitfield bTPS_FR             : 3;
   bitfield bTPV_FR             : 1;
   bitfield bTPS_FL             : 3;
   bitfield bTPV_FL             : 1;
   bitfield bTPS_RR             : 3;
   bitfield bTPV_RR             : 1;
   bitfield bTPS_RL             : 3;
   bitfield bTPV_RL             : 1;
   bitfield ucTP_FL             : 8;
   bitfield ucTP_FR             : 8;
   bitfield ucTP_RL             : 8;
   bitfield ucTP_RR             : 8;
   bitfield bTPMS_Locate_Status : 1;
   bitfield bTPMS_Learn_Status  : 1;
   bitfield b6Gap1              : 6;
   bitfield bTMP_S              : 4;
   bitfield bTemp_Warning_FL    : 1;
   bitfield bTemp_Warning_FR    : 1;
   bitfield bTemp_Warning_RL    : 1;
   bitfield bTemp_Warning_RR    : 1;
}CAN_HMI_type;

typedef struct{
   uint8  u8MajorRelease;
   uint8  u8MinorRelease;
   uint16 u16MicroRelease;
   uint32 u32Crc;
}CAN_TPMS_Software_ID_type;

typedef struct{
   uint8 ucTT_FL;
   uint8 ucTT_FR;
   uint8 ucTT_RL;
   uint8 ucTT_RR;
   uint8 ucRP_FL;
   uint8 ucRP_FR;
   uint8 ucRP_RL;
   uint8 ucRP_RR;
}tsHMI_Temperature_RefPres;

typedef struct{
   uint8 ucStatus;
}tsTPMS_Data;

typedef struct{
   uint32 ulAbsTimeStamp;
   uint16 uiPulseCtrFL;
   uint16 uiPulseCtrFR;
   uint16 uiPulseCtrRL;
   uint16 uiPulseCtrRR;
   uint16 uiSimTimeStamp;
   uint8  ucAge;
}tsEnvAbs_Data;

typedef struct{
   uint8 ucData0;
   uint8 ucData1;
   uint8 ucData2;
   uint8 ucData3;
   uint8 ucData4;
   uint8 ucData5;
   uint8 ucData6;
   uint8 ucData7;
}Type_SwcApplTpms_stMessageCan;

typedef struct{
   uint8*  pucReqData;
   uint16  uiReqDataLen;
   uint8*  pucResData;
   uint16* puiResDataLen;
}tsTPMSDiag_Data;

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
extern uint8   SwcApplTpms_u8TransmitCAN      (uint16 uiCanMsgID,       Type_SwcApplTpms_stMessageCan* spCAN_Message);
extern uint8   HufIf_CanMsgReceive            (uint16 uiCanMsgID, const Type_SwcApplTpms_stMessageCan* spCAN_Message);
extern void    HufIf_Init_Huf_SWC             (void);
extern void    HufIf_RCtSaEnvData             (const tsEnv_Data*    spRxEnvDataIn);
extern void    HufIf_RCtSaReTelDec            (      tsWS_RxDataIn* spRxDataIn, const tsEnv_Data* spEnvDataIn);
extern void    HufIf_RCtAbsEnvData            (const tsEnvAbs_Data* spRxEnvAbsDataIn);
extern void    HufIf_RCtSaTpmsData            (      tsTPMS_Data*   spTPMS_Data, const tsEnv_Data* spEnvData);
extern void    HufIf_GetVersion               (struct struct_Version* sVersion);
extern boolean HufIf_CheckCRC8                (const uint8* pucAkTel, const uint8 ucLen);
extern uint8   HufIf_DiagReqCallback          (const enum_TPMSDiagnosticRequest eDiagRequest, tsTPMSDiag_Data* PS_MsgContext);
extern void    HufIf_GetStatusErrorERR        (uint8 eErrorType);
extern uint8   ClientIf_NvM_ReadBlock         (uint16 uiBlockNr, uint16 uiLen,       NVM_BLOCK_TYPE* ulpDestPtr);
extern uint8   ClientIf_NvM_WriteBlock        (uint16 uiBlockNr, uint16 uiLen, const NVM_BLOCK_TYPE* ulpSrcPtr);
extern void    ClientIf_SetCurrentErrorERR    (enum_TPMSErrorType eErrorType);
extern void    ClientIf_ResetCurrentErrorERR  (enum_TPMSErrorType eErrorType);
extern void    ClientIf_DeleteCurrentErrorERR (enum_TPMSErrorType eErrorType);
extern void    ClientIf_GetECUTimeStampValue  (uint32* ulpECUTimeStamp);
extern void    ClientIf_Debug_DiagReqCallback (const enum_TPMSDiagnosticRequest eDiagRequest, tsTPMSDiag_Data* spDiag_Data, uint8 ucReturnVal);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

