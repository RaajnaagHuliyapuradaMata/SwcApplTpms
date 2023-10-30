

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "procdat.hpp"
#else
  #include "procdat_if.hpp"
#endif
#include "wallocX.hpp"

uint8 ucGetRadPosAtSlotPDIF( uint8 ucSlotNo )
{
  return ucGetWPOfCol( ucSlotNo );
}

