/******************************************************************************/
/* File   : SwcApplTpms_Diag.c                                                */
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

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "global.hpp"
#include "state_fzzX.hpp"
#include "state_bzx.hpp"
#include "procdatx.hpp"
#include "WallocX.hpp"
#include "WnTypePar.hpp"
#include "USWarnX.hpp"
#include "USCS.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "eeiface.hpp"
#include "calibrX.hpp"
#include "Walloc_IF.hpp"
#include "walloc.hpp"

#include "SwcApplTpms_LearnEOL.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DIAG__TEMPERATURE_OFFSET_FOR_UNSIGNED                     ((sint8)   40)
#define DIAG__CU8_RESERVED_DATA                                   ((uint8) 0x00)
#define DIAG__CU8_POSITIVE_RESPONSE                               ((uint8) 0x00)
#define DIAG__CU8_NEG_RES_INVALID_FORMAT                          ((uint8) 0x13)
#define DIAG__CU8_NEG_RES_NVM_READ_FAIL                           ((uint8) 0x2A)
#define DIAG__CU8_NEG_RES_NVM_WRITE_FAIL                          ((uint8) 0x2B)
#define DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT                  ((uint8) 0x22)
#define DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE                    ((uint8) 0x31)
#define DIAG__CU8_ROUTINESTARTSTOP_LENGTH                         ((uint8) 0x01)
#define DIAG__CU8_ROUTINERESULT_LENGTH                            ((uint8) 0x00)
#define DIAG__CU8_ROUTINESTART                                    ((uint8) 0x01)
#define DIAG__CU8_ROUTINESTOP                                     ((uint8) 0x00)
#define DIAG__CU8_ROUTINETIMEOUT                                  ((uint8) 0xFF)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 (*DIAG__ReqCallback_Type)(tsTPMSDiag_Data* PtParam);

typedef struct{
   enum_TPMSDiagnosticRequest eDiagRequest;
   DIAG__ReqCallback_Type PF_ReqCallback;
}DIAG__struct_ReqHandler;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8 DIAG__ReqCallback_ReadWSNr01                               tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadWSNr02                               (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadWSNr03                               (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadWSNr04                               (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadIdFL                                 (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadIdFR                                 (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadIdRR                                 (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadIdRL                                 (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadLastReceivedWheelSensor              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteWSNr01                              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteWSNr02                              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteWSNr03                              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteWSNr04                              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadWheelSensorIDs                       (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteWheelSensorIDs                      (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadVehicleSpecificParameters            (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteVehicleSpecificParameters           (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadAutoLearnWSParameters                (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteAutoLearnWSParameters               (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadAdditionalPressureOfMinimumPressure  (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteAdditionalPressureOfMinimumPressure (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadBCMFaultReason                       (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteBCMFaultReason                      (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadBCMPosition                          (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteBCMPosition                         (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadABSTicksValue                        (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteABSTicksValue                       (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadRSSINoiseLevel                       (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteRSSINoiseLevel                      (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_ReadTemperatureWarningThreshold          (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_WriteTemperatureWarningThreshold         (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_StartEOL_TPMS_TestProcedure              (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_StopEOL_TPMS_TestProcedure               (tsTPMSDiag_Data *PS_MsgContext);
static uint8 DIAG__ReqCallback_RequestResultsEOL_TPMS_TestProcedure     (tsTPMSDiag_Data *PS_MsgContext);
static void  DIAG__GetWSDataForPosition                                 (const uint8 CU8_PosIndex, uint8* PU8_InterfaceData);
static void  DIAG__GetWsIdForPosition                                   (const uint8 CU8_PosIndex, uint8* PU8_InterfaceData);
static uint8 DIAG__GetLastReceivedWheelId                               (uint8* PU8_ResData);
static uint8 DIAG__PutNewIDAndResetWarning                              (uint8* PU8_ReqData);
static void  DIAG__GetVehicleSpecPara                                   (uint8* PU8_ResData);
static void  DIAG__PutVehicleSpecPara                                   (uint8* PU8_ReqData);
static void  DIAG__GetMinPressThresEE                                   (uint8* PU8_ResData);
static void  DIAG__PutMinPressThresEE                                   (uint8* PU8_ReqData);
static void  DIAG__EOLRoutineStart                                      (uint8* PU8_ReqData, uint8* PU8_ResData);
static void  DIAG__EOLRoutineReqResponse                                (uint8* PU8_ResData);

static uint8 AU8_ResData[16];
static uint16 U16_RespLenght;

static const DIAG__struct_ReqHandler DIAG__AS_ReqHandlerArray[E_TPMS_DIAG_MAX_NUMBER] = {
      {E_TPMS_DIAG_READ_WS_ID1,                    &DIAG__ReqCallback_ReadWSNr01}
   ,  {E_TPMS_DIAG_READ_WS_ID2,                    &DIAG__ReqCallback_ReadWSNr02}
   ,  {E_TPMS_DIAG_READ_WS_ID3,                    &DIAG__ReqCallback_ReadWSNr03}
   ,  {E_TPMS_DIAG_READ_WS_ID4,                    &DIAG__ReqCallback_ReadWSNr04}
   ,  {E_TPMS_DIAG_READ_ID_FL,                     &DIAG__ReqCallback_ReadIdFL}
   ,  {E_TPMS_DIAG_READ_ID_FR,                     &DIAG__ReqCallback_ReadIdFR}
   ,  {E_TPMS_DIAG_READ_ID_RR,                     &DIAG__ReqCallback_ReadIdRR}
   ,  {E_TPMS_DIAG_READ_ID_RL,                     &DIAG__ReqCallback_ReadIdRL}
   ,  {E_TPMS_DIAG_READ_LAST_RECEIVED_WS,          &DIAG__ReqCallback_ReadLastReceivedWheelSensor}
   ,  {E_TPMS_DIAG_WRITE_WS_ID1,                   &DIAG__ReqCallback_WriteWSNr01}
   ,  {E_TPMS_DIAG_WRITE_WS_ID2,                   &DIAG__ReqCallback_WriteWSNr02}
   ,  {E_TPMS_DIAG_WRITE_WS_ID3,                   &DIAG__ReqCallback_WriteWSNr03}
   ,  {E_TPMS_DIAG_WRITE_WS_ID4,                   &DIAG__ReqCallback_WriteWSNr04}
   ,  {E_TPMS_DIAG_READ_WS_IDS,                    &DIAG__ReqCallback_ReadWheelSensorIDs}
   ,  {E_TPMS_DIAG_WRITE_WS_IDS,                   &DIAG__ReqCallback_WriteWheelSensorIDs}
   ,  {E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS,       &DIAG__ReqCallback_ReadVehicleSpecificParameters}
   ,  {E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS,      &DIAG__ReqCallback_WriteVehicleSpecificParameters}
   ,  {E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS,  &DIAG__ReqCallback_ReadAutoLearnWSParameters}
   ,  {E_TPMS_DIAG_WRITE_AUTO_LEARN_WS_PARAMETERS, &DIAG__ReqCallback_WriteAutoLearnWSParameters}
   ,  {E_TPMS_DIAG_READ_PRESSURE_OF_MIN_PRESS,     &DIAG__ReqCallback_ReadAdditionalPressureOfMinimumPressure}
   ,  {E_TPMS_DIAG_WRITE_PRESSURE_OF_MIN_PRESS,    &DIAG__ReqCallback_WriteAdditionalPressureOfMinimumPressure}
   ,  {E_TPMS_DIAG_START_TPMS_EOL,                 &DIAG__ReqCallback_StartEOL_TPMS_TestProcedure}
   ,  {E_TPMS_DIAG_STOP_TPMS_EOL,                  &DIAG__ReqCallback_StopEOL_TPMS_TestProcedure}
   ,  {E_TPMS_DIAG_RESULT_TPMS_EOL,                &DIAG__ReqCallback_RequestResultsEOL_TPMS_TestProcedure}
   ,  {E_TPMS_DIAG_READ_ECU_FAULT_REASON,          &DIAG__ReqCallback_ReadBCMFaultReason}
   ,  {E_TPMS_DIAG_WRITE_ECU_FAULT_REASON,         &DIAG__ReqCallback_WriteBCMFaultReason}
   ,  {E_TPMS_DIAG_READ_ECU_POSITION,              &DIAG__ReqCallback_ReadBCMPosition}
   ,  {E_TPMS_DIAG_WRITE_ECU_POSITION,             &DIAG__ReqCallback_WriteBCMPosition}
   ,  {E_TPMS_DIAG_READ_ABS_TICKS,                 &DIAG__ReqCallback_ReadABSTicksValue}
   ,  {E_TPMS_DIAG_WRITE_ABS_TICKS,                &DIAG__ReqCallback_WriteABSTicksValue}
   ,  {E_TPMS_DIAG_READ_NOISE_LEVEL,               &DIAG__ReqCallback_ReadRSSINoiseLevel}
   ,  {E_TPMS_DIAG_WRITE_NOISE_LEVEL,              &DIAG__ReqCallback_WriteRSSINoiseLevel}
   ,  {E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR,   &DIAG__ReqCallback_ReadTemperatureWarningThreshold}
   ,  {E_TPMS_DIAG_WRITE_TEMPERATURE_WARNING_THR,  &DIAG__ReqCallback_WriteTemperatureWarningThreshold}
};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static uint8 DIAG__ReqCallback_ReadWSNr01(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWSDataForPosition(cRadPosVL, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 10;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadWSNr02(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWSDataForPosition(cRadPosVR, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 10;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadWSNr03(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWSDataForPosition(cRadPosHL, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 10;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadWSNr04(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWSDataForPosition(cRadPosHR, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 10;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadIdFL(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWsIdForPosition(cRadPosVL, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 4U;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadIdFR(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWsIdForPosition(cRadPosVR, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 4U;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadIdRR(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWsIdForPosition(cRadPosHR, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 4U;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadIdRL(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetWsIdForPosition(cRadPosHL, &AU8_ResData[0]);
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 4U;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadLastReceivedWheelSensor(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  (void) DIAG__GetLastReceivedWheelId( &AU8_ResData[0] );
   PS_MsgContext->pucResData = AU8_ResData;
    U16_RespLenght = 8;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteWSNr01(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = ( PS_MsgContext->pucReqData[0] );
  AU8_ResData[1] = ( PS_MsgContext->pucReqData[1] );
  AU8_ResData[2] = ( PS_MsgContext->pucReqData[2] );
  AU8_ResData[3] = ( PS_MsgContext->pucReqData[3] );
  AU8_ResData[4] = cRadPosVL;
  U8_RetVal = DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteWSNr02(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = ( PS_MsgContext->pucReqData[0] );
  AU8_ResData[1] = ( PS_MsgContext->pucReqData[1] );
  AU8_ResData[2] = ( PS_MsgContext->pucReqData[2] );
  AU8_ResData[3] = ( PS_MsgContext->pucReqData[3] );
  AU8_ResData[4] = cRadPosVR;
  U8_RetVal = DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteWSNr03(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = ( PS_MsgContext->pucReqData[0] );
  AU8_ResData[1] = ( PS_MsgContext->pucReqData[1] );
  AU8_ResData[2] = ( PS_MsgContext->pucReqData[2] );
  AU8_ResData[3] = ( PS_MsgContext->pucReqData[3] );
  AU8_ResData[4] = cRadPosHL;
  U8_RetVal = DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteWSNr04(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = ( PS_MsgContext->pucReqData[0] );
  AU8_ResData[1] = ( PS_MsgContext->pucReqData[1] );
  AU8_ResData[2] = ( PS_MsgContext->pucReqData[2] );
  AU8_ResData[3] = ( PS_MsgContext->pucReqData[3] );
  AU8_ResData[4] = cRadPosHR;
  U8_RetVal = DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadWheelSensorIDs(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_Index = 0;
  uint8 U8_RadPos = 0;
  uint32 U32_TmpID;
  uint8 U8_LoopCnt;
  U16_RespLenght = 16;
  for(U8_LoopCnt = 0; U8_LoopCnt < U16_RespLenght; U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
   for( U8_Index = 0u; U8_Index < 4u; U8_Index++){
      U8_RadPos = GETucRadpositionPD(U8_Index);
      U32_TmpID = ulGetID(U8_Index);
      switch(U8_RadPos){
        case cRadPosVL:
            AU8_ResData[0] = (uint8) (0xFFu & (U32_TmpID >> 24u) );
            AU8_ResData[1] = (uint8) (0xFFu & (U32_TmpID >> 16u) );
            AU8_ResData[2] = (uint8) (0xFFu & (U32_TmpID >> 8u) );
            AU8_ResData[3] = (uint8) (0xFFu & (U32_TmpID) );
          break;

        case cRadPosVR:
            AU8_ResData[4] = (uint8) (0xFFu & (U32_TmpID >> 24u) );
            AU8_ResData[5] = (uint8) (0xFFu & (U32_TmpID >> 16u) );
            AU8_ResData[6] = (uint8) (0xFFu & (U32_TmpID >> 8u) );
            AU8_ResData[7] = (uint8) (0xFFu & (U32_TmpID) );
          break;

        case cRadPosHL:
            AU8_ResData[8]  = (uint8) (0xFFu & (U32_TmpID >> 24u) );
            AU8_ResData[9]  = (uint8) (0xFFu & (U32_TmpID >> 16u) );
            AU8_ResData[10] = (uint8) (0xFFu & (U32_TmpID >> 8u) );
            AU8_ResData[11] = (uint8) (0xFFu & (U32_TmpID) );
          break;

        case cRadPosHR:
            AU8_ResData[12] = (uint8) (0xFFu & (U32_TmpID >> 24u) );
            AU8_ResData[13] = (uint8) (0xFFu & (U32_TmpID >> 16u) );
            AU8_ResData[14] = (uint8) (0xFFu & (U32_TmpID >> 8u) );
            AU8_ResData[15] = (uint8) (0xFFu & (U32_TmpID) );
          break;

        default:
          break;
      }
   }
   PS_MsgContext->pucResData = AU8_ResData;
    (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteWheelSensorIDs(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  uint32 *ID1, *ID2,*ID3,*ID4;
  for(U8_LoopCnt = 0; U8_LoopCnt < 5; U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  ID1 = (uint32*)&PS_MsgContext->pucReqData[0];
  ID2 = (uint32*)&PS_MsgContext->pucReqData[4];
  ID3 = (uint32*)&PS_MsgContext->pucReqData[8];
  ID4 = (uint32*)&PS_MsgContext->pucReqData[12];
  if( (*ID1 == *ID2 ) ||
      (*ID1 == *ID3 ) ||
      (*ID1 == *ID4 ) ||
      (*ID2 == *ID3 ) ||
      (*ID2 == *ID4 ) ||
      (*ID3 == *ID4 ) ){
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  else{
    AU8_ResData[0] = ( PS_MsgContext->pucReqData[0] );
    AU8_ResData[1] = ( PS_MsgContext->pucReqData[1] );
    AU8_ResData[2] = ( PS_MsgContext->pucReqData[2] );
    AU8_ResData[3] = ( PS_MsgContext->pucReqData[3] );
    AU8_ResData[4] = cRadPosVL;
    (void)DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );

    AU8_ResData[0] = ( PS_MsgContext->pucReqData[4] );
    AU8_ResData[1] = ( PS_MsgContext->pucReqData[5] );
    AU8_ResData[2] = ( PS_MsgContext->pucReqData[6] );
    AU8_ResData[3] = ( PS_MsgContext->pucReqData[7] );
    AU8_ResData[4] = cRadPosVR;
    (void)DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );

    AU8_ResData[0] = ( PS_MsgContext->pucReqData[8] );
    AU8_ResData[1] = ( PS_MsgContext->pucReqData[9] );
    AU8_ResData[2] = ( PS_MsgContext->pucReqData[10] );
    AU8_ResData[3] = ( PS_MsgContext->pucReqData[11] );
    AU8_ResData[4] = cRadPosHL;
    (void)DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );

    AU8_ResData[0] = ( PS_MsgContext->pucReqData[12] );
    AU8_ResData[1] = ( PS_MsgContext->pucReqData[13] );
    AU8_ResData[2] = ( PS_MsgContext->pucReqData[14] );
    AU8_ResData[3] = ( PS_MsgContext->pucReqData[15] );
    AU8_ResData[4] = cRadPosHR;
    (void)DIAG__PutNewIDAndResetWarning( &AU8_ResData[0] );
  }
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadVehicleSpecificParameters(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LoopCnt;
  for(U8_LoopCnt = 0; U8_LoopCnt < sizeof(AU8_ResData); U8_LoopCnt++){
    AU8_ResData[U8_LoopCnt] = 0;
  }
  DIAG__GetVehicleSpecPara( &AU8_ResData[0] );
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 4;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteVehicleSpecificParameters(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 AU8_ReqData[2];
  uint8 U8_VarCodLegislation;
  uint8 U8_VarCodPlacardPress;
  uint8 U8_VarCodMinPressThres;
  uint8 U8_VarCodOffroadPlacardPress;
  uint8 U8_VarCodOffroadPlacardPressMin;
  uint8 U8_VarCodMinimumPressure;
  U8_VarCodLegislation           = ( PS_MsgContext->pucReqData[0] );
  U8_VarCodPlacardPress          = ( PS_MsgContext->pucReqData[1] );
  U8_VarCodOffroadPlacardPress   = ( PS_MsgContext->pucReqData[2] );
  U8_VarCodMinimumPressure       = ( PS_MsgContext->pucReqData[3] );
  if( (U8_VarCodPlacardPress >= 60u)    && (U8_VarCodPlacardPress <= 214u) ){
      if(U8_VarCodLegislation == E_PRC_LEG){
          U8_VarCodMinPressThres = u8_PRC_MinPrs_digits;
          U8_VarCodOffroadPlacardPressMin = u8_PRC_Offroad_Press_digits;
      }
      else if(U8_VarCodLegislation == E_EU_KO_LEG){
          U8_VarCodMinPressThres = u8_EU_MinPrs_digits;
          U8_VarCodOffroadPlacardPressMin = u8_EU_Offroad_Press_digits;
      }
      else if(U8_VarCodLegislation == E_US_LEG_NON_EXTRA_LOAD_TIRES){
          U8_VarCodMinPressThres = u8_US_NonExtra_MinPrs_digits;
          U8_VarCodOffroadPlacardPressMin = u8_Us_NonExtra_Offroad_Press_digits;
      }
      else if(U8_VarCodLegislation == E_US_LEG_EXTRA_LOAD_TIRES){
          U8_VarCodMinPressThres = u8_US_Extra_MinPrs_digits;
          U8_VarCodOffroadPlacardPressMin = u8_Us_Extra_Offroad_Press_digits;
      }
      else{
        U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
      }
      if(DIAG__CU8_POSITIVE_RESPONSE == U8_RetVal){
        AU8_ReqData[0] = U8_VarCodLegislation;
        AU8_ReqData[1] = U8_VarCodPlacardPress;
        DIAG__PutVehicleSpecPara(&AU8_ReqData[0]);
        if(U8_VarCodOffroadPlacardPress < U8_VarCodOffroadPlacardPressMin){
          U8_VarCodOffroadPlacardPress = U8_VarCodOffroadPlacardPressMin;
        }
        NvM3_PUTucVarCodOffroadPlacardPress(U8_VarCodOffroadPlacardPress);
        if(U8_VarCodMinimumPressure < U8_VarCodMinPressThres){
          U8_VarCodMinimumPressure = U8_VarCodMinPressThres;
        }
        DIAG__PutMinPressThresEE(&U8_VarCodMinimumPressure);
        if(ucPutPMinCS(U8_VarCodMinimumPressure, 0) > 0){
          PutDataEE(ucCdIdWNc, tCDA.ucByte);
        }
      }
      else{
      }
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
  }
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadAutoLearnWSParameters(tsTPMSDiag_Data *PS_MsgContext){
  WAParameter tWAParLocal;
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  GetWADataEE(cWAParameter, (unsigned char *) &tWAParLocal);
  AU8_ResData[0] = tWAParLocal.ucMinCt4ZomReset;
  AU8_ResData[1] = tWAParLocal.ucMinERMeanRssiLevel;
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 2;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteAutoLearnWSParameters(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_MinCt4ZomReset = PS_MsgContext->pucReqData[0];
  uint8 U8_MinERMeanRssiLevel = PS_MsgContext->pucReqData[1];
  GetWADataEE(cWAParameter, (unsigned char *) &tWAPar);
  tWAPar.ucMinCt4ZomReset = U8_MinCt4ZomReset;
  tWAPar.ucMinERMeanRssiLevel = U8_MinERMeanRssiLevel;
  PutWADataEE(cWAParameter, (unsigned char *) &tWAPar);
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadAdditionalPressureOfMinimumPressure(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = 0;
  DIAG__GetMinPressThresEE( &AU8_ResData[0] );
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 1;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteAdditionalPressureOfMinimumPressure(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_VarCodMinPressThres;
  uint8 U8_LowLimitOfPMIN;
  uint8 U8_HighLimitOfPMIN = 0xD6;
  U16_RespLenght = 0;
  U8_VarCodMinPressThres   = ( PS_MsgContext->pucReqData[0] );
  if(GETucVarCodLegislationEE() == E_EU_KO_LEG){
          U8_LowLimitOfPMIN = u8_EU_MinPrs_digits;
  }
  else if(GETucVarCodLegislationEE() == E_US_LEG_NON_EXTRA_LOAD_TIRES){
          U8_LowLimitOfPMIN = u8_US_NonExtra_MinPrs_digits;
  }
  else if(GETucVarCodLegislationEE() == E_US_LEG_EXTRA_LOAD_TIRES){
          U8_LowLimitOfPMIN = u8_US_Extra_MinPrs_digits;
  }
  else
          U8_LowLimitOfPMIN = u8_PRC_MinPrs_digits;
  }
  if((U8_VarCodMinPressThres >= U8_LowLimitOfPMIN) && (U8_VarCodMinPressThres <= U8_HighLimitOfPMIN)){
      DIAG__PutMinPressThresEE( &U8_VarCodMinPressThres );
      if(ucPutPMinCS(U8_VarCodMinPressThres, 0) > 0){
          PutDataEE(ucCdIdWNc, tCDA.ucByte);
      }
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadBCMFaultReason(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = 0;
  NvM_ReadData_ECUDefect(&AU8_ResData[0]);
  (PS_MsgContext->pucResData) = AU8_ResData;
  U16_RespLenght = 1;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteBCMFaultReason(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 BCMFaultReasonToWrite;
  BCMFaultReasonToWrite = ( PS_MsgContext->pucReqData[0]);
  if(BCMFaultReasonToWrite < 3){
    NvM_WriteData_ECUDefect(BCMFaultReasonToWrite);
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
  }
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadBCMPosition(tsTPMSDiag_Data *PS_MsgContext){
  WAParameter tWAParLocal;
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = 0;
  tWAParLocal.ucEcuPosition = 0;
  GetWADataEE(cWAParameter, (unsigned char *) &tWAParLocal);
  if((tWAParLocal.ucEcuPosition == ucECUPosFront) ||
      (tWAParLocal.ucEcuPosition == ucECUPosRear)  ||
      (tWAParLocal.ucEcuPosition == ucECUPosNeutral)){
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  AU8_ResData[0] = tWAParLocal.ucEcuPosition;
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 1;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteBCMPosition(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_NewECUPosition;
  U8_NewECUPosition = PS_MsgContext->pucReqData[0];

  if((U8_NewECUPosition == ucECUPosFront) ||
      (U8_NewECUPosition == ucECUPosRear)  ||
      (U8_NewECUPosition == ucECUPosNeutral)){
    GetWADataEE(cWAParameter, (unsigned char *) &tWAPar);
    tWAPar.ucEcuPosition = U8_NewECUPosition;
   PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadABSTicksValue(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  WAABSTicksInOneRevolution LocalABSTicksInOneRev;
  LocalABSTicksInOneRev.ucFrontAxisABSTicks = 0;
  LocalABSTicksInOneRev.ucRearAxisABSTicks = 0;
  GetWADataEE(cWAABSTicksInOneRevolution, (unsigned char *) &LocalABSTicksInOneRev);
  if((LocalABSTicksInOneRev.ucFrontAxisABSTicks >= 32U) ||
      (LocalABSTicksInOneRev.ucRearAxisABSTicks >= 32U)){
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  AU8_ResData[0] = LocalABSTicksInOneRev.ucFrontAxisABSTicks;
  AU8_ResData[1] = LocalABSTicksInOneRev.ucRearAxisABSTicks;
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 2;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteABSTicksValue(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  WAABSTicksInOneRevolution LocalABSTicksInOneRev, ParamaterABSTicksInOneRev;
  LocalABSTicksInOneRev.ucFrontAxisABSTicks = 0;
  LocalABSTicksInOneRev.ucRearAxisABSTicks = 0;
  ParamaterABSTicksInOneRev.ucFrontAxisABSTicks = PS_MsgContext->pucReqData[0];
  ParamaterABSTicksInOneRev.ucRearAxisABSTicks = PS_MsgContext->pucReqData[1];
  if((ParamaterABSTicksInOneRev.ucFrontAxisABSTicks >= 32U) ||
      (ParamaterABSTicksInOneRev.ucRearAxisABSTicks >= 32U)){
    GetWADataEE(cWAABSTicksInOneRevolution, (unsigned char *) &LocalABSTicksInOneRev);
   if((LocalABSTicksInOneRev.ucFrontAxisABSTicks == ParamaterABSTicksInOneRev.ucFrontAxisABSTicks) &&
        (LocalABSTicksInOneRev.ucRearAxisABSTicks == ParamaterABSTicksInOneRev.ucRearAxisABSTicks)){
   }
   else{
   PutWADataEE(cWAABSTicksInOneRevolution, (unsigned char *) &ParamaterABSTicksInOneRev );
   }
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadRSSINoiseLevel(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_LocalNoiseLevel = 0;
  GetWADataEE(cWAParameter, (unsigned char *) &tWAPar);
  AU8_ResData[0] = tWAPar.ucMinOffsetGXe;
  AU8_ResData[1] = tWAPar.ucOffsetOverlapsGXe;
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 2;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteRSSINoiseLevel(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  if( ( PS_MsgContext->pucReqData[0] >= 1 ) && ( PS_MsgContext->pucReqData[1] > 10 ) ){
    GetWADataEE(cWAParameter, (unsigned char *) &tWAPar);
    tWAPar.ucMinOffsetGXe = PS_MsgContext->pucReqData[0];
    tWAPar.ucOffsetOverlapsGXe = PS_MsgContext->pucReqData[1];
   PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  U16_RespLenght = 0;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_ReadTemperatureWarningThreshold(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = ((uint8) (NvM3_GETucVarCodTemperatureWarningThresEE() + DIAG__TEMPERATURE_OFFSET_FOR_UNSIGNED));
  PS_MsgContext->pucResData = AU8_ResData;
  U16_RespLenght = 1;
  (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_WriteTemperatureWarningThreshold(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  sint8 S8_TemperatureWarningThres = ((sint8) PS_MsgContext->pucReqData[0]) - DIAG__TEMPERATURE_OFFSET_FOR_UNSIGNED;
  if(S8_TemperatureWarningThres <= ((sint8) 120)){
    NvM3_PUTucVarCodTemperatureWarningThresEE(S8_TemperatureWarningThres);
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_CONDITIONS_NOT_CORRECT;
  }
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_StartEOL_TPMS_TestProcedure(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_TmpReq = 0;
  uint8 U8_TmpRes = 0;
  AU8_ResData[0] = 0;
  U16_RespLenght = 0;
  if( PS_MsgContext->uiReqDataLen == DIAG__CU8_ROUTINESTARTSTOP_LENGTH ){
    U8_TmpReq = PS_MsgContext->pucReqData[0];
    DIAG__EOLRoutineStart( &U8_TmpReq, &U8_TmpRes );
   if( U8_TmpRes == RET_ERROR ){
      U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
   }
   else{
      DIAG__EOLRoutineReqResponse( AU8_ResData );
      U16_RespLenght = 1;
   }
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  PS_MsgContext->pucResData = AU8_ResData;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_StopEOL_TPMS_TestProcedure(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  AU8_ResData[0] = 1;
  U16_RespLenght = 0;
  if( PS_MsgContext->uiReqDataLen == DIAG__CU8_ROUTINESTARTSTOP_LENGTH ){
   if(PS_MsgContext->pucReqData[0] == DIAG__CU8_ROUTINESTOP){
      EOL_ResetLearnRoutine();
      U16_RespLenght = 1;
   }
   else{
      U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
   }
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  PS_MsgContext->pucResData = AU8_ResData;
  PS_MsgContext->puiResDataLen = &U16_RespLenght;
  return U8_RetVal;
}

static uint8 DIAG__ReqCallback_RequestResultsEOL_TPMS_TestProcedure(tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  U16_RespLenght = 0;
  AU8_ResData[0] =0;
  if( PS_MsgContext->uiReqDataLen == DIAG__CU8_ROUTINERESULT_LENGTH ){
    DIAG__EOLRoutineReqResponse( AU8_ResData );
    AU8_ResData[1] = GETucReifendruckPD(cRadPosVL);
    AU8_ResData[2] = GETucReifendruckPD(cRadPosVR);
    AU8_ResData[3] = GETucReifendruckPD(cRadPosHL);
    AU8_ResData[4] = GETucReifendruckPD(cRadPosHR);
   PS_MsgContext->pucResData = AU8_ResData;
    U16_RespLenght = 5;
    (PS_MsgContext->puiResDataLen) = &U16_RespLenght;
  }
  else{
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  return U8_RetVal;
}

static void DIAG__GetWSDataForPosition(const uint8 CU8_PosIndex, uint8* PU8_InterfaceData){
  uint8 U8_Idx;
  uint8 U8_TempRadPos;
  uint32 U32_TmpID;
  uint8 U8_Temp;
  uint8 U8_LocalReifendruckPD;
  U8_Idx = 0;
  U32_TmpID = ulGetID(CU8_PosIndex);
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 24) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 16) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 8) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID) );
  U8_Idx += 1;
  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
    U8_TempRadPos = GETucRadpositionPD(CU8_PosIndex);
  }
  else{
    U8_TempRadPos = cRadPosRR;
  }
  PU8_InterfaceData[U8_Idx] = U8_TempRadPos;
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = 0xFF;
  U8_Idx += 1;
  U8_LocalReifendruckPD = GETucReifendruckPD(CU8_PosIndex);
  if( U8_LocalReifendruckPD <= 0xF8 ){
   PU8_InterfaceData[U8_Idx] = ( 0xFFu & ((U8_LocalReifendruckPD + 2)/4 ) );
  }
  else{
   PU8_InterfaceData[U8_Idx] = 0xFF;
  }
  U8_Idx += 1;
  U8_Temp = (uint8) (0xFF & (GETscTemperaturPD(CU8_PosIndex) + DIAG__TEMPERATURE_OFFSET_FOR_UNSIGNED));
  if( U8_Temp < 0xA7 ){
   PU8_InterfaceData[U8_Idx] = U8_Temp;
  }
  else{
   PU8_InterfaceData[U8_Idx] = 0xFF;
  }
  U8_Idx += 1;
  U8_LocalReifendruckPD = GETucVarCodPlacardPressEE();
  PU8_InterfaceData[U8_Idx] = (0xFFu & ((U8_LocalReifendruckPD + 2) / 4));
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = GETucRestlebensdauerPD(CU8_PosIndex) & ~0x80;
}

static void DIAG__GetWsIdForPosition(const uint8 CU8_PosIndex, uint8* PU8_InterfaceData){
  uint8 U8_Idx;
  uint32 U32_TmpID;
  U8_Idx = 0;
  U32_TmpID = ulGetID(ucGetIndexOfHistoryWP(CU8_PosIndex));
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 24) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 16) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID >> 8) );
  U8_Idx += 1;
  PU8_InterfaceData[U8_Idx] = (uint8) (0xFFu & (U32_TmpID) );
}

static uint8 DIAG__GetLastReceivedWheelId(uint8* PU8_ResData){
  uint8 U8_Idx;
  uint8 U8_RadPos;
  uint32 U32_REId;
  uint8 U8_LocalTemperature;
  uint8 U8_LocalPreProcPressurePD;
  U32_REId = ulGetReDataIdPD();
  for(U8_Idx = 0u; U8_Idx < sizeof(U32_REId); U8_Idx++){
    *PU8_ResData = (uint8) (((U32_REId) >> ((sizeof(U32_REId) - 1 - U8_Idx) * 8)) & 0xFFU);
   PU8_ResData++;
  }
  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
    U8_RadPos = ucGetWPOfCol( ucGetColOfID( &U32_REId ) );
  }
  else{
    U8_RadPos = cRadPosRR;
  }
  *PU8_ResData = U8_RadPos;
  PU8_ResData++;
  *PU8_ResData = 0xFFu;
  PU8_ResData++;
  U8_LocalPreProcPressurePD = ucGetReDataPreProcPressurePD();
  if(U8_LocalPreProcPressurePD <= 0xFC ){
    *PU8_ResData = (uint8)(0xFFu & ((U8_LocalPreProcPressurePD + 2)/4));
  }
  else{
    *PU8_ResData = 0xFF;
  }
  PU8_ResData++;
  U8_LocalTemperature = (uint8) (0xFF & (scGetReDataPreProcTemperaturePD() + DIAG__TEMPERATURE_OFFSET_FOR_UNSIGNED) );
  if( U8_LocalTemperature < 0xA7 ){
    *PU8_ResData = U8_LocalTemperature;
  }
  else{
    *PU8_ResData = 0xFF;
  }
  PU8_ResData++;
  return(8u);
}

static uint8 DIAG__PutNewIDAndResetWarning(uint8* PU8_ReqData){
  uint8 AU8_Service[2],U8_Idx;
  uint8 U8_Ret;
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint32 U32_REId = 0U;
  for(U8_Idx = 0u; U8_Idx < sizeof(U32_REId); U8_Idx++){
    U32_REId |= (((uint32)(*PU8_ReqData)) << ((sizeof(U32_REId) - 1 - U8_Idx) * 8));
   PU8_ReqData++;
  }
  U8_Ret = ucSetID(&U32_REId, PU8_ReqData);
  if( U8_Ret == 0 ){
    U8_RetVal = DIAG__CU8_NEG_RES_REQUEST_OUT_OF_RANGE;
  }
  else{
    InitBZ();
   if( (*PU8_ReqData) > 3 ){
      AU8_Service[0] = ucResetWarnVectorc;
      AU8_Service[1] = 4;
      (void) ucWarnManagerWN( ucDiagServicec, AU8_Service );
      AU8_Service[0] = 0;
      AU8_Service[1] = 0;
      (void) ucTSSMsgManagerTM( ucPorInitc, AU8_Service );
   }
   else{
      for(U8_Idx = 0; U8_Idx < cMaxLR; U8_Idx++){
        if( (U8_Ret & (uint8)(0x10u<<U8_Idx)) == (0x10u<<U8_Idx) ){
          AU8_Service[0] = ucResetWarnVectorc;
          AU8_Service[1] = U8_Idx;
          (void) ucWarnManagerWN( ucDiagServicec, AU8_Service );
          AU8_Service[0] = 0;
          AU8_Service[1] = 0;
          (void) ucTSSMsgManagerTM( ucPorInitc, AU8_Service );
        }
        else{
        }
      }
   }
  }
  return U8_RetVal;
}

static void DIAG__GetVehicleSpecPara(uint8* PU8_ResData){
  *PU8_ResData = ( GETucVarCodLegislationEE() );
  PU8_ResData++;
  *PU8_ResData = (uint8) (0xFFu & GETucVarCodPlacardPressEE());
  PU8_ResData++;
  *PU8_ResData = (uint8) (0xFFU & NvM3_GETucVarCodOffroadPlacardPress());
  PU8_ResData++;
  *PU8_ResData = (uint8) ( 0xFFu & GETucVarCodMinPressThresEE());
  PU8_ResData++;
}

static void DIAG__PutVehicleSpecPara(uint8* PU8_ReqData){
  PUTucVarCodLegislationEE(*(PU8_ReqData + 0));
  PUTucVarCodPlacardPressEE(*(PU8_ReqData + 1));
  CalibrSetPressureCAL();
}

static void DIAG__GetMinPressThresEE(uint8* PU8_ResData){
  *PU8_ResData = (uint8) ( 0xFFu & GETucVarCodMinPressThresEE());
}

static void DIAG__PutMinPressThresEE(uint8* PU8_ReqData){
  PUTucVarCodMinPressThresEE(*(PU8_ReqData + 0));
  CalibrSetPressureCAL();
}

static void DIAG__EOLRoutineStart(uint8* PU8_ReqData, uint8* PU8_ResData){
  *PU8_ResData = EOL_StartLearnRoutine( *PU8_ReqData );
}

static void DIAG__EOLRoutineReqResponse(uint8* PU8_ResData){
  uint8 ucRoutineStatusValue;
  ucRoutineStatusValue = EOL_GetStatusEOLRoutine();
  if( (ucRoutineStatusValue > EOL_ROUT_ENDED_WITH_ERROR) || (ucRoutineStatusValue == EOL_ROUT_RESERVED) ){
    EOL_PutStatusEOLRoutine( EOL_ROUT_NEVER_STARTED );
   ucRoutineStatusValue = EOL_ROUT_NEVER_STARTED;
  }
  else{
  }
  *PU8_ResData = ucRoutineStatusValue;
}

uint8 HufIf_DiagReqCallback(const enum_TPMSDiagnosticRequest eDiagRequest, tsTPMSDiag_Data *PS_MsgContext){
  uint8 U8_RetVal = DIAG__CU8_POSITIVE_RESPONSE;
  uint8 U8_Index = 0;
  for(U8_Index = 0; U8_Index < E_TPMS_DIAG_MAX_NUMBER; U8_Index++){
   if(eDiagRequest == DIAG__AS_ReqHandlerArray[U8_Index].eDiagRequest){
      if(((void *) 0) != DIAG__AS_ReqHandlerArray[U8_Index].PF_ReqCallback){
        U8_RetVal = DIAG__AS_ReqHandlerArray[U8_Index].PF_ReqCallback(PS_MsgContext);
      }
      else{
        U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
      }
      break;
   }
  }
  if(U8_Index >= E_TPMS_DIAG_MAX_NUMBER ){
    U8_RetVal = DIAG__CU8_NEG_RES_INVALID_FORMAT;
  }
  else{
  }
  ClientIf_Debug_DiagReqCallback(eDiagRequest,PS_MsgContext,U8_RetVal);
  return U8_RetVal;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

