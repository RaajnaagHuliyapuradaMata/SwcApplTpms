

#ifndef _hs_inaktivereignis_H
#define _hs_inaktivereignis_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "HS_InaktivereignisX.h"

#define cErrorNoAction  0x00
#define cErrorNotActive 0x01
#define cErrorUnknown   0x03

typedef struct{
  uint8 ucStatDatumText[8];
  uint8 ucStatUhrzeitText[8];
  uint32 ulStatKilometerstandWert;
  uint8 ucStatInternerFehlercode;
  uint8 ucStatZaehlerInaktivWert;
}
tHsInaktivereignisType;

static uint8 SaveInaktivereignisDS(Rte_Instance self, uint8 ucErrorCode);
static void IeFiFoShiftDS(Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif

