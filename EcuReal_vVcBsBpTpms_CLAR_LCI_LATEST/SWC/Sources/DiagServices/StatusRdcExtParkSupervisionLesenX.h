#ifndef _statusrdcextparksupervisionlesen_X_H
#define _statusrdcextparksupervisionlesen_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cucIxStatRdcExtParkSupConfigWert                  ( (uint8)  0)
#define cucIxStatRdcExtParkSupTolTempCompWert             ( (uint8)  1)
#define cucIxStatRdcExtParkSupTolTempNonCompWert          ( (uint8)  2)
#define cucIxStatRdcExtParkSupMobilityLossThWert          ( (uint8)  3)
#define cucIxStatRdcExtParkSupWarnPercentCompWert         ( (uint8)  4)
#define cucIxStatRdcExtParkSupWarnPercentNonCompWert      ( (uint8)  5)
#define cucIxStatRdcExtParkSupNotifPercentCompWert        ( (uint8)  6)
#define cucIxStatRdcExtParkSupNotifPercentNonCompWert     ( (uint8)  7)
#define cucIxStatRdcExtParkSupRefTempWert                 ( (uint8)  8)
#define cucIxStatRdcExtParkSupLastAmbPresWert             ( (uint8) 10)
#define cucIxStatRdcExtParkSupRcpFrontWert                ( (uint8) 11)
#define cucIxStatRdcExtParkSupRcpRearWert                 ( (uint8) 12)
#define cucIxStatRdcExtParkSupQuFnTyrInfoWert             ( (uint8) 13)
#define cucIxStatRdcExtParkSupQuTplWert                   ( (uint8) 14)
#define cucIxStatRdcExtParkSupIntWarnThFrontWert          ( (uint8) 15)
#define cucIxStatRdcExtParkSupIntWarnThRearWert           ( (uint8) 17)
#define cucIxStatRdcExtParkSupIntNotifThFrontWert         ( (uint8) 19)
#define cucIxStatRdcExtParkSupIntNotifThRearWert          ( (uint8) 21)
#define cucIxStatRdcExtParkSupActTirePressureFlWert       ( (uint8) 23)
#define cucIxStatRdcExtParkSupActTirePressureFrWert       ( (uint8) 25)
#define cucIxStatRdcExtParkSupActTirePressureRlWert       ( (uint8) 27)
#define cucIxStatRdcExtParkSupActTirePressureRrWert       ( (uint8) 29)
#define cucIxStatRdcExtParkSupActTireTempFlWert           ( (uint8) 31)
#define cucIxStatRdcExtParkSupActTireTempFrWert           ( (uint8) 32)
#define cucIxStatRdcExtParkSupActTireTempRlWert           ( (uint8) 33)
#define cucIxStatRdcExtParkSupActTireTempRrWert           ( (uint8) 34)
#define cucIxStatRdcExtParkSupActiveCcm1Wert              ( (uint8) 35)
#define cucIxStatRdcExtParkSupActiveCcm2Wert              ( (uint8) 37)
#define cucIxStatRdcExtParkSupActiveCcm3Wert              ( (uint8) 39)
#define cucIxStatRdcExtParkSupActiveCcm4Wert              ( (uint8) 41)
#define cucIxStatRdcExtParkSupActiveCcm5Wert              ( (uint8) 43)
#define cucIxStatRdcExtParkSupSleepDateWert               ( (uint8) 45)
#define cucIxStatRdcExtParkSupSleepTimeWert               ( (uint8) 53)
#define cucIxStatRdcExtParkSupWakeupDateWert              ( (uint8) 61)
#define cucIxStatRdcExtParkSupWakeupTimeWert              ( (uint8) 69)

extern void GetStatusRdcExtParkSupervisionLesen(Rte_Instance self, uint8 *pucData);

#ifdef __cplusplus
}
#endif

#endif
