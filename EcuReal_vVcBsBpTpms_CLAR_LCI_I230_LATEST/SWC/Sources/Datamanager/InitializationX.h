#ifndef InitializationX_h
#define InitializationX_h
/******************************************************************************/
/* File   : InitializationX.h                                                 */
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

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8 ucPressure;
   sint8 scTemperature;
}tDeclRatedValuePair;

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
extern void InitRatedValuesDM(Rte_Instance self);
extern void ReStorePinitTinitDM(Rte_Instance self);
extern void StartInitializationProcessDM(Rte_Instance self);
extern uint8 ucGetPWarnMinDM(void);
extern void SetNewRatedValueDM(Rte_Instance self, uint8 ucRatedPres, sint8 scRatedTemp, uint8 ucHistCol);
extern void SetAllNewRatedValueDM(Rte_Instance self);
extern uint8 ucGetPinitTinitDM(uint8 ucSlotNo);
extern sint8 scGetTinitDM(uint8 ucSlotNo);
extern uint8 ucGetPminFzgDM(void);
extern uint8 ErPlausiInitPressINIT(Rte_Instance self, boolean bER, boolean bCalcPinitTinit);
extern uint8 ZoPlausiInitPressINIT(Rte_Instance self, boolean bZO, uint8 ucTyreIndex);
extern void CalcTinitDM(Rte_Instance self, uint8 ucPReifenInit, sint8 scTReifenInit, uint8 ucTRefShift, sint8 scTAinit, uint8* pucPinit, sint8* pscTinit);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

