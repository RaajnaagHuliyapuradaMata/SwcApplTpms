

#ifndef HUF_RTE_HEADER_
#define HUF_RTE_HEADER_

#include "SwcApplTpms_Rte_Type.hpp"

#define STATIC   static

# ifndef Off
#  define Off (0U)
# endif

# ifndef ON
#  define ON (1U)
# endif

#define RET_OK     0x00u
#define RET_ERROR  0x01u

#define HUF_SWC_BASE_TIME_MS          200U
#define HUF_SWC_TIME_1_SEC_DIVIDER    (1000U/HUF_SWC_BASE_TIME_MS)

#define SENSOR_AUFLOESUNG_25MBAR

#define UI_MUL_OFFSET               ((uint16) 1024)
#define UC_KALIB_BEZUGSTEMP_CELSIUS ((uint8 )  20)
#define UI_KELVIN_OFFSET            ((uint16) 273)
#define UI_KALIB_BEZUGS_TEMP_KELVIN ((uint16)(UI_KELVIN_OFFSET+UC_KALIB_BEZUGSTEMP_CELSIUS))
#define UI_UMGEBUNGSDRUCK_MBAR      ((uint16) 950)
#define UC_UMGEBUNGSDRUCK_KPA       ((uint8 )(UI_UMGEBUNGSDRUCK_MBAR/(uint8)10))

#ifdef SENSOR_AUFLOESUNG_25MBAR
#define SENSOR_RESOLUTION_MBAR    25
#elif(defined SENSOR_AUFLOESUNG_54MBAR)
#define SENSOR_RESOLUTION_MBAR    55
#else
#error Unbekannte Sensoraufloesung!
#endif

#define UI_P_SENSOR_RESOLUTION_PAS  ((uint16)SENSOR_RESOLUTION_MBAR * (uint8)100)
#define UC_P_UMGEBUNGSDRUCK_BIN     ((uint8)(((uint32)UI_UMGEBUNGSDRUCK_MBAR * (uint8)100)/UI_P_SENSOR_RESOLUTION_PAS))

#define INVALID_WS_ID         ((uint32)(0xFFFFFFFFU))
#define UNKNOWN_WS_ID         ((uint32)(0xFFFFFFFF)U)
#define INVALID_WS_P          ((uint8)0xFFU)
#define INVALID_WS_T          ((uint8)0xFFU)
#define INVALID_VEH_IGN       ((uint8)0xFFU)
#define UNKNOWN_RAD_POSITION  ((uint8)0xFFU)
#define UNKNOWN_WS_PRESSURE   ((uint8)0xFFU)
#define UNKNOWN_RE_LIFETIME   ((uint8)0xFFU)
#define UNKNOWN_TIRE_STATE    ((uint8)0x00U)
#define UNKNOWN_RE_SPIN       ((uint8)0x03U)

#define ACHSE1_LI           0x17U
#define ACHSE1_RI           0x19U
#define ACHSE2_LI           0x27U
#define ACHSE2_RI           0x29U

#define UC_SIGNAL_NOT_AVAILABLE (uint8 )0xFFU
#define UC_SIGNAL_ERROR         (uint8 )0xFEU
#define UI_SIGNAL_NOT_AVAILABLE (uint16)0xFFFFU
#define UI_SIGNAL_ERROR         (uint16)0xFFFEU

#define CU16_NVM_ALL_CATEG_CONSISTENT       (uint16)(((uint16)1<<NVM_MAX_CATEGORYS)-1)

struct struct_BCM_Version
{
   uint8 ucaBCM_Version[5];
  uint8 ucaBCM_Date[12];
};

extern const struct struct_Version     g_sHufVersion;
extern const struct struct_BCM_Version g_sBCMVersion;

extern tsEnv_Data g_sEnv_Data;

extern void    Init_Huf_Common(void);
extern void    Huf_SWC_Basic_Timer(void);
extern uint8   GetNextWheelIndex(uint8 *ucpWheelIndex);
extern uint8   GetSystem_Data_MalfunctionBulb(void);
extern uint16  GetBaseLevel(void);
extern void    EvBCMFaultStatusChanged(boolean bBCMFault);
extern boolean GetSystem_DefectECUState(void);
extern void    GetSystem_TpmsStatus(uint8* pucStatus);

#ifdef WIN32
extern uint32  GetSystem_TimeMs(void);
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern void    PUTbWUDefectDI(boolean bWUDefect);
extern void    PUTbWUFailedDI(boolean bWUFailed);
extern void    INCREMENT(uint8 *ucValue, uint8 ucThreshold);
extern void    DECREMENT(uint8 *ucValue, uint8 ucThreshold);
extern uint8   GetSystem_Data_TpmsIndication(void);
extern boolean GetSystem_Data_PacardValuesValid(void);
extern uint8   GetSystem_Data_Reserved01(void);
extern uint8   GetSystem_Data_Reserved02(void);
extern sint8   Calc_Real_AK_Temperature(uint8 ucAk_TempInfo);
extern void    SetEventEvDiagEvalOS(void);
#endif //BUILD_WITH_UNUSED_FUNCTION

extern void    Init_OSEK(void);
extern void    SwcIf_OSEK_MainTask(uint8 ucSystemSeconds);
extern void    SetEventEvExceedVThresOS(void);
extern void    SetEventEvUnderrunVThresOS(void);
extern void    SetRelAlarmAlActivateWUFDOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlProceedWUFDOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlDeactivateWUFDOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlEOLRoutineTimerOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlMinuteCntOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlZOTimeOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlIDOMOS(uint16 ushTime, uint16 ushPeriod);
extern void    SetRelAlarmAlMissedRXCntOS( uint16 ushTime, uint16 ushPeriod );
extern void    CancelAlarmAlActivateWUFDOS(void);
extern void    CancelAlarmAlDeactivateWUFDOS(void);
extern void    CancelAlarmAlProceedWUFDOS(void);
extern void    CancelAlarmAlEOLRoutineTimerOS(void);
extern void    CancelAlarmAlMinuteCntOS(void);
extern void    CancelAlarmAlZOTimeOS(void);
extern void    CancelAlarmAlIDOMOS(void);
extern void    CancelAlarmAlMissedRxCntOS(void);
extern boolean GetAlarmAlZOTimeOS(uint16 *pushAlarmTicks);
extern boolean GetAlarmAlIDOMOS(uint16 *pushAlarmTicks);
extern boolean GetAlarmAlMinuteCntOS(uint16 *pushAlarmTicks);

extern void    Breakpoint(void);
extern void    Nop(void);

extern void    ReadReDataFromRingBuffer_iBTCM(const tsWS_RxDataIn* spRxDataIn);

#endif

