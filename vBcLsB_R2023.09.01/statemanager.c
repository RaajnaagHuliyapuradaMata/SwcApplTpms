

#define STATEMANAGER_C

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
  #include "SwcApplTpms_CAN_If.hpp"
  #include "SwcApplTpms_DTC_If.hpp"
  #include "uswarnX.hpp"
  #include "Uswarn_IfX.hpp"
  #include "procdatX.hpp"
  #include "wallocX.hpp"
  #include "statisticsX.hpp"
  #include "rediagX.hpp"
  #include "IDOM_X.hpp"
  #include "statemanager.hpp"
  #include "statemanagerX.hpp"
  #include "cd_decoder_X.hpp"
  #include "multiframeX.hpp"
  #include "State_FzzX.hpp"
  #include "State_BzX.hpp"
  #include "State_ZkX.hpp"
  #include "global.hpp"
  #include "WatcfX.hpp"
  #include "WnTypePar.hpp"
  #include "abs_linX.hpp"
  #include "CfgSwcApplTpms.hpp"
  #include "BusMsgX.hpp"
  #include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

  #include "SwcApplTpms_LearnEOL.hpp"
#else
  #include "CfgSwcApplTpms.hpp"
  #include "applmainX.hpp"
  #include "uswarnX.hpp"
  #include "uswarn_Ifx.hpp"
  #include "procdatX.hpp"
  #include "errmemX.hpp"
  #include "wallocX.hpp"
  #include "statisticsX.hpp"
  #include "rediagX.hpp"
  #include "idom_X.hpp"
  #include "sgdiagx.hpp"
  #include "bandmodex.hpp"
  #include "romdata_ifX.hpp"
  #include "ccpifx.hpp"
  #include "eecata2_ifx.hpp"
  #include "eecate_ifx.hpp"
  #include "silaX.hpp"
  #include "REDiag_if.hpp"
  #include "transmitx.hpp"
  #include "calibrx.hpp"
  #include "statemanager.hpp"
  #include "statemanagerX.hpp"
  #include "cd_decoder_X.hpp"
  #include "multiframeX.hpp"
  #include "global.hpp"
  #include "WnTypePar.hpp"
  #include "ReceiveX.hpp"

  #include "abs_linX.hpp"
#endif

#define MAX_CNT_VALUE_TO_RESET_ERR    35U
#define cCallsFor10Minutes 3000U
#define c10MinutesBCMTime 600000U
#define cCallsFor8Minutes 2400U
#define c8MinutesBCMTime 480000U
#define c1MinuteBCMTime 60000U
#define cTPMSCyclicCallPeriod 200U

#define cEvalSpeedValueMissingThreshold   (uint16) 0x0A8CU

static uint8  ucWheelPos = cRadPosUndef;
static uint8  ucHistSlot = cAnzRad;

static uint8  ucMinutenCnt;

static uint8  ucTrefControl;
static sint8  scTrefRxTemp;

static uint16 ush5minTimer1;

static boolean bSpeedSubstituteValInUseStatus;

static uint16 ushTimerIn200MsForContinuousSpeedStatus;

static unsigned long ulBCMTimePrevious = 0;

static uint8 u8WUDefectErrStatus = 0;

static uint8 aucPosRecCounter[cAnzRad] = {0, 0, 0, 0};

#ifdef BUILD_WITH_UNUSED_FUNCTION
static uint16 SM_GetThresholdValueIn200msForContinuousSpeedStatus(ENUM_EVALUATION_TIME_MODE_TYPE eEvalMode);
#endif

void CountPositionReception(uint8 ucRecWheelPos);

void InitSM(void)
{
  InitBZ();
  InitFZZ();
  InitZK();
  InitWATCF();

  SM_ResetStatusForSpeedValueInUse();

  Init_AxImbSuppressionCounter();

  Start_AxImbSuppressionCounter();

  ucTrefControl = LOCKED;
  scTrefRxTemp = GETscAdaptedTrefEE();
#ifdef G_USE_PART_ER
  PartWalloc_Init();
#endif //G_USE_PART_ER
  ucMinutenCnt = 0x00U;
  ucWUMode3DiagActive = 0x00U;

  ush5minTimer1 = 0;  //reset 5 minutes counter for OperateTrefTemperature()
}

void InitAfterKl15OnSM(void)
{
  InitBZ();
#ifdef G_USE_PART_ER
#ifdef IBTCM_SW_ANPASSUNGEN
  SetPartErTimerWA(GETucPartErTimerFactorEE(), 200);
#else
  SetPartErTimerWA(GETucPartErTimerFactorEE(), 100);
#endif
#endif //G_USE_PART_ER

  ClearBitZustandskennungZK(cPOS_CHANGED_VL);
  ClearBitZustandskennungZK(cPOS_CHANGED_VR);
  ClearBitZustandskennungZK(cPOS_CHANGED_HL);
  ClearBitZustandskennungZK(cPOS_CHANGED_HR);

  InitIDOM();

  ReloadSTATISTICS();

  InitAddZomDataSM();

  SM_ResetStatusForSpeedValueInUse();

  UpdateHistoryFromRAMWIthTheOneFromNVM();
  u8WUDefectErrStatus = 0;
}

void InitAfterKl15OffSM(void)
{
  StoreSTATISTICS();

  PUTucPatmoEE( GETucPatmoPD() );
  PUTscAdaptedTrefEE( scTrefRxTemp );

  StopWallocTOAlarm();

  InitSM();
}

static void CheckForStoersenderZeit(void)
{
  boolean l_bFlag;
  boolean l_bSensorMissFlag;

  l_bSensorMissFlag = bGetPossibleRfInterf();
  l_bFlag = GETbStoersenderZeit();
  if((l_bFlag == TRUE) && (l_bSensorMissFlag == TRUE))
  {
    SetCurrentErrorERR(cZO_ERR_RF_INTERFERENCE);
    ResetCurrentErrorERR(cZO_ERR_RF_INTERFERENCE);
   PUTbHfIntLatchEE(TRUE);
  }
  else{

   if((GETbHfIntLatchEE() == FALSE) && (l_bSensorMissFlag == FALSE))
   {
      DeleteCurrentErrorERR(cZO_ERR_RF_INTERFERENCE);
   }
  }
}

#ifdef IBTCM_SW_ANPASSUNGEN

void EvIDOMTimeoutSM(void)
{
  SetRFinTime();
}
#endif

void SequenceControlSM(void)
{
  boolean bSpeedValid = FALSE;
#ifdef IBTCM_SW_ANPASSUNGEN

#else
  ucLiveCounterSM++;

  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE )
  {
   ControlWATO( cWATO_READ_ALARM, 0 );
  }
#endif

  CheckForStoersenderZeit();

#ifdef G_USE_PART_ER
  if(DecrPartErTimerWA(GETbWUFDActive()) == FALSE)
  {

   if(GETbStoersenderFf() == FALSE)
   {
      if(CheckPartErStateSM()!= 0x0F)
      {
      }
   }
  }
#endif//G_USE_PART_ER

  OperateTrefTemperature();
  bSpeedValid = ReceiveGetVehicleSpeedValidity();

  //check if we should increment HistProtecTimer and control periodicity of cyclic call
  if((bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE) && (bSpeedValid == TRUE))
  {
    IncrHistProtectTimer();
   ulBCMTimePrevious = 0; //ucControlCyclicCallPeriod(); RST Debug XXX BUILD_RIVIAN : 6.8.2021 don't use this monitoring in a BHSENS hardware!

  }
  else{
   ulBCMTimePrevious = 0; // don't monitor the periodicity of cyclic call when the car is not moving.
  }
}

void EvReDataSM(void){
  static uint8  ucFrameType;
  boolean bHelp = FALSE;
  uint32  ulReID;
  uint8 ucSuppIdent;
  uint8 ucTelType;

  ucSuppIdent = (uint8)(ulGetReDataIdPD() >> 28 );
  ucTelType = ucGetReDataTelTypePD();

  RSSIBalancePD( GETucOffset() );

  ulReID = ulGetReDataIdPD();
  ucHistSlot = ucGetColOfID(&ulReID);

  SaveReDataAtBufferPD(ucHistSlot);

  if(cTelTypeRotatS == ucTelType)
  {

   ucFrameType = ucCheckForMultiFrameMF( ulReID, ucGetReDataTGCounter(), cMF_MAX_FILTER_TIME_ROTATS);
  }
  else{

   ucFrameType = ucCheckForMultiFrameMF( ulReID, ucGetReDataTGCounter(), cMF_MAX_FILTER_TIME);
  }

  if( cTelTypeRotatS == ucTelType)
  {
   ucWheelPos = ucGetWheelPosSM();
    SaveRotatS();
  }

  bHelp = bCheckSuppIdentAndTelTypeSM(ucSuppIdent, ucTelType );

  if( bHelp == TRUE )
  {
   if( (LearningWheelPosActiveSM() == TRUE ) && ((ucFrameType == cFT_SINGLE_FRAME)||(cTelTypeRotatS == ucTelType)) )
   {
      if(cTelTypeRotatS != ucTelType)
      {

        SetAddZomDataSM();
      }

      ucLearningWheelPosSM();
   }
   else{
      //nothing
   }

   if((ucFrameType == cFT_SINGLE_FRAME) && (bGetBitBetriebszustandBZ(cEIGENRAD | cTEILEIGENRAD) == TRUE) && (ucTelType != cTelTypeRotatS))
   {

      ucWheelPos = ucGetWheelPosSM();

      if( (ucWheelPos != cRadPosFR) && (ucHistSlot < cAnzRad) )
      {
        SaveReDataInSlotSM( ucHistSlot );

#ifdef FILTER_SYMC_CAN_MSGS
        CheckStateOf_ER_PressureRx();
#endif

        if( ucIsReHwDefectPD(ucHistSlot) == TRUE )
        {
          SensorErrorDiagSM( TRUE, ucHistSlot );
        }
        else if(ucIsReHwDefectPD(ucHistSlot) == FALSE)
        {
          SensorErrorDiagSM( FALSE, ucHistSlot );
        }
        else{
        }

        if( bIsReOverTempPD(ucHistSlot) == TRUE )
        {
          SensorTemperatureDiagSM( TRUE, ucHistSlot );
        }
        else{
          SensorTemperatureDiagSM( FALSE, ucHistSlot );
        }

        if( bIsReLowLifeTimePD(ucHistSlot) == TRUE )
        {
          SensorLowLifeTimeDiagSM( TRUE, ucHistSlot );
        }
        else{
          SensorLowLifeTimeDiagSM( FALSE, ucHistSlot );
        }

        bHelp = FALSE;
        bHelp |= ucIsReHwDefectPD(ucHistSlot);

#ifdef BUILD_WITH_UNUSED_FUNCTION

        bHelp |= bIsReMessFailPD(ucHistSlot);
#endif
        if( bHelp == TRUE )
        {

        }
        else{

          InitResetWarnPressRefSM(ucHistSlot, GETucReifendruckPD ( ucHistSlot ));

          if(ucGetProbeCt(ucHistSlot) == 1U)
          {
            tWnState = tCheckForFlatTyreSM( ucHistSlot, ucWheelPos );
          }

          tWnState = tCheckForFlatTyreSM( ucHistSlot, ucWheelPos );
        }
      }
   }

   if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
   {
      PUTucMarkReceivedDatagramSTATISTICS(TRUE, ucHistSlot);
      (void)CountValidDatagramSTATISTICS(ucHistSlot);
   }

   CountPositionReception(ucWheelPos);

  }
}

static void ucLearningWheelPosSM(void)
{
  static struct InputWA tWaData;
  uint8  i = 0;
  uint8  ucWaState = 0;
#ifdef G_USE_ROTATION_DIRECTION
  uint8  ucSpinDir_l;
#endif //G_USE_ROTATION_DIRECTION

  tWaData.ulID = ulGetReDataPreProcIdPD();
  tWaData.ucRssi = ucGetReDataRssiAvgPD();

  tWaData.ucStatus = 0x00;

  if(cRE_AK_TM_MODE_LEARNDRIVE == (ucGetReDataPreProcTransModePD() & cRE_AK_TM_MODE_LEARNDRIVE))
  {

    tWaData.ucStatus |= cIDStateM4;
  }
  else if(cRE_AK_TM_MODE_DRIVE == (ucGetReDataPreProcTransModePD() & cRE_AK_TM_MODE_DRIVE))
  {

    tWaData.ucStatus |= cIDStateDrive;
  }
  else{

    tWaData.ucStatus &=(uint8)((cIDStateM4|cIDStateDrive)^0xFF);
  }

#ifdef G_USE_ROTATION_DIRECTION

  ucSpinDir_l = ((ucGetReDataPreProcWheelDirPD() >> 2)  & 0x03);

  tWaData.ucStatus |= ((ucSpinDir_l & 0x02) << 4);
  tWaData.ucStatus |= ((ucSpinDir_l & 0x01) << 3);
#endif //G_USE_ROTATION_DIRECTION

  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE )
  {

    tWaData.ucStatus &= (uint8) (0x40 ^ 0xff);
    tWaData.ucStatus |= (uint8) 0x80;
  }else{

   if( bGetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT ) == FALSE )
   {

      tWaData.ucStatus &= (uint8) (0xC0 ^ 0xff);
   }else{

      tWaData.ucStatus |= 0x40;
      tWaData.ucStatus &= (uint8) (0x80 ^ 0xff);
   }
  }

  ucWaState = ucLearnID( &tWaData );

  if( (ucWaState & cWAStateZO) == cWAStateZO)
  {
    SetBitBetriebszustandBZ( cER_FINISH | cZO_FINISH );
   ClearBitBetriebszustandBZ( cTEILEIGENRAD );
   CheckStateOf_ER_PressureRx_after_Allocation();

   for( i = 0; i < cMaxLR; i++ )
   {
      if((ucWaState & (uint8)(0x10 << i)) == (uint8)(0x10 << i))
      {
        SetChangedBit4WP( ucGetWPOfCol(i) );
      }
   }

    EntryWAStateFinishedSM();
  }
  else{
   if( (ucWaState & cWAStateER) == cWAStateER)
   {
      SetBitBetriebszustandBZ( cER_FINISH );
      ClearBitBetriebszustandBZ( cZO_FINISH );
      ClearBitBetriebszustandBZ( cTEILEIGENRAD );

      for( i = 0; i < cMaxLR; i++ )
      {
        if((ucWaState & (uint8)(0x10 << i)) == (uint8)(0x10 << i))
        {
          SetChangedBit4WP( ucGetWPOfCol(i) );
        }
      }
      EntryWAStateUnassignedSM();
   }
   else{
      ClearBitBetriebszustandBZ( cER_FINISH | cZO_FINISH );
      if( (ucWaState & cWAStateActive) == cWAStateActive )
      {
        ClearBitBetriebszustandBZ( cER_LEARNING ); //this bit is used inverted. It will be set to 0 when the wheel management should start (when 4 WS are received)
      }
      else{
        SetBitBetriebszustandBZ( cER_LEARNING );
      }
   }
  }
}

boolean LearningWheelPosActiveSM(void)
{
  boolean bLearnActive = FALSE;

  if(bGetBitBetriebszustandBZ(cWA_STARTED) == TRUE)
  {

   if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
   {

      if(bGetBitBetriebszustandBZ(cWA_FINISH) == FALSE)
      {

        if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == FALSE)
        {

          bLearnActive = TRUE;
        }
        else{

          if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE)
          {

            bLearnActive = TRUE;
          }
        }
      }
   }
  }

  return (bLearnActive);
}

static void EntryWAStateUnassignedSM(void)
{
  uint8 ucHistCol;
  boolean bChangeState = FALSE;
  uint32 ulReID;

  (void)DeleteCurrentErrorERR(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);
  (void)DeleteCurrentErrorERR(cZO_ERR_DETECT_TO0_MANY_SENSORS);

  PUTbHfIntLatchEE(FALSE);

  if( bGetBitBetriebszustandBZ( cZUGEORDNET ) == TRUE )
  {
   for( ucHistCol = 0; ucHistCol < cMaxLR; ucHistCol++ )
   {
      if( ucGetWPOfCol(ucHistCol) >= cMaxLR )
      {
        bChangeState = TRUE;

        PreloadFromAddZomDataSM(ucHistCol);
      }
   }

   if(bChangeState == TRUE)
   {

      ClearBitBetriebszustandBZ( cZUGEORDNET );
      (void) ClearPosUSWIF();
   }
  }
  else{
   if(bGetBitBetriebszustandBZ( cEIGENRAD ) == FALSE)
   {
      for( ucHistCol = 0; ucHistCol < cMaxLR; ucHistCol++ )
      {

        PreloadFromAddZomDataSM(ucHistCol);
      }
      bChangeState = TRUE;
   }
  }

  if(bChangeState == TRUE)
  {

    InitSTATISTICS();

   ulReID = ulGetReDataPreProcIdPD();

   Check4FastWarnOutputSM(ucGetColOfID( &ulReID ));
  }
  SetBitBetriebszustandBZ( cEIGENRAD );
  ClearBitBetriebszustandBZ( cWA_FINISH | cER_LEARNING );
}

static void EntryWAStateFinishedSM(void)
{
  uint32 ulReID;
  boolean bNewZoState = FALSE;

  DeleteErrorsOnZugeordnetSM();

  ClearBitBetriebszustandBZ( cER_LEARNING );

  if( bGetBitBetriebszustandBZ( cZUGEORDNET ) == FALSE )
  {

    SetBitBetriebszustandBZ( cZUGEORDNET | cEIGENRAD );

    (void) NewPositionsUSWIF( GETpucStartAdrWP() );

   bNewZoState = TRUE;
  }

  if(bNewZoState == TRUE)
  {

   ulReID = ulGetReDataPreProcIdPD();

   Check4FastWarnOutputSM(ucGetColOfID( &ulReID ));

  }

  SetBitBetriebszustandBZ( cWA_FINISH );
}

static uint8 ucGetWheelPosSM(void)
{
  uint8 ucLocalWheelPos;
  uint8 ucHistPos;
  uint8 ucRetVal;
  uint32 ulReID;

  ulReID = ulGetReDataPreProcIdPD();
  ucHistPos = ucGetColOfID( &ulReID );

  if( ucHistPos < cAnzRad )
  {
   ucLocalWheelPos = ucGetWPOfCol( ucHistPos );

   if( ucLocalWheelPos < cAnzRad )
   {
      ucRetVal = ucLocalWheelPos;
   }
   else{
      ucRetVal = cRadPosUndef;
   }
  }
  else{

   ucRetVal = cRadPosFR;
  }

  return ucRetVal;
}

static tWnStateType tCheckForFlatTyreSM( uint8 l_ucZomSlot, uint8 l_ucWheelPos )
{
  struct HFTel tHFTel;
  struct TssMsg tTssMsg;
  tWnStateType tRetWnState;
  uint8 ucLocalReifendruck;
//  uint8 ucLocalPatmo;

  tHFTel.ucId = l_ucZomSlot;

  ucLocalReifendruck = GETucReifendruckPD(l_ucZomSlot);
//  ucLocalPatmo = GETucPatmoPD();

  if( (ucLocalReifendruck > 0x04) && (ucLocalReifendruck < 0xFF) )
  {
    tHFTel.ucP = ucLocalReifendruck;
  }
  else{
    tHFTel.ucP = 0;
  }

  tHFTel.scTWE = GETscTemperaturPD( l_ucZomSlot );
  tHFTel.ucLifeTime = 200;

  if( (ucGetReDataPreProcTransModePD() & cRE_AK_TM_EVENT_DP) != 0 )
  {

    tHFTel.ucState = 0x02;
  }
  else if((ucGetReDataPreProcTransModePD() & (cRE_AK_TM_MODE_DRIVE | cRE_AK_TM_MODE_LEARNDRIVE)) != 0 )
  {

    tHFTel.ucState = 0x01;
  }
  else{
    tHFTel.ucState = 0x00;
  }

  tHFTel.ushVehicleSpeed = GETushSpeedFZZ();
  tHFTel.scTa = GETscOutdoorTemperatureFZZ();

  tHFTel.scTref = scChooseTrefTemperature();
  tHFTel.ucKLState = 0x00;

  if( bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE )
  {
    tHFTel.ucKLState |= 0x01;
  }

  if( bGetBitFahrzeugzustandFZZ( cMOTOR_LAEUFT ) == TRUE )
  {
    tHFTel.ucKLState |= 0x02;
  }

  tTssMsg.ucWarning = ucWarnManagerWN( ucComparec, (uint8 *) &tHFTel );

  tTssMsg.ucId = tHFTel.ucId;
  tTssMsg.ucSystemState = tHFTel.ucKLState;

  if( bGetBitBetriebszustandBZ( cZUGEORDNET ) == TRUE )
  {
    tTssMsg.ucPos = l_ucWheelPos;
    tTssMsg.ucSystemState |= (uint8) 0x80;
  }else{
    tTssMsg.ucPos = ucWPUNc;
  }

  (void) ucTSSMsgManagerTM( ucTssMsgOutc, (uint8 *) &tTssMsg );

  tRetWnState = WN_STATE_NO_WARNING;
#ifndef IBTCM_SW_ANPASSUNGEN
  if( GETbPhartWN() )
  {
    tRetWnState = WN_STATE_HW_NOPOS;
  }

  if( GETbPhartVlWN() )
  {
    tRetWnState = WN_STATE_HW_FL;
  }

  if( GETbPhartVrWN() )
  {
    tRetWnState = WN_STATE_HW_FR;
  }

  if( GETbPhartHlWN() )
  {
    tRetWnState = WN_STATE_HW_RL;
  }

  if( GETbPhartHrWN() )
  {
    tRetWnState = WN_STATE_HW_RR;
  }
#endif //IBTCM_SW_ANPASSUNGEN
  return tRetWnState;
}

static void DeleteErrorsOnZugeordnetSM(void)
{

  (void) DeleteCurrentErrorERR( cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS );

  (void) DeleteCurrentErrorERR(cZO_ERR_DETECT_TO0_MANY_SENSORS);
  (void) DeleteCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
  (void) DeleteCurrentErrorERR( cZO_ERR_WS_DEFECT_XX );
  (void) DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_XX );
  (void) DeleteCurrentErrorERR( cZO_ERR_FAILED_TRIES );

  NvM3_PUTucAutolocationFailedCounter(ucDefAutolocationFailedCounterInit);

  if( bGetBitZustandskennungZK( cPOS_CHANGED_VL ) == TRUE )
  {
    (void) ResetWULowLifeTimeCounter(0);
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_DEFECT_FL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_FL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_BATTERY_LOW_FL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_OVERTEMPERATURE_FL );

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & (uint8)(((uint8)(0x10 << cRadPosVL) ^ 0xFF)));
  }

  if( bGetBitZustandskennungZK( cPOS_CHANGED_VR ) == TRUE )
  {
    (void) ResetWULowLifeTimeCounter(1);
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_DEFECT_FR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_FR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_BATTERY_LOW_FR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_OVERTEMPERATURE_FR );

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & (uint8)(((uint8)(0x10 << cRadPosVR) ^ 0xFF)));
  }

  if( bGetBitZustandskennungZK( cPOS_CHANGED_HL ) == TRUE )
  {
    (void) ResetWULowLifeTimeCounter(2);
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_DEFECT_RL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_RL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_BATTERY_LOW_RL );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_OVERTEMPERATURE_RL );

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & (uint8)(((uint8)(0x10 << cRadPosHL) ^ 0xFF)));
  }

  if( bGetBitZustandskennungZK( cPOS_CHANGED_HR ) == TRUE)
  {
    (void) ResetWULowLifeTimeCounter(3);
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_DEFECT_RR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_RR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_BATTERY_LOW_RR );
    (void) DeleteCurrentErrorERR( cZO_ERR_WS_OVERTEMPERATURE_RR );

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & (uint8)(((uint8)(0x10 << cRadPosHR) ^ 0xFF)));
  }
}

void EvZOTimeoutSM(void)
{
  uint8 ucWATOResult;

  ucWATOResult = ucWATO();

  if( (ucWATOResult & 0x0f) == 0 )
  {
   ClearBitBetriebszustandBZ( cTO_MUCH_RE | cZO_TIMEOUT );
  }
  else{

   if((bGetBitBetriebszustandBZ(cEIGENRAD) == FALSE) ||
       ((bGetBitBetriebszustandBZ(cHIST_PRELOAD) == TRUE) && (bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)))
   {

      if( (ucWATOResult & 0x0f) == 0x01 )
      {
        (void) SetCurrentErrorERR( cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS );
        (void) ResetCurrentErrorERR( cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS );
      }

      if( (ucWATOResult & 0x0f) == 0x05 )
      {
        (void) SetCurrentErrorERR( cZO_ERR_DETECT_TO0_MANY_SENSORS );
        (void) ResetCurrentErrorERR( cZO_ERR_DETECT_TO0_MANY_SENSORS );
        SetBitBetriebszustandBZ( cTO_MUCH_RE );
      }

      if( (ucWATOResult & 0x0f) == 0x09 )
      {

        (void) SetCurrentErrorERR( cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS );
        (void) ResetCurrentErrorERR( cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS );
      }
   }
   else{
      if(bGetBitBetriebszustandBZ(cZUGEORDNET) == FALSE)
      {

#ifdef DETECT_SYMC_WALLOC_DTC

        if( (ucWATOResult & 0x0f) == 0x02 ) //-> ZO error
        {
          (void)SetCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
          (void)ResetCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
        }
        //else if( ((ucWATOResult & 0x0f) == 0x03 )|| //-> direction detection error
        //         ((ucWATOResult & 0x0f) == 0x06 )  )//-> WP consistency error
        //{
          //(void) SetCurrentErrorERR( cZO_ERR_SIDE_LOCATION );
        //}
        else if( (ucWATOResult & 0x0f) == 0x04 )//-> axis detection error
        {
          uint8 ucAutolocationFailedCounter = NvM3_GETucAutolocationFailedCounter();

          if(ucAutolocationFailedCounter > 0U)
          {
            ucAutolocationFailedCounter--;
            NvM3_PUTucAutolocationFailedCounter(ucAutolocationFailedCounter);
          }
          else{
            (void) SetCurrentErrorERR(cZO_ERR_FAILED_TRIES);
            (void) ResetCurrentErrorERR(cZO_ERR_FAILED_TRIES);
          }

          (void) SetCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
          (void) ResetCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
        }
        else{

        }
#else
        if( (ucWATOResult & 0x0f) == 0x02 )
        {
          (void) SetCurrentErrorERR( cZO_ERR_AXIS_LOCATION );
        }
#endif
      }
   }
    SetBitBetriebszustandBZ( cZO_TIMEOUT );
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void SetGlobalSystemStateSM(void)
{
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef BUILD_WITH_UNUSED_FUNCTION
boolean SgDiagGetOutOfVolt(void)
{
#ifdef IBTCM_SW_ANPASSUNGEN

  return (FALSE);
#else
  return (GETbVBatLowDtcDI());
#endif
}
#endif

static void SensorErrorDiagSM( boolean bHwDefect, uint8 ucZomPos )
{
  if( bHwDefect == TRUE )
  {
   CntWUDefectRD( ucZomPos );
  }
  else{
    ResetWUDefectRD( ucZomPos );
  }
}

static void SensorTemperatureDiagSM( boolean bReTempExceed, uint8 ucZomPos )
{
  ucWUMode3DiagActive |= (uint8)(0x01 << ucZomPos);

  if( bReTempExceed == TRUE )
  {
   CntWUHighTempRD( ucZomPos );
  }
  else{
    ResetWUHighTempRD( ucZomPos );
  }
}

static void SensorLowLifeTimeDiagSM( boolean bReLowLifeTime, uint8 ucZomPos )
{
  if( bReLowLifeTime == TRUE )
  {
   CntWULowLifeTimeRD( ucZomPos );
  }
  else{
    ResetWULowLifeTimeRD( ucZomPos );
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void EvDiagEvalSM(void)
{
  (void) EvalVoltDiagSM();
  (void) EvalECUDiagSM();
  (void) EvalWUDiagSM();
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 EvalVoltDiagSM(void)
{
#ifdef IBTCM_SW_ANPASSUNGEN

  return(FALSE);
#else
  const uint8 cVBatHighTime = 60;
  const uint8 cVBatLowTime = 60;
  const uint8 cStopVDiagTime = 5;

  STATIC uint8 ucStopVDiagCt = 0x00;
  uint8 ucEvalResult = FALSE;
  uint16 ushHelp;

  if( GETbStopVDiagDI() == FALSE )
  {
      ucStopVDiagCt = 0x00;

      if(GETbVBatHighDI() == TRUE)
      {
        if(ucVBatHighErrorTime == 0x00)
        {
          ucVBatHighErrorTime = cVBatHighTime;
        }
        else{

          if(GetAlarmAlDiagEvalOS(&ushHelp) == FALSE)
          {
            ucVBatHighErrorTime--;
          }
        }

        if(ucVBatHighErrorTime == 0x00)
        {

          SetCurrentErrorERR(cKl30Ueberspannung);
        }
      }
      else{
        ucVBatHighErrorTime = cVBatHighTime;

        ResetCurrentErrorERR(cKl30Ueberspannung);
      }

      if(GETbVBatLowDI() == TRUE)
      {
        if(ucVBatLowErrorTime == 0x00)
        {
          ucVBatLowErrorTime = cVBatLowTime;
        }
        else{

          if(GetAlarmAlDiagEvalOS(&ushHelp) == FALSE)
          {
            ucVBatLowErrorTime--;
          }
        }

        if(ucVBatLowErrorTime == 0x00)
        {

          SetCurrentErrorERR(cKl30Unterspannung);
        }
      }
      else{

        ucVBatLowErrorTime = cVBatLowTime;

        ResetCurrentErrorERR(cKl30Unterspannung);
      }
  }
  else{

   if(GETbVBatLowDI() == FALSE)
   {
      if(GetAlarmAlDiagEvalOS(&ushHelp) == FALSE)
      {

        if(ucStopVDiagCt < cStopVDiagTime)
        {
          ucStopVDiagCt++;
        }
        else{

          SetCurrentErrorERR(cBetriebsspannungDefekt);
        }
      }
   }
  }

  ucEvalResult |= GETbVBatHighDI();
  ucEvalResult |= GETbVBatLowDI();
  ucEvalResult |= GETbStopVDiagDI();
  if(ucEvalResult == TRUE)
  {
   CancelAlarmAlDiagEvalOS();
    SetRelAlarmAlDiagEvalOS(1,0);
   ucEvalResult = FALSE;
  }
  else{
   CancelAlarmAlDiagEvalOS();
  }
  return(ucEvalResult);
#endif
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 EvalECUDiagSM(void)
{
#ifdef IBTCM_SW_ANPASSUNGEN

  return(FALSE);
#else
  uint8 ucEvalResult = 0;

  if(GETbRAMErrorDI() == TRUE)
  {
    SetCurrentErrorERR(cSpeicherRamSP);
  }

  if(GETbROMErrorDI() == TRUE)
  {
    SetCurrentErrorERR(cRomFehlerSP);
  }

  if(GETbHfRecDemErrDI() == TRUE)
  {

  }

  if(GETbHfRecRssiErrDI() == TRUE)
  {

  }

  return(ucEvalResult);
#endif
}

#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 EvalWUDiagSM(void)
{
  uint8 ucEvalResult = 0;
  uint8 ucErrCount;

  ucErrCount = EvalWUDefektSM();

  if(ucErrCount == 0)
  {
   PUTbWUDefectDI(FALSE);

    DeleteCurrentErrorERR(ucWUDefectERRc[cAnzRad]);

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & 0x0F);
  }

  ucErrCount = EvalWUHighTempSM();

  if(ucErrCount == 0)
  {

    DeleteCurrentErrorERR(ucWUTemperatureERRc[cAnzRad]);

   PUTucReHeatUpStatusEE(GETucReHeatUpStatusEE() & (uint8)0xF0);

   CancelAlarmAlMinuteCntOS();

   ucMinutenCnt = 0;
  }

  ucErrCount = EvalWULowLifeTimeSM();

  if(ucErrCount == 0)
  {

    DeleteCurrentErrorERR(ucWULowLifeTimeERRc[cAnzRad]);
  }
#ifdef BUILD_WITH_UNUSED_FUNCTION
  if(EOL_GetEOLRoutineActive() == FALSE)
  {
#endif

  ucErrCount = EvalWUNoRecSM();

  if(ucErrCount == 0)
  {
   PUTbWUFailedDI(FALSE);

   if( GETbStoersenderZeit() == FALSE )
   {
      PUTbHfIntLatchEE(FALSE);
   }

    DeleteCurrentErrorERR(ucWUFailERRc[cAnzRad]);

   PUTucReErrorStatusEE(GETucReErrorStatusEE() & (uint8)0xF0);
  }
#ifdef BUILD_WITH_UNUSED_FUNCTION
  }
#endif
  return(ucEvalResult);
}
#endif

void EvalWUDefektSM( uint8 u8ZOMPosition )
{
  uint8 l_ucWheelPos;
  uint8 l_u8ErrorStatusFromEE;
  const uint8 cWUDefectLimit = 5;

  l_u8ErrorStatusFromEE = GETucReErrorStatusEE();
  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
  {
    l_ucWheelPos = GETucRadpositionPD(u8ZOMPosition);
  }
  else{
    l_ucWheelPos = cRadPosRR;
  }

  if(GetWUDefectRD(u8ZOMPosition) >= cWUDefectLimit)
  {
    SetCurrentErrorERR(ucWUDefectERRc[l_ucWheelPos]);
    ResetCurrentErrorERR(ucWUDefectERRc[l_ucWheelPos]);
   if(l_ucWheelPos < cAnzRad)
   {

      l_u8ErrorStatusFromEE |= (uint8)((uint8)(0x10 << l_ucWheelPos) & 0xF0);
   }
   else{

      l_u8ErrorStatusFromEE |= (uint8)0xF0;

      DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosVL]);
      DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosVR]);
      DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosHL]);
      DeleteCurrentErrorERR(ucWUDefectERRc[cRadPosHR]);
   }
  }
  else{
   if(GetWUDefectRD(u8ZOMPosition) == 0x00)
   {

      if(l_ucWheelPos < cAnzRad)
      {
        DeleteCurrentErrorERR(ucWUDefectERRc[l_ucWheelPos]);

        l_u8ErrorStatusFromEE &= (uint8)(((uint8)(0x10 << l_ucWheelPos) ^ 0xFF));
      }
      else{
      }

      u8WUDefectErrStatus |= (uint8)(0x01 << u8ZOMPosition);
   }
  }

  if(u8WUDefectErrStatus == 0x0F)
  {
    //PUTbWUDefectDI(FALSE);

    DeleteCurrentErrorERR(ucWUDefectERRc[cAnzRad]);

    l_u8ErrorStatusFromEE &= 0x0F;
   u8WUDefectErrStatus = 0;
  }
  PUTucReErrorStatusEE(l_u8ErrorStatusFromEE);
}

void EvalWUNoRecSM(uint8 ucIx)
{
  uint8 ucErrCount = cAnzRad;
  uint8 l_ucWheelPos;
  boolean bSensorMissingErrorAllowed = FALSE;
  boolean bInvalidSpeedErrorToBeSet = FALSE;
  uint16 ushThresholdForContinuousSpeedStatusIn200ms = 0;
  uint8 ucSetUnspecificPositionMissing = 0;
  boolean l_bSensorStillMissFlag;
  uint8 l_u8ErrorStatusFromEE;
  boolean bAutoLearnStopped;
  uint8 ucAutoLearnDTCState= 0;
  //uint16 ushMaxSensorMissTimeValue = 0;

  uint16 ushFolgeAusfallCount;
  uint8 ucWuDefect;
  uint8 ucEolRoutineActive;
  l_u8ErrorStatusFromEE = GETucReErrorStatusEE();

  ushThresholdForContinuousSpeedStatusIn200ms = cEvalSpeedValueMissingThreshold;//SM_GetThresholdValueIn200msForContinuousSpeedStatus(eEvalTimeMode);

  ucErrCount = ucGetMissingErrorCnt();

  bAutoLearnStopped = (bGetBitBetriebszustandBZ(cZO_TIMEOUT | cER_FINISH | cER_LEARNING) != 0);

  if((FALSE == bSpeedSubstituteValInUseStatus) &&(ushTimerIn200MsForContinuousSpeedStatus >= ushThresholdForContinuousSpeedStatusIn200ms))
  {

   bSensorMissingErrorAllowed = TRUE;
  }
  else{

  }

  ucAutoLearnDTCState = DTC_GetActiveStatusOfDTC(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS);

  ucSetUnspecificPositionMissing = ucCheckPotentialErInZom();

  if(GETbStatisticActiveSTATISTICS(ucIx) == TRUE)
  {
   if((bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE) && (ucSetUnspecificPositionMissing == FALSE))
   {
      l_ucWheelPos = GETucRadpositionPD(ucIx);
   }
   else{
      l_ucWheelPos = cRadPosRR;
   }

   if(l_ucWheelPos > cAnzRad)
   {
      l_ucWheelPos = cAnzRad;
   }

   if(GETusFolgeAusfallCntSTATISTICS(ucIx) >= GETusMaxFolgeAusfallEE())
   {
      if(TRUE == bSensorMissingErrorAllowed)
      {
        if(bAutoLearnStopped == TRUE)
        {
          SetCurrentErrorERR(ucWUFailERRc[l_ucWheelPos]);
          ResetCurrentErrorERR(ucWUFailERRc[l_ucWheelPos]);
        }
      }
      else{

        bInvalidSpeedErrorToBeSet = TRUE;
      }

      if(l_ucWheelPos < cAnzRad)
      {

        l_u8ErrorStatusFromEE |= (uint8)((uint8)(0x01 << l_ucWheelPos) & 0x0F);
      }
      else{

        l_u8ErrorStatusFromEE |= 0x0F;

        DeleteCurrentErrorERR(ucWUFailERRc[cRadPosVL]);
        DeleteCurrentErrorERR(ucWUFailERRc[cRadPosVR]);
        DeleteCurrentErrorERR(ucWUFailERRc[cRadPosHL]);
        DeleteCurrentErrorERR(ucWUFailERRc[cRadPosHR]);
      }
   }
   else{
      //if((GETusFolgeAusfallCntSTATISTICS(ucIx) <= MAX_CNT_VALUE_TO_RESET_ERR) && (GetWUDefectRD(ucIx) == 0x00))

      ushFolgeAusfallCount = GETusFolgeAusfallCntSTATISTICS(ucIx);
      ucWuDefect = GetWUDefectRD(ucIx);
      ucEolRoutineActive = EOL_GetEOLRoutineActive();
      if((ushFolgeAusfallCount <= MAX_CNT_VALUE_TO_RESET_ERR)
       && (ucWuDefect == 0x00)
       && (ucEolRoutineActive == EOL_ROUTINE_INACTIVE)
      )
      {

        if((l_ucWheelPos < cAnzRad) && (ucAutoLearnDTCState == 0)) //reset position specific error only if "AL not possible" DTC is not set
        {
          DeleteCurrentErrorERR(ucWUFailERRc[l_ucWheelPos]);

          l_u8ErrorStatusFromEE &= (uint8)((uint8)(0x01 << l_ucWheelPos) ^ 0xFF);

          ucErrCount--; //ucErrCount can contain here only values between [1...4]
        }
        else{
          ucErrCount--; //ucErrCount can contain here only values between [1...4]
        }
        PutMissingErrCnt(ucErrCount);  //update global variable MissingErrCnt
      }
   }
  }

  if(ucErrCount == 0)
  {
    //PUTbWUFailedDI(FALSE);
    l_bSensorStillMissFlag = bGetPossibleRfInterf();

   if((GETbStoersenderZeit() == FALSE) && (l_bSensorStillMissFlag == FALSE))
   {
      PUTbHfIntLatchEE(FALSE);
   }

   if((ucAutoLearnDTCState == 0))
   {
      DeleteCurrentErrorERR(ucWUFailERRc[cAnzRad]);

    l_u8ErrorStatusFromEE &= (uint8)0xF0;
   }
   else{
      //do nothing
   }
  }

  PUTucReErrorStatusEE(l_u8ErrorStatusFromEE);

  if(TRUE == bInvalidSpeedErrorToBeSet)
  {

   if((FALSE != bSpeedSubstituteValInUseStatus) &&(ushTimerIn200MsForContinuousSpeedStatus >= ushThresholdForContinuousSpeedStatusIn200ms))
   {
      SetCurrentErrorERR(cCANSpeedSignalInvalidError);
      ResetCurrentErrorERR(cCANSpeedSignalInvalidError);
   }
   else{

   }
  }
  else{

  }

  if(FALSE == bSpeedSubstituteValInUseStatus)
  {
    DeleteCurrentErrorERR(cCANSpeedSignalInvalidError);
  }
  else{

  }
}

void EvalWUHighTempSM(void)
{
  uint8 ucErrCount = cAnzRad;
  uint8 i;
  uint8 l_ucWheelPos;
  uint8 l_u8OverTempStatusEE;
  uint16 ushHelp;

  const uint8 cWUHighTempLimit = 2;
  const uint8 cOverTempErrorTimeLimit = 9;

  l_u8OverTempStatusEE = GETucReHeatUpStatusEE();
  for(i = 0; i < cAnzRad; i++)
  {
   if((ucWUMode3DiagActive & (uint8)(0x01 << i)) == (uint8)(0x01 << i))
   {
      if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
      {
        l_ucWheelPos = GETucRadpositionPD(i);
      }
      else{
        l_ucWheelPos = cRadPosRR;
      }

      if(GetWUHighTempRD(i) >= cWUHighTempLimit)
      {

        if( GetAlarmAlMinuteCntOS( &ushHelp ) == FALSE )
        {
          CancelAlarmAlMinuteCntOS();
          SetRelAlarmAlMinuteCntOS(60,60);
        }

        if( ucMinutenCnt >= cOverTempErrorTimeLimit )
        {

          SetCurrentErrorERR(ucWUTemperatureERRc[l_ucWheelPos]);
          ResetCurrentErrorERR(ucWUTemperatureERRc[l_ucWheelPos]);
          if(l_ucWheelPos < cAnzRad)
          {

            l_u8OverTempStatusEE |= (uint8)((uint8)(0x01 << l_ucWheelPos) & 0x0F);
          }
          else{

            l_u8OverTempStatusEE |= (uint8)0x0F;

            DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosVL]);
            DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosVR]);
            DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosHL]);
            DeleteCurrentErrorERR(ucWUTemperatureERRc[cRadPosHR]);
          }
        }
      }
      else{
        if(GetWUHighTempRD(i) == 0x00)
        {

          if(l_ucWheelPos < cAnzRad)
          {
            DeleteCurrentErrorERR(ucWUTemperatureERRc[l_ucWheelPos]);

            l_u8OverTempStatusEE &= (uint8)(((uint8)(0x01 << l_ucWheelPos) ^ 0xFF));
          }
          else{
          }
          ucErrCount--;
        }
      }
   }
  }

  if(ucErrCount == 0)
  {

    DeleteCurrentErrorERR(ucWUTemperatureERRc[cAnzRad]);

    l_u8OverTempStatusEE &= (uint8)0xF0;

   CancelAlarmAlMinuteCntOS();

   ucMinutenCnt = 0;
  }

  PUTucReHeatUpStatusEE(l_u8OverTempStatusEE);
}

void EvalWULowLifeTimeSM( uint8 u8ZomPos )
{
  uint8 l_ucWheelPos;

  const uint8 cWULowLifeTimeCount = 10;

  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
  {
    l_ucWheelPos = GETucRadpositionPD(u8ZomPos);
  }
  else{
    l_ucWheelPos = cRadPosRR;
  }

  if(GetWULowLifeTimeRD(u8ZomPos) >= cWULowLifeTimeCount)
  {

    SetCurrentErrorERR(ucWULowLifeTimeERRc[l_ucWheelPos]);
    ResetCurrentErrorERR(ucWULowLifeTimeERRc[l_ucWheelPos]);
  }
  else{
   if(GetWULowLifeTimeRD(u8ZomPos) == 0x00)
   {

      DeleteCurrentErrorERR(ucWULowLifeTimeERRc[l_ucWheelPos]);
   }
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void EvBandModeServiceSM(void)
{
#ifdef IBTCM_SW_ANPASSUNGEN

#else
  (void)EOL_CheckPeriodicLearnRoutineStatus();
#endif
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void EvMinuteCntSM(void)
{
  if( ucMinutenCnt < (uint8) 255 )
  {
   ucMinutenCnt++;
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void SetResetWarnPressRefSM (void){
  uint8 aucWarnAtId[4];
  uint8 l_ucZomSlot;

  (void)GetWarnOfIdUSWIF(&aucWarnAtId[0]);

  for(l_ucZomSlot = 0; l_ucZomSlot < cAnzRad; l_ucZomSlot++)
  {

   if(aucWarnAtId[l_ucZomSlot] != 0x00)
   {
      PUTucResetWarnPressRefEE(l_ucZomSlot, GETucReifendruckPD ( l_ucZomSlot ));
   }
  }
}
#endif //BUILD_WITH_UNUSED_FUNCTION

static void InitResetWarnPressRefSM(const uint8 l_ucZomSlot, const uint8 ucActPress)
{
  uint8 aucWarnAtId[4];

  (void)GetWarnOfIdUSWIF(&aucWarnAtId[0]);

  if(l_ucZomSlot < cAnzRad)
  {

   if(aucWarnAtId[l_ucZomSlot] == 0x00)
   {

      if(GETucResetWarnPressRefEE(l_ucZomSlot) != cInvalidREpressure)
      {
        PUTucResetWarnPressRefEE(l_ucZomSlot, cInvalidREpressure);
      }
   }
   else{

      if(GETucResetWarnPressRefEE(l_ucZomSlot) == cInvalidREpressure)
      {
        PUTucResetWarnPressRefEE(l_ucZomSlot, ucActPress);
      }
   }
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint8 CheckWUReceptionSM(void){
  uint8 i,j;
  uint8 ucCtWUFail = 0x00;
  boolean bIdKnown = FALSE;

  for(i = 0; i < cSumWE; i++)
  {
   for(j = 0; j < cAnzRad; j++)
   {

      if(ulGetZOMID(i) == ulGetID(j))
      {
        bIdKnown = TRUE;
      }
   }
  }

  if(bIdKnown == FALSE)
  {
   for(i = 0; i < cSumWE; i++)
   {
      if(ucGetProbeCt(i) <= 2)
      {
        ucCtWUFail++;
      }
   }
  }
  return (ucCtWUFail);
}
#endif

static void SaveReDataInSlotSM( uint8 ucParamZomSlot )
{
  PUTucReifendruckPD(ucGetReDataPreProcPressurePD(), ucParamZomSlot);
  PUTscTemperaturPD(scGetReDataPreProcTemperaturePD(), ucParamZomSlot);

  PUTucRestlebensdauerPD( ucGetReDataPreProcRemainingLifeTimePD(), ucParamZomSlot );

  PUTucTransModePD( ucGetReDataPreProcTransModePD(), ucParamZomSlot );

  PUTucTelTypePD( ucGetReDataTelTypePD(), ucParamZomSlot );

#ifdef G_USE_ROTATION_DIRECTION

  PUTucWheelDirPD( ucGetReDataPreProcWheelDirPD(), ucParamZomSlot );
#endif //G_USE_ROTATION_DIRECTION

  PUTushSensorDefectPD( CheckSensorDefectSM(ucParamZomSlot), ucParamZomSlot );

  PUTucRSSIsumPD( ucGetReDataRssiAvgPD(), ucParamZomSlot );
}

static uint16 CheckSensorDefectSM( uint8 ucParamZomSlot )
{
  uint16 ushSensorDefect = GETushSensorDefectPD(ucParamZomSlot);
  uint16 ushHelp;

  if((ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_PRES_NOT_RECEIVED ) == 0x0000)
  {
   ushHelp = (ushSensorDefect & (RE_AK_SF_MOTION_NOT_RECEIVED | RE_AK_SF_TEMP_NOT_RECEIVED |
                                  RE_AK_SF_RS_RL_FAIL | RE_AK_SF_TEMP_FAIL));
   ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_PRES_FAIL );
   ushSensorDefect |= ushHelp;
  }
  else{
   ushSensorDefect |= RE_AK_SF_PRES_NOT_RECEIVED;
  }

  if((ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_TEMP_NOT_RECEIVED ) == 0x0000)
  {
   ushHelp = (ushSensorDefect & (RE_AK_SF_MOTION_NOT_RECEIVED | RE_AK_SF_PRES_NOT_RECEIVED |
                                  RE_AK_SF_RS_RL_FAIL | RE_AK_SF_PRES_FAIL));
   ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() &  RE_AK_SF_TEMP_FAIL);
   ushSensorDefect |= ushHelp;
  }
  else{
   ushSensorDefect |= RE_AK_SF_TEMP_NOT_RECEIVED;
  }

  if((ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_MOTION_NOT_RECEIVED) == 0x0000)
  {
   ushHelp = (ushSensorDefect & (RE_AK_SF_TEMP_NOT_RECEIVED | RE_AK_SF_PRES_NOT_RECEIVED |
                                  RE_AK_SF_PRES_FAIL | RE_AK_SF_TEMP_FAIL));
   ushSensorDefect = (ushGetReDataPreProcSensorDefectPD() & RE_AK_SF_RS_RL_FAIL);
   ushSensorDefect |= ushHelp;
  }
  else{
   ushSensorDefect |= RE_AK_SF_MOTION_NOT_RECEIVED;
  }

  return(ushSensorDefect);
}

#ifdef G_USE_PART_ER
static uint8 CheckPartErStateSM(void){
  uint8 ucHelp;
  uint8 ucHistCol;
  uint8 ucDelFlag = 0x0F;
  uint16 usLocalMaxMissedCnt = 0;

  if(ushGetBetriebszustandBZ( cTEILEIGENRAD | cZO_TIMEOUT | cWA_FINISH | cER_LEARNING) == cER_LEARNING)
  {
   ucDelFlag = 0x00;

   ucHelp = GETucPartErTimerFactorEE();
   ucHelp = CheckPartErCriteriaWA(ucHelp);

   if(ucHelp != 0x00)
   {

      InitSTATISTICS();

      SetChangedBit4WP(cAnzRad);

      SetBitBetriebszustandBZ(cTEILEIGENRAD);
      ClearBitBetriebszustandBZ(cEIGENRAD);
      ClearBitBetriebszustandBZ(cZUGEORDNET);

      for(ucHistCol = 0x00; ucHistCol < cAnzRad; ucHistCol++)
      {

        if(ulGetID(ucHistCol) == cInitHistID)
        {
          usLocalMaxMissedCnt = GETusMaxFolgeAusfallEE();
          if(GETusFolgeAusfallCntSTATISTICS(ucHistCol) < usLocalMaxMissedCnt)
          {
            PUTusFolgeAusfallCntSTATISTICS(usLocalMaxMissedCnt, ucHistCol);
          }

          if(ushTimerIn200MsForContinuousSpeedStatus < SM_GetThresholdValueIn200msForContinuousSpeedStatus(E_NORMAL_TIME_EVAL_MODE))
          {
            ushTimerIn200MsForContinuousSpeedStatus = SM_GetThresholdValueIn200msForContinuousSpeedStatus(E_NORMAL_TIME_EVAL_MODE);
          }
          else{

          }

          ucDelFlag |= (uint8)(0x01 << ucHistCol);
        }
        else{
          PreloadFromAddZomDataSM(ucHistCol);
        }
      }
   }
   else{
      for(ucHistCol = 0x00; ucHistCol < cAnzRad; ucHistCol++)
      {

        if(GETusFolgeAusfallCntSTATISTICS(ucHistCol) >= (GETucPartErTimerFactorEE() - 2))
        {
          usLocalMaxMissedCnt = GETusMaxFolgeAusfallEE();
          if(GETusFolgeAusfallCntSTATISTICS(ucHistCol) < usLocalMaxMissedCnt)
          {
            PUTusFolgeAusfallCntSTATISTICS(usLocalMaxMissedCnt, ucHistCol);
          }

          if(ushTimerIn200MsForContinuousSpeedStatus >= (SM_GetThresholdValueIn200msForContinuousSpeedStatus(E_PART_TIME_EVAL_MODE) - 660))
          {
            if(ushTimerIn200MsForContinuousSpeedStatus < SM_GetThresholdValueIn200msForContinuousSpeedStatus(E_NORMAL_TIME_EVAL_MODE))
            {
                ushTimerIn200MsForContinuousSpeedStatus = SM_GetThresholdValueIn200msForContinuousSpeedStatus(E_NORMAL_TIME_EVAL_MODE);
            }
            else{

            }
          }
          else{

          }

          ucDelFlag |= (uint8)(0x01 << ucHistCol);
        }
        else{
          PreloadFromAddZomDataSM(ucHistCol);
        }
      }
   }

   for(ucHistCol = 0x00; ucHistCol < cAnzRad; ucHistCol++)
   {

      if((ucDelFlag & (uint8)(0x01 << ucHistCol)) == (0x01 << ucHistCol))
      {
        ClearReDataInSlotPD(ucHistCol);
        (void)ResetWarnVectorUSWIF(ucHistCol);
        (void)ClearWarnOfIdUSWIF( ucHistCol );
      }
   }

    (void)EvalWUNoRecSM();

   if(bGetBitBetriebszustandBZ(cTEILEIGENRAD) == TRUE)
   {

      Check4FastWarnOutputSM(cAnzRad);
   }
  }
  return (ucDelFlag);
}
#endif //G_USE_PART_ER

#ifdef BUILD_WITH_UNUSED_FUNCTION

static void SetTransportModeSM( const boolean bMode )
{
#ifdef IBTCM_SW_ANPASSUNGEN

#else
  if( bMode == TRUE)
  {
   if( GETbTransportModeEE() == FALSE )
   {
      PUTbTransportModeEE( TRUE );

      SetWAModeFix();
      (void)WAInit();

   }
  }
  else{
   if( GETbTransportModeEE() == TRUE)
   {
      PUTbTransportModeEE( FALSE );

      InitSTATISTICS();

      if(EOL_GetEOLRoutineActive() == FALSE)
      {

        SetWAModeLearn();

        (void)WAInit();
      }
   }
  }
#endif
}
#endif

STATIC void Check4FastWarnOutputSM (uint8 ignoreCol)
{
  uint8 ucHistCol;
  uint8 ucRadPosition;

  for(ucHistCol = 0; ucHistCol < cAnzRad; ucHistCol++)
  {
   if(ucHistCol != ignoreCol)
   {

      if(ulGetID(ucHistCol) != cInitHistID)
      {
        if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
        {
          ucRadPosition = GETucRadpositionPD(ucHistCol);
        }
        else{
          ucRadPosition = cRadPosRR;
        }

        (void)tCheckForFlatTyreSM(ucHistCol, ucRadPosition);
      }
   }
  }
}

void PunctureWarningReset(void){
  uint8 i = 0;
  uint8 ucCnt = 0;

  for(i = 0; i < ucSumWEc; i++)
  {
   if(ucGetWarnBitWN(i, ucDHWIxc) == 1)
   {

      ClearWarnBitWN(i, ucDHWIxc);
      ResetM1Pressure(i);
      ucCnt++;
   }
  }
  if(ucCnt > 0)
  {
   Check4FastWarnOutputSM(cAnzRad); //check all IDs for warnings, to delete the puncture warning from ucTyreWarning[]
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void Check4ImmediateWarnOutputSM (uint8 l_HistCol, uint8 l_WheelPos)
{
  if(l_WheelPos <= cRadPosRR)
  {
    (void)tCheckForFlatTyreSM(l_HistCol, l_WheelPos);
    (void)tCheckForFlatTyreSM(l_HistCol, l_WheelPos);
  }
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void InformWarnHandlerSM(boolean ResetWarn, const uint8 PressFA, const uint8 PressRA)
{
  uint8 ucHelp = 0x00;
  uint8 ucHistCol;
  uint8 ucRadPosition;
//uint8 aucDiagService[6];
//uint16 ushHelp;
  uint8 ucPWarnMin;

  if( ResetWarn == TRUE )
  {

    (void)ResetWarnVectorUSWIF(cAnzRad);

    (void)ClearWarnOfIdUSWIF( cAnzRad );
  }

  ucPWarnMin = ( GETucVarCodMinPressThresEE() );
  (void) ucWAlgoPrePara( ucPWarnMin, GETucPSollMinVaEE(), GETucPSollMinHaEE());

  for( ucHistCol = 0; ucHistCol < cAnzRad; ucHistCol++ )
  {
     if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
     {
        ucRadPosition = GETucRadpositionPD(ucHistCol);
     }
     else{
        ucRadPosition = cRadPosRR;
     }

     if(ucRadPosition < cRadPosHL)
     {

        ucHelp = PressFA;

     }
     else{
        if(ucRadPosition < cRadPosRR)
        {

          ucHelp = PressRA;
        }
        else{

           ucHelp = PressFA;
        }
     }

     (void)CfgReInitSingleUSWIF( ucHelp, 20, ucHistCol );

  }
}

static void InitAddZomDataSM (void){
  uint8 i;

  for(i = 0; i < cSumWE; i++)
  {
    tAddZomData[i].ulID = 0x0000;
    tAddZomData[i].ucPressure = cInvalidREpressure;
    tAddZomData[i].scTemperature = cInvalidREtemperature;
  }
}

static void SetAddZomDataSM (void){
  uint8 i;
  uint8 ucZomCol = cSumWE;

  for(i = 0; i < cSumWE; i++)
  {
   if(ulGetZOMID(i) == ulGetReDataPreProcIdPD())
   {
      ucZomCol = i;
   }
  }

  if(ucZomCol < cSumWE)
  {
    tAddZomData[ucZomCol].ulID = ulGetReDataPreProcIdPD();

    tAddZomData[ucZomCol].ucPressure = ucGetReDataPreProcPressurePD();

    tAddZomData[ucZomCol].scTemperature = scGetReDataPreProcTemperaturePD();
  }
}

static void PreloadFromAddZomDataSM (uint8 ucHistCol)
{
  uint8 i;

  for(i = 0; i < cSumWE; i++)
  {
   if(tAddZomData[i].ulID == ulGetID(ucHistCol))
   {
      PUTucReifendruckPD(tAddZomData[i].ucPressure, ucHistCol);
      PUTscTemperaturPD(tAddZomData[i].scTemperature, ucHistCol);
   }
  }
}

boolean bCheckSuppIdentAndTelTypeSM(uint8 SuppIdent, uint8 TelType)
{
  boolean bHelp = FALSE;

  if(SuppIdent != 0x02)
  {

   if((GETushSuppIdentFilterEE() & (uint16)(0x01 << (SuppIdent & 0x0f))) == (uint16)(0x01 << (SuppIdent & 0x0f)))
   {

      if((TelType == cTelTypeAK35def) || (TelType == 0x20) || (TelType == cTelTypeStandstill))
      {
        bHelp = TRUE;
      }
   }
  }
  else{

   bHelp = TRUE;
  }
  return (bHelp);
}

void SM_ResetStatusForSpeedValueInUse(void){
  bSpeedSubstituteValInUseStatus = TRUE;
  ushTimerIn200MsForContinuousSpeedStatus = 0;
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

static uint16 SM_GetThresholdValueIn200msForContinuousSpeedStatus(ENUM_EVALUATION_TIME_MODE_TYPE eEvalTimeMode)
{
  uint16 ushReturnThresholdValIn200ms = 0;

  if(E_PART_TIME_EVAL_MODE == eEvalTimeMode)
  {

   ushReturnThresholdValIn200ms = (uint16)0x05DC;
  }
  else{

   ushReturnThresholdValIn200ms = (uint16)0x0A8C;
  }

  return ushReturnThresholdValIn200ms;
}
#endif //BUILD_WITH_UNUSED_FUNCTION

extern void SM_TimerProcessForSpeedValueInUseStatus(void){
  boolean bNewSpeedSubstituteValInUseStatus = FALSE;

#ifdef IBTCM_SW_ANPASSUNGEN
  if(TRUE == ReceiveGetVehicleSpeedValidity())
  {
   bNewSpeedSubstituteValInUseStatus = FALSE;
  }
  else{
   bNewSpeedSubstituteValInUseStatus = TRUE;
  }
#else

  bNewSpeedSubstituteValInUseStatus = ReceiveGetSigSubstituteValInUseStatus(VEHSPEED_SIGHDL);
#endif

  if(bSpeedSubstituteValInUseStatus != bNewSpeedSubstituteValInUseStatus)
  {

   bSpeedSubstituteValInUseStatus = bNewSpeedSubstituteValInUseStatus;

   ushTimerIn200MsForContinuousSpeedStatus = 0;
  }
  else{

   if(ushTimerIn200MsForContinuousSpeedStatus < 0xFFFF)
   {
      ushTimerIn200MsForContinuousSpeedStatus++;
   }
   else{

   }
  }
}

static void OperateTrefTemperature(void){
  uint16 ushVehSpeed = 0;

  if( ush5minTimer1 >= TIME_5MIN_OVER )
  {

   if( ush5minTimer1 != TIME_5MIN_DONE )
   {

      if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE)
      {
        if(bCheckActPresEnoughPplacardSM() == TRUE)
        {

          ucTrefControl = ENABLE_ADAPT;
        }
        else{

          ucTrefControl = NO_ADAPT;
        }
        ush5minTimer1 = TIME_5MIN_DONE;
      }
   }
  }
  else{
    (void) ReceiveGetVehicleSpeed( &ushVehSpeed );

   if( ushVehSpeed >= SPEED_10KMH )
   {
      ush5minTimer1++;
   }
  }
}

static sint8 scChooseTrefTemperature(void){
  uint16 ushVehSpeed;
  sint8 scRet;

  ushVehSpeed = 0;

  if( ucTrefControl == LOCKED )
  {
   scRet = scLockEuFbyTref;
  }
  else{
   if( ucTrefControl == NO_ADAPT )
   {
      scRet = GETscAdaptedTrefEE();
   }
   else{
      if( ucTrefControl == ENABLE_ADAPT )
      {
        (void) ReceiveGetVehicleSpeed( &ushVehSpeed );

        if( ushVehSpeed >= SPEED_10KMH )
        {

          (void) ReceiveGetTrefTemperature( &scTrefRxTemp );
        }
        scRet = scTrefRxTemp;
      }
      else{

        scRet = RECEIVE_TEMP20_SUBSTVAL;
      }
   }
  }
  return scRet;
}

static boolean bCheckActPresEnoughPplacardSM(void){
  uint8 i;
  uint16 ushCalcLimit;
  boolean bRet = FALSE;
  uint8 ucLocalReifendruck;

  ushCalcLimit = (uint16) (0xFF & GETucVarCodPlacardPressEE());
  ushCalcLimit *= 95;
  ushCalcLimit += 50;
  ushCalcLimit /=100;

  for(i = 0; i < cAnzRad; i++)
  {
   ucLocalReifendruck = GETucReifendruckPD(i);
   if( (ucLocalReifendruck >= ushCalcLimit) &&
         (ucLocalReifendruck < 0xFE)             )
   {

      bRet = TRUE;
   }
   else{
      bRet = FALSE;
      break;
   }
  }

  return bRet;
}

#ifdef IBTCM_SW_ANPASSUNGEN
#ifdef FILTER_SYMC_CAN_MSGS

void CheckStateOf_ER_PressureRx(void){
  uint8   l_ucLoop;
  uint8   l_ucRadPos;
  uint8   l_ucTemp;
  uint8   l_ucPressure;
  uint8   l_ucCount;
  boolean l_bDoIt;
  uint8   l_ucZomSlot;
  boolean l_bState;
  uint8   l_ucDefectWsCnt;

  l_ucDefectWsCnt = 0;
  l_bState = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);

  if(l_bState == FALSE) //perform only if not positively performed yet
  {

    //Check whether one or more WSs are already known as defective. those doesn't have to be waited for
    l_ucCount = 0x01;
    l_ucTemp = GETucReErrorStatusEE();//Status der WSs abholen
   l_ucTemp |= GETucReHeatUpStatusEE();  //Overtemperature Status der WSs abholen
    l_bDoIt = TRUE;  //Gegenteil muss sich erst beweisen

    //Check only WSs, which are not yet known as defective
   for(l_ucRadPos = 0; l_ucRadPos < cAnzRad; l_ucRadPos++)
   {
   	if(((l_ucTemp & (l_ucCount * 0x01)) == (l_ucCount * 0x01)) ||  //-> RE Ausfall oder Overtemperature: nur Flags im unteren Nibble
        ((l_ucTemp & (l_ucCount * 0x10)) == (l_ucCount * 0x10))) //-> RE Defekt : nur Flags im oberen Nibble
      {
        //WS is not ok, count defect sensors. If there are more then one, don't show pressure values on HMI for all sensors (System Spec. SR_671)
        l_ucDefectWsCnt++;
        if(l_ucDefectWsCnt > 1)
        {
          l_bDoIt = FALSE;
        }
      }
      else{
        //-> WS is ok, evaluate
        //-> Check whether there is already a pressure value available

        l_ucZomSlot = cAnzRad;
        for(l_ucLoop = 0; (l_ucLoop < cAnzRad) && (l_ucZomSlot == cAnzRad); l_ucLoop++)
        {
          if(GETucRadpositionPD(l_ucLoop) == l_ucRadPos)
          {
            l_ucZomSlot = l_ucLoop;
          }
        }
        if(l_ucZomSlot < cAnzRad)
        {
          l_ucPressure = GETucReifendruckPD(l_ucZomSlot);
        }
        else{
          l_ucPressure = cInvalidPressureCAN;
        }
        //l_ucPressure = ucGetValidTyrePressureRelAtPosPD(l_ucLauf); Geht nur bei Zugeordnet!!!
        if((l_ucPressure == cInvalidPressureCAN))
           //|| (l_ucPressure == 254) //Pressure value 254 == 6,35 Bar_rel is a valid value and a substitute value for P > 6,35 Bar_rel
           //|| (l_ucPressure == 0))  //0 is also a valid value
        {
          l_bDoIt = FALSE;
          break;
        }
      }
      l_ucCount <<= 1;
   }
   if(l_bDoIt == TRUE)
   {
      SetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
   }
  }
}

void CheckStateOf_ER_PressureRx_after_Allocation(void){
  boolean l_bState;
  boolean l_bDoIt;
  uint8   l_ucZomSlot;
  uint8   l_ucAddZomSlot;
  uint32  l_ulZomID;
  uint8   l_ucPressure;
//  uint8   l_ucLoopCnt;
  uint8   l_ucHistCol;

  l_ucPressure = 0;

  l_bDoIt = TRUE;  //the opposide must first be proven
  l_bState = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);

  if(l_bState == FALSE) //perform only if not positively performed yet
  {
   for(l_ucZomSlot = 0; l_ucZomSlot < cAnzRad; l_ucZomSlot++)
   {
      l_ulZomID = ulGetZOMID(l_ucZomSlot);
      for(l_ucAddZomSlot = 0; l_ucAddZomSlot < cSumWE; l_ucAddZomSlot++)
      {
        if(tAddZomData[l_ucAddZomSlot].ulID == l_ulZomID)
        {
          l_ucPressure = tAddZomData[l_ucAddZomSlot].ucPressure;
        }
        if((l_ucPressure == cInvalidPressureCAN))
           //|| (l_ucPressure == 254) //Pressure value 254 == 6,35 Bar_rel is a valid value and a substitute value for P > 6,35 Bar_rel
           //|| (l_ucPressure == 0)) //0 is also a valid value
        {
          l_bDoIt = FALSE;
          break;
        }
      }
      if(l_bDoIt == FALSE)
      {
        break;
      }
   }
  }
  if(l_bDoIt == TRUE)
  {
//    l_ucLoopCnt = 0;
    //put the actual pressure values from addZomData to Pressure-Array for HMI-message building
   for(l_ucHistCol = 0; l_ucHistCol < cMaxLR; l_ucHistCol++)
   {
      PreloadFromAddZomDataSM(l_ucHistCol);
//      l_ucLoopCnt++;
   }
//    if(l_ucLoopCnt == cAnzRad)
//    {
    SetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
//    }
  }
}

boolean SendRealReData(void){
  boolean l_bState_BZ;
//  boolean l_bState_FZ;
  boolean l_bRet;
  boolean l_bStatus;

  l_bStatus = bGetBitBetriebszustandBZ(cSEND_RE_DATA_ON_CAN);

  if(l_bStatus == FALSE)
  {
    l_bState_BZ = bGetBitBetriebszustandBZ(cALL_ER_PRESSURE_RX);
  //l_bState_FZ = bGetBitFahrzeugzustandFZZ(cRS_VTHRES);      Wird akt. nicht gewollt!
  //  l_bState_FZ = FALSE;
   if(l_bState_BZ == TRUE)  //Aalle ER-REs min. 1x empfangen
    //    || (l_bState_FZ == TRUE)  ) //Rollswitch muesste aktiv sein
   {
      SetBitBetriebszustandBZ(cSEND_RE_DATA_ON_CAN);
      l_bRet = TRUE;
   }
   else{
      l_bRet = FALSE;
   }
  }
  else{
    l_bRet = TRUE;
  }
  return (l_bRet);
}

#endif

#endif //IBTCM_SW_ANPASSUNGEN

void CountPositionReception(uint8 ucRecWheelPos)
{

  if(ucRecWheelPos < cAnzRad)
  {
    aucPosRecCounter[ucRecWheelPos]++;
  }
}

uint8 DCM_InvIf_WheelPosReceptionCounter(uint8 ucRecWheelPos)
{
  return aucPosRecCounter[ucRecWheelPos];
}

uint8 DCM_InvIf_WheelPosCurrIDGetValue(void){
  return ucGetWheelPosSM();
}

static void ucControlCyclicCallPeriod(void){
  boolean bRestartCnt = FALSE;
  boolean bDeleteDtc = FALSE;
  unsigned long ulBCMTimeNow = 0;  //BCM time stamp at the moment
  unsigned long ulTimeDifference = 0;  //time between now and the last time stamp
  signed long slPeriodDelta = 0; //deviation of real call period to the default period value of 200 ms
  unsigned long ulRealRunTime = 0; //run time from start of last measurement incl. cumulative delta time
  static signed long slCumulativPeriodDelta = 0; //cumulative period delta
  static unsigned long ulCallsCnt = 0;

  ClientIf_GetECUTimeStampValue(&ulBCMTimeNow);
  ulCallsCnt++;
  ulCallsCnt %= 0xFFFFFFFFU;

  if(ulBCMTimePrevious == 0)
  {
   ulBCMTimePrevious = ulBCMTimeNow; //for the first call just save first time stamp
  }
  else{
   if(ulBCMTimeNow >= ulBCMTimePrevious)
   {
      ulTimeDifference = ulBCMTimeNow - ulBCMTimePrevious;
   }
   else{
      //ulTimeDifference = 0xFFFFFFFF - ulBCMTimePrevious + ulBCMTimeNow; //this overflow can happen only once in 48 days continues IGN ON
      ulTimeDifference = cTPMSCyclicCallPeriod; //To avoid the error case when IGN was set to OFF with Speed != 0, which could cause calculation of too big TimeDifference.
   }
   ulBCMTimePrevious = ulBCMTimeNow;

   slPeriodDelta = ulTimeDifference - cTPMSCyclicCallPeriod;

   slCumulativPeriodDelta += slPeriodDelta;
  }

  ulRealRunTime = ((ulCallsCnt * cTPMSCyclicCallPeriod) + slCumulativPeriodDelta);

  if(ulRealRunTime >= c10MinutesBCMTime) //positive deviation delta
  {
    //set DTC BCM internal fault
    NvM_WriteData_ECUDefect(U8_ECU_DEFECT_CYCLIC_TASK);
    SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
    ResetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
   bRestartCnt = TRUE; //reset all counter to start next measurement cycle
  }
  else if((ulCallsCnt >= cCallsFor10Minutes) && (ulRealRunTime <= c8MinutesBCMTime)) //negative deviation delta
  {
    //set DTC BCM internal fault
    NvM_WriteData_ECUDefect(U8_ECU_DEFECT_CYCLIC_TASK);
    SetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
    ResetCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
   bRestartCnt = TRUE; //reset all counter to start next measurement cycle
  }
  else{
   if(slCumulativPeriodDelta >= 0)
   {//reset by small positive deviation if this count cycle last already for more then 8 minutes and cumulative deviation is less than 1 minute (10%)
      if((ulCallsCnt >= cCallsFor8Minutes) && (slCumulativPeriodDelta <= c1MinuteBCMTime))
      {
        //reset all counter to start next measurement cycle
        bRestartCnt = TRUE;
        bDeleteDtc = TRUE;
      }
   }
   else{//reset by small negative deviation
      if(((ulCallsCnt * cTPMSCyclicCallPeriod) >= c10MinutesBCMTime) && ((-1 * slCumulativPeriodDelta) < c1MinuteBCMTime))
      {
        //reset all counter to start next measurement cycle
        bRestartCnt = TRUE;
        bDeleteDtc = TRUE;
      }
   }

    //reset all counters latest after 11 minutes (10 min + 10% deviation)
   if((ulCallsCnt * cTPMSCyclicCallPeriod) >= (c10MinutesBCMTime + c1MinuteBCMTime))
   {
      bRestartCnt = TRUE;
      bDeleteDtc = TRUE;
   }
  }

  if(bRestartCnt == TRUE)
  {
   ulCallsCnt = 0;
   slCumulativPeriodDelta = 0;
   ulBCMTimePrevious = 0;
  }
  if(bDeleteDtc == TRUE)
  {
    DeleteCurrentErrorERR(cZO_ERR_BCM_INTERNAL_FAULT);
    NvM_WriteData_ECUDefect(U8_ECU_NOT_DEFECT);
  }
}

