#include "EeErfsEcoBlockX.h"

#include "erfs_X.h"

void PutErfsEcoNeuerReifenEE(Rte_Instance self, const uint8* pucData)
{
   uint8 i;

   for(i = 0; i < TYRE_DATA_BYTES; i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[i];
   }
}

void PutErfsEcoReifenTabelleEE(Rte_Instance self, const uint8* pucData, const uint8 ucElement)
{
   uint8 i, Index;

   Index = (ucElement*TYRE_DATA_BYTES);

   if(ucElement < TYRE_LIST_MAX_ELEMENTS){
      for(i=0; i<TYRE_DATA_BYTES ;i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[Index+i];
      }
   }
   else{

      for(i = 0; i < 2; i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[Index+i];
      }
   }
}

