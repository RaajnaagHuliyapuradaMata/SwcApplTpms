#include "Initialization.h"
#include "CodingDataX.h"
#include "State_FzzX.h"
#include "USWarn_IfX.h"
#include "state_bzX.h"
#include "datamanagerX.h"
#include "EeCommonBlockX.h"
#include "EeWarnstatusBlockX.h"
#include "wallocX.h"
#include "EeErfsBlockX.h"
#include "InfoTyreX.h"

static sint8 scTinitDM[cAnzRad]               = { cInvalidREtemperature, cInvalidREtemperature, cInvalidREtemperature, cInvalidREtemperature };
static uint8 ucPinitTinitDM[cAnzRad]          = {
                                                  cInvalidREpressure,
                                                  cInvalidREpressure,
                                                  cInvalidREpressure,
                                                  cInvalidREpressure
};

void StartInitializationProcessDM( Rte_Instance self){
  InitRatedValuesDM( self);
  ResetWarningsUSWIF( self);
  (void) ucSetPminFzgAsSetPressureUSWIF( self);
}

void InitRatedValuesDM( Rte_Instance self){
  uint8 ucLoop;
  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    SetNewRatedValueDM( self, cInvalidREpressure, cInvalidREtemperature, ucLoop);
  }
}

void ReStorePinitTinitDM( Rte_Instance self){
  uint8  ucLoop;
  uint8  ucPSollKalt;
  sint8  scTSollKalt;
  uint8  ucPSollWarm;
  sint8  scTSollWarm;
  uint16 ushMSoll_l;
  uint8  ucEnvP_l;
  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    if( ucGetPTSollUSWIF( self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, ucLoop) == cRetOk){
      if( (ucPSollKalt == cInvalidREpressure) || (scTSollKalt == cInvalidREtemperature)){
        ucPinitTinitDM[ucLoop] = ucGetPminFzgDM();
        scTinitDM[ucLoop]      = GETscTAinitValEE( self);
      }else{
        ucPinitTinitDM[ucLoop] = ucPSollKalt;
        scTinitDM[ucLoop]      = scTSollKalt;
      }
    }else{
      ucPinitTinitDM[ucLoop] = ucGetPminFzgDM();
      scTinitDM[ucLoop]      = GETscTAinitValEE( self);
    }
  }
}

uint8 ucGetPWarnMinDM(void){
  uint8 ucRetVal;
  if( ucGetCRdciTpmsMarketCD() == cMARKET_US){
    ucRetVal = cPWarnMinUSbar;
  }else{
    ucRetVal = cPWarnMinEUbar;
  }
  return ucRetVal;
}

void SetNewRatedValueDM( Rte_Instance self, uint8 ucRatedPres, sint8 scRatedTemp, uint8 ucHistCol){
  sint8 scTAmb;
  if(ucHistCol < cAnzRad){
    if( (ucRatedPres == cInvalidREpressure) || (scRatedTemp == cInvalidREtemperature)){
	    scTinitDM[ucHistCol]      = cInvalidREtemperature;
	    ucPinitTinitDM[ucHistCol] = cInvalidREpressure;
    }
    else{
	    if( (ucPinitTinitDM[ucHistCol] == cInvalidREpressure) || (scTinitDM[ucHistCol] == cInvalidREtemperature)){
        scTAmb = GETscTAmbValEE( self);
        PUTscTAinitValEE( self, scTAmb);
			  CalcTinitDM( self, ucRatedPres, scRatedTemp, ucGetCRdciTRefShiftCD(), scTAmb, &ucPinitTinitDM[ucHistCol], &scTinitDM[ucHistCol]);
	    }
    }
	}
}

void SetAllNewRatedValueDM( Rte_Instance self){
  uint8 ucLoop;
  for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    SetNewRatedValueDM( self, ucGetRePressureRelDM( ucLoop), scGetReTemperatureCentDM( ucLoop), ucLoop);
  }
}

void CalcTinitDM( Rte_Instance self, uint8 ucPReifenInit, sint8 scTReifenInit, uint8 ucTRefShift, sint8 scTAinit, uint8* pucPinit, sint8* pscTinit){
  sint16 sshTinit;
  if( (ucTRefShift == (uint8) 0xFF) || (scTAinit == cInvalidOutdoorTemperature)){
    *pucPinit = ucPReifenInit;
    *pscTinit = scTReifenInit;
  }else{
    sshTinit = (sint16) ((sint16) ucTRefShift * scTReifenInit) + ((sint16) (100 - ucTRefShift) * scTAinit);
    if( sshTinit < 0){
      *pscTinit = (sint8) ((sshTinit - 50) / 100);
    }else{
      *pscTinit = (sint8) ((sshTinit + 50) / 100);
    }

    if( scTReifenInit < *pscTinit)
    {
      *pscTinit = scTReifenInit;
    }else{
      if( *pscTinit < (scTReifenInit - 15))
      {
        *pscTinit = scTReifenInit - 15;
      }
    }

    *pucPinit = (uint8) (((((((uint32) (ucPReifenInit + GETucPAmbValEE( self)) * (uint32) (*pscTinit + 273)) * 10) / (uint32) (scTReifenInit + 273)) + 5) / 10) - GETucPAmbValEE( self));
  }
}

sint8 scGetTinitDM( uint8 ucSlotNo){
  sint8 sRet;
  if(ucSlotNo < cAnzRad){
    sRet = scTinitDM[ucSlotNo];
  }
  else{
    sRet = cInvalidREtemperature;
  }
  return sRet;
}

uint8 ucGetPinitTinitDM( uint8 ucSlotNo){
  uint8 uRet;
  if(ucSlotNo < cAnzRad){
    uRet = ucPinitTinitDM[ucSlotNo];
  }
  else{
    uRet = cInvalidREpressure;
  }
  return uRet;
}

uint8 ucGetPminFzgDM(void){
  uint8 ucPminFzg;
  if( ucGetCRdciMinRcpFaCD() < ucGetCRdciMinRcpRaCD()){
    ucPminFzg = ucGetCRdciMinRcpFaCD();
  }else{
    ucPminFzg = ucGetCRdciMinRcpRaCD();
  }
  return ucPminFzg;
}

uint8 ErPlausiInitPressINIT( Rte_Instance self, boolean bER, boolean bCalcPinitTinit){
  uint8   ucRet = TRUE;
  uint8   ucLoop;
  uint8   uxMaxInitPress = 0x00;
  uint8   ucPMin;
  boolean bFlag = FALSE;
  if( bER == TRUE){
    if( bCalcPinitTinit == TRUE){
      SetAllNewRatedValueDM( self);
      bFlag = TRUE;
    }else{
      for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        if( (ucPinitTinitDM[ucLoop] == cInvalidREpressure) || (scTinitDM[ucLoop] == cInvalidREtemperature)){
          SetNewRatedValueDM( self, ucGetRePressureRelDM(ucLoop), scGetReTemperatureCentDM(ucLoop), ucLoop);
          bFlag = TRUE;
        }
      }
    }
    if( bFlag == TRUE){
      ucPMin = ucGetPminFzgDM();
      for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        if((ucPinitTinitDM[ucLoop] > uxMaxInitPress) && (ucPinitTinitDM[ucLoop] != cInvalidREpressure)){
          uxMaxInitPress = ucPinitTinitDM[ucLoop];
        }
      }
      for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        if(ucPinitTinitDM[ucLoop] != cInvalidREpressure){
          if((uxMaxInitPress - ucPinitTinitDM[ucLoop]) > ucGetCRdciPInitRangeMaxCD()){
            ucPinitTinitDM[ucLoop]  = (uxMaxInitPress - ucGetCRdciPInitRangeMaxCD());
            ucRet = FALSE;
          }
          if(ucPinitTinitDM[ucLoop] < ucPMin){
            if(ucPinitTinitDM[ucLoop] < (ucPMin - ucGetCRdciDpToIPminCD())){
              PUTPlausiInitErrorEE( self, TRUE);
            }
            ucPinitTinitDM[ucLoop] = ucPMin;
            ucRet = FALSE;
          }
        }
      }
      for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        (void) ucCfgReInitSingleUSWIF( self, ucPinitTinitDM[ucLoop], scTinitDM[ucLoop], ucLoop, cRadPosUndef);
        NotificationITY( self, cNotifyRcpChangedITY, ucLoop);
      }
    }
  }
  return ucRet;
}

uint8 ZoPlausiInitPressINIT( Rte_Instance self, boolean bZO, uint8 ucTyreIndex){
  uint8   ucRet = TRUE;
  uint8   ucLoop;
  uint8   ucPMin, ucDiff;
  uint8   ucPInitAtPos[cAnzRad];
  if( bZO == TRUE){
    if( ucTyreIndex == OP_SLCTN_TYR_AVLB_AndererReifen){
      ucRet = ErPlausiInitPressINIT( self, bGetBitBetriebszustandBZ(cEIGENRAD), FALSE);
      ucPInitAtPos[cRadPosVL] = ucPinitTinitDM[ucGetColOfWP(cRadPosVL)];
      ucPInitAtPos[cRadPosVR] = ucPinitTinitDM[ucGetColOfWP(cRadPosVR)];
      ucPInitAtPos[cRadPosHL] = ucPinitTinitDM[ucGetColOfWP(cRadPosHL)];
      ucPInitAtPos[cRadPosHR] = ucPinitTinitDM[ucGetColOfWP(cRadPosHR)];
      if((ucPInitAtPos[cRadPosVL] != cInvalidREpressure) && (ucPInitAtPos[cRadPosVR] != cInvalidREpressure)){
        if(ucPInitAtPos[cRadPosVL] > ucPInitAtPos[cRadPosVR]){
          ucDiff = (ucPInitAtPos[cRadPosVL] - ucPInitAtPos[cRadPosVR]);
          if( ucDiff > ucGetCRdciDeltaPLRCD()){
            ucPInitAtPos[cRadPosVR] = ucPInitAtPos[cRadPosVL] - ucGetCRdciDeltaPLRCD();
            ucRet = FALSE;
          }
        }
        else{
          ucDiff = (ucPInitAtPos[cRadPosVR] - ucPInitAtPos[cRadPosVL]);
          if( ucDiff > ucGetCRdciDeltaPLRCD()){
            ucPInitAtPos[cRadPosVL] = ucPInitAtPos[cRadPosVR] - ucGetCRdciDeltaPLRCD();
            ucRet = FALSE;
          }
        }
      }
      if((ucPInitAtPos[cRadPosHL] != cInvalidREpressure) && (ucPInitAtPos[cRadPosHR] != cInvalidREpressure)){
        if(ucPInitAtPos[cRadPosHL] > ucPInitAtPos[cRadPosHR]){
          ucDiff = (ucPInitAtPos[cRadPosHL] - ucPInitAtPos[cRadPosHR]);
          if( ucDiff > ucGetCRdciDeltaPLRCD()){
            ucPInitAtPos[cRadPosHR] = ucPInitAtPos[cRadPosHL] - ucGetCRdciDeltaPLRCD();
            ucRet = FALSE;
          }
        }
        else{
          ucDiff = (ucPInitAtPos[cRadPosHR] - ucPInitAtPos[cRadPosHL]);
          if( ucDiff > ucGetCRdciDeltaPLRCD()){
            ucPInitAtPos[cRadPosHL] = ucPInitAtPos[cRadPosHR] - ucGetCRdciDeltaPLRCD();
            ucRet = FALSE;
          }
        }
      }
      for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        if(ucLoop < cRadPosHL){
          ucPMin = ucGetCRdciMinRcpFaCD();
        }
        else{
          ucPMin = ucGetCRdciMinRcpRaCD();
        }
        if(ucPInitAtPos[ucLoop] < ucPMin){
          if(ucPInitAtPos[ucLoop] < (ucPMin - ucGetCRdciDpToIPminCD())){
            PUTPlausiInitErrorEE( self, TRUE);
          }
          ucPInitAtPos[ucLoop] = ucPMin;
          ucRet = FALSE;
        }
        ucPinitTinitDM[ucGetColOfWP(ucLoop)] = ucPInitAtPos[ucLoop];
      }
      for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        (void) ucCfgReInitSingleUSWIF( self, ucPinitTinitDM[ucLoop], scTinitDM[ucLoop], ucLoop, ucGetWPOfColWAL( ucLoop));
        NotificationITY( self, cNotifyRcpChangedITY, ucLoop);
      }
    }else{
      for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
        if( (ucPinitTinitDM[ucLoop] == cInvalidREpressure) || (scTinitDM[ucLoop] == cInvalidREtemperature)){
          ReStorePinitTinitDM( self);
        }
        (void) ucCfgReInitSingleUSWIF( self, ucPinitTinitDM[ucLoop], scTinitDM[ucLoop], ucLoop, ucGetWPOfColWAL( ucLoop));
        NotificationITY( self, cNotifyRcpChangedITY, ucLoop);
      }
    }
  }

  return ucRet;
}

