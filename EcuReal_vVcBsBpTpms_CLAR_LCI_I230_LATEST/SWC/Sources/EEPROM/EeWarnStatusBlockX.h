#ifndef EeWarnStatusBlockX_h
#define EeWarnStatusBlockX_h
/******************************************************************************/
/* File   : EeWarnStatusBlockX.h                                              */
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
#include "TSS_StdX.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "USWarn_ifX.h"
#include "InitializationX.h"
#include "TAmbFiltX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct WarnStatusNvmBlock{
   uint8                 ucInitialize;
   uint8                 ucWS;
   tCalibrationTab       tCD;
   uint8                 ucTS;
  WarnConfigArrayType   aucCB;
  WarnBitArrayType      aucWarnStatus;
   ShortTimerArrayType   ushWarnStatusShortTimer;
  LongTimerArrayType    ushWarnStatusLongTimer;
   TAmbientValueType     scTAinitValue;
   PhySensorTyrePresType ucLastWuPressure[cAnzRad];
   PhySensorTyreTempType scLastWuTemperature[cAnzRad];
   uint32                ulTinitOatLowerTimeStart;
   uint32                ulTinitOatHigherTimeStart;
   boolean               bCorrTinitLowerEvent;
   boolean               bCorrTinitHigherEvent;
   uint32                ulCoolingCaptTime;
}tWarnStatusNvmBlockType;

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
extern void                   InitWarnStatusBlockEE(Rte_Instance self);
extern void                   SetWarnStatusBlockUpdateFlagEE(void);
extern boolean                bGetWarnStatusBlockUpdateFlagEE(void);
extern void                   ClearWarnStatusBlockUpdateFlagEE(void);
extern uint8                  GETucWarnStatusBlockInitializeEE(Rte_Instance self);
extern void                   PUTucWarnStatusBlockInitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern void                   GETucWsEE(Rte_Instance self, uint8* x);
extern void                   PUTucWsEE(Rte_Instance self, uint8 x, boolean bUpdateOnEvent);
extern void                   GETtCdEE(Rte_Instance self, tCalibrationTab * x);
extern void                   PUTtCdInitValEE(Rte_Instance self, boolean bUpdateOnEvent);
extern void                   PUTtCdEE(Rte_Instance self, const tCalibrationTab * x, boolean bUpdateOnEvent);
extern void                   GETucTsEE(Rte_Instance self, uint8* x);
extern void                   PUTucTsEE(Rte_Instance self, uint8 x, boolean bUpdateOnEvent);
extern void                   GETaucCbEE(Rte_Instance self, WarnConfigArrayType * x);
extern void                   PUTaucCbInitValEE(Rte_Instance self, boolean bUpdateOnEvent);
extern void                   PUTaucCbEE(Rte_Instance self, const WarnConfigArrayType * x, boolean bUpdateOnEvent);
extern void                   GETaucWarnTypeArrayEE(Rte_Instance self, WarnBitArrayType * x);
extern void                   PUTaucWarnTypeArrayInitValEE(Rte_Instance self, boolean bUpdateOnEvent);
extern void                   PUTaucWarnTypeArrayEE(Rte_Instance self, const WarnBitArrayType * x, boolean bUpdateOnEvent);
extern void                   GETaushShortTimerEE(Rte_Instance self, ShortTimerArrayType * x);
extern void                   PUTaushShortTimerInitValEE(Rte_Instance self, boolean bUpdateOnEvent);
extern void                   PUTaushShortTimerEE(Rte_Instance self, const ShortTimerArrayType * x, boolean bUpdateOnEvent);
extern void                   GETaushLongTimerEE(Rte_Instance self, LongTimerArrayType * x);
extern void                   PUTaushLongTimerInitValEE(Rte_Instance self, boolean bUpdateOnEvent);
extern void                   PUTaushLongTimerEE(Rte_Instance self, const LongTimerArrayType * x, boolean bUpdateOnEvent);
extern sint8                  GETscTAinitValEE(Rte_Instance self);
extern void                   PUTscTAinitValEE(Rte_Instance self, sint8 x);
extern PhySensorTyrePresType  GETucLastWuPressureEE(Rte_Instance self, uint8 i);
extern void                   PUTucLastWuPressureEE(Rte_Instance self, PhySensorTyrePresType x, uint8 i);
extern PhySensorTyreTempType  GETscLastWuTemperatureEE(Rte_Instance self, uint8 i);
extern void                   PUTscLastWuTemperatureEE(Rte_Instance self, PhySensorTyreTempType x, uint8 i);
extern uint32                 GETulTinitOatLowerTimeStartEE(Rte_Instance self);
extern void                   PUTulTinitOatLowerTimeStartEE(Rte_Instance self, uint32 x);
extern uint32                 GETulTinitOatHigherTimeStartEE(Rte_Instance self);
extern void                   PUTulTinitOatHigherTimeStartEE(Rte_Instance self, uint32 x);
extern boolean                GETbCorrTinitLowerEventEE(Rte_Instance self);
extern void                   PUTbCorrTinitLowerEventEE(Rte_Instance self, boolean x);
extern boolean                GETbCorrTinitHigherEventEE(Rte_Instance self);
extern void                   PUTbCorrTinitHigherEventEE(Rte_Instance self, boolean x);
extern uint32                 GETulCoolingCaptTimeEE(Rte_Instance self);
extern void                   PUTulCoolingCaptTimeEE(Rte_Instance self, uint32 x);

#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

