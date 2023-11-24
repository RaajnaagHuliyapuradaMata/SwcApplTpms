

#include "EeZomBlock.h"

static boolean bBlock1NeedsUpdate = FALSE;
static boolean bBlock2NeedsUpdate = FALSE;

void InitZomBlock1EE( Rte_Instance self)
{
  uint16 i;

  for ( i = 0; i < sizeof(Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock(self)->Data); i++)
  {
    Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock(self)->Data[i] = 0xff;
  }

  PUTucZomBlock1InitializeEE( self, 0xff);

  for( i = 0; i < cNvmRdciZom1_Size; i++)
  {
    PUTtZomEE( self, 0, i);
  }

  PUTWaIdChangeBitsToNvmEE( self, 0);
  PUTWatoEE( self, ucDefWATOTime);
  PUTAllocStateToNvmEE( self, 0);

  PUTucPermutationStateToNvmEE(self, 0);

  PUTucZomBlock1InitializeEE( self, cNvmInitialized);
}

void InitZomBlock2EE( Rte_Instance self)
{
  uint16 i;

  for ( i = 0; i < sizeof(Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock(self)->Data); i++)
  {
    Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock(self)->Data[i] = 0xff;
  }

  PUTucZomBlock2InitializeEE( self, 0xff);

  for( i = cNvmRdciZom1_Size; i < sizeof(tZOM); i++)
  {
    PUTtZomEE( self, 0, i);
  }

  PUTucZomBlock2InitializeEE( self, cNvmInitialized);
}

uint8 GETucZomBlock1InitializeEE( Rte_Instance self)
{
  return ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucInitialized;
}

void PUTucZomBlock1InitializeEE( Rte_Instance self, uint8 ucNvmInitialize)
{
  ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucInitialized = ucNvmInitialize;
}

uint8 GETucZomBlock2InitializeEE( Rte_Instance self)
{
  return ((tZomNvmBlock2Type*) (void*) Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock( self)->Data)->ucInitialized;
}

void PUTucZomBlock2InitializeEE( Rte_Instance self, uint8 ucNvmInitialize)
{
  ((tZomNvmBlock2Type*) (void*) Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock( self)->Data)->ucInitialized = ucNvmInitialize;
}

void PUTWatoEE( Rte_Instance self, uint8 x)
{
  ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWato = (x);
}

uint8 GETWatoEE( Rte_Instance self)
{
  return( ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWato);
}

void PUTZomToNvmEE( Rte_Instance self, const uint8 pRamAdr[], uint16 ucLen)
{
  uint16 i;

  for (i=0; i<ucLen; i++)
	{
    PUTtZomEE( self, pRamAdr[i], i);
	}
}

void GETZomFromNvmEE( Rte_Instance self, uint8 pRamAdr[], uint16 ucLen)
{
  uint16 i;

  for (i=0; i<ucLen; i++)
  {
    pRamAdr[i] = GETtZomEE( self, i);
  }
}

void PUTAllocStateToNvmEE( Rte_Instance self, uint8 x)
{
  ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWaState = (x);
}

uint8 GETAllocStateFromNvmEE( Rte_Instance self)
{
  return ( ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWaState);
}

void PUTWaIdChangeBitsToNvmEE( Rte_Instance self, uint8 x)
{
  ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWaIdChangeBits = (x);
}

uint8 GETIdChangeBitsFromNvmEE( Rte_Instance self)
{
  return ( ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucWaIdChangeBits);
}

void PUTucPermutationStateToNvmEE( Rte_Instance self, uint8 x)
{
  ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucPermutationState = (x);
}

uint8 GETucPermutationStateFromNvmEE( Rte_Instance self)
{
  return ( ((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->ucPermutationState);
}

static uint8 GETtZomEE( Rte_Instance self, uint16 i)
{
  uint8 ucRet;

  if( i < cNvmRdciZom1_Size)
  {
    ucRet =  ((uint8*)(void*)(((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->tZomSlot))[i];
  }else{
    ucRet =  ((uint8*)(void*)(((tZomNvmBlock2Type*) (void*) Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock( self)->Data)->tZomSlot))[i-cNvmRdciZom1_Size];
  }

  return ucRet;
}

static void PUTtZomEE( Rte_Instance self, uint8 x, uint16 i)
{
  if( i < cNvmRdciZom1_Size)
  {
    ((uint8*)(void*)(((tZomNvmBlock1Type*) (void*) Rte_Pim_NvmRdciZomBlock1_NVBlock_MirrorBlock( self)->Data)->tZomSlot))[i] = (x);
  }else{
    if(i < (2*cNvmRdciZom1_Size))
    {
      ((uint8*)(void*)(((tZomNvmBlock2Type*) (void*) Rte_Pim_NvmRdciZomBlock2_NVBlock_MirrorBlock( self)->Data)->tZomSlot))[i-cNvmRdciZom1_Size] = (x);
    }
  }
}

void SetZomBlock1UpdateFlagEE(void)
{
  bBlock1NeedsUpdate = TRUE;
}

void SetZomBlock2UpdateFlagEE(void)
{
  bBlock2NeedsUpdate = TRUE;
}

void ClearZomBlock1UpdateFlagEE(void)
{
  bBlock1NeedsUpdate = FALSE;
}

void ClearZomBlock2UpdateFlagEE(void)
{
  bBlock2NeedsUpdate = FALSE;
}

boolean bGetZomBlock1UpdateFlagEE(void)
{
  return bBlock1NeedsUpdate;
}

boolean bGetZomBlock2UpdateFlagEE(void)
{
  return bBlock2NeedsUpdate;
}

