

#ifndef _ee_diagblock_H
#define _ee_diagblock_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "EeDiagBlockX.h"

typedef struct{
  uint8 ucRInitCallEvents;
  uint8 ucInitByHufEvents;
  uint8 ucCodingChangedEvents;
}
ResetEventCounterType;

#ifdef __cplusplus
}
#endif

#endif

