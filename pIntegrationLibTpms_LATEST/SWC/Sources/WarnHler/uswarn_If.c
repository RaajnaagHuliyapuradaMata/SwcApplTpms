#include "uswarn_ifx.h"
#include "WAllocX.h"
#include "InitializationX.h"
#include "EeCommonBlockX.h"
#include "CodingDataX.h"
#include "USCS.h"

void InitUSWIF( Rte_Instance self){
  uint8 ucLoop;
  uint8 aucData[12];
  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    aucData[ucLoop] = ucGetWPOfColWAL( ucLoop);
    if( aucData[ucLoop] > cAnzRad){
      aucData[ucLoop] = cRadPosUndef;
    }
  }
  InitUSWAlgo( self, aucData);
  if( ucGetCRdciTpmsMarketCD() == cMARKET_US){
    aucData[0] = (uint8) 0x01;
    aucData[1] = (uint8) 0x00;
    aucData[2] = (uint8) 0x01;
  }else{
    aucData[0] = (uint8) 0x02;
    aucData[1] = (uint8) 0x00;
    aucData[2] = (uint8) 0x02;
  }

  (void) ucUSWAlgoParaWN( self, ucWrParaBytec, aucData);
  (void) ucCfgPSollMinUSWIF( self);
  (void) ucCfgPMinUSWIF( self, ucGetPWarnMinDM());

  aucData[0]  = ucGetCRdciUiwThCCD();
  aucData[1]  = ucGetCRdciUiwThNcCD();
  aucData[2]  = ucGetCRdciUiaThCCD();
  aucData[3]  = ucGetCRdciUiaThNcCD();
  aucData[4]  = ucGetCRdciTimeoutPrewarnCD();
  aucData[5]  = ucGetCRdciPanneThCD();
  aucData[6]  = ucGetCRdciDpToIPminCD();
  aucData[7]  = ucGetCRdciShortHoldTimeCD();
  aucData[8]  = ucGetCRdciLongHoldTimeCD();
  aucData[9]  = (uint8) ((uint16) ((ucGetCRdciThCTolCD()  * 100) + 125) / 250);
  aucData[10] = (uint8) ((uint16) ((ucGetCRdciThNCTolCD() * 100) + 125) / 250);

  aucData[11] = (uint8) bGetCRdciMaxThresholdCD();

  (void) ucUSWAlgoParaWN( self, ucWrParaThresc, aucData);

  aucData[0] = ucRdParaSubSetc;
  aucData[1] = 0;
  aucData[2] = 0;
  (void) ucWarnManagerWN( self, ucDiagServicec, aucData);
}

uint8 ucCfgReInitSingleUSWIF( Rte_Instance self, uint8 ucPressure, sint8 scTemperature, uint8 ucZomPos, uint8 ucWheelPos)
{
  uint8 ucResult, aucDiagService[5];

  aucDiagService[0] = ucCfgReInitSinglec;
  aucDiagService[1] = ucZomPos;
  aucDiagService[2] = ucPressure;
  aucDiagService[3] = (uint8) scTemperature;
  aucDiagService[4] = ucWheelPos;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = cRetError;
  }else{
    ucResult = cRetOk;
  }

  return( ucResult);
}

uint8 ucCfgTReifenSingleUSWIF( Rte_Instance self, sint8 scTemperature, uint8 ucZomPos)
{
  uint8 ucResult, aucDiagService[3];

  aucDiagService[0] = ucCfgTReifenSinglec;
  aucDiagService[1] = ucZomPos;
  aucDiagService[2] = (uint8) scTemperature;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = 0xff;
  }else{
    ucResult = 0;
  }

  return( ucResult);
}

uint8 ucGetPTSollUSWIF( Rte_Instance self, uint8* pucPSollKalt, sint8* pscTSollKalt, uint8* pucPSollWarm, sint8* pscTSollWarm, uint16* pushMSoll, uint8* pucEnvP, uint8 ucZomPos)
{
  uint8 ucResult, aucDiagService[7];

  aucDiagService[0] = ucGetPTSollc;
  aucDiagService[1] = ucZomPos;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    *pucPSollKalt  = cInvalidREpressure;
    *pscTSollKalt  = cInvalidREtemperature;
    *pucPSollWarm  = cInvalidREpressure;
    *pscTSollWarm  = cInvalidREtemperature;
    *pushMSoll     = 0;
    *pucEnvP       = 40;

    ucResult       = cRetError;
  }else{
    *pucPSollKalt  = aucDiagService[0];
    *pscTSollKalt  = (sint8)  aucDiagService[1];
    *pucPSollWarm  = aucDiagService[2];
    *pscTSollWarm  = (sint8)  aucDiagService[3];
    *pushMSoll     = (uint16) (aucDiagService[4] + ((uint16) aucDiagService[5] << 8));
    *pucEnvP       = aucDiagService[6];

    ucResult       = cRetOk;
  }

  return( ucResult);
}

uint8 ucGetWpPTSollUSWIF( uint8* pucPSoll, sint8* pscTSoll, uint8 ucWheelPos)
{
  uint8 ucResult;

  if( ucWheelPos < cAnzRad)
  {
    *pucPSoll = ucGetPSollCS( cAnzRad, ucWheelPos);
    *pscTSoll = scGetTSollCS( cAnzRad, ucWheelPos);

    ucResult  = cRetOk;
  }else{
    *pucPSoll = cInvalidREpressure;
    *pscTSoll = cInvalidREtemperature;

    ucResult  = cRetError;
  }

  return( ucResult);
}

uint8 ucSetPTSollAfterWpChangedUSWIF( Rte_Instance self, uint8 ucHistSlot, uint8 ucNewWheelPos)
{
  uint8 ucResult;
  uint8 ucPres;
  sint8 scTemp;
  uint8 ucPminFzg;
  sint8 scTamb;

  if( (ucHistSlot < cAnzRad) && (ucNewWheelPos < cAnzRad))
  {
    if( ucGetWpPTSollUSWIF( &ucPres, &scTemp, ucNewWheelPos) == cRetOk)
    {

      ucPminFzg = ucGetPminFzgDM();
      scTamb = GETscTAmbValEE( self);

      ucResult = ucCfgReInitSingleUSWIF( self, ucPminFzg, scTamb, ucHistSlot, cRadPosUndef);
      ucResult |= ucCfgReInitSingleUSWIF( self, ucPres, scTemp, ucHistSlot, cRadPosUndef);
    }else{
      ucResult  = cRetError;
    }
  }else{
    ucResult  = cRetError;
  }

  return ucResult;
}

uint8 ucCfgPMinUSWIF( Rte_Instance self, uint8 ucPMin)
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucCfgPMinc;
  aucDiagService[1] = ucPMin;
  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = 0xff;
  }else{
    ucResult = 0;
  }
  return( ucResult);
}

uint8 ucCfgPSollMinUSWIF( Rte_Instance self)
{
  uint8 ucLoop, ucWheelPos, ucResult, aucDiagService[5];

  aucDiagService[0] = ucCfgPSollMinc;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ucWheelPos = ucGetWPOfColWAL( ucLoop);
    if( ucWheelPos == cAnzRad)
    {
      aucDiagService[1 + ucLoop] = ucGetPminFzgDM();
    }else{
      if( (ucWheelPos == cRadPosVL) || (ucWheelPos == cRadPosVR))
      {
        aucDiagService[1 + ucLoop] = ucGetCRdciMinRcpFaCD();
      }else{
        aucDiagService[1 + ucLoop] = ucGetCRdciMinRcpRaCD();
      }
    }
  }

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = 0xff;
  }else{
    ucResult = 0;
  }
  return( ucResult);
}

uint8 ResetWarnVectorUSWIF( Rte_Instance self, uint8 ucZomPos)
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucResetWarnVectorc;
  aucDiagService[1] = ucZomPos;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = 0xff;
  }else{
    ucResult = 0;
  }

  return( ucResult);
}

uint8 PorInitUSWIF( Rte_Instance self)
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = 0;
  aucDiagService[1] = 0;

  if( ucTPMSMsgManagerTM( self, ucPorInitc, aucDiagService) == 0x00)
  {
    ucResult = 0;
  }else{
    ucResult = 0xff;
  }

  return( ucResult);
}

uint8 NewPositionsUSWIF( Rte_Instance self)
{
  uint8 i, ucResult, aucDiagService[5];

  aucDiagService[0] = ucNewPositionsc;

  for( i = 0; i < cAnzRad; i++)
  {
    ucResult = ucGetWPOfColWAL( i);
    if( ucResult > cAnzRad)
    {
      aucDiagService[i + 1] = cRadPosUndef;
    }else{
      aucDiagService[i + 1] = ucResult;
    }
  }

  if( ucTPMSMsgManagerTM( self, ucDiagServicec, aucDiagService) == 0x00)
  {
    ucResult = cRetOk;
  }else{
    ucResult = cRetError;
  }

  return( ucResult);
}

uint8 ClearPosUSWIF( Rte_Instance self)
{
  uint8 ucResult, aucDiagService[1];

  aucDiagService[0] = ucClearPosc;

  if(ucTPMSMsgManagerTM( self, ucDiagServicec, aucDiagService) == 0x00)
  {
    ucResult = 0;
  }else{
    ucResult = 0xff;
  }

  return( ucResult);
}

void ResetWarningsUSWIF( Rte_Instance self){
  (void) ResetWarnVectorUSWIF( self, cAnzRad);
  (void) TimerStopUSWIF( self);
  (void) PorInitUSWIF( self);
  (void) NewPositionsUSWIF( self);
  (void)ucCfgPSollMinUSWIF( self);
}

uint8 TimerStopUSWIF( Rte_Instance self)
{
  uint8 ucResult, aucDiagService[1];

  aucDiagService[0] = ucTimerStopc;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    ucResult = 0xff;
  }else{
    ucResult = 0;
  }

  return( ucResult);
}

uint8 ucSetPminFzgAsSetPressureUSWIF( Rte_Instance self)
{
  uint8 ucRet = cRetOk;
  uint8 ucLoop;
  uint8 ucMinPres;
  sint8 scTAmbVal;

  ucMinPres = ucGetPminFzgDM();
  scTAmbVal = GETscTAmbValEE( self);

  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ucRet = ucCfgReInitSingleUSWIF( self, ucMinPres, scTAmbVal, ucLoop, cRadPosUndef);
  }

  return ucRet;
}

uint8 ucGetWarnVectorIdExtIFH( Rte_Instance self, uint8* pucWarnVectors)
{
  uint8 i, ucResult, aucDiagService[cAnzRad];
  uint8 *pucDiagService;

  aucDiagService[0] = ucGetWarnVectorsIdc;

  if( ucTPMSMsgManagerTM( self, ucDiagServicec, aucDiagService) == (uint8) 0x00)
  {
    pucDiagService = &aucDiagService[0];

    for( i = 0; i < cAnzRad; i++)
    {
      pucWarnVectors[i] = pucDiagService[i];
    }

    ucResult = (uint8) 0x00;
  }else{
    ucResult = 0xFF;
  }

  return( ucResult);
}

uint8 ucGetWarnBitIdIntIFH( Rte_Instance self, uint8* pucWarnVectors)
{
  uint8 ucLoop, ucResult, aucDiagService[6];

  aucDiagService[0] = ucGetWarnVectorsc;
  aucDiagService[1] = ucWarnBitIxWNc;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == (uint8) 0x00)
  {
    for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
    {
      pucWarnVectors[ucLoop] = aucDiagService[ucLoop + 2];
    }

    ucResult = (uint8) 0x00;
  }else{
    ucResult = 0xFF;
  }

  return( ucResult);
}

uint8 ucGetWarnBitTonnageIdIntIFH( Rte_Instance self, uint8* pucWarnVectors)
{
  uint8 ucLoop, ucResult, aucDiagService[6];

  aucDiagService[0] = ucGetWarnVectorsc;
  aucDiagService[1] = ucWarnBitTonnageIxWNc;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == (uint8) 0x00)
  {
    for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
    {
      pucWarnVectors[ucLoop] = aucDiagService[ucLoop + 2];
    }

    ucResult = (uint8) 0x00;
  }else{
    ucResult = 0xFF;
  }

  return( ucResult);
}

uint8 ucGetWarnBitAirMassIdIntIFH( Rte_Instance self, uint8* pucWarnVectors)
{
  uint8 ucLoop, ucResult, aucDiagService[6];

  aucDiagService[0] = ucGetWarnVectorsc;
  aucDiagService[1] = ucWarnBitAirMassIxWNc;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == (uint8) 0x00)
  {
    for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
    {
      pucWarnVectors[ucLoop] = aucDiagService[ucLoop + 2];
    }

    ucResult = (uint8) 0x00;
  }else{
    ucResult = 0xFF;
  }

  return( ucResult);
}

uint8 ucGetWThresUSWIF( Rte_Instance self, uint8 ucWarnType, uint8* pucSetThres, uint8* pucResetThres)
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucGetWThresc;
  aucDiagService[1] = ucWarnType;

  if( ucWarnManagerWN( self, ucDiagServicec, aucDiagService) == 0xff)
  {
    *pucSetThres = 0x00;
    *pucResetThres = 0x00;

    ucResult = 0xff;
  }else{
    *pucSetThres = aucDiagService[0];
    *pucResetThres = aucDiagService[1];

    ucResult = 0;
  }
  return( ucResult);
}

uint8 GetDropIsoCodVal(void)
{
  return(ucGetCRdciTrefSeasAdjConfigCD(3));
}

