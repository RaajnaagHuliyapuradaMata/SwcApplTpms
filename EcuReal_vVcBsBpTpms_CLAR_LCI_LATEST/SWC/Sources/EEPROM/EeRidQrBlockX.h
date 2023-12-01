

#ifndef _ee_rid_qr_block_X_H
#define _ee_rid_qr_block_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cMaxQRCodeSets                  ((uint8)12)

#define cMountedDateIx                  ((uint8)0)
#define cMountedKmIx                    ((uint8)6)
#define cUnmountedDateIx                ((uint8)10)
#define cUnmountedKmIx                  ((uint8)16)
#define cRuntimeKmIx                    ((uint8)20)

extern void InitRidQrBlock1u2EE(Rte_Instance self);

extern uint8 GETTyreDimQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreDimQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreDOTQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreDOTQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreOEMQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreOEMQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreRuntimeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreRuntimeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreMountedFlagEE(Rte_Instance self, uint8 i);
extern void PUTTyreMountedFlagEE(Rte_Instance self, uint8 i, uint8 y);

extern void    ClearRidQrBlock1UpdateFlagEE(void);
extern void    ClearRidQrBlock2UpdateFlagEE(void);
extern boolean bGetRidQrBlock1UpdateFlagEE(void);
extern boolean bGetRidQrBlock2UpdateFlagEE(void);
extern void    SetRidQrBlock1UpdateFlagEE(void);
extern void    SetRidQrBlock2UpdateFlagEE(void);

#ifdef __cplusplus
}
#endif

#endif
