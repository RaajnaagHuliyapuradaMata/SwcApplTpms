#ifndef _rdcerfsecoservices_X_H
#define _rdcerfsecoservices_X_H
/******************************************************************************/
/* File   : RdcErfsEcoServicesX.h                                             */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
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
extern void GetStatusRdcErfsEcoTabLesenDS(uint8* pucData);
extern void GetStatusRdcErfsAktReifenEcoLesenDS(Rte_Instance self, uint8* pucData);
extern void GetStatusRdcErfsAktReifenLesenDS(Rte_Instance self, uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoAktReifenposVorgebenDS(Rte_Instance self, const uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoNeueReifenVorgebenDS(Rte_Instance self, const uint8* pucData);
extern uint8 ucPutSteuernRdcErfsEcoReifentabelleVorgebenDS(Rte_Instance self, const uint8* pucData, const uint8 ucElement);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

