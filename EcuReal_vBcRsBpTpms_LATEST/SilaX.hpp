#ifndef  SILA_X_H
#define SILA_X_H

typedef enum{
      SILA_STATE_CHECK = 0x00u,
      SILA_STATE_NORMAL_OFF = 0x09u,
      SILA_STATE_PERMANENT_ON = 0x0Au,
      SILA_STATE_MALFUNCTIONFLASH = 0x0Bu
}tSilaStateType;

extern void  SilaInit(void);
extern void  SilaPutState(tSilaStateType ucState);
extern tSilaStateType SilaGetState(void);
extern void SilaTimeOut (void);
extern void  SilaTask(void);

#endif

