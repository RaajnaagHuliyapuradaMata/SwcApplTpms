#include "StatusRdcMessdatenblock.h"
#include "DataManagerX.h"
#include "WAllocX.h"
#include "State_bzX.h"
#include "State_fzzX.h"
#include "State_zkX.h"
#include "USWarn_ifX.h"
#include "WuMonitoringX.h"
#include "EeWarnStatusBlockX.h"
#include "EeZomBlockX.h"
#include "InfoTyreX.h"
#include "RdcTsaServicesX.h"

void GetStatusRdcMessdatenblockDS( Rte_Instance self, uint8 ucBlockNo, uint8* pucData){
  uint32                ulReID;
  uint16                ushTempVal, ushM;
  PhySensorTyrePresType ucPress, ucPcold, ucPwarm, ucPamb;
  PhySensorTyreTempType scTemp, scTcold, scTwarm;
  uint8                 ucHardWarning;
  uint8                 ucWheelPos;
  uint8                 ucBattLevel;
  uint8                 ucTemp;

  if( ucBlockNo < 4){
    ulReID = (uint32) ulGetIDOfColWAL( ucBlockNo);
    pucData[cucIxStatReIdentifierWert + 0]              = (uint8) ((ulReID >> 24) & 0x000000FFu);
    pucData[cucIxStatReIdentifierWert + 1]              = (uint8) ((ulReID >> 16) & 0x000000FFu);
    pucData[cucIxStatReIdentifierWert + 2]              = (uint8) ((ulReID >>  8) & 0x000000FFu);
    pucData[cucIxStatReIdentifierWert + 3]              = (uint8) ((ulReID >>  0) & 0x000000FFu);
    ucWheelPos = ucGetWPOfColWAL( ucBlockNo);
    if( ucWheelPos < cRadPosUndef){
      pucData[cucIxStatRadPositionNr]                   = ucWheelPos;
      ucTemp = GetQrIxOfWheelPos( self, ucWheelPos);
      ucTemp <<= 4;
      ucTemp &= 0xf0u;
      pucData[cucIxStatRadPositionNr]                  |= ucTemp;
    }else{
      pucData[cucIxStatRadPositionNr]                   = 5;
    }
    ucPress = ucGetRePressureRelDM( ucBlockNo);
    if( ucPress == cInvalidREpressure){
      pucData[cucIxStatLetzterReifendruckwertWert + 0]  = (uint8) (((uint16) -9999 >> 8) & 0x00FFu);
      pucData[cucIxStatLetzterReifendruckwertWert + 1]  = (uint8) (((uint16) -9999 >> 0) & 0x00FFu);
    }else{
      pucData[cucIxStatLetzterReifendruckwertWert + 0]= (uint8) ((((uint16) ucPress * 25) >> 8) & 0x00FFu);
      pucData[cucIxStatLetzterReifendruckwertWert + 1]= (uint8) ((((uint16) ucPress * 25) >> 0) & 0x00FFu);
    }
    scTemp = scGetReTemperatureCentDM( ucBlockNo);
    if( scTemp == cInvalidREtemperature)
    {
      pucData[cucIxStatLetzterReifentemperaturwertWert] = (uint8) 0xff;
    }else{
      pucData[cucIxStatLetzterReifentemperaturwertWert] = (uint8) (scGetReTemperatureCentDM( ucBlockNo) + 50);
    }
    if( ucGetPTSollUSWIF( self, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushM, &ucPamb, ucBlockNo) == cRetError){
      pucData[cucIxStatSolldruckWert + 0]               = (uint8) (((uint16) -9999 >> 8) & 0x00FFu);
      pucData[cucIxStatSolldruckWert + 1]               = (uint8) (((uint16) -9999 >> 0) & 0x00FFu);
    }else{
      if( ucPwarm == cInvalidREpressure){
        pucData[cucIxStatSolldruckWert + 0]             = (uint8) (((uint16) -9999 >> 8) & 0x00FFu);
        pucData[cucIxStatSolldruckWert + 1]             = (uint8) (((uint16) -9999 >> 0) & 0x00FFu);
      }else{
        pucData[cucIxStatSolldruckWert + 0]             = (uint8) ((((uint16) ucPwarm * 25) >> 8) & 0x00FFu);
        pucData[cucIxStatSolldruckWert + 1]             = (uint8) ((((uint16) ucPwarm * 25) >> 0) & 0x00FFu);
      }
    }

    ushTempVal = ushGetWheelUnitGoodCounterWUM( ucBlockNo);
    pucData[cucIxStatGutempfaengeWert + 0]              = (uint8) ((ushTempVal >> 8) & 0x00FFu);
    pucData[cucIxStatGutempfaengeWert + 1]              = (uint8) (ushTempVal        & 0x00FFu);
    pucData[cucIxStatAusbeuteWert]                      = ucGetYieldRateWUM( ucBlockNo);
    pucData[cucIxStatRssiPegelWert + 0]                 = 0x00;
    pucData[cucIxStatRssiPegelWert + 1]                 = GETucLastSNRFromNvmMirrorEE( self, ucBlockNo);
    ucBattLevel = GETucLastBatteryStateFromNvmMirrorEE( self, ucBlockNo);
    if(ucBattLevel == 0xff){
      pucData[cucIxStatRestlebensdauerWert + 0]         = (uint8) (((uint16) -999 >> 8) & 0x00FFu);
      pucData[cucIxStatRestlebensdauerWert + 1]         = (uint8) (((uint16) -999 >> 0) & 0x00FFu);
    }else{
      pucData[cucIxStatRestlebensdauerWert + 0]         = 0;
      pucData[cucIxStatRestlebensdauerWert + 1]         = ucBattLevel;
    }
    pucData[cucIxStatRadelektronikStatus] = GETucWheelSensorStatusFromNvmMirrorEE( self, ucBlockNo);
    ucHardWarning  = GETucWarningGroupTM( cucWT_GrpPanne);
    ucHardWarning |= GETucWarningGroupTM( cucWT_GrpPmin);
    ucHardWarning |= GETucWarningGroupTM( cucWT_GrpPwarn);
    if( bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){
      ucWheelPos = ucGetWPOfColWAL( ucBlockNo);
      if( (ucHardWarning & (uint8) (1 << ucWheelPos)) == 0){
        pucData[cucIxStatHarteWarnungAktiv]             = 0x00;
      }
      else{
        pucData[cucIxStatHarteWarnungAktiv]             = 0x01;
      }
    }
    else{
      if( (ucHardWarning & (uint8) (1 << ucBlockNo)) == 0){
        pucData[cucIxStatHarteWarnungAktiv]             = 0x00;
      }else{
        pucData[cucIxStatHarteWarnungAktiv]             = 0x01;
      }
    }
    ucTemp = GETucLastPosChangedInfoFromNvmMirrorEE( self);
    pucData[cucIxStatPosChanged]                        = (ucTemp >> ucBlockNo) & 0x01;
    pucData[cucIxStatFolgeausfallWert]                  = GETucTimeSinceLastRecEventFromNvmMirrorEE( self, ucBlockNo);
    if(ulReID == 0){
      pucData[cucIxStatReHersteller]                      = 0xff;
    }
    else{
      pucData[cucIxStatReHersteller]                      = (uint8) ((ulReID >> 28) & 0x0000000Fu);
    }
    ushM = GETushLastPalStatusEE( self, ucBlockNo);
    ushTempVal = (ushM & 0x00C0u) >> 6;
    if(ushTempVal == 0x01){
      pucData[cucIxStatRadelektronikSendemode] = 0x06;
    }
    else if(ushTempVal == 0x02){
      pucData[cucIxStatRadelektronikSendemode] = 0x08;
    }
    else if(ushTempVal == 0x03){
      ushTempVal = (ushM & 0xE000u) >> 13;
      switch (ushTempVal){
        case (uint16)1: pucData[cucIxStatRadelektronikSendemode] = 0x07u; break;
        case (uint16)2: pucData[cucIxStatRadelektronikSendemode] = 0x00u; break;
        case (uint16)3: pucData[cucIxStatRadelektronikSendemode] = 0x02u; break;
        case (uint16)4: pucData[cucIxStatRadelektronikSendemode] = 0x04u; break;
        case (uint16)5: pucData[cucIxStatRadelektronikSendemode] = 0x03u; break;
        case (uint16)6: pucData[cucIxStatRadelektronikSendemode] = 0x05u; break;
        default:        pucData[cucIxStatRadelektronikSendemode] = 0xffu; break;
      }
    }
    else{
      pucData[cucIxStatRadelektronikSendemode] = 0xffu;
    }
    pucData[cucIxStatTelegrammtyp] = GETucLastTelegramTypeFromNvmMirrorEE(self, ucBlockNo);
  }else{
    pucData[cucIxStatReIdentifierWert + 0]              = 0x00u;
    pucData[cucIxStatReIdentifierWert + 1]              = 0x00u;
    pucData[cucIxStatReIdentifierWert + 2]              = 0x00u;
    pucData[cucIxStatReIdentifierWert + 3]              = 0x00u;
    pucData[cucIxStatRadPositionNr]                     = cRadPosUndef;
    pucData[cucIxStatLetzterReifendruckwertWert + 0]    = (uint8) (((uint16) -9999 >> 8) & 0x00FFu);
    pucData[cucIxStatLetzterReifendruckwertWert + 1]    = (uint8) (((uint16) -9999 >> 0) & 0x00FFu);
    pucData[cucIxStatLetzterReifentemperaturwertWert]   = 0xff;
    pucData[cucIxStatSolldruckWert + 0]                 = (uint8) (((uint16) -9999 >> 8) & 0x00FFu);
    pucData[cucIxStatSolldruckWert + 1]                 = (uint8) (((uint16) -9999 >> 0) & 0x00FFu);
    pucData[cucIxStatGutempfaengeWert + 0]              = 0x00u;
    pucData[cucIxStatGutempfaengeWert + 1]              = 0x00u;
    pucData[cucIxStatAusbeuteWert]                      = 0x00u;
    pucData[cucIxStatRssiPegelWert + 0]                 = 0x00u;
    pucData[cucIxStatRssiPegelWert + 1]                 = 0x00u;
    pucData[cucIxStatRestlebensdauerWert + 0]           = (uint8) (((uint16) -999 >> 8) & 0x00FFu);
    pucData[cucIxStatRestlebensdauerWert + 1]           = (uint8) (((uint16) -999 >> 0) & 0x00FFu);
    pucData[cucIxStatRadelektronikStatus]               = 0xFFu;
    pucData[cucIxStatHarteWarnungAktiv]                 = 0x00u;
    pucData[cucIxStatPosChanged]                        = 0x00u;
    pucData[cucIxStatFolgeausfallWert]                  = 0x00u;
    pucData[cucIxStatReHersteller]                      = 0xFFu;
    pucData[cucIxStatRadelektronikSendemode]            = 0xFFu;
    pucData[cucIxStatTelegrammtyp]                      = 0xFFu;
  }
}

