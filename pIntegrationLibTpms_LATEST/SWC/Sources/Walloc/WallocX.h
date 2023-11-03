#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "cd_decoder_x.h"

#define Test_LOG_ENABLE 1
#define FPA
#define cSumWE  16
#define cMaxLR  4
#define cHiStateZG (uint8) 2U
#define cHiStateER (uint8) 1U
#define cWheelPos_FL  cRadPosVL
#define cWheelPos_FR  cRadPosVR
#define cWheelPos_RL  cRadPosHL
#define cWheelPos_RR  cRadPosHR
#define cWheelPos_NA  cRadPosUndef
#define cIDStateSpinning 0x0C
#define cIDStateSpinLeft 0x08
#define cIDStateSpinRight 0x04
#define cRLTelValid 0x80
#define ucBkwdc (uint8) 0x40
#define ucNoDriveInfoc (uint8) 0x80
#define cIDStateDrvBack 0x40
#define cIDStateNoDrvInfo 0x80
#define cIDStateM4 0x04
#define cWAChange       (uint8)0xF0
#define cWAStateBreak   (uint8)0x08
#define cWAStateZO      (uint8)0x04
#define cWAStateER      (uint8)0x02
#define cWAStateActive  (uint8)0x01
#define ucDefWACtrl (uint8) 0
#define cWAParInitialized (uint8) 0x55
#define ucDefMinERMeanRssiLevel (uint8) 14
#define ucDefMinCt4ER (uint8) 7
#define ucDefMinCt4HistER (uint8) 3
#define ucDefWATOTime (uint8) 108
#define ucDefLEARNTime (uint8) 33
#define ucMinCt4ERReset (uint8) 6
#define cABSTickError (uint16) 0xFFFFU
#define cREOff                  (uint16)0x01
#define cREStationary           (uint16)0x02
#define cLearnWMotion           (uint16)0x03
#define cLearnWoMotion          (uint16)0x04
#define cNormalDriveWMotion     (uint16)0x05
#define cNormalDriveWoMotion    (uint16)0x06
#define cDeltaP                 (uint16)0x01
#define cLFTriggered            (uint16)0x02
#define cScheduled              (uint16)0x03
#define cNoLts                  (uint16)0x01
#define cLts7days               (uint16)0x02
#define cLts30days              (uint16)0x03
#define cRestoreZomContents     FALSE
#define cRestartLearnLocate     TRUE

typedef struct{
  uint8 ucWACtrl;
  uint8 ucWAParInitialized;
  uint8 ucMinCt4ER;
  uint8 ucMinCt4HistER;
  uint8 ucMinERMeanRssiLevel;
  uint8 WATOTime;
  uint8 LEARNTime;
}tWAParameter;

struct ZOMSlot{
  uint32 ulID;
  uint16 ushMVdN[4];
  uint16 ushMVdN2[4];
  uint16 ushRssiSum;
  uint16 ushPosCompVal[4];
  uint16 ushPosCompVal2[4];
  uint8  ucAbsoluteProbeCt;
  uint8  ucLearnProbeCt;
  uint8  ucLocateProbeCt;
  uint8  ucStatus;
  uint8  ucResetABSRefFlag;
  uint8  ucABSRef[4];
  uint8  ucLearnTimer;
  uint8  ucFrameCounter;
  uint8  ucP;
  uint8  ucT;
};

#ifdef Test_LOG_ENABLE
struct ZOMInfoSlot{
  uint8 ucABSComp[4];
  uint8 ucDistanceStandard[4];
  uint8 ucDistanceShadow[4];
  uint8 ucRelCmpVal[4];
  uint8 ucDeltaMin;
  uint8 ucToothTelCtCorrLearnBit;
  uint8 ucToothTelCtCorrNoLearnBit;
  uint8 ucToothTelCtNoCorr;
  uint8 ucToothTelCtNoLearnMode;
  uint16 ushABSRefOffset[4];
};
#endif

extern struct ZOMSlot tZOM[cSumWE];

#ifdef Test_LOG_ENABLE
extern struct ZOMInfoSlot tZOMInfo[cSumWE];
#endif

extern uint8 InitWAL( Rte_Instance self, boolean bClearZom);
extern uint8 ucLearnID( Rte_Instance self, const tRFTelType * ptInputWA);
extern uint8 ucWATO( Rte_Instance self, uint8* ucOpenPositions);
extern void  TickAbsoluteLearnTimerWAL(void);
extern void  TickSingleRELearnTimerWAL(void);
extern uint8 ucGetWATOTimeWAL(void);
extern void  PutWATOTimeWAL(uint8 ucTime);
extern uint8 ucGetLEARNTimeWAL(void);
extern void  PutLEARNTimeWAL(uint8 ucTime);
extern uint16 ushFindIdSetInZomWAL(const uint32 *ptHistSet, uint8 ucMinProbeCt, uint8 ucSlots2Search);
extern void SetbackLearnProbeCountersWAL(void);
extern void SetbackLocateProbeCountersWAL(void);
extern void ClearReDriveModeStateWAL(void);
extern uint8 ucGetColOfID(const uint32* pt2ID);
extern uint8 ucGetColOfWP(uint8 ucWP);
extern uint8 ucGetWPOfColWAL(uint8 ucIx);
extern uint32 ulGetIDOfColWAL(uint8 ucIx);
extern uint8 ucGetSuppIdOfColWAL(uint8 ucIx);
extern uint8 ucSetHistoryID( Rte_Instance self, uint32 ulID, uint8 ucWP);
extern void  ClearHistoryWPs( Rte_Instance self);
extern uint8 ucGetWAState(void);
extern uint8 ucGetHistoryState(void);
extern uint8 ucGetHistoryWpChangedBits(void);
extern uint8 ucGetHistoryIdChangedBitsWAL(void);
extern uint32* GetPointerToHistoryIdSetWAL(void);
extern void SetZOMWP(uint8 ucIx,uint8 ucWP);
extern uint32 ulGetZOMID(uint8 ucIx);
extern uint8 ucGetZOMPosOfID(const uint32* pt2ID);
extern uint8 ucGetZomStatus(uint8  ucIdx);
extern uint8 ucGetZomToothTelCtCorrLearnBit(uint8 ucIdx);
extern uint8 ucGetZomToothTelCtCorrNoLearnBit(uint8 ucIdx);
extern uint8 ucGetZomToothTelCtrNoCorr(uint8 ucIdx);
extern uint8 ucGetZomToothTelCtNoLearnMode(uint8 ucIdx);
extern uint8 ucGetZomLocateProbeCt(uint8 ucIdx);
extern uint8 ucGetZomDeltaMin(uint8 ucIdx);
extern uint16 ushGetZomDeltaSum(uint8 ucIdx, uint8 ucWP, uint8 ucSpec);
extern uint8 ucGetZomAbsComp(uint8 ucIdx, uint8 ucPos);
extern uint8 ucGetZomAbsMetrics(uint8 ucIdx, uint8 ucPos);
extern uint8 ucGetZomPalFrameCounter(uint8 ucIx);
extern uint8 ucGetZomResetAbsRefFlag(uint8 ucIdx);
extern uint8 ucGetZomAbsRefStartValue(uint8 ucIdx, uint8 ucPos);
extern uint16 ushGetZomAbsRefValue(uint8 ucSpectrum, uint8 ucIdx, uint8 ucPos);
extern uint8 ucGetZomLearnProbeCt(uint8 ucIdx);
extern uint8 ucGetZomAbsoluteProbeCt(uint8 ucIdx);
extern uint8 ucGetZomPressure(uint8 ucIdx);
extern uint8 ucGetZomTemperature(uint8 ucIdx);
extern uint8 ucGetZomDistanceValue(uint8 ucSpectrum, uint8 ucIdx, uint8 ucPos);
extern uint8 ucNrOfBitSet16(uint16 ushTarget);
extern uint8 ucNrOfBitSet8(uint8 ucTarget);
extern uint8* pucGetNewWheelPosOfIdWAL_debug( Rte_Instance self, uint8 * pucPermState);

#ifdef __cplusplus
}
#endif
