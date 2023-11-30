#ifndef ccm_h
#define ccm_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "ccmX.h"

#define cCcUnspecWarningInFahrzyklusFlagInitState     ( (boolean) FALSE)
#define cCcUnspecWarningInFahrzyklusFlagActiveState   ( (boolean) TRUE)

static uint8 ucNokCounterCCM = 0;

static uint8 ucGetMalfunctionCCM(void);
static uint8 ucGetInterferenceCCM(void);
static uint8 ucGetFlatTireCCM( Rte_Instance self);
static uint8 ucGetLernphaseCCM( Rte_Instance self);
static uint8 ucGetReifenwechselCCM( Rte_Instance self);
static uint8 ucGetBefuellhinweisCCM(void);
static uint8 ucGetPlausiCheckCCM( Rte_Instance self);
static uint8 ucGetAutoSelFailedCCM( Rte_Instance self);
static uint8 ucGetSpeedCcm2158CCM(void);
static uint8 ucGetSpeedCcm2159CCM(void);
static void StartCCM( uint8 ucCcmIx);
static void StopCCM( uint8 ucCcmIx);

#ifdef __cplusplus
}
#endif

#endif
