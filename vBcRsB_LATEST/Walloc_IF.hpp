#pragma once
/******************************************************************************/
/* File   : Template.hpp                                                      */
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
#include "cd_decoder_x.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cMaxTeLen sizeof(tRFTelType)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef tPreBuf tRFTelType;


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
extern void StartWATO(unsigned char ucTimeInSec);
extern void CancelWATO(void);
extern unsigned short ushGetABSingleTick(unsigned char ucIx);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char ucGetABSTick(unsigned short * p2aushABS);
extern unsigned short ushGetLW(void);
#endif

#ifdef pb_ModulTest_050104
extern unsigned char ucGetFW(signed short * p2shFW);
extern void ResetEEPROM(void);
extern void TESTPutWayStretch(unsigned short * p2WayStretch);
extern void TESTResetABStick(void);
extern void TESTPutSingleABStick(unsigned short ushTickVal, unsigned char ucIx);
extern void TESTPutLenkwinkel(signed short shLW);
extern void TESTPutSpeed(unsigned char);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

