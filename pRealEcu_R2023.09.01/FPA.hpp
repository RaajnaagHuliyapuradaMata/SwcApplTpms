

#ifndef FPA_H
#define FPA_H

#include "Walloc_IF.hpp"

unsigned char ucMINUS_ABSigOFL_MOD_ZAHN(unsigned char ucABSTicksRevol);
unsigned char ucABSigOFL_MOD_ZAHN(unsigned char ucABSTicksRevol);
void ResetAllocType(void);
extern void SaveDebugAllocType(unsigned char ucAllocReason);
extern unsigned char CounterPreparation (unsigned char ucID, tRFTelType * ptInputWA);
extern  unsigned char ucConceptFixPos0(void);
extern void Very1stABSTickIinit(void);
extern unsigned char ucGetAnZahn(unsigned char ucWheelPosIx);

#ifdef pb_ModulTest_050104
extern void TESTPrintToothZOM_HL(void);
extern void TESTPrintToothZOMAsLine(void);
extern void TESTPrinToothZOMSummary(unsigned char i);
extern void TESTPrintFPAZOMSlot(unsigned char ucSlot);
#endif //pb_ModulTest_050104

#endif

