/******************************************************************************/
/* File   : SteuernDigitalRdc.c                                               */
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
#include "SteuernDigitalRdcX.h"
#include "DataManagerX.h"
#include "BandmodeX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "EeDiagBlockX.h"
#include "EeErfsBlockX.h"
#include "wallocX.h"
#include "walloc_managerX.h"
#include "WuMonitoringX.h"
#include "HS_KalibrierereignisX.h"
#include "CodingDataX.h"
#include "StatusbarX.h"

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
static uint8 ucBandmodeDS(Rte_Instance self, uint8 ucAction);
static uint8 ucTestErFahrtDS(Rte_Instance self, uint8 ucAction);
static uint8 ucCalRequestDS(Rte_Instance self, uint8 ucAction);

uint8 ucPutSteuernDigitalRdcDS(Rte_Instance self, uint8 ucFunctionNo, uint8 ucActionNo){
   uint8 ucRet;
   switch(ucFunctionNo){
      case cFunctionNo_BandmodeDS:    ucRet = ucBandmodeDS    (self, ucActionNo); break;
      case cFunctionNo_TestErFahrtDS: ucRet = ucTestErFahrtDS (self, ucActionNo); break;
      case cFunctionNo_CalRequestDS:  ucRet = ucCalRequestDS  (self, ucActionNo); break;
      default:                        ucRet = cucRetValErrorDS;                   break;
   }
   return ucRet;
}

static uint8 ucBandmodeDS(Rte_Instance self, uint8 ucAction){
   uint8 ucRet;
   switch(ucGetStatusConditionVehicleFZZ()){
      case ST_CON_VEH_Wohnen:
      case ST_CON_VEH_Pruefen_Analyse_Diagnose:
      case ST_CON_VEH_Fahrbereitschaft_herstellen:
      case ST_CON_VEH_Fahren:
      case ST_CON_VEH_Fahrbereitschaft_beenden:
         switch(ucAction){
            case cActionNo_BandmodeEinDS:
               BandmodeActivateBM();
               PUTTyreSelectionBckgrdEE(self, FALSE);
               PUTTyreSelectionActiveEE(self, FALSE);
               InitSBR(self);
               StartLearnLocateWAM(self);
               WatoStopWAM();
               SetWumActivityStatusWUM(self, cWUM_DISABLED, cNO_EVALUATION);
               PUTushBandmodeStateEE(self, ushGetStateBM());
               ucRet = cucRetValOkDS;
               break;

            case cActionNo_BandmodeAusDS:
               BandmodeDeactivateBM();
               SetWumActivityStatusWUM(self, cWUM_ENABLED, cNO_EVALUATION);
               if(FALSE == bGetCRdciErfsEnableCD()){
                  PUTPlausiInitErrorEE(self, TRUE);
               }
               else{
                  if(GETStSelectTyreEE(self) == ST_SLCTN_TYR_Verbaut_Felgensensor){
                     PUTTyreChangedEE(self, FALSE);
                  }
                  else{
                     PUTTyreChangedEE(self, TRUE);
                     PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Keine_automatische_Auswahl2M7CK, StatusWheelTypeChangePosition_Position_Unbekannt);
                  }
               }
               StartLearnLocateWAM(self);
               PUTushBandmodeStateEE(self, ushGetStateBM());
               ucRet = cucRetValOkDS;
               break;

            default:
               ucRet = cucRetValErrorDS;
               break;
         }
         break;

      default:
         ucRet = cucRetValErrorDS;
         break;
   }
   return ucRet;
}

static uint8 ucTestErFahrtDS(Rte_Instance self, uint8 ucAction){
   uint8 ucRet;
   if(TRUE == bGetBandmodeBM()){
      if(TRUE == bGetBitBetriebszustandBZ(cEIGENRAD)){
         switch(ucGetStatusConditionVehicleFZZ()){
            case ST_CON_VEH_Wohnen:
            case ST_CON_VEH_Pruefen_Analyse_Diagnose:
            case ST_CON_VEH_Fahrbereitschaft_herstellen:
            case ST_CON_VEH_Fahren:
            case ST_CON_VEH_Fahrbereitschaft_beenden:
               switch(ucAction){
                  case cActionNo_TestErFahrtSetDS:
                     if(TRUE == bStartServiceBM(cushTestEigenradFahrtBM)){
                        ucRet = cucRetValServiceNotStartetDS;
                     }
                     else{
                        ucRet = cucRetValOkDS;
                        SetWumActivityStatusWUM(self, cWUM_BM_DIENST_START, cNO_EVALUATION);
                     }
                     break;

                  case cActionNo_TestErFahrtSetNoSpeedDS:
                     if(TRUE == bStartServiceBM(cushTestEigenradFahrtNoSpeedBM)){
                        ucRet = cucRetValServiceNotStartetDS;
                     }
                     else{
                        ucRet = cucRetValOkDS;
                        SetWumActivityStatusWUM(self, cWUM_BM_DIENST_START, cNO_EVALUATION);
                     }
                     break;

                  case cActionNo_TestErFahrtResetDS:
                     StopServiceBM();
                     SetWumActivityStatusWUM(self, cWUM_DISABLED, cDO_EVALUATION);
                     ucRet = cucRetValOkDS;
                     break;

                  default:
                     ucRet = cucRetValErrorDS;
                     break;
               }
               PUTushBandmodeStateEE(self, ushGetStateBM());
               break;

            default:
               ucRet = cucRetValErrorDS;
               break;
         }
      }
      else{
         ucRet = cucRetValErrorDS;
      }
   }
   else{
      ucRet = cucRetValErrorDS;
   }
   return ucRet;
}

static uint8 ucCalRequestDS(Rte_Instance self, uint8 ucAction){
   uint8 ucRet = cucRetValErrorDS;
   switch(ucGetStatusConditionVehicleFZZ()){
      case ST_CON_VEH_Wohnen:
      case ST_CON_VEH_Pruefen_Analyse_Diagnose:
      case ST_CON_VEH_Fahrbereitschaft_herstellen:
      case ST_CON_VEH_Fahren:
      case ST_CON_VEH_Fahrbereitschaft_beenden:
         switch(ucAction){
            case cActionNo_CalRequestSetDS:
               if(OP_SLCTN_TYR_AVLB_AndererReifen == GetSelectedTyreIndexDM()){
                  if(TRUE == CheckPrepareTyreSelectionDM(self, GetLoadStateDM(), GetSelectedTyreIndexDM(), GetSeasonDM(), GetStatusManSelectionDM())){
                     SaveCurrentTyreSelectionDM(self);
                     ucRet = cucRetValOkDS;
                  }
                  else{
                     ucRet = cucRetValErrorDS;
                  }
               }
               else{
                  ucRet = cucRetValErrorDS;
               }
               break;

            case cActionNo_CalRequestResetDS:
               ucRet = cucRetValOkDS;
               break;

            default:
               ucRet = cucRetValErrorDS;
               break;
         }
         break;

      default:
         ucRet = cucRetValErrorDS;
         break;
   }
   return ucRet;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

