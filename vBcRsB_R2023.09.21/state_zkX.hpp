#ifndef _state_zk_X_H
#define _state_zk_X_H

#include "tss_stdx.hpp"

#define cCAL_TIO              ((uint16) 0x0004)
#define cCAL_P_HA_INVALID     ((uint16) 0x0008)
#define cCAL_P_VA_INVALID     ((uint16) 0x0010)
#define cCAL_P_MIN_INVALID    ((uint16) 0x0020)
#define cPOS_CHANGED_VL       ((uint16) 0x0400)
#define cPOS_CHANGED_VR       ((uint16) 0x0800)
#define cPOS_CHANGED_HL       ((uint16) 0x1000)
#define cPOS_CHANGED_HR       ((uint16) 0x2000)
#define cZK_ALLE_BITS         ((uint16) 0xffffU)

extern void InitZK(void);

extern void ClearBitZustandskennungZK(uint16 ushBitMask);
extern boolean bGetBitZustandskennungZK(uint16  ushBitMask);
extern void SetChangedBit4WP(uint8 ucWP);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void SetBitZustandskennungZK(uint16 ushBitMask);
extern uint16 ushGetZustandskennungZK(uint16 ushBitMask);
#endif

#endif
