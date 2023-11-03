#include "uswarn.h"
#include "USCS.h"
#include "eeiface.h"
#include "USWTime.h"

#define ucClearIdWarningc ((uint8) 0x01)
#define ucClearWarningc   ((uint8) 0x10)
#define cMaiden           ((uint8) 0x00)
#define cInitSingleId     ((uint8) 0x03)

static const uint8 ucBitNoc[ucMaxWarnTypeWNc] = {
  1, 2, 4, 8, 16, 32, 64, 128
};

static uint8 ucWarnStateWN;
static WarnBitArrayType aucWarnBitsWN;
static uint8 aucFrikBitWN[cAnzRad];
static uint8 ucWarnSetThres[ucMaxWarnTypeWNc]   = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8 ucWarnResetThres[ucMaxWarnTypeWNc] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static boolean  bFirstTelWN[cAnzRad] = { TRUE, TRUE, TRUE, TRUE };

uint8 ucSetWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWtAttr)
{
  const uint8 aucWTFreakEnable[] = cWT_FreakEnable_map;
  uint8 ucRet = 0;

  if( (ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < cAnzRad) && (ucWtAttr < ucWarnBitArraySizeWNc))
  {
    if( bGetX8BitWM( &aucWarnBitsWN[ucIdX][ucWtAttr], ucWarnTypeIx) == 0)
    {
      if( (bGetX8BitWM( &aucFrikBitWN[ucIdX], ucWarnTypeIx) == 0) && (aucWTFreakEnable[ucWarnTypeIx] == (uint8) 1))
      {
        SetX8BitWM( &aucFrikBitWN[ucIdX], ucWarnTypeIx);
        ucRet = (uint8) 0;
      }else{
        SetX8BitWM( &aucWarnBitsWN[ucIdX][ucWtAttr], ucWarnTypeIx);
        ucRet = (uint8) 1;
      }
    }else{

      ucRet = (uint8) 1;
    }
  }else{
    ucRet = (uint8) 0xff;
  }

  return ucRet;
}

void ClearWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx)
{
  uint8 ucLoop;

  if( (ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < cAnzRad))
  {
    ClearX8BitWM( &aucFrikBitWN[ucIdX], ucWarnTypeIx);

    for( ucLoop = 0; ucLoop < ucWarnBitArraySizeWNc; ucLoop++)
    {
      ClearX8BitWM( &aucWarnBitsWN[ucIdX][ucLoop], ucWarnTypeIx);
    }
  }
}

uint8  ucGetWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWtAttr)
{
  uint8 ucRet = 0;

  if( (ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < cAnzRad) && (ucWtAttr < ucWarnBitArraySizeWNc))
  {
    ucRet = bGetX8BitWM( &aucWarnBitsWN[ucIdX][ucWtAttr], ucWarnTypeIx);
  }else{
    ucRet = (uint8) 0xff;
  }

  return ucRet;
}

static uint8 bGetX8BitWM( const uint8* ptByte, uint8 ucBitNo)
{
  uint8 ucRet;

  if( (*ptByte & ucBitNoc[ucBitNo]) == ucBitNoc[ucBitNo])
  {
    ucRet = 1;
  }else{
    ucRet = 0;
  }

  return ucRet;
}

static void ClearX8BitWM( uint8* ptByte, uint8 ucBitNo)
{
  if((*ptByte & ucBitNoc[ucBitNo]) > 0)
  {
    *ptByte &= (uint8) ~ucBitNoc[ucBitNo];
  }
}

static void SetX8BitWM( uint8* ptByte, uint8 ucBitNo)
{
  if( (*ptByte & ucBitNoc[ucBitNo]) == 0)
  {
    *ptByte |= ucBitNoc[ucBitNo];
  }
}

uint8 ucGetUSEUCode(void)
{
  uint8 i;

  if((ucWarnStateWN & ucCtryMaskc) == ucUSCodec)
  {
    i = cIxPMinUS;
  }else{
    i = cIxPMinEU;
  }

  return (i);
}

uint8 ucPfT( uint16 ushM, sint8 scT, uint8 ucPamb)
{
  uint32 ulHelp;

  ulHelp  = ((uint32) ushM * 10);
  ulHelp *= (uint16) ((sint16) scT + (sint16) ush273Kelvinc);
  ulHelp /= ushGSFc;
  ulHelp += 5;
  ulHelp /= 10;

  if( ulHelp > ucPamb)
  {
    ulHelp -= ucPamb;

    if(ulHelp > 0x00FF)
    {
      ulHelp = 0x00FF;
    }
  }else{
    ulHelp = 0;
  }

  return( (uint8) ulHelp);
}

uint16 ushMIso( uint8 ucP, sint8 scT, uint8 ucPamb)
{
  uint32 ulHelp;

  ulHelp = ((uint32) ucP + ucPamb);

  if( ulHelp != 0)
  {
    ulHelp *= (uint32) (ushGSFc * 10);
    ulHelp /= (uint16) ((sint16) scT + (sint16) ush273Kelvinc);
    ulHelp += 5;
    ulHelp /= 10;
  }

  return( (uint16) ulHelp);
}

static void ClearWarntypeBit( uint8 ucWType, uint8 ucId, uint8 ucMode)
{
  void (*const fpt2WnTypeCallbackClearWnBit[]) ( uint8) = cWT_WNcallbackClearWnBit_map;
  uint8 ucLoop, ucWTCount;

  if( (ucMode & ucClearWarningc) == ucClearWarningc)
  {
    for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
    {
      ClearWarnBitWN( ucLoop, ucWType);

      for ( ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++)
      {
        if( fpt2WnTypeCallbackClearWnBit[ucWTCount] != NULL)
        {
          (void) fpt2WnTypeCallbackClearWnBit[ucWTCount] ( ucLoop);
        }
      }
    }
  }

  if( (ucMode & ucClearIdWarningc) == ucClearIdWarningc)
  {
    ClearWarnBitWN( ucId, ucWType);

    for ( ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++)
    {
      if( fpt2WnTypeCallbackClearWnBit[ucWTCount] != NULL)
      {
        (void) fpt2WnTypeCallbackClearWnBit[ucWTCount] ( ucId);
      }
    }
  }

  return;
}

void ClearWarnAttrBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWarnAttr)
{
  if( (ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < cAnzRad) && (ucWarnAttr < ucWarnBitArraySizeWNc))
  {
    ClearX8BitWM( &aucWarnBitsWN[ucIdX][ucWarnAttr], ucWarnTypeIx);
  }
}

static void InitWN( uint8 ucInit, uint8 ucIdX)
{
  uint8 ucLoop;

  switch ( ucInit)
  {
    case cMaiden:

      ucIdX = cAnzRad;
      for ( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
      {
        ClearWarntypeBit( ucLoop, ucIdX, ((ucWarnStateWN & ucCtryMaskc) | ucClearWarningc));
      }

    break;

    case cInitialized:

      ucIdX = cAnzRad;
      for ( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
      {
        ClearWarntypeBit( ucLoop, ucIdX, (ucWarnStateWN & ucCtryMaskc));
      }
    break;

    case cInitSingleId:
      if( ucIdX <= cAnzRad)
      {
        for ( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc ; ucLoop++)
        {
          if( ucIdX == cAnzRad)
          {
            ClearWarntypeBit( ucLoop, ucIdX, ucClearWarningc);
        }else{
            ClearWarntypeBit( ucLoop, ucIdX, ucClearIdWarningc);
          }
        }
      }else{

      }
    break;

    default:
    break;
  }
}

static void RdParaSubSet( uint8* pucData)
{

  ((tParaSubSet *) (void *) pucData)->ucParaByte[ucIxWnCfgc] &= (uint8) 0xFC;

  if((ucWarnStateWN & ucCtryMaskc) == ucUSCodec)
  {
    ((tParaSubSet *) (void *) pucData)->ucParaByte[ucIxWnCfgc] |= 0x01;
  }else if((ucWarnStateWN & ucCtryMaskc) == ucEuroCodec)
  {
    ((tParaSubSet *) (void *) pucData)->ucParaByte[ucIxWnCfgc] |=  0x02;
  }else{
  }
}

static void WrParaSubSet( Rte_Instance self, const uint8* pucData)
{
  uint8 ucHelp;

  ucHelp = ((((const tParaSubSet *) (const void *) pucData)->ucParaByte[ucIxWnCfgc] & 0x03) == 1) ? ucUSCodec : ucEuroCodec;

  GetDataEE( self, cucWsIdWN, &ucWarnStateWN);

  if( (ucWarnStateWN & ucCtryMaskc) != (ucHelp & ucCtryMaskc))
  {
    ucWarnStateWN &= (uint8) ~ucCtryMaskc;
    ucWarnStateWN |= (ucCtryMaskc & ucHelp);

    if((ucWarnStateWN & ucCtryMaskc) == ucUSCodec)
    {
      InitCS(cIxPMinUS);
    }else{
      InitCS(cIxPMinEU);
    }

    ucWarnStateWN |= ucHelp;
    InitWN( (uint8) cMaiden, (uint8) 0xFF);
    PutDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN, TRUE);
    ucHelp = ucWarnStateWN | ucClearWarningc;
  }

  if(ucHelp != (ucWarnStateWN & ((uint8) ~cInitialized)))
  {
    PutDataEE( self, cucWsIdWN, &ucWarnStateWN, TRUE);
    PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
  }
}

static uint8 ucGenWNVector( Rte_Instance self, uint8* pucData)
{
  const uint8 aucWnTypec[] = cWT_WNvector_map;
  uint8 (*const fpt2WnType[]) ( tLocalWarnDat *, uint8, uint8) = cAllWT_function;

  tLocalWarnDat tLWD;
  uint8 ucLoop, ucRet = 0, ucResult;

  tLWD.tHFD.ucId           = 0;
  tLWD.ucCurWarnSetThres   = 0;
  tLWD.ucCurWarnResetThres = 0;

  tLWD.tHFD = *((tHFTelDat *) (void *) pucData);

  if( tLWD.tHFD.ucId < cAnzRad)
  {
    tLWD.tCOD.ucPwThresCfactorCOD    = ucPrewarnThresCfactor;
    tLWD.tCOD.ucPwThresNCfactorCOD   = ucPrewarnThresNCfactor;
    tLWD.tCOD.ucAlThresCfactorCOD    = ucAlarmThresCfactor;
    tLWD.tCOD.ucAlThresNCfactorCOD   = ucAlarmThresNCfactor;
    tLWD.tCOD.ucPrewarnDelayMinCOD   = ucPrewarnDelayMin;
    tLWD.tCOD.ucPanneThresCOD        = ucPanneThres;
    tLWD.tCOD.ucShortHoldTimeCOD     = ucShortHoldTime;
    tLWD.tCOD.ucLongHoldTimeCOD      = ucLongHoldTime;
    tLWD.tCOD.ucThCTolCOD            = ucThCTol;
    tLWD.tCOD.ucThNCTolCOD           = ucThNCTol;
    tLWD.tCOD.ucSaturierungAktivCOD  = ucSaturierungAktiv;

    tLWD.tSD.ucPanneClearHyst     = ucDpToIPmin;

    tLWD.tSD.ucPSoll  = ucGetPSollCS( tLWD.tHFD.ucId, cRadPosUndef);
    tLWD.tSD.scTSoll  = scGetTSollCS( tLWD.tHFD.ucId, cRadPosUndef);
    tLWD.tSD.ushMSoll = ushGetMSollCS( tLWD.tHFD.ucId);

    tLWD.bNoFreakNoTimer = bFirstTelWN[tLWD.tHFD.ucId];

    if( tLWD.tHFD.ucEnvP != ucGetPambCS( tLWD.tHFD.ucId))
    {

      (void) ucPutMSollCS( tLWD.tHFD.ucId, ushMIso( ucGetPSollCS( tLWD.tHFD.ucId, cRadPosUndef), scGetTSollCS( tLWD.tHFD.ucId, cRadPosUndef), tLWD.tHFD.ucEnvP));
    }

    (void) ucPutEnvDataCS( tLWD.tHFD.ucId, tLWD.tHFD.ucEnvP, tLWD.tHFD.scTa);

    (void) ucPutPinitTreifenCS( tLWD.tHFD.ucId, tLWD.tHFD.scTWE);
    tLWD.tSD.ucPinitTreifen = ucGetPinitTreifenCS( tLWD.tHFD.ucId);

    PutDataEE( self, cucCdIdWN, &tCDA, FALSE);

    for ( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
    {
      if( fpt2WnType[ucLoop] != NULL)
      {
        ucResult = fpt2WnType[ucLoop]( &tLWD, ucWarnStateWN, ucLoop);

        if( ucResult == 1)
        {
          tLWD.tHFD.ucWarnState |= aucWnTypec[ucLoop];
          tLWD.tHFD.ucWarnAttr  |= aucWnTypec[ucLoop];
        }else if( ucResult == 2)
        {
          tLWD.tHFD.ucWarnState |= aucWnTypec[ucLoop];
          tLWD.tHFD.ucWarnAttr  &= (uint8) (~(uint8) aucWnTypec[ucLoop]);
        }else{

          tLWD.tHFD.ucWarnState &= (uint8) (~(uint8) aucWnTypec[ucLoop]);
          tLWD.tHFD.ucWarnAttr  &= (uint8) (~(uint8) aucWnTypec[ucLoop]);
        }

        ucWarnSetThres[ucLoop]   = tLWD.ucCurWarnSetThres;
        ucWarnResetThres[ucLoop] = tLWD.ucCurWarnResetThres;
      }else{

        ucWarnSetThres[ucLoop]   = 0;
        ucWarnResetThres[ucLoop] = 0;

        tLWD.tHFD.ucWarnState &= (uint8) (~(uint8) aucWnTypec[ucLoop]);
        tLWD.tHFD.ucWarnAttr  &= (uint8) (~(uint8) aucWnTypec[ucLoop]);
      }
    }

    bFirstTelWN[tLWD.tHFD.ucId] = FALSE;

    (*(tHFTelDat *) (void *) pucData).ucWarnState = tLWD.tHFD.ucWarnState;
    (*(tHFTelDat *) (void *) pucData).ucWarnAttr  = tLWD.tHFD.ucWarnAttr;
  }

  return ucRet;
}

uint8 ucWarnManagerWN( Rte_Instance self, uint8 ucAction, uint8* pucData)
{
  uint8 ucRet = 0;

  switch( ucAction)
  {
    case ucFilterActivationc:
      ucRet = ucWarnManager_FilterActivationWM();
    break;

    case ucPorInitc:
      ucRet = ucWarnManager_PorInitWM( self, pucData);
    break;

    case ucComparec :
      ucRet = ucWarnManager_CompareWM( self, pucData);
    break;

    case ucDiagServicec:
      ucRet = ucWarnManagerDsWM( self, pucData);
    break;

    default:
      ucRet = 0xFF;
    break;
  }

  return( ucRet);
}

static uint8 ucWarnManager_FilterActivationWM(void)
{
  uint8 ucLoop;
  uint8 ucRet = 0;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    bFirstTelWN[ucLoop] = FALSE;
  }

  return ucRet;
}

static uint8 ucWarnManager_PorInitWM( Rte_Instance self, const uint8* pucData)
{
  uint8 ucRet = 0;

  GetDataEE( self, cucWsIdWN, &ucWarnStateWN);

  if( (ucWarnStateWN & cInitialized) == cInitialized)
  {

    GetDataEE( self, cucCdIdWN, &tCDA);
    InitWN( cInitialized, (uint8) 0xFF);

    GetDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN);
    ucRet = ucWarnStateWN;
  }else{

    ucWarnStateWN |= pucData[0];

    if( (pucData[0] & ucCtryMaskc) == ucUSCodec)
    {
      InitCS( cIxPMinUS);
    }else{
      InitCS( cIxPMinEU);
    }

    InitWN( cMaiden, (uint8) 0xFF);
    PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
    PutDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN, TRUE);
    ucWarnStateWN |= cInitialized;
    PutDataEE( self, cucWsIdWN, &ucWarnStateWN, TRUE);
    ucRet = ucWarnStateWN;
  }

  return ucRet;
}

static uint8 ucWarnManager_CompareWM( Rte_Instance self, uint8* pucData)
{
  uint8 ucRet = 0;

  GetDataEE( self, cucWsIdWN, &ucWarnStateWN);

  if( (ucWarnStateWN & cInitialized) != cInitialized)
  {
    InitCS( ucPorInitc);
    InitWN( cMaiden, (uint8) 0xFF);

    PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
    ucWarnStateWN |= cInitialized;
    PutDataEE( self, cucWsIdWN, &ucWarnStateWN, TRUE);
  }

  ucRet = ucGenWNVector( self, pucData);

  PutDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN, TRUE);

  return ucRet;
}

static uint8 ucWarnManagerDsWM( Rte_Instance self, uint8* pucData)
{
  uint8 ucRet = 0;

  switch ( pucData[0])
  {
    case ucCfgPMinc:
      ucRet = ucWarnManagerDs_CfgPMinWM( self, &pucData[1]);
    break;

    case ucCfgPSollMinc:
      ucRet = ucWarnManagerDs_CfgPSollMinWM( self, &pucData[1]);
    break;

    case ucCfgReInitSinglec:
      ucRet = ucWarnManagerDs_CfgReInitSingleWM( self, &pucData[1]);
    break;

    case ucCfgTReifenSinglec:
      ucRet = ucWarnManagerDs_CfgTReifenSingleWM( self, &pucData[1]);
    break;

    case ucResetWarnVectorc:
      ucRet = ucWarnManagerDs_ResetWarnVectorWM( self, &pucData[1]);
    break;

    case ucGetWarnVectorsc:
      ucRet = ucWarnManagerDs_GetWarnVectorsWM( &pucData[1]);
    break;

    case ucRdParaSubSetc:
      ucRet = ucWarnManagerDs_RdParaSubSetWM( pucData);
    break;

    case ucWrParaSubSetc:
      ucRet = ucWarnManagerDs_WrParaSubSetWM( self, pucData);
    break;

    case ucGetPTSollc:
      ucRet = ucWarnManagerDs_GetPTSollWM( pucData);
    break;

    case ucGetWThresc:
      ucRet = ucWarnManagerDs_GetWarnThresWM( pucData);
    break;

    case ucTimerStopc:
      ucRet = ucWarnManagerDs_TimerStopWM();
    break;

    default:
      ucRet = 0xff;
    break;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_CfgPMinWM( Rte_Instance self, const uint8* pucData)
{
  uint8 ucTmp, ucRet = 0;

  ucTmp = ucGetUSEUCode();

  if( ucPutPMinCS( pucData[0], ucTmp) > 0)
  {
    PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
  }else{
    ucRet = 0xff;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_CfgPSollMinWM( Rte_Instance self, const uint8* pucData)
{
  uint8 ucLoop, ucMarket, ucRet = 0;

  ucMarket = ucGetUSEUCode();

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    if( ucPutPSollMinCS( ucLoop, pucData[ucLoop], ucMarket) > 0)
    {
      if( ucGetPSollCS( ucLoop, cRadPosUndef) < pucData[ucLoop])
      {
        if( ucPutCalTabVectorCS( ucLoop, pucData[ucLoop], scGetTSollCS( ucLoop, cRadPosUndef), cRadPosUndef) > 0)
        {
          PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
          ucRet = 0;
        }else{
          ucRet = 0xff;
        }
      }else{

        PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
        ucRet = 0;
      }
    }else{
      ucRet = 0xff;
    }
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_CfgReInitSingleWM( Rte_Instance self, const uint8* pucData)
{
  uint8  ucRet = 0;

  if( ucPutCalTabVectorCS( pucData[0], pucData[1], (sint8) pucData[2], pucData[3]) > 0)
  {
    if( ucPutMSollCS( pucData[0], ushMIso( ucGetPSollCS( pucData[0], cRadPosUndef), scGetTSollCS( pucData[0], cRadPosUndef), ucGetPambCS( pucData[0]))) > 0)
    {

      if( ucPutPinitTreifenCS( pucData[0], scGetTreifenCS( pucData[0])) > 0)
      {
        PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
        ucRet = ucWarnStateWN;
      }else{
        ucRet = 0xff;
      }
    }else{
      ucRet = 0xff;
    }
  }else{
    ucRet = 0xff;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_CfgTReifenSingleWM( Rte_Instance self, const uint8* pucData)
{
  uint8  ucRet = 0;

  if( ucPutPinitTreifenCS( pucData[0], (sint8) pucData[1]) > 0)
  {
    PutDataEE( self, cucCdIdWN, &tCDA, TRUE);
  }else{
    ucRet = 0xff;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_ResetWarnVectorWM( Rte_Instance self, const uint8* pucData)
{
  InitWN( cInitSingleId, pucData[0]);
  PutDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN, TRUE);

  return 0;
}

static uint8 ucWarnManagerDs_GetWarnVectorsWM( uint8* pucData)
{
  uint8  ucLoop;

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 1] = aucWarnBitsWN[ucLoop][pucData[0]];
  }

  return 0;
}

static uint8 ucWarnManagerDs_RdParaSubSetWM( uint8* pucData)
{
  RdParaSubSet( pucData);

  return 0;
}

static uint8 ucWarnManagerDs_WrParaSubSetWM( Rte_Instance self, const uint8* pucData)
{
  WrParaSubSet( self, pucData);

  return 0;
}

static uint8 ucWarnManagerDs_GetPTSollWM( uint8* pucData)
{
  uint16 ushM;
  uint8  ucHistId, ucRet = 0;

  ucHistId = pucData[1];

  if( ucHistId < cAnzRad)
  {
    pucData[0] = ucGetPSollCS( ucHistId, cRadPosUndef);
    pucData[1] = (uint8) scGetTSollCS( ucHistId, cRadPosUndef);
    pucData[2] = ucGetPinitTreifenCS( ucHistId);
    pucData[3] = (uint8) scGetTreifenCS( ucHistId);

    ushM = ushGetMSollCS( ucHistId);
    pucData[4] = (uint8) (ushM & 0x00FF);
    pucData[5] = (uint8) ((ushM >> 8) & 0x00FF);

    pucData[6] = ucGetPambCS( ucHistId);

    ucRet = 0;
  }else{
    ucRet = 0xff;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_GetWarnThresWM( uint8* pucData)
{
  uint8 ucWType, ucRet = 0;

  ucWType = pucData[1];
  if( ucWType < ucMaxWarnTypeWNc)
  {
    pucData[0] = ucWarnSetThres[ucWType];
    pucData[1] = ucWarnResetThres[ucWType];
    ucRet = 0;
  }else{
    ucRet = 0xff;
  }

  return ucRet;
}

static uint8 ucWarnManagerDs_TimerStopWM(void)
{
  uint8 ucRet = 0;

  TimerStopWT();

  return ucRet;
}

uint8 ucGetPTolWN( uint8 ucPenv, uint8 ucPre, sint8 scTre)
{
  uint8 ucPtol;

  if( ((uint16) ucPre + ucPenv) > 200)
  {
    ucPtol = 4;
  }else if( scTre < -20)
  {
    ucPtol = 4;
  }else if( scTre < 0)
  {
    ucPtol = 3;
  }else if( scTre < 90)
  {
    ucPtol = 2;
  }else{
    ucPtol = 3;
  }

  return ucPtol;
}

void PutWarnBitsToNvmWN( Rte_Instance self)
{
  PutDataEE( self, cucWarnTypeArrayIdWN, &aucWarnBitsWN, TRUE);
}
