#include "EeGlobalFunctionsX.h"
#include "EeDiagBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeZomBlockX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"

#ifndef TESSY
#ifdef WIN32
#include "assert.h"
#endif
#endif

#define cMinNvmMemReserve 5
#define cOfcCommonBlock      0x0001
#define cOfcDiagBlock1       0x0002
#define cOfcDiagBlock2       0x0004
#define cOfcErfsBlock        0x0008
#define cOfcErfsEcoBlock     0x0010
#define cOfcRidQrBlock1      0x0020
#define cOfcRidQrBlock2      0x0040
#define cOfcHistoryBlock     0x0080
#define cOfcWarnstatusBlock  0x0100
#define cOfcZomBlock1        0x0200
#define cOfcZomBlock2        0x0400

void CheckMemoryReserveEE(Rte_Instance self){
#ifdef _EcuVirtual
   UNUSED(self);
#else
   uint16 ushTotalMem;
   uint16 ushMaxUsedMem;
   uint16 ushOfcBits = 0;
   uint16 i;
#ifndef TESSY
    #ifdef WIN32
      ushTotalMem = sizeof(Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tCommonNvmBlockType);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tDiagNvmBlock1Type);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tDiagNvmBlock2Type);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tHistoryNvmBlockType);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tWarnStatusNvmBlockType);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tZomNvmBlock1Type);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = sizeof(tZomNvmBlock2Type);
      assert(ushMaxUsedMem < (ushTotalMem - cMinNvmMemReserve));

      ushTotalMem = sizeof(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = ushTotalMem - 2;

      for(i=ushTotalMem; i>ushMaxUsedMem; i--){
          if(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[i] != 0xff){
          ushOfcBits |= cOfcErfsBlock;
        }
      }

      ushTotalMem = sizeof(Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = ushTotalMem - cMinNvmMemReserve;

      for(i=ushTotalMem; i>ushMaxUsedMem; i--){
          if(Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self)->Data[i] != 0xff){
          ushOfcBits |= cOfcRidQrBlock1;
        }
      }

      ushTotalMem = sizeof(Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self)->Data) - 1;
      ushMaxUsedMem = ushTotalMem - cMinNvmMemReserve;

      for(i=ushTotalMem; i>ushMaxUsedMem; i--){
          if(Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self)->Data[i] != 0xff){
          ushOfcBits |= cOfcRidQrBlock2;
        }
      }
      assert(ushOfcBits == 0);
    #endif
#endif
#endif
}

