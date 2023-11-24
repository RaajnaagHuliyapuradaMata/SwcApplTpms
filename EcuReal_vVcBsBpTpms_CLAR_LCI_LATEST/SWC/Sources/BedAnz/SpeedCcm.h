

#ifndef _speed_ccm_H
#define _speed_ccm_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "SpeedCcmX.h"

static void     CalculatePressThSCC( Rte_Instance self);
static boolean  bIsPressureTooLowSCC(void);
static boolean  bIsSpeedTooHighSCC(void);

#ifdef __cplusplus
}
#endif

#endif
