#include "EeErfsBlock.h"
#include "datamanagerX.h"
#include "RID_X.h"
#include "erfs_X.h"
#include "CodingDataX.h"
#include "HS_KalibrierereignisX.h"

#define cErfsInitializer        ((uint8)0x00)
#define cSelLoadConIxNVM        ((uint8)0x01)
#define cSelSeasonIxNVM         ((uint8)0x02)
#define cSelSuTyreIxNVM         ((uint8)0x03)
#define cSelWiTyreIxNVM         ((uint8)0x04)
#define cSelTyreListIxNVM       ((uint8)0x05)
#define cTyreSelectionActive    ((uint8)0x06)
#define cPlausiInitError        ((uint8)0x07)
#define cTyreChanged            ((uint8)0x08)
#define cStManSelection         ((uint8)0x09)
#define cIdrMessage             ((uint8)0x0A)
#define cInvalidTyreList        ((uint8)0x0B)
#define cStSelectTyre           ((uint8)0x0C)
#define cTyreSelectionBckgrd    ((uint8)0x0D)
#define cSelAutoTyreIxNVM       ((uint8)0x0E)
#define cAutomaticSelFailed     ((uint8)0x0F)
#define cUseSavedHistRidDataCt  ((uint8)0x10)
#define cDimDOTSize             (cTyreDimSize + cTyreDOTSize)
#define cMaxDimDotSets          ((uint8)4)
#define cTyreDim1_StartIx       (0x11)
#define cTyreDOT1_StartIx       (cTyreDim1_StartIx + cTyreDimSize)
#define cCurErfsTyreData        (cTyreDim1_StartIx + (cMaxDimDotSets * cDimDOTSize))
#define cCurSuErfsTyreData      (cCurErfsTyreData + TYRE_DATA_BYTES)
#define cCurWiErfsTyreData      (cCurSuErfsTyreData + TYRE_DATA_BYTES)

static boolean bBlockNeedsUpdate = FALSE;

static void CheckValueChangesAndSetUpdateFlag(uint8 ucOldValue, uint8 ucNewValue){
   if(ucOldValue != ucNewValue){
      bBlockNeedsUpdate = TRUE;
   }
}

void InitErfsBlockEE(Rte_Instance self){
   uint16 ushLoop;
   for(ushLoop = 0; ushLoop < sizeof(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data); ushLoop++){
      Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[ushLoop] = 0xff;
   }
   PUTSelectedSuTyreIndexEE   (self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedWiTyreIndexEE   (self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedTyreIndexEE     (self, OP_SLCTN_TYR_AVLB_SignalUngueltig);
   PUTSelectedAutoTyreIndexEE (self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedLoadStateEE     (self, ST_TAR_P_LOCO_TPCT_Signal_ungueltig);
   PUTSelectedSeasonEE        (self, OP_TYR_SEA_TPCT_Sommerreifen);
   PUTIdrMessageEE            (self, OP_IDR_SLCTN_Signal_unbefuellt);
   PUTStManSelectionEE        (self, ST_MAN_SLCTN_Signal_ungueltig);
   PUTInvalidTyreListEE       (self, TRUE);

   PUTTyreSelectionActiveEE(
         self
#ifdef _EcuVirtual
      ,  FALSE
#else
      ,  TRUE
#endif
   );

   PUTTyreSelectionBckgrdEE   (self, TRUE);
   SetCalibrationRootCauseDS  (self, cCalVirgin);
   PUTPlausiInitErrorEE       (self, FALSE);
   PUTTyreChangedEE           (self, FALSE);
   PUTStSelectTyreEE          (self, ST_SLCTN_TYR_SignalUngueltig);
   PUTUseSavedHistRidDataCtEE (self, 0x00);
   DeleteRidDataOfHisColRID   (self, 0x0F);
   PUTucErfsInitializerEE     (self, cNvmInitialized);
   bBlockNeedsUpdate = TRUE;
}

uint8 GETAutomaticSelectionFailedStatusEE (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cAutomaticSelFailed                         ]);}
uint8 GETIdrMessageEE                     (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cIdrMessage                                 ]);}
uint8 GETInvalidTyreListEE                (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cInvalidTyreList                            ]);}
uint8 GETPlausiInitErrorEE                (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cPlausiInitError                            ]);}
uint8 GETSelectedAutoTyreIndexEE          (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelAutoTyreIxNVM                           ]);}
uint8 GETSelectedLoadStateEE              (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelLoadConIxNVM                            ]);}
uint8 GETSelectedSeasonEE                 (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSeasonIxNVM                             ]);}
uint8 GETSelectedSuTyreIndexEE            (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSuTyreIxNVM                             ]);}
uint8 GETSelectedTyreIndexEE              (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelTyreListIxNVM                           ]);}
uint8 GETSelectedWiTyreIndexEE            (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelWiTyreIxNVM                             ]);}
uint8 GETStManSelectionEE                 (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStManSelection                             ]);}
uint8 GETStSelectTyreEE                   (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStSelectTyre                               ]);}
uint8 GETTyreChangedEE                    (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreChanged                                ]);}
uint8 GETTyreSelectionActiveEE            (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionActive                        ]);}
uint8 GETTyreSelectionBckgrdEE            (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionBckgrd                        ]);}
uint8 GETucErfsInitializerEE              (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cErfsInitializer                            ]);}
uint8 GETUseSavedHistRidDataCtEE          (Rte_Instance self)                            {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cUseSavedHistRidDataCt                      ]);}
uint8 GETTyreDimDataEE                    (Rte_Instance self, uint8 i, uint8 x)          {return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreDim1_StartIx + (cDimDOTSize * i) + (x) ]);}
void  PUTucErfsInitializerEE              (Rte_Instance self, uint8 x)                   {                                                                                                                                             Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cErfsInitializer                           ] = (x);}
void  PUTAutomaticSelectionFailedStatusEE (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cAutomaticSelFailed                        ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cAutomaticSelFailed                        ] = (x);}
void  PUTIdrMessageEE                     (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cIdrMessage                                ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cIdrMessage                                ] = (x);}
void  PUTInvalidTyreListEE                (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cInvalidTyreList                           ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cInvalidTyreList                           ] = (x);}
void  PUTPlausiInitErrorEE                (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cPlausiInitError                           ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cPlausiInitError                           ] = (x);}
void  PUTSelectedAutoTyreIndexEE          (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelAutoTyreIxNVM                          ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelAutoTyreIxNVM                          ] = (x);}
void  PUTSelectedLoadStateEE              (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelLoadConIxNVM                           ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelLoadConIxNVM                           ] = (x);}
void  PUTSelectedSeasonEE                 (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSeasonIxNVM                            ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSeasonIxNVM                            ] = (x);}
void  PUTSelectedSuTyreIndexEE            (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSuTyreIxNVM                            ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelSuTyreIxNVM                            ] = (x);}
void  PUTSelectedTyreIndexEE              (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelTyreListIxNVM                          ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelTyreListIxNVM                          ] = (x);}
void  PUTSelectedWiTyreIndexEE            (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelWiTyreIxNVM                            ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cSelWiTyreIxNVM                            ] = (x);}
void  PUTStManSelectionEE                 (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStManSelection                            ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStManSelection                            ] = (x);}
void  PUTStSelectTyreEE                   (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStSelectTyre                              ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cStSelectTyre                              ] = (x);}
void  PUTTyreChangedEE                    (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreChanged                               ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreChanged                               ] = (x);}
void  PUTTyreSelectionActiveEE            (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionActive                       ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionActive                       ] = (x);}
void  PUTTyreSelectionBckgrdEE            (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionBckgrd                       ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreSelectionBckgrd                       ] = (x);}
void  PUTUseSavedHistRidDataCtEE          (Rte_Instance self, uint8 x)                   {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cUseSavedHistRidDataCt                     ], x); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cUseSavedHistRidDataCt                     ] = (x);}
void  PUTTyreDimDataEE                    (Rte_Instance self, uint8 i, uint8 x, uint8 y) {CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreDim1_StartIx + (cDimDOTSize * i) + (x)], y); Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[cTyreDim1_StartIx + (cDimDOTSize * i) + (x)] = (y);}

uint8 GETTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x){
   uint8 Index;
  Index = cTyreDOT1_StartIx + (cDimDOTSize * i) + (x);
   return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index]);
}

void PUTTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y){
   uint8 Index;
  Index = cTyreDOT1_StartIx + (cDimDOTSize * i) + (x);
  CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index], y);
  Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index] = (y);
}

uint8 GETCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 Season){
   uint8 Index;
   if(Season == CSEASON_SUMMER){
    Index = cCurSuErfsTyreData + (i);
   }
   else if(Season == CSEASON_WINTER){
    Index = cCurWiErfsTyreData + (i);
   }
   else{
    Index = cCurErfsTyreData + (i);
   }
   return(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index]);
}

void PUTCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 Season){
   uint8 Index;
   if(Season == CSEASON_SUMMER){
    Index = cCurSuErfsTyreData + (i);
   }
   else if(Season == CSEASON_WINTER){
    Index = cCurWiErfsTyreData + (i);
   }
   else{
    Index = cCurErfsTyreData + (i);
   }
  CheckValueChangesAndSetUpdateFlag(Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index], x);
  Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self)->Data[Index] = (x);
}

void SetErfsBlockWriteMeEE(void){
   bBlockNeedsUpdate = TRUE;
}

boolean bGetErfsBlockWriteMeEE(void){
   return bBlockNeedsUpdate;
}

void ClearErfsBlockWriteMeEE(void){
   bBlockNeedsUpdate = FALSE;
}
