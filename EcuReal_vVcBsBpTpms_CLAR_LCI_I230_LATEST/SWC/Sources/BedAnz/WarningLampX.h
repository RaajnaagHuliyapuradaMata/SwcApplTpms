#ifndef WarningLampX_h
#define WarningLampX_h
/******************************************************************************/
/* File   : WarningLampX.h                                                    */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
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
#define cCcStartStopState_Stop          ((uint8) 0x00u)
#define cCcStartStopState_Start         ((uint8) 0x01u)
#define cCcStartStopState_Invalid       ((uint8) 0x03u)
#define cCcStartStopState_Stoped        ((uint8) 0xF0u + cCcStartStopState_Stop)
#define cCcStartStopState_Started       ((uint8) 0xF0u + cCcStartStopState_Start)
#define cCcBlinkState_Off               ((uint8) 0x00u)
#define cCcBlinkState_Slow              ((uint8) 0x01u)
#define cCcBlinkState_Fast              ((uint8) 0x02u)
#define cCcBlinkState_Invalid           ((uint8) 0x03u)
#define cCcRepetitionRate_Undefined     ((uint8) 0x00u)
#define cCcRepetitionRate_01            ((uint8) 0x01u)
#define cCcRepetitionRate_02            ((uint8) 0x02u)
#define cCcRepetitionRate_03            ((uint8) 0x03u)
#define cCcRepetitionRate_04            ((uint8) 0x04u)
#define cCcRepetitionRate_05            ((uint8) 0x05u)
#define cCcRepetitionRate_06            ((uint8) 0x06u)
#define cCcRepetitionRate_07            ((uint8) 0x07u)
#define cCcRepetitionRate_08            ((uint8) 0x08u)
#define cCcRepetitionRate_09            ((uint8) 0x09u)
#define cCcRepetitionRate_10            ((uint8) 0x0Au)
#define cCcRepetitionRate_11            ((uint8) 0x0Bu)
#define cCcRepetitionRate_12            ((uint8) 0x0Cu)
#define cCcRepetitionRate_13            ((uint8) 0x0Du)
#define cCcRepetitionRate_14            ((uint8) 0x0Eu)
#define cCcRepetitionRate_Invalid       ((uint8) 0x0fu)
#define cCcFixLampStateOff              ((uint8) 0u)
#define cCcFixLampStateStatic           ((uint8) 1u)
#define cCcFixLampStateBlinking         ((uint8) 2u)
#define cCcFixLampStateInvalid          ((uint8) 3u)

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
extern void    InitWL(void);
extern void    PutCheckControlNumberWL(uint8 ucFixLampControl);
extern uint8   ucGetCcStartStopStateWL(void);
extern uint8   ucGetCcBlinkStateFixLampWL(void);
extern uint8   ucGetCcRepetitionRateWL(void);
extern void    MainFunctionWL(void);
extern boolean bIsBlinkingAllowedWL(void);
extern void    PutCcStartStopStateWL(uint8 ucCcStartStopState);
extern void    BlinkingAllowedWL( boolean bState);
extern void    SwitchOnWL(void);
extern void    SwitchOffWL(void);
extern uint8   ucGetActualStateWL(void);
extern uint16  ushGetBlinkingTimeWL(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

