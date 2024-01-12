/******************************************************************************/
/* File   : REDiag.c                                                          */
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

#include "REDiag_if.hpp"
#include "CfgSwcApplTpms.hpp"
#include "statemanagerX.hpp"
#include "REDiagX.hpp"

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
static const uint8 cMaxWUDefectCnt      = 250;
static const uint8 cMaxWULowLifeTimeCnt = 250;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8 ucCntWUDefect[4];
static uint8 ucCntLowLifeTime[4];

#ifdef js_ReHighTemperatureDiag_230312
static const uint8 cMaxWUOverTempCnt = 250;
static uint8 ucCntWUOverTemp[4];
#endif

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void ResetWUFailedErrRD(uint8 ucIx){
   EvalWUNoRecSM(ucIx);
}

boolean SetWUFailedErrRD(uint16 CounterValue, uint8 ucIx){
   boolean bErrState = FALSE;
   if( CounterValue >= MaxFailCounterInEE()){
      EvalWUNoRecSM(ucIx);
      bErrState = TRUE;
   }
   return(bErrState);
}

void CntWUDefectRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      if(ucCntWUDefect[ZomPos] < cMaxWUDefectCnt){
         ucCntWUDefect[ZomPos]++;
      }
      EvalWUDefektSM(ZomPos);
   }
}

void ResetWUDefectRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      ucCntWUDefect[ZomPos] = 0;
      EvalWUDefektSM(ZomPos);
   }
}

uint8 GetWUDefectRD(uint8 ZomPos){
   return(ucCntWUDefect[ZomPos]);
}

#ifdef js_ReHighTemperatureDiag_230312
void CntWUHighTempRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      if(ucCntWUOverTemp[ZomPos] < cMaxWUOverTempCnt){
         ucCntWUOverTemp[ZomPos]++;
      }
      EvalWUHighTempSM();
   }
}

void ResetWUHighTempRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      ucCntWUOverTemp[ZomPos] = 0;
      EvalWUHighTempSM();
   }
}

uint8 GetWUHighTempRD(uint8 ZomPos){
   return(ucCntWUOverTemp[ZomPos]);
}
#endif

void CntWULowLifeTimeRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      if(ucCntLowLifeTime[ZomPos] < cMaxWULowLifeTimeCnt){
         ucCntLowLifeTime[ZomPos]++;
      }
      EvalWULowLifeTimeSM(ZomPos);
   }
}

void ResetWULowLifeTimeRD(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      ucCntLowLifeTime[ZomPos] = 0;
      EvalWULowLifeTimeSM(ZomPos);
   }
}

void ResetWULowLifeTimeCounter(uint8 ZomPos){
   if(ZomPos < cAnzRad){
      ucCntLowLifeTime[ZomPos] = 0;
   }
}

uint8 GetWULowLifeTimeRD(uint8 ZomPos){
   return(ucCntLowLifeTime[ZomPos]);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

