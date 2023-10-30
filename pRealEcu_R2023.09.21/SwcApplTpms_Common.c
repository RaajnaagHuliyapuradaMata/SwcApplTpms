#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "tss_stdx.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "UsWarnX.hpp"
#include "ProcDatX.hpp"
#include "SilaX.hpp"
#include "MultiframeX.hpp"
#include "StatisticsX.hpp"
#include "CD_Decoder_X.hpp"
#include "statemanagerX.hpp"
#include "state_bzx.hpp"
#include "WnTypePar.hpp"
#include "IDOM_X.hpp"
#include "WallocX.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "DevCanHandling.hpp"
#include "SwcApplTpms_DTC_If.hpp"

#ifdef BUILD_WITH_UNUSED_DATA

#define RE_TEMP_OFFSET_AK            ((sint8)52)
#define RE_TEMP_INVALID_AK                0x00U
#define RE_TEMP_UNDERFLOW_AK              0x01U
#define RE_TEMP_VALID_MINIMUM_AK          0x02U
#define RE_TEMP_VALID_MAXIMUM_AK          0xEFU
#define RE_TEMP_OVERFLOW_F0_AK            0xF0U
#define RE_TEMP_OVERFLOW_F1_AK            0xF1U
#define RE_TEMP_OVERFLOW_F2_AK            0xF2U
#define RE_TEMP_OVERFLOW_F3_AK            0xF3U
#define RE_TEMP_OVERFLOW_F4_AK            0xF4U
#define RE_TEMP_OVERFLOW_F5_AK            0xF5U
#define RE_TEMP_OVERFLOW_F6_AK            0xF6U

#define RE_TEMP_MINIMUM_HUF      ((sint8)( -40))
#define RE_TEMP_MAXIMUM_HUF      ((sint8)( 120))
#define RE_TEMP_INVALID_HUF      ((sint8)(0x7F))

#endif

const unsigned char aucCRC2fTab[] = {
  0, 47, 94,113,188,147,226,205, 87,120,  9, 38,235,196,181,154,
174,129,240,223, 18, 61, 76, 99,249,214,167,136, 69,106, 27, 52,
115, 92, 45,  2,207,224,145,190, 36, 11,122, 85,152,183,198,233,
221,242,131,172, 97, 78, 63, 16,138,165,212,251, 54, 25,104, 71,
230,201,184,151, 90,117,  4, 43,177,158,239,192, 13, 34, 83,124,
 72,103, 22, 57,244,219,170,133, 31, 48, 65,110,163,140,253,210,
149,186,203,228, 41,  6,119, 88,194,237,156,179,126, 81, 32, 15,
 59, 20,101, 74,135,168,217,246,108, 67, 50, 29,208,255,142,161,
227,204,189,146, 95,112,  1, 46,180,155,234,197,  8, 39, 86,121,
 77, 98, 19, 60,241,222,175,128, 26, 53, 68,107,166,137,248,215,
144,191,206,225, 44,  3,114, 93,199,232,153,182,123, 84, 37, 10,
 62, 17, 96, 79,130,173,220,243,105, 70, 55, 24,213,250,139,164
   ,  5, 42, 91,116,185,150,231,200, 82,125, 12, 35,238,193,176,159,
171,132,245,218, 23, 56, 73,102,252,211,162,141, 64,111, 30, 49,
118, 89, 40,  7,202,229,148,187, 33, 14,127, 80,157,178,195,236,
216,247,134,169,100, 75, 58, 21,143,160,209,254, 51, 28,109, 66
};  // AK CRC table (polynom 0x2F)

#ifdef BUILD_WITH_UNUSED_DATA

struct struct_RE_Data
{
   uint32 ulID;
   uint8  ucPressure;
   sint8  scTemperature;
   uint8  ucRemainingLifeTime;
   uint8  ucTransMode;
   uint16 ushSensorDefect;
   uint8  ucRollSwitch;
   uint8  ucWheelDir;
};

struct  struct_sBitfeld_BZ
{
  bitfield bEigenradHist    :1;
  bitfield bZugeordnetHist  :1;
  bitfield bEigenrad        :1;
  bitfield bZugeordnet      :1;
  bitfield bBestaetigt      :1;
  bitfield bXdaCanOn        :1;
  bitfield bSystemActive    :1;
  bitfield UnusedBit8       :1;
  bitfield UnusedBit7       :1;
  bitfield UnusedBit6       :1;
  bitfield UnusedBit5       :1;
  bitfield UnusedBit4       :1;
  bitfield UnusedBit3       :1;
  bitfield UnusedBit2       :1;
  bitfield UnusedBit1       :1;
  bitfield UnusedBit0       :1;
};

struct  struct_sBitfeld_FZZ
{
  bitfield bMotor_laeuft     :1;
  bitfield bLiftAchseUp      :1;
  bitfield bLiftaxleAvailable:1;
  bitfield bAntUeberStromAkt :1;
  bitfield bAntUeberSpgAkt   :1;
  bitfield bSw_Kl15          :1;
  bitfield bFzg_faehrt       :1;
  bitfield bCan0_BusOff      :1;
  bitfield bUnusedbit7       :1;
  bitfield bUnusedBit6       :1;
  bitfield bUnusedBit5       :1;
  bitfield bUnusedBit4       :1;
  bitfield bUnusedBit3       :1;
  bitfield bUnusedBit2       :1;
  bitfield bUnusedBit1       :1;
  bitfield bUnusedBit0       :1;
};

struct struct_System
{
  boolean bPlacardValid;
  uint8 ucTpmsIndication;
  uint8 ucReserved01;
  uint8 ucReserved02;
};

static struct struct_System m_sSystem;

typedef struct{
  bitfield bUnused00             :1;
  bitfield bUnused01             :1;
  bitfield bUnused02             :1;
  bitfield bUnused03             :1;
  bitfield VBatLowTxOff          :1;
  bitfield VBatLowDtc            :1;
  bitfield WUDefect              :1;
  bitfield WUFailed              :1;

  bitfield RAMError              :1;
  bitfield ROMError              :1;
  bitfield HfRecDemErr           :1;
  bitfield HfRecRssiErr          :1;
  bitfield StopVDiag             :1;
  bitfield VBatSuspect           :1;
  bitfield VBatLow               :1;
  bitfield VBatHigh              :1;
}tBitfeldDI;

typedef struct{
  tBitfeldDI      b;
}tDIAG;

#endif

static uint16 m_uiSystemTicks_ms;
static uint8  m_ucSystemTicks_sec;
static uint8  m_ucSystemTicks_min;

#ifdef BUILD_WITH_UNUSED_DATA
static tDIAG tDiagnoseDI;
#endif

       void    Init_Huf_Common(void);
       void    Huf_SWC_Basic_Timer(void);
       uint8   GetNextWheelIndex(uint8 *ucpWheelIndex);
static uint8   CalcCrc8(const uint8 ui8BasePtr[], uint8 ui8BufLen);
       uint8   GetSystem_Data_MalfunctionBulb(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
       void    PUTbWUDefectDI(boolean bWUDefect);
       void    PUTbWUFailedDI(boolean bWUFailed);
       void    INCREMENT(uint8 *ucValue, uint8 ucThreshold);
       void    DECREMENT(uint8 *ucValue, uint8 ucThreshold);
       boolean HufIf_CheckCRC8(const uint8 *pucAkTel);
       uint8   GetSystem_Data_TpmsIndication(void);
       boolean GetSystem_Data_PacardValuesValid(void);
static void    SetSystem_Data_Reserved01(uint8 ucData);
       uint8   GetSystem_Data_Reserved01(void);
static void    SetSystem_Data_Reserved02(uint8 ucData);
       uint8   GetSystem_Data_Reserved02(void);
       sint8   Calc_Real_AK_Temperature(uint8 ucAk_TempInfo);
#endif //BUILD_WITH_UNUSED_FUNCTION

void Init_Huf_Common(void){

  Init_OSEK();

  m_uiSystemTicks_ms  = 0U;
  m_ucSystemTicks_sec = 0U;
  m_ucSystemTicks_min = 0U;

#ifdef BUILD_WITH_UNUSED_FUNCTION
  m_sSystem.bPlacardValid = TRUE;
  m_sSystem.ucTpmsIndication   = 0x00U;
  SetSystem_Data_Reserved01(0x00U);
  SetSystem_Data_Reserved02(0x00U);
#endif
  g_sEnv_Data.uiVehSpeed            = 0x00U;
  g_sEnv_Data.ucIgnition            = 0x00U;
  g_sEnv_Data.ucAmbTemperature      = 0xFFU;
  g_sEnv_Data.ucAthmosPressure      = 0xFFU;
  g_sEnv_Data.ucVehDirection        = 0x0DU;
  g_sEnv_Data.bECU_Fault            = 0x00U;
  g_sEnv_Data.uiNvmBlockConsistence = CU16_NVM_ALL_CATEG_CONSISTENT;
  g_sEnv_Data.uiNoiseRSSI           = 0xFFFFU;
  g_sEnv_Data.bRoadMode             = 0x00U;
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void INCREMENT(uint8 *ucValue,uint8 ucThreshold)
{
  if(*ucValue < ucThreshold)
  {
    ++(*ucValue);
  }
  else{
    (*ucValue) = 0U;
  }
}
void DECREMENT(uint8 *ucValue,uint8 ucThreshold)
{
  if(*ucValue > 0U)
  {
    --(*ucValue);
  }
  else{
    (*ucValue) = ucThreshold;
  }
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void Huf_SWC_Basic_Timer(void){
#ifdef HUF_DEBUG
  uint8 l_ucTestData;
#endif
#ifdef DEBUG_WARNING_THRESHOLDS
  uint8 Arr[8];
#endif

  if(m_uiSystemTicks_ms >= (HUF_SWC_TIME_1_SEC_DIVIDER - 1))
  {
    m_ucSystemTicks_sec++;
    m_uiSystemTicks_ms = 0U;

   if( (DTC_StatusOfDTC & cDTC_STATE_CHANGED) == cDTC_STATE_CHANGED)
   {
      NvM2_PutDTCSingleActiveStatusEE(DTC_IsDTCInActiveState);
      StoreSTATISTICS();
   }

   if( (DTC_StatusOfDTC & cDTC_WAS_DELETED_TROUGH_DIAG) == cDTC_WAS_DELETED_TROUGH_DIAG )
   {
      uint8 u8Cnt;
      for(u8Cnt = 0; u8Cnt < E_TPMS_ERROR_MAX_NUMBER;u8Cnt++)
      {
        if(DTC_GetActiveStatusOfDTC(u8Cnt) == TRUE)
        {
          SetCurrentErrorERR(u8Cnt);
        }
        else{

        }
      }

      DTC_StatusOfDTC = cDTC_IS_CLEARED;
      DTC_SaveActiveStatustoEE();
   }
   else{

   }

    TimerWT(ucCountc);
    OperateAtmosphericPressure();
    Increment_AxImbSuppressionCounter();
   CalcPatmo();
    WALLOC_UpdateTelegramSkipTimer();

#ifdef HUF_DEBUG
    l_ucTestData = (uint8)((((uint16)m_ucSystemTicks_min * 60U) + m_ucSystemTicks_sec) >> 8U);
    SetSystem_Data_Reserved01(l_ucTestData);
    l_ucTestData = (uint8)((((uint16)m_ucSystemTicks_min * 60U) + m_ucSystemTicks_sec) >> 0U);
    SetSystem_Data_Reserved02(l_ucTestData);
#endif
#ifdef DEBUG_WARNING_THRESHOLDS
    DebugWarnTresh(&Arr[0]);
#endif
    DCM_CyclicDebugSystemDataUpdate();
  }
  else{

    m_uiSystemTicks_ms++;
  }

  SilaTask();

  TimeMF();

  if(g_sEnv_Data.uiVehSpeed == 0)
  {
   PunctureWarningReset();
  }

  SM_TimerProcessForSpeedValueInUseStatus();

  IDOM();

  SequenceControlSM();

  if(m_ucSystemTicks_sec >= 60U)
  {
    m_ucSystemTicks_sec = 0U;
    m_ucSystemTicks_min++;
  }

  if(m_ucSystemTicks_min >= 60U)
  {
    m_ucSystemTicks_min = 0U;
  }

  CheckWUFDVThresSTATISTICS();

  SwcIf_OSEK_MainTask(m_ucSystemTicks_sec);
}

#ifdef UNUSED_CODE
static uint8 GetGvcAnzVerbRe(void){
  return(cAnzRad);
}

static uint8 GetIsoPosOfLegalVehicleWheels(uint8 ucWheelIndex)
{
  const uint8 cl_ucaValidGvcWheelPos[cAnzRad] = {ACHSE1_LI,ACHSE1_RI,ACHSE2_LI,ACHSE2_RI};
        uint8 l_ucIsoPos;

  l_ucIsoPos = UNKNOWN_RAD_POSITION;

  if(ucWheelIndex < cAnzRad)
  {

    l_ucIsoPos = cl_ucaValidGvcWheelPos[ucWheelIndex];
  }
  return(l_ucIsoPos);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetNextWheelIndex(uint8 *ucpWheelIndex)
{
  const uint8 cl_ucaValidWheelPos[cAnzRad] = {ACHSE1_LI,ACHSE1_RI,ACHSE2_LI,ACHSE2_RI};
        uint8  l_ucIsoPos;
        uint8  l_ucZomRadPos;
        uint8  l_ucOriginalNr;
        uint8  l_ucSecurityCnt;

  l_ucSecurityCnt = 0U;
  l_ucOriginalNr  = *ucpWheelIndex;
  l_ucIsoPos      = UNKNOWN_RAD_POSITION;

  do
  {
    l_ucSecurityCnt++;
   if(*ucpWheelIndex < (cAnzRad-1U))
   {
      (*ucpWheelIndex)++;
   }
   else{
      *ucpWheelIndex = 0U;
   }

    l_ucZomRadPos = GETucRadpositionPD(*ucpWheelIndex);

   if(l_ucZomRadPos == 0xF0U)
   {
      l_ucIsoPos = cl_ucaValidWheelPos[*ucpWheelIndex];
   }
   else{
      l_ucIsoPos = cl_ucaValidWheelPos[l_ucZomRadPos];
   }
  }
  while((l_ucIsoPos      == UNKNOWN_RAD_POSITION)&&
        (l_ucSecurityCnt  < cAnzRad             )  );

  if(l_ucSecurityCnt >= cAnzRad)
  {
    *ucpWheelIndex = l_ucOriginalNr;
  }
  else{

  }
  return(l_ucIsoPos);
}

#endif // BUILD_WITH_UNUSED_FUNCTION

static uint8 CalcCrc8(const uint8 ui8BasePtr[], uint8 ui8BufLen){
   uint8 l_ucLauf, ui8CRCReg = (uint8) 0xAA;
   for(l_ucLauf = 0U;l_ucLauf < ui8BufLen;l_ucLauf++){
        ui8CRCReg = aucCRC2fTab [ui8BasePtr[l_ucLauf] ^ ui8CRCReg ];
   }
    return(ui8CRCReg);
}

boolean HufIf_CheckCRC8(const uint8 * pucAkTel, const uint8 ucLen){
  boolean l_bRet;
  uint8 l_ucCRC_Calc;
  uint8 l_ucLen;
  l_ucLen = ucGetLen4Cmd(*pucAkTel);
  if((l_ucLen != 0U) && (ucLen != 0U) && (l_ucLen == (ucLen - 1))){
    l_ucCRC_Calc = CalcCrc8(pucAkTel, l_ucLen);
   if(l_ucCRC_Calc == pucAkTel[l_ucLen]){
      l_bRet = TRUE;
   }
   else{
      l_bRet = FALSE;
   }
  }
  else{
    l_bRet = FALSE;
  }
  return (l_bRet);
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetSystem_Data_TpmsIndication(void){
  uint8 l_ucRet;

  l_ucRet = m_sSystem.ucTpmsIndication;
  return (l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

boolean GetSystem_Data_PacardValuesValid(void){
  boolean l_bRet;

  l_bRet = m_sSystem.bPlacardValid;
  return (l_bRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static void SetSystem_Data_Reserved01(uint8 ucData)
{
  m_sSystem.ucReserved01 = ucData;
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetSystem_Data_Reserved01(void){
  uint8 l_ucRet;

  l_ucRet = m_sSystem.ucReserved01;
  return (l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static void SetSystem_Data_Reserved02(uint8 ucData)
{
  m_sSystem.ucReserved02 = ucData;
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetSystem_Data_Reserved02(void){
  uint8 l_ucRet;

  l_ucRet = m_sSystem.ucReserved02;
  return (l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

sint8 Calc_Real_AK_Temperature(uint8 ucAk_TempInfo)
{
  uint8  l_ucTempInfo;
  sint16 l_siTest;
  sint8 l_scTempReal;

  l_ucTempInfo = ucAk_TempInfo;

  if(l_ucTempInfo == RE_TEMP_INVALID_AK)
  {
    l_scTempReal = RE_TEMP_INVALID_HUF;
  }

  else if(l_ucTempInfo == RE_TEMP_UNDERFLOW_AK)
  {
    l_scTempReal = RE_TEMP_MINIMUM_HUF;
  }

  else if(l_ucTempInfo <= RE_TEMP_VALID_MAXIMUM_AK)
  {

    l_siTest = (sint16)l_ucTempInfo;

    l_siTest = (l_siTest - RE_TEMP_OFFSET_AK);

   if(l_siTest < RE_TEMP_MINIMUM_HUF)
   {
      l_scTempReal = RE_TEMP_MINIMUM_HUF;
   }
   else if(l_siTest > RE_TEMP_MAXIMUM_HUF)
   {
      l_scTempReal = RE_TEMP_MAXIMUM_HUF;
   }
   else{

      l_scTempReal = (sint8)l_siTest;
   }
  }

  else{
   switch(l_ucTempInfo)
   {
      case RE_TEMP_OVERFLOW_F0_AK:
        l_scTempReal =  89;
        break;
      case RE_TEMP_OVERFLOW_F1_AK:
        l_scTempReal =  94;
        break;
      case RE_TEMP_OVERFLOW_F2_AK:
        l_scTempReal =  99;
        break;
      case RE_TEMP_OVERFLOW_F3_AK:
        l_scTempReal = 104;
        break;
      case RE_TEMP_OVERFLOW_F4_AK:
        l_scTempReal = 109;
        break;
      case RE_TEMP_OVERFLOW_F5_AK:
        l_scTempReal = 114;
        break;
      case RE_TEMP_OVERFLOW_F6_AK:
        l_scTempReal = 119;
        break;
      default:
        l_scTempReal = RE_TEMP_MAXIMUM_HUF;
      break;
   }
  }
  return(l_scTempReal);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

void PUTbWUDefectDI( boolean bWUDefect )
{
  tDiagnoseDI.b.WUDefect = bWUDefect;
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

void PUTbWUFailedDI( boolean bWUFailed )
{
  tDiagnoseDI.b.WUFailed = bWUFailed;
}
#endif

uint16  GetBaseLevel(void){

  return g_sEnv_Data.uiNoiseRSSI;
}

void EvBCMFaultStatusChanged(boolean bBCMFault)
{
  if(TRUE == bBCMFault)
  {
    NvM_WriteData_ECUDefect(U8_ECU_DEFECT_FAULT_BIT_SET);
    SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
    ResetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
  }
  else{
    NvM_WriteData_ECUDefect(U8_ECU_NOT_DEFECT);
    DeleteCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
  }
}

boolean GetSystem_DefectECUState(void){
  boolean bRetVal = FALSE;
  uint8 u8ECUStatus = U8_ECU_NOT_DEFECT;

  NvM_ReadData_ECUDefect(&u8ECUStatus);

  if(U8_ECU_NOT_DEFECT != u8ECUStatus)
  {

   bRetVal = TRUE;
  }
  else{

   bRetVal = FALSE;
  }

  return bRetVal;
}

void GetSystem_TpmsStatus(uint8* pucStatus)
{

  *pucStatus = 0x00;

  *pucStatus |= (((SilaGetState() == SILA_STATE_MALFUNCTIONFLASH) ? 0U:1U)<<0);

  *pucStatus |= ((((bGetBitBetriebszustandBZ(cWA_FINISH) == TRUE)&&(DCH_IsContinousAPCReadingActive() == FALSE))  ?  1U:0U)<<1);

  *pucStatus |= (((DCH_SubmultiplexConfigGetStatus() == TRUE) ? 1U:0U)<<2);

  *pucStatus |= (((bGetBitBetriebszustandBZ(cER_FINISH) == TRUE) ? 1U:0U)<<3);

  *pucStatus |= ((( DCH_IsDeveloperModeActive() == TRUE) ? 1U:0U)<<4);
}

#ifdef WIN32

uint32 GetSystem_TimeMs(void){
  uint32 u32Time = 0;

  u32Time = ((uint32)m_ucSystemTicks_min * 60000) + ((uint32)m_ucSystemTicks_sec * 1000) + ((uint32)m_uiSystemTicks_ms * HUF_SWC_BASE_TIME_MS);

  return u32Time;
}
#endif

#ifdef HUF_DEBUG
uint8* ucpGetPointer_ucSystemTicks_sec(void){
  uint8* l_ucpRet;
  l_ucpRet = &m_ucSystemTicks_sec;
  return(l_ucpRet);
}
#endif

