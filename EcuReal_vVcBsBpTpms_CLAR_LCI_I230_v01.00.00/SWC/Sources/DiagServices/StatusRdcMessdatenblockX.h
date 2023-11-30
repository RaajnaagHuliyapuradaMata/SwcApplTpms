#ifndef StatusRdcMessdatenblockX_h
#define StatusRdcMessdatenblockX_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cucIxStatReIdentifierWert                 ((uint8)  0)
#define cucIxStatRadPositionNr                    ((uint8)  4)
#define cucIxStatLetzterReifendruckwertWert       ((uint8)  5)
#define cucIxStatLetzterReifentemperaturwertWert  ((uint8)  7)
#define cucIxStatSolldruckWert                    ((uint8)  8)
#define cucIxStatGutempfaengeWert                 ((uint8) 10)
#define cucIxStatAusbeuteWert                     ((uint8) 12)
#define cucIxStatRssiPegelWert                    ((uint8) 13)
#define cucIxStatRestlebensdauerWert              ((uint8) 15)
#define cucIxStatRadelektronikStatus              ((uint8) 17)
#define cucIxStatHarteWarnungAktiv                ((uint8) 18)
#define cucIxStatPosChanged                       ((uint8) 19)
#define cucIxStatFolgeausfallWert                 ((uint8) 20)
#define cucIxStatReHersteller                     ((uint8) 21)
#define cucIxStatRadelektronikSendemode           ((uint8) 22)
#define cucIxStatTelegrammtyp                     ((uint8) 23)

extern void GetStatusRdcMessdatenblockDS( Rte_Instance self, uint8 ucBlockNo, uint8* pucData);

#ifdef __cplusplus
}
#endif

#endif
