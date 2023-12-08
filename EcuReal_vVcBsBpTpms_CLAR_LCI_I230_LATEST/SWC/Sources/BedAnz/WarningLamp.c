/******************************************************************************/
/* File   : WarningLamp.c                                                     */
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
#include "WarningLampX.h"

#include "CcmX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cFixLampBlinkTimePreloadValue                            ((uint16) 700u)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
   eFL_Off = 0,
   eFL_Static = 1,
   eFL_Blinking = 2,
   eFL_Invalid = 0xff
}tFL_StatesDecl;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8          ucCcStartStopStateWL = cCcStartStopState_Invalid;
static uint8          ucCcBlinkStateWL     = cCcBlinkState_Invalid;
static boolean        bBlinkingAllowedWL   = TRUE;
static uint16         ushFlashTimeCnt      = cFixLampBlinkTimePreloadValue;
static tFL_StatesDecl tFL_State            = eFL_Invalid;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static boolean bIsBlinkingWL(void);
static void StartBlinkingWL(void);

void InitWL(void)
{
   ucCcStartStopStateWL    = cCcStartStopState_Invalid;
   ucCcBlinkStateWL        = cCcBlinkState_Invalid;
   bBlinkingAllowedWL      = TRUE;
   ushFlashTimeCnt         = cFixLampBlinkTimePreloadValue;

   tFL_State               = eFL_Invalid;
}

void PutCheckControlNumberWL(uint8 ucFixLampControl)
{
   switch(ucFixLampControl){
      case cCcFixLampStateOff:
      SwitchOffWL();
      break;

      case cCcFixLampStateStatic:
      SwitchOnWL();
      break;

      case cCcFixLampStateBlinking:
      StartBlinkingWL();
      break;

      default:
      SwitchOffWL();
      break;
   }
}

void PutCcStartStopStateWL(uint8 ucCcStartStopState)
{
   ucCcStartStopStateWL = ucCcStartStopState;
}

uint8 ucGetCcStartStopStateWL(void)
{
   return ucCcStartStopStateWL;
}

uint8 ucGetCcBlinkStateFixLampWL(void)
{
   return ucCcBlinkStateWL;
}

uint8 ucGetCcRepetitionRateWL(void)
{
   return cCcRepetitionRate_10;
}

void MainFunctionWL(void)
{
   switch(tFL_State){
      case eFL_Blinking:
      if(bIsBlinkingWL() == FALSE){
        PutCcStartStopStateWL( cCcStartStopState_Start);
        ucCcBlinkStateWL = cCcBlinkState_Off;
        tFL_State        = eFL_Static;
      }
      else{
      }
      break;

      case eFL_Off:
      case eFL_Static:
      default:
      break;
   }
}

boolean bIsBlinkingAllowedWL(void)
{
   return bBlinkingAllowedWL;
}

void SwitchOnWL(void)
{
   if(ucGetCcStartStopStateWL() != cCcStartStopState_Started){
    PutCcStartStopStateWL( cCcStartStopState_Start);
      ucCcBlinkStateWL     = cCcBlinkState_Off;

    tFL_State = eFL_Static;
   }
}

void SwitchOffWL(void)
{
   if(ucGetCcStartStopStateWL() == cCcStartStopState_Started){
    PutCcStartStopStateWL( cCcStartStopState_Stop);
      ucCcBlinkStateWL     = cCcBlinkState_Off;

    tFL_State = eFL_Off;
   }
   else if(ucGetCcStartStopStateWL() == cCcStartStopState_Stoped){
    PutCcStartStopStateWL( cCcStartStopState_Invalid);
      ucCcBlinkStateWL     = cCcBlinkState_Invalid;
    BlinkingAllowedWL( TRUE);
   }
   else{
   }
}

static void StartBlinkingWL(void)
{
   if(bIsBlinkingAllowedWL() == TRUE){
    PutCcStartStopStateWL( cCcStartStopState_Start);
    BlinkingAllowedWL( FALSE);
      ucCcBlinkStateWL     = cCcBlinkState_Slow;
      ushFlashTimeCnt      = cFixLampBlinkTimePreloadValue - 1;
    tFL_State = eFL_Blinking;
   }
}

static boolean bIsBlinkingWL(void)
{
   boolean bRet = TRUE;

   if(ushFlashTimeCnt == 0u){
      ushFlashTimeCnt = cFixLampBlinkTimePreloadValue;
   }

   if(ushFlashTimeCnt != cFixLampBlinkTimePreloadValue){
      ushFlashTimeCnt--;
   }
   else{
    bRet = FALSE;
   }

   return bRet;
}

void BlinkingAllowedWL( boolean bState)
{
   bBlinkingAllowedWL = bState;
}

uint8 ucGetActualStateWL(void)
{
   uint8 ucRet = 0x00;
   uint8 ucState;
   ucState = ucGetCcStartStopStateWL();
   if((ucState == cCcStartStopState_Start) || (ucState == cCcStartStopState_Started)){
      ucRet|= 0x01;

      if(ucGetCcBlinkStateFixLampWL() == cCcBlinkState_Slow){
      ucRet|= 0x10;
      }else if(ucGetCcBlinkStateFixLampWL() == cCcBlinkState_Fast){
      ucRet|= 0x20;
      }
      else{
      }
   }

   return ucRet;
}

uint16 ushGetBlinkingTimeWL(void)
{
   uint16 ushRet;

   if(ushFlashTimeCnt == cFixLampBlinkTimePreloadValue){
      ushRet = 0;
   }
   else{
      ushRet = ushFlashTimeCnt;
   }

   return ushRet;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

