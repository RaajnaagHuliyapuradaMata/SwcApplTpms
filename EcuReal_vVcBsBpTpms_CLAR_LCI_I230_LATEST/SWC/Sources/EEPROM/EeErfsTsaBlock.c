#include "EeErfsTsaBlockX.h"

static boolean bBlockNeedsUpdate = FALSE;

void InitErfsTsaBlockEE(Rte_Instance self){
   uint8 i;
   for(i = 0; i < sizeof(ImpTypeArrayDcm_RdcErfsTsaDatenLesenReadDataType); i++){
      PutTsaDataEE(self, 0x00, i);
   }
}

uint8 GetTsaDataEE(Rte_Instance self, uint8 i){
   return(Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self)->Data[i]);
}

void PutTsaDataEE(Rte_Instance self, uint8 x, uint8 i){
   Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self)->Data[i] = (x);
}

void SetErfsTsaBlockWriteMeEE(void){
   bBlockNeedsUpdate = TRUE;
}

void ClearErfsTsaBlockWriteMeEE(void){
   bBlockNeedsUpdate = FALSE;
}

boolean bGetErfsTsaBlockWriteMeEE(void){
   return bBlockNeedsUpdate;
}

