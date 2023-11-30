#ifndef SteuernDigitalRdcX_h
#define SteuernDigitalRdcX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cFunctionNo_BandmodeDS            ( (uint8)  1)
#define cFunctionNo_TestErFahrtDS         ( (uint8)  4)
#define cFunctionNo_CalRequestDS          ( (uint8)  8)
#define cActionNo_BandmodeEinDS           ( (uint8) 1)
#define cActionNo_BandmodeAusDS           ( (uint8) 0)
#define cActionNo_TestErFahrtResetDS      ( (uint8) 0)
#define cActionNo_TestErFahrtSetDS        ( (uint8) 1)
#define cActionNo_TestErFahrtSetNoSpeedDS ( (uint8) 2)
#define cActionNo_CalRequestSetDS         ( (uint8) 1)
#define cActionNo_CalRequestResetDS       ( (uint8) 0)
#define cucRetValOkDS                 ((uint8) 0x00)
#define cucRetValServiceNotStartetDS  ((uint8) 0x0F)
#define cucRetValServiceNotStopedDS   ((uint8) 0xF0)
#define cucRetValErrorDS              ((uint8) 0xFF)

extern uint8 ucPutSteuernDigitalRdcDS( Rte_Instance self, uint8 ucFunctionNo, uint8 ucActionNo);

#ifdef __cplusplus
}
#endif

#endif
