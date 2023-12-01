

#ifndef _hs_warnereignis_H
#define _hs_warnereignis_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "HS_WarnereignisX.h"

#define cGroupMask_A  (uint32)0xfU
#define cGroupMask_B  (uint32)0xf0U
#define cGroupMask_C  (uint32)0xf00U
#define cGroupMask_D  (uint32)0xf000U
#define cGroupMask_E  (uint32)0xf0000U

#define cGroupOffset_A (uint8)0
#define cGroupOffset_B (uint8)4
#define cGroupOffset_C (uint8)8
#define cGroupOffset_D (uint8)12
#define cGroupOffset_E (uint8)16

#define cFindBitSet     1
#define cFindBitCleared 0

#define cEventTypePanne 0
#define cEventTypeWarn  1
#define cEventTypeWeich 2

static uint8 ucCheckWarningGroup( uint32 ulBitsOld, uint32 ulBitsNew, uint32 ulGroupMask, uint8 ucDirection);
static uint8 ucNoOfActivePreWarningsDS(void);

static uint8 SaveWarnereignisDS(Rte_Instance self, uint8 ucPos, uint8 ucWarningType);
static uint8 SaveWarnereignisWeichDS(Rte_Instance self, uint8 ucPos);
static uint8 SaveWarnereignisRuecknahmeDS(Rte_Instance self, uint8 ucPos);

static void SaveHighestSpeedWithActiveWarningDS(Rte_Instance self, uint8 ucVMax);
static void CumulateKilometers_160_to_max_DS(Rte_Instance self);
static void CumulateKilometers_100_to_160_DS(Rte_Instance self);
static void CumulateKilometers_0_to_100_DS(Rte_Instance self);

static boolean bWarnereignis3ActiveDS(Rte_Instance self);
static boolean bWarnereignis2ActiveDS(Rte_Instance self);
static boolean bWarnereignis1ActiveDS(Rte_Instance self);

static void WriteWarnereignis_3_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);
static void WriteWarnereignis_2_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);
static void WriteWarnereignis_1_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);

static void ShiftMileageDS( uint8 ucEventNumber);

static uint8 ucFindFirstBitInLoNibbleDS( uint8 ucByte);

#ifdef __cplusplus
}
#endif

#endif

