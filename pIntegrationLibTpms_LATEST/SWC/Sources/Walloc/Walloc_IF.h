#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "WAllocX.h"

#define cWAParameter      ((uint8) 0)
#define cHistoryIDSet     ((uint8) 1)
#define cHistoryWPSet     ((uint8) 2)
#define cZOMContent       ((uint8) 3)
#define cAllocState       ((uint8) 4)
#define cIDChangeBits     ((uint8) 5)
#define cPermutationState ((uint8) 6)
#define cMaxTeLen sizeof(tRFTelType)

extern void GetWADataEE( Rte_Instance self, uint8 ucId, uint8 *pRamAdr, uint16 ucLen);
extern void PutWADataEE( Rte_Instance self, uint8 ucId, const uint8 *pRamAdr, uint16 ucLen);
extern void CancelWATO(void);
extern uint8 ucGetABSTick( uint16* p2aushABS);
extern uint8 ucGetSpeed(void);
extern uint16 ushGetABSingleTick( uint8 ucIx);
extern uint16 ushGetAbsTickDifference( uint16 ushLeftVal, uint16 ushRightVal);

# ifdef __cplusplus
}
# endif
