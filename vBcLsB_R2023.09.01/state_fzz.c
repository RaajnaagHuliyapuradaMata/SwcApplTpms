

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "SwcApplTpms_CAN_If.hpp"
  #include "state_fzz.hpp"
  #include "statemanagerX.hpp"
  #include "State_FzzX.hpp"
  #include "WatcfX.hpp"
  #include "WAllocX.hpp"
  #include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#else
  #include "state_fzz.hpp"
  #include "statemanagerX.hpp"
  #include "receiveX.hpp"
  #include "ecustateX.hpp"
  #include "sgdiagX.hpp"
  #include "procdatX.hpp"
  #include "vehstatex.hpp"
#endif

#define BACKWARD_COUNTER_MAX_VALUES  ((uint8)16)

static uint16 ushFahrzeugzustand;

static uint8 ucBackwardEventCounter;

void InitFZZ(void)
{
  boolean bEcuState;
  bEcuState = 0;
  ClearBitFahrzeugzustandFZZ( cFZZ_ALLE_BITS );

  ucBackwardEventCounter = 0;

  (void) VehStateGetKL15( &bEcuState );
  if( bEcuState == TRUE )
  {
    SetBitFahrzeugzustandFZZ( cKL_15_EIN );
  }
  else{
   ClearBitFahrzeugzustandFZZ( cKL_15_EIN );
  }

  if( VehStateGetVehicleRollingState( ) == TRUE)
  {
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }
  else{
   ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }

  if(VehStateGetReDiagActiveState( ) == TRUE)
  {
    SetBitFahrzeugzustandFZZ( cRS_VTHRES );
  }
  else{
   ClearBitFahrzeugzustandFZZ( cRS_VTHRES );
  }
}

void SetBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   ushFahrzeugzustand |= ushBitMask;
}

void ClearBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   ushFahrzeugzustand &= ~ushBitMask;
}

boolean bGetBitFahrzeugzustandFZZ( uint16 ushBitMask )
{
   return (boolean) ((ushFahrzeugzustand & ushBitMask) != 0 );
}

uint16 ushGetFahrzeugzustandFZZ( uint16 ushBitMask )
{
   return (ushFahrzeugzustand & ushBitMask);
}

void EvTerminal15OnFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == FALSE )
  {
    SetBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitWATCF();
    InitAfterKl15OnSM();
#ifdef IBTCM_SW_ANPASSUNGEN

#else
    InitAfterKl15OnDI();
#endif
  }
}

void EvTerminal15OffFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE )
  {
   ClearBitFahrzeugzustandFZZ( cKL_15_EIN );

    InitAfterKl15OffSM();
  }
}

#ifdef IBTCM_SW_ANPASSUNGEN

#else

void EvVehicleRollingFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE )
  {
    SetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }
}
#endif

#ifdef IBTCM_SW_ANPASSUNGEN

#else

void EvVehicleStandsStillFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE )
  {
   ClearBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT );
  }
}
#endif

void EvReDiagActiveFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == FALSE )
  {
    SetBitFahrzeugzustandFZZ( cRS_VTHRES );
   ControlWATO( cWATO_RESTART_ALARM, 0 );
    SetRelAlarmAlMissedRXCntOS( 1, 1 );
  }
}

void EvReDiagInactiveFZZ(void)
{
  if( bGetBitFahrzeugzustandFZZ( cRS_VTHRES ) == TRUE )
  {
   ClearBitFahrzeugzustandFZZ( cRS_VTHRES );
   ControlWATO( cWATO_BREAK_ALARM, 0 );
   CancelAlarmAlMissedRxCntOS();
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void EvEngineRunningFZZ(void)
{
  SetBitFahrzeugzustandFZZ( cMOTOR_LAEUFT );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef BUILD_WITH_UNUSED_FUNCTION

void EvEngineStopedFZZ(void)
{
  ClearBitFahrzeugzustandFZZ( cMOTOR_LAEUFT );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void EvDriveDirectionForwardFZZ(void)
{
  ClearBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );
#ifdef FPA
  ReNewABSRef();
#endif
}

void EvDriveDirectionBackwardFZZ(void)
{
  SetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT );

  ucBackwardEventCounter++;
  ucBackwardEventCounter = ucBackwardEventCounter % BACKWARD_COUNTER_MAX_VALUES;

#ifdef FPA
  ReNewABSRef();
#endif
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GETucDirectionFZZ(void)
{
  uint8 ucDirection;
  ucDirection = 0;

  (void) ReceiveGetDirection( &ucDirection);

  return ucDirection;
}
#endif //BUILD_WITH_UNUSED_FUNCTION

sint8 GETscOutdoorTemperatureFZZ(void)
{
  sint16 sshOutdoorTemp = 0;
  sint8 scOutdoorTemperature = 0;

  (void) ReceiveGetOutdoorTemp( &sshOutdoorTemp );

  scOutdoorTemperature = (sint8)(sshOutdoorTemp);

  return scOutdoorTemperature;
}

uint16 GETushSpeedFZZ(void)
{
  uint16 ushVehicleSpeed;
  ushVehicleSpeed = 0;

  (void) ReceiveGetVehicleSpeed( &ushVehicleSpeed );

  return ushVehicleSpeed;
}

uint8 DCM_InvIf_VehicleStatusGetValue(void){
  return (uint8) ( ushGetFahrzeugzustandFZZ( 0x000F ) & 0x0F);
}

uint8 DCM_InvIf_TempAmbientGetValue(void){
  //return GETscOutdoorTemperatureFZZ();
  return g_sEnv_Data.ucAmbTemperature;
}

uint8 DCM_InvIf_GearReverseGetCntValue(void){
  return ucBackwardEventCounter;
}
#ifdef NVM_DEBUG

void DCM_InvIf_NvmBlockConsistence(uint8 *u8_NvMBuffer)
{
  u8_NvMBuffer[0] =  (uint8)(0xFFU & (g_sEnv_Data.uiNvmBlockConsistence >> 8U));
  u8_NvMBuffer[1] =  (uint8)(0xFFU &  g_sEnv_Data.uiNvmBlockConsistence       );
}

#endif
