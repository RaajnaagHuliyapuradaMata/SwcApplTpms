#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "state_fzzX.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

#define VEHSTATE_RET_OK  ( (sint8) 0 )
#define VEHSTATE_RET_ERR ( (sint8) 1 )
#define VEHSTATE_RESERVED ( (uint8) 2 )

#pragma PRQA_MESSAGES_OFF 3453

#define HYSTSetFlag(x)   ( HysteresisFlags.ucBitfieldValue |= ((uint8)(1u << (x))) )
#define HYSTClearFlag(x) ( HysteresisFlags.ucBitfieldValue &= ((uint8)~((uint8)(1u << (x)))) )
#define HYSTIsFlagSet(x) ( ((HysteresisFlags.ucBitfieldValue & ((uint8)(1u << (x)))) == ((uint8)(1u << (x)))) ? TRUE : FALSE )
#define HYSTERESIS_MAX ( (uint8) 2 )

#pragma PRQA_MESSAGES_ON

#define TIME_30S_OVER  ( (uint16)  30 )
#define STOP_COUNTER_MAX_VALUES     ((uint8)16)

typedef struct {
   uint8 ucBitfieldValue;
} tHysteresisFlags;

typedef struct {
   uint16 hystActiveValue;
   uint16 hystInactiveValue;
   uint8 ucCallbackNr;
} tHysteresisData;

typedef struct {
   uint16 hystActualValue;
   uint16 hystLastValue;
} tHysteresisValues;

static tHysteresisFlags HysteresisFlags;
static tHysteresisValues HysteresisValues[HYSTERESIS_MAX];
static uint8 uc30secTimer2;
static uint8 ucStopEventsCounter;

void VehStateInit(
   void);
static sint8 VehStateGetHysteresisHandle(
   uint8 signalHandle,
   uint8* pHystHandle);
void VehStateTriggerHysteresis(
   uint8 signalHandle,
   uint16 actVelocity);
void VehStateGetKL15(
   boolean* bpKL15);
boolean VehStateGetVehicleRollingState(
   void);
boolean VehStateGetRoadmode(
   void);
boolean VehStateGetReDiagActiveState(
   void);
static void VehStateCallbackVehicleRollingChange(
   void);
static void VehStateCallbackReDiagActiveChange(
   void);
uint8 ReceiveGetVehicleSpeed(
   uint16* pVehSpeed);
uint8 ReceiveGetDirection(
   uint8* pucDirection);
uint8 ReceiveGetOutdoorTemp(
   sint16* pODTemp);
uint8 ReceiveGetTrefTemperature(
   sint8* pODTemp);
boolean ReceiveGetVehicleSpeedValidity(
   void);
uint8 ReceiveGetFmmotmax(
   uint8* pucFmmotmaxPressure);
void OperateAtmosphericPressure(
   void);

void VehStateInit(
   void){
   uint8 i;
   HysteresisFlags.ucBitfieldValue = 0u;
   for(i = 0u; i < HYSTERESIS_MAX; i++){
      HysteresisValues[i].hystActualValue = 0u;
      HysteresisValues[i].hystLastValue = 0u;
   }
   uc30secTimer2 = 0;
   ucStopEventsCounter = 0;
}

static sint8 VehStateGetHysteresisHandle(
   uint8 signalHandle,
   uint8* pHystHandle){
   uint8 i;
   sint8 retVal;
   static const uint8 sigHandle2hystHandle[HYSTERESIS_MAX] = {
      VEHSTATE_VEHICLE_SPEED_HYST_ID,
      VEHSTATE_REDIAG_ACTIVE_HYST_ID};
   retVal = VEHSTATE_RET_ERR;
   for(i = 0u; i < HYSTERESIS_MAX; i++){
      if(signalHandle == sigHandle2hystHandle[i]){
         *pHystHandle = i;
         retVal = VEHSTATE_RET_OK;
      }
   }
   return (retVal);
}

void VehStateTriggerHysteresis(
   uint8 signalHandle,
   uint16 actVelocity){
   uint8 hystHandle;
   static const tHysteresisData HysteresisData[HYSTERESIS_MAX + 1] = {
      {
         (uint16)(7),
         (uint16)(3),
         VEHSTATE_VEHICLE_SPEED_HYST_ID},
      {
         (uint16)(30),
         (uint16)(25),
         VEHSTATE_REDIAG_ACTIVE_HYST_ID},
      {
         (uint16)(0),
         (uint16)(0),
         VEHSTATE_RESERVED}};
   if(VehStateGetHysteresisHandle(
      signalHandle,
      &hystHandle) == VEHSTATE_RET_OK){
      HysteresisValues[hystHandle].hystLastValue = HysteresisValues[hystHandle].hystActualValue;
      HysteresisValues[hystHandle].hystActualValue = actVelocity;
      if((HysteresisValues[hystHandle].hystActualValue >= HysteresisData[hystHandle].hystActiveValue) && (HysteresisValues[hystHandle].hystLastValue < HysteresisData[hystHandle].hystActiveValue) && (HYSTIsFlagSet(hystHandle) == FALSE)){
         HYSTSetFlag(
            hystHandle);
         if(HysteresisData[hystHandle].ucCallbackNr == VEHSTATE_VEHICLE_SPEED_HYST_ID){
            VehStateCallbackVehicleRollingChange();
         }
         else if(HysteresisData[hystHandle].ucCallbackNr == VEHSTATE_REDIAG_ACTIVE_HYST_ID){
            VehStateCallbackReDiagActiveChange();
         }
         else{
         }
      }
      else if((HysteresisValues[hystHandle].hystActualValue <= HysteresisData[hystHandle].hystInactiveValue) && (HysteresisValues[hystHandle].hystLastValue > HysteresisData[hystHandle].hystInactiveValue) && (HYSTIsFlagSet(hystHandle) == TRUE)){
         HYSTClearFlag(
            hystHandle);
         if(HysteresisData[hystHandle].ucCallbackNr == VEHSTATE_VEHICLE_SPEED_HYST_ID){
            VehStateCallbackVehicleRollingChange();
         }
         else if(HysteresisData[hystHandle].ucCallbackNr == VEHSTATE_REDIAG_ACTIVE_HYST_ID){
            VehStateCallbackReDiagActiveChange();
         }
         else{
         }
      }
      else{
      }
   }
}

void VehStateGetKL15(
   boolean* bpKL15){
   switch(g_sEnv_Data.ucIgnition){
      case VEH_IGN_ON: {
         *bpKL15 = g_sEnv_Data.ucIgnition;
         break;
      }
      case VEH_IGN_OFF: {
         *bpKL15 = g_sEnv_Data.ucIgnition;
         break;
      }
      case VEH_IGN_UNKNOWN:
      default: {
         *bpKL15 = RECEIVE_KL15_SUBSTVAL;
         break;
      }
   }
}

boolean VehStateGetVehicleRollingState(
   void){
   boolean bHelp;
   if(HYSTIsFlagSet(
      VEHSTATE_VEHICLE_SPEED_HYST_ID)){
      bHelp = TRUE;
   }
   else{
      bHelp = FALSE;
   }
   return (bHelp);
}

boolean VehStateGetRoadmode(
   void){
   return g_sEnv_Data.bRoadMode;
}

boolean VehStateGetReDiagActiveState(
   void){
   boolean bHelp;
   if(HYSTIsFlagSet(
      VEHSTATE_REDIAG_ACTIVE_HYST_ID)){
      bHelp = TRUE;
   }
   else{
      bHelp = FALSE;
   }
   return (bHelp);
}

static void VehStateCallbackVehicleRollingChange(
   void){
   if(VehStateGetVehicleRollingState() == TRUE){
      SetBitFahrzeugzustandFZZ(
         cFAHRZEUG_FAEHRT);
   }
   else{
      ClearBitFahrzeugzustandFZZ(
         cFAHRZEUG_FAEHRT);
      ucStopEventsCounter++;
      ucStopEventsCounter = ucStopEventsCounter % STOP_COUNTER_MAX_VALUES;
   }
}

static void VehStateCallbackReDiagActiveChange(
   void){
   if(VehStateGetReDiagActiveState() == TRUE){
      EvReDiagActiveFZZ();
   }
   else{
      EvReDiagInactiveFZZ();
   }
}

uint8 ReceiveGetVehicleSpeed(
   uint16* pVehSpeed){
   uint8 l_ucRetVal = TRUE;
   if(g_sEnv_Data.uiVehSpeed < 1023){
      *pVehSpeed = g_sEnv_Data.uiVehSpeed;
   }
   else{
      *pVehSpeed = RECEIVE_VEHSPEED_SUBSTVAL;
      l_ucRetVal = FALSE;
   }
   return (l_ucRetVal);
}

uint8 ReceiveGetDirection(
   uint8* pucDirection){
   uint8 l_ucRetVal = TRUE;
   switch(g_sEnv_Data.ucVehDirection){
      case 0x00U: {
         *pucDirection = cDriveDirForward;
         break;
      }
      case 0x01U: {
         *pucDirection = cDriveDirBackward;
         break;
      }
      case 0x02U: {
         *pucDirection = RECEIVE_DIRECTION_SUBSTVAL;
         break;
      }
      default: {
         *pucDirection = RECEIVE_DIRECTION_SUBSTVAL;
         l_ucRetVal = FALSE;
         break;
      }
   }
   return (l_ucRetVal);
}

uint8 ReceiveGetOutdoorTemp(
   sint16* pODTemp){
   sint16 l_siTemp = 0;
   uint8 l_ucRetVal = TRUE;
   if(0xFF != g_sEnv_Data.ucAmbTemperature){
      l_siTemp = (sint16)(g_sEnv_Data.ucAmbTemperature >> 1);
      l_siTemp = l_siTemp - 40;
      *pODTemp = l_siTemp;
   }
   else{
      *pODTemp = RECEIVE_TEMP_SUBSTVAL;
      l_ucRetVal = FALSE;
   }
   return l_ucRetVal;
}

uint8 ReceiveGetTrefTemperature(
   sint8* pODTemp){
   uint8 l_ucRetVal = TRUE;
   sint16 l_siODTemp = 0;
   l_ucRetVal = ReceiveGetOutdoorTemp(
      &l_siODTemp);
   if(FALSE == l_ucRetVal){
      *pODTemp = RECEIVE_TEMP20_SUBSTVAL;
   }
   else{
      *pODTemp = (sint8)(l_siODTemp);
   }

   return (l_ucRetVal);
}

boolean ReceiveGetVehicleSpeedValidity(
   void){
   boolean bValid = FALSE;
   uint16 u16Temp = 0;
   bValid = ReceiveGetVehicleSpeed(
      &u16Temp);
   return (bValid);
}

uint8 ReceiveGetFmmotmax(
   uint8* pucFmmotmaxPressure){
   uint8 l_ucRetVal = TRUE;
   if(g_sEnv_Data.ucAthmosPressure != 0xFF){
      if(uc30secTimer2 >= TIME_30S_OVER){
         if((g_sEnv_Data.ucAthmosPressure >= cFMMOTMAXmin) && (g_sEnv_Data.ucAthmosPressure <= cFMMOTMAXmax)){
            *pucFmmotmaxPressure = (uint8)(g_sEnv_Data.ucAthmosPressure);
         }
         else{
            *pucFmmotmaxPressure = cFMMOTMAXnotValid;
         }
      }
      else{
         *pucFmmotmaxPressure = cFMMOTMAXnotValid;
      }
   }
   else{
      *pucFmmotmaxPressure = RECEIVE_FMMOTMAX_SUBSTVAL;
      l_ucRetVal = FALSE;
   }
   return (l_ucRetVal);
}

void OperateAtmosphericPressure(
   void){
   if(uc30secTimer2 >= TIME_30S_OVER){
   }
   else{
      uc30secTimer2++;
   }
}

uint16 DCM_InvIf_SpeedVehicGetValue(
   void){
   uint16 LocalVehicleSpeedValue;
   uint8 SpeedValidity;
   SpeedValidity = ReceiveGetVehicleSpeed(
      &LocalVehicleSpeedValue);
   if(FALSE == SpeedValidity){
      LocalVehicleSpeedValue = 0xffff;
   }
   else{
   }
   return LocalVehicleSpeedValue;
}

uint8 DCM_InvIf_PressAmbientGetValue(
   void){
   return g_sEnv_Data.ucAthmosPressure;
}

uint8 DCM_InvIf_NoiseLevelGetValue(
   void){
   return (uint8)(g_sEnv_Data.uiNoiseRSSI & 0x00FF);
}

uint8 DCM_InvIf_StopEventsGetCntValue(
   void){
   return ucStopEventsCounter;
}

uint8 DCM_InvIf_VehDirectionGetValue(
   void){
   return g_sEnv_Data.ucVehDirection;
}

