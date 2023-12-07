#include "RdcTsaServices.h"
#include "RID_X.h"
#include "EeRidQrBlockX.h"
#include "EeErfsBlockX.h"
#include "EeErfsTsaBlockX.h"
#include "EeCommonBlockX.h"
#include "wallocX.h"
#include "DataManagerX.h"
#include "State_bzX.h"

#ifndef TESSY
  #ifdef WIN32
    #include "assert.h"
  #endif
#endif

#define cMaxTyreElements                ((uint8)12)
#define cMountedTyreElements            ((uint8)4)
#define cUnmountedTyreElements          ((uint8)8)
#define cQRCodeDataSize                 ((uint8)30)
#define cRuntimeDataSize                ((uint8)25)
#define cTyreUnmountedFlag              ((uint8)0x5A)

static boolean UpdateTyreQrCodeDataInNvRam;

void GetRdcRidAktReifenQRCodeLesenDS(Rte_Instance self, uint8* paucData)
{
   uint8 QrIx,j,index, ucHelp;
   uint8 ucOffset, ucPrev, ucCur;

  #ifndef TESSY
    #ifdef WIN32

      assert(sizeof(ImpTypeArrayDcm_RdcRidAktReifenQrCodeLesenReadDataType) == (cMountedTyreElements * cQRCodeDataSize));
    #endif
  #endif

   index = 0x00;

   for(j = 0; j < (uint8) (cMountedTyreElements * cQRCodeDataSize) ; j++){
    paucData[j] = 0x00;
   }

   for(QrIx = 0; QrIx < cMaxQRCodeSets; QrIx++){
      if((GETTyreMountedFlagEE(self, QrIx) & 0x0F) == cTyreMountedFlag){

      paucData[index] = (QrIx+1);
      index++;

      for(j=0; j<cTyreOEMSize;j++){

        ucOffset = (uint8)(2-(j/4));
        ucOffset += j;

        ucPrev = GETTyreOEMQrCodeDataEE(self, QrIx, (ucOffset - 1));
        ucCur = GETTyreOEMQrCodeDataEE(self, QrIx, (ucOffset));

        paucData[index] = GetOemIdDS(ucPrev, ucCur, j);
        index++;
      }

      paucData[index] = ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x0F) << 2);
      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 2) & 0xC0) >> 6);
      index++;

      for(j=0; j<cTyreDOTSize;j++){
        paucData[index] = GETTyreDOTQrCodeDataEE(self, QrIx, j);
        index++;
      }

      for(j=0; j<cTyreDimSize;j++){
        paucData[index] = GETTyreDimQrCodeDataEE(self, QrIx, j);
        index++;
      }

      paucData[index] = ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x10) << 2);

      paucData[index] |= (GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x20);

      paucData[index] |= ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x40) >> 2);

      paucData[index] |= (GETTyreOEMQrCodeDataEE(self, QrIx, 10) & 0x08);

      paucData[index] |= ((GETTyreOEMQrCodeDataEE(self, QrIx, 0) & 0x03) << 1);
      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x80) >> 7);
      index++;

      ucHelp = (GETTyreMountedFlagEE(self, QrIx) & (uint8)0xF0);
      for(j=0; j<cAnzRad;j++){
          if((ucHelp & (uint8)(0x10<<j)) != 0x00){
          ucHelp = j;
        }
      }
      paucData[index] = ucHelp;
      index++;

      paucData[index] = 0x01;

      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 0) & 0xFC) >> 1);
      index++;
      }
   }
}

void GetRdcRidAlteReifenQRCodeLesenDS(Rte_Instance self, uint8* paucData)
{
   uint8 QrIx,j,index,OlIx, ucOffset, ucPrev, ucCur;
   uint8 LatestUnmountEntryIx[8] = {cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets};

   index = 0x00;

   for(j = 0; j < (uint8) (cUnmountedTyreElements * cQRCodeDataSize) ; j++){
    paucData[j] = 0x00;
   }

  GetLatestUnmountedQrDataEntries(self, &LatestUnmountEntryIx[0]);

   for(OlIx=0; OlIx<8;OlIx++){
    QrIx = LatestUnmountEntryIx[OlIx];

      if(QrIx != cMaxQRCodeSets){

      paucData[index] = (QrIx+1);
      index++;

      for(j=0; j<cTyreOEMSize;j++){

        ucOffset = (uint8)(2-(j/4));
        ucOffset += j;

        ucPrev = GETTyreOEMQrCodeDataEE(self, QrIx, (ucOffset - 1));
        ucCur = GETTyreOEMQrCodeDataEE(self, QrIx, (ucOffset));

        paucData[index] = GetOemIdDS(ucPrev, ucCur, j);
        index++;
      }

      paucData[index] = ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x0F) << 2);
      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 2) & 0xC0) >> 6);
      index++;

      for(j=0; j<cTyreDOTSize;j++){
        paucData[index] = GETTyreDOTQrCodeDataEE(self, QrIx, j);
        index++;
      }

      for(j=0; j<cTyreDimSize;j++){
        paucData[index] = GETTyreDimQrCodeDataEE(self, QrIx, j);
        index++;
      }

      paucData[index] = ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x10) << 2);

      paucData[index] |= (GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x20);

      paucData[index] |= ((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x40) >> 2);

      paucData[index] |= (GETTyreOEMQrCodeDataEE(self, QrIx, 10) & 0x08);

      paucData[index] |= ((GETTyreOEMQrCodeDataEE(self, QrIx, 0) & 0x03) << 1);
      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 1) & 0x80) >> 7);
      index++;

      paucData[index] = 0x05;
      index++;

      paucData[index] = 0;

      paucData[index] |= (uint8)((GETTyreOEMQrCodeDataEE(self, QrIx, 0) & 0xFC) >> 1);
      index++;
      }
   }
}

 uint8 GetOemIdDS(uint8 ucPrev, uint8 ucCur, uint8 IdIx)
 {
   uint8 uc8BitId;

   IdIx++;

      switch(IdIx){
      case (uint8)1:
      case (uint8)5:
      case (uint8)9:
        {
          uc8BitId = (ucCur & 0x3F);
          break;
        }
      case (uint8)2:
      case (uint8)6:
      case (uint8)10:
        {
          uc8BitId = (uint8)((ucCur & 0xFC) >> 2);
          break;
        }
      case (uint8)3:
      case (uint8)7:
      case (uint8)11:
        {
          uc8BitId = (uint8)((ucPrev & 0x03) << 4);
          uc8BitId |= (uint8)((ucCur & 0xF0) >> 4);
          break;
        }
      case (uint8)4:
      case (uint8)8:
        {
          uc8BitId = (uint8)((ucPrev & 0x0F) << 2);
          uc8BitId |= (uint8)((ucCur & 0xC0) >> 6);
          break;
        }
      default:
        {
          break;
        }
      }
    return(uc8BitId + 0x20);
 }

void GetRdcRidAktReifenLaufstreckeLesenDS(Rte_Instance self, uint8* paucData)
{
   uint8 i, QrIx, index;
  Rdci_MILE_KM_Type CurMileKm, SavMileKm;

   index = 0x00;

   for(i = 0; i < (uint8)(cMountedTyreElements*cRuntimeDataSize) ; i++){
    paucData[i] = 0x00;
   }

   for(QrIx = 0; QrIx < cMaxQRCodeSets; QrIx++){

    CurMileKm = GETulMileKmEE(self);

      if((GETTyreMountedFlagEE(self, QrIx) & 0x0F) == cTyreMountedFlag){
      paucData[index] = (QrIx+1);
      index++;

      for(i = 0; i < 6; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cMountedDateIx + i);
        index++;
      }

      for(i = 0; i < 4; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + i);
        index++;
      }

      for(i = 0; i < 6; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cUnmountedDateIx + i);
        index++;
      }

      for(i = 0; i < 4; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cUnmountedKmIx + i);
        index++;
      }

      SavMileKm = ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + 0) << 24);
      SavMileKm |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + 1) << 16);
      SavMileKm |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + 2) << 8);
      SavMileKm |= GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + 3);

      if(CurMileKm >= SavMileKm){

        CurMileKm = (CurMileKm - SavMileKm);

        SavMileKm = ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cRuntimeKmIx + 0) << 24);
        SavMileKm |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cRuntimeKmIx + 1) << 16);
        SavMileKm |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, QrIx, cRuntimeKmIx + 2) << 8);
        SavMileKm |= GETTyreRuntimeDataEE(self, QrIx, cRuntimeKmIx + 3);

        SavMileKm += CurMileKm;

        for(i = 0; i < 4; i++){
          paucData[index] = (uint8)(SavMileKm >> (8*(3-i)));
          index++;
        }
      }
      else{

        for(i = 0; i < 4; i++){
          paucData[index] = 0xFF;
          index++;
        }
      }
      }
   }
}

void GetRdcRidAlteReifenLaufstreckeLesenDS(Rte_Instance self, uint8* paucData)
{
   uint8 i, QrIx, index, OlIx;
   uint8 LatestUnmountEntryIx[8] = {cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets};

   index = 0x00;

   for(i = 0; i < (uint8)(cUnmountedTyreElements*cRuntimeDataSize) ; i++){
    paucData[i] = 0x00;
   }
  GetLatestUnmountedQrDataEntries(self, &LatestUnmountEntryIx[0]);

   for(OlIx=0; OlIx<8;OlIx++){
    QrIx = LatestUnmountEntryIx[OlIx];

      if(QrIx != cMaxQRCodeSets){
      paucData[index] = (QrIx+1);
      index++;

      for(i = 0; i < 6; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cMountedDateIx + i);
        index++;
      }

      for(i = 0; i < 4; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cMountedKmIx + i);
        index++;
      }

      for(i = 0; i < 6; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cUnmountedDateIx + i);
        index++;
      }

      for(i = 0; i < 4; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cUnmountedKmIx + i);
        index++;
      }

      for(i = 0; i < 4; i++){
        paucData[index] = GETTyreRuntimeDataEE(self, QrIx, cRuntimeKmIx + i);
        index++;
      }
      }
   }
}

void SaveCompleteQrCodeDataDS(Rte_Instance self)
{
   uint8 HisIx,i,CompVal1, QrIx, HelpPos, ChangePos = 0x00;
   uint8 OldMountIx[4] = {cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets,cMaxQRCodeSets};
   uint8 EntryIx = cMaxQRCodeSets;
   uint8 OemDataAvl, RidDotDataAvl;

   if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE){
    OemDataAvl = SaveOemDataRID();
    RidDotDataAvl = GetRidManAutoFLagRID();

      for(HisIx = 0;HisIx < cAnzRad; HisIx++){
      HelpPos = ucGetWPOfColWAL(HisIx);

      if(HelpPos < cMaxLR){

        for(QrIx=0;QrIx<cMaxQRCodeSets;QrIx++){
          CompVal1 = GETTyreMountedFlagEE(self, QrIx);

          if((CompVal1 & 0x0F) == cTyreMountedFlag){
            if((CompVal1 & (uint8)(0x10 << HelpPos)) == (uint8)(0x10 << HelpPos)){
              OldMountIx[HelpPos] = QrIx;
            }
          }
        }

          if(((RidDotDataAvl & (uint8)(0x01 << HisIx)) == (uint8)(0x01 << HisIx)) && ((OemDataAvl & (uint8)(0x11 << HisIx)) == (uint8)(0x11 << HisIx))){
          EntryIx = CompareTyreSerNumRID(self, HisIx);

          if((OldMountIx[HelpPos] < cMaxQRCodeSets) && (OldMountIx[HelpPos] != EntryIx)){
             PUTTyreMountedFlagEE(self, OldMountIx[HelpPos], cTyreUnmountedFlag);

             ChangePos |= (0x08 >> HelpPos);

             PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Reifenwechseln_erkannt, ChangePos);
          }

          for(QrIx=0;QrIx<cMaxQRCodeSets;QrIx++){
            CompVal1 = GETTyreDimQrCodeDataEE(self, QrIx, 0);

            if((CompVal1 == 0x00) || (CompVal1 == 0xFF)){
              if(EntryIx == cMaxQRCodeSets){
                EntryIx = QrIx;
              }
            }
          }

          if(EntryIx == cMaxQRCodeSets){
             SearchOldestUnmountEntryIndex(self, &EntryIx, &OldMountIx[0]);
          }

          for(i=0;i<cTyreDimSize;i++){
            PUTTyreDimQrCodeDataEE(self, EntryIx, i, GETTyreDimDataEE(self,HisIx,i));
          }
          for(i=0;i<cTyreDOTSize;i++){
            PUTTyreDOTQrCodeDataEE(self, EntryIx, i, GETTyreDOTDataEE(self,HisIx,i));
          }
          for(i=0;i<cTyreOEMSize;i++){
            PUTTyreOEMQrCodeDataEE(self, EntryIx, i, GetTyreOEMDataRID(HisIx,i));
          }

          PUTTyreMountedFlagEE(self, EntryIx, (cTyreMountedFlag | (uint8) (0x10 << HelpPos)));
        }
      }
      }
    SetTyreRuntimeDataDS(self, &OldMountIx[0]);
   }
}

static uint8 CompareTyreSerNumRID(Rte_Instance self, uint8 HisIx)
{
   uint8 Ix,i,j,ucMask, ucCmp1,ucCmp2;

  Ix = cMaxQRCodeSets;

  CheckDefaultSerNumAndReplaceRID(HisIx);

   for(i = 0; i < cMaxQRCodeSets; i++){
      if(Ix == cMaxQRCodeSets){
      Ix = i;

      for(j = 2; j < cTyreOEMSize; j++){

          if(j == 2){
          ucMask = 0x3F;
        }
        else if(j == (cTyreOEMSize - 1)){
          ucMask = 0xF0;
        }
        else{
          ucMask = 0xFF;
        }

        ucCmp1 = (GETTyreOEMQrCodeDataEE(self, i, j) & ucMask);
        ucCmp2 = (GetTyreOEMDataRID(HisIx,j) & ucMask);

          if(ucCmp1 != ucCmp2){
           Ix = cMaxQRCodeSets;
        }
      }
      }
   }

   return(Ix);
}

static void SearchOldestUnmountEntryIndex(Rte_Instance self, uint8* pEntryIx, const uint8* OldMountIx)
{
   uint8 QrIx,i,j,SmallestUmmountedKm[4],ucHelp[cDateSize] = {0x00,0x00,0x00,0x00,0x00,0x00};
   boolean bStopComp;

   for(QrIx=0;QrIx<cMaxQRCodeSets;QrIx++){
    bStopComp = FALSE;

      for(i=0; i< cAnzRad; i++){
      if(OldMountIx[i] == QrIx){
        bStopComp = TRUE;
      }
      }

      if(FALSE == bStopComp){
      if(GETTyreMountedFlagEE(self, QrIx) == cTyreUnmountedFlag){

          if(*pEntryIx == cMaxQRCodeSets){
          *pEntryIx = QrIx;

          for(i=0;i<cKmSize;i++){
            SmallestUmmountedKm[i] = GETTyreRuntimeDataEE(self, *pEntryIx, cUnmountedKmIx + i);
          }
        }
        else{

          bStopComp = FALSE;

          for(i=0;i<cKmSize;i++){
            if(bStopComp == FALSE){
              if(SmallestUmmountedKm[i] > GETTyreRuntimeDataEE(self, QrIx, cUnmountedKmIx + i)){

                *pEntryIx = QrIx;

                for(j=0;j<cKmSize;j++){
                  SmallestUmmountedKm[j] = GETTyreRuntimeDataEE(self, *pEntryIx, cUnmountedKmIx + j);
                }
                bStopComp = TRUE;
              }
              else{
                if(SmallestUmmountedKm[i] < GETTyreRuntimeDataEE(self, QrIx, cUnmountedKmIx + i)){
                  bStopComp = TRUE;
                }
              }
            }
          }
        }
      }
      }
   }

   SaveRuntimeDataInEE(self, *pEntryIx, cUnmountedKmIx, &ucHelp[0], cKmSize);
   SaveRuntimeDataInEE(self, *pEntryIx, cRuntimeKmIx, &ucHelp[0], cKmSize);
   SaveRuntimeDataInEE(self, *pEntryIx, cUnmountedDateIx, &ucHelp[0], cDateSize);
}

static void SetTyreRuntimeDataDS(Rte_Instance self, const uint8* OldMountIx)
{
   uint8 i,j,Ix;
   boolean bFound = FALSE;
  Rdci_UHRZEIT_DATUM_Type timeDate;
  Rdci_MILE_KM_Type mileKm;
   uint8 cTempBuffer[9], ucDataBuffer[6];
  Rdci_MILE_KM_Type MountKM, UnmountKM, RunKM, DiffKM;

   timeDate = GETtTimeDateEE(self);
  GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));

  mileKm = GETulMileKmEE(self);

   for(j=0;j<cAnzRad;j++){
    Ix = OldMountIx[j];

      if(Ix < cMaxQRCodeSets){
      if(GETTyreMountedFlagEE(self, Ix) == cTyreUnmountedFlag){

        ucDataBuffer[0] = cTempBuffer[6];
        ucDataBuffer[1] = cTempBuffer[7];
        ucDataBuffer[2] = cTempBuffer[3];
        ucDataBuffer[3] = cTempBuffer[4];
        ucDataBuffer[4] = cTempBuffer[0];
        ucDataBuffer[5] = cTempBuffer[1];
        SaveRuntimeDataInEE(self, Ix, cUnmountedDateIx, &ucDataBuffer[0], cDateSize);

        ucDataBuffer[0] = (uint8)((mileKm >> 24) & 0xffU);
        ucDataBuffer[1] = (uint8)((mileKm >> 16) & 0xffU);
        ucDataBuffer[2] = (uint8)((mileKm >> 8) & 0xffU);
        ucDataBuffer[3] = (uint8)(mileKm & 0xffU);
        SaveRuntimeDataInEE(self, Ix, cUnmountedKmIx, &ucDataBuffer[0], cKmSize);

        MountKM = ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cMountedKmIx)) << 24);
        MountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cMountedKmIx+1)) << 16);
        MountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cMountedKmIx+2)) << 8);
        MountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cMountedKmIx+3)));

        UnmountKM = ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cUnmountedKmIx)) << 24);
        UnmountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cUnmountedKmIx+1)) << 16);
        UnmountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cUnmountedKmIx+2)) << 8);
        UnmountKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cUnmountedKmIx+3)));

        RunKM = ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cRuntimeKmIx)) << 24);
        RunKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cRuntimeKmIx+1)) << 16);
        RunKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cRuntimeKmIx+2)) << 8);
        RunKM |= ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, Ix, (cRuntimeKmIx+3)));

          if(UnmountKM > MountKM){
          DiffKM = UnmountKM - MountKM;
        }
        else{
          DiffKM = 0x00;
        }

        RunKM += DiffKM;

        ucDataBuffer[0] = (uint8)((RunKM >> 24) & 0xffU);
        ucDataBuffer[1] = (uint8)((RunKM >> 16) & 0xffU);
        ucDataBuffer[2] = (uint8)((RunKM >> 8) & 0xffU);
        ucDataBuffer[3] = (uint8)(RunKM & 0xffU);
        SaveRuntimeDataInEE(self, Ix, cRuntimeKmIx, &ucDataBuffer[0], cKmSize);
      }
      }
   }

   for(j=0;j<cMaxQRCodeSets;j++){
    bFound = FALSE;

      if((GETTyreMountedFlagEE(self, j) & 0x0F) == cTyreMountedFlag){
      for(i=0;i<cAnzRad;i++){
          if(j == OldMountIx[i]){
          bFound = TRUE;
        }
      }
      }
      else{
      bFound = TRUE;
      }

      if(bFound == FALSE){

      ucDataBuffer[0] = cTempBuffer[6];
      ucDataBuffer[1] = cTempBuffer[7];
      ucDataBuffer[2] = cTempBuffer[3];
      ucDataBuffer[3] = cTempBuffer[4];
      ucDataBuffer[4] = cTempBuffer[0];
      ucDataBuffer[5] = cTempBuffer[1];
      SaveRuntimeDataInEE(self, j, cMountedDateIx, &ucDataBuffer[0], cDateSize);

      ucDataBuffer[0] = (uint8)((mileKm >> 24) & 0xffU);
      ucDataBuffer[1] = (uint8)((mileKm >> 16) & 0xffU);
      ucDataBuffer[2] = (uint8)((mileKm >> 8) & 0xffU);
      ucDataBuffer[3] = (uint8)(mileKm & 0xffU);
      SaveRuntimeDataInEE(self, j, cMountedKmIx, &ucDataBuffer[0], cKmSize);
      }
   }
}

static void SaveRuntimeDataInEE(Rte_Instance self, const uint8 Ix, const uint8 StartIx, const uint8* Buffer, const uint8 Size)
{
   uint8 i;

   for(i=0; i<Size;i++){
    PUTTyreRuntimeDataEE(self, Ix,(StartIx+i),Buffer[i]);
   }
}

void SetUpdateTyreQrCodeDataInNvRam(boolean bVal)
{
  UpdateTyreQrCodeDataInNvRam = bVal;
}

boolean GetUpdateTyreQrCodeDataInNvRamDM(void)
{
   return (UpdateTyreQrCodeDataInNvRam);
}

void SaveTsaDataDS(Rte_Instance self, const uint8* pucData)
{
   uint8 i;

   for(i = 0; i < sizeof(ImpTypeArrayDcm_RdcErfsTsaDatenLesenReadDataType); i++){
    PutTsaDataEE(self, pucData[i], i);
   }
}

void ReadTsaDataDS(Rte_Instance self, uint8* pucData)
{
   uint8 i;

   for(i=0; i<sizeof(ImpTypeArrayDcm_RdcErfsTsaDatenLesenReadDataType); i++){
    pucData[i] = GetTsaDataEE(self, i);
   }
}

void ResetQRTyreMountedFlags(Rte_Instance self, uint8 HisFlags)
{
   uint8 Ix1,Ix2,CompVal1, ChangePos;
   uint8 OldMountIx[4] = {cMaxQRCodeSets, cMaxQRCodeSets, cMaxQRCodeSets, cMaxQRCodeSets};

  ChangePos = 0x00;

  Ix2 = 0x00;

   for(Ix1=0;Ix1<cMaxQRCodeSets;Ix1++){
    CompVal1 = GETTyreMountedFlagEE(self, Ix1);
      if((CompVal1 & 0x0F) == cTyreMountedFlag){
      if(Ix2 < cAnzRad){
        OldMountIx[Ix2] = Ix1;
        Ix2++;
      }

      }
   }

   for(Ix1=0;Ix1<cAnzRad;Ix1++){
      if(OldMountIx[Ix1] < cMaxQRCodeSets){
      CompVal1 = GETTyreMountedFlagEE(self, OldMountIx[Ix1]);

      for(Ix2=0;Ix2<cAnzRad;Ix2++){
          if((CompVal1 & (HisFlags & (uint8)(0x10 << Ix2))) != 0x00){
          PUTTyreMountedFlagEE(self, OldMountIx[Ix1], cTyreUnmountedFlag);

          ChangePos |= (0x08 >> Ix2);

          PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_Reifenwechseln_erkannt, ChangePos);
        }
      }
      }
   }
   SetTyreRuntimeDataDS(self, &OldMountIx[0]);
}

static void GetLatestUnmountedQrDataEntries(Rte_Instance self, uint8* pUnmountEntryIndex)
{
   uint8 SmallestUmmountedKm[4] = {0x00,0x00,0x00,0x00};

   uint8 QrIx,i,j,MinIx,MinCt,ucHelp;
   boolean bStopComp;

   MinCt = 0;
   MinIx = cMaxQRCodeSets;

   for(QrIx=0; QrIx<cMaxQRCodeSets;QrIx++){
      if(GETTyreMountedFlagEE(self, QrIx) == cTyreUnmountedFlag){
      if(MinCt < 8){
        pUnmountEntryIndex[MinCt] = QrIx;
      }
      MinCt++;
      }
   }

   if(MinCt > 8){
    QrIx = pUnmountEntryIndex[7];
    QrIx++;

    while (QrIx < cMaxQRCodeSets){
      if(GETTyreMountedFlagEE(self, QrIx) == cTyreUnmountedFlag){
        MinCt = 0;
        MinIx = 0;

        for(i=0;i<cKmSize;i++){
          SmallestUmmountedKm[i] = GETTyreRuntimeDataEE(self, pUnmountEntryIndex[0], cUnmountedKmIx + i);
        }

        for(MinCt=1; MinCt<8;MinCt++){
          bStopComp = FALSE;

          for(i=0;i<cKmSize;i++){
            if(bStopComp == FALSE){
              ucHelp = GETTyreRuntimeDataEE(self, pUnmountEntryIndex[MinCt], cUnmountedKmIx + i);

              if(SmallestUmmountedKm[i] > ucHelp){

                MinIx = MinCt;

                for(j=0;j<cKmSize;j++){
                  SmallestUmmountedKm[j] = GETTyreRuntimeDataEE(self, pUnmountEntryIndex[MinIx], cUnmountedKmIx + j);
                }
                bStopComp = TRUE;
              }
              else{
                if(SmallestUmmountedKm[i] < ucHelp){
                  bStopComp = TRUE;
                }
              }
            }
          }
        }

        bStopComp = FALSE;

        for(i=0;i<cKmSize;i++){
          if(bStopComp == FALSE){
            ucHelp = GETTyreRuntimeDataEE(self, QrIx, cUnmountedKmIx + i);

            if(SmallestUmmountedKm[i] > ucHelp){
              bStopComp = TRUE;
            }
            else
            {
              if(SmallestUmmountedKm[i] < ucHelp){

                pUnmountEntryIndex[MinIx] = QrIx;
                bStopComp = TRUE;
              }
            }
          }
        }
      }
      QrIx++;
      }
   }

}

uint8 GetQrIxOfWheelPos(Rte_Instance self, uint8 ucWheelPos)
{
   uint8 i, ucHelp, QrIx;

  QrIx = cMaxQRCodeSets;

   if(ucWheelPos < cAnzRad){
      for(i=0; i<cMaxQRCodeSets; i++){
      ucHelp = GETTyreMountedFlagEE(self, i);

      if((ucHelp & 0x0F) == cTyreMountedFlag){
          if((ucHelp & (uint8)(0x10<<ucWheelPos)) == (uint8)(0x10<<ucWheelPos)){
          QrIx = i;
        }
      }
      }
   }
   return (QrIx+1);
}

