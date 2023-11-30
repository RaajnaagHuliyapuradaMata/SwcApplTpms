#ifndef InfoTyreX_h
#define InfoTyreX_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "EeCommonBlockX.h"

typedef uint16  InfoTyrePresType;
typedef uint16  InfoTyreTempType;

#define cTyrePressureInvalidValueITY                ( (InfoTyrePresType) 0xFFFFu)
#define cTyrePressureNotAvailableValueITY           ( (InfoTyrePresType) 0xFFFEu)
#define cTyrePressureFuncIfaceNotAvailableValueITY  ( (InfoTyrePresType) 0xFFFDu)
#define cTyrePressureNotPresentValueITY             ( (InfoTyrePresType) 0xFFFCu)
#define cTyreTemperatureInvalidValueITY             ( (InfoTyreTempType) 0xFFFFu)
#define cTyreTemperatureNotAvailableValueITY        ( (InfoTyreTempType) 0xFFFEu)
#define cITYTyreTemperatureOffsetValue              ( (uint16) 40)
#define cFastListCycleTime (20)
#define cSlowListCycleTime (500)
#define cDefDisplayTimeoutVal (80)
#define cNotifyInitITY            ( (uint8) 0)
#define cNotifyTelRecITY          ( (uint8) 1)
#define cNotifyRcpChangedITY      ( (uint8) 2)
#define cNotifyBeladungChangedITY ( (uint8) 3)
#define cSetCoolingDataInitITY    ( (uint8) 0)
#define cSetCoolingDataInvalidITY ( (uint8) 1)
#define cSetCoolingDataCvalITY    ( (uint8) 2)
#define cSetCoolingDataWvalITY    ( (uint8) 3)
#define cSetCoolingDataReStartITY ( (uint8) 4)

typedef struct TyreData_Struct{
	 uint8 Width;
	 uint8 Carcass;
	 uint8 Radius;
	 uint8 Runflat;
	 uint8 Season;
	 uint8 LoadIndex;
	 uint8 SpeedIndex;
	 uint8 SideRelation;
   uint8 Age;
   uint8 Abrasion;
   uint8 LengthOfRun;
}TyreDataType;

extern void    InitITY( Rte_Instance self);
extern void    MainFunctionITY( Rte_Instance self);
extern void    GetTyrePressureValueITY( Rte_Instance self, uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr);
extern void    GetTyreTemperatureValueITY( Rte_Instance self, uint16* pushTfl, uint16* pushTfr, uint16* pushTrl, uint16* pushTrr);
extern void    GetRelatedPressureValueITY( Rte_Instance self, uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr);
extern uint16  ushGetMaxCoolingDownTimeITY(void);
extern uint16  ushGetCorHoldOffTimeITY(void);
extern void    GetStTyrITY( uint8* pucQuFnTyrInfo, uint8* pucQuTpl, uint8* pucQuTfai);
extern boolean GetListTyreDataITY( const uint8 ucIndex, TyreDataType * ListTyreData);
extern boolean GetFAxisTyreDataITY( Rte_Instance self, TyreDataType * FATyreData);
extern boolean GetRAxisTyreDataITY( Rte_Instance self, TyreDataType * RATyreData);
extern void StartDisplayConfTimeoutITY( uint8 TimeoutVal);
extern uint8 GetDisplayConfTimeoutITY(void);
extern void NotificationITY( Rte_Instance self, uint8 ucNotificationState, uint8 ucSlotNo);
extern void GetAvlPTyreCoolingValITY( uint8 ucHistSlot, uint8* pucAvlPTyre_warm, sint8* pscAvlTTyre_warm, uint8* pucAvlPTyre_kalt, sint8* pscAvlTTyre_kalt, uint8* pucAvlPTyre_t, sint8*  pscAvlTTyre_t, uint8* pucTarPTyre_warm, uint8* pucTarPTyre_kalt, sint8* pscTarTTyre_kalt, uint8*  pucTarPTyre_t, uint16* pushElapsedCoolingTime, uint16* pushTimeTicks, uint32* pulCoolingCaptTime);
extern void StartStChangeTimeITY(uint8 TimeoutVal);
extern uint8 GetStChangeTimeITY(void);

#ifdef __cplusplus
}
#endif

#endif
