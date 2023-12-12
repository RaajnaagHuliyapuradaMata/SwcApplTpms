#ifndef _rdctsaservices_X_H
#define _rdctsaservices_X_H
/******************************************************************************/
/* File   : RdcTsaServicesX.h                                                 */
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
#define cTyreMountedFlag                ((uint8) 0x05)
#define cDateSize                       ((uint8) 6)
#define cKmSize                         ((uint8)4)

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
extern void GetRdcRidAktReifenQRCodeLesenDS(Rte_Instance self, uint8* paucData);
extern void GetRdcRidAlteReifenQRCodeLesenDS(Rte_Instance self, uint8* paucData);
extern void GetRdcRidAktReifenLaufstreckeLesenDS(Rte_Instance self, uint8* paucData);
extern void GetRdcRidAlteReifenLaufstreckeLesenDS(Rte_Instance self, uint8* paucData);
extern void SaveCompleteQrCodeDataDS(Rte_Instance self);
extern void SetUpdateTyreQrCodeDataInNvRam( boolean bVal);
extern boolean GetUpdateTyreQrCodeDataInNvRamDM(void);
extern void SaveTsaDataDS(Rte_Instance self, const uint8* pucData);
extern void ReadTsaDataDS(Rte_Instance self, uint8* pucData);
extern void ResetQRTyreMountedFlags(Rte_Instance self, uint8 HisFlags);
extern uint8 GetOemIdDS(uint8 ucPrev, uint8 ucCur, uint8 IdIx);
extern uint8 GetQrIxOfWheelPos (Rte_Instance self, uint8 ucWheelPos);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

