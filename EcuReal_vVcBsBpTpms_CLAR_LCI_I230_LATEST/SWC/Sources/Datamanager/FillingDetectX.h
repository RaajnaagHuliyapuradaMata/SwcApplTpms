

#ifndef _filling_detect_X_H
#define _filling_detect_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

void StartFillingDetectionFID(Rte_Instance self);
boolean ProcessFillingDetectionFID(Rte_Instance self, uint8 ucSlot);

#ifdef __cplusplus
}
#endif

#endif
