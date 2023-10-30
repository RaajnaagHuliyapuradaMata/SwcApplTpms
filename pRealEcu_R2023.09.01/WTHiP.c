

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003

#else
#include <stdio.h>
#endif

unsigned char bHiP( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char  ucRet;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;
#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = tPSSA.ucParaHighPressThres;
#endif

  if(ptLWD->tHFD.tHF.ucP >= tPSSA.ucParaHighPressThres)
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHiPIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHiPIxc) == 1)
   {
      if(ptLWD->tHFD.tHF.ucP <= (tPSSA.ucParaHighPressThres - tPSSA.ucParaHighPressResetThres))
      {
        ucRet = 0;
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHiPIxc);
      }
      else{
        ucRet = 1;
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHiPIxc);
      ucRet = 0;
   }
  }
  return(ucRet);
}

#ifndef pb_ModulTest_02062003

#else
void PrintHiPCfg(void){
  printf("Parametersatz HiP:\n");
  printf("Schwelle/mbar; Hysterese/mbar; \n");
  printf(" %3d; %d; \n",tWDA.tWD.ucParaHighPressThres*ucPResInMBarc,tWDA.tWD.ucParaHighPressResetThres*ucPResInMBarc);
}
#endif
