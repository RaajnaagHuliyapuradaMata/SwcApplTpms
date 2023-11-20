#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "ProcDatX.hpp"
#include "State_BzX.hpp"
#include "BusMsgX.hpp"
#include "SilaX.hpp"
#include "WallocX.hpp"
#include "statemanagerX.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "State_FzzX.hpp"
#include "DevCanHandling.hpp"

#define RE_TEMP_OFFSET_CAN                                                   50U
#define RE_TEMP_INVALID_HUF                                        ((sint8)0x7F)
#define E_OK                                                                  0U
#define E_NOT_OK                                                              1U

static uint8 m_ucWheelIndexTire;

static void CheckDbgReqMsgData(        const Type_SwcApplTpms_stMessageCan* spCAN_Message);
static void GenNextDebugMsgData(             Type_SwcApplTpms_stMessageCan* spCAN_Message);
static void GenDebugResMsgData(              Type_SwcApplTpms_stMessageCan* spCAN_Message);
static void GenHmiMsgData(                   Type_SwcApplTpms_stMessageCan* spCAN_Message);
static void Gen_TPMS_Software_ID_MsgData(    Type_SwcApplTpms_stMessageCan* spCAN_Message);
static void GenHmiTemperatureRefPresMsgData( Type_SwcApplTpms_stMessageCan* spCAN_Message);

void Init_CAN_Data(void){
  m_ucWheelIndexTire = 0x00U;
}

uint8 HufIf_CanMsgReceive(
            uint16                         uiCanMsgID
   ,  const Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   uint8 retVal = E_OK;
   switch(uiCanMsgID
   ){
      case CAN_MSG_DEBUG_REQ:
         if(
               bGetBitFahrzeugzustandFZZ(
                  cKL_15_EIN
               )
            == TRUE
         ){
            CheckDbgReqMsgData(
               spCAN_Message
            );
         }
         break;

      default:
         retVal = E_NOT_OK;
         break;
   }
   return retVal;
}

uint8 SwcApplTpms_u8TransmitCAN(
      uint16                         uiCanMsgID
   ,  Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   uint8 retVal = E_OK;
   switch(
      uiCanMsgID
   ){
      case CAN_MSG_DEBUG_RES:                            GenDebugResMsgData(              spCAN_Message); break;
      case CAN_MSG_Debug_CYCLIC:                         GenNextDebugMsgData(             spCAN_Message); break;
      case CAN_MSG_HMI_CYCLIC:   BusMsgDoTeleFinished(); GenHmiMsgData(                   spCAN_Message); break;
      case CAN_MSG_HMI_TEMP_CYCLIC:                      GenHmiTemperatureRefPresMsgData( spCAN_Message); break;
      case CAN_MSG_TPMS_Software_ID_CYCLIC:              Gen_TPMS_Software_ID_MsgData(    spCAN_Message); break;
      default: retVal = E_NOT_OK;                                                                         break;
   }
   return retVal;
}

static void CheckDbgReqMsgData(
   const Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   DCH_CheckCanDebugRequest(
      spCAN_Message
   );
}

static void GenNextDebugMsgData(
   Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   DCM_DataToTransmitOnCAN(
      spCAN_Message
   );
}

static void GenDebugResMsgData(
   Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   DCH_GetCanDebugResponseData(spCAN_Message);
}

static void GenHmiMsgData(
   Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   boolean        l_bSendRealDataStatus = FALSE;
   tuCAN_HMI_Data l_sHMI;

   l_bSendRealDataStatus = SendRealReData();
                                                       l_sHMI.sHMI.b6Gap1              = BUSMSG_GAP1_DEFAULT;
                                                       l_sHMI.sHMI.bTPS_FR             = (0x07 & BusMsgGetWarning(BUSMSG_TYRE_VR));
                                                       l_sHMI.sHMI.bTPV_FR             = (0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidVR() : BUSMSG_TYREPRESS_INVALID));
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_FR){l_sHMI.sHMI.ucTP_FR             = cInvalidPressureCAN;}
   else                                               {l_sHMI.sHMI.ucTP_FR             = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_VR);}
                                                       l_sHMI.sHMI.bTemp_Warning_FR    = (0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_VR));
                                                       l_sHMI.sHMI.bTPS_FL             = (0x07 & BusMsgGetWarning(BUSMSG_TYRE_VL));
                                                       l_sHMI.sHMI.bTPV_FL             = (0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidVL() : BUSMSG_TYREPRESS_INVALID));
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_FL){l_sHMI.sHMI.ucTP_FL             = cInvalidPressureCAN;}
   else                                               {l_sHMI.sHMI.ucTP_FL             = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_VL);}
                                                       l_sHMI.sHMI.bTemp_Warning_FL    = (0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_VL));
                                                       l_sHMI.sHMI.bTPS_RR             = (0x07 & BusMsgGetWarning(BUSMSG_TYRE_HR));
                                                       l_sHMI.sHMI.bTPV_RR             = (0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidHR() : BUSMSG_TYREPRESS_INVALID));
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_RR){l_sHMI.sHMI.ucTP_RR             = cInvalidPressureCAN;}
   else                                               {l_sHMI.sHMI.ucTP_RR             = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_HR);}
                                                       l_sHMI.sHMI.bTemp_Warning_RR    = (0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_HR));
                                                       l_sHMI.sHMI.bTPS_RL             = (0x07 & BusMsgGetWarning(BUSMSG_TYRE_HL));
                                                       l_sHMI.sHMI.bTPV_RL             = (0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidHL() : BUSMSG_TYREPRESS_INVALID));
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_RL){l_sHMI.sHMI.ucTP_RL             = cInvalidPressureCAN;}
   else                                               {l_sHMI.sHMI.ucTP_RL             = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_HL);}
                                                       l_sHMI.sHMI.bTemp_Warning_RL    = (0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_HL));
                                                       l_sHMI.sHMI.bTMP_S              = SilaGetState();
                                                       l_sHMI.sHMI.bTPMS_Locate_Status = ((bGetBitBetriebszustandBZ(cWA_FINISH) == TRUE) ? 1U : 0U);
                                                       l_sHMI.sHMI.bTPMS_Learn_Status  = ((bGetBitBetriebszustandBZ(cER_FINISH) == TRUE) ? 1U : 0U);
   *spCAN_Message = l_sHMI.sMsgsBytes;
}

extern void VERSION_GetSoftware_ID(
   uint8* ucData
);

static void Gen_TPMS_Software_ID_MsgData(
   Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   VERSION_GetSoftware_ID(
      spCAN_Message
   );
}

static void GenHmiTemperatureRefPresMsgData(
   Type_SwcApplTpms_stMessageCan* spCAN_Message
){
   tuCAN_HMI_Data l_sHMIData;
   uint8 U8_RefPres;
   if(
         VehStateGetRoadmode()
      != 0
   )   {U8_RefPres = NvM3_GETucVarCodOffroadPlacardPress();}
   else{U8_RefPres = GETucVarCodPlacardPressEE();}

   BusMsgDetermineTemperatures();

   if(
         SendRealReData()
      == TRUE
   ){
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_FL = BusMsgGetTemperature(BUSMSG_TYRE_VL);
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_FR = BusMsgGetTemperature(BUSMSG_TYRE_VR);
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_RL = BusMsgGetTemperature(BUSMSG_TYRE_HL);
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_RR = BusMsgGetTemperature(BUSMSG_TYRE_HR);
   }
   else{
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_FL = cInvalidTemperatureCAN;
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_FR = cInvalidTemperatureCAN;
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_RL = cInvalidTemperatureCAN;
      l_sHMIData.sHMI_Temperature_RefPres.ucTT_RR = cInvalidTemperatureCAN;
   }
   l_sHMIData.sHMI_Temperature_RefPres.ucRP_FL = U8_RefPres;
   l_sHMIData.sHMI_Temperature_RefPres.ucRP_FR = U8_RefPres;
   l_sHMIData.sHMI_Temperature_RefPres.ucRP_RL = U8_RefPres;
   l_sHMIData.sHMI_Temperature_RefPres.ucRP_RR = U8_RefPres;
   *spCAN_Message = l_sHMIData.sMsgsBytes;
}

