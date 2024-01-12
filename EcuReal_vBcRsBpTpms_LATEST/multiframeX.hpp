#pragma once
/******************************************************************************/
/* File   : multiframeX.hpp                                                   */
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
#define cMF_MAX_FILTER_TIME                                          ((uint8) 2)
#define cMF_MAX_FILTER_TIME_ROTATS                                   ((uint8) 7)
#define cFT_SINGLE_FRAME                                             ((uint8) 0)
#define cFT_MULTI_FRAME                                              ((uint8) 1)

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
extern void  TimeMF                 (void);
extern uint8 ucCheckForMultiFrameMF (uint32 ulReID, uint8 ucTGCounter, uint8 u8MaxTimeFilter);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

