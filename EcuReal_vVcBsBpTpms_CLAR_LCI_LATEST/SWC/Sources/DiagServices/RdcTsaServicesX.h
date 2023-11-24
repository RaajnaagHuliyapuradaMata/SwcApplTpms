

#ifndef _rdctsaservices_X_H
#define _rdctsaservices_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

 #define cTyreMountedFlag                ((uint8) 0x05)
 #define cDateSize                       ((uint8) 6)
 #define cKmSize                         ((uint8)4)

extern void GetRdcRidAktReifenQRCodeLesenDS( Rte_Instance self, uint8 * paucData);
extern void GetRdcRidAlteReifenQRCodeLesenDS( Rte_Instance self, uint8 * paucData);
extern void GetRdcRidAktReifenLaufstreckeLesenDS( Rte_Instance self, uint8 * paucData);
extern void GetRdcRidAlteReifenLaufstreckeLesenDS( Rte_Instance self, uint8 * paucData);
extern void SaveCompleteQrCodeDataDS( Rte_Instance self);
extern void SetUpdateTyreQrCodeDataInNvRam( boolean bVal);
extern boolean GetUpdateTyreQrCodeDataInNvRamDM(void);
extern void SaveTsaDataDS( Rte_Instance self, const uint8* pucData);
extern void ReadTsaDataDS( Rte_Instance self, uint8* pucData);
extern void ResetQRTyreMountedFlags( Rte_Instance self, uint8 HisFlags);
extern uint8 GetOemIdDS( uint8 ucPrev, uint8 ucCur, uint8 IdIx);
extern uint8 GetQrIxOfWheelPos ( Rte_Instance self, uint8 ucWheelPos);

#ifdef __cplusplus
}
#endif

#endif

