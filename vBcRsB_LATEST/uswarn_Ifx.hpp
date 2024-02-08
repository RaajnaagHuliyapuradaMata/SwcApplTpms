#pragma once
/******************************************************************************/
/* File   : uswarn_Ifx.hpp                                                    */
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
#include "uswarnX.hpp"
#include "Tpms_Rte_Data_Type.hpp"

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
extern uint8   ClearPosUSWIF           (void);
extern void    ResetWarningsUSWIF      (void);
extern uint8   NewPositionsUSWIF       (const uint8* pucRadPos);
extern uint8   GetPTSollUSWIF          (      uint8* pucPressure, sint8* pscTemperature, uint8 ucZomPos);
extern uint8   CfgReInitSingleUSWIF    (      uint8  ucPressure, sint8 scTemperature, uint8 ucZomPos);
extern uint8   ucCfgPMinUSWIF          (      uint8  ucPMin);
extern uint8   CfgPSollMinAtIdUSWIF    (      uint8  ucPressure, uint8 ucZomPos);
extern uint8   ResetWarnVectorUSWIF    (      uint8  ucZomPos);
extern uint8   ClearWarnOfIdUSWIF      (      uint8  ucZomPos);
extern uint8   GetWarnOfIdUSWIF        (      uint8* pucWarnOfId);
extern uint8   GetPWarmUSWIF           (      uint8* pucPressure, sint8 *pscTemperature, uint8 ucZomPos);
extern uint8   ucWAlgoPrePara          (      uint8  ucPWarnMin, uint8 ucPSollMinVA, uint8 ucPSollMinHA);
extern boolean DynWarnResetCond        (      uint8  ActPress, uint8 WarnPress, uint8 ZomPos);
extern uint8   GetPosOfIdIFH           (      uint8  ucIdPos, uint8* pucCarMountedPos);
extern uint8   GetIdOfPosIFH           (      uint8  ucPos, uint8* pucIdOfCarMountedPos);
extern void    ResetOldWarningsByNewEr (      uint8  ucErChangeState, uint8 ucMaxErNumber);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

