

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
        if( fpt2WnTypeCallbackCount[ucWTCount] != NULL)
        {
          fpt2WnTypeCallbackCount[ucWTCount]( self);
        }
      }
    break;

    case ucIniTimec:
      for ( ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++)
      {
        if( fpt2WnTypeCallbackInit[ucWTCount] != NULL)
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
    if( fpt2WnTypeCallbackStop[ucLoop] != NULL)
    {
      fpt2WnTypeCallbackStop[ucLoop]();
    }
  }
}

