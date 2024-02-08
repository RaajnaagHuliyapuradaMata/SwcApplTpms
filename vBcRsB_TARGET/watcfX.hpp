#ifndef _watcf_X_H
#define _watcf_X_H

#define cWATO_STOP_ALARM     ((uint8) 0x01)
#define cWATO_START_ALARM    ((uint8) 0x02)
#define cWATO_READ_ALARM     ((uint8) 0x04)
#define cWATO_BREAK_ALARM    ((uint8) 0x08)
#define cWATO_RESTART_ALARM  ((uint8) 0x10)

extern void InitWATCF(void);
extern void StartWallocTOAlarm(uint8 ucTimeInSec);
extern void StopWallocTOAlarm(void);
extern void ControlWATO(uint8 ucCommand, uint8 ucTimeInSec);

#endif
