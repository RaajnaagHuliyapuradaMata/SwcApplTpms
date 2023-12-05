#ifndef BandmodeX_h
#define BandmodeX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cushBandmodeActivationBM        ((uint16) 0x0001)
#define cushTestEigenradFahrtBM         ((uint16) 0x0002)
#define cushTestEigenradFahrtNoSpeedBM  ((uint16) 0x0004)
#define cushAllServiceBitsBM            ((uint16) 0x0006)
#define cushReceptionReFlBM             ((uint16) 0x0010)
#define cushReceptionReFrBM             ((uint16) 0x0020)
#define cushReceptionReRrBM             ((uint16) 0x0040)
#define cushReceptionReRlBM             ((uint16) 0x0080)
#define cushAllReceptionBitsBM          ((uint16) 0x00F0)
#define cushErFahrtVThresBM             ((uint16) 0x1000)
#define cushAllBitsBM                   ((uint16) 0xFFFF)
#define cushThisBitsSavedInEeBM         ((uint16) 0x0FFF)
#define cushResetAllStatusBitsBM        ((uint16) 0x0000 | cushAllReceptionBitsBM)

extern void PutStateBM ( uint16 ushState);
extern uint16 ushGetStateBM (void);
extern boolean bGetStateBitBM ( uint16 ushBitMask);
extern void    SetStateBitBM ( uint16 ushBitMask, boolean bState);
extern boolean bGetBandmodeBM(void);
extern void    StopServiceBM(void);
extern boolean bStartServiceBM( uint16 ushService);
extern void InitBM( uint16 ushState);
extern void BandmodeActivateBM (void);
extern void BandmodeDeactivateBM (void);
extern void CycleBandModeServiceBM (Rte_Instance self, boolean bSpeedThresBM);
extern void CountWheelElectronicDataBM( uint8 ucWheelPos);

#ifdef __cplusplus
}
#endif

#endif
