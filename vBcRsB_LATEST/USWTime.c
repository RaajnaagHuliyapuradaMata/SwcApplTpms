/******************************************************************************/
/* File   : USWTime.c                                                         */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "USWarnX.hpp"
#include "global.hpp"
#include "WnTypePar.hpp"
#include "USWarn.hpp"
#include "USWTime.hpp"

#ifndef pb_TestUSWTime_02062003
#else
#include <stdio.h>
#endif

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static unsigned char ucGetFilterSTActive(unsigned char ucIdX);
#ifndef pb_ModulTest_02062003

#else
static void TimeDelay(unsigned char);
#endif

cSTATIC unsigned char ucFilterSTActive;
cSTATIC unsigned char ucSofTimerWT[ucSumWEc];

static unsigned char ucGetFilterSTActive(unsigned char ucIdX){
   unsigned char ucRet;
   ucRet = ((ucFilterSTActive & ucBitNoc[ucIdX]) == ucBitNoc[ucIdX]) ? (unsigned char) 1: (unsigned char) 0;
    return(ucRet);
}

void StopFilterSTWT( unsigned char ucIdX){
   if(ucIdX < ucSumWEc){
        ucFilterSTActive &= (unsigned char) (~ucBitNoc[ucIdX]);
        ucSofTimerWT[ucIdX] = ucFilterTimeSTc;
   }
}

unsigned char ucStartFilterSTWT( unsigned char ucIdX){
  if(ucIdX < ucSumWEc){
   if( (ucFilterSTActive & ucBitNoc[ucIdX]) == ucBitNoc[ucIdX] ){
   }
   else{
      ucFilterSTActive |= ucBitNoc[ucIdX];
      ucSofTimerWT[ucIdX] = ucFilterTimeSTc;
   }
#ifdef pb_ModulTest_02062003
    TimeDelay(ucFilterTimeSTc);
#endif
    return((unsigned char)  ((ucSofTimerWT[ucIdX] > 0) ? 1:0));
  }
  else{
    return((unsigned char) 0xff);
  }
}

void TimerWT( unsigned char ucAction){
  static unsigned char ucTime10sec = 0;
  unsigned char i;
  switch(ucAction){
   case (unsigned short) ucCountc:
        ucTime10sec++;
        if(ucTime10sec == ucTimeFilterPrescInMSc )
        {
          ucTime10sec = 0;

          for( i = 0; i < ucSumWEc; i++ )
          {
            if( ucGetFilterSTActive(i) == 1 )
            {
              if( ucSofTimerWT[i] > 0)
              {
                ucSofTimerWT[i]--;
              }
            }
          }

          ChangeWNParaSubSet();
        }
      break;

  case (unsigned short) ucIniTimec:
        ucTime10sec = 0;
        ucFilterSTActive = 0;
        for( i = 0; i < ucSumWEc; i++ )
        {
            ucSofTimerWT[i] = ucFilterTimeSTc;
        }
      break;

  default:
      break;
  }
}

#ifndef pb_ModulTest_02062003
#else
void ResetUSWTime(void){
   unsigned char ucLoop;
   const unsigned char ucInitValuec = 0;
   ucFilterSTActive = ucInitValuec;
   for(ucLoop = 0; ucLoop < ucSumWEc; ucLoop++){
        ucSofTimerWT[ucLoop] = ucInitValuec;
   }
}

static void TimeDelay(unsigned char ucDelayIn20Seconds){
  unsigned long i;
  for(i = 0; i < (unsigned long) ((unsigned long) (20000 * ucDelayIn20Seconds) / ushCallFreqInMSWTc);i++){
    TimerWT( ucCountc );
  }
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

