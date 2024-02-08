

#ifndef _uswarn_if_X_H
#define _uswarn_if_X_H

#include "uswarnX.hpp"
#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
#else
  #include "types.hpp"
  #include "warn_cfg.hpp"
#endif

//extern const struct ParaSubSet tParaSubSetc[];

extern uint8 GetPTSollUSWIF(uint8 *pucPressure, sint8 *pscTemperature, uint8 ucZomPos);
extern uint8 CfgReInitSingleUSWIF(uint8 ucPressure, sint8 scTemperature, uint8 ucZomPos);
extern uint8 ucCfgPMinUSWIF( uint8 ucPMin );
extern uint8 CfgPSollMinAtIdUSWIF(uint8 ucPressure, uint8 ucZomPos);
extern uint8 ResetWarnVectorUSWIF(uint8 ucZomPos);
extern uint8 ClearWarnOfIdUSWIF(uint8 ucZomPos);
extern uint8 GetWarnOfIdUSWIF(uint8 *pucWarnOfId);
extern uint8 GetPWarmUSWIF( uint8 *pucPressure, sint8 *pscTemperature, uint8 ucZomPos );
extern uint8 NewPositionsUSWIF(const uint8 * pucRadPos);
extern uint8 ClearPosUSWIF(void);
extern void ResetWarningsUSWIF(void);
extern uint8 ucWAlgoPrePara(uint8 ucPWarnMin, uint8 ucPSollMinVA, uint8 ucPSollMinHA);
extern boolean DynWarnResetCond(uint8 ActPress, uint8 WarnPress, uint8 ZomPos);
extern uint8 GetPosOfIdIFH(uint8 ucIdPos, uint8 *pucCarMountedPos);
extern uint8 GetIdOfPosIFH(uint8 ucPos, uint8 *pucIdOfCarMountedPos);
extern void ResetOldWarningsByNewEr(uint8 ucErChangeState, uint8 ucMaxErNumber);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern uint8 GetHWFreakBitsIFH(uint8 * pucFreakBits);
extern uint8 GetIsoUSWIF(uint8 ucPressure, sint8 scTemperature, uint16 *pushIsochore);
extern uint8 PorInitUSWIF(void);
extern uint8 PutPWarmUSWIF(uint8 ucPressure, uint8 ucZomPos);
extern void InitDynWarnReset(void);
#endif //BUILD_WITH_UNUSED_FUNCTION

#endif

