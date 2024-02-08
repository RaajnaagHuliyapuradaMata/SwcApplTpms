

#ifndef REDiagX_H
#define REDiagX_H

#include "CfgSwcApplTpms.hpp"
#include "tss_stdx.hpp"

extern const uint8 ucWUDefectERRc[cAnzRad+1];
extern const uint8 ucWUFailERRc[cAnzRad+1];
#ifdef js_ReHighTemperatureDiag_230312
extern const uint8 ucWUTemperatureERRc[cAnzRad+1];
#endif
extern const uint8 ucWULowLifeTimeERRc[cAnzRad+1];

extern void ResetWUFailedErrRD(uint8 ucIx);
extern boolean SetWUFailedErrRD(uint16 CounterValue, uint8 ucIx);
extern void CntWUDefectRD(uint8 ZomPos);
extern void ResetWUDefectRD(uint8 ZomPos);

extern uint8 GetWUDefectRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWUDefectRD

#ifdef js_ReHighTemperatureDiag_230312

extern void CntWUHighTempRD(uint8 ZomPos);
extern void ResetWUHighTempRD(uint8 ZomPos);

extern uint8 GetWUHighTempRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWUHighTempRD

#endif

extern void CntWULowLifeTimeRD(uint8 ZomPos);
extern void ResetWULowLifeTimeRD(uint8 ZomPos);
extern void ResetWULowLifeTimeCounter(uint8 ZomPos);

extern uint8 GetWULowLifeTimeRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWULowLifeTimeRD

#endif
