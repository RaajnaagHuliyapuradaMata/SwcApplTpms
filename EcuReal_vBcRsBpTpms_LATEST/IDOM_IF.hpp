#pragma once
/******************************************************************************/
/* File   : IDOM_IF.hpp                                                       */
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
#include "Tpms_Rte_Data_Type.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#ifdef BUILD_WITH_UNUSED_DATA
#define ucVehMovesc                                                  ((uint8) 1)
#endif

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8  u8ApplState;
   uint16 u16MaxFFCtVal;
   uint16 u16CurBaseLevel;
}tIDOMInput;


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
extern void   StartIDOMAlarm  (uint16 ushNrOfCurFF);
extern void   StopIDOMAlarm   (void);
extern void   BreakIDOMAlarm  (void);
extern void   GetIDOMInput    (tIDOMInput* pIDOMInput);
extern uint16 GetParaOffset   (void);
extern uint16 GetParaOverlaps (void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

