

#ifndef _statusrdcdeveloperdatalesen_X_H
#define _statusrdcdeveloperdatalesen_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cStatusRdcDeveloperDataLesen_MuxChannel0  ((uint8)  0)
#define cStatusRdcDeveloperDataLesen_MuxChannel1  ((uint8)  1)
#define cStatusRdcDeveloperDataLesen_MuxChannel2  ((uint8)  2)
#define cStatusRdcDeveloperDataLesen_MuxChannel3  ((uint8)  3)
#define cStatusRdcDeveloperDataLesen_MuxChannel4  ((uint8)  4)
#define cStatusRdcDeveloperDataLesen_MuxChannel5  ((uint8)  5)
#define cStatusRdcDeveloperDataLesen_MuxChannel6  ((uint8)  6)
#define cStatusRdcDeveloperDataLesen_MuxChannel7  ((uint8)  7)
#define cStatusRdcDeveloperDataLesen_MuxChannel8  ((uint8)  8)
#define cStatusRdcDeveloperDataLesen_MuxChannel9  ((uint8)  9)
#define cStatusRdcDeveloperDataLesen_MuxChannel10 ((uint8) 10)
#define cStatusRdcDeveloperDataLesen_MuxChannel11 ((uint8) 11)
#define cStatusRdcDeveloperDataLesen_MuxChannel12 ((uint8) 12)
#define cStatusRdcDeveloperDataLesen_MuxChannel13 ((uint8) 13)
#define cStatusRdcDeveloperDataLesen_MuxChannel14 ((uint8) 14)
#define cStatusRdcDeveloperDataLesen_MuxChannel15 ((uint8) 15)
#define cStatusRdcDeveloperDataLesen_MuxChannel16 ((uint8) 16)

#define cStatusRdcDeveloperDataLesen_MuxChannelMaxValidValue ( cStatusRdcDeveloperDataLesen_MuxChannel16)

extern void GetStatusRdcDeveloperDataLesenDS( Rte_Instance self, uint8* pucData);
extern uint8 ucPutDeveloperDataMuxChannelDS( uint8 ucMuxChannel);

extern uint8 ucGetDeveloperDataMuxChannelDS(void);

#ifdef __cplusplus
}
#endif

#endif

