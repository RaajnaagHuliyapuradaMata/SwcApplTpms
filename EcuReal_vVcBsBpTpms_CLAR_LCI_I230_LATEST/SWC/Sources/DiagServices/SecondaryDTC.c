/******************************************************************************/
/* File   : SecondaryDTC.c                                                    */
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
#include "SecondaryDTCX.h"

#include "HS_InaktivereignisX.h"
#include "state_bzX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cMaxSizeSecDtcFifo  5

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
static uint8 ucSecondaryErrors = 0;
static uint8 ucSecondaryErrChangedFlags = 0;
static strSecondaryDtcFiFo tSecondaryFifo[cMaxSizeSecDtcFifo];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void SetSecondaryErrorSCD(uint8 ucError){
      ucSecondaryErrors |= ucError;
    SetSecondaryErrChangedFlagSCD(ucError);
}

void ClearSecondaryErrorSCD(uint8 ucError){
   if((ucSecondaryErrors & ucError) == ucError){
      ucSecondaryErrors ^= ucError;
      ucSecondaryErrChangedFlags |= ucError;
   }
}

uint8 GetSecondaryErrorsSCD(void){
   return ucSecondaryErrors;
}

void SetSecondaryErrChangedFlagSCD(uint8 ucError){
   ucSecondaryErrChangedFlags |= ucError;
}

uint8 GetSecondaryErrChangedFlagsSCD(void){
   return ucSecondaryErrChangedFlags;
}

void ClearSecondaryErrChangedFlagSCD(uint8 ucError){
   if((ucSecondaryErrChangedFlags & ucError) == ucError){
      ucSecondaryErrChangedFlags ^= ucError;
   }
}

void ClearSecondaryErrChangedFlagsSCD(void){
   ucSecondaryErrChangedFlags = cSecondaryNoError;
}

void InitSecondaryDtcFiFoSCD(void){
   uint8 i;
   for(i=0; i<cMaxSizeSecDtcFifo; i++){
    tSecondaryFifo[i].ucErrorNumber = cSecondaryNoError;
    tSecondaryFifo[i].ucCausingWheelPos = 0xff;
   }
}

void SecondaryDtcFiFoGetFirstEntrySCD(uint8* pucError, uint8* pucWheelPos){
  *pucWheelPos = tSecondaryFifo[0].ucCausingWheelPos;
  *pucError = tSecondaryFifo[0].ucErrorNumber;
}

void SecondaryDtcFiFoShiftSCD(uint8* pucError, uint8* pucWheelPos){
   uint8 i;
   *pucError = tSecondaryFifo[0].ucErrorNumber;
   *pucWheelPos = tSecondaryFifo[0].ucCausingWheelPos;
   for(i = 0; i < (cMaxSizeSecDtcFifo - 1); i++){
    tSecondaryFifo[i].ucErrorNumber = tSecondaryFifo[i+1].ucErrorNumber;
    tSecondaryFifo[i].ucCausingWheelPos = tSecondaryFifo[i+1].ucCausingWheelPos;
   }
   tSecondaryFifo[cMaxSizeSecDtcFifo - 1].ucErrorNumber = cSecondaryNoError;
   tSecondaryFifo[cMaxSizeSecDtcFifo - 1].ucCausingWheelPos = 0xff;
}

void SecondaryDtcFiFoWriteEntrySCD(uint8 ucDtc, uint8 ucPos){
   uint8 i = 0;
  while ((tSecondaryFifo[i].ucErrorNumber != cSecondaryNoError) && (i < cMaxSizeSecDtcFifo)){
      if(tSecondaryFifo[i].ucErrorNumber == ucDtc){
      i = cMaxSizeSecDtcFifo;
      }
      else{
      i++;
      }
   }
   if(i < cMaxSizeSecDtcFifo){
    tSecondaryFifo[i].ucErrorNumber = ucDtc;
    tSecondaryFifo[i].ucCausingWheelPos = ucPos;
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

