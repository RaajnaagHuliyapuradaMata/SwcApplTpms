#ifndef _steuerndigitalrdc_H
#define _steuerndigitalrdc_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "SteuernDigitalRdcX.h"

static uint8 ucBandmodeDS(Rte_Instance self, uint8 ucAction);
static uint8 ucTestErFahrtDS(Rte_Instance self, uint8 ucAction);
static uint8 ucCalRequestDS(Rte_Instance self, uint8 ucAction);

#ifdef __cplusplus
}
#endif

#endif

