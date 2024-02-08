#ifndef _multiframe_X_H
#define _multiframe_X_H

#include "tss_stdx.hpp"

#ifdef IBTCM_SW_ANPASSUNGEN
#define cMF_MAX_FILTER_TIME        ((uint8)  2)
#define cMF_MAX_FILTER_TIME_ROTATS ((uint8)  7)
#else
#define cMF_MAX_FILTER_TIME        ((uint8)  4)
#define cMF_MAX_FILTER_TIME_ROTATS ((uint8) 14)
#endif

#define cFT_SINGLE_FRAME  ((uint8) 0 )
#define cFT_MULTI_FRAME   ((uint8) 1 )

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void InitMF(void);
#endif

extern void TimeMF(void);
extern uint8 ucCheckForMultiFrameMF( uint32 ulReID, uint8 ucTGCounter, uint8 u8MaxTimeFilter  );

#endif
