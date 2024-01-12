#pragma once
/******************************************************************************/
/* File   : abs_linX.hpp                                                      */
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
#include "tss_stdx.hpp"
#include "Tpms_Rte_Data_Type.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cABS_OK                                                   ((uint8) 0x00)
#define cABS_ERROR                                                ((uint8) 0x01)
#define cABS_VALUE_TOO_OLD                                        ((uint8) 0x02)
#define cABS_STATE_INIT                                           ((uint8) 0x00)
#define ccABS_STATE_LinABS_AVL                                    ((uint8) 0x01)
#define ccABS_STATE_LinABS_ERR                                    ((uint8) 0x02)

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
extern void InitABS(void);
extern void  PutABS(uint32 ulTime, const uint16 ushCnt[]);
extern uint8 GetLinABS(uint16 ushCnt[]);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern uint8 ucStateABS(void);
#endif

extern uint8 LockABS(void);
extern uint8 UnlockABS(void);
extern uint8 LinABS(uint32 ulRfTimeStamp);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

