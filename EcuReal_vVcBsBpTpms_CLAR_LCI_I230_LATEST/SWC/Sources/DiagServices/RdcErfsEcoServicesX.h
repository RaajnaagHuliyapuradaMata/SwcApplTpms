#ifndef _rdcerfsecoservices_X_H
#define _rdcerfsecoservices_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void GetStatusRdcErfsEcoTabLesenDS(uint8* pucData);
extern void GetStatusRdcErfsAktReifenEcoLesenDS(Rte_Instance self, uint8* pucData);
extern void GetStatusRdcErfsAktReifenLesenDS(Rte_Instance self, uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoAktReifenposVorgebenDS(Rte_Instance self, const uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoNeueReifenVorgebenDS(Rte_Instance self, const uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoReifentabelleVorgebenDS(Rte_Instance self, const uint8* pucData, const uint8 ucElement);

#ifdef __cplusplus
}
#endif

#endif

