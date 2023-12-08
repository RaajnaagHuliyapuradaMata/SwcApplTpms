#include "Walloc_IF.h"
#include "abs_linX.h"
#include "walloc_managerX.h"
#include "state_fzzX.h"
#include "EeHistoryBlockX.h"
#include "EeZomBlockX.h"

void GetWADataEE(Rte_Instance self, uint8 ucId, uint8 pRamAdr[], uint16 ucLen){
   uint8 i;
   switch(ucId){
      case cWAParameter:
      for(i=0; i<ucLen; i++){
        pRamAdr[i] = GETtWAparamEE(self, i);
      }
      break;

      case cHistoryIDSet:
      for(i=0; i<ucLen; i++){
        pRamAdr[i] = GETucWAHistIDEE(self, i);
      }
      break;

      case cHistoryWPSet:
      for(i=0; i<ucLen; i++){
        pRamAdr[i] = GETucWAHistWPEE(self, i);
      }
      break;

      case cZOMContent:
      GETZomFromNvmEE(self, pRamAdr, ucLen);
      break;

      case cAllocState:
      pRamAdr[0] = GETAllocStateFromNvmEE(self);
      break;

      case cIDChangeBits:
      pRamAdr[0] = GETIdChangeBitsFromNvmEE(self);
      break;

      case cPermutationState:
      pRamAdr[0] = GETucPermutationStateFromNvmEE(self);
      break;

      default:
      break;
   }
}

void PutWADataEE(Rte_Instance self, uint8 ucId, const uint8 pRamAdr[], uint16 ucLen){
   uint8 i;
   switch(ucId){
      case cWAParameter:
	    for(i=0;i < ucLen;i++){
        PUTtWAparamEE(self, pRamAdr[i], i);
	    }
	  break;

      case cHistoryIDSet:
	    for(i=0;i < ucLen;i++){
        PUTucWAHistIDEE(self, pRamAdr[i], i);
	    }
	  break;

      case cHistoryWPSet:
	    for(i=0;i < ucLen;i++){
        PUTucWAHistWPEE(self, pRamAdr[i], i);
  	  }
	  break;

      case cZOMContent:
      PUTZomToNvmEE(self, pRamAdr, ucLen);
      break;

      case cAllocState:
      PUTAllocStateToNvmEE(self, pRamAdr[0]);
      break;

      case cIDChangeBits:
      PUTWaIdChangeBitsToNvmEE(self, pRamAdr[0]);
      break;

      case cPermutationState:
      PUTucPermutationStateToNvmEE(self, pRamAdr[0]);
      break;

      default:
	  break;
   }
}

void CancelWATO(void){
  WatoStopWAM();
}

uint8 ucGetABSTick(uint16* p2aushABS){
   uint8 ucRet;
   ucRet = ucGetLinABS( p2aushABS);
   if(ucRet == cABS_OK){
      ucRet = (uint8) 1;
   }
   else{
      ucRet = (uint8) 0;
   }
   return ucRet;
}

uint16 ushGetABSingleTick(uint8 ucIx){
   uint8  ucRet;
   uint16 ushCnt[4];
   uint16 ushCurrentAbsTick;
   ucRet = ucGetLinABS(ushCnt);
   if(ucRet == cABS_OK){
      ushCurrentAbsTick = ushCnt[ucIx];
   }
   else{
      ushCurrentAbsTick = cABSTickError;
   }
   return (ushCurrentAbsTick);
}

uint8 ucGetSpeed(void){
   uint16 ushV = GETushSpeedFZZ();
   if(ushV > 255){
      return ((uint8) 255);
   }
   else{
      return ((uint8) ushV);
   }
}

uint16 ushGetAbsTickDifference(uint16 ushLeftVal, uint16 ushRightVal){
   uint16 retVal;
   retVal = (ushRightVal > ushLeftVal) ? (ushRightVal - ushLeftVal): ((cAbsOverflowValue - ushLeftVal) + ushRightVal + cAbsOverflowCorrection);
   return (retVal);
}

