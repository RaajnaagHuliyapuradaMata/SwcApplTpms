/******************************************************************************/
/* File   : WTEuF.c                                                           */
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
static unsigned char bEUKOIsWarnLowActive(
   struct LocalWarnDat* ptLWD);
static unsigned char bUSIsWarnLowActive(
   struct LocalWarnDat* ptLWD);
static unsigned char bPRCIsWarnLowActive(
   struct LocalWarnDat* ptLWD);

unsigned char bEuF(
   struct LocalWarnDat* ptLWD,
   unsigned char ucWarnCfg){
   unsigned char ucRet = 0;
   uint8 u8_activeLegislation = E_US_LEG_NON_EXTRA_LOAD_TIRES;
   uint8 LocalWarnCfgToRemoveWarning;
   LocalWarnCfgToRemoveWarning = ucWarnCfg;
   u8_activeLegislation = GETucVarCodLegislationEE();
   if(u8_activeLegislation == E_EU_KO_LEG){
      ucRet = bEUKOIsWarnLowActive(
         ptLWD);
   }
   else if((u8_activeLegislation == E_US_LEG_NON_EXTRA_LOAD_TIRES) || (u8_activeLegislation == E_US_LEG_EXTRA_LOAD_TIRES)){
      ucRet = bUSIsWarnLowActive(
         ptLWD);
   }
   else{
      ucRet = bPRCIsWarnLowActive(
         ptLWD);
   }
   return (ucRet);
}

static unsigned char bEUKOIsWarnLowActive(
   struct LocalWarnDat* ptLWD){
   unsigned char ucPCompare;
   unsigned char ucRet = 0;
   unsigned char ucIsobarLimit;
   unsigned short ushHelp;
   signed short sshTemp;
   signed char scTaBuf;
   scTaBuf = ptLWD->tHFD.tHF.scTa;
   ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
   if(ptLWD->tHFD.tHF.scTa > sc40Gradc){
      ptLWD->tHFD.tHF.scTa = sc40Gradc + scTDropHTVc;
   }
   else{
      if((ptLWD->tHFD.tHF.scTa + scTDropHTVc ) >= 0){
         ptLWD->tHFD.tHF.scTa += scTDropHTVc;
      }
      else{
         ptLWD->tHFD.tHF.scTa = 0;
      }
   }
   if(ptLWD->tHFD.tHF.scTWE > ptLWD->tHFD.tHF.scTa){
      ushHelp = (unsigned short)ptLWD->tHFD.tHF.scTa + ush273Kelvinc;
      ucPCompare = ucPfT(
         ptLWD->tSD.ushMSoll,
         ushHelp);
      sshTemp = (sint16)(sc20Gradc - (ptLWD->tHFD.tHF.scTref));
      sshTemp = (signed short)(sshTemp * 12u);
      sshTemp /= ucPResInMBarc;
      ucPCompare = (unsigned char)(0xFF & (ucPCompare + sshTemp));
      ucPCompare = (uint8)(0xFF & (ucPCompare + (ucPfT(
         ushMDropHTVc,
         (unsigned short)(ptLWD->tHFD.tHF.scTWE - ptLWD->tHFD.tHF.scTa)))));
      ucPCompare = (uint8)(0xFF & (ucPCompare - uc1Barc ));
      ucPCompare -= (unsigned char)((unsigned short)(ucEuFactorEuFc * ucPCompare) / 100);
      ucPCompare += uc100mBarc;
   }
   else{
      ucPCompare = ucPfT(
         ptLWD->tSD.ushMSoll,
         ushHelp);
      sshTemp = (sint16)(sc20Gradc - (ptLWD->tHFD.tHF.scTref));
      sshTemp = (signed short)(sshTemp * 12u);
      sshTemp /= ucPResInMBarc;
      ucPCompare = (unsigned char)(0xFF & (ucPCompare + sshTemp));
      ucPCompare = (uint8)(0xFF & (ucPCompare - uc1Barc ));
      ucPCompare -= (unsigned char)((unsigned short)(ucEuFactorEuFc * ucPCompare) / 100);
      ucPCompare += uc100mBarc;
   }
   ucIsobarLimit = (unsigned char)(0xFF & (ptLWD->tSD.ucPSoll - ucThresLimitEuFc ));
   if(ucPCompare > ucIsobarLimit){
      ucPCompare = ucIsobarLimit;
   }
#ifdef pb_DebugWarnLevels_030203
   ptLWD->ucCurWarnLevel = ucPCompare;
#endif
   if((ptLWD->tHFD.tHF.ucP < ucPCompare) && (ptLWD->tHFD.tHF.scTref < scLockEuFbyTref )){
      ucRet = ucSetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc);
   }
   else{
      if(ucGetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc) == 1){
         if(ptLWD->tHFD.tHF.ucP >= ptLWD->tSD.ucPSoll){
            ClearWarnBitWN(
               ptLWD->tHFD.tHF.ucId,
               ucEuFIxc);
            ucRet = 0;
         }
         else{
            if(ptLWD->tHFD.tHF.ucP >= (ucPCompare + ucThresLimitEuFc )){
               if(ptLWD->tHFD.tHF.ucP >= (ptLWD->tSD.ucPSoll - uc100mBarc)){
                  ClearWarnBitWN(
                     ptLWD->tHFD.tHF.ucId,
                     ucEuFIxc);
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
      }
      else{
         ClearWarnBitWN(
            ptLWD->tHFD.tHF.ucId,
            ucEuFIxc);
         ucRet = 0;
      }
   }
   ptLWD->tHFD.tHF.scTa = scTaBuf;
   return (ucRet);
}

static unsigned char bUSIsWarnLowActive(
   struct LocalWarnDat* ptLWD){
   uint8 u8Pplacard;
   uint8 ucPCompareSETCond, ucPCompareRESETCond, u8ReceivedRelativePressure;
   unsigned char ucRet = 0;
   static uint8 u8ConsecLowPRxCnt = 0;
   u8Pplacard = ptLWD->tSD.ucPSoll;
   u8ReceivedRelativePressure = (uint8)(0xFF & ptLWD->tHFD.tHF.ucP);
   ucPCompareSETCond = (((uint8)(u8Pplacard / u8_US_Resolution) - ((uint8)(((uint16)((u8Pplacard / u8_US_Resolution) * u8_US_25Percent)) / (uint16)100))) * u8_US_Resolution) + u8_US_Tolerance;
#ifdef pb_DebugWarnLevels_030203
   ptLWD->ucCurWarnLevel = ucPCompareSETCond;
#endif
   if(u8ReceivedRelativePressure <= ucPCompareSETCond){
      ucRet = ucSetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc);
   }
   else{
      if(ucGetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc) == 1){
         ucPCompareRESETCond =
               (ptLWD->tSD.ucPSoll > ucNegHystPMinc ) ? (ptLWD->tSD.ucPSoll - ucNegHystPMinc ) : 0;
         if(ptLWD->tHFD.tHF.ucP >= ucPCompareRESETCond){
            ClearWarnBitWN(
               ptLWD->tHFD.tHF.ucId,
               ucEuFIxc);
            ucRet = 0;
         }
         else{
            ucRet = 1;
         }
      }
      else{
         ClearWarnBitWN(
            ptLWD->tHFD.tHF.ucId,
            ucEuFIxc);
         ucRet = 0;
      }
   }
   return (ucRet);
}

static unsigned char bPRCIsWarnLowActive(
   struct LocalWarnDat* ptLWD){
   uint8 u8Pplacard;
   uint8 ucPCompareSETCond, ucPCompareRESETCond, u8ReceivedRelativePressure;
   unsigned char ucRet = 0;
   static uint8 u8ConsecLowPRxCnt = 0;
   u8Pplacard = ptLWD->tSD.ucPSoll;
   u8ReceivedRelativePressure = (uint8)(0xFF & ptLWD->tHFD.tHF.ucP);
   ucPCompareSETCond = (((uint16)(u8Pplacard * u8_PRC_Percent_calc)) / 100) + u8_PRC_Tolerance_digits;
   if(u8ReceivedRelativePressure <= ucPCompareSETCond){
      ucRet = ucSetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc);
   }
   else{
      if(ucGetWarnBitWN(
         ptLWD->tHFD.tHF.ucId,
         ucEuFIxc) == 1){
         ucPCompareRESETCond =
               (u8Pplacard > ucNegHystPMinc ) ? (u8Pplacard - ucNegHystPMinc ) : 0;
         if(ptLWD->tHFD.tHF.ucP >= ucPCompareRESETCond){
            ClearWarnBitWN(
               ptLWD->tHFD.tHF.ucId,
               ucEuFIxc);
            ucRet = 0;
         }
         else{
            ucRet = 1;
         }
      }
      else{
         ClearWarnBitWN(
            ptLWD->tHFD.tHF.ucId,
            ucEuFIxc);
         ucRet = 0;
      }
   }
   return (ucRet);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

