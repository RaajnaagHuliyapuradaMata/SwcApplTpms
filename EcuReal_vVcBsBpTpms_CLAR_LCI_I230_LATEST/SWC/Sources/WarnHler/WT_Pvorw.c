#include "WnTypePar.h"

#define ucTIMER_STATE_IDLEc      ((uint8) 0)
#define ucTIMER_STATE_RUNNINGc   ((uint8) 1)
#define ucTIMER_STATE_EXPIREDc   ((uint8) 2)
#define ushTIMER_INIT_VALUEc     ((uint16) 0xFFFFu)

static uint8 ucTimerStatePVORW[cAnzRad] = { ucTIMER_STATE_IDLEc, ucTIMER_STATE_IDLEc, ucTIMER_STATE_IDLEc, ucTIMER_STATE_IDLEc };
static uint16 ushTimerCounterSecPVORW[cAnzRad] = { ushTIMER_INIT_VALUEc, ushTIMER_INIT_VALUEc, ushTIMER_INIT_VALUEc, ushTIMER_INIT_VALUEc };

static void TimerStartPVORW( uint8 ucIdX, uint8 ucDelayInMin);
static void TimerStopPVORW( uint8 ucIdX);

uint8 bWT_Pvorw( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8 ucWarnSetThres, ucWarnResetThres;
  uint8 ucPminThresTol, ucPvorwCThresTol, ucPvorwNCThres, ucPwarnNCThres;
  uint8 ucPtolNC, ucPtolC, ucRet;
  ucPtolNC = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThNCTolCOD;
  ucPtolC  = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThCTolCOD;
  ucPminThresTol    = ucGetPMinCS() + ucPtolNC;
  ucPvorwNCThres    = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucPwThresNCfactorCOD) * ptLWD->tSD.ucPSoll) + 50) / 100);
  ucPwarnNCThres    = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucAlThresNCfactorCOD) * ptLWD->tSD.ucPSoll) + 50) / 100);

  if( ucPwarnNCThres > ucPminThresTol){
    if( ucPvorwNCThres < (ucPwarnNCThres + cucMinDistPvorw)){
      ucPvorwNCThres = (ucPwarnNCThres + cucMinDistPvorw);
    }
  }else{
    if( ucPvorwNCThres < (ucPminThresTol + cucMinDistPvorw)){
      ucPvorwNCThres = (ucPminThresTol + cucMinDistPvorw);
    }
  }

  ucPvorwCThresTol  = (uint8) ((uint16) (((100 - ptLWD->tCOD.ucPwThresCfactorCOD) * ptLWD->tSD.ucPinitTreifen) + 50) / 100) + ucPtolC;

  if( ucPvorwCThresTol > ucPvorwNCThres){
    ucWarnSetThres = ucPvorwCThresTol;
  }else{
    ucWarnSetThres = ucPvorwNCThres;
  }

  if( (ucWarnCfg & ucCtryMaskc) == ucUSCodec){
    if( (boolean) ptLWD->tCOD.ucSaturierungAktivCOD == TRUE){
      if( ucWarnSetThres > (ptLWD->tSD.ucPSoll - ucPtolNC)){
        ucWarnSetThres = (ptLWD->tSD.ucPSoll - ucPtolNC);
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
      TimerStopPVORW( ptLWD->tHFD.ucId);

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
    if( ptLWD->tHFD.ucP < ucWarnSetThres){
      if( ptLWD->tHFD.ucP <= ucPvorwNCThres){
        if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc) == 1){
          ClearWarnAttrBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          if( ucRet == 0){
            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          }
        }else{
          if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc) == 0)
          {
            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
            if( ucRet == 1)
            {

              TimerStartPVORW( ptLWD->tHFD.ucId, ptLWD->tCOD.ucPrewarnDelayMinCOD);
            }
          }
        }
        ucRet = 0;
      }else{

        if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc) == 1)
        {
          ClearWarnAttrBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);

          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
          if( ucRet == 0)
          {

            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
          }
        }else{
          if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc) == 0)
          {
            ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
            if( ucRet == 1)
            {

              TimerStartPVORW( ptLWD->tHFD.ucId, ptLWD->tCOD.ucPrewarnDelayMinCOD);
            }
          }
        }
        ucRet = 0;
      }
    }else if( ptLWD->tHFD.ucP > ucWarnSetThres)
    {

      TimerStopPVORW( ptLWD->tHFD.ucId);
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }else{

      ucRet = 0;
    }
  }

  return ucRet;
}

static void TimerStartPVORW( uint8 ucIdX, uint8 ucDelayInMin)
{
  ucTimerStatePVORW[ucIdX]       = ucTIMER_STATE_RUNNINGc;
  ushTimerCounterSecPVORW[ucIdX] = (uint16) ucDelayInMin * 600;
}

void TimerStopAllPVORW(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    TimerStopPVORW( ucLoop);
  }
}

static void TimerStopPVORW( uint8 ucIdX)
{
  ucTimerStatePVORW[ucIdX]       = ucTIMER_STATE_IDLEc;
  ushTimerCounterSecPVORW[ucIdX] = ushTIMER_INIT_VALUEc;
}

void TimerInitPVORW(Rte_Instance self)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ucGetWarnBitWN( ucLoop, cucIX_Pvorw, ucWarnBitIxWNc) == 1)
    {
      ushTimerCounterSecPVORW[ucLoop] = 0;
      ucTimerStatePVORW[ucLoop]       = ucTIMER_STATE_EXPIREDc;
    }else if( ucGetWarnBitWN( ucLoop, cucIX_Pvorw, ucWarnBitAirMassIxWNc) == 1)
    {
      ClearWarnAttrBitWN( ucLoop, cucIX_Pvorw, ucWarnBitAirMassIxWNc);
      TimerStopPVORW( ucLoop);
    }else if( ucGetWarnBitWN( ucLoop, cucIX_Pvorw, ucWarnBitTonnageIxWNc) == 1)
    {
      ClearWarnAttrBitWN( ucLoop, cucIX_Pvorw, ucWarnBitTonnageIxWNc);
      TimerStopPVORW( ucLoop);
    }else{
      TimerStopPVORW( ucLoop);
    }
  }

  PutWarnBitsToNvmWN(self);
}

void TimerCountPVORW(Rte_Instance self)
{
  uint8 ucLoop;
  uint8 ucRet;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ucTimerStatePVORW[ucLoop] == ucTIMER_STATE_RUNNINGc)
    {
      if( ushTimerCounterSecPVORW[ucLoop] > 0)
      {
        ushTimerCounterSecPVORW[ucLoop]--;
      }else{
        ucTimerStatePVORW[ucLoop] = ucTIMER_STATE_EXPIREDc;

        ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pvorw, ucWarnBitIxWNc);
        if( ucRet == 0)
        {

          ucRet = ucSetWarnBitWN( ucLoop, cucIX_Pvorw, ucWarnBitIxWNc);
        }
      }
    }
  }

  PutWarnBitsToNvmWN(self);
}

void GetTimerValPVORW( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt)
{
  *ucTimState = ucTimerStatePVORW[ucZomPos];
  *ushTimCnt = ushTimerCounterSecPVORW[ucZomPos];
}

