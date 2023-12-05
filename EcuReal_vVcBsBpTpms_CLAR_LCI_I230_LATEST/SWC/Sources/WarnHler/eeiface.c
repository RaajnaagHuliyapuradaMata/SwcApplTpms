

#include "eeiface.h"

#include "EeWarnStatusBlockX.h"

void GetDataEE(Rte_Instance self, uint8 ucId, void * pRamAdr)
{
  switch ( ucId)
  {
    case cucWsIdWN:
      GETucWsEE(self, (uint8*) pRamAdr);
    break;

    case cucCdIdWN:
      GETtCdEE(self, (tCalibrationTab *) pRamAdr);
    break;

    case cucTsIdTM:
      GETucTsEE(self, (uint8*) pRamAdr);
    break;

    case cucCbIdTM:
      GETaucCbEE(self, (WarnConfigArrayType *) pRamAdr);
    break;

    case cucWarnTypeArrayIdWN:
      GETaucWarnTypeArrayEE(self, (WarnBitArrayType *) pRamAdr);
    break;

    case cucShortTimerIdWN:
      GETaushShortTimerEE(self, (ShortTimerArrayType *) pRamAdr);
    break;

    case cucLongTimerIdWN:
      GETaushLongTimerEE(self, (LongTimerArrayType *) pRamAdr);
    break;

    default:
    break;
  }
}

void PutDataEE(Rte_Instance self, uint8 ucId, const void * pRamAdr, boolean bUpdateOnEvent)
{
  switch( ucId)
  {
    case cucWsIdWN:
      PUTucWsEE(self, *(const uint8 *) pRamAdr, bUpdateOnEvent);
    break;

    case cucCdIdWN:
      PUTtCdEE(self, (const tCalibrationTab *) pRamAdr, bUpdateOnEvent);
    break;

    case cucTsIdTM:
      PUTucTsEE(self, *(const uint8 *) pRamAdr, bUpdateOnEvent);
    break;

    case cucCbIdTM:
      PUTaucCbEE(self, (const WarnConfigArrayType *) pRamAdr, bUpdateOnEvent);
   	break;

    case cucWarnTypeArrayIdWN:
      PUTaucWarnTypeArrayEE(self, (const WarnBitArrayType *) pRamAdr, bUpdateOnEvent);
    break;

    case cucShortTimerIdWN:
      PUTaushShortTimerEE(self, (const ShortTimerArrayType *) pRamAdr, bUpdateOnEvent);
    break;

    case cucLongTimerIdWN:
      PUTaushLongTimerEE(self, (const LongTimerArrayType *) pRamAdr, bUpdateOnEvent);
    break;

    default:
    break;
  }
}
