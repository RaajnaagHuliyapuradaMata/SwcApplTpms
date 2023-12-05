#ifndef StatusReLesenDruckcodierung_h
#define StatusReLesenDruckcodierung_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "StatusReLesenDruckcodierungX.h"

#define cRecCounterDefaultVal                         ((uint8)  0xff)

typedef struct{
  uint32 ulReID;
  uint8  ucPres;
  uint8  ucBatt;
  uint8  ucRecCounter;
}StatusReLesenDruckcodierungDataType;

#ifdef __cplusplus
}
#endif

#endif
