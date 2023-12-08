#include "HS_WarnereignisX.h"

#include "DatamanagerX.h"
#include "EeDiagBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeCommonBlockX.h"
#include "SecondaryDTCX.h"
#include "WuMonitoringX.h"
#include "State_fzzX.h"
#include "WallocX.h"
#include "USWarn_ifX.h"
#include "state_bzX.h"
#include "InfoTyreX.h"
#include "BreakTireX.h"
#include "RdcTsaServicesX.h"

#ifndef TESSY
#ifdef WIN32
    #include "assert.h"
#endif
#endif

#define cGroupMask_A  (uint32)0xfU
#define cGroupMask_B  (uint32)0xf0U
#define cGroupMask_C  (uint32)0xf00U
#define cGroupMask_D  (uint32)0xf000U
#define cGroupMask_E  (uint32)0xf0000U

#define cGroupOffset_A (uint8)0
#define cGroupOffset_B (uint8)4
#define cGroupOffset_C (uint8)8
#define cGroupOffset_D (uint8)12
#define cGroupOffset_E (uint8)16

#define cFindBitSet     1
#define cFindBitCleared 0

#define cEventTypePanne 0
#define cEventTypeWarn  1
#define cEventTypeWeich 2
#define cMaxNrOfWarningGroups    8

static uint32 ulLastWSB = 0xffffffffU;
static uint8  ucLastWarnOut = 0xffU;
static uint32 ulMileage0_We1 = 0;
static uint32 ulMileage100_We1 = 0;
static uint32 ulMileage160_We1 = 0;
static uint32 ulMileage0_We2 = 0;
static uint32 ulMileage100_We2 = 0;
static uint32 ulMileage160_We2 = 0;
static uint32 ulMileage0_We3 = 0;
static uint32 ulMileage100_We3 = 0;
static uint32 ulMileage160_We3 = 0;

static uint8 ucCheckWarningGroup(uint32 ulBitsOld, uint32 ulBitsNew, uint32 ulGroupMask, uint8 ucDirection);
static uint8 ucNoOfActivePreWarningsDS(void);
static uint8 SaveWarnereignisDS(Rte_Instance self, uint8 ucPos, uint8 ucWarningType);
static uint8 SaveWarnereignisWeichDS(Rte_Instance self, uint8 ucPos);
static uint8 SaveWarnereignisRuecknahmeDS(Rte_Instance self, uint8 ucPos);
static void SaveHighestSpeedWithActiveWarningDS(Rte_Instance self, uint8 ucVMax);
static void CumulateKilometers_160_to_max_DS(Rte_Instance self);
static void CumulateKilometers_100_to_160_DS(Rte_Instance self);
static void CumulateKilometers_0_to_100_DS(Rte_Instance self);
static boolean bWarnereignis3ActiveDS(Rte_Instance self);
static boolean bWarnereignis2ActiveDS(Rte_Instance self);
static boolean bWarnereignis1ActiveDS(Rte_Instance self);
static void WriteWarnereignis_3_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);
static void WriteWarnereignis_2_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);
static void WriteWarnereignis_1_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize);
static void ShiftMileageDS(uint8 ucEventNumber);
static uint8 ucFindFirstBitInLoNibbleDS(uint8 ucByte);

void InitFastaWarnEventsDS(Rte_Instance self)
{
   ulLastWSB = GETulWarnOutTM();
   ucLastWarnOut = ucGetWarnOutStateBT(self);
}

void ProcessFastaWarnEventsDS(Rte_Instance self)
{
   uint32 ulWSB;
   uint8  ucWarnOut;
   uint8  ucPosition;
   uint8  i;
   uint8  ucWarningType;

   uint32 ulGroupsToCheck[3];
   uint8  ucNoOfGroupsToCheck;

   ulWSB = GETulWarnOutTM();
   ucWarnOut = ucGetWarnOutStateBT(self);

   if(ulLastWSB == 0xffffffffU){
      ulLastWSB = ulWSB;
   }
   if(ucLastWarnOut == 0xffU){
      ucLastWarnOut = ucWarnOut;
   }

   if(ucWarnOut != ucLastWarnOut){

      ucPosition = ucCheckWarningGroup( (uint32) ucLastWarnOut, (uint32) ucWarnOut, cMaskLoNibble, cFindBitSet);

      if(ucPosition < cMaxLR){

      ucWarningType = ucCheckWarningGroup( (uint32) ucLastWarnOut, (uint32) ucWarnOut, cMaskHiNibble, cFindBitSet);

      if(ucWarningType == 0){

        (void)SaveWarnereignisDS(self, ucPosition, cEventTypePanne);
      }
      else if(ucWarningType == 1){

       (void) SaveWarnereignisDS(self, ucPosition, cEventTypeWarn);
      }
      else{

          if((ucWarnOut & cBtWsBreakTirePw) == cBtWsBreakTirePw){

          (void) SaveWarnereignisDS(self, ucPosition, cEventTypePanne);
        }
        else{

          (void) SaveWarnereignisDS(self, ucPosition, cEventTypeWarn);
        }
      }
      }
      else{

      ucWarningType = ucCheckWarningGroup( (uint32) ucLastWarnOut, (uint32) ucWarnOut, cMaskHiNibble, cFindBitSet);

      if(ucWarningType == 0){

        ucPosition = ucFindFirstBitInLoNibbleDS( (ucWarnOut & cMaskLoNibble));

        (void) SaveWarnereignisDS(self, ucPosition, cEventTypePanne);
      }
      else if(ucWarningType == 1){

        ucPosition = ucFindFirstBitInLoNibbleDS( (ucWarnOut & cMaskLoNibble));

        (void) SaveWarnereignisDS(self, ucPosition, cEventTypeWarn);
      }
      else{

      }
      }

      ucLastWarnOut = ucWarnOut;
   }

   if(ulWSB != ulLastWSB){

      ucPosition = ucCheckWarningGroup(ulLastWSB, ulWSB, cGroupMask_D, cFindBitSet);
      if(ucPosition < cMaxLR){
      (void) SaveWarnereignisWeichDS(self, ucPosition);
      }

      ulGroupsToCheck[0] = cGroupMask_A;
      ulGroupsToCheck[1] = cGroupMask_B;
      ulGroupsToCheck[2] = cGroupMask_C;
      ucNoOfGroupsToCheck = 3;

      ucPosition = cMaxLR;
    i = 0;
    while ( (ucPosition == cMaxLR) && (i < ucNoOfGroupsToCheck)){
      ucPosition = ucCheckWarningGroup(ulLastWSB, ulWSB, ulGroupsToCheck[i], cFindBitCleared);
      if(ucPosition < cMaxLR){
        i = ucNoOfGroupsToCheck;
        (void) SaveWarnereignisRuecknahmeDS(self, ucPosition);
      }
      else{
        i++;
      }
      }

      ulLastWSB = ulWSB;
   }
}

static uint8 ucCheckWarningGroup(uint32 ulBitsOld, uint32 ulBitsNew, uint32 ulGroupMask, uint8 ucDirection)
{
   uint8  ucGroupNew;
   uint8  ucGroupOld;
   uint8  ucSetBits;
   uint8  ucClearedBits;
   uint8  ucOffset;
   uint8  ucRetVal = cMaxLR;

   switch(ulGroupMask){
      case cGroupMask_A: ucOffset = cGroupOffset_A; break;
      case cGroupMask_B: ucOffset = cGroupOffset_B; break;
      case cGroupMask_C: ucOffset = cGroupOffset_C; break;
      case cGroupMask_D: ucOffset = cGroupOffset_D; break;
      case cGroupMask_E: ucOffset = cGroupOffset_E; break;
      default: ucOffset = 0xff;
   }

   if(ucOffset != 0xff){
      ucGroupNew = (uint8)((ulBitsNew & ulGroupMask) >> ucOffset);
      ucGroupOld = (uint8)((ulBitsOld & ulGroupMask) >> ucOffset);

      if(ucDirection == cFindBitSet){
      ucSetBits = (ucGroupNew ^ ucGroupOld) & ucGroupNew;

      ucRetVal = ucFindFirstBitInLoNibbleDS( (ucSetBits & cMaskLoNibble));
      }
      else{
      ucClearedBits = (ucGroupNew ^ ucGroupOld) & ucGroupOld;

      ucRetVal = ucFindFirstBitInLoNibbleDS( (ucClearedBits & cMaskLoNibble));
      }
   }
   else{
      ucRetVal = cMaxLR;
   }

   return ucRetVal;
}

static uint8 ucNoOfActivePreWarningsDS(void)
{
   uint8 ucRetVal;
   ucRetVal = (uint8)((ulLastWSB >> 12) & (uint32)0x0f);
   ucRetVal = ucNrOfBitSet8(ucRetVal);
   return ucRetVal;
}

static uint8 SaveWarnereignisDS(Rte_Instance self, uint8 ucPos, uint8 ucWarningType)
{
  Rdci_UHRZEIT_DATUM_Type timeDate;
  Rdci_MILE_KM_Type mileKm;
   uint8 cTempBuffer[9];
   uint8 cData[cSizeWarnereignis];
   uint8 i;
   uint8 ucRetVal;
   uint8 ucSlot;
   uint8 ucTemp, ucPcold, ucPwarm, ucPamb, ucPosType;
   sint8 scTcold, scTwarm, scTemp;
   uint16 ushTemp, ushM;
   uint8 ucCounterWarn;

#ifndef TESSY
    #ifdef WIN32

    assert(sizeof(ImpTypeArrayDcm_RdcHsWarnereignis1ReadDataType) == cNvmRdciDiagBlock1HsWarn_1_Size);
    #endif
#endif

   ucCounterWarn = GetHsWarnereignis_1_CounterEE(self);

   if(ucCounterWarn == 0xff){
      ucCounterWarn = 1;
   }
   else if(ucCounterWarn < 0xfe){
      ucCounterWarn++;
   }
   else{}

   if(ucWarningType == cEventTypePanne){
      ucTemp = cSecondaryRdciPannenwarnung;
   }
   else{
      ucTemp = cSecondaryRdciDruckwarnung;
   }

   SetSecondaryErrorSCD(ucTemp);

   if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE){
      ucPosType = 4;
   }
   else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE){
      ucPosType = 4;
   }
   else{
      ucPosType = 0;
   }

   switch(ucPos){
      case cWheelPos_FL:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_FL<<ucPosType);
      break;

      case cWheelPos_FR:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_FR<<ucPosType);
      break;

      case cWheelPos_RL:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_RL<<ucPosType);
      break;

      case cWheelPos_RR:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_RR<<ucPosType);
      break;

      case cWheelPos_NA:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_NO_POS);
      break;

      default:
    SecondaryDtcFiFoWriteEntrySCD(ucTemp, RDC_TAB_POSITION_SENSOR_INVALID);
      break;
   }

   timeDate = GETtTimeDateEE(self);
  GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i] = cTempBuffer[i];
   }
  GetTimeStringDM((uint8)timeDate.DISP_HR, (uint8)timeDate.DISP_MN, (uint8)timeDate.DISP_SEC, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i+8] = cTempBuffer[i];
   }

  mileKm = GETulMileKmEE(self);
  cData[16] = (uint8)((mileKm >> 24) & 0xffU);
  cData[17] = (uint8)((mileKm >> 16) & 0xffU);
  cData[18] = (uint8)((mileKm >> 8) & 0xffU);
  cData[19] = (uint8)(mileKm & 0xffU);

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == FALSE){
      ucSlot = ucPos;
   }
   else{
      ucSlot = ucGetColOfWP(ucPos);
   }

  cData[20] = (uint8) (GETscTAinitValEE(self) + 40);
  cData[21] = (uint8) (GETscTAmbValEE(self) + 40);

   ucTemp = GETucPAmbValEE(self);
   ushTemp = Change25mBarToHpa(ucTemp);
  cData[22] = (uint8)((ushTemp >> 8) & 0xffU);
  cData[23] = (uint8)(ushTemp & 0xffU);

  cData[24] = GETucWheelSensorStatusFromNvmMirrorEE(self, ucSlot);

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
    cData[25] = ucPos;
   }
   else{
    cData[25] = 0x05;
   }

   for(i=0; i<cMaxLR; i++){
      ucTemp = ucGetWPOfColWAL(i);
      if(ucTemp < cMaxLR){
      cData[26 + (6 * i)] = ucTemp;
      ucTemp = GetQrIxOfWheelPos(self, ucTemp);
      ucTemp <<= 4;
      ucTemp &= 0xf0u;
      cData[26 + (6 * i)] |= ucTemp;
      }
      else{
      cData[26 + (6 * i)] = 0x05;
      }

      (void)ucGetPTSollUSWIF(self, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushM, &ucPamb, i);
      if(ucPwarm == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucPwarm);
      }
    cData[27 + (6 * i)] = (uint8) ((ushTemp >> 8) & 0xffU);
    cData[28 + (6 * i)] = (uint8) (ushTemp & 0xffU);

      ucTemp = ucGetRePressureRelDM(i);
      if(ucTemp == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucTemp);
      }
    cData[29 + (6 * i)] = (uint8)((ushTemp >> 8) & 0xffU);
    cData[30 + (6 * i)] = (uint8)(ushTemp & 0xffU);

      scTemp = scGetReTemperatureCentDM(i);
      if(scTemp == cInvalidREtemperature){
      scTemp = (sint8) 205;
      }
    cData[31 + (6 * i)] = (uint8)(scTemp + 50);
   }

  cData[50] = ucCounterWarn;

   for(i=0; i<7; i++){
    cData[51+i] = 0;
   }

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignis_3_EE(self, GetHsWarnereignis_2_EE(self, i), i, cSAVE_ON_EVENT);
   }
   PutWe3ZomSlotEE(self, GetWe2ZomSlotEE(self));
   ShiftMileageDS(2);

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignis_2_EE(self, GetHsWarnereignis_1_EE(self, i), i, cSAVE_ON_EVENT);
   }
   PutWe2ZomSlotEE(self, GetWe1ZomSlotEE(self));
   ShiftMileageDS(1);

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignis_1_EE(self, cData[i], i, cSAVE_ON_EVENT);
   }
   PutWe1ZomSlotEE(self, ucSlot);
   ulMileage0_We1 = GETulMileKmEE(self);
   ulMileage100_We1 = GETulMileKmEE(self);
   ulMileage160_We1 = GETulMileKmEE(self);

   ucRetVal = 0;
   return ucRetVal;
}

void CountDrivenKilometersWithWarningDS(Rte_Instance self)
{
   uint16 ushSpeed;
   uint8  ucSpeed;
   static uint8 ucSpeedState = 0;

   ushSpeed = GETushSpeedFZZ();

   if(ushSpeed <= 500){
      ucSpeed = (uint8)(ushSpeed >> 1);
   }
   else{
      ucSpeed = 0;
      ushSpeed = 0;
   }
   SaveHighestSpeedWithActiveWarningDS(self, ucSpeed);

   switch(ucSpeedState){

      case (uint8)0:
      if(ushSpeed > 0){
      ulMileage0_We1 = GETulMileKmEE(self);
      ulMileage0_We2 = GETulMileKmEE(self);
      ulMileage0_We3 = GETulMileKmEE(self);
      ucSpeedState = 1;
      }
      break;

      case (uint8)1:
      if(ushSpeed > 100){
      CumulateKilometers_0_to_100_DS(self);
      ulMileage100_We1 = GETulMileKmEE(self);
      ulMileage100_We2 = GETulMileKmEE(self);
      ulMileage100_We3 = GETulMileKmEE(self);
      ucSpeedState = 2;
      }
      else if(ushSpeed == 0){
      CumulateKilometers_0_to_100_DS(self);
      ucSpeedState = 0;
      }
      else {}
      break;

      case (uint8)2:
      if(ushSpeed > 160){
      CumulateKilometers_100_to_160_DS(self);
      ulMileage160_We1 = GETulMileKmEE(self);
      ulMileage160_We2 = GETulMileKmEE(self);
      ulMileage160_We3 = GETulMileKmEE(self);
      ucSpeedState = 3;
      }
      else if(ushSpeed <= 100){
      CumulateKilometers_100_to_160_DS(self);
      ulMileage0_We1 = GETulMileKmEE(self);
      ulMileage0_We2 = GETulMileKmEE(self);
      ulMileage0_We3 = GETulMileKmEE(self);
      ucSpeedState = 1;
      }
      else {}
      break;

      default:
      if(ushSpeed <= 160){
      CumulateKilometers_160_to_max_DS(self);
      ulMileage100_We1 = GETulMileKmEE(self);
      ulMileage100_We2 = GETulMileKmEE(self);
      ulMileage100_We3 = GETulMileKmEE(self);
      ucSpeedState = 2;
      }
      break;
   }
}

void ReadWarnereignis_1_DS(Rte_Instance self, uint8* paucData)
{
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWarn_1_Size; i++){
    paucData[i] = GetHsWarnereignis_1_EE(self, i);
   }
}

void ReadWarnereignis_2_DS(Rte_Instance self, uint8* paucData)
{
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWarn_1_Size; i++){
    paucData[i] = GetHsWarnereignis_2_EE(self, i);
   }
}

void ReadWarnereignis_3_DS(Rte_Instance self, uint8* paucData)
{
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWarn_1_Size; i++){
    paucData[i] = GetHsWarnereignis_3_EE(self, i);
   }
}

static void WriteWarnereignis_1_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize)
{
   uint8 i;

   for(i=0; i<ucSize; i++){
    PutHsWarnereignis_1_EE(self, aucData[i], i, cSAVE_ON_SHUTDOWN);
   }
}

static void WriteWarnereignis_2_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize)
{
   uint8 i;

   for(i=0; i<ucSize; i++){
    PutHsWarnereignis_2_EE(self, aucData[i], i, cSAVE_ON_SHUTDOWN);
   }
}

static void WriteWarnereignis_3_DS(Rte_Instance self, const uint8* aucData, uint8 ucSize)
{
   uint8 i;

   for(i=0; i<ucSize; i++){
    PutHsWarnereignis_3_EE(self, aucData[i], i, cSAVE_ON_SHUTDOWN);
   }
}

static void ShiftMileageDS(uint8 ucEventNumber)
{
   switch(ucEventNumber){

      case (uint8)2:
      ulMileage0_We3 = ulMileage0_We2;
      ulMileage100_We3 = ulMileage100_We2;
      ulMileage160_We3 = ulMileage160_We2;
      break;

      case (uint8)1:
      ulMileage0_We2 = ulMileage0_We1;
      ulMileage100_We2 = ulMileage100_We1;
      ulMileage160_We2 = ulMileage160_We1;
      break;

      default:
      break;
   }
}

static boolean bWarnereignis1ActiveDS(Rte_Instance self)
{
   boolean bRetVal = FALSE;
   if(GetWe1ZomSlotEE(self) != 255){
    bRetVal = TRUE;
   }
   return bRetVal;
}

static boolean bWarnereignis2ActiveDS(Rte_Instance self)
{
   boolean bRetVal = FALSE;
   if(GetWe2ZomSlotEE(self) != 255){
    bRetVal = TRUE;
   }
   return bRetVal;
}

static boolean bWarnereignis3ActiveDS(Rte_Instance self)
{
   boolean bRetVal = FALSE;
   if(GetWe3ZomSlotEE(self) != 255){
    bRetVal = TRUE;
   }
   return bRetVal;
}

static void SaveHighestSpeedWithActiveWarningDS(Rte_Instance self, uint8 ucVMax)
{
   uint8 ucData[cNvmRdciDiagBlock1HsWarn_1_Size];

   if(bWarnereignis1ActiveDS(self) == TRUE){
      ReadWarnereignis_1_DS(self, ucData);
      if(ucVMax > ucData[57]){
      ucData[57] = ucVMax;
      WriteWarnereignis_1_DS(self, ucData, sizeof(ucData));
      }

   }

   if(bWarnereignis2ActiveDS(self) == TRUE){
      ReadWarnereignis_2_DS(self, ucData);
      if(ucVMax > ucData[57]){
      ucData[57] = ucVMax;
      WriteWarnereignis_2_DS(self, ucData, sizeof(ucData));
      }

   }

   if(bWarnereignis3ActiveDS(self) == TRUE){
      ReadWarnereignis_3_DS(self, ucData);
      if(ucVMax > ucData[57]){
      ucData[57] = ucVMax;
      WriteWarnereignis_3_DS(self, ucData, sizeof(ucData));
      }
   }
}

static void CumulateKilometers_0_to_100_DS(Rte_Instance self)
{
   uint32  ulDiff;
   uint8   ucData[cNvmRdciDiagBlock1HsWarn_1_Size];
   uint16  ushTemp;

   if(bWarnereignis1ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage0_We1;
      ReadWarnereignis_1_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[51]) << 8) + (uint16)(ucData[52]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[51] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[52] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_1_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis2ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage0_We2;
      ReadWarnereignis_2_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[51]) << 8) + (uint16)(ucData[52]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[51] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[52] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_2_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis3ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage0_We3;
      ReadWarnereignis_3_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[51]) << 8) + (uint16)(ucData[52]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[51] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[52] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_3_DS(self, ucData, sizeof(ucData));
   }
}

static void CumulateKilometers_100_to_160_DS(Rte_Instance self)
{
   uint32  ulDiff;
   uint8   ucData[cNvmRdciDiagBlock1HsWarn_1_Size];
   uint16  ushTemp;

   if(bWarnereignis1ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage100_We1;
      ReadWarnereignis_1_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[53]) << 8) + (uint16)(ucData[54]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[53] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[54] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_1_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis2ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage100_We2;
      ReadWarnereignis_2_DS(self, ucData);
      ushTemp = ((uint16)(ucData[53]) << 8) + (uint16)(ucData[54]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[53] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[54] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_2_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis3ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage100_We3;
      ReadWarnereignis_3_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[53]) << 8) + (uint16)(ucData[54]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[53] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[54] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_3_DS(self, ucData, sizeof(ucData));
   }
}

static void CumulateKilometers_160_to_max_DS(Rte_Instance self)
{
   uint32  ulDiff;
   uint8   ucData[cNvmRdciDiagBlock1HsWarn_1_Size];
   uint16  ushTemp;

   if(bWarnereignis1ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage160_We1;
      ReadWarnereignis_1_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[55]) << 8) + (uint16)(ucData[56]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[55] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[56] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_1_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis2ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage160_We2;
      ReadWarnereignis_2_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[55]) << 8) + (uint16)(ucData[56]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[55] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[56] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_2_DS(self, ucData, sizeof(ucData));
   }

   if(bWarnereignis3ActiveDS(self) == TRUE){
      ulDiff = GETulMileKmEE(self) - ulMileage160_We3;
      ReadWarnereignis_3_DS(self, ucData);
      ushTemp = (uint16)((uint16)(ucData[55]) << 8) + (uint16)(ucData[56]);
      if((ushTemp + (uint16)ulDiff) < 0xffffu){
      ushTemp += (uint16)ulDiff;
      }
      ucData[55] = (uint8)((ushTemp >> 8) & 0xffu);
      ucData[56] = (uint8)(ushTemp & 0xffu);
    WriteWarnereignis_3_DS(self, ucData, sizeof(ucData));
   }
}

static uint8 SaveWarnereignisWeichDS(Rte_Instance self, uint8 ucPos)
{
  Rdci_UHRZEIT_DATUM_Type timeDate;
  Rdci_MILE_KM_Type mileKm;
   uint8 cTempBuffer[9];
   uint8 cData[cSizeWarnereignisWeich];
   uint8 i;
   uint8 ucRetVal;
   uint8 ucSlot;
   uint8 ucTemp, ucPcold, ucPwarm, ucPamb, ucPosType;
   sint8 scTcold, scTwarm, scTemp;
   uint16 ushTemp, ushM;
   uint32 ulTemp;
   uint8 ucCounterWarnWeich;

#ifndef TESSY
    #ifdef WIN32

    assert(sizeof(ImpTypeArrayDcm_RdcHsWarnereignisWeich1ReadDataType) == cNvmRdciDiagBlock1HsWeich_1_Size);
    #endif
#endif

   ucCounterWarnWeich = GetHsWarnereignisWeich_1_CounterEE(self);

   if(ucCounterWarnWeich == 0xff){
      ucCounterWarnWeich = 1;
   }
   else if(ucCounterWarnWeich < 0xfe){
      ucCounterWarnWeich++;
   }
   else{}

   SetSecondaryErrorSCD(cSecondaryRdciBefuellhinweis);

   if(ucNoOfActivePreWarningsDS() > 1){
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_NO_POS);
   }

   else{

      if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE){
      ucPosType = 4;
      }
      else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE){
      ucPosType = 4;
      }
      else{
      ucPosType = 0;
      }

      switch(ucPos){
      case cWheelPos_FL:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_FL<<ucPosType);
      break;

      case cWheelPos_FR:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_FR<<ucPosType);
      break;

      case cWheelPos_RL:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_RL<<ucPosType);
      break;

      case cWheelPos_RR:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_RR<<ucPosType);
      break;

      case cWheelPos_NA:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_NO_POS);
      break;

      default:
      SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciBefuellhinweis, RDC_TAB_POSITION_SENSOR_INVALID);
      break;
      }
   }

   timeDate = GETtTimeDateEE(self);
  GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i] = cTempBuffer[i];
   }
  GetTimeStringDM((uint8)timeDate.DISP_HR, (uint8)timeDate.DISP_MN, (uint8)timeDate.DISP_SEC, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i+8] = cTempBuffer[i];
   }

  mileKm = GETulMileKmEE(self);
  cData[16] = (uint8)((mileKm >> 24) & 0xffU);
  cData[17] = (uint8)((mileKm >> 16) & 0xffU);
  cData[18] = (uint8)((mileKm >> 8) & 0xffU);
  cData[19] = (uint8)(mileKm & 0xffU);

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == FALSE){
      ucSlot = ucPos;
   }
   else{
      ucSlot = ucGetColOfWP(ucPos);
   }

  cData[20] = (uint8) (GETscTAinitValEE(self) + 40);
  cData[21] = (uint8) (GETscTAmbValEE(self) + 40);

   ucTemp = GETucPAmbValEE(self);
   ushTemp = Change25mBarToHpa(ucTemp);
  cData[22] = (uint8)((ushTemp >> 8) & 0xffU);
  cData[23] = (uint8)(ushTemp & 0xffU);

   ucTemp = bGetReMuteStatusBySlotWUM(ucSlot);
   if(ucTemp > 0){
    cData[24] = 1;
   }
   else{
      ucTemp = bGetReDefectStatusBySlotWUM(ucSlot);
      if(ucTemp > 0){
      cData[24] = 2;
      }
      else{
      ulTemp = ulGetIDOfColWAL(ucSlot);
      ucTemp = ucGetZOMPosOfID(&ulTemp);
      if(ucTemp == cSumWE){
        cData[24] = 3;
      }
      else{
        cData[24] = 0;
      }
      }
   }

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
    cData[25] = ucPos;
   }
   else{
    cData[25] = 0x05;
   }

   for(i=0; i<cMaxLR; i++){
      ucTemp = ucGetWPOfColWAL(i);
      if(ucTemp < cMaxLR){
      cData[26 + (6 * i)] = ucTemp;
      ucTemp = GetQrIxOfWheelPos(self, ucTemp);
      ucTemp <<= 4;
      ucTemp &= 0xf0u;
      cData[26 + (6 * i)] |= ucTemp;
      }
      else{
      cData[26 + (6 * i)] = 0x05;
      }

      (void)ucGetPTSollUSWIF(self, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushM, &ucPamb, i);
      if(ucPwarm == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucPwarm);
      }
    cData[27 + (6 * i)] = (uint8) ((ushTemp >> 8) & 0xffU);
    cData[28 + (6 * i)] = (uint8) (ushTemp & 0xffU);

      ucTemp = ucGetRePressureRelDM(i);
      if(ucTemp == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucTemp);
      }
    cData[29 + (6 * i)] = (uint8) ((ushTemp >> 8) & 0xffU);
    cData[30 + (6 * i)] = (uint8) (ushTemp & 0xffU);

      scTemp = scGetReTemperatureCentDM(i);
      if(scTemp == cInvalidREtemperature){
      scTemp = (sint8) 205;
      }
    cData[31 + (6 * i)] = (uint8)(scTemp + 50);
   }

  cData[50] = ucCounterWarnWeich;

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignisWeich_3_EE(self, GetHsWarnereignisWeich_2_EE(self, i), i);
   }

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignisWeich_2_EE(self, GetHsWarnereignisWeich_1_EE(self, i), i);
   }

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignisWeich_1_EE(self, cData[i], i);
   }

   ucRetVal = 0;

   return ucRetVal;
}

void ReadWarnereignisWeich_1_DS(Rte_Instance self, uint8* aucData)
{
   uint8* pData = (uint8*)(&aucData[0]);
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWeich_1_Size; i++){
    pData[i] = GetHsWarnereignisWeich_1_EE(self, i);
   }
}

void ReadWarnereignisWeich_2_DS(Rte_Instance self, uint8* aucData)
{
   uint8* pData = (uint8*)(&aucData[0]);
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWeich_1_Size; i++){
    pData[i] = GetHsWarnereignisWeich_2_EE(self, i);
   }
}

void ReadWarnereignisWeich_3_DS(Rte_Instance self, uint8* aucData)
{
   uint8* pData = (uint8*)(&aucData[0]);
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWeich_1_Size; i++){
    pData[i] = GetHsWarnereignisWeich_3_EE(self, i);
   }
}

static uint8 SaveWarnereignisRuecknahmeDS(Rte_Instance self, uint8 ucPos)
{
  Rdci_UHRZEIT_DATUM_Type timeDate;
  Rdci_MILE_KM_Type mileKm;
   uint8 cTempBuffer[9];
   uint8 cData[cSizeWarnereignisRuecknahme];
   uint8 i;
   uint8 ucRetVal;
   uint8 ucSlot;
   uint8 ucTemp, ucPcold, ucPwarm, ucPamb, ucPosType;
   sint8 scTcold, scTwarm, scTemp;
   uint16 ushTemp, ushM;
   uint32 ulTemp;
   uint8 ucCounterWarnRuecknahme;

#ifndef TESSY
    #ifdef WIN32

      assert(sizeof(ImpTypeArrayDcm_RdcHsWarnereignisRuecknahmeReadDataType) == cNvmRdciDiagBlock1HsWRueck_Size);
    #endif
#endif

   ucCounterWarnRuecknahme = GetHsWarnereignisRuecknahmeCounterEE(self);
   if(ucCounterWarnRuecknahme == 0xff){
      ucCounterWarnRuecknahme = 1;
   }
   else if(ucCounterWarnRuecknahme < 0xfe){
      ucCounterWarnRuecknahme++;
   }
   else{}

   SetSecondaryErrorSCD(cSecondaryRdciWarnruecknahme);

   if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE){
      ucPosType = 4;
   }
   else if(bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG) == TRUE){
      ucPosType = 4;
   }
   else{
      ucPosType = 0;
   }

   switch(ucPos){
      case cWheelPos_FL:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_FL<<ucPosType);
      break;

      case cWheelPos_FR:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_FR<<ucPosType);
      break;

      case cWheelPos_RL:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_RL<<ucPosType);
      break;

      case cWheelPos_RR:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_RR<<ucPosType);
      break;

      case cWheelPos_NA:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_NO_POS);
      break;

      default:
    SecondaryDtcFiFoWriteEntrySCD(cSecondaryRdciWarnruecknahme, RDC_TAB_POSITION_SENSOR_INVALID);
      break;
   }

   timeDate = GETtTimeDateEE(self);
  GetDateStringDM(timeDate.DISP_DATE_YR, (uint8)timeDate.DISP_DATE_MON, (uint8)timeDate.DISP_DATE_DAY, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i] = cTempBuffer[i];
   }
  GetTimeStringDM((uint8)timeDate.DISP_HR, (uint8)timeDate.DISP_MN, (uint8)timeDate.DISP_SEC, cTempBuffer, sizeof(cTempBuffer));
   for(i=0; i<8; i++){
    cData[i+8] = cTempBuffer[i];
   }

  mileKm = GETulMileKmEE(self);
  cData[16] = (uint8)((mileKm >> 24) & 0xffU);
  cData[17] = (uint8)((mileKm >> 16) & 0xffU);
  cData[18] = (uint8)((mileKm >> 8) & 0xffU);
  cData[19] = (uint8)(mileKm & 0xffU);

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == FALSE){
      ucSlot = ucPos;
   }
   else{
      ucSlot = ucGetColOfWP(ucPos);
   }

  cData[20] = (uint8) (GETscTAinitValEE(self) + 40);
  cData[21] = (uint8) (GETscTAmbValEE(self) + 40);
   ucTemp = GETucPAmbValEE(self);
   ushTemp = Change25mBarToHpa(ucTemp);
  cData[22] = (uint8) ((ushTemp >> 8) & 0xffU);
  cData[23] = (uint8) (ushTemp & 0xffU);

   ucTemp = bGetReMuteStatusBySlotWUM(ucSlot);
   if(ucTemp > 0){
    cData[24] = 1;
   }
   else{
      ucTemp = bGetReDefectStatusBySlotWUM(ucSlot);
      if(ucTemp > 0){
      cData[24] = 2;
      }
      else{
      ulTemp = ulGetIDOfColWAL(ucSlot);
      ucTemp = ucGetZOMPosOfID(&ulTemp);
      if(ucTemp == cSumWE){
        cData[24] = 3;
      }
      else{
        cData[24] = 0;
      }
      }
   }

   if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
    cData[25] = ucPos;
   }
   else{
    cData[25] = 0x05;
   }

   for(i=0; i<cMaxLR; i++){
      ucTemp = ucGetWPOfColWAL(i);
      if(ucTemp < cMaxLR){
      cData[26 + (6 * i)] = ucTemp;
      ucTemp = GetQrIxOfWheelPos(self, ucTemp);
      ucTemp <<= 4;
      ucTemp &= 0xf0u;
      cData[26 + (6 * i)] |= ucTemp;
      }
      else{
      cData[26 + (6 * i)] = 0x05;
      }

      (void)ucGetPTSollUSWIF(self, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushM, &ucPamb, i);
      if(ucPwarm == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucPwarm);
      }
    cData[27 + (6 * i)] = (uint8) ((ushTemp >> 8) & 0xffU);
    cData[28 + (6 * i)] = (uint8) (ushTemp & 0xffU);

      ucTemp = ucGetRePressureRelDM(i);
      if(ucTemp == cInvalidREpressure){
      ushTemp = 0xffffu;
      }
      else{
      ushTemp = Change25mBarToHpa(ucTemp);
      }
    cData[29 + (6 * i)] = (uint8) ((ushTemp >> 8) & 0xffU);
    cData[30 + (6 * i)] = (uint8) (ushTemp & 0xffU);

      scTemp = scGetReTemperatureCentDM(i);
      if(scTemp == cInvalidREtemperature){
      scTemp = (sint8) 205;
      }
    cData[31 + (6 * i)] = (uint8)(scTemp + 50);
   }

  cData[50] = ucCounterWarnRuecknahme;

   for(i=0; i<sizeof(cData); i++){
    PutHsWarnereignisRuecknahmeEE(self, cData[i], i);
   }

   if(GetWe1ZomSlotEE(self) == ucSlot){
    PutWe1ZomSlotEE(self, 0xffu);
   }
   if(GetWe2ZomSlotEE(self) == ucSlot){
    PutWe2ZomSlotEE(self, 0xffu);
   }
   if(GetWe3ZomSlotEE(self) == ucSlot){
    PutWe3ZomSlotEE(self, 0xffu);
   }
   else {}

   ucRetVal = 0;
   return ucRetVal;
}

void ReadWarnereignisRuecknahmeDS(Rte_Instance self, uint8* paucData)
{
   uint8 i;

   for(i=0; i<cNvmRdciDiagBlock1HsWRueck_Size; i++){
    paucData[i] = GetHsWarnereignisRuecknahmeEE(self, i);
   }
}

static uint8 ucFindFirstBitInLoNibbleDS(uint8 ucByte)
{
   uint8 ucLoop;
   uint8 ucRet = 4;

   if(ucByte > 0){
      for(ucLoop = 0; ((ucRet == 4) && (ucLoop < 4)); ucLoop++){
      if((ucByte & (uint8) (1 << ucLoop)) != 0){
        ucRet = ucLoop;
      }
      }
   }

   return ucRet;
}
