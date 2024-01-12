#pragma once
/******************************************************************************/
/* File   : FPA.hpp                                                           */
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
#include "Walloc_IF.hpp"

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
extern unsigned char ucMINUS_ABSigOFL_MOD_ZAHN (unsigned char ucABSTicksRevol);
extern unsigned char ucABSigOFL_MOD_ZAHN       (unsigned char ucABSTicksRevol);
extern void          ResetAllocType            (void);
extern void          SaveDebugAllocType        (unsigned char ucAllocReason);
extern unsigned char CounterPreparation        (unsigned char ucID, tRFTelType * ptInputWA);
extern unsigned char ucConceptFixPos0          (void);
extern void          Very1stABSTickIinit       (void);
extern unsigned char ucGetAnZahn               (unsigned char ucWheelPosIx);
extern void          TESTPrintToothZOM_HL      (void);
extern void          TESTPrintToothZOMAsLine   (void);
extern void          TESTPrinToothZOMSummary   (unsigned char i);
extern void          TESTPrintFPAZOMSlot       (unsigned char ucSlot);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

