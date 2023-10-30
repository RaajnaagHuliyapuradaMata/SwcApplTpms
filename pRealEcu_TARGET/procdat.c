#include "Std_Types.hpp"

#include "global.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "procdatX.hpp"
#include "procdat.hpp"
#include "statisticsX.hpp"
#include "cd_decoder_X.hpp"
#include "statemanagerX.hpp"
#include "state_bzX.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "busmsgX.hpp"

#define TIME_1S_OVER  ( (uint8) 1 )
#define NR_OF_SURPRESSED_TELEGRAMS    ((uint8) 5U )
#define OVER_TEMPERATURE_VALUE        ((uint8) 0xF7U )
#define ONE_BAR_PRESSURE              ((uint16) 40U )
#define LOWEST_ATMOSPHERIC_PRESS      ((uint8) 22U )
#define HIGHEST_ATMOSPHERIC_PRESS     ((uint8) 44U )

typedef struct{
   uint32 ulID;
   uint8  ucPressure;
   sint8  scTemperature;
   uint8  ucRemainingLifeTime;
   uint8  ucTransMode;
   uint16 ushSensorDefect;
}tREDATAPREPROC_DECL;

static tPreBuf      tReDataPD;
static tRxRotatSBuf tWs_RxRotatSBuf[12];
static uint8        ucRotatSTelIndexPut;
static uint16       ucTyreInvalidPressSurpressionCnt[5];
static uint8        ucRotL;
static uint8        ucSnRotH;
static uint8        ucRecEventPD;
static uint8        U8_AllReceivedTelegCnt;
static uint8        ucReifendruckPD[cAnzRad];
static sint8        scTemperaturPD[cAnzRad];
static uint8        ucRestlebensdauerPD[cAnzRad];
static uint8        ucRSSIsumPD[cAnzRad];
static uint8        ucTelTypePD[cAnzRad];
static uint8        ucTransModePD[cAnzRad];
static uint16       ushSensorDefectPD[cAnzRad];
static uint8        ucPatmoPD;

static tREDATAPREPROC_DECL tReDataPreProcPD = {
      (uint32) 0
   ,  (uint8)  cInvalidREpressure
   ,  (sint8)  cInvalidREtemperature
   ,  (uint8)  cInvalidRElifeTime
   ,  (uint8)  cInvalidTransMode
   ,  (uint16) cInvalidSensorDefect
};

uint8 ucRotatSTelIndexGet;

static uint16 ushCalcAKPressurePD(
      uint8  ucRawPres
   ,  uint8* pucPhyPres
);
static uint16 ushCalcAKTemperaturePD(
      uint8  ucRawTemp
   ,  sint8* pscPhyTemp
);

void InitPD(void){
   uint8 ucLoop;
   ReloadSTATISTICS();
   ucRecEventPD = 0;
   U8_AllReceivedTelegCnt = 0;
   ucRotatSTelIndexPut = 0;
   ucRotatSTelIndexGet = 0;
   for(
      ucLoop = 0;
      ucLoop < cAnzRad;
      ucLoop ++
   ){
      ucReifendruckPD[ucLoop]                  = cInvalidREpressure;
      scTemperaturPD[ucLoop]                   = cInvalidREtemperature;
      ucRestlebensdauerPD[ucLoop]              = cInvalidRElifeTime;
      ucRSSIsumPD[ucLoop]                      = cInvalidRSSIsum;
      ucTelTypePD[ucLoop]                      = cInvalidTelType;
      ucTransModePD[ucLoop]                    = cInvalidTransMode;
      ushSensorDefectPD[ucLoop]                = cInvalidSensorDefect;
      ucTyreInvalidPressSurpressionCnt[ucLoop] = 0;
   }
   PUTucPatmoPD(
      GETucPatmoEE()
   );
}

void IncrementAllReceivedTelegCnt(void){
   U8_AllReceivedTelegCnt++;
}

uint32 ulGetReDataIdPD(void){
   uint32 ul_LocalID;
   ul_LocalID = (
         ((uint32)tReDataPD.AK35def.ucID[0] << 24U)
      |  ((uint32)tReDataPD.AK35def.ucID[1] << 16U)
      |  ((uint32)tReDataPD.AK35def.ucID[2] << 8U)
      |  ((uint32)tReDataPD.AK35def.ucID[3] << 0U)
   );
   return ul_LocalID;
}

uint8 ucGetReDataPressurePD(void){
   uint8 ucHelp;
   if(
         (cTelTypeAK35def == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeHufStatus == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeAK35defLMA == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeStandstill == tReDataPD.AK35def.ucCmdID)
   ){
      ucHelp = tReDataPD.AK35def.ucPressure;
   }
   else{
      ucHelp = ((uint8)0x00);
   }
   return ucHelp;
}

uint8 ucGetReDataTemperaturePD(void){
   uint8 ucHelp;
   if(
         (cTelTypeAK35def        == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeHufStatus      == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeAK35defLMA     == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeStandstill     == tReDataPD.AK35def.ucCmdID)
   ){
      ucHelp = tReDataPD.AK35def.ucTemperature;
   }
   else{
      ucHelp = ((uint8)0x00);
   }
   return ucHelp;
}

uint8 ucGetReDataRemainingLifeTimePD(void){
   uint8 ucHelp;
   if(
         (cTelTypeHufStatus      == tReDataPD.AK35def.ucCmdID)
      || (cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID)
   ){
      ucHelp = (uint8)((tReDataPD.HufStatus.ucByte2Status & 0x3C) >> 2);
   }
   else{
      ucHelp = ((uint8)0x0F);
   }
   return ucHelp;
}

uint8 ucGetReDataStatePD(void){
   uint8 ucHelp = 0;
   if(cTelTypeAK35def == tReDataPD.AK35def.ucCmdID){
      ucHelp = cRE_AK_TM_MODE_DRIVE;
   }
   else if(cTelTypeRotatS == tReDataPD.AK35def.ucCmdID){
      ucHelp = cRE_AK_TM_MODE_LEARNDRIVE;
   }
   else if((cTelTypeHufStatus == tReDataPD.AK35def.ucCmdID) || (cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID)){
      if(OVER_TEMPERATURE_VALUE == tReDataPD.HufStatus.ucTemperature){
         ucHelp = cRE_AK_TM_MODE_OVERTEMP;
      }
      else{
         switch((tReDataPD.HufStatus.ucByte1Status & 0xE0u) >> 5){
            case 3:  ucHelp = cRE_AK_TM_MODE_LEARNDRIVE; break;
            case 5:  ucHelp = cRE_AK_TM_MODE_DRIVE;      break;
            default: ucHelp = cRE_AK_TM_MODE_STANDSTILL; break;
         }
         if(1 == ((tReDataPD.HufStatus.ucByte2Status & 0xC0u) >> 6)){
            ucHelp = cRE_AK_TM_EVENT_DP;
         }
      }
   }
   else{
      ucHelp = ((uint8)0);
   }
   return ucHelp;
}

uint8 ucGetReDataRssiAvgPD(void){return tReDataPD.Struc.ucAvg;}
uint8 ucGetReDataTelTypePD(void){return tReDataPD.AK35def.ucCmdID;}

uint8 ucGetReDataTGCounter(void){
   uint8 ucHelp = 0;
   if((cTelTypeHufStatus == tReDataPD.AK35def.ucCmdID) || (cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID)){
      ucHelp = (uint8)(tReDataPD.HufStatus.ucByte1Status & 0x1Fu);
   }
   else{
      ucHelp = 0;
   }
   return ucHelp;
}

tPreBuf* pGetCurTel            (void){return &tReDataPD;}
uint32   ulGetReDataPreProcIdPD(void){return tReDataPreProcPD.ulID;}
void     PutReDataPreProcIdPD(uint32 ulID){tReDataPreProcPD.ulID = ulID;}
uint8    ucGetReDataPreProcPressurePD(void){return tReDataPreProcPD.ucPressure;}
void     PutReDataPreProcPressurePD(uint8 ucPressure){tReDataPreProcPD.ucPressure = ucPressure;}
sint8    scGetReDataPreProcTemperaturePD(void){return tReDataPreProcPD.scTemperature;}
void     PutReDataPreProcTemperaturePD(sint8 scTemperature){tReDataPreProcPD.scTemperature = scTemperature;}
uint8    ucGetReDataPreProcRemainingLifeTimePD(void){return tReDataPreProcPD.ucRemainingLifeTime;}
void     PutReDataPreProcRemainingLifeTimePD(uint8 ucRemainingLifeTime){tReDataPreProcPD.ucRemainingLifeTime = ucRemainingLifeTime;}
uint8    ucGetReDataPreProcTransModePD(void){return tReDataPreProcPD.ucTransMode;}
void     PutReDataPreProcTransModePD(uint8 ucTransMode){tReDataPreProcPD.ucTransMode = ucTransMode;}
uint16   ushGetReDataPreProcSensorDefectPD(void){return tReDataPreProcPD.ushSensorDefect;}
void     PutReDataPreProcSensorDefectPD(uint16 ushSensorDefect){tReDataPreProcPD.ushSensorDefect = ushSensorDefect;}

uint8 ucGetValidTyrePressureRelAtPosPD(uint8 ucRadPos){
   uint8 ucRet;
   uint8 ucZomPos;
   ucZomPos = ucGetSlotNoAtPosPD(ucRadPos);
   if(ucZomPos < cAnzRad){
      if(ucReifendruckPD[ucZomPos] == cInvalidREpressure){
         ucRet = cInvalidREpressure;
      }
      else{
         ucRet = ucReifendruckPD[ucZomPos];
      }
   }
   else{
      ucRet = cInvalidREpressure;
   }
   return ucRet;
}

uint8 ucGetValidTemperatureRelAtPosPD(uint8 ucRadPos){
   uint8 ucRet;
   uint8 ucZomPos;
   ucZomPos = ucGetSlotNoAtPosPD(ucRadPos);
   if(ucZomPos < cAnzRad){
      if(scTemperaturPD[ucZomPos] == cInvalidREtemperature){
         ucRet = cInvalidTemperatureCAN;
      }
      else{
         ucRet = (uint8)(scTemperaturPD[ucZomPos] + 50);
      }
   }
   else{
      ucRet = cInvalidTemperatureCAN;
   }
   return ucRet;
}

uint8 ucGetSlotNoAtPosPD(uint8 ucRadPos){
   uint8 ucLoop;
   uint8 ucRet;
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      ucRet = cAnzRad;
      for(
         ucLoop = 0;
         ucLoop < cAnzRad;
         ucLoop ++
      ){
         if(ucGetRadPosAtSlotPDIF(ucLoop) == ucRadPos){
            ucRet = ucLoop;
            break;
         }
      }
   }
   else{
      ucRet = cAnzRad;
   }
   return ucRet;
}

void ReadReDataFromRingBuffer_iBTCM(const Type_SwcApplTpms_stTelegramWS* spRxDataIn){
   boolean l_bDoIt;
   boolean l_bAnalyseTelegram;
   uint8 l_ucTelType;
   l_bDoIt = TRUE;
   l_bAnalyseTelegram = TRUE;
   l_ucTelType = spRxDataIn->ucaTelegram[2];
   if(FALSE != ucTelOfInterest(l_ucTelType)){
      tReDataPD.Struc.ulTimeStamp = spRxDataIn->ulRxTimeStamp;
      tReDataPD.Struc.ucAvg = (uint8)(0x00FFu & spRxDataIn->uiRxRSSI);
      switch(l_ucTelType){
         case cTelTypeAK35def:
         case cTelTypeAK35defLMA:
         case cTelTypeStandstill:
            tReDataPD.AK35def.ucCmdID          = l_ucTelType;
            tReDataPD.AK35def.ucID[0]          = spRxDataIn->ucaTelegram[3];
            tReDataPD.AK35def.ucID[1]          = spRxDataIn->ucaTelegram[4];
            tReDataPD.AK35def.ucID[2]          = spRxDataIn->ucaTelegram[5];
            tReDataPD.AK35def.ucID[3]          = spRxDataIn->ucaTelegram[6];
            tReDataPD.AK35def.ucPressure       = spRxDataIn->ucaTelegram[7];
            tReDataPD.AK35def.ucTemperature    = spRxDataIn->ucaTelegram[8];
            tReDataPD.AK35def.ucCRC8           = spRxDataIn->ucaTelegram[9];
            break;
         case cTelTypeHufStatus:
         case cTelTypeHufStatusLearn:
            tReDataPD.HufStatus.ucCmdID        = l_ucTelType;
            tReDataPD.HufStatus.ucID[0]        = spRxDataIn->ucaTelegram[3];
            tReDataPD.HufStatus.ucID[1]        = spRxDataIn->ucaTelegram[4];
            tReDataPD.HufStatus.ucID[2]        = spRxDataIn->ucaTelegram[5];
            tReDataPD.HufStatus.ucID[3]        = spRxDataIn->ucaTelegram[6];
            tReDataPD.HufStatus.ucPressure     = spRxDataIn->ucaTelegram[7];
            tReDataPD.HufStatus.ucTemperature  = spRxDataIn->ucaTelegram[8];
            tReDataPD.HufStatus.ucByte1Status  = spRxDataIn->ucaTelegram[9];
            tReDataPD.HufStatus.ucByte2Status  = spRxDataIn->ucaTelegram[10];
            tReDataPD.HufStatus.ucCRC8         = spRxDataIn->ucaTelegram[11];
            break;
         case cTelTypeRotatS:
            tReDataPD.RotatS.ucCmdID           = l_ucTelType;
            tReDataPD.RotatS.ucID[0]           = spRxDataIn->ucaTelegram[3];
            tReDataPD.RotatS.ucID[1]           = spRxDataIn->ucaTelegram[4];
            tReDataPD.RotatS.ucID[2]           = spRxDataIn->ucaTelegram[5];
            tReDataPD.RotatS.ucID[3]           = spRxDataIn->ucaTelegram[6];
            tReDataPD.RotatS.ucSnRH            = spRxDataIn->ucaTelegram[7];
            tReDataPD.RotatS.ucRL              = spRxDataIn->ucaTelegram[8];
            tReDataPD.RotatS.ucCRC8            = spRxDataIn->ucaTelegram[9];
            break;
         case cTelTypeHufLfResponse:
            tReDataPD.LfResponse.ucCmdID       = l_ucTelType;
            tReDataPD.LfResponse.ucID[0]       = spRxDataIn->ucaTelegram[3];
            tReDataPD.LfResponse.ucID[1]       = spRxDataIn->ucaTelegram[4];
            tReDataPD.LfResponse.ucID[2]       = spRxDataIn->ucaTelegram[5];
            tReDataPD.LfResponse.ucID[3]       = spRxDataIn->ucaTelegram[6];
            tReDataPD.LfResponse.ucPressure    = spRxDataIn->ucaTelegram[7];
            tReDataPD.LfResponse.ucTemperature = spRxDataIn->ucaTelegram[8];
            tReDataPD.LfResponse.ucReserved    = spRxDataIn->ucaTelegram[9];
            tReDataPD.LfResponse.ucByte1Status = spRxDataIn->ucaTelegram[10];
            tReDataPD.LfResponse.ucByte2Status = spRxDataIn->ucaTelegram[11];
            tReDataPD.LfResponse.ucCRC8        = spRxDataIn->ucaTelegram[12];
            l_bAnalyseTelegram                 = FALSE;
            break;
         case cTelTypeSchraderFP:
            tReDataPD.SchraderType.ucCmdID     = l_ucTelType;
            tReDataPD.SchraderType.ucID[0]     = spRxDataIn->ucaTelegram[3];
            tReDataPD.SchraderType.ucID[1]     = spRxDataIn->ucaTelegram[4];
            tReDataPD.SchraderType.ucID[2]     = spRxDataIn->ucaTelegram[5];
            tReDataPD.SchraderType.ucID[3]     = spRxDataIn->ucaTelegram[6];
            tReDataPD.SchraderType.ucReserved1 = spRxDataIn->ucaTelegram[7];
            tReDataPD.SchraderType.ucReserved2 = spRxDataIn->ucaTelegram[8];
            tReDataPD.SchraderType.ucReserved3 = spRxDataIn->ucaTelegram[9];
            tReDataPD.SchraderType.ucReserved4 = spRxDataIn->ucaTelegram[10];
            tReDataPD.SchraderType.ucReserved5 = spRxDataIn->ucaTelegram[11];
            tReDataPD.SchraderType.ucReserved6 = spRxDataIn->ucaTelegram[12];
            tReDataPD.SchraderType.ucReserved7 = spRxDataIn->ucaTelegram[13];
            tReDataPD.SchraderType.ucReserved8 = spRxDataIn->ucaTelegram[14];
            tReDataPD.SchraderType.ucCRC8      = spRxDataIn->ucaTelegram[15];
            l_bAnalyseTelegram                 = FALSE;
            break;
         default:
            l_bDoIt = FALSE;
            break;
      }
   }
   else{
      l_bDoIt = FALSE;
   }
   if(TRUE == l_bDoIt){
      ucRecEventPD++;
      if(TRUE == l_bAnalyseTelegram){
         EvReDataSM();
      }
      DCM_EventDataUpdateOnRx();
   }
}

void RSSIBalancePD(uint8 ucOffsetVal){
   if(tReDataPD.Struc.ucAvg > ucOffsetVal){
      tReDataPD.Struc.ucAvg -= ucOffsetVal;
   }
   else{
      tReDataPD.Struc.ucAvg = 0;
   }
}

void ClearReDataInSlotPD(uint8 ucZomSlot){
   ucReifendruckPD[ucZomSlot]     = cInvalidREpressure;
   scTemperaturPD[ucZomSlot]      = cInvalidREtemperature;
   ucRestlebensdauerPD[ucZomSlot] = cInvalidRElifeTime;
   ucRSSIsumPD[ucZomSlot]         = cInvalidRSSIsum;
   ucTelTypePD[ucZomSlot]         = cInvalidTelType;
   ucTransModePD[ucZomSlot]       = cInvalidTransMode;
   ushSensorDefectPD[ucZomSlot]   = cInvalidSensorDefect;
}

uint8 GETucReifendruckPD(uint8 ucZomSlot){return ucReifendruckPD[ucZomSlot];}

void PUTucReifendruckPD(
      uint8 ucInData
   ,  uint8 ucZomSlot
){
   uint8 ucWheelPosition;
   ucReifendruckPD[ucZomSlot] = ucInData;
   ucWheelPosition = ucGetWPOfCol(ucZomSlot);
   switch(ucWheelPosition){
      case cRadPosVL: NvM_WriteData_PressureFL(ucInData); break;
      case cRadPosVR: NvM_WriteData_PressureFR(ucInData); break;
      case cRadPosHL: NvM_WriteData_PressureRL(ucInData); break;
      case cRadPosHR: NvM_WriteData_PressureRR(ucInData); break;
      default:                                            break;
   }
}

sint8 GETscTemperaturPD(uint8 ucZomSlot){return scTemperaturPD[ucZomSlot];}

void PUTscTemperaturPD(
      sint8 scInData
   ,  uint8 ucZomSlot
){
   uint8 ucWheelPosition;
   scTemperaturPD[ucZomSlot] = scInData;
   ucWheelPosition = ucGetWPOfCol(ucZomSlot);
   switch(ucWheelPosition){
      case cRadPosVL: NvM_WriteData_TemperatureFL(scInData); break;
      case cRadPosVR: NvM_WriteData_TemperatureFR(scInData); break;
      case cRadPosHL: NvM_WriteData_TemperatureRL(scInData); break;
      case cRadPosHR: NvM_WriteData_TemperatureRR(scInData); break;
      default:                                               break;
   }
}

uint8 GETucRestlebensdauerPD(uint8 ucZomSlot){return ucRestlebensdauerPD[ucZomSlot];}

void PUTucRestlebensdauerPD(
      uint8 ucInData
   ,  uint8 ucZomSlot
){
   ucRestlebensdauerPD[ucZomSlot] = ucInData;
}

void PUTucRSSIsumPD(
      uint8 ucInData
   ,  uint8 ucZomSlot
){
   ucRSSIsumPD[ucZomSlot] = ucInData;
}

void PUTucTelTypePD(
      uint8 ucInData
   ,  uint8 ucZomSlot
){
   ucTelTypePD[ucZomSlot] = ucInData;
}

uint8 GETucTransModePD(uint8 ucZomSlot){return ucTransModePD[ucZomSlot];}

void PUTucTransModePD(
      uint8 ucInData
   ,  uint8 ucZomSlot
){
   ucTransModePD[ucZomSlot] = ucInData;
}

uint16 GETushSensorDefectPD(uint8 ucZomSlot){return ushSensorDefectPD[ucZomSlot];}

void PUTushSensorDefectPD(
      uint16 ushInData
   ,  uint8 ucZomSlot
){
   ushSensorDefectPD[ucZomSlot] = ushInData;
}

uint8 GETucRadpositionPD(uint8 ucZomSlot){return ucGetRadPosAtSlotPDIF(ucZomSlot);}

uint16 PreProcPressAndTempPD(void){
   uint8 ucPres;
   sint8 scTemp;
   uint16 ushSensorfehler = 0;
   ushSensorfehler |= ushCalcAKPressurePD(
         ucGetReDataPressurePD()
      ,  &ucPres
   );
   ushSensorfehler |= ushCalcAKTemperaturePD(
         ucGetReDataTemperaturePD()
      ,  &scTemp
   );
   PutReDataPreProcPressurePD(ucPres);
   PutReDataPreProcTemperaturePD(scTemp);
   return (ushSensorfehler);
}

static uint16 ushCalcAKPressurePD(
      uint8  ucRawPres
   ,  uint8* pucPhyPres
){
   uint16 ushError = 0;
   uint16 ushPsensorAbs;
   switch(ucRawPres){
      case cRE_AK_PRES_INVALID:
         ushError = RE_AK_SF_PRES_FAIL;
         *pucPhyPres = cInvalidREpressure;
         break;

      case cRE_AK_PRES_UNDERFLOW:
         ushError = RE_AK_SF_PRES_UNDERFLOW;
         *pucPhyPres = 0;
         break;

      case cRE_AK_PRES_OVERFLOW:
         ushError = RE_AK_SF_PRES_OVERFLOW;
         *pucPhyPres = 254;
         break;

      default:
         ushPsensorAbs = ((uint16)ucRawPres + ONE_BAR_PRESSURE) - 2u;
         if(ushPsensorAbs > (uint16)GETucPatmoPD()){
            *pucPhyPres = (uint8)(0xFFu & (ushPsensorAbs - GETucPatmoPD()));
            ushError = 0;
         }
         else{
            *pucPhyPres = 0;
            ushError = RE_AK_SF_PRES_UNDERFLOW;
         }
         break;
   }
   return ushError;
}

static uint16 ushCalcAKTemperaturePD(
      uint8  ucRawTemp
   ,  sint8* pscPhyTemp
){
   uint16 ushError = 0;
   switch(ucRawTemp){
      case cRE_AK_TEMP_INVALID:
         ushError = RE_AK_SF_TEMP_FAIL;
         *pscPhyTemp = cInvalidREtemperature;
         break;

      case cRE_AK_TEMP_UNDERFLOW:
         ushError = RE_AK_SF_TEMP_UNDERFLOW;
         *pscPhyTemp = -40;
         break;

      default:
         if(ucRawTemp < cRE_AK_TEMP_OVERFLOW){
            if(ucRawTemp < cRE_AK_TEMP_RANGE_VALUE){
               *pscPhyTemp = (sint8)(ucRawTemp - 52);
            }
            else{
               *pscPhyTemp = (sint8)((cRE_AK_TEMP_RANGE_VALUE - 1) - 52);
            }
         }
         else{
            ushError = RE_AK_SF_TEMP_OVERFLOW;
            *pscPhyTemp = 120;
         }
         break;
   }
   return ushError;
}

void SaveReDataAtBufferPD(uint8 ucZomSlot){
   uint16 ushSensorDefect = 0x0000;
   uint8 ucLocalReDataTelType = 0x00;
   PutReDataPreProcIdPD(ulGetReDataIdPD());
   ucLocalReDataTelType = ucGetReDataTelTypePD();
   if(ucLocalReDataTelType != cTelTypeRotatS){
      ushSensorDefect = PreProcPressAndTempPD();
      if(ucGetReDataPreProcPressurePD() == 0xFF){
         if(ucTyreInvalidPressSurpressionCnt[ucZomSlot] < 50u){
            ucTyreInvalidPressSurpressionCnt[ucZomSlot]++;
         }
         if(ucTyreInvalidPressSurpressionCnt[ucZomSlot] <= NR_OF_SURPRESSED_TELEGRAMS){
            if(ucZomSlot < cAnzRad){
               PutReDataPreProcPressurePD(
                  GETucReifendruckPD(
                     ucZomSlot));
            }
            else{
               PutReDataPreProcPressurePD(
                  0xFF);
            }
         }
         else{
         }
      }
      else{
         ucTyreInvalidPressSurpressionCnt[ucZomSlot] = 0;
      }
   }
   else{
      ushSensorDefect = (RE_AK_SF_PRES_NOT_RECEIVED | RE_AK_SF_TEMP_NOT_RECEIVED);
      if(ucZomSlot < cAnzRad){
         PutReDataPreProcPressurePD(
            GETucReifendruckPD(ucZomSlot)
         );
         PutReDataPreProcTemperaturePD(
            GETscTemperaturPD(ucZomSlot)
         );
      }
      else{
         PutReDataPreProcPressurePD(cInvalidREpressure);
         PutReDataPreProcTemperaturePD(cInvalidREtemperature);
      }
   }
   if(
         (cTelTypeHufStatus      == ucLocalReDataTelType)
      || (cTelTypeHufStatusLearn == ucLocalReDataTelType)
   ){
      PutReDataPreProcRemainingLifeTimePD(
         ucGetReDataRemainingLifeTimePD()
      );
   }
   else{
      if(ucZomSlot < cAnzRad){
         PutReDataPreProcRemainingLifeTimePD(
            GETucRestlebensdauerPD(ucZomSlot)
         );
      }
      else{
         PutReDataPreProcRemainingLifeTimePD(cInvalidRElifeTime);
      }
      ushSensorDefect |= RE_AK_SF_RLT_NOT_RECEIVED;
   }
   PutReDataPreProcTransModePD(
      ucGetReDataStatePD()
   );
   PutReDataPreProcSensorDefectPD(ushSensorDefect);
}

uint8 ucIsReHwDefectPD(uint8 ZomSlot){
   uint8 ucRet = 0x03;
   if(
      0 == (GETushSensorDefectPD(ZomSlot) & RE_AK_SF_HW_DEFECT)
   ){
      if(
            0
         == (
                  GETushSensorDefectPD(ZomSlot)
               &  (
                        RE_AK_SF_PRES_NOT_RECEIVED
                     |  RE_AK_SF_TEMP_NOT_RECEIVED
                     |  RE_AK_SF_MOTION_NOT_RECEIVED
                  )
            )
      ){
         ucRet = (uint8)FALSE;
      }
   }
   else{
      ucRet = (uint8)TRUE;
   }
   return (ucRet & 0x03u);
}

boolean bIsReOverTempPD(uint8 ZomSlot){
   return (
         cRE_AK_TM_MODE_OVERTEMP
      == (
               cRE_AK_TM_MODE_OVERTEMP
            &  GETucTransModePD(ZomSlot)
         )
   )
   ? TRUE
   : FALSE
   ;
}

boolean bIsReLowLifeTimePD(uint8 ZomSlot){
   return (0x01u == GETucRestlebensdauerPD(ZomSlot))
   ? TRUE
   : FALSE
   ;
}

uint8 GETucPatmoPD(void){
   uint8 ret;
   return (
         (ucPatmoPD < LOWEST_ATMOSPHERIC_PRESS)
      || (ucPatmoPD > HIGHEST_ATMOSPHERIC_PRESS)
   )
   ? (uint8)ONE_BAR_PRESSURE
   : ucPatmoPD
   ;
}

void PUTucPatmoPD(
   uint8 ucInData){
   ucPatmoPD = ucInData;
}

void CalcPatmo(void){
   static uint8 uc1secTimer = 0;
   uint8 ucFmmotmax;
   uint16 ushCalcValue;
   static uint32 ulMeanValue;
   ucFmmotmax = 0;
   uc1secTimer++;
   if(uc1secTimer >= TIME_1S_OVER){
      (void)ReceiveGetFmmotmax(&ucFmmotmax);
      if(ucFmmotmax > 0u){
         if((ulMeanValue < (78u * cFMMOTMAXmin)) || (ulMeanValue > (78u * cFMMOTMAXmax))){
            ulMeanValue = (250u * GETucPatmoPD());
         }
         ushCalcValue = (uint16)(78u * ucFmmotmax);
         ulMeanValue = (9u * ulMeanValue) + ushCalcValue;
         ulMeanValue /= 10u;
         ushCalcValue = ((uint16)ulMeanValue) + 39u;
         ushCalcValue /= 250u;
         PUTucPatmoPD((uint8)ushCalcValue);
      }
      uc1secTimer = 0u;
   }
   else{
   }
}

void SaveRotatS(void){
   ucRotL   = tReDataPD.RotatS.ucRL;
   ucSnRotH = tReDataPD.RotatS.ucSnRH;
}

void PutRotatSDataInBuffer(const Type_SwcApplTpms_stTelegramWS* spRxDataIn){
   int i;
   if(ucRotatSTelIndexPut < cWsTelBufferSize){
      tWs_RxRotatSBuf[ucRotatSTelIndexPut].RxDataIn.ulRxTimeStamp = spRxDataIn->ulRxTimeStamp;
      tWs_RxRotatSBuf[ucRotatSTelIndexPut].RxDataIn.uiRxRSSI = spRxDataIn->uiRxRSSI;
      for(i = 0; i < MAX_SIZE_WS_TELEGRAM; i++){
         tWs_RxRotatSBuf[ucRotatSTelIndexPut].RxDataIn.ucaTelegram[i] = spRxDataIn->ucaTelegram[i];
      }
      (void)ReceiveGetVehicleSpeed(
         &tWs_RxRotatSBuf[ucRotatSTelIndexPut].ushVehSpeed);
   }
   ucRotatSTelIndexPut++;
   ucRotatSTelIndexPut %= cWsTelBufferSize;
}

tRxRotatSBuf* pGetRotatSDataTFromBuffer(uint8 ucBufferIndex){return &tWs_RxRotatSBuf[ucBufferIndex];}
uint8 ucGetRotatSDataBufferIndex(void){return ucRotatSTelIndexPut;}

uint16 ushGetRotatSVehSpeed(void){
   uint16 VehicleSpeedValue;
   if(ucRotatSTelIndexGet < cWsTelBufferSize){
      VehicleSpeedValue = tWs_RxRotatSBuf[ucRotatSTelIndexGet].ushVehSpeed;
   }
   else{
      VehicleSpeedValue = 0;
   }
   return VehicleSpeedValue;
}

void DCM_InvIf_RxStatusFieldGetValue(uint8* u8_StatusFieldValue){
   if((cTelTypeHufStatusLearn == tReDataPD.AK35def.ucCmdID) || (cTelTypeHufStatus == tReDataPD.AK35def.ucCmdID)){
      u8_StatusFieldValue[0] = (uint8)tReDataPD.HufStatus.ucByte1Status;
      u8_StatusFieldValue[1] = (uint8)tReDataPD.HufStatus.ucByte2Status;
   }
   else{
      u8_StatusFieldValue[0] = 0;
      u8_StatusFieldValue[1] = 0;
   }
}

uint8 DCM_InvIf_PressLastRxIDGetValue(void){return ucGetReDataPreProcPressurePD();}
sint8 DCM_InvIf_TempLastRxIDGetValue(void){return scGetReDataPreProcTemperaturePD();}

void DCM_InvIf_LastRxIDGetValue(
   uint8* u8_LastIdReceived){
   u8_LastIdReceived[0] = (uint8)tReDataPD.Struc.aucTelDat[1];
   u8_LastIdReceived[1] = (uint8)tReDataPD.Struc.aucTelDat[2];
   u8_LastIdReceived[2] = (uint8)tReDataPD.Struc.aucTelDat[3];
   u8_LastIdReceived[3] = (uint8)tReDataPD.Struc.aucTelDat[4];
}

uint8 DCM_InvIf_TelTypeCurrIDGetValue(void){return ucGetReDataTelTypePD();}

void DCM_InvIf_RFTimeStampGetValue(
   uint8* u8_TimeStampValue){
   u8_TimeStampValue[0] = (uint8)((tReDataPD.Struc.ulTimeStamp & 0x00FF0000U) >> 16U);
   u8_TimeStampValue[1] = (uint8)((tReDataPD.Struc.ulTimeStamp & 0x0000FF00U) >> 8U);
   u8_TimeStampValue[2] = (uint8)(tReDataPD.Struc.ulTimeStamp & 0x000000FFU);
}

uint8 DCM_InvIf_RawRSSIGetValue(void){return (uint8)tReDataPD.Struc.ucAvg;}
uint8 DCM_InvIf_RecEventGetCntValue(void){return ucRecEventPD;}

void DCM_InvIf_RawRfTelGetValue(
   uint8 u8_StartPosition,
   uint8 u8_NumberOfBytesToCopy,
   uint8 u8_RxTelegBytesValues[]){
   uint8 u8_LocalCnt;
   uint8 u8TGSize = 0;
   u8TGSize = ucGetLen4Cmd(
      tReDataPD.Struc.aucTelDat[0]);
   if((u8TGSize != 0) && (u8TGSize != 0xFFU)){
      u8TGSize = u8TGSize + 1;
   }
   for(u8_LocalCnt = (u8_StartPosition);
         u8_LocalCnt < ((u8_StartPosition) + u8_NumberOfBytesToCopy);
         u8_LocalCnt++){
      if(u8_LocalCnt < u8TGSize){
         u8_RxTelegBytesValues[u8_LocalCnt - u8_StartPosition] = tReDataPD.Struc.aucTelDat[u8_LocalCnt];
      }
      else{
         u8_RxTelegBytesValues[u8_LocalCnt - u8_StartPosition] = 0x00;
      }
   }
}

uint8 DCM_InvIf_AllReceivedTelegGetValue(void){return U8_AllReceivedTelegCnt;}
