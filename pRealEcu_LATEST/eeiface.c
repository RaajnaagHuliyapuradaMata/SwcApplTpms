#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "eeiface.hpp"
#include "global.hpp"

void GetDataEE(
   unsigned char ucId,
   unsigned char* pRamAdr){
   if((ucId > 0) && (ucId < 7)){
      ReadBlock2Member(
         1,
         ucId,
         pRamAdr);
   }
}

void PutDataEE(
   unsigned char ucId,
   const unsigned char* pRamAdr){
   if((ucId > 0) && (ucId < 7)){
      WriteMember2Blocks(
         1,
         ucId,
         (unsigned char*)pRamAdr);
   }
}
