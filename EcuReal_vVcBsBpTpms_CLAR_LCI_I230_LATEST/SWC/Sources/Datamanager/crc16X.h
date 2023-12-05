#ifndef crc16X_h
#define crc16X_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

extern uint16 ushCalcCrc16( const uint8 *pucBuffer, uint16 ushLength);
extern uint8 ucCalcCrc8( const uint8 *pui8Buffer, uint8 ui8MessageLen);

#ifdef __cplusplus
}
#endif

#endif
