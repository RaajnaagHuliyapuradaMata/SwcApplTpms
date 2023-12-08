#ifndef _speed_ccm_X_H
#define _speed_ccm_X_H
/******************************************************************************/
/* File   : SpeedCcmX.h                                                       */
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
#define cSCC_STATE_SPEED_CCM_ENABLED                             ((uint8) 0x01u)
#define cSCC_STATE_PWF_FAHREN                                    ((uint8) 0x02u)
#define cSCC_STATE_WP_KNOWN                                      ((uint8) 0x04u)
#define cSCC_STATE_P_TOO_LOW                                     ((uint8) 0x08u)
#define cSCC_STATE_V_TOO_HIGH                                    ((uint8) 0x10u)
#define cSCC_STATE_DISPLAY_CCM_2158                              ((uint8) 0x20u)
#define cSCC_STATE_DISPLAY_CCM_2159                              ((uint8) 0x40u)
#define cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC              ((uint8) 0x80u)

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
extern void  InitSCC(void);
extern uint8 ucGetStateSCC(uint8 ucMask);
extern void  MainSCC(Rte_Instance self);
extern void  GetSpeedCcmValSCC_debug(uint8* pucState, uint16* pushSpeedVmaxTime, uint16* pushSpeedCcmThFa, uint16* pushSpeedCcmThRa);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

