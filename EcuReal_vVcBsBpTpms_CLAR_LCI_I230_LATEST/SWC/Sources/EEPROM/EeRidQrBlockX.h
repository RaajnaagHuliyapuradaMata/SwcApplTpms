#ifndef _ee_rid_qr_block_X_H
#define _ee_rid_qr_block_X_H
/******************************************************************************/
/* File   : EeRidQrBlockX.h                                                   */
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
#define cMaxQRCodeSets                  ((uint8)12)
#define cMountedDateIx                  ((uint8)0)
#define cMountedKmIx                    ((uint8)6)
#define cUnmountedDateIx                ((uint8)10)
#define cUnmountedKmIx                  ((uint8)16)
#define cRuntimeKmIx                    ((uint8)20)

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
extern void InitRidQrBlock1u2EE(Rte_Instance self);

extern uint8 GETTyreDimQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreDimQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreDOTQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreDOTQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreOEMQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreOEMQrCodeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreRuntimeDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void PUTTyreRuntimeDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8 GETTyreMountedFlagEE(Rte_Instance self, uint8 i);
extern void PUTTyreMountedFlagEE(Rte_Instance self, uint8 i, uint8 y);
extern void    ClearRidQrBlock1UpdateFlagEE(void);
extern void    ClearRidQrBlock2UpdateFlagEE(void);
extern boolean bGetRidQrBlock1UpdateFlagEE(void);
extern boolean bGetRidQrBlock2UpdateFlagEE(void);
extern void    SetRidQrBlock1UpdateFlagEE(void);
extern void    SetRidQrBlock2UpdateFlagEE(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

