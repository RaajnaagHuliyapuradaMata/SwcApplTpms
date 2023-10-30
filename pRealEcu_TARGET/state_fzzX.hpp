#ifndef _state_fzz_X_H
#define _state_fzz_X_H

#include "tss_stdx.hpp"

#define cKL_15_EIN            ((uint16) 0x0001)
#define cRS_VTHRES            ((uint16) 0x0002)
#define cFAHRZEUG_FAEHRT      ((uint16) 0x0004)
#define cRUECKWAERTSFAHRT     ((uint16) 0x0008)
#define cMOTOR_LAEUFT         ((uint16) 0x0400)
#define cFZZ_ALLE_BITS        ((uint16) 0xffffU)

extern void InitFZZ(void);

extern void SetBitFahrzeugzustandFZZ(uint16 ushBitMask);
extern void ClearBitFahrzeugzustandFZZ(uint16 ushBitMask);
extern boolean bGetBitFahrzeugzustandFZZ(uint16 ushBitMask);
extern uint16 ushGetFahrzeugzustandFZZ(uint16 ushBitMask);

extern void EvTerminal15OnFZZ(void);
extern void EvTerminal15OffFZZ(void);

extern void EvVehicleRollingFZZ(void);
extern void EvVehicleStandsStillFZZ(void);

extern void EvReDiagActiveFZZ(void);
extern void EvReDiagInactiveFZZ(void);

extern void EvDriveDirectionForwardFZZ(void);
extern void EvDriveDirectionBackwardFZZ(void);

extern uint32 GETulSysTimeFZZ(void);
extern sint8 GETscOutdoorTemperatureFZZ(void);
extern uint16 GETushSpeedFZZ(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void EvEngineRunningFZZ(void);
extern void EvEngineStopedFZZ(void);
extern uint8 GETucDirectionFZZ(void);
#endif

#pragma PRQA_NO_SIDE_EFFECTS bGetBitFahrzeugzustandFZZ
#pragma PRQA_NO_SIDE_EFFECTS ushGetFahrzeugzustandFZZ

#endif

