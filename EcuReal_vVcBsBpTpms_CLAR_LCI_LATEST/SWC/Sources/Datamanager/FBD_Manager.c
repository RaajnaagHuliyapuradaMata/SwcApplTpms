#include "FBD_Manager.h"
#include "WAllocX.h"

static uint8 ucAllocationDelay = 0xFF;

void GetDataFBD( uint8 ucPos, uint32* pulTyreId, uint8* pucSuppId){
  uint32 ulId;
  uint8 ucSlot;
  ucSlot = ucGetColOfWP(ucPos);
  if(ucSlot < cMaxLR){
    ulId = (uint32) ulGetIDOfColWAL(ucSlot);
    *pulTyreId = (uint32) (ulId & 0x0FFFFFFFul);
    *pucSuppId = (uint8)  ((ulId & 0xF0000000ul) >> 28);
  }
}

void PmStartDataAllocTimerFBD(void){
  if(0xFF == ucAllocationDelay){
    ucAllocationDelay = cFbdDataAllocDelay;
  }
}

void PmStopDataAllocTimerFBD(void){
  ucAllocationDelay = 0x00;
}

uint8 PmDataAllocTimerTickFBD(void){
  uint8 ucRetVal = 0xff;
  if((ucAllocationDelay > 0) && (0xFF != ucAllocationDelay)){
    ucAllocationDelay--;
    ucRetVal = ucAllocationDelay;
  }
  return ucRetVal;
}
