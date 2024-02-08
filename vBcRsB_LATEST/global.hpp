#pragma once
/******************************************************************************/
/* File   : global.hpp                                                        */
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
#define pb_DebugWarnLevels_030203

#if defined(pb_ModulTest_02062003) || defined(TestUSCSc) || defined(pb_TestCtrl_110203) || defined (pb_TestEeIface_200103)
#define pb_EeIfaceOnPc_200103
#endif

#define pb_QACStatic_160503

#ifdef pb_QACStatic_160503
#define cSTATIC static
#else
#define cSTATIC
#endif

#define ucMaxPosc 4
#define ucSumWEc  (unsigned char) 4
#define scLockEuFbyTref   (signed char) 127
#define ucWsIdWNc (unsigned short) 1
#define ucCdIdWNc (unsigned short) 2
#define ucWdIdWNc (unsigned short) 3
#define ucTsIdTMc (unsigned short) 4
#define ucCbIdTMc (unsigned short) 5
#define ucWarnTypeArrayIdWNc (unsigned short) 6
#define ucIxWnCfgc 0
#define ucIxMsCfgc 1
#define NEGATE_UCHAR(x) ( (uint8) ( 0xFF&(~(x)) ) )
#define NEGATE_USHORT(x) ( (uint16) ( 0xFFFF&(~(x)) ) )
#define NEGATE_ULONG(x) ( (uint32) ( 0xFFFFFFFF&(~(x)) ) )

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
extern void ChangeWNParaSubSet(void);
extern const unsigned char ucBitNoc[ucSumWEc];

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

