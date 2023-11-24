#include "state_fzz.h"
#include "datamanagerX.h"

static uint16 ushFahrzeugzustand = 0;
static uint16 ushVehicleSpeedFzz = 0;
static uint8  ucGear = GEAR_INVALID;
static sint8  scOutdoorTemperature = cInvalidOutdoorTemperature;
static uint8  ucStatusConditionVehicleFZZ = ST_CON_VEH_Parken_BN_iO;
static uint8  ucStatusLastConditionVehicleFZZ = ST_CON_VEH_Parken_BN_iO;
static uint8 ucFlexrayStatus = 0x01;

void InitFZZ(void)
{

  ClearBitFahrzeugzustandFZZ( cFZZ_ALLE_BITS);
  ushVehicleSpeedFzz = 0;
  scOutdoorTemperature = cInvalidOutdoorTemperature;
  ucStatusConditionVehicleFZZ = 0xFFu;
  ucStatusLastConditionVehicleFZZ = 0xFFu;
}

void SetBitFahrzeugzustandFZZ( uint16 ushBitMask)
{
   ushFahrzeugzustand |= ushBitMask;
}

void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask)
{
   ushFahrzeugzustand &= ~ushBitMask;
}

boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask)
{
  boolean bRet;

  if( (ushFahrzeugzustand & ushBitMask) == ushBitMask)
  {
    bRet = TRUE;
  }
  else
  {
    bRet = FALSE;
  }

  return bRet;
}

uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask)
{
   return (ushFahrzeugzustand & ushBitMask);
}

void EvTerminal15OnFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN) == FALSE)
  {
    SetBitFahrzeugzustandFZZ( cKL_15_EIN);

    InitAfterKl15OnDM();
  }
}

void EvTerminal15OffFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN) == TRUE)
  {
    ClearBitFahrzeugzustandFZZ( cKL_15_EIN);

    InitAfterKl15OffDM();
  }
}

void EvVehicleRollingFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT) == FALSE)
  {
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT);
  }
}

void EvVehicleStandsStillFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT) == TRUE)
  {
    ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT);
  }
}

void EvReDiagActiveFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES) == FALSE)
  {
    SetBitFahrzeugzustandFZZ( cRS_VTHRES);

  }
}

void EvReDiagInactiveFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES) == TRUE)
  {
    ClearBitFahrzeugzustandFZZ( cRS_VTHRES);
  }
}

void EvDriveDirectionForwardFZZ(void)
{
  ClearBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT);
}

void EvDriveDirectionBackwardFZZ(void)
{
  SetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT);
}

void SETOutdoorTemperatureFZZ( sint8 temperature)
{
  scOutdoorTemperature = temperature;
}

sint8 GETscOutdoorTemperatureFZZ(void)
{
  return scOutdoorTemperature;
}

void SETSpeedFZZ( uint16 speed)
{
  static uint16 ushLastVehicleSpeed = 0;

  ushVehicleSpeedFzz = speed;

  if( ushVehicleSpeedFzz < cV_TH_FAHRZEUG_LERNT_SET)
  {
    ClearBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT);
  }
  else
  {
    SetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT);
  }

  if( ushVehicleSpeedFzz < cV_TH_FAHRZEUG_FAEHRT_SET)
  {
    ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT);
    if(ushLastVehicleSpeed >= cV_TH_FAHRZEUG_FAEHRT_SET)
    {
      ClearBitFahrzeugzustandFZZ( cLONG_PARK);
      ClearStopTimeDM();
    }
  }else{
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT);
  }

  if( ushVehicleSpeedFzz >= cV_MIN_PAL)
  {
    SetBitFahrzeugzustandFZZ( cRS_VTHRES);
  }else{
    ClearBitFahrzeugzustandFZZ( cRS_VTHRES);
  }

  if( ushVehicleSpeedFzz >= cV_MIN_BM)
  {
    SetBitFahrzeugzustandFZZ( cBM_VTHRES);
  }else{
      ClearBitFahrzeugzustandFZZ( cBM_VTHRES);
  }

  if( ushVehicleSpeedFzz > cV_MAX_PAL)
  {
    SetBitFahrzeugzustandFZZ( cMP_VTHRES);
  }else{
    ClearBitFahrzeugzustandFZZ( cMP_VTHRES);
  }

  ushLastVehicleSpeed = ushVehicleSpeedFzz;
}

uint16 GETushSpeedFZZ(void)
{
  return (ushVehicleSpeedFzz);
}

void SetGearFZZ(uint8 gear)
{
  ucGear = gear;
}

uint8 GETucGearFZZ(void)
{
  return (ucGear);
}

void SETBusStateFZZ( ImpTypeValFrBusState busstate)
{
  if(busstate == FR_STATE_ACTIVE)
  {
    ucFlexrayStatus &= (uint8)(~cFzzBusState);
  }
  else
  {
    ucFlexrayStatus |= cFzzBusState;
  }

  if((ucFlexrayStatus & (cFzzBusState | cFzzFSSperre)) > 0)
  {
    SetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED);
  }
  else
  {
    ClearBitFahrzeugzustandFZZ(cNW_DTC_LOCKED);
  }
}

void SETFehlerspeicherSperreFZZ( Rdci_ST_ILK_ERRM_FZM_Type fssperre)
{
  if(fssperre == ST_ILK_ERRM_FZM_Fehlerspeicherfreigabe)
  {
    ucFlexrayStatus &= (uint8)(~cFzzFSSperre);
  }
  else
  {
    ucFlexrayStatus |= cFzzFSSperre;
  }

  if((ucFlexrayStatus & (cFzzBusState | cFzzFSSperre)) > 0)
  {
    SetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED);
  }
  else
  {
    ClearBitFahrzeugzustandFZZ(cNW_DTC_LOCKED);
  }
}

uint8 ucGetFlexrayStatusFZZ(void)
{
  return ucFlexrayStatus;
}

uint8 ucGetStatusConditionVehicleFZZ(void)
{
  return ucStatusConditionVehicleFZZ;
}

uint8 ucGetStatusLastConditionVehicleFZZ(void)
{
  return ucStatusLastConditionVehicleFZZ;
}

void PutStatusConditionVehicleFZZ( uint8 ucStatusConditionVehicle)
{
  ucStatusLastConditionVehicleFZZ = ucStatusConditionVehicleFZZ;
  ucStatusConditionVehicleFZZ = ucStatusConditionVehicle;
  if(( ucStatusConditionVehicle  == ST_CON_VEH_Pruefen_Analyse_Diagnose)
   || ( ucStatusConditionVehicle  == ST_CON_VEH_Fahrbereitschaft_herstellen)
   || ( ucStatusConditionVehicle  == ST_CON_VEH_Fahren)
   || ( ucStatusConditionVehicle  == ST_CON_VEH_Fahrbereitschaft_beenden))
  {
    EvTerminal15OnFZZ();
  }
  else
  {
    EvTerminal15OffFZZ();
  }

}

void ClearStatusLastConditionVehicleFZZ(void)
{
  ucStatusLastConditionVehicleFZZ = ST_CON_VEH_Parken_BN_iO;
}

boolean bPwfIsFahrenFZZ(void)
{
  uint8 ucSCV;
  ucSCV = ucGetStatusConditionVehicleFZZ();

  if( ( ucSCV == ST_CON_VEH_Fahren)
   ||  ( ucSCV == ST_CON_VEH_Fahrbereitschaft_beenden)
   ||  ( ucSCV == ST_CON_VEH_Fahrbereitschaft_herstellen))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
