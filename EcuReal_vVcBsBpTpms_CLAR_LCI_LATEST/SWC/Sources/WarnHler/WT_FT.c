#include "WnTypePar.h"

uint8 bWT_FT( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8 ucWarnSetThres, ucWarnResetThres, ucPtol, ucRet;
  ucWarnCfg = ucWarnCfg;
  ucPtol = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThNCTolCOD;
  ucWarnSetThres   = ucThresFTc;
  ucWarnResetThres = ucGetPMinCS() + ucPtol;
  ptLWD->ucCurWarnSetThres   = ucWarnSetThres;
  ptLWD->ucCurWarnResetThres = ucWarnResetThres;
  if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc) == 1){
    if( ptLWD->tHFD.ucP > ucWarnResetThres){
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }else{
      ucRet = ucWarnBitTonnageIxWNc;
    }
  }else{
    if( ptLWD->tHFD.ucP < ucWarnSetThres){
      ClearWarnAttrBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitAirMassIxWNc);
      ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
      if( ucRet == 1){
        (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
        ucRet = ucWarnBitTonnageIxWNc;
      }else{
        ucRet = 0;
      }
    }else{
      ClearWarnBitWN( ptLWD->tHFD.ucId, ucWtIx);
      ucRet = 0;
    }
  }
  return ucRet;
}
