/******************************************************************************/
/* File   : CodingData.c                                                      */
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
#include "CodingDataX.h"

#include "crc16X.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeErfsblockX.h"
#include "uswarn_Ifx.h"
#include "WuMonitoringX.h"
#include "SeasRcpAdjX.h"
#include "datamanagerX.h"
#include "HS_KalibrierereignisX.h"
#include "StatusbarX.h"
#include "walloc_managerX.h"
#include "WallocX.h"

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
static tCodingDataDeclCD tCodingDataCD;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
boolean bGetCRdciTPrewarnNcCD                  (void)                                         {return tCodingDataCD.bCRdciTPrewarnNc                  ;}
boolean bGetCRdciMaxThresholdCD                (void)                                         {return tCodingDataCD.bCRdciMaxThreshold                ;}
boolean bGetCRdciPrewarnEnableCD               (void)                                         {return tCodingDataCD.bCRdciPrewarnEnable               ;}
boolean bGetCRdciStatInitCD                    (void)                                         {return tCodingDataCD.bCRdciStatInit                    ;}
boolean bGetCRdciNumPrewarnDetectCD            (void)                                         {return tCodingDataCD.bCRdciNumPrewarnDetect            ;}
boolean bGetCRdciPrewarnIgnitionCD             (void)                                         {return tCodingDataCD.bCRdciPrewarnIgnition             ;}
boolean bGetCRdciPanneBefPosCD                 (void)                                         {return tCodingDataCD.bCRdciPanneBefPos                 ;}
boolean bGetCRdciFastDeflateEnableCD           (void)                                         {return tCodingDataCD.bCRdciFastDeflateEnable           ;}
boolean bGetCRdciTyrIdFiltGwCD                 (void)                                         {return tCodingDataCD.bCRdciTyrIdFiltGw                 ;}
boolean bGetCRdciResetPlausiCD                 (void)                                         {return tCodingDataCD.bCRdciResetPlausi                 ;}
uint8   ucGetCRdciTpmsMarketCD                 (void)                                         {return tCodingDataCD.ucCRdciTpmsMarket                 ;}
boolean bGetCRdciSensorForeignAkRdkCD          (void)                                         {return tCodingDataCD.bCRdciSensorForeignAkRdk          ;}
boolean bGetCRdciSensorLocSyncCD               (void)                                         {return tCodingDataCD.bCRdciSensorLocSync               ;}
boolean bGetCRdciErfsEnableCD                  (void)                                         {return tCodingDataCD.bCRdciErfsEnable                  ;}
boolean bGetCRdciTrefSeasonalAdjustmentCD      (void)                                         {return tCodingDataCD.bCRdciTrefSeasonalAdjustment      ;}
boolean bGetCRdciDispResetCD                   (void)                                         {return tCodingDataCD.bCRdciDispReset                   ;}
uint8   ucGetCRdciCorHoldOffTimeCD             (void)                                         {return tCodingDataCD.ucCRdciCorHoldOffTime             ;}
uint8   ucGetCRdciTRefShiftCD                  (void)                                         {return tCodingDataCD.ucCRdciTRefShift                  ;}
uint8   ucGetCRdciUiaThCCD                     (void)                                         {return tCodingDataCD.ucCRdciUiaThC                     ;}
uint8   ucGetCRdciUiwThCCD                     (void)                                         {return tCodingDataCD.ucCRdciUiwThC                     ;}
uint8   ucGetCRdciUiaThNcCD                    (void)                                         {return tCodingDataCD.ucCRdciUiaThNc                    ;}
uint8   ucGetCRdciUiwThNcCD                    (void)                                         {return tCodingDataCD.ucCRdciUiwThNc                    ;}
uint8   ucGetCRdciPanneThCD                    (void)                                         {return tCodingDataCD.ucCRdciPanneTh                    ;}
uint8   ucGetCRdciMinRcpFaCD                   (void)                                         {return tCodingDataCD.ucCRdciMinRcpFa                   ;}
uint8   ucGetCRdciMinRcpRaCD                   (void)                                         {return tCodingDataCD.ucCRdciMinRcpRa                   ;}
uint8   ucGetCRdciDeltaPLRCD                   (void)                                         {return tCodingDataCD.ucCRdciDeltaPLR                   ;}
uint8   ucGetCRdciPInitRangeMaxCD              (void)                                         {return tCodingDataCD.ucCRdciPInitRangeMax              ;}
uint8   ucGetCRdciTimeoutPrewarnCD             (void)                                         {return tCodingDataCD.ucCRdciTimeoutPrewarn             ;}
uint8   ucGetCRdciDtAmbPrewarnCD               (void)                                         {return tCodingDataCD.ucCRdciDtAmbPrewarn               ;}
uint8   ucGetCRdciDpToIPminCD                  (void)                                         {return tCodingDataCD.ucCRdciDpToIPmin                  ;}
uint8   ucGetCRdciLearnLocateConfigCD          (uint8 ucIx)                                   {return tCodingDataCD.aucCRdciLearnLocateConfig[ucIx]   ;}
uint8   ucGetCRdciXminCoolTireCD               (void)                                         {return tCodingDataCD.ucCRdciXminCoolTire               ;}
uint8   ucGetCRdciMaxCorTimeCD                 (void)                                         {return tCodingDataCD.ucCRdciMaxCorTime                 ;}
uint8   ucGetCRdciMaxCorRcpCD                  (void)                                         {return tCodingDataCD.ucCRdciMaxCorRcp                  ;}
uint8   ucGetCRdciThCTolCD                     (void)                                         {return tCodingDataCD.ucCRdciThCTol                     ;}
uint8   ucGetCRdciThNCTolCD                    (void)                                         {return tCodingDataCD.ucCRdciThNCTol                    ;}
uint8   ucGetCRdciLongHoldTimeCD               (void)                                         {return tCodingDataCD.ucCRdciLongHoldTime               ;}
uint8   ucGetCRdciShortHoldTimeCD              (void)                                         {return tCodingDataCD.ucCRdciShortHoldTime              ;}
boolean bGetCRdciEcoRcpEnableCD                (void)                                         {return tCodingDataCD.bCRdciEcoRcpEnable                ;}
boolean bGetCRdciDefaultLoadCondCD             (void)                                         {return tCodingDataCD.bCRdciDefaultLoadCond             ;}
uint8   ucGetCRdciErfsPlacardSourceCD          (void)                                         {return tCodingDataCD.ucCRdciErfsPlacardSource          ;}
boolean bGetCRdciDefaultMenuSelCD              (void)                                         {return tCodingDataCD.bCRdciDefaultMenuSel              ;}
uint8   ucGetCRdciDispConfTimeoutCD            (void)                                         {return tCodingDataCD.ucCRdciDispConfTimeout            ;}
boolean bGetCRdciRidEnableCD                   (void)                                         {return tCodingDataCD.bCRdciRidEnable                   ;}
uint8   ucGetCRdciTrefSeasAdjConfigCD          (uint8 ucIx)                                   {return tCodingDataCD.aucCRdciTrefSeasAdjConfig[ucIx]   ;}
boolean bGetCRdciSpeedCcmEnableCD              (void)                                         {return tCodingDataCD.bCRdciSpeedCcmEnable              ;}
uint16  ushGetCRdciSpeedCcmThCD                (void)                                         {return tCodingDataCD.ushCRdciSpeedCcmTh                ;}
uint8   ucGetCRdciSpeedCcmTimeCD               (void)                                         {return tCodingDataCD.ucCRdciSpeedCcmTime               ;}
uint8   ucGetCRdciSpeedCcmHystCD               (void)                                         {return tCodingDataCD.ucCRdciSpeedCcmHyst               ;}
sint16  sshGetCRdciSpeedCcmPressOffsetFaCD     (void)                                         {return tCodingDataCD.sshCRdciSpeedCcmPressOffsetFa     ;}
sint16  sshGetCRdciSpeedCcmPressOffsetRaCD     (void)                                         {return tCodingDataCD.sshCRdciSpeedCcmPressOffsetRa     ;}
uint8   ucGetCRdciParkSupExtParkSupConfigCD    (void)                                         {return tCodingDataCD.ucCRdciParkSupExtParkSupConfig    ;}
uint8   ucGetCRdciParkSupMobilityLossThValueCD (void)                                         {return tCodingDataCD.ucCRdciParkSupMobilityLossThValue ;}
uint8   ucGetCRdciParkSupNotifThCValueCD       (void)                                         {return tCodingDataCD.ucCRdciParkSupNotifThCValue       ;}
uint8   ucGetCRdciParkSupNotifThNcValueCD      (void)                                         {return tCodingDataCD.ucCRdciParkSupNotifThNcValue      ;}
uint8   ucGetCRdciParkSupTolNoTempCompCD       (void)                                         {return tCodingDataCD.ucCRdciParkSupTolNoTempComp       ;}
uint8   ucGetCRdciParkSupTolTempCompCD         (void)                                         {return tCodingDataCD.ucCRdciParkSupTolTempComp         ;}
uint8   ucGetCRdciParkSupWarningThCValueCD     (void)                                         {return tCodingDataCD.ucCRdciParkSupWarningThCValue     ;}
uint8   ucGetCRdciParkSupWarningThNcValueCD    (void)                                         {return tCodingDataCD.ucCRdciParkSupWarningThNcValue    ;}
void    PutCRdciTPrewarnNcCD                   (boolean bCRdciTPrewarnNc                     ){       tCodingDataCD.bCRdciTPrewarnNc                  = bCRdciTPrewarnNc                  ;}
void    PutCRdciMaxThresholdCD                 (boolean bCRdciMaxThreshold                   ){       tCodingDataCD.bCRdciMaxThreshold                = bCRdciMaxThreshold                ;}
void    PutCRdciPrewarnEnableCD                (boolean bCRdciPrewarnEnable                  ){       tCodingDataCD.bCRdciPrewarnEnable               = bCRdciPrewarnEnable               ;}
void    PutCRdciStatInitCD                     (boolean bCRdciStatInit                       ){       tCodingDataCD.bCRdciStatInit                    = bCRdciStatInit                    ;}
void    PutCRdciNumPrewarnDetectCD             (boolean bCRdciNumPrewarnDetect               ){       tCodingDataCD.bCRdciNumPrewarnDetect            = bCRdciNumPrewarnDetect            ;}
void    PutCRdciPrewarnIgnitionCD              (boolean bCRdciPrewarnIgnition                ){       tCodingDataCD.bCRdciPrewarnIgnition             = bCRdciPrewarnIgnition             ;}
void    PutCRdciPanneBefPosCD                  (boolean bCRdciPanneBefPos                    ){       tCodingDataCD.bCRdciPanneBefPos                 = bCRdciPanneBefPos                 ;}
void    PutCRdciFastDeflateEnableCD            (boolean bCRdciFastDeflateEnable              ){       tCodingDataCD.bCRdciFastDeflateEnable           = bCRdciFastDeflateEnable           ;}
void    PutCRdciTyrIdFiltGwCD                  (boolean bCRdciTyrIdFiltGw                    ){       tCodingDataCD.bCRdciTyrIdFiltGw                 = bCRdciTyrIdFiltGw                 ;}
void    PutCRdciResetPlausiCD                  (boolean bCRdciResetPlausi                    ){       tCodingDataCD.bCRdciResetPlausi                 = bCRdciResetPlausi                 ;}
void    PutCRdciTpmsMarketCD                   (uint8   ucCRdciTpmsMarket                    ){       tCodingDataCD.ucCRdciTpmsMarket                 = ucCRdciTpmsMarket                 ;}
void    PutCRdciSensorForeignAkRdkCD           (boolean bCRdciSensorForeignAkRdk             ){       tCodingDataCD.bCRdciSensorForeignAkRdk          = bCRdciSensorForeignAkRdk          ;}
void    PutCRdciSensorLocSyncCD                (boolean bCRdciSensorLocSync                  ){       tCodingDataCD.bCRdciSensorLocSync               = bCRdciSensorLocSync               ;}
void    PutCRdciErfsEnableCD                   (boolean bCRdciErfsEnable                     ){       tCodingDataCD.bCRdciErfsEnable                  = bCRdciErfsEnable                  ;}
void    PutCRdciTrefSeasonalAdjustmentCD       (boolean bCRdciTrefSeasonalAdjustment         ){       tCodingDataCD.bCRdciTrefSeasonalAdjustment      = bCRdciTrefSeasonalAdjustment      ;}
void    PutCRdciDispResetCD                    (boolean bCRdciDispReset                      ){       tCodingDataCD.bCRdciDispReset                   = bCRdciDispReset                   ;}
void    PutCRdciCorHoldOffTimeCD               (uint8   ucCRdciCorHoldOffTime                ){       tCodingDataCD.ucCRdciCorHoldOffTime             = ucCRdciCorHoldOffTime             ;}
void    PutCRdciTRefShiftCD                    (uint8   ucCRdciTRefShift                     ){       tCodingDataCD.ucCRdciTRefShift                  = ucCRdciTRefShift                  ;}
void    PutCRdciUiaThCCD                       (uint8   ucCRdciUiaThC                        ){       tCodingDataCD.ucCRdciUiaThC                     = ucCRdciUiaThC                     ;}
void    PutCRdciUiwThCCD                       (uint8   ucCRdciUiwThC                        ){       tCodingDataCD.ucCRdciUiwThC                     = ucCRdciUiwThC                     ;}
void    PutCRdciUiaThNcCD                      (uint8   ucCRdciUiaThNc                       ){       tCodingDataCD.ucCRdciUiaThNc                    = ucCRdciUiaThNc                    ;}
void    PutCRdciUiwThNcCD                      (uint8   ucCRdciUiwThNc                       ){       tCodingDataCD.ucCRdciUiwThNc                    = ucCRdciUiwThNc                    ;}
void    PutCRdciPanneThCD                      (uint8   ucCRdciPanneTh                       ){       tCodingDataCD.ucCRdciPanneTh                    = ucCRdciPanneTh                    ;}
void    PutCRdciMinRcpFaCD                     (uint8   ucCRdciMinRcpFa                      ){       tCodingDataCD.ucCRdciMinRcpFa                   = ucCRdciMinRcpFa                   ;}
void    PutCRdciMinRcpRaCD                     (uint8   ucCRdciMinRcpRa                      ){       tCodingDataCD.ucCRdciMinRcpRa                   = ucCRdciMinRcpRa                   ;}
void    PutCRdciDeltaPLRCD                     (uint8   ucCRdciDeltaPLR                      ){       tCodingDataCD.ucCRdciDeltaPLR                   = ucCRdciDeltaPLR                   ;}
void    PutCRdciPInitRangeMaxCD                (uint8   ucCRdciPInitRangeMax                 ){       tCodingDataCD.ucCRdciPInitRangeMax              = ucCRdciPInitRangeMax              ;}
void    PutCRdciTimeoutPrewarnCD               (uint8   ucCRdciTimeoutPrewarn                ){       tCodingDataCD.ucCRdciTimeoutPrewarn             = ucCRdciTimeoutPrewarn             ;}
void    PutCRdciDtAmbPrewarnCD                 (uint8   ucCRdciDtAmbPrewarn                  ){       tCodingDataCD.ucCRdciDtAmbPrewarn               = ucCRdciDtAmbPrewarn               ;}
void    PutCRdciDpToIPminCD                    (uint8   ucCRdciDpToIPmin                     ){       tCodingDataCD.ucCRdciDpToIPmin                  = ucCRdciDpToIPmin                  ;}
void    PutCRdciLearnLocateConfigCD            (uint8   ucCRdciLearnLocateConfig, uint8 ucIx ){       tCodingDataCD.aucCRdciLearnLocateConfig[ucIx]   = ucCRdciLearnLocateConfig          ;}
void    PutCRdciXminCoolTireCD                 (uint8   ucCRdciXminCoolTire                  ){       tCodingDataCD.ucCRdciXminCoolTire               = ucCRdciXminCoolTire               ;}
void    PutCRdciMaxCorTimeCD                   (uint8   ucCRdciMaxCorTime                    ){       tCodingDataCD.ucCRdciMaxCorTime                 = ucCRdciMaxCorTime                 ;}
void    PutCRdciMaxCorRcpCD                    (uint8   ucCRdciMaxCorRcp                     ){       tCodingDataCD.ucCRdciMaxCorRcp                  = ucCRdciMaxCorRcp                  ;}
void    PutCRdciThCTolCD                       (uint8   ucCRdciThCTol                        ){       tCodingDataCD.ucCRdciThCTol                     = ucCRdciThCTol                     ;}
void    PutCRdciThNCTolCD                      (uint8   ucCRdciThNCTol                       ){       tCodingDataCD.ucCRdciThNCTol                    = ucCRdciThNCTol                    ;}
void    PutCRdciLongHoldTimeCD                 (uint8   ucCRdciLongHoldTime                  ){       tCodingDataCD.ucCRdciLongHoldTime               = ucCRdciLongHoldTime               ;}
void    PutCRdciShortHoldTimeCD                (uint8   ucCRdciShortHoldTime                 ){       tCodingDataCD.ucCRdciShortHoldTime              = ucCRdciShortHoldTime              ;}
void    PutCRdciEcoRcpEnableCD                 (boolean bCRdciEcoRcpEnable                   ){       tCodingDataCD.bCRdciEcoRcpEnable                = bCRdciEcoRcpEnable                ;}
void    PutCRdciDefaultLoadCondCD              (boolean bCRdciDefaultLoadCond                ){       tCodingDataCD.bCRdciDefaultLoadCond             = bCRdciDefaultLoadCond             ;}
void    PutCRdciErfsPlacardSourceCD            (uint8   ucCRdciErfsPlacardSource             ){       tCodingDataCD.ucCRdciErfsPlacardSource          = ucCRdciErfsPlacardSource          ;}
void    PutCRdciDefaultMenuSelCD               (boolean bCRdciDefaultMenuSel                 ){       tCodingDataCD.bCRdciDefaultMenuSel              = bCRdciDefaultMenuSel              ;}
void    PutCRdciDispConfTimeoutCD              (uint8   ucCRdciDispConfTimeout               ){       tCodingDataCD.ucCRdciDispConfTimeout            = ucCRdciDispConfTimeout            ;}
void    PutCRdciRidEnableCD                    (boolean bCRdciRidEnable                      ){       tCodingDataCD.bCRdciRidEnable                   = bCRdciRidEnable                   ;}
void    PutCRdciTrefSeasAdjConfigCD            (uint8   ucCRdciTrefSeasAdjConfig, uint8 ucIx ){       tCodingDataCD.aucCRdciTrefSeasAdjConfig[ucIx]   = ucCRdciTrefSeasAdjConfig          ;}
void    PutCRdciSpeedCcmEnableCD               (boolean bCRdciSpeedCcmEnable                 ){       tCodingDataCD.bCRdciSpeedCcmEnable              = bCRdciSpeedCcmEnable              ;}
void    PutCRdciSpeedCcmThCD                   (uint16  ushCRdciSpeedCcmTh                   ){       tCodingDataCD.ushCRdciSpeedCcmTh                = ushCRdciSpeedCcmTh                ;}
void    PutCRdciSpeedCcmTimeCD                 (uint8   ucCRdciSpeedCcmTime                  ){       tCodingDataCD.ucCRdciSpeedCcmTime               = ucCRdciSpeedCcmTime               ;}
void    PutCRdciSpeedCcmHystCD                 (uint8   ucCRdciSpeedCcmHyst                  ){       tCodingDataCD.ucCRdciSpeedCcmHyst               = ucCRdciSpeedCcmHyst               ;}
void    PutCRdciSpeedCcmPressOffsetFaCD        (sint16  sshCRdciSpeedCcmPressOffsetFa        ){       tCodingDataCD.sshCRdciSpeedCcmPressOffsetFa     = sshCRdciSpeedCcmPressOffsetFa     ;}
void    PutCRdciSpeedCcmPressOffsetRaCD        (sint16  sshCRdciSpeedCcmPressOffsetRa        ){       tCodingDataCD.sshCRdciSpeedCcmPressOffsetRa     = sshCRdciSpeedCcmPressOffsetRa     ;}
void    PutCRdciParkSupExtParkSupConfigCD      (uint8   ucCRdciParkSupExtParkSupConfig       ){       tCodingDataCD.ucCRdciParkSupExtParkSupConfig    = ucCRdciParkSupExtParkSupConfig    ;}
void    PutCRdciParkSupMobilityLossThValueCD   (uint8   ucCRdciParkSupMobilityLossThValue    ){       tCodingDataCD.ucCRdciParkSupMobilityLossThValue = ucCRdciParkSupMobilityLossThValue ;}
void    PutCRdciParkSupNotifThCValueCD         (uint8   ucCRdciParkSupNotifThCValue          ){       tCodingDataCD.ucCRdciParkSupNotifThCValue       = ucCRdciParkSupNotifThCValue       ;}
void    PutCRdciParkSupNotifThNcValueCD        (uint8   ucCRdciParkSupNotifThNcValue         ){       tCodingDataCD.ucCRdciParkSupNotifThNcValue      = ucCRdciParkSupNotifThNcValue      ;}
void    PutCRdciParkSupTolNoTempCompCD         (uint8   ucCRdciParkSupTolNoTempComp          ){       tCodingDataCD.ucCRdciParkSupTolNoTempComp       = ucCRdciParkSupTolNoTempComp       ;}
void    PutCRdciParkSupTolTempCompCD           (uint8   ucCRdciParkSupTolTempComp            ){       tCodingDataCD.ucCRdciParkSupTolTempComp         = ucCRdciParkSupTolTempComp         ;}
void    PutCRdciParkSupWarningThCValueCD       (uint8   ucCRdciParkSupWarningThCValue        ){       tCodingDataCD.ucCRdciParkSupWarningThCValue     = ucCRdciParkSupWarningThCValue     ;}
void    PutCRdciParkSupWarningThNcValueCD      (uint8   ucCRdciParkSupWarningThNcValue       ){       tCodingDataCD.ucCRdciParkSupWarningThNcValue    = ucCRdciParkSupWarningThNcValue    ;}

boolean CheckCodingDataCrcCD(Rte_Instance self){
   uint8*  pCodingData;
   uint16  ushCrc;
   uint16  ushCrcNvm;
   boolean bCodingDataChanged = FALSE;

   pCodingData = (uint8*) &tCodingDataCD;
   ushCrc      = ushCalcCrc16(pCodingData, sizeof(tCodingDataCD));
   ushCrcNvm   = GETushCrcCodingDataEE(self);

   if(ushCrcNvm == ushCrc){
      bCodingDataChanged = FALSE;
   }
   else{
      bCodingDataChanged = TRUE;
      PUTushCrcCodingDataEE(self, ushCrc);
   }

   return bCodingDataChanged;
}

void RestartSystemAfterCodingCD(Rte_Instance self){
   StartSRA(self);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

