#include "Std_Types.hpp"

#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003
#else
#include <stdio.h>
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

unsigned char bHardTVDR( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char ucPCompare,ucResPCompare,ucRet;
  unsigned short ushHelp;
  signed char scTaBuf;

  scTaBuf = ptLWD->tHFD.tHF.scTa;
  ucRet = (unsigned char)((ptLWD->tHFD.tHF.ushVehicleSpeed >  255) ?  255 : ptLWD->tHFD.tHF.ushVehicleSpeed);
  if( ucRet <= ucSpeedLevelHTVc)
  {
   ucPCompare = 0;
  }
  else{
   ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
   if( ptLWD->tHFD.tHF.scTa > sc40Gradc )
   {
      ptLWD->tHFD.tHF.scTa = sc40Gradc + scTDropHTVc;
   }
   else{
      if( (ptLWD->tHFD.tHF.scTa + scTDropHTVc) >= 0 )
      {
        ptLWD->tHFD.tHF.scTa += scTDropHTVc;
      }
      else{
        ptLWD->tHFD.tHF.scTa = 0;
      }
   }
   if(ptLWD->tHFD.tHF.scTWE > ptLWD->tHFD.tHF.scTa)
   {
      ushHelp = (unsigned short) ptLWD->tHFD.tHF.scTa +  ush273Kelvinc;
      ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTVc, ptLWD->tSD.scTSoll ))), ushHelp) ;
      ucPCompare = (uint8)(0xFF & (ucPCompare + ucPfT(ushMDropHTVc, (unsigned short) (ptLWD->tHFD.tHF.scTWE-ptLWD->tHFD.tHF.scTa))));
   }
   else{
      ucPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucThresHTVc, ptLWD->tSD.scTSoll ))), ushHelp) ;
   }
  }
  ucPCompare -= uc1Barc; //make rel. value from abs.

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucPCompare;
#endif
  if( ptLWD->tHFD.tHF.ucP <= ucPCompare )
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc) == 1)
   {
      ucResPCompare = (ptLWD->tSD.ucPSoll > ucNegHystHTVc) ? (ptLWD->tSD.ucPSoll - ucNegHystHTVc):0;
      if((ucWarnCfg & ucIsoClearc) == ucIsoClearc)
      {
        if( ptLWD->tHFD.tHF.ucP >= ucResPCompare )
        {
          ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
          ucResPCompare = ucPfT((unsigned short)(0xFFFF & (ptLWD->tSD.ushMSoll - ushMIso(ucNegHystHTVc, ptLWD->tSD.scTSoll ))), ushHelp) ;
          ucResPCompare -= uc1Barc; //make rel. value from abs.
          if(ptLWD->tHFD.tHF.ucP >= ucResPCompare)
          {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
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
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
            ucRet = 0;
          }
          else{
            if(DynWarnResetCond(ptLWD->tHFD.tHF.ucP, ucPCompare, ptLWD->tHFD.tHF.ucId) == TRUE)
            {
              ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
              ucRet = 0;
            }
            else{
              ucRet = 1;
            }
          }
        }
        else{
          if(ptLWD->tHFD.tHF.ucP >= (ucResPCompare +  ucHystHTVc))
          {
            ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
            ucRet = 0;
          }
          else{
            ucRet = 1;
          }
        }
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucHardTVIxc);
      ucRet = 0;
   }

  }
  ptLWD->tHFD.tHF.scTa = scTaBuf;
  return(ucRet);
}
#endif

#ifndef pb_ModulTest_02062003

#else
void PrintHTVCfg(void){
  printf("Parametersatz HardTV:\n");
  printf("Schwelle/mbar; Hysterese/mbar; TempKnick/°C; MDrop; SpeedLevel/km/h ; NegHyst/mBar;\n");
  printf("%d; %d; %d; %d; %d ; %d \n",ucThresHTVc *ucPResInMBarc,ucHystHTVc*ucPResInMBarc,scTDropHTVc, ushMDropHTVc, ucSpeedLevelHTVc,ucNegHystHTVc*ucPResInMBarc );
}

#endif
