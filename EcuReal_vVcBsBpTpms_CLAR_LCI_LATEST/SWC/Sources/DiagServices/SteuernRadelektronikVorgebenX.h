

#ifndef _steuernradelektronikvorgeben_X_H
#define _steuernradelektronikvorgeben_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern uint8 ucPutSteuernRadelektronikVorgebenDS( Rte_Instance self, uint32 ulReId, uint8 ucRadPos);

#ifdef __cplusplus
}
#endif

#endif

