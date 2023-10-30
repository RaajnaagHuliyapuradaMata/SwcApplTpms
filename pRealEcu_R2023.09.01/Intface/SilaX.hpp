

#ifndef  SILA_X_H
#define SILA_X_H

#ifdef IBTCM_SW_ANPASSUNGEN
#else
   #include "types.hpp"
#endif

typedef enum{
  SILA_STATE_CHECK               = 0x00u
   ,  SILA_STATE_NORMAL_OFF          = 0x09u
   ,  SILA_STATE_PERMANENT_ON        = 0x0Au
   ,  SILA_STATE_MALFUNCTIONFLASH    = 0x0Bu
}tSilaStateType;

extern void  SilaInit(void);

extern void  SilaPutState(tSilaStateType ucState);

extern tSilaStateType SilaGetState(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION

extern void  SilaKL15On(void);
#endif

extern void SilaTimeOut (void);

extern void  SilaTask(void);

#endif

