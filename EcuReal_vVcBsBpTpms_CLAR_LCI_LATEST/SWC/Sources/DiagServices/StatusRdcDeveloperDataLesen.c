#include "StatusRdcDeveloperDataLesen.h"
#include "DataManagerX.h"
#include "WAllocX.h"
#include "abs_linX.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "State_BzX.h"
#include "State_FzzX.h"
#include "State_ZkX.h"
#include "Walloc_ManagerX.h"
#include "USWarn_IfX.h"
#include "USCS.h"
#include "BreakTireX.h"
#include "InitializationX.h"
#include "NWMonitoringX.h"
#include "WUMonitoringX.h"
#include "CcmX.h"
#include "InfoTyreX.h"
#include "CodingDataX.h"

static uint8 ucDeveloperDataMuxChannelDS = cStatusRdcDeveloperDataLesen_MuxChannelDefValue;

void GetStatusRdcDeveloperDataLesenDS(Rte_Instance self, uint8* pucData)
{
  switch( ucDeveloperDataMuxChannelDS)
  {
  case cStatusRdcDeveloperDataLesen_MuxChannel0:
    GetStatusRdcDevDataLesen_Ch0DS(self, pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel1:
    GetStatusRdcDevDataLesen_Ch1DS(self, pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel2:
    GetStatusRdcDevDataLesen_Ch2DS(self, pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel3:
    GetStatusRdcDevDataLesen_Ch3DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel4:
    GetStatusRdcDevDataLesen_Ch4DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel5:
    GetStatusRdcDevDataLesen_Ch5DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel6:
    GetStatusRdcDevDataLesen_Ch6DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel7:
    GetStatusRdcDevDataLesen_Ch7DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel8:
    GetStatusRdcDevDataLesen_Ch8DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel9:
    GetStatusRdcDevDataLesen_Ch9DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel10:
    GetStatusRdcDevDataLesen_Ch10DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel11:
    GetStatusRdcDevDataLesen_Ch11DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel12:
    GetStatusRdcDevDataLesen_Ch12DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel13:
    GetStatusRdcDevDataLesen_Ch13DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel14:
    GetStatusRdcDevDataLesen_Ch14DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel15:
    GetStatusRdcDevDataLesen_Ch15DS( pucData);
    break;

  case cStatusRdcDeveloperDataLesen_MuxChannel16:
    GetStatusRdcDevDataLesen_Ch16DS( pucData);
    break;

  default:
    GetStatusRdcDevDataLesen_Ch0DS(self, pucData);
    break;
  }
}

uint8 ucPutDeveloperDataMuxChannelDS( uint8 ucMuxChannel)
{
  uint8 ucRetVal;

  if( ucMuxChannel < cStatusRdcDeveloperDataLesen_MuxChannelMaxValue)
  {
    ucDeveloperDataMuxChannelDS = ucMuxChannel;
    ucRetVal = cRetOk;
  }else{
    ucDeveloperDataMuxChannelDS = cStatusRdcDeveloperDataLesen_MuxChannelDefValue;
    ucRetVal = cRetError;
  }

  return ucRetVal;
}

uint8 ucGetDeveloperDataMuxChannelDS(void)
{
  return ucDeveloperDataMuxChannelDS;
}

static void GetStatusRdcDevDataLesen_Ch0DS(Rte_Instance self, uint8* pucData)
{
  uint32 ulDWord;
  uint16 ushWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel0;

  ulDWord = ulGetStopTimeDM();
  pucData[1] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
  pucData[2] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
  pucData[3] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
  pucData[4] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

  pucData[5] = GETucUnAipEE(self);
  pucData[6] = GETucUnTempEE(self);
  pucData[7] = GETucUnMileEE(self);

  ushWord = ushGetBetriebszustandBZ( cBZ_ALLE_BITS);
  pucData[8] = (uint8) ((ushWord >>  8) & 0x00FFu);
  pucData[9] = (uint8) ((ushWord >>  0) & 0x00FFu);

  pucData[10] = ucGetStatusConditionVehicleFZZ();
  pucData[11] = ucGetStatusLastConditionVehicleFZZ();

  ushWord = ushGetZustandskennungZK( cZK_ALLE_BITS);
  pucData[12] = (uint8) ((ushWord >>  8) & 0x00FFu);
  pucData[13] = (uint8) ((ushWord >>  0) & 0x00FFu);

  pucData[14] = (uint8) GETscTAinitValEE(self);
  pucData[15] = (uint8) GETscTAmbValEE(self);

  if( GETsshTAmbFiltValEE(self) < 0)
  {
    pucData[16] = (uint8) ((GETsshTAmbFiltValEE(self) - 50) / 100);
  }else{
    pucData[16] = (uint8) ((GETsshTAmbFiltValEE(self) + 50) / 100);
  }

  pucData[17] = GETucTAmbFiltFactValEE(self);
  pucData[18] = GETucPAmbValEE(self);

  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch1DS(Rte_Instance self, uint8* pucData){
  uint32 ulDWord;
  uint16 ushWord;
  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel1;
  pucData[1] = ucGetWAState();
  pucData[2] = ucGetIdChangedBitsZK();
  pucData[3] = ucGetStopCounter();

  ulDWord = GETulTimestampEE(self);
  pucData[4] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
  pucData[5] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
  pucData[6] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
  pucData[7] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

  ushWord = ushGetWatoTimeoutValueWAM();
  pucData[8] = (uint8) ((ushWord >>  8) & 0x00FFu);
  pucData[9] = (uint8) ((ushWord >>  0) & 0x00FFu);

  pucData[10] = 0xFF;
  pucData[11] = 0xFF;
  pucData[12] = 0xFF;
  pucData[13] = 0xFF;
  pucData[14] = 0xFF;
  pucData[15] = 0xFF;
  pucData[16] = 0xFF;
  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch2DS(Rte_Instance self, uint8* pucData)
{
  uint8               ucData[cAnzRad];
  WarnConfigArrayType aucCb;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel2;

  if( ucGetWarnBitIdIntIFH(self, ucData) == 0x00)
  {
    pucData[1] = ucData[0];
    pucData[2] = ucData[1];
    pucData[3] = ucData[2];
    pucData[4] = ucData[3];
  }else{
    pucData[1] = 0xFF;
    pucData[2] = 0xFF;
    pucData[3] = 0xFF;
    pucData[4] = 0xFF;
  }

  if( ucGetWarnBitTonnageIdIntIFH(self, ucData) == 0x00)
  {
    pucData[5] = ucData[0];
    pucData[6] = ucData[1];
    pucData[7] = ucData[2];
    pucData[8] = ucData[3];
  }else{
    pucData[5] = 0xFF;
    pucData[6] = 0xFF;
    pucData[7] = 0xFF;
    pucData[8] = 0xFF;
  }

  if( ucGetWarnBitAirMassIdIntIFH(self, ucData) == 0x00)
  {
    pucData[9]  = ucData[0];
    pucData[10] = ucData[1];
    pucData[11] = ucData[2];
    pucData[12] = ucData[3];
  }else{
    pucData[9]  = 0xFF;
    pucData[10] = 0xFF;
    pucData[11] = 0xFF;
    pucData[12] = 0xFF;
  }

  GETucWsEE(self, &pucData[13]);
  GETucTsEE(self, &pucData[14]);

  GETaucCbEE(self, &aucCb);
  pucData[15] = aucCb[0];
  pucData[16] = aucCb[1];

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch3DS( uint8* pucData)
{
  uint8  ucLoop;
  uint16 ushWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel3;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 1] = ucGetPSollMinCS( ucLoop);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 5] = ucGetPSollCS( ucLoop, cRadPosUndef);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 9] = (uint8) scGetTSollCS( ucLoop, cRadPosUndef);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ushWord = ushGetMSollCS( ucLoop);
    pucData[((ucLoop * 2) + 13)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 14)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }
}

static void GetStatusRdcDevDataLesen_Ch4DS( uint8* pucData)
{
  uint8 ucLoop;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel4;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 1] = ucGetPinitTreifenCS( ucLoop);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 5] = (uint8) scGetTreifenCS( ucLoop);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 9] = ucGetPambCS( ucLoop);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 13] = (uint8) scGetTambCS( ucLoop);
  }

  pucData[17] = ucGetPMinCS();

  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch5DS( uint8* pucData)
{
  uint8  ucLoop;
  uint8  ucByte;
  uint16 ushWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel5;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    GetTimerValPWARN( ucLoop, &ucByte, &ushWord);
    pucData[((ucLoop * 2) + 1)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 2)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    GetTimerValPWARNTOL( ucLoop, &ucByte, &ushWord);
    pucData[((ucLoop * 2) +  9)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 10)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch6DS( uint8* pucData)
{
  uint8 ucLoop;
  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel6;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[(ucLoop * 2) + 1] = 0xff;
    pucData[(ucLoop * 2) + 2] = 0xff;
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 9] = ucGetPinitTinitDM( ucLoop);
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 13] = 0xff;
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[ucLoop + 17] = (uint8) scGetTinitDM( ucLoop);
  }
}

static void GetStatusRdcDevDataLesen_Ch7DS( uint8* pucData)
{
  uint8  ucLoop;
  uint16 ushWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel7;

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    pucData[(ucLoop * 2) + 1] = 0xff;
    pucData[(ucLoop * 2) + 2] = 0xff;
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ushWord = GetTarPTyrDisplayValueDM( ucLoop);
    pucData[((ucLoop * 2) +  9)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 10)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }

  pucData[17] = ucGetPWarnMinDM();

  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch8DS( uint8* pucData)
{
  uint8 ucLoop;
  uint8 ucSetLevel;
  uint8 ucResetLevel;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel8;

  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    GetWarnThresDM( 0, ucLoop, &ucSetLevel, &ucResetLevel);
    pucData[((ucLoop * 2) + 1)] = ucSetLevel;
    pucData[((ucLoop * 2) + 2)] = ucResetLevel;
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch9DS( uint8* pucData)
{
  uint8 ucLoop;
  uint8 ucSetLevel;
  uint8 ucResetLevel;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel9;

  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    GetWarnThresDM( 1, ucLoop, &ucSetLevel, &ucResetLevel);
    pucData[((ucLoop * 2) + 1)] = ucSetLevel;
    pucData[((ucLoop * 2) + 2)] = ucResetLevel;
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch10DS( uint8* pucData)
{
  uint8 ucLoop;
  uint8 ucSetLevel;
  uint8 ucResetLevel;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel10;

  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    GetWarnThresDM( 2, ucLoop, &ucSetLevel, &ucResetLevel);
    pucData[((ucLoop * 2) + 1)] = ucSetLevel;
    pucData[((ucLoop * 2) + 2)] = ucResetLevel;
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch11DS( uint8* pucData)
{
  uint8 ucLoop;
  uint8 ucSetLevel;
  uint8 ucResetLevel;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel11;

  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    GetWarnThresDM( 3, ucLoop, &ucSetLevel, &ucResetLevel);
    pucData[((ucLoop * 2) + 1)] = ucSetLevel;
    pucData[((ucLoop * 2) + 2)] = ucResetLevel;
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch12DS( uint8* pucData)
{
  uint8  ucLoop;
  uint32 ulDWord;
  uint16 ushWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel12;

  ulDWord = ulGetNetworkErrorsNWM();
  pucData[1] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
  pucData[2] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
  pucData[3] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
  pucData[4] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

  ulDWord = ulGetWheelUnitErrorsWUM(cNoFilter);
  pucData[5] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
  pucData[6] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
  pucData[7] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
  pucData[8] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ushWord = ushGetReDefectCounterBySlotWUM( ucLoop);
    pucData[((ucLoop * 2) +  9)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 10)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }

  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch13DS( uint8* pucData)
{
  uint8  ucLoop;
  uint16 ushWord;
  uint32 ulDWord;

  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel13;

  pucData[1] = ucGetAutoLocFailedCounterWUM();

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ushWord = ushGetMuteTimerValueWUM( ucLoop);
    pucData[((ucLoop * 2) + 2)] = (uint8) ((ushWord >>  8) & 0x00FFu);
    pucData[((ucLoop * 2) + 3)] = (uint8) ((ushWord >>  0) & 0x00FFu);
  }

  pucData[10] = ucGetBreakTireStateBT();

  ulDWord = ulGetStartedStateOfVklCCM();
  pucData[11] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
  pucData[12] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
  pucData[13] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
  pucData[14] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

  pucData[15] = 0xFF;
  pucData[16] = 0xFF;
  pucData[17] = 0xFF;
  pucData[18] = 0xFF;
  pucData[19] = 0xFF;
  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch14DS( uint8* pucData)
{
  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel14;

  pucData[1] = 0x00;
  if( bGetCRdciTPrewarnNcCD()             == TRUE) { pucData[1] |= 0x01u; }
  if( bGetCRdciMaxThresholdCD()           == TRUE) { pucData[1] |= 0x02u; }
  if( bGetCRdciPrewarnEnableCD()          == TRUE) { pucData[1] |= 0x04u; }
  if( bGetCRdciStatInitCD()               == TRUE) { pucData[1] |= 0x08u; }
  if( bGetCRdciNumPrewarnDetectCD()       == TRUE) { pucData[1] |= 0x10u; }
  if( bGetCRdciPrewarnIgnitionCD()        == TRUE) { pucData[1] |= 0x20u; }
  if( bGetCRdciPanneBefPosCD()            == TRUE) { pucData[1] |= 0x40u; }
  if( bGetCRdciFastDeflateEnableCD()      == TRUE) { pucData[1] |= 0x80u; }

  pucData[2] = 0x00;
  if( bGetCRdciTyrIdFiltGwCD()            == TRUE) { pucData[2] |= 0x01u; }
  if( bGetCRdciResetPlausiCD()            == TRUE) { pucData[2] |= 0x02u; }
                                                      pucData[2] |= ((ucGetCRdciTpmsMarketCD() << 2) & 0x1Cu);
  if( bGetCRdciSensorForeignAkRdkCD()     == TRUE) { pucData[2] |= 0x20u; }
  if( bGetCRdciSensorLocSyncCD()          == TRUE) { pucData[2] |= 0x40u; }
  if( bGetCRdciErfsEnableCD()             == TRUE) { pucData[2] |= 0x80u; }

  pucData[3] = 0x00;
  if( bGetCRdciTrefSeasonalAdjustmentCD() == TRUE) { pucData[3] |= 0x01u; }
  if( bGetCRdciDispResetCD()              == TRUE) { pucData[3] |= 0x10u; }
                                                      pucData[3] |= ((ucGetCRdciCorHoldOffTimeCD() & 0x07u) << 5);

  pucData[4]  = ucGetCRdciTRefShiftCD();
  pucData[5]  = ucGetCRdciUiaThCCD();
  pucData[6]  = ucGetCRdciUiwThCCD();
  pucData[7]  = ucGetCRdciUiaThNcCD();
  pucData[8]  = ucGetCRdciUiwThNcCD();
  pucData[9]  = ucGetCRdciPanneThCD();
  pucData[10] = ucGetCRdciMinRcpFaCD();
  pucData[11] = ucGetCRdciMinRcpRaCD();
  pucData[12] = ucGetCRdciDeltaPLRCD();
  pucData[13] = ucGetCRdciPInitRangeMaxCD();
  pucData[14] = ucGetCRdciTimeoutPrewarnCD();
  pucData[15] = ucGetCRdciDtAmbPrewarnCD();
  pucData[16] = ucGetCRdciDpToIPminCD();
  pucData[17] = ucGetCRdciLearnLocateConfigCD( 0);
  pucData[18] = ucGetCRdciLearnLocateConfigCD( 1);
  pucData[19] = ucGetCRdciXminCoolTireCD();
  pucData[20] = ucGetCRdciMaxCorTimeCD();
}

static void GetStatusRdcDevDataLesen_Ch15DS( uint8* pucData)
{
  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel15;

  pucData[1]  = ucGetCRdciMaxCorRcpCD();

  pucData[2] = 0x00;
  pucData[2]  = (ucGetCRdciThCTolCD() & 0x0Fu);
  pucData[2]  |= (uint8) ((ucGetCRdciThNCTolCD() & 0x0Fu) << 4);

  pucData[3] = 0x00;
  pucData[3]  = (ucGetCRdciLongHoldTimeCD() & 0x0Fu);
  pucData[3]  |= (uint8) ((ucGetCRdciShortHoldTimeCD() & 0x07u) << 4);
  if( bGetCRdciEcoRcpEnableCD()       == TRUE) { pucData[3] |= 0x80u; }

  pucData[4] = 0x00;
  if( bGetCRdciDefaultLoadCondCD()    == TRUE) { pucData[4] |= 0x01u; }
                                                  pucData[4] |= ((ucGetCRdciErfsPlacardSourceCD() & 0x03u) << 1);
  if( bGetCRdciDefaultMenuSelCD()     == TRUE) { pucData[4] |= 0x08u; }
  pucData[4]  |= (uint8) ((ucGetCRdciDispConfTimeoutCD() & 0x0Fu) << 4);

  pucData[5] = 0x00;
  if( bGetCRdciRidEnableCD()          == TRUE) { pucData[5] |= 0x01u; }

  pucData[6]  = ucGetCRdciTrefSeasAdjConfigCD( 0);
  pucData[7]  = ucGetCRdciTrefSeasAdjConfigCD( 1);
  pucData[8]  = ucGetCRdciTrefSeasAdjConfigCD( 2);
  pucData[9]  = ucGetCRdciTrefSeasAdjConfigCD( 3);

  pucData[10] = GetLoadStateDM();
  pucData[11] = GetSeasonDM();
  pucData[12] = GetSummerTyreIndexDM();
  pucData[13] = GetWinterTyreIndexDM();
  pucData[14] = GetLengthOfTyreListDM();
  pucData[15] = GetSelectedTyreIndexDM();
  pucData[16] = GetStatusManSelectionDM();
  pucData[17] = GetIDRMessageCenterDM();
  pucData[18] = GetSizeOfTyreListElementDM();
  pucData[19] = GetDefaultLoadCondDM();

  pucData[20] = 0xFF;
}

static void GetStatusRdcDevDataLesen_Ch16DS( uint8* pucData){
  uint16 ushSpeedCcmVal;
  pucData[0] = cStatusRdcDeveloperDataLesen_MuxChannel16;
  pucData[1] = 0x00;
  if( bGetCRdciSpeedCcmEnableCD() == TRUE)
  {
    pucData[1] |= 0x01;
  }

  ushSpeedCcmVal = ushGetCRdciSpeedCcmThCD();
  pucData[2] = (uint8) ((ushSpeedCcmVal >> 8) & 0x00ffu);
  pucData[3] = (uint8) ((ushSpeedCcmVal >> 0) & 0x00ffu);

  pucData[4] = ucGetCRdciSpeedCcmTimeCD();
  pucData[5] = ucGetCRdciSpeedCcmHystCD();

  ushSpeedCcmVal = (uint16) sshGetCRdciSpeedCcmPressOffsetFaCD();
  pucData[6] = (uint8) ((ushSpeedCcmVal >> 8) & 0x00ffu);
  pucData[7] = (uint8) ((ushSpeedCcmVal >> 0) & 0x00ffu);

  ushSpeedCcmVal = (uint16) sshGetCRdciSpeedCcmPressOffsetRaCD();
  pucData[8] = (uint8) ((ushSpeedCcmVal >> 8) & 0x00ffu);
  pucData[9] = (uint8) ((ushSpeedCcmVal >> 0) & 0x00ffu);

  pucData[10] = ucGetCRdciParkSupExtParkSupConfigCD();
  pucData[11] = ucGetCRdciParkSupMobilityLossThValueCD();
  pucData[12] = ucGetCRdciParkSupNotifThCValueCD();
  pucData[13] = ucGetCRdciParkSupNotifThNcValueCD();
  pucData[14] = ucGetCRdciParkSupTolNoTempCompCD();
  pucData[15] = ucGetCRdciParkSupTolTempCompCD();
  pucData[16] = ucGetCRdciParkSupWarningThCValueCD();
  pucData[17] = ucGetCRdciParkSupWarningThNcValueCD();

  pucData[18] = 0xffu;
  pucData[19] = 0xffu;
  pucData[20] = 0xffu;
}
