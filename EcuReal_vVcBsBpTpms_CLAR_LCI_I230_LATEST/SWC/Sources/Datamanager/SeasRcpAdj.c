#include "SeasRcpAdj.h"
#include "State_BzX.h"
#include "CodingDataX.h"
#include "InitializationX.h"
#include "WAllocX.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "HS_KalibrierereignisX.h"
#include "datamanagerX.h"
#include "state_fzzx.h"

static uint8    ucDeltaTinitLowerThSRA              = 0xFFu;
static uint8    ucDeltaTinitHigherThSRA             = 0xFFu;
static uint8    ucSlowTimeConstSRA                  = 0xFFu;
static uint8    ucFastTimeConstSRA                  = 0xFFu;
static uint32   ulTinitOatLowerTimeTicksSRA         = 0xFFFFFFFFu;
static uint32   ulTinitOatHigherTimeTicksSRA        = 0xFFFFFFFFu;
static uint32   ulTinitOatLowerSysTimeEndPointSRA   = 0xFFFFFFFFu;
static uint32   ulTinitOatHigherSysTimeEndPointSRA  = 0xFFFFFFFFu;
static boolean  bCorrTinitLowerEventSRA             = FALSE;
static boolean  bCorrTinitHigherEventSRA            = FALSE;
static uint16   ushTimeDiffInMinsSRA               = 0x0000u;

void InitSRA(Rte_Instance self){
  uint8  ucNibble;
  uint32 ulStartSraSysTime;
  if( bGetCRdciTrefSeasonalAdjustmentCD() == TRUE){
    ucNibble = (ucGetCRdciTrefSeasAdjConfigCD( 0) & cLoNibblePassedSRA);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ucDeltaTinitLowerThSRA     = 0xFFu;       }else{ ucDeltaTinitLowerThSRA    = ucNibble; }
    ucNibble = ((ucGetCRdciTrefSeasAdjConfigCD( 0) & cHiNibblePassedSRA) >> 4);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ucDeltaTinitHigherThSRA    = 0xFFu;       }else{ ucDeltaTinitHigherThSRA   = ucNibble; }
    ucNibble = (ucGetCRdciTrefSeasAdjConfigCD( 1) & cLoNibblePassedSRA);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ucSlowTimeConstSRA   = 0xFFu;       }else{ ucSlowTimeConstSRA = ucNibble; }
    ucNibble = ((ucGetCRdciTrefSeasAdjConfigCD( 1) & cHiNibblePassedSRA) >> 4);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ucFastTimeConstSRA  = 0xFFu;       }else{ ucFastTimeConstSRA = ucNibble; }
    ucNibble = (ucGetCRdciTrefSeasAdjConfigCD( 2) & cLoNibblePassedSRA);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ulTinitOatLowerTimeTicksSRA   = 0xFFFFFFFFu; }else{ ulTinitOatLowerTimeTicksSRA   = ((uint32) ucNibble * 86400u); }
    ucNibble = ((ucGetCRdciTrefSeasAdjConfigCD( 2) & cHiNibblePassedSRA) >> 4);
    if( (ucNibble == 0x00u) || (ucNibble == 0x0Fu)) { ulTinitOatHigherTimeTicksSRA  = 0xFFFFFFFFu; }else{ ulTinitOatHigherTimeTicksSRA  = ((uint32) ucNibble * 86400u); }
    if( (ulTinitOatLowerTimeTicksSRA == 0xFFFFFFFFu) || (ulTinitOatHigherTimeTicksSRA == 0xFFFFFFFFu)){
      ucDeltaTinitLowerThSRA                = 0xFFu;
      ucDeltaTinitHigherThSRA               = 0xFFu;

      ucSlowTimeConstSRA                    = 0xFFu;
      ucFastTimeConstSRA                    = 0xFFu;

      ulTinitOatLowerTimeTicksSRA           = 0xFFFFFFFFu;
      ulTinitOatHigherTimeTicksSRA          = 0xFFFFFFFFu;

      ulTinitOatLowerSysTimeEndPointSRA     = 0xFFFFFFFFu;
      ulTinitOatHigherSysTimeEndPointSRA    = 0xFFFFFFFFu;

      bCorrTinitLowerEventSRA               = FALSE;
      bCorrTinitHigherEventSRA              = FALSE;

      ushTimeDiffInMinsSRA                 = 0x0000u;
    }
    else{
      ulStartSraSysTime                     = GETulTinitOatLowerTimeStartEE(self);
      if( ulStartSraSysTime == 0xffffffffu){
        ulTinitOatLowerSysTimeEndPointSRA = ulTinitOatLowerTimeTicksSRA;
      }
      else{
        ulTinitOatLowerSysTimeEndPointSRA = (ulStartSraSysTime + ulTinitOatLowerTimeTicksSRA);
      }
      ulStartSraSysTime                     = GETulTinitOatHigherTimeStartEE(self);
      if( ulStartSraSysTime == 0xffffffffu){
        ulTinitOatHigherSysTimeEndPointSRA = ulTinitOatHigherTimeTicksSRA;
      }
      else{
        ulTinitOatHigherSysTimeEndPointSRA = (ulStartSraSysTime + ulTinitOatHigherTimeTicksSRA);
      }
    }
  }
  else{
    ucDeltaTinitLowerThSRA                  = 0xFFu;
    ucDeltaTinitHigherThSRA                 = 0xFFu;
    ucSlowTimeConstSRA                      = 0xFFu;
    ucFastTimeConstSRA                      = 0xFFu;
    ulTinitOatLowerTimeTicksSRA             = 0xFFFFFFFFu;
    ulTinitOatHigherTimeTicksSRA            = 0xFFFFFFFFu;
    ulTinitOatLowerSysTimeEndPointSRA       = 0xFFFFFFFFu;
    ulTinitOatHigherSysTimeEndPointSRA      = 0xFFFFFFFFu;
    bCorrTinitLowerEventSRA                 = FALSE;
    bCorrTinitHigherEventSRA                = FALSE;
    ushTimeDiffInMinsSRA = 0x0000u;
  }
}

void StartSRA(Rte_Instance self){
  StartOatLowerTimeSRA(self);
  StartOatHigherTimeSRA(self);
}

static void StartOatLowerTimeSRA(Rte_Instance self){
  uint32 ulStartSraSysTime;
  if( ulTinitOatLowerTimeTicksSRA == 0xffffffffu){
    PUTulTinitOatLowerTimeStartEE(self, 0xffffffffu);
    ulTinitOatLowerSysTimeEndPointSRA = 0xffffffffu;
  }
  else{
    ulStartSraSysTime = ulGetSysTimeDM();
    if( ulStartSraSysTime == 0xffffffffu){
      PUTulTinitOatLowerTimeStartEE(self, 0xffffffffu);
      ulTinitOatLowerSysTimeEndPointSRA = 0xffffffffu;
    }
    else{
      PUTulTinitOatLowerTimeStartEE(self, ulStartSraSysTime);
      ulTinitOatLowerSysTimeEndPointSRA = (ulStartSraSysTime + ulTinitOatLowerTimeTicksSRA);
    }
  }
}

static void StartOatHigherTimeSRA(Rte_Instance self){
  uint32 ulStartSraSysTime;
  if( ulTinitOatHigherTimeTicksSRA == 0xffffffffu){
    PUTulTinitOatHigherTimeStartEE(self, 0xffffffffu);
    ulTinitOatHigherSysTimeEndPointSRA = 0xffffffffu;
  }
  else{
    ulStartSraSysTime = ulGetSysTimeDM();
    if( ulStartSraSysTime == 0xffffffffu){
      PUTulTinitOatHigherTimeStartEE(self, 0xffffffffu);
      ulTinitOatHigherSysTimeEndPointSRA = 0xffffffffu;
    }
    else{
      PUTulTinitOatHigherTimeStartEE(self, ulStartSraSysTime);
      ulTinitOatHigherSysTimeEndPointSRA = (ulStartSraSysTime + ulTinitOatHigherTimeTicksSRA);
    }
  }
}

void CyclicSRA(Rte_Instance self){
  uint8   ucPSollKalt;
  sint8   scTSollKalt;
  uint8   ucPSollWarm;
  sint8   scTSollWarm;
  uint16  ushMSollKalt;
  uint8   ucEnvPress;
  sint8   scEnvTemp;
  uint8   ucLoop;
  uint32  ulSysTime;

  if( bGetCRdciTrefSeasonalAdjustmentCD() == TRUE){
    CyclicOATSampleFuncSRA(GETushSpeedFZZ(), self);

    if( ucDeltaTinitLowerThSRA != 0xFFu)
    {
      if( bCorrTinitLowerEventSRA == TRUE)
      {
        if( GETslOATavgEE(self) > ((GETscTAinitValEE(self) - (ucDeltaTinitLowerThSRA + cHyst))*1000))
        {
          bCorrTinitLowerEventSRA = FALSE;
        }else{
        }
      }else{
        if( GETslOATavgEE(self) <= ((GETscTAinitValEE(self) - ucDeltaTinitLowerThSRA)*1000))
        {
          bCorrTinitLowerEventSRA = TRUE;
        }else{
        }
      }
    }else{
      bCorrTinitLowerEventSRA = FALSE;
    }

    if( ucDeltaTinitHigherThSRA != 0xFFu)
    {
      if( bCorrTinitHigherEventSRA == TRUE)
      {
        if( GETslOATavgEE(self) < ((GETscTAinitValEE(self) + (ucDeltaTinitHigherThSRA - cHyst))*1000))
        {
          bCorrTinitHigherEventSRA = FALSE;
        }else{
        }
      }else{
        if( GETslOATavgEE(self) >= ((GETscTAinitValEE(self) + ucDeltaTinitHigherThSRA)*1000))
        {
          bCorrTinitHigherEventSRA = TRUE;
        }else{
        }
      }
    }else{
      bCorrTinitHigherEventSRA = FALSE;
    }

    ulSysTime = ulGetSysTimeDM();
    if( (ulTinitOatLowerSysTimeEndPointSRA != 0xFFFFFFFFu) && (ulSysTime != 0xFFFFFFFFu)){
      if( ulGetSysTimeDM() > ulTinitOatLowerSysTimeEndPointSRA){
        if( bCorrTinitLowerEventSRA == TRUE){
          scEnvTemp = (sint8)(GETslOATavgEE(self)/1000);
          PUTscTAinitValEE(self, scEnvTemp);
          SetCalibrationRootCauseDS(self, cCalSeaAdj);
          (void)SaveCalibrationEventDS(self);

          if( bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE)
          {
            for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
            {

              (void)ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSollKalt, &ucEnvPress, ucLoop);

              if( bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE)
              {
                (void) ucCfgReInitSingleUSWIF(self, ucPSollKalt, scEnvTemp, ucLoop, ucGetWPOfColWAL( ucLoop));
              }else{
                (void) ucCfgReInitSingleUSWIF(self, ucPSollKalt, scEnvTemp, ucLoop, cRadPosUndef);
              }
            }
          }
        }else{
        }
        StartOatLowerTimeSRA(self);
      }
    }
    ulSysTime = ulGetSysTimeDM();
    if( (ulTinitOatHigherSysTimeEndPointSRA != 0xFFFFFFFFu) && (ulSysTime != 0xFFFFFFFFu)){
      if( ulGetSysTimeDM() > ulTinitOatHigherSysTimeEndPointSRA){
        if( bCorrTinitHigherEventSRA == TRUE){
          scEnvTemp = (sint8)(GETslOATavgEE(self)/1000);
          PUTscTAinitValEE(self, scEnvTemp);
          SetCalibrationRootCauseDS(self, cCalSeaAdj);
          (void)SaveCalibrationEventDS(self);
          if( bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE){
            for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
              (void)ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSollKalt, &ucEnvPress, ucLoop);

              if( bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){
                (void) ucCfgReInitSingleUSWIF(self, ucPSollKalt, scEnvTemp, ucLoop, ucGetWPOfColWAL( ucLoop));
              }else{
                (void) ucCfgReInitSingleUSWIF(self, ucPSollKalt, scEnvTemp, ucLoop, cRadPosUndef);
              }
            }
          }
        }else{
        }
        StartOatHigherTimeSRA(self);
      }
    }
    PUTbCorrTinitLowerEventEE(self, bCorrTinitLowerEventSRA);
    PUTbCorrTinitHigherEventEE(self, bCorrTinitHigherEventSRA);
  }else{
  }
}

void GetInternalLowerDataSRA( uint8* pucDeltaTinitTh, uint8* pucSlowTimeConst, uint32* pulTinitOatTimeTicks, uint32* pulTinitOatTime, boolean* pbCorrTinitEvent){
  uint32 ulSysTime;
  *pucDeltaTinitTh      = ucDeltaTinitLowerThSRA;
  *pucSlowTimeConst    = ucSlowTimeConstSRA;
  *pulTinitOatTimeTicks = ulTinitOatLowerTimeTicksSRA;
  ulSysTime             = ulGetSysTimeDM();
  if( (ulSysTime == 0xffffffffu) || (ulTinitOatLowerSysTimeEndPointSRA == 0xffffffffu)){
    *pulTinitOatTime    = 0xffffffffu;
  }
  else{
    *pulTinitOatTime    = (ulTinitOatLowerSysTimeEndPointSRA - ulSysTime);
  }
  *pbCorrTinitEvent     = bCorrTinitLowerEventSRA;
}

void GetInternalHigherDataSRA( uint8* pucDeltaTinitTh, uint8* pucFastTimeConst, uint32* pulTinitOatTimeTicks, uint32* pulTinitOatTime, boolean* pbCorrTinitEvent){
  uint32 ulSysTime;
  *pucDeltaTinitTh      = ucDeltaTinitHigherThSRA;
  *pucFastTimeConst    = ucFastTimeConstSRA;
  *pulTinitOatTimeTicks = ulTinitOatHigherTimeTicksSRA;
  ulSysTime             = ulGetSysTimeDM();
  if( (ulSysTime == 0xffffffffu) || (ulTinitOatHigherSysTimeEndPointSRA == 0xffffffffu)){
    *pulTinitOatTime    = 0xffffffffu;
  }
  else{
    *pulTinitOatTime    = (ulTinitOatHigherSysTimeEndPointSRA - ulSysTime);
  }
  *pbCorrTinitEvent     = bCorrTinitHigherEventSRA;
}

static void CyclicOATSampleFuncSRA(uint16 ushCurSpeed, Rte_Instance self)
{
  static uint8 ucPermDriveTime = 0x00u;
  static uint8 ucCylicDriveSampleTime = cCyclicDriveTime;
  static uint16 ushCountMins = 0x0000u;
  ushCountMins++;
  if(ushCountMins == 12u){
    ushCountMins = 0x0000u;
    if(ushTimeDiffInMinsSRA < 0xFFFFu){
      ushTimeDiffInMinsSRA++;
    }
  }
  else
  {
    if(0x0002 == ushCountMins)
    {
      if(0x0000u == ushTimeDiffInMinsSRA)
      {
        if((ulGetStopTimeDM()/60) < 0xFFFFu)
        {
          ushTimeDiffInMinsSRA = (uint16)(ulGetStopTimeDM()/60);
        }
        else
        {
          ushTimeDiffInMinsSRA = 0xFFFFu;
        }

      }
    }
  }

  if((ushCurSpeed != 0xffffU) && (ushCurSpeed >= 20u))
  {

    if(ucPermDriveTime < cPermDriveTime)
    {
      ucPermDriveTime++;
    }
  }
  else
  {
    ucPermDriveTime = 0x00;
  }

  if(ucCylicDriveSampleTime < cCyclicDriveTime)
  {
    ucCylicDriveSampleTime++;
  }
  else
  {

    if(FALSE == GETucFilDetActiveEE(self))
    {
      if(cPermDriveTime == ucPermDriveTime)
      {

        CalculateOATavgSRA(self);

        ucCylicDriveSampleTime = 0;
      }
    }
  }
}

static void CalculateOATavgSRA(Rte_Instance self){
  sint8 scCurOAT;
  sint32 slHighResCurOAT, slAvgOAT;
  uint16 ushFilterRatio;
  uint16 ushTimeConst = 0x00;
  scCurOAT = GETscOutdoorTemperatureFZZ();
  slHighResCurOAT = ((sint32)scCurOAT * 1000);
  slAvgOAT = GETslOATavgEE(self);
  if(scCurOAT != (cInvalidOutdoorTemperature)){
    if(slHighResCurOAT >= slAvgOAT){
      if(ucFastTimeConstSRA != 0xFF){
        ushTimeConst = ucFastTimeConstSRA * 12 * 60;
      }
    }
    else{
      if(ucSlowTimeConstSRA != 0xFF){
        ushTimeConst = ucSlowTimeConstSRA * 12 * 60;
      }
    }
    if(0 != ushTimeConst){
      ushFilterRatio = (uint16)(((uint32)ushTimeDiffInMinsSRA * 1000) / ((uint32)ushTimeDiffInMinsSRA + (uint32)ushTimeConst));
      slAvgOAT = (slAvgOAT - (((sint32)ushFilterRatio * ((slAvgOAT - slHighResCurOAT)/1000))));
      PUTslOATavgEE(self, slAvgOAT);
    }
    ushTimeDiffInMinsSRA = 0x0000u;
  }
}

