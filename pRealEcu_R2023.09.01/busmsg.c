

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
  #include "busmsgX.hpp"
  #include "busmsg.hpp"
  #include "silaX.hpp"
  #include "ProcDatX.hpp"
  #include "USWarnX.hpp"
  #include "state_bzX.hpp"
  #include "CfgSwcApplTpms.hpp"
  #include "statisticsX.hpp"
  #include "CfgSwcApplTpms_IDOM.hpp"
  #include "SwcApplTpms_DTC_If.hpp"
  #include "WallocX.hpp"
#else
  #include "CfgSwcApplTpms.hpp"
  #include "busmsgX.hpp"
  #include "busmsg.hpp"
  #include "applosX.hpp"
  #include "silaX.hpp"
  #include "ErrMemX.hpp"
  #include "idom_x.hpp"
  #include "transmitX.hpp"
  #include "ProcDatX.hpp"
  #include "USWarnX.hpp"
  #include "uswarn_Ifx.hpp"
  #include "state_bzX.hpp"
  #include "eecate_ifx.hpp"
  #include "eecatc_ifx.hpp"
  #include "eecatb_ifx.hpp"
  #include "statisticsx.hpp"
  #include "applmainX.hpp"
  #include "wallocX.hpp"
  #include "statemanagerX.hpp"
  #include "calibrX.hpp"
  #include "VehStateX.hpp"
#endif

#define TEXTFLAGS_INVALID        ( (boolean) FALSE )
#define RDKACTIVE_INVALID        ( (boolean) FALSE )

#define AXLE_IMBALANCE_UNKNOWN    0x00U
#define AXLE_IMBALANCE_ABSENT     0x01U
#define AXLE_IMBALANCE_PRESENT    0x02U

STATIC uint8 ucTyreTemperature[BUSMSG_NUMBER_OF_TYRES];

STATIC uint8 ucTyrePressUncomp[BUSMSG_NUMBER_OF_TYRES];

STATIC uint8 ucTyreWarning[BUSMSG_NUMBER_OF_TYRES];

STATIC uint8 ucTyreTemperatureWarning;

STATIC boolean bTyreValidVL;

STATIC boolean bTyreValidVR;

STATIC boolean bTyreValidHL;

STATIC boolean bTyreValidHR;

STATIC boolean bTextFlags[BUSMSG_NUMBER_OF_TEXTFLAGS];

#ifdef IBTCM_SW_ANPASSUNGEN

#else
  struct tTransmitFlagsDecl tTransmitFlags;
#endif

static boolean GETbNoWarnPartSurv (const uint8 ucPos);
static void BusMsgCheckWarningsFrontLeft(void);
static void BusMsgCheckWarningsFrontRight(void);
static void BusMsgCheckWarningsRearLeft(void);
static void BusMsgCheckWarningsRearRight(void);
static void BusMsgCheckWarningsUnknownPos(void);
static uint8 BusMsgDetermineErrCounter(void);

void BusMsgInit(void){
  uint8 i;

  for( i = 0; i < BUSMSG_NUMBER_OF_TYRES; i++ )
  {
   ucTyrePressUncomp[i] = cInvalidPressureCAN;
   ucTyreWarning[i] = BUSMSG_WARN_UNKNOWN;
   ucTyreTemperature[i] = cInvalidTemperatureCAN;
  }

  bTyreValidVL = BUSMSG_TYREPRESS_INVALID;
  bTyreValidVR = BUSMSG_TYREPRESS_INVALID;
  bTyreValidHL = BUSMSG_TYREPRESS_INVALID;
  bTyreValidHR = BUSMSG_TYREPRESS_INVALID;

  ucTyreTemperatureWarning = BUSMSG_TEMPERATURE_NO_WARNING;

  for( i = 0; i < BUSMSG_NUMBER_OF_TEXTFLAGS; i++ )
  {
   bTextFlags[i] = TEXTFLAGS_INVALID;
  }
}

void BusMsgClr(void){
  uint8 i;

  for( i = 0; i < BUSMSG_NUMBER_OF_TYRES; i++ )
  {
   ucTyrePressUncomp[i] = cInvalidPressureCAN;
   ucTyreWarning[i] = BUSMSG_WARN_UNKNOWN;
  }

  bTyreValidVL = BUSMSG_TYREPRESS_INVALID;
  bTyreValidVR = BUSMSG_TYREPRESS_INVALID;
  bTyreValidHL = BUSMSG_TYREPRESS_INVALID;
  bTyreValidHR = BUSMSG_TYREPRESS_INVALID;

  for( i = 0; i < BUSMSG_NUMBER_OF_TEXTFLAGS; i++ )
  {
   bTextFlags[i] = TEXTFLAGS_INVALID;
  }

  SilaPutState( SILA_STATE_NORMAL_OFF );
}

void BusMsgTemperatureClear(void){
  uint8 U8_Counter;

  for( U8_Counter = 0; U8_Counter < BUSMSG_NUMBER_OF_TYRES; U8_Counter++ )
  {
   ucTyreTemperature[U8_Counter] = cInvalidTemperatureCAN;
  }

  for( U8_Counter = 0; U8_Counter < BUSMSG_NUMBER_OF_TEXTFLAGS; U8_Counter++ )
  {
   bTextFlags[U8_Counter] = TEXTFLAGS_INVALID;
  }
}

void BusMsgPutTemperature(uint8 ucId, uint8 ucTemperature)
{

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
   ucTyreTemperature[ucId] = ucTemperature;
  }
}

uint8 BusMsgGetTemperature(uint8 ucId)
{
  uint8 U8_Temperature = cInvalidTemperatureCAN;

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
    U8_Temperature = ucTyreTemperature[ucId];
  }
  else{

  }

  return U8_Temperature;
}

void BusMsgPutTyrePressUncomp(uint8 ucId, uint8 ucpress)
{

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
   ucTyrePressUncomp[ucId] = ucpress;
  }
}

uint8 BusMsgGetTyrePressUncomp(uint8 ucId)
{

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
    return( ucTyrePressUncomp[ucId] );
  }
  else{
    return( cInvalidPressureCAN );
  }
}

void BusMsgPutTemperatureWarning(uint8 ucId, boolean BO_IsTemperatureWarningActive)
{
  if(BO_IsTemperatureWarningActive != FALSE)
  {
   ucTyreTemperatureWarning = ucTyreTemperatureWarning | (1<<ucId);
  }
  else{
   ucTyreTemperatureWarning = ucTyreTemperatureWarning & (~(1<<ucId));
  }
}

boolean BusMsgGetTemperatureWarning(uint8 ucId)
{
  boolean BO_IsTemperatureWarningActive;

  BO_IsTemperatureWarningActive = (ucTyreTemperatureWarning >> ucId) & 1U;

  return BO_IsTemperatureWarningActive;
}

void BusMsgPutWarning(uint8 ucId, uint8 ucwarning)
{

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
#ifdef HUF_DEBUG
   if(ucwarning != BUSMSG_WARN_NOMINAL)
   {
      Nop();
      //Breakpoint();
   }
#endif
   ucTyreWarning[ucId] = ucwarning;
  }
}

uint8 BusMsgGetWarning(uint8 ucId)
{
  uint8 ucHelp;

  ucHelp = BUSMSG_WARN_UNKNOWN;

  if( ucId < BUSMSG_NUMBER_OF_TYRES )
  {
   ucHelp = ucTyreWarning[ucId];
  }
  return( ucHelp );
}

void BusMsgPutTyrePressValidVL(boolean bstate)
{
  bTyreValidVL = bstate;
}

boolean BusMsgGetTyrePressValidVL(void){
  return( bTyreValidVL );
}

void BusMsgPutTyrePressValidVR(boolean bstate)
{
  bTyreValidVR = bstate;
}

boolean BusMsgGetTyrePressValidVR(void){
  return( bTyreValidVR );
}

void BusMsgPutTyrePressValidHL(boolean bstate)
{
  bTyreValidHL = bstate;
}

boolean BusMsgGetTyrePressValidHL(void){
  return( bTyreValidHL );
}

void BusMsgPutTyrePressValidHR(boolean bstate)
{
  bTyreValidHR = bstate;
}

boolean BusMsgGetTyrePressValidHR(void){
  return( bTyreValidHR );
}

void BusMsgPutTextflag(uint8 ucId, boolean bstate)
{

  if( ucId < BUSMSG_NUMBER_OF_TEXTFLAGS )
  {
   bTextFlags[ucId] = bstate;
  }
}

boolean BusMsgGetTextflag(uint8 ucId)
{
  boolean bHelp;

  bHelp = TEXTFLAGS_INVALID;

  if( ucId < BUSMSG_NUMBER_OF_TEXTFLAGS )
  {
   bHelp = bTextFlags[ucId];
  }

  return (bHelp);
}

void BusMsgDoTeleFinished(void){
  uint8 ucTemp1;
  uint8 ucReErrCount = 0;
  uint16 usTempNoRxTime = 0;

  BusMsgClr();

#ifdef IBTCM_SW_ANPASSUNGEN

  if((GetSystem_DefectECUState() == TRUE) || (ushGetBetriebszustandBZ(cZO_TIMEOUT | cER_FINISH) == cZO_TIMEOUT) || (DTC_GetActiveStatusOfDTC(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS)== TRUE))
#else
  if( bGetBitBetriebszustandBZ(cDTC_INACTIVE) == TRUE )
#endif
  {

    BusMsgPutTextflag(BUSMSG_TEXTFLAG_3, 1);
    SilaPutState( SILA_STATE_MALFUNCTIONFLASH );
  }
  else{

   if((GETbHfIntLatchEE() == TRUE) || (DTC_GetActiveStatusOfDTC(cZO_ERR_RF_INTERFERENCE) == TRUE))
   {

      BusMsgPutTextflag(BUSMSG_TEXTFLAG_4, 1);
      SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
   }
  }

  if( bGetBitBetriebszustandBZ( cZUGEORDNET ) == TRUE )
  {
   ucReErrCount = BusMsgDetermineErrCounter();

   if( ucReErrCount > 1 )
   {

      BusMsgPutTextflag(BUSMSG_TEXTFLAG_1, 1);
   }

    BusMsgCheckWarningsFrontLeft();

    BusMsgCheckWarningsFrontRight();

    BusMsgCheckWarningsRearLeft();

    BusMsgCheckWarningsRearRight();

  }
  else{

   if(    (bGetBitBetriebszustandBZ( cER_FINISH ) == TRUE)
        || ( (bGetBitBetriebszustandBZ( cEIGENRAD ) == TRUE) && (bGetBitBetriebszustandBZ( cHIST_PRELOAD ) == TRUE) ) )
   {
      ucReErrCount = BusMsgDetermineErrCounter();

      if( ucReErrCount > 1 )
      {

        BusMsgPutTextflag(BUSMSG_TEXTFLAG_1, 1);
      }

      BusMsgCheckWarningsUnknownPos();
   }
   else{
   }
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_VL));
  if(      (TRUE == GETbNoWarnPartSurvVL())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTyrePressUncomp(BUSMSG_TYRE_VL, cInvalidPressureCAN);
    BusMsgPutTyrePressValidVL(BUSMSG_TYREPRESS_INVALID);
    BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_UNKNOWN);
  }
  else{
   ucTemp1 = ucGetValidTyrePressureRelAtPosPD(cRadPosVL);

   if( ucTemp1 >= cInvalidREpressure )
   {

      BusMsgPutTyrePressUncomp(BUSMSG_TYRE_VL, cInvalidPressureCAN);

      BusMsgPutTyrePressValidVL(BUSMSG_TYREPRESS_INVALID);
   }
   else{
      BusMsgPutTyrePressUncomp( BUSMSG_TYRE_VL, ucTemp1 );

      BusMsgPutTyrePressValidVL(BUSMSG_TYREPRESS_VALID);
   }
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_VR));
  if(       (TRUE == GETbNoWarnPartSurvVR())
          || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
          || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
          || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
    )
  {

    BusMsgPutTyrePressUncomp(BUSMSG_TYRE_VR, cInvalidPressureCAN);
    BusMsgPutTyrePressValidVR(BUSMSG_TYREPRESS_INVALID);
    BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_UNKNOWN);
  }
  else{
   ucTemp1 = ucGetValidTyrePressureRelAtPosPD(cRadPosVR);

   if( ucTemp1 >= cInvalidREpressure )
   {

      BusMsgPutTyrePressUncomp(BUSMSG_TYRE_VR, cInvalidPressureCAN);

      BusMsgPutTyrePressValidVR(BUSMSG_TYREPRESS_INVALID);
   }
   else{
      BusMsgPutTyrePressUncomp( BUSMSG_TYRE_VR, ucTemp1 );

      BusMsgPutTyrePressValidVR(BUSMSG_TYREPRESS_VALID);
   }
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_HL));
  if(      (TRUE == GETbNoWarnPartSurvHL())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTyrePressUncomp(BUSMSG_TYRE_HL, cInvalidPressureCAN);
    BusMsgPutTyrePressValidHL(BUSMSG_TYREPRESS_INVALID);
    BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_UNKNOWN);
  }
  else{
   ucTemp1 = ucGetValidTyrePressureRelAtPosPD(cRadPosHL);

   if( ucTemp1 >= cInvalidREpressure )
   {

      BusMsgPutTyrePressUncomp(BUSMSG_TYRE_HL, cInvalidPressureCAN);

      BusMsgPutTyrePressValidHL(BUSMSG_TYREPRESS_INVALID);
   }
   else{
      BusMsgPutTyrePressUncomp( BUSMSG_TYRE_HL, ucTemp1 );

      BusMsgPutTyrePressValidHL(BUSMSG_TYREPRESS_VALID);
   }
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_HR));
  if(      (TRUE == GETbNoWarnPartSurvHR())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
    )
  {

    BusMsgPutTyrePressUncomp(BUSMSG_TYRE_HR, cInvalidPressureCAN);
    BusMsgPutTyrePressValidHR(BUSMSG_TYREPRESS_INVALID);
    BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_UNKNOWN);
  }
  else{
   ucTemp1 = ucGetValidTyrePressureRelAtPosPD(cRadPosHR);

   if( ucTemp1 >= cInvalidREpressure )
   {

      BusMsgPutTyrePressUncomp(BUSMSG_TYRE_HR, cInvalidPressureCAN);

      BusMsgPutTyrePressValidHR(BUSMSG_TYREPRESS_INVALID);
   }
   else{
      BusMsgPutTyrePressUncomp( BUSMSG_TYRE_HR, ucTemp1 );

      BusMsgPutTyrePressValidHR(BUSMSG_TYREPRESS_VALID);
   }
  }

#ifdef IBTCM_SW_ANPASSUNGEN

#else
  TransmitUpdateData();
#endif
}

void BusMsgDetermineTemperatures(void){
  uint8 ucTemperature;
  uint8 ucReErrCount = 0;
  uint16 usTempNoRxTime = 0;

  BusMsgTemperatureClear();

  if((GetSystem_DefectECUState() == TRUE) || (ushGetBetriebszustandBZ(cZO_TIMEOUT | cER_FINISH) == cZO_TIMEOUT) || (DTC_GetActiveStatusOfDTC(cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS)== TRUE))
  {

    BusMsgPutTextflag(BUSMSG_TEXTFLAG_3, 1);
  }
  else{

   if((GETbHfIntLatchEE() == TRUE) || (DTC_GetActiveStatusOfDTC(cZO_ERR_RF_INTERFERENCE) == TRUE))
   {

      BusMsgPutTextflag(BUSMSG_TEXTFLAG_4, 1);
   }
  }

  ucReErrCount = BusMsgDetermineErrCounter();

  if( ucReErrCount > 1 )
  {

    BusMsgPutTextflag(BUSMSG_TEXTFLAG_1, 1);
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_VL));
  if(      (TRUE == GETbNoWarnPartSurvVL())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTemperature(BUSMSG_TYRE_VL, cInvalidTemperatureCAN);
  }
  else{
   ucTemperature = ucGetValidTemperatureRelAtPosPD(cRadPosVL);
    BusMsgPutTemperature(BUSMSG_TYRE_VL, ucTemperature);
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_VR));
  if(      (TRUE == GETbNoWarnPartSurvVR())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTemperature(BUSMSG_TYRE_VR, cInvalidTemperatureCAN);
  }
  else{
   ucTemperature = ucGetValidTemperatureRelAtPosPD(cRadPosVR);
    BusMsgPutTemperature(BUSMSG_TYRE_VR, ucTemperature);
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_HL));
  if(      (TRUE == GETbNoWarnPartSurvHL())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTemperature(BUSMSG_TYRE_HL, cInvalidTemperatureCAN);
  }
  else{
   ucTemperature = ucGetValidTemperatureRelAtPosPD(cRadPosHL);
    BusMsgPutTemperature(BUSMSG_TYRE_HL, ucTemperature);
  }

  usTempNoRxTime = GETusFolgeAusfallCntSTATISTICS(ucGetIndexOfHistoryWP(BUSMSG_TYRE_HR));
  if(      (TRUE == GETbNoWarnPartSurvHR())
         || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_3)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if AL not possible and this sensor not received for longer time
         || ((TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_4)) && (usTempNoRxTime >= ucMaxFF4RFInterference))  //if RF-Interference and this sensor not received for longer time
     )
  {

    BusMsgPutTemperature(BUSMSG_TYRE_HR, cInvalidTemperatureCAN);
  }
  else{
   ucTemperature = ucGetValidTemperatureRelAtPosPD(cRadPosHR);
    BusMsgPutTemperature(BUSMSG_TYRE_HR, ucTemperature);
  }
}

STATIC boolean GETbNoWarnPartSurv (const uint8 ucPos)
{
  uint8 ucRet = FALSE;

  if( ucPos < BUSMSG_NUMBER_OF_TYRES )
  {

   if((GETucReErrorStatusEE() & (uint8)(0x01 << ucPos)) == (uint8)(0x01 << ucPos))
   {
      ucRet = TRUE;
   }

   if((GETucReErrorStatusEE() & (uint8)(0x10 << ucPos)) == (uint8)(0x10 << ucPos))
   {
      ucRet = TRUE;
   }

   if((GETucReHeatUpStatusEE() & (uint8)(0x01 << ucPos)) == (uint8)(0x01 << ucPos))
   {
      ucRet = TRUE;
   }
  }

  return(ucRet);
}

static void BusMsgCheckWarningsFrontLeft(void){
  if((TRUE == GETbNoWarnPartSurvVL()) || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1)))
  {

    BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_UNKNOWN);
    SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
  }
  else{

   if( GETbPMFL())
   {
      BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_HARD);
      SilaPutState(SILA_STATE_PERMANENT_ON);
   }
   else{

      if(GETbDHWFL())
      {
        BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_PUNCTURE);
        SilaPutState(SILA_STATE_PERMANENT_ON);
      }
      else{

        if(GETbPECEFL())
        {
          BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_SOFT);
          SilaPutState(SILA_STATE_PERMANENT_ON);
        }
        else{

          BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_NOMINAL);
        }
      }
   }

   if( GETbTWFL())
   {
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VL, TRUE);
   }
   else{

      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VL, FALSE);
   }
  }
}

static void BusMsgCheckWarningsFrontRight(void){
  if((TRUE == GETbNoWarnPartSurvVR()) || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1)))
  {

    BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_UNKNOWN);
    SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
  }
  else{

   if( GETbPMFR())
   {
      BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_HARD);
      SilaPutState(SILA_STATE_PERMANENT_ON);
   }
   else{

      if(GETbDHWFR())
      {
        BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_PUNCTURE);
        SilaPutState(SILA_STATE_PERMANENT_ON);
      }
      else{

        if(GETbPECEFR())
        {
          BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_SOFT);
          SilaPutState(SILA_STATE_PERMANENT_ON);
        }
        else{

          BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_NOMINAL);
        }
      }
   }

   if( GETbTWFR())
   {
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VR, TRUE);
   }
   else{

      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VR, FALSE);
   }
  }
}

static void BusMsgCheckWarningsRearLeft(void){
  if((TRUE == GETbNoWarnPartSurvHL()) || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1)))
  {

    BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_UNKNOWN);
    SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
  }
  else{

   if( GETbPMRL())
   {
      BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_HARD);
      SilaPutState(SILA_STATE_PERMANENT_ON);
   }
   else{

      if(GETbDHWRL())
      {
        BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_PUNCTURE);
        SilaPutState(SILA_STATE_PERMANENT_ON);
      }
      else{

        if(GETbPECERL())
        {
          BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_SOFT);
          SilaPutState(SILA_STATE_PERMANENT_ON);
        }
        else{

          BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_NOMINAL);
        }
      }
   }

   if( GETbTWRL())
   {
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HL, TRUE);
   }
   else{

      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HL, FALSE);
   }
  }
}

static void BusMsgCheckWarningsRearRight(void){
  if((TRUE == GETbNoWarnPartSurvHR()) || (TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1)))
  {

    BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_UNKNOWN);
    SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
  }
  else{

   if( GETbPMRR())
   {
      BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_HARD);
      SilaPutState(SILA_STATE_PERMANENT_ON);
   }
   else{

      if(GETbDHWRR())
      {
        BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_PUNCTURE);
        SilaPutState(SILA_STATE_PERMANENT_ON);
      }
      else{

        if(GETbPECERR())
        {
          BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_SOFT);
          SilaPutState(SILA_STATE_PERMANENT_ON);
        }
        else{

          BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_NOMINAL);
        }
      }
   }

   if( GETbTWRR())
   {
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HR, TRUE);
   }
   else{

      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HR, FALSE);
   }
  }
}

static void BusMsgCheckWarningsUnknownPos(void){
  if( TRUE == BusMsgGetTextflag(BUSMSG_TEXTFLAG_1))
  {

    BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_UNKNOWN);
    BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_UNKNOWN);
    BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_UNKNOWN);
    BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_UNKNOWN);
    SilaPutState(SILA_STATE_MALFUNCTIONFLASH);
  }
  else{

   if( GETbPMNA())
   {
      BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_HARD);
      BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_HARD);
      BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_HARD);
      BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_HARD);
      SilaPutState(SILA_STATE_PERMANENT_ON);
   }
   else{

      if(GETbDHWNA())
      {
        BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_PUNCTURE);
        BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_PUNCTURE);
        BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_PUNCTURE);
        BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_PUNCTURE);
        SilaPutState(SILA_STATE_PERMANENT_ON);
      }
      else{

        if(GETbPECENA())
        {
          BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_SOFT);
          BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_SOFT);
          BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_SOFT);
          BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_SOFT);
          SilaPutState(SILA_STATE_PERMANENT_ON);
        }
        else{

          BusMsgPutWarning(BUSMSG_TYRE_VL, BUSMSG_WARN_NOMINAL);
          BusMsgPutWarning(BUSMSG_TYRE_VR, BUSMSG_WARN_NOMINAL);
          BusMsgPutWarning(BUSMSG_TYRE_HL, BUSMSG_WARN_NOMINAL);
          BusMsgPutWarning(BUSMSG_TYRE_HR, BUSMSG_WARN_NOMINAL);
        }
      }
   }

   if( GETbTWNA())
   {
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VL, TRUE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VR, TRUE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HL, TRUE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HR, TRUE);
   }
   else{

      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VL, FALSE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_VR, FALSE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HL, FALSE);
      BusMsgPutTemperatureWarning(BUSMSG_TYRE_HR, FALSE);
   }
  }
}

static uint8 BusMsgDetermineErrCounter(void){
  uint8 ucReErrCount=0;

  if( GETbNoWarnPartSurvVL() == TRUE)
  {
   ucReErrCount++;
  }

  if( GETbNoWarnPartSurvHL() == TRUE)
  {
   ucReErrCount++;
  }

  if( GETbNoWarnPartSurvVR() == TRUE)
  {
   ucReErrCount++;
  }

  if( GETbNoWarnPartSurvHR() == TRUE)
  {
   ucReErrCount++;
  }

  return ucReErrCount;
}
