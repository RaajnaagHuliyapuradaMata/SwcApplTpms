#ifndef _procdat_H
#define _procdat_H

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "tss_stdx.hpp"
#else
  #include "tss_stdx.hpp"
  #include "ring_buffer_X.hpp"
#endif

extern uint8 ucGetRadPosAtSlotPDIF(uint8 ucSlotNo);

#endif
