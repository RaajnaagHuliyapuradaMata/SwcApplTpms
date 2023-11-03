

#ifndef _waninglamp_H
#define _waninglamp_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "WarningLampX.h"

#define cFixLampBlinkTimePreloadValue   ( (uint16) 700u)

typedef enum{

  eFL_Off = 0,
  eFL_Static = 1,
  eFL_Blinking = 2,
  eFL_Invalid = 0xff
}tFL_StatesDecl;

#ifdef _EcuVirtual
#else
static boolean bIsBlinkingWL(void);
static void StartBlinkingWL(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
