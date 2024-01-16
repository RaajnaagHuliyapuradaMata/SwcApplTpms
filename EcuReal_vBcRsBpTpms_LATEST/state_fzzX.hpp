#pragma once
/******************************************************************************/
/* File   : state_fzzX.hpp                                                    */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cKL_15_EIN                                            ((uint16) 0x0001U)
#define cRS_VTHRES                                            ((uint16) 0x0002U)
#define cFAHRZEUG_FAEHRT                                      ((uint16) 0x0004U)
#define cRUECKWAERTSFAHRT                                     ((uint16) 0x0008U)
#define cMOTOR_LAEUFT                                         ((uint16) 0x0400U)
#define cFZZ_ALLE_BITS                                        ((uint16) 0xffffU)

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
extern void    InitFZZ                     (void);
extern void    SetBitFahrzeugzustandFZZ    (uint16 ushBitMask);
extern void    ClearBitFahrzeugzustandFZZ  (uint16 ushBitMask);
extern void    EvTerminal15OnFZZ           (void);
extern void    EvTerminal15OffFZZ          (void);
extern void    EvVehicleRollingFZZ         (void);
extern void    EvVehicleStandsStillFZZ     (void);
extern void    EvReDiagActiveFZZ           (void);
extern void    EvReDiagInactiveFZZ         (void);
extern void    EvDriveDirectionForwardFZZ  (void);
extern void    EvDriveDirectionBackwardFZZ (void);
extern uint32  GETulSysTimeFZZ             (void);
extern sint8   GETscOutdoorTemperatureFZZ  (void);
extern uint16  GETushSpeedFZZ              (void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void    EvEngineRunningFZZ          (void);
extern void    EvEngineStopedFZZ           (void);
extern uint8   GETucDirectionFZZ           (void);
#endif

extern boolean bGetBitFahrzeugzustandFZZ   (uint16 ushBitMask);
#ifndef CfgProject_dSwitchReSim
#pragma PRQA_NO_SIDE_EFFECTS bGetBitFahrzeugzustandFZZ
#endif

extern uint16  ushGetFahrzeugzustandFZZ    (uint16 ushBitMask);
#ifndef CfgProject_dSwitchReSim
#pragma PRQA_NO_SIDE_EFFECTS ushGetFahrzeugzustandFZZ
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

