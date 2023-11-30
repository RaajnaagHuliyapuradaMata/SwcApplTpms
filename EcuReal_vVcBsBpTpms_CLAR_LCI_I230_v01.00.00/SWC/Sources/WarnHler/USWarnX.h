#ifndef USWarnX_h
#define USWarnX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

#define cIxPMinEU ((uint8) 0)
#define cIxPMinUS ((uint8) 1)
#define ucPorInitc                cIxPMinEU
#define ucDiagServicec            ((uint8)  4)
#define ucComparec                ((uint8)  5)
#define ucFilterActivationc       ((uint8)  6)
#define ucCfgReInitSinglec        ((uint8) 10)
#define ucCfgTReifenSinglec       ((uint8) 11)
#define ucRdParaSubSetc           ((uint8) 12)
#define ucWrParaSubSetc           ((uint8) 13)
#define ucResetWarnVectorc        ((uint8) 14)
#define ucGetWarnVectorsc         ((uint8) 19)
#define ucGetPTSollc              ((uint8) 22)
#define ucCfgPMinc                ((uint8) 23)
#define ucCfgPSollMinc            ((uint8) 24)
#define ucGetWThresc              ((uint8) 32)
#define ucTimerStopc              ((uint8) 33)
#define ucTPMSMsgOutc             ((uint8)  6)
#define ucNewPositionsc           ((uint8)  2)
#define ucClearPosc               ((uint8)  3)
#define ucWrWnValidTMc            ((uint8)  4)
#define ucRdWnValidTMc            ((uint8)  5)
#define ucClearWarnOfIdc          ((uint8)  6)
#define ucGetWarnVectorsIdc       ((uint8)  8)
#define ucPutWarnVectorSetc       ((uint8)  9)
#define ucCountc                  ((uint8)  7)
#define ucIniTimec                ((uint8)  8)
#define ucWrParaBytec             ((uint8)  1)
#define ucWrParaThresc            ((uint8)  2)
#define ushHWNoPosc               ((uint16) 0x0001)
#define ushHWPosFLc               ((uint16) 0x0002)
#define ushHWPosFRc               ((uint16) 0x0004)
#define ushHWPosRLc               ((uint16) 0x0008)
#define ushHWPosRRc               ((uint16) 0x0010)
#define ushHWPosSTc               ((uint16) 0x0020)
#define ushWWPosFLc               ((uint16) 0x0040)
#define ushWWPosFRc               ((uint16) 0x0080)
#define ushWWPosRLc               ((uint16) 0x0100)
#define ushWWPosRRc               ((uint16) 0x0200)
#define ushWWPosSTc               ((uint16) 0x0400)
#define ushWWNoPosc               ((uint16) 0x0800)
#define ucMaxWTGroupc    ((uint8) 8)
#define cucWT_GroupA     ((uint8) 0)
#define cucWT_GroupB     ((uint8) 1)
#define cucWT_GroupC     ((uint8) 2)
#define cucWT_GroupD     ((uint8) 3)
#define cucWT_GroupE     ((uint8) 4)
#define cucWT_GroupF     ((uint8) 5)
#define cucWT_GroupG     ((uint8) 6)
#define cucWT_GroupH     ((uint8) 7)
#define cucWsIdWN             ((uint8) 1)
#define cucCdIdWN             ((uint8) 2)
#define cucTsIdTM             ((uint8) 4)
#define cucCbIdTM             ((uint8) 5)
#define cucWarnTypeArrayIdWN  ((uint8) 6)
#define cucShortTimerIdWN     ((uint8) 7)
#define cucLongTimerIdWN      ((uint8) 8)
#define ucPosDepWarnc       ((uint8) 0x80)
#define cucWarnOutArrayDim    ((uint8) 2)
#define cucWarnOutStateIx     ((uint8) 0)
#define cucWarnOutAttrIx      ((uint8) 1)

typedef struct{
  uint8 ucAccess;
  uint8 ucParaByte[2];
}tParaSubSet;

typedef struct{
  uint8 ucId;
  uint8 ucPos;
  uint8 ucSystemState;
  uint8  ucWarnState;
  uint8  ucWarnAttr;
}tTPMSMsgData;

typedef struct{
    uint8  ucPMinAbs;
    uint8  aucPSollMin[cAnzRad];
    uint8  aucPSoll[2][cAnzRad];
    sint8  ascTSoll[2][cAnzRad];
    uint16 aushMSoll[cAnzRad];
    uint8  aucPinitTreifen[cAnzRad];
    sint8  ascTreifen[cAnzRad];
    uint8  aucEnvPres[cAnzRad];
    sint8  ascEnvTemp[cAnzRad];
}tCalibrationTab;

extern uint8 ucWarnManagerWN( Rte_Instance self, uint8 ucAction, uint8* pucData);
extern uint8 ucTPMSMsgManagerTM( Rte_Instance self, uint8 ucAction, uint8* pucData);
extern void TimerWT( Rte_Instance self, uint8 ucAction);
extern void TimerStopWT(void);
extern uint8 ucUSWAlgoParaWN( Rte_Instance self, uint8 ucAction, const uint8* pucData);
extern void InitUSWAlgo( Rte_Instance self, const uint8* ptWPos);
extern uint32 GETulWarnOutTM(void);
extern uint32 GETulWarnAttrOutTM(void);
extern uint8  GETucWarningGroupTM( uint8 ucWarningGroup);
extern uint8 ucGetUSEUCode(void);
extern uint8 GetDropIsoCodVal(void);

#ifdef __cplusplus
}
#endif

#endif
