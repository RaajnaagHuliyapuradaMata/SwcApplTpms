

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
#if(defined HUF_DEBUG) && (defined WIN32)
  #include "debug.hpp"
#endif

#define RE_TEMP_OFFSET_CAN 50U
#define RE_TEMP_INVALID_HUF      ((sint8)(0x7F))

#define E_OK                   (0U)
#define E_NOT_OK               (1U)

static uint8         m_ucWheelIndexTire;

static void CheckDbgReqMsgData(const tsCAN_Message* spCAN_Message);
static void GenNextDebugMsgData(tsCAN_Message* spCAN_Message);
static void GenDebugResMsgData(tsCAN_Message * spCAN_Message);
static void GenHmiMsgData(tsCAN_Message *spCAN_Message);
static void GenHmiTemperatureRefPresMsgData(tsCAN_Message *spCAN_Message);
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalTirePosition(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalTirePressure(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalTireTemperature(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalTireState(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalMalfuncBulb(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalTpmsIndication(void);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static boolean GetSignalPacardValuesValid(void);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalSensorNoRx(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalSensorBatLow(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalSensorRsDefect(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalSensorSpin(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalBatLifeRemaining(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalReserved01(uint8);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8   GetSignalReserved02(uint8);
#endif

void Init_CAN_Data(void){
  m_ucWheelIndexTire = 0x00U;
}

uint8 HufIf_CanMsgReceive(uint16 uiCanMsgID,const tsCAN_Message* spCAN_Message)
{
  uint8 retVal = E_OK;

  switch(uiCanMsgID)
  {
   case CAN_MSG_DEBUG_REQ:

      if(bGetBitFahrzeugzustandFZZ(cKL_15_EIN) == TRUE)
      {
        CheckDbgReqMsgData(spCAN_Message);
      }
#if(defined HUF_DEBUG) && (defined WIN32)
      //print("Rx CAN-Msg \"CAN_MSG_DEBUG_REQ\"\n\r");
#endif
      break;
    default:
      //Breakpoint();
      retVal = E_NOT_OK;
      break;
  }

  ClientIf_Debug_CanMsgReceive(uiCanMsgID,spCAN_Message,retVal);

  return retVal;
 }

uint8 HufIf_CanMsgTransmit(uint16 uiCanMsgID,tsCAN_Message* spCAN_Message)
{
  uint8   retVal;

  retVal = E_OK;

  switch(uiCanMsgID)
  {

  case CAN_MSG_DEBUG_RES:
    GenDebugResMsgData(spCAN_Message);

#if(defined HUF_DEBUG) && (defined WIN32)
    //print("Tx CAN-Msg \"CAN_MSG_DEBUG_RES\"\n\r");
#endif
   break;

  case CAN_MSG_Debug_CYCLIC:
    GenNextDebugMsgData(spCAN_Message);

   break;

  case CAN_MSG_HMI_CYCLIC:
    BusMsgDoTeleFinished();
    GenHmiMsgData(spCAN_Message);
   break;

  case CAN_MSG_HMI_TEMP_CYCLIC:
    GenHmiTemperatureRefPresMsgData(spCAN_Message);
   break;

  default:
    //Breakpoint();
   if(uiCanMsgID != 0xFFU)
   {
      //Nop();
   }
    retVal = E_NOT_OK;
   break;
  }

  ClientIf_Debug_CanMsgTransmit(uiCanMsgID, spCAN_Message, retVal);

  return retVal;
}

static void CheckDbgReqMsgData(const tsCAN_Message *spCAN_Message)
{
  DCH_CheckCanDebugRequest(spCAN_Message);
}

static void GenNextDebugMsgData(tsCAN_Message *spCAN_Message)
{
  DCM_DataToTransmitOnCAN(spCAN_Message);
}

static void GenDebugResMsgData(tsCAN_Message *spCAN_Message)
{
  DCH_GetCanDebugResponseData(spCAN_Message);
}

static void GenHmiMsgData(tsCAN_Message *spCAN_Message)
{
   boolean l_bSendRealDataStatus = FALSE;
    tuCAN_HMI_Data l_sHMI;

#ifdef FILTER_SYMC_CAN_MSGS
    l_bSendRealDataStatus = SendRealReData();
#else
    l_bSendRealDataStatus = TRUE;
#endif

    l_sHMI .sHMI .b6Gap1 = BUSMSG_GAP1_DEFAULT;

    l_sHMI.sHMI.bTPS_FR = ( 0x07 & BusMsgGetWarning(BUSMSG_TYRE_VR) );
    l_sHMI.sHMI.bTPV_FR = ( 0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidVR():BUSMSG_TYREPRESS_INVALID) );
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_FR)
   {
      l_sHMI.sHMI.ucTP_FR = cInvalidPressureCAN;
   }
   else{
      l_sHMI.sHMI.ucTP_FR = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_VR);
   }
    l_sHMI.sHMI.bTemp_Warning_FR = ( 0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_VR) );

    l_sHMI.sHMI.bTPS_FL = ( 0x07 & BusMsgGetWarning(BUSMSG_TYRE_VL) );
    l_sHMI.sHMI.bTPV_FL = ( 0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidVL():BUSMSG_TYREPRESS_INVALID) );
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_FL)
   {
      l_sHMI.sHMI.ucTP_FL = cInvalidPressureCAN;
   }
   else{
      l_sHMI.sHMI.ucTP_FL = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_VL);
   }
    l_sHMI.sHMI.bTemp_Warning_FL = ( 0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_VL) );

    l_sHMI.sHMI.bTPS_RR = ( 0x07 & BusMsgGetWarning(BUSMSG_TYRE_HR) );
    l_sHMI.sHMI.bTPV_RR = ( 0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidHR():BUSMSG_TYREPRESS_INVALID) );
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_RR)
   {
      l_sHMI.sHMI.ucTP_RR = cInvalidPressureCAN;
   }
   else{
      l_sHMI.sHMI.ucTP_RR = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_HR);
   }
    l_sHMI.sHMI.bTemp_Warning_RR = ( 0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_HR) );

    l_sHMI.sHMI.bTPS_RL = ( 0x07 & BusMsgGetWarning(BUSMSG_TYRE_HL) );
    l_sHMI.sHMI.bTPV_RL = ( 0x01 & ((l_bSendRealDataStatus == TRUE) ? BusMsgGetTyrePressValidHL():BUSMSG_TYREPRESS_INVALID) );
   if(BUSMSG_TYREPRESS_INVALID == l_sHMI.sHMI.bTPV_RL)
   {
      l_sHMI.sHMI.ucTP_RL = cInvalidPressureCAN;
   }
   else{
      l_sHMI.sHMI.ucTP_RL = BusMsgGetTyrePressUncomp(BUSMSG_TYRE_HL);
   }
    l_sHMI.sHMI.bTemp_Warning_RL = ( 0x01 & BusMsgGetTemperatureWarning(BUSMSG_TYRE_HL) );

    l_sHMI.sHMI.bTMP_S = SilaGetState();

    l_sHMI.sHMI.bTPMS_Locate_Status = ((bGetBitBetriebszustandBZ(cWA_FINISH) == TRUE) ? 1U:0U);
    l_sHMI.sHMI.bTPMS_Learn_Status = ((bGetBitBetriebszustandBZ(cER_FINISH) == TRUE) ? 1U:0U);

    *spCAN_Message = l_sHMI.sMsgsBytes;
}

static void GenHmiTemperatureRefPresMsgData(tsCAN_Message *spCAN_Message)
{
  tuCAN_HMI_Data l_sHMIData;
  uint8 U8_RefPres;

  if(VehStateGetRoadmode() != 0)
  {
    U8_RefPres = NvM3_GETucVarCodOffroadPlacardPress();
  }
  else{
    U8_RefPres = GETucVarCodPlacardPressEE();
  }

  BusMsgDetermineTemperatures();

  if(SendRealReData() == TRUE)
  {
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

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalTirePosition(uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;
  uint8 l_ucRadPos;

  l_ucRadPos = GETucRadpositionPD(ucWheelIndexTire);

  switch(l_ucRadPos)
  {
  case 0U:
    l_ucRet = ACHSE1_LI;
   break;
  case 1U:
    l_ucRet = ACHSE1_RI;
   break;
  case 2U:
    l_ucRet = ACHSE2_LI;
   break;
  case 3U:
    l_ucRet = ACHSE2_RI;
   break;
  default:
    l_ucRet = UNKNOWN_RAD_POSITION;
   break;
  }

  if(l_ucRet == UNKNOWN_RAD_POSITION)
  {
    l_ucRet = UC_SIGNAL_NOT_AVAILABLE;
  }
  else{
    l_ucRet = l_ucRet;
  }

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalTirePressure(uint8 ucZomPos)
{
  uint8 l_ucRet;
  uint8 l_ucZomRadPos;

  l_ucZomRadPos = GETucRadpositionPD(ucZomPos);
  l_ucRet       = BusMsgGetTyrePressUncomp(l_ucZomRadPos);

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalTireTemperature(uint8 ucWheelIndexTire)
{
  uint8  l_ucRet;
  sint8  l_scTemp;
  sint16 l_siTemp;

  l_scTemp = GETscTemperaturPD(ucWheelIndexTire);

  if(l_scTemp == RE_TEMP_INVALID_HUF)
  {
    l_ucRet  = UC_SIGNAL_NOT_AVAILABLE;
  }
  else{

    l_siTemp  = l_scTemp;
    l_siTemp += (sint8)RE_TEMP_OFFSET_CAN;
    l_ucRet   = (uint8) (0xFF & l_siTemp);
  }

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalTireState(uint8 ucZomPos)
{
  uint8 l_ucRet;
  uint8 l_ucZomRadPos;

  l_ucZomRadPos = GETucRadpositionPD(ucZomPos);
  l_ucRet       = BusMsgGetWarning(l_ucZomRadPos);

#ifdef HUF_DEBUG
  if(l_ucRet > 3)
  {

    Breakpoint();
    l_ucRet = BUSMSG_WARN_UNKNOWN;
  }
  else{

  }

#endif
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalMalfuncBulb(uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;
  tSilaStateType l_eSilaState;

  l_eSilaState = SilaGetState();
  switch(l_eSilaState)
  {
  case SILA_STATE_NORMAL_OFF:
    l_ucRet = 0U;
   break;
  case SILA_STATE_PERMANENT_ON:
    l_ucRet = 1U;
   break;
  case SILA_STATE_MALFUNCTIONFLASH:
    l_ucRet = 2U;
   break;
  case SILA_STATE_CHECK:
  default:
    l_ucRet = 3U;
   break;
  }
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalTpmsIndication(void){
  uint8 l_ucRet;

  l_ucRet = GetSystem_Data_TpmsIndication();

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static boolean GetSignalPacardValuesValid(void){
  boolean l_bRet;

  l_bRet = GetSystem_Data_PacardValuesValid();
  return(l_bRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalSensorNoRx(uint8 ucZomPos)
{
  uint8 l_ucRet;
  uint8 l_ucZomRadPos;
  uint8 l_ucBits;

  uint16 l_uiError;

  l_ucZomRadPos = GETucRadpositionPD(ucZomPos);

  l_uiError = GETucReErrorStatusEE();
  l_uiError = l_uiError & 0x0FU;

  l_ucBits = ( (0xFF) & ( 0x01U << l_ucZomRadPos)) ;
  if((l_uiError & l_ucBits) == l_ucBits)
  {
    l_ucRet = TRUE;
  }
  else{
    l_ucRet = FALSE;
  }

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalSensorBatLow(uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;

  l_ucRet = GETucRestlebensdauerPD(ucWheelIndexTire);

  if(l_ucRet == cInvalidRElifeTime)
  {
    l_ucRet = 3U;
  }
  else{
    l_ucRet = bIsReLowLifeTimePD(ucWheelIndexTire);
   if(l_ucRet == TRUE)
   {
      l_ucRet = 1U;
   }
   else{
      l_ucRet = 0U;
   }
  }

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalSensorRsDefect(uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;

  uint16 l_uiDefect;
  l_uiDefect = GETushSensorDefectPD(ucWheelIndexTire);
  if((l_uiDefect & RE_AK_SF_RS_RL_FAIL) == RE_AK_SF_RS_RL_FAIL)
  {
    l_ucRet = TRUE;
  }
  else{
    l_ucRet = FALSE;
  }
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalSensorSpin(uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;

  l_ucRet = GETucWheelDirPD(ucWheelIndexTire);
  if(l_ucRet == cInvalidWheelDir)
  {
    l_ucRet = 0x03U;
  }
#ifdef HUF_DEBUG
  if(l_ucRet > 0x03U)
  {
    Breakpoint();
  }
#endif
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalBatLifeRemaining (uint8 ucWheelIndexTire)
{
  uint8 l_ucRet;

  l_ucRet = GETucRestlebensdauerPD(ucWheelIndexTire);

  if(l_ucRet == cInvalidRElifeTime)
  {
    l_ucRet = UC_SIGNAL_NOT_AVAILABLE;
  }
  else{
    l_ucRet = (uint8)(l_ucRet & 0x7FU);
  }
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalReserved01(uint8 ucWheelIndexTire)
{
  uint16 l_uiBZ;
  uint8  l_ucRet;

  l_uiBZ = ushGetBetriebszustandBZ(0xFF00U);
  l_ucRet = (uint8)(l_uiBZ >> 8U);

  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 GetSignalReserved02(uint8 ucWheelIndexTire)
{
  uint16 l_uiBZ;
  uint8  l_ucRet;

  l_uiBZ = ushGetBetriebszustandBZ(0x00FFU);
  l_ucRet = (uint8) ( 0xFF & (l_uiBZ >> 0U) );

  return(l_ucRet);
}
#endif

