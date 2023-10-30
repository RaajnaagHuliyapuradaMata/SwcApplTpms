#ifndef _procdat_X_H
#define _procdat_X_H

#include "tss_stdx.hpp"
#include "cd_decoder_x.hpp"

#define cRE_AK_SUPPLIER_INVALID       ((uint8) 0x00)
#define cRE_AK_SUPPLIER_AUTONET       ((uint8) 0x01)
#define cRE_AK_SUPPLIER_BERU          ((uint8) 0x02)
#define cRE_AK_SUPPLIER_CONTI         ((uint8) 0x03)
#define cRE_AK_SUPPLIER_TRW           ((uint8) 0x04)
#define cRE_AK_SUPPLIER_SCHRADER      ((uint8) 0x05)
#define cRE_AK_SUPPLIER_UNKNOWN       ((uint8) 0x0F)
#define cRE_AK_RL_SPIN_ACT            ((uint8) 0x03)
#define cRE_AK_RL_SPIN_HIST           ((uint8) 0x0C)
#define cRE_AK_RS_TOGGLE              ((uint8) 0x10)
#define cRE_AK_RL_TOGGLE              ((uint8) 0x20)
#define cRE_AK_RL_CONFIRM             ((uint8) 0x40)
#define cRE_AK_RS_RL_FAILED           ((uint8) 0x80)
#define cRE_AK_PRES_INVALID           ((uint8) 0x00)
#define cRE_AK_PRES_UNDERFLOW         ((uint8) 0x01)
#define cRE_AK_PRES_OVERFLOW          ((uint8) 0xff)
#define cRE_AK_TEMP_INVALID           ((uint8) 0x00)
#define cRE_AK_TEMP_UNDERFLOW         ((uint8) 0x01)
#define cRE_AK_TEMP_OVERFLOW          ((uint8) 0xf0)
#define cRE_AK_TEMP_RANGE_VALUE       ((uint8) 0xAD)
#define cRE_AK_TM_MODE_STANDSTILL    ((uint8) 0x00)
#define cRE_AK_TM_MODE_DRIVE         ((uint8) 0x01)
#define cRE_AK_TM_MODE_LEARNDRIVE    ((uint8) 0x02)
#define cRE_AK_TM_MODE_OVERTEMP      ((uint8) 0x04)
#define cRE_AK_TM_EVENT_DP           ((uint8) 0x10)
#define cRE_AK_TM_EVENT_LF_TRIG      ((uint8) 0x20)
#define cRE_AK_RS                     ((uint8) 0x01)
#define RE_AK_SF_NO_ERROR             ((uint16) 0x0000)
#define RE_AK_SF_RS_RL_FAIL           ((uint16) 0x0002)
#define RE_AK_SF_HW_DIAG              ((uint16) 0x0004)
#define RE_AK_SF_MS_DIAG              ((uint16) 0x0008)
#define RE_AK_SF_PRES_FAIL            ((uint16) 0x0010)
#define RE_AK_SF_PRES_INVALID         ((uint16) 0x0020)
#define RE_AK_SF_PRES_UNDERFLOW       ((uint16) 0x0040)
#define RE_AK_SF_PRES_OVERFLOW        ((uint16) 0x0080)
#define RE_AK_SF_TEMP_INVALID         ((uint16) 0x0100)
#define RE_AK_SF_TEMP_UNDERFLOW       ((uint16) 0x0200)
#define RE_AK_SF_TEMP_OVERFLOW        ((uint16) 0x0400)
#define RE_AK_SF_TEMP_FAIL            ((uint16) 0x0800)
#define RE_AK_SF_PRES_NOT_RECEIVED    ((uint16) 0x1000)
#define RE_AK_SF_TEMP_NOT_RECEIVED    ((uint16) 0x2000)
#define RE_AK_SF_RLT_NOT_RECEIVED     ((uint16) 0x4000)
#define RE_AK_SF_MOTION_NOT_RECEIVED  ((uint16) 0x8000)
#define RE_AK_SF_HW_DEFECT            ((uint16) 0x0810)
#define RE_AK_SF_MESS_INVALID         ((uint16) 0x0000)
#define cRX_TIME_STAMP_INVALID 0xFFFFFFFFU

extern uint8 ucRotatSTelIndexGet;

extern uint8 GETucReifendruckPD(uint8 ucZomSlot);
extern void PUTucReifendruckPD(uint8 ucInData, uint8 ucZomSlot);
extern uint8 ucGetValidTyrePressureRelAtPosPD(uint8 ucRadPos);
extern uint8 ucGetValidTemperatureRelAtPosPD(uint8 ucRadPos);
extern sint8 GETscTemperaturPD(uint8 ucZomSlot);
extern void PUTscTemperaturPD(sint8 scInData, uint8 ucZomSlot);
extern uint8 GETucRestlebensdauerPD(uint8 ucZomSlot);
extern void PUTucRestlebensdauerPD(uint8 ucInData, uint8 ucZomSlot);
extern void PUTucRSSIsumPD(uint8 ucInData, uint8 ucZomSlot);
extern void PUTucTelTypePD(uint8 ucInData, uint8 ucZomSlot);
extern uint8 GETucTransModePD(uint8 ucZomSlot);
extern void PUTucTransModePD(uint8 ucInData, uint8 ucZomSlot);
extern uint16 GETushSensorDefectPD(uint8 ucZomSlot);
extern void PUTushSensorDefectPD(uint16 ushInData, uint8 ucZomSlot);
extern uint8 GETucRadpositionPD(uint8 ucZomSlot);
extern void InitPD(void);
extern uint8 ucGetSlotNoAtPosPD(uint8 ucRadPos);
extern void ReadReDataFromRingBufferPD(void);
extern void RSSIBalancePD(uint8 ucOffsetVal);
extern void ClearReDataInSlotPD(uint8 ucZomSlot);
extern uint32 ulGetReDataIdPD(void);
extern uint8 ucGetReDataPressurePD(void);
extern uint8 ucGetReDataTemperaturePD(void);
extern uint8 ucGetReDataRemainingLifeTimePD(void);
extern uint8 ucGetReDataStatePD(void);
extern uint8 ucGetReDataRssiAvgPD(void);
extern uint16 ushGetReDataTimeStampPD(void);
extern uint8 ucGetReDataTelTypePD(
   void);
extern uint8 ucGetReDataTGCounter(void);
extern tPreBuf* pGetCurTel(void);
extern uint32 ulGetReDataPreProcIdPD(void);
extern void   PutReDataPreProcIdPD(uint32 ulID);
extern uint8  ucGetReDataPreProcPressurePD(void);
extern void   PutReDataPreProcPressurePD(uint8 ucPressure);
extern sint8  scGetReDataPreProcTemperaturePD(void);
extern void   PutReDataPreProcTemperaturePD(sint8 scTemperature);
extern uint8  ucGetReDataPreProcRemainingLifeTimePD(void);
extern void   PutReDataPreProcRemainingLifeTimePD(uint8 ucRemainingLifeTime);
extern uint8  ucGetReDataPreProcTransModePD(void);
extern void   PutReDataPreProcTransModePD(uint8 ucTransMode);
extern uint16 ushGetReDataPreProcSensorDefectPD(void);
extern void   PutReDataPreProcSensorDefectPD(uint16 ushSensorDefect);
extern uint8  ucGetReDataPreProcWheelDirPD(void);
extern void   PutReDataPreProcWheelDirPD(uint8 ucWheelDir);
extern void SaveReDataAtBufferPD(uint8 ucZomSlot);
extern uint16 PreProcPressAndTempPD(void);
extern uint8 ucIsReHwDefectPD( uint8 ZomSlot );
extern boolean bIsReOverTempPD( uint8 ZomSlot );
extern boolean bIsReLowLifeTimePD( uint8 ZomSlot );
extern void PUTucPatmoPD(uint8 ucInData);
extern uint8 GETucPatmoPD(void);
extern void CalcPatmo(void);
extern void SaveRotatS(void);
extern void PutRotatSDataInBuffer(const tsWS_RxDataIn* spRxDataIn);
extern tRxRotatSBuf* pGetRotatSDataTFromBuffer(uint8 ucBufferIndex);
extern uint8 ucGetRotatSDataBufferIndex(void);
extern uint16 ushGetRotatSVehSpeed(void);
extern void IncrementAllReceivedTelegCnt(void);

#endif
