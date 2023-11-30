

#ifndef EEIFACE_H
#define EEIFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

extern void GetDataEE( Rte_Instance self, uint8 ucId, void * pRamAdr);
extern void PutDataEE( Rte_Instance self, uint8 ucId, const void * pRamAdr, boolean bUpdateOnEvent);

#ifdef __cplusplus
}
#endif

#endif
