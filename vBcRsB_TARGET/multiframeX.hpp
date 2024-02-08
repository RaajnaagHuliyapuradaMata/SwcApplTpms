#ifndef _multiframe_X_H
#define _multiframe_X_H

#include "tss_stdx.hpp"

#define cMF_MAX_FILTER_TIME        ((uint8)  2)
#define cMF_MAX_FILTER_TIME_ROTATS ((uint8)  7)
#define cFT_SINGLE_FRAME  ((uint8) 0 )
#define cFT_MULTI_FRAME   ((uint8) 1 )

extern void TimeMF(void);
extern uint8 ucCheckForMultiFrameMF( uint32 ulReID, uint8 ucTGCounter, uint8 u8MaxTimeFilter  );

#endif
