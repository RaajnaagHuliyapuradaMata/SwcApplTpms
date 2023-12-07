

#ifndef USWARN_IF_X_H
#define USWARN_IF_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

#define cSwCodeRDW   (uint8) 0
#define cSwCodeUSA   (uint8) 1

extern uint8 ucCfgReInitSingleUSWIF(Rte_Instance self, uint8 ucPressure, sint8 scTemperature, uint8 ucZomPos, uint8 ucWheelPos);
extern uint8 ucCfgTReifenSingleUSWIF(Rte_Instance self, sint8 scTemperature, uint8 ucZomPos);
extern uint8 ucGetPTSollUSWIF(Rte_Instance self, uint8* pucPSollKalt, sint8* pscTSollKalt, uint8* pucPSollWarm, sint8* pscTSollWarm, uint16* pushMSoll, uint8* pucEnvP, uint8 ucZomPos);
extern uint8 ucGetWpPTSollUSWIF(uint8* pucPSoll, sint8* pscTSoll, uint8 ucWheelPos);
extern uint8 ucSetPTSollAfterWpChangedUSWIF(Rte_Instance self, uint8 ucHistSlot, uint8 ucNewWheelPos);
extern uint8 ucCfgPMinUSWIF(Rte_Instance self, uint8 ucPMin);
extern uint8 ucCfgPSollMinUSWIF(Rte_Instance self);

extern uint8 ResetWarnVectorUSWIF(Rte_Instance self, uint8 ucZomPos);
extern uint8 PorInitUSWIF(Rte_Instance self);
extern uint8 NewPositionsUSWIF(Rte_Instance self);
extern uint8 ClearPosUSWIF(Rte_Instance self);
extern void  ResetWarningsUSWIF(Rte_Instance self);
extern uint8 TimerStopUSWIF(Rte_Instance self);

extern uint8 ucGetWarnVectorIdExtIFH(Rte_Instance self, uint8* pucWarnVectors);
extern uint8 ucGetWarnBitIdIntIFH(Rte_Instance self, uint8* pucWarnVectors);
extern uint8 ucGetWarnBitTonnageIdIntIFH(Rte_Instance self, uint8* pucWarnVectors);
extern uint8 ucGetWarnBitAirMassIdIntIFH(Rte_Instance self, uint8* pucWarnVectors);

extern uint8 ucGetWThresUSWIF(Rte_Instance self, uint8 ucWarnType, uint8* pucSetThres, uint8* pucResetThres);

extern uint8 ucSetPminFzgAsSetPressureUSWIF(Rte_Instance self);
extern void  InitUSWIF(Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif

