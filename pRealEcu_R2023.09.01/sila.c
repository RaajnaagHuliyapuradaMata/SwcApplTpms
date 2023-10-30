

#ifdef IBTCM_SW_ANPASSUNGEN
   #include "iTpms_Interface.hpp"
   #include "SwcApplTpms_Rte.hpp"
   #include "SilaX.hpp"
   #include "sila.hpp"
#else
   #include "SilaX.hpp"
   #include "sila.hpp"
   #include "transmitX.hpp"
   #include "eecata2_ifX.hpp"
   #include "applmainX.hpp"

   #include "testvi.hpp"
   #include "testviX.hpp"
#endif

STATIC tSilaStateType ucSilaState;
STATIC tSilaStateType ucSilaStateOut;
STATIC tSilaStateType ucSilaStateInt;

void SilaInit(void){
  ucSilaState    = SILA_STATE_NORMAL_OFF;
  ucSilaStateOut = SILA_STATE_NORMAL_OFF;
  ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}

void SilaPutState(tSilaStateType ucState)
{
  if(    (ucSilaStateInt == SILA_STATE_MALFUNCTIONFLASH)
      && (ucState == SILA_STATE_PERMANENT_ON)            )
  {

  }
  else{
   ucSilaStateInt = ucState;
  }
}

tSilaStateType SilaGetState(void){
  return( ucSilaStateOut );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void SilaKL15On(void){
  ucSilaState = SILA_STATE_CHECK;
  ucSilaStateOut = SILA_STATE_NORMAL_OFF;
  ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}
#endif

void  SilaTask(void){
  ucSilaStateOut = ucSilaStateInt;
}
