/******************************************************************************/
/* File   : EeGlobalFuntions.c                                                */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

