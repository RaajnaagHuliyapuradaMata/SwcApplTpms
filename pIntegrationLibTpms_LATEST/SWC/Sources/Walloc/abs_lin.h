#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "abs_linX.h"

#define cABS_DEBUG_MODE                       0
#define cDEBUG_ERROR_NO_ERROR                 ((uint8) 0x00)
#define cDEBUG_ERROR_OVERFLOW_ABSTIMEDIFF     ((uint8) 0x01)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVL        ((uint8) 0x02)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVR        ((uint8) 0x04)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHL        ((uint8) 0x08)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHR        ((uint8) 0x10)
#define cTimeOverflowValue        0xFFFFU
#define cPalTimingRange           (uint16)1260
#define cAbsSignalPeriodicity     (uint16)10
#define cAbsBufferSize            (uint8)((cPalTimingRange + cMaxTelegramRetention + cTelegramWaitingTime) / cAbsSignalPeriodicity)

static boolean bCarStandStillABS(void);
static uint16 ushCalcABS(uint16 ushRfTimeStamp, uint16 ush1stAbsTimeStamp, uint16 ush1stAbsCnt, uint16 ush2ndAbsTimeStamp, uint16 ush2ndAbsCnt);
static void RollDetectionABS(void);

# ifdef __cplusplus
}
# endif
