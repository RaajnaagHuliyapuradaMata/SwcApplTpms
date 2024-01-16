#pragma once
/******************************************************************************/
/* File   : watcfX.hpp                                                        */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cWATO_STOP_ALARM                                          ((uint8) 0x01)
#define cWATO_START_ALARM                                         ((uint8) 0x02)
#define cWATO_READ_ALARM                                          ((uint8) 0x04)
#define cWATO_BREAK_ALARM                                         ((uint8) 0x08)
#define cWATO_RESTART_ALARM                                       ((uint8) 0x10)

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
extern void InitWATCF(void);
extern void StartWallocTOAlarm(uint8 ucTimeInSec);
extern void StopWallocTOAlarm(void);
extern void ControlWATO(uint8 ucCommand, uint8 ucTimeInSec);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

