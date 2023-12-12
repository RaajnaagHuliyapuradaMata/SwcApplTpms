#ifndef _ee_global_functions_X_H
#define _ee_global_functions_X_H
/******************************************************************************/
/* File   : EeGlobalFunctionsX.h                                              */
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
#include "Rte_CtApHufTpmsSWC.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cDiagBlock1           0
#define cDiagBlock2           1
#define cHistoBlock           2
#define cErfsBlock            3
#define cErfsEcoBlock         4
#define cWarnstatusBlock      5
#define cErfsTsaBlock         6
#define cRidQrBlock1          7
#define cRidQrBlock2          8
#define cZomblock1            9
#define cZomblock2            10
#define cCommonBlock          11
#define cAttemptCounterSize   12

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
extern void CheckMemoryReserveEE(Rte_Instance self);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

