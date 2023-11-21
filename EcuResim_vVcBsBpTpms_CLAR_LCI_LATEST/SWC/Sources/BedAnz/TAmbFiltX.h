

#ifndef _tambfilt_X_H
#define _tambfilt_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cTAmbientFilterFactorDefaultValue   ((uint8) 10)

typedef sint8  TAmbientValueType;

typedef sint16 TAmbientFilterValueType;

typedef uint8  TAmbientFilterFactorValueType;

extern void InitTAF( Rte_Instance self);
extern void CyclicTAF( Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif
