#ifndef WALLOC_H
#define WALLOC_H

#include "Tpms_Rte_Data_Type.hpp"

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

struct ZOMSlot{
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
  unsigned char ucABSRef[4];
  unsigned short ushMVdN[4];
  unsigned short ushPosCompVal[4];
  unsigned short ushMVdN2[4];
  unsigned short ushPosCompVal2[4];
  unsigned char ucRelCmpVal[4];
  unsigned char ucSort[4];
  unsigned char ucAlgoTelEvtCnt;
  unsigned char ucResetABSRefFlag;
  boolean  bPotNewID;
  boolean  bOwnID;
#endif
};

extern unsigned char ucGetERState(void);
extern unsigned char ucSumCtID(unsigned char ucMinCt, unsigned char ucMinRssi);
extern void SetZOMWP(unsigned char ucIx,unsigned char ucWP);
extern WAParameter tWAPar;
extern struct ZOMSlot tZOM[cSumWE];

#endif

