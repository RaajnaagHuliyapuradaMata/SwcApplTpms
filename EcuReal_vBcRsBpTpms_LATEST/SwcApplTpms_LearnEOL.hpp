#pragma once
/******************************************************************************/
/* File   : SwcApplTpms_LearnEOL.hpp                                          */
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
#include "tss_stdx.hpp"
#include "Tpms_Rte_Data_Type.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define EOL_ROUT_NEVER_STARTED            0x00U
#define EOL_ROUT_RUNNING                  0x01U
#define EOL_ROUT_FINISHED_SUCCESSFULLY    0x02U
#define EOL_ROUT_RESERVED                 0x03U
#define EOL_ROUT_STOPPED_ON_REQUEST       0x04U
#define EOL_ROUT_START_WRONG_PARAM        0x05U
#define EOL_ROUT_ENDED_WITH_ERROR         0x07U
#define EOL_ROUTINE_ACTIVE                TRUE
#define EOL_ROUTINE_INACTIVE              FALSE

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
extern void    EOL_InitLearnRoutine                (void);
extern uint8   EOL_StartLearnRoutine               (uint8 ucLearnRoutineTimeoutValue);
extern void    EOL_ResetLearnRoutine               (void);
extern boolean EOL_CheckPeriodicLearnRoutineStatus (void);
extern uint8   EOL_GetStatusEOLRoutine             (void);
extern void    EOL_PutStatusEOLRoutine             (uint8 u8NewStatus);
extern uint8   EOL_GetEOLRoutineActive             (void);
extern void    EOL_PutEOLRoutineActive             (uint8 ucNewStatus);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

