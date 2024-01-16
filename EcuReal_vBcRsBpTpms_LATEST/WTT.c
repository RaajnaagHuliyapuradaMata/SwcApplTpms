/******************************************************************************/
/* File   : WTT.c                                                             */
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

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"

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
unsigned char bTW(
      struct LocalWarnDat* ptLWD
   ,  unsigned char        ucWarnCfg
){
   uint8 LocalWarnCfgToRemoveWarning = ucWarnCfg;
   sint8         S8_TempThreshold       = NvM3_GETucVarCodTemperatureWarningThresEE();
   uint8         U8_CurrentWarnBitState = ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
   unsigned char ucRet = 0;
   if(U8_CurrentWarnBitState == 0){
      if(
            ptLWD->tHFD.tHF.scTWE
         >= S8_TempThreshold
      ){
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
      }
   }
   else{
      if(
            ptLWD->tHFD.tHF.scTWE
         <  (
                  S8_TempThreshold
               -  10
            )
      ){
         ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
         ucRet = 0;
      }
      else{
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
      }
   }
   return(ucRet);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

