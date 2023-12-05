#include "WnTypePar.h"
#include "eeiface.h"

#define ucLONG_TIMER_STATE_IDLEc      ((uint8) 0)
#define ucLONG_TIMER_STATE_RUNNINGc   ((uint8) 1)
#define ucLONG_TIMER_STATE_EXPIREDc   ((uint8) 2)
#define ushLONG_TIMER_INIT_VALUEc     ((uint16) 0xFFFFu)
#define ucLONG_TIMER_OFF_VALUEc       ((uint8)  19)

static LongTimerStateArrayType ucLongTimerStatePWARNTOL = { ucLONG_TIMER_STATE_IDLEc, ucLONG_TIMER_STATE_IDLEc, ucLONG_TIMER_STATE_IDLEc, ucLONG_TIMER_STATE_IDLEc };
static LongTimerArrayType ushWarnDelayLongTimerPWARNTOL = { ushLONG_TIMER_INIT_VALUEc, ushLONG_TIMER_INIT_VALUEc, ushLONG_TIMER_INIT_VALUEc, ushLONG_TIMER_INIT_VALUEc };

static void TimerStartPWARNTOL( uint8 ucIdX, uint8 ucDelayInMin);
static void TimerStopPWARNTOL( uint8 ucIdX);

uint8 bWT_PwarnTol( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8 ucWarnSetThres, ucWarnResetThres;
  uint8 ucPminThresTol, ucPwarnCThresTol, ucPwarnNCThres;
  uint8 ucPtolC, ucPtolNC, ucRet = 0;

  ucPtolC  = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThCTolCOD;
  ucPtolNC = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThNCTolCOD;

  ucPminThresTol = ucGetPMinCS() + ucPtolNC;

  ucPwarnNCThres = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucAlThresNCfactorCOD) * ptLWD->tSD.ucPSoll) + 50) / 100);

  if( ucPwarnNCThres < ucPminThresTol)
  {
    ucPwarnNCThres = ucPminThresTol;
  }

  ucPwarnCThresTol = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucAlThresCfactorCOD) * ptLWD->tSD.ucPinitTreifen) + 50) / 100) + ucPtolC;

  if( ucPwarnCThresTol > ucPwarnNCThres)
  {
    ucWarnSetThres = ucPwarnCThresTol;
  }else{
    ucWarnSetThres = ucPwarnNCThres;
  }

  if( (ucWarnCfg & ucCtryMaskc) == ucUSCodec)
  {
    if( (boolean) ptLWD->tCOD.ucSaturierungAktivCOD == TRUE)
    {
      if( ucWarnSetThres > (ucPwarnNCThres + ucPtolNC))
      {
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
      TimerStopPWARNTOL( ptLWD->tHFD.ucId);
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

                TimerStartPWARNTOL( ptLWD->tHFD.ucId, ptLWD->tCOD.ucLongHoldTimeCOD);

                if( ucLongTimerStatePWARNTOL[ptLWD->tHFD.ucId] == ucLONG_TIMER_STATE_IDLEc)
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

                TimerStartPWARNTOL( ptLWD->tHFD.ucId, ptLWD->tCOD.ucLongHoldTimeCOD);

                if( ucLongTimerStatePWARNTOL[ptLWD->tHFD.ucId] == ucLONG_TIMER_STATE_IDLEc)
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

      TimerStopPWARNTOL( ptLWD->tHFD.ucId);
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }else{

      ucRet = 0;
    }
  }

  return ucRet;
}

static void TimerStartPWARNTOL( uint8 ucIdX, uint8 ucDelayInMin)
{
  if( ucDelayInMin < ucLONG_TIMER_OFF_VALUEc)
  {
    ucLongTimerStatePWARNTOL[ucIdX] = ucLONG_TIMER_STATE_RUNNINGc;
    ushWarnDelayLongTimerPWARNTOL[ucIdX] = (uint16) ucDelayInMin * 600;
  }else{
    ucLongTimerStatePWARNTOL[ucIdX] = ucLONG_TIMER_STATE_IDLEc;
    ushWarnDelayLongTimerPWARNTOL[ucIdX] = ushLONG_TIMER_INIT_VALUEc;
  }
}

void TimerStopAllPWARNTOL(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    TimerStopPWARNTOL( ucLoop);
  }
}

static void TimerStopPWARNTOL( uint8 ucIdX)
{
  ucLongTimerStatePWARNTOL[ucIdX]      = ucLONG_TIMER_STATE_IDLEc;
  ushWarnDelayLongTimerPWARNTOL[ucIdX] = ushLONG_TIMER_INIT_VALUEc;
}

void TimerInitPWARNTOL(Rte_Instance self)
{
  uint8 ucLoop;
  uint8 ucRet;

  GetDataEE(self, cucLongTimerIdWN, &ushWarnDelayLongTimerPWARNTOL);

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ushWarnDelayLongTimerPWARNTOL[ucLoop] == 0)
    {

      if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc) == 1)
      {
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitAirMassIxWNc) == 1)
      {
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_RUNNINGc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitTonnageIxWNc) == 1)
      {
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_RUNNINGc;
      }else{
        TimerStopPWARNTOL( ucLoop);
      }
    }else if( ushWarnDelayLongTimerPWARNTOL[ucLoop] == ushLONG_TIMER_INIT_VALUEc)
    {

      if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc) == 1)
      {
        ushWarnDelayLongTimerPWARNTOL[ucLoop] = 0;
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitAirMassIxWNc) == 1)
      {
        ushWarnDelayLongTimerPWARNTOL[ucLoop] = 0;
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;
        ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        }
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitTonnageIxWNc) == 1)
      {
        ushWarnDelayLongTimerPWARNTOL[ucLoop] = 0;
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;
        ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        }
      }else{
        TimerStopPWARNTOL( ucLoop);
      }
    }else{

      if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc) == 1)
      {
        ushWarnDelayLongTimerPWARNTOL[ucLoop] = 0;
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitAirMassIxWNc) == 1)
      {
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_RUNNINGc;
      }else if( ucGetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitTonnageIxWNc) == 1)
      {
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_RUNNINGc;
      }else{
        TimerStopPWARNTOL( ucLoop);
      }
    }
  }

  PutWarnBitsToNvmWN(self);
}

void TimerCountPWARNTOL(Rte_Instance self)
{
  uint8 ucLoop;
  uint8 ucRet;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ucLongTimerStatePWARNTOL[ucLoop] == ucLONG_TIMER_STATE_RUNNINGc)
    {
      if( ushWarnDelayLongTimerPWARNTOL[ucLoop] > 0)
      {
        ushWarnDelayLongTimerPWARNTOL[ucLoop]--;
      }else{
        ucLongTimerStatePWARNTOL[ucLoop] = ucLONG_TIMER_STATE_EXPIREDc;

        ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_PwarnTol, ucWarnBitIxWNc);
        }
      }
    }
  }

  PutDataEE(self, cucLongTimerIdWN, &ushWarnDelayLongTimerPWARNTOL, FALSE);

  PutWarnBitsToNvmWN(self);
}

void GetTimerValPWARNTOL( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt)
{
  *ucTimState = ucLongTimerStatePWARNTOL[ucZomPos];
  *ushTimCnt  = ushWarnDelayLongTimerPWARNTOL[ucZomPos];
}

