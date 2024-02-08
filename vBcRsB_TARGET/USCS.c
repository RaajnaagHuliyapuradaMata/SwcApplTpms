#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "global.hpp"
#include "USWarn.hpp"
#include "USCS.hpp"
#include "WnTypePar.hpp"

#define ucTSollDefc 20U
#define ushPMinInMBar 1500U
#define ushPSollDefInMBar 1800U
#define ucPMinDefc (unsigned char) 60U
#define ucPSollDefc (unsigned char) 72U
#define ushMSollDefc (unsigned short) 391U
#define ucPwarmDefc ucPSollDefc
#define ushPMinInMBarUS 1400U
#define ushPSollDefInMBarUS 1800U
#define ucPMinDefUSc  (unsigned char) 56U
#define ucPSollDefUSc (unsigned char) 72U
#define ushMSollDefUSc (unsigned short) 391U
#define ushPMinXLInMBar 1600U
#define ushPMinSollXLInMBarc 2000U
#define ucPMinXLc  (unsigned char) 64U
#define ucPMinSollXLc  (unsigned char) 80U
#define ushMSollDefXLc (unsigned short) 419U

union CDA tCDA;

unsigned char ucGetPMinCS(
   void){
   return (tCDA.tCalTab.ucPMinAbs);
}

unsigned char ucPutPMinCS(
   unsigned char ucPMin,
   unsigned char ucMode){
   static const unsigned char aucPMinCSc[4] = {
      (ucPMinDefc ),
      (ucPMinDefUSc ),
      (ucPMinXLc ),
      (u8_PRC_MinPrs_digits)};
   unsigned char ucRet;
   unsigned char u8_activeLegislation = E_US_LEG_NON_EXTRA_LOAD_TIRES;
   ucMode = ucMode;
   u8_activeLegislation = GETucVarCodLegislationEE();
   if((u8_activeLegislation > 0) && (u8_activeLegislation < E_INVALID_LEG)){
      if(ucPMin >= aucPMinCSc[u8_activeLegislation - 1]){
         tCDA.tCalTab.ucPMinAbs = ucPMin;
         ucRet = 0xFF;
      }
      else{
         ucRet = 0;
         tCDA.tCalTab.ucPMinAbs = aucPMinCSc[u8_activeLegislation - 1];
      }
   }
   else{
      ucRet = 0;
   }
   return (ucRet);
}

unsigned char ucGetPSollCS(
   unsigned char ucIdX){
   if(ucIdX < ucSumWEc){
      return (tCDA.tCalTab.aucPSoll[ucIdX]);
   }
   else{
      return ((unsigned char)0);
   }
}

signed char scGetTSollCS(
   unsigned char ucIdX){
   if(ucIdX < ucSumWEc){
      return (tCDA.tCalTab.ascTSoll[ucIdX]);
   }
   else{
      return (-126);
   }
}

unsigned short ushGetMSollCS(
   unsigned char ucIdX){
   if(ucIdX < ucSumWEc){
      return (tCDA.tCalTab.aushMSoll[ucIdX]);
   }
   else{
      return (0);
   }
}

unsigned char ucPutCalTabVectorCS(
   unsigned char ucIdX,
   unsigned char ucP,
   signed char scT,
   unsigned short ushM){
   unsigned char ucRet;
   if(ucIdX < ucSumWEc){
      if(ucP >= tCDA.tCalTab.aucPSollMin[ucIdX]){
         tCDA.tCalTab.aushMSoll[ucIdX] = ushM;
         tCDA.tCalTab.aucPSoll[ucIdX] = ucP;
         tCDA.tCalTab.ascTSoll[ucIdX] = scT;
         ucRet = 0xFF;
      }
      else{
         ucRet = 0;
      }
   }
   else{
      ucRet = 0;
   }
   return (ucRet);
}

unsigned char ucPutPSollMinCS(
   unsigned char ucIdX,
   unsigned char ucP,
   unsigned char ucMode){
   const unsigned char aucPSollMinCSc[3] = {
      (ucPSollDefc ),
      (ucPSollDefUSc ),
      (ucPMinSollXLc )};
   unsigned char ucRet;
   if(ucIdX < ucSumWEc){
      if(ucP >= aucPSollMinCSc[ucMode]){
         tCDA.tCalTab.aucPSollMin[ucIdX] = ucP;
         ucRet = 0xFF;
      }
      else{
         ucRet = 0;
      }
   }
   else{
      ucRet = 0;
   }
   return (ucRet);
}

void InitCS(
   unsigned char ucInit){
   unsigned char i;
   switch(ucInit){
      case (unsigned short)0: {
         tCDA.tCalTab.ucPMinAbs = ucPMinDefc;
         for(i = 0; i < ucSumWEc ; i++){
            tCDA.tCalTab.aucPSollMin[i] = ucPSollDefc;
            tCDA.tCalTab.aucPSoll[i] = ucPSollDefc;
            tCDA.tCalTab.ascTSoll[i] = ucTSollDefc;
            tCDA.tCalTab.aushMSoll[i] = ushMSollDefc;
            tCDA.tCalTab.aucPWarm[i] = ucPwarmDefc;
         }
      }
         break;

      case (unsigned short)1: {
         tCDA.tCalTab.ucPMinAbs = ucPMinDefUSc;
         for(i = 0; i < ucSumWEc ; i++){
            tCDA.tCalTab.aucPSollMin[i] = ucPSollDefUSc;
            tCDA.tCalTab.aucPSoll[i] = ucPSollDefUSc;
            tCDA.tCalTab.ascTSoll[i] = ucTSollDefc;
            tCDA.tCalTab.aushMSoll[i] = ushMSollDefUSc;
            tCDA.tCalTab.aucPWarm[i] = ucPwarmDefc;
         }
      }
         break;

      case (unsigned short)2: {
         tCDA.tCalTab.ucPMinAbs = ucPMinXLc;
         for(i = 0; i < ucSumWEc ; i++){
            tCDA.tCalTab.aucPSollMin[i] = ucPMinSollXLc;
            tCDA.tCalTab.aucPSoll[i] = ucPMinSollXLc;
            tCDA.tCalTab.ascTSoll[i] = ucTSollDefc;
            tCDA.tCalTab.aushMSoll[i] = ushMSollDefXLc;
            tCDA.tCalTab.aucPWarm[i] = ucPwarmDefc;
         }
      }
         break;

      default:
         break;
   }
   return;
}

unsigned char ucGetPwarmCS(
   unsigned char ucIdX){
   if(ucIdX < ucSumWEc){
      return (tCDA.tCalTab.aucPWarm[ucIdX]);
   }
   else{
      return (0);
   }
}

void PutPwarmCS(
   unsigned char Pwarm,
   unsigned char ucIdX){
   if((ucIdX < ucSumWEc ) && (Pwarm >= ucPwarmDefc )){
      tCDA.tCalTab.aucPWarm[ucIdX] = (Pwarm);
   }
}
