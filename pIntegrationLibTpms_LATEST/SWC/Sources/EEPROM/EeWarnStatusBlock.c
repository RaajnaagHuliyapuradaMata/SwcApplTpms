#include "EeWarnStatusBlock.h"

static boolean bBlockNeedsUpdate = FALSE;

void InitWarnStatusBlockEE( Rte_Instance self){
  uint8   ucHistPos;
  uint16  ushLoop;
  for ( ushLoop = 0; ushLoop < sizeof(Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock(self)->Data); ushLoop++){
    Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock(self)->Data[ushLoop] = 0xff;
  }

  PUTucWarnStatusBlockInitializeEE( self, 0xff);
  PUTucWsEE( self, 0x00, FALSE);
  PUTtCdInitValEE( self, FALSE);
  PUTucTsEE( self, 0x00, FALSE);
  PUTaucCbInitValEE( self, FALSE);
  PUTaucWarnTypeArrayInitValEE( self, FALSE);
  PUTaushShortTimerInitValEE( self, FALSE);
  PUTaushLongTimerInitValEE( self, FALSE);
  PUTscTAinitValEE( self, cInitTemperature);
  for ( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++){
    PUTucLastWuPressureEE( self, cInvalidREpressure, ucHistPos);
    PUTscLastWuTemperatureEE( self, cInvalidREtemperature, ucHistPos);
  }
  PUTulTinitOatLowerTimeStartEE( self, 0xFFFFFFFFu);
  PUTulTinitOatHigherTimeStartEE( self, 0xFFFFFFFFu);
  PUTbCorrTinitLowerEventEE( self, FALSE);
  PUTbCorrTinitHigherEventEE( self, FALSE);
  PUTulCoolingCaptTimeEE( self, (uint32) 0xFFFFFFFFu);
  PUTucWarnStatusBlockInitializeEE( self, cNvmInitialized);
  SetWarnStatusBlockUpdateFlagEE();
}

uint8 GETucWarnStatusBlockInitializeEE( Rte_Instance self){
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucInitialize);
}

void PUTucWarnStatusBlockInitializeEE( Rte_Instance self, uint8 ucNvmInitialize){
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucInitialize = ucNvmInitialize;
}

void GETucWsEE( Rte_Instance self, uint8 * x){
#ifdef _EcuVirtual
  if( x != NULL_PTR){
#else
  if( x != NULL){
#endif
    *x = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucWS;
  }
}

void PUTucWsEE( Rte_Instance self, uint8 x, boolean bUpdateOnEvent){
  if( bUpdateOnEvent == TRUE){
    if( x != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucWS){
      SetWarnStatusBlockUpdateFlagEE();
    }
  }else{
  }
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucWS = x;
}

void GETtCdEE( Rte_Instance self, tCalibrationTab * x){
#ifdef _EcuVirtual
  if( x != NULL_PTR){
#else
  if( x != NULL){
#endif
    *x = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->tCD;
  }
}

void PUTtCdInitValEE( Rte_Instance self, boolean bUpdateOnEvent){
  tCalibrationTab tCalInit =  {
#ifdef _EcuVirtual
      0,
#else
      { 0                              },
#endif
      { 0, 0, 0, 0                     },
      { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
      { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
      { 0, 0, 0, 0                     },
      { 0, 0, 0, 0                     },
      { 0, 0, 0, 0                     },
      { 0, 0, 0, 0                     },
      { 0, 0, 0, 0                     }
   };
  PUTtCdEE( self, &tCalInit, bUpdateOnEvent);
}

void PUTtCdEE( Rte_Instance self, const tCalibrationTab * x, boolean bUpdateOnEvent){
#ifdef _EcuVirtual
  if( x != NULL_PTR){
#else
  if( x != NULL){
#endif
    if( bUpdateOnEvent == TRUE){
      SetWarnStatusBlockUpdateFlagEE();
    }else{

    }

    ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->tCD = *x;
  }
}

void GETucTsEE( Rte_Instance self, uint8 * x)
{
#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    *x = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucTS;
  }
}

void PUTucTsEE( Rte_Instance self, uint8 x, boolean bUpdateOnEvent)
{
  if( bUpdateOnEvent == TRUE)
  {

    if( x != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucTS)
    {
      SetWarnStatusBlockUpdateFlagEE();
    }
  }else{

  }

  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucTS = x;
}

void GETaucCbEE( Rte_Instance self, WarnConfigArrayType * x)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for ( ucHistPos = 0; ucHistPos < sizeof(WarnConfigArrayType); ucHistPos++)
    {
      (*x)[ucHistPos] = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucCB[ucHistPos];
    }
  }
}

void PUTaucCbInitValEE( Rte_Instance self, boolean bUpdateOnEvent)
{
  WarnConfigArrayType aucWarnConfigInit = { 0, 0 };

  PUTaucCbEE( self, (const WarnConfigArrayType *) &aucWarnConfigInit, bUpdateOnEvent);
}

void PUTaucCbEE( Rte_Instance self, const WarnConfigArrayType * x, boolean bUpdateOnEvent)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for( ucHistPos = 0; ucHistPos < sizeof(WarnConfigArrayType); ucHistPos++)
    {
      if( bUpdateOnEvent == TRUE)
      {

        if( (*x)[ucHistPos] != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucCB[ucHistPos])
        {
          SetWarnStatusBlockUpdateFlagEE();
        }
      }else{

      }

      ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucCB[ucHistPos] = (*x)[ucHistPos];
    }
  }
}

void GETaucWarnTypeArrayEE( Rte_Instance self, WarnBitArrayType * x)
{
  uint8 ucHistPos, ucAttrTyp;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for ( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      for ( ucAttrTyp = 0; ucAttrTyp < ucWarnBitArraySizeWNc; ucAttrTyp++)
      {
        (*x)[ucHistPos][ucAttrTyp] = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucWarnStatus[ucHistPos][ucAttrTyp];
      }
    }
  }
}

void PUTaucWarnTypeArrayInitValEE( Rte_Instance self, boolean bUpdateOnEvent)
{
  WarnBitArrayType aucWarnBitInit = {
                                      { 0, 0, 0 },
                                      { 0, 0, 0 },
                                      { 0, 0, 0 },
                                      { 0, 0, 0 }
                                    };

  PUTaucWarnTypeArrayEE( self, (const WarnBitArrayType *) &aucWarnBitInit, bUpdateOnEvent);
}

void PUTaucWarnTypeArrayEE( Rte_Instance self, const WarnBitArrayType * x, boolean bUpdateOnEvent)
{
  uint8 ucHistPos, ucAttrTyp;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      for( ucAttrTyp = 0; ucAttrTyp < ucWarnBitArraySizeWNc; ucAttrTyp++)
      {
        if( bUpdateOnEvent == TRUE)
        {

          if( (*x)[ucHistPos][ucAttrTyp] != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucWarnStatus[ucHistPos][ucAttrTyp])
          {
            SetWarnStatusBlockUpdateFlagEE();
          }
        }else{

        }

        ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->aucWarnStatus[ucHistPos][ucAttrTyp] = (*x)[ucHistPos][ucAttrTyp];
      }
    }
  }
}

void GETaushShortTimerEE( Rte_Instance self, ShortTimerArrayType * x)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for ( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      (*x)[ucHistPos] = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusShortTimer[ucHistPos];
    }
  }
}

void PUTaushShortTimerInitValEE( Rte_Instance self, boolean bUpdateOnEvent)
{
  ShortTimerArrayType aushShortTimer = { 0, 0, 0, 0 };

  PUTaushShortTimerEE( self, (const ShortTimerArrayType *) &aushShortTimer, bUpdateOnEvent);
}

void PUTaushShortTimerEE( Rte_Instance self, const ShortTimerArrayType * x, boolean bUpdateOnEvent)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      if( bUpdateOnEvent == TRUE)
      {

        if( (*x)[ucHistPos] != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusShortTimer[ucHistPos])
        {
          SetWarnStatusBlockUpdateFlagEE();
        }
      }else{

      }

      ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusShortTimer[ucHistPos] = (*x)[ucHistPos];
    }
  }
}

void GETaushLongTimerEE( Rte_Instance self, LongTimerArrayType * x)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for ( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      (*x)[ucHistPos] = ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusLongTimer[ucHistPos];
    }
  }
}

void PUTaushLongTimerInitValEE( Rte_Instance self, boolean bUpdateOnEvent)
{
  LongTimerArrayType aushLongTimer = { 0, 0, 0, 0 };

  PUTaushLongTimerEE( self, (const LongTimerArrayType *) &aushLongTimer, bUpdateOnEvent);
}

void PUTaushLongTimerEE( Rte_Instance self, const LongTimerArrayType * x, boolean bUpdateOnEvent)
{
  uint8 ucHistPos;

#ifdef _EcuVirtual
  if( x != NULL_PTR)
#else
  if( x != NULL)
#endif
  {
    for( ucHistPos = 0; ucHistPos < cAnzRad; ucHistPos++)
    {
      if( bUpdateOnEvent == TRUE)
      {

        if( (*x)[ucHistPos] != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusLongTimer[ucHistPos])
        {
          SetWarnStatusBlockUpdateFlagEE();
        }
      }else{

      }

      ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ushWarnStatusLongTimer[ucHistPos] = (*x)[ucHistPos];
    }
  }
}

sint8 GETscTAinitValEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->scTAinitValue);
}

void PUTscTAinitValEE( Rte_Instance self, sint8 x)
{
  if( x != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->scTAinitValue)
  {
    SetWarnStatusBlockUpdateFlagEE();
  }

  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->scTAinitValue = x;
}

PhySensorTyrePresType GETucLastWuPressureEE( Rte_Instance self, uint8 i)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucLastWuPressure[i]);
}

void PUTucLastWuPressureEE( Rte_Instance self, PhySensorTyrePresType x, uint8 i)
{
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ucLastWuPressure[i] = x;
}

PhySensorTyreTempType GETscLastWuTemperatureEE( Rte_Instance self, uint8 i)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->scLastWuTemperature[i]);
}

void PUTscLastWuTemperatureEE( Rte_Instance self, PhySensorTyreTempType x, uint8 i)
{
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->scLastWuTemperature[i] = x;
}

uint32 GETulTinitOatLowerTimeStartEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulTinitOatLowerTimeStart);
}

void PUTulTinitOatLowerTimeStartEE( Rte_Instance self, uint32 x)
{
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulTinitOatLowerTimeStart = x;
}

uint32 GETulTinitOatHigherTimeStartEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulTinitOatHigherTimeStart);
}

void PUTulTinitOatHigherTimeStartEE( Rte_Instance self, uint32 x)
{
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulTinitOatHigherTimeStart = x;
}

boolean GETbCorrTinitLowerEventEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitLowerEvent);
}

void PUTbCorrTinitLowerEventEE( Rte_Instance self, boolean x)
{
  if( x != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitLowerEvent)
  {
    SetWarnStatusBlockUpdateFlagEE();
  }

  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitLowerEvent = x;
}

boolean GETbCorrTinitHigherEventEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitHigherEvent);
}

void PUTbCorrTinitHigherEventEE( Rte_Instance self, boolean x)
{
  if( x != ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitHigherEvent)
  {
    SetWarnStatusBlockUpdateFlagEE();
  }

  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->bCorrTinitHigherEvent = x;
}

uint32 GETulCoolingCaptTimeEE( Rte_Instance self)
{
  return( ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulCoolingCaptTime);
}

void PUTulCoolingCaptTimeEE( Rte_Instance self, uint32 x)
{
  ((tWarnStatusNvmBlockType *) (void *) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock( self)->Data)->ulCoolingCaptTime = x;
}

void SetWarnStatusBlockUpdateFlagEE(void)
{
  bBlockNeedsUpdate = TRUE;
}

void ClearWarnStatusBlockUpdateFlagEE(void)
{
  bBlockNeedsUpdate = FALSE;
}

boolean bGetWarnStatusBlockUpdateFlagEE(void)
{
  return bBlockNeedsUpdate;
}

