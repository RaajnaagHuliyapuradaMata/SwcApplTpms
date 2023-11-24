#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cCAL_TIO              ((uint16) 0x0004u)
#define cCAL_P_HA_INVALID     ((uint16) 0x0008u)
#define cCAL_P_VA_INVALID     ((uint16) 0x0010u)
#define cCAL_P_MIN_INVALID    ((uint16) 0x0020u)
#define cPOS_CHANGED_VL       ((uint16) 0x0400u)
#define cPOS_CHANGED_VR       ((uint16) 0x0800u)
#define cPOS_CHANGED_HL       ((uint16) 0x1000u)
#define cPOS_CHANGED_HR       ((uint16) 0x2000u)
#define cZK_ALLE_BITS         ((uint16) 0xFFFFu)
#define cID_CHANGED_COL_0     ((uint8) 0x01)
#define cID_CHANGED_COL_1     ((uint8) 0x02)
#define cID_CHANGED_COL_2     ((uint8) 0x04)
#define cID_CHANGED_COL_3     ((uint8) 0x08)
#define cID_CHANGED_ALL       ((uint8) 0x0f)

extern void InitZK(void);
extern void SetBitZustandskennungZK( uint16 ushBitMask);
extern void ClearBitZustandskennungZK( uint16 ushBitMask);
extern boolean bGetBitZustandskennungZK( uint16 ushBitMask);
extern uint16 ushGetZustandskennungZK( uint16 ushBitMask);
extern void SetWpChangedBitZK( uint8 ucWP);
extern uint8 ucGetWpChangedBitsZK(void);
extern void SetIdChangedBitsZK( uint8 ucChangedBits);
extern uint8 ucGetIdChangedBitsZK(void);
extern void ClearIdChangedBitsZK(void);
extern void ClearWpChangedBitsZK(void);

#ifdef __cplusplus
}
#endif
