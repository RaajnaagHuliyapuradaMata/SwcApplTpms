

#ifdef IBTCM_SW_ANPASSUNGEN
   #include "iTpms_Interface.hpp"
   #include "SwcApplTpms_Rte.hpp"
   #include "SwcApplTpms_NvM_If.hpp"
  #include "statemanagerx.hpp"
   #include "calibr.hpp"
   #include "calibrX.hpp"
#else
   #include "tss_stdx.hpp"

   #include "eecatc_ifx.hpp"
   #include "eecate_ifx.hpp"
   #include "procdatx.hpp"
   #include "statemanagerx.hpp"
   #include "statisticsx.hpp"
   #include "busmsgX.hpp"

   #include "calibr.hpp"
   #include "calibrX.hpp"
#endif

void CalibrSetPressureCAL(void){
  uint8 u8Press;
  uint8 u8LocalVarCodPlacardPress;

  u8LocalVarCodPlacardPress = GETucVarCodPlacardPressEE();

  if( (u8LocalVarCodPlacardPress >=  cMINPOK) &&
       (u8LocalVarCodPlacardPress <=  cMAXPOK)    )

  {
   u8Press = u8LocalVarCodPlacardPress;
  }
  else{

    //u8Press = 136;
     u8Press = 96;

   PUTucVarCodPlacardPressEE(u8Press);
  }

  InformWarnHandlerSM( 0, u8Press, u8Press);
}

