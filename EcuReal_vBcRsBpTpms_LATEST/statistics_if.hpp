#pragma once
/******************************************************************************/
/* File   : statistics_if.hpp                                                 */
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
#include "statisticsx.hpp"

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
extern void SetRecCounterInEE( uint16 ushValue, uint8 ucSlot);
extern void SetMissCounterInEE( uint16 ushValue, uint8 ucSlot);
extern void SetFailCounterInEE( uint16 ucValue, uint8 ucSlot);
extern uint16 GetRecCounterInEE( uint8 ucSlot);
extern uint16 GetMissCounterInEE( uint8 ucSlot);
extern uint16 GetFailCounterInEE( uint8 ucSlot);
extern boolean CarIsDriving(void);
extern boolean ReDiagActive(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint32 WUIDinSlot (uint8);
#endif

extern boolean RfInterferenceActive(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
void ChangeSystemState(void);
#endif

extern boolean CheckWUFDErr(uint16 CounterValue, uint8 ucIx);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

