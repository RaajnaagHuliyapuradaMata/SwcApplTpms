#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
  #include "CfgSwcApplTpms_Warning.hpp"
  #include "tss_stdx.hpp"
  #include "USWarnX.hpp"
  #include "uswarn_Ifx.hpp"
  #include "USWarn.hpp"
  #include "WnTypePar.hpp"
  #include "state_fzzX.hpp"
#else
  #include "tss_stdx.hpp"
  #include "USWarnX.hpp"
  #include "uswarn_ifx.hpp"
  #include "uswarn.hpp"
  #include "wntypepar.hpp"
  #include "state_FzzX.hpp"
  #include "eecate_ifx.hpp"
  #include "eecata2_ifx.hpp"
#endif

#ifdef cd_DynWarnResetCond_100309
STATIC uint8 ucDynWarnResetActive;
#endif

uint8 CfgReInitSingleUSWIF( uint8 ucPressure, sint8 scTemperature, uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[4];

  aucDiagService[0] = ucCfgReInitSinglec;
  aucDiagService[1] = ucZomPos;
  aucDiagService[2] = ucPressure;
  aucDiagService[3] = (uint8) scTemperature;
  if( ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xFF;
  }
  else{
   ucResult = 0;
  }
  return( ucResult );
}

uint8 ucCfgPMinUSWIF( uint8 ucPMin )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucCfgPMinc;
  aucDiagService[1] = ucPMin;
  if( ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }
  else{
   ucResult = 0;
  }
  return( ucResult );
}

uint8 ResetWarnVectorUSWIF( uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucResetWarnVectorc;
  aucDiagService[1] = ucZomPos;

  if( ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xFF;
  }
  else{
   ucResult = 0;
  }

  return( ucResult );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 PorInitUSWIF(void)
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = 0;
  aucDiagService[1] = 0;

  if( ucTSSMsgManagerTM( ucPorInitc, aucDiagService ) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  return( ucResult );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

uint8 ClearWarnOfIdUSWIF( uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucClearWarnOfIdc;
  aucDiagService[1] = ucZomPos;

  if( ucTSSMsgManagerTM(ucDiagServicec, aucDiagService) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  return( ucResult );
}

uint8 GetWarnOfIdUSWIF( uint8 *pucWarnOfId )
{
  uint8 ucResult, aucDiagService[4];

  aucDiagService[0] = ucGetWarnVectorsIdc;
  aucDiagService[1] = 0;
  aucDiagService[2] = 0;
  aucDiagService[3] = 0;

  if( ucTSSMsgManagerTM(ucDiagServicec, aucDiagService) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  pucWarnOfId[0] = aucDiagService[0];
  pucWarnOfId[1] = aucDiagService[1];
  pucWarnOfId[2] = aucDiagService[2];
  pucWarnOfId[3] = aucDiagService[3];

  return( ucResult );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetHWFreakBitsIFH( uint8 *pucFreakBits )
{
  uint8 ucResult, aucDiagService[1];

  aucDiagService[0] = ucGetHWFreakBitsc;

  if( ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xFF;
  }
  else{
   ucResult = 0;
  }

  *pucFreakBits = aucDiagService[0];

  return( ucResult );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

uint8 NewPositionsUSWIF( const uint8 *pucRadPos )
{
  uint8 i, ucResult, aucDiagService[6];

  aucDiagService[0] = ucNewPositionsc;

  for( i = 0; i < cAnzRad; i++ )
  {
    aucDiagService[i + 1] = pucRadPos[i];

  }

  if( ucTSSMsgManagerTM( ucDiagServicec, aucDiagService ) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  return( ucResult );
}

uint8 ClearPosUSWIF(void)
{
  uint8 ucResult, aucDiagService[1];

  aucDiagService[0] = ucClearPosc;

  if(ucTSSMsgManagerTM( ucDiagServicec, aucDiagService ) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  return( ucResult );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
void ResetWarningsUSWIF(void)
{

  (void) ResetWarnVectorUSWIF( 5 );

  (void) PorInitUSWIF();
}
#endif //BUILD_WITH_UNUSED_FUNCTION

uint8 ucWAlgoPrePara( uint8 ucPWarnMin, uint8 ucPSollMinVA, uint8 ucPSollMinHA )
{
  uint8 ucType, ucPSollMin, ucResult, ucResult1, ucResult2;

  PSSType tPAR;

  if( ucPSollMinVA < ucPSollMinHA )
  {
   ucPSollMin = ucPSollMinVA;
  }
  else{
   ucPSollMin = ucPSollMinHA;
  }
  ucType = ( GETucVarCodMinPressThresEE() );
  tPAR.ucAccess = (uint8) 0;
  tPAR.ucParaByte[0] = cUSWAlgo_ParaByte0_EU;
  tPAR.ucParaByte[1] = cUSWAlgo_ParaByte1_EU;
  tPAR.scTResLimit   = cUSWAlgo_TResLimit_EU;
  tPAR.ucParaHighPressThres = GETucVarCodHighPressThresEE();
  tPAR.ucParaHighPressResetThres = NvM3_GETucVarCodHighPressResetThresEE();
  tPAR.ucParaAxImbSetThres = GETucVarCodAxImbSetThresEE();
  tPAR.ucParaAxImbResThres = GETucVarCodAxImbResThresEE();

  ucResult1 = ucUSWAlgoPara( ucType, ucPSollMin, &tPAR );

  ucResult2 = ucCfgPMinUSWIF( ucPWarnMin );

  if( (ucResult1 == 0x00) && (ucResult2 == 0x00) )
  {
   ucResult = cRetOk;
  }
  else{
   ucResult = cRetError;
  }

  return( ucResult );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GetIsoUSWIF( uint8 ucPressure, sint8 scTemperature, uint16 *pushIsochore )
{
  uint8 ucResult, aucDiagService[3];
  uint16 *pushDiagService;

  aucDiagService[0] = ucGetIsoc;
  aucDiagService[1] = ucPressure;
  aucDiagService[2] = (uint8)scTemperature;

  if( ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }else{
   ucResult = 0;
  }

  pushDiagService = (uint16 *) &aucDiagService[0];
  *pushIsochore = *pushDiagService;

  return( ucResult );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint8 GetPTSollUSWIF( uint8 *pucPressure, sint8 *pscTemperature, uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucGetPTSollc;
  aucDiagService[1] = ucZomPos;
  if(ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }else{
   ucResult = 0;
  }

  if(pucPressure != NULL)
  {
    *pucPressure = aucDiagService[0];
  }
  if(pscTemperature != NULL)
  {
    *pscTemperature = (sint8)aucDiagService[1];
  }

  return( ucResult );
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint8 CfgPSollMinAtIdUSWIF( uint8 ucPressure, uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[3];

  aucDiagService[0] = ucCfgPSollMinAtIdc;
  aucDiagService[1] = ucZomPos;
  aucDiagService[2] = ucPressure;
  if(ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }else{
   ucResult = 0;
  }
  return( ucResult );
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint8 GetPWarmUSWIF( uint8 *pucPressure, sint8 *pscTemperature, uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucGetPwarmc;
  aucDiagService[1] = ucZomPos;
  if(ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }else{
   ucResult = 0;
  }

  if(pucPressure != NULL)
  {
    *pucPressure = aucDiagService[0];
  }
  if(pscTemperature != NULL)
  {
    *pscTemperature = (sint8)aucDiagService[1];
  }

  return( ucResult );
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 PutPWarmUSWIF( uint8 ucPressure, uint8 ucZomPos )
{
  uint8 ucResult, aucDiagService[3];

  aucDiagService[0] = PutPwarm;
  aucDiagService[1] = ucPressure;
  aucDiagService[2] = ucZomPos;
  if(ucWarnManagerWN( ucDiagServicec, aucDiagService ) == 0xff )
  {
   ucResult = 0xff;
  }else{
   ucResult = 0;
  }

  return( ucResult );
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef cd_DynWarnResetCond_100309

boolean DynWarnResetCond(uint8 ActPress, uint8 WarnPress, uint8 ZomPos)
{
  boolean bReturn;

  bReturn = FALSE;

  if((ucDynWarnResetActive & (uint8)(1 << ZomPos)) == (uint8)(1 << ZomPos))
  {

   if(ActPress >= (WarnPress + 0x04))
   {

      if(ActPress > GETucResetWarnPressRefEE(ZomPos))
      {
        if((ActPress - GETucResetWarnPressRefEE(ZomPos)) > GETucResetWarnPresLimitEE())
        {
          bReturn = TRUE;
        }
      }
   }

   if(bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE)
   {
      ucDynWarnResetActive &= (uint8)((uint8)(1 << ZomPos) ^ 0xFF);
   }
  }
  return(bReturn);
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void InitDynWarnReset(void){
  ucDynWarnResetActive = (uint8)0x0F;
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#endif

uint8 GetPosOfIdIFH( uint8 ucIdPos, uint8 *pucCarMountedPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucGetPosOfIdc;
  aucDiagService[1] = ucIdPos;

  if( ucTSSMsgManagerTM(ucDiagServicec, aucDiagService) == 0x00 )
  {
   ucResult = 0;
  }
  else{
   ucResult = 0xFF;
  }

  *pucCarMountedPos = aucDiagService[0];

  return( ucResult );
}

uint8 GetIdOfPosIFH( uint8 ucPos, uint8 *pucIdOfCarMountedPos )
{
  uint8 ucResult, aucDiagService[2];

  aucDiagService[0] = ucGetIdcOfPos;
  aucDiagService[1] = ucPos;

  if( ucTSSMsgManagerTM(ucDiagServicec, aucDiagService) == 0x00 )
  {
   ucResult = 0;
  }else{
   ucResult = 0xff;
  }

  *pucIdOfCarMountedPos = aucDiagService[0];

  return( ucResult );
}

void ResetOldWarningsByNewEr(uint8 ucErChangeState, uint8 ucMaxErNumber)
{
  uint8 ucLoop = 0;

  for(ucLoop = 0; ucLoop < ucMaxErNumber; ucLoop++)
  {
   if((ucErChangeState & (uint8)(0x10 << ucLoop)) == (uint8)(0x10 << ucLoop))
   {
      (void)ResetWarnVectorUSWIF(ucLoop);
      (void)ClearWarnOfIdUSWIF(ucLoop);
   }
  }
}

