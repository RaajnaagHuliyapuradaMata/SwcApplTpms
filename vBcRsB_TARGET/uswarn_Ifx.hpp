#ifndef _uswarn_if_X_H
#define _uswarn_if_X_H

#include "uswarnX.hpp"
#include "Tpms_Rte_Data_Type.hpp"

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

#endif

