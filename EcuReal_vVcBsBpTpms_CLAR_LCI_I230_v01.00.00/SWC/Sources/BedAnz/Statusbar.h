#ifndef Statusbar_h
#define Statusbar_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "StatusbarX.h"
#include "RTE_Type.h"

#define cNoDisplay       (uint8)0
#define cStartStatusbar  (uint8)1
#define cSlowTo49        (uint8)2
#define cFastTo50        (uint8)3
#define cSlowTo99        (uint8)4
#define cFastTo100       (uint8)5
#define cWait100         (uint8)6
#define cFinish          (uint8)7
#define cSbrWaitAt_0     (uint8)0
#define cSbrWaitForEr    (uint8)1
#define cSbrWait         (uint8)2
#define cSbrGo           (uint8)3
#define cTickOff         (uint8)0
#define cTickDelay_1sec  (uint8)1
#define cTickDelay_2sec  (uint8)2
#define cTickDelay_3sec  (uint8)3
#define cTickDelay_4sec  (uint8)4
#define cTickDelay_5sec  (uint8)5
#define cTickDelay_8sec  (uint8)8
#define cNoWarningActive          (uint8)0xA0
#define cWarningModuleNotReady    (uint8)0x80

static boolean bStatusbarActiveSBR(void);
static boolean bCheckAllocConditionSBR(void);
static uint8 ucCountTickDelay(void);
static void SetTickDelaySBR( Rte_Instance self);
static void JumpToNextDecadeSBR( Rte_Instance self);
static void IncValueSBR( Rte_Instance self);
static void JumpTo100SBR( Rte_Instance self);
static void JumpTo50SBR( Rte_Instance self);
static void JumpTo254SBR( Rte_Instance self);

# ifdef __cplusplus
}
# endif

#endif
