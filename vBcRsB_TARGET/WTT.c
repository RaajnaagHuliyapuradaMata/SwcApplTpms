#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"

unsigned char bTW(
      struct LocalWarnDat* ptLWD
   ,  unsigned char        ucWarnCfg
){
   uint8 LocalWarnCfgToRemoveWarning = ucWarnCfg;
   sint8         S8_TempThreshold       = NvM3_GETucVarCodTemperatureWarningThresEE();
   uint8         U8_CurrentWarnBitState = ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
   unsigned char ucRet = 0;
   if(U8_CurrentWarnBitState == 0){
      if(
            ptLWD->tHFD.tHF.scTWE
         >= S8_TempThreshold
      ){
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
      }
   }
   else{
      if(
            ptLWD->tHFD.tHF.scTWE
         <  (
                  S8_TempThreshold
               -  10
            )
      ){
         ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
         ucRet = 0;
      }
      else{
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
      }
   }
   return(ucRet);
}
