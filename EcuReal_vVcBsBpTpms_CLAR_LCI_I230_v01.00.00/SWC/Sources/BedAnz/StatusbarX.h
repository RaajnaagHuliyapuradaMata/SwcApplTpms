#ifndef StatusbarX_h
#define StatusbarX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

extern void InitSBR( Rte_Instance self);
extern void ContinueSBR( Rte_Instance self);
extern void StartSBR( Rte_Instance self);
extern void StatusbarTimerTickSBR( Rte_Instance self);
extern void SetStatusBarActivityToGoSBR(void);

# ifdef __cplusplus
}
# endif

#endif
