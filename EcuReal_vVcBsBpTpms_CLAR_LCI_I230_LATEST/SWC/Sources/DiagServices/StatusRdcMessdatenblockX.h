#ifndef StatusRdcMessdatenblockX_h
#define StatusRdcMessdatenblockX_h
/******************************************************************************/
/* File   : StatusRdcMessdatenblockX.h                                        */
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
#define cucIxStatReIdentifierWert                 ((uint8)  0)
#define cucIxStatRadPositionNr                    ((uint8)  4)
#define cucIxStatLetzterReifendruckwertWert       ((uint8)  5)
#define cucIxStatLetzterReifentemperaturwertWert  ((uint8)  7)
#define cucIxStatSolldruckWert                    ((uint8)  8)
#define cucIxStatGutempfaengeWert                 ((uint8) 10)
#define cucIxStatAusbeuteWert                     ((uint8) 12)
#define cucIxStatRssiPegelWert                    ((uint8) 13)
#define cucIxStatRestlebensdauerWert              ((uint8) 15)
#define cucIxStatRadelektronikStatus              ((uint8) 17)
#define cucIxStatHarteWarnungAktiv                ((uint8) 18)
#define cucIxStatPosChanged                       ((uint8) 19)
#define cucIxStatFolgeausfallWert                 ((uint8) 20)
#define cucIxStatReHersteller                     ((uint8) 21)
#define cucIxStatRadelektronikSendemode           ((uint8) 22)
#define cucIxStatTelegrammtyp                     ((uint8) 23)

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
extern void GetStatusRdcMessdatenblockDS(Rte_Instance self, uint8 ucBlockNo, uint8* pucData);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

