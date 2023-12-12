#ifndef _ee_erfs_block_X_H
#define _ee_erfs_block_X_H
/******************************************************************************/
/* File   : EeErfsBlockX.h                                                    */
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
extern void    InitErfsBlockEE(Rte_Instance self);
extern uint8   GETucErfsInitializerEE(Rte_Instance self);
extern void    PUTucErfsInitializerEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedSeasonEE(Rte_Instance self);
extern void    PUTSelectedSeasonEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedLoadStateEE(Rte_Instance self);
extern void    PUTSelectedLoadStateEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedSuTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedSuTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedWiTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedWiTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedAutoTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedAutoTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETAutomaticSelectionFailedStatusEE(Rte_Instance self);
extern void    PUTAutomaticSelectionFailedStatusEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreSelectionActiveEE(Rte_Instance self);
extern void    PUTTyreSelectionBckgrdEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreSelectionBckgrdEE(Rte_Instance self);
extern void    PUTTyreSelectionActiveEE(Rte_Instance self, uint8 x);
extern uint8   GETPlausiInitErrorEE(Rte_Instance self);
extern void    PUTPlausiInitErrorEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreChangedEE(Rte_Instance self);
extern void    PUTTyreChangedEE(Rte_Instance self, uint8 x);
extern uint8   GETStManSelectionEE(Rte_Instance self);
extern void    PUTStManSelectionEE(Rte_Instance self, uint8 x);
extern uint8   GETIdrMessageEE(Rte_Instance self);
extern void    PUTIdrMessageEE(Rte_Instance self, uint8 x);
extern uint8   GETInvalidTyreListEE(Rte_Instance self);
extern void    PUTInvalidTyreListEE(Rte_Instance self, uint8 x);
extern uint8   GETStSelectTyreEE(Rte_Instance self);
extern void    PUTStSelectTyreEE(Rte_Instance self, uint8 x);
extern uint8   GETUseSavedHistRidDataCtEE(Rte_Instance self);
extern void    PUTUseSavedHistRidDataCtEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreDimDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void    PUTTyreDimDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8   GETTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void    PUTTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8   GETCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 Season);
extern void    PUTCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 Season);
extern void    SetErfsBlockWriteMeEE(void);
extern boolean bGetErfsBlockWriteMeEE(void);
extern void    ClearErfsBlockWriteMeEE(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

