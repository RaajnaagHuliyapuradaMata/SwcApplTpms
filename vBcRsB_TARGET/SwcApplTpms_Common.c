/******************************************************************************/
/* File   : SwcApplTpms_Common.c                                              */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
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
};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint16 m_uiSystemTicks_ms;
static uint8  m_ucSystemTicks_sec;
static uint8  m_ucSystemTicks_min;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
       void    Init_Huf_Common(void);
       void    Huf_SWC_Basic_Timer(void);
       uint8   GetNextWheelIndex(uint8 *ucpWheelIndex);
static uint8   CalcCrc8(const uint8 ui8BasePtr[], uint8 ui8BufLen);
       uint8   GetSystem_Data_MalfunctionBulb(void);

void Init_Huf_Common(void){
  Init_OSEK();
  m_uiSystemTicks_ms  = 0U;
  m_ucSystemTicks_sec = 0U;
  m_ucSystemTicks_min = 0U;
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

void Huf_SWC_Basic_Timer(void){
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
      for(u8Cnt = 0; u8Cnt < SwcApplTpms_eError_MAX_NUMBER;u8Cnt++)
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

static uint8 CalcCrc8(const uint8 ui8BasePtr[], uint8 ui8BufLen){
   uint8 l_ucLauf, ui8CRCReg = (uint8) 0xAA;
   for(l_ucLauf = 0U;l_ucLauf < ui8BufLen;l_ucLauf++){
        ui8CRCReg = aucCRC2fTab [ui8BasePtr[l_ucLauf] ^ ui8CRCReg ];
   }
    return(ui8CRCReg);
}

boolean HufIf_CheckCRC8(const uint8 * pucAkTel, const uint8 lu8Len){
  boolean l_bRet;
  uint8 l_ucCRC_Calc;
  uint8 l_lu8Len;
  l_lu8Len = ucGetLen4Cmd(*pucAkTel);
  if((l_lu8Len != 0U) && (lu8Len != 0U) && (l_lu8Len == (lu8Len - 1))){
    l_ucCRC_Calc = CalcCrc8(pucAkTel, l_lu8Len);
   if(l_ucCRC_Calc == pucAkTel[l_lu8Len]){
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

uint16  GetBaseLevel(void){
  return g_sEnv_Data.uiNoiseRSSI;
}

void EvBCMFaultStatusChanged(boolean bBCMFault)
{
  if(TRUE == bBCMFault)
  {
    NvM_WriteData_ECUDefect(U8_ECU_DEFECT_FAULT_BIT_SET);
    SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

