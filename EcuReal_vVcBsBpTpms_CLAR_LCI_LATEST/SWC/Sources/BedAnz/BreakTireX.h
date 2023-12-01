#ifndef BreakTireX_h
#define BreakTireX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cBtWsBreakTireInit      ( (uint8) 0x00)
#define cBtWsBreakTireLoMask    ( (uint8) 0x0F)
#define cBtWsBreakTireHiMask    ( (uint8) 0xF0)
#define cBtWsBreakTire0         ( (uint8) 0x01)
#define cBtWsBreakTire1         ( (uint8) 0x02)
#define cBtWsBreakTire2         ( (uint8) 0x04)
#define cBtWsBreakTire3         ( (uint8) 0x08)
#define cBtWsBreakTirePw        ( (uint8) 0x10)
#define cBtWsBreakTireDw        ( (uint8) 0x20)
#define cBtWsBreakTireTsb       ( (uint8) 0x40)
#define cBtWsBreakTireMulti     ( (uint8) 0x80)

extern void  InitBT(Rte_Instance self);
extern void  SetBreakTireStateBT(Rte_Instance self);
extern uint8 ucGetBreakTireStateBT(void);
extern uint8 ucGetWarnOutStateBT(Rte_Instance self);
extern boolean bGetBefuellhinweisBT(void);
extern void    PwfChangeParken2WohnenBT(void);

#ifdef __cplusplus
}
#endif

#endif
