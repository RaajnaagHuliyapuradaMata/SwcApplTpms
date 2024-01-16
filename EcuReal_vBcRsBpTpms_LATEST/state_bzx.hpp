#pragma once
/******************************************************************************/
/* File   : state_bzx.hpp                                                     */
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
#define cER_FINISH                                             ((uint16) 0x0001)
#define cTO_MUCH_RE                                            ((uint16) 0x0002)
#define cER_LEARNING                                           ((uint16) 0x0004)
#define cEIGENRAD                                              ((uint16) 0x0008)
#define cZUGEORDNET                                            ((uint16) 0x0010)
#define cWA_FINISH                                             ((uint16) 0x0020)
#define cHIST_PRELOAD                                          ((uint16) 0x0040)
#define cZO_FINISH                                             ((uint16) 0x0080)
#define cWA_STARTED                                            ((uint16) 0x0100)
#define cRESERVED_BIT9                                         ((uint16) 0x0200)
#define cDTC_INACTIVE                                          ((uint16) 0x0400)
#define cTEILEIGENRAD                                          ((uint16) 0x0800)
#define cZO_TIMEOUT                                            ((uint16) 0x1000)
#define cALL_ER_PRESSURE_RX                                    ((uint16) 0x2000)
#define cSEND_RE_DATA_ON_CAN                                   ((uint16) 0x4000)
#define cRESERVED_BIT15                                        ((uint16) 0x8000)
#define cBZ_ALLE_BITS                                          ((uint16) 0xffff)

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
extern void    InitBZ                    (void);
extern void    SetBitBetriebszustandBZ   (uint16 ushBitMask);
extern void    ClearBitBetriebszustandBZ (uint16 ushBitMask);
extern void    EvVehicleSpeedChangedBZ   (uint16 ushNewVehicleSpeed);

extern boolean bGetBitBetriebszustandBZ  (uint16 ushBitMask);
#ifndef CfgProject_dSwitchReSim
#pragma PRQA_NO_SIDE_EFFECTS bGetBitBetriebszustandBZ
#endif

extern uint16  ushGetBetriebszustandBZ   (uint16 ushBitMask);
#ifndef CfgProject_dSwitchReSim
#pragma PRQA_NO_SIDE_EFFECTS ushGetBetriebszustandBZ
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

