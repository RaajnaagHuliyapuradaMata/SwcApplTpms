/******************************************************************************/
/* File   : state_fzz.c                                                       */
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

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "state_fzz.hpp"
#include "statemanagerX.hpp"
#include "State_FzzX.hpp"
#include "WatcfX.hpp"
#include "WAllocX.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define BACKWARD_COUNTER_MAX_VALUES                                  ((uint8)16)

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
static uint16 ushFahrzeugzustand;
static uint8 ucBackwardEventCounter;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitFZZ(void){
   boolean bEcuState;
   bEcuState = 0;
   ClearBitFahrzeugzustandFZZ(cFZZ_ALLE_BITS);
   ucBackwardEventCounter = 0;
   (void)VehStateGetKL15(&bEcuState);

   if(TRUE == bEcuState                        ){SetBitFahrzeugzustandFZZ(cKL_15_EIN       );} else{ClearBitFahrzeugzustandFZZ(cKL_15_EIN       );}
   if(TRUE == VehStateGetVehicleRollingState() ){SetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT );} else{ClearBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT );}
   if(TRUE == VehStateGetReDiagActiveState()   ){SetBitFahrzeugzustandFZZ(cRS_VTHRES       );} else{ClearBitFahrzeugzustandFZZ(cRS_VTHRES       );}
}

void SetBitFahrzeugzustandFZZ(uint16 ushBitMask){
   ushFahrzeugzustand |= ushBitMask;
}

void ClearBitFahrzeugzustandFZZ(uint16 ushBitMask){
   ushFahrzeugzustand &= ~ushBitMask;
}

boolean bGetBitFahrzeugzustandFZZ(uint16 ushBitMask){
   return (boolean)((ushFahrzeugzustand & ushBitMask) != 0);
}

uint16 ushGetFahrzeugzustandFZZ(uint16 ushBitMask){
   return (ushFahrzeugzustand & ushBitMask);
}

void EvTerminal15OnFZZ(void){
   if(FALSE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      SetBitFahrzeugzustandFZZ(cKL_15_EIN);
      InitWATCF();
      InitAfterKl15OnSM();
   }
}

void EvTerminal15OffFZZ(void){
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      ClearBitFahrzeugzustandFZZ(cKL_15_EIN);
      InitAfterKl15OffSM();
   }
}

void EvReDiagActiveFZZ(void){
   if(FALSE == bGetBitFahrzeugzustandFZZ(cRS_VTHRES)){
      SetBitFahrzeugzustandFZZ(cRS_VTHRES);
      ControlWATO(cWATO_RESTART_ALARM, 0);
      SetRelAlarmAlMissedRXCntOS(1, 1);
   }
}

void EvReDiagInactiveFZZ(void){
   if(TRUE == bGetBitFahrzeugzustandFZZ(cRS_VTHRES)){
      ClearBitFahrzeugzustandFZZ(cRS_VTHRES);
      ControlWATO(cWATO_BREAK_ALARM, 0);
      CancelAlarmAlMissedRxCntOS();
   }
}

void EvDriveDirectionForwardFZZ(void){
   ClearBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
#ifdef FPA
   ReNewABSRef();
#endif
}

void EvDriveDirectionBackwardFZZ(void){
   SetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
   ucBackwardEventCounter++;
   ucBackwardEventCounter = ucBackwardEventCounter % BACKWARD_COUNTER_MAX_VALUES;
#ifdef FPA
   ReNewABSRef();
#endif
}

sint8 GETscOutdoorTemperatureFZZ(void){
   sint16 sshOutdoorTemp       = 0;
   sint8  scOutdoorTemperature = 0;
   (void)ReceiveGetOutdoorTemp(&sshOutdoorTemp);
   scOutdoorTemperature = (sint8)(sshOutdoorTemp);
   return scOutdoorTemperature;
}

uint16 GETushSpeedFZZ(void){
   uint16 ushVehicleSpeed;
   ushVehicleSpeed = 0;
   (void)ReceiveGetVehicleSpeed(&ushVehicleSpeed);
   return ushVehicleSpeed;
}

uint8 DCM_InvIf_VehicleStatusGetValue(void){
   return (uint8)(ushGetFahrzeugzustandFZZ(0x000F) & 0x0F);
}

uint8 DCM_InvIf_TempAmbientGetValue(void){
   return g_sEnv_Data.ucAmbTemperature;
}

uint8 DCM_InvIf_GearReverseGetCntValue(void){
   return ucBackwardEventCounter;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

