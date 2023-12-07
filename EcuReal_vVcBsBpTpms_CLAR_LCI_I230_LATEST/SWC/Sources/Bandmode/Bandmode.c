#include "Bandmode.h"
#include "RID_X.h"
#include "EeErfsBlockX.h"
#include "InitializationX.h"
#include "datamanagerX.h"
#include "HS_KalibrierereignisX.h"
#include "state_bzX.h"

#ifdef _EcuVirtual
static uint16 ushStateBM                          = 0x0000;
static uint8  ucCounterWheelElectronicBM[cAnzRad] = {0, 0, 0, 0};

static boolean bGetOtherBmServiceSetBM   (uint16       ushService);
static void    SaveRidDataAndCompareInBM (Rte_Instance self);
#else
#endif

static void VerifyGutEmpfCtBM(Rte_Instance self){
   const uint16 ushWheelPosOrderConvZ2CW[cAnzRad] = {cushReceptionReFlBM, cushReceptionReFrBM, cushReceptionReRlBM, cushReceptionReRrBM};
         uint8  ucLoop;
         uint8  ucCt = 0;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(ucCounterWheelElectronicBM[ucLoop] >= cucMaxCountWheelElectronicBM){
         SetStateBitBM(ushWheelPosOrderConvZ2CW[ucLoop], FALSE);
         ucCt++;
      }
   }
   if(cAnzRad == ucCt){
      SaveRidDataAndCompareInBM(self);
      if(TRUE == GETTyreSelectionActiveEE(self)){
         SetSolldruckDM(               self, GETSelectedLoadStateEE(self),          GETSelectedTyreIndexEE(self));
         (void)ZoPlausiInitPressINIT(  self, bGetBitBetriebszustandBZ(cZUGEORDNET), GETSelectedTyreIndexEE(self));
         SetCalibrationRootCauseDS(    self, cCalRidNoStatusbar);
         (void)SaveCalibrationEventDS( self);
         PUTTyreSelectionBckgrdEE(     self, FALSE);
         PUTTyreSelectionActiveEE(     self, FALSE);
         SetCalibrationRootCauseDS(    self, cCalInvalid);
      }
   }
}

static boolean bGetOtherBmServiceSetBM(uint16 ushService)
{
   boolean bRet = FALSE;
   uint16 ushOtherServices;

   ushOtherServices = ~ushService;

   if(((ushStateBM & cushAllServiceBitsBM) & ushOtherServices) != 0){
     bRet = TRUE;
   }

   return bRet;
}

void InitBM(uint16 ushState)
{
  const uint16 ushWheelPosOrderConvZ2CW[cAnzRad] = { cushReceptionReFlBM, cushReceptionReFrBM, cushReceptionReRlBM, cushReceptionReRrBM };
   uint8 ucLoop;

   PutStateBM(ushState);

   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(bGetStateBitBM(ushWheelPosOrderConvZ2CW[ucLoop]) == TRUE){
      ucCounterWheelElectronicBM[ucLoop] = 0;
      }
      else{
      ucCounterWheelElectronicBM[ucLoop] = cucMaxCountWheelElectronicBM;
      }
   }
}

void PutStateBM (uint16 ushState)
{
   ushStateBM = ushState;
}

uint16 ushGetStateBM (void)
{
   return ushStateBM;
}

boolean bGetStateBitBM (uint16 ushBitMask)
{
   boolean bRet;

   if((ushStateBM & ushBitMask) == ushBitMask){
    bRet = TRUE;
   }
   else{
    bRet = FALSE;
   }

   return bRet;
}

void SetStateBitBM (uint16 ushBitMask, boolean bState)
{
   if(bState == TRUE){
      ushStateBM |= ushBitMask;
   }
   else{
      ushStateBM &= (uint16) ~ushBitMask;
   }
}

void BandmodeActivateBM (void)
{
  InitBM( (cushResetAllStatusBitsBM | cushBandmodeActivationBM));
}

void BandmodeDeactivateBM (void)
{
  InitBM( cushResetAllStatusBitsBM);
}

boolean bGetBandmodeBM(void)
{
   return bGetStateBitBM ( cushBandmodeActivationBM);
}

void StopServiceBM(void)
{
  InitBM( (cushResetAllStatusBitsBM | cushBandmodeActivationBM));
}

boolean bStartServiceBM(uint16 ushService)
{
   boolean bRet = FALSE;

   if(bGetOtherBmServiceSetBM(ushService) == FALSE){
      if(bGetStateBitBM(ushService) == FALSE){
      InitBM( (cushResetAllStatusBitsBM | cushBandmodeActivationBM | ushService));
      }
      else{
      }
   }
   else{
    bRet = TRUE;
   }

   return bRet;
}

void CycleBandModeServiceBM (Rte_Instance self, boolean bSpeedThresBM)
{
   if(bGetStateBitBM( cushTestEigenradFahrtBM) == TRUE){
    SetStateBitBM ( cushErFahrtVThresBM, bSpeedThresBM);

    VerifyGutEmpfCtBM(self);
   }
   else if(bGetStateBitBM( cushTestEigenradFahrtNoSpeedBM) == TRUE){
    SetStateBitBM ( cushErFahrtVThresBM, TRUE);

    VerifyGutEmpfCtBM(self);
   }
   else{
   }
}

void CountWheelElectronicDataBM(uint8 ucWheelPos)
{
   boolean bState;

   bState = (bGetBandmodeBM() & (bGetStateBitBM ( cushTestEigenradFahrtNoSpeedBM) | (bGetStateBitBM ( cushTestEigenradFahrtBM) & bGetStateBitBM ( cushErFahrtVThresBM))));

   if(bState == TRUE){
      if(ucWheelPos < cAnzRad){
      if(ucCounterWheelElectronicBM[ucWheelPos] < 250){
        ucCounterWheelElectronicBM[ucWheelPos]++;
      }
      }
   }
}

static void SaveRidDataAndCompareInBM(Rte_Instance self)
{
   uint8 AutoIx,CurIx;

  AutoIx = GETSelectedAutoTyreIndexEE(self);
  CurIx = GETSelectedTyreIndexEE(self);

   if((AutoIx == OP_SLCTN_TYR_AVLB_AndererReifen) || (AutoIx != CurIx)){

      if(CheckRearAxisRidDataAvailRID() == TRUE){

      SaveRidDataAndCompareRID(self);
      }
   }
}

