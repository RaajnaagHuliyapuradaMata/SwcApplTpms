#ifndef SeasRcpAdj_h
#define SeasRcpAdj_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "SeasRcpAdjX.h"

#define cLoNibblePassedSRA ( (uint8) 0x0Fu)
#define cHiNibblePassedSRA ( (uint8) 0xF0u)
#define cCyclicDriveTime   ( (uint8) 120)
#define cPermDriveTime     ( (uint8) 12)
#define cHyst              ( (uint8) 2)

static void StartOatLowerTimeSRA(Rte_Instance self);
static void StartOatHigherTimeSRA(Rte_Instance self);
static void CalculateOATavgSRA(Rte_Instance self);
static void CyclicOATSampleFuncSRA(uint16 ushCurSpeed, Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif
