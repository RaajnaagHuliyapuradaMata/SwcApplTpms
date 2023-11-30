#ifndef USWarn_h
#define USWarn_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "USWarnX.h"

#define ushGSFc       ((uint16) 1024)

extern tCalibrationTab tCDA;
extern uint8 ucPrewarnThresCfactor;
extern uint8 ucPrewarnThresNCfactor;
extern uint8 ucAlarmThresCfactor;
extern uint8 ucAlarmThresNCfactor;
extern uint8 ucPrewarnDelayMin;
extern uint8 ucPanneThres;
extern uint8 ucDpToIPmin;
extern uint8 ucShortHoldTime;
extern uint8 ucLongHoldTime;
extern uint8 ucThCTol;
extern uint8 ucThNCTol;
extern uint8 ucSaturierungAktiv;

static uint8 bGetX8BitWM( const uint8* ptByte, uint8 ucBitNo);
static void  ClearX8BitWM( uint8* ptByte, uint8 ucBitNo);
static void  SetX8BitWM( uint8* ptByte, uint8 ucBitNo);
static void  ClearWarntypeBit( uint8 ucWType, uint8 ucId, uint8 ucMode);
static void  InitWN( uint8 ucInit, uint8 ucIdX);
static void  RdParaSubSet( uint8* pucData);
static void  WrParaSubSet( Rte_Instance self, const uint8* pucData);
static uint8 ucGenWNVector( Rte_Instance self, uint8* pucData);
static uint8 ucWarnManager_FilterActivationWM(void);
static uint8 ucWarnManager_PorInitWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManager_CompareWM( Rte_Instance self, uint8* pucData);
static uint8 ucWarnManagerDsWM( Rte_Instance self, uint8* pucData);
static uint8 ucWarnManagerDs_CfgPMinWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_CfgPSollMinWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_CfgReInitSingleWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_CfgTReifenSingleWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_ResetWarnVectorWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_GetWarnVectorsWM( uint8* pucData);
static uint8 ucWarnManagerDs_RdParaSubSetWM( uint8* pucData);
static uint8 ucWarnManagerDs_WrParaSubSetWM( Rte_Instance self, const uint8* pucData);
static uint8 ucWarnManagerDs_GetPTSollWM( uint8* pucData);
static uint8 ucWarnManagerDs_GetWarnThresWM( uint8* pucData);
static uint8 ucWarnManagerDs_TimerStopWM(void);

#ifdef __cplusplus
}
#endif

#endif
