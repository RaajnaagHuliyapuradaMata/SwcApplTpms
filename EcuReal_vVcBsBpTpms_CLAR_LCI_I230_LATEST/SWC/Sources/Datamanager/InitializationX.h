#ifndef InitializationX_h
#define InitializationX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

typedef struct{
  uint8 ucPressure;
  sint8 scTemperature;
}tDeclRatedValuePair;

extern void InitRatedValuesDM(Rte_Instance self);
extern void ReStorePinitTinitDM(Rte_Instance self);
extern void StartInitializationProcessDM(Rte_Instance self);
extern uint8 ucGetPWarnMinDM(void);
extern void SetNewRatedValueDM(Rte_Instance self, uint8 ucRatedPres, sint8 scRatedTemp, uint8 ucHistCol);
extern void SetAllNewRatedValueDM(Rte_Instance self);
extern uint8 ucGetPinitTinitDM( uint8 ucSlotNo);
extern sint8 scGetTinitDM( uint8 ucSlotNo);
extern uint8 ucGetPminFzgDM(void);
extern uint8 ErPlausiInitPressINIT(Rte_Instance self, boolean bER, boolean bCalcPinitTinit);
extern uint8 ZoPlausiInitPressINIT(Rte_Instance self, boolean bZO, uint8 ucTyreIndex);
extern void CalcTinitDM(Rte_Instance self, uint8 ucPReifenInit, sint8 scTReifenInit, uint8 ucTRefShift, sint8 scTAinit, uint8* pucPinit, sint8* pscTinit);

#ifdef __cplusplus
}
#endif

#endif
