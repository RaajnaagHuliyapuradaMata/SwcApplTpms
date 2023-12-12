#ifndef _hs_inaktivereignis_X_H
#define _hs_inaktivereignis_X_H
/******************************************************************************/
/* File   : HS_InaktivereignisX.h                                             */
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
#define cMaxSizeIeFiFo 3
#define cIeFiFoEmpty    (uint8)0xFE
#define cDtcInvalid    ((uint8) 255u)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
   cDtcWuMuteFl = 0,
   cDtcWuMuteFr,
   cDtcWuMuteRl,
   cDtcWuMuteRr,
   cDtcUnspecifiedWuMute,
   cDtcWuDefectFl,
   cDtcWuDefectFr,
   cDtcWuDefectRl,
   cDtcWuDefectRr,
   cDtcBandmode,
   cDtcAutoLearningFailed,
   cDtcGatewayOrAntennaError,
   cDtcInputMissing,
   cDtcInputInvalid,
   cDtcInputAliveError,
   cDtcInputCrcError,
   cDtcRdciRfExternalInterference,
   cDtcSpeedSignalFailure,
   cDtcUnspecifiedWfcDefect,
   cDtcGatewayOrAntennaError2ndFBD,
   cDtcGatewayOrAntennaErrorAllFBD,
   cDtcDataPackageError1stFBD,
   cDtcDataPackageError2ndFBD,
   cDtcDataPackageErrorAllFBD,
   cDtc4WrongWuMounted,
   cDtc1To3WrongWuMounted,
   cDtcWuLocalisationFailed,
   cDtcRdciOtherWuSensorType,
   cDtcWuLowBatteryFl,
   cDtcWuLowBatteryFr,
   cDtcWuLowBatteryRl,
   cDtcWuLowBatteryRr
}tWuErrors;

typedef struct{
   uint8 ucErrorNumber;
   uint8 ucIeSent;
}strIeFiFo;

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
extern void ReadInaktivereignisDS(Rte_Instance self, uint8* paucData);
extern void ProcessIeFiFoDS(Rte_Instance self);
extern void InitIeFiFoDS(Rte_Instance self);
extern void IeFiFoWriteEntryDS(Rte_Instance self, uint8 ucErrorNumber);
extern void ClearIeFifoDS(Rte_Instance self);
extern uint8 GetCurrentInactiveReasonDS(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

