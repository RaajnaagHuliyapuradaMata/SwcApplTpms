#ifndef _statemanager_X_H
#define _statemanager_X_H

#ifdef IBTCM_SW_ANPASSUNGEN
#else
  #include "tss_stdx.hpp"
  #include "state_bzX.hpp"
  #include "state_fzzX.hpp"
  #include "state_zkX.hpp"
  #include "watcfX.hpp"
#endif

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

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void SetGlobalSystemStateSM(void);
extern void EvBandModeServiceSM(void);
extern void SetResetWarnPressRefSM(void);
extern void Check4ImmediateWarnOutputSM(uint8 l_HistCol, uint8 l_WheelPos);
extern void EvDiagEvalSM(void);
#endif

#ifdef IBTCM_SW_ANPASSUNGEN

#ifdef FILTER_SYMC_CAN_MSGS
extern void CheckStateOf_ER_PressureRx(void);
extern void CheckStateOf_ER_PressureRx_after_Allocation(void);
extern boolean SendRealReData(void);
#endif

extern void EvIDOMTimeoutSM(void);
extern void SM_ResetStatusForSpeedValueInUse(void);
#endif

#endif
