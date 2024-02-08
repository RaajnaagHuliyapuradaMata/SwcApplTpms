

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "multiframe.hpp"
  #include "multiframeX.hpp"
#else
  #include "multiframe.hpp"
  #include "multiframeX.hpp"
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

void InitMF(void)
{
  uint8 ucSlot;

  for( ucSlot = 0; ucSlot < cMF_MAX_SLOT; ucSlot++ )
  {
    InitOneSlotMF( ucSlot );
  }
}
#endif

static void InitOneSlotMF( uint8 ucSlot )
{
  if(ucSlot < cMF_MAX_SLOT)
  {
    tMultiFrameMF[ucSlot].ulReId = (uint32)0;
    tMultiFrameMF[ucSlot].ucLockTimeCounter = 0;
    tMultiFrameMF[ucSlot].ucFrameCounter = 0;
    tMultiFrameMF[ucSlot].ucTGCounter = 0;
  }
}

void TimeMF(void)
{
  uint8 ucSlot;

  for( ucSlot = 0; ucSlot < cMF_MAX_SLOT; ucSlot++ )
  {
   if( tMultiFrameMF[ucSlot].ucLockTimeCounter > 0 )
   {
      tMultiFrameMF[ucSlot].ucLockTimeCounter--;
   }
  }
}

uint8 ucCheckForMultiFrameMF( uint32 ulReID, uint8 ucTGCounter, uint8 u8MaxTimeFilter)
{
  uint8 ucSlot;
  uint8 ucRet = cFT_MULTI_FRAME;

  ucSlot = ucSearchIdMF( ulReID );

  if( ucSlot < cMF_MAX_SLOT )
  {
   if( (tMultiFrameMF[ucSlot].ucLockTimeCounter == 0) || ((ucTGCounter!=0) && (tMultiFrameMF[ucSlot].ucTGCounter != ucTGCounter)) )
   {

      InitOneSlotMF( ucSlot );
      tMultiFrameMF[ucSlot].ucLockTimeCounter = u8MaxTimeFilter;
      tMultiFrameMF[ucSlot].ucFrameCounter++;
      tMultiFrameMF[ucSlot].ulReId = ulReID;
      tMultiFrameMF[ucSlot].ucTGCounter = ucTGCounter;

      ucRet = cFT_SINGLE_FRAME;
   }
   else{
      if(
          (tMultiFrameMF[ucSlot].ucFrameCounter < cMF_MAX_FRAMES) ||
          ( (ucTGCounter!=0) && (tMultiFrameMF[ucSlot].ucTGCounter == ucTGCounter) )
         )
      {
        tMultiFrameMF[ucSlot].ucFrameCounter++;

        ucRet = cFT_MULTI_FRAME;
      }
      else{

        ucRet = cFT_SINGLE_FRAME;
      }
   }
  }
  else{

   ucRet = cFT_SINGLE_FRAME;
  }

  return ucRet;
}

static uint8 ucSearchIdMF( uint32 ulReID )
{
  uint8 ucSlot;
  uint8 ucFreeSlot      = cMF_MAX_SLOT;
  uint8 ucFreeSlotNoId  = cMF_MAX_SLOT;
  uint8 ucRet           = cMF_MAX_SLOT;

  for( ucSlot = 0; ((ucSlot < cMF_MAX_SLOT) && (ucRet == cMF_MAX_SLOT)); ucSlot++ )
  {
   if( tMultiFrameMF[ucSlot].ulReId == ulReID )
   {
      ucRet = ucSlot;
   }
   else{
      if( tMultiFrameMF[ucSlot].ulReId == 0 )
      {
        if( ucFreeSlotNoId == cMF_MAX_SLOT )
        {
          ucFreeSlotNoId = ucSlot;
        }
      }

      if( tMultiFrameMF[ucSlot].ucLockTimeCounter == 0 )
      {
        if( ucFreeSlot == cMF_MAX_SLOT )
        {
          ucFreeSlot = ucSlot;
        }
      }
   }
  }

  if( ucRet == cMF_MAX_SLOT )
  {

   if( ucFreeSlotNoId < cMF_MAX_SLOT )
   {

      ucRet = ucFreeSlotNoId;
   }
   else{
      if( ucFreeSlot < cMF_MAX_SLOT )
      {

        ucRet = ucFreeSlot;
      }
   }
  }

  return ucRet;
}

