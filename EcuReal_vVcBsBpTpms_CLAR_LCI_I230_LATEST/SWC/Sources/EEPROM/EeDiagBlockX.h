#ifndef EeDiagBlockX_h
#define EeDiagBlockX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "Hs_InaktivereignisX.h"

#define cSizeInaktivereignis        ( (uint16) ( sizeof(ImpTypeArrayDcm_RdcHsInaktivereignisReadDataType)   / 3))
#define cSizeKalibrierereignis      ( (uint16) ( sizeof(ImpTypeArrayDcm_RdcHsKalibrierereignisReadDataType) / 3))
#define cSizeWarnereignis           ( (uint16) ( sizeof(ImpTypeArrayDcm_RdcHsWarnereignis1ReadDataType)))
#define cSizeWarnereignisWeich      ( (uint16) ( sizeof(ImpTypeArrayDcm_RdcHsWarnereignisWeich1ReadDataType)))
#define cSizeWarnereignisRuecknahme ( (uint16) ( sizeof(ImpTypeArrayDcm_RdcHsWarnereignisRuecknahmeReadDataType)))
#define cNvmRdciDiagBlock1HsWarn_1_Size         ( (uint16) (cSizeWarnereignis * sizeof(uint8)))
#define cNvmRdciDiagBlock1HsWeich_1_Size        ( (uint16) (cSizeWarnereignisWeich * sizeof(uint8)))
#define cNvmRdciDiagBlock1HsWRueck_Size         ( (uint16) (cSizeWarnereignisRuecknahme * sizeof(uint8)))
#define cPosStatKalibrierungWert                (uint16)  1
#define cPosStatZaehlerInaktivereignisWert      (uint16) 21
#define cPosStatZaehlerKalibrierereignisWert    (uint16) 49
#define cPosStatZaehlerWarnereignisWert         (uint16) 50
#define cPosStatZaehlerWarnereignisWeichWert    (uint16) 50
#define cPosStatZaehlerWRuecknahmeWert          (uint16) 50
#define cSAVE_ON_SHUTDOWN   FALSE
#define cSAVE_ON_EVENT      TRUE

typedef struct DiagNvmBlock_1{
   uint8                     ucInitialize;
   uint8                     ucWarnereignis1[cSizeWarnereignis];
   uint8                     ucWe1ZomSlot;
   uint8                     ucWarnereignis2[cSizeWarnereignis];
   uint8                     ucWe2ZomSlot;
   uint8                     ucWarnereignis3[cSizeWarnereignis];
   uint8                     ucWe3ZomSlot;
   uint8                     ucWarnereignisWeich1[cSizeWarnereignisWeich];
   uint8                     ucWarnereignisWeich2[cSizeWarnereignisWeich];
   uint8                     ucWarnereignisWeich3[cSizeWarnereignisWeich];
   uint8                     ucWarnereignisRueck[cSizeWarnereignisRuecknahme];
  Rdci_UHRZEIT_DATUM_Type   tExtParkSupSleepTimeDate;
  Rdci_UHRZEIT_DATUM_Type   tExtParkSupWakeupTimeDate;
}tDiagNvmBlock1Type;

typedef struct DiagNvmBlock_2{
   uint8                 ucInitialize;
   uint16                ushBandmodeState;
   uint8                 ucHsInaktiv_1[cSizeInaktivereignis];
   uint8                 ucHsInaktiv_2[cSizeInaktivereignis];
   uint8                 ucHsInaktiv_3[cSizeInaktivereignis];
   uint8                 ucHsKalib_1[cSizeKalibrierereignis];
   uint8                 ucHsKalib_2[cSizeKalibrierereignis];
   uint8                 ucHsKalib_3[cSizeKalibrierereignis];
   uint32                ulWumErrors;
   uint32                ulNwmErrors;
   strIeFiFo             IeFiFo_0;
   strIeFiFo             IeFiFo_1;
   strIeFiFo             IeFiFo_2;
   uint8                 ucCalRootCause;
   uint16                ushWSDefectCnt[4];
   uint8                 ucResEvCt[3];
}tDiagNvmBlock2Type;

extern void InitDiagBlock1EE(Rte_Instance self);
extern void InitDiagBlock2EE(Rte_Instance self);
extern void SetDiagBlock1UpdateFlagEE(void);
extern void SetDiagBlock2UpdateFlagEE(void);
extern void ClearDiagBlock1UpdateFlagEE(void);
extern void ClearDiagBlock2UpdateFlagEE(void);
extern boolean bGetDiagBlock1UpdateFlagEE(void);
extern boolean bGetDiagBlock2UpdateFlagEE(void);
extern uint8 GETucDiagBlock1InitializeEE(Rte_Instance self);
extern uint8 GETucDiagBlock2InitializeEE(Rte_Instance self);
extern void PUTucDiagBlock1InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern void PUTucDiagBlock2InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern uint16 GETushBandmodeStateEE(Rte_Instance self);
extern void PUTushBandmodeStateEE(Rte_Instance self, uint16 ushBandmodeState);
extern void PutHsInaktivereignis_1_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsInaktivereignis_2_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsInaktivereignis_3_EE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GetHsInaktivereignis_1_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsInaktivereignis_2_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsInaktivereignis_3_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsInaktivereignis_1_CounterEE(Rte_Instance self);
extern uint8 GetHsInaktivereignis_2_CounterEE(Rte_Instance self);
extern uint8 GetHsInaktivereignis_3_CounterEE(Rte_Instance self);
extern void PutIeFiFoToNvmEE(Rte_Instance self, const strIeFiFo* tFiFo);
extern void GetIeFiFoFromNvmEE(Rte_Instance self, strIeFiFo* tFiFo);
extern uint8 GetHsKalibrierereignis_1_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsKalibrierereignis_2_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsKalibrierereignis_3_EE(Rte_Instance self, uint8 i);
extern void PutHsKalibrierereignis_1_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsKalibrierereignis_2_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsKalibrierereignis_3_EE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GetHsKalibrierereignis_1_CounterEE(Rte_Instance self);
extern uint8 GetHsKalibrierereignis_2_CounterEE(Rte_Instance self);
extern uint8 GetHsKalibrierereignis_3_CounterEE(Rte_Instance self);
extern uint8 GetHsKalibrierereignis_1_RootCauseEE(Rte_Instance self);
extern uint8 GetHsWarnereignis_1_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsWarnereignis_2_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsWarnereignis_3_EE(Rte_Instance self, uint8 i);
extern void PutHsWarnereignis_1_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent);
extern void PutHsWarnereignis_2_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent);
extern void PutHsWarnereignis_3_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent);
extern uint8 GetHsWarnereignis_1_CounterEE(Rte_Instance self);
extern uint8 GetHsWarnereignis_2_CounterEE(Rte_Instance self);
extern uint8 GetHsWarnereignis_3_CounterEE(Rte_Instance self);
extern void PutWe1ZomSlotEE(Rte_Instance self, uint8 x);
extern void PutWe2ZomSlotEE(Rte_Instance self, uint8 x);
extern void PutWe3ZomSlotEE(Rte_Instance self, uint8 x);
extern uint8 GetWe1ZomSlotEE(Rte_Instance self);
extern uint8 GetWe2ZomSlotEE(Rte_Instance self);
extern uint8 GetWe3ZomSlotEE(Rte_Instance self);
extern uint8 GetHsWarnereignisWeich_1_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsWarnereignisWeich_2_EE(Rte_Instance self, uint8 i);
extern uint8 GetHsWarnereignisWeich_3_EE(Rte_Instance self, uint8 i);
extern void PutHsWarnereignisWeich_1_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsWarnereignisWeich_2_EE(Rte_Instance self, uint8 x, uint8 i);
extern void PutHsWarnereignisWeich_3_EE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GetHsWarnereignisWeich_1_CounterEE(Rte_Instance self);
extern uint8 GetHsWarnereignisWeich_2_CounterEE(Rte_Instance self);
extern uint8 GetHsWarnereignisWeich_3_CounterEE(Rte_Instance self);
extern uint8 GetHsWarnereignisRuecknahmeEE(Rte_Instance self, uint8 i);
extern void PutHsWarnereignisRuecknahmeEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GetHsWarnereignisRuecknahmeCounterEE(Rte_Instance self);
extern uint32 GETulWumErrorsEE(Rte_Instance self);
extern void PUTulWumErrorsEE(Rte_Instance self, uint32 ulValue);
extern uint32 GETulNwmErrorsEE(Rte_Instance self);
extern void PUTulNwmErrorsEE(Rte_Instance self, uint32 ulValue);
extern void PUTucCalibrationRootCauseEE(Rte_Instance self, uint8 x);
extern uint8 GETucCalibrationRootCauseEE(Rte_Instance self);
extern void PUTSensorDefectCounterToNvmMirrorEE(Rte_Instance self, uint16 ushVal, uint8 ucCol);
extern void GETSensorDefectCounterFromNvmMirrorEE(Rte_Instance self, uint16* pushVal, uint8 ucCol);
extern uint8 ucGetCodingDataChangeEventCounterEE(Rte_Instance self);
extern uint8 ucGetInitByHufEventCounterEE(Rte_Instance self);
extern uint8 ucGetInitByContiEventCounterEE(Rte_Instance self);
extern void IncCodingDataChangeEventCounterEE(Rte_Instance self);
extern void IncInitByHufEventCounterEE(Rte_Instance self);
extern void IncInitByContiEventCounterEE(Rte_Instance self);
extern Rdci_UHRZEIT_DATUM_Type GETtExtParkSupSleepTimeDateEE(Rte_Instance self);
extern void PUTtExtParkSupSleepTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x);
extern Rdci_UHRZEIT_DATUM_Type GETtExtParkSupWakeupTimeDateEE(Rte_Instance self);
extern void PUTtExtParkSupWakeupTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x);

#ifdef __cplusplus
}
#endif

#endif
