/******************************************************************************/
/* File   : WTLowP.c                                                          */
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

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswtime.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003
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
#ifdef WITH_UNUSED_WARNINGS
unsigned char bLowP(struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg){
  unsigned char ucRet;
  uint8         LocalWarnCfgToRemoveWarning = ucWarnCfg;

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucThresLowPc;
#endif

  if(ptLWD->tHFD.tHF.ucP <= ucThresLowPc){
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc) == 1){
      if( ptLWD->tHFD.tHF.ucP >= ptLWD->tSD.ucPSoll ){
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
        StopFilterSTWT(ptLWD->tHFD.tHF.ucId);
        ucRet = 0;
      }
      else{
        ucRet = 1;
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
      StopFilterSTWT(ptLWD->tHFD.tHF.ucId);
      ucRet = 0;
   }
  }
  return(ucRet);
}
#endif

#ifndef pb_ModulTest_02062003
#else
void PrintLowPCfg(void){
  printf("Parametersatz LowP:\n");
  printf("LowP: Schwelle/mbar;\n");
  printf(" %d; \n", ucThresLowPc * ucPResInMBarc);
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

