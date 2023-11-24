#include "WnTypePar.h"

uint8 bWT_Pmin( tLocalWarnDat *ptLWD, uint8 ucWarnCfg, uint8 ucWtIx){
  uint8  ucWarnSetThres, ucWarnResetThres, ucPtol, ucRet;
  ucWarnCfg = ucWarnCfg;
  ucPtol = ucGetPTolWN( ptLWD->tHFD.ucEnvP, ptLWD->tHFD.ucP, ptLWD->tHFD.scTWE) + ptLWD->tCOD.ucThNCTolCOD;
  ucWarnSetThres = ucGetPMinCS() + ucPtol;
  if( ptLWD->tSD.ucPinitTreifen < ptLWD->tSD.ucPSoll){
    ucWarnResetThres = ptLWD->tSD.ucPSoll - ptLWD->tSD.ucPanneClearHyst;
  }else{
    ucWarnResetThres = ptLWD->tSD.ucPinitTreifen - ptLWD->tSD.ucPanneClearHyst;
  }
  if( ucWarnSetThres > ucWarnResetThres){
    ucWarnResetThres = ucWarnSetThres;
  }
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
      if( ucGetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc) == 0){
        if( ptLWD->bNoFreakNoTimer == TRUE){
          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          if( ucRet == 0){
            (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          }
          (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
          ucRet = ucWarnBitTonnageIxWNc;
        }else{
          ucRet = ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitTonnageIxWNc);
          if( ucRet == 1){
            (void) ucSetWarnBitWN( ptLWD->tHFD.ucId, ucWtIx, ucWarnBitIxWNc);
            ucRet = ucWarnBitTonnageIxWNc;
          }else{
            ucRet = 0;
          }
        }
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
