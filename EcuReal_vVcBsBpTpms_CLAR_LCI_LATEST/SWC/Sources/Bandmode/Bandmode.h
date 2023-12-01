#ifndef Bandmode_h
#define Bandmode_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "BandmodeX.h"

#define cucMaxCountWheelElectronicBM  ((uint8)  1)

#ifdef _EcuVirtual
#else
static uint16 ushStateBM                    = 0x0000;
static uint8  ucCounterWheelElectronicBM[cAnzRad]   = { 0, 0, 0, 0 };

static void    VerifyGutEmpfCtBM(Rte_Instance self);
static boolean bGetOtherBmServiceSetBM( uint16 ushService);
static void SaveRidDataAndCompareInBM (Rte_Instance self);
#endif

#ifdef __cplusplus
}
#endif

#endif
