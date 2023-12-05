#ifndef FPA_h
#define FPA_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "FPA_X.h"
#include "WallocX.h"

#ifdef FPA
#define FULLTURNINABSTICKS 96
#define HALFTURNINABSTICKS 48
#define QUARTURNINABSTICKS 24
#define cMIN_DIST_BEFORE_DECISION 0

typedef struct{
  uint8 ucIsAmbigous;
  uint8 ucAimsWheelPos;
  uint8 ucIsFighting;
  uint8 ucIsAmbigousXorFighting;
}tIdCharacteristic;

typedef struct{
  tIdCharacteristic tIdChar[cMaxLR];
  uint8 ucSumAmbigous;
  uint8 ucSumFighting;
  uint8 ucSumAmbXorFighting;
}tIdEvaluation;

static void   SetReferenceValuesFPA(uint8 ucSlot);
static void   ClearAverageDistanceSumValuesFPA(uint8 ucSlot);
static void   GenerateAbsoluteCompareValuesFPA(uint8 ucSlot);
static void   SortBiggest1st(const uint8 *ptVal, uint8 *ptIx, uint8 ucMax);
static uint16 ushMinStretch4Decision(void);
static uint32 ulCalcCompareSumFPA(uint8 ucSlot);
static uint16 ushGetABSingleTickPAL(uint8 ucIx);
static uint16 ushGetABSingleTickFr2(uint8 ucIx);
static uint16 ushGetABSingleTickFr3(uint8 ucIx);
static uint16 ushGetABSingleTickN90(uint8 ucIx);
static uint16 ushGetABSingleTickN90Fr2(uint8 ucIx);
static uint16 ushGetABSingleTickN90Fr3(uint8 ucIx);
static uint8  ucGetTDL100(void);
static uint16 ushGetTDL210(void);
static uint8  ucMINUS_ABSigOFL_MOD_ZAHN(void);
static uint8  ucABSigOFL_MOD_ZAHN(void);

#ifdef pb_ModulTest_050104
extern void TESTPrintToothZOM_HL(void);
extern void TESTPrintToothZOMAsLine(void);
extern void TESTPrinToothZOMSummary(uint8 i);
extern void TESTPrintFPAZOMSlot(uint8 ucSlot);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
