/******************************************************************************/
/* File   : SwcApplTpms_OSEK_If.c                                             */
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
#include "StatisticsX.hpp"
#include "StatemanagerX.hpp"
#include "SwcApplTpms_LearnEOL.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define EtWUFailDet             0x01U
#define EtStatemanager          0x02U
#define MAX_ALARMS              0x08U
#define AlActivateWUFD          0x00U
#define AlDeactivateWUFD        0x01U
#define AlProceedWUFD           0x02U
#define AlEOLRoutineCnt         0x03U
#define AlZOTime                0x04U
#define AlIDOM                  0x05U
#define AlMinuteCnt             0x06U
#define AlMissedRXCnt           0x07U
#define EvExceedVThres          ((uint16)0x0001U)
#define EvUnderrunVThres        ((uint16)0x0002U)
#define EvActivateWUFailDet     ((uint16)0x0004U)
#define EvDeactivateWUFailDet   ((uint16)0x0008U)
#define EvProceedWUFailDet      ((uint16)0x0010U)
#define EvEOLRoutineCnt         ((uint16)0x0020U)
#define EvZOTimeout             ((uint16)0x0040U)
#define EvIDOMTimeout           ((uint16)0x0080U)
#define EvMinuteCnt             ((uint16)0x0100U)
#define EvMissedRXCnt           ((uint16)0x0200U)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct struct_OS_Alarms{
   boolean bAlarmState;
   uint16 uiStartTime;
   uint16 uiPeriodTime;
   uint16 uiSecCnt;
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static struct struct_OS_Alarms m_sOsAlarms[MAX_ALARMS];
static uint16 m_uiEvExceedVThres;
static uint16 m_uiEvUnderrunVThres;
static uint16 m_uiEvActivateWUFailDet;
static uint16 m_uiEvDeactivateWUFailDet;
static uint16 m_uiEvProceedWUFailDet;
static uint16 m_uiEvEOLRoutineCnt;
static uint16 m_uiEvZOTimeout;
static uint16 m_uiEvIDOMTimeout;
static uint16 m_uiEvMinuteCnt;
static uint16 m_uiEvMissedRXCnt;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void SwcIf_TASK_EtWUFailDet(
   void);
static void SwcIf_TASK_EtStatemanager(
   void);
static void SwcIf_GetEvent(
   uint16 uiTaskNr,
   uint16* uipEvent);
static void SwcIf_ClearEvent(
   uint16 uiTaskNr,
   uint16 uiEvent);
static void Check_OS_Alarm(
   uint8 ucSystemSeconds);
static boolean Get_OS_Alarm(
   uint8 u8AlarmIndex,
   uint16* pushAlarmTicks);

void Init_OSEK(
   void){
   uint8 l_ucLauf;
   for(l_ucLauf = 0U; l_ucLauf < MAX_ALARMS; l_ucLauf++){
      m_sOsAlarms[l_ucLauf].bAlarmState = FALSE;
      m_sOsAlarms[l_ucLauf].uiPeriodTime = 0U;
      m_sOsAlarms[l_ucLauf].uiStartTime = 0U;
      m_sOsAlarms[l_ucLauf].uiSecCnt = 0U;
   }
   m_uiEvExceedVThres = FALSE;
   m_uiEvUnderrunVThres = FALSE;
   m_uiEvActivateWUFailDet = FALSE;
   m_uiEvDeactivateWUFailDet = FALSE;
   m_uiEvProceedWUFailDet = FALSE;
   m_uiEvEOLRoutineCnt = FALSE;
   m_uiEvZOTimeout = FALSE;
   m_uiEvIDOMTimeout = FALSE;
   m_uiEvMinuteCnt = FALSE;
   m_uiEvMissedRXCnt = FALSE;
}

void SwcIf_OSEK_MainTask(
   uint8 ucSystemSeconds){
   Check_OS_Alarm(
      ucSystemSeconds);
   SwcIf_TASK_EtStatemanager();
   SwcIf_TASK_EtWUFailDet();
}

static void SwcIf_TASK_EtStatemanager(
   void){
   uint16 l_uiEvent = 0U;
   SwcIf_GetEvent(
      EtStatemanager,
      &l_uiEvent);
   if((l_uiEvent & EvZOTimeout) == EvZOTimeout){
      EvZOTimeoutSM();
      SwcIf_ClearEvent(
         EtStatemanager,
         EvZOTimeout);
   }
   if((l_uiEvent & EvIDOMTimeout) == EvIDOMTimeout){
      EvIDOMTimeoutSM();
      SwcIf_ClearEvent(
         EtStatemanager,
         EvIDOMTimeout);
   }
   if((l_uiEvent & EvMinuteCnt) == EvMinuteCnt){
      EvMinuteCntSM();
      SwcIf_ClearEvent(
         EtStatemanager,
         EvMinuteCnt);
   }
}

static void SwcIf_TASK_EtWUFailDet(
   void){
   uint16 l_uiEvent = 0U;
   SwcIf_GetEvent(
      EtWUFailDet,
      &l_uiEvent);
   if((l_uiEvent & EvExceedVThres) == EvExceedVThres){
      ExceedVThresSTATISTICS();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvExceedVThres);
   }
   else{
      if((l_uiEvent & EvUnderrunVThres) == EvUnderrunVThres){
         UnderrunVThresSTATISTICS();
         SwcIf_ClearEvent(
            EtWUFailDet,
            EvUnderrunVThres);
      }
   }
   if((l_uiEvent & EvActivateWUFailDet) == EvActivateWUFailDet){
      ActivateWUFDSTATISTICS();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvActivateWUFailDet);
   }
   if((l_uiEvent & EvDeactivateWUFailDet) == EvDeactivateWUFailDet){
      DeactivateWUFDSTATISTICS();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvDeactivateWUFailDet);
   }
   if((l_uiEvent & EvProceedWUFailDet) == EvProceedWUFailDet){
      ProceedWUFDSTATISTICS();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvProceedWUFailDet);
   }
   if((l_uiEvent & EvEOLRoutineCnt) == EvEOLRoutineCnt){
      (void)EOL_CheckPeriodicLearnRoutineStatus();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvEOLRoutineCnt);
   }
   if((l_uiEvent & EvMissedRXCnt) == EvMissedRXCnt){
      MissedCntStatistics();
      SwcIf_ClearEvent(
         EtWUFailDet,
         EvMissedRXCnt);
   }
}

static void SwcIf_GetEvent(
   uint16 uiTaskNr,
   uint16* uipEvent){
   *uipEvent = 0U;
   switch(uiTaskNr){
      case EtWUFailDet: {
         *uipEvent = m_uiEvExceedVThres | m_uiEvUnderrunVThres | m_uiEvActivateWUFailDet | m_uiEvDeactivateWUFailDet | m_uiEvProceedWUFailDet | m_uiEvEOLRoutineCnt | m_uiEvMissedRXCnt;
         break;
      }
      case EtStatemanager: {
         *uipEvent = m_uiEvZOTimeout | m_uiEvIDOMTimeout | m_uiEvMinuteCnt;
         break;
      }
      default: {
         break;
      }
   }
}

static void SwcIf_ClearEvent(
   uint16 uiTaskNr,
   uint16 uiEvent){
   switch(uiTaskNr){
      case EtWUFailDet: {
         switch(uiEvent){
            case EvExceedVThres: {
               m_uiEvExceedVThres = FALSE;
               break;
            }
            case EvUnderrunVThres: {
               m_uiEvUnderrunVThres = FALSE;
               break;
            }
            case EvActivateWUFailDet: {
               m_uiEvActivateWUFailDet = FALSE;
               break;
            }
            case EvDeactivateWUFailDet: {
               m_uiEvDeactivateWUFailDet = FALSE;
               break;
            }
            case EvProceedWUFailDet: {
               m_uiEvProceedWUFailDet = FALSE;
               break;
            }
            case EvEOLRoutineCnt: {
               m_uiEvEOLRoutineCnt = FALSE;
               break;
            }
            case EvMissedRXCnt: {
               m_uiEvMissedRXCnt = FALSE;
               break;
            }
            default: {
               break;
            }
         }
         break;
      }
      case EtStatemanager: {
         switch(uiEvent){
            case EvZOTimeout: {
               m_uiEvZOTimeout = FALSE;
               break;
            }
            case EvIDOMTimeout: {
               m_uiEvIDOMTimeout = FALSE;
               break;
            }
            case EvMinuteCnt: {
               m_uiEvMinuteCnt = FALSE;
               break;
            }
            default: {
               break;
            }
         }
         break;
      }
      default: {
         break;
      }
   }
}

static void Check_OS_Alarm(
   uint8 ucSystemSeconds){
   uint8 l_ucLauf;
   static uint8 sl_ucLastSystemSeconds = 0xFFU;
   if(sl_ucLastSystemSeconds != ucSystemSeconds){
      sl_ucLastSystemSeconds = ucSystemSeconds;
      for(l_ucLauf = 0U; l_ucLauf < MAX_ALARMS; l_ucLauf++){
         if(m_sOsAlarms[l_ucLauf].bAlarmState == TRUE){
            m_sOsAlarms[l_ucLauf].uiSecCnt++;
            if(m_sOsAlarms[l_ucLauf].uiSecCnt >= m_sOsAlarms[l_ucLauf].uiStartTime){
               switch(l_ucLauf){
                  case AlActivateWUFD:
                     m_uiEvActivateWUFailDet = EvActivateWUFailDet;
                     break;
                  case AlDeactivateWUFD:
                     m_uiEvDeactivateWUFailDet = EvDeactivateWUFailDet;
                     break;
                  case AlProceedWUFD:
                     m_uiEvProceedWUFailDet = EvProceedWUFailDet;
                     break;
                  case AlEOLRoutineCnt:
                     m_uiEvEOLRoutineCnt = EvEOLRoutineCnt;
                     break;
                  case AlZOTime:
                     m_uiEvZOTimeout = EvZOTimeout;
                     break;
                  case AlIDOM:
                     m_uiEvIDOMTimeout = EvIDOMTimeout;
                     break;
                  case AlMinuteCnt:
                     m_uiEvMinuteCnt = EvMinuteCnt;
                     break;
                  case AlMissedRXCnt:
                     m_uiEvMissedRXCnt = EvMissedRXCnt;
                     break;
                  default:
                     break;
               }
               if(m_sOsAlarms[l_ucLauf].uiPeriodTime > 0U){
                  m_sOsAlarms[l_ucLauf].uiStartTime = m_sOsAlarms[l_ucLauf].uiPeriodTime;
               }
               else{
                  m_sOsAlarms[l_ucLauf].bAlarmState = FALSE;
                  m_sOsAlarms[l_ucLauf].uiStartTime = 0U;
               }
               m_sOsAlarms[l_ucLauf].uiSecCnt = 0U;
            }
         }
      }
   }
}

static boolean Get_OS_Alarm(
   uint8 u8AlarmIndex,
   uint16* pushAlarmTicks){
   boolean bRetVal = FALSE;
   if(u8AlarmIndex < MAX_ALARMS){
      if(FALSE != m_sOsAlarms[u8AlarmIndex].bAlarmState){
         if(m_sOsAlarms[u8AlarmIndex].uiStartTime >= m_sOsAlarms[u8AlarmIndex].uiSecCnt){
            *pushAlarmTicks = m_sOsAlarms[u8AlarmIndex].uiStartTime - m_sOsAlarms[u8AlarmIndex].uiSecCnt;
            bRetVal = TRUE;
         }
         else{
            *pushAlarmTicks = 0;
            bRetVal = FALSE;
         }
      }
      else{
         *pushAlarmTicks = 0;
         bRetVal = FALSE;
      }
   }
   else{
      *pushAlarmTicks = 0;
      bRetVal = FALSE;
   }
   return bRetVal;
}

void SetEventEvExceedVThresOS(
   void){
   m_uiEvExceedVThres = EvExceedVThres;
}

void SetEventEvUnderrunVThresOS(
   void){
   m_uiEvUnderrunVThres = EvUnderrunVThres;
}

void SetRelAlarmAlActivateWUFDOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlActivateWUFD].bAlarmState = TRUE;
   m_sOsAlarms[AlActivateWUFD].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlActivateWUFD].uiStartTime = ushTime;
   m_sOsAlarms[AlActivateWUFD].uiSecCnt = 0U;
}

void SetRelAlarmAlDeactivateWUFDOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlDeactivateWUFD].bAlarmState = TRUE;
   m_sOsAlarms[AlDeactivateWUFD].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlDeactivateWUFD].uiStartTime = ushTime;
   m_sOsAlarms[AlDeactivateWUFD].uiSecCnt = 0U;
}

void SetRelAlarmAlProceedWUFDOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlProceedWUFD].bAlarmState = TRUE;
   m_sOsAlarms[AlProceedWUFD].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlProceedWUFD].uiStartTime = ushTime;
   m_sOsAlarms[AlProceedWUFD].uiSecCnt = 0U;
}

void SetRelAlarmAlEOLRoutineTimerOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlEOLRoutineCnt].bAlarmState = TRUE;
   m_sOsAlarms[AlEOLRoutineCnt].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlEOLRoutineCnt].uiStartTime = ushTime;
   m_sOsAlarms[AlEOLRoutineCnt].uiSecCnt = 0U;
}

void SetRelAlarmAlMinuteCntOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlMinuteCnt].bAlarmState = TRUE;
   m_sOsAlarms[AlMinuteCnt].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlMinuteCnt].uiStartTime = ushTime;
   m_sOsAlarms[AlMinuteCnt].uiSecCnt = 0U;
}

void SetRelAlarmAlZOTimeOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlZOTime].bAlarmState = TRUE;
   m_sOsAlarms[AlZOTime].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlZOTime].uiStartTime = ushTime;
   m_sOsAlarms[AlZOTime].uiSecCnt = 0U;
}

void SetRelAlarmAlIDOMOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlIDOM].bAlarmState = TRUE;
   m_sOsAlarms[AlIDOM].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlIDOM].uiStartTime = ushTime;
   m_sOsAlarms[AlIDOM].uiSecCnt = 0U;
}

void SetRelAlarmAlMissedRXCntOS(
   uint16 ushTime,
   uint16 ushPeriod){
   m_sOsAlarms[AlMissedRXCnt].bAlarmState = TRUE;
   m_sOsAlarms[AlMissedRXCnt].uiPeriodTime = ushPeriod;
   m_sOsAlarms[AlMissedRXCnt].uiStartTime = ushTime;
   m_sOsAlarms[AlMissedRXCnt].uiSecCnt = 0U;
}

void CancelAlarmAlActivateWUFDOS(
   void){
   m_sOsAlarms[AlActivateWUFD].bAlarmState = FALSE;
   m_sOsAlarms[AlActivateWUFD].uiPeriodTime = 0U;
   m_sOsAlarms[AlActivateWUFD].uiStartTime = 0U;
   m_sOsAlarms[AlActivateWUFD].uiSecCnt = 0U;
}

void CancelAlarmAlDeactivateWUFDOS(
   void){
   m_sOsAlarms[AlDeactivateWUFD].bAlarmState = FALSE;
   m_sOsAlarms[AlDeactivateWUFD].uiPeriodTime = 0U;
   m_sOsAlarms[AlDeactivateWUFD].uiStartTime = 0U;
   m_sOsAlarms[AlDeactivateWUFD].uiSecCnt = 0U;
}

void CancelAlarmAlProceedWUFDOS(
   void){
   m_sOsAlarms[AlProceedWUFD].bAlarmState = FALSE;
   m_sOsAlarms[AlProceedWUFD].uiPeriodTime = 0U;
   m_sOsAlarms[AlProceedWUFD].uiStartTime = 0U;
   m_sOsAlarms[AlProceedWUFD].uiSecCnt = 0U;
}

void CancelAlarmAlEOLRoutineTimerOS(
   void){
   m_sOsAlarms[AlEOLRoutineCnt].bAlarmState = FALSE;
   m_sOsAlarms[AlEOLRoutineCnt].uiPeriodTime = 0U;
   m_sOsAlarms[AlEOLRoutineCnt].uiStartTime = 0U;
   m_sOsAlarms[AlEOLRoutineCnt].uiSecCnt = 0U;
}

void CancelAlarmAlMinuteCntOS(
   void){
   m_sOsAlarms[AlMinuteCnt].bAlarmState = FALSE;
   m_sOsAlarms[AlMinuteCnt].uiPeriodTime = 0U;
   m_sOsAlarms[AlMinuteCnt].uiStartTime = 0U;
   m_sOsAlarms[AlMinuteCnt].uiSecCnt = 0U;
}

void CancelAlarmAlZOTimeOS(
   void){
   m_sOsAlarms[AlZOTime].bAlarmState = FALSE;
   m_sOsAlarms[AlZOTime].uiPeriodTime = 0U;
   m_sOsAlarms[AlZOTime].uiStartTime = 0U;
   m_sOsAlarms[AlZOTime].uiSecCnt = 0U;
}

void CancelAlarmAlIDOMOS(
   void){
   m_sOsAlarms[AlIDOM].bAlarmState = FALSE;
   m_sOsAlarms[AlIDOM].uiPeriodTime = 0U;
   m_sOsAlarms[AlIDOM].uiStartTime = 0U;
   m_sOsAlarms[AlIDOM].uiSecCnt = 0U;
}

void CancelAlarmAlMissedRxCntOS(
   void){
   m_sOsAlarms[AlMissedRXCnt].bAlarmState = FALSE;
   m_sOsAlarms[AlMissedRXCnt].uiPeriodTime = 0U;
   m_sOsAlarms[AlMissedRXCnt].uiStartTime = 0U;
   m_sOsAlarms[AlMissedRXCnt].uiSecCnt = 0U;
}

boolean GetAlarmAlZOTimeOS(
   uint16* pushAlarmTicks){
   boolean bRetVal = FALSE;
   bRetVal = Get_OS_Alarm(
      AlZOTime,
      pushAlarmTicks);
   return bRetVal;
}

boolean GetAlarmAlIDOMOS(
   uint16* pushAlarmTicks){
   boolean bRetVal = FALSE;
   bRetVal = Get_OS_Alarm(
      AlIDOM,
      pushAlarmTicks);
   return bRetVal;
}

boolean GetAlarmAlMinuteCntOS(
   uint16* pushAlarmTicks){
   boolean bRetVal = FALSE;
   bRetVal = Get_OS_Alarm(
      AlMinuteCnt,
      pushAlarmTicks);
   return bRetVal;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

