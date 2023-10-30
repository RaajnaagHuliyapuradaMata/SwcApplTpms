#ifndef WallocX_H
#define WallocX_H

struct InputWA{
   unsigned long ulID;
   unsigned char ucStatus;
   unsigned char ucRssi;
};

typedef struct {
   unsigned char ucWACtrl;
   unsigned char ucMinRssiLevel;
   unsigned char ucMinRssiDistance;
   unsigned char ucMinVariationDistance;
   unsigned char ucLeRiMinDistance;
   unsigned char ucEcuPosition;
   unsigned char ucMinCt4ER;
   unsigned char ucMinCt4HistER;
   unsigned char ucMinCt4ZomReset;
   unsigned char ucMinERMeanRssiLevel;
   unsigned char WATOTimeInSec;
   unsigned char ucTimeoutAutoLoc;
   unsigned char ucNewMinCntEvt;
   unsigned char ucMinTimeProtectER;
   unsigned char ucnMinRxTGRF;
   unsigned char ucnRelValMinDiff;
   unsigned char ucnRelValMidDiff;
   unsigned char ucnRelValCompetDiff;
   unsigned char ucMaxZOnorm;
   unsigned char ucnMinA;
   unsigned char ucMinSpeedAutoLearnStart;
   unsigned char ucOffsetOverlapsGXe;
   unsigned char ucnVweight;
   unsigned char ucMinOffsetGXe;
   unsigned char ucSufficientRssiDistance;
} WAParameter;

typedef struct {
   unsigned char ucFrontAxisABSTicks;
   unsigned char ucRearAxisABSTicks;
} WAABSTicksInOneRevolution;

#include "Tpms_Rte_Data_Type.hpp"

#define cSumWE  8
#define cMaxLR  4
#define cHiStateZG (unsigned char) 2
#define cHiStateER (unsigned char) 1
#define cWheelPos_FL  0x00
#define cWheelPos_FR  0x01
#define cWheelPos_RL  0x02
#define cWheelPos_RR  0x03
#define cIDStateSpinning      0x28
#define cIDStateSpinLeft      0x20
#define cIDStateSpinRight     0x08
#define cIDStateDrive         0x02
#define cIDStateReserved      0x01
#define cIDStateDrvBack       0x40
#define cIDStateNoDrvInfo     0x80
#define cIDStateM4            0x04
#define cWAChange (unsigned char) 0xF0
#define cWAStateBreak 0x08
#define cWAStateZO 0x04
#define cWAStateER 0x02
#define cWAStateActive 0x01
#define ucDefWACtrl (unsigned char) 0
#define ucDefMinRssiLevel (unsigned char) 0
#define ucDefMinRssiDistance (unsigned char) 10
#define ucDefMinVariationDistance (unsigned char) 10
#define ucDefLeRiMinDistance (unsigned char) 1
#define ucECUPosFront (unsigned char) 0x55
#define ucECUPosRear (unsigned char) 0xAA
#define ucECUPosNeutral (unsigned char) 0xFF
#define ucDefMinCt4ER (unsigned char) 9
#define ucDefMinCt4HistER (unsigned char) 2
#define ucDefMinCt4ZomReset (unsigned char) 8
#define ucDefMinERMeanRssiLevel (unsigned char) 28
#define ucDefWATOTimeInSec (unsigned char) 60
#define ucDefTimeoutAutoLoc (unsigned char) 9
#define ucDefNewMinCntEvt (unsigned char) 5
#define ucDefMinTimeProtectER (unsigned char)  3
#define ucnDefMinRxTGRF (unsigned char) 15
#define ucDefnRelValMinDiff (unsigned char) 5
#define ucDefnRelValMidDiff (unsigned char) 5
#define ucDefnRelValCompetDiff (unsigned char) 10
#define ucDefMaxZOnorm (unsigned char) 15
#define ucDefnMinA (unsigned char) 10
#define ucDefMinSpeedAutoLearnStart 30
#define ucDefMinSpeedAutoLearnCont (unsigned char) 7
#define ucDefnVweight (unsigned char) 60
#define ucDefMinOffsetGXe (unsigned char) 1
#define ucDefSufficientRssiDistance (unsigned char) 12
#define ucDefOffsetOverlapsGXe    55U

#define cWADefInitParam { \
      ucDefWACtrl \
   ,  ucDefMinRssiLevel \
   ,  ucDefMinRssiDistance \
   ,  ucDefMinVariationDistance \
   ,  ucDefLeRiMinDistance \
   ,  ucECUPosRear \
   ,  ucDefMinCt4AxAnalysis \
   ,  ucDefMinCt4ER \
   ,  ucDefMinCt4HistER \
   ,  ucDefMinERMeanRssiLevel \
   ,  ucDefWATOTimeInSec \
}

#define cInitHistID ((unsigned long) 0xFFFFFFFFU)
#define cWAHistIDSetDefInit {cInitHistID,cInitHistID,cInitHistID,cInitHistID}
#define cWAHistWPSetDefInit {(unsigned char) 8,(unsigned char) 8,(unsigned char) 8,(unsigned char) 8}

#define cSumABSig (unsigned char) 4

#ifdef BUILD_LORDSTOWN
#define cDefaultABSCountNr 108
#else
#define cDefaultABSCountNr 96
#endif

#define ucDefAutolocationFailedCounterInit ((unsigned char) 10U - 1U)
#define RealOutput
#define FPA
#define ABS_Test_LOG_ENABLE

extern void UpdateHistoryFromRAMWIthTheOneFromNVM(
   void);
extern unsigned char WAInit(
   void);
extern unsigned char ucLearnID(
   struct InputWA* ptInputWA);
extern unsigned char ucWATO(
   void);
extern unsigned char ucGetColOfID(
   unsigned long* pt2ID);
extern unsigned char ucGetWPOfCol(
   unsigned char ucIx);
extern unsigned long ulGetID(
   unsigned char ucIx);
extern uint8 ucSetID(
   uint32* pt2ID,
   uint8* pt2Pos);
extern unsigned char ucGetIndexOfHistoryWP(
   unsigned char ucWPNumber);
extern unsigned long ulGetZOMID(
   unsigned char ucIx);
extern unsigned char ucGetZOMWP(
   unsigned char ucIx);

#pragma PRQA_NO_SIDE_EFFECTS ulGetZOMID

extern unsigned char ucGetProbeCt(
   unsigned char ucIx);

#pragma PRQA_NO_SIDE_EFFECTS ucGetProbeCt

extern unsigned char ucSetHistory(
   unsigned char ucType);
extern void AlignZOM(
   unsigned short ushERSlot);
extern void ClearZOM(
   unsigned char ucIx);
extern void SetWAModeFix(
   void);
extern void SetWAModeLearn(
   void);
extern unsigned char* GETpucStartAdrWP(
   void);
extern unsigned short ushGetMeanRssiSum(
   unsigned char ucIx);
extern unsigned char ucGetRssiDifference(
   unsigned char ucFirstIx,
   unsigned char ucSecondIx);

#pragma PRQA_NO_SIDE_EFFECTS ushGetMeanRssiSum

extern unsigned char ucGetZOMPosOfID(
   unsigned long* pt2ID);
extern void IncrHistProtectTimer(
   void);
extern void WALLOC_UpdateTelegramSkipTimer(
   void);
extern unsigned char WALLOC_ucGetMinSpeedAutoLearnStart(
   void);
extern unsigned char ucCheckPotentialErInZom(
   void);
extern boolean bGetHistProtecTimeOver(
   void);
#pragma PRQA_NO_SIDE_EFFECTS bGetHistProtecTimeOver

#ifdef FPA
extern void RebuildABSRef(
   unsigned char ucWP,
   unsigned char ucABSTicksOneRevol,
   unsigned char ucCorrectionValue);
extern void ReNewABSRef(
   void);
extern void SortBiggest1st(
   unsigned char* ptVal,
   unsigned char* ptIx,
   unsigned char ucMax);
extern void IncAxisDetectionError(
   void);
extern void ResetAllocType(
   void);
extern void ResetNrOfTOs(
   void);
extern void ResetAllocErrorCnt(
   void);

#ifdef ABS_Test_LOG_ENABLE
extern unsigned char ucABSigOFL_MOD_ZAHN(
   unsigned char ucABSTicksRevol);
extern unsigned char ucGetABSTicksFullRevolFrontAx(
   void);
extern unsigned char ucGetABSTicksFullRevolRearAx(
   void);
#endif

#endif //FPA

extern void ResetHistoryToDefault(
   void);

#endif
