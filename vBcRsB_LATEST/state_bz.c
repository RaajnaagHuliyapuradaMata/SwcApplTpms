/******************************************************************************/
/* File   : state_bz.c                                                        */
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

#include "tss_stdx.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "statemanagerX.hpp"
#include "wallocX.hpp"
#include "State_BzX.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

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
static uint16 ushBetriebszustand;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitBZ(void){
   uint8 ucLocalWAState;
   ClearBitBetriebszustandBZ(
         cER_FINISH
      |  cTO_MUCH_RE
      |  cER_LEARNING
      |  cEIGENRAD
      |  cZUGEORDNET
      |  cWA_FINISH
      |  cHIST_PRELOAD
      |  cZO_FINISH
      |  cZO_TIMEOUT
      |  cTEILEIGENRAD
      |  cALL_ER_PRESSURE_RX
      |  cSEND_RE_DATA_ON_CAN
      |  cWA_STARTED
   );
   ucLocalWAState = WAInit();
   if((ucLocalWAState & cHiStateZG ) == cHiStateZG){
      SetBitBetriebszustandBZ( cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD);
   }
   else{
      if((ucLocalWAState & cHiStateER ) == cHiStateER){
         SetBitBetriebszustandBZ( cEIGENRAD | cHIST_PRELOAD);
      }
   }
   SetBitBetriebszustandBZ(cER_LEARNING);
}

void SetBitBetriebszustandBZ(uint16 ushBitMask){
   ushBetriebszustand |= ushBitMask;
}

void ClearBitBetriebszustandBZ(uint16 ushBitMask){
   ushBetriebszustand &= ~ushBitMask;
}

boolean bGetBitBetriebszustandBZ(uint16 ushBitMask){
   return (boolean) ((ushBetriebszustand & ushBitMask) != 0 );
}

uint16 ushGetBetriebszustandBZ(uint16 ushBitMask){
   return (ushBetriebszustand & ushBitMask);
}

void EvVehicleSpeedChangedBZ(uint16 ushNewVehicleSpeed){
   if(ushNewVehicleSpeed >= (uint16)WALLOC_ucGetMinSpeedAutoLearnStart()){
    SetBitBetriebszustandBZ(cWA_STARTED);
  }
  else{
  }
}

uint16 DCM_InvIf_TPMSStateGetStatus(void){
  return ushGetBetriebszustandBZ(0xFFFF);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

