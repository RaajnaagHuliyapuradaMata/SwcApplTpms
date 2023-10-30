

#ifndef REDiag_if_H
#define REDiag_if_H

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "tss_stdx.hpp"
#else
  #include "tss_stdx.hpp"
  #include "sgdiagX.hpp"
  #include "applmainx.hpp"
#endif

extern uint16 MaxFailCounterInEE(void);

#endif
