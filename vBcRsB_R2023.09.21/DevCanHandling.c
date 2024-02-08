#include "Std_Types.hpp"

#include "DevCanHandling.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"

#include "WallocX.hpp"

#include "global.hpp"

#define DCH_DEBUG_CFG     0U    //!< activate or deactivate a command configuration
#define DCH_DEBUG_CYC     1U    //!< activate or deactivate debug cyclic message transmission
#define DCH_DEBUG_NVM     2U    //!< read/write NvM data

#define DCH_SUB_MULTIPLEX_0_MSG        0U   //!< Submultiplex 0 message
#define DCH_SUB_MULTIPLEX_1_MSG        1U   //!< Submultiplex 1 message
#define DCH_SUB_MULTIPLEX_2_MSG        2U   //!< Submultiplex 2 message
#define DCH_SUB_MULTIPLEX_3_MSG        3U   //!< Submultiplex 3 message
#define DCH_SUB_MULTIPLEX_4_MSG        4U   //!< Submultiplex 4 message
#define DCH_SUB_MULTIPLEX_5_MSG        5U   //!< Submultiplex 5 message

#define DCH_CAN_DBG_POS_RESP_WRITE      0xAAU   //!< CAN debug configuration positive response data
#define DCH_CAN_DBG_POS_RESP_READ       0x55U   //!< CAN debug configuration positive response data
#define DCH_CAN_DBG_NEG_RESP            0x22U   //!< CAN debug configuration negative response data

#define DCH_ALL_MULTIPLEX_ENABLED   0xFFU   //!< all multiplex messages enabled in one Byte
#define DCH_MULTIPLEX_ENABLED       1U      //!< bit for checking enabled status
#define DCH_MULTIPLEX_DISABLED      0U      //!< bit for checking disabled status

#define DCH_CAN_DEBUG_ACTIVE        0x65    //!< value needed to activate can debug configuration functionality

#define DCH_ENABLE_CAN_DEBUG        1U    //!< enable a functionality in CAN debug
#define DCH_DISABLE_CAN_DEBUG       0U    //!< disable a functionality in CAN debug

#define DCH_MSG_NR_IN_SUBMULTIPLEX_CFG    48U   //!< number of bits which are in the DCH_MultiplexMsgData structure 6*8 = 48
#define DCH_ELEMENT_NR_IN_ARRAY           6U    //!< number of elements of the structure type(DCH_MultiplexMsgData), more exactly DCH_asMultiMsgPackageAct[6]
#define DCH_BITS_IN_ONE_BYTE              8U    //!< number of bits in one byte

#define DCH_NVM_READ_CMD          1U    //!< NvM read enabled
#define DCH_NVM_WRITE_CMD         2U    //!< NvM write enabled

#define DCH_ALL_SUBMULTIPLEXES_ACTIVE     0x3F  //!< value for all submultiplexes active

#define DCH_U8_MAXSIZE_MASK       0xFFU   //!< maximum value on one byte

#define DCH_MULTIPLEX_INDEX           0U   //!< multiplex index from CAN message(byte0)
#define DCH_SUB_MULTIPLEX_INDEX       1U   //!< submultiplex index from CAN message(byte1)

typedef struct{
  uint8 au8_MsgActivationInfo[6];
}DCH_MultiplexMsgData;

static DCH_MultiplexMsgData DCH_asMultiMsgPackageAct[6];   //!< multiplex packages containing on each bit the active/inactive status of a cyclic debug message, the last one, has only 2 bytes of info

static Type_SwcApplTpms_stMessageCan DCH_NvMReadWritteResponse;  //!< message to be transmitted on CAN after a successful NvM read/write command was received

static boolean DCH_bEnableCanDebugConfig;        //!< if set, debug messages are active and can be configured
static boolean DCH_bEnableSingleMultiplexConfig;     //!< if set, single multiplex messages can be activated and deactivate
static boolean DCH_bEnableNvMAccess;       //!< if set, NvM read and writte is enabled

static boolean DCH_BO_EnableContinousAPCReading;     //!< if set, continuous APC reading should be enabled

static uint8 DCH_au8CurrentConfigMsg[2];     //!< keeps the 2 MSB bytes from CAN, with multiplex and submultiplex data

static uint8 DCH_U8_SubmultiplexesActive;    //!< keeps the submultiplexes received status

static boolean DCH_bEnableDeveloperModeConfig;        //!< if set, all RF frames will be forwarded to TPMS module

//! Check the CAN debug command, for activating specific configurations.
static void DCH_ActivateDebugCfg(const Type_SwcApplTpms_stMessageCan* sDebugCanMsgCfg);

//! Check if NvM access is enabled and if it is so, read data from NvM and also writte into it.
static void DCH_NvMReadWriteDebugHandling(const Type_SwcApplTpms_stMessageCan* sMultiplexCanNvMCfg);

//! Enable all cyclic multiplex ID messages sending
static void DCH_EnableAllMutiplexMsg(void);

//! Disable all cyclic multiplex ID messages sending
static void DCH_DisableAllMutiplexMsg(void);

//! Set a value, received as parameter, to the whole structure keeping the Multiplex ID configurations.
static void DCH_SetValueToMultiplexMsg(uint8 U8_SetValue);

//! Read a block from NvM, and return the calue on CAN debug config response
static void DCH_DebugNvMRead(const Type_SwcApplTpms_stMessageCan* CanDebugNvmRead);

//! Write specific bytes from a block in NvM.
static void DCH_DebugNvMWrite(const Type_SwcApplTpms_stMessageCan* CanDebugNvmWrite);

//! Update cyclic multiplex messages configuration.
static void DCH_MultiplexMsgUpdate(const Type_SwcApplTpms_stMessageCan* sMultiplexCanMsgCfg);

static void DCH_ActivateDebugCfg(const Type_SwcApplTpms_stMessageCan* sDebugCanMsgCfg)
{
  if( DCH_ENABLE_CAN_DEBUG == DCH_IsCanDebugEnabled())
  { // if CAN Debug is already enabled, don't enter on "else if" anymore.
   if(DCH_MULTIPLEX_ENABLED == (DCH_MULTIPLEX_ENABLED & sDebugCanMsgCfg->ucData2) )
   {
      DCH_EnableAllMutiplexMsg();
      DCH_U8_SubmultiplexesActive = DCH_ALL_SUBMULTIPLEXES_ACTIVE;
   }
   else{
      DCH_DisableAllMutiplexMsg();
   }
    // check second bit
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

    // check second bit
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

    // check second bit
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
  else{ // do nothing, not activated before and not active in current try
  }
}

/*!************************************************************************************************
 * \brief Update cyclic multiplex messages configuration.
 *
 *  If single multiplex ID is enabled to be configured, store the CAN message with the
 *  configuration in a global array.
 *
 * \param[in]   const Type_SwcApplTpms_stMessageCan* sMultiplexCanMsgCfg - CAN message received from BCM
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
static void DCH_MultiplexMsgUpdate(const Type_SwcApplTpms_stMessageCan* sMultiplexCanMsgCfg)
{
  uint8 SubMultiplexValue;
  SubMultiplexValue = sMultiplexCanMsgCfg->ucData1;
  if( DCH_MULTIPLEX_ENABLED == DCH_bEnableSingleMultiplexConfig )
  {
   if( SubMultiplexValue <= DCH_SUB_MULTIPLEX_5_MSG )
   {
      if(DCH_SUB_MULTIPLEX_5_MSG == SubMultiplexValue)
      { // last message has only 2 bytes with values, the rest are blank
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
   else{// do nothing, out of array bounds, not a valid submultiplex value
   }
  }
  else{//do nothing, not enabled remain with default
  }
}

/*!************************************************************************************************
 * \brief Set a value, received as parameter, to the whole structure keeping the Multiplex ID configurations.
 *
 * \param[in]   uint8 U8_SetValue - Value to be set on all bytes.
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
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

/*!************************************************************************************************
 * \brief Enable all cyclic multiplex ID messages sending
 *
 * \param[in]   -
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
static void DCH_EnableAllMutiplexMsg(void){
  DCH_SetValueToMultiplexMsg(DCH_ALL_MULTIPLEX_ENABLED);
}

/*!************************************************************************************************
 * \brief Disable all cyclic multiplex ID messages sending
 *
 * \param[in]   -
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
static void DCH_DisableAllMutiplexMsg(void){
  DCH_SetValueToMultiplexMsg(DCH_MULTIPLEX_DISABLED);
}

/*!************************************************************************************************
 * \brief Check if NvM access is enabled and if it is so, read data from NvM and also writte into it.
 *
 * \param[in]   const Type_SwcApplTpms_stMessageCan* sMultiplexCanNvMCfg - CAN message received from BCM
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
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
        // should not enter this case, so do nothing if does, not a active command
        break;
   }

  }
  else{
    // do nothing
  }
}

/*!************************************************************************************************
 * \brief Read a block from NvM, and return the calue on CAN debug config response
 *
 * \param[in]   const Type_SwcApplTpms_stMessageCan* CanDebugNvmRead - NvM Read information received on CAN
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
static void DCH_DebugNvMRead(const Type_SwcApplTpms_stMessageCan* CanDebugNvmRead)
{
//  uint8 u8_Length;
  uint8 u8_GlobBlockNr;
  uint8 u8_LocalData[sizeof(NVM_BLOCK_TYPE)];
  uint8 U8_ReadSuccessful;
  NVM_BLOCK_TYPE l_ulTemp;
  u8_GlobBlockNr = CanDebugNvmRead->ucData2;
//  u8_Length      = CanDebugNvmRead->ucData3;
  U8_ReadSuccessful = ClientIf_NvM_ReadBlock(u8_GlobBlockNr, 1, &l_ulTemp);

  if( 0 == U8_ReadSuccessful)
  {
   u8_LocalData[0]  = (uint8)((l_ulTemp >> 24U) & 0xFFU);  /* MSB */ /* Wegen QAC */
   u8_LocalData[1]  = (uint8)((l_ulTemp >> 16U) & 0xFFU);
   u8_LocalData[2]  = (uint8)((l_ulTemp >>  8U) & 0xFFU);
   u8_LocalData[3]  = (uint8)((l_ulTemp >>  0U) & 0xFFU);  /* LSB */
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_POS_RESP_READ;  //CanDebugNvmRead->ucData1;
  }
  else{
   u8_LocalData[0]  = 0;  /* MSB */
   u8_LocalData[1]  = 0;
   u8_LocalData[2]  = 0;
   u8_LocalData[3]  = 0;  /* LSB */
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_NEG_RESP;  //CanDebugNvmRead->ucData1;
  }

  DCH_NvMReadWritteResponse.ucData0 = CanDebugNvmRead->ucData0; /* MSB */
  DCH_NvMReadWritteResponse.ucData2 = CanDebugNvmRead->ucData2;
  DCH_NvMReadWritteResponse.ucData3 = CanDebugNvmRead->ucData3; /* LSB */
  DCH_NvMReadWritteResponse.ucData4 = u8_LocalData[0];
  DCH_NvMReadWritteResponse.ucData5 = u8_LocalData[1];
  DCH_NvMReadWritteResponse.ucData6 = u8_LocalData[2];
  DCH_NvMReadWritteResponse.ucData7 = u8_LocalData[3];
}

/*!************************************************************************************************
 * \brief Write specific bytes from a block in NvM.
 *
 *  Gets as parameter a block number which want's to be writen, the bytes which should be written
 *  in that block and the values which should be written in each block.
 *
 * \param[in]   const Type_SwcApplTpms_stMessageCan* CanDebugNvmWrite - CAN debug message from BCM to writte a block
 * \return      -
 *
 * \note        -
 * \warning     -
 *************************************************************************************************/
static void DCH_DebugNvMWrite(const Type_SwcApplTpms_stMessageCan* CanDebugNvmWrite)
{
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

  // check if data should be taken from Nvm or CAN message
  {
  if( 0 == U8_ReadWriteSuccessful )
  {
   if((( U8_BytesToWrite >> 0) & 1U) == 1U)
   {
      U8_WriteData[0] = CanDebugNvmWrite->ucData4;
   }
   else{
      U8_WriteData[0] = U8_TempReadDataFromNvm[0];
   }

   if((( U8_BytesToWrite >> 1) & 1U) == 1U)
   {
      U8_WriteData[1]    = CanDebugNvmWrite->ucData5;
   }
   else{
      U8_WriteData[1] = U8_TempReadDataFromNvm[1];
   }

   if((( U8_BytesToWrite >> 2) & 1U) == 1U)
   {
      U8_WriteData[2]    = CanDebugNvmWrite->ucData6;
   }
   else{
      U8_WriteData[2] = U8_TempReadDataFromNvm[2];
   }

   if((( U8_BytesToWrite >> 3) & 1U) == 1U)
   {
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
  // Write data to NvM
  U32_Block = ((((NVM_BLOCK_TYPE)U8_WriteData[0] << 24U) & 0xFF000000U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[1] << 16U) & 0x00FF0000U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[2] <<  8U) & 0x0000FF00U) +
               (((NVM_BLOCK_TYPE)U8_WriteData[3] <<  0U) & 0x000000FFU)  );
  U8_ReadWriteSuccessful |= ClientIf_NvM_WriteBlock (U8_GlobBlockNr, 1, &U32_Block);

  DCH_NvMReadWritteResponse.ucData0 = CanDebugNvmWrite->ucData0;

  if( 0 == U8_ReadWriteSuccessful )
  {
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_POS_RESP_WRITE;  //CanDebugNvmRead->ucData1;
  }
  else{
    DCH_NvMReadWritteResponse.ucData1 = DCH_CAN_DBG_NEG_RESP;  //CanDebugNvmRead->ucData1;
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

uint8 DCH_MultiplexMsgGetActiveStatus(uint8 ui8_MultiplexNr)
{
  uint8 SubMultiplexValue;
  uint8 ByteInSubMultiplex;
  uint8 BitInByteSubMultiplex;
  uint8 LocalMultiStatus = DCH_MULTIPLEX_DISABLED;

  SubMultiplexValue = ui8_MultiplexNr / DCH_MSG_NR_IN_SUBMULTIPLEX_CFG; // multiplex number / number of multiplex messages in a submultiplex can config
  ByteInSubMultiplex = ((ui8_MultiplexNr / DCH_BITS_IN_ONE_BYTE) - (SubMultiplexValue * DCH_ELEMENT_NR_IN_ARRAY) ); // ( ( multiplex number / nr of bits in a byte) - ( array number * number of elements in an array) )
  BitInByteSubMultiplex = (ui8_MultiplexNr % DCH_BITS_IN_ONE_BYTE); //

  LocalMultiStatus = ( DCH_MULTIPLEX_ENABLED  & (DCH_asMultiMsgPackageAct[SubMultiplexValue].au8_MsgActivationInfo[ByteInSubMultiplex] >> BitInByteSubMultiplex) );

  return LocalMultiStatus;
}

void DCH_CheckCanDebugRequest(const Type_SwcApplTpms_stMessageCan* CanDebugRequestMsg)
{
  // store first 2 values for response
  DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX] = CanDebugRequestMsg->ucData0;
  DCH_au8CurrentConfigMsg[DCH_SUB_MULTIPLEX_INDEX] = CanDebugRequestMsg->ucData1;

  switch(CanDebugRequestMsg->ucData0 )
  {
   case DCH_DEBUG_CFG:
      DCH_ActivateDebugCfg(CanDebugRequestMsg);
      break;

   case DCH_DEBUG_CYC:
      DCH_MultiplexMsgUpdate(CanDebugRequestMsg);
      if( CanDebugRequestMsg->ucData1 < 8)
      {
        DCH_U8_SubmultiplexesActive |= ( DCH_U8_MAXSIZE_MASK & ( DCH_MULTIPLEX_ENABLED << CanDebugRequestMsg->ucData1) );
      }
      else{
        //not a valid submultiplex, don't count
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

  if(DCH_ALL_SUBMULTIPLEXES_ACTIVE == DCH_U8_SubmultiplexesActive)
  {
   ConfigFinished = DCH_MULTIPLEX_ENABLED;
  }
  return ConfigFinished;
}

void DCH_GetCanDebugResponseData(Type_SwcApplTpms_stMessageCan* CanDebugResponseMsg)
{
  uint8 LocalResponseValue;

  switch(DCH_au8CurrentConfigMsg[DCH_MULTIPLEX_INDEX])
  {
   case DCH_SUB_MULTIPLEX_0_MSG:
      if( DCH_ENABLE_CAN_DEBUG == DCH_IsCanDebugEnabled())
      {
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
      if( ( DCH_MULTIPLEX_ENABLED == DCH_bEnableSingleMultiplexConfig )
       && (DCH_MULTIPLEX_ENABLED == DCH_SubmultiplexConfigGetStatus() ) )
      {
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
