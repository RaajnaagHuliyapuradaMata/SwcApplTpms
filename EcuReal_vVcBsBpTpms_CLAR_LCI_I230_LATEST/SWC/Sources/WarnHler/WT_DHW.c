#include "WnTypePar.h"

#define ushTimerInitValDHWc ( (uint16)   0)
#define ushTimeGradDHWc     ( (uint16) 250)
#define ucDifDHWc           ( (uint8)    3)

static uint8  aucReferencePressureDHW[cAnzRad];
static uint8  aucLastPressureDHW[cAnzRad];
static uint16 ushTimerCountLatchDHW[cAnzRad];
static uint16 ushTimerCountDHW[cAnzRad];
static void SetPresRefDHW( uint8 ucIdx);
static void TimerStopDHW( uint8 ucIdX);

uint8 bWT_DHW( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8  ucWarnSetThres, ucWarnResetThres, ucRet = 0;
  ucWarnCfg = ucWarnCfg;
  if( ptLWD->tSD.ucPinitTreifen < ptLWD->tSD.ucPSoll){
    ucWarnResetThres = ptLWD->tSD.ucPSoll - ptLWD->tSD.ucPanneClearHyst;
  }else{
    ucWarnResetThres = ptLWD->tSD.ucPinitTreifen - ptLWD->tSD.ucPanneClearHyst;
  }
  if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc) == 0){
    if( (ptLWD->tHFD.ucP >= ptLWD->tCOD.ucPanneThresCOD) && (ptLWD->tHFD.ucP < ucWarnResetThres)){
      if( aucReferencePressureDHW[ptLWD->tHFD.ucId] == cInvalidREpressure){
        aucReferencePressureDHW[ptLWD->tHFD.ucId] = ptLWD->tHFD.ucP;
        ushTimerCountDHW[ptLWD->tHFD.ucId] = ushTimeGradDHWc;
      }else{
        if( (ptLWD->tHFD.ucP >= aucReferencePressureDHW[ptLWD->tHFD.ucId]) || (ushTimerCountDHW[ptLWD->tHFD.ucId] == ushTimerInitValDHWc)){
          aucReferencePressureDHW[ptLWD->tHFD.ucId] = ptLWD->tHFD.ucP;
          ushTimerCountDHW[ptLWD->tHFD.ucId] = ushTimeGradDHWc;
        }
      }
      aucLastPressureDHW[ptLWD->tHFD.ucId] = ptLWD->tHFD.ucP;
      ushTimerCountLatchDHW[ptLWD->tHFD.ucId] = ushTimerCountDHW[ptLWD->tHFD.ucId];
    }else{
      ushTimerCountDHW[ptLWD->tHFD.ucId]      = ushTimerInitValDHWc;
      ushTimerCountLatchDHW[ptLWD->tHFD.ucId] = ushTimerInitValDHWc;
    }
    ucRet = 0;
  }else{
    ushTimerCountDHW[ptLWD->tHFD.ucId]      = ushTimerInitValDHWc;
    ushTimerCountLatchDHW[ptLWD->tHFD.ucId] = ushTimerInitValDHWc;
    ucRet = ucWarnBitTonnageIxWNc;
    if( ptLWD->tHFD.ucP > ucWarnResetThres){
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }
  }
  if( aucReferencePressureDHW[ptLWD->tHFD.ucId] >= ucDifDHWc){
    ucWarnSetThres = aucReferencePressureDHW[ptLWD->tHFD.ucId] - ucDifDHWc;
  }
  else{
    ucWarnSetThres = 0;
  }
  ptLWD->ucCurWarnSetThres   = ucWarnSetThres;
  ptLWD->ucCurWarnResetThres = ucWarnResetThres;
  return ucRet;
}

void ResetPresRefDHW( uint8 ucIdx){
  uint8 ucLoop;
  if( ucIdx < cAnzRad){
    aucReferencePressureDHW[ucIdx] = cInvalidREpressure;
    aucLastPressureDHW[ucIdx] = cInvalidREpressure;
    ushTimerCountDHW[ucIdx] = ushTimerInitValDHWc;
    ushTimerCountLatchDHW[ucIdx] = ushTimerInitValDHWc;
  }
  else{
    for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      aucReferencePressureDHW[ucLoop] = cInvalidREpressure;
      aucLastPressureDHW[ucLoop] = cInvalidREpressure;
      ushTimerCountDHW[ucLoop] = ushTimerInitValDHWc;
      ushTimerCountLatchDHW[ucLoop] = ushTimerInitValDHWc;
    }
  }
}

static void SetPresRefDHW( uint8 ucIdx){
  aucReferencePressureDHW[ucIdx] = aucLastPressureDHW[ucIdx];
  aucLastPressureDHW[ucIdx] = cInvalidREpressure;
  if( ushTimerCountLatchDHW[ucIdx] < ushTimeGradDHWc){
    ushTimerCountDHW[ucIdx] = (ushTimeGradDHWc - ushTimerCountLatchDHW[ucIdx]);
  }
  else{
    ushTimerCountDHW[ucIdx] = ushTimeGradDHWc;
  }
}

void TimerStopAllDHW(void){
  uint8 ucLoop;
  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    TimerStopDHW( ucLoop);
  }
}

static void TimerStopDHW( uint8 ucIdX){
  ushTimerCountDHW[ucIdX] = ushTimerInitValDHWc;
  ushTimerCountLatchDHW[ucIdX] = ushTimerInitValDHWc;
}

void TimerInitDHW(Rte_Instance self){
  uint8 ucLoop;
  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    TimerStopDHW( ucLoop);
  }
  PutWarnBitsToNvmWN(self);
}

void TimerCountDHW(Rte_Instance self){
  uint8 ucLoop;
  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    if( ushTimerCountDHW[ucLoop] == ushTimerInitValDHWc){
    }
    else if( ushTimerCountDHW[ucLoop] == 1){
      if( aucLastPressureDHW[ucLoop] == cInvalidREpressure){
        ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitTonnageIxWNc);
        ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitAirMassIxWNc);
        ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitIxWNc);
        ResetPresRefDHW( ucLoop);
      }
      else{
        if( (aucReferencePressureDHW[ucLoop] - aucLastPressureDHW[ucLoop]) >= ucDifDHWc){
          if( ucGetWarnBitWN( ucLoop, cucIX_DHW, ucWarnBitIxWNc) == 0){
            ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitAirMassIxWNc);
            (void) ucSetWarnBitWN( ucLoop, cucIX_DHW, ucWarnBitTonnageIxWNc);
            (void) ucSetWarnBitWN( ucLoop, cucIX_DHW, ucWarnBitIxWNc);
            if( (ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitTonnageIxWNc) + ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitAirMassIxWNc)) > 0){
              ResetPresRefDHW( ucLoop);
            }
            else{
              SetPresRefDHW( ucLoop);
            }
          }
        }
        else{
          if( ucGetWarnBitWN( ucLoop, cucIX_DHW, ucWarnBitIxWNc) > 0){
            if( (ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitTonnageIxWNc) + ucGetWarnBitWN( ucLoop, cucIX_Pwarn, ucWarnBitAirMassIxWNc)) > 0){
              ResetPresRefDHW( ucLoop);
            }
            else{
              ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitTonnageIxWNc);
              ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitAirMassIxWNc);
              ClearWarnAttrBitWN( ucLoop, cucIX_DHW, ucWarnBitIxWNc);
              SetPresRefDHW( ucLoop);
            }
          }
          else{
            SetPresRefDHW( ucLoop);
          }
        }
      }
    }
    else{
      ushTimerCountDHW[ucLoop]--;
    }
  }
  PutWarnBitsToNvmWN(self);
}

void GetTimerValDHW( uint8 ucZomPos, uint8* pucRefPres, uint8* pucLastPres, uint16* pushTimCnt, uint16* pushTimCountLatch){
  *pucRefPres         = aucReferencePressureDHW[ucZomPos];
  *pucLastPres        = aucLastPressureDHW[ucZomPos];
  *pushTimCnt         = ushTimerCountDHW[ucZomPos];
  *pushTimCountLatch  = ushTimerCountLatchDHW[ucZomPos];
}
