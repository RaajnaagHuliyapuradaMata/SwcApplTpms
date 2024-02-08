#include "Std_Types.hpp"

#include "Walloc_IF.hpp"
#include "WAllocX.hpp"
#include "cd_decoder_x.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "statemanagerX.hpp"
#include "abs_linX.hpp"
#include "watcfX.hpp"

void CancelWATO(void){
  StopWallocTOAlarm();
}

void StartWATO(
   unsigned char ucTimeInSec){
   if(ucTimeInSec > 0){
    StartWallocTOAlarm(ucTimeInSec);
  }
}

#ifdef FPA
unsigned short ushGetABSingleTick(
   unsigned char ucIx){
  unsigned char LocalCnt;
  unsigned char  ucRet;
  unsigned short ushCnt[4];
  unsigned short ushCurrentAbsTick = 0;
   for(LocalCnt = 0; LocalCnt < 4; LocalCnt++){
   ushCnt[LocalCnt] = 0;
  }
  ucRet = GetLinABS( ushCnt );
   if(ucRet == cABS_OK){
   ushCurrentAbsTick = ushCnt[ucIx];
  }
  else{
   ushCurrentAbsTick = 0;
  }
  return ( ushCurrentAbsTick );
}
#endif
