#ifndef _ee_history_block_H
#define _ee_history_block_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "EeHistoryBlockX.h"

static void CompareValuesAndSetUpdateFlagEE(uint8 ucOld, uint8 ucNew);
static uint8 GETAllocFailCounterEE(Rte_Instance self);
static void PUTAllocFailCounterEE(Rte_Instance self, uint8 x);
static uint8 GETCntLoBatEE(Rte_Instance self, uint8 i);
static void PUTCntLoBatEE(Rte_Instance self, uint8 x, uint8 i);
static uint8 GETRfIfStateMachineEE (Rte_Instance self);
static void PUTRfIfStateMachineEE (Rte_Instance self, uint8 x);

#ifdef __cplusplus
}
#endif

#endif

