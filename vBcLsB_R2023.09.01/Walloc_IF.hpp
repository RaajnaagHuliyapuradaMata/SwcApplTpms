

#ifndef WAEEIFACE_H
#define WAEEIFACE_H

#include "cd_decoder_x.hpp"

typedef tPreBuf tRFTelType;   //SSC

#define cMaxTeLen sizeof(tRFTelType)

extern void StartWATO(unsigned char ucTimeInSec);
extern void CancelWATO(void);
extern unsigned short ushGetABSingleTick(unsigned char ucIx);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char ucGetABSTick(unsigned short * p2aushABS);
extern unsigned short ushGetLW(void);
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef pb_ModulTest_050104
extern unsigned char ucGetFW(signed short * p2shFW);
extern void ResetEEPROM(void);
extern void TESTPutWayStretch(unsigned short * p2WayStretch);
extern void TESTResetABStick(void);
extern void TESTPutSingleABStick(unsigned short ushTickVal, unsigned char ucIx);
extern void TESTPutLenkwinkel(signed short shLW);
extern void TESTPutSpeed(unsigned char);
#endif

#endif
