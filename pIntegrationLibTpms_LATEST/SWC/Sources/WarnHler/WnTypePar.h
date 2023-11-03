#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "TSS_StdX.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "Warn_Cfg.h"
#include "USWarnX.h"

#define ucIxWnCfgc            ((uint8) 0)
#define ucIxMsCfgc            ((uint8) 1)
#define ucMaxWarnTypeWNc      ((uint8) 8)
#define ucWarnBitArraySizeWNc ((uint8) 3)
#define ucWarnBitIxWNc        ((uint8) 0)
#define ucWarnBitTonnageIxWNc ((uint8) 1)
#define ucWarnBitAirMassIxWNc ((uint8) 2)
#define cucIX_Ppanne          ((uint8) 0)
#define cucIX_Pmin            ((uint8) 1)
#define cucIX_Pwarn           ((uint8) 2)
#define cucIX_PwarnTol        ((uint8) 3)
#define cucIX_Pvorw           ((uint8) 4)
#define cucIX_5               ((uint8) 5)
#define cucIX_DHW             ((uint8) 6)
#define cucIX_FT              ((uint8) 7)
#define cucWN_Ppanne          ((uint8) (1 << cucIX_Ppanne))
#define cucWN_Pmin            ((uint8) (1 << cucIX_Pmin))
#define cucWN_Pwarn           ((uint8) (1 << cucIX_Pwarn))
#define cucWN_PwarnTol        ((uint8) (1 << cucIX_PwarnTol))
#define cucWN_Pvorw           ((uint8) (1 << cucIX_Pvorw))
#define cucWN_5               ((uint8) (1 << cucIX_5))
#define cucWN_DHW             ((uint8) (1 << cucIX_DHW))
#define cucWN_FT              ((uint8) (1 << cucIX_FT))
#define cucWT_GrpPanne         cucWT_GroupA
#define cucWT_GrpPmin          cucWT_GroupB
#define cucWT_GrpPwarn         cucWT_GroupC
#define cucWT_GrpPvorw         cucWT_GroupD
#define cucWT_GrpDHW           cucWT_GroupE
#define cucWT_GrpFT            cucWT_GroupF
#define cWT_WNindex_map              { cucIX_Ppanne,    cucIX_Pmin,     cucIX_Pwarn,        cucIX_PwarnTol,       cucIX_Pvorw,        cucIX_5,  cucIX_DHW,        cucIX_FT     }
#define cWT_WNvector_map             { cucWN_Ppanne,    cucWN_Pmin,     cucWN_Pwarn,        cucWN_PwarnTol,       cucWN_Pvorw,        cucWN_5,  cucWN_DHW,        cucWN_FT     }
#define cAllWT_function              { bWT_Ppanne,      bWT_Pmin,       bWT_Pwarn,          bWT_PwarnTol,         bWT_Pvorw,          NULL,     bWT_DHW,          bWT_FT       }
#define cWT_WNcallbackClearWnBit_map { NULL,            NULL,           NULL,               NULL,                 NULL,               NULL,     ResetPresRefDHW,  NULL         }
#define cWT_WNcallbackSetWnBit_map   { NULL,            NULL,           NULL,               NULL,                 NULL,               NULL,     NULL,             NULL         }
#define cWT_WNcallbackTimerInit_map  { NULL,            NULL,           TimerInitPWARN,     TimerInitPWARNTOL,    TimerInitPVORW,     NULL,     TimerInitDHW,     NULL         }
#define cWT_WNcallbackTimerCount_map { NULL,            NULL,           TimerCountPWARN,    TimerCountPWARNTOL,   TimerCountPVORW,    NULL,     TimerCountDHW,    NULL         }
#define cWT_WNcallbackTimerStop_map  { NULL,            NULL,           TimerStopAllPWARN,  TimerStopAllPWARNTOL, TimerStopAllPVORW,  NULL,     TimerStopAllDHW,  NULL         }
#define cWT_Group_map                { cucWT_GrpPanne,  cucWT_GrpPmin,  cucWT_GrpPwarn,     cucWT_GrpPwarn,       cucWT_GrpPvorw,     255,      cucWT_GrpDHW,     cucWT_GrpFT  }
#define cWT_NonMaskable_map          { 1,               1,              1,                  1,                    0,                  0,        0,                1            }
#define cWT_FreakEnable_map          { 1,               1,              1,                  1,                    0,                  0,        0,                1            }
#define ush273Kelvinc ((uint16) 273)
#define ucEuroCodec   ((uint8) 0x00)
#define ucUSCodec     ((uint8) 0x04)
#define cInitialized  ((uint8) 0x01)
#define ucCtryMaskc   ((uint8) 0x0C)
#define cUSWAlgo_ParaByte1_US         ((uint8) 0x01)
#define cUSWAlgo_ParaByte1_EU         ((uint8) 0x02)
#define cUSWAlgo_ParaByte0_ROW        ((uint8)  0x02)
#define cUSWAlgo_ParaByte1_ROW        ((uint8)  0x00)
#define cUSWAlgo_ParaByte0_NAR ((uint8) 0x01)
#define cUSWAlgo_ParaByte1_NAR ((uint8) 0x00)
#define ucPResInMBarc  ((uint8) 25)
#define ucTimerTickInMsWTc      ((uint8) 100)
#define cucMinDistPvorw         ((uint8) 4)
#define ucThresFTc                ((uint8) (500 / ucPResInMBarc))

typedef struct{
  uint8  ucId;
  uint8  ucP;
  sint8  scTWE;
  uint8  ucLifeTime;
  uint16 ushVehicleSpeed;
  sint8  scTa;
  uint8  ucEnvP;
  uint8  ucWarnState;
  uint8  ucWarnAttr;
}tHFTelDat;

typedef struct{
  uint8 ucPwThresCfactorCOD;
  uint8 ucPwThresNCfactorCOD;
  uint8 ucAlThresCfactorCOD;
  uint8 ucAlThresNCfactorCOD;
  uint8  ucPrewarnDelayMinCOD;
  uint8  ucPanneThresCOD;
  uint8  ucShortHoldTimeCOD;
  uint8  ucLongHoldTimeCOD;
  uint8  ucThCTolCOD;
  uint8  ucThNCTolCOD;
  uint8  ucSaturierungAktivCOD;
}tCodingDat;

typedef struct{
  uint8  ucPSoll;
  sint8  scTSoll;
  uint16 ushMSoll;
  uint8  ucPanneClearHyst;
  uint8  ucPinitTreifen;
}tSollDat;

typedef struct{
  tHFTelDat   tHFD;
  tSollDat    tSD;
  tCodingDat  tCOD;
  boolean     bNoFreakNoTimer;
  uint8       ucCurWarnSetThres;
  uint8       ucCurWarnResetThres;
}tLocalWarnDat;

typedef uint8                 WarnConfigArrayType[2];
typedef uint8                 WarnBitArrayType[cAnzRad][ucWarnBitArraySizeWNc];
typedef uint16                ShortTimerArrayType[cAnzRad];
typedef uint8                 ShortTimerStateArrayType[cAnzRad];
typedef uint16                LongTimerArrayType[cAnzRad];
typedef uint8                 LongTimerStateArrayType[cAnzRad];

extern uint8  ucGetPMinCS(void);

extern uint8  ucGetWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWtAttr);
extern void   ClearWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx);
extern void   ClearWarnAttrBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWarnAttr);
extern uint8  ucSetWarnBitWN( uint8 ucIdX, uint8 ucWarnTypeIx, uint8 ucWtAttr);
extern uint8  ucGetPTolWN( uint8 ucPenv, uint8 ucPre, sint8 scTre);
extern void   PutWarnBitsToNvmWN( Rte_Instance self);

extern uint8  ucPfT( uint16 ushM, sint8 scT, uint8 ucPamb);
extern uint16 ushMIso( uint8 ucP, sint8 scT, uint8 ucPamb);

extern uint8  bWT_Ppanne( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_Pmin( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_Pwarn( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_PwarnTol( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_Pvorw( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_DHW( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);
extern uint8  bWT_FT( tLocalWarnDat* ptLWD, uint8 ucWarnCfg, uint8 ucWtIx);

extern void   ResetPresRefDHW( uint8 ucIdx);
extern void   TimerInitDHW( Rte_Instance self);
extern void   TimerCountDHW( Rte_Instance self);
extern void   TimerStopAllDHW(void);
extern void   GetTimerValDHW( uint8 ucZomPos, uint8* pucRefPres, uint8* pucLastPres, uint16* pushTimCnt, uint16* pushTimCountLatch);

extern void   TimerInitPVORW( Rte_Instance self);
extern void   TimerCountPVORW( Rte_Instance self);
extern void   TimerStopAllPVORW(void);
extern void   GetTimerValPVORW( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt);

extern void   TimerInitPWARN( Rte_Instance self);
extern void   TimerCountPWARN( Rte_Instance self);
extern void   TimerStopAllPWARN(void);
extern void   GetTimerValPWARN( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt);

extern void   TimerInitPWARNTOL( Rte_Instance self);
extern void   TimerCountPWARNTOL( Rte_Instance self);
extern void   TimerStopAllPWARNTOL(void);
extern void   GetTimerValPWARNTOL( uint8 ucZomPos, uint8* ucTimState, uint16* ushTimCnt);

#ifdef __cplusplus
}
#endif

