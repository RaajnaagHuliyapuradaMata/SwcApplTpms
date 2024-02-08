/******************************************************************************/
/* File   : DevCanHandling.c                                                  */
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

#include "DevCanHandling.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"
#include "WallocX.hpp"
#include "global.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DCH_DEBUG_CFG                                                         0U
#define DCH_DEBUG_CYC                                                         1U
#define DCH_DEBUG_NVM                                                         2U
#define DCH_SUB_MULTIPLEX_0_MSG                                               0U
#define DCH_SUB_MULTIPLEX_1_MSG                                               1U
#define DCH_SUB_MULTIPLEX_2_MSG                                               2U
#define DCH_SUB_MULTIPLEX_3_MSG                                               3U
#define DCH_SUB_MULTIPLEX_4_MSG                                               4U
#define DCH_SUB_MULTIPLEX_5_MSG                                               5U
#define DCH_CAN_DBG_POS_RESP_WRITE                                         0xAAU
#define DCH_CAN_DBG_POS_RESP_READ                                          0x55U
#define DCH_CAN_DBG_NEG_RESP                                               0x22U
#define DCH_ALL_MULTIPLEX_ENABLED                                          0xFFU
#define DCH_MULTIPLEX_ENABLED                                                 1U
#define DCH_MULTIPLEX_DISABLED                                                0U
#define DCH_CAN_DEBUG_ACTIVE                                                0x65
#define DCH_ENABLE_CAN_DEBUG                                                  1U
#define DCH_DISABLE_CAN_DEBUG                                                 0U
#define DCH_MSG_NR_IN_SUBMULTIPLEX_CFG                                       48U
#define DCH_ELEMENT_NR_IN_ARRAY                                               6U
#define DCH_BITS_IN_ONE_BYTE                                                  8U
#define DCH_NVM_READ_CMD                                                      1U
#define DCH_NVM_WRITE_CMD                                                     2U
#define DCH_ALL_SUBMULTIPLEXES_ACTIVE                                       0x3F
#define DCH_U8_MAXSIZE_MASK                                                0xFFU
#define DCH_MULTIPLEX_INDEX                                                   0U
#define DCH_SUB_MULTIPLEX_INDEX                                               1U

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8 au8_MsgActivationInfo[6];
}DCH_MultiplexMsgData;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static DCH_MultiplexMsgData DCH_asMultiMsgPackageAct[6];
static Type_SwcApplTpms_stMessageCan DCH_NvMReadWritteResponse;
static boolean DCH_bEnableCanDebugConfig;
static boolean DCH_bEnableSingleMultiplexConfig;
static boolean DCH_bEnableNvMAccess;
static boolean DCH_BO_EnableContinousAPCReading;
static uint8 DCH_au8CurrentConfigMsg[2];
static uint8 DCH_U8_SubmultiplexesActive;
static boolean DCH_bEnableDeveloperModeConfig;
static void DCH_ActivateDebugCfg(const Type_SwcApplTpms_stMessageCan* sDebugCanMsgCfg);
static void DCH_NvMReadWriteDebugHandling(const Type_SwcApplTpms_stMessageCan* sMultiplexCanNvMCfg);
static void DCH_EnableAllMutiplexMsg(void);
static void DCH_DisableAllMutiplexMsg(void);
static void DCH_SetValueToMultiplexMsg(uint8 U8_SetValue);
static void DCH_DebugNvMRead(const Type_SwcApplTpms_stMessageCan* CanDebugNvmRead);
static void DCH_DebugNvMWrite(const Type_SwcApplTpms_stMessageCan* CanDebugNvmWrite);
static void DCH_MultiplexMsgUpdate(const Type_SwcApplTpms_stMessageCan* sMultiplexCanMsgCfg);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void DCH_ActivateDebugCfg(const Type_SwcApplTpms_stMessageCan* sDebugCanMsgCfg){
  if( DCH_ENABLE_CAN_DEBUG == DCH_IsCanDebugEnabled())
  {
   if(DCH_MULTIPLEX_ENABLED == (DCH_MULTIPLEX_ENABLED & sDebugCanMsgCfg->ucData2) )
   {
      DCH_EnableAllMutiplexMsg();
      DCH_U8_SubmultiplexesActive = DCH_ALL_SUBMULTIPLEXES_ACTIVE;
   }
   else{
      DCH_DisableAllMutiplexMsg();
   }
   if(( DCH_MULTIPLEX_ENABLED << 1 ) == ( ( DCH_MULTIPLEX_ENABLED << 1 ) & sDebugCanMsgCfg->ucData2 ) )
   {
      DCH_bEnableSingleMultiplexConfig = DCH_MULTIPLEX_ENABLED;
   }
   else{
      DCH_bEnableSingleMultiplexConfig = DCH_MULTIPLEX_DISABLED;
   }
   if(DCH_MULTIPLEX_ENABLED == (DCH_MULTIPLEX_ENABLED & (sDebugCanMsgCfg->ucData3) ) )
   {
      DCH_BO_EnableContinousAPCReading = DCH_MULTIPLEX_ENABLED;
   }
   else{
      DCH_BO_EnableContinousAPCReading = DCH_MULTIPLEX_DISABLED;
   }
   if(( DCH_MULTIPLEX_ENABLED << 1 ) == ( ( DCH_MULTIPLEX_ENABLED << 1 ) & sDebugCanMsgCfg->ucData3 ) )
   {
      DCH_bEnableDeveloperModeConfig = DCH_MULTIPLEX_ENABLED;
   }
   else{
      DCH_bEnableDeveloperModeConfig = DCH_MULTIPLEX_DISABLED;
   }
   if(DCH_MULTIPLEX_ENABLED == (DCH_MULTIPLEX_ENABLED & (sDebugCanMsgCfg->ucData4) ) )
   {
      DCH_bEnableNvMAccess = DCH_MULTIPLEX_ENABLED;
   }
   else{
      DCH_bEnableNvMAccess = DCH_MULTIPLEX_DISABLED;
   }
   if(( DCH_MULTIPLEX_ENABLED << 1 ) == ( ( DCH_MULTIPLEX_ENABLED << 1 ) & sDebugCanMsgCfg->ucData4 ) )
   {
      ResetHistoryToDefault();
   }
   else{
   }
  }
  else if(DCH_CAN_DEBUG_ACTIVE == sDebugCanMsgCfg->ucData1)
  {
    DCH_bEnableCanDebugConfig = DCH_ENABLE_CAN_DEBUG;
  }
  else{
  }
}

static void DCH_MultiplexMsgUpdate(const Type_SwcApplTpms_stMessageCan* sMultiplexCanMsgCfg){
  uint8 SubMultiplexValue;
  SubMultiplexValue = sMultiplexCanMsgCfg->ucData1;
  if( DCH_MULTIPLEX_ENABLED == DCH_bEnableSingleMultiplexConfig ){
   if( SubMultiplexValue <= DCH_SUB_MULTIPLEX_5_MSG ){
      if(DCH_SUB_MULTIPLEX_5_MSG == SubMultiplexValue){
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[0] = sMultiplexCanMsgCfg->ucData2;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[1] = sMultiplexCanMsgCfg->ucData3;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[2] = 0x00;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[3] = 0x00;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[4] = 0x00;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[5] = 0x00;
      }
      else{
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[0] = sMultiplexCanMsgCfg->ucData2;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[1] = sMultiplexCanMsgCfg->ucData3;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[2] = sMultiplexCanMsgCfg->ucData4;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[3] = sMultiplexCanMsgCfg->ucData5;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[4] = sMultiplexCanMsgCfg->ucData6;
        DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[5] = sMultiplexCanMsgCfg->ucData7;
      }
   }
   else{
   }
  }
  else{
  }
}

static void DCH_SetValueToMultiplexMsg(uint8 U8_SetValue)
{
  uint8 LocalArrCnt;
  uint8 LocalStrCnt;
  for(LocalStrCnt = 0; LocalStrCnt < SIZE_ARRAY(DCH_asMultiMsgPackageAct,DCH_MultiplexMsgData); LocalStrCnt++)
  {
   for(LocalArrCnt = 0; LocalArrCnt < sizeof(DCH_MultiplexMsgData); LocalArrCnt++)
   {
       DCH_asMultiMsgPackageAct[LocalStrCnt].au8_MsgActivationInfo[LocalArrCnt] = U8_SetValue;
   }
  }
}

static void DCH_EnableAllMutiplexMsg(void){
  DCH_SetValueToMultiplexMsg(DCH_ALL_MULTIPLEX_ENABLED);
}

static void DCH_DisableAllMutiplexMsg(void){
  DCH_SetValueToMultiplexMsg(DCH_MULTIPLEX_DISABLED);
}

static void DCH_NvMReadWriteDebugHandling(const Type_SwcApplTpms_stMessageCan* sMultiplexCanNvMCfg)
{
  if( DCH_MULTIPLEX_ENABLED == DCH_bEnableNvMAccess )
  {
   switch(sMultiplexCanNvMCfg->ucData1 )
   {
      case DCH_NVM_READ_CMD:
        DCH_DebugNvMRead(sMultiplexCanNvMCfg);
        break;

      case DCH_NVM_WRITE_CMD:
        DCH_DebugNvMWrite(sMultiplexCanNvMCfg);
        break;

      default:
        break;
   }

  }
  else{
  }
}

static void DCH_DebugNvMRead(const Type_SwcApplTpms_stMessageCan* CanDebugNvmRead){
  uint8 u8_GlobBlockNr;
  uint8 u8_LocalData[sizeof(NVM_BLOCK_TYPE)];
  uint8 U8_ReadSuccessful;
  NVM_BLOCK_TYPE l_ulTemp;
  u8_GlobBlockNr = CanDebugNvmRead->ucData2;
  U8_ReadSuccessful = ClientIf_NvM_ReadBlock(u8_GlobBlockNr, 1, &l_ulTemp);

  if( 0 == U8_ReadSuccessful){
   u8_LocalData[0]  = (uint8)((l_ulTemp >> 24U) & 0xFFU);
   u8_LocalData[1]  = (uint8)((l_ulTemp >> 16U) & 0xFFU);
   u8_LocalData[2]  = (uint8)((l_ulTemp >>  8U) & 0xFFU);
   u8_LocalData[3]  = (uint8)((l_ulTemp >>  0U) & 0xFFU);
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_POS_RESP_READ;
  }
  else{
   u8_LocalData[0]  = 0;
   u8_LocalData[1]  = 0;
   u8_LocalData[2]  = 0;
   u8_LocalData[3]  = 0;
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_NEG_RESP;
  }
  DCH_NvMReadWritteResponse.ucData0 = CanDebugNvmRead->ucData0;
  DCH_NvMReadWritteResponse.ucData2 = CanDebugNvmRead->ucData2;
  DCH_NvMReadWritteResponse.ucData3 = CanDebugNvmRead->ucData3;
  DCH_NvMReadWritteResponse.ucData4 = u8_LocalData[0];
  DCH_NvMReadWritteResponse.ucData5 = u8_LocalData[1];
  DCH_NvMReadWritteResponse.ucData6 = u8_LocalData[2];
  DCH_NvMReadWritteResponse.ucData7 = u8_LocalData[3];
}

static void DCH_DebugNvMWrite(const Type_SwcApplTpms_stMessageCan* CanDebugNvmWrite){
  uint8 U8_BytesToWrite;
  uint8 U8_GlobBlockNr;
  uint8 U8_WriteData[sizeof(NVM_BLOCK_TYPE)];
  uint8 U8_TempReadDataFromNvm[sizeof(NVM_BLOCK_TYPE)];
  uint8 U8_ReadWriteSuccessful;
  NVM_BLOCK_TYPE U32_Block;
  NVM_BLOCK_TYPE NVM_TempReadData;
  U8_GlobBlockNr = CanDebugNvmWrite->ucData2;
  U8_BytesToWrite = CanDebugNvmWrite->ucData3;
  U8_ReadWriteSuccessful = ClientIf_NvM_ReadBlock(U8_GlobBlockNr,1,&NVM_TempReadData);
  U8_TempReadDataFromNvm[0]  = (uint8)((NVM_TempReadData >> 24U) & 0xFFU);
  U8_TempReadDataFromNvm[1]  = (uint8)((NVM_TempReadData >> 16U) & 0xFFU);
  U8_TempReadDataFromNvm[2]  = (uint8)((NVM_TempReadData >>  8U) & 0xFFU);
  U8_TempReadDataFromNvm[3]  = (uint8)((NVM_TempReadData >>  0U) & 0xFFU);

  {
  if( 0 == U8_ReadWriteSuccessful){
   if((( U8_BytesToWrite >> 0) & 1U) == 1U){
      U8_WriteData[0] = CanDebugNvmWrite->ucData4;
   }
   else{
      U8_WriteData[0] = U8_TempReadDataFromNvm[0];
   }
   if((( U8_BytesToWrite >> 1) & 1U) == 1U){
      U8_WriteData[1]    = CanDebugNvmWrite->ucData5;
   }
   else{
      U8_WriteData[1] = U8_TempReadDataFromNvm[1];
   }
   if((( U8_BytesToWrite >> 2) & 1U) == 1U){
      U8_WriteData[2]    = CanDebugNvmWrite->ucData6;
   }
   else{
      U8_WriteData[2] = U8_TempReadDataFromNvm[2];
   }
   if((( U8_BytesToWrite >> 3) & 1U) == 1U){
      U8_WriteData[3]    = CanDebugNvmWrite->ucData7;
   }
   else{
      U8_WriteData[3] = U8_TempReadDataFromNvm[3];
   }
  }
  else{
    U8_WriteData[0]  = 0;
    U8_WriteData[1]  = 0;
    U8_WriteData[2]  = 0;
    U8_WriteData[3]  = 0;
  }
  }
  U32_Block = ((((NVM_BLOCK_TYPE)U8_WriteData[0] << 24U) & 0xFF000000U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[1] << 16U) & 0x00FF0000U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[2] <<  8U) & 0x0000FF00U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[3] <<  0U) & 0x000000FFU)  );
  U8_ReadWriteSuccessful |= ClientIf_NvM_WriteBlock (U8_GlobBlockNr, 1, &U32_Block);
  DCH_NvMReadWritteResponse.ucData0 = CanDebugNvmWrite->ucData0;
  if( 0 == U8_ReadWriteSuccessful){
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_POS_RESP_WRITE;
  }
  else{
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_NEG_RESP;
  }
  DCH_NvMReadWritteResponse.ucData2 = CanDebugNvmWrite->ucData2;
  DCH_NvMReadWritteResponse.ucData3 = CanDebugNvmWrite->ucData3;
  DCH_NvMReadWritteResponse.ucData4 = U8_WriteData[0];
  DCH_NvMReadWritteResponse.ucData5 = U8_WriteData[1];
  DCH_NvMReadWritteResponse.ucData6 = U8_WriteData[2];
  DCH_NvMReadWritteResponse.ucData7 = U8_WriteData[3];
}

boolean DCH_IsCanDebugEnabled(void){
  return DCH_bEnableCanDebugConfig;
}

void DCH_Init(void){
  DCH_bEnableDeveloperModeConfig = DCH_MULTIPLEX_DISABLED;
  DCH_bEnableCanDebugConfig = DCH_DISABLE_CAN_DEBUG;
  DCH_U8_SubmultiplexesActive = DCH_MULTIPLEX_DISABLED;
  DCH_bEnableSingleMultiplexConfig = DCH_MULTIPLEX_DISABLED;
  DCH_bEnableNvMAccess = DCH_MULTIPLEX_DISABLED;
  DCH_BO_EnableContinousAPCReading = DCH_MULTIPLEX_DISABLED;
  DCH_au8CurrentConfigMsg[0] = 0xFF;
  DCH_au8CurrentConfigMsg[1] = 0xFF;
  DCH_SetValueToMultiplexMsg(DCH_MULTIPLEX_DISABLED);
}

boolean DCH_IsContinousAPCReadingActive(void){
  return DCH_BO_EnableContinousAPCReading;
}

uint8 DCH_MultiplexMsgGetActiveStatus(uint8 ui8_MultiplexNr){
  uint8 SubMultiplexValue;
  uint8 ByteInSubMultiplex;
  uint8 BitInByteSubMultiplex;
  uint8 LocalMultiStatus = DCH_MULTIPLEX_DISABLED;

  SubMultiplexValue = ui8_MultiplexNr / DCH_MSG_NR_IN_SUBMULTIPLEX_CFG;
  ByteInSubMultiplex = ((ui8_MultiplexNr / DCH_BITS_IN_ONE_BYTE) - (SubMultiplexValue * DCH_ELEMENT_NR_IN_ARRAY) );
  BitInByteSubMultiplex = (ui8_MultiplexNr % DCH_BITS_IN_ONE_BYTE);
  LocalMultiStatus = ( DCH_MULTIPLEX_ENABLED  & (DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[ByteInSubMultiplex] >> BitInByteSubMultiplex) );
  return LocalMultiStatus;
}

void DCH_CheckCanDebugRequest(const Type_SwcApplTpms_stMessageCan* CanDebugRequestMsg){
  DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX] = CanDebugRequestMsg->ucData0;
  DCH_au8CurrentConfigMsg[DCH_SUB_MULTIPLEX_INDEX] = CanDebugRequestMsg->ucData1;
  switch(CanDebugRequestMsg->ucData0){
   case DCH_DEBUG_CFG:
      DCH_ActivateDebugCfg(CanDebugRequestMsg);
      break;

   case DCH_DEBUG_CYC:
      DCH_MultiplexMsgUpdate(CanDebugRequestMsg);
      if( CanDebugRequestMsg->ucData1 < 8){
        DCH_U8_SubmultiplexesActive |= ( DCH_U8_MAXSIZE_MASK & ( DCH_MULTIPLEX_ENABLED << CanDebugRequestMsg->ucData1) );
      }
      else{
      }
      break;

   case DCH_DEBUG_NVM:
      DCH_NvMReadWriteDebugHandling(CanDebugRequestMsg);
      break;

    default:
      break;
  }
}

uint8 DCH_SubmultiplexConfigGetStatus(void){
  uint8 ConfigFinished;
  ConfigFinished = DCH_MULTIPLEX_DISABLED;
  if(DCH_ALL_SUBMULTIPLEXES_ACTIVE == DCH_U8_SubmultiplexesActive){
   ConfigFinished = DCH_MULTIPLEX_ENABLED;
  }
  return ConfigFinished;
}

void DCH_GetCanDebugResponseData(Type_SwcApplTpms_stMessageCan* CanDebugResponseMsg){
  uint8 LocalResponseValue;
  switch(DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX]){
   case DCH_SUB_MULTIPLEX_0_MSG:
      if(DCH_ENABLE_CAN_DEBUG == DCH_IsCanDebugEnabled()){
        LocalResponseValue = DCH_CAN_DBG_POS_RESP_WRITE;
      }
      else{
        LocalResponseValue = DCH_CAN_DBG_NEG_RESP;
      }
      CanDebugResponseMsg->ucData0 = DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX];
      CanDebugResponseMsg->ucData1 = LocalResponseValue;
      CanDebugResponseMsg->ucData2 = 0x00;
      CanDebugResponseMsg->ucData3 = 0x00;
      CanDebugResponseMsg->ucData4 = 0x00;
      CanDebugResponseMsg->ucData5 = 0x00;
      CanDebugResponseMsg->ucData6 = 0x00;
      CanDebugResponseMsg->ucData7 = 0x00;
   break;

   case DCH_SUB_MULTIPLEX_1_MSG:
      if((DCH_MULTIPLEX_ENABLED == DCH_bEnableSingleMultiplexConfig)
       && (DCH_MULTIPLEX_ENABLED == DCH_SubmultiplexConfigGetStatus())){
        LocalResponseValue = DCH_CAN_DBG_POS_RESP_WRITE;
      }
      else{
        LocalResponseValue = DCH_CAN_DBG_NEG_RESP;
      }
      CanDebugResponseMsg->ucData0 = DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX];
      CanDebugResponseMsg->ucData1 = LocalResponseValue;
      CanDebugResponseMsg->ucData2 = 0x00;
      CanDebugResponseMsg->ucData3 = 0x00;
      CanDebugResponseMsg->ucData4 = 0x00;
      CanDebugResponseMsg->ucData5 = 0x00;
      CanDebugResponseMsg->ucData6 = 0x00;
      CanDebugResponseMsg->ucData7 = 0x00;
   break;

   case DCH_SUB_MULTIPLEX_2_MSG:
      CanDebugResponseMsg->ucData0 = DCH_NvMReadWritteResponse.ucData0;
      CanDebugResponseMsg->ucData1 = DCH_NvMReadWritteResponse.ucData1;
      CanDebugResponseMsg->ucData2 = DCH_NvMReadWritteResponse.ucData2;
      CanDebugResponseMsg->ucData3 = DCH_NvMReadWritteResponse.ucData3;
      CanDebugResponseMsg->ucData4 = DCH_NvMReadWritteResponse.ucData4;
      CanDebugResponseMsg->ucData5 = DCH_NvMReadWritteResponse.ucData5;
      CanDebugResponseMsg->ucData6 = DCH_NvMReadWritteResponse.ucData6;
      CanDebugResponseMsg->ucData7 = DCH_NvMReadWritteResponse.ucData7;
   break;

    default:
      CanDebugResponseMsg->ucData0 = DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX];
      CanDebugResponseMsg->ucData1 = DCH_CAN_DBG_NEG_RESP;
      CanDebugResponseMsg->ucData2 = 0x00;
      CanDebugResponseMsg->ucData3 = 0x00;
      CanDebugResponseMsg->ucData4 = 0x00;
      CanDebugResponseMsg->ucData5 = 0x00;
      CanDebugResponseMsg->ucData6 = 0x00;
      CanDebugResponseMsg->ucData7 = 0x00;
   break;
   }
}

boolean DCH_IsDeveloperModeActive(void){
   return DCH_bEnableDeveloperModeConfig;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

