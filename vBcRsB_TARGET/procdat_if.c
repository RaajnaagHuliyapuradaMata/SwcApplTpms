#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "procdat.hpp"
#include "wallocX.hpp"

uint8 ucGetRadPosAtSlotPDIF(
   uint8 ucSlotNo){ //TBD: Move to other c file
  return ucGetWPOfCol( ucSlotNo );
}

