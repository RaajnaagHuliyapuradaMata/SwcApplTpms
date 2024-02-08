
#ifndef HUF_LEARNEOL
#define HUF_LEARNEOL

#include "tss_stdx.hpp"
#include "Tpms_Rte_Data_Type.hpp"

#define EOL_ROUT_NEVER_STARTED            0x00U
#define EOL_ROUT_RUNNING                  0x01U
#define EOL_ROUT_FINISHED_SUCCESSFULLY    0x02U
#define EOL_ROUT_RESERVED                 0x03U
#define EOL_ROUT_STOPPED_ON_REQUEST       0x04U
#define EOL_ROUT_START_WRONG_PARAM        0x05U
#define EOL_ROUT_ENDED_WITH_ERROR         0x07U

#define EOL_ROUTINE_ACTIVE                TRUE
#define EOL_ROUTINE_INACTIVE              FALSE

extern void EOL_InitLearnRoutine(void);
extern uint8 EOL_StartLearnRoutine( uint8 ucLearnRoutineTimeoutValue);
extern void EOL_ResetLearnRoutine (void);
extern boolean EOL_CheckPeriodicLearnRoutineStatus(void);
extern uint8 EOL_GetStatusEOLRoutine(void);
extern void EOL_PutStatusEOLRoutine( uint8 u8NewStatus );
extern uint8 EOL_GetEOLRoutineActive(void);
extern void EOL_PutEOLRoutineActive( uint8 ucNewStatus );

#endif

