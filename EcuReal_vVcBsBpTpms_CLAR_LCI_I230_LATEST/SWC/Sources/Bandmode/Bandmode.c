/******************************************************************************/
/* File   : Bandmode.c                                                        */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "BandmodeX.h"

#include "RID_X.h"
#include "EeErfsBlockX.h"
#include "InitializationX.h"
#include "datamanagerX.h"
#include "HS_KalibrierereignisX.h"
#include "state_bzX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cucMaxCountWheelElectronicBM                                 ((uint8) 1)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint16 ushStateBM                          = 0x0000;
static uint8  ucCounterWheelElectronicBM[cAnzRad] = {0, 0, 0, 0};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static boolean bGetOtherBmServiceSetBM   (uint16       ushService);
static void    SaveRidDataAndCompareInBM (Rte_Instance self);

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
   uint16 ushOtherServices = ~ushService;
   if(0 != ((ushStateBM & cushAllServiceBitsBM) & ushOtherServices)){
      bRet = TRUE;
   }
   return bRet;
}

void InitBM(uint16 ushState){
   const uint16 ushWheelPosOrderConvZ2CW[cAnzRad] = {cushReceptionReFlBM, cushReceptionReFrBM, cushReceptionReRlBM, cushReceptionReRrBM};
   uint8 ucLoop;
   PutStateBM(ushState);
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(TRUE == bGetStateBitBM(ushWheelPosOrderConvZ2CW[ucLoop])){ucCounterWheelElectronicBM[ucLoop] = 0;}
      else                                                        {ucCounterWheelElectronicBM[ucLoop] = cucMaxCountWheelElectronicBM;}
   }
}

void   PutStateBM    (uint16 ushState){       ushStateBM = ushState;}
uint16 ushGetStateBM (void)           {return ushStateBM;}

boolean bGetStateBitBM(uint16 ushBitMask){
   boolean bRet;
   if((ushStateBM & ushBitMask) == ushBitMask){bRet = TRUE;}
   else                                       {bRet = FALSE;}
   return bRet;
}

void SetStateBitBM(uint16 ushBitMask, boolean bState){
   if(TRUE == bState){ushStateBM |= ushBitMask;}
   else              {ushStateBM &= (uint16) ~ushBitMask;}
}

void    BandmodeActivateBM   (void){       InitBM((cushResetAllStatusBitsBM | cushBandmodeActivationBM));}
void    BandmodeDeactivateBM (void){       InitBM(cushResetAllStatusBitsBM);}
boolean bGetBandmodeBM       (void){return bGetStateBitBM(cushBandmodeActivationBM);}
void    StopServiceBM        (void){       InitBM((cushResetAllStatusBitsBM | cushBandmodeActivationBM));}

boolean bStartServiceBM(uint16 ushService){
   boolean bRet = FALSE;
   if(FALSE == bGetOtherBmServiceSetBM(ushService)){
      if(FALSE == bGetStateBitBM(ushService)){InitBM((cushResetAllStatusBitsBM | cushBandmodeActivationBM | ushService));}
      else{}
   }
   else{
      bRet = TRUE;
   }
   return bRet;
}

void CycleBandModeServiceBM (Rte_Instance self, boolean bSpeedThresBM){
        if(TRUE == bGetStateBitBM(cushTestEigenradFahrtBM))       {SetStateBitBM(cushErFahrtVThresBM, bSpeedThresBM); VerifyGutEmpfCtBM(self);}
   else if(TRUE == bGetStateBitBM(cushTestEigenradFahrtNoSpeedBM)){SetStateBitBM(cushErFahrtVThresBM, TRUE);          VerifyGutEmpfCtBM(self);}
   else{}
}

void CountWheelElectronicDataBM(uint8 ucWheelPos){
   boolean bState;
   bState = (bGetBandmodeBM() & (bGetStateBitBM ( cushTestEigenradFahrtNoSpeedBM) | (bGetStateBitBM ( cushTestEigenradFahrtBM) & bGetStateBitBM ( cushErFahrtVThresBM))));
   if(TRUE == bState){
      if(ucWheelPos < cAnzRad){
         if(ucCounterWheelElectronicBM[ucWheelPos] < 250){
           ucCounterWheelElectronicBM[ucWheelPos]++;
         }
      }
   }
}

static void SaveRidDataAndCompareInBM(Rte_Instance self){
   uint8 AutoIx, CurIx;
   AutoIx = GETSelectedAutoTyreIndexEE(self);
   CurIx  = GETSelectedTyreIndexEE(self);
   if((OP_SLCTN_TYR_AVLB_AndererReifen == AutoIx) || (AutoIx != CurIx)){
      if(TRUE == CheckRearAxisRidDataAvailRID()){
         SaveRidDataAndCompareRID(self);
      }
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

