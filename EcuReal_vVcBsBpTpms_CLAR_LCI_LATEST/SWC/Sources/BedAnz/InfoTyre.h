#ifndef InfoTyre_h
#define InfoTyre_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "InfoTyreX.h"

#define cQuFnTyrInfo_Ready          ( (uint8) 0x20)
#define cQuFnTyrInfo_Init           ( (uint8) 0x80)
#define cQuFnTyrInfo_Error          ( (uint8) 0x60)
#define cQuFnTyrInfo_Interference   ( (uint8) 0xE0)
#define cQuFnTyrInfo_LearningPhase  ( (uint8) 0xE8)
#define cQuFnTyrInfo_Active         ( (uint8) 0xA0)
#define cQuFnTyrInfo_Fallback       ( (uint8) 0xB0)
#define cQuFnTyrInfo_Active_Reset   ( (uint8) 0xA8)
#define cQuFnTyrInfo_Fallback_Reset ( (uint8) 0xB8)
#define cQuTpl_Init                 ( (uint8) 0x80)
#define cQuTpl_BreakTyrePosBase     ( (uint8) 0x20)
#define cQuTpl_BreakTyrePosMaskFr   ( (uint8) 0x21)
#define cQuTpl_BreakTyrePosMaskFl   ( (uint8) 0x22)
#define cQuTpl_BreakTyrePosMaskRr   ( (uint8) 0x24)
#define cQuTpl_BreakTyrePosMaskRl   ( (uint8) 0x28)
#define cQuTpl_BreakTyreNoPos       ( (uint8) 0x30)
#define cQuTpl_Diffusion            ( (uint8) 0x31)
#define cQuTpl_Active               ( (uint8) 0xA0)
#define cQuTfai_Init                ( (uint8) 0x80)
#define cQuTfai_FlatTyreFr          ( (uint8) 0x21)
#define cQuTfai_FlatTyreFl          ( (uint8) 0x22)
#define cQuTfai_FlatTyreRr          ( (uint8) 0x24)
#define cQuTfai_FlatTyreRl          ( (uint8) 0x28)
#define cQuTfai_Active              ( (uint8) 0xA0)
#define cCoolTyreMonInit            ( (uint8) 0x00)
#define cCoolTyreMonRunning         ( (uint8) 0x01)
#define cCoolTyreMonWaiting         ( (uint8) 0x02)
#define cCoolTyreMonFinish          ( (uint8) 0x03)
#define cCoolTyreMonDriving         ( (uint8) 0x7f)
#define cCoolTyreMonDeactivated     ( (uint8) 0xff)
#define cCoolingIntervalInitVal     ( (uint16) 0xffffu)
#define cCoolingIntervalResetVal    ( (uint16) 0x7fffu)
#define cCoolingIntervalTicksVal    ( (uint16)    600)

typedef struct{
  uint8  ucAvlPTyre_warm;
  sint8  scAvlTTyre_warm;
  uint8  ucAvlPTyre_kalt;
  sint8  scAvlTTyre_kalt;
  uint8  ucAvlPTyre_t;
  sint8  scAvlTTyre_t;
  uint8  ucTarPTyre_warm;
  uint8  ucTarPTyre_kalt;
  sint8  scTarTTyre_kalt;
  uint8  ucTarPTyre_t;
}tCoolTyreMonDataDeclCD;

#ifdef _EcuVirtual
#else
static PhySensorTyrePresType ucAvlPTyreFlh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreFrh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreRlh = cInvalidREpressure;
static PhySensorTyrePresType ucAvlPTyreRrh = cInvalidREpressure;
static sint8 scAvlTTyreFlh = cInvalidREtemperature;
static sint8 scAvlTTyreFrh = cInvalidREtemperature;
static sint8 scAvlTTyreRlh = cInvalidREtemperature;
static sint8 scAvlTTyreRrh = cInvalidREtemperature;
static PhySensorTyrePresType ucTarPTyreFlh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreFrh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreRlh = cInvalidREpressure;
static PhySensorTyrePresType ucTarPTyreRrh = cInvalidREpressure;
static uint8 ucQuFnTyrInfo;
static uint8 ucQuTpl;
static uint8 ucQuTfai;
static uint8 ucDispConfTime = FALSE;
static uint8 ucStChangeTime = FALSE;
static boolean bSuppressDisplayOfPTValuesITY(Rte_Instance self);
static uint16  ushGetConvertedPressureValueITY( uint16 ushPressureValue, tPressureUnitType eTo, boolean bRoundMode);
static uint16  ushGetConvertedTemperatureValueITY( sint16 sshTemperatureValue, tTemperatureUnitType eFrom, tTemperatureUnitType eTo);
static void SetQuFnTyrInfoITY(Rte_Instance self);
static void SetQuTplITY(void);
static void SetQuTfaiITY(Rte_Instance self);
static void GetPinitTinitITY( uint16* pushPfl, uint16* pushPfr, uint16* pushPrl, uint16* pushPrr);
static void CorrectFilteredTaITY(Rte_Instance self);
static uint8 ucCoolingTyreMonitoringITY(Rte_Instance self, uint16* pushElapsedCoolingTime);
static void InitAvlPTyreCoolingDownDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucState);
static void InitTarPTyreCoolingDownDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucState);
static void SetAvlPTyreCoolingDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState);
static void SetTarPTyreCoolingDataITY(Rte_Instance self, uint8 ucHistSlot, uint8 ucActionState);
static void CalcCoolingDownDataITY( uint16 ushElapsedCoolingTime);
#endif

#ifdef __cplusplus
}
#endif

#endif
