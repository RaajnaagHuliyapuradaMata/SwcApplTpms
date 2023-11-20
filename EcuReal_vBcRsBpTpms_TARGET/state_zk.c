#include "Std_Types.hpp"

#include "tss_stdx.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "state_zkx.hpp"
#include "statemanagerX.hpp"

static uint16 ushZustandskennung;

void InitZK(
   void){
   ClearBitZustandskennungZK(
      cZK_ALLE_BITS);
}

void ClearBitZustandskennungZK(
   uint16 ushBitMask){
   ushZustandskennung &= ~ushBitMask;
}

boolean bGetBitZustandskennungZK(
   uint16 ushBitMask){
   return (boolean)((ushZustandskennung & ushBitMask) != 0);
}

void SetChangedBit4WP(
   uint8 ucWP){
   switch(ucWP){
      case (uint8)0: {
         ushZustandskennung |= cPOS_CHANGED_VL;
         break;
      }
      case (uint8)1: {
         ushZustandskennung |= cPOS_CHANGED_VR;
         break;
      }
      case (uint8)2: {
         ushZustandskennung |= cPOS_CHANGED_HL;
         break;
      }
      case (uint8)3: {
         ushZustandskennung |= cPOS_CHANGED_HR;
         break;
      }
      default: {
         ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL | cPOS_CHANGED_HR);
         break;
      }
   }
}
