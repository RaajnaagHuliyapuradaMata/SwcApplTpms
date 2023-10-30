#include "Std_Types.hpp"

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003
#else
#include <stdio.h>
#endif

#ifdef WITH_UNUSED_WARNINGS
unsigned char bHardTDR( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char ucPCompare,ucResPCompare,ucRet;
  unsigned short ushHelp;
  signed char scTaBuf;

  scTaBuf = ptLWD->tHFD.tHF.scTa;
  ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
  if( ptLWD->tHFD.tHF.scTa > sc40Gradc )
  {
    ptLWD->tHFD.tHF.scTa = sc40Gradc + scTDropHTc;
  }
  else{
   if( (ptLWD->tHFD.tHF.scTa + scTDropHTc) >= 0 )
   {
      ptLWD->tHFD.tHF.scTa += scTDropHTc;
   }
   else{
      ptLWD->tHFD.tHF.scTa = 0;
   }
  }
  if(ptLWD->tHFD.tHF.scTWE > ptLWD->tHFD.tHF.scTa)
  {
   ushHelp = (unsigned short) ptLWD->tHFD.tHF.scTa +  ush273Kelvinc;
   ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTc, ptLWD->tSD.scTSoll ))), ushHelp) ;
   ucPCompare = (uint8)(0xFF & (ucPCompare + ucPfT(ushMDropHTc, (unsigned short) (ptLWD->tHFD.tHF.scTWE-ptLWD->tHFD.tHF.scTa))));
  }
  else{
   ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTc, ptLWD->tSD.scTSoll ))), ushHelp) ;
  }
  ucPCompare -= uc1Barc; //make relative value from absolute

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucPCompare;
#endif

  if(ptLWD->tHFD.tHF.ucP <= ucPCompare)
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc) == 1)
   {
      ucResPCompare = (ptLWD->tSD.ucPSoll > ucNegHystHTc) ? (ptLWD->tSD.ucPSoll - ucNegHystHTc):0;
      if((ucWarnCfg & ucIsoClearc) == ucIsoClearc)
      {
        if( ptLWD->tHFD.tHF.ucP >= ucResPCompare )
        {
          ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
          if(ptLWD->tHFD.tHF.ucP >= (ucPfT(ptLWD->tSD.ushMSoll, ushHelp) - uc1Barc))
          {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            ucRet = 1;
          }
        }
        else{
          ucRet = 1;
        }
      }
      else{
        if( ptLWD->tHFD.tHF.scTWE < ( scTaBuf + scTResLimitc) )
        {
          if(ptLWD->tHFD.tHF.ucP >= ucResPCompare)
          {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            if(DynWarnResetCond(ptLWD->tHFD.tHF.ucP, ucPCompare, ptLWD->tHFD.tHF.ucId) == TRUE)
            {
              ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
              ucRet = 0;
            }
            else{
              ucRet = 1;
            }
          }
        }
        else{
          if(ptLWD->tHFD.tHF.ucP >= (ucResPCompare +  ucHystHTc))
          {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
            ucRet = 0;
          }
          else{
            ucRet = 1;
          }
        }
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTIxc);
      ucRet = 0;
   }
  }
  ptLWD->tHFD.tHF.scTa = scTaBuf;
  return(ucRet);
}
#endif //WITH_UNUSED_WARNINGS

#ifndef pb_ModulTest_02062003

#else
void PrintHTCfg(void){
  printf("Parametersatz HardT:\n");
  printf("Schwelle/mbar; Hysterese/mbar; TempKnick/°C; MDrop \n");
  printf("%d; %d; %d; %d; \n",ucThresHTc*ucPResInMBarc,ucHystHTc*ucPResInMBarc,scTDropHTc, ushMDropHTc);
}

#endif
