#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cABS_OK              ((uint8) 0x00)
#define cABS_ERROR           ((uint8) 0x01)
#define cABS_STATE_INIT						            ((uint8) 0x00)
#define ccABS_STATE_LinABS_AVL                ((uint8) 0x01)
#define ccABS_STATE_LinABS_ERR                ((uint8) 0x02)

#ifdef ABS_SIG_SIZE_ONEBYTE
#define cAbsOverflowValue 0xFFU
#else
#define cAbsOverflowValue 0xFFFFU
#endif

#ifdef ABS_SIG_FFFF_IS_INVALID
#define cAbsOverflowCorrection 0
#else
#define cAbsOverflowCorrection 1
#endif

#define cMaxTelegramRetention     (uint16)200
#define cTelegramWaitingTime      (uint16)30

typedef struct typedef_struct_tABS_DATA{
  uint16 ushAbsTimeStamp;
  uint16 ushAbsCntVl;
  uint16 ushAbsCntVr;
  uint16 ushAbsCntHl;
  uint16 ushAbsCntHr;
  uint8 ucOverflowCntVl;
  uint8 ucOverflowCntVr;
  uint8 ucOverflowCntHl;
  uint8 ucOverflowCntHr;
}tABS_DATA;

extern void InitABS(void);
extern void PutABS( uint16 ushTime, const uint16* ushCnt);
extern uint8 ucLinABS( uint16 ushRfTimeStamp);
extern uint8 ucGetLinABS( uint16* ushCnt);
extern uint8 ucGetLinStatusABS(void);
extern void EnableRollDetectionABS(void);
extern void DisableRollDetectionABS(void);
extern uint16 ushGetLinABSValue(uint8 ucIndex);
extern uint8 ucGetStopCounter(void);
extern void GetLastAbsTicks(tABS_DATA* ushLastAbsVals);

# ifdef __cplusplus
}
# endif
