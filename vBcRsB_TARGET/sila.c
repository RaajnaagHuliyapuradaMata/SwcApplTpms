#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SilaX.hpp"

STATIC tSilaStateType ucSilaState;
STATIC tSilaStateType ucSilaStateOut;
STATIC tSilaStateType ucSilaStateInt;

void SilaInit(void){
   ucSilaState = SILA_STATE_NORMAL_OFF;
   ucSilaStateOut = SILA_STATE_NORMAL_OFF;
   ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}

void SilaPutState(
   tSilaStateType ucState){
   if((ucSilaStateInt == SILA_STATE_MALFUNCTIONFLASH) && (ucState == SILA_STATE_PERMANENT_ON)){
   }
   else{
      ucSilaStateInt = ucState;
   }
}

tSilaStateType SilaGetState(void){
   return (ucSilaStateOut);
}

void  SilaTask(void){
   ucSilaStateOut = ucSilaStateInt;
}
