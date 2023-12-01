#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cER_FINISH            ((uint16) 0x0001u)
#define cTOO_MUCH_RE          ((uint16) 0x0002u)
#define cLOC_NOT_POSSIBLE     ((uint16) 0x0004u)
#define cEIGENRAD             ((uint16) 0x0008u)
#define cZUGEORDNET           ((uint16) 0x0010u)
#define cZWANGSZUORDNUNG      ((uint16) 0x0020u)
#define cHIST_PRELOAD         ((uint16) 0x0040u)
#define cZO_FINISH            ((uint16) 0x0080u)
#define cLOC_INTERRUPTED      ((uint16) 0x0100u)
#define cDTC_INACTIVE         ((uint16) 0x0400u)
#define cTEILEIGENRAD         ((uint16) 0x0800u)
#define cZO_TIMEOUT           ((uint16) 0x1000u)
#define cBZ_ALLE_BITS         ((uint16) 0xFFFFu)

extern void InitBZ(Rte_Instance self, boolean bStartupInit);
extern void SetBitBetriebszustandBZ( uint16 ushBitMask);
extern void ClearBitBetriebszustandBZ( uint16 ushBitMask);
extern boolean bGetBitBetriebszustandBZ( uint16 ushBitMask);
extern uint16 ushGetBetriebszustandBZ( uint16 ushBitMask);

#ifdef __cplusplus
}
#endif
