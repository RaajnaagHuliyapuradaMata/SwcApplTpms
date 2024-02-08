#pragma once
/******************************************************************************/
/* File   : statemanagerX.hpp                                                 */
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
extern void InitSM(void);
extern void InitAfterKl15OnSM(void);
extern void InitAfterKl15OffSM(void);
extern void SequenceControlSM(void);
extern void EvReDataSM(void);
extern void EvZOTimeoutSM(void);
extern void EvalWUDefektSM( uint8 u8ZOMPosition );
extern void EvalWUNoRecSM(uint8 ucIx);
extern void EvalWUHighTempSM(void);
extern void EvalWULowLifeTimeSM( uint8 u8ZomPos );
extern void EvMinuteCntSM(void);
extern boolean SgDiagGetOutOfVolt(void);
extern void InformWarnHandlerSM(boolean ResetWarn, const uint8 PressFA, const uint8 PressRA);
extern boolean bCheckSuppIdentAndTelTypeSM(uint8 SuppIdent, uint8 TelType);
extern boolean LearningWheelPosActiveSM(void);
extern void PunctureWarningReset(void);
extern void SM_TimerProcessForSpeedValueInUseStatus(void);

#ifdef FILTER_SYMC_CAN_MSGS
extern void CheckStateOf_ER_PressureRx(void);
extern void CheckStateOf_ER_PressureRx_after_Allocation(void);
extern boolean SendRealReData(void);
#endif

extern void EvIDOMTimeoutSM(void);
extern void SM_ResetStatusForSpeedValueInUse(void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

