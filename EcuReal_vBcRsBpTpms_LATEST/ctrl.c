/******************************************************************************/
/* File   : ctrl.c                                                            */
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

#include "USWarnX.hpp"
#include "global.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct ParaSubSet tPSSA;

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
void ChangeWNParaSubSet(void){
   if(tPSSA.ucAccess == ucRdParaSubSetc){
      RdParaSubSet(
         &tPSSA);
      tPSSA.ucAccess = ucRdWnValidTMc;
      RdWnValidTMc(
         &tPSSA);
      tPSSA.ucAccess = 0;
   }
   if(tPSSA.ucAccess == ucWrParaSubSetc){
      tPSSA.ucAccess = ucWrParaSubSetc;
      WrParaSubSet(
         &tPSSA);
      tPSSA.ucAccess = ucWrWnValidTMc;
      WrWnValidTMc(
         &tPSSA);
      tPSSA.ucAccess = ucRdParaSubSetc;
      RdParaSubSet(
         &tPSSA);
   }
}

unsigned char ucUSWAlgoPara(
   unsigned char ucType,
   unsigned char ucPres,
   struct ParaSubSet* ptPara){
   unsigned char ucHelp;
   unsigned char aucDgService[5];
   unsigned char ucLoop;
   const unsigned char ucUSFactorPFc = (unsigned char)25;
   const unsigned char ucEUFactorPFc = (unsigned char)16;
   tPSSA.ucAccess = ucRdParaSubSetc;
   ChangeWNParaSubSet();
   tPSSA.ucParaByte[ucIxWnCfgc] = ptPara->ucParaByte[ucIxWnCfgc];
   tPSSA.ucParaByte[ucIxWnCfgc] &= (unsigned char)0xBF;
   if((unsigned char)(ucType & 0x40) == 0x40){
      tPSSA.ucParaByte[ucIxWnCfgc] |= 0x40;
   }
   tPSSA.ucParaByte[ucIxMsCfgc] = ptPara->ucParaByte[ucIxMsCfgc];
   tPSSA.scTResLimit = ptPara->scTResLimit;
   tPSSA.ucParaHighPressThres = ptPara->ucParaHighPressThres;
   tPSSA.ucParaHighPressResetThres = ptPara->ucParaHighPressResetThres;
   tPSSA.ucParaAxImbSetThres = ptPara->ucParaAxImbSetThres;
   tPSSA.ucParaAxImbResThres = ptPara->ucParaAxImbResThres;
   tPSSA.ucAccess = ucWrParaSubSetc;
   ChangeWNParaSubSet();
   ucHelp = ucPres;
   if((unsigned char)(ucType & 0x03) == 0x01){
      ucHelp -= (unsigned char)((unsigned short)(ucUSFactorPFc * ucHelp) / 100);
   }
   else{
      ucHelp -= (unsigned char)((unsigned short)(ucEUFactorPFc * ucHelp) / 100);
   }
   aucDgService[0] = ucCfgPMinc;
   aucDgService[1] = ucHelp;
   ucHelp = ucWarnManagerWN(
      ucDiagServicec,
      aucDgService);
   aucDgService[0] = ucCfgPSollMinAtIdc;
   aucDgService[2] = ucPres;
   aucDgService[3] = 0;
   for(ucLoop = 0; (ucLoop < ucSumWEc ) && (ucHelp != 0xff); ucLoop++){
      aucDgService[1] = ucLoop;
      ucHelp = ucWarnManagerWN(
         ucDiagServicec,
         aucDgService);
   }
   return (ucHelp);
}

void InitUSWAlgo(
   const unsigned char* ptWPos){
   unsigned char aucDgServ[6], i;
   aucDgServ[0] = 0x00;
   aucDgServ[0] = ucWarnManagerWN(
      ucPorInitc,
      aucDgServ);
   aucDgServ[0] = 0x00;
   aucDgServ[1] = 0x00;
   aucDgServ[2] = 0x00;
   aucDgServ[0] = ucTSSMsgManagerTM(
      ucPorInitc,
      aucDgServ);
   TimerWT(
      ucIniTimec);
   aucDgServ[1] = ucGetWarnVectorsc;
   aucDgServ[0] = (unsigned char)ucWarnManagerWN(
      ucDiagServicec,
      &aucDgServ[1]);
   aucDgServ[0] = ucPutWarnVectorSetc;
   aucDgServ[0] = ucTSSMsgManagerTM(
      ucDiagServicec,
      aucDgServ);
   aucDgServ[0] = ucNewPositionsc;
   aucDgServ[1] = *ptWPos;
   for(i = 0; i < (ucSumWEc - 1); i++){
      aucDgServ[2 + i] = ptWPos[1 + i];
   }
   aucDgServ[0] = ucTSSMsgManagerTM(
      ucDiagServicec,
      aucDgServ);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

