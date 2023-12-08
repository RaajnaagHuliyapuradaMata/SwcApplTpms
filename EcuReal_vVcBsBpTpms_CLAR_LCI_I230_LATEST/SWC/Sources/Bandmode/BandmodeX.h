#ifndef BandmodeX_h
#define BandmodeX_h
/******************************************************************************/
/* File   : BandmodeX.h                                                       */
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
#define cushBandmodeActivationBM                               ((uint16) 0x0001)
#define cushTestEigenradFahrtBM                                ((uint16) 0x0002)
#define cushTestEigenradFahrtNoSpeedBM                         ((uint16) 0x0004)
#define cushAllServiceBitsBM                                   ((uint16) 0x0006)
#define cushReceptionReFlBM                                    ((uint16) 0x0010)
#define cushReceptionReFrBM                                    ((uint16) 0x0020)
#define cushReceptionReRrBM                                    ((uint16) 0x0040)
#define cushReceptionReRlBM                                    ((uint16) 0x0080)
#define cushAllReceptionBitsBM                                 ((uint16) 0x00F0)
#define cushErFahrtVThresBM                                    ((uint16) 0x1000)
#define cushAllBitsBM                                          ((uint16) 0xFFFF)
#define cushThisBitsSavedInEeBM                                ((uint16) 0x0FFF)
#define cushResetAllStatusBitsBM                               ((uint16) 0x0000 | cushAllReceptionBitsBM)

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
extern void    PutStateBM (uint16 ushState);
extern uint16  ushGetStateBM (void);
extern boolean bGetStateBitBM (uint16 ushBitMask);
extern void    SetStateBitBM (uint16 ushBitMask, boolean bState);
extern boolean bGetBandmodeBM(void);
extern void    StopServiceBM(void);
extern boolean bStartServiceBM(uint16 ushService);
extern void    InitBM(uint16 ushState);
extern void    BandmodeActivateBM (void);
extern void    BandmodeDeactivateBM (void);
extern void    CycleBandModeServiceBM (Rte_Instance self, boolean bSpeedThresBM);
extern void    CountWheelElectronicDataBM(uint8 ucWheelPos);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

