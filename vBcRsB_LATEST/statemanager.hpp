#pragma once
/******************************************************************************/
/* File   : statemanager.hpp                                                  */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#ifdef STATEMANAGER_C
#define TIME_5MIN_OVER ( (uint16)   1500 )
#define TIME_5MIN_DONE ( (uint16) 0xFFFF )
#define SPEED_10KMH    ( (uint16)     10 )

#define LOCKED         ( (uint8)    0x00 )
#define ENABLE_ADAPT   ( (uint8)    0x01 )
#define NO_ADAPT       ( (uint8)    0x02 )
#define DEFAULT_ADAPT  ( (uint8)    0x03 )

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
  WN_STATE_NO_WARNING
   ,  WN_STATE_HW_NOPOS
   ,  WN_STATE_HW_FL
   ,  WN_STATE_HW_FR
   ,  WN_STATE_HW_RL
   ,  WN_STATE_HW_RR
}tWnStateType;

typedef struct{
  uint32 ulID;
  uint8  ucPressure;
  sint8  scTemperature;
}tAdditionalZomData;

typedef enum{
   E_NORMAL_TIME_EVAL_MODE
   ,  E_PART_TIME_EVAL_MODE
}ENUM_EVALUATION_TIME_MODE_TYPE;


/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static tWnStateType    tWnState;
#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8 ucLiveCounterSM = FALSE;
static uint8 ucVBatHighErrorTime;
static uint8 ucVBatLowErrorTime;
#endif

static uint8 ucWUMode3DiagActive;
static tAdditionalZomData tAddZomData[cSumWE];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void SaveReDataInSlotSM(uint8 ucParamZomSlot );
static uint16 CheckSensorDefectSM( uint8 ucParamZomSlot );
static void ucLearningWheelPosSM(void);
static uint8 ucGetWheelPosSM(void);
static tWnStateType tCheckForFlatTyreSM(uint8 l_ucZomSlot, uint8 l_ucWheelPos);
static void DeleteErrorsOnZugeordnetSM(void);
static void EntryWAStateUnassignedSM(void);
static void EntryWAStateFinishedSM(void);
static void  SensorErrorDiagSM(boolean bHwDefect, uint8 ucZomPos);
static void  SensorTemperatureDiagSM(boolean bReTempExceed, uint8 ucZomPos);
static void SensorLowLifeTimeDiagSM(boolean bReLowLifeTime, uint8 ucZomPos);

#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint8 EvalVoltDiagSM(void);
static uint8 EvalECUDiagSM(void);
static uint8 EvalWUDiagSM(void);
#endif

static void CheckForStoersenderZeit(void);
static void InitResetWarnPressRefSM(const uint8 l_ucZomSlot, const uint8 ucActPress);
static uint8 CheckWUReceptionSM(void);
static void ucControlCyclicCallPeriod(void);

#ifdef G_USE_PART_ER
static uint8 CheckPartErStateSM(void);
#endif //G_USE_PART_ER
static void SetTransportModeSM(const boolean bMode);
static void InitAddZomDataSM (void);
static void SetAddZomDataSM (void);
static void PreloadFromAddZomDataSM (uint8 ucHistCol);
static void Check4FastWarnOutputSM(uint8 ignoreCol);
static void OperateTrefTemperature(void);
static sint8 scChooseTrefTemperature(void);
static boolean bCheckActPresEnoughPplacardSM(void);
#endif //#ifdef STATEMANAGER_C

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

