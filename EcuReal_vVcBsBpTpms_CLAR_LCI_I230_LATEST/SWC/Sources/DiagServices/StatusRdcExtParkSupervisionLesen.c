/******************************************************************************/
/* File   : StatusRdcExtParkSupervisionLesen.c                                */
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
#include "StatusRdcExtParkSupervisionLesenX.h"

#include "CodingDataX.h"
#include "WnTypePar.h"
#include "USWarn_IfX.h"
#include "WAllocX.h"
#include "DataManagerX.h"
#include "State_BzX.h"
#include "WarningLampX.h"
#include "InfoTyreX.h"
#include "CcmX.h"
#include "EeDiagBlockX.h"

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
static uint16 SearchMaxWarnLimitValue(uint16 current, uint16 new);

void GetStatusRdcExtParkSupervisionLesen(Rte_Instance self, uint8 *pucData){
   uint8  ucPress;
   sint8  scTemp;
   uint16 ushTref;
   uint8  ucPva;
   uint8  ucPha;
   uint8  ucDummy;
   sint8  scDummy;
   uint16 ushDummy;
   uint8  ucHistCol;
   uint16 ushWnThFa, ushWnThRa;
   uint16 ushNyThFa, ushNyThRa;
   uint16 ushPressVL, ushPressVR, ushPressHL, ushPressHR;
   uint8  ucTempVL, ucTempVR, ucTempHL, ucTempHR;
   uint8 ucQuFnTyrInfo;
   uint8 ucQuTpl;
   uint8 ucQuTfai;
   uint8  ucLoop, ucNoCcmId;
   uint16 ushCcmId;
  Rdci_UHRZEIT_DATUM_Type timeDate;
   uint8 aucDateBuffer[9];
   uint8 aucTimeBuffer[9];
  GetStTyrITY( &ucQuFnTyrInfo, &ucQuTpl, &ucQuTfai);

   if(bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){
      (void) ucGetPTSollUSWIF(self, &ucPress, &scTemp, &ucDummy, &scDummy, &ushDummy, &ucDummy, ucGetColOfWP( cRadPosVL));
      if((ucPress == cInvalidREpressure) || (scTemp == cInvalidREtemperature)){
      (void) ucGetPTSollUSWIF(self, &ucPress, &scTemp, &ucDummy, &scDummy, &ushDummy, &ucDummy, ucGetColOfWP( cRadPosVR));
      if((ucPress == cInvalidREpressure) || (scTemp == cInvalidREtemperature)){
        ushTref = 0x00FFu;
        ucPva   = 0x63u;
      }
      else{
        ushTref = ((uint16) scTemp + 50);
        ucPva   = (uint8) ((((uint16) ucPress * 25) + 50) / 100);
      }
      }
      else{
      ushTref = ((uint16) scTemp + 50);
      ucPva   = (uint8) ((((uint16) ucPress * 25) + 50) / 100);
      }

      (void) ucGetPTSollUSWIF(self, &ucPress, &scTemp, &ucDummy, &scDummy, &ushDummy, &ucDummy, ucGetColOfWP( cRadPosHL));

      if((ucPress == cInvalidREpressure) || (scTemp == cInvalidREtemperature)){

      (void) ucGetPTSollUSWIF(self, &ucPress, &scTemp, &ucDummy, &scDummy, &ushDummy, &ucDummy, ucGetColOfWP( cRadPosHR));

      if((ucPress == cInvalidREpressure) || (scTemp == cInvalidREtemperature)){

        ushTref = 0x00FFu;
        ucPha   = 0x63u;
      }
      else{

        ushTref = ((uint16) scTemp + 50);
        ucPha   = (uint8) ((((uint16) ucPress * 25) + 50) / 100);
      }
      }
      else{

      ushTref = ((uint16) scTemp + 50);
      ucPha   = (uint8) ((((uint16) ucPress * 25) + 50) / 100);
      }

      ucHistCol = ucGetColOfWP( cRadPosVL);
    GetWarnThresDM(ucHistCol, cucIX_Pmin, &ucPress, &ucDummy);
      ushWnThFa = (uint16) ucPress * 25;
    GetWarnThresDM(ucHistCol, cucIX_Pwarn, &ucPress, &ucDummy);
      ushWnThFa = SearchMaxWarnLimitValue(ushWnThFa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_PwarnTol, &ucPress, &ucDummy);
      ushWnThFa = SearchMaxWarnLimitValue(ushWnThFa, (uint16)ucPress * 25);

      ucHistCol = ucGetColOfWP( cRadPosVR);
    GetWarnThresDM(ucHistCol, cucIX_Pmin, &ucPress, &ucDummy);
      ushWnThFa = SearchMaxWarnLimitValue(ushWnThFa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_Pwarn, &ucPress, &ucDummy);
      ushWnThFa = SearchMaxWarnLimitValue(ushWnThFa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_PwarnTol, &ucPress, &ucDummy);
      ushWnThFa = SearchMaxWarnLimitValue(ushWnThFa, (uint16)ucPress * 25);

      ucHistCol = ucGetColOfWP( cRadPosHL);
    GetWarnThresDM(ucHistCol, cucIX_Pmin, &ucPress, &ucDummy);
      ushWnThRa = (uint16) ucPress * 25;
    GetWarnThresDM(ucHistCol, cucIX_Pwarn, &ucPress, &ucDummy);
      ushWnThRa = SearchMaxWarnLimitValue(ushWnThRa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_PwarnTol, &ucPress, &ucDummy);
      ushWnThRa = SearchMaxWarnLimitValue(ushWnThRa, (uint16)ucPress * 25);

      ucHistCol = ucGetColOfWP( cRadPosHR);
    GetWarnThresDM(ucHistCol, cucIX_Pmin, &ucPress, &ucDummy);
      ushWnThRa = SearchMaxWarnLimitValue(ushWnThRa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_Pwarn, &ucPress, &ucDummy);
      ushWnThRa = SearchMaxWarnLimitValue(ushWnThRa, (uint16)ucPress * 25);
    GetWarnThresDM(ucHistCol, cucIX_PwarnTol, &ucPress, &ucDummy);
      ushWnThRa = SearchMaxWarnLimitValue(ushWnThRa, (uint16)ucPress * 25);

      ucHistCol = ucGetColOfWP( cRadPosVL);
    GetWarnThresDM(ucHistCol, cucIX_Pvorw, &ucPress, &ucDummy);
      ushNyThFa = (uint16) ucPress * 25;

      ucHistCol = ucGetColOfWP( cRadPosVR);
    GetWarnThresDM(ucHistCol, cucIX_Pvorw, &ucPress, &ucDummy);
      ushNyThFa = SearchMaxWarnLimitValue(ushNyThFa, (uint16)ucPress * 25);

      ucHistCol = ucGetColOfWP( cRadPosHL);
    GetWarnThresDM(ucHistCol, cucIX_Pvorw, &ucPress, &ucDummy);
      ushNyThRa = (uint16) ucPress * 25;

      ucHistCol = ucGetColOfWP( cRadPosHR);
    GetWarnThresDM(ucHistCol, cucIX_Pvorw, &ucPress, &ucDummy);
      ushNyThRa = SearchMaxWarnLimitValue(ushNyThRa, (uint16)ucPress * 25);

      ucPress = ucGetValidTyrePressureRelAtWheelPosDM( cRadPosVL);
      if(ucPress == cInvalidREpressure){
      ushPressVL = 0x270Fu;
      }
      else{
      ushPressVL = (uint16) ucPress * 25;
      }

      ucPress = ucGetValidTyrePressureRelAtWheelPosDM( cRadPosVR);
      if(ucPress == cInvalidREpressure){
      ushPressVR = 0x270Fu;
      }
      else{
      ushPressVR = (uint16) ucPress * 25;
      }

      ucPress = ucGetValidTyrePressureRelAtWheelPosDM( cRadPosHL);
      if(ucPress == cInvalidREpressure){
      ushPressHL = 0x270Fu;
      }
      else{
      ushPressHL = (uint16) ucPress * 25;
      }

      ucPress = ucGetValidTyrePressureRelAtWheelPosDM( cRadPosHR);
      if(ucPress == cInvalidREpressure){
      ushPressHR = 0x270Fu;
      }
      else{
      ushPressHR = (uint16) ucPress * 25;
      }

      scTemp = scGetValidTyreTemperatureAtWheelPosDM( cRadPosVL);
      if(scTemp == cInvalidREtemperature){
      ucTempVL = 0xFFu;
      }
      else{
      ucTempVL = (uint8) scTemp + 50;
      }

      scTemp = scGetValidTyreTemperatureAtWheelPosDM( cRadPosVR);
      if(scTemp == cInvalidREtemperature){
      ucTempVR = 0xFFu;
      }
      else{
      ucTempVR = (uint8) scTemp + 50;
      }

      scTemp = scGetValidTyreTemperatureAtWheelPosDM( cRadPosHL);
      if(scTemp == cInvalidREtemperature){
      ucTempHL = 0xFFu;
      }
      else{
      ucTempHL = (uint8) scTemp + 50;
      }

      scTemp = scGetValidTyreTemperatureAtWheelPosDM( cRadPosHR);
      if(scTemp == cInvalidREtemperature){
      ucTempHR = 0xFFu;
      }
      else{
      ucTempHR = (uint8) scTemp + 50;
      }
   }
   else{
      ushTref     = 0x00FF;
      ucPva       = 0x63;
      ucPha       = 0x63;
      ushWnThFa   = 0x270Fu;
      ushWnThRa   = 0x270Fu;
      ushNyThFa   = 0x270Fu;
      ushNyThRa   = 0x270Fu;
      ushPressVL  = 0x270Fu;
      ushPressVR  = 0x270Fu;
      ushPressHL  = 0x270Fu;
      ushPressHR  = 0x270Fu;
      ucTempVL    = 0xFFu;
      ucTempVR    = 0xFFu;
      ucTempHL    = 0xFFu;
      ucTempHR    = 0xFFu;
   }

  pucData[cucIxStatRdcExtParkSupConfigWert]                 = ucGetCRdciParkSupExtParkSupConfigCD();
  pucData[cucIxStatRdcExtParkSupTolTempCompWert]            = ucGetCRdciParkSupTolTempCompCD();
  pucData[cucIxStatRdcExtParkSupTolTempNonCompWert]         = ucGetCRdciParkSupTolNoTempCompCD();
  pucData[cucIxStatRdcExtParkSupMobilityLossThWert]         = ucGetCRdciParkSupMobilityLossThValueCD();
  pucData[cucIxStatRdcExtParkSupWarnPercentCompWert]        = ucGetCRdciParkSupWarningThCValueCD();
  pucData[cucIxStatRdcExtParkSupWarnPercentNonCompWert]     = ucGetCRdciParkSupWarningThNcValueCD();
  pucData[cucIxStatRdcExtParkSupNotifPercentCompWert]       = ucGetCRdciParkSupNotifThCValueCD();
  pucData[cucIxStatRdcExtParkSupNotifPercentNonCompWert]    = ucGetCRdciParkSupNotifThNcValueCD();
  pucData[cucIxStatRdcExtParkSupRefTempWert + 0]            = (uint8) ((ushTref >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupRefTempWert + 1]            = (uint8) ((ushTref >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupLastAmbPresWert]            = (uint8) ((((uint16) GETucPAmbValEE(self) * 25) - 600) / 2);
  pucData[cucIxStatRdcExtParkSupRcpFrontWert]               = ucPva;
  pucData[cucIxStatRdcExtParkSupRcpRearWert]                = ucPha;
  pucData[cucIxStatRdcExtParkSupQuFnTyrInfoWert]            = ucQuFnTyrInfo;
  pucData[cucIxStatRdcExtParkSupQuTplWert]                  = ucQuTpl;
  pucData[cucIxStatRdcExtParkSupIntWarnThFrontWert + 0]     = (uint8) ((ushWnThFa >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntWarnThFrontWert + 1]     = (uint8) ((ushWnThFa >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntWarnThRearWert + 0]      = (uint8) ((ushWnThRa >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntWarnThRearWert + 1]      = (uint8) ((ushWnThRa >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntNotifThFrontWert + 0]    = (uint8) ((ushNyThFa >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntNotifThFrontWert + 1]    = (uint8) ((ushNyThFa >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntNotifThRearWert + 0]     = (uint8) ((ushNyThRa >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupIntNotifThRearWert + 1]     = (uint8) ((ushNyThRa >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureFlWert + 0]  = (uint8) ((ushPressVL >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureFlWert + 1]  = (uint8) ((ushPressVL >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureFrWert + 0]  = (uint8) ((ushPressVR >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureFrWert + 1]  = (uint8) ((ushPressVR >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureRlWert + 0]  = (uint8) ((ushPressHL >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureRlWert + 1]  = (uint8) ((ushPressHL >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureRrWert + 0]  = (uint8) ((ushPressHR >> 8) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTirePressureRrWert + 1]  = (uint8) ((ushPressHR >> 0) & 0x00FF);
  pucData[cucIxStatRdcExtParkSupActTireTempFlWert]          = ucTempVL;
  pucData[cucIxStatRdcExtParkSupActTireTempFrWert]          = ucTempVR;
  pucData[cucIxStatRdcExtParkSupActTireTempRlWert]          = ucTempHL;
  pucData[cucIxStatRdcExtParkSupActTireTempRrWert]          = ucTempHR;
  pucData[cucIxStatRdcExtParkSupActiveCcm1Wert + 0]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm1Wert + 1]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm2Wert + 0]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm2Wert + 1]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm3Wert + 0]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm3Wert + 1]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm4Wert + 0]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm4Wert + 1]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm5Wert + 0]         = 0x00;
  pucData[cucIxStatRdcExtParkSupActiveCcm5Wert + 1]         = 0x00;
   ucNoCcmId = 0;
   for(ucLoop = 0; ((ucLoop < cCcIX_NumberOfMessages) && (ucNoCcmId < 5)); ucLoop++){
      if((ulGetStartedStateOfVklCCM() & (uint32)(1 << ucLoop)) == (uint32)(1 << ucLoop)){
      ushCcmId = ushGetCcNumberOfIxCCM(ucLoop);
      switch(ucNoCcmId){
        case (uint8) 0:
          pucData[cucIxStatRdcExtParkSupActiveCcm1Wert + 0] = (uint8) ((ushCcmId >> 8) & 0x00FF);
          pucData[cucIxStatRdcExtParkSupActiveCcm1Wert + 1] = (uint8) ((ushCcmId >> 0) & 0x00FF);
        break;

        case (uint8) 1:
          pucData[cucIxStatRdcExtParkSupActiveCcm2Wert + 0] = (uint8) ((ushCcmId >> 8) & 0x00FF);
          pucData[cucIxStatRdcExtParkSupActiveCcm2Wert + 1] = (uint8) ((ushCcmId >> 0) & 0x00FF);
        break;

        case (uint8) 2:
          pucData[cucIxStatRdcExtParkSupActiveCcm3Wert + 0] = (uint8) ((ushCcmId >> 8) & 0x00FF);
          pucData[cucIxStatRdcExtParkSupActiveCcm3Wert + 1] = (uint8) ((ushCcmId >> 0) & 0x00FF);
        break;

        case (uint8) 3:
          pucData[cucIxStatRdcExtParkSupActiveCcm4Wert + 0] = (uint8) ((ushCcmId >> 8) & 0x00FF);
          pucData[cucIxStatRdcExtParkSupActiveCcm4Wert + 1] = (uint8) ((ushCcmId >> 0) & 0x00FF);
        break;

        default:
          pucData[cucIxStatRdcExtParkSupActiveCcm5Wert + 0] = (uint8) ((ushCcmId >> 8) & 0x00FF);
          pucData[cucIxStatRdcExtParkSupActiveCcm5Wert + 1] = (uint8) ((ushCcmId >> 0) & 0x00FF);
        break;
      }

      ucNoCcmId++;
      }
   }
   timeDate = GETtExtParkSupSleepTimeDateEE(self);
  GetDateStringDM( timeDate.DISP_DATE_YR, timeDate.DISP_DATE_MON, timeDate.DISP_DATE_DAY, aucDateBuffer, sizeof(aucDateBuffer));
  GetTimeStringDM( timeDate.DISP_HR, timeDate.DISP_MN, timeDate.DISP_SEC, aucTimeBuffer, sizeof(aucTimeBuffer));
   for(ucLoop = 0; ucLoop < 8; ucLoop++){
    pucData[cucIxStatRdcExtParkSupSleepDateWert + ucLoop] = aucDateBuffer[ucLoop];
    pucData[cucIxStatRdcExtParkSupSleepTimeWert + ucLoop] = aucTimeBuffer[ucLoop];
   }
   timeDate = GETtExtParkSupWakeupTimeDateEE(self);
  GetDateStringDM( timeDate.DISP_DATE_YR, timeDate.DISP_DATE_MON, timeDate.DISP_DATE_DAY, aucDateBuffer, sizeof(aucDateBuffer));
  GetTimeStringDM( timeDate.DISP_HR, timeDate.DISP_MN, timeDate.DISP_SEC, aucTimeBuffer, sizeof(aucTimeBuffer));
   for(ucLoop = 0; ucLoop < 8; ucLoop++){
    pucData[cucIxStatRdcExtParkSupWakeupDateWert + ucLoop] = aucDateBuffer[ucLoop];
    pucData[cucIxStatRdcExtParkSupWakeupTimeWert + ucLoop] = aucTimeBuffer[ucLoop];
   }
}

static uint16 SearchMaxWarnLimitValue(uint16 current, uint16 new)
{
   if(current != (cInvalidREpressure * 25)){
      if(new != (cInvalidREpressure * 25)){
      current = ushGetMaxValueDM(current, new);
      }
   }
   else{
    current = new;
   }
   return (current);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

