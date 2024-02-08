

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswtime.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003

#else
#include <stdio.h>
#endif

#ifdef WITH_UNUSED_WARNINGS
unsigned char bLowP( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{

  unsigned char ucRet;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;
#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucThresLowPc;
#endif

  if(ptLWD->tHFD.tHF.ucP <= ucThresLowPc)
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc) == 1)
   {
      if( ptLWD->tHFD.tHF.ucP >= ptLWD->tSD.ucPSoll )
      {
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
        StopFilterSTWT(ptLWD->tHFD.tHF.ucId);
        ucRet = 0;
      }
      else{
        ucRet = 1;
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucSoftTIxc);
      StopFilterSTWT(ptLWD->tHFD.tHF.ucId);
      ucRet = 0;
   }
  }

  return(ucRet);
}
#endif //WITH_UNUSED_WARNINGS

#ifndef pb_ModulTest_02062003

#else
void PrintLowPCfg(void){
  printf("Parametersatz LowP:\n");
  printf("LowP: Schwelle/mbar;\n");
  printf(" %d; \n",ucThresLowPc*ucPResInMBarc);
}
#endif
