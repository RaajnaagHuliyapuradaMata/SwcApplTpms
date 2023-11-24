#include "HS_Kalibrierereignis.h"
#include "DatamanagerX.h"
#include "EeCommonBlockX.h"
#include "EeDiagBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeErfsBlockX.h"
#include "SecondaryDTCX.h"
#include "state_fzzX.h"
#include "WallocX.h"
#include "State_bzX.h"
#include "RdcTsaServicesX.h"

#ifndef TESSY
  #ifdef WIN32
    #include "assert.h"
  #endif
#endif

void SetCalibrationRootCauseDS( Rte_Instance self, uint8 ucRootCause)
{
  PUTucCalibrationRootCauseEE( self, ucRootCause);
}

uint8 ucGetCalibrationRootCauseDS( Rte_Instance self)
{
  return GETucCalibrationRootCauseEE( self);
}

uint8 SaveCalibrationEventDS( Rte_Instance self)
{
  Rdci_UHRZEIT_DATUM_Type timeDate;
  Rdci_MILE_KM_Type mileKm;
  uint8 cTempBuffer[9];
  uint8 cData[cSizeKalibrierereignis];
  uint8 i;
  uint8 ucRetVal;
  uint8 ucTemp, ucPcold, ucPwarm, ucPamb;
  sint8 scTcold, scTwarm, scTemp;
  uint16 ushTemp, ushM;
  uint8 ucCounterKalib;
  uint8 ucCalStatus, ucCalStatusBackup;

  #ifndef TESSY
    #ifdef WIN32

    assert(sizeof(ImpTypeArrayDcm_RdcHsKalibrierereignisReadDataType) == (cSizeKalibrierereignis * 3));
    #endif
  #endif

  ucCalStatus = ucGetCalibrationRootCauseDS( self);
  ucCalStatusBackup = ucCalStatus;

  if((ucCalStatus != cCalNvmError) && (ucCalStatus != cCalInvalid))
  {
    if(GETSelectedTyreIndexEE( self) == OP_SLCTN_TYR_AVLB_AndererReifen)
    {
      ucCalStatus = cCalOtherTyre;
    }

    if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE)
    {
      ucCalStatus |= cCalPA;
    }
    else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE)
    {
      ucCalStatus |= cCalPA;
    }
    else {}
  }

  if(ucCalStatus == cCalInvalid)
  {
    ucRetVal = 2;
  }

  else if(ucCalStatus == cCalNvmError)
  {
    ucRetVal = 3;

  }

  else if(GETTyreSelectionActiveEE( self) == FALSE)
  {

    if(GETTyreSelectionBckgrdEE( self) == TRUE)
    {
      if(bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)
      {
        ucRetVal = 3;
      }
      else if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE)
      {
        ucRetVal = 3;
      }
      else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE)
      {
        ucRetVal = 3;
      }
      else
      {
        ucRetVal = 0;
        SetCalibrationRootCauseDS( self, cCalInvalid);
      }
    }

    else
    {
      ucRetVal = 0;
      SetCalibrationRootCauseDS( self, cCalInvalid);
    }
  }

  else
  {
    ucRetVal = 0;
    if(bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)
    {
      ucCalStatus = cCalError;
    }
    else if(bGetBitBetriebszustandBZ(cZUGEORDNET) == FALSE)
    {
      ucCalStatus = cCalError;
    }
    else if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE)
    {
      SetCalibrationRootCauseDS( self, ucCalStatusBackup);
    }
    else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE)
    {
      SetCalibrationRootCauseDS( self, ucCalStatusBackup);
    }
    else
    {
      SetCalibrationRootCauseDS( self, cCalInvalid);
    }
  }

  if(ucRetVal == 0)
  {

    ucCounterKalib = GetHsKalibrierereignis_1_CounterEE( self);
    if(ucCounterKalib == 0xff)
    {
      ucCounterKalib = 1;
    }
    else if(ucCounterKalib < 0xfe)
    {
      ucCounterKalib++;
    }
    else
    {}

    SetSecondaryErrorSCD(cSecondaryRdciKalibrierung);
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciKalibrierung, RDC_TAB_POSITION_SENSOR_INVALID);

    if(ucCalStatus == cCalError)
    {
      ucTemp = 0xff;
    }
    else
    {
      ucTemp = GETPlausiInitErrorEE( self);
    }
    switch (ucTemp)
    {
      case (uint8)0:
      if((ucCalStatusBackup == cCalByHMI) || (ucCalStatusBackup == cCalRidStatusbar))
      {
        cData[0] = cCalEvManPlausiSuccessful;
      }
      else
      {
        cData[0] = cCalEvPlausiSuccessful;
      }
      break;

      case (uint8)1:
      if((ucCalStatusBackup == cCalByHMI) || (ucCalStatusBackup == cCalRidStatusbar))
      {
        cData[0] = cCalEvManPlausiFailed;
      }
      else
      {
        cData[0] = cCalEvPlausiFailed;
      }
      break;

      default:
      cData[0] = cCalEvInvalid;
      break;
    }

    cData[1] = ucCalStatus;

    timeDate = GETtTimeDateEE( self);
    GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));
    for (i=0; i<8; i++)
    {
      cData[i+2] = cTempBuffer[i];
    }
    GetTimeStringDM((uint8)timeDate.DISP_HR, (uint8)timeDate.DISP_MN, (uint8)timeDate.DISP_SEC, cTempBuffer, sizeof(cTempBuffer));
    for (i=0; i<8; i++)
    {
      cData[i+10] = cTempBuffer[i];
    }

    mileKm = GETulMileKmEE( self);
    cData[18] = (uint8)((mileKm >> 24) & 0xffU);
    cData[19] = (uint8)((mileKm >> 16) & 0xffU);
    cData[20] = (uint8)((mileKm >> 8) & 0xffU);
    cData[21] = (uint8)(mileKm & 0xffU);
    cData[22] = (uint8) (GETscTAinitValEE( self) + 40);
    ucTemp = GETucPAmbValEE( self);
    ushTemp = Change25mBarToHpa(ucTemp);
    cData[23] = (uint8)((ushTemp >> 8) & 0xffU);
    cData[24] = (uint8)(ushTemp & 0xffU);

    for (i=0; i<cMaxLR; i++)
    {
      ucTemp = ucGetWPOfColWAL(i);
      if(ucTemp < cMaxLR)
      {
        cData[25 + (6 * i)] = ucTemp;
        ucTemp = GetQrIxOfWheelPos( self, ucTemp);
        ucTemp <<= 4;
        ucTemp &= 0xf0u;
        cData[25 + (6 * i)] |= ucTemp;
      }
      else
      {
        cData[25 + (6 * i)] = 0x05 + i;
      }

      ucTemp = ucGetRePressureRelDM(i);
      if(ucTemp == cInvalidREpressure)
      {
        ushTemp = 0xffffu;
      }
      else
      {
        ushTemp = Change25mBarToHpa(ucTemp);
      }
      cData[26 + (6 * i)] = (uint8)((ushTemp >> 8) & 0xffU);
      cData[27 + (6 * i)] = (uint8)(ushTemp & 0xffU);

      scTemp = scGetReTemperatureCentDM(i);
      if(scTemp == cInvalidREtemperature)
      {
        scTemp = (sint8) 205;
      }
      cData[28 + (6 * i)] = (uint8)scTemp + 50;

      (void)ucGetPTSollUSWIF( self, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushM, &ucPamb, i);
      if(ucPcold == cInvalidREpressure)
      {
        ushTemp = 0xffffu;
      }
      else
      {
        ushTemp = Change25mBarToHpa(ucPcold);
      }
      cData[29 + (6 * i)] = (uint8)((ushTemp >> 8) & 0xffU);
      cData[30 + (6 * i)] = (uint8)(ushTemp & 0xffU);
    }

    cData[49] = ucCounterKalib;

    for (i=0; i<sizeof(cData); i++)
    {
      PutHsKalibrierereignis_3_EE( self, GetHsKalibrierereignis_2_EE( self, i), i);
    }

    for (i=0; i<sizeof(cData); i++)
    {
      PutHsKalibrierereignis_2_EE( self, GetHsKalibrierereignis_1_EE( self, i), i);
    }

    for (i=0; i<sizeof(cData); i++)
    {
      PutHsKalibrierereignis_1_EE( self, cData[i], i);
    }

    ucRetVal = 0;
  }
  return ucRetVal;
}

void ReadCalibrationEventDS( Rte_Instance self, uint8 * paucData)
{
  uint8 i;

  for ( i = 0; i < cSizeKalibrierereignis; i++)
  {
    paucData[i] = GetHsKalibrierereignis_1_EE( self, i);
  }

  for ( i = 0; i < cSizeKalibrierereignis; i++)
  {
    paucData[cSizeKalibrierereignis + i] = GetHsKalibrierereignis_2_EE( self, i);
  }

  for ( i = 0; i < cSizeKalibrierereignis; i++)
  {
    paucData[(2 * cSizeKalibrierereignis) + i] = GetHsKalibrierereignis_3_EE( self, i);
  }
}

uint8 GetLatestCalibrationRootCauseDS( Rte_Instance self)
{
  return (GetHsKalibrierereignis_1_RootCauseEE( self));
}

