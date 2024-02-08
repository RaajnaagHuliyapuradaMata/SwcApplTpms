

#ifndef _statistics_if_H
#define _statistics_if_H

#include "statisticsx.hpp"

extern void SetRecCounterInEE( uint16 ushValue, uint8 ucSlot);
extern void SetMissCounterInEE( uint16 ushValue, uint8 ucSlot);
extern void SetFailCounterInEE( uint16 ucValue, uint8 ucSlot);

extern uint16 GetRecCounterInEE( uint8 ucSlot);
extern uint16 GetMissCounterInEE( uint8 ucSlot);
extern uint16 GetFailCounterInEE( uint8 ucSlot);

extern boolean CarIsDriving(void);
extern boolean ReDiagActive(void);
#ifdef BUILD_WITH_UNUSED_FUNCTION
uint32 WUIDinSlot (uint8);
#endif
extern boolean RfInterferenceActive(void);
#ifdef BUILD_WITH_UNUSED_FUNCTION
void ChangeSystemState(void);
#endif
extern boolean CheckWUFDErr(uint16 CounterValue, uint8 ucIx);

#endif
