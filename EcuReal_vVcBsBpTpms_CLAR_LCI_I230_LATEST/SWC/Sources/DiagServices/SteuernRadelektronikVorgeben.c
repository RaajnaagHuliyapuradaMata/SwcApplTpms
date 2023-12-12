/******************************************************************************/
/* File   : SteuernRadelektronikVorgeben.c                                    */
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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "SteuernRadelektronikVorgebenX.h"

#include "WAllocX.h"
#include "uswarn_ifX.h"
#include "walloc_managerX.h"
#include "datamanagerX.h"
#include "state_bzX.h"
#include "state_zkX.h"
#include "WuMonitoringX.h"

#include "EeErfsBlockX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeWarnstatusBlockX.h"

#include "StatusbarX.h"
#include "InitializationX.h"
#include "SeasRcpAdjX.h"
#include "HS_KalibrierereignisX.h"

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
uint8 ucPutSteuernRadelektronikVorgebenDS(Rte_Instance self, uint32 ulReId, uint8 ucRadPos){
   uint8 ucRet;
   uint8 ucLoop;
   if(ucRadPos < cMaxLR){
      if(0xFFFFFFFFu == ulReId){
         ucRet = 0xff;
      }
      else{
         ucRet = ucSetHistoryID(self, ulReId, ucRadPos);
         if(0 == ucRet){
            ucRet = 0xff;
         }
         else{
            SetHistoryChangeBitsDM(self);
            InitBZ(self, FALSE);
            if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
               if(TRUE != GETTyreSelectionActiveEE(self)){
                  SetBitBetriebszustandBZ(cZO_FINISH);
               }
               (void)ucSetAutolocErrorStatusWUM(self, cAUTOLOC_SUCCESSFUL);
            }
            if(TRUE == bGetBitBetriebszustandBZ(cEIGENRAD)){
               if(TRUE != GETTyreSelectionActiveEE(self)){
                  SetBitBetriebszustandBZ(cER_FINISH);
               }
               SetAutoLearnErrorStatusWUM(self, cAUTOLEARN_SUCCESSFUL);
            }
            PUTLastLocStateEE(self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
            ResetWUM(self, (ucRet & 0x0f), cWithoutLowBat, cWithoutWuRelatedDtcs);
            if((uint32) 0 == ulReId){
               (void)ucSetPminFzgAsSetPressureUSWIF(self);
               ResetWUM(self, cAllSlots, cWithLowBat, cWithWuRelatedDtcs);
               (void)ucSetAutolocErrorStatusWUM(self, cAUTOLOC_SUCCESSFUL);
               PUTTyreSelectionBckgrdEE(self, TRUE);
               PUTTyreSelectionActiveEE(self, TRUE);
               SetCalibrationRootCauseDS(self, cCalByDiag);
               StartSBR(self);
               StartSRA(self);
               StartLearnLocateWAM(self);
               ClearLastReceivedReDataArraysDM();
               for(ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
                  PUTucLastWuPressureEE(self, cInvalidREpressure, ucLoop);
                  PUTscLastWuTemperatureEE(self, cInvalidREtemperature, ucLoop);
                  PUTucWheelSensorStatusToNvmMirrorEE(self, cRE_STATUS_NOT_REC, ucLoop);
                  PUTucLastTelegramTypeToNvmMirrorEE(self, cInvalidTelType, ucLoop);
                  PUTucLastSNRToNvmMirrorEE(self, cInvalidSignalToNoiseRatio, ucLoop);
                  PUTushLastPalStatusEE(self, cInvalidRePalStatusMdb, ucLoop);
                  PUTucTimeSinceLastRecEventToNvmMirrorEE(self, 0, ucLoop);
                  PUTucLastBatteryStateToNvmMirrorEE(self, cInvalidBatteryLevel, ucLoop);
               }
               PUTucFBD4CountEE(self, 1);
            }
            ResetWarningsUSWIF(self);
            PUTucLastPosChangedInformationToNvmMirrorEE(self, ucGetIdChangedBitsZK() | ucGetWpChangedBitsZK());
            ucRet = 0x00;
         }
      }
   }
   else{
      ucRet = 0xff;
   }
   return ucRet;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

