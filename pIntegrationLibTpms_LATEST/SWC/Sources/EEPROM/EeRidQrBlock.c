

#include "EeRidQrBlock.h"

#include "RID_X.h"

#define cTyreRuntimeInfoSize            ((uint8)24)
#define cMountedFlagSize                ((uint8)1)

#define cTyreDim1_StartIx	               (0x00)
#define cTyreDOT1_StartIx                (cTyreDim1_StartIx         + cTyreDimSize)
#define cTyreOEM1_StartIx                (cTyreDOT1_StartIx         + cTyreDOTSize)
#define cTyreRuntimeInfo1_StartIx        (cTyreOEM1_StartIx         + cTyreOEMSize)
#define cMountedFlag_StartIx             (cTyreRuntimeInfo1_StartIx + cTyreRuntimeInfoSize)

#define cTotalSize                       (cTyreDimSize + cTyreDOTSize + cTyreOEMSize + cTyreRuntimeInfoSize + cMountedFlagSize)

static boolean bBlock1NeedsUpdate = FALSE;
static boolean bBlock2NeedsUpdate = FALSE;

static void CheckValueChangesAndSetUpdateFlag(uint8 , uint8 , uint8);

static void CheckValueChangesAndSetUpdateFlag(uint8 ucOldValue, uint8 ucNewValue, uint8 ucBlockNo)
{
  if(ucNewValue != ucOldValue)
  {
    if( ucBlockNo == 1)
    {
      bBlock1NeedsUpdate = TRUE;
    }else{
      bBlock2NeedsUpdate = TRUE;
    }
  }
}

void InitRidQrBlock1u2EE( Rte_Instance self)
{
  uint8   EntryIx;
  uint8   i;
  uint16  j;

  for ( j = 0; j < sizeof(Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self)->Data); j++)
  {
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self)->Data[j] = 0xff;
  }

  for ( j = 0; j < sizeof(Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self)->Data); j++)
  {
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self)->Data[j] = 0xff;
  }

  for ( EntryIx = 0; EntryIx < cMaxQRCodeSets; EntryIx++)
  {
    for ( i = 0; i < cTyreDimSize; i++)
    {
      PUTTyreDimQrCodeDataEE( self, EntryIx, i, 0x00);
    }

    for ( i = 0; i < cTyreDOTSize; i++)
    {
      PUTTyreDOTQrCodeDataEE( self, EntryIx, i, 0x00);
    }

    for ( i = 0; i < cTyreOEMSize; i++)
    {
      PUTTyreOEMQrCodeDataEE( self, EntryIx, i, 0x00);
    }

    PUTTyreMountedFlagEE( self, EntryIx, 0x00);

    for ( i = 0; i < cTyreRuntimeInfoSize; i++)
    {
      PUTTyreRuntimeDataEE( self, EntryIx, i, 0x00);
    }
  }
}

uint8 GETTyreDimQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x)
{
  uint8  ucRet;
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreDim1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreDim1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }

  return ucRet;
}

void PUTTyreDimQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x, uint8 y)
{
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreDim1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 1);
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreDim1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 2);
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }
}

uint8 GETTyreDOTQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x)
{
  uint8  ucRet;
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreDOT1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreDOT1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }

  return ucRet;
}

void PUTTyreDOTQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x, uint8 y)
{
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreDOT1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 1);
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreDOT1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 2);
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }
}

uint8 GETTyreOEMQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x)
{
  uint8  ucRet;
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreOEM1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreOEM1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }

  return ucRet;
}

void PUTTyreOEMQrCodeDataEE( Rte_Instance self, uint8 i, uint8 x, uint8 y)
{
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreOEM1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 1);
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreOEM1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 2);
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }
}

uint8 GETTyreRuntimeDataEE( Rte_Instance self, uint8 i, uint8 x)
{
  uint8  ucRet;
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreRuntimeInfo1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreRuntimeInfo1_StartIx + (x);
    ucRet = Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }

  return ucRet;
}

void PUTTyreRuntimeDataEE( Rte_Instance self, uint8 i, uint8 x, uint8 y)
{
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cTyreRuntimeInfo1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 1);
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cTyreRuntimeInfo1_StartIx + (x);
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 2);
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }
}

uint8 GETTyreMountedFlagEE( Rte_Instance self, uint8 i)
{
  uint8  ucRet;
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cMountedFlag_StartIx;
    ucRet = Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cMountedFlag_StartIx;
    ucRet = Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex];
  }

  return ucRet;
}

void PUTTyreMountedFlagEE( Rte_Instance self, uint8 i, uint8 y)
{
  uint16 ushIndex;

  if( i < 6)
  {
    ushIndex = (i * cTotalSize) + cMountedFlag_StartIx;
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 1);
    Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }else{
    ushIndex = ((i - 6) * cTotalSize) + cMountedFlag_StartIx;
    CheckValueChangesAndSetUpdateFlag( Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex], y, 2);
    Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock( self)->Data[ushIndex] = (y);
  }
}

void SetRidQrBlock1UpdateFlagEE(void)
{
  bBlock1NeedsUpdate = TRUE;
}

void SetRidQrBlock2UpdateFlagEE(void)
{
  bBlock2NeedsUpdate = TRUE;
}

void ClearRidQrBlock1UpdateFlagEE(void)
{
  bBlock1NeedsUpdate = FALSE;
}

void ClearRidQrBlock2UpdateFlagEE(void)
{
  bBlock2NeedsUpdate = FALSE;
}

boolean bGetRidQrBlock1UpdateFlagEE(void)
{
  return bBlock1NeedsUpdate;
}

boolean bGetRidQrBlock2UpdateFlagEE(void)
{
  return bBlock2NeedsUpdate;
}

