

#ifndef _statusrdclesen_X_H
#define _statusrdclesen_X_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cucIxStatEigenraederBekannt               ((uint8)  0)
#define cucIxStatRadposErBekannt                  ((uint8)  1)
#define cucIxStatDtcInactive                      ((uint8)  2)
#define cucIxStatKalAnforderungAktiv              ((uint8)  3)
#define cucIxStatRadZuordnungTimeout              ((uint8)  4)
#define cucIxStatBandmodeAktiv                    ((uint8)  5)
#define cucIxStatTestEigenradFahrt                ((uint8)  6)
#define cucIxStatErFahrtVthresAkiv                ((uint8)  7)
#define cucIxStatBmTimeoutActive                  ((uint8)  8)
#define cucIxStatHarteWarnungUnspezifischAktiv    ((uint8)  9)
#define cucIxStatHarteWarnungVlAktiv              ((uint8) 10)
#define cucIxStatHarteWarnungVrAktiv              ((uint8) 11)
#define cucIxStatHarteWarnungHlAktiv              ((uint8) 12)
#define cucIxStatHarteWarnungHrAktiv              ((uint8) 13)
#define cucIxStatKl15Ein                          ((uint8) 14)
#define cucIxStatFzgFaehrt                        ((uint8) 15)
#define cucIxStatErkennungAlleRe                  ((uint8) 16)

extern void GetStatusRdcLesenDS(Rte_Instance self, uint8* pucData);

#ifdef __cplusplus
}
#endif

#endif

