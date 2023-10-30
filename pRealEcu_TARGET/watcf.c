#define WATCF_C

#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "watcf.hpp"
#include "watcfX.hpp"
#include "state_fzzX.hpp"
#include "wallocX.hpp"

void InitWATCF(
   void){
   ucAlZOTimeTicks = (uint8)0;
}

void StartWallocTOAlarm(
   uint8 ucTimeInSec){
   ControlWATO(
      cWATO_START_ALARM,
      ucTimeInSec);
}

void StopWallocTOAlarm(
   void){
   ControlWATO(
      cWATO_STOP_ALARM,
      0);
}

void ControlWATO(
   uint8 ucCommand,
   uint8 ucTimeInSec){
   uint16 ushHelp;
   switch(ucCommand){
      case cWATO_START_ALARM:
         ucAlZOTimeTicks = ucTimeInSec;
         if(ucAlZOTimeTicks != (uint8)0){
            CancelAlarmAlZOTimeOS();
            if(bGetBitFahrzeugzustandFZZ(
               cRS_VTHRES) == TRUE){
               SetRelAlarmAlZOTimeOS(
                  (uint16)ucAlZOTimeTicks,
                  (uint16)0);
            }
         }
         break;

      case cWATO_RESTART_ALARM:
         if(ucAlZOTimeTicks != (uint8)0){
            CancelAlarmAlZOTimeOS();
            SetRelAlarmAlZOTimeOS(
               (uint16)ucAlZOTimeTicks,
               (uint16)0);
         }
         else{
            CancelAlarmAlZOTimeOS();
            SetRelAlarmAlZOTimeOS(
               ucDefWATOTimeInSec,
               (uint16)0);
         }
         break;

      case cWATO_READ_ALARM:
         if(GetAlarmAlZOTimeOS(
            &ushHelp) == TRUE){
            ucAlZOTimeTicks = (uint8)ushHelp;
         }
         break;

      case cWATO_BREAK_ALARM:
         if(GetAlarmAlZOTimeOS(
            &ushHelp) == TRUE){
            ucAlZOTimeTicks = (uint8)ushHelp;
         }
         CancelAlarmAlZOTimeOS();
         break;

      default:
         CancelAlarmAlZOTimeOS();
         ucAlZOTimeTicks = ucTimeInSec;
         break;
   }
}

