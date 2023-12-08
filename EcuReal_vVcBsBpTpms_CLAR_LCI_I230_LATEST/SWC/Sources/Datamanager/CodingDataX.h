#ifndef CodingDataX_h
#define CodingDataX_h
/******************************************************************************/
/* File   : CodingDataX.h                                                     */
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
#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cucShortHoldTimeOffValue                              ((uint8)        8)
#define cucLongHoldTimeOffValue                               ((uint8)       19)
#define cushWarnDelayTimerOffValue                            ((uint16) 0xFFFFu)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   boolean bCRdciTPrewarnNc;
   boolean bCRdciMaxThreshold;
   boolean bCRdciPrewarnEnable;
   boolean bCRdciStatInit;
   boolean bCRdciNumPrewarnDetect;
   boolean bCRdciPrewarnIgnition;
   boolean bCRdciPanneBefPos;
   boolean bCRdciFastDeflateEnable;
   boolean bCRdciTyrIdFiltGw;
   boolean bCRdciResetPlausi;
   uint8   ucCRdciTpmsMarket;
   boolean bCRdciSensorForeignAkRdk;
   boolean bCRdciSensorLocSync;
   boolean bCRdciErfsEnable;
   boolean bCRdciTrefSeasonalAdjustment;
   boolean bCRdciDispReset;
   uint8   ucCRdciCorHoldOffTime;
   uint8   ucCRdciTRefShift;
   uint8   ucCRdciUiaThC;
   uint8   ucCRdciUiwThC;
   uint8   ucCRdciUiaThNc;
   uint8   ucCRdciUiwThNc;
   uint8   ucCRdciPanneTh;
   uint8   ucCRdciMinRcpFa;
   uint8   ucCRdciMinRcpRa;
   uint8   ucCRdciDeltaPLR;
   uint8   ucCRdciPInitRangeMax;
   uint8   ucCRdciTimeoutPrewarn;
   uint8   ucCRdciDtAmbPrewarn;
   uint8   ucCRdciDpToIPmin;
   uint8   aucCRdciLearnLocateConfig[2];
   uint8   ucCRdciXminCoolTire;
   uint8   ucCRdciMaxCorTime;
   uint8   ucCRdciMaxCorRcp;
   uint8   ucCRdciThCTol;
   uint8   ucCRdciThNCTol;
   uint8   ucCRdciLongHoldTime;
   uint8   ucCRdciShortHoldTime;
   boolean bCRdciEcoRcpEnable;
   boolean bCRdciDefaultLoadCond;
   uint8   ucCRdciErfsPlacardSource;
   boolean bCRdciDefaultMenuSel;
   uint8   ucCRdciDispConfTimeout;
   boolean bCRdciRidEnable;
   uint8   aucCRdciTrefSeasAdjConfig[4];
   boolean bCRdciSpeedCcmEnable;
   uint16  ushCRdciSpeedCcmTh;
   uint8   ucCRdciSpeedCcmTime;
   uint8   ucCRdciSpeedCcmHyst;
   sint16  sshCRdciSpeedCcmPressOffsetFa;
   sint16  sshCRdciSpeedCcmPressOffsetRa;
   uint8   ucCRdciParkSupExtParkSupConfig;
   uint8   ucCRdciParkSupMobilityLossThValue;
   uint8   ucCRdciParkSupNotifThCValue;
   uint8   ucCRdciParkSupNotifThNcValue;
   uint8   ucCRdciParkSupTolNoTempComp;
   uint8   ucCRdciParkSupTolTempComp;
   uint8   ucCRdciParkSupWarningThCValue;
   uint8   ucCRdciParkSupWarningThNcValue;
}tCodingDataDeclCD;

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
#ifdef __cplusplus
extern "C"
{
#endif
extern boolean bGetCRdciTPrewarnNcCD(void);
extern boolean bGetCRdciMaxThresholdCD(void);
extern boolean bGetCRdciPrewarnEnableCD(void);
extern boolean bGetCRdciStatInitCD(void);
extern boolean bGetCRdciNumPrewarnDetectCD(void);
extern boolean bGetCRdciPrewarnIgnitionCD(void);
extern boolean bGetCRdciPanneBefPosCD(void);
extern boolean bGetCRdciFastDeflateEnableCD(void);
extern boolean bGetCRdciTyrIdFiltGwCD(void);
extern boolean bGetCRdciResetPlausiCD(void);
extern uint8   ucGetCRdciTpmsMarketCD(void);
extern boolean bGetCRdciSensorForeignAkRdkCD(void);
extern boolean bGetCRdciSensorLocSyncCD(void);
extern boolean bGetCRdciErfsEnableCD(void);
extern boolean bGetCRdciTrefSeasonalAdjustmentCD(void);
extern boolean bGetCRdciDispResetCD(void);
extern uint8   ucGetCRdciCorHoldOffTimeCD(void);
extern uint8   ucGetCRdciTRefShiftCD(void);
extern uint8   ucGetCRdciUiaThCCD(void);
extern uint8   ucGetCRdciUiwThCCD(void);
extern uint8   ucGetCRdciUiaThNcCD(void);
extern uint8   ucGetCRdciUiwThNcCD(void);
extern uint8   ucGetCRdciPanneThCD(void);
extern uint8   ucGetCRdciMinRcpFaCD(void);
extern uint8   ucGetCRdciMinRcpRaCD(void);
extern uint8   ucGetCRdciDeltaPLRCD(void);
extern uint8   ucGetCRdciPInitRangeMaxCD(void);
extern uint8   ucGetCRdciTimeoutPrewarnCD(void);
extern uint8   ucGetCRdciDtAmbPrewarnCD(void);
extern uint8   ucGetCRdciDpToIPminCD(void);
extern uint8   ucGetCRdciLearnLocateConfigCD(uint8 ucIx);
extern uint8   ucGetCRdciXminCoolTireCD(void);
extern uint8   ucGetCRdciMaxCorTimeCD(void);
extern uint8   ucGetCRdciMaxCorRcpCD(void);
extern uint8   ucGetCRdciThCTolCD(void);
extern uint8   ucGetCRdciThNCTolCD(void);
extern uint8   ucGetCRdciLongHoldTimeCD(void);
extern uint8   ucGetCRdciShortHoldTimeCD(void);
extern boolean bGetCRdciEcoRcpEnableCD(void);
extern boolean bGetCRdciDefaultLoadCondCD(void);
extern uint8   ucGetCRdciErfsPlacardSourceCD(void);
extern boolean bGetCRdciDefaultMenuSelCD(void);
extern uint8   ucGetCRdciDispConfTimeoutCD(void);
extern boolean bGetCRdciRidEnableCD(void);
extern uint8   ucGetCRdciTrefSeasAdjConfigCD(uint8 ucIx);
extern boolean bGetCRdciSpeedCcmEnableCD(void);
extern uint16  ushGetCRdciSpeedCcmThCD(void);
extern uint8   ucGetCRdciSpeedCcmTimeCD(void);
extern uint8   ucGetCRdciSpeedCcmHystCD(void);
extern sint16  sshGetCRdciSpeedCcmPressOffsetFaCD(void);
extern sint16  sshGetCRdciSpeedCcmPressOffsetRaCD(void);
extern uint8   ucGetCRdciParkSupExtParkSupConfigCD(void);
extern uint8   ucGetCRdciParkSupMobilityLossThValueCD(void);
extern uint8   ucGetCRdciParkSupNotifThCValueCD(void);
extern uint8   ucGetCRdciParkSupNotifThNcValueCD(void);
extern uint8   ucGetCRdciParkSupTolNoTempCompCD(void);
extern uint8   ucGetCRdciParkSupTolTempCompCD(void);
extern uint8   ucGetCRdciParkSupWarningThCValueCD(void);
extern uint8   ucGetCRdciParkSupWarningThNcValueCD(void);
extern void PutCRdciTPrewarnNcCD( boolean bCRdciTPrewarnNc);
extern void PutCRdciMaxThresholdCD( boolean bCRdciMaxThreshold);
extern void PutCRdciPrewarnEnableCD( boolean bCRdciPrewarnEnable);
extern void PutCRdciStatInitCD( boolean bCRdciStatInit);
extern void PutCRdciNumPrewarnDetectCD( boolean bCRdciNumPrewarnDetect);
extern void PutCRdciPrewarnIgnitionCD( boolean bCRdciPrewarnIgnition);
extern void PutCRdciPanneBefPosCD( boolean bCRdciPanneBefPos);
extern void PutCRdciFastDeflateEnableCD( boolean bCRdciFastDeflateEnable);
extern void PutCRdciTyrIdFiltGwCD( boolean bCRdciTyrIdFiltGw);
extern void PutCRdciResetPlausiCD( boolean bCRdciResetPlausi);
extern void PutCRdciTpmsMarketCD(uint8 ucCRdciTpmsMarket);
extern void PutCRdciSensorForeignAkRdkCD( boolean bCRdciSensorForeignAkRdk);
extern void PutCRdciSensorLocSyncCD( boolean bCRdciSensorLocSync);
extern void PutCRdciErfsEnableCD( boolean bCRdciErfsEnable);
extern void PutCRdciTrefSeasonalAdjustmentCD( boolean bCRdciTrefSeasonalAdjustment);
extern void PutCRdciDispResetCD( boolean bCRdciDispReset);
extern void PutCRdciCorHoldOffTimeCD(uint8 ucCRdciCorHoldOffTime);
extern void PutCRdciTRefShiftCD(uint8 ucCRdciTRefShift);
extern void PutCRdciUiaThCCD(uint8 ucCRdciUiaThC);
extern void PutCRdciUiwThCCD(uint8 ucCRdciUiwThC);
extern void PutCRdciUiaThNcCD(uint8 ucCRdciUiaThNc);
extern void PutCRdciUiwThNcCD(uint8 ucCRdciUiwThNc);
extern void PutCRdciPanneThCD(uint8 ucCRdciPanneTh);
extern void PutCRdciMinRcpFaCD(uint8 ucCRdciMinRcpFa);
extern void PutCRdciMinRcpRaCD(uint8 ucCRdciMinRcpRa);
extern void PutCRdciDeltaPLRCD(uint8 ucCRdciDeltaPLR);
extern void PutCRdciPInitRangeMaxCD(uint8 ucCRdciPInitRangeMax);
extern void PutCRdciTimeoutPrewarnCD(uint8 ucCRdciTimeoutPrewarn);
extern void PutCRdciDtAmbPrewarnCD(uint8 ucCRdciDtAmbPrewarn);
extern void PutCRdciDpToIPminCD(uint8 ucCRdciDpToIPmin);
extern void PutCRdciLearnLocateConfigCD(uint8 ucCRdciLearnLocateConfig, uint8 ucIx);
extern void PutCRdciXminCoolTireCD(uint8 ucCRdciXminCoolTire);
extern void PutCRdciMaxCorTimeCD(uint8 ucCRdciMaxCorTime);
extern void PutCRdciMaxCorRcpCD(uint8 ucCRdciMaxCorRcp);
extern void PutCRdciThCTolCD(uint8 ucCRdciThCTol);
extern void PutCRdciThNCTolCD(uint8 ucCRdciThNCTol);
extern void PutCRdciLongHoldTimeCD(uint8 ucCRdciLongHoldTime);
extern void PutCRdciShortHoldTimeCD(uint8 ucCRdciShortHoldTime);
extern void PutCRdciEcoRcpEnableCD( boolean bCRdciEcoRcpEnable);
extern void PutCRdciDefaultLoadCondCD( boolean bCRdciDefaultLoadCond);
extern void PutCRdciErfsPlacardSourceCD(uint8 ucCRdciErfsPlacardSource);
extern void PutCRdciDefaultMenuSelCD( boolean bCRdciDefaultMenuSel);
extern void PutCRdciDispConfTimeoutCD(uint8 ucCRdciDispConfTimeout);
extern void PutCRdciRidEnableCD( boolean bCRdciRidEnable);
extern void PutCRdciTrefSeasAdjConfigCD(uint8 ucCRdciTrefSeasAdjConfig, uint8 ucIx);
extern void PutCRdciSpeedCcmEnableCD( boolean bCRdciSpeedCcmEnable);
extern void PutCRdciSpeedCcmThCD(uint16 ushCRdciSpeedCcmTh);
extern void PutCRdciSpeedCcmTimeCD(uint8 ucCRdciSpeedCcmTime);
extern void PutCRdciSpeedCcmHystCD(uint8 ucCRdciSpeedCcmHyst);
extern void PutCRdciSpeedCcmPressOffsetFaCD( sint16 sshCRdciSpeedCcmPressOffsetFa);
extern void PutCRdciSpeedCcmPressOffsetRaCD( sint16 sshCRdciSpeedCcmPressOffsetRa);
extern void PutCRdciParkSupExtParkSupConfigCD(uint8 ucCRdciParkSupExtParkSupConfig);
extern void PutCRdciParkSupMobilityLossThValueCD(uint8 ucCRdciParkSupMobilityLossThValue);
extern void PutCRdciParkSupNotifThCValueCD(uint8 ucCRdciParkSupNotifThCValue);
extern void PutCRdciParkSupNotifThNcValueCD(uint8 ucCRdciParkSupNotifThNcValue);
extern void PutCRdciParkSupTolNoTempCompCD(uint8 ucCRdciParkSupTolNoTempComp);
extern void PutCRdciParkSupTolTempCompCD(uint8 ucCRdciParkSupTolTempComp);
extern void PutCRdciParkSupWarningThCValueCD(uint8 ucCRdciParkSupWarningThCValue);
extern void PutCRdciParkSupWarningThNcValueCD(uint8 ucCRdciParkSupWarningThNcValue);
extern boolean CheckCodingDataCrcCD(Rte_Instance self);
extern void RestartSystemAfterCodingCD(Rte_Instance self);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

