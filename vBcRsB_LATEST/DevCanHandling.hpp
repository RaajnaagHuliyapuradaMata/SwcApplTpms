#pragma once
/******************************************************************************/
/* File   : DevCanHandling.hpp                                                */
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
#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"
#include "global.hpp"

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
extern void    DCH_CheckCanDebugRequest        (const Type_SwcApplTpms_stMessageCan* CanDebugRequestMsg);
extern void    DCH_GetCanDebugResponseData     (      Type_SwcApplTpms_stMessageCan* CanDebugResponseMsg);
extern uint8   DCH_MultiplexMsgGetActiveStatus (uint8 ui8_MultiplexNr);
extern void    DCH_Init                        (void);
extern boolean DCH_IsDeveloperModeActive       (void);
extern boolean DCH_IsContinousAPCReadingActive (void);
extern boolean DCH_IsCanDebugEnabled           (void);
extern uint8   DCH_SubmultiplexConfigGetStatus (void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

