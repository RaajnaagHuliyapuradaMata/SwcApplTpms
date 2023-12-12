#ifndef _statusrdclesen_X_H
#define _statusrdclesen_X_H
/******************************************************************************/
/* File   : StatusRdcLesenX.h                                                 */
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
#define cucIxStatEigenraederBekannt               ((uint8)  0)
#define cucIxStatRadposErBekannt                  ((uint8)  1)
#define cucIxStatDtcInactive                      ((uint8)  2)
#define cucIxStatKalAnforderungAktiv              ((uint8)  3)
#define cucIxStatRadZuordnungTimeout              ((uint8)  4)
#define cucIxStatBandmodeAktiv                    ((uint8)  5)
#define cucIxStatTestEigenradFahrt                ((uint8)  6)
#define cucIxStatErFahrtVthresAkiv                ((uint8)  7)
#define cucIxStatBmTimeoutActive                  ((uint8)  8)
#define cucIxStatHarteWarnungUnspezifischAktiv    ((uint8)  9)
#define cucIxStatHarteWarnungVlAktiv              ((uint8) 10)
#define cucIxStatHarteWarnungVrAktiv              ((uint8) 11)
#define cucIxStatHarteWarnungHlAktiv              ((uint8) 12)
#define cucIxStatHarteWarnungHrAktiv              ((uint8) 13)
#define cucIxStatKl15Ein                          ((uint8) 14)
#define cucIxStatFzgFaehrt                        ((uint8) 15)
#define cucIxStatErkennungAlleRe                  ((uint8) 16)

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
extern void GetStatusRdcLesenDS(Rte_Instance self, uint8* pucData);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

