#include "WnTypePar.h"
#include "eeiface.h"

#define ucSHORT_TIMER_STATE_IDLEc     ((uint8) 0)
#define ucSHORT_TIMER_STATE_RUNNINGc  ((uint8) 1)
#define ucSHORT_TIMER_STATE_EXPIREDc  ((uint8) 2)
#define ushSHORT_TIMER_INIT_VALUEc    ((uint16) 0xFFFFu)
#define ucSHORT_TIMER_OFF_VALUEc      ((uint8)  8)

static ShortTimerStateArrayType ucShortTimerStatePWARN = { ucSHORT_TIMER_STATE_IDLEc, ucSHORT_TIMER_STATE_IDLEc, ucSHORT_TIMER_STATE_IDLEc, ucSHORT_TIMER_STATE_IDLEc };
static ShortTimerArrayType ushWarnDelayShortTimerPWARN = { ushSHORT_TIMER_INIT_VALUEc, ushSHORT_TIMER_INIT_VALUEc, ushSHORT_TIMER_INIT_VALUEc, ushSHORT_TIMER_INIT_VALUEc };

static void TimerStartPWARN( uint8 ucIdX, uint8 ucDelayInMin);
static void TimerStopPWARN( uint8 ucIdX);

uint8 bWT_Pwarn( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8 ucWarnSetThres, ucWarnResetThres;
  uint8 ucPminThresTol, ucPwarnCThres, ucPwarnNCThres;
  uint8 ucPtolNC, ucRet = 0;

  ucPtolNC = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThNCTolCOD;
  ucPminThresTol = ucGetPMinCS() + ucPtolNC;
  ucPwarnNCThres    = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucAlThresNCfactorCOD) * ptLWD->tSD.ucPSoll) + 50) / 100);
  if( ucPwarnNCThres < ucPminThresTol){
    ucPwarnNCThres = ucPminThresTol;
  }

  ucPwarnCThres  = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucAlThresCfactorCOD) * ptLWD->tSD.ucPinitTreifen) + 50) / 100);

  if( ucPwarnCThres > ucPwarnNCThres){
    ucWarnSetThres = ucPwarnCThres;
  }else{
    ucWarnSetThres = ucPwarnNCThres;
  }

  if( (ucWarnCfg & ucCtryMaskc) == ucUSCodec){
    if( (boolean) ptLWD->tCOD.ucSaturierungAktivCOD == TRUE){
      if( ucWarnSetThres > (ucPwarnNCThres + ucPtolNC)){
        ucWarnSetThres = (ucPwarnNCThres + ucPtolNC);
      }
    }
  }

  if( ptLWD->tSD.ucPinitTreifen < ptLWD->tSD.ucPSoll)
  {
    ucWarnResetThres = ptLWD->tSD.ucPSoll - ptLWD->tSD.ucPanneClearHyst;
  }else{
    ucWarnResetThres = ptLWD->tSD.ucPinitTreifen - ptLWD->tSD.ucPanneClearHyst;
  }

  if( ucWarnSetThres > ucWarnResetThres)
  {
    ucWarnResetThres = ucWarnSetThres;
  }

  ptLWD->ucCurWarnSetThres   = ucWarnSetThres;
  ptLWD->ucCurWarnResetThres = ucWarnResetThres;

  if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc) == 1)
  {

    if( ptLWD->tHFD.ucP > ucWarnResetThres)
    {

      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      TimerStopPWARN( ptLWD->tHFD.ucId);
      ucRet = 0;
    }else{

      if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc) == 1)
      {
        ucRet = ucWarnBitAirMassIxWNc;
      }else{
        ucRet = ucWarnBitTonnageIxWNc;
      }
    }
  }else{

    if( ptLWD->tHFD.ucP < ucWarnSetThres)
    {

      if( ptLWD->tHFD.ucP <= ucPwarnNCThres)
      {

        if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc) == 1)
        {
          ClearWarnAttrBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);

          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          if( ucRet == 0)
          {

            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          }
          ucRet = 0;
        }else{
          if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc) == 0)
          {
            if( ptLWD->bNoFreakNoTimer == TRUE)
            {

              ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
              if( ucRet == 0)
              {

                (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
              }

              (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
              ucRet = ucWarnBitTonnageIxWNc;
            }else{
              ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
              if( ucRet == 1)
              {

                TimerStartPWARN( ptLWD->tHFD.ucId, ptLWD->tCOD.ucShortHoldTimeCOD);

                if( ucShortTimerStatePWARN[ptLWD->tHFD.ucId] == ucSHORT_TIMER_STATE_IDLEc)
                {
                  (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
                  ucRet = ucWarnBitTonnageIxWNc;
                }else{
                  ucRet = 0;
                }
              }else{
                ucRet = 0;
              }
            }
          }else{
            ucRet = 0;
          }
        }
      }else{

        if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc) == 1)
        {
          ClearWarnAttrBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);

          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
          if( ucRet == 0)
          {

            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
          }
          ucRet = 0;
        }else{
          if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc) == 0)
          {
            if( ptLWD->bNoFreakNoTimer == TRUE)
            {

              ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
              if( ucRet == 0)
              {

                (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
              }

              (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
              ucRet = ucWarnBitAirMassIxWNc;
            }else{
              ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
              if( ucRet == 1)
              {

                TimerStartPWARN( ptLWD->tHFD.ucId, ptLWD->tCOD.ucShortHoldTimeCOD);

                if( ucShortTimerStatePWARN[ptLWD->tHFD.ucId] == ucSHORT_TIMER_STATE_IDLEc)
                {
                  (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
                  ucRet = ucWarnBitAirMassIxWNc;
                }else{
                  ucRet = 0;
                }
              }else{
                ucRet = 0;
              }
            }
          }else{
            ucRet = 0;
          }
        }
      }
    }else if( ptLWD->tHFD.ucP > ucWarnSetThres)
    {

      TimerStopPWARN( ptLWD->tHFD.ucId);
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }else{

      ucRet = 0;
    }
  }

  return ucRet;
}

static void TimerStartPWARN( uint8 ucIdX, uint8 ucDelayInMin)
{
  if( ucDelayInMin < ucSHORT_TIMER_OFF_VALUEc)
  {
    ucShortTimerStatePWARN[ucIdX] = ucSHORT_TIMER_STATE_RUNNINGc;
    ushWarnDelayShortTimerPWARN[ucIdX] = (uint16) ucDelayInMin * 600;
  }else{
    ucShortTimerStatePWARN[ucIdX] = ucSHORT_TIMER_STATE_IDLEc;
    ushWarnDelayShortTimerPWARN[ucIdX] = ushSHORT_TIMER_INIT_VALUEc;
  }
}

void TimerStopAllPWARN(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    TimerStopPWARN( ucLoop);
  }
}

static void TimerStopPWARN( uint8 ucIdX)
{
  ucShortTimerStatePWARN[ucIdX]      = ucSHORT_TIMER_STATE_IDLEc;
  ushWarnDelayShortTimerPWARN[ucIdX] = ushSHORT_TIMER_INIT_VALUEc;
}

void TimerInitPWARN(Rte_Instance self)
{
  uint8 ucLoop;
  uint8 ucRet;

  GetDataEE(self, cucShortTimerIdWN, &ushWarnDelayShortTimerPWARN);

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ushWarnDelayShortTimerPWARN[ucLoop] == 0)
    {

      if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc) == 1)
      {
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitAirMassIxWNc) == 1)
      {
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_RUNNINGc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitTonnageIxWNc) == 1)
      {
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_RUNNINGc;
      }else{
        TimerStopPWARN( ucLoop);
      }
    }else if( ushWarnDelayShortTimerPWARN[ucLoop] == ushSHORT_TIMER_INIT_VALUEc)
    {

      if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc) == 1)
      {
        ushWarnDelayShortTimerPWARN[ucLoop] = 0;
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitAirMassIxWNc) == 1)
      {
        ushWarnDelayShortTimerPWARN[ucLoop] = 0;
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;
        ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        }
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitTonnageIxWNc) == 1)
      {
        ushWarnDelayShortTimerPWARN[ucLoop] = 0;
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;
        ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        }
      }else{
        TimerStopPWARN( ucLoop);
      }
    }else{

      if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc) == 1)
      {
        ushWarnDelayShortTimerPWARN[ucLoop] = 0;
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitAirMassIxWNc) == 1)
      {
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_RUNNINGc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitTonnageIxWNc) == 1)
      {
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_RUNNINGc;
      }else{
        TimerStopPWARN( ucLoop);
      }
    }
  }

  PutWarnBitsToNvmWN(self);
}

void TimerCountPWARN(Rte_Instance self)
{
  uint8 ucLoop;
  uint8 ucRet;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ucShortTimerStatePWARN[ucLoop] == ucSHORT_TIMER_STATE_RUNNINGc)
    {
      if( ushWarnDelayShortTimerPWARN[ucLoop] > 0)
      {
        ushWarnDelayShortTimerPWARN[ucLoop]--;
      }else{
        ucShortTimerStatePWARN[ucLoop] = ucSHORT_TIMER_STATE_EXPIREDc;

        ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitIxWNc);
        }
      }
    }
  }

  PutDataEE(self, cucShortTimerIdWN, &ushWarnDelayShortTimerPWARN, FALSE);

  PutWarnBitsToNvmWN(self);
}

void GetTimerValPWARN( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt)
{
  *ucTimState = ucShortTimerStatePWARN[ucZomPos];
  *ushTimCnt  = ushWarnDelayShortTimerPWARN[ucZomPos];
}

