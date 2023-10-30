#include "Std_Types.hpp"

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"

#ifndef pb_ModulTest_02062003
#else
#include <stdio.h>
#endif

#ifdef WITH_UNUSED_WARNINGS
unsigned char bFT( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char  ucRet;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucThresFTc;
#endif

  if(ptLWD->tHFD.tHF.ucP <= ucThresFTc)
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucFTIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucFTIxc) == 1)
   {
      if(ptLWD->tHFD.tHF.ucP > (ucThresFTc + ucHystFTc))
      {
        ucRet = 0;
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucFTIxc);
      }
      else{
        ucRet = 1;
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucFTIxc);
      ucRet = 0;
   }
  }
  return(ucRet);
}
#endif //WITH_UNUSED_WARNINGS

#ifndef pb_ModulTest_02062003

#else
void PrintFTCfg(void){
  printf("Parametersatz FT:\n");
  printf("Schwelle/mbar; Hysterese/mbar; \n");
  printf(" %3d; %d; \n",ucThresFTc*ucPResInMBarc,ucHystFTc*ucPResInMBarc);
}

#endif
