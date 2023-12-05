#ifndef _wu_monitoring_X_H
#define _wu_monitoring_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cAllocNoError                     (uint32)0x00000000U
#define cAllocAutoLearningFailed          (uint32)0x00000001U
#define cAlloc4WrongWuMounted             (uint32)0x00000002U
#define cAlloc1To3WrongWuMounted          (uint32)0x00000004U
#define cAllocWuMuteFl                    (uint32)0x00000008U
#define cAllocWuMuteFr                    (uint32)0x00000010U
#define cAllocWuMuteRl                    (uint32)0x00000020U
#define cAllocWuMuteRr                    (uint32)0x00000040U
#define cAllocUnspecifiedWuMute           (uint32)0x00000080U
#define cAllocWuDefectFl                  (uint32)0x00000100U
#define cAllocWuDefectFr                  (uint32)0x00000200U
#define cAllocWuDefectRl                  (uint32)0x00000400U
#define cAllocWuDefectRr                  (uint32)0x00000800U
#define cAllocUnspecifiedWfcDefect        (uint32)0x00002000U
#define cAllocWuLocalisationFailed        (uint32)0x00001000U
#define cAllocGatewayOrAntennaError       (uint32)0x00004000U
#define cAllocRdciOtherWuSensorType       (uint32)0x00008000U
#define cAllocWuLowBatteryFl              (uint32)0x00010000U
#define cAllocWuLowBatteryFr              (uint32)0x00020000U
#define cAllocWuLowBatteryRl              (uint32)0x00040000U
#define cAllocWuLowBatteryRr              (uint32)0x00080000U
#define cAllocRdciRfExternalInterference  (uint32)0x00100000U
#define cRdciSystemNotAvailable           (uint32)0x00200000U
#define cRdciPartialSystemAvailability    (uint32)0x00400000U

#define cAUTOLOC_SUCCESSFUL     0
#define cAUTOLOC_FAILED         1
#define cAUTOLEARN_SUCCESSFUL   0
#define cAUTOLEARN_FAILED       1
#define cXCLOC_FALSE            10

#define cNoRfIf                  0
#define cRfIfIsActive            1
#define cLastDrvCycEndedWithRfIf 2

#define cWUM_DISABLED           (uint8) 0
#define cWUM_BM_DIENST_START    (uint8) 1
#define cWUM_BM_DIENST_RUN      (uint8) 2
#define cWUM_ENABLED            (uint8) 3

#define cNO_EVALUATION          (uint8) 0
#define cDO_EVALUATION          (uint8) 1

#define cWithoutLowBat          (uint8) 0
#define cWithLowBat             (uint8) 1
#define cWithoutWuRelatedDtcs   (uint8) 0
#define cWithWuRelatedDtcs      (uint8) 1
#define cAllSlots               (uint8) 0x0f

#define cFilterSubseqErr                  TRUE
#define cNoFilter                         FALSE

#define cPTC_Mute                         (uint8)0
#define cPTC_Defect                       (uint8)1
#define cPTC_LowBat                       (uint8)2
#define cPTC_WrongMounted                 (uint8)3
#define cPTC_WrongSupplier                (uint8)4
#define cPTC_AntennaGateway               (uint8)5
#define cPTC_LocalisationFailed           (uint8)6
#define cPTC_RfInterference               (uint8)7

#define cNO_OF_LO_BAT_TELEGRAMS  40

#define cWU_BLOCK_FAIL_TIME    (542U)

#define cWU_SINGLE_FAIL_TIME_1 (35U)
#define cWU_SINGLE_FAIL_TIME_2 (30U)
#define cWU_DOUBLE_FAIL_TIME   (65U)
#define cWU_TIMER_STOPPED      (0xFFFFU)

#define cALIVE_TEL_TIMEOUT      420

#define cRE_STATUS_IO         (uint8) 0
#define cRE_STATUS_MUTE       (uint8) 1
#define cRE_STATUS_DEFECT     (uint8) 2
#define cRE_STATUS_NOT_REC    (uint8) 3
#define cRE_STATUS_INVALID    (uint8) 0xffu

extern void InitWUM(Rte_Instance self);
extern void ResetWUM(Rte_Instance self, uint8 ucSlots, uint8 ucWLowBatt, uint8 ucWDtcs);
extern void SwitchUnspecificToSpecificErrorsWUM(Rte_Instance self);
extern void SwitchSpecificToUnspecificErrorsWUM(Rte_Instance self);
extern void ProcessWuMonitoringWUM(Rte_Instance self, ImpTypeRecCddRdcData rdcData, uint8 ucTelType);
extern void WuMonitoringTimerTickWUM(Rte_Instance self);
extern void SetWheelUnitErrorWUM(Rte_Instance self, uint32 ulDtcBit);
extern void ClearWheelUnitErrorWUM(Rte_Instance self, uint32 ulDtcBit);
extern void ClearWheelUnitErrChangedFlagWUM( uint32 ulDtcBit);
extern void ClearWheelUnitErrChangedFlagsWUM(void);
extern uint32 ulGetWheelUnitErrorsWUM( boolean bUseFilter);
extern uint32 ulGetWheelUnitErrChangedFlagsWUM(void);
extern boolean bGetWheelUnitErrorWUM( uint32 ulErrorBit);
extern uint8 ucGetYieldRateWUM( uint8 ucCol);
extern void SetWheelUnitGoodCounterWUM( uint8 ucCol, uint16 ushVal);
extern void SetWheelUnitMissingCounterWUM( uint8 ucCol, uint16 ushVal);
extern uint16 ushGetWheelUnitGoodCounterWUM( uint8 ucCol);
extern uint16 ushGetWheelUnitMissingCounterWUM( uint8 ucCol);
extern uint8 ucGetSingleFailTimerValueWUM( uint8 ucCol);
extern uint8 ucGetReMuteStatusWUM(void);
extern uint8 ucGetReDefectStatusWUM(void);
extern boolean bGetReMuteStatusBySlotWUM( uint8 ucSlot);
extern boolean bGetReDefectStatusBySlotWUM( uint8 ucSlot);
extern uint16 ushGetReDefectCounterBySlotWUM( uint8 ucSlot);
extern boolean bGetLocalisationPossibilityWUM(void);
extern void SetWumActivityStatusWUM(Rte_Instance self, uint8 ucStatus, uint8 ucEvaluation);
extern uint8 ucSetAutolocErrorStatusWUM(Rte_Instance self, uint8 ucStatus);
extern void SetAutoLearnErrorStatusWUM(Rte_Instance self, uint8 ucStatus);
extern uint8 ucGetAutoLocFailedCounterWUM(void);
extern void RfInterferenceInLastCycleDetectedWUM(Rte_Instance self);
extern void ClearMuteWUM(Rte_Instance self, uint8 ucCol, uint8 ucWP);
extern void ClearAllSpecificMutesWUM(Rte_Instance self);
extern uint16 ushGetMuteTimerValueWUM( uint8 ucCol);
extern uint16 ushGetGatewayAntennaTimerValueWUM(void);
extern uint8 ucGetLoBatCounterValueWUM( uint8 ucCol);
extern uint8 ucGetWumActivityStatusWUM(void);
extern boolean bSystemInactiveByRfInterferenceWUM(void);
extern boolean bPrio1ErrorIsSetWUM(void);
extern void ClearErrorConditionsWUM(Rte_Instance self, uint8 ucWP, uint8 ucParamToClear);

#ifdef __cplusplus
}
#endif

#endif
