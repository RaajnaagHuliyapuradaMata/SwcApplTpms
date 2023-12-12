#include "EeHistoryBlockX.h"

#include "WuMonitoringX.h"

static boolean bBlockNeedsUpdate = FALSE;

static void CompareValuesAndSetUpdateFlagEE(uint8 ucOld, uint8 ucNew);
static uint8 GETAllocFailCounterEE(Rte_Instance self);
static void PUTAllocFailCounterEE(Rte_Instance self, uint8 x);
static uint8 GETCntLoBatEE(Rte_Instance self, uint8 i);
static void PUTCntLoBatEE(Rte_Instance self, uint8 x, uint8 i);
static uint8 GETRfIfStateMachineEE (Rte_Instance self);
static void PUTRfIfStateMachineEE (Rte_Instance self, uint8 x);

void InitZoHistoryBlockEE(Rte_Instance self)
{
   uint8 ucLoop;

   PUTucHistoryBlockInitializeEE(self, 0xff);

   for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
    PUTucWAHistWPEE(self, cWheelPos_NA, ucLoop);
   }

   for(ucLoop = 0; ucLoop < cNvmRdciZoHistoryWaIdSet_Size; ucLoop++){
    PUTucWAHistIDEE(self, 0, ucLoop);
   }

   for(ucLoop = 0; ucLoop < cNvmRdciZoHistoryWaParam_Size; ucLoop++){
    PUTtWAparamEE(self, 0, ucLoop);
   }

   PUTLastLocStateEE(self, 0);

   PUTucStatusbarEE(self, 0);

   for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
    PutCntLoBatToNvmZOMirrorblockEE(self, 0, ucLoop);
   }
   PutAllocFailCounterToNvmZOMirrorblockEE(self, 0);
   PutRfIfStateMachineToNvmZOMirrorblockEE(self, cNoRfIf);

   PUTucHistoryBlockInitializeEE(self, cNvmInitialized);
   bBlockNeedsUpdate = TRUE;
}

uint8 GETucHistoryBlockInitializeEE(Rte_Instance self)
{
   return ((tHistoryNvmBlockType*)(void*)Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucInitialized;
}

void PUTucHistoryBlockInitializeEE(Rte_Instance self, uint8 ucNvmInitialize)
{
   ((tHistoryNvmBlockType*)(void*)Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucInitialized = ucNvmInitialize;
}

uint8 GETucWAHistIDEE(Rte_Instance self, uint8 i)
{
   return( ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ulWAHistIDSet))[i]);
}

void PUTucWAHistIDEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cNvmRdciZoHistoryWaIdSet_Size){
    CompareValuesAndSetUpdateFlagEE(((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ulWAHistIDSet))[i], x);
    ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ulWAHistIDSet))[i] = (x);
}
}

uint8 GETucWAHistWPEE(Rte_Instance self, uint8 i)
{
   return( ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucWAHistWPSet[i]);
}

void PUTucWAHistWPEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cMaxLR){
    CompareValuesAndSetUpdateFlagEE(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucWAHistWPSet[i], x);
    ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucWAHistWPSet[i] = (x);
      }
   }

uint8 GETtWAparamEE(Rte_Instance self, uint8 i)
{
   return ( ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->WAParamSet))[i]);
}

void PUTtWAparamEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cNvmRdciZoHistoryWaParam_Size){
    CompareValuesAndSetUpdateFlagEE(((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->WAParamSet))[i], x);
    ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->WAParamSet))[i] = (x);
}
}

uint16 GETLastLocStateEE (Rte_Instance self)
{
   uint16 ushRet;
   ushRet  = ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ushLastLocState;

   return (ushRet);
}

void PUTLastLocStateEE (Rte_Instance self, uint16 ushLastLocState)
{

   if(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ushLastLocState != ushLastLocState){
    SetZoHistoryBlockUpdateFlagEE();
   }
   ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ushLastLocState = ushLastLocState;
}

static uint8 GETAllocFailCounterEE(Rte_Instance self)
{
   return ( ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucAllocFailedCounter);
}

static void PUTAllocFailCounterEE(Rte_Instance self, uint8 x)
{
  CompareValuesAndSetUpdateFlagEE(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucAllocFailedCounter, x);
   ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucAllocFailedCounter = (x);
}

static uint8 GETCntLoBatEE(Rte_Instance self, uint8 i)
{
   return ( ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucLowBat))[i]);
}

static void PUTCntLoBatEE(Rte_Instance self, uint8 x, uint8 i){
   if(i < cMaxLR){
    ((uint8*)(void*)(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucLowBat))[i] = (x);
   }
}

static uint8 GETRfIfStateMachineEE (Rte_Instance self)
{
   return ( ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucRfIfStateMachine);
}

static void PUTRfIfStateMachineEE (Rte_Instance self, uint8 x)
{
  CompareValuesAndSetUpdateFlagEE(((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucRfIfStateMachine, x);
   ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->ucRfIfStateMachine = (x);
}

uint8 GETucStatusbarEE(Rte_Instance self)
{
   return ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->Statusbar;
}

void PUTucStatusbarEE(Rte_Instance self, uint8 ucValue){
   ((tHistoryNvmBlockType*) (void*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self)->Data)->Statusbar = ucValue;
}

void PutCntLoBatToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCounter, uint8 ucCol)
{
   static uint8 ucLastCounter = 0;

   PUTCntLoBatEE(self, ucCounter, ucCol);

   if  (((ucLastCounter == (cNO_OF_LO_BAT_TELEGRAMS - 1)) && (ucCounter == cNO_OF_LO_BAT_TELEGRAMS))
    || ((ucLastCounter == ((2 * cNO_OF_LO_BAT_TELEGRAMS) - 1)) && (ucCounter == 0))){
    bBlockNeedsUpdate = TRUE;
   }
   ucLastCounter = ucCounter;
}

uint8 GetCntLoBatFromNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCol)
{
   return (GETCntLoBatEE(self, ucCol));
}

void PutAllocFailCounterToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCounter)
{
   PUTAllocFailCounterEE(self, ucCounter);
}

uint8 GetAllocFailCounterFromNvmZOMirrorblockEE(Rte_Instance self)
{
   return (GETAllocFailCounterEE(self));
}

void PutRfIfStateMachineToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucRfIfStateMachine)
{
   PUTRfIfStateMachineEE(self, ucRfIfStateMachine);
}

uint8 GetRfIfStateMachineFromNvmZOMirrorblockEE(Rte_Instance self)
{
   return (GETRfIfStateMachineEE(self));
}

boolean bGetZoHistoryBlockUpdateFlagEE(void)
{
   return bBlockNeedsUpdate;
}

void SetZoHistoryBlockUpdateFlagEE(void)
{
   bBlockNeedsUpdate = TRUE;
}

void ClearZoHistoryBlockUpdateFlagEE(void)
{
   bBlockNeedsUpdate = FALSE;
}

static void CompareValuesAndSetUpdateFlagEE(uint8 ucOld, uint8 ucNew)
{
   if(ucNew != ucOld){
    bBlockNeedsUpdate = TRUE;
   }
}
