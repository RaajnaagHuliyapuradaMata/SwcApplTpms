#ifndef _statusrdcdeveloperdatalesen_X_H
#define _statusrdcdeveloperdatalesen_X_H
/******************************************************************************/
/* File   : StatusRdcDeveloperDataLesenX.h                                    */
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
#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cStatusRdcDeveloperDataLesen_MuxChannel0  ((uint8)  0)
#define cStatusRdcDeveloperDataLesen_MuxChannel1  ((uint8)  1)
#define cStatusRdcDeveloperDataLesen_MuxChannel2  ((uint8)  2)
#define cStatusRdcDeveloperDataLesen_MuxChannel3  ((uint8)  3)
#define cStatusRdcDeveloperDataLesen_MuxChannel4  ((uint8)  4)
#define cStatusRdcDeveloperDataLesen_MuxChannel5  ((uint8)  5)
#define cStatusRdcDeveloperDataLesen_MuxChannel6  ((uint8)  6)
#define cStatusRdcDeveloperDataLesen_MuxChannel7  ((uint8)  7)
#define cStatusRdcDeveloperDataLesen_MuxChannel8  ((uint8)  8)
#define cStatusRdcDeveloperDataLesen_MuxChannel9  ((uint8)  9)
#define cStatusRdcDeveloperDataLesen_MuxChannel10 ((uint8) 10)
#define cStatusRdcDeveloperDataLesen_MuxChannel11 ((uint8) 11)
#define cStatusRdcDeveloperDataLesen_MuxChannel12 ((uint8) 12)
#define cStatusRdcDeveloperDataLesen_MuxChannel13 ((uint8) 13)
#define cStatusRdcDeveloperDataLesen_MuxChannel14 ((uint8) 14)
#define cStatusRdcDeveloperDataLesen_MuxChannel15 ((uint8) 15)
#define cStatusRdcDeveloperDataLesen_MuxChannel16 ((uint8) 16)

#define cStatusRdcDeveloperDataLesen_MuxChannelMaxValidValue ( cStatusRdcDeveloperDataLesen_MuxChannel16)

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
#ifdef __cplusplus
extern "C"
{
#endif
extern void GetStatusRdcDeveloperDataLesenDS(Rte_Instance self, uint8* pucData);
extern uint8 ucPutDeveloperDataMuxChannelDS(uint8 ucMuxChannel);
extern uint8 ucGetDeveloperDataMuxChannelDS(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

