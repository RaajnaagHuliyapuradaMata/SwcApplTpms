

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
#endif
#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"
#include "statemanager.hpp"
#include "statisticsX.hpp"
#include "state_bzX.hpp"

#ifndef pb_ModulTest_02062003

#else
#include <stdio.h>
#endif

static uint8 aucIsoPresMemory[ucSumWEc];
static uint16 ushAxImbSuppresionCounter;
static boolean bAxImbSuppresionCounter_Started;
static boolean timerExpired;

#ifdef IBTCM_SW_ANPASSUNGEN
#define U16_CNT_MAX_VAL ((uint16)600) //ssc: must be 600 for 10 minutes
#else
#define U8_CNT_MAX_VAL ((uint8)100)
#endif

#define U8_MIN_NB_OF_RxTelInCurentState_FOR_AX_IMB      ((uint8)10)

#ifdef BUILD_WITH_UNUSED_FUNCTION
unsigned char bAxImb( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg )
{
  uint8 ucID;
  uint8 ucID_otherWEonAx = ucSumWEc;
  uint8 ucP;
  sint8 scT;
  uint16 ushIso;
  uint8 aucCarMountedPos[1];
  uint8 aucWEid[1];
  uint8 ucPos = ucSumWEc, uc2ndPos =ucSumWEc;
  uint8 ucToCompareV1=0, ucToCompareV2=0;
  uint8 ucRet = 0;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;
  aucCarMountedPos[0] = 0;
  aucWEid[0] = 0;
  ucID = ptLWD->tHFD.tHF.ucId;
  ucP = ptLWD->tHFD.tHF.ucP;
  scT = ptLWD->tHFD.tHF.scTWE;
  ushIso = ushMIso( ucP, scT);

  GetPosOfIdIFH( ucID, &aucCarMountedPos[0] );
  ucPos = aucCarMountedPos[0];

  if(ucPos < ucSumWEc)
  {

    aucIsoPresMemory[ucPos] = ucPfT( ushIso, (20 + ush273Kelvinc) );

#ifdef pb_DebugWarnLevels_030203
   if(aucIsoPresMemory[ucPos] > 40)
   {
      ptLWD->ucCurWarnLevel = (aucIsoPresMemory[ucPos] - uc1Barc);  //gives out the relative threshold value (only for debug?)
   }
   else{
      ptLWD->ucCurWarnLevel = 0;
   }
#endif

   if( ucPos == ucWPFLc )
   {
      uc2ndPos = ucWPFRc;
   }

   if( ucPos == ucWPFRc )
   {
      uc2ndPos = ucWPFLc;
   }

   if( ucPos == ucWPRLc )
   {
      uc2ndPos = ucWPRRc;
   }

   if( ucPos == ucWPRRc )
   {
      uc2ndPos = ucWPRLc;
   }

    GetIdOfPosIFH( uc2ndPos, &aucWEid[0] );
   ucID_otherWEonAx = aucWEid[0];

   ucToCompareV2 = ucToCompareV1;
   if( aucIsoPresMemory[uc2ndPos] < aucIsoPresMemory[ucPos] )
   {
      if(  aucIsoPresMemory[uc2ndPos] !=0)
      {
        ucToCompareV1 = aucIsoPresMemory[uc2ndPos];
        ucToCompareV2 = aucIsoPresMemory[ucPos];
      }
   }
   else{
      if(  aucIsoPresMemory[ucPos] !=0)
      {
        ucToCompareV1 = aucIsoPresMemory[ucPos];
        ucToCompareV2 = aucIsoPresMemory[uc2ndPos];
      }
   }
  }
  else{
   ucToCompareV2 = ucToCompareV1;
  }

  if(ucToCompareV2 > (ucToCompareV1 + tPSSA.ucParaAxImbSetThres))
  {
   if(ushAxImbSuppresionCounter >= U16_CNT_MAX_VAL)
   {

      if((ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucAxImbIxc) == 1))
      {
        ucRet = 1;
      }
      else{
        ucRet = 0;
      }
   }
   else{

      if((ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucAxImbIxc) == 1))
      {
        ucRet = 1;
      }
      else{
        ucRet = 0;
      }
   }
  }
  else{
   if(ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucAxImbIxc) == 1)
   {
      if(ucToCompareV2 <= (ucToCompareV1 + tPSSA.ucParaAxImbResThres))
      {
        ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucAxImbIxc);
        ClearWarnBitWN(ucID_otherWEonAx, ucAxImbIxc);

        ucRet = 0;
      }
      else{
        ucRet = 1;
      }
   }
   else{
      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucAxImbIxc);
      ClearWarnBitWN(ucID_otherWEonAx, ucAxImbIxc);

      ucRet = 0;
   }
  }

  return(ucRet);
}
#endif

void Init_AxImbSuppressionCounter(void){
  ushAxImbSuppresionCounter = 0;
  bAxImbSuppresionCounter_Started = FALSE;
  timerExpired = FALSE;
}

void Start_AxImbSuppressionCounter(void){
  bAxImbSuppresionCounter_Started = TRUE;
}

void Increment_AxImbSuppressionCounter(void){
  if((bAxImbSuppresionCounter_Started == TRUE) &&
    (timerExpired != TRUE))
  {
   if(ushAxImbSuppresionCounter < U16_CNT_MAX_VAL)
   {
      ushAxImbSuppresionCounter++;
   }
   else{
      timerExpired = TRUE;
   }
  }
}

#ifndef pb_ModulTest_02062003

#else
void PrintAxImbCfg(void){
  printf("Parametersatz AxImb:\n");
  printf("SetImb: Schwelle/mbar;ResetImb: Schwelle/mbar;\n");
  printf(" %d; %d;\n",tWDA.tWD.ucParaAxImbSetThres*ucPResInMBarc,tWDA.tWD.ucParaAxImbResThres*ucPResInMBarc);
}

#endif
