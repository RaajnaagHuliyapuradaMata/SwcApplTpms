#ifndef _multiframe_H
#define _multiframe_H

#include "tss_stdx.hpp"

#define cMF_MAX_FRAMES      ((uint8)  3)
#define cMF_MAX_SLOT        ((uint8) 10)

typedef struct typedef_struct_tMultiFrameDeclMF{
  uint32 ulReId;
  uint8  ucLockTimeCounter;
  uint8  ucFrameCounter;
  uint8  ucTGCounter;
}tMultiFrameDeclMF;

tMultiFrameDeclMF tMultiFrameMF[cMF_MAX_SLOT];

static void InitOneSlotMF(uint8 ucSlot);
static uint8 ucSearchIdMF(uint32 ulReID);

#endif
