#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "statemanagerx.hpp"
#include "calibr.hpp"
#include "calibrX.hpp"

void CalibrSetPressureCAL(void){
   uint8 u8Press;
   uint8 u8LocalVarCodPlacardPress;
   u8LocalVarCodPlacardPress = GETucVarCodPlacardPressEE();
   if((u8LocalVarCodPlacardPress >= cMINPOK) && (u8LocalVarCodPlacardPress <= cMAXPOK)){
      u8Press = u8LocalVarCodPlacardPress;
   }
   else{
      u8Press = 96;
      PUTucVarCodPlacardPressEE(
         u8Press);
   }
   InformWarnHandlerSM(
      0,
      u8Press,
      u8Press);
}

