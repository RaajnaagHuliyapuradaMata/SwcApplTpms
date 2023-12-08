/******************************************************************************/
/* File   : InfoTyre.c                                                        */
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
#include "InfoTyreX.h"

#include "datamanagerX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "BreakTireX.h"
#include "USWarn_ifX.h"
#include "erfs_X.h"
#include "wallocX.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeErfsBlockX.h"
#include "EeDiagBlockX.h"
#include "EeHistoryBlockX.h"
#include "CodingDatax.h"
#include "WuMonitoringX.h"
#include "NwMonitoringX.h"
#include "RID_X.h"
#include "BandmodeX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cQuFnTyrInfo_Ready                                    ((uint8)     0x20)
#define cQuFnTyrInfo_Init                                     ((uint8)     0x80)
#define cQuFnTyrInfo_Error                                    ((uint8)     0x60)
#define cQuFnTyrInfo_Interference                             ((uint8)     0xE0)
#define cQuFnTyrInfo_LearningPhase                            ((uint8)     0xE8)
#define cQuFnTyrInfo_Active                                   ((uint8)     0xA0)
#define cQuFnTyrInfo_Fallback                                 ((uint8)     0xB0)
#define cQuFnTyrInfo_Active_Reset                             ((uint8)     0xA8)
#define cQuFnTyrInfo_Fallback_Reset                           ((uint8)     0xB8)
#define cQuTpl_Init                                           ((uint8)     0x80)
#define cQuTpl_BreakTyrePosBase                               ((uint8)     0x20)
#define cQuTpl_BreakTyrePosMaskFr                             ((uint8)     0x21)
#define cQuTpl_BreakTyrePosMaskFl                             ((uint8)     0x22)
#define cQuTpl_BreakTyrePosMaskRr                             ((uint8)     0x24)
#define cQuTpl_BreakTyrePosMaskRl                             ((uint8)     0x28)
#define cQuTpl_BreakTyreNoPos                                 ((uint8)     0x30)
#define cQuTpl_Diffusion                                      ((uint8)     0x31)
#define cQuTpl_Active                                         ((uint8)     0xA0)
#define cQuTfai_Init                                          ((uint8)     0x80)
#define cQuTfai_FlatTyreFr                                    ((uint8)     0x21)
#define cQuTfai_FlatTyreFl                                    ((uint8)     0x22)
#define cQuTfai_FlatTyreRr                                    ((uint8)     0x24)
#define cQuTfai_FlatTyreRl                                    ((uint8)     0x28)
#define cQuTfai_Active                                        ((uint8)     0xA0)
#define cCoolTyreMonInit                                      ((uint8)     0x00)
#define cCoolTyreMonRunning                                   ((uint8)     0x01)
#define cCoolTyreMonWaiting                                   ((uint8)     0x02)
#define cCoolTyreMonFinish                                    ((uint8)     0x03)
#define cCoolTyreMonDriving                                   ((uint8)     0x7f)
#define cCoolTyreMonDeactivated                               ((uint8)     0xff)
#define cInitValCoolingDownTime                               ((uint16) 0xffffu)
#define cCoolingIntervalInitVal                               ((uint16) 0xffffu)
#define cCoolingIntervalResetVal                              ((uint16) 0x7fffu)
#define cCoolingIntervalTicksVal                              ((uint16)     600)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8 ucAvlPTyre_warm;
   sint8 scAvlTTyre_warm;
   uint8 ucAvlPTyre_kalt;
   sint8 scAvlTTyre_kalt;
   uint8 ucAvlPTyre_t;
   sint8 scAvlTTyre_t;
   uint8 ucTarPTyre_warm;
   uint8 ucTarPTyre_kalt;
   sint8 scTarTTyre_kalt;
   uint8 ucTarPTyre_t;
}tCoolTyreMonDataDeclCD;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static PhySensorTyrePresType ucTarPTyreFlh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreFrh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreRlh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreRrh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreFlh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreFrh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreRlh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreRrh = cInvalidREpressure;
static sint8                 scAvlTTyreFlh = cInvalidREtemperature;
static sint8                 scAvlTTyreFrh = cInvalidREtemperature;
static sint8                 scAvlTTyreRlh = cInvalidREtemperature;
static sint8                 scAvlTTyreRrh = cInvalidREtemperature;
static uint8                 ucQuFnTyrInfo;
static uint8                 ucQuTpl;
static uint8                 ucQuTfai;
static uint8                 ucDispConfTime = FALSE;
static uint8                 ucStChangeTime = FALSE;

static boolean               bSuppressDisplayOfPTValuesITY      (Rte_Instance self);
static uint16                ushGetConvertedPressureValueITY    (uint16 ushPressureValue, tPressureUnitType eTo, boolean bRoundMode);
static uint16                ushGetConvertedTemperatureValueITY (sint16 sshTemperatureValue, tTemperatureUnitType eFrom, tTemperatureUnitType eTo);
static void                  SetQuFnTyrInfoITY                  (Rte_Instance self);
static void                  SetQuTplITY                        (void);
static void                  SetQuTfaiITY                       (Rte_Instance self);
static void                  GetPinitTinitITY                   (uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr);
static void                  CorrectFilteredTaITY               (Rte_Instance self);
static uint8                 ucCoolingTyreMonitoringITY         (Rte_Instance self, uint16* pushElapsedCoolingTime);
static void                  InitAvlPTyreCoolingDownDataITY     (Rte_Instance self, uint8 ucHistSlot, uint8 ucState);
static void                  InitTarPTyreCoolingDownDataITY     (Rte_Instance self, uint8 ucHistSlot, uint8 ucState);
static void                  SetAvlPTyreCoolingDataITY          (Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState);
static void                  SetTarPTyreCoolingDataITY          (Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState);
static void                  CalcCoolingDownDataITY             (uint16 ushElapsedCoolingTime);

static tCoolTyreMonDataDeclCD tCoolTyreMonData[cAnzRad] = {
      {cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure}
   ,  {cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure, cInvalidREpressure, cInvalidREtemperature, cInvalidREpressure}
};

static uint16  ushCoolingTicks             = cCoolingIntervalInitVal;
static uint32  ulCoolingCaptTime_g         = (uint32) 0xFFFFFFFFu;
static boolean bTelReceived                = FALSE;
static boolean bBeladungChanged            = FALSE;
static uint16  ushElapsedCoolingTime_debug = 0;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitITY(Rte_Instance self){
   uint8 ucHistSlot;

   ucAvlPTyreFlh = cInvalidREpressure;
   ucAvlPTyreFrh = cInvalidREpressure;
   ucAvlPTyreRlh = cInvalidREpressure;
   ucAvlPTyreRrh = cInvalidREpressure;

   scAvlTTyreFlh = cInvalidREtemperature;
   scAvlTTyreFrh = cInvalidREtemperature;
   scAvlTTyreRlh = cInvalidREtemperature;
   scAvlTTyreRrh = cInvalidREtemperature;

   ucTarPTyreFlh = cInvalidREpressure;
   ucTarPTyreFrh = cInvalidREpressure;
   ucTarPTyreRlh = cInvalidREpressure;
   ucTarPTyreRrh = cInvalidREpressure;

   ucQuFnTyrInfo = cQuFnTyrInfo_Init;
   ucQuTpl       = cQuTpl_Init;
   ucQuTfai      = cQuTfai_Init;

   for(ucHistSlot = 0; ucHistSlot<cAnzRad; ucHistSlot++){
      tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = cInvalidREpressure;
      tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = cInvalidREtemperature;
      tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = cInvalidREpressure;
      tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = cInvalidREtemperature;
      tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = cInvalidREpressure;
      tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = cInvalidREtemperature;
      tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = cInvalidREpressure;
      tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt = cInvalidREpressure;
      tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt = cInvalidREtemperature;
      tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = cInvalidREpressure;
   }

   ushCoolingTicks = cCoolingIntervalInitVal;
   ulCoolingCaptTime_g = (uint32) 0xFFFFFFFFu;
   bTelReceived = FALSE;
   bBeladungChanged = FALSE;

   ushElapsedCoolingTime_debug = 0;

   ulCoolingCaptTime_g = GETulCoolingCaptTimeEE(self);
   ushCoolingTicks = cCoolingIntervalInitVal;

   for(ucHistSlot = 0; ucHistSlot<cAnzRad; ucHistSlot++){
      InitAvlPTyreCoolingDownDataITY(self, ucHistSlot, cNotifyInitITY);
      InitTarPTyreCoolingDownDataITY(self, ucHistSlot, cNotifyInitITY);
   }
}

void MainFunctionITY(Rte_Instance self){
   uint8   ucCoolingState, ucHistSlot, ucWheelPos;
   uint16  ushElapsedCoolingTime;
   boolean bDefectFlag;

   SetQuTplITY();
   SetQuTfaiITY(self);
   SetQuFnTyrInfoITY(self);
   SetTarPTyrDisplayValueDM(self, GETSelectedLoadStateEE(self), GETSelectedTyreIndexEE(self), GETStManSelectionEE(self));
   ucCoolingState = ucCoolingTyreMonitoringITY(self, &ushElapsedCoolingTime);
   if(cCoolTyreMonInit == ucCoolingState){
   }
   else if((cCoolTyreMonRunning == ucCoolingState) || (cCoolTyreMonWaiting == ucCoolingState)){
      if(cCoolingIntervalInitVal == ushCoolingTicks){
         CalcCoolingDownDataITY(ushElapsedCoolingTime);
         ushCoolingTicks = cCoolingIntervalTicksVal;
      }
      else{
         if(ushCoolingTicks > 0){
            ushCoolingTicks--;
         }
         else{
            CalcCoolingDownDataITY(ushElapsedCoolingTime);
            ushCoolingTicks = cCoolingIntervalTicksVal;
         }
      }
   }
   else if(cCoolTyreMonFinish == ucCoolingState){
      CalcCoolingDownDataITY(0);
   }
   else if(ucCoolingState == cCoolTyreMonDriving){
   }
   else{
      CorrectFilteredTaITY(self);
   }
   if(TRUE == bSuppressDisplayOfPTValuesITY(self)){
      ucAvlPTyreFlh = cInvalidREpressure;
      ucAvlPTyreFrh = cInvalidREpressure;
      ucAvlPTyreRlh = cInvalidREpressure;
      ucAvlPTyreRrh = cInvalidREpressure;

      scAvlTTyreFlh = cInvalidREtemperature;
      scAvlTTyreFrh = cInvalidREtemperature;
      scAvlTTyreRlh = cInvalidREtemperature;
      scAvlTTyreRrh = cInvalidREtemperature;

      if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
         bDefectFlag = FALSE;
         for(ucHistSlot = 0; ((ucHistSlot < cAnzRad) && (FALSE == bDefectFlag)); ucHistSlot++){
            if(ushGetReDefectCounterBySlotWUM(ucHistSlot) > 0){
               bDefectFlag = TRUE;
            }
         }
         for(ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
            ucWheelPos = ucGetWPOfColWAL(ucHistSlot);
            if(cRadPosVL == ucWheelPos){
               if(TRUE == bDefectFlag){ucTarPTyreFlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
               else                   {ucTarPTyreFlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            }
            else if(cRadPosVR == ucWheelPos){
               if(TRUE == bDefectFlag){ucTarPTyreFrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
               else                   {ucTarPTyreFrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            }
            else if(cRadPosHL == ucWheelPos){
               if(TRUE == bDefectFlag){ucTarPTyreRlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
               else                   {ucTarPTyreRlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            }
            else if(cRadPosHR == ucWheelPos){
               if(TRUE == bDefectFlag){ucTarPTyreRrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
               else                   {ucTarPTyreRrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            }
            else{
            }
         }
      }
      else{
         ucTarPTyreFlh = cInvalidREpressure;
         ucTarPTyreFrh = cInvalidREpressure;
         ucTarPTyreRlh = cInvalidREpressure;
         ucTarPTyreRrh = cInvalidREpressure;
      }
   }
   else{
      bDefectFlag = FALSE;
      for(ucHistSlot = 0; ((ucHistSlot < cAnzRad) && (FALSE == bDefectFlag)); ucHistSlot++){
         if(ushGetReDefectCounterBySlotWUM(ucHistSlot) > 0){
            bDefectFlag = TRUE;
         }
      }
      for(ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
         ucWheelPos = ucGetWPOfColWAL(ucHistSlot);
         if(cRadPosVL == ucWheelPos){
            if(TRUE == bDefectFlag){ucTarPTyreFlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
            else                   {ucTarPTyreFlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            ucAvlPTyreFlh = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
            scAvlTTyreFlh = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
         }
         else if(cRadPosVR == ucWheelPos){
            if(TRUE == bDefectFlag){ucTarPTyreFrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
            else                   {ucTarPTyreFrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            ucAvlPTyreFrh = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
            scAvlTTyreFrh = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
         }
         else if(cRadPosHL == ucWheelPos){
            if(TRUE == bDefectFlag){ucTarPTyreRlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
            else                   {ucTarPTyreRlh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            ucAvlPTyreRlh = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
            scAvlTTyreRlh = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
         }
         else if(cRadPosHR == ucWheelPos){
            if(TRUE == bDefectFlag){ucTarPTyreRrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;}
            else                   {ucTarPTyreRrh = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;}
            ucAvlPTyreRrh = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
            scAvlTTyreRrh = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
         }
         else{
         }
      }
   }
   ushElapsedCoolingTime_debug = ushElapsedCoolingTime;
}

static void InitAvlPTyreCoolingDownDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucState){
   uint8 ucLoop;
   if(ucHistSlot < cAnzRad){
      switch(ucState){
         case cNotifyInitITY:
            if(0 == ulCoolingCaptTime_g) {SetAvlPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataCvalITY);}
            else                         {SetAvlPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataWvalITY);}
            break;

         case cNotifyTelRecITY:
            for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
               if(ucLoop == ucHistSlot)                                                   {SetAvlPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataWvalITY);}
               else{
                  if(((0xFFFFFFFFu != ulCoolingCaptTime_g) && (ulCoolingCaptTime_g > 0))) {SetAvlPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataReStartITY);}
               }
            }
            break;

         case cNotifyRcpChangedITY:      break;
         case cNotifyBeladungChangedITY: break;
         default:                        break;
      }
   }
}

static void SetAvlPTyreCoolingDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState){
   uint8  ucPc, ucPw, ucPamb;
   sint8  scTc, scTw;
   uint16 ushM;
   switch(ucActionState){
      case cSetCoolingDataInvalidITY:
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = cInvalidREpressure;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = cInvalidREtemperature;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = cInvalidREpressure;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = cInvalidREtemperature;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = cInvalidREpressure;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = cInvalidREtemperature;
         break;

      case cSetCoolingDataCvalITY:
         ucPw = ucGetRePressureRelDM     (ucHistSlot);
         scTw = scGetReTemperatureCentDM (ucHistSlot);
         if((cInvalidREpressure == ucPw) || (cInvalidREtemperature == scTw)){
            ucPc = cInvalidREpressure;
            scTc = cInvalidREtemperature;
            ucPw = cInvalidREpressure;
            scTw = cInvalidREtemperature;
         }
         else{
            scTc = GETscTAmbValEE(self);
            if(scTw > scTc){
               ucPamb = GETucPAmbValEE(self);
               ushM   = ushMIso (ucPw, scTw, ucPamb);
               ucPc   = ucPfT   (ushM, scTc, ucPamb);
            }
            else{
               ucPc = ucPw;
               scTc = scTw;
            }
         }
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = ucPc;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = scTc;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = ucPw;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = scTw;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = ucPc;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = scTc;
         break;

      case cSetCoolingDataWvalITY:
         ucPw = ucGetRePressureRelDM     (ucHistSlot);
         scTw = scGetReTemperatureCentDM (ucHistSlot);
         if((cInvalidREpressure == ucPw) || (cInvalidREtemperature == scTw)){
            ucPc = cInvalidREpressure;
            scTc = cInvalidREtemperature;
            ucPw = cInvalidREpressure;
            scTw = cInvalidREtemperature;
         }
         else{
            scTc = GETscTAmbValEE(self);
            if(scTw > scTc){
               ucPamb = GETucPAmbValEE(self);
               ushM   = ushMIso (ucPw, scTw, ucPamb);
               ucPc   = ucPfT   (ushM, scTc, ucPamb);
            }
            else{
               ucPc = ucPw;
               scTc = scTw;
            }
         }
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = ucPc;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = scTc;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = ucPw;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = scTw;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = ucPw;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = scTw;
         break;

      case cSetCoolingDataReStartITY:
         ucPw = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
         scTw = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
         if((cInvalidREpressure == ucPw) || (cInvalidREtemperature == scTw)){
            ucPc = cInvalidREpressure;
            scTc = cInvalidREtemperature;
            ucPw = cInvalidREpressure;
            scTw = cInvalidREtemperature;
         }
         else{
            scTc = GETscTAmbValEE(self);
            if(scTw > scTc){
               ucPamb = GETucPAmbValEE(self);
               ushM   = ushMIso (ucPw, scTw, ucPamb);
               ucPc   = ucPfT   (ushM, scTc, ucPamb);
            }
            else{
               ucPc = ucPw;
               scTc = scTw;
            }
         }
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = ucPc;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = scTc;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = ucPw;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = scTw;
         tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = ucPw;
         tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = scTw;
         break;

      default:
         break;
   }
}

static void InitTarPTyreCoolingDownDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucState){
   uint8 ucLoop;
   if(ucHistSlot < cAnzRad){
      switch(ucState){
         case cNotifyInitITY:
            if(0 == ulCoolingCaptTime_g){SetTarPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataCvalITY);}
            else                        {SetTarPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataWvalITY);}
            break;

         case cNotifyTelRecITY:
            for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
                    if(0           == ulCoolingCaptTime_g){SetTarPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataCvalITY);}
               else if(0xFFFFFFFFu == ulCoolingCaptTime_g){SetTarPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataWvalITY);}
               else{
                  if(ucLoop == ucHistSlot){SetTarPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataWvalITY);}
                  else                    {SetTarPTyreCoolingDataITY(self, ucLoop, cSetCoolingDataReStartITY);}
               }
            }
            break;

         case cNotifyRcpChangedITY:
         case cNotifyBeladungChangedITY:
            if(0 == ulCoolingCaptTime_g){SetTarPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataCvalITY);}
            else                        {SetTarPTyreCoolingDataITY(self, ucHistSlot, cSetCoolingDataWvalITY);}
            break;

         default:
            break;
      }
   }
}

static void SetTarPTyreCoolingDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState){
   uint8  ucPc, ucPw, ucPamb;
   sint8  scTc, scTw;
   uint16 ushM;
   switch(ucActionState){
      case cSetCoolingDataInvalidITY:
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt = cInvalidREpressure;
         tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt = cInvalidREtemperature;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = cInvalidREpressure;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = cInvalidREpressure;
         break;

      case cSetCoolingDataCvalITY:
         (void) ucGetPTSollUSWIF(self, &ucPc, &scTc, &ucPw, &scTw, &ushM, &ucPamb, ucHistSlot);
         if((cInvalidREpressure == ucPc) || (cInvalidREtemperature == scTc)){
            ucPc = cInvalidREpressure;
            scTc = cInvalidREtemperature;
         }
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt = ucPc;
         tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt = scTc;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = ucPc;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = ucPc;
         break;

      case cSetCoolingDataWvalITY:
         (void) ucGetPTSollUSWIF(self, &ucPc, &scTc, &ucPw, &scTw, &ushM, &ucPamb, ucHistSlot);
         if((cInvalidREpressure == ucPw) || (cInvalidREtemperature == scTw)){
            ucPc = cInvalidREpressure;
            scTc = cInvalidREtemperature;
            ucPw = cInvalidREpressure;
            scTw = cInvalidREtemperature;
         }
         else{
            if(ucPw < ucPc){
               ucPw = ucPc;
            }
            else{
               if((uint16) (ucPc + ucGetCRdciMaxCorRcpCD()) > 254){
               }
               else{
                  if(ucPw > (ucPc + ucGetCRdciMaxCorRcpCD())){
                     ucPw = (ucPc + ucGetCRdciMaxCorRcpCD());
                  }
               }
            }
         }
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt = ucPc;
         tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt = scTc;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = ucPw;
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = ucPw;
         break;

      case cSetCoolingDataReStartITY:
         tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;
         break;

      default:
         break;
   }
}

static void CalcCoolingDownDataITY(uint16 ushElapsedCoolingTime){
   uint8 ucHistSlot;
   for(ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
      if(0 == ushElapsedCoolingTime){
         if(
         (cInvalidREpressure != tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt)
         && (cInvalidREtemperature != tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt)
         ){
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt;
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt;
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt;
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt;
         }
         else{
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt = cInvalidREpressure;
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt = cInvalidREtemperature;
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = cInvalidREpressure;
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = cInvalidREtemperature;
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t    = cInvalidREpressure;
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_t    = cInvalidREtemperature;
         }
         if(cInvalidREpressure != tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt){
            tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;
            tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;
         }
         else{
            tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = cInvalidREpressure;
            tCoolTyreMonData[ucHistSlot].ucTarPTyre_t    = cInvalidREpressure;
         }
      }
      else{
         if(
               (cInvalidREpressure    != tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm)
            && (cInvalidREtemperature != tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm)
            && (cInvalidREpressure    != tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt)
            && (cInvalidREtemperature != tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt)
         ){
            tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm - (uint8) ((((((((((uint32) (tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm - tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt) * (uint32) 100000) / (uint32) ushGetMaxCoolingDownTimeITY()) + 5) / 10) * (uint32) ushElapsedCoolingTime) * 10) / 10000) + 5) / 10);
            tCoolTyreMonData[ucHistSlot].scAvlTTyre_t = tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm - (sint8) ((((((((((sint32) (tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm - tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt) * (sint32) 100000) / (sint32) ushGetMaxCoolingDownTimeITY()) + 5) / 10) * (sint32) ushElapsedCoolingTime) * 10) / 10000) + 5) / 10);
            if(
                  (tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t < tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt)
               || (tCoolTyreMonData[ucHistSlot].scAvlTTyre_t < tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt)
            ){
               tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt;
               tCoolTyreMonData[ucHistSlot].scAvlTTyre_t = tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt;
            }
         }
         if(
               (tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm != cInvalidREpressure)
            && (tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt != cInvalidREpressure)
            && (tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt != cInvalidREtemperature)
         ){
            tCoolTyreMonData[ucHistSlot].ucTarPTyre_t = tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm - (uint8) ((((((((((uint32) (tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm - tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt) * (uint32) 100000) / (uint32) ushGetMaxCoolingDownTimeITY()) + 5) / 10) * (uint32) ushElapsedCoolingTime) * 10) / 10000) + 5) / 10);
            if(tCoolTyreMonData[ucHistSlot].ucTarPTyre_t < tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt){
               tCoolTyreMonData[ucHistSlot].ucTarPTyre_t = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;
            }
            else{
               if((uint16) (tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt + ucGetCRdciMaxCorRcpCD()) > 254){
               }
               else{
                  if(tCoolTyreMonData[ucHistSlot].ucTarPTyre_t > (tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt + ucGetCRdciMaxCorRcpCD())){
                     tCoolTyreMonData[ucHistSlot].ucTarPTyre_t = (tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt + ucGetCRdciMaxCorRcpCD());
                  }
               }
            }
         }
      }
   }
}

void GetTyrePressureValueITY(Rte_Instance self, uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr){
   uint8 ucHistSlot;
   uint8 ucWarnVector[cAnzRad];
   if(FALSE == GETTyreSelectionActiveEE(self)){
      (void) ucGetWarnVectorIdExtIFH(self, ucWarnVector);
      if(cInvalidREpressure == ucAvlPTyreFlh){
         *pushPfl = cTyrePressureNotAvailableValueITY;
      }
      else{
         ucHistSlot = ucGetColOfWP(cRadPosVL);
         if(0 == ucWarnVector[ucHistSlot]){*pushPfl = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreFlh, GETucUnAipEE(self), TRUE );}
         else                             {*pushPfl = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreFlh, GETucUnAipEE(self), FALSE);}
      }
      if(cInvalidREpressure == ucAvlPTyreFrh){
         *pushPfr = cTyrePressureNotAvailableValueITY;
      }
      else{
         ucHistSlot = ucGetColOfWP(cRadPosVR);
         if(0 == ucWarnVector[ucHistSlot]){*pushPfr = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreFrh, GETucUnAipEE(self), TRUE );}
         else                             {*pushPfr = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreFrh, GETucUnAipEE(self), FALSE);}
      }
      if(cInvalidREpressure == ucAvlPTyreRlh){
         *pushPrl = cTyrePressureNotAvailableValueITY;
      }
      else{
         ucHistSlot = ucGetColOfWP(cRadPosHL);
         if(0 == ucWarnVector[ucHistSlot]){*pushPrl = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreRlh, GETucUnAipEE(self), TRUE );}
         else                             {*pushPrl = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreRlh, GETucUnAipEE(self), FALSE);}
      }
      if(cInvalidREpressure == ucAvlPTyreRrh){
         *pushPrr = cTyrePressureNotAvailableValueITY;
      }
      else{
         ucHistSlot = ucGetColOfWP(cRadPosHR);
         if(0 == ucWarnVector[ucHistSlot]){*pushPrr = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreRrh, GETucUnAipEE(self), TRUE );}
         else                             {*pushPrr = ushGetConvertedPressureValueITY((uint16) ucAvlPTyreRrh, GETucUnAipEE(self), FALSE);}
      }
   }
   else{
      if(TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
         *pushPfl = cTyrePressureNotPresentValueITY;
         *pushPfr = cTyrePressureNotPresentValueITY;
         *pushPrl = cTyrePressureNotPresentValueITY;
         *pushPrr = cTyrePressureNotPresentValueITY;
      }
      else{
         *pushPfl = cTyrePressureNotAvailableValueITY;
         *pushPfr = cTyrePressureNotAvailableValueITY;
         *pushPrl = cTyrePressureNotAvailableValueITY;
         *pushPrr = cTyrePressureNotAvailableValueITY;
      }
   }
}

void GetTyreTemperatureValueITY(Rte_Instance self, uint16* pushTfl, uint16* pushTfr, uint16* pushTrl, uint16* pushTrr){
   if(FALSE == GETTyreSelectionActiveEE(self)){
      *pushTfl = ushGetConvertedTemperatureValueITY((sint16) scAvlTTyreFlh, eTEMPERATURE_UNIT_CELSIUS, GETucUnTempEE(self));
      *pushTfr = ushGetConvertedTemperatureValueITY((sint16) scAvlTTyreFrh, eTEMPERATURE_UNIT_CELSIUS, GETucUnTempEE(self));
      *pushTrl = ushGetConvertedTemperatureValueITY((sint16) scAvlTTyreRlh, eTEMPERATURE_UNIT_CELSIUS, GETucUnTempEE(self));
      *pushTrr = ushGetConvertedTemperatureValueITY((sint16) scAvlTTyreRrh, eTEMPERATURE_UNIT_CELSIUS, GETucUnTempEE(self));
   }
   else{
      *pushTfl = cTyreTemperatureNotAvailableValueITY;
      *pushTfr = cTyreTemperatureNotAvailableValueITY;
      *pushTrl = cTyreTemperatureNotAvailableValueITY;
      *pushTrr = cTyreTemperatureNotAvailableValueITY;
   }
}

void GetRelatedPressureValueITY(Rte_Instance self, uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr){
   uint16 ushPfl, ushPfr, ushPrl, ushPrr;
   GetPinitTinitITY(&ushPfl, &ushPfr, &ushPrl, &ushPrr);
   if(
         (ushPfl >= cTyrePressureNotPresentValueITY)
      || (ushPfr >= cTyrePressureNotPresentValueITY)
      || (ushPrl >= cTyrePressureNotPresentValueITY)
      || (ushPrr >= cTyrePressureNotPresentValueITY)
   ){
      *pushPfl = cTyrePressureFuncIfaceNotAvailableValueITY;
      *pushPfr = cTyrePressureFuncIfaceNotAvailableValueITY;
      *pushPrl = cTyrePressureFuncIfaceNotAvailableValueITY;
      *pushPrr = cTyrePressureFuncIfaceNotAvailableValueITY;
   }
   else if(TRUE == GETTyreSelectionActiveEE(self)){
      *pushPfl = ushGetConvertedPressureValueITY(ushPfl, GETucUnAipEE(self), TRUE);
      *pushPfr = ushGetConvertedPressureValueITY(ushPfr, GETucUnAipEE(self), TRUE);
      *pushPrl = ushGetConvertedPressureValueITY(ushPrl, GETucUnAipEE(self), TRUE);
      *pushPrr = ushGetConvertedPressureValueITY(ushPrr, GETucUnAipEE(self), TRUE);
   }
   else if(FALSE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      *pushPfl = ushGetConvertedPressureValueITY(ushPfl, GETucUnAipEE(self), TRUE);
      *pushPfr = ushGetConvertedPressureValueITY(ushPfr, GETucUnAipEE(self), TRUE);
      *pushPrl = ushGetConvertedPressureValueITY(ushPrl, GETucUnAipEE(self), TRUE);
      *pushPrr = ushGetConvertedPressureValueITY(ushPrr, GETucUnAipEE(self), TRUE);
   }
   else if(0 != ucGetReDefectStatusWUM()){
      *pushPfl = ushGetConvertedPressureValueITY(ushPfl, GETucUnAipEE(self), TRUE);
      *pushPfr = ushGetConvertedPressureValueITY(ushPfr, GETucUnAipEE(self), TRUE);
      *pushPrl = ushGetConvertedPressureValueITY(ushPrl, GETucUnAipEE(self), TRUE);
      *pushPrr = ushGetConvertedPressureValueITY(ushPrr, GETucUnAipEE(self), TRUE);
   }
   else{
      *pushPfl = ushGetConvertedPressureValueITY((uint16) ucTarPTyreFlh, GETucUnAipEE(self), TRUE);
      *pushPfr = ushGetConvertedPressureValueITY((uint16) ucTarPTyreFrh, GETucUnAipEE(self), TRUE);
      *pushPrl = ushGetConvertedPressureValueITY((uint16) ucTarPTyreRlh, GETucUnAipEE(self), TRUE);
      *pushPrr = ushGetConvertedPressureValueITY((uint16) ucTarPTyreRrh, GETucUnAipEE(self), TRUE);
   }
}

static uint8 ucCoolingTyreMonitoringITY(Rte_Instance self, uint16* pushElapsedCoolingTime){
   uint32 ulCarStandStillTime;
   uint8  ucRet = cCoolTyreMonInit;
   if(0 != ushGetMaxCoolingDownTimeITY()){
      if(TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
         if((0xFFFFFFFFu != ulCoolingCaptTime_g) && (ulCoolingCaptTime_g > 0)){
            for(uint8 ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
               tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
               tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
               tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;
            }
         }
         ulCoolingCaptTime_g = 0xFFFFFFFFu;
         *pushElapsedCoolingTime = 0;
         bTelReceived = FALSE;
         bBeladungChanged = FALSE;
         ushCoolingTicks = cCoolingIntervalInitVal;
         ucRet = cCoolTyreMonDriving;
      }
      else{
         if(ulCoolingCaptTime_g > 0){
            ulCarStandStillTime = ulGetStopTimeDM();
            if(ulCarStandStillTime > 0u){
               if(TRUE == bTelReceived){
                  *pushElapsedCoolingTime = 0;
                  ulCoolingCaptTime_g = ulCarStandStillTime;
                  bTelReceived = FALSE;
                  bBeladungChanged = FALSE;
                  ushCoolingTicks = cCoolingIntervalTicksVal;
                  ucRet = cCoolTyreMonWaiting;
               }
               else if(0xFFFFFFFFu == ulCoolingCaptTime_g){
                  ulCoolingCaptTime_g = ulCarStandStillTime;
                  *pushElapsedCoolingTime = 0;
                  bBeladungChanged = FALSE;
                  ushCoolingTicks = cCoolingIntervalTicksVal;
                  ucRet = cCoolTyreMonWaiting;
               }
               else{
                  if((ulCarStandStillTime - ulCoolingCaptTime_g) >= ((uint32) ushGetCorHoldOffTimeITY() + (uint32) ushGetMaxCoolingDownTimeITY())){
                     ulCoolingCaptTime_g = 0x00000000;
                     *pushElapsedCoolingTime = 0;
                     bBeladungChanged = FALSE;
                     ushCoolingTicks = cCoolingIntervalInitVal;
                     ucRet = cCoolTyreMonFinish;
                  }
                  else if((ulCarStandStillTime - ulCoolingCaptTime_g) <= ushGetCorHoldOffTimeITY()){
                     *pushElapsedCoolingTime = 0;
                     bBeladungChanged = FALSE;
                     ushCoolingTicks = cCoolingIntervalTicksVal;
                     ucRet = cCoolTyreMonWaiting;
                  }
                  else{
                     *pushElapsedCoolingTime = (uint16) (ulCarStandStillTime - ulCoolingCaptTime_g) - ushGetCorHoldOffTimeITY();
                     if(TRUE == bBeladungChanged){
                        bBeladungChanged = FALSE;
                        ushCoolingTicks = cCoolingIntervalInitVal;
                     }
                     ucRet = cCoolTyreMonRunning;
                  }
               }
               PUTulCoolingCaptTimeEE(self, ulCoolingCaptTime_g);
            }
         }
         else{
            *pushElapsedCoolingTime = 0;
            ushCoolingTicks = cCoolingIntervalInitVal;
            ucRet = cCoolTyreMonDeactivated;
         }
      }
   }
   else{
      ulCoolingCaptTime_g = 0x00000000;
      *pushElapsedCoolingTime = 0;
      ushCoolingTicks = cCoolingIntervalInitVal;
      ucRet = cCoolTyreMonDeactivated;
   }
   return ucRet;
}

uint16 ushGetMaxCoolingDownTimeITY(void){
   return (uint16) ucGetCRdciMaxCorTimeCD() * 60;
}

uint16 ushGetCorHoldOffTimeITY(void){
   return (uint16) ucGetCRdciCorHoldOffTimeCD() * 60;
}

static void GetPinitTinitITY(uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr){
   *pushPfl = GetTarPTyrDisplayValueDM(cRadPosVL);
   *pushPfr = GetTarPTyrDisplayValueDM(cRadPosVR);
   *pushPrl = GetTarPTyrDisplayValueDM(cRadPosHL);
   *pushPrr = GetTarPTyrDisplayValueDM(cRadPosHR);
}

static void CorrectFilteredTaITY(Rte_Instance self){
   sint8 scTAdiff;
   if(GETscOutdoorTemperatureFZZ() < 127){
      scTAdiff = GETscOutdoorTemperatureFZZ() - GETscTAmbValEE(self);
      if((scTAdiff < -10) || (scTAdiff > +10)){
         PUTscTAmbValEE(self, GETscOutdoorTemperatureFZZ());
      }
   }
}

void GetStTyrITY(uint8* pucQuFnTyrInfo, uint8* pucQuTpl, uint8* pucQuTfai){
   *pucQuFnTyrInfo = ucQuFnTyrInfo;
   *pucQuTpl       = ucQuTpl;
   *pucQuTfai      = ucQuTfai;
}

static uint16 ushGetConvertedPressureValueITY(uint16 ushPressureValue, tPressureUnitType eTo, boolean bRoundMode){
   uint16 ushRetVal;
   if(ushPressureValue < 0x00ffu){
      switch(eTo){
      case ePRESSURE_UNIT_KPA: ushRetVal = (((ushPressureValue * (uint16) 25) / 10) * 10);                 break;
      case ePRESSURE_UNIT_PSI: ushRetVal = (uint16) (((uint32) ushPressureValue * 25 * 145) / 10000) * 10; break;

      default:
         if(FALSE == bRoundMode){ushRetVal =  (ushPressureValue >> 2);}
         else                   {ushRetVal = ((ushPressureValue >> 1u) + 0x01u) >> 1u;}
         break;
      }
   }
   else{
      ushRetVal = ushPressureValue;
   }
   return ushRetVal;
}

static uint16 ushGetConvertedTemperatureValueITY(sint16 sshTemperatureValue, tTemperatureUnitType eFrom, tTemperatureUnitType eTo){
   sint16 sshTempVal;
   uint16 ushRetVal;
   switch(eFrom){
      case eTEMPERATURE_UNIT_CELSIUS:
         if((sshTemperatureValue < -40) || (sshTemperatureValue > 125)){
            ushRetVal = cTyreTemperatureNotAvailableValueITY;
         }
         else{
            if(eTEMPERATURE_UNIT_FAHRENHEIT == eTo){
               sshTempVal = (sint16) ((sshTemperatureValue * 18) + 320);
               if(sshTempVal > 0){sshTempVal = ((sshTempVal + 5) / 10);}
               else              {sshTempVal = ((sshTempVal - 5) / 10);}
            }
            else{
               sshTempVal = sshTemperatureValue;
            }
            ushRetVal = (uint16) sshTempVal + cITYTyreTemperatureOffsetValue;
         }
         break;

      case eTEMPERATURE_UNIT_FAHRENHEIT:
         if((sshTemperatureValue < -40) || (sshTemperatureValue > 257)){
            ushRetVal = cTyreTemperatureNotAvailableValueITY;
         }
         else{
            if(eTEMPERATURE_UNIT_CELSIUS == eTo){
               sshTempVal = ((sshTemperatureValue * 10) - (sint16) 320);
               if((sshTempVal % 18) >= 9){sshTempVal = (sshTempVal / 18) + 1;}
               else                      {sshTempVal = (sshTempVal / 18);}
            }
            else{
               sshTempVal = sshTemperatureValue;
            }
            ushRetVal = (uint16) sshTempVal + cITYTyreTemperatureOffsetValue;
         }
         break;

      default:
         if((sshTemperatureValue < -40) || (sshTemperatureValue > 125)){ushRetVal = cTyreTemperatureNotAvailableValueITY;}
         else                                                          {ushRetVal = (uint16) sshTemperatureValue + cITYTyreTemperatureOffsetValue;}
         break;
   }
   return ushRetVal;
}

static boolean bSuppressDisplayOfPTValuesITY(Rte_Instance self){
   uint8   ucLoop;
   boolean bRet = FALSE;
          if(TRUE == bSystemInactiveByRfInterferenceWUM()){bRet = TRUE;}
   else if(0    == ushGetGatewayAntennaTimerValueWUM() ){bRet = TRUE;}
   else if(TRUE == bRdcDataErrorIsSetNWM()             ){bRet = TRUE;}
   else{
      if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
              if(ucGetReMuteStatusWUM()   > 0){bRet = TRUE;}
         else if(ucGetReDefectStatusWUM() > 0){bRet = TRUE;}
         else if(GETucStatusbarEE(self) < 100){
            if((0xA0 != ucQuFnTyrInfo) && (0xA8 != ucQuFnTyrInfo)){
               bRet = TRUE;
            }
         }
         else{
            for(ucLoop = 0; ((ucLoop < cAnzRad) && (FALSE == bRet)); ucLoop++){
                    if(cInvalidREpressure    == ucGetValidTyrePressureRelAtWheelPosDM(ucLoop)){bRet = TRUE;}
               else if(cInvalidREtemperature == scGetValidTyreTemperatureAtWheelPosDM(ucLoop)){bRet = TRUE;}
               else{}
            }
         }
      }
      else{
#ifdef _EcuVirtual
         bRet = FALSE;
#else
         bRet = TRUE;
#endif
      }
   }
   return bRet;
}

static void SetQuFnTyrInfoITY(Rte_Instance self){
   boolean bOutput = FALSE;
   if(TRUE == bGetBandmodeBM()){
      ucQuFnTyrInfo = cQuFnTyrInfo_Error;
   }
   else{
      if(TRUE == GETTyreSelectionActiveEE(self)){
         if(TRUE == GETTyreChangedEE(self)){
            if(TRUE == bGetCRdciDispResetCD()){
               bOutput = TRUE;
            }
         }
         if((TRUE == GETPlausiInitErrorEE(self))){
            if(TRUE == bGetCRdciResetPlausiCD()){
               bOutput = TRUE;
            }
         }
         if(GETucStatusbarEE(self) < 50){
            ucQuFnTyrInfo = cQuFnTyrInfo_LearningPhase;
         }
         else{
            if(TRUE == bGetBitBetriebszustandBZ(cDTC_INACTIVE)){
               if(TRUE == bSystemInactiveByRfInterferenceWUM()){ucQuFnTyrInfo = cQuFnTyrInfo_Interference;}
               else                                            {ucQuFnTyrInfo = cQuFnTyrInfo_Error;}
            }
            else{
               if(TRUE == bOutput){ucQuFnTyrInfo = cQuFnTyrInfo_Fallback_Reset;}
               else               {ucQuFnTyrInfo = cQuFnTyrInfo_Fallback;}
            }
         }
      }
      else{
      if(TRUE == bGetBitBetriebszustandBZ(cDTC_INACTIVE)){
            if(TRUE == bSystemInactiveByRfInterferenceWUM()){ucQuFnTyrInfo = cQuFnTyrInfo_Interference;}
            else                                            {ucQuFnTyrInfo = cQuFnTyrInfo_Error;}
         }
         else{
            if((TRUE == GETPlausiInitErrorEE(self))){
               if(TRUE == bGetCRdciResetPlausiCD()){
                  bOutput = TRUE;
               }
            }
            if(TRUE == GETTyreChangedEE(self)){
               if(TRUE == bGetCRdciDispResetCD()){
                  bOutput = TRUE;
               }
            }
            if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
               if(GETucStatusbarEE(self) < 100){
                  if(TRUE == bOutput){ucQuFnTyrInfo = cQuFnTyrInfo_Fallback_Reset;}
                  else               {ucQuFnTyrInfo = cQuFnTyrInfo_Fallback;}
               }
               else{
                  if(TRUE == bOutput){ucQuFnTyrInfo = cQuFnTyrInfo_Active_Reset;}
                  else               {ucQuFnTyrInfo = cQuFnTyrInfo_Active;}
               }
            }
            else{
               if(TRUE == bGetBitBetriebszustandBZ(cEIGENRAD)){
                  if(TRUE == bOutput){ucQuFnTyrInfo = cQuFnTyrInfo_Fallback_Reset;}
                  else               {ucQuFnTyrInfo = cQuFnTyrInfo_Fallback;}
               }
               else{
                  ucQuFnTyrInfo = cQuFnTyrInfo_Ready;
               }
            }
         }
      }
   }
}

static void SetQuTplITY(void){
   uint8   ucBreakTireState, ucLoop;
   boolean bReAllOk = TRUE;
   if(TRUE == bGetBandmodeBM()){
      ucQuTpl = cQuTpl_Active;
   }
   else{
      ucBreakTireState = ucGetBreakTireStateBT();
      if(cBtWsBreakTireInit == ucBreakTireState){
         if(TRUE == bGetBefuellhinweisBT()){ucQuTpl = cQuTpl_Diffusion;}
         else                              {ucQuTpl = cQuTpl_Active;}
      }
      else{
         if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
                 if(ucGetReMuteStatusWUM()   > 0){bReAllOk = FALSE;}
            else if(ucGetReDefectStatusWUM() > 0){bReAllOk = FALSE;}
            else                                 {bReAllOk = TRUE;}
            if(TRUE == bReAllOk){
               ucQuTpl = 0x00;
               if(0 != (ucBreakTireState & cBtWsBreakTirePw)){
                  ucBreakTireState |= (GETucWarningGroupTM(cucWT_GrpPmin)  & (uint8) 0x0F);
                  ucBreakTireState |= (GETucWarningGroupTM(cucWT_GrpPwarn) & (uint8) 0x0F);
               }
               for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
                  if(0 != (ucBreakTireState & (uint8) (0x01 << ucLoop))){
                     switch(ucLoop){
                        case cRadPosVL: ucQuTpl |= cQuTpl_BreakTyrePosMaskFl; break;
                        case cRadPosVR: ucQuTpl |= cQuTpl_BreakTyrePosMaskFr; break;
                        case cRadPosHL: ucQuTpl |= cQuTpl_BreakTyrePosMaskRl; break;
                        default:        ucQuTpl |= cQuTpl_BreakTyrePosMaskRr; break;
                     }
                  }
               }
            }
            else{
               ucQuTpl = cQuTpl_BreakTyreNoPos;
            }
            if(0x00 == ucQuTpl){ucQuTpl  = cQuTpl_Active;}
            else               {ucQuTpl |= cQuTpl_BreakTyrePosBase;}
         }
         else if(TRUE == bGetBitBetriebszustandBZ(cEIGENRAD)){ucQuTpl = cQuTpl_BreakTyreNoPos;}
         else                                                {ucQuTpl = cQuTpl_Active;}
      }
   }
}

static void SetQuTfaiITY(Rte_Instance self){
   const uint8 ucConvIRadpos2Tfai[cAnzRad] = {cQuTfai_FlatTyreFl, cQuTfai_FlatTyreFr, cQuTfai_FlatTyreRl, cQuTfai_FlatTyreRr};
   const uint8 ucConvBitNo[cAnzRad]        = {0x01, 0x02, 0x04, 0x08};

   uint8 ucLoop;
   uint8 ucFlatTyreState;
   uint8 ucFlatTyreCount;
   uint8 ucFlatTyrePosition;
   uint8 ucFlatTyreHistSlot;
   uint8 ucHardWarningAirMass[cAnzRad];
   uint8 ucHardWarningTonnage[cAnzRad];

          if(TRUE  == bGetBandmodeBM()                            ){ucQuTfai = cQuTfai_Active;}
   else if(FALSE == bGetBitBetriebszustandBZ(cZO_FINISH)        ){ucQuTfai = cQuTfai_Active;}
   else if(TRUE  == bGetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE) ){ucQuTfai = cQuTfai_Active;}
   else if(0     != ucGetReMuteStatusWUM()                      ){ucQuTfai = cQuTfai_Active;}
   else if(0     != ucGetReDefectStatusWUM()                    ){ucQuTfai = cQuTfai_Active;}
   else{
      ucFlatTyreState = (GETucWarningGroupTM(cucWT_GrpFT) & 0x0Fu);
      ucFlatTyreCount = 0;
      for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
         if(0 != (ucFlatTyreState & ucConvBitNo[ucLoop])){
            ucFlatTyreCount++;
            ucQuTfai = ucConvIRadpos2Tfai[ucLoop];
            ucFlatTyrePosition = ucLoop;
         }
      }
           if(0 == ucFlatTyreCount) {ucQuTfai = cQuTfai_Active;}
      else if(ucFlatTyreCount > 1)  {ucQuTfai = cQuTfai_Active;}
      else{
         ucFlatTyreHistSlot = ucGetColOfWP(ucFlatTyrePosition);
         (void)ucGetWarnBitAirMassIdIntIFH(self, ucHardWarningAirMass);
         (void)ucGetWarnBitTonnageIdIntIFH(self, ucHardWarningTonnage);
         for(ucLoop=0; ucLoop<cAnzRad; ucLoop++){
            if(ucFlatTyreHistSlot != ucLoop){
               ucHardWarningAirMass[ucLoop] |= ucHardWarningTonnage[ucLoop];
               ucHardWarningAirMass[ucLoop] &= 0x0f;
               if(ucHardWarningAirMass[ucLoop] > 0){
                  ucQuTfai = cQuTfai_Active;
               }
            }
         }
      }
   }
}

boolean GetListTyreDataITY(const uint8 ucIndex, TyreDataType * ListTyreData){
   boolean bRet = E_OK;

   ListTyreData->Carcass      = 0x00;
   ListTyreData->LoadIndex    = 0x00;
   ListTyreData->Radius       = 0x00;
   ListTyreData->Runflat      = 0x00;
   ListTyreData->Season       = 0x00;
   ListTyreData->SideRelation = 0x00;
   ListTyreData->SpeedIndex   = 0x00;
   ListTyreData->Width        = 0x00;
   ListTyreData->Age          = 0x00;
   ListTyreData->Abrasion     = 0x00;
   ListTyreData->LengthOfRun  = 0x00;
   if(TRUE == bGetCRdciErfsEnableCD()){
      if(ucIndex < OP_SLCTN_TYR_AVLB_AndererReifen){
         ListTyreData->Carcass = GetKarkasseRaw(ucIndex);
         ListTyreData->LoadIndex = GetTragfaehigkeitRaw(ucIndex);
         ListTyreData->Radius = GetDurchmesserRaw(ucIndex);
         ListTyreData->Runflat = GetReifentypRaw(ucIndex);
         ListTyreData->Season = GetSaisonRaw(ucIndex);
         ListTyreData->SideRelation = GetQuerschnittRaw(ucIndex);
         ListTyreData->SpeedIndex = GetGeschwIndexRaw(ucIndex);
         ListTyreData->Width = GetReifenbreiteRaw(ucIndex);
         ListTyreData->Age = 0x00;
         ListTyreData->Abrasion = 0x00;
         ListTyreData->LengthOfRun = 0x00;
      }
   }
   return bRet;
}

boolean GetFAxisTyreDataITY(Rte_Instance self, TyreDataType* FATyreData){
   boolean bRet = E_NOT_OK;
   uint8 ResHistReDimData[cTyreDimSize] = {0x00,0x00,0x00,0x00,0x00,0x00};

  FATyreData->Age         = 0x00;
  FATyreData->Abrasion    = 0x00;
  FATyreData->LengthOfRun = 0x00;

   if(TRUE == bGetCRdciErfsEnableCD()){
      if(OP_IDR_SLCTN_Automatische_Auswahl == GETStManSelectionEE(self)){
      if(TRUE == GetFAxisTyreDataRID(&ResHistReDimData[0])){
        FATyreData->Age         = 0x00;
        FATyreData->Abrasion    = 0x00;
        FATyreData->LengthOfRun = 0x00;
      }
      }
   }
  FATyreData->Width        = (uint8)((ResHistReDimData[0] & 0xF8)>>3);
  FATyreData->Carcass      = (uint8)((ResHistReDimData[0] & 0x06)>>1);
  FATyreData->Runflat      = (uint8)((ResHistReDimData[1] & 0x06)>>1);
  FATyreData->SideRelation = (uint8)((ResHistReDimData[1] & 0xF8)>>3);
  FATyreData->SpeedIndex   = ResHistReDimData[2] & 0x0F;
  FATyreData->Radius       = (uint8)((ResHistReDimData[2] & 0xF0)>>4);
  FATyreData->LoadIndex    = (uint8)((ResHistReDimData[3] & 0xFC)>>2);
  FATyreData->Season       = ResHistReDimData[3] & 0x03;
   bRet = E_OK;
   return bRet;
}

boolean GetRAxisTyreDataITY(Rte_Instance self, TyreDataType* RATyreData){
   boolean bRet                           = E_NOT_OK;
   uint8   ResHistReDimData[cTyreDimSize] = {0x00,0x00,0x00,0x00,0x00,0x00};
   uint8   TyreListIndex;

   if(TRUE == bGetCRdciErfsEnableCD()){
      if(OP_IDR_SLCTN_Automatische_Auswahl == GetStatusManSelectionDM()){
         (void) GetRAxisTyreDataRID(self, &ResHistReDimData[0]);
         RATyreData->Width        = (uint8)((ResHistReDimData[0] & 0xF8)>>3);
         RATyreData->Carcass      = (uint8)((ResHistReDimData[0] & 0x06)>>1);
         RATyreData->Runflat      = (uint8)((ResHistReDimData[1] & 0x06)>>1);
         RATyreData->SideRelation = (uint8)((ResHistReDimData[1] & 0xF8)>>3);
         RATyreData->SpeedIndex   = ResHistReDimData[2] & 0x0F;
         RATyreData->Radius       = (uint8)((ResHistReDimData[2] & 0xF0)>>4);
         RATyreData->LoadIndex    = (uint8)((ResHistReDimData[3] & 0xFC)>>2);
         RATyreData->Season       = ResHistReDimData[3] & 0x03;
         RATyreData->Age          = 0x00;
         RATyreData->Abrasion     = 0x00;
         RATyreData->LengthOfRun  = 0x00;
      }
      else{
         if(CSEASON_SUMMER == GETSelectedSeasonEE(self)){TyreListIndex = GETSelectedSuTyreIndexEE(self);}
         else                                           {TyreListIndex = GETSelectedWiTyreIndexEE(self);}
         (void)GetListTyreDataITY(TyreListIndex, RATyreData);
      }
   }
   else{
      RATyreData->Width        = 0x00;
      RATyreData->Carcass      = 0x00;
      RATyreData->Runflat      = 0x00;
      RATyreData->SideRelation = 0x00;
      RATyreData->SpeedIndex   = 0x00;
      RATyreData->Radius       = 0x00;
      RATyreData->LoadIndex    = 0x00;
      RATyreData->Season       = 0x00;
      RATyreData->Age          = 0x00;
      RATyreData->Abrasion     = 0x00;
      RATyreData->LengthOfRun  = 0x00;
   }
   bRet = E_OK;
   return bRet;
}

void StartDisplayConfTimeoutITY(uint8 TimeoutVal){
	ucDispConfTime = ((TimeoutVal & 0x0F)*10);
}

uint8 GetDisplayConfTimeoutITY(void){
   if(ucDispConfTime > FALSE){
      ucDispConfTime--;
   }
   return ucDispConfTime;
}

void StartStChangeTimeITY(uint8 TimeoutVal){
   ucStChangeTime = ((TimeoutVal & 0x0F)*10);
}

uint8 GetStChangeTimeITY(void){
   if(ucStChangeTime > FALSE){
      ucStChangeTime--;
   }
   return ucStChangeTime;
}

void NotificationITY(Rte_Instance self, uint8 ucNotificationState, uint8 ucSlotNo){
   uint8 ucHistSlot;
   if(cNotifyTelRecITY == ucNotificationState){
      if(ucSlotNo < cAnzRad){
         InitAvlPTyreCoolingDownDataITY(self, ucSlotNo, cNotifyTelRecITY);
         InitTarPTyreCoolingDownDataITY(self, ucSlotNo, cNotifyTelRecITY);
         bTelReceived = TRUE;
      }
   }
   else if(cNotifyRcpChangedITY == ucNotificationState){
      if(ucSlotNo < cAnzRad){
         InitTarPTyreCoolingDownDataITY(self, ucSlotNo, cNotifyRcpChangedITY);
      }
      else{
         for(ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
            InitTarPTyreCoolingDownDataITY(self, ucHistSlot, cNotifyRcpChangedITY);
         }
      }
   }
   else{
      if(ucSlotNo < cAnzRad){
         InitTarPTyreCoolingDownDataITY(self, ucSlotNo, cNotifyBeladungChangedITY);
      }
      else{
         for(ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++){
            InitTarPTyreCoolingDownDataITY(self, ucHistSlot, cNotifyBeladungChangedITY);
         }
      }
      bBeladungChanged = TRUE;
   }
}

void GetAvlPTyreCoolingValITY(uint8 ucHistSlot, uint8* pucAvlPTyre_warm, sint8* pscAvlTTyre_warm, uint8* pucAvlPTyre_kalt, sint8* pscAvlTTyre_kalt, uint8* pucAvlPTyre_t, sint8* pscAvlTTyre_t, uint8* pucTarPTyre_warm, uint8* pucTarPTyre_kalt, sint8* pscTarTTyre_kalt, uint8* pucTarPTyre_t, uint16* pushElapsedCoolingTime, uint16* pushTimeTicks, uint32* pulCoolingCaptTime){
   *pucAvlPTyre_warm       = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_warm;
   *pscAvlTTyre_warm       = tCoolTyreMonData[ucHistSlot].scAvlTTyre_warm;
   *pucAvlPTyre_kalt       = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_kalt;
   *pscAvlTTyre_kalt       = tCoolTyreMonData[ucHistSlot].scAvlTTyre_kalt;
   *pucAvlPTyre_t          = tCoolTyreMonData[ucHistSlot].ucAvlPTyre_t;
   *pscAvlTTyre_t          = tCoolTyreMonData[ucHistSlot].scAvlTTyre_t;
   *pucTarPTyre_warm       = tCoolTyreMonData[ucHistSlot].ucTarPTyre_warm;
   *pucTarPTyre_kalt       = tCoolTyreMonData[ucHistSlot].ucTarPTyre_kalt;
   *pscTarTTyre_kalt       = tCoolTyreMonData[ucHistSlot].scTarTTyre_kalt;
   *pucTarPTyre_t          = tCoolTyreMonData[ucHistSlot].ucTarPTyre_t;
   *pushElapsedCoolingTime = ushElapsedCoolingTime_debug;
   *pushTimeTicks          = ushCoolingTicks;
   *pulCoolingCaptTime     = ulCoolingCaptTime_g;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

