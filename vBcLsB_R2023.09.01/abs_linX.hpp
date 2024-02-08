

#ifndef _abs_lin_X_H
#define _abs_lin_X_H

#include "tss_stdx.hpp"
#include "Tpms_Rte_Data_Type.hpp"

#define cABS_OK              ((uint8) 0x00)
#define cABS_ERROR           ((uint8) 0x01)
#define cABS_VALUE_TOO_OLD   ((uint8) 0x02)

#define cABS_STATE_INIT          ((uint8) 0x00)
#define ccABS_STATE_LinABS_AVL   ((uint8) 0x01)
#define ccABS_STATE_LinABS_ERR   ((uint8) 0x02)

extern void InitABS(void);

extern void  PutABS( uint32 ulTime, const uint16 ushCnt[] );
extern uint8 GetLinABS( uint16 ushCnt[] );

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern uint8 ucStateABS(void);
#endif //BUILD_WITH_UNUSED_FUNCTION
extern uint8 LockABS(void);
extern uint8 UnlockABS(void);
extern uint8 LinABS(uint32 ulRfTimeStamp);

#endif
