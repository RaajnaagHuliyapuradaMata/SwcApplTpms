/******************************************************************************/
/* File   : ccm.c                                                             */
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
#include "ccmX.h"

#include "state_bzX.h"
#include "BreakTireX.h"
#include "WarningLampX.h"
#include "RID_X.h"
#include "EeErfsBlockX.h"
#include "EeHistoryBlockX.h"
#include "CodingDataX.h"
#include "WuMonitoringX.h"
#include "BandmodeX.h"
#include "DatamanagerX.h"
#include "SpeedCcmX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cCcUnspecWarningInFahrzyklusFlagInitState              ((boolean) FALSE)
#define cCcUnspecWarningInFahrzyklusFlagActiveState            ((boolean) TRUE)

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
static const tCcStructDecl tCcStruct[cCcIX_NumberOfMessages] = {
   {  cCcInactive,             cCcFixLampStateBlinking },
   {  cCcExternalInterference, cCcFixLampStateBlinking },
   {  cCcFlatTireFL,           cCcFixLampStateStatic   },
   {  cCcFlatTireFR,           cCcFixLampStateStatic   },
   {  cCcFlatTireRL,           cCcFixLampStateStatic   },
   {  cCcFlatTireRR,           cCcFixLampStateStatic   },
   {  cCcFlatTire,             cCcFixLampStateStatic   },
   {  cCcFlatTireFL_RSC,       cCcFixLampStateStatic   },
   {  cCcFlatTireFR_RSC,       cCcFixLampStateStatic   },
   {  cCcFlatTireRL_RSC,       cCcFixLampStateStatic   },
   {  cCcFlatTireRR_RSC,       cCcFixLampStateStatic   },
   {  cCcFlatTire_RSC,         cCcFixLampStateStatic   },
   {  cCcFlatTireFL_NoRSC,     cCcFixLampStateStatic   },
   {  cCcFlatTireFR_NoRSC,     cCcFixLampStateStatic   },
   {  cCcFlatTireRL_NoRSC,     cCcFixLampStateStatic   },
   {  cCcFlatTireRR_NoRSC,     cCcFixLampStateStatic   },
   {  cCcFlatTire_NoRSC,       cCcFixLampStateStatic   },
   {  cCcDruckwarnung,         cCcFixLampStateStatic   },
   {  cCcBefuellhinweis,       cCcFixLampStateOff      },
   {  cCcReifenwechsel,        cCcFixLampStateOff      },
   {  cCcPlausiCheck,          cCcFixLampStateOff      },
   {  cCcLernphase,            cCcFixLampStateOff      },
   {  cCcAutoSelFailed,        cCcFixLampStateOff      },
   {  cCcSpeedCcm2158,         cCcFixLampStateOff      },
   {  cCcSpeedCcm2159,         cCcFixLampStateOff      },
   {  cCcInvalid,              cCcFixLampStateInvalid  }
};

static uint8 ucNokCounterCCM                        = 0;
static uint8 ucCcIxMalfunction                      = cCcIX_Invalid;
static uint8 ucCcIxInterference                     = cCcIX_Invalid;
static uint8 ucCcIxFlatTire                         = cCcIX_Invalid;
static uint8 ucCcIxFlatTireOldValue                 = cCcIX_Invalid;
static uint8 ucCcIxLernphase                        = cCcIX_Invalid;
static uint8 ucCcIxBefuellhinweis                   = cCcIX_Invalid;
static uint8 ucCcIxReifenwechsel                    = cCcIX_Invalid;
static uint8 ucCcIxPlausiCheck                      = cCcIX_Invalid;
static uint8 ucCcIxAutoSelFailed                    = cCcIX_Invalid;
static uint8 ucCcIxSpeedCcm2158                     = cCcIX_Invalid;
static uint8 ucCcIxSpeedCcm2159                     = cCcIX_Invalid;
static boolean bCcUnspecWarningInFahrzyklusFlag     = cCcUnspecWarningInFahrzyklusFlagInitState;
static uint8 aucVklBits[cCcIX_NumberOfMessages];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static uint8 ucGetMalfunctionCCM(void);
static uint8 ucGetInterferenceCCM(void);
static uint8 ucGetFlatTireCCM(Rte_Instance self);
static uint8 ucGetLernphaseCCM(Rte_Instance self);
static uint8 ucGetReifenwechselCCM(Rte_Instance self);
static uint8 ucGetBefuellhinweisCCM(void);
static uint8 ucGetPlausiCheckCCM(Rte_Instance self);
static uint8 ucGetAutoSelFailedCCM(Rte_Instance self);
static uint8 ucGetSpeedCcm2158CCM(void);
static uint8 ucGetSpeedCcm2159CCM(void);
static void StartCCM(uint8 ucCcmIx);
static void StopCCM(uint8 ucCcmIx);

void InitCCM(void)
{
   uint8 ucLoop;

   ucCcIxMalfunction                     = cCcIX_Invalid;
   ucCcIxInterference                    = cCcIX_Invalid;
   ucCcIxFlatTire                        = cCcIX_Invalid;
   ucCcIxFlatTireOldValue                = cCcIX_Invalid;
   ucCcIxLernphase                       = cCcIX_Invalid;
   ucCcIxBefuellhinweis                  = cCcIX_Invalid;
   ucCcIxReifenwechsel                   = cCcIX_Invalid;
   ucCcIxPlausiCheck                     = cCcIX_Invalid;
   ucCcIxAutoSelFailed                   = cCcIX_Invalid;
   ucCcIxSpeedCcm2158                    = cCcIX_Invalid;
   ucCcIxSpeedCcm2159                    = cCcIX_Invalid;

   bCcUnspecWarningInFahrzyklusFlag      = cCcUnspecWarningInFahrzyklusFlagInitState;

   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
    aucVklBits[ucLoop]  = cCcStartStopState_Invalid;
   }
}

void MainFunctionCCM(Rte_Instance self)
{
   uint8 ucLoop;
   uint8 ucFklAct;
   ucCcIxMalfunction         = ucGetMalfunctionCCM();
   ucCcIxInterference        = ucGetInterferenceCCM();
   ucCcIxFlatTire            = ucGetFlatTireCCM(self);
   ucCcIxLernphase           = ucGetLernphaseCCM(self);
   ucCcIxBefuellhinweis      = ucGetBefuellhinweisCCM();
   ucCcIxPlausiCheck         = ucGetPlausiCheckCCM(self);
   ucCcIxReifenwechsel       = ucGetReifenwechselCCM(self);
   ucCcIxAutoSelFailed       = ucGetAutoSelFailedCCM(self);
   ucCcIxSpeedCcm2158        = ucGetSpeedCcm2158CCM();
   ucCcIxSpeedCcm2159        = ucGetSpeedCcm2159CCM();

   if(ucCcIxMalfunction != cCcIX_Invalid){
    StartCCM( cCcIX_Inactive);
   }
   else{
    StopCCM( cCcIX_Inactive);
   }

   if(ucCcIxInterference != cCcIX_Invalid){
    StartCCM( cCcIX_ExternalInterference);
   }
   else{
    StopCCM( cCcIX_ExternalInterference);
   }

   if(ucCcIxFlatTire != cCcIX_Invalid){
    StopCCM( cCcIX_Befuellhinweis);
      if(ucCcIxFlatTire == cCcIX_Druckwarnung){
      bCcUnspecWarningInFahrzyklusFlag = cCcUnspecWarningInFahrzyklusFlagInitState;
      }else if((ucCcIxFlatTire == cCcIX_FlatTire) || (ucCcIxFlatTire == cCcIX_FlatTire_RSC) || (ucCcIxFlatTire == cCcIX_FlatTire_NoRSC)){
      bCcUnspecWarningInFahrzyklusFlag = cCcUnspecWarningInFahrzyklusFlagActiveState;
      }
      else{
      if(bCcUnspecWarningInFahrzyklusFlag != cCcUnspecWarningInFahrzyklusFlagInitState){
        ucCcIxFlatTire = ucCcIxFlatTireOldValue;
      }
      }

      if(ucCcIxFlatTire != ucCcIxFlatTireOldValue){
      StopCCM(ucCcIxFlatTireOldValue);
      }
    StartCCM(ucCcIxFlatTire);
   }
   else{
      for(ucLoop = cCcIX_FlatTireFL; ucLoop <= cCcIX_Druckwarnung; ucLoop++){
      StopCCM(ucLoop);
      }

      if(ucCcIxBefuellhinweis != cCcIX_Invalid){
      StartCCM( cCcIX_Befuellhinweis);
      }
      else{
      StopCCM( cCcIX_Befuellhinweis);
      }

    bCcUnspecWarningInFahrzyklusFlag = cCcUnspecWarningInFahrzyklusFlagInitState;
   }
   ucCcIxFlatTireOldValue = ucCcIxFlatTire;

   if(ucCcIxLernphase != cCcIX_Invalid){
    StartCCM( cCcIX_Lernphase);
   }
   else{
    StopCCM( cCcIX_Lernphase);
   }

   if(ucCcIxPlausiCheck != cCcIX_Invalid){
    StartCCM( cCcIX_PlausiCheck);
   }
   else{
    StopCCM( cCcIX_PlausiCheck);
   }

   if(ucCcIxReifenwechsel != cCcIX_Invalid){
    StartCCM( cCcIX_Reifenwechsel);
   }
   else{
    StopCCM( cCcIX_Reifenwechsel);
   }

   if(ucCcIxAutoSelFailed != cCcIX_Invalid){
    StartCCM( cCcIX_AutoSelFailed);
   }
   else{
    StopCCM( cCcIX_AutoSelFailed);
   }

   if(ucCcIxSpeedCcm2158 != cCcIX_Invalid){
    StartCCM( cCcIX_SpeedCcm2158);
   }
   else{
    StopCCM( cCcIX_SpeedCcm2158);
   }

   if(ucCcIxSpeedCcm2159 != cCcIX_Invalid){
    StartCCM( cCcIX_SpeedCcm2159);
   }
   else{
    StopCCM( cCcIX_SpeedCcm2159);
   }

   if(ucCcIxMalfunction != cCcIX_Invalid){
      ucFklAct = cCcIX_Inactive;
   }
   else if(ucCcIxInterference != cCcIX_Invalid){
      ucFklAct = cCcIX_ExternalInterference;
   }
   else if(ucCcIxFlatTire != cCcIX_Invalid){
      ucFklAct = ucCcIxFlatTire;
   }
   else if(ucCcIxBefuellhinweis != cCcIX_Invalid){
      ucFklAct = cCcIX_Befuellhinweis;
   }
   else if(ucCcIxReifenwechsel != cCcIX_Invalid){
      ucFklAct = cCcIX_Reifenwechsel;
   }
   else if(ucCcIxPlausiCheck != cCcIX_Invalid){
      ucFklAct = cCcIX_PlausiCheck;
   }
   else if(ucCcIxLernphase != cCcIX_Invalid){
      ucFklAct = cCcIX_Lernphase;
   }
   else if(ucCcIxAutoSelFailed != cCcIX_Invalid){
      ucFklAct = cCcIX_AutoSelFailed;
   }
   else{
      ucFklAct = cCcIX_Invalid;
   }
   PutCheckControlNumberWL( tCcStruct[ucFklAct].ucCcFixLampControl);
}

static uint8 ucGetMalfunctionCCM(void)
{
   uint8 ucRet = cCcIX_Invalid;

   if(bGetBitBetriebszustandBZ( cDTC_INACTIVE) == TRUE){

     if(bSystemInactiveByRfInterferenceWUM() == FALSE)
     {
       ucRet = cCcIX_Inactive;
     }else{
       ucRet = cCcIX_Invalid;
     }
   }
   else if(bGetBandmodeBM() == TRUE){
     ucRet = cCcIX_Inactive;
   }
   else{
     ucRet = cCcIX_Invalid;
   }

   return ucRet;
}

static uint8 ucGetInterferenceCCM(void)
{
   uint8  ucRet = cCcIX_Invalid;

   if(bGetBitBetriebszustandBZ(cDTC_INACTIVE) == TRUE){
      if(bSystemInactiveByRfInterferenceWUM() == TRUE){

      ucRet = cCcIX_ExternalInterference;
      }
   }

   return ucRet;
}

static uint8  ucGetFlatTireCCM(Rte_Instance self)
{
   uint8 ucRet;
   uint8 ucLoop;
   uint8 ucCcBreakTireState;
   boolean bRSCInfo, bReAllOk;

   ucRet =  cCcIX_Invalid;
   ucCcBreakTireState = ucGetBreakTireStateBT();

   if((ucCcBreakTireState & cBtWsBreakTireHiMask) == cBtWsBreakTireInit){
      ucRet = cCcIX_Invalid;
   }
   else if((ucCcBreakTireState & cBtWsBreakTirePw) == cBtWsBreakTirePw){
      if((ucCcBreakTireState & (cBtWsBreakTireTsb | cBtWsBreakTireMulti)) == 0){

      if(ucGetReMuteStatusWUM() > 0){
        bReAllOk = FALSE;
      }
      else if(ucGetReDefectStatusWUM() > 0){
        bReAllOk = FALSE;
      }
      else{
        bReAllOk = TRUE;
      }

      if(bReAllOk == TRUE){
        ucRet = cCcIX_Invalid;

          if(bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){
          for(ucLoop = 0; ((ucLoop < cAnzRad) && (ucRet == cCcIX_Invalid)); ucLoop++){
            if((ucCcBreakTireState & (uint8) (0x01 << ucLoop)) != 0){
              if(ucLoop == cRadPosVL){

                if(GetReliableRSCInfoRID(self, cRadPosVL, &bRSCInfo) == TRUE){
                  if(bRSCInfo == TRUE)
                  {
                    ucRet = cCcIX_FlatTireFL_RSC;
                  }
                  else
                  {
                    ucRet = cCcIX_FlatTireFL_NoRSC;
                  }
                }else{
                  ucRet = cCcIX_FlatTireFL;
                }
              }else if(ucLoop == cRadPosVR){
                if(GetReliableRSCInfoRID(self, cRadPosVR, &bRSCInfo) == TRUE){
                  if(bRSCInfo == TRUE)
                  {
                    ucRet = cCcIX_FlatTireFR_RSC;
                  }
                  else
                  {
                    ucRet = cCcIX_FlatTireFR_NoRSC;
                  }
                }else{
                  ucRet = cCcIX_FlatTireFR;
                }
              }else if(ucLoop == cRadPosHL){
                if(GetReliableRSCInfoRID(self, cRadPosHL, &bRSCInfo) == TRUE){
                  if(bRSCInfo == TRUE)
                  {
                    ucRet = cCcIX_FlatTireRL_RSC;
                  }
                  else
                  {
                    ucRet = cCcIX_FlatTireRL_NoRSC;
                  }
                }else{
                  ucRet = cCcIX_FlatTireRL;
                }
              }else{

                if(GetReliableRSCInfoRID(self, cRadPosHR, &bRSCInfo) == TRUE){
                  if(bRSCInfo == TRUE)
                  {
                    ucRet = cCcIX_FlatTireRR_RSC;
                  }
                  else
                  {
                    ucRet = cCcIX_FlatTireRR_NoRSC;
                  }
                }else{
                  ucRet = cCcIX_FlatTireRR;
                }
              }
            }
          }
        }else if(bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE){

          if(GetReliableRSCInfoRID(self, cRadPosUndef, &bRSCInfo) == TRUE){
             if(bRSCInfo == TRUE)
             {
              ucRet = cCcIX_FlatTire_RSC;
             }
             else
             {
               ucRet = cCcIX_FlatTire_NoRSC;
             }
          }
          else{
            ucRet = cCcIX_FlatTire;
          }
         }
         else{

          ucRet = cCcIX_Invalid;
        }
      }
      else{

          if(GetReliableRSCInfoRID(self, cRadPosUndef, &bRSCInfo) == TRUE){
          if(bRSCInfo == TRUE){
            ucRet = cCcIX_FlatTire_RSC;
            }
            else{
            ucRet = cCcIX_FlatTire_NoRSC;
          }
         }
         else{
          ucRet = cCcIX_FlatTire;
        }
      }
      }
      else{

      if(GetReliableRSCInfoRID(self, cRadPosUndef, &bRSCInfo) == TRUE){
          if(bRSCInfo == TRUE){
          ucRet = cCcIX_FlatTire_RSC;
        }
        else{
          ucRet = cCcIX_FlatTire_NoRSC;
        }
      }
      else{
        ucRet = cCcIX_FlatTire;
      }
      }
   }
   else if((ucCcBreakTireState & cBtWsBreakTireDw) == cBtWsBreakTireDw){

      if(bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE){

      ucRet = cCcIX_Druckwarnung;
      }
      else{

      ucRet = cCcIX_Invalid;
      }
   }
   else{

      ucRet = cCcIX_Invalid;
   }

   return ucRet;
}

static uint8 ucGetLernphaseCCM(Rte_Instance self)
{
   uint8 ucRet = cCcIX_Invalid;

   if(GETucStatusbarEE(self) < 100){

      ucRet = cCcIX_Lernphase;
   }

   return ucRet;
}

static uint8 ucGetReifenwechselCCM(Rte_Instance self)
{
   uint8 ucRet = cCcIX_Invalid;

   if(GETTyreChangedEE(self) == TRUE){
      if(bGetCRdciDispResetCD() == TRUE){

      ucRet = cCcIX_Reifenwechsel;
      }
   }

   return ucRet;
}

static uint8 ucGetAutoSelFailedCCM(Rte_Instance self)
{
   uint8 ucRet = cCcIX_Invalid;

   if(GETAutomaticSelectionFailedStatusEE(self) == TRUE){
      if(bGetCRdciErfsEnableCD() == TRUE){

      ucRet = cCcIX_AutoSelFailed;
      }
   }

   return ucRet;
}

static uint8 ucGetBefuellhinweisCCM(void)
{
   uint8 ucRet = cCcIX_Invalid;

   if(bGetBefuellhinweisBT() == TRUE){
      ucRet = cCcIX_Befuellhinweis;
   }

   return ucRet;
}

static uint8 ucGetPlausiCheckCCM(Rte_Instance self)
{
   uint8 ucRet = cCcIX_Invalid;

   if(GETPlausiInitErrorEE(self) == TRUE){
      if(bGetCRdciResetPlausiCD() == TRUE){

      ucRet = cCcIX_PlausiCheck;
      }
   }

   return ucRet;
}

static uint8 ucGetSpeedCcm2158CCM(void)
{
   uint8  ucRet;

   if(ucGetStateSCC( cSCC_STATE_DISPLAY_CCM_2158) == cSCC_STATE_DISPLAY_CCM_2158){
      ucRet = cCcIX_SpeedCcm2158;
   }
   else{
      ucRet = cCcIX_Invalid;
   }

   return ucRet;
}

static uint8 ucGetSpeedCcm2159CCM(void)
{
   uint8  ucRet;

   if(ucGetStateSCC( cSCC_STATE_DISPLAY_CCM_2159) == cSCC_STATE_DISPLAY_CCM_2159){
      ucRet = cCcIX_SpeedCcm2159;
   }
   else{
      ucRet = cCcIX_Invalid;
   }

   return ucRet;
}

static void StartCCM(uint8 ucCcmIx)
{
   if(ucCcmIx != cCcIX_Invalid){
      if(aucVklBits[ucCcmIx] != cCcStartStopState_Started){
      aucVklBits[ucCcmIx] = cCcStartStopState_Start;
      }
      else{
      }
   }
   else{
   }
}

static void StopCCM(uint8 ucCcmIx)
{
   if(ucCcmIx != cCcIX_Invalid){
      if(aucVklBits[ucCcmIx] == cCcStartStopState_Started){
      aucVklBits[ucCcmIx] = cCcStartStopState_Stop;
      }
      else{
      }
   }
   else{
   }
}

uint8 ucFillVklDataCCM(uint8 ucIx, uint16* pushCcmId, uint8* pucCcmStartStop, uint8* pucCcmBlinking, uint8* pucTransCycle)
{
   uint8 ucRet = 0;

   if(aucVklBits[ucIx] == cCcStartStopState_Start){
    *pushCcmId          = tCcStruct[ucIx].ushCcNumber;
    *pucCcmStartStop    = cCcStartStopState_Start;
    *pucCcmBlinking     = cCcBlinkState_Off;
    *pucTransCycle      = cCcRepetitionRate_10;
      ucRet = cCcStartStopState_Start;
   }
   else if(aucVklBits[ucIx] == cCcStartStopState_Started){
      ucRet = 0xFF;
   }
   else if(aucVklBits[ucIx] == cCcStartStopState_Stop){
    *pushCcmId          = tCcStruct[ucIx].ushCcNumber;
    *pucCcmStartStop    = cCcStartStopState_Stop;
    *pucCcmBlinking     = cCcBlinkState_Off;
    *pucTransCycle      = cCcRepetitionRate_10;
      ucRet = cCcStartStopState_Stop;
   }
   else if(aucVklBits[ucIx] == cCcStartStopState_Stoped){
    *pushCcmId          = tCcStruct[cCcIX_Invalid].ushCcNumber;
    *pucCcmStartStop    = cCcStartStopState_Invalid;
    *pucCcmBlinking     = cCcBlinkState_Invalid;
    *pucTransCycle      = cCcRepetitionRate_Invalid;

    aucVklBits[ucIx]    = cCcStartStopState_Invalid;
      ucRet = 0xFF;
   }
   else{
    *pushCcmId          = tCcStruct[cCcIX_Invalid].ushCcNumber;
    *pucCcmStartStop    = cCcStartStopState_Invalid;
    *pucCcmBlinking     = cCcBlinkState_Invalid;
    *pucTransCycle      = cCcRepetitionRate_Invalid;

    aucVklBits[ucIx]    = cCcStartStopState_Invalid;
      ucRet = 0xFF;
   }
   return ucRet;
}

void SetVklStartedCCM(uint8 ucIx, boolean bOkFlag)
{
   if(bOkFlag == TRUE){
    aucVklBits[ucIx] = cCcStartStopState_Started;
   }
   else{
      ucNokCounterCCM++;
   }
}

void SetVklStopedCCM(uint8 ucIx, boolean bOkFlag)
{
   if(bOkFlag == TRUE){
    aucVklBits[ucIx] = cCcStartStopState_Stoped;
   }
   else{
      ucNokCounterCCM++;
   }
}

uint8 ucFillFklDataCCM(uint16* pushCcmId, uint8* pucCcmStartStop, uint8* pucCcmBlinking, uint8* pucTransCycle)
{
   uint8 ucRet = 0;
   uint8 ucStartStopState = ucGetCcStartStopStateWL();

   if(ucStartStopState == cCcStartStopState_Start){
    *pushCcmId       = cCcFixLamp;
    *pucCcmStartStop = cCcStartStopState_Start;
    *pucCcmBlinking  = ucGetCcBlinkStateFixLampWL();
    *pucTransCycle   = ucGetCcRepetitionRateWL();
      ucRet = cCcStartStopState_Start;
   }
   else if(ucStartStopState == cCcStartStopState_Started){
    *pushCcmId       = cCcFixLamp;
    *pucCcmStartStop = cCcStartStopState_Start;
    *pucCcmBlinking  = ucGetCcBlinkStateFixLampWL();
    *pucTransCycle   = ucGetCcRepetitionRateWL();
      ucRet = 0xFF;
   }
   else if(ucStartStopState == cCcStartStopState_Stop){
    *pushCcmId       = cCcFixLamp;
    *pucCcmStartStop = cCcStartStopState_Stop;
    *pucCcmBlinking  = ucGetCcBlinkStateFixLampWL();
    *pucTransCycle   = ucGetCcRepetitionRateWL();
      ucRet = cCcStartStopState_Stop;
   }
   else{
    PutCcStartStopStateWL( cCcStartStopState_Invalid);
    *pushCcmId       = cCcInvalid;
    *pucCcmStartStop = cCcStartStopState_Invalid;
    *pucCcmBlinking  = cCcBlinkState_Invalid;
    *pucTransCycle   = cCcRepetitionRate_Invalid;
      ucRet = 0xFF;
   }

   return ucRet;
}

void SetFklStartedCCM( boolean bOkFlag)
{
   if(bOkFlag == TRUE){
    PutCcStartStopStateWL( cCcStartStopState_Started);
   }
   else{
      ucNokCounterCCM++;
   }
}

void SetFklStopedCCM( boolean bOkFlag)
{
   if(bOkFlag == TRUE){
    PutCcStartStopStateWL( cCcStartStopState_Stoped);
   }
   else{
      ucNokCounterCCM++;
   }
}

void StopCycleCCM(void)
{
   bCcUnspecWarningInFahrzyklusFlag = cCcUnspecWarningInFahrzyklusFlagInitState;
}

void StartCycleCCM(void)
{
  BlinkingAllowedWL( TRUE);

  RestartMessagesCCM();
  RestartBlinkingCCM();
}

uint32 ulGetStartStateOfVklCCM(void)
{
   uint8 ucLoop;
   uint32 ulRet = 0x0000;

   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if(aucVklBits[ucLoop] == cCcStartStopState_Start){
      ulRet |= (uint32) (1 << ucLoop);
      }
   }

   return ulRet;
}

uint32 ulGetStopStateOfVklCCM(void)
{
   uint8 ucLoop;
   uint32 ulRet = 0x0000;

   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if(aucVklBits[ucLoop] == cCcStartStopState_Stop){
      ulRet |= (uint32) (1 << ucLoop);
      }
   }

   return ulRet;
}

uint32 ulGetStartedStateOfVklCCM(void)
{
   uint8 ucLoop;
   uint32 ulRet = 0x0000;

   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if((aucVklBits[ucLoop] == cCcStartStopState_Start) || (aucVklBits[ucLoop] == cCcStartStopState_Started)){
      ulRet |= (uint32) (1 << ucLoop);
      }
   }

   return ulRet;
}

void RestartMessagesCCM(void)
{
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if(aucVklBits[ucLoop] == cCcStartStopState_Started){
      aucVklBits[ucLoop] = cCcStartStopState_Start;
      }
   }
}

void RestartBlinkingCCM(void)
{
   uint8 ucLoop;
   uint8 ucBlinkState = cCcFixLampStateInvalid;

   if(ucGetCcBlinkStateFixLampWL() == cCcBlinkState_Slow){
    BlinkingAllowedWL( TRUE);
    SwitchOffWL();
      ucBlinkState = cCcFixLampStateBlinking;
   }
   else{

      for(ucLoop = 0; ((ucLoop < cCcIX_NumberOfMessages) && (ucBlinkState != cCcFixLampStateBlinking)); ucLoop++){
      if((aucVklBits[ucLoop] == cCcStartStopState_Start) || (aucVklBits[ucLoop] == cCcStartStopState_Started)){

        switch( tCcStruct[ucLoop].ucCcFixLampControl){
          case cCcFixLampStateBlinking:
            BlinkingAllowedWL( TRUE);
            SwitchOffWL();
            ucBlinkState = cCcFixLampStateBlinking;
          break;

          case cCcFixLampStateStatic:
            BlinkingAllowedWL( TRUE);
            SwitchOffWL();
            ucBlinkState = cCcFixLampStateStatic;
          break;

          default:
            if(ucBlinkState != cCcFixLampStateStatic){
              BlinkingAllowedWL( TRUE);
              SwitchOffWL();
              ucBlinkState = cCcFixLampStateOff;
            }
          break;
        }
      }
      }
   }

   PutCheckControlNumberWL(ucBlinkState);
}

uint8 ucGetNokCounterCCM(void)
{
   return ucNokCounterCCM;
}

uint16 ushGetCcNumberOfIxCCM(uint8 ucIx)
{
   uint16 ushNum = 0x0000;

   if(ucIx < cCcIX_NumberOfMessages){
      ushNum = tCcStruct[ucIx].ushCcNumber;
   }

   return (ushNum);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

