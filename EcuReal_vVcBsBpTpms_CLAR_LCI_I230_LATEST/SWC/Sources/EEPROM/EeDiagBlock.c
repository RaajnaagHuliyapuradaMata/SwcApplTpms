

#include "EeDiagBlock.h"
#include "HS_KalibrierereignisX.h"

static boolean bBlock1NeedsUpdate = FALSE;
static boolean bBlock2NeedsUpdate = FALSE;

void InitDiagBlock1EE(Rte_Instance self)
{
   uint8 ucLoop;
  Rdci_UHRZEIT_DATUM_Type tTimeDate = { 0, 0, 0, 0, 0, 0, 0, 0 };

   PUTucDiagBlock1InitializeEE(self, 0xff);

   for(ucLoop = 0; ucLoop < cNvmRdciDiagBlock1HsWarn_1_Size; ucLoop++){
    PutHsWarnereignis_1_EE(self, 0xffu, ucLoop, cSAVE_ON_EVENT);
    PutHsWarnereignis_2_EE(self, 0xffu, ucLoop, cSAVE_ON_EVENT);
    PutHsWarnereignis_3_EE(self, 0xffu, ucLoop, cSAVE_ON_EVENT);
   }

   PutWe1ZomSlotEE(self, 0xffu);
   PutWe2ZomSlotEE(self, 0xffu);
   PutWe3ZomSlotEE(self, 0xffu);

   for(ucLoop = 0; ucLoop < cNvmRdciDiagBlock1HsWeich_1_Size; ucLoop++){
    PutHsWarnereignisWeich_1_EE(self, 0xffu, ucLoop);
    PutHsWarnereignisWeich_2_EE(self, 0xffu, ucLoop);
    PutHsWarnereignisWeich_3_EE(self, 0xffu, ucLoop);
   }

   for(ucLoop = 0; ucLoop < cNvmRdciDiagBlock1HsWRueck_Size; ucLoop++){
    PutHsWarnereignisRuecknahmeEE(self, 0xffu, ucLoop);
   }

   PUTtExtParkSupSleepTimeDateEE(self, tTimeDate);
   PUTtExtParkSupWakeupTimeDateEE(self, tTimeDate);

   PUTucDiagBlock1InitializeEE(self, cNvmInitialized);
   bBlock1NeedsUpdate = TRUE;
}

void InitDiagBlock2EE(Rte_Instance self)
{
   uint8 ucLoop;

   PUTucDiagBlock2InitializeEE(self, 0xff);

   PUTushBandmodeStateEE(self, 0);

   for(ucLoop = 0; ucLoop < cSizeInaktivereignis; ucLoop++){
    PutHsInaktivereignis_1_EE(self, 0xffu, ucLoop);
    PutHsInaktivereignis_2_EE(self, 0xffu, ucLoop);
    PutHsInaktivereignis_3_EE(self, 0xffu, ucLoop);
   }

   for(ucLoop = 0; ucLoop < cSizeKalibrierereignis; ucLoop++){
    PutHsKalibrierereignis_1_EE(self, 0xffu, ucLoop);
    PutHsKalibrierereignis_2_EE(self, 0xffu, ucLoop);
    PutHsKalibrierereignis_3_EE(self, 0xffu, ucLoop);
   }

   PUTulWumErrorsEE(self, 0);
   PUTulNwmErrorsEE(self, 0);

  ClearIeFifoDS(self);

   PUTucCalibrationRootCauseEE(self, cCalVirgin);

   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[0] = 0;
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[1] = 0;
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[2] = 0;

   PUTucDiagBlock2InitializeEE(self, cNvmInitialized);
   bBlock2NeedsUpdate = TRUE;
}

uint8 GETucDiagBlock1InitializeEE(Rte_Instance self)
{
   return ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucInitialize;
}

void PUTucDiagBlock1InitializeEE(Rte_Instance self, uint8 ucNvmInitialize)
{
   ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucInitialize = ucNvmInitialize;
}

uint8 GETucDiagBlock2InitializeEE(Rte_Instance self)
{
   return ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucInitialize;
}

void PUTucDiagBlock2InitializeEE(Rte_Instance self, uint8 ucNvmInitialize)
{
   ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucInitialize = ucNvmInitialize;
}

uint16 GETushBandmodeStateEE(Rte_Instance self)
{
   uint16 ushState;

   ushState  = ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushBandmodeState;

   return ushState;
}

void PUTushBandmodeStateEE(Rte_Instance self, uint16 ushBandmodeState)
{
   if(ushBandmodeState != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushBandmodeState){
    SetDiagBlock2UpdateFlagEE();
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushBandmodeState = ushBandmodeState;
}

uint8 GetHsInaktivereignis_1_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_1[i]);
}

void PutHsInaktivereignis_1_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeInaktivereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_1[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_1[i] = (x);
   }
}

uint8 GetHsInaktivereignis_1_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_1[cPosStatZaehlerInaktivereignisWert]);
}

uint8 GetHsInaktivereignis_2_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_2[i]);
}

void PutHsInaktivereignis_2_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeInaktivereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_2[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_2[i] = (x);
   }
}

uint8 GetHsInaktivereignis_2_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_2[cPosStatZaehlerInaktivereignisWert]);
}

uint8 GetHsInaktivereignis_3_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_3[i]);
}

void PutHsInaktivereignis_3_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeInaktivereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_3[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_3[i] = (x);
   }
}

uint8 GetHsInaktivereignis_3_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsInaktiv_3[cPosStatZaehlerInaktivereignisWert]);
}

void GetIeFiFoFromNvmEE(Rte_Instance self, strIeFiFo* tFiFo)
{
   tFiFo[0].ucErrorNumber  =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucErrorNumber;
   tFiFo[0].ucIeSent       =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucIeSent;
   tFiFo[1].ucErrorNumber  =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucErrorNumber;
   tFiFo[1].ucIeSent       =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucIeSent;
   tFiFo[2].ucErrorNumber  =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucErrorNumber;
   tFiFo[2].ucIeSent       =  ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucIeSent;
}

void PutIeFiFoToNvmEE(Rte_Instance self, const strIeFiFo* tFiFo)
{
   boolean bUpdate = FALSE;

   if(tFiFo[0].ucErrorNumber != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucErrorNumber){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucErrorNumber = (tFiFo[0].ucErrorNumber);
   if(tFiFo[0].ucIeSent != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucIeSent){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_0.ucIeSent = (tFiFo[0].ucIeSent);

   if(tFiFo[1].ucErrorNumber != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucErrorNumber){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucErrorNumber = (tFiFo[1].ucErrorNumber);

   if(tFiFo[1].ucIeSent != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucIeSent){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_1.ucIeSent = (tFiFo[1].ucIeSent);

   if(tFiFo[2].ucErrorNumber != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucErrorNumber){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucErrorNumber = (tFiFo[2].ucErrorNumber);

   if(tFiFo[2].ucIeSent != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucIeSent){
    bUpdate = TRUE;
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->IeFiFo_2.ucIeSent = (tFiFo[2].ucIeSent);

   if(TRUE == bUpdate){
    SetDiagBlock2UpdateFlagEE();
   }
}

uint8 GetHsKalibrierereignis_1_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_1[i]);
}

void PutHsKalibrierereignis_1_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeKalibrierereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_1[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_1[i] = (x);
   }
}

uint8 GetHsKalibrierereignis_1_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_1[cPosStatZaehlerKalibrierereignisWert]);
}

uint8 GetHsKalibrierereignis_1_RootCauseEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_1[cPosStatKalibrierungWert]);
}

uint8 GetHsKalibrierereignis_2_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_2[i]);
}

void PutHsKalibrierereignis_2_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeKalibrierereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_2[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_2[i] = (x);
   }
}

uint8 GetHsKalibrierereignis_2_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_2[cPosStatZaehlerKalibrierereignisWert]);
}

uint8 GetHsKalibrierereignis_3_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_3[i]);
}

void PutHsKalibrierereignis_3_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeKalibrierereignis){
      if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_3[i]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_3[i] = (x);
   }
}

uint8 GetHsKalibrierereignis_3_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucHsKalib_3[cPosStatZaehlerKalibrierereignisWert]);
}

uint8 GetHsWarnereignis_1_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis1[cPosStatZaehlerWarnereignisWert]);
}

uint8 GetHsWarnereignis_1_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis1[i]);
}

void PutHsWarnereignis_1_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent)
{
   if(i < cSizeWarnereignis){
      if(bSaveOnEvent == TRUE){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis1[i] = (x);
   }
}

uint8 GetWe1ZomSlotEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe1ZomSlot);
}

void PutWe1ZomSlotEE(Rte_Instance self, uint8 x)
{
   ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe1ZomSlot = (x);
}

uint8 GetHsWarnereignis_2_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis2[cPosStatZaehlerWarnereignisWert]);
}

uint8 GetHsWarnereignis_2_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis2[i]);
}

void PutHsWarnereignis_2_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent)
{
   if(i < cSizeWarnereignis){
      if(bSaveOnEvent == TRUE){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis2[i] = (x);
   }
}

uint8 GetWe2ZomSlotEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe2ZomSlot);
}

void PutWe2ZomSlotEE(Rte_Instance self, uint8 x)
{
   ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe2ZomSlot = (x);
}

uint8 GetHsWarnereignis_3_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis3[cPosStatZaehlerWarnereignisWert]);
}

uint8 GetHsWarnereignis_3_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis3[i]);
}

void PutHsWarnereignis_3_EE(Rte_Instance self, uint8 x, uint8 i, boolean bSaveOnEvent)
{
   if(i < cSizeWarnereignis){
      if(bSaveOnEvent == TRUE){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignis3[i] = (x);
   }
}

uint8 GetWe3ZomSlotEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe3ZomSlot);
}

void PutWe3ZomSlotEE(Rte_Instance self, uint8 x)
{
   ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWe3ZomSlot = (x);
}

uint8 GetHsWarnereignisWeich_1_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich1[cPosStatZaehlerWarnereignisWeichWert]);
}

uint8 GetHsWarnereignisWeich_1_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich1[i]);
}

void PutHsWarnereignisWeich_1_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeWarnereignisWeich){
      if(x != ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich1[i]){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich1[i] = (x);
   }
}

uint8 GetHsWarnereignisWeich_2_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich2[cPosStatZaehlerWarnereignisWeichWert]);
}

uint8 GetHsWarnereignisWeich_2_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich2[i]);
}

void PutHsWarnereignisWeich_2_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeWarnereignisWeich){
      if(x != ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich2[i]){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich2[i] = (x);
   }
}

uint8 GetHsWarnereignisWeich_3_CounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich3[cPosStatZaehlerWarnereignisWeichWert]);
}

uint8 GetHsWarnereignisWeich_3_EE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich3[i]);
}

void PutHsWarnereignisWeich_3_EE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeWarnereignisWeich){
      if(x != ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich3[i]){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisWeich3[i] = (x);
   }
}

uint8 GetHsWarnereignisRuecknahmeEE(Rte_Instance self, uint8 i)
{
   return( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisRueck[i]);
}

void PutHsWarnereignisRuecknahmeEE(Rte_Instance self, uint8 x, uint8 i)
{
   if(i < cSizeWarnereignisRuecknahme){
      if(x != ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisRueck[i]){
      SetDiagBlock1UpdateFlagEE();
      }
    ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisRueck[i] = (x);
   }
}

uint8 GetHsWarnereignisRuecknahmeCounterEE(Rte_Instance self)
{
   return ( ((tDiagNvmBlock1Type*) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->ucWarnereignisRueck[cPosStatZaehlerWRuecknahmeWert]);
}

Rdci_UHRZEIT_DATUM_Type GETtExtParkSupSleepTimeDateEE(Rte_Instance self)
{
  Rdci_UHRZEIT_DATUM_Type cUhrzeitDatumInitVal = { 0, 0, 0, 0, 0, 0, 0, 0 };
   uint8 ucStDispCtiDate;

   ucStDispCtiDate = ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupSleepTimeDate.ST_DISP_CTI_DATE;
   if(((ucStDispCtiDate & 0x01) == 0) || (ucStDispCtiDate == 0x0f)){
      return( cUhrzeitDatumInitVal);
   }
   else{
      return( ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupSleepTimeDate);
   }
}

void PUTtExtParkSupSleepTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x)
{
   ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupSleepTimeDate = (x);
}

Rdci_UHRZEIT_DATUM_Type GETtExtParkSupWakeupTimeDateEE(Rte_Instance self)
{
  Rdci_UHRZEIT_DATUM_Type cUhrzeitDatumInitVal = { 0, 0, 0, 0, 0, 0, 0, 0 };
   uint8 ucStDispCtiDate;

   ucStDispCtiDate = ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupWakeupTimeDate.ST_DISP_CTI_DATE;
   if(((ucStDispCtiDate & 0x01) == 0) || (ucStDispCtiDate == 0x0f)){
      return( cUhrzeitDatumInitVal);
   }
   else{
      return( ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupWakeupTimeDate);
   }
}

void PUTtExtParkSupWakeupTimeDateEE(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type x)
{
   ((tDiagNvmBlock1Type *) (void*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self)->Data)->tExtParkSupWakeupTimeDate = (x);
}

uint8 GETucCalibrationRootCauseEE(Rte_Instance self)
{
   return( ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucCalRootCause);
}

void PUTucCalibrationRootCauseEE(Rte_Instance self, uint8 x)
{
   if(x != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucCalRootCause){
    SetDiagBlock2UpdateFlagEE();
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucCalRootCause = (x);
}

uint32 GETulWumErrorsEE(Rte_Instance self)
{
   uint32 l_ulWumErrors;

  l_ulWumErrors  = ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulWumErrors;

   return l_ulWumErrors;
}

void PUTulWumErrorsEE(Rte_Instance self, uint32 ulValue)
{
   if(ulValue != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulWumErrors){
    SetDiagBlock2UpdateFlagEE();
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulWumErrors = ulValue;
}

uint32 GETulNwmErrorsEE(Rte_Instance self)
{
   uint32 l_ulNwmErrors;

  l_ulNwmErrors  = ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulNwmErrors;

   return l_ulNwmErrors;
}

void PUTulNwmErrorsEE(Rte_Instance self, uint32 ulValue)
{
   if(ulValue != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulNwmErrors){
    SetDiagBlock2UpdateFlagEE();
   }
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ulNwmErrors = ulValue;
}

void PUTSensorDefectCounterToNvmMirrorEE(Rte_Instance self, uint16 ushVal, uint8 ucCol)
{
   if(ucCol < 4){
      if(ushVal != ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushWSDefectCnt[ucCol]){
      SetDiagBlock2UpdateFlagEE();
      }
    ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushWSDefectCnt[ucCol] = ushVal;
   }
}

void GETSensorDefectCounterFromNvmMirrorEE(Rte_Instance self, uint16* pushVal, uint8 ucCol)
{
  *pushVal = ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ushWSDefectCnt[ucCol];
}

void SetDiagBlock1UpdateFlagEE(void)
{
   bBlock1NeedsUpdate = TRUE;
}

void SetDiagBlock2UpdateFlagEE(void)
{
   bBlock2NeedsUpdate = TRUE;
}

void ClearDiagBlock1UpdateFlagEE(void)
{
   bBlock1NeedsUpdate = FALSE;
}

void ClearDiagBlock2UpdateFlagEE(void)
{
   bBlock2NeedsUpdate = FALSE;
}

boolean bGetDiagBlock1UpdateFlagEE(void)
{
   return bBlock1NeedsUpdate;
}

boolean bGetDiagBlock2UpdateFlagEE(void)
{
   return bBlock2NeedsUpdate;
}

uint8 ucGetInitByContiEventCounterEE(Rte_Instance self)
{
   return ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[0];
}

uint8 ucGetInitByHufEventCounterEE(Rte_Instance self)
{
   return ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[1];
}

uint8 ucGetCodingDataChangeEventCounterEE(Rte_Instance self)
{
   return ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[2];
}

void IncInitByContiEventCounterEE(Rte_Instance self)
{
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[0]++;
   bBlock2NeedsUpdate = TRUE;
}

void IncInitByHufEventCounterEE(Rte_Instance self)
{
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[1]++;
   bBlock2NeedsUpdate = TRUE;
}

void IncCodingDataChangeEventCounterEE(Rte_Instance self)
{
   ((tDiagNvmBlock2Type*) (void*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self)->Data)->ucResEvCt[2]++;
   bBlock2NeedsUpdate = TRUE;
}

