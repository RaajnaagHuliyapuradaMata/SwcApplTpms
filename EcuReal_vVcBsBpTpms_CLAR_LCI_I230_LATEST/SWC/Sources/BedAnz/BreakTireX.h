#ifndef BreakTireX_h
#define BreakTireX_h
/******************************************************************************/
/* File   : BreakTireX.h                                                      */
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
#define cBtWsBreakTireInit                                        ((uint8) 0x00)
#define cBtWsBreakTireLoMask                                      ((uint8) 0x0F)
#define cBtWsBreakTireHiMask                                      ((uint8) 0xF0)
#define cBtWsBreakTire0                                           ((uint8) 0x01)
#define cBtWsBreakTire1                                           ((uint8) 0x02)
#define cBtWsBreakTire2                                           ((uint8) 0x04)
#define cBtWsBreakTire3                                           ((uint8) 0x08)
#define cBtWsBreakTirePw                                          ((uint8) 0x10)
#define cBtWsBreakTireDw                                          ((uint8) 0x20)
#define cBtWsBreakTireTsb                                         ((uint8) 0x40)
#define cBtWsBreakTireMulti                                       ((uint8) 0x80)

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
extern void    InitBT(Rte_Instance self);
extern void    SetBreakTireStateBT(Rte_Instance self);
extern uint8   ucGetBreakTireStateBT(void);
extern uint8   ucGetWarnOutStateBT(Rte_Instance self);
extern boolean bGetBefuellhinweisBT(void);
extern void    PwfChangeParken2WohnenBT(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

