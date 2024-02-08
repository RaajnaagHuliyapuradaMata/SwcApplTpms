

#ifndef HUF_DTC_IF_HEADER_
#define HUF_DTC_IF_HEADER_

#include "CfgSwcApplTpms.hpp"
#include "iTpms_Interface.hpp"

#define cDTC_IS_CLEARED                 0x00U
#define cDTC_WAS_DELETED_TROUGH_DIAG    0x01U
#define cDTC_STATE_CHANGED              0x02U

#define cERROR_CODE_INACTIVE          (uint8)0xFF

//#define cZO_ERR_BCM_INTERNAL_FAULT              cERROR_CODE_INACTIVE// RST: don't use this for Rivian! (uint8)E_TPMS_ERROR_NOT_FUNCTIONING_DUE_TO_ECU_INTERNAL_FAULT
#define cZO_ERR_BCM_INTERNAL_FAULT              (uint8)E_TPMS_ERROR_NOT_FUNCTIONING_DUE_TO_ECU_INTERNAL_FAULT //RST: 6.8.21: wieder rein. Macht sonst vermutlich Probleme
#define cZO_ERR_NO_QUALIFIED_SENSOR_SIGNALS     (uint8)E_TPMS_ERROR_NO_QUALIFIED_SENSOR_SIGNALS
#define cZuWenigRadsensoren                     cERROR_CODE_INACTIVE
#define cRadzuordnungNichtMoeglich              cERROR_CODE_INACTIVE
#define cZO_ERR_DETECT_TO0_MANY_SENSORS         (uint8)E_TPMS_ERROR_DETECTED_TOO_MANY_SENSORS

#define U8_ECU_NOT_DEFECT             ((uint8)0x00)
#define U8_ECU_DEFECT_FAULT_BIT_SET   ((uint8)0x01)
#define U8_ECU_DEFECT_CYCLIC_TASK     ((uint8)0x02)

#define cCANSpeedSignalInvalidError             (uint8)E_TPMS_ERROR_WS_MISSING_DURING_CONTINUOUS_INVALID_SPEED

#ifdef DETECT_SYMC_WALLOC_DTC
#define cZO_ERR_AXIS_LOCATION                 (uint8)E_TPMS_ERROR_AXLE_LOCATE_FAIL
#define cZO_ERR_SIDE_LOCATION                 cERROR_CODE_INACTIVE
#define cZO_ERR_FAILED_TRIES                  (uint8)E_TPMS_ERROR_AUTOLOCATION_FAILED
#else
#define cZO_ERR_AXIS_LOCATION                 (uint8)E_TPMS_ERROR_AXLE_LOCATE_FAIL
#endif

#define cZO_ERR_WS_BATTERY_LOW_FL               (uint8)E_TPMS_ERROR_WS_LIFE_TIME_FL_CNT_LOW
#define cZO_ERR_WS_DEFECT_FL                    (uint8)E_TPMS_ERROR_WS_DEFECT_FL
#define cZO_ERR_WS_MISSING_FL                   (uint8)E_TPMS_ERROR_WS_MISSING_FL

#define cVLHarteWarnung                         cERROR_CODE_INACTIVE
#define cVLMindestdruckUnterschritten           cERROR_CODE_INACTIVE
#define cVLWarngrenzeUnterschritten             cERROR_CODE_INACTIVE
#define cVLBelGeschwUeberschritten              cERROR_CODE_INACTIVE
#define cVLFremdsender                          cERROR_CODE_INACTIVE
#define cVLTempKeinEmpfang                      cERROR_CODE_INACTIVE
#define cZO_ERR_WS_OVERTEMPERATURE_FL           (uint8)E_TPMS_ERROR_WS_OVER_TEMP_FL

#define cZO_ERR_WS_BATTERY_LOW_FR               (uint8)E_TPMS_ERROR_WS_LIFE_TIME_FR_CNT_LOW
#define cZO_ERR_WS_DEFECT_FR                    (uint8)E_TPMS_ERROR_WS_DEFECT_FR
#define cZO_ERR_WS_MISSING_FR                   (uint8)E_TPMS_ERROR_WS_MISSING_FR

#define cVRHarteWarnung                         cERROR_CODE_INACTIVE
#define cVRMindestdruckUnterschritten           cERROR_CODE_INACTIVE
#define cVRWarngrenzeUnterschritten             cERROR_CODE_INACTIVE
#define cVRBelGeschwUeberschritten              cERROR_CODE_INACTIVE
#define cVRFremdsender                          cERROR_CODE_INACTIVE
#define cVRTempKeinEmpfang                      cERROR_CODE_INACTIVE
#define cZO_ERR_WS_OVERTEMPERATURE_FR           (uint8)E_TPMS_ERROR_WS_OVER_TEMP_FR

#define cZO_ERR_WS_BATTERY_LOW_RL               (uint8)E_TPMS_ERROR_WS_LIFE_TIME_RL_CNT_LOW
#define cZO_ERR_WS_DEFECT_RL                    (uint8)E_TPMS_ERROR_WS_DEFECT_RL
#define cZO_ERR_WS_MISSING_RL                   (uint8)E_TPMS_ERROR_WS_MISSING_RL

#define cHLHarteWarnung                         cERROR_CODE_INACTIVE
#define cHLMindestdruckUnterschritten           cERROR_CODE_INACTIVE
#define cHLWarngrenzeUnterschritten             cERROR_CODE_INACTIVE
#define cHLBelGeschwUeberschritten              cERROR_CODE_INACTIVE
#define cHLFremdsender                          cERROR_CODE_INACTIVE
#define cHLTempKeinEmpfang                      cERROR_CODE_INACTIVE
#define cZO_ERR_WS_OVERTEMPERATURE_RL           (uint8)E_TPMS_ERROR_WS_OVER_TEMP_RL

#define cZO_ERR_WS_BATTERY_LOW_RR               (uint8)E_TPMS_ERROR_WS_LIFE_TIME_RR_CNT_LOW
#define cZO_ERR_WS_DEFECT_RR                    (uint8)E_TPMS_ERROR_WS_DEFECT_RR
#define cZO_ERR_WS_MISSING_RR                   (uint8)E_TPMS_ERROR_WS_MISSING_RR

#define cHRHarteWarnung                         cERROR_CODE_INACTIVE
#define cHRMindestdruckUnterschritten           cERROR_CODE_INACTIVE
#define cHRWarngrenzeUnterschritten             cERROR_CODE_INACTIVE
#define cHRBelGeschwUeberschritten              cERROR_CODE_INACTIVE
#define cHRFremdsender                          cERROR_CODE_INACTIVE
#define cHRTempKeinEmpfang                      cERROR_CODE_INACTIVE
#define cZO_ERR_WS_OVERTEMPERATURE_RR           (uint8)E_TPMS_ERROR_WS_OVER_TEMP_RR

#define cRRBatterieLow                          cERROR_CODE_INACTIVE
#define cRRSensorfehler                         cERROR_CODE_INACTIVE
#define cRRUebertragungskanalDefekt             cERROR_CODE_INACTIVE

#define cRRSchnellerDruckverlust                cERROR_CODE_INACTIVE
#define cRRMindestdruckUnterschritten           cERROR_CODE_INACTIVE
#define cRRWarngrenzeUnterschritten             cERROR_CODE_INACTIVE
#define cRRBelGeschwUeberschritten              cERROR_CODE_INACTIVE
#define cRRFremdsender                          cERROR_CODE_INACTIVE
#define cRRTempKeinEmpfang                      cERROR_CODE_INACTIVE
#define cRRTemperaturabschaltung                cERROR_CODE_INACTIVE

#define cZO_ERR_WS_BATTERY_LOW_XX               cERROR_CODE_INACTIVE
#define cZO_ERR_WS_DEFECT_XX                    (uint8)E_TPMS_ERROR_WS_DEFECT_UNKNOWN_POS
#define cZO_ERR_WS_MISSING_XX                   (uint8)E_TPMS_ERROR_WS_MISSING_UNKNOWN_POS

#define cSchnellerDruckverlust                  cERROR_CODE_INACTIVE
#define cMindestdruckUnterschritten             cERROR_CODE_INACTIVE
#define cWarngrenzeUnterschritten               cERROR_CODE_INACTIVE
#define cBelGeschwUeberschritten                cERROR_CODE_INACTIVE
#define cZO_ERR_RF_INTERFERENCE                 (uint8)E_TPMS_ERROR_RF_INTERFERENCE
#define cTempKeinEmpfang                        cERROR_CODE_INACTIVE
#define cZO_ERR_WS_OVERTEMPERATURE_XX           cERROR_CODE_INACTIVE

extern uint8 DTC_IsDTCInActiveState[4];
extern uint8 DTC_StatusOfDTC;

extern void Init_DTC(void);
extern void SetCurrentErrorERR(uint8 ucCurrentExtErrorIndex);
extern void ResetCurrentErrorERR(uint8 ucCurrentExtErrorIndex);
extern void DeleteCurrentErrorERR(uint8 ucCurrentExtErrorIndex);

extern void DTC_SetDTCActiveStatus(uint8 u8DTCToSet);
extern void DTC_DeleteDTCActiveStatus(uint8 u8DTCToDelete);

extern boolean DTC_GetActiveStatusOfDTC(uint8 u8DTCNumber);

#pragma PRQA_NO_SIDE_EFFECTS DTC_GetActiveStatusOfDTC

extern void DTC_SaveActiveStatustoEE(void);
extern void DTC_RestoreActiveStatusfromEE(void);

#endif

