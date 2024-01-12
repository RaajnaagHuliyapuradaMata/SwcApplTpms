#pragma once
/******************************************************************************/
/* File   : REDiagX.hpp                                                       */
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
#include "CfgSwcApplTpms.hpp"
#include "tss_stdx.hpp"


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
extern const uint8 ucWUDefectERRc[cAnzRad+1];
extern const uint8 ucWUFailERRc[cAnzRad+1];
extern const uint8 ucWULowLifeTimeERRc[cAnzRad+1];

#ifdef js_ReHighTemperatureDiag_230312
extern const uint8 ucWUTemperatureERRc[cAnzRad+1];
#endif

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void ResetWUFailedErrRD(uint8 ucIx);
extern boolean SetWUFailedErrRD(uint16 CounterValue, uint8 ucIx);
extern void CntWUDefectRD(uint8 ZomPos);
extern void ResetWUDefectRD(uint8 ZomPos);

extern uint8 GetWUDefectRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWUDefectRD

#ifdef js_ReHighTemperatureDiag_230312
extern void CntWUHighTempRD(uint8 ZomPos);
extern void ResetWUHighTempRD(uint8 ZomPos);

extern uint8 GetWUHighTempRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWUHighTempRD
#endif

extern void CntWULowLifeTimeRD(uint8 ZomPos);
extern void ResetWULowLifeTimeRD(uint8 ZomPos);
extern void ResetWULowLifeTimeCounter(uint8 ZomPos);

extern uint8 GetWULowLifeTimeRD(uint8 ZomPos);
#pragma PRQA_NO_SIDE_EFFECTS GetWULowLifeTimeRD

#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

