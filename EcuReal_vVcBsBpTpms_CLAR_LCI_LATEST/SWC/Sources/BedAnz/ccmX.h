#ifndef ccmX_h
#define ccmX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cCcInactive              ( (uint16) 0x0095u)
#define cCcExternalInterference  ( (uint16) 0x0090u)
#define cCcFlatTireFL            ( (uint16) 0x008Bu)
#define cCcFlatTireFR            ( (uint16) 0x008Fu)
#define cCcFlatTireRL            ( (uint16) 0x008Du)
#define cCcFlatTireRR            ( (uint16) 0x008Cu)
#define cCcFlatTire              ( (uint16) 0x0093u)
#define cCcFlatTireFL_RSC        ( (uint16) 0x07EEu)
#define cCcFlatTireFR_RSC        ( (uint16) 0x07EFu)
#define cCcFlatTireRL_RSC        ( (uint16) 0x07ECu)
#define cCcFlatTireRR_RSC        ( (uint16) 0x07EDu)
#define cCcFlatTire_RSC          ( (uint16) 0x07EBu)
#define cCcFlatTireFL_NoRSC      ( (uint16) 0x0866u)
#define cCcFlatTireFR_NoRSC      ( (uint16) 0x0867u)
#define cCcFlatTireRL_NoRSC      ( (uint16) 0x0864u)
#define cCcFlatTireRR_NoRSC      ( (uint16) 0x0865u)
#define cCcFlatTire_NoRSC        ( (uint16) 0x0863u)
#define cCcAutoSelFailed         ( (uint16) 0x0890u)
#define cCcBefuellhinweis        ( (uint16) 0x03BBu)
#define cCcPlausiCheck           ( (uint16) 0x03BCu)
#define cCcDruckwarnung          ( (uint16) 0x03BDu)
#define cCcLernphase             ( (uint16) 0x0147u)
#define cCcReifenwechsel         ( (uint16) 0x008Eu)
#define cCcFixLamp               ( (uint16) 0x0150u)
#define cCcSpeedCcm2158          ( (uint16) 0x086Eu)
#define cCcSpeedCcm2159          ( (uint16) 0x086Fu)
#define cCcInvalid               ( (uint16) 0xFFFFu)
#define cCcIX_Inactive              ( (uint8)  0u)
#define cCcIX_ExternalInterference  ( (uint8)  1u)
#define cCcIX_FlatTireFL            ( (uint8)  2u)
#define cCcIX_FlatTireFR            ( (uint8)  3u)
#define cCcIX_FlatTireRL            ( (uint8)  4u)
#define cCcIX_FlatTireRR            ( (uint8)  5u)
#define cCcIX_FlatTire              ( (uint8)  6u)
#define cCcIX_FlatTireFL_RSC        ( (uint8)  7u)
#define cCcIX_FlatTireFR_RSC        ( (uint8)  8u)
#define cCcIX_FlatTireRL_RSC        ( (uint8)  9u)
#define cCcIX_FlatTireRR_RSC        ( (uint8) 10u)
#define cCcIX_FlatTire_RSC          ( (uint8) 11u)
#define cCcIX_FlatTireFL_NoRSC      ( (uint8) 12u)
#define cCcIX_FlatTireFR_NoRSC      ( (uint8) 13u)
#define cCcIX_FlatTireRL_NoRSC      ( (uint8) 14u)
#define cCcIX_FlatTireRR_NoRSC      ( (uint8) 15u)
#define cCcIX_FlatTire_NoRSC        ( (uint8) 16u)
#define cCcIX_Druckwarnung          ( (uint8) 17u)
#define cCcIX_Befuellhinweis        ( (uint8) 18u)
#define cCcIX_Reifenwechsel         ( (uint8) 19u)
#define cCcIX_PlausiCheck           ( (uint8) 20u)
#define cCcIX_Lernphase             ( (uint8) 21u)
#define cCcIX_AutoSelFailed         ( (uint8) 22u)
#define cCcIX_SpeedCcm2158          ( (uint8) 23u)
#define cCcIX_SpeedCcm2159          ( (uint8) 24u)
#define cCcIX_Invalid               ( (uint8) 25u)
#define cCcIX_NumberOfMessages      ( (uint8) 26u)

typedef struct{
  uint16 ushCcNumber;
  uint8  ucCcFixLampControl;
}tCcStructDecl;

extern void   InitCCM(void);
extern void   MainFunctionCCM(Rte_Instance self);
extern void   StartCycleCCM(void);
extern void   StopCycleCCM(void);
extern uint8 ucFillVklDataCCM( uint8 ucIx, uint16* pushCcmId, uint8* pucCcmStartStop, uint8* pucCcmBlinking, uint8* pucTransCycle);
extern uint8 ucFillFklDataCCM( uint16* pushCcmId, uint8* pucCcmStartStop, uint8* pucCcmBlinking, uint8* pucTransCycle);
extern void SetVklStartedCCM( uint8 ucIx, boolean bOkFlag);
extern void SetVklStopedCCM( uint8 ucIx, boolean bOkFlag);
extern void SetFklStartedCCM( boolean bOkFlag);
extern void SetFklStopedCCM( boolean bOkFlag);
extern uint32 ulGetStartStateOfVklCCM(void);
extern uint32 ulGetStopStateOfVklCCM(void);
extern uint32 ulGetStartedStateOfVklCCM(void);
extern void RestartMessagesCCM(void);
extern void RestartBlinkingCCM(void);
extern uint8 ucGetNokCounterCCM(void);
extern uint16 ushGetCcNumberOfIxCCM(uint8 ucIx);

#ifdef __cplusplus
}
#endif

#endif
