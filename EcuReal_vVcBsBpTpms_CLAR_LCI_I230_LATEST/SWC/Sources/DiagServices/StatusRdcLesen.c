/******************************************************************************/
/* File   : StatusRdcLesen.c                                                  */
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
#include "StatusRdcLesenX.h"
#include "State_BzX.h"
#include "State_FzzX.h"
#include "DataManagerX.h"
#include "EeDiagBlockX.h"
#include "EeErfsBlockX.h"
#include "UsWarn_IFX.h"
#include "BandmodeX.h"
#include "InfoTyreX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void GetStatusRdcLesenDS(Rte_Instance self, uint8* pucData){
   uint8         ucHardWarning;
   uint8         ucWarningState;
   uint8         ucLoop;
   if(bGetBandmodeBM() == TRUE){
    pucData[cucIxStatEigenraederBekannt]  = (uint8) bGetBitBetriebszustandBZ( cEIGENRAD);
    pucData[cucIxStatRadposErBekannt]     = (uint8) bGetBitBetriebszustandBZ( cZUGEORDNET);
   }
   else{
    pucData[cucIxStatEigenraederBekannt]  = (uint8) bGetBitBetriebszustandBZ( cER_FINISH);
    pucData[cucIxStatRadposErBekannt]     = (uint8) bGetBitBetriebszustandBZ( cZO_FINISH);
   }

   if(bGetBitBetriebszustandBZ( cDTC_INACTIVE) == TRUE){
    pucData[cucIxStatDtcInactive]         = (uint8) TRUE;
   }
   else{
    pucData[cucIxStatDtcInactive]         = (uint8) FALSE;
   }
  pucData[cucIxStatDtcInactive] |= (uint8) (ushGetStateBM() & cushAllReceptionBitsBM);
  pucData[cucIxStatKalAnforderungAktiv] = (uint8) GETTyreSelectionActiveEE(self);
  pucData[cucIxStatRadZuordnungTimeout] = (uint8) bGetBitBetriebszustandBZ( cZO_TIMEOUT);
  pucData[cucIxStatBandmodeAktiv]       = (uint8) bGetBandmodeBM();

   if(bGetStateBitBM( cushTestEigenradFahrtBM) == TRUE){
    pucData[cucIxStatTestEigenradFahrt] = 1;
   }
   else if(bGetStateBitBM( cushTestEigenradFahrtNoSpeedBM) == TRUE){
    pucData[cucIxStatTestEigenradFahrt] = 1;
   }
   else{
    pucData[cucIxStatTestEigenradFahrt] = 0;
   }

  pucData[cucIxStatErFahrtVthresAkiv]   = (uint8) bGetStateBitBM ( cushErFahrtVThresBM);
  pucData[cucIxStatBmTimeoutActive]     = 0;

   ucHardWarning  = GETucWarningGroupTM( cucWT_GrpPanne);
   ucHardWarning |= GETucWarningGroupTM( cucWT_GrpPmin);
   ucHardWarning |= GETucWarningGroupTM( cucWT_GrpPwarn);

   if(bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE){
    pucData[cucIxStatHarteWarnungUnspezifischAktiv] = (uint8) 0x00;

      for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if((ucHardWarning & (uint8) (0x01 << ucLoop)) == 0){

        ucWarningState = 0x00;
      }
      else{

        ucWarningState = 0x01;
      }

      if(ucLoop == cRadPosVL){
        pucData[cucIxStatHarteWarnungVlAktiv] = ucWarningState;
      }else if(ucLoop == cRadPosVR){
        pucData[cucIxStatHarteWarnungVrAktiv] = ucWarningState;
      }else if(ucLoop == cRadPosHL){
        pucData[cucIxStatHarteWarnungHlAktiv] = ucWarningState;
      }
      else{
        pucData[cucIxStatHarteWarnungHrAktiv] = ucWarningState;
      }
      }
   }
   else{
    pucData[cucIxStatHarteWarnungVlAktiv] = (uint8) 0x00;
    pucData[cucIxStatHarteWarnungVrAktiv] = (uint8) 0x00;
    pucData[cucIxStatHarteWarnungHlAktiv] = (uint8) 0x00;
    pucData[cucIxStatHarteWarnungHrAktiv] = (uint8) 0x00;

      if(bGetBitBetriebszustandBZ( cEIGENRAD) == TRUE){
      if(ucHardWarning == 0){
        pucData[cucIxStatHarteWarnungUnspezifischAktiv] = (uint8) 0x00;
      }
      else{

        pucData[cucIxStatHarteWarnungUnspezifischAktiv] = (uint8) 0x01;
      }
      }
      else{
      pucData[cucIxStatHarteWarnungUnspezifischAktiv] = (uint8) 0x00;
      }
   }

  pucData[cucIxStatKl15Ein] = (uint8) bGetBitFahrzeugzustandFZZ( cKL_15_EIN);
  pucData[cucIxStatFzgFaehrt] = (uint8) bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT);

   if((ushGetStateBM() & cushAllReceptionBitsBM) == 0x0000){
    pucData[cucIxStatErkennungAlleRe] = (uint8) TRUE;
   }
   else{
    pucData[cucIxStatErkennungAlleRe] = (uint8) FALSE;
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

