/******************************************************************************/
/* File   : WTDHW.c                                                           */
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
static unsigned char aucLastPressureM1DHW[ucSumWEc];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
unsigned char bDHW(struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg){
   static const unsigned char  ucModeMaskc = (unsigned char) 0x03;
   static const unsigned char  ucMode1c    = (unsigned char) 0x01;
   static const unsigned char  ucMode2     = (unsigned char) 0x02;
   static const unsigned short ushMinVc    = (unsigned char) 20;
                uint8          LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;
  if(aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] == 0){
    aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] = ptLWD->tHFD.tHF.ucP;
   ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc);
#ifdef pb_DebugWarnLevels_030203
    ptLWD->ucCurWarnLevel = aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId];
#endif
    return((unsigned char) 0);
  }
  else{
   if(    ((ptLWD->tHFD.tHF.ucState & ucModeMaskc) == ucMode2)
         && (ptLWD->tHFD.tHF.ushVehicleSpeed >= ushMinVc)
         && ((ptLWD->tHFD.tHF.ucP + ucDifDHWc) <= aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId])
         ){
      return( ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc));
   }
   else{
      if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc) == 1){
        if( ptLWD->tHFD.tHF.ushVehicleSpeed == 0 ){
          ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc);
          return((unsigned char) 0);
        }
        else{
          return((unsigned char) 1);
        }
      }
      else{
        if( ptLWD->tHFD.tHF.ushVehicleSpeed == 0 ){
          aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] = ptLWD->tHFD.tHF.ucP;
        }
#ifdef pb_DebugWarnLevels_030203
        ptLWD->ucCurWarnLevel = aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId];
#endif
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc);
        return((unsigned char) 0);
      }
   }
  }
}

void ResetM1Pressure(unsigned char i){
  if(i < ucSumWEc){
    aucLastPressureM1DHW[i] = 0;
  }
  else{
   for( i = 0; i < ucSumWEc; i++ ){
      aucLastPressureM1DHW[i] = 0;
   }
  }
}

#ifndef pb_ModulTest_02062003
#else
void PrintDHWCfg(void){
  printf("Parametersatz DHW:\n");
  printf(" MinDiff; NegHyst/mBar\n");
  printf(" %d; %d; \n", ucDifDHWc * ucPResInMBarc, ucNegHystDHWc * ucPResInMBarc);
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

