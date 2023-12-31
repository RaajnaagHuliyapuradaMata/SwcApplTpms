#include "state_bzX.h"
#include "wallocX.h"
#include "EeHistoryBlockX.h"

static uint16 ushBetriebszustand = 0;

void InitBZ(Rte_Instance self, boolean bStartupInit){
   uint16 ushDtcInactive;
   uint8  ucHistoryState;
   if(TRUE == bStartupInit){
      SetBitBetriebszustandBZ(GETLastLocStateEE(self));
   }
   else{
      ushDtcInactive = ushBetriebszustand & cDTC_INACTIVE;
      ClearBitBetriebszustandBZ(cBZ_ALLE_BITS);
      SetBitBetriebszustandBZ(ushDtcInactive);
   }
   ucHistoryState = InitWAL(self, cRestoreZomContents);
   if(cHiStateZG == (ucHistoryState & cHiStateZG)){
      SetBitBetriebszustandBZ(cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD);
   }
   else{
      if(cHiStateER == (ucHistoryState & cHiStateER)){
         SetBitBetriebszustandBZ(cEIGENRAD | cHIST_PRELOAD);
      }
   }
}

void SetBitBetriebszustandBZ(uint16 ushBitMask){
   ushBetriebszustand |= ushBitMask;
}

void ClearBitBetriebszustandBZ(uint16 ushBitMask){
   ushBetriebszustand &= ~ushBitMask;
}

boolean bGetBitBetriebszustandBZ(uint16 ushBitMask){
   return (boolean) ((ushBetriebszustand & ushBitMask) != 0);
}

uint16 ushGetBetriebszustandBZ(uint16 ushBitMask){
   return (ushBetriebszustand & ushBitMask);
}

