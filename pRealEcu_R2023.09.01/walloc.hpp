

#ifndef WALLOC_H
#define WALLOC_H

#ifdef IBTCM_SW_ANPASSUNGEN
   #include "Tpms_Rte_Data_Type.hpp"
#else
    #include "types.hpp"
#endif

#define cInitialState (unsigned char) 0
#define cNoAxis (unsigned char) 0xCF
#define cECUAxis (unsigned char) 0x10
#define cFrontAxis (unsigned char) 0x10
#define cOtherAxis (unsigned char) 0x20
#define cBackAxis (unsigned char) 0x20
#define cNoSpin (unsigned char) 0x3F
#define cRightSpin (unsigned char) 0x40
#define cLeftSpin (unsigned char) 0x80

#define cWP_RR (unsigned char) 0x08
#define cWP_RL (unsigned char) 0x04
#define cWP_FR (unsigned char) 0x02
#define cWP_FL (unsigned char) 0x01

#define cNoWPos (unsigned char) 0xF0

struct ZOMSlot
{
  unsigned long ulID;

  unsigned char ucStatus;

  unsigned char ucProbeCt;
  unsigned char ucLeftCt;
  unsigned char ucRightCt;

  unsigned short ushVariation;
  unsigned short ushRssiSum;
  unsigned char ucLastRssi;
  unsigned char ucSkipNewTelTimerInSec;

#ifdef FPA
  unsigned char ucABSRef[4];    // ABS sensor's freerunning tick info at very 1st tel reception at all 4 wheel pos ( = index)
  unsigned short ushMVdN[4];        // dN's mean value (index is pos R)
  unsigned short ushPosCompVal[4];  // indicator for constant sending position (sum of deltas, smallest==best)
  unsigned short ushMVdN2[4];        // 2nd dN2's mean value (index is pos R)
  unsigned short ushPosCompVal2[4];  // 2nd indicator for constant sending position (sum of deltas
  unsigned char ucRelCmpVal[4];     // relative indicator for constant sending position in percent (smallest==best)
  unsigned char ucSort[4];          // sorted by hight indices of ucRelCmpVal
  unsigned char ucAlgoTelEvtCnt;	//amount of APC-telegrams/events used in auto location algorithm
  unsigned char ucResetABSRefFlag;
  boolean  bPotNewID;				//set TRUE if the ID is a potential candidat for own wheels (ER)
  boolean  bOwnID;					//set TRUE if the ID is one of own wheels (ER)
#endif
};

extern unsigned char ucGetERState(void);
extern unsigned char ucSumCtID(unsigned char ucMinCt, unsigned char ucMinRssi);
extern void SetZOMWP(unsigned char ucIx,unsigned char ucWP);

#ifdef WALLOC_INT
WAParameter tWAPar;

#ifdef pb_ModulTest_050104
struct ZOMSlot tZOM[cSumWE];
#else
#ifdef IBTCM_SW_ANPASSUNGEN
struct ZOMSlot tZOM[cSumWE];
#else
#pragma DATA_SEG RAM_ZOM
struct ZOMSlot tZOM[cSumWE];
#pragma DATA_SEG DEFAULT
#endif
#endif

#else
extern WAParameter tWAPar;

#ifdef pb_ModulTest_050104
extern struct ZOMSlot tZOM[cSumWE];
#else
#ifdef IBTCM_SW_ANPASSUNGEN
extern struct ZOMSlot tZOM[cSumWE];
#else
#pragma DATA_SEG RAM_ZOM
extern struct ZOMSlot tZOM[cSumWE];
#pragma DATA_SEG DEFAULT
#endif
#endif

#endif

#endif

