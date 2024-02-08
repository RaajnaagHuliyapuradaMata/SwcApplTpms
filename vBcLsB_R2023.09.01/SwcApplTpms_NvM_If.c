/******************************************************************************/
/* File   : SwcApplTpms_NvM_If.c                                              */
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
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "TSS_StdX.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"

#define cFAHRZEUG_FAEHRT      ((uint16) 0x0004) //TBD: Move to defines and bin check?

#include "CfgSwcApplTpms_Warning.hpp"
#include "walloc_if.hpp"
#include "WallocX.hpp"
#include "UsWarnX.hpp"
#include "global.hpp"
#include "USCS.hpp"

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
uint8 GETucResetWarnPresLimitEE(void){
   static const uint8 cResetWarnPresLimit = 12U;
   return cResetWarnPresLimit;
}

uint8 GETucPSollMinVaEE(void){
   STATIC const uint8  cPSollMinVaBarAbs = 72U;
   return cPSollMinVaBarAbs;
}

uint8 GETucPSollMinHaEE(void){
   STATIC const uint8  cPSollMinHaBarAbs = 72U;
   return cPSollMinHaBarAbs;
}

uint16 GETushSuppIdentFilterEE(void){
   const uint16 ushSuppIdentFilter = 0x0004U;
   return ushSuppIdentFilter;
}

uint16 GETusMaxFolgeAusfallEE(void){
   STATIC const uint16  cMaxFolgeAusfall = 540U;
   return cMaxFolgeAusfall;
}

#ifdef G_USE_PART_ER
uint8 GETucPartErTimerFactorEE(void){
   STATIC const uint8  cucPartErTimerFactor = 250U;
   return cucPartErTimerFactor;
}
#endif

uint8 GETucTimeTransmitIntervalCompletePeriodEE(void){
   STATIC const uint8 cucTimeTransmitIntervalCompletePeriod = 33U;
   return cucTimeTransmitIntervalCompletePeriod;
}

uint8 GETucMinOffsetGXeEE(void){
   WAParameter LocaltWAPar;
   GetWADataEE(cWAParameter, (unsigned char *) &LocaltWAPar);
   return LocaltWAPar.ucMinOffsetGXe;
}

uint8 GETucOffsetOverlapsGXeEE(void){
   WAParameter LocaltWAPar;
   GetWADataEE(cWAParameter, (unsigned char *) &LocaltWAPar);
   return LocaltWAPar.ucOffsetOverlapsGXe;
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint8 GETucMaxStoersenderZeitMinutenEE(void){
   STATIC const uint8  cucMaxStoersenderZeitMinuten = 10;
   return cucMaxStoersenderZeitMinuten;
}

boolean GETbTransportModeEE(void){
   boolean l_bRet;
   l_bRet = FALSE;
   return l_bRet;
}

boolean GETbTabCalRequestEE(void){
   boolean l_bRet;
   l_bRet = FALSE;
   return l_bRet;
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

