#include "Std_Types.hpp"

#include "Tpms_Rte_Data_Type.hpp"
#include "iTPMS_Interface.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "IDOM_IF.hpp"
#include "CfgSwcApplTpms_IDOM.hpp"
#include "state_fzzX.hpp"
#include "statisticsX.hpp"

static uint16 ushAlarmTimeInSec;

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
   pIDOMInput->ucApplState = (unsigned char)bGetBitFahrzeugzustandFZZ(
      cRS_VTHRES);
   pIDOMInput->ushMaxFFCtVal = usMaxFF;
   pIDOMInput->ushCurBaseLevel = GetBaseLevel();
}

uint16 GetParaOffset(void){
   return ((uint16)GETucMinOffsetGXeEE());
}

uint16 GetParaOverlaps(void){
   return ((uint16)GETucOffsetOverlapsGXeEE());
}
