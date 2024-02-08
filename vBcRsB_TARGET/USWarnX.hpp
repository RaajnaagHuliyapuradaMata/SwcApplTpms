
#ifndef USWarnX_H

#define USWarnX_H

#include "global.hpp"

struct ParaSubSet
{
  unsigned char ucAccess;

  unsigned char ucParaByte[2];

  signed char scTResLimit;

  unsigned char ucParaHighPressThres;
  unsigned char ucParaHighPressResetThres;
  unsigned char ucParaAxImbSetThres;
  unsigned char ucParaAxImbResThres;
};

typedef struct ParaSubSet PSSType;

extern unsigned char ucWarnManagerWN(unsigned char ucAction, unsigned char *ptData);

//#define DEBUG_WARNING_THRESHOLDS

#ifdef DEBUG_WARNING_THRESHOLDS
  extern void DebugWarnTresh(unsigned char *ptData);
#endif
struct HFTel
{
   unsigned char ucId;
   unsigned char ucP;
   signed char scTWE;
   unsigned char ucLifeTime;
   unsigned char ucState;
   unsigned short ushVehicleSpeed;
   signed char scTa;
   signed char scTref;
   unsigned char ucKLState;
};

#define ucPMinc    (unsigned char) 0x01
#define ucAxImbc   (unsigned char) 0x02
#define ucFTc      (unsigned char) 0x04
#define ucDHWc     (unsigned char) 0x08
#define ucHardTc   (unsigned char) 0x10
#define ucHiPc     (unsigned char) 0x20
#define ucTWc      (unsigned char) 0x40
#define ucEuFc     (unsigned char) 0x80

extern unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData);

extern void WrWnValidTMc(struct ParaSubSet *plptru8Data);

extern void RdWnValidTMc(struct ParaSubSet *plptru8Data);

struct TssMsg
{
  unsigned char ucId;
  unsigned char ucPos;
  unsigned char ucSystemState;
  unsigned char ucWarning;
};

extern void TimerWT( unsigned char ucAction );

extern unsigned char ucUSWAlgoPara(unsigned char ucType, unsigned char ucPres, struct ParaSubSet *ptPara);

extern void InitUSWAlgo(const unsigned char *ptWPos);

extern void RdParaSubSet(struct ParaSubSet * ptData);
extern void WrParaSubSet(struct ParaSubSet * ptData);

#define ucWPFLc (unsigned char) 0
#define ucWPFRc (unsigned char) 1
#define ucWPRLc (unsigned char) 2
#define ucWPRRc (unsigned char) 3
#define ucWPNAc (unsigned char) 4
#define ucWPSTc (unsigned char) 4
#define ucWPUNc (unsigned char) 8

#define cIxPMinEU 0
#define cIxPMinUS 1
#define cIxPMinXL 2

#define ucPorInitc 1
#define cKl15Init 2
#define cSingleIdInit 3
#define ucDiagServicec 4
#define ucPorInitUSc 5

#define ucComparec 5

#define ucCfgCtryCodec  1
#define ucCfgReInitSinglec  10
#define ucRdParaSubSetc 12
#define ucWrParaSubSetc 13
#define ucResetWarnVectorc 14
#define ucCfgPSollMinAtIdc 15
#define ucGetIsoc 16
#define ucGetPSollAtTempc 17
#define ucGetPSollMinc 18
#define ucGetWarnVectorsc 19
#define ucGetHWFreakBitsc 21
#define ucGetPTSollc 22
#define ucCfgPMinc  (unsigned char) 23
#define ucCfgPFactorc  24
#define ucCfgDHWc 25
#define ucCfgFTc  26
#define ucCfgHTc 27
#define ucCfgHTVc 28
#define ucCfgSTc  29
#define ucCfgTSc 30
#define ucGetWarnTypec 31

#define ucGetPwarmc 32
#define PutPwarm 33

#define ucTssMsgOutc 6

#define ucNewPositionsc  2
#define ucClearPosc 3
#define ucWrWnValidTMc 4
#define ucRdWnValidTMc 5
#define ucClearWarnOfIdc 6
#define ucGetWarnVectorsIdc 8
#define ucPutWarnVectorSetc 9
#define ucGetPosOfIdc 10
#define ucGetIdcOfPos 11

#define ucCountc (unsigned char) 7
#define ucIniTimec (unsigned char) 8

extern unsigned char aucWheelPosWarn[ucMaxPosc + 1];

#define GETbPMFL() ( (aucWheelPosWarn[ucWPFLc] & ucPMinc) == ucPMinc )
#define GETbPMFR() ( (aucWheelPosWarn[ucWPFRc] & ucPMinc) == ucPMinc )
#define GETbPMRL() ( (aucWheelPosWarn[ucWPRLc] & ucPMinc) == ucPMinc )
#define GETbPMRR() ( (aucWheelPosWarn[ucWPRRc] & ucPMinc) == ucPMinc )
#define GETbPMNA() ( (aucWheelPosWarn[ucWPNAc] & ucPMinc) == ucPMinc )

#define GETbFax() ( ((aucWheelPosWarn[ucWPFLc] & ucAxImbc) == ucAxImbc) && ((aucWheelPosWarn[ucWPFRc] & ucAxImbc) == ucAxImbc) )
#define GETbRax() ( ((aucWheelPosWarn[ucWPRLc] & ucAxImbc) == ucAxImbc) && ((aucWheelPosWarn[ucWPRRc] & ucAxImbc) == ucAxImbc) )

#define GETbDHWFL() ( (aucWheelPosWarn[ucWPFLc] & ucDHWc) == ucDHWc )
#define GETbDHWFR() ( (aucWheelPosWarn[ucWPFRc] & ucDHWc) == ucDHWc )
#define GETbDHWRL() ( (aucWheelPosWarn[ucWPRLc] & ucDHWc) == ucDHWc )
#define GETbDHWRR() ( (aucWheelPosWarn[ucWPRRc] & ucDHWc) == ucDHWc )
#define GETbDHWNA() ( (aucWheelPosWarn[ucWPNAc] & ucDHWc) == ucDHWc )

#define GETbHiPFL() ( (aucWheelPosWarn[ucWPFLc] & ucHiPc) == ucHiPc )
#define GETbHiPFR() ( (aucWheelPosWarn[ucWPFRc] & ucHiPc) == ucHiPc )
#define GETbHiPRL() ( (aucWheelPosWarn[ucWPRLc] & ucHiPc) == ucHiPc )
#define GETbHiPRR() ( (aucWheelPosWarn[ucWPRRc] & ucHiPc) == ucHiPc )
#define GETbHiPNA() ( (aucWheelPosWarn[ucWPNAc] & ucHiPc) == ucHiPc )

#define GETbSoftPFL() ( (aucWheelPosWarn[ucWPFLc] & ucLowPc) == ucLowPc )
#define GETbSoftPFR() ( (aucWheelPosWarn[ucWPFRc] & ucLowPc) == ucLowPc )
#define GETbSoftPRL() ( (aucWheelPosWarn[ucWPRLc] & ucLowPc) == ucLowPc )
#define GETbSoftPRR() ( (aucWheelPosWarn[ucWPRRc] & ucLowPc) == ucLowPc )
#define GETbSoftPNA() ( (aucWheelPosWarn[ucWPNAc] & ucLowPc) == ucLowPc )

#define GETbPECEFL() ( (aucWheelPosWarn[ucWPFLc] & ucEuFc) == ucEuFc )
#define GETbPECEFR() ( (aucWheelPosWarn[ucWPFRc] & ucEuFc) == ucEuFc )
#define GETbPECERL() ( (aucWheelPosWarn[ucWPRLc] & ucEuFc) == ucEuFc )
#define GETbPECERR() ( (aucWheelPosWarn[ucWPRRc] & ucEuFc) == ucEuFc )
#define GETbPECENA() ( (aucWheelPosWarn[ucWPNAc] & ucEuFc) == ucEuFc )

#define GETbTWFL() ( (aucWheelPosWarn[ucWPFLc] & ucTWc) == ucTWc )
#define GETbTWFR() ( (aucWheelPosWarn[ucWPFRc] & ucTWc) == ucTWc )
#define GETbTWRL() ( (aucWheelPosWarn[ucWPRLc] & ucTWc) == ucTWc )
#define GETbTWRR() ( (aucWheelPosWarn[ucWPRRc] & ucTWc) == ucTWc )
#define GETbTWNA() ( (aucWheelPosWarn[ucWPNAc] & ucTWc) == ucTWc )

extern unsigned short ushWarnOutTM;

#define GETbPhartWN()          ( (ushWarnOutTM & ushHWNoPosc) == ushHWNoPosc )
#define GETbPhartVlWN()        ( (ushWarnOutTM & ushHWPosFLc) == ushHWPosFLc )
#define GETbPhartVrWN()        ( (ushWarnOutTM & ushHWPosFRc) == ushHWPosFRc )
#define GETbPhartHlWN()        ( (ushWarnOutTM & ushHWPosRLc) == ushHWPosRLc )
#define GETbPhartHrWN()        ( (ushWarnOutTM & ushHWPosRRc) == ushHWPosRRc )
#define GETbPweichVlWN()       ( (ushWarnOutTM & ushWWPosFLc) == ushWWPosFLc )
#define GETbPweichVrWN()       ( (ushWarnOutTM & ushWWPosFRc) == ushWWPosFRc )
#define GETbPweichHlWN()       ( (ushWarnOutTM & ushWWPosRLc) == ushWWPosRLc )
#define GETbPweichHrWN()       ( (ushWarnOutTM & ushWWPosRRc) == ushWWPosRRc )
#define GETbPweichRrWN()       ( (ushWarnOutTM & ushWWPosSTc) == ushWWPosSTc )
#define GETbPminVlWN()         ( (ushWarnOutTM & ushHWPosFLc) == ushHWPosFLc )
#define GETbPminVrWN()         ( (ushWarnOutTM & ushHWPosFRc) == ushHWPosFRc )
#define GETbPminHlWN()         ( (ushWarnOutTM & ushHWPosRLc) == ushHWPosRLc )
#define GETbPminHrWN()         ( (ushWarnOutTM & ushHWPosRRc) == ushHWPosRRc )

#define GETbPminWN()           ( (ushWarnOutTM & ushHWNoPosc) == ushHWNoPosc )
#define GETbPweichWN()         ( (ushWarnOutTM & ushWWNoPosc) == ushWWNoPosc )

#define GETushWarnstatus1WN()  ( ushWarnOutTM )
#define GETucLoWarnstatus1WN() ( (unsigned char) ushWarnOutTM )
#define GETucHiWarnstatus1WN() ( (unsigned char) (ushWarnOutTM >> 8) )

extern struct ParaSubSet tPSSA;

struct WD
{
  signed char scTResLimit;
  unsigned char ucParaHighPressThres;
  unsigned char ucParaHighPressResetThres;
  unsigned char ucParaAxImbSetThres;
  unsigned char ucParaAxImbResThres;
};

#ifdef pb_ModulTest_02062003
extern void ResetCtrl(void);
#endif

#endif
