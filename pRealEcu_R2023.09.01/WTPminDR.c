

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
#else
  #include "eecate_ifx.hpp"
#endif

#include "global.hpp"
#include "uswarn.hpp"
#include "USCS.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"

#ifndef pb_ModulTest_02062003

#else
#include <stdio.h>
#endif

static unsigned char bEUKOIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);

static unsigned char bUSIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);

static unsigned char bPRCIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg);

unsigned char bPMinDR( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg )
{
  unsigned char ucRet = 0;
  uint8 u8_activeLegislation = E_US_LEG_NON_EXTRA_LOAD_TIRES;

  u8_activeLegislation = GETucVarCodLegislationEE();

  if( u8_activeLegislation == E_EU_KO_LEG )
  {

   ucRet = bEUKOIsWarnVeryLowActive(ptLWD, ucWarnCfg);
  }
  else if( (u8_activeLegislation == E_US_LEG_NON_EXTRA_LOAD_TIRES) || (u8_activeLegislation == E_US_LEG_EXTRA_LOAD_TIRES) )
  {

   ucRet = bUSIsWarnVeryLowActive(ptLWD, ucWarnCfg);
  }
  else{

   ucRet = bPRCIsWarnVeryLowActive(ptLWD, ucWarnCfg);
  }

  return(ucRet);
}

static unsigned char bEUKOIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char ucPCompare, ucResPCompare, ucRet;
  unsigned short ushHelp;

#ifdef NVM_ZUGRIFFSPROBLEM
  ucPCompare = 100;  // == ucPMinDefc; (2,5Bar)  instead of ucGetPMinCS();
#else
  ucPCompare = ucGetPMinCS();
#endif
#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucPCompare;
#endif

   if(ptLWD->tHFD.tHF.ucP < ucPCompare)
   {
      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
   }
   else{
      if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc) == 1)
      {
        ucResPCompare = (ptLWD->tSD.ucPSoll > ucNegHystPMinc) ? (ptLWD->tSD.ucPSoll - ucNegHystPMinc):0;
        if((ucWarnCfg & ucIsoClearc) == ucIsoClearc)
        {
          if(ptLWD->tHFD.tHF.ucP >= ucResPCompare )
          {
            ushHelp = (unsigned short)(0xFFFF & (ptLWD->tHFD.tHF.scTWE + ush273Kelvinc));
            ucResPCompare = ucPfT(ptLWD->tSD.ushMSoll, ushHelp);
            if(ucResPCompare >= uc1Barc)
            {
              ucResPCompare -= uc1Barc; //make rel. value from abs.
              if(ptLWD->tHFD.tHF.ucP >= ucResPCompare)
              {
                ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
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
            ucRet = 1;
          }
        }
        else{
          if( ptLWD->tHFD.tHF.scTWE < ( ptLWD->tHFD.tHF.scTa + scTResLimitc) )
          {
            if(ptLWD->tHFD.tHF.ucP >= ucResPCompare )
            {
              ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
              ucRet = 0;
            }
            else{
              if(DynWarnResetCond(ptLWD->tHFD.tHF.ucP, ucPCompare, ptLWD->tHFD.tHF.ucId) == TRUE)
              {
                ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
                ucRet = 0;
              }
              else{
                ucRet = 1;
              }
            }
          }
          else{
            if(ptLWD->tHFD.tHF.ucP >= (ucResPCompare +  ucHystPMinc))
            {
              ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
              ucRet = 0;
            }
            else{
              ucRet = 1;
            }
          }
        }
      }
      else{
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
        ucRet = 0;
      }
   }
    return(ucRet);
}

static unsigned char bUSIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  uint8 u8Pplacard, u8Pmin, u8ReceivedRelativePressure;
  uint8 ucPCompareSETCond, ucPCompareTermenA, ucPCompareTermenB, ucPCompareRESETCond;
  unsigned char ucRet = 0;
  static uint8 u8ConsecLowPRxCnt = 0;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;
  //ucPCompare = ucGetPMinCS();

  u8Pplacard = ptLWD->tSD.ucPSoll;
  u8Pmin = (uint8)(0xFF & GETucVarCodMinPressThresEE());
  u8ReceivedRelativePressure = (uint8)(0xFF & ptLWD->tHFD.tHF.ucP);

  ucPCompareTermenA = ( (uint8)(u8Pplacard/u8_US_Resolution) - ( (uint8)( ((uint16)((u8Pplacard/u8_US_Resolution)* u8_US_30Percent))/(uint16)100  ) ) ) * u8_US_Resolution;

  ucPCompareTermenB = (uint8)(0xFF & (u8Pmin + u8_US_Tolerance));

  if( ucPCompareTermenA >= ucPCompareTermenB )
  {
   ucPCompareSETCond = ucPCompareTermenA;
  }
  else{
   ucPCompareSETCond = ucPCompareTermenB;
  }

#ifdef pb_DebugWarnLevels_030203
  ptLWD->ucCurWarnLevel = ucPCompareSETCond;
#endif

  if(u8ReceivedRelativePressure <= ucPCompareSETCond)
  {

   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
  }
  else{

   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc) == 1)
   {

      ucPCompareRESETCond = (ptLWD->tSD.ucPSoll > ucNegHystPMinc) ? (ptLWD->tSD.ucPSoll - ucNegHystPMinc):0;

      if(ptLWD->tHFD.tHF.ucP >= ucPCompareRESETCond)
      {

        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);

        ucRet = 0;
      }
      else{

        ucRet = 1;
      }
   }
   else{

      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);

      ucRet = 0;
   }
  }

  return(ucRet);
}

static unsigned char bPRCIsWarnVeryLowActive(struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char ucPCompare, ucResPCompare, ucRet;

  ucPCompare = ucGetPMinCS();

  if(ptLWD->tHFD.tHF.ucP < ucPCompare)
  {
   ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);
  }
  else{

   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc) == 1)
   {

      ucResPCompare = (ptLWD->tSD.ucPSoll > ucNegHystPMinc ) ? (ptLWD->tSD.ucPSoll - ucNegHystPMinc ) : 0;

      if(ptLWD->tHFD.tHF.ucP >= ucResPCompare)
      {

        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);

        ucRet = 0;
      }
      else{

        ucRet = 1;
      }
   }
   else{

      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucPMinIxc);

      ucRet = 0;
   }
  }

  return(ucRet);
}

#ifndef pb_ModulTest_02062003

#else
void PrintPMinCfg(void){
  printf("\n Parametersatz PMin:\n");
  printf(" PMinabs/mbar; Hysterese/mbar; \n");
  printf(" %4d; %3d; \n",ucGetPMinCS()*ucPResInMBarc,ucHystPMinc*ucPResInMBarc );
}

#endif
