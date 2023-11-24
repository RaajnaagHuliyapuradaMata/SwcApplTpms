#include "SteuernDigitalRdc.h"
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

uint8 ucPutSteuernDigitalRdcDS( Rte_Instance self, uint8 ucFunctionNo, uint8 ucActionNo)
{
  uint8 ucRet = cucRetValErrorDS;

  if( ucFunctionNo == cFunctionNo_BandmodeDS)
  {

    ucRet = ucBandmodeDS( self, ucActionNo);
  }else if( ucFunctionNo == cFunctionNo_TestErFahrtDS)
  {

    ucRet = ucTestErFahrtDS( self, ucActionNo);
  }else if( ucFunctionNo == cFunctionNo_CalRequestDS)
  {

    ucRet = ucCalRequestDS( self, ucActionNo);
  }else{

    ucRet = cucRetValErrorDS;
  }

  return ucRet;
}

static uint8 ucBandmodeDS( Rte_Instance self, uint8 ucAction)
{
  uint8   ucRet  = cucRetValErrorDS;
  boolean bState = FALSE;

  if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Wohnen)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Pruefen_Analyse_Diagnose)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_herstellen)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahren)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_beenden)
  {
    bState = TRUE;
  }else{
  }

  if( bState == TRUE)
  {
    if( ucAction == cActionNo_BandmodeEinDS)
    {

      BandmodeActivateBM();

      PUTTyreSelectionBckgrdEE( self, FALSE);
      PUTTyreSelectionActiveEE( self, FALSE);

      InitSBR( self);
      StartLearnLocateWAM( self);
      WatoStopWAM();
      SetWumActivityStatusWUM( self, cWUM_DISABLED, cNO_EVALUATION);
      PUTushBandmodeStateEE( self, ushGetStateBM());
      ucRet = cucRetValOkDS;
    }else if( ucAction == cActionNo_BandmodeAusDS)
    {

      BandmodeDeactivateBM();
      SetWumActivityStatusWUM( self, cWUM_ENABLED, cNO_EVALUATION);
      if(bGetCRdciErfsEnableCD() == FALSE)
      {
        PUTPlausiInitErrorEE( self, TRUE);
      }
      else
      {
        if(GETStSelectTyreEE( self) == ST_SLCTN_TYR_Verbaut_Felgensensor)
        {
          PUTTyreChangedEE( self, FALSE);
        }
        else
        {
          PUTTyreChangedEE( self, TRUE);
          PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Keine_automatische_Auswahl2M7CK, StatusWheelTypeChangePosition_Position_Unbekannt);
        }
      }
      StartLearnLocateWAM( self);
      PUTushBandmodeStateEE( self, ushGetStateBM());
      ucRet = cucRetValOkDS;
    }else{
      ucRet = cucRetValErrorDS;
    }
  }

  return ucRet;
}

static uint8 ucTestErFahrtDS( Rte_Instance self, uint8 ucAction)
{
  uint8   ucRet  = cucRetValOkDS;
  boolean bState = FALSE;

  if( bGetBandmodeBM() == TRUE)
  {
    if( bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE)
    {
      if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Wohnen)
      {
        bState = TRUE;
      }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Pruefen_Analyse_Diagnose)
      {
        bState = TRUE;
      }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_herstellen)
      {
        bState = TRUE;
      }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahren)
      {
        bState = TRUE;
      }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_beenden)
      {
        bState = TRUE;
      }else{
      }
    }
  }

  if( bState == TRUE)
  {
    if( ucAction == cActionNo_TestErFahrtSetDS)
    {

      if( bStartServiceBM( cushTestEigenradFahrtBM) == TRUE)
      {
        ucRet = cucRetValServiceNotStartetDS;
      }else{
        SetWumActivityStatusWUM( self, cWUM_BM_DIENST_START, cNO_EVALUATION);
      }
    }else if( ucAction == cActionNo_TestErFahrtSetNoSpeedDS)
    {
      if( bStartServiceBM( cushTestEigenradFahrtNoSpeedBM) == TRUE)
      {
        ucRet = cucRetValServiceNotStartetDS;
      }else{
        SetWumActivityStatusWUM( self, cWUM_BM_DIENST_START, cNO_EVALUATION);
      }
    }else if( ucAction == cActionNo_TestErFahrtResetDS)
    {
      StopServiceBM();
      SetWumActivityStatusWUM( self, cWUM_DISABLED, cDO_EVALUATION);
      ucRet = cucRetValOkDS;
    }else{
      ucRet = cucRetValErrorDS;
    }

    PUTushBandmodeStateEE( self, ushGetStateBM());

  }else{
    ucRet  = cucRetValErrorDS;
  }

  return ucRet;
}

static uint8 ucCalRequestDS( Rte_Instance self, uint8 ucAction)
{
  uint8   ucRet  = cucRetValErrorDS;
  boolean bState = FALSE;

  if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Wohnen)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Pruefen_Analyse_Diagnose)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_herstellen)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahren)
  {
    bState = TRUE;
  }else if( ucGetStatusConditionVehicleFZZ() == ST_CON_VEH_Fahrbereitschaft_beenden)
  {
    bState = TRUE;
  }else{
  }

  if( bState == TRUE)
  {
    if( ucAction == cActionNo_CalRequestSetDS)
    {

      if(GetSelectedTyreIndexDM() == OP_SLCTN_TYR_AVLB_AndererReifen)
      {
        if(CheckPrepareTyreSelectionDM( self, GetLoadStateDM(), GetSelectedTyreIndexDM(), GetSeasonDM(), GetStatusManSelectionDM()) == TRUE)
        {
          SaveCurrentTyreSelectionDM( self);
          ucRet = cucRetValOkDS;
        }
      }

    }else if( ucAction == cActionNo_CalRequestResetDS)
    {

      ucRet = cucRetValOkDS;
    }else{
      ucRet = cucRetValErrorDS;
    }
  }

  return ucRet;
}

