#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "WallocX.h"

#define cNvmRdciZom1_Size                     ( (uint16) (8 * sizeof(struct ZOMSlot)))

typedef struct ZomNvmBlock_1{
  uint8             ucInitialized;
  struct ZOMSlot    tZomSlot[8];
  uint8             ucWato;
  uint8             ucWaState;
  uint8             ucWaIdChangeBits;
  uint8             ucPermutationState;
}tZomNvmBlock1Type;

typedef struct ZomNvmBlock_2{
  uint8             ucInitialized;
  struct ZOMSlot    tZomSlot[8];
}tZomNvmBlock2Type;

extern void InitZomBlock1EE(Rte_Instance self);
extern void InitZomBlock2EE(Rte_Instance self);
extern uint8 GETucZomBlock1InitializeEE(Rte_Instance self);
extern void  PUTucZomBlock1InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern uint8 GETucZomBlock2InitializeEE(Rte_Instance self);
extern void  PUTucZomBlock2InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern void PUTZomToNvmEE(Rte_Instance self, const uint8 pRamAdr[], uint16 ucLen);
extern void GETZomFromNvmEE(Rte_Instance self, uint8 pRamAdr[], uint16 ucLen);
extern void  PUTWatoEE(Rte_Instance self, uint8 x);
extern uint8 GETWatoEE(Rte_Instance self);
extern void  PUTAllocStateToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETAllocStateFromNvmEE(Rte_Instance self);
extern void  PUTWaIdChangeBitsToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETIdChangeBitsFromNvmEE(Rte_Instance self);
extern void  PUTucPermutationStateToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETucPermutationStateFromNvmEE(Rte_Instance self);
extern void    SetZomBlock1UpdateFlagEE(void);
extern void    SetZomBlock2UpdateFlagEE(void);
extern void    ClearZomBlock1UpdateFlagEE(void);
extern void    ClearZomBlock2UpdateFlagEE(void);
extern boolean bGetZomBlock1UpdateFlagEE(void);
extern boolean bGetZomBlock2UpdateFlagEE(void);

#ifdef __cplusplus
}
#endif
