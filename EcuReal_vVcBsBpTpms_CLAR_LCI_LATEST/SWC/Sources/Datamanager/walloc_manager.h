#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "walloc_managerX.h"
#include "datamanagerX.h"
#include "abs_linX.h"

#define WATO_STATE_STOP   (0U)
#define WATO_STATE_RUN    (1U)
#define WATO_STATE_HALT   (2U)
#define SPIN_FORWARD      (0U)
#define SPIN_REVERSE      (1U)
#define SPIN_NA           (2U)
#define SPIN_INVALID      (0xff)
#define cSHORT_PARK_TIME  (5*60U)
#define cResRefPoint_NoAction  (uint8)0x00
#define cResRefPoint_DDBackOk  (uint8)0x01
#define cResetRefPoint_SpeedOk (uint8)0x02

static boolean bLearningWheelPosActiveWAM( uint8 ucSpeedThreshold);
static void SetLearnStateWAM(Rte_Instance self, uint8 ucWAState);
static void SetDrivingDirectionWAM(void);
static void StartCalOnErFinishWAM(void);
static void ProcessCalOnErFinishWAM(void);

# ifdef __cplusplus
}
# endif
