/******************************************************************************/
/* File   : WTHTDR.c                                                          */
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
unsigned char bHardTDR(struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg){
  unsigned char  ucPCompare, ucResPCompare, ucRet;
  unsigned short ushHelp;
    signed char  scTaBuf;

  scTaBuf = ptLWD->tHFD.tHF.scTa;
  ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
  if( ptLWD->tHFD.tHF.scTa > sc40Gradc ){
    ptLWD->tHFD.tHF.scTa = sc40Gradc + scTDropHTc;
  }
  else{
   if( (ptLWD->tHFD.tHF.scTa + scTDropHTc) >= 0 ){
      ptLWD->tHFD.tHF.scTa += scTDropHTc;
   }
   else{
      ptLWD->tHFD.tHF.scTa = 0;
   }
  }
  if(ptLWD->tHFD.tHF.scTWE > ptLWD->tHFD.tHF.scTa){
   ushHelp = (unsigned short) ptLWD->tHFD.tHF.scTa +  ush273Kelvinc;
   ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTc, ptLWD->tSD.scTSoll ))), ushHelp) ;
   ucPCompare = (uint8)(0xFF & (ucPCompare + ucPfT(ushMDropHTc, (unsigned short) (ptLWD->tHFD.tHF.scTWE-ptLWD->tHFD.tHF.scTa))));
  }
  else{
   ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTc, ptLWD->tSD.scTSoll ))), ushHelp) ;
  }
  ucPCompare -= uc1Barc;

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucPCompare;
#endif

  if(ptLWD->tHFD.tHF.ucP <= ucPCompare){
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc) == 1){
      ucResPCompare = (ptLWD->tSD.ucPSoll > ucNegHystHTc) ? (ptLWD->tSD.ucPSoll - ucNegHystHTc):0;
      if((ucWarnCfg & ucIsoClearc) == ucIsoClearc){
        if( ptLWD->tHFD.tHF.ucP >= ucResPCompare ){
          ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
          if(ptLWD->tHFD.tHF.ucP >= (ucPfT(ptLWD->tSD.ushMSoll, ushHelp) - uc1Barc)){
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            ucRet = 1;
          }
        }
        else{
          ucRet = 1;
        }
      }
      else{
        if( ptLWD->tHFD.tHF.scTWE < ( scTaBuf + scTResLimitc) ){
          if(ptLWD->tHFD.tHF.ucP >= ucResPCompare){
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            if(DynWarnResetCond(ptLWD->tHFD.tHF.ucP, ucPCompare, ptLWD->tHFD.tHF.ucId) == TRUE){
              ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
              ucRet = 0;
            }
            else{
              ucRet = 1;
            }
          }
        }
        else{
          if(ptLWD->tHFD.tHF.ucP >= (ucResPCompare +  ucHystHTc)){
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            ucRet = 1;
          }
        }
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
      ucRet = 0;
   }
  }
  ptLWD->tHFD.tHF.scTa = scTaBuf;
  return(ucRet);
}
#endif

#ifndef pb_ModulTest_02062003
#else
void PrintHTCfg(void){
  printf("Parametersatz HardT:\n");
  printf("Schwelle/mbar; Hysterese/mbar; TempKnick/°C; MDrop \n");
  printf("%d; %d; %d; %d; \n", ucThresHTc * ucPResInMBarc, ucHystHTc * ucPResInMBarc, scTDropHTc, ushMDropHTc);
}

#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

