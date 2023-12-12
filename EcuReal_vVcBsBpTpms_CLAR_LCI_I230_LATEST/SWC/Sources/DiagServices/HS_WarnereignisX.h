#ifndef _hs_warnereignis_X_H
#define _hs_warnereignis_X_H
/******************************************************************************/
/* File   : Template.h                                                        */
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
extern void InitFastaWarnEventsDS(Rte_Instance self);
extern void ProcessFastaWarnEventsDS(Rte_Instance self);
extern void CountDrivenKilometersWithWarningDS(Rte_Instance self);
extern void ReadWarnereignisRuecknahmeDS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_1_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_2_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_3_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignisWeich_1_DS(Rte_Instance self, uint8* aucData);
extern void ReadWarnereignisWeich_2_DS(Rte_Instance self, uint8* aucData);
extern void ReadWarnereignisWeich_3_DS(Rte_Instance self, uint8* aucData);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

