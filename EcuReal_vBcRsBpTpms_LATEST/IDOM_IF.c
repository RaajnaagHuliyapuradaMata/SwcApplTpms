/******************************************************************************/
/* File   : IDOM_IF.c                                                         */
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

#include "Tpms_Rte_Data_Type.hpp"
#include "iTPMS_Interface.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "IDOM_IF.hpp"
#include "CfgSwcApplTpms_IDOM.hpp"
#include "state_fzzX.hpp"
#include "statisticsX.hpp"

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

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint16 ushAlarmTimeInSec;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void StartIDOMAlarm(
   uint16 ushNrOfCurFF){
   if(((ushNrOfCurFF + ushAlarmTimeInSec) >= ushMaxTimeWithoutMsgInSec) && (ushNrOfCurFF < ushMaxTimeWithoutMsgInSec)){
      SetRelAlarmAlIDOMOS(
         (0xFFFF & (ushMaxTimeWithoutMsgInSec - ushNrOfCurFF)),
         0);
   }
   else{
      SetRelAlarmAlIDOMOS(
         ushAlarmTimeInSec,
         0);
   }
}

void StopIDOMAlarm(void){
   CancelAlarmAlIDOMOS();
   ushAlarmTimeInSec = ushHFiAlarmTimeInSec;
}

void BreakIDOMAlarm(void){
   uint16 ushHelp;
   uint8 u8AlarmStatus = FALSE;
   ushHelp = 0;
   u8AlarmStatus = GetAlarmAlIDOMOS(
      &ushHelp);
   if(FALSE != u8AlarmStatus){
      ushAlarmTimeInSec = ushHelp;
   }
   else{
      ushAlarmTimeInSec = 0;
   }
   CancelAlarmAlIDOMOS();
}

void GetIDOMInput(
   tIDOMInput* pIDOMInput){
   uint8 i = (unsigned char)0;
   uint16 usMaxFF = (unsigned short)0;
   for(i = 0; i < 4; i++){
      if(GETusFolgeAusfallCntSTATISTICS(
         i) > usMaxFF){
         usMaxFF = GETusFolgeAusfallCntSTATISTICS(
            i);
      }
   }
   pIDOMInput->u8ApplState = (unsigned char)bGetBitFahrzeugzustandFZZ(
      cRS_VTHRES);
   pIDOMInput->u16MaxFFCtVal = usMaxFF;
   pIDOMInput->u16CurBaseLevel = GetBaseLevel();
}

uint16 GetParaOffset(void){
   return ((uint16)GETucMinOffsetGXeEE());
}

uint16 GetParaOverlaps(void){
   return ((uint16)GETucOffsetOverlapsGXeEE());
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

