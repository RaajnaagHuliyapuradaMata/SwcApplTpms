

#include "USWTime.h"

#include "eeiface.h"

void TimerWT( Rte_Instance self, uint8 ucAction)
{
  void (*const fpt2WnTypeCallbackInit[]) ( Rte_Instance self)  = cWT_WNcallbackTimerInit_map;
  void (*const fpt2WnTypeCallbackCount[]) ( Rte_Instance self) = cWT_WNcallbackTimerCount_map;
  uint8 ucWTCount;

  switch (ucAction)
  {
    case ucCountc:
      for ( ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++)
      {
#ifdef _SwcApplTpms_CLAR_LCI
        if( fpt2WnTypeCallbackCount[ucWTCount] != NULL_PTR)
#else
        if( fpt2WnTypeCallbackCount[ucWTCount] != NULL)
#endif
        {
          fpt2WnTypeCallbackCount[ucWTCount]( self);
        }
      }
    break;

    case ucIniTimec:
      for ( ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++)
      {
#ifdef _SwcApplTpms_CLAR_LCI
        if( fpt2WnTypeCallbackInit[ucWTCount] != NULL_PTR)
#else
        if( fpt2WnTypeCallbackInit[ucWTCount] != NULL)
#endif
        {
          fpt2WnTypeCallbackInit[ucWTCount]( self);
        }
      }
    break;

    default:

    break;
  }
}

void TimerStopWT(void)
{
  uint8 ucLoop;
  void (*const fpt2WnTypeCallbackStop[]) (void) = cWT_WNcallbackTimerStop_map;

  for ( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
#ifdef _SwcApplTpms_CLAR_LCI
    if( fpt2WnTypeCallbackStop[ucLoop] != NULL_PTR)
#else
    if( fpt2WnTypeCallbackStop[ucLoop] != NULL)
#endif
    {
      fpt2WnTypeCallbackStop[ucLoop]();
    }
  }
}

