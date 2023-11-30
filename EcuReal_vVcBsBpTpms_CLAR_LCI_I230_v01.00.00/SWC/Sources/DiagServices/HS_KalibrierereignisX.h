#ifndef HS_KalibrierereignisX_h
#define HS_KalibrierereignisX_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cCalError               (uint8)0x00
#define cCalOtherTyre           (uint8)0x01
#define cCalByHMI               (uint8)0x02
#define cCalByDiag              (uint8)0x03
#define cCalVirgin              (uint8)0x04
#define cCalFilDetRe0           (uint8)0x05
#define cCalFilDetRe1           (uint8)0x06
#define cCalFilDetRe2           (uint8)0x07
#define cCalFilDetRe3           (uint8)0x08
#define cCalNvmError            (uint8)0x09
#define cCalRidNoStatusbar      (uint8)0x0A
#define cCalRidStatusbar        (uint8)0x0B
#define cCalSeaAdj              (uint8)0x0C
#define cCalRunning             (uint8)0xFE
#define cCalInvalid             (uint8)0xFF
#define cCalPA                  (uint8)0x80
#define cCalOtherTyre_PA        (cCalOtherTyre      + cCalPA)
#define cCalByHMI_PA            (cCalByHMI          + cCalPA)
#define cCalByDiag_PA           (cCalByDiag         + cCalPA)
#define cCalVirgin_PA           (cCalVirgin         + cCalPA)
#define cCalFilDetRe0_PA        (cCalFilDetRe0      + cCalPA)
#define cCalFilDetRe1_PA        (cCalFilDetRe1      + cCalPA)
#define cCalFilDetRe2_PA        (cCalFilDetRe2      + cCalPA)
#define cCalFilDetRe3_PA        (cCalFilDetRe3      + cCalPA)
#define cCalRidNoStatusbar_PA   (cCalRidNoStatusbar + cCalPA)
#define cCalRidStatusbar_PA     (cCalRidStatusbar	  + cCalPA)
#define cCalSeaAdj_PA           (cCalSeaAdj         + cCalPA)

extern void ReadCalibrationEventDS( Rte_Instance self, uint8 * paucData);
extern uint8 SaveCalibrationEventDS( Rte_Instance self);
extern void SetCalibrationRootCauseDS( Rte_Instance self, uint8 ucRootCause);
extern uint8 GetLatestCalibrationRootCauseDS( Rte_Instance self);
extern uint8 ucGetCalibrationRootCauseDS( Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif
