
#ifndef WallocX_H
#define WallocX_H

struct InputWA
{
  unsigned long ulID;
  unsigned char ucStatus;
  unsigned char ucRssi;
};

typedef struct{
  unsigned char ucWACtrl;
  unsigned char ucMinRssiLevel;
  unsigned char ucMinRssiDistance;
  unsigned char ucMinVariationDistance;
  unsigned char ucLeRiMinDistance;
  unsigned char ucEcuPosition;
  //unsigned char ucMinCt4AxAnalysis;
  unsigned char ucMinCt4ER;
  unsigned char ucMinCt4HistER;
  unsigned char ucMinCt4ZomReset;
  unsigned char ucMinERMeanRssiLevel;
  unsigned char WATOTimeInSec;
  unsigned char ucTimeoutAutoLoc;

  unsigned char ucNewMinCntEvt;
  unsigned char ucMinTimeProtectER ;
  unsigned char ucnMinRxTGRF;

  unsigned char ucnRelValMinDiff;
  unsigned char ucnRelValMidDiff;
  unsigned char ucnRelValCompetDiff;
  unsigned char ucMaxZOnorm;
  unsigned char ucnMinA;

  unsigned char ucMinSpeedAutoLearnStart;
//  unsigned char ucMinSpeedAutoLearnCont;    //TODO Sergej: Handling of all new WAParameters members in NvM!
  unsigned char ucOffsetOverlapsGXe;
  unsigned char ucnVweight;
  unsigned char ucMinOffsetGXe;
  unsigned char ucSufficientRssiDistance;
}WAParameter;

typedef struct{
   unsigned char ucFrontAxisABSTicks;
   unsigned char ucRearAxisABSTicks;
}WAABSTicksInOneRevolution;

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
#endif

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
#define ucDefMinRssiDistance (unsigned char) 10 //07.12.2017 ssc: changed from 7 to 10 after tests on target vehicle
#define ucDefMinVariationDistance (unsigned char) 10
#define ucDefLeRiMinDistance (unsigned char) 1

#define ucECUPosFront (unsigned char) 0x55
#define ucECUPosRear (unsigned char) 0xAA
#define ucECUPosNeutral (unsigned char) 0xFF

//#define ucDefMinCt4AxAnalysis (unsigned char) 15
#define ucDefMinCt4ER (unsigned char) 9 // 12 2008-11-28 ur - OIL#220
//#ifdef BUILD_RIVIAN //this is defined in makefile!
//#define ucDefMinCt4HistER (unsigned char) 3 // 2021-07-20 rst - increased to 3 for Rivian because the first TG always comes from standstill monitoring NVM!
//#else                                       //2021-08-11 rst - took it back. takes too long if pressure on key feature is deactivated
#define ucDefMinCt4HistER (unsigned char) 2
//#endif
#define ucDefMinCt4ZomReset (unsigned char) 8
#define ucDefMinERMeanRssiLevel (unsigned char) 28 // 15;  2008-11-28 ur - OIL#220
#define ucDefWATOTimeInSec (unsigned char) 60
#define ucDefTimeoutAutoLoc (unsigned char) 9
#define ucDefNewMinCntEvt (unsigned char) 5 // nNewMinCntEvt from APC algorithm design
#define ucDefMinTimeProtectER (unsigned char)  3 //time in minute to protect historic own wheels
#define ucnDefMinRxTGRF (unsigned char) 15 // compare value for minimum number of Rf telegrams from each (own) wheel sensor
#define ucDefnRelValMinDiff (unsigned char) 5 //default value for percent difference between smallest relative value and 2nd smallest
#define ucDefnRelValMidDiff (unsigned char) 5 //default value for percent difference between two middle relative values
#define ucDefnRelValCompetDiff (unsigned char) 10 //default value for percent difference between two competing for the same position WS
#define ucDefMaxZOnorm (unsigned char) 15  //default value for maximally allowed relative value to put a new learned WS instead of a History WS
#define ucDefnMinA (unsigned char) 10 // default value for minimal allowed percent difference between the smallest and the highest relative value
#define ucDefMinSpeedAutoLearnStart 30 //default value for minimal speed allowed to start with auto-learn routine
#define ucDefMinSpeedAutoLearnCont (unsigned char) 7 // default value for minimal speed allowed to continue with auto-learn routine
#define ucDefnVweight (unsigned char) 60 // default value for velocity threshold to distinguish between low and high speed
#define ucDefMinOffsetGXe (unsigned char) 1 //default value for individual offset adjustment of the ECU antenna offset.
#define ucDefSufficientRssiDistance (unsigned char) 12 // default value for RSSI distance between front and rear axis to do a side-allocation without ABS-diviation
#define ucDefOffsetOverlapsGXe    55U   // default value for RF interference level decision

#define cWADefInitParam \
{ \
 ucDefWACtrl, \
 ucDefMinRssiLevel, \
 ucDefMinRssiDistance, \
 ucDefMinVariationDistance, \
 ucDefLeRiMinDistance, \
 ucECUPosRear, \
 ucDefMinCt4AxAnalysis, \
 ucDefMinCt4ER, \
 ucDefMinCt4HistER, \
 ucDefMinERMeanRssiLevel, \
 ucDefWATOTimeInSec \
}
#define cInitHistID ((unsigned long) 0xFFFFFFFFU)
#define cWAHistIDSetDefInit {cInitHistID,cInitHistID,cInitHistID,cInitHistID}
#define cWAHistWPSetDefInit {(unsigned char) 8,(unsigned char) 8,(unsigned char) 8,(unsigned char) 8}

#define cSumABSig (unsigned char) 4 // available ABS signals FL,FR, RL, RR = 4

//Default value of ABS pulses for 1 revolution
#ifdef BUILD_LORDSTOWN    //define this in makefile, then it is independent from source code
#define cDefaultABSCountNr 108
#else
#define cDefaultABSCountNr 96
#endif
//#define cDefaultABSCountNr 96

#define ucDefAutolocationFailedCounterInit ((unsigned char) 10U - 1U) //starting value for the autolocation failed counter.

#ifdef WIN32
#ifndef _LIB
#ifndef _USRDLL
#define pb_ModulTest_050104
#endif
#endif
#endif
#define RealOutput  // generate detailed output telegram by telegram for real data simulation, while OFF only summary is printed
//#define pb_Statistic
//#define pb_FullStatOut  // generates detailed statistic data instead of WA algorithm simulation

#define FPA                // fix point allocation (Fixed Position wheel allocation )
//#define AEC                //
#define ABS_Test_LOG_ENABLE    //enable additional values for debug in ZOM

extern void UpdateHistoryFromRAMWIthTheOneFromNVM(void);
extern unsigned char WAInit(void);
extern unsigned char ucLearnID(struct InputWA *ptInputWA);
extern unsigned char ucWATO(void);

extern unsigned char ucGetColOfID(unsigned long *pt2ID);
extern unsigned char ucGetWPOfCol(unsigned char ucIx);
extern unsigned long ulGetID(unsigned char ucIx);
extern uint8 ucSetID(uint32 *pt2ID, uint8 *pt2Pos);//, unsigned char ucSum);
extern unsigned char ucGetIndexOfHistoryWP(unsigned char ucWPNumber);

extern unsigned long ulGetZOMID(unsigned char ucIx);
extern unsigned char ucGetZOMWP(unsigned char ucIx);
#pragma PRQA_NO_SIDE_EFFECTS ulGetZOMID

extern unsigned char ucGetProbeCt(unsigned char ucIx);
#pragma PRQA_NO_SIDE_EFFECTS ucGetProbeCt

extern unsigned char ucSetHistory(unsigned char ucType);
extern void AlignZOM(unsigned short ushERSlot);
extern void ClearZOM(unsigned char ucIx);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void RdWAPara(WAParameter *pPara2RdOut);
extern void WrWAPara(WAParameter *pPara2WrIn);
extern void InitHistory(void);
extern unsigned char  ucCheckHistRxEv(void);
extern unsigned char ucGetWATOTimeInSec(void);
extern void ChangeWAPara(void);
#endif//BUILD_WITH_UNUSED_FUNCTION
extern void SetWAModeFix(void);
extern void SetWAModeLearn(void);

extern unsigned char * GETpucStartAdrWP(void);
extern unsigned short ushGetMeanRssiSum(unsigned char ucIx);
extern unsigned char ucGetRssiDifference(unsigned char ucFirstIx, unsigned char ucSecondIx);

#pragma PRQA_NO_SIDE_EFFECTS ushGetMeanRssiSum

#ifdef G_USE_PART_ER
extern void PartWalloc_Init(void);
extern unsigned char CheckPartErCriteriaWA(const unsigned char);
extern unsigned char DecrPartErTimerWA(const unsigned char);
extern void SetPartErTimerWA(const unsigned char, const unsigned char);
#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char GetPartErTimerFinishWA(void);
#endif
#endif //G_USE_PART_ER
extern unsigned char ucGetZOMPosOfID(unsigned long *pt2ID);
extern void IncrHistProtectTimer(void);

extern void WALLOC_UpdateTelegramSkipTimer(void);
extern unsigned char WALLOC_ucGetMinSpeedAutoLearnStart(void);
extern unsigned char ucCheckPotentialErInZom(void);
extern boolean bGetHistProtecTimeOver(void);
#pragma PRQA_NO_SIDE_EFFECTS bGetHistProtecTimeOver

#ifdef FPA
extern void RebuildABSRef(unsigned char ucWP, unsigned char ucABSTicksOneRevol, unsigned char ucCorrectionValue);
extern void ReNewABSRef(void);
extern void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax);
extern void IncAxisDetectionError(void);
extern void ResetAllocType(void);
extern void ResetNrOfTOs(void);
extern void ResetAllocErrorCnt(void);
#ifdef G_USE_ROTATION_DIRECTION
extern void IncDirDetectionError(void);
#endif //G_USE_ROTATION_DIRECTION

#ifdef ABS_Test_LOG_ENABLE
extern unsigned char ucABSigOFL_MOD_ZAHN(unsigned char ucABSTicksRevol);
extern unsigned char ucGetABSTicksFullRevolFrontAx(void);
extern unsigned char ucGetABSTicksFullRevolRearAx(void);
#endif

#endif //FPA

extern void ResetHistoryToDefault(void);

#ifdef pb_ModulTest_050104
extern void TESTPrintWAStatus(void);
extern void TESTPrintHistory(void);
extern void TESTPrintWAParameters(void);
extern void TESTPrintZOM(unsigned char , unsigned char );
extern void TESTPrintCompleteWAData(void);
extern void TESTPrintInputWA(tRFTelType *);
extern void TESTPrintZOMAsLine(unsigned char ucStart, unsigned char ucWidth);
extern void TESTPrintZOMHL(unsigned char ucStart, unsigned char ucWidth);

extern unsigned char TESTucGetZOMStatus(unsigned char ucIx);
extern unsigned char TESTGetucWAState(void);
extern unsigned char TESTucGetToTime(void);
extern void TESTLoadHistory(unsigned long *, unsigned char *);

extern void TESTPutWayStretch(unsigned short * p2WayStretch);
extern void TESTPutLenkwinkel(signed short shLW);
extern void TESTPutSpeed(unsigned char ucCurSpeed);
extern void TESTPutABStick(unsigned short * p2ABStick);
extern void TESTPutFW(signed short * p2FW);

extern void TESTResetWallocRAM(void);

#ifdef AEC
extern void TESTPrintConcep5pb1HL(unsigned char ucStart, unsigned char ucWidth);
extern void TESTPrintConcep5pb1AsLine(unsigned char ucStart, unsigned char ucWidth);
extern unsigned char TESTucGetBCt(unsigned char i);
extern void TESTprinConcept5pb1Summary(unsigned char i);
extern void TESTprintStatisticSummary(unsigned char i);
extern void CtRealPEv(void);
extern void CtHit(unsigned long ulID);
extern void CtCE(void);
extern void CtBCtReset(void);
extern void CtACMReset(void);
extern void TESTPrintACM(void);
extern void BuildPeakRate(unsigned long ulID);
extern void PutMofID(unsigned short ushCurM, unsigned long * pulID);
extern void PUTBadPeakRate(unsigned short ushPeaks);
void TESTPrintPeakEvZOMHL(unsigned char ucStart, unsigned char ucWidth);
void TESTPrintPeakEvZOMAsLine(unsigned char ucStart, unsigned char ucWidth);
// CA STUFF___________________________________________________________________
extern void TESTPrintCAZOM_HL(unsigned char ucStart, unsigned char ucWidth);
extern void TESTPrintCAZOMAsLine(unsigned char ucStart, unsigned char ucWidth);
extern void TESTPrintCAZOMSummary(unsigned char i);

#endif  //AEC

#endif

#endif
