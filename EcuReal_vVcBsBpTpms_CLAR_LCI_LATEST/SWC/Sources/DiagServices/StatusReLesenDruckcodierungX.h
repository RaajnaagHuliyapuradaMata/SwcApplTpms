#ifndef StatusReLesenDruckcodierungX_h
#define StatusReLesenDruckcodierungX_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cStatusReLesenDruckcodierungDataArraySize     ((uint8) 8)

extern void InitStatusReLesenDruckcodierungDS(void);
extern void PutStatusReLesenDruckcodierungDataDS( uint32 ulId, uint8 ucPres, uint8 ucPresState, uint8 ucBatt);
extern void GetStatusReLesenDruckcodierungDS( uint8* pucData);

#ifdef __cplusplus
}
#endif

#endif
