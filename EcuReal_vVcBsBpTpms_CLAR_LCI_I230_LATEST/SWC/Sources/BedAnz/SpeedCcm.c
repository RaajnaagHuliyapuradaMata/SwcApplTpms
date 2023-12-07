#include "SpeedCcm.h"
#include "CodingDataX.h"
#include "State_BzX.h"
#include "State_FzzX.h"
#include "eRFS_X.h"
#include "EeErfsBlockX.h"
#include "WAllocX.h"
#include "DataManagerX.h"
#include "UsWarn_IfX.h"

static uint16 ushSpeedVmaxTimeSCC;
static uint16 ushSpeedCcmThFaSCC;
static uint16 ushSpeedCcmThRaSCC;
static uint8  ucStateSCC;

void InitSCC(void)
{
   ushSpeedVmaxTimeSCC = 0xffffu;

   ushSpeedCcmThFaSCC = 0;
   ushSpeedCcmThRaSCC = 0;

   ucStateSCC = 0x00u;
   if(bGetCRdciSpeedCcmEnableCD() == TRUE){
      ucStateSCC |= cSCC_STATE_SPEED_CCM_ENABLED;
   }
}

uint8 ucGetStateSCC(uint8 ucMask)
{
   return (ucStateSCC & ucMask);
}

void MainSCC(Rte_Instance self)
{
   if((ucStateSCC & cSCC_STATE_SPEED_CCM_ENABLED) == cSCC_STATE_SPEED_CCM_ENABLED){

    CalculatePressThSCC(self);

      if(bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){

      ucStateSCC |= cSCC_STATE_WP_KNOWN;

      if(bIsPressureTooLowSCC() == TRUE){

        ucStateSCC |= cSCC_STATE_P_TOO_LOW;
      }
      else{

        ucStateSCC &= (uint8) ~cSCC_STATE_P_TOO_LOW;
      }
      }
      else{
      ucStateSCC &= (uint8) ~cSCC_STATE_WP_KNOWN;
      ucStateSCC &= (uint8) ~cSCC_STATE_P_TOO_LOW;
      }

      if(bPwfIsFahrenFZZ() == TRUE){

      ucStateSCC |= cSCC_STATE_PWF_FAHREN;

      if(bIsSpeedTooHighSCC() == TRUE){

        ucStateSCC |= cSCC_STATE_V_TOO_HIGH;

          if(((ucStateSCC & (cSCC_STATE_DISPLAY_CCM_2158 | cSCC_STATE_DISPLAY_CCM_2159)) == 0) && ((ucStateSCC & cSCC_STATE_P_TOO_LOW) == cSCC_STATE_P_TOO_LOW) && ((ucStateSCC & cSCC_STATE_WP_KNOWN) == cSCC_STATE_WP_KNOWN)){

          if((ucStateSCC & cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC) == cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC){

            ucStateSCC |= cSCC_STATE_DISPLAY_CCM_2158;
          }
          else{

            ucStateSCC |= cSCC_STATE_DISPLAY_CCM_2159;
            ucStateSCC |= cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC;
          }
        }
        else{

        }
      }
      else{

        ucStateSCC &= (uint8) ~cSCC_STATE_V_TOO_HIGH;
        ucStateSCC &= (uint8) ~cSCC_STATE_DISPLAY_CCM_2158;
        ucStateSCC &= (uint8) ~cSCC_STATE_DISPLAY_CCM_2159;
      }
      }
      else{

      ucStateSCC &= (uint8) ~cSCC_STATE_PWF_FAHREN;
      ucStateSCC &= (uint8) ~cSCC_STATE_V_TOO_HIGH;
      ucStateSCC &= (uint8) ~cSCC_STATE_DISPLAY_CCM_2158;
      ucStateSCC &= (uint8) ~cSCC_STATE_DISPLAY_CCM_2159;
      ucStateSCC &= (uint8) ~cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC;
      ushSpeedVmaxTimeSCC = 0xffffu;
      }
   }
}

void GetSpeedCcmValSCC_debug(uint8* pucState, uint16* pushSpeedVmaxTime, uint16* pushSpeedCcmThFa, uint16* pushSpeedCcmThRa)
{
  *pucState           = ucStateSCC;
  *pushSpeedVmaxTime  = ushSpeedVmaxTimeSCC;
  *pushSpeedCcmThFa   = ushSpeedCcmThFaSCC;
  *pushSpeedCcmThRa   = ushSpeedCcmThRaSCC;
}

static void CalculatePressThSCC(Rte_Instance self)
{
   uint8  ucTyreIx;
   uint8  ucHistId;

   uint8  ucTemp;
   sint8  scTemp;
   uint16 ushTemp;

   sint8  scTinit;
   uint8  ucPl, ucPr;
   uint16 ushM;
   uint8  ucPamb;

   ucTyreIx = GETSelectedTyreIndexEE(self);

   ucHistId = ucGetColOfWP( cRadPosVL);
   ushSpeedCcmThFaSCC = (uint16) (((sint16) GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucTyreIx) * 25) + sshGetCRdciSpeedCcmPressOffsetFaCD());
   (void) ucGetPTSollUSWIF(self, &ucTemp, &scTinit, &ucTemp, &scTemp, &ushTemp, &ucPamb, ucHistId);
   ushM = ushMIso( (uint8) (ushSpeedCcmThFaSCC / 25), scTinit, ucPamb);
   ucPl = ucPfT(ushM, scGetReTemperatureCentDM(ucHistId), ucPamb);

   ucHistId = ucGetColOfWP( cRadPosVR);
   ushSpeedCcmThFaSCC = (uint16) (((sint16) GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucTyreIx) * 25) + sshGetCRdciSpeedCcmPressOffsetFaCD());
   (void) ucGetPTSollUSWIF(self, &ucTemp, &scTinit, &ucTemp, &scTemp, &ushTemp, &ucPamb, ucHistId);
   ushM = ushMIso( (uint8) (ushSpeedCcmThFaSCC / 25), scTinit, ucPamb);
   ucPr = ucPfT(ushM, scGetReTemperatureCentDM(ucHistId), ucPamb);

   if(ucPl > ucPr){
      ushSpeedCcmThFaSCC = (uint16)ucPl * 25;
   }
   else{
      ushSpeedCcmThFaSCC = (uint16)ucPr * 25;
   }

   ucHistId = ucGetColOfWP( cRadPosHL);
   ushSpeedCcmThRaSCC = (uint16) (((sint16) GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucTyreIx) * 25) + sshGetCRdciSpeedCcmPressOffsetRaCD());
   (void) ucGetPTSollUSWIF(self, &ucTemp, &scTinit, &ucTemp, &scTemp, &ushTemp, &ucPamb, ucHistId);
   ushM = ushMIso( (uint8) (ushSpeedCcmThRaSCC / 25), scTinit, ucPamb);
   ucPl = ucPfT(ushM, scGetReTemperatureCentDM(ucHistId), ucPamb);

   ucHistId = ucGetColOfWP( cRadPosHR);
   ushSpeedCcmThRaSCC = (uint16) (((sint16) GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucTyreIx) * 25) + sshGetCRdciSpeedCcmPressOffsetRaCD());
   (void) ucGetPTSollUSWIF(self, &ucTemp, &scTinit, &ucTemp, &scTemp, &ushTemp, &ucPamb, ucHistId);
   ushM = ushMIso( (uint8) (ushSpeedCcmThRaSCC / 25), scTinit, ucPamb);
   ucPr = ucPfT(ushM, scGetReTemperatureCentDM(ucHistId), ucPamb);

   if(ucPl > ucPr){
      ushSpeedCcmThRaSCC = (uint16)ucPl * 25;
   }
   else{
      ushSpeedCcmThRaSCC = (uint16)ucPr * 25;
   }
}

static boolean bIsPressureTooLowSCC(void)
{
   uint8   ucWheelPos, ucHistId;
   boolean bPressTooLow = FALSE;

   for(ucWheelPos = cRadPosVL; ((ucWheelPos <= cRadPosHR) && (bPressTooLow == FALSE)); ucWheelPos++){
      ucHistId = ucGetColOfWP(ucWheelPos);

      if((ucGetRePressureRelDM(ucHistId) != cInvalidREpressure) && (ucHistId < cAnzRad)){

      switch(ucWheelPos){
        case cRadPosVL:
        case cRadPosVR:

          if(((uint16) ucGetRePressureRelDM(ucHistId) * 25) < ushSpeedCcmThFaSCC){
            bPressTooLow = TRUE;
          }
        break;

        default:
          if(((uint16) ucGetRePressureRelDM(ucHistId) * 25) < ushSpeedCcmThRaSCC){
            bPressTooLow = TRUE;
          }
        break;
      }
      }
   }

   return bPressTooLow;
}

static boolean bIsSpeedTooHighSCC(void)
{
   static boolean bSpeedTooHigh = FALSE;

   if(GETushSpeedFZZ() >= ushGetCRdciSpeedCcmThCD()){

      if(ushSpeedVmaxTimeSCC == 0xffffu){

      ushSpeedVmaxTimeSCC = ((uint16) ucGetCRdciSpeedCcmTimeCD() * 10);

      bSpeedTooHigh = FALSE;
      }
      else{

      if(ushSpeedVmaxTimeSCC > 0){
        ushSpeedVmaxTimeSCC--;
      }
      else{

        bSpeedTooHigh = TRUE;
      }
      }
   }
   else if(GETushSpeedFZZ() < (ushGetCRdciSpeedCcmThCD() - ucGetCRdciSpeedCcmHystCD())){

      ushSpeedVmaxTimeSCC = 0xffffu;

    bSpeedTooHigh = FALSE;
   }
   else{

      if(bSpeedTooHigh == FALSE){

      ushSpeedVmaxTimeSCC = 0xffffu;
      }
   }

   return bSpeedTooHigh;
}
