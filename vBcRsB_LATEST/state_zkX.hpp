#pragma once
/******************************************************************************/
/* File   : state_zkX.hpp                                                     */
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
#define cCAL_TIO                                              ((uint16) 0x0004U)
#define cCAL_P_HA_INVALID                                     ((uint16) 0x0008U)
#define cCAL_P_VA_INVALID                                     ((uint16) 0x0010U)
#define cCAL_P_MIN_INVALID                                    ((uint16) 0x0020U)
#define cPOS_CHANGED_VL                                       ((uint16) 0x0400U)
#define cPOS_CHANGED_VR                                       ((uint16) 0x0800U)
#define cPOS_CHANGED_HL                                       ((uint16) 0x1000U)
#define cPOS_CHANGED_HR                                       ((uint16) 0x2000U)
#define cZK_ALLE_BITS                                         ((uint16) 0xffffU)

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
extern void InitZK                      (void);
extern void ClearBitZustandskennungZK   (uint16 ushBitMask);
extern boolean bGetBitZustandskennungZK (uint16 ushBitMask);
extern void SetChangedBit4WP            (uint8  ucWP);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void SetBitZustandskennungZK     (uint16 ushBitMask);
extern uint16 ushGetZustandskennungZK   (uint16 ushBitMask);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

