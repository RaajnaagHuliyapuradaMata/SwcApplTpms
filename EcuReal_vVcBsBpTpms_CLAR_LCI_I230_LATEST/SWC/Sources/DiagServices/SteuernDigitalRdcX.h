#ifndef SteuernDigitalRdcX_h
#define SteuernDigitalRdcX_h
/******************************************************************************/
/* File   : SteuernDigitalRdcX.h                                              */
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
#define cFunctionNo_BandmodeDS                                    ((uint8) 1)
#define cFunctionNo_TestErFahrtDS                                 ((uint8) 4)
#define cFunctionNo_CalRequestDS                                  ((uint8) 8)
#define cActionNo_BandmodeEinDS                                   ((uint8) 1)
#define cActionNo_BandmodeAusDS                                   ((uint8) 0)
#define cActionNo_TestErFahrtResetDS                              ((uint8) 0)
#define cActionNo_TestErFahrtSetDS                                ((uint8) 1)
#define cActionNo_TestErFahrtSetNoSpeedDS                         ((uint8) 2)
#define cActionNo_CalRequestSetDS                                 ((uint8) 1)
#define cActionNo_CalRequestResetDS                               ((uint8) 0)
#define cucRetValOkDS                                             ((uint8) 0x00)
#define cucRetValServiceNotStartetDS                              ((uint8) 0x0F)
#define cucRetValServiceNotStopedDS                               ((uint8) 0xF0)
#define cucRetValErrorDS                                          ((uint8) 0xFF)

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
extern uint8 ucPutSteuernDigitalRdcDS(Rte_Instance self, uint8 ucFunctionNo, uint8 ucActionNo);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

