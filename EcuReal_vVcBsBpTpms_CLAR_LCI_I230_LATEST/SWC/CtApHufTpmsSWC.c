/******************************************************************************/
/* File   : CtApHufTpmsSWC.c                                                  */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Rte_CtApHufTpmsSWC.h"

#if defined( TESSY) || defined( QAC_MISRA_CHECK)
#undef WIN32
#else
#ifdef WIN32
    #include <stdio.h>
    #include <string.h>
#endif
#endif

#include "Rte_Type.h"
#include "DataManagerX.h"
#include "walloc_managerX.h"
#include "crc16X.h"
#include "WuMonitoringX.h"
#include "NwMonitoringX.h"
#include "SecondaryDtcX.h"
#include "StatusbarX.h"
#include "WarningLampX.h"
#include "InfoTyreX.h"
#include "CD_Decoder_X.h"
#include "erfs_X.h"
#include "RID_X.h"
#include "state_fzzX.h"
#include "state_bzX.h"
#include "state_zkX.h"
#include "StatusRdcLesenX.h"
#include "StatusRdcMessdatenblockX.h"
#include "SteuernDigitalRdcX.h"
#include "SteuernRadelektronikVorgebenX.h"
#include "HS_InaktivereignisX.h"
#include "HS_KalibrierereignisX.h"
#include "HS_WarnereignisX.h"
#include "RdcErfsEcoServicesX.h"
#include "RdcTsaServicesX.h"
#include "RdcAnlernenLokalisierungLesenX.h"
#include "StatusRdcDeveloperDataLesenX.h"
#include "SteuernRdcDeveloperConfigX.h"
#include "StatusReLesenDruckcodierungX.h"
#include "StatusRdcExtParkSupervisionLesenX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeDiagBlockX.h"
#include "EeErfsBlockX.h"
#include "EeErfsTsaBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeErfsEcoBlockX.h"
#include "EeZomBlockX.h"
#include "EeRidQrBlockX.h"
#include "EeGlobalFunctionsX.h"
#include "BandmodeX.h"
#include "CodingDataX.h"
#include "DebugMsgX.h"
#include "FBD_ManagerX.h"
#include "TAmbFiltX.h"
#include "BreakTireX.h"
#include "CcmX.h"
#include "SeasRcpAdjX.h"
#include "SpeedCcmX.h"

#ifdef _EcuVirtual
#include "EcuVirtual_stdio.h"
#else
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cRDCI_VERSION                                          ((uint16) 0x0213)
#define cDEM_STATUS_DTC_IS_ACTIVE       (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT)
#define cDEM_STATUS_SET_WARNING_LAMP (cDEM_STATUS_DTC_IS_ACTIVE | DEM_UDS_STATUS_WIR)
#define cFbdSwitchCodeId1                                                      0
#define cFbdSwitchCodeId2                                                      2
#define cFbdSwitchCodeId3                                                      3
#define cFbdSwitchCodeId4                                                      4
#define cFbdSwitchCodeParkMon                                                 10
#define cFbdMonitorOn                                                       0x01
#define cFbdMonitorOff                                                      0x00
#define cFbdDataRequest                                                     0x01
#define cFbdNoDataRequest                                                   0x00
#define cNoIdFiltering                                                      0x00
#define cFbdMonId1Active                                                    0x01
#define cFbdMonId2Active                                                    0x02
#define cFbdMonId3Active                                                    0x04
#define cFbdMonId4Active                                                    0x08
#define cUpdateNoRe                                                         0x00
#define cUpdateRe0                                                          0x01
#define cUpdateRe01                                                         0x02
#define cUpdateRe012                                                        0x03
#define cUpdateRe0123                                                       0x04
#define c1secTaskTimeslot_5                                      ((uint16)    5)
#define c1secTaskTimeslot_6                                      ((uint16)    6)
#define c1secTaskTimeslot_7                                      ((uint16)    7)
#define c1secTaskTimeslot_8                                      ((uint16)    8)
#define c1secTaskTimeslot_9                                      ((uint16)    9)
#define c1secTaskTimeslot_15                                     ((uint16)   15)
#define c1secTaskTimeslot_16                                     ((uint16)   16)
#define c1secTaskTimeslot_17                                     ((uint16)   17)
#define c1secTaskTimeslot_18                                     ((uint16)   18)
#define c1secTaskTimeslot_19                                     ((uint16)   19)
#define c1secTaskTimeslot_25                                     ((uint16)   25)
#define c1secTaskTimeslot_26                                     ((uint16)   26)
#define c1secTaskTimeslot_27                                     ((uint16)   27)
#define c1secTaskTimeslot_28                                     ((uint16)   28)
#define c1secTaskTimeslot_29                                     ((uint16)   29)
#define c100msecTaskTimeslot_0                                   ((uint16)    0)
#define c100msecTaskTimeslot_1                                   ((uint16)    1)
#define c100msecTaskTimeslot_2                                   ((uint16)    2)
#define c100msecTaskTimeslot_3                                   ((uint16)    3)
#define c100msecTaskTimeslot_4                                   ((uint16)    4)
#define c100msecTaskTimeslot_5                                   ((uint16)    5)
#define c100msecTaskTimeslot_6                                   ((uint16)    6)
#define c100msecTaskTimeslot_7                                   ((uint16)    7)
#define c100msecTaskTimeslot_8                                   ((uint16)    8)
#define c100msecTaskTimeslot_9                                   ((uint16)    9)
#define c5secTaskTimeslot_35                                     ((uint16)   35)
#define c5secTaskTimeslot_36                                     ((uint16)   36)
#define c5secTaskTimeslot_37                                     ((uint16)   37)
#define c5secTaskTimeslot_38                                     ((uint16)   38)
#define c5secTaskTimeslot_39                                     ((uint16)   39)
#define c2minTaskTimeslot_2000                                   ((uint16) 2000)
#define c2minTaskTimeslot_2100                                   ((uint16) 2100)
#define c2minTaskTimeslot_2200                                   ((uint16) 2200)
#define c2minTaskTimeslot_2300                                   ((uint16) 2300)
#define c2minTaskTimeslot_2400                                   ((uint16) 2400)
#define cWUM_DTC                                                 ((uint8)     1)
#define cNW_DTC                                                  ((uint8)     2)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static volatile uint8                                               ucNvmIsInitializedSWC = cNvmInitialized;
static          ImpTypeVal_C_Funktion_ReifenPannenerkennung_aktiv_e ucReifenPannenerkennung_aktiv           = (uint8)DISABLE;
static          boolean                                             bInitIsDone                             = FALSE;
static          uint8                                               aucNvmSaveAttempts[cAttemptCounterSize] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static          uint8                                               ucDataIndex                             = 0xFF;
static          boolean                                             bReducedTyreListActive                  = FALSE;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void  InitSWC                          (Rte_Instance);
static uint8 ucGetTelegramTypeSWC             (const ImpTypeRecCddRdcData*);
static uint8 ucRdcChecksumSWC                 (const ImpTypeRecCddRdcData*, uint8);
static void  CyclicDemServicesSWC             (Rte_Instance, uint16);
static void  CheckFunktionszustandDTC         (Rte_Instance, uint32, const uint8);
static void  SetSeasonTyreData                (Rte_Instance);
static void  SetAxleTyreData                  (Rte_Instance);
static void  SendTyreListElement              (Rte_Instance, Rdci_RQ_OL_TPCT_Type *);
static void  CompCurTyrSelWithTyreListEntries (Rte_Instance, uint8);
static uint8 GetReducedTyreList               (Rte_Instance self);
static void  SaveNvmCommonBlockOnEventSWC     (Rte_Instance);
static void  SaveNvmDiagBlock1OnEventSWC      (Rte_Instance);
static void  SaveNvmDiagBlock2OnEventSWC      (Rte_Instance);
static void  SaveNvmErfsBlockOnEventSWC       (Rte_Instance);
static void  SaveNvmErfsTsaBlockOnEventSWC    (Rte_Instance);
static void  SaveNvmRidQrBlock1OnEventSWC     (Rte_Instance);
static void  SaveNvmRidQrBlock2OnEventSWC     (Rte_Instance);
static void  SaveNvmZoHistoryBlockOnEventSWC  (Rte_Instance);
static void  SaveNvmWarnstatusBlockOnEventSWC (Rte_Instance);
static void  SendDebugMessageSWC              (Rte_Instance);
static void  UpdateFbd4ControlDataSWC         (Rte_Instance, uint8, uint8);
static void  UpdateFbd4ParkingMonitorSWC      (Rte_Instance, uint8, uint8);
static void  ReadAbsAndRdcDataFromRteSWC      (Rte_Instance self);
static void  ProcessTelegramWaitingQueueSWC   (Rte_Instance self);
static void  TwoMinutesTaskSWC                (Rte_Instance self);
static void  FiveSecondsTaskSWC               (Rte_Instance self);
static void  OneSecondTaskSWC                 (Rte_Instance self);
static void  HundredMillisecondsTaskSWC       (Rte_Instance self);
static void  TwentyMillisecondsTaskSWC        (Rte_Instance self, uint8 swcRunTime);
static void  TenMillisecondsTaskSWC           (Rte_Instance self, Rdci_RQ_OL_TPCT_Type* opRequestTyreList);
static void  VklFklHandlingSWC                (Rte_Instance self);
static void  UpdateFbd4IdsSWC                 (Rte_Instance self);
static uint8 CalcRuntimeSWC                   (Rte_Instance self, uint32 swcRunTime1);
static void  InitCOD                          (Rte_Instance);
static uint8 InitTyreList                     (Rte_Instance);
static uint8 InitTyreListCyclically           (Rte_Instance);
static void  DegradeToOtherTyre               (Rte_Instance self);
static void  SendTPMSInternalLastValuesSWC    (Rte_Instance self);
static void  SendTPMSCalibrationDataSWC       (Rte_Instance self);
static void  SendTPMSErfsActualTireDataSWC    (Rte_Instance self);
static void  SendTPMSTireMileageDataSWC       (Rte_Instance self);
static void  SendTPMSQrCodeDataSWC            (Rte_Instance self);

void ReInitRdciSWC              (void);
void GetNvmWriteAttemptCounters (uint8* pChar);

#define CTAPHUFTPMSSWC_START_SEC_CODE
#include "CtApHufTpmsSWC_MemMap.h"
FUNC(void, CtApHufTpmsSWC_CODE) RCyclicRDCiTask(Rte_Instance self){
   static StbMB_SystemTimeType              systemTime              = {0xffffffffu, 0xffffu, 0xffffffffu, 0xffffffffu };
   static Rdci_T_SEC_COU_REL_Type           relTime                 = 0xffffffffu;
   static Rdci_GNSSPositionAltitude_Type    GNSSPositionAltitude    = {Rte_InitValue_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude    };
   static Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters = {Rte_InitValue_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters };
   static Rdci_V_VEH_Type                   speedData               = {0};
   static Rdci_WMOM_DRV_4_Type              directionData           = {0};
   static Rdci_CON_VEH_Type                 conditionVehicle        = {0};
   static Rdci_UHRZEIT_DATUM_Type           timeDate                = {0};
   static Rdci_MILE_KM_Type                 MileKm                  = {0};
   static StbMB_SystemTimeType              sysTime                 = {0};
   static Rdci_UN_AIP_Type                  unitAipData             = 0;
   static Rdci_UN_TEMP_Type                 unitTempData            = 0;
   static Rdci_UN_MILE_Type                 unitMileData            = 0;
   static Rdci_TEMP_EX_Type                 temperatureData         = 0;
   static uint8                             ucIdrMessageTimer       = 0;
   static Rdci_OP_IDR_SLCTN_Type            opIdrSelection;
   static Rdci_ST_IDR_MSGC_Type             stIdrMsg;
   static Rdci_OP_SLCTN_TYR_AVLB_Type       opSelectedTyrePointer;
   static Rdci_OP_TAR_P_LOCO_TPCT_Type      opSelectLoadCon;
   static Rdci_OP_TPCT_Type                 opSettingConfirmation;
   static Rdci_OP_TYR_SEA_TPCT_Type         opSelectSeason;
   static Rdci_RQ_OL_TPCT_Type              opRequestTyreList;
   static Rdci_AIP_ENG_DRV_Type             atmPressure;
   static Rdci_ST_ILK_ERRM_FZM_Type         ucFzzstd;
   static ImpTypeValFrBusState              ucFlexrayBusState;
   static uint32                            swcRunTime1;
   static uint8                             swcRunTime;
          uint8                             ucPWFStateTransition = ePWFInvalid;
          uint8                             ucTemp;

#if(IGNORE_CODING_SWITCH == 1)
   ucReifenPannenerkennung_aktiv = (uint8)AKTIV_RDC;
#else
   ucReifenPannenerkennung_aktiv = (self)->RpCalPrmRDCi.Prm_C_Funktion_ReifenPannenerkennung_aktiv_e();
#endif

   if((uint8)AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      (void) Rte_Call_StbMB_AbsoluteTimeBaseValue_GetAbsoluteTime(self, &sysTime);
      swcRunTime1 = sysTime.ticks;
      if(cNvmInitialized != ucNvmIsInitializedSWC){
         PUTucCommonBlockInitializeEE(     self, 0);
         PUTucErfsInitializerEE(           self, 0);
         PUTucDiagBlock1InitializeEE(      self, 0);
         PUTucDiagBlock2InitializeEE(      self, 0);
         PUTucWarnStatusBlockInitializeEE( self, 0);
         PUTucZomBlock1InitializeEE(       self, 0);
         PUTucZomBlock2InitializeEE(       self, 0);
         bInitIsDone           = FALSE;
         ucNvmIsInitializedSWC = cNvmInitialized;
      }
      if(FALSE == bInitIsDone){
         InitSWC(self);
      }
      (void)InitTyreListCyclically(self);
      if(TRUE == Rte_IsUpdated_RpFrPdu_V_VEH_V_VEH(self)){
         (void) Rte_Read_RpFrPdu_V_VEH_V_VEH(self, &speedData);
         if(CheckV_VEH_MsgNWM(self, speedData) != cNoError){
            speedData.V_VEH_COG = 0;
         }
         SetVehicleSpeedWAM(self, speedData);
      }
      else{
         if(TRUE == bGetNetworkErrorNWM(cNetwork_V_VEH_MsgMissing)){
            speedData.V_VEH_COG = 0;
            SetVehicleSpeedWAM(self, speedData);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_WMOM_DRV_4_WMOM_DRV_4(self)){
         (void)Rte_Read_RpFrPdu_WMOM_DRV_4_WMOM_DRV_4(self, &directionData);
         if(cNoError == CheckWMOM_DRV_4_MsgNWM(self, directionData)){
            SetGearWAM(directionData);
         }
      }

      if(TRUE == Rte_IsUpdated_RpFrPdu_A_TEMP_TEMP_EX(self)){
         (void)Rte_Read_RpFrPdu_A_TEMP_TEMP_EX(self, &temperatureData);
         if(cNoError == CheckA_TEMP_MsgNWM(self, temperatureData)){
            SetExternalTemperatureDM(self, temperatureData);
         }
      }
      ucTemp = 0;
      if(TRUE == Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_AIP(  self)){ucTemp++;}
      if(TRUE == Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_TEMP(self)){ucTemp++;}
      if(ucTemp > 0){
         (void)Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_AIP(  self, &unitAipData);
         (void)Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_TEMP(self, &unitTempData);
         if(cNoError == CheckEINHEITEN_BN2020_MsgNWM(self, unitAipData, unitTempData)){
            SetUnitAipDM(  self, unitAipData);
            SetUnitTempDM(self, unitTempData);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_EINHEITEN_BN2020_UN_MILE(self)){
         (void)Rte_Read_RpFrPdu_EINHEITEN_BN2020_UN_MILE(self, &unitMileData);
         SetUnitMileDM(self, unitMileData);
      }
      if(TRUE == bGetCRdciErfsEnableCD()){
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_IDR_SLCTN(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_IDR_SLCTN(self, &opIdrSelection);
            if(OP_IDR_SLCTN_Automatische_Auswahl == opIdrSelection){
               SetStatusManSelectionDM(ST_MAN_SLCTN_Automatische_Reifenauswahl);
            }
            else{
               if(OP_IDR_SLCTN_Manuelle_Auswahl == opIdrSelection){
                  SetStatusManSelectionDM(ST_MAN_SLCTN_Manuelle_Reifenauswahl);
               }
            }
         }
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_ST_IDR_MSGC(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_ST_IDR_MSGC(self, &stIdrMsg);
            if(IDR_MSGC_MZ_Inaktiv == stIdrMsg){
               if(OP_IDR_MSGC_MZ_Aktivieren == GetIDRMessageCenterDM()){
                  SetIDRMessageCenterDM(OP_IDR_MSGC_MZ_Deaktivieren);
                  ucIdrMessageTimer = 20;
               }
            }
         }
         else{
            if(ucIdrMessageTimer > 0){
               if(1 == ucIdrMessageTimer){
                  SetIDRMessageCenterDM(OP_IDR_MSGC_Keine_Aktion);
                  PUTIdrMessageEE(self, OP_IDR_MSGC_Keine_Aktion);
               }
               ucIdrMessageTimer--;
            }
         }
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_SLCTN_TYR_AVLB(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_SLCTN_TYR_AVLB(self, &opSelectedTyrePointer);
            SetSelectedTyreIndexDM(opSelectedTyrePointer);
            if(opSelectedTyrePointer < OP_SLCTN_TYR_AVLB_SignalUngueltig){
               if(OP_SLCTN_TYR_AVLB_Funktionsschnittstelle_ist_nicht_verfuegbar != opSelectedTyrePointer){
                  if(OP_TYR_SEA_TPCT_Winterreifen == GetSeasonDM()){
                     SetWinterTyreIndexDM(GetSelectedTyreIndexDM());
                  }
                  else{
                     if(OP_TYR_SEA_TPCT_Sommerreifen == GetSeasonDM()){
                        SetSummerTyreIndexDM(GetSelectedTyreIndexDM());
                     }
                  }
               }
               else{
                  DegradeToOtherTyre(self);
                  ResetCurrentTyreSelectionDM(self);
                  PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_RDC_degradiert_Funktion_niLJ29OU, StatusWheelTypeChangePosition_Position_Unbekannt);
               }
            }
         }
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TAR_P_LOCO_TPCT(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TAR_P_LOCO_TPCT(self, &opSelectLoadCon);
            SetLoadStateDM(opSelectLoadCon);
         }
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TYR_SEA_TPCT(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TYR_SEA_TPCT(self, &opSelectSeason);
            SetSeasonDM(opSelectSeason);
            if(opSelectSeason < OP_TYR_SEA_TPCT_KeineAenderung){
               if(OP_TYR_SEA_TPCT_Winterreifen == GetSeasonDM()){
                  SetSelectedTyreIndexDM(GetWinterTyreIndexDM());
               }
               else{
                  if(OP_TYR_SEA_TPCT_Sommerreifen == GetSeasonDM()){
                     SetSelectedTyreIndexDM(GetSummerTyreIndexDM());
                  }
               }
            }
         }
         if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_RQ_OL_TPCT(self)){
            (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_RQ_OL_TPCT(self, &opRequestTyreList);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TPCT(self)){
         (void)Rte_Read_RpFrPdu_BEDIENUNG_FAHRWERK_OP_TPCT(self, &opSettingConfirmation);
         if(OP_TPCT_RDCSlashRPASetzen == opSettingConfirmation){
            if(OP_IDR_SLCTN_Manuelle_Auswahl == GetStatusManSelectionDM()){
               if(OP_TYR_SEA_TPCT_Winterreifen == GetSeasonDM()){
                  SetSelectedTyreIndexDM(GetWinterTyreIndexDM());
               }
               else{
                  if(OP_TYR_SEA_TPCT_Sommerreifen == GetSeasonDM()){
                     SetSelectedTyreIndexDM(GetSummerTyreIndexDM());
                  }
               }
            }
            if(TRUE == CheckPrepareTyreSelectionDM(self,  GetLoadStateDM(), GetSelectedTyreIndexDM(), GetSeasonDM(), GetStatusManSelectionDM())){
               SaveCurrentTyreSelectionDM(self);
               if(OP_IDR_SLCTN_Manuelle_Auswahl == GetStatusManSelectionDM()){
                  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self, TRUE);
                  StartDisplayConfTimeoutITY(ucGetCRdciDispConfTimeoutCD());
               }
               else{
                  SetCalibrationRootCauseDS(self, cCalRidStatusbar);
               }
            }
            else{
               ResetCurrentTyreSelectionDM(self);
            }
         }
         else{
            if(OP_TPCT_RDCEinstellungenAbgebrochen == opSettingConfirmation){
               ResetCurrentTyreSelectionDM(self);
            }
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_RELATIVZEIT_T_SEC_COU_REL(self)){
         (void) Rte_Read_RpFrPdu_RELATIVZEIT_T_SEC_COU_REL(self, &relTime);
         (void) CheckBN2020_RELATIVZEIT_MsgNWM(self, relTime);
         systemTime.systemTicks = relTime;
         SetStopTimeDM(self, systemTime);
      }
      SetSysTimeDM(systemTime.systemTicks);
      if(TRUE == Rte_IsUpdated_RpFrPdu_DT_PT_1_AIP_ENG_DRV(self)){
         (void) Rte_Read_RpFrPdu_DT_PT_1_AIP_ENG_DRV(self, &atmPressure);
         if(cNoError == CheckDT_PT_1_MsgNWM(self, atmPressure)){SetExternalPressureDM(self, atmPressure, (uint8) cNoError);}
         else                                                  {SetExternalPressureDM(self, atmPressure, (uint8) cSignalError);}
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude(self)){
         (void)Rte_Read_RpFrPdu_NMEARawData2Part2_GNSSPositionAltitude(self, &GNSSPositionAltitude);
         if(cNoError == CheckNMEARawData2Part2_MsgNWM(self, GNSSPositionAltitude)){SetGNSSPositionAltitudeDM(self, GNSSPositionAltitude, (uint8) cNoError);}
         else                                                                     {SetGNSSPositionAltitudeDM(self, GNSSPositionAltitude, (uint8) cSignalError);}
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters(self)){
         (void)Rte_Read_RpFrPdu_NMEARawData2Part3_GNSSErrorAltitudeMeters(self, &GNSSErrorAltitudeMeters);
         if(cNoError == CheckNMEARawData2Part3_MsgNWM(self, GNSSErrorAltitudeMeters)){SetGNSSErrorAltitudeMetersDM(self, GNSSErrorAltitudeMeters, cNoError);}
         else                                                                        {SetGNSSErrorAltitudeMetersDM(self, GNSSErrorAltitudeMeters, (uint8) cSignalError);}
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_UHRZEIT_DATUM_UHRZEIT_DATUM(self)){
         (void)Rte_Read_RpFrPdu_UHRZEIT_DATUM_UHRZEIT_DATUM(self, &timeDate);
         if(cNoError == CheckUHRZEIT_DATUM_MsgNWM(self, timeDate)){
            SetTimeDateDM(self, timeDate);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_KILOMETERSTAND_MILE_KM(self)){
         (void)Rte_Read_RpFrPdu_KILOMETERSTAND_MILE_KM(self, &MileKm);
         if(cNoError == CheckKILOMETERSTAND_MsgNWM(self, MileKm)){
            SetMileageDM(self, MileKm);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_CON_VEH_CON_VEH(self)){
         (void)Rte_Read_RpFrPdu_CON_VEH_CON_VEH(self, &conditionVehicle);
         if(cNoError == CheckCON_VEH_MsgNWM(self, conditionVehicle)){
            ucPWFStateTransition = SetParkenWohnenFahrenDM(conditionVehicle);
            switch(ucPWFStateTransition){
               case (uint8) eParkenStandfunktion:
                  timeDate = GETtTimeDateEE(self);
                  PUTtExtParkSupWakeupTimeDateEE(self, timeDate);
                  UpdateFbd4ControlDataSWC(self, cNoIdFiltering, cUpdateNoRe);
                  UpdateFbd4ParkingMonitorSWC(self, cFbdMonitorOff, cFbdNoDataRequest);
                  if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
                     PmStartDataAllocTimerFBD();
                  }
                  break;

               case (uint8) eParkenWohnen:
                  InitStatusReLesenDruckcodierungDS();
                  PwfChangeParken2WohnenBT();
                  if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
                     PmStartDataAllocTimerFBD();
                  }
                  break;

               case (uint8) eWohnenFahren:
                  InitStatusReLesenDruckcodierungDS();
                  (void)ucWarnManagerWN(self, ucFilterActivationc, (uint8*) NULL_PTR);
                  if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
                     PmStartDataAllocTimerFBD();
                  }
                  if(
                        (TRUE == bGetNetworkErrorNWM(cNetwork_RELATIVZEIT_MsgMissing))
                     && (
                              (TRUE == bGetBitBetriebszustandBZ(cZO_FINISH))
                           || (TRUE == bGetBitBetriebszustandBZ(cZO_TIMEOUT))
                        )
                  ){
                     SetBitFahrzeugzustandFZZ(cLONG_PARK);
                     InitRDCiFunctionsPartTwoDM(self);
                  }
                  break;

               case (uint8) eFahrenWohnen:
                  UpdateFbd4ParkingMonitorSWC(self, cFbdMonitorOn, cFbdNoDataRequest);
                  timeDate = GETtTimeDateEE(self);
                  PUTtExtParkSupSleepTimeDateEE(self, timeDate);
                  break;

               case (uint8) eWohnenParken:
                  StopCycleCCM();
                  UpdateFbd4ParkingMonitorSWC(self, cFbdMonitorOn, cFbdNoDataRequest);
                  PmStopDataAllocTimerFBD();
                  break;

               case (uint8)eStandFktParken:
                  StopCycleCCM();
                  UpdateFbd4ParkingMonitorSWC(self, cFbdMonitorOn, cFbdNoDataRequest);
                  PmStopDataAllocTimerFBD();
                  break;

               default:
                  break;
            }
         }
      }
      if(TRUE == bPwfIsFahrenFZZ()){
         SETBusStateFZZ(FR_STATE_ACTIVE);
      }
      else{
         if(E_OK == Rte_Read_RpRdci_FrBusState_FrBusState(self, &ucFlexrayBusState)){
            SETBusStateFZZ(ucFlexrayBusState);
         }
      }
      if(TRUE == Rte_IsUpdated_RpFrPdu_FZZSTD_ST_ILK_ERRM_FZM(self)){
         (void)Rte_Read_RpFrPdu_FZZSTD_ST_ILK_ERRM_FZM(self, &ucFzzstd);
         if(cNoError == CheckFZZSTD_MsgNWM(ucFzzstd)){
            SETFehlerspeicherSperreFZZ(ucFzzstd);
         }
         else{
            SETFehlerspeicherSperreFZZ(ST_ILK_ERRM_FZM_Fehlerspeicherfreigabe);
         }
      }
      ReadAbsAndRdcDataFromRteSWC(self);
      TwoMinutesTaskSWC(self);
      FiveSecondsTaskSWC(self);
      OneSecondTaskSWC(self);
      HundredMillisecondsTaskSWC(self);
      TenMillisecondsTaskSWC(self, &opRequestTyreList);
      IncreaseRCyclicCallCounter();
      swcRunTime = CalcRuntimeSWC(self, swcRunTime1);
      TwentyMillisecondsTaskSWC(self, swcRunTime);
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) RExitRDCiBye(Rte_Instance self){
#ifdef RTE_INIT_IMPLICIT_BUFFERS
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH             (self, Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH             (self, Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH             (self, Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH             (self, Rte_InitValue_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH       (self, Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH       (self, Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH       (self, Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH       (self, Rte_InitValue_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR          (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR          (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR     (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR   (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR    (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR         (self, Rte_InitValue_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2 (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1      (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1       (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1        (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2 (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2      (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2       (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2        (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2 (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3      (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3       (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3        (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2 (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4      (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4       (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4        (self, Rte_InitValue_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9       (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31      (self, Rte_InitValue_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR        (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR        (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR   (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR     (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR       (self, Rte_InitValue_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR         (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR     (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR       (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2 (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR         (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR   (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR         (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR         (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID        (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR         (self, Rte_InitValue_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_ACTVN_PM                         (self, Rte_InitValue_PpFrPdu_PM_ACTVN_PM);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_PM_ID2                           (self, Rte_InitValue_PpFrPdu_PM_PM_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_PM_RQ_PM_DT                         (self, Rte_InitValue_PpFrPdu_PM_RQ_PM_DT);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR   (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR     (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR               (self, Rte_InitValue_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_OP_IDR_MSGC                (self, Rte_InitValue_PpFrPdu_ST_TYR_2_OP_IDR_MSGC);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP           (self, Rte_InitValue_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN               (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB         (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR               (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB         (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT         (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT            (self, Rte_InitValue_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH             (self, Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH             (self, Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH             (self, Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH             (self, Rte_InitValue_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR   (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR     (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR);
   Rte_IWrite_RExitRDCiBye_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2       (self, Rte_InitValue_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2);
#endif
#ifdef _EcuVirtual
   UNUSED(self);
#else
#endif
}

FUNC(void, CtApHufTpmsSWC_CODE) RInitRDCiStartup(Rte_Instance self){
   InitSWC(self);
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
#ifdef _EcuVirtual
   UNUSED(self);
#else
#endif
   return RTE_E_OK;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_FunktionenReifendruckkontrolleReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
#ifdef _EcuVirtual
   UNUSED(self);
#else
#endif
   return RTE_E_OK;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal   = RTE_E_PiServiceDcmRdcAktuelleAussentemperatur_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
#ifdef _EcuVirtual
   UNUSED(self);
#else
#endif
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcAktuelleAussentemperaturReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcAktuelleAussentemperatur_E_NOT_OK;
   }
   else{
      *Data = (uint8) GETscTAmbValEE(self);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAussendruck_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcAussendruck_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
#ifdef _EcuVirtual
   UNUSED(self);
#else
#endif
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcAussendruck_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   uint16 ushPamb;
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcAussendruck_E_NOT_OK;
   }
   else{
      ushPamb = (uint16) GETucPAmbValEE(self) * 25;
      Data[0] = (uint8) ((uint16) (ushPamb >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPamb >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcInaktivStatus_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcInaktivStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcInaktivStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = 0xff;
      ucRetVal = RTE_E_PiServiceDcmRdcInaktivStatus_E_NOT_OK;
   }
   else{
      if(TRUE == bGetBitBetriebszustandBZ(cDTC_INACTIVE)){
         *Data = GetCurrentInactiveReasonDS();
      }
      else{
         *Data = TAB_RDC_INT_FEHLER_INVALID;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcKalibrierungStatus_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKalibrierungStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcKalibrierungStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = 0xff;
      ucRetVal = RTE_E_PiServiceDcmRdcKalibrierungStatus_E_NOT_OK;
   }
   else{
      if(TRUE == GETTyreSelectionBckgrdEE(self)){
         *Data = cCalRunning;
      }
      else{
         *Data = GetLatestCalibrationRootCauseDS(self);
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcKonfiguration_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcKonfiguration_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcKonfigurationReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = 0xff;
      ucRetVal = RTE_E_PiServiceDcmRdcKonfiguration_E_NOT_OK;
   }
   else{
           if(OP_SLCTN_TYR_AVLB_AndererReifen == GETSelectedTyreIndexEE(self))   {*Data = RDC_INT_KONFIG_RDC_RESET;}
      else if(FALSE                           == bGetCRdciRidEnableCD())         {*Data = RDC_INT_KONFIG_ERFS_WITHOUT_RID;}
      else{
              if(OP_IDR_SLCTN_Manuelle_Auswahl     == GETStManSelectionEE(self)) {*Data = RDC_INT_KONFIG_ERFS_WITH_RID_MAN_SEL;}
         else if(OP_IDR_SLCTN_Automatische_Auswahl == GETStManSelectionEE(self)) {*Data = RDC_INT_KONFIG_ERFS_WITH_RID_AUT_SEL;}
         else                                                                    {*Data = RDC_INT_KONFIG_INVALID;}
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcPosition_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcPosition_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcPosition_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcPositionReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   uint8 ucDtcNumber;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = 0xff;
      ucRetVal = RTE_E_PiServiceDcmRdcPosition_E_NOT_OK;
   }
   else{
     SecondaryDtcFiFoShiftSCD(&ucDtcNumber, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReferenzAussentemperatur_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReferenzAussentemperaturReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReferenzAussentemperatur_E_NOT_OK;
   }
   else{
      *Data = (uint8) GETscTAinitValEE(self);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckHl_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHl_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   uint8                 ucHistId;
   uint16                ushPress;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckHl_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosHL);
      if(ucHistId < cAnzRad){ucPress = ucGetRePressureRelDM(ucHistId);}
      else                  {ucPress = cInvalidREpressure;}

      if(cInvalidREpressure == ucPress){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckHr_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckHr_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   uint8 ucHistId;
   uint16 ushPress;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckHr_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosHR);
      if(ucHistId < cAnzRad){ucPress = ucGetRePressureRelDM(ucHistId);}
      else                  {ucPress = cInvalidREpressure;}

      if(cInvalidREpressure == ucPress){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckVl_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVl_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   uint8 ucHistId;
   uint16 ushPress;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckVl_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosVL);
      if(ucHistId < cAnzRad){ucPress = ucGetRePressureRelDM(ucHistId);}
      else                  {ucPress = cInvalidREpressure;}

      if(cInvalidREpressure == ucPress){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckVr_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifendruckVr_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   uint8 ucHistId;
   uint16 ushPress;

   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifendruckVr_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosVR);
      if(ucHistId < cAnzRad){ucPress = ucGetRePressureRelDM(ucHistId);}
      else                  {ucPress = cInvalidREpressure;}

      if(ucPress == cInvalidREpressure){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturHl_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHl_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturHlReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyreTempType scTemp;
   uint8                 ucHistId;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturHl_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosHL);
      if(ucHistId < cAnzRad){scTemp = scGetReTemperatureCentDM(ucHistId);}
      else                  {scTemp = cInvalidREtemperature;}

      *Data = (uint8) scTemp;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturHr_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturHr_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturHrReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   PhySensorTyreTempType scTemp;
   uint8 ucHistId;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturHr_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosHR);
      if(ucHistId < cAnzRad){scTemp = scGetReTemperatureCentDM(ucHistId);}
      else                  {scTemp = cInvalidREtemperature;}

      *Data = (uint8) scTemp;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturVl_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVl_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturVlReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyreTempType scTemp;
   uint8                 ucHistId;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturVl_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosVL);
      if(ucHistId < cAnzRad){scTemp = scGetReTemperatureCentDM(ucHistId);}
      else                  {scTemp = cInvalidREtemperature;}

      *Data = (uint8) scTemp;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturVr_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcReifentemperaturVr_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcReifentemperaturVrReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyreTempType scTemp;
   uint8                 ucHistId;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcReifentemperaturVr_E_NOT_OK;
   }
   else{
      ucHistId = ucGetColOfWP(cRadPosVR);
      if(ucHistId < cAnzRad){scTemp = scGetReTemperatureCentDM(ucHistId);}
      else                  {scTemp = cInvalidREtemperature;}

      *Data = (uint8) scTemp;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcSensorHersteller_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSensorHersteller_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcSensorHerstellerReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   uint8          i;
   uint8          ucValue;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = TAB_RDC_RE_HERSTELLER_INVALID;
      ucRetVal = RTE_E_PiServiceDcmRdcSensorHersteller_E_NOT_OK;
   }
   else{
      i = 0;
      while ((ucGetSuppIdOfColWAL(i) == TAB_RDC_RE_HERSTELLER_HUF) && (i < cMaxLR)){
         i++;
      }
      if(cMaxLR == i){ucValue = TAB_RDC_RE_HERSTELLER_HUF;}
      else           {ucValue = ucGetSuppIdOfColWAL(i);}

           if(FALSE == bGetBitBetriebszustandBZ(cZO_FINISH)      ){ucValue |= 0x10;}
      else if(TRUE  == bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG)){ucValue |= 0x10;}
      else{}

      *Data = ucValue;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcSolldruckHinten_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckHinten_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   PhySensorTyreTempType scTemp;
   uint16                ushPress;

   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcSolldruckHinten_E_NOT_OK;
   }
   else{
      (void)ucGetWpPTSollUSWIF(&ucPress, &scTemp, cRadPosHL);
      if(ucPress == cInvalidREpressure){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcSolldruckVorn_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcSolldruckVorn_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType        ucRetVal = RTE_E_OK;
   PhySensorTyrePresType ucPress;
   PhySensorTyreTempType scTemp;
   uint16                ushPress;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcSolldruckHinten_E_NOT_OK;
   }
   else{
      (void)ucGetWpPTSollUSWIF(&ucPress, &scTemp, cRadPosVL);
      if(ucPress == cInvalidREpressure){ushPress = (uint16) 0xffffu;}
      else                             {ushPress = (uint16) ucPress * 25;}

      Data[0] = (uint8) ((uint16) (ushPress >> 8) & 0x00ffu);
      Data[1] = (uint8) ((uint16) (ushPress >> 0) & 0x00ffu);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcStatus_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcStatus_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmDiagRdcStatus_ReadData(Rte_Instance self, P2VAR(ImpTypeValDcm_RdcStatusReadDataType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *Data = 0xff;
      ucRetVal = RTE_E_PiServiceDcmRdcStatus_E_NOT_OK;
   }
   else{
           if(TRUE == bGetBitBetriebszustandBZ(cZO_FINISH)){*Data = TAB_RDC_INTERNE_STATUS_SENSOREN_ANGELERNT_UND_LOKALISIERT;}
      else if(TRUE == bGetBitBetriebszustandBZ(cER_FINISH)){*Data = TAB_RDC_INTERNE_STATUS_SENSOREN_ANGELERNT;}
      else                                                 {*Data = TAB_RDC_INTERNE_STATUS_SENSOREN_NICHT_ANGELERNT_NICHT_LOKALISIERT;}

   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcAnlernenLokalisierungLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcAnlernenLokalisierungLesen_E_NOT_OK;
   }
   else{
      GetRdcAnlernenLokalisierungLesenDS( Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if(ucReifenPannenerkennung_aktiv != (uint8) AKTIV_RDC){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcErfsEcoTabelleLesen_E_NOT_OK;
   }
   else{
      if(GetMaxTyreTablePos() == L_OL_TYP_TYR_SignalUngueltig){
         *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
         ucRetVal = RTE_E_PiServiceDcmRdcErfsEcoTabelleLesen_E_NOT_OK;
      }
      else{
         *ErrorCode = RTE_E_OK;
         ucRetVal = RTE_E_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcErfsEcoTabelleLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcErfsEcoTabelleLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcErfsEcoTabLesenDS( Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsInaktivereignis_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsInaktivereignis_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsInaktivereignis_E_NOT_OK;
   }
   else{
      ReadInaktivereignisDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsKalibrierereignis_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsKalibrierereignis_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsKalibrierereignis_E_NOT_OK;
   }
   else{
      ReadCalibrationEventDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis1_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis1_E_NOT_OK;
   }
   else{
      ReadWarnereignis_1_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis2_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis2_E_NOT_OK;
   }
   else{
      ReadWarnereignis_2_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis3_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignis3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignis3_E_NOT_OK;
   }
   else{
      ReadWarnereignis_3_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisRuecknahme_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisRuecknahme_E_NOT_OK;
   }
   else{
      ReadWarnereignisRuecknahmeDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich1_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich1_E_NOT_OK;
   }
   else{
      ReadWarnereignisWeich_1_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich2_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich2_E_NOT_OK;
   }
   else{
      ReadWarnereignisWeich_2_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich3_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcHsWarnereignisWeich3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcHsWarnereignisWeich3_E_NOT_OK;
   }
   else{
      ReadWarnereignisWeich_3_DS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock1_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock1_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock1_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock1_E_NOT_OK;
   }
   else{
      GetStatusRdcMessdatenblockDS(self, 0, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock2_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock2_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock2_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock2_E_NOT_OK;
   }
   else{
      GetStatusRdcMessdatenblockDS(self, 1, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock3_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock3_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock3_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock3_E_NOT_OK;
   }
   else{
      GetStatusRdcMessdatenblockDS(self, 2, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock4_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock4_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcMessdatenblock4_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcMessdatenblock4_E_NOT_OK;
   }
   else{
      GetStatusRdcMessdatenblockDS(self, 3, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcRidAktReifenLaufstreckeLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcRidAktReifenLaufstreckeLesen_E_NOT_OK;
   }
   else{
      GetRdcRidAktReifenLaufstreckeLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcRidAktReifenQrCodeLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcRidAktReifenQrCodeLesen_E_NOT_OK;
   }
   else{
      GetRdcRidAktReifenQRCodeLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcRidAlteReifenLaufstreckeLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcRidAlteReifenLaufstreckeLesen_E_NOT_OK;
   }
   else{
      GetRdcRidAlteReifenLaufstreckeLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmRdcRidAlteReifenQrCodeLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmRdcRidAlteReifenQrCodeLesen_E_NOT_OK;
   }
   else{
      GetRdcRidAlteReifenQRCodeLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcDeveloperDataLesen_E_NOT_OK;
   }
   else{
      if(ucGetDeveloperDataMuxChannelDS() > cStatusRdcDeveloperDataLesen_MuxChannelMaxValidValue){
         *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
         ucRetVal = RTE_E_PiServiceDcmStatusRdcDeveloperDataLesen_E_NOT_OK;
      }
      else{
         *ErrorCode = RTE_E_OK;
         ucRetVal = RTE_E_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcDeveloperDataLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcDeveloperDataLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcDeveloperDataLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsAktReifenEcoLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsAktReifenEcoLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcErfsAktReifenEcoLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsAktReifenLesen_E_NOT_OK;
   }
   else{
      if(bGetCRdciEcoRcpEnableCD() == TRUE){
         *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
         ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsAktReifenEcoLesen_E_NOT_OK;
      }
      else{
         *ErrorCode = RTE_E_OK;
         ucRetVal = RTE_E_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsAktReifenLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcErfsAktReifenLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsTsaDatenLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcErfsTsaDatenLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcErfsTsaDatenLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   ReadTsaDataDS(self, Data);
   return RTE_E_OK;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcExtParkSupervisionLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcExtParkSupervisionLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcExtParkSupervisionLesen(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcLesen_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcLesen_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcLesen_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcLesen_E_NOT_OK;
   }
   else{
      GetStatusRdcLesenDS(self, Data);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcVersion_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusRdcVersion_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusRdcVersion_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusRdcVersion_E_NOT_OK;
   }
   else{
      Data[0] = (uint8) ((cRDCI_VERSION >> 8) & 0x00FF);
      Data[1] = (uint8) ((cRDCI_VERSION >> 0) & 0x00FF);
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead(Rte_Instance self, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmStatusReLesenDruckcodierung_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      ucRetVal = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmStatusReLesenDruckcodierung_ReadData(Rte_Instance self, P2VAR(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) Data){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDcmStatusReLesenDruckcodierung_E_NOT_OK;
   }
   else{
      GetStatusReLesenDruckcodierungDS( Data);
      InitStatusReLesenDruckcodierungDS();
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernDigitalRdc_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernDigitalRdc_E_NOT_OK;
   }
   else{
      ucRetVal = ucPutSteuernDigitalRdcDS(self, Data[0], Data[1]);
      if(RTE_E_OK == ucRetVal){
         *ErrorCode = RTE_E_OK;
      }
      else{
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
         ucRetVal = RTE_E_PiServiceDcmSteuernDigitalRdc_E_NOT_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRadelektronikVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   uint32         ulReID   = 0;
   uint8          ucRadPos = cAnzRad;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRadelektronikVorgeben_E_NOT_OK;
   }
   else{
      ulReID = (
                     ((uint32) Data[0] << 24)
                  +  ((uint32) Data[1] << 16)
                  +  ((uint32) Data[2] <<  8)
                  +  ((uint32) Data[3] <<  0)
      );
      ucRadPos = Data[4];
      ucRetVal = ucPutSteuernRadelektronikVorgebenDS(self, ulReID, ucRadPos);
      if(RTE_E_OK == ucRetVal){
         *ErrorCode = RTE_E_OK;
      }
      else{
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
         ucRetVal = RTE_E_PiServiceDcmSteuernRadelektronikVorgeben_E_NOT_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcDeveloperConfig_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcDeveloperConfig_E_NOT_OK;
   }
   else{
      ucRetVal = ucPutSteuernRdcDeveloperConfigDS(Data[0], &Data[1]);
      if(RTE_E_OK == ucRetVal){
         *ErrorCode = RTE_E_OK;
      }
      else{
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
         ucRetVal = RTE_E_PiServiceDcmSteuernRdcDeveloperConfig_E_NOT_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsDeveloperConfig_E_NOT_OK;
   }
   else{
      ucRetVal = RTE_E_OK;
      *ErrorCode = RTE_E_OK;
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoAktReifenPosVorgeben_E_NOT_OK;
   }
   else{
      ucRetVal = ucPutSteuernRdcErfsEcoAktReifenposVorgebenDS(self, Data);
      if(RTE_E_OK == ucRetVal){
         *ErrorCode = RTE_E_OK;
      }
      else{
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
         ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoAktReifenPosVorgeben_E_NOT_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, ImpTypeRefDcm_OpStatusType OpStatus, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   static NvM_RequestResultType ucNvmReqResult = NVM_REQ_OK;
          Std_ReturnType        ucRetVal       = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_E_NOT_OK;
   }
   else{
      if(NVM_REQ_PENDING != ucNvmReqResult){
         ucRetVal = ucPutSteuernRdcErfsEcoNeueReifenVorgebenDS(self, Data);
         if((Data[0] >= 0) && (Data[0] < TYRE_LIST_MAX_ELEMENTS)){
            ucRetVal |= Rte_Call_CpNvmRdciErfsEcoBlock_SetDataIndex(self, Data[0]);
            ucRetVal |= Rte_Call_CpNvmRdciErfsEcoBlock_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self));
            aucNvmSaveAttempts[cErfsEcoBlock]++;
            if(RTE_E_OK != ucRetVal){
               *ErrorCode = RTE_E_OK;
               ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_DCM_E_PENDING;
            }
         }
         else{
           *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
           ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_E_NOT_OK;
         }
      }
      if(RTE_E_OK == ucRetVal){
         (void) Rte_Call_CpNvmRdciErfsEcoBlock_GetErrorStatus(self, &ucNvmReqResult );
         if(NVM_REQ_OK == ucNvmReqResult){
           ucDataIndex = 0xFF;
           *ErrorCode = RTE_E_OK;
         }
         else{
           *ErrorCode = RTE_E_OK;
           ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoNeueReifenVorgeben_DCM_E_PENDING;
         }
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, ImpTypeRefDcm_OpStatusType OpStatus, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   static NvM_RequestResultType ucNvmReqResult = NVM_REQ_OK;
   static uint8                 DataIndex      = 0x00;
          Std_ReturnType        ucRetVal       = RTE_E_OK;
          uint8                 i;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoReifentabelleVorgeben_E_NOT_OK;
   }
   else{
      *ErrorCode = RTE_E_OK;
      if(TRUE == CalcDiagTyreListCrcAndCompare(Data)){
         if(DataIndex <= TYRE_LIST_MAX_ELEMENTS){
            if(NVM_REQ_PENDING != ucNvmReqResult){
               ucRetVal  = ucPutSteuernRdcErfsEcoReifentabelleVorgebenDS (self, Data, DataIndex);
               ucRetVal |= Rte_Call_CpNvmRdciErfsEcoBlock_SetDataIndex   (self, DataIndex);
               ucRetVal |= Rte_Call_CpNvmRdciErfsEcoBlock_WriteBlock     (self, (uint8*) Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self));
               aucNvmSaveAttempts[cErfsEcoBlock]++;
            }
            (void) Rte_Call_CpNvmRdciErfsEcoBlock_GetErrorStatus(self, &ucNvmReqResult);
            if((RTE_E_OK == ucRetVal) && (NVM_REQ_OK == ucNvmReqResult)){
               for(i = 0; i < TYRE_DATA_BYTES; i++){
                  SetDiagTyreListMember(DataIndex,i,Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i]);
               }
               DataIndex++;
            }
            ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoReifentabelleVorgeben_DCM_E_PENDING;
         }
         else{
            DataIndex = 0x00;
            if(BMW_FACTORY_HO == ucGetCRdciErfsPlacardSourceCD()){
               i = CopyDiagTyreListToTyreList(self);
               CompCurTyrSelWithTyreListEntries(self, i);
            }
         }
      }
      else{
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE; 
         ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsEcoReifentabelleVorgeben_E_NOT_OK;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDcmSteuernRdcErfsTsaDatenVorgeben_WriteData(Rte_Instance self, P2CONST(uint8, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) Data, P2VAR(ImpTypeRefDcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ErrorCode){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      ucRetVal = RTE_E_PiServiceDcmSteuernRdcErfsTsaDatenVorgeben_E_NOT_OK;
   }
   else{
      SaveTsaDataDS(self, Data);
      SetErfsTsaBlockWriteMeEE();
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAlloc1To3WrongWuMounted);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAlloc1To3WrongWuMounted);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_WrongMounted);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAlloc4WrongWuMounted);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAlloc4WrongWuMounted);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_WrongMounted);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_A_TEMP_SignalError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_A_TEMP_SignalError);
            ClearErrorConditionsNWM(cPTC_A_TEMP_Signal);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_A_TEMP_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_A_TEMP_MsgMissing);
            ClearErrorConditionsNWM(cPTC_A_TEMP_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciAusfall_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciAusfall);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciAusfall);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocAutoLearningFailed);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocAutoLearningFailed);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciBefuellhinweis);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciBefuellhinweis);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_CON_VEH_AliveError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_AliveError);
            ClearErrorConditionsNWM(cPTC_CON_VEH_Alive);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_CON_VEH_CrcError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_CrcError);
            ClearErrorConditionsNWM(cPTC_CON_VEH_Crc);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_CON_VEH_SignalError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_SignalError);
            ClearErrorConditionsNWM(cPTC_CON_VEH_Signal);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_CON_VEH_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_MsgMissing);
            ClearErrorConditionsNWM(cPTC_CON_VEH_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciDruckwarnung);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciDruckwarnung);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_EINHEITEN_SignalError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_EINHEITEN_SignalError);
            ClearErrorConditionsNWM(cPTC_EINHEITEN_Signal);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_EINHEITEN_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_EINHEITEN_MsgMissing);
            ClearErrorConditionsNWM(cPTC_EINHEITEN_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_ErfsCodingDataInconsistent);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocGatewayOrAntennaError);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocGatewayOrAntennaError);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_AntennaGateway);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciKalibrierung);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciKalibrierung);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocRdciOtherWuSensorType);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocRdciOtherWuSensorType);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciPannenwarnung);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciPannenwarnung);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciPartialSystemAvailability_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cRdciPartialSystemAvailability);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_AliveError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_AliveError);
            ClearErrorConditionsNWM(cPTC_RDC_DT_Alive);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_SignalError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_SignalError);
            ClearErrorConditionsNWM(cPTC_RDC_DT_Signal);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_MsgMissing);
            ClearErrorConditionsNWM(cPTC_RDC_DT_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_RELATIVZEIT_SignalError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_RELATIVZEIT_SignalError);
            ClearErrorConditionsNWM(cPTC_RELATIVZEIT_Signal);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_RELATIVZEIT_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_RELATIVZEIT_MsgMissing);
            ClearErrorConditionsNWM(cPTC_RELATIVZEIT_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocRdciRfExternalInterference);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_RfInterference);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciSystemNotAvailable_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cRdciSystemNotAvailable);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocUnspecifiedWfcDefect);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_Defect);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocUnspecifiedWuMute);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_Mute);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_V_VEH_AliveError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_AliveError);
            ClearErrorConditionsNWM(cPTC_V_VEH_Alive);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_SigQualifError);
            ClearErrorConditionsNWM(cPTC_V_VEH_SigQualif);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_SigQualifError);
            ClearErrorConditionsNWM(cPTC_V_VEH_SigQualif);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
Std_ReturnType ucRetVal = RTE_E_OK;

   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_V_VEH_CrcError);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_CrcError);
            ClearErrorConditionsNWM(cPTC_V_VEH_Crc);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearNetworkErrorNWM(self, cNetwork_V_VEH_MsgMissing);
            (void)ulGetNetworkErrorsNWM();
            ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_MsgMissing);
            ClearErrorConditionsNWM(cPTC_V_VEH_Missing);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearSecondaryErrorSCD(cSecondaryRdciWarnruecknahme);
            ClearSecondaryErrChangedFlagSCD(cSecondaryRdciWarnruecknahme);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuDefectFl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectFl);
            ClearErrorConditionsWUM(self, cWheelPos_FL, cPTC_Defect);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuDefectFr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectFr);
            ClearErrorConditionsWUM(self, cWheelPos_FR, cPTC_Defect);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuDefectRl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectRl);
            ClearErrorConditionsWUM(self, cWheelPos_RL, cPTC_Defect);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuDefectRr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectRr);
            ClearErrorConditionsWUM(self, cWheelPos_RR, cPTC_Defect);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuLocalisationFailed);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuLocalisationFailed);
            ClearErrorConditionsWUM(self, cWheelPos_NA, cPTC_LocalisationFailed);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryFl);
            ClearErrorConditionsWUM(self, cWheelPos_FL, cPTC_LowBat);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryFr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryFr);
            ClearErrorConditionsWUM(self, cWheelPos_FR, cPTC_LowBat);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryRl);
            ClearErrorConditionsWUM(self, cWheelPos_RL, cPTC_LowBat);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuLowBatteryRr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryRr);
            ClearErrorConditionsWUM(self, cWheelPos_RR, cPTC_LowBat);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuMuteFl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteFl);
            ClearErrorConditionsWUM(self, cWheelPos_FL, cPTC_Mute);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuMuteFr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteFr);
            ClearErrorConditionsWUM(self, cWheelPos_FR, cPTC_Mute);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuMuteRl);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteRl);
            ClearErrorConditionsWUM(self, cWheelPos_RL, cPTC_Mute);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(Std_ReturnType, CtApHufTpmsSWC_CODE) ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent(Rte_Instance self, ImpTypeRefDem_InitMonitorReasonType InitMonitorReason){
   Std_ReturnType ucRetVal = RTE_E_OK;
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
      ucRetVal = RTE_E_PiServiceDemCallbackInitMonitorForEvent_E_NOT_OK;
   }
   else{
      switch(InitMonitorReason){
         case DEM_INIT_MONITOR_CLEAR:
            ClearWheelUnitErrorWUM(self, cAllocWuMuteRr);
            (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
            ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteRr);
            ClearErrorConditionsWUM(self, cWheelPos_RR, cPTC_Mute);
            break;

         case DEM_INIT_MONITOR_RESTART:
            break;

         default:
            break;
      }
   }
   return ucRetVal;
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciCommonBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciCommonBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      if(NVM_REQ_OK == JobResult){
         switch(ServiceId){
            case NVM_READ_BLOCK:             break;
            case NVM_WRITE_BLOCK:            break;
            case NVM_RESTORE_BLOCK_DEFAULTS: break;
            case NVM_ERASE_BLOCK:            break;
            case NVM_INVALIDATE_NV_BLOCK:    break;
            case NVM_READ_ALL:               break;
            default:                         break;
         }
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
              SetDiagBlock1UpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciDiagBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetDiagBlock2UpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetErfsBlockWriteMeEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsEcoBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsEcoBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      if(NVM_REQ_OK == JobResult){
         switch(ServiceId){
             case NVM_READ_BLOCK:             break;
             case NVM_WRITE_BLOCK:            break;
             case NVM_RESTORE_BLOCK_DEFAULTS: break;
             case NVM_ERASE_BLOCK:            break;
             case NVM_INVALIDATE_NV_BLOCK:    break;
             case NVM_READ_ALL:               break;
             default:                         break;
         }
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsTsaBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciErfsTsaBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetErfsTsaBlockWriteMeEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetRidQrBlock1UpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciRidQrBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetRidQrBlock2UpdateFlagEE();
            }
            break;

        case NVM_RESTORE_BLOCK_DEFAULTS: break;
        case NVM_ERASE_BLOCK:            break;
        case NVM_INVALIDATE_NV_BLOCK:    break;
        case NVM_READ_ALL:               break;
        default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciWarnStatusBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciWarnStatusBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetWarnStatusBlockUpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZoHistoryBlock_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZoHistoryBlock_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetZoHistoryBlockUpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock1_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock1_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;

         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetZomBlock1UpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock2_NvMNotifyInitBlock_InitBlock(Rte_Instance self){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      ucNvmIsInitializedSWC = 0x00;
   }
}

FUNC(void, CtApHufTpmsSWC_CODE) ROpInvNvmRdciZomBlock2_NvMNotifyJobFinished_JobFinished(Rte_Instance self, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult){
   if((uint8) AKTIV_RDC != ucReifenPannenerkennung_aktiv){
   }
   else{
      switch(ServiceId){
         case NVM_READ_BLOCK:             break;
         case NVM_WRITE_BLOCK:
            if(NVM_REQ_OK != JobResult){
               SetZomBlock2UpdateFlagEE();
            }
            break;

         case NVM_RESTORE_BLOCK_DEFAULTS: break;
         case NVM_ERASE_BLOCK:            break;
         case NVM_INVALIDATE_NV_BLOCK:    break;
         case NVM_READ_ALL:               break;
         default:                         break;
      }
   }
}
#define CTAPHUFTPMSSWC_STOP_SEC_CODE
#include "CtApHufTpmsSWC_MemMap.h"

static void ReadAbsAndRdcDataFromRteSWC(Rte_Instance self){
   static uint8                ucReadAbsRdcAlternating = 0;
          ImpTypeRecCddAbsData absData                 = {0};
          ImpTypeRecCddRdcData rdcData                 = {0};
          uint8                ucErrorValue            = 0;
          uint8                ucTelegramType          = 0;
   if(ucReadAbsRdcAlternating < 10){
      do{
         ucErrorValue = Rte_Receive_RpCddAbsData_DeCddAbsData(self, &absData);
         if(RTE_E_OK == ucErrorValue){
            SetAbsDataWAM( absData);
            ucReadAbsRdcAlternating ++;
         }
         else{
            ucReadAbsRdcAlternating = 10;
         }
      }
      while (ucReadAbsRdcAlternating < 10);
   }
   else{
      do{
         ucErrorValue = Rte_Receive_RpCddRdcData_DeCddRdcData(self, &rdcData);
         if(RTE_E_OK == ucErrorValue){
            ucReadAbsRdcAlternating++;
            ucErrorValue   = CheckRDC_DT_PCKG12_MsgNWM(self, &rdcData);
            ucTelegramType = ucGetTelegramTypeSWC(&rdcData);
            if(TELTYPE_INVALID != ucTelegramType){
               if(TELTYPE_FBD4_ALIVE == (ucTelegramType & TELTYPE_FBD4_ALIVE)){
                  ProcessWuMonitoringWUM(self, rdcData, ucTelegramType);
                  PutRfBackgroundNoiseLevelDM(&rdcData);
               }
               else if(TELTYPE_RID == (ucTelegramType & TELTYPE_RID)){
                  if(
                        (FALSE == bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError))
                     && (cAliveError != (ucErrorValue & cAliveError))
                  ){
                     ProcessWuMonitoringWUM (self, rdcData, ucTelegramType);
                     SaveRidWeDataDM        (self, rdcData);
                  }
               }
               else{
                  if(
                        (FALSE == bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError))
                     && (cAliveError != (ucErrorValue & cAliveError))
                     && (FALSE == CheckReIdLatelyProcBufDM(rdcData.TYR_ID))
                  ){
                     (void) ucSetRdcDataDM(&rdcData, ucTelegramType);
                     WriteReIdLatelyProcBufDM(rdcData.TYR_ID);
                  }
               }
            }
         }
         else{
            ucReadAbsRdcAlternating = 30;
         }
      }while(ucReadAbsRdcAlternating < 30);
      ucReadAbsRdcAlternating = 0;
   }
   ProcessTelegramWaitingQueueSWC(self);
}

static void ProcessTelegramWaitingQueueSWC(Rte_Instance self){
   uint8                ucTelegramType = 0;
   ImpTypeRecCddRdcData rdcData        = {0};
   RdcDataWaitingTimerTickDM();
   if(cRdcDataAvailable == ucGetRdcDataDM(&rdcData, &ucTelegramType)){
      ProcessAllocationWAM   (self, rdcData);
      ProcessWuMonitoringWUM (self, rdcData, ucTelegramType);
      (void)ucNewReDataDM    (self, rdcData);
   }
}

static void FiveSecondsTaskSWC(Rte_Instance self){
   static uint16 ushTime5sec = 0;
   switch(ushTime5sec){
      case c5secTaskTimeslot_35: WatoTickWAM              (self); break;
      case c5secTaskTimeslot_36: CyclicTAF                (self); break;
      case c5secTaskTimeslot_37: CyclicSRA                (self); break;
      case c5secTaskTimeslot_38: SaveCompleteQrCodeDataDS (self); break;
      default:                                                    break;
   }
   ushTime5sec++;
   if(500 == ushTime5sec){
      ushTime5sec = 0;
   }
}

static void TwoMinutesTaskSWC(Rte_Instance self){
   static uint16 ushTime2min = 0;
   switch(ushTime2min){
      case c2minTaskTimeslot_2000: SendTPMSInternalLastValuesSWC (self); break;
      case c2minTaskTimeslot_2100: SendTPMSCalibrationDataSWC    (self); break;
      case c2minTaskTimeslot_2200: SendTPMSErfsActualTireDataSWC (self); break;
      case c2minTaskTimeslot_2300: SendTPMSTireMileageDataSWC    (self); break;
      case c2minTaskTimeslot_2400: SendTPMSQrCodeDataSWC         (self); break;
      default:                                                           break;
   }
   ushTime2min++;
   if(ushTime2min > 12000){
      ushTime2min = 0;
   }
}

static void OneSecondTaskSWC(Rte_Instance self){
   static uint16 ushTime1sec = 0;
          uint8  ucState;
          uint16 ushTimerTicks;
   switch(ushTime1sec){
      case c1secTaskTimeslot_5:
         WuMonitoringTimerTickWUM (self);
         StatusbarTimerTickSBR    (self);
         ExternalTemperatureTimerTickDM();
         switch(PmDataAllocTimerTickFBD()){
            case (uint8)8: UpdateFbd4ControlDataSWC    (self, cNoIdFiltering, cUpdateRe0        ); break;
            case (uint8)7: UpdateFbd4ControlDataSWC    (self, cNoIdFiltering, cUpdateRe01       ); break;
            case (uint8)6: UpdateFbd4ControlDataSWC    (self, cNoIdFiltering, cUpdateRe012      ); break;
            case (uint8)5: UpdateFbd4ControlDataSWC    (self, cNoIdFiltering, cUpdateRe0123     ); break;
            case (uint8)4: UpdateFbd4ParkingMonitorSWC (self, cFbdMonitorOff, cFbdDataRequest   ); break;
            case (uint8)3: UpdateFbd4ParkingMonitorSWC (self, cFbdMonitorOff, cFbdNoDataRequest ); break;
            case (uint8)2: UpdateFbd4ParkingMonitorSWC (self, cFbdMonitorOff, cFbdDataRequest   ); break;
            case (uint8)1: UpdateFbd4ParkingMonitorSWC (self, cFbdMonitorOn,  cFbdDataRequest   ); break;
            default:                                                                               break;
         }
         (void) Rte_Call_CpNvmRdciZoHistoryBlock_SetRamBlockStatus  (self, TRUE);
         (void) Rte_Call_CpNvmRdciCommonBlock_SetRamBlockStatus     (self, TRUE);
         (void) Rte_Call_CpNvmRdciDiagBlock1_SetRamBlockStatus      (self, TRUE);
         (void) Rte_Call_CpNvmRdciDiagBlock2_SetRamBlockStatus      (self, TRUE);
         (void) Rte_Call_CpNvmRdciErfsBlock_SetRamBlockStatus       (self, TRUE);
         (void) Rte_Call_CpNvmRdciErfsEcoBlock_SetRamBlockStatus    (self, TRUE);
         (void) Rte_Call_CpNvmRdciErfsTsaBlock_SetRamBlockStatus    (self, TRUE);
         (void) Rte_Call_CpNvmRdciWarnStatusBlock_SetRamBlockStatus (self, TRUE);
         (void) Rte_Call_CpNvmRdciRidQrBlock1_SetRamBlockStatus     (self, TRUE);
         (void) Rte_Call_CpNvmRdciRidQrBlock2_SetRamBlockStatus     (self, TRUE);
         (void) Rte_Call_CpNvmRdciZomBlock1_SetRamBlockStatus       (self, TRUE);
         (void) Rte_Call_CpNvmRdciZomBlock2_SetRamBlockStatus       (self, TRUE);
         break;

      case c1secTaskTimeslot_6:  SaveNvmDiagBlock1OnEventSWC      (self); break;
      case c1secTaskTimeslot_7:  SaveNvmDiagBlock2OnEventSWC      (self); break;
      case c1secTaskTimeslot_8:  SaveNvmErfsBlockOnEventSWC       (self); break;
      case c1secTaskTimeslot_9:  SaveNvmRidQrBlock1OnEventSWC     (self); break;
      case c1secTaskTimeslot_15: SaveNvmRidQrBlock2OnEventSWC     (self); break;
      case c1secTaskTimeslot_16: SaveNvmZoHistoryBlockOnEventSWC  (self); break;
      case c1secTaskTimeslot_17: SaveNvmWarnstatusBlockOnEventSWC (self); break;
      case c1secTaskTimeslot_18: SaveNvmErfsTsaBlockOnEventSWC    (self); break;

      case c1secTaskTimeslot_25:
         ucState = GETucAipGpsStateEE(self);
         if(TRUE == bGetNetworkErrorNWM(cNetwork_DT_PT_1_MsgMissing)){
            ucState &= (uint8) ~(cAGS_AipSigRec | cAGS_AipSigValid);
            PUTucAipEngDrvEE   (self, (Rdci_AIP_ENG_DRV_Type) 0xffu);
            PUTucAipGpsStateEE (self, ucState);
         }
         if(0 != (bGetNetworkErrorNWM(cNetwork_NMEARawData2Part2_MsgMissing) + bGetNetworkErrorNWM(cNetwork_NMEARawData2Part3_MsgMissing))){
            ucState &= (uint8) ~(cAGS_GpsAltSigRec | cAGS_GpsAltSigValid | cAGS_GpsErrAltSigRec | cAGS_GpsErrAltSigValid | cAGS_GpsAltSigTio);
            PUTushPositionAltitudeEE    (self, (Rdci_GNSSPositionAltitude_Type)    0xffffu);
            PUTushErrorAltitudeMetersEE (self, (Rdci_GNSSErrorAltitudeMeters_Type) 0xffffu);
            PUTushGpsTioTicksEE         (self, 0);
            PUTucAipGpsStateEE          (self, ucState);
         }
         if(TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
            if(cAGS_GpsAltSigTio == (ucState & cAGS_GpsAltSigTio)){
               ushTimerTicks = GETushGpsTioTicksEE(self);
               if(ushTimerTicks > 0){
                  ushTimerTicks--;
               }
               else{
                  PUTucPAmbValEE(self, cAGS_AipDefaultVal);
               }
               PUTushGpsTioTicksEE(self, ushTimerTicks);
            }
         }
         break;

      default:
         break;
   }
   ushTime1sec++;
   if(100 == ushTime1sec){
      ushTime1sec = 0;
   }
}

static void HundredMillisecondsTaskSWC(Rte_Instance self){
   static uint16                     ushTime100ms = 0;
          Rdci_AVL_P_TYR_FLH_Type    avlPTyreFL;
          Rdci_AVL_P_TYR_FRH_Type    avlPTyreFR;
          Rdci_AVL_P_TYR_RLH_Type    avlPTyreRL;
          Rdci_AVL_P_TYR_RRH_Type    avlPTyreRR;
          Rdci_AVL_TEMP_TYR_FLH_Type avlTTyreFL;
          Rdci_AVL_TEMP_TYR_FRH_Type avlTTyreFR;
          Rdci_AVL_TEMP_TYR_RLH_Type avlTTyreRL;
          Rdci_AVL_TEMP_TYR_RRH_Type avlTTyreRR;
          Rdci_TAR_P_TYR_FLH_Type    tarPTyreFL;
          Rdci_TAR_P_TYR_FRH_Type    tarPTyreFR;
          Rdci_TAR_P_TYR_RLH_Type    tarPTyreRL;
          Rdci_TAR_P_TYR_RRH_Type    tarPTyreRR;
          Rdci_ST_TYR_Type           tStTyre = {0};
          uint8                      ucPSollKalt;
          sint8                      scTSollKalt;
          uint8                      ucPSollWarm;
          sint8                      scTSollWarm;
          uint8                      ucTref;
          uint8                      ucPva;
          uint8                      ucPha;
          uint16                     ushMSoll_l;
          uint8                      ucEnvP_l;
          uint8                      ucSTWTChangeDet;

   switch(ushTime100ms){
      case c100msecTaskTimeslot_0:
         if(TRUE == bGetBandmodeBM()){
            CycleBandModeServiceBM(self, bGetBitFahrzeugzustandFZZ(cBM_VTHRES));
            PUTushBandmodeStateEE(  self, (ushGetStateBM() & cushThisBitsSavedInEeBM));
         }
         if(FALSE == GetDisplayConfTimeoutITY()){
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_ST_SLCTN_BAX_TYP_TYR(self, FALSE);
         }
         if(FALSE == GetStChangeTimeITY()){
            if(GetStWheelTypeChangeDetEventDM(1) != StatusWheelTypeChangeDetection_RDC_noch_nicht_verfuegbar){
               CopyStWheelTypeChangeBufAndRestartTimerDM();
            }
            else{
               ucSTWTChangeDet = GetStWheelTypeChangedDetStateDM();
               Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection( self, ucSTWTChangeDet);
               Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(  self, StatusWheelTypeChangePosition_Position_Unbekannt);
            }
         }
         else{
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangeDetection( self, GetStWheelTypeChangeDetEventDM(0));
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_StatusWheelTypeChange_StatusWheelTypeChangePosition(  self, GetStWheelTypeChangePosDM());
         }
         break;

      case c100msecTaskTimeslot_1:
         MainSCC(self);
         DeleteReIdLatelyProcBufDM();
         break;

      case c100msecTaskTimeslot_2:
         CyclicRDCiFunctionDM(                                             self);
         VklFklHandlingSWC(                                                self);
         GetTyrePressureValueITY(                                          self, &avlPTyreFL, &avlPTyreFR, &avlPTyreRL, &avlPTyreRR);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FLH(       self, avlPTyreFL);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_FRH(       self, avlPTyreFR);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RLH(       self, avlPTyreRL);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_P_TYR_AVL_P_TYR_RRH(       self, avlPTyreRR);
         GetTyreTemperatureValueITY(                                       self, &avlTTyreFL, &avlTTyreFR, &avlTTyreRL, &avlTTyreRR);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FLH( self, avlTTyreFL);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_FRH( self, avlTTyreFR);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RLH( self, avlTTyreRL);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_AVL_TEMP_TYR_AVL_TEMP_TYR_RRH( self, avlTTyreRR);
         GetRelatedPressureValueITY(                                       self, &tarPTyreFL, &tarPTyreFR, &tarPTyreRL, &tarPTyreRR);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FLH(       self, ushGetMaxValueDM(tarPTyreFL, tarPTyreFR));
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_FRH(       self, ushGetMaxValueDM(tarPTyreFL, tarPTyreFR));
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RLH(       self, ushGetMaxValueDM(tarPTyreRL, tarPTyreRR));
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TAR_P_TYR_TAR_P_TYR_RRH(       self, ushGetMaxValueDM(tarPTyreRL, tarPTyreRR));
         GetStTyrITY(                                                      &tStTyre.QU_FN_TYR_INFO, &tStTyre.QU_TPL, &tStTyre.QU_TFAI);
         (void) Rte_Send_PpFrPdu_ST_TYR_ST_TYR(                            self, &tStTyre);
         if(FALSE == bGetBandmodeBM()){
            TimerTickNWM(self);
         }
         ProcessIeFiFoDS(self);
         break;

      case c100msecTaskTimeslot_3:
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_ExtParkSupConfig(             self, ucGetCRdciParkSupExtParkSupConfigCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_MobilityLossThresholdValue(   self, ucGetCRdciParkSupMobilityLossThValueCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueC(  self, ucGetCRdciParkSupNotifThCValueCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_NotificationThresholdValueNc( self, ucGetCRdciParkSupNotifThNcValueCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueC(       self, ucGetCRdciParkSupWarningThCValueCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_WarningThresholdValueNc(      self, ucGetCRdciParkSupWarningThNcValueCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolNoTempComp(                self, ucGetCRdciParkSupTolNoTempCompCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_TolTempComp(                  self, ucGetCRdciParkSupTolTempCompCD());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_PwfChange(                    self, ucGetStatusConditionVehicleFZZ());
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_LastReceivedAmbientPressure(  self, (uint8) (((GETucPAmbValEE(self) * 25) - 600) / 2));
         if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
            (void) ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, ucGetColOfWP(cRadPosVL));
            if((ucPSollKalt == cInvalidREpressure) || (scTSollKalt == cInvalidREtemperature)){
               (void) ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, ucGetColOfWP(cRadPosVR));
               if((ucPSollKalt == cInvalidREpressure) || (scTSollKalt == cInvalidREtemperature)){
                  ucTref = RDCSystemReferenceTemp_Funktionsschnittstelle_ist_nicht_vLIFMXP;
                  ucPva  = RelRecommendedColdInflationPressure_FunktionsschnittstellQ2FK13;
               }
               else{
                  ucTref = (uint8) (scTSollKalt + 50);
                  ucPva  = (((ucPSollKalt * 25) + 50) / 100);
               }
            }
            else{
               ucTref = (uint8) (scTSollKalt + 50);
               ucPva  = (((ucPSollKalt * 25) + 50) / 100);
            }
            (void) ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, ucGetColOfWP(cRadPosHL));
            if((ucPSollKalt == cInvalidREpressure) || (scTSollKalt == cInvalidREtemperature)){
               (void) ucGetPTSollUSWIF(self, &ucPSollKalt, &scTSollKalt, &ucPSollWarm, &scTSollWarm, &ushMSoll_l, &ucEnvP_l, ucGetColOfWP(cRadPosHR));
               if((ucPSollKalt == cInvalidREpressure) || (scTSollKalt == cInvalidREtemperature)){
                  ucTref = RDCSystemReferenceTemp_Funktionsschnittstelle_ist_nicht_vLIFMXP;
                  ucPha  = RelRecommendedColdInflationPressure_FunktionsschnittstellQ2FK13;
               }
               else{
                  ucTref = (uint8) (scTSollKalt + 50);
                  ucPha  = (((ucPSollKalt * 25) + 50) / 100);
               }
            }
            else{
               ucTref = (uint8) (scTSollKalt + 50);
               ucPha  = (((ucPSollKalt * 25) + 50) / 100);
            }
         }
         else{
            ucTref = RDCSystemReferenceTemp_Funktionsschnittstelle_ist_nicht_vLIFMXP;
            ucPva  = RelRecommendedColdInflationPressure_FunktionsschnittstellQ2FK13;
            ucPha  = RelRecommendedColdInflationPressure_FunktionsschnittstellQ2FK13;
         }
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RDCSystemReferenceTemp(                       self, ucTref);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureFrontAxle(self, ucPva);
         Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TyreParkSupervision_RelRecommendedColdInflationPressureRearAxle(  self, ucPha);
         break;

      case c100msecTaskTimeslot_4:
         CyclicDemServicesSWC(self, c100msecTaskTimeslot_4);
         break;

      case c100msecTaskTimeslot_6:
         CyclicDemServicesSWC(self, c100msecTaskTimeslot_6);
         break;

      case c100msecTaskTimeslot_8:
         CyclicDemServicesSWC(self, c100msecTaskTimeslot_8);
         break;

      default:
         break;
   }
   ushTime100ms++;
   if(10 == ushTime100ms){
      ushTime100ms = 0;
   }
}

static void TwentyMillisecondsTaskSWC(Rte_Instance self, uint8 swcRunTime){
   static uint8 ucTime20ms = 0;
   ucTime20ms++;
   if(2 == ucTime20ms){
#if(USE_DEBUG_MESSAGE == 1)
      SetSwcRunTimeDBG(swcRunTime);
      SendDebugMessageSWC(self);
#endif
      ucTime20ms = 0;
   }
}

static void TenMillisecondsTaskSWC(Rte_Instance self, Rdci_RQ_OL_TPCT_Type* opRequestTyreList){
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_L_OL_TYP_TYR(self, GetLengthOfTyreListDM());
   if(TRUE == bGetCRdciStatInitCD()){Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self, GETucStatusbarEE(self));}
   else                             {Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_QU_RDC_INIT_DISP(self, QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens);}
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_SUTR_AVLB( self, GetSummerTyreIndexDM());
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_TYR(       self, GETStSelectTyreEE(self));
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_SLCTN_WITR_AVLB( self, GetWinterTyreIndexDM());
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TAR_P_LOCO_TPCT( self, GetLoadStateDM());
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_TYR_SEA_TPCT(    self, GetSeasonDM());
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_OP_IDR_MSGC(        self, GetIDRMessageCenterDM());
   Rte_IWrite_RCyclicRDCiTask_PpFrPdu_ST_TYR_2_ST_MAN_SLCTN(       self, GetStatusManSelectionDM());
   SetSeasonTyreData   (self);
   SetAxleTyreData     (self);
   SendTyreListElement (self, opRequestTyreList);
   UpdateFbd4IdsSWC    (self);
}

static void VklFklHandlingSWC(Rte_Instance self){
   static ImpTypeRecCcm_DISP_CC_BYPA_00 tFkl;
   static ImpTypeRecCcm_DISP_CC_BYPA_00 tVkl;
          uint8                         ucLoop;
   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if(cCcStartStopState_Stop == ucFillVklDataCCM(ucLoop, &tVkl.NO_CC_BYPA_00, &tVkl.ST_CC_BYPA_00, &tVkl.ST_IDC_CC_BYPA_00, &tVkl.TRANF_CC_BYPA_00)){
         if(RTE_E_OK == Rte_Send_PpCcm_DISP_CC_BYPA_00_DeCcm_DISP_CC_BYPA_00(self, &tVkl)){SetVklStopedCCM(ucLoop, TRUE );}
         else                                                                             {SetVklStopedCCM(ucLoop, FALSE);}
      }
   }
   for(ucLoop = 0; ucLoop < cCcIX_NumberOfMessages; ucLoop++){
      if(cCcStartStopState_Start == ucFillVklDataCCM(ucLoop, &tVkl.NO_CC_BYPA_00, &tVkl.ST_CC_BYPA_00, &tVkl.ST_IDC_CC_BYPA_00, &tVkl.TRANF_CC_BYPA_00)){
         if(RTE_E_OK == Rte_Send_PpCcm_DISP_CC_BYPA_00_DeCcm_DISP_CC_BYPA_00(self, &tVkl)){SetVklStartedCCM(ucLoop, TRUE );}
         else                                                                             {SetVklStartedCCM(ucLoop, FALSE);}
      }
   }
   if(cCcStartStopState_Start == ucFillFklDataCCM(&tFkl.NO_CC_BYPA_00, &tFkl.ST_CC_BYPA_00, &tFkl.ST_IDC_CC_BYPA_00, &tFkl.TRANF_CC_BYPA_00)){
      if(RTE_E_OK == Rte_Send_PpCcm_DISP_CC_BYPA_00_DeCcm_DISP_CC_BYPA_00(self, &tFkl)){SetFklStartedCCM(TRUE );}
      else                                                                             {SetFklStartedCCM(FALSE);}
   }
   else if(cCcStartStopState_Stop == ucFillFklDataCCM( &tFkl.NO_CC_BYPA_00, &tFkl.ST_CC_BYPA_00, &tFkl.ST_IDC_CC_BYPA_00, &tFkl.TRANF_CC_BYPA_00)){
      if(RTE_E_OK == Rte_Send_PpCcm_DISP_CC_BYPA_00_DeCcm_DISP_CC_BYPA_00(self, &tFkl)){SetFklStopedCCM(TRUE );}
      else                                                                             {SetFklStopedCCM(FALSE);}
   }
   else{}
}

static void UpdateFbd4IdsSWC(Rte_Instance self){
   static uint8  ucLastHistoryIdChanged = 0;
   if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
      if(ucGetIdChangedBitsZK() > 0){
         if(ucGetIdChangedBitsZK() != ucLastHistoryIdChanged){
            UpdateFbd4ControlDataSWC(self, cNoIdFiltering, cUpdateRe0123);
         }
         ucLastHistoryIdChanged = ucGetIdChangedBitsZK();
      }
   }
}

static uint8 CalcRuntimeSWC(Rte_Instance self, uint32 swcRunTime1){
   uint8                swcRunTime;
   uint32               swcRunTime2;
   StbMB_SystemTimeType sysTime;
   (void) Rte_Call_StbMB_AbsoluteTimeBaseValue_GetAbsoluteTime(self, &sysTime);
   swcRunTime2 = sysTime.ticks;
   if(swcRunTime2 >= swcRunTime1){
      swcRunTime = (uint8)(((swcRunTime2 - swcRunTime1) / (uint32)4000) & 0xff);
   }
   else{
      swcRunTime = (uint8)((((0xee6b2800u - swcRunTime1) + swcRunTime2) / (uint32)4000) & 0xff);
   }
   return swcRunTime;
}

static void InitSWC(Rte_Instance self){
   uint8                           ucErrorValue = 0xff;
   uint8                           ucQueueEraseCounter;
   ImpTypeRecCddAbsData            absData;
   ImpTypeRecCddRdcData            rdcData;
   ImpTypeRefDem_UdsStatusByteType EventStatusByte;

   InitRDCiEepromDM(self);
   InitCOD(self);

   if((uint8) AKTIV_RDC == ucReifenPannenerkennung_aktiv){
      if(Rte_Call_DemErrorRdci1To3WrongWuMountedInfo_GetEventStatus(         self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAlloc1To3WrongWuMounted         );}}
      if(Rte_Call_DemErrorRdci4WrongWuMountedInfo_GetEventStatus(            self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAlloc4WrongWuMounted            );}}
      if(Rte_Call_DemErrorRdciAutoLearningFailedInfo_GetEventStatus(         self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocAutoLearningFailed         );}}
      if(Rte_Call_DemErrorRdciGatewayOrAntennaErrorInfo_GetEventStatus(      self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocGatewayOrAntennaError      );}}
      if(Rte_Call_DemErrorRdciOtherWuSensorTypeInfo_GetEventStatus(          self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocRdciOtherWuSensorType      );}}
      if(Rte_Call_DemErrorRdciRfExternalInterferenceInfo_GetEventStatus(     self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocRdciRfExternalInterference );}}
      if(Rte_Call_DemErrorRdciUnspecifiedWfcDefectInfo_GetEventStatus(       self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocUnspecifiedWfcDefect       );}}
      if(Rte_Call_DemErrorRdciUnspecifiedWuMuteInfo_GetEventStatus(          self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute          );}}
      if(Rte_Call_DemErrorRdciWuDefectFlInfo_GetEventStatus(                 self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuDefectFl                 );}}
      if(Rte_Call_DemErrorRdciWuDefectFrInfo_GetEventStatus(                 self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuDefectFr                 );}}
      if(Rte_Call_DemErrorRdciWuDefectRlInfo_GetEventStatus(                 self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuDefectRl                 );}}
      if(Rte_Call_DemErrorRdciWuDefectRrInfo_GetEventStatus(                 self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuDefectRr                 );}}
      if(Rte_Call_DemErrorRdciWuLocalisationFailedInfo_GetEventStatus(       self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuLocalisationFailed       );}}
      if(Rte_Call_DemErrorRdciWuLowBatteryFlInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFl             );}}
      if(Rte_Call_DemErrorRdciWuLowBatteryFrInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuLowBatteryFr             );}}
      if(Rte_Call_DemErrorRdciWuLowBatteryRlInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRl             );}}
      if(Rte_Call_DemErrorRdciWuLowBatteryRrInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuLowBatteryRr             );}}
      if(Rte_Call_DemErrorRdciWuMuteFlInfo_GetEventStatus(                   self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuMuteFl                   );}}
      if(Rte_Call_DemErrorRdciWuMuteFrInfo_GetEventStatus(                   self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuMuteFr                   );}}
      if(Rte_Call_DemErrorRdciWuMuteRlInfo_GetEventStatus(                   self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuMuteRl                   );}}
      if(Rte_Call_DemErrorRdciWuMuteRrInfo_GetEventStatus(                   self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetWheelUnitErrorWUM(self, cAllocWuMuteRr                   );}}

      (void)ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
      ClearWheelUnitErrChangedFlagsWUM();

      if(Rte_Call_DemErrorRdciATempInvalidInfo_GetEventStatus(               self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_A_TEMP_SignalError         );}}
      if(Rte_Call_DemErrorRdciATempTimeoutInfo_GetEventStatus(               self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_A_TEMP_MsgMissing          );}}
      if(Rte_Call_DemErrorRdciRdcDtPckg1InvalidInfo_GetEventStatus(          self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_SignalError    );}}
      if(Rte_Call_DemErrorRdciRdcDtPckg1TimeoutInfo_GetEventStatus(          self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_MsgMissing     );}}
      if(Rte_Call_DemErrorRdciRdcDtPckg1AliveInfo_GetEventStatus(            self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_AliveError     );}}
      if(Rte_Call_DemErrorRdciEinheitenBn2020InvalidInfo_GetEventStatus(     self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_EINHEITEN_SignalError      );}}
      if(Rte_Call_DemErrorRdciEinheitenBn2020TimeoutInfo_GetEventStatus(     self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_EINHEITEN_MsgMissing       );}}
      if(Rte_Call_DemErrorRdciConVehAliveInfo_GetEventStatus(                self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_CON_VEH_AliveError         );}}
      if(Rte_Call_DemErrorRdciConVehCrcInfo_GetEventStatus(                  self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_CON_VEH_CrcError           );}}
      if(Rte_Call_DemErrorRdciConVehInvalidInfo_GetEventStatus(              self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_CON_VEH_SignalError        );}}
      if(Rte_Call_DemErrorRdciConVehTimeoutInfo_GetEventStatus(              self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_CON_VEH_MsgMissing         );}}
      if(Rte_Call_DemErrorRdciErfsCodingDataInconsistentInfo_GetEventStatus(self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_ErfsCodingDataInconsistent );}}
      if(Rte_Call_DemErrorRdciRelativzeitInvalidInfo_GetEventStatus(         self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_RELATIVZEIT_SignalError    );}}
      if(Rte_Call_DemErrorRdciRelativzeitTimeoutInfo_GetEventStatus(         self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_RELATIVZEIT_MsgMissing     );}}
      if(Rte_Call_DemErrorRdciVVehAliveFailureInfo_GetEventStatus(           self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_V_VEH_AliveError           );}}
      if(Rte_Call_DemErrorRdciVVehCrcFailureInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_V_VEH_CrcError             );}}
      if(Rte_Call_DemErrorRdciVVehCogInvalidInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError       );}}
      if(Rte_Call_DemErrorRdciVVehCogQualifierInfo_GetEventStatus(           self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError       );}}
      if(Rte_Call_DemErrorRdciVVehTimeoutInfo_GetEventStatus(                self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetNetworkErrorNWM(self, cNetwork_V_VEH_MsgMissing           );}}

      (void)ulGetNetworkErrorsNWM();
      ClearNetworkErrChangedFlagsNWM();

      if(Rte_Call_DemErrorRdciKalibrierungInfo_GetEventStatus(               self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciKalibrierung       );}}
      if(Rte_Call_DemErrorRdciAusfallInfo_GetEventStatus(                    self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciAusfall            );}}
      if(Rte_Call_DemErrorRdciBefuellhinweisInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciBefuellhinweis     );}}
      if(Rte_Call_DemErrorRdciDruckwarnungInfo_GetEventStatus(               self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciDruckwarnung       );}}
      if(Rte_Call_DemErrorRdciPannenwarnungInfo_GetEventStatus(              self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciPannenwarnung      );}}
      if(Rte_Call_DemErrorRdciWarnruecknahmeInfo_GetEventStatus(             self, &EventStatusByte) == E_OK){if((EventStatusByte & cDEM_STATUS_DTC_IS_ACTIVE) == cDEM_STATUS_DTC_IS_ACTIVE){SetSecondaryErrorSCD(cSecondaryRdciWarnruecknahme     );}}

      ClearSecondaryErrChangedFlagsSCD();

      ucQueueEraseCounter = 10; do{ucErrorValue = Rte_Receive_RpCddAbsData_DeCddAbsData(self, &absData); ucQueueEraseCounter--;}while((ucErrorValue == 0x00) && (ucQueueEraseCounter > 0));
      ucQueueEraseCounter = 10; do{ucErrorValue = Rte_Receive_RpCddRdcData_DeCddRdcData(self, &rdcData); ucQueueEraseCounter--;}while((ucErrorValue == 0x00) && (ucQueueEraseCounter > 0));

      InitRDCiFunctionsPartOneDM(self);

      if(TRUE == CheckCodingDataCrcCD(self)){
         RestartSystemAfterCodingCD(self);
      }

      if(ST_TAR_P_LOCO_TPCT_Signal_ungueltig == GETSelectedLoadStateEE(self)){
         PUTSelectedLoadStateEE(self, GetDefaultLoadCondDM());
      }

      if(ST_MAN_SLCTN_Signal_ungueltig == GETStManSelectionEE(self)){
         PUTStManSelectionEE(self, bGetCRdciDefaultMenuSelCD());
      }

      UpdateFbd4ParkingMonitorSWC(self, cFbdMonitorOff, cFbdNoDataRequest);
      UpdateFbd4ControlDataSWC(    self, cNoIdFiltering, cUpdateNoRe);

      (void)InitTyreList(self);
   }
   bInitIsDone = TRUE;
}

static void InitCOD(Rte_Instance self){
   const uint8* pucArray;

#if(IGNORE_CODING_SWITCH == 1)
      ucReifenPannenerkennung_aktiv = (uint8) AKTIV_RDC;
#else
      ucReifenPannenerkennung_aktiv = (self)->RpCalPrmRDCi.Prm_C_Funktion_ReifenPannenerkennung_aktiv_e();
#endif

   PutCRdciTPrewarnNcCD(                 (boolean) Rte_Prm_RpCalPrmRDCi_CRdciTPrewarnNc(                          self));
   PutCRdciMaxThresholdCD(               (boolean) Rte_Prm_RpCalPrmRDCi_CRdciMaxThreshold(                        self));
   PutCRdciPrewarnEnableCD(              (boolean) Rte_Prm_RpCalPrmRDCi_CRdciPrewarnEnable(                       self));
   PutCRdciStatInitCD(                   (boolean) Rte_Prm_RpCalPrmRDCi_CRdciStatInit(                            self));
   PutCRdciNumPrewarnDetectCD(           (boolean) Rte_Prm_RpCalPrmRDCi_CRdciNumPrewarnDetect(                    self));
   PutCRdciPrewarnIgnitionCD(            (boolean) Rte_Prm_RpCalPrmRDCi_CRdciPrewarnIgnition(                     self));
   PutCRdciPanneBefPosCD(                (boolean) Rte_Prm_RpCalPrmRDCi_CRdciPanneBefPos(                         self));
   PutCRdciFastDeflateEnableCD(          (boolean) Rte_Prm_RpCalPrmRDCi_CRdciFastDeflateEnable(                   self));
   PutCRdciTyrIdFiltGwCD(                (boolean) Rte_Prm_RpCalPrmRDCi_CRdciTyrIdFiltGw(                         self));
   PutCRdciResetPlausiCD(                (boolean) Rte_Prm_RpCalPrmRDCi_CRdciResetPlausi(                         self));
   PutCRdciTpmsMarketCD(                 (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciTpmsMarket(                          self));
   PutCRdciSensorForeignAkRdkCD(         (boolean) Rte_Prm_RpCalPrmRDCi_CRdciSensorForeignAkRdk(                  self));
   PutCRdciSensorLocSyncCD(              (boolean) Rte_Prm_RpCalPrmRDCi_CRdciSensorLocSync(                       self));
   PutCRdciErfsEnableCD(                 (boolean) Rte_Prm_RpCalPrmRDCi_CRdciErfsEnable(                          self));
   PutCRdciTrefSeasonalAdjustmentCD(     (boolean) Rte_Prm_RpCalPrmRDCi_CRdciTrefSeasonalAdjustment(              self));
   PutCRdciDispResetCD(                  (boolean) Rte_Prm_RpCalPrmRDCi_CRdciDispReset(                           self));
   PutCRdciCorHoldOffTimeCD(             (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciCorHoldOffTime(                      self) * 5);
   PutCRdciTRefShiftCD(                  (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciTRefShift(                           self));
   PutCRdciUiaThCCD(                     (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciUiaThC(                              self));
   PutCRdciUiwThCCD(                     (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciUiwThC(                              self));
   PutCRdciUiaThNcCD(                    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciUiaThNc(                             self));
   PutCRdciUiwThNcCD(                    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciUiwThNc(                             self));
   PutCRdciPanneThCD(                    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciPanneTh(                             self));
   PutCRdciMinRcpFaCD(                   (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciMinRcpFa(                            self));
   PutCRdciMinRcpRaCD(                   (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciMinRcpRa(                            self));
   PutCRdciDeltaPLRCD(                   (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciDeltaPLR(                            self));
   PutCRdciPInitRangeMaxCD(              (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciPInitRangeMax(                       self));
   PutCRdciTimeoutPrewarnCD(             (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciTimeoutPrewarn(                      self));
   PutCRdciDtAmbPrewarnCD(               (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciDtAmbPrewarn(                        self));
   PutCRdciDpToIPminCD(                  (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciDpToIPmin(                           self));

   pucArray = (const uint8*) Rte_Prm_RpCalPrmRDCi_CRdciLearnLocateConfig(self);
   PutCRdciLearnLocateConfigCD(          pucArray[0], 0);
   PutCRdciLearnLocateConfigCD(          pucArray[1], 1);

   PutCRdciXminCoolTireCD(               (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciXminCoolTire(                        self));
   PutCRdciMaxCorTimeCD(                 (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciMaxCorTime(                          self));
   PutCRdciMaxCorRcpCD(                  (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciMaxCorRcp(                           self));
   PutCRdciThCTolCD(                     (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciThCTol(                              self));
   PutCRdciThNCTolCD(                    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciThNCTol(                             self));
   PutCRdciLongHoldTimeCD(               (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciLongHoldTime(                        self) + 5);
   PutCRdciShortHoldTimeCD(              (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciShortHoldTime(                       self) + 1);
   PutCRdciEcoRcpEnableCD(               (boolean) Rte_Prm_RpCalPrmRDCi_CRdciEcoRcpEnable(                        self));
   PutCRdciDefaultLoadCondCD(            (boolean) Rte_Prm_RpCalPrmRDCi_CRdciDefaultLoadCond(                     self));
   PutCRdciErfsPlacardSourceCD(          (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciErfsPlacardSource(                   self));
   PutCRdciDefaultMenuSelCD(             (boolean) Rte_Prm_RpCalPrmRDCi_CRdciDefaultMenuSel(                      self));
   PutCRdciDispConfTimeoutCD(            (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciDispConfTimeout(                     self));
   PutCRdciRidEnableCD(                  (boolean) Rte_Prm_RpCalPrmRDCi_CRdciRidEnable(                           self));

   pucArray = (const uint8*) Rte_Prm_RpCalPrmRDCi_CRdciTrefSeasAdjConfig(self);
   PutCRdciTrefSeasAdjConfigCD( pucArray[0], 0);
   PutCRdciTrefSeasAdjConfigCD( pucArray[1], 1);
   PutCRdciTrefSeasAdjConfigCD( pucArray[2], 2);
   PutCRdciTrefSeasAdjConfigCD( pucArray[3], 3);

   PutCRdciSpeedCcmEnableCD(             (boolean) Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmEnable(                      self));
   PutCRdciSpeedCcmThCD(                 (uint16)  Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmTh(                          self));
   PutCRdciSpeedCcmTimeCD(               (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmTime(                        self));
   PutCRdciSpeedCcmHystCD(               (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmHyst(                        self));
   PutCRdciSpeedCcmPressOffsetFaCD(      (sint16)  Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmPressOffsetFa(               self));
   PutCRdciSpeedCcmPressOffsetRaCD(      (sint16)  Rte_Prm_RpCalPrmRDCi_CRdciSpeedCcmPressOffsetRa(               self));
   PutCRdciParkSupExtParkSupConfigCD(    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupExtParkSupConfig(             self));
   PutCRdciParkSupMobilityLossThValueCD( (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupMobilityLossThresholdValue(   self));
   PutCRdciParkSupNotifThCValueCD(       (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupNotificationThresholdValueC(  self));
   PutCRdciParkSupNotifThNcValueCD(      (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupNotificationThresholdValueNc(self));
   PutCRdciParkSupTolNoTempCompCD(       (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupTolNoTempComp(                self));
   PutCRdciParkSupTolTempCompCD(         (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupTolTempComp(                  self));
   PutCRdciParkSupWarningThCValueCD(     (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupWarningThresholdValueC(       self));
   PutCRdciParkSupWarningThNcValueCD(    (uint8)   Rte_Prm_RpCalPrmRDCi_CRdciParkSupWarningThresholdValueNc(      self));
}

static uint8 InitTyreList(Rte_Instance self){
  const ImpTypeRecCRdciErfsReifenEco * pTyreListPtr;
   uint8 TyreListEntrySize, i, j, offset, MaxTyreIndex;
   boolean bConCheck = TRUE;

   MaxTyreIndex = L_OL_TYP_TYR_SignalUngueltig;

   if(bGetCRdciErfsEnableCD() == TRUE){
      for(i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
         for(j = 0; j < TYRE_DATA_BYTES; j++){
           SetTyreListMember(i,j,0xFF);
         }
      }

    TyreListEntrySize = GetSizeOfTyreListElementDM();

      if(ucGetCRdciErfsPlacardSourceCD() == CAF_ERFS2_ECO_BLOCK){
         pTyreListPtr = Rte_Prm_RpCalPrmRDCi_CRdciErfsReifenEco(self);
#ifdef D_SwcApplTpms_CLAR_LCI
         if(pTyreListPtr != NULL)
#else
         if(pTyreListPtr != NULL_PTR)
#endif
         {
            for(i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
               offset = (i * TyreListEntrySize);
               if(0xFF != pTyreListPtr->DeData[offset]){
                  MaxTyreIndex = i;
                  for(j = 0; j < TyreListEntrySize; j++){
                     SetTyreListMember(i,j,pTyreListPtr->DeData[j + offset ]);
                  }
               }
            }
            bConCheck = CheckTyreListConsistency(TyreListEntrySize, MaxTyreIndex);
            if(TRUE == bConCheck){
               MaxTyreIndex += 1;
               PUTInvalidTyreListEE(self, FALSE);
            }
            else{
               MaxTyreIndex = GetReducedTyreList(self);
            }
         }
         if(L_OL_TYP_TYR_SignalUngueltig == MaxTyreIndex){
            DegradeToOtherTyre(self);
            PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_RDC_degradiert_ungueltige_5LUQLJ, StatusWheelTypeChangePosition_Position_Unbekannt);
         }
         CompCurTyrSelWithTyreListEntries(self, MaxTyreIndex);
      }
   }
   else{
      DegradeToOtherTyre (self);
      ResetCurrentTyreSelectionDM(self);
      SetMaxTyreTablePos( L_OL_TYP_TYR_SignalUngueltig);
      SetLengthOfTyreListDM( L_OL_TYP_TYR_SignalUngueltig);
      PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_RDC_degradiert_eRFS_nicht_X1055P, StatusWheelTypeChangePosition_Position_Unbekannt);
   }
   return(MaxTyreIndex);
}

static uint8 InitTyreListCyclically(Rte_Instance self){
   uint8 TyreListEntrySize,j;
   boolean bConCheck = TRUE;
   static boolean bRead = NVM_REQ_OK;
  NvM_RequestResultType ucNvmReqResult;
   static uint8 MaxTyreIndex = L_OL_TYP_TYR_SignalUngueltig;
   if(bGetCRdciErfsEnableCD() == TRUE){
    TyreListEntrySize = GetSizeOfTyreListElementDM();
      if(ucGetCRdciErfsPlacardSourceCD() == BMW_FACTORY_HO){
      if(ucDataIndex == 0xFF){
        PUTInvalidTyreListEE(self, TRUE);
        (void) Rte_Call_CpNvmRdciErfsEcoBlock_SetDataIndex(self, 0);
        bRead = Rte_Call_CpNvmRdciErfsEcoBlock_ReadBlock(self, (uint8*) Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self));
        ucDataIndex = 0x00;
      }
      if(ucDataIndex < TYRE_LIST_MAX_ELEMENTS){
        (void) Rte_Call_CpNvmRdciErfsEcoBlock_GetErrorStatus(self, &ucNvmReqResult);

          if(NVM_REQ_PENDING != ucNvmReqResult){
          if((bRead == NVM_REQ_OK) && (NVM_REQ_OK == ucNvmReqResult)){
            if(Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[0] != 0xFF){
              MaxTyreIndex = ucDataIndex;
              for(j = 0; j < TyreListEntrySize; j++){
                SetTyreListMember(ucDataIndex,j,Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[j]);
              }
            }
            ucDataIndex++;
            (void) Rte_Call_CpNvmRdciErfsEcoBlock_SetDataIndex(self, ucDataIndex);
          }
          bRead = Rte_Call_CpNvmRdciErfsEcoBlock_ReadBlock(self, (uint8*) Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self));
        }
      }
      else{
          if(ucDataIndex == TYRE_LIST_MAX_ELEMENTS){
          ucDataIndex++;
          bConCheck = CheckTyreListConsistency(TyreListEntrySize, MaxTyreIndex);
          if(TRUE == bConCheck){
            MaxTyreIndex += 1;
            PUTInvalidTyreListEE(self, FALSE);
          }
          else{
            MaxTyreIndex = GetReducedTyreList(self);
          }

          if(L_OL_TYP_TYR_SignalUngueltig == MaxTyreIndex){
            DegradeToOtherTyre (self);
            PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_RDC_degradiert_ungueltige_5LUQLJ, StatusWheelTypeChangePosition_Position_Unbekannt);
          }

          CompCurTyrSelWithTyreListEntries(self, MaxTyreIndex);
        }
        else{
        }
      }
      }
   }
   return(MaxTyreIndex);
}

static void CompCurTyrSelWithTyreListEntries(Rte_Instance self, uint8 MaxTyreTableIx){
   uint8 i,j,MatchIx,FactoryTyreIndex, l_Season, ucCurTyreIx, ucAutoTyrIx, ucSuTyrIx, ucWiTyrIx, ucStManSel;
   boolean bComp;

  FactoryTyreIndex = OP_SLCTN_TYR_AVLB_AndererReifen;
   ucCurTyreIx = GETSelectedTyreIndexEE(self);
   ucAutoTyrIx = GETSelectedAutoTyreIndexEE(self);
   ucSuTyrIx = GETSelectedSuTyreIndexEE(self);
   ucWiTyrIx = GETSelectedWiTyreIndexEE(self);
   ucStManSel = GETStManSelectionEE(self);

   if(MaxTyreTableIx <= TYRE_LIST_MAX_ELEMENTS){
      for(l_Season = CSEASON_SUMMER; l_Season <= CSEASON_NOCHANGE; l_Season++){
      MatchIx = OP_SLCTN_TYR_AVLB_SignalUngueltig;

      if(GETCurErfsTyreDataEE(self, 0 , l_Season) != 0xFF){
        for(i=0;i<MaxTyreTableIx;i++){
          bComp = TRUE;

          for(j=0;j<TYRE_DATA_BYTES;j++){
            if(GetTyreListMember(i,j) != GETCurErfsTyreDataEE(self, j , l_Season)){
              bComp = FALSE;
            }
          }

          if((bComp == TRUE) && (MatchIx == OP_SLCTN_TYR_AVLB_SignalUngueltig)){
            MatchIx = i;
          }
        }
      }

      if(l_Season == CSEASON_SUMMER){
          if(MatchIx == OP_SLCTN_TYR_AVLB_SignalUngueltig){
          MatchIx = OP_SLCTN_TYR_AVLB_AndererReifen;
        }

          if(ucSuTyrIx != OP_SLCTN_TYR_AVLB_AndererReifen){
          ucSuTyrIx = MatchIx;
        }
      }
      else if(l_Season == CSEASON_WINTER){
          if(MatchIx == OP_SLCTN_TYR_AVLB_SignalUngueltig){
          MatchIx = OP_SLCTN_TYR_AVLB_AndererReifen;
        }

          if(ucWiTyrIx != OP_SLCTN_TYR_AVLB_AndererReifen){
          ucWiTyrIx = MatchIx;
        }
      }
      else{
          if(MatchIx == OP_SLCTN_TYR_AVLB_SignalUngueltig){
          if(GETSelectedAutoTyreIndexEE(self) == GETSelectedSuTyreIndexEE(self)){
            MatchIx = ucSuTyrIx;
          }
          else if(GETSelectedAutoTyreIndexEE(self) == GETSelectedWiTyreIndexEE(self)){
            MatchIx = ucWiTyrIx;
          }
          else{
            MatchIx = OP_SLCTN_TYR_AVLB_AndererReifen;
          }
        }
        ucAutoTyrIx = MatchIx;
      }
      }
   }

   if(ucCurTyreIx == OP_SLCTN_TYR_AVLB_SignalUngueltig){
      for(i=0;i<TYRE_LIST_MAX_ELEMENTS;i++){
      if(GetTyreListMember(i,0) != 0xFF){
          if(GetWerksauslieferungRaw(i) != 0x00){
           FactoryTyreIndex = i;
        }
      }
      }

      if((FactoryTyreIndex != OP_SLCTN_TYR_AVLB_AndererReifen) && (ucStManSel == OP_IDR_SLCTN_Manuelle_Auswahl)){
      ucCurTyreIx = FactoryTyreIndex;

      if(GETSelectedSeasonEE(self) == CSEASON_SUMMER){
        ucSuTyrIx = FactoryTyreIndex;
      }
      else{
        ucWiTyrIx = FactoryTyreIndex;
      }
      SetSolldruckDM(self, GETSelectedLoadStateEE(self), ucCurTyreIx);
      (void) ZoPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cZUGEORDNET), ucCurTyreIx);

      SetCalibrationRootCauseDS(self, cCalByDiag);
      (void)SaveCalibrationEventDS(self);

     }
      else{
      ucCurTyreIx = OP_SLCTN_TYR_AVLB_AndererReifen;
      }
   }
   else{
      if(ucCurTyreIx >= TYRE_LIST_MAX_ELEMENTS){
      if(ucStManSel == OP_IDR_SLCTN_Automatische_Auswahl){
          if(FALSE == GETTyreSelectionBckgrdEE(self)){
          ucStManSel = ST_MAN_SLCTN_Manuelle_Reifenauswahl;

          PUTTyreChangedEE(self, TRUE);
          PutStWheelTypeChangeEventDM(StatusWheelTypeChangeDetection_RDC_degradiert_kein_passenKH9ZA9, StatusWheelTypeChangePosition_Position_Unbekannt);
        }
      }
      }
      else{
      if(ucStManSel == OP_IDR_SLCTN_Manuelle_Auswahl){
          if(GETSelectedSeasonEE(self) == CSEASON_SUMMER){
          ucCurTyreIx = ucSuTyrIx;
        }
        else{
          ucCurTyreIx = ucWiTyrIx;
        }
      }
      else{
        ucCurTyreIx = ucAutoTyrIx;
      }
      }
   }
   PUTSelectedTyreIndexEE(self, ucCurTyreIx);
   PUTSelectedAutoTyreIndexEE(self, ucAutoTyrIx);
   PUTSelectedSuTyreIndexEE(self, ucSuTyrIx);
   PUTSelectedWiTyreIndexEE(self, ucWiTyrIx);
   PUTStManSelectionEE(self, ucStManSel);

   SetLoadStateDM( GETSelectedLoadStateEE(self));
   SetSeasonDM( GETSelectedSeasonEE(self));
   SetSummerTyreIndexDM( GETSelectedSuTyreIndexEE(self));
   SetWinterTyreIndexDM( GETSelectedWiTyreIndexEE(self));
   SetSelectedTyreIndexDM( GETSelectedTyreIndexEE(self));
   SetIDRMessageCenterDM( GETIdrMessageEE(self));
   SetStatusManSelectionDM( GETStManSelectionEE(self));
   SetMaxTyreTablePos( MaxTyreTableIx);
   SetLengthOfTyreListDM( MaxTyreTableIx);
}

static void DegradeToOtherTyre (Rte_Instance self){
   if(OP_SLCTN_TYR_AVLB_AndererReifen != GETSelectedTyreIndexEE(self)){
    PUTTyreChangedEE(self, TRUE);
   }
   PUTSelectedSuTyreIndexEE(self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedWiTyreIndexEE(self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedTyreIndexEE(self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedAutoTyreIndexEE(self, OP_SLCTN_TYR_AVLB_AndererReifen);
   PUTSelectedSeasonEE(self, CSEASON_SUMMER);
   PUTIdrMessageEE(self, OP_IDR_SLCTN_Signal_unbefuellt);
   PUTStManSelectionEE(self, ST_MAN_SLCTN_Manuelle_Reifenauswahl);
   PUTInvalidTyreListEE(self, TRUE);
   PUTStSelectTyreEE(self, ST_SLCTN_TYR_SignalUngueltig);
}

static uint8 GetReducedTyreList(Rte_Instance self){
   uint8 j,TyreListEntrySize,MaxTyreIndex;

   MaxTyreIndex = L_OL_TYP_TYR_SignalUngueltig;

   TyreListEntrySize = GetSizeOfTyreListElementDM();

   if(GETCurErfsTyreDataEE(self, 0, CSEASON_NOCHANGE) != 0xFF){
    MaxTyreIndex = 0;

      for(j = 0; j < TyreListEntrySize; j++){
      SetTyreListMember(MaxTyreIndex,j,GETCurErfsTyreDataEE(self, j, CSEASON_NOCHANGE));
      }
   }

   if(GETCurErfsTyreDataEE(self, 0, CSEASON_SUMMER) != 0xFF){
      if(MaxTyreIndex < L_OL_TYP_TYR_SignalUngueltig){
      MaxTyreIndex += 1;
      }
      else{
      MaxTyreIndex = 0;
      }

      for(j = 0; j < TyreListEntrySize; j++){
      SetTyreListMember(MaxTyreIndex,j,GETCurErfsTyreDataEE(self, j, CSEASON_SUMMER));
      }
   }

   if(GETCurErfsTyreDataEE(self, 0, CSEASON_WINTER) != 0xFF){
      if(MaxTyreIndex < L_OL_TYP_TYR_SignalUngueltig){
      MaxTyreIndex += 1;
      }
      else{
      MaxTyreIndex = 0;
      }

      for(j = 0; j < TyreListEntrySize; j++){
      SetTyreListMember(MaxTyreIndex,j,GETCurErfsTyreDataEE(self, j, CSEASON_WINTER));
      }
   }

   if(MaxTyreIndex < L_OL_TYP_TYR_SignalUngueltig){
    MaxTyreIndex +=1;
    bReducedTyreListActive = TRUE;
   }
   return(MaxTyreIndex);
}

static uint8 ucGetTelegramTypeSWC(const ImpTypeRecCddRdcData* rdcData){
   uint8 ucRetVal = TELTYPE_INVALID;
   static uint8 ucLastAlv[2] = { 0xff, 0xff };
   uint8 DpIx;

   if(rdcData->SUPP_ID == cSupplCodeUnknown){
      ucRetVal = TELTYPE_INVALID;
   }

   else if(rdcData->SUPP_ID == cSupplCodeUnused){
      if((rdcData->TYR_ID == 0) && (rdcData->PCKG_ID == 0xff)){
      if(0x34 == rdcData->DP_NO){
        DpIx = cDataPackage34Ix;
      }
      else{
        DpIx = cDataPackage12Ix;
      }

      if((rdcData->RDC_DT_6 != ucLastAlv[DpIx])
       && (rdcData->RDC_DT_6 != 0xff)){
        ucLastAlv[DpIx] = rdcData->RDC_DT_6;
        ucRetVal = TELTYPE_FBD4_ALIVE;
      }
      else{
        ucRetVal = TELTYPE_INVALID;
      }
      }

      else{
      ucRetVal = TELTYPE_INVALID;
      }
   }

   else if(rdcData->SUPP_ID != cSupplCodeHuf){
      if(bGetCRdciSensorForeignAkRdkCD() == TRUE){
      ucRetVal = TELTYPE_FOREIGN_SUPPLIER;
      }
      else{
      ucRetVal = TELTYPE_INVALID;
      }
   }

   else{
      ucRetVal = TELTYPE_STANDARD;
   }

   if((ucRetVal != TELTYPE_INVALID) && (ucRetVal != TELTYPE_FBD4_ALIVE)){
      switch(rdcData->PCKG_ID){
      case cTelTypeSELPAL:
      case cTelTypeSELPAL1:
      if(ucRdcChecksumSWC(rdcData, 10) == rdcData->RDC_DT_8){
        ucRetVal |= TELTYPE_ALLOCATABLE;
      }
      else{
        ucRetVal = TELTYPE_INVALID;
      }
            break;

      case cTelTypeContiFP:
      if((bGetCRdciSensorLocSyncCD() == TRUE) && (rdcData->SUPP_ID == cSupplCodeConti)){
          if(ucRdcChecksumSWC(rdcData, 10) == rdcData->RDC_DT_8){
          ucRetVal |= TELTYPE_ALLOCATABLE;
        }
        else{
          ucRetVal = TELTYPE_INVALID;
        }
      }
      else{
        ucRetVal = TELTYPE_INVALID;
      }
            break;

      case cTelTypeAK35def:
      case cTelTypeAK35defLMA:
      if(ucRdcChecksumSWC(rdcData, 7) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
      else if((rdcData->RDC_DT_2 & 0xF0u) == 0xF0){
        ucRetVal = TELTYPE_INVALID;
      }
      else {}

            break;

      case cTelTypeBeruLong:
      if(ucRdcChecksumSWC(rdcData, 10) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
            break;

      case cTelTypeBeruMed:
      if(ucRdcChecksumSWC(rdcData, 8) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
            break;

      case cTelTypeG4Standard:
      if(ucRdcChecksumSWC(rdcData, 8) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
            break;

      case cTelTypeTyreDataOE1:
      case cTelTypeTyreDIM:
      if(ucRdcChecksumSWC(rdcData, 11) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
      else{
        ucRetVal |= TELTYPE_RID;
      }
            break;

      case cTelTypeTyreDataOE2:
      if(ucRdcChecksumSWC(rdcData, 10) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
      else{
        ucRetVal |= TELTYPE_RID;
      }
            break;

      case cTelTypeTyreStatus:
      if(ucRdcChecksumSWC(rdcData, 9) != rdcData->RDC_DT_8){
        ucRetVal = TELTYPE_INVALID;
      }
      else{
        ucRetVal |= TELTYPE_RID;
      }
            break;

      case cTelTypeTyreDOT:
	    ucRetVal |= TELTYPE_RID;
            break;

         default:
      ucRetVal = TELTYPE_INVALID;
            break;
      }
   }
   return (ucRetVal);
}

static uint8 ucRdcChecksumSWC(const ImpTypeRecCddRdcData* rdcData, uint8 ucLength){
   uint8 aucBuffer[30];
   uint8 ucRetVal;

  aucBuffer[0] = rdcData->PCKG_ID;
  aucBuffer[1] = (rdcData->SUPP_ID << 4) | (uint8)(((rdcData->TYR_ID & (uint32)0x0f000000u) >> 24));
  aucBuffer[2] = (uint8)((rdcData->TYR_ID & (uint32)0x00ff0000u) >> 16);
  aucBuffer[3] = (uint8)((rdcData->TYR_ID & (uint32)0x0000ff00u) >> 8);
  aucBuffer[4] = (uint8) (rdcData->TYR_ID & (uint32)0x000000ffu);
  aucBuffer[5] = rdcData->RDC_DT_1;
  aucBuffer[6] = rdcData->RDC_DT_2;
  aucBuffer[7] = rdcData->RDC_DT_3;
  aucBuffer[8] = rdcData->RDC_DT_4;
  aucBuffer[9] = rdcData->RDC_DT_5;
  aucBuffer[10] = rdcData->RDC_DT_6;
  aucBuffer[11] = rdcData->RDC_DT_7;
   ucRetVal = ucCalcCrc8(aucBuffer, ucLength);
   return ucRetVal;
}

static void CyclicDemServicesSWC(Rte_Instance self, uint16 ushTimeSlot){
   static uint8 ucFsLoeschen = 0;

   uint32 ulDtc;
   uint32 ulDtcChangedFlag;
   boolean bWarningIndicator = FALSE;
   Std_ReturnType ucRteReturn = 0;

   if((GetMaxTyreTablePos() == L_OL_TYP_TYR_SignalUngueltig) || (bReducedTyreListActive == TRUE)){
      (void) Rte_Call_DemErrorRdciErfsCodingDataInconsistent_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
    SetNetworkErrorNWM(self, cNetwork_ErfsCodingDataInconsistent);
   }
   else{
      (void) Rte_Call_DemErrorRdciErfsCodingDataInconsistent_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
    ClearNetworkErrorNWM(self, cNetwork_ErfsCodingDataInconsistent);
   }

   if(ushTimeSlot == c100msecTaskTimeslot_4){
      ulDtc = ulGetWheelUnitErrorsWUM(cFilterSubseqErr);
      ulDtcChangedFlag = ulGetWheelUnitErrChangedFlagsWUM();

      if((ulDtc & cAllocGatewayOrAntennaError) == cAllocGatewayOrAntennaError){
      if((ulDtcChangedFlag & cAllocGatewayOrAntennaError) == cAllocGatewayOrAntennaError){
        (void) Rte_Call_DemErrorRdciGatewayOrAntennaError_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(0x01 == GetDataPackageErrorIndNWM(self, cGA_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcGatewayOrAntennaError);
        }
        else if(0x02 == GetDataPackageErrorIndNWM(self, cGA_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcGatewayOrAntennaError2ndFBD);
        }
        else{
          IeFiFoWriteEntryDS(self, cDtcGatewayOrAntennaErrorAllFBD);
        }
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciGatewayOrAntennaError_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocGatewayOrAntennaError);

      if((ulDtc & cAllocRdciOtherWuSensorType) == cAllocRdciOtherWuSensorType){
      if((ulDtcChangedFlag & cAllocRdciOtherWuSensorType) == cAllocRdciOtherWuSensorType){
        (void) Rte_Call_DemErrorRdciOtherWuSensorType_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciOtherWuSensorType_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocRdciOtherWuSensorType);

      if((ulDtc & cAllocRdciRfExternalInterference) == cAllocRdciRfExternalInterference){
      if((ulDtcChangedFlag & cAllocRdciRfExternalInterference) == cAllocRdciRfExternalInterference){
        (void) Rte_Call_DemErrorRdciRfExternalInterference_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcRdciRfExternalInterference);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRfExternalInterference_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocRdciRfExternalInterference);

      if((ulDtc & cAllocAutoLearningFailed) == cAllocAutoLearningFailed){
      if((ulDtcChangedFlag & cAllocAutoLearningFailed) == cAllocAutoLearningFailed){
        (void) Rte_Call_DemErrorRdciAutoLearningFailed_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcAutoLearningFailed);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciAutoLearningFailed_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocAutoLearningFailed);

      if((ulDtc & cAlloc4WrongWuMounted) == cAlloc4WrongWuMounted){
      if((ulDtcChangedFlag & cAlloc4WrongWuMounted) == cAlloc4WrongWuMounted){
        (void) Rte_Call_DemErrorRdci4WrongWuMounted_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdci4WrongWuMounted_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAlloc4WrongWuMounted);

      if((ulDtc & cAlloc1To3WrongWuMounted) == cAlloc1To3WrongWuMounted){
      if((ulDtcChangedFlag & cAlloc1To3WrongWuMounted) == cAlloc1To3WrongWuMounted){
        (void) Rte_Call_DemErrorRdci1To3WrongWuMounted_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdci1To3WrongWuMounted_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAlloc1To3WrongWuMounted);

      if((ulDtc & cAllocWuLocalisationFailed) == cAllocWuLocalisationFailed){
      if((ulDtcChangedFlag & cAllocWuLocalisationFailed) == cAllocWuLocalisationFailed){
        (void) Rte_Call_DemErrorRdciWuLocalisationFailed_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuLocalisationFailed_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuLocalisationFailed);

      if((ulDtc & cAllocWuMuteFl) == cAllocWuMuteFl){
      if((ulDtcChangedFlag & cAllocWuMuteFl) == cAllocWuMuteFl){
        (void) Rte_Call_DemErrorRdciWuMuteFl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuMuteFl);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuMuteFl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteFl);

      if((ulDtc & cAllocWuMuteFr) == cAllocWuMuteFr){
      if((ulDtcChangedFlag & cAllocWuMuteFr) == cAllocWuMuteFr){
        (void) Rte_Call_DemErrorRdciWuMuteFr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuMuteFr);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuMuteFr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteFr);

      if((ulDtc & cAllocWuMuteRl) == cAllocWuMuteRl){
      if((ulDtcChangedFlag & cAllocWuMuteRl) == cAllocWuMuteRl){
        (void) Rte_Call_DemErrorRdciWuMuteRl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuMuteRl);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuMuteRl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteRl);

      if((ulDtc & cAllocWuMuteRr) == cAllocWuMuteRr){
      if((ulDtcChangedFlag & cAllocWuMuteRr) == cAllocWuMuteRr){
        (void) Rte_Call_DemErrorRdciWuMuteRr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuMuteRr);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuMuteRr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuMuteRr);

      if((ulDtc & cAllocUnspecifiedWuMute) == cAllocUnspecifiedWuMute){
      if((ulDtcChangedFlag & cAllocUnspecifiedWuMute) == cAllocUnspecifiedWuMute){
        (void) Rte_Call_DemErrorRdciUnspecifiedWuMute_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcUnspecifiedWuMute);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciUnspecifiedWuMute_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocUnspecifiedWuMute);

      if((ulDtc & cAllocWuDefectFl) == cAllocWuDefectFl){
      if((ulDtcChangedFlag & cAllocWuDefectFl) == cAllocWuDefectFl){
        (void) Rte_Call_DemErrorRdciWuDefectFl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuDefectFl);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuDefectFl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectFl);

      if((ulDtc & cAllocWuDefectFr) == cAllocWuDefectFr){
      if((ulDtcChangedFlag & cAllocWuDefectFr) == cAllocWuDefectFr){
        (void) Rte_Call_DemErrorRdciWuDefectFr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuDefectFr);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuDefectFr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);

      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectFr);

      if((ulDtc & cAllocWuDefectRl) == cAllocWuDefectRl){
      if((ulDtcChangedFlag & cAllocWuDefectRl) == cAllocWuDefectRl){
        (void) Rte_Call_DemErrorRdciWuDefectRl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuDefectRl);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuDefectRl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);

      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectRl);

      if((ulDtc & cAllocWuDefectRr) == cAllocWuDefectRr){
      if((ulDtcChangedFlag & cAllocWuDefectRr) == cAllocWuDefectRr){
        (void) Rte_Call_DemErrorRdciWuDefectRr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcWuDefectRr);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuDefectRr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);

      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuDefectRr);

      if((ulDtc & cAllocUnspecifiedWfcDefect) == cAllocUnspecifiedWfcDefect){
      if((ulDtcChangedFlag & cAllocUnspecifiedWfcDefect) == cAllocUnspecifiedWfcDefect){
        (void) Rte_Call_DemErrorRdciUnspecifiedWfcDefect_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcUnspecifiedWfcDefect);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciUnspecifiedWfcDefect_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocUnspecifiedWfcDefect);

      if((ulDtc & cAllocWuLowBatteryFl) == cAllocWuLowBatteryFl){
      if((ulDtcChangedFlag & cAllocWuLowBatteryFl) == cAllocWuLowBatteryFl){
        (void) Rte_Call_DemErrorRdciWuLowBatteryFl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuLowBatteryFl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryFl);

      if((ulDtc & cAllocWuLowBatteryFr) == cAllocWuLowBatteryFr){
      if((ulDtcChangedFlag & cAllocWuLowBatteryFr) == cAllocWuLowBatteryFr){
        (void) Rte_Call_DemErrorRdciWuLowBatteryFr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuLowBatteryFr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryFr);

      if((ulDtc & cAllocWuLowBatteryRl) == cAllocWuLowBatteryRl){
      if((ulDtcChangedFlag & cAllocWuLowBatteryRl) == cAllocWuLowBatteryRl){
        (void) Rte_Call_DemErrorRdciWuLowBatteryRl_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuLowBatteryRl_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryRl);

      if((ulDtc & cAllocWuLowBatteryRr) == cAllocWuLowBatteryRr){
      if((ulDtcChangedFlag & cAllocWuLowBatteryRr) == cAllocWuLowBatteryRr){
        (void) Rte_Call_DemErrorRdciWuLowBatteryRr_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciWuLowBatteryRr_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearWheelUnitErrChangedFlagWUM(cAllocWuLowBatteryRr);

    CheckFunktionszustandDTC(self, ulDtc, cWUM_DTC);
   }
   else if(ushTimeSlot == c100msecTaskTimeslot_6){
      ulDtc = ulGetNetworkErrorsNWM();
      ulDtcChangedFlag = ulGetNetworkErrChangedFlagsNWM();

      if((ulDtc & cNetwork_A_TEMP_MsgMissing) == cNetwork_A_TEMP_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_A_TEMP_MsgMissing) == cNetwork_A_TEMP_MsgMissing){
        (void) Rte_Call_DemErrorRdciATempTimeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciATempTimeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_A_TEMP_MsgMissing);

      if((ulDtc & cNetwork_A_TEMP_SignalError) == cNetwork_A_TEMP_SignalError){
      if((ulDtcChangedFlag & cNetwork_A_TEMP_SignalError) == cNetwork_A_TEMP_SignalError){
        (void) Rte_Call_DemErrorRdciATempInvalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciATempInvalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_A_TEMP_SignalError);

      if((ulDtc & cNetwork_RDC_DT_PCKG_MsgMissing) == cNetwork_RDC_DT_PCKG_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_RDC_DT_PCKG_MsgMissing) == cNetwork_RDC_DT_PCKG_MsgMissing){
        (void) Rte_Call_DemErrorRdciRdcDtPckg1Timeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(0x01 == GetDataPackageErrorIndNWM(self, cDP_TO_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError1stFBD);
        }
        else if(0x02 == GetDataPackageErrorIndNWM(self, cDP_TO_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError2ndFBD);
        }
        else{
          IeFiFoWriteEntryDS(self, cDtcDataPackageErrorAllFBD);
        }
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRdcDtPckg1Timeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_MsgMissing);

      if((ulDtc & cNetwork_RDC_DT_PCKG_AliveError) == cNetwork_RDC_DT_PCKG_AliveError){
      if((ulDtcChangedFlag & cNetwork_RDC_DT_PCKG_AliveError) == cNetwork_RDC_DT_PCKG_AliveError){
        (void) Rte_Call_DemErrorRdciRdcDtPckg1Alive_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(0x01 == GetDataPackageErrorIndNWM(self, cDP_AE_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError1stFBD);
        }
        else if(0x02 == GetDataPackageErrorIndNWM(self, cDP_AE_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError2ndFBD);
        }
        else{
          IeFiFoWriteEntryDS(self, cDtcDataPackageErrorAllFBD);
        }
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRdcDtPckg1Alive_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_AliveError);

      if((ulDtc & cNetwork_RDC_DT_PCKG_SignalError) == cNetwork_RDC_DT_PCKG_SignalError){
      if((ulDtcChangedFlag & cNetwork_RDC_DT_PCKG_SignalError) == cNetwork_RDC_DT_PCKG_SignalError){
        (void) Rte_Call_DemErrorRdciRdcDtPckg1Invalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(0x01 == GetDataPackageErrorIndNWM(self, cDP_SE_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError1stFBD);
        }
        else if(0x02 == GetDataPackageErrorIndNWM(self, cDP_SE_SHIFT)){
          IeFiFoWriteEntryDS(self, cDtcDataPackageError2ndFBD);
        }
        else{
          IeFiFoWriteEntryDS(self, cDtcDataPackageErrorAllFBD);
        }
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRdcDtPckg1Invalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_RDC_DT_PCKG_SignalError);

      if((ulDtc & cNetwork_EINHEITEN_MsgMissing) == cNetwork_EINHEITEN_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_EINHEITEN_MsgMissing) == cNetwork_EINHEITEN_MsgMissing){
        (void) Rte_Call_DemErrorRdciEinheitenBn2020Timeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciEinheitenBn2020Timeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_EINHEITEN_MsgMissing);

      if((ulDtc & cNetwork_EINHEITEN_SignalError) == cNetwork_EINHEITEN_SignalError){
      if((ulDtcChangedFlag & cNetwork_EINHEITEN_SignalError) == cNetwork_EINHEITEN_SignalError){
        (void) Rte_Call_DemErrorRdciEinheitenBn2020Invalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciEinheitenBn2020Invalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_EINHEITEN_SignalError);

      if((ulDtc & cNetwork_CON_VEH_MsgMissing) == cNetwork_CON_VEH_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_CON_VEH_MsgMissing) == cNetwork_CON_VEH_MsgMissing){
        (void) Rte_Call_DemErrorRdciConVehTimeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciConVehTimeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_MsgMissing);

      if((ulDtc & cNetwork_CON_VEH_SignalError) == cNetwork_CON_VEH_SignalError){
      if((ulDtcChangedFlag & cNetwork_CON_VEH_SignalError) == cNetwork_CON_VEH_SignalError){
        (void) Rte_Call_DemErrorRdciConVehInvalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciConVehInvalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_SignalError);

      if((ulDtc & cNetwork_CON_VEH_AliveError) == cNetwork_CON_VEH_AliveError){
      if((ulDtcChangedFlag & cNetwork_CON_VEH_AliveError) == cNetwork_CON_VEH_AliveError){
        (void) Rte_Call_DemErrorRdciConVehAlive_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciConVehAlive_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_AliveError);

      if((ulDtc & cNetwork_CON_VEH_CrcError) == cNetwork_CON_VEH_CrcError){
      if((ulDtcChangedFlag & cNetwork_CON_VEH_CrcError) == cNetwork_CON_VEH_CrcError){
        (void) Rte_Call_DemErrorRdciConVehCrc_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciConVehCrc_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_CON_VEH_CrcError);

      if((ulDtc & cNetwork_RELATIVZEIT_MsgMissing) == cNetwork_RELATIVZEIT_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_RELATIVZEIT_MsgMissing) == cNetwork_RELATIVZEIT_MsgMissing){
        (void) Rte_Call_DemErrorRdciRelativzeitTimeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRelativzeitTimeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_RELATIVZEIT_MsgMissing);

      if((ulDtc & cNetwork_RELATIVZEIT_SignalError) == cNetwork_RELATIVZEIT_SignalError){
      if((ulDtcChangedFlag & cNetwork_RELATIVZEIT_SignalError) == cNetwork_RELATIVZEIT_SignalError){
        (void) Rte_Call_DemErrorRdciRelativzeitInvalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciRelativzeitInvalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_RELATIVZEIT_SignalError);

      if((ulDtc & cNetwork_V_VEH_MsgMissing) == cNetwork_V_VEH_MsgMissing){
      if((ulDtcChangedFlag & cNetwork_V_VEH_MsgMissing) == cNetwork_V_VEH_MsgMissing){
        (void) Rte_Call_DemErrorRdciVVehTimeout_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcSpeedSignalFailure);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciVVehTimeout_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_MsgMissing);

      if((ulDtc & cNetwork_V_VEH_SigQualifError) == cNetwork_V_VEH_SigQualifError){
      if((ulDtcChangedFlag & cNetwork_V_VEH_SigQualifError) == cNetwork_V_VEH_SigQualifError){
        (void) Rte_Call_DemErrorRdciVVehCogInvalid_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcSpeedSignalFailure);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciVVehCogInvalid_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      (void) Rte_Call_DemErrorRdciVVehCogQualifier_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_SigQualifError);

      if((ulDtc & cNetwork_V_VEH_AliveError) == cNetwork_V_VEH_AliveError){
      if((ulDtcChangedFlag & cNetwork_V_VEH_AliveError) == cNetwork_V_VEH_AliveError){
        (void) Rte_Call_DemErrorRdciVVehAliveFailure_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcSpeedSignalFailure);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciVVehAliveFailure_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_AliveError);

      if((ulDtc & cNetwork_V_VEH_CrcError) == cNetwork_V_VEH_CrcError){
      if((ulDtcChangedFlag & cNetwork_V_VEH_CrcError) == cNetwork_V_VEH_CrcError){
        (void) Rte_Call_DemErrorRdciVVehCrcFailure_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
        IeFiFoWriteEntryDS(self, cDtcSpeedSignalFailure);
      }
      }
      else{
      (void) Rte_Call_DemErrorRdciVVehCrcFailure_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      }
    ClearNetworkErrChangedFlagNWM(cNetwork_V_VEH_CrcError);

    CheckFunktionszustandDTC(self, ulDtc, cNW_DTC);
   }
   else{
      ulDtc = (uint32)GetSecondaryErrorsSCD();
      ulDtcChangedFlag = (uint32)GetSecondaryErrChangedFlagsSCD();
      if((ulDtc & cSecondaryRdciKalibrierung) == cSecondaryRdciKalibrierung){
          if((ulDtcChangedFlag & cSecondaryRdciKalibrierung) == cSecondaryRdciKalibrierung){
          ucRteReturn = Rte_Call_DemErrorRdciKalibrierung_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciKalibrierung);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciKalibrierung_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciKalibrierung);
      }

      if((ulDtc & cSecondaryRdciAusfall) == cSecondaryRdciAusfall){
          if((ulDtcChangedFlag & cSecondaryRdciAusfall) == cSecondaryRdciAusfall){
          ucRteReturn = Rte_Call_DemErrorRdciAusfall_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciAusfall);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciAusfall_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciAusfall);
      }

      if((ulDtc & cSecondaryRdciBefuellhinweis) == cSecondaryRdciBefuellhinweis){
          if((ulDtcChangedFlag & cSecondaryRdciBefuellhinweis) == cSecondaryRdciBefuellhinweis){
          ucRteReturn = Rte_Call_DemErrorRdciBefuellhinweis_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciBefuellhinweis);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciBefuellhinweis_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciBefuellhinweis);
      }

      if((ulDtc & cSecondaryRdciDruckwarnung) == cSecondaryRdciDruckwarnung){
          if((ulDtcChangedFlag & cSecondaryRdciDruckwarnung) == cSecondaryRdciDruckwarnung){
          ucRteReturn = Rte_Call_DemErrorRdciDruckwarnung_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciDruckwarnung);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciDruckwarnung_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciDruckwarnung);
      }

      if((ulDtc & cSecondaryRdciPannenwarnung) == cSecondaryRdciPannenwarnung){
          if((ulDtcChangedFlag & cSecondaryRdciPannenwarnung) == cSecondaryRdciPannenwarnung){
          ucRteReturn = Rte_Call_DemErrorRdciPannenwarnung_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciPannenwarnung);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciPannenwarnung_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciPannenwarnung);
      }

      if((ulDtc & cSecondaryRdciWarnruecknahme) == cSecondaryRdciWarnruecknahme){
          if((ulDtcChangedFlag & cSecondaryRdciWarnruecknahme) == cSecondaryRdciWarnruecknahme){
          ucRteReturn = Rte_Call_DemErrorRdciWarnruecknahme_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
          if(ucRteReturn == E_OK){
            ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciWarnruecknahme);
          }
        }
      }
      else{
        (void) Rte_Call_DemErrorRdciWarnruecknahme_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
        ClearSecondaryErrChangedFlagSCD((uint8)cSecondaryRdciWarnruecknahme);
      }
   }

   if(bGetBandmodeBM() == TRUE){
      if(ucFsLoeschen > 0){
      (void) Rte_Call_DemErrorRdciTpmsManufactoryMode_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      ucFsLoeschen--;
      }
      else{
      (void) Rte_Call_DemErrorRdciTpmsManufactoryMode_SetEventStatus(self, DEM_EVENT_STATUS_FAILED);
      }
   }

   else{
      (void) Rte_Call_DemErrorRdciTpmsManufactoryMode_SetEventStatus(self, DEM_EVENT_STATUS_PASSED);
      ucFsLoeschen = 0;
   }

   if(bPrio1ErrorIsSetWUM() == TRUE){
    bWarningIndicator = TRUE;
   }
   else if(bPrio1ErrorIsSetNWM() == TRUE){
    bWarningIndicator = TRUE;
   }
   else if(bSystemInactiveByRfInterferenceWUM() == TRUE){
    bWarningIndicator = TRUE;
   }
   else {}

   if(bWarningIndicator == FALSE){
    ClearBitBetriebszustandBZ(cDTC_INACTIVE);
   }
   else{
    SetBitBetriebszustandBZ(cDTC_INACTIVE);
   }
}

static void CheckFunktionszustandDTC(Rte_Instance self, uint32 ulDTC, const uint8 ErrType){
   uint8 ucAddDTC;
   static uint8 ucActiveFlags = 0x00;

   ucAddDTC = bGetBandmodeBM();

   if(cWUM_DTC == ErrType){
      if(((ulDTC & (cAllocRdciRfExternalInterference | cAllocAutoLearningFailed | cAllocWuMuteFl | cAllocWuMuteFr | cAllocWuMuteRl | cAllocWuMuteRr |
      cAllocWuDefectFl | cAllocWuDefectFr | cAllocWuDefectRl | cAllocWuDefectRr | cAllocUnspecifiedWfcDefect | cAllocUnspecifiedWuMute | cAllocGatewayOrAntennaError)) != cAllocNoError)
      || (ucAddDTC == TRUE)){
      ucActiveFlags |= cWUM_DTC;
      }
      else{
      ucActiveFlags &= (uint8)(cWUM_DTC^0xFF);
      }
   }
   else{
      if(((ulDTC & (cNetwork_RDC_DT_PCKG_MsgMissing | cNetwork_RDC_DT_PCKG_AliveError | cNetwork_RDC_DT_PCKG_SignalError | cNetwork_V_VEH_MsgMissing |
      cNetwork_V_VEH_CrcError | cNetwork_V_VEH_AliveError | cNetwork_V_VEH_SigQualifError)) != cAllocNoError)){
      ucActiveFlags |= cNW_DTC;
      }
      else{
      ucActiveFlags &= (uint8)(cNW_DTC ^ 0xFF);
      }
   }

   if(ucActiveFlags != 0x00){
      if(FALSE == bGetWheelUnitErrorWUM(cRdciSystemNotAvailable)){
      if(E_OK == Rte_Call_DemErrorRdciSystemNotAvailable_SetEventStatus(self, DEM_EVENT_STATUS_FAILED)){
        SetWheelUnitErrorWUM(self, cRdciSystemNotAvailable);
      }
      }
      if(TRUE == bGetWheelUnitErrorWUM(cRdciPartialSystemAvailability)){
      if(E_OK == Rte_Call_DemErrorRdciPartialSystemAvailability_SetEventStatus(self, DEM_EVENT_STATUS_PASSED)){
        ClearWheelUnitErrorWUM(self, cRdciPartialSystemAvailability);
      }
      }
   }
   else{
      if(TRUE == bGetWheelUnitErrorWUM(cRdciSystemNotAvailable)){
      if(E_OK == Rte_Call_DemErrorRdciSystemNotAvailable_SetEventStatus(self, DEM_EVENT_STATUS_PASSED)){
        ClearWheelUnitErrorWUM(self, cRdciSystemNotAvailable);
      }
      }
   }

   if(cWUM_DTC == ErrType){
      ucAddDTC = GetMaxTyreTablePos();

      if(((ulDTC & (cAlloc4WrongWuMounted|cAlloc1To3WrongWuMounted|cAllocWuLocalisationFailed)) != cAllocNoError)
        || (ucAddDTC == L_OL_TYP_TYR_SignalUngueltig)){
      if(FALSE == bGetWheelUnitErrorWUM(cRdciPartialSystemAvailability)){
          if(E_OK == Rte_Call_DemErrorRdciPartialSystemAvailability_SetEventStatus(self, DEM_EVENT_STATUS_FAILED)){
          SetWheelUnitErrorWUM(self, cRdciPartialSystemAvailability);
        }
      }
      }
      else{
      if(TRUE == bGetWheelUnitErrorWUM(cRdciPartialSystemAvailability)){
          if(E_OK == Rte_Call_DemErrorRdciPartialSystemAvailability_SetEventStatus(self, DEM_EVENT_STATUS_PASSED)){
          ClearWheelUnitErrorWUM(self, cRdciPartialSystemAvailability);
        }
      }
      }
   }
}

void ReInitRdciSWC(void){
   bInitIsDone = FALSE;
}

static void SetSeasonTyreData(Rte_Instance self){
	 TyreDataType TData;
	 uint8 SeasonIndex;

	SeasonIndex = GetSummerTyreIndexDM();

	if(GetListTyreDataITY(SeasonIndex, &TData) == E_OK){
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SOTR_TYP_TYR_ID2(self, 4);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_CAC_SUTR_TYP_TYR(self, TData.Carcass);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_LCC_SUTR_TYP_TYR(self, TData.LoadIndex);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_IDX_V_SUTR_TYP_TYR(self, TData.SpeedIndex);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RAD_SUTR_TYP_TYR(self, TData.Radius);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RELA_SIDE_SUTR_TYP_TYR(self, TData.SideRelation);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_RFL_SUTR_TYP_TYR(self, TData.Runflat);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_SEA_SUTR_TYP_TYR(self, TData.Season);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_SOTR_TYP_TYR_WID_SUTR_TYP_TYR(self, TData.Width);
	}

	SeasonIndex = GetWinterTyreIndexDM();

	if(GetListTyreDataITY(SeasonIndex, &TData) == E_OK){
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WITR_TYP_TYR_ID2(self, 3);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_CAC_WITR_TYP_TYR(self, TData.Carcass);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_LCC_WITR_TYP_TYR(self, TData.LoadIndex);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_IDX_V_WITR_TYP_TYR(self, TData.SpeedIndex);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RAD_WITR_TYP_TYR(self, TData.Radius);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RELA_SIDE_WITR_TYP_TYR(self, TData.SideRelation);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_RFL_WITR_TYP_TYR(self, TData.Runflat);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_SEA_WITR_TYP_TYR(self, TData.Season);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_WITR_TYP_TYR_WID_WITR_TYP_TYR(self, TData.Width);
	 }
}

static void SetAxleTyreData(Rte_Instance self){
   TyreDataType TData;

   TData.Width = 0;
   TData.SpeedIndex = 0;
   TData.SideRelation = 0;
   TData.Season = 0;
   TData.Runflat = 0;
   TData.LoadIndex = 0;
   TData.LengthOfRun = 0;
   TData.Carcass = 0;
   TData.Age = 0;
   TData.Abrasion = 0;

   if(GetRAxisTyreDataITY(self, &TData) == E_OK){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_BAX_TYP_TYR_ID2(self, 0);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_CAC_BAX_TYP_TYR(self, TData.Carcass);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_LCC_BAX_TYP_TYR(self, TData.LoadIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_IDX_V_BAX_TYP_TYR(self, TData.SpeedIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RAD_BAX_TYP_TYR(self, TData.Radius);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RELA_SIDE_BAX_TYP_TYR(self, TData.SideRelation);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_RFL_BAX_TYP_TYR(self, TData.Runflat);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_SEA_BAX_TYP_TYR(self, TData.Season);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_WID_BAX_TYP_TYR(self, TData.Width);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AG_BAX_TYP_TYR(self, TData.Age);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_AA_BAX_TYP_TYR(self, TData.Abrasion);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_BAX_TYP_TYR_LOR_BAX_TYP_TYR(self, TData.LengthOfRun);
   }

   if(GetFAxisTyreDataITY(self, &TData) == E_OK){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_FTAX_TYP_TYR_ID2(self, 2);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_CAC_FTAX_TYP_TYR(self, TData.Carcass);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_LCC_FTAX_TYP_TYR(self, TData.LoadIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_IDX_V_FTAX_TYP_TYR(self, TData.SpeedIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RAD_FTAX_TYP_TYR(self, TData.Radius);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RELA_SIDE_FTAX_TYP_TYR(self, TData.SideRelation);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_RFL_FTAX_TYP_TYR(self, TData.Runflat);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_SEA_FTAX_TYP_TYR(self, TData.Season);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_WID_FTAX_TYP_TYR(self, TData.Width);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AG_FTAX_TYP_TYR(self, TData.Age);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_AA_FTAX_TYP_TYR(self, TData.Abrasion);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FTAX_TYP_TYR_LOR_FTAX_TYP_TYR(self, TData.LengthOfRun);
   }
}

static void SendTyreListElement(Rte_Instance self, Rdci_RQ_OL_TPCT_Type* pReq){
	static uint8 TyreListElementCount = 0;
	TyreDataType TData;
	static boolean bListFastCycleActive = FALSE;
	static uint16 CycleTimer = cSlowListCycleTime;

	if(GetLengthOfTyreListDM() != CTLIST_INDEX_INVALID){
		if(*pReq == TRUE){
			TyreListElementCount = 0x00;

			bListFastCycleActive = TRUE;

			CycleTimer = 0x0001;

			*pReq = FALSE;

		}

		CycleTimer--;

		if(CycleTimer == 0x0000){
			if(GetListTyreDataITY(TyreListElementCount, &TData) == E_OK)
			{
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self, TData.Carcass);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self, TData.LoadIndex);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self, TData.SpeedIndex);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self, 5);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self, TData.Radius);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self, TData.SideRelation);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self, TData.Runflat);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self, TData.Season);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self, TyreListElementCount);
				Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self, TData.Width);
			}
			TyreListElementCount++;

			if(TyreListElementCount >= GetLengthOfTyreListDM())
			{
				bListFastCycleActive = FALSE;
				TyreListElementCount = 0;
			}

			if(bListFastCycleActive == TRUE)
			{
				CycleTimer = cFastListCycleTime;
			}
			else
			{
				CycleTimer = cSlowListCycleTime;
			}
		}
	}
	else{
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_CAC_TYP_TYR(self, CAC_TYP_TYR_SignalUngueltig);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_LCC_TYP_TYR(self, 0x3F);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_IDX_V_TYP_TYR(self, IDX_V_TYP_TYR_SignalUngueltig);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_OL_AVLB_TYP_TYR_ID2(self, 5);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RAD_TYP_TYR(self, 0x0F);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RELA_SIDE_TYP_TYR(self, 0x1F);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_RFL_TYP_TYR(self, RFL_TYP_TYR_SignalUngueltig);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_SEA_TYP_TYR(self, SEA_TYP_TYR_SignalUngueltig);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_ST_TYR_OL_ID(self, OP_SLCTN_TYR_AVLB_SignalUngueltig);
		Rte_IWrite_RCyclicRDCiTask_PpFrPdu_OL_AVLB_TYP_TYR_WID_TYP_TYR(self, 0x1F);

		*pReq = FALSE;
	}
}

static void SaveNvmCommonBlockOnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetCommonBlockUpdateFlagEE() == TRUE){
      ucWriteErrorState = Rte_Call_CpNvmRdciCommonBlock_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciCommonBlock_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearCommonBlockUpdateFlagEE();
      aucNvmSaveAttempts[cCommonBlock]++;
      }
      else{
      }
   }
}

static void SaveNvmDiagBlock1OnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetDiagBlock1UpdateFlagEE() == TRUE){
      ucWriteErrorState = Rte_Call_CpNvmRdciDiagBlock1_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciDiagBlock1_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearDiagBlock1UpdateFlagEE();
      aucNvmSaveAttempts[cDiagBlock1]++;
      }
      else{
      }
   }
}

static void SaveNvmDiagBlock2OnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetDiagBlock2UpdateFlagEE() == TRUE){
      ucWriteErrorState = Rte_Call_CpNvmRdciDiagBlock2_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciDiagBlock2_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearDiagBlock2UpdateFlagEE();
      aucNvmSaveAttempts[cDiagBlock2]++;
      }
      else{
      }
   }
}

static void SaveNvmErfsBlockOnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;
   uint8 ucTemp;

   ucTemp = 0;
   if(bGetErfsBlockWriteMeEE() == TRUE)  { ucTemp = 1; }

   if(ucTemp == 1){
	   ucWriteErrorState = Rte_Call_CpNvmRdciErfsBlock_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciErfsBlock_NVBlock_MirrorBlock(self));
    aucNvmSaveAttempts[cErfsBlock]++;

      if(ucWriteErrorState == RTE_E_OK){
      ClearErfsBlockWriteMeEE();
      }
      else{
      }
   }
}

static void SaveNvmErfsTsaBlockOnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;
   uint8 ucTemp;

   ucTemp = 0;
   if(bGetErfsTsaBlockWriteMeEE() == TRUE)  { ucTemp = 1; }

   if(ucTemp == 1){
     ucWriteErrorState = Rte_Call_CpNvmRdciErfsTsaBlock_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearErfsTsaBlockWriteMeEE();
      aucNvmSaveAttempts[cErfsTsaBlock]++;
      }
      else{
      }
   }
}

static void SaveNvmRidQrBlock1OnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetRidQrBlock1UpdateFlagEE() == 1){
     ucWriteErrorState = Rte_Call_CpNvmRdciRidQrBlock1_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciRidQrBlock1_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearRidQrBlock1UpdateFlagEE();
      aucNvmSaveAttempts[cRidQrBlock1]++;
      }
      else{
      }
   }
}

static void SaveNvmRidQrBlock2OnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetRidQrBlock2UpdateFlagEE() == 1){
     ucWriteErrorState = Rte_Call_CpNvmRdciRidQrBlock2_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciRidQrBlock2_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearRidQrBlock2UpdateFlagEE();
      aucNvmSaveAttempts[cRidQrBlock2]++;
      }
      else{
      }
   }
}

static void SaveNvmZoHistoryBlockOnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetZoHistoryBlockUpdateFlagEE() == TRUE){
     ucWriteErrorState = Rte_Call_CpNvmRdciZoHistoryBlock_WriteBlock(self, (uint8*) Rte_Pim_NvmRdciZoHistoryBlock_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearZoHistoryBlockUpdateFlagEE();
      aucNvmSaveAttempts[cHistoBlock]++;
      }
      else{
      }
   }
}

static void SaveNvmWarnstatusBlockOnEventSWC(Rte_Instance self){
   Std_ReturnType ucWriteErrorState = RTE_E_OK;

   if(bGetWarnStatusBlockUpdateFlagEE() == TRUE){
     ucWriteErrorState = Rte_Call_CpNvmRdciWarnStatusBlock_WriteBlock(self, (uint8*) (void*) Rte_Pim_NvmRdciWarnStatusBlock_NVBlock_MirrorBlock(self));
      if(ucWriteErrorState == RTE_E_OK){
      ClearWarnStatusBlockUpdateFlagEE();
      aucNvmSaveAttempts[cWarnstatusBlock]++;
      }
      else{
      IncreaseWriteErrorCounterForNvmWarnstatusBlock();
      }
   }
}

static void UpdateFbd4ControlDataSWC(Rte_Instance self, uint8 ucActivateFilters, uint8 ucUpdateRe){
  Rdci_CTR_SUPP_ID_1_Type CtrSuppId;
  Rdci_CTR_TYR_ID_1_Type  CtrTyrId;

   if(bGetCRdciTyrIdFiltGwCD() == TRUE){
      if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE){
      CtrSuppId = 0;
      CtrTyrId = 0;
      if(ucUpdateRe >= cUpdateRe0){
        GetDataFBD(cRadPosVL, (uint32*) &CtrTyrId, &CtrSuppId);
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CNTR_FBD_TPMS_1_ID2(self, cFbdSwitchCodeId1);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_FIL_ACTV_1(self, ucActivateFilters & 0x01);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_SUPP_ID_1(self, CtrSuppId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_1_CTR_TYR_ID_1(self, CtrTyrId);

      CtrSuppId = 0;
      CtrTyrId = 0;
      if(ucUpdateRe >= cUpdateRe01){
        GetDataFBD(cRadPosVR, (uint32*) &CtrTyrId, &CtrSuppId);
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CNTR_FBD_TPMS_2_ID2(self, cFbdSwitchCodeId2);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_FIL_ACTV_2(self, (ucActivateFilters & 0x02) >> 1);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_SUPP_ID_2(self, CtrSuppId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_2_CTR_TYR_ID_2(self, CtrTyrId);

      CtrSuppId = 0;
      CtrTyrId = 0;
      if(ucUpdateRe >= cUpdateRe012){
        GetDataFBD(cRadPosHR, (uint32*) &CtrTyrId, &CtrSuppId);
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CNTR_FBD_TPMS_3_ID2(self, cFbdSwitchCodeId3);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_FIL_ACTV_3(self,(ucActivateFilters & 0x04) >> 2);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_SUPP_ID_3(self, CtrSuppId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_3_CTR_TYR_ID_3(self, CtrTyrId);

      CtrSuppId = 0;
      CtrTyrId = 0;
      if(ucUpdateRe >= cUpdateRe0123){
        GetDataFBD(cRadPosHL, (uint32*) &CtrTyrId, &CtrSuppId);
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CNTR_FBD_TPMS_4_ID2(self, cFbdSwitchCodeId4);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_FIL_ACTV_4(self, (ucActivateFilters & 0x08) >> 3);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_SUPP_ID_4(self, CtrSuppId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_CNTR_FBD_TPMS_4_CTR_TYR_ID_4(self, CtrTyrId);
      }
   }
}

static void UpdateFbd4ParkingMonitorSWC(Rte_Instance self, uint8 ucPmControl, uint8 ucDataRequest){
   if(bGetCRdciTyrIdFiltGwCD() == TRUE){
      if(bGetBitBetriebszustandBZ(cEIGENRAD) == TRUE){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_PM_ID2(self, cFbdSwitchCodeParkMon);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_ACTVN_PM(self, ucPmControl);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_PM_RQ_PM_DT(self, ucDataRequest);
      }
   }
}

static void SendDebugMessageSWC(Rte_Instance self){
   uint8 ucDebugMessageData[DEBUG_MESSAGE_SIZE];

#ifdef WIN32

   static FILE* fStream;
   static const char filename[] = "debug_msg_telegram_log.csv";
   uint8 i, ucLoop;
   uint8 ucBcdChar[4];
   static boolean bFirst = TRUE;

   if(bFirst == TRUE){
      remove("debug_msg_telegram_log.csv");
    bFirst = FALSE;
   }

#endif

  GetDebugMessageContentDBG(self, ucDebugMessageData);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0(self, ucDebugMessageData[0]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1(self, ucDebugMessageData[1]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2(self, ucDebugMessageData[2]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3(self, ucDebugMessageData[3]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4(self, ucDebugMessageData[4]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5(self, ucDebugMessageData[5]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6(self, ucDebugMessageData[6]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7(self, ucDebugMessageData[7]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8(self, ucDebugMessageData[8]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9(self, ucDebugMessageData[9]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10(self, ucDebugMessageData[10]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11(self, ucDebugMessageData[11]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12(self, ucDebugMessageData[12]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13(self, ucDebugMessageData[13]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14(self, ucDebugMessageData[14]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15(self, ucDebugMessageData[15]);

#if(DEBUG_MESSAGE_SIZE == 32)
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16(self, ucDebugMessageData[16]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17(self, ucDebugMessageData[17]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18(self, ucDebugMessageData[18]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19(self, ucDebugMessageData[19]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20(self, ucDebugMessageData[20]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21(self, ucDebugMessageData[21]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22(self, ucDebugMessageData[22]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23(self, ucDebugMessageData[23]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24(self, ucDebugMessageData[24]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25(self, ucDebugMessageData[25]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26(self, ucDebugMessageData[26]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27(self, ucDebugMessageData[27]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28(self, ucDebugMessageData[28]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29(self, ucDebugMessageData[29]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30(self, ucDebugMessageData[30]);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31(self, ucDebugMessageData[31]);

#ifdef WIN32

   switch(ucDebugMessageData[0]){
      case 0:
      case 18:
      case 1:
      case 19:

      if(fopen_s(&fStream, filename, "a") == 0){
      for(i=0; i<32; i++){
        for(ucLoop = 3; ucLoop > 0; ucLoop--){
          ucBcdChar[ucLoop - 1] = (ucDebugMessageData[i] % 10) + 0x30;
          ucDebugMessageData[i] /= 10;
        }
        ucBcdChar[3] = ';';
        fwrite( (uint8*) &ucBcdChar, sizeof(uint8), 4, fStream);
      }
      fclose( fStream);
      {
        fopen_s(&fStream, filename, "ab");
        ucDebugMessageData[0] = 13;
        ucDebugMessageData[1] = 10;
        fwrite( (uint8*) &ucDebugMessageData, sizeof(uint8), 2, fStream);
        fclose( fStream);
      }

      }
      break;

      default:
      break;
   }

#endif
#endif
}

static void SendTPMSInternalLastValuesSWC(Rte_Instance self){
   uint8   ucLoop;

   uint32  ulSensorNoId;
   uint8   ucWheelPos;
   uint16  ushPress;
   sint8   scTemp;
   uint8   ucDummy;
   sint8   scDummy;
   uint16  ushDummy;
   uint8   ucPwarm;
   uint16  ushPwarm;
   uint8   ucYieldRate;
   uint8   ucRssi;
   uint8   ucBattLevel;

   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      ulSensorNoId = ulGetIDOfColWAL(ucLoop);
      if(ulSensorNoId == 0){
      ulSensorNoId = TpmsSensorSerialNo_Signal_unbefuellt;
      ucWheelPos = TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar;
      ushPress = TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar;
      scTemp = TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar;
      ushPwarm = TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar;
      ucYieldRate = TpmsSensorReceptionYield_Funktionsschnittstelle_ist_nichtGK538O;
      ucRssi = TpmsSensorReceptionRssi_Funktionsschnittstelle_ist_nicht_OD2HBC;
      ucBattLevel = TpmsSensorBatteryStatus_Funktionsschnittstelle_ist_nicht_4JIGN3;
      }
      else{
      ucWheelPos = ucGetWPOfColWAL(ucLoop);
      if(ucWheelPos < cRadPosUndef){
        ucWheelPos |= ((GetQrIxOfWheelPos(self, ucWheelPos) << 4) & 0xf0u);
      }
      else{
        ucWheelPos = 5;
      }

      ushPress = (uint16)ucGetRePressureRelDM(ucLoop);
      if(ushPress == (uint16)cInvalidREpressure){
        ushPress = 0xD8F1u;
      }
      else{
        ushPress *= 25;
      }

      scTemp = scGetReTemperatureCentDM(ucLoop);
      if(scTemp == cInvalidREtemperature){
        scTemp = -1;
      }
      else{
        scTemp += 50;
      }

      if(ucGetPTSollUSWIF(self, &ucDummy, &scDummy, &ucPwarm, &scDummy, &ushDummy, &ucDummy, ucLoop) == cRetError){
        ushPwarm = 0xD8F1u;
      }
      else{
          if(ucPwarm == cInvalidREpressure){
          ushPwarm = 0xD8F1u;
        }
        else{
          ushPwarm = ucPwarm * 25;
        }
      }

      ucYieldRate = ucGetYieldRateWUM(ucLoop);

      ucRssi = GETucLastSNRFromNvmMirrorEE(self, ucLoop);

      ucBattLevel = GETucLastBatteryStateFromNvmMirrorEE(self, ucLoop);
      if(ucBattLevel == 0xff){
        ucBattLevel = 0x9Du;
      }
      }

      switch(ucLoop){
      case (uint8)0:
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId1(self, ulSensorNoId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId1(self, ucWheelPos);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId1(self, ushPress);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId1(self, (uint8)scTemp);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId1(self, ushPwarm);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId1(self, ucYieldRate);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId1(self, ucRssi);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId1(self, ucBattLevel);
            break;

      case (uint8)1:
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId2(self, ulSensorNoId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId2(self, ucWheelPos);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId2(self, ushPress);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId2(self, (uint8)scTemp);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId2(self, ushPwarm);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId2(self, ucYieldRate);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId2(self, ucRssi);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId2(self, ucBattLevel);
            break;

      case (uint8)2:
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId3(self, ulSensorNoId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId3(self, ucWheelPos);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId3(self, ushPress);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId3(self, (uint8)scTemp);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId3(self, ushPwarm);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId3(self, ucYieldRate);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId3(self, ucRssi);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId3(self, ucBattLevel);
            break;

      default:
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastSensorSerNoId4(self, ulSensorNoId);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPositionId4(self, ucWheelPos);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastPressureMbarId4(self, ushPress);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTemperatureDegCId4(self, (uint8)scTemp);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastTargetPressureMbarId4(self, ushPwarm);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionYieldId4(self, ucYieldRate);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastReceptionRssiId4(self, ucRssi);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TPMSInternalLastValues_TpmsInternalLastBatteryStatusId4(self, ucBattLevel);
            break;
      }
   }
}

static void SendTPMSCalibrationDataSWC(Rte_Instance self){
   uint8   ucLoop;

   uint8   ucNoOfCalibrations;
   uint64  u64CalibrationDateTime;
   uint32  ulCalibrationMileage;

   ucNoOfCalibrations = GetHsKalibrierereignis_1_CounterEE(self);
   if(ucNoOfCalibrations == 0xffu){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self, TpmsCalibrationPlausibility_Signal_unbefuellt);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self, TpmsCalibrationType_Signal_unbefuellt);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self, TpmsCalibrationDateTime_Signal_unbefuellt);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self, TpmsCalibrationDateTime_Signal_unbefuellt);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self, TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self, TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self, TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self, TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self, TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self, TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self, TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self, TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self, TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self, TireTemperature_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self, TpmsPressureMbar_Funktionsschnittstelle_ist_nicht_verfuegbar);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self, TpmsCalibrationNo_Signal_unbefuellt);
   }
   else{
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPlausibility(self, GetHsKalibrierereignis_1_EE(self, 0));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationCalibrationType(self, GetHsKalibrierereignis_1_EE(self, 1));

      u64CalibrationDateTime = 0;
      for(ucLoop = 0; ucLoop < sizeof(Rdci_TpmsCalibrationDate_Type); ucLoop++){
      u64CalibrationDateTime += ((Rdci_TpmsCalibrationDate_Type)GetHsKalibrierereignis_1_EE(self, (ucLoop + 2)) << (ucLoop * 8));
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationDate(self, u64CalibrationDateTime);

      u64CalibrationDateTime = 0;
      for(ucLoop = 0; ucLoop < sizeof(Rdci_TpmsCalibrationTime_Type); ucLoop++){
      u64CalibrationDateTime += ((Rdci_TpmsCalibrationTime_Type)GetHsKalibrierereignis_1_EE(self, (ucLoop + 10)) << (ucLoop * 8));
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTime(self, u64CalibrationDateTime);

      ulCalibrationMileage = 0;
      for(ucLoop = 0; ucLoop < sizeof(Rdci_TpmsCalibrationMileage_Type); ucLoop++){
      ulCalibrationMileage += ((Rdci_TpmsCalibrationMileage_Type)GetHsKalibrierereignis_1_EE(self, (ucLoop + 18)) << (((sizeof(Rdci_TpmsCalibrationMileage_Type) - ucLoop) - 1) * 8));
      }
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationMileage(self, ulCalibrationMileage);

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientTemperature(self, GetHsKalibrierereignis_1_EE(self, 22)+10);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationAmbientPressure(self, (((Rdci_TpmsCalibrationAmbientPressure_Type)GetHsKalibrierereignis_1_EE(self, 23) << 8) + (Rdci_TpmsCalibrationAmbientPressure_Type)GetHsKalibrierereignis_1_EE(self, 24)));

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId1(self, GetHsKalibrierereignis_1_EE(self, 25));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId1(self, (((Rdci_TpmsCalibrationActualTirePressureId1_Type)GetHsKalibrierereignis_1_EE(self, 26) << 8) + (Rdci_TpmsCalibrationActualTirePressureId1_Type)GetHsKalibrierereignis_1_EE(self, 27)));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId1(self, GetHsKalibrierereignis_1_EE(self, 28));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId1(self, (((Rdci_TpmsCalibrationTireTargetPressureId1_Type)GetHsKalibrierereignis_1_EE(self, 29) << 8) + (Rdci_TpmsCalibrationTireTargetPressureId1_Type)GetHsKalibrierereignis_1_EE(self, 30)));

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId2(self, GetHsKalibrierereignis_1_EE(self, 31));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId2(self, (((Rdci_TpmsCalibrationActualTirePressureId2_Type)GetHsKalibrierereignis_1_EE(self, 32) << 8) + (Rdci_TpmsCalibrationActualTirePressureId2_Type)GetHsKalibrierereignis_1_EE(self, 33)));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId2(self, GetHsKalibrierereignis_1_EE(self, 34));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId2(self, (((Rdci_TpmsCalibrationTireTargetPressureId2_Type)GetHsKalibrierereignis_1_EE(self, 35) << 8) + (Rdci_TpmsCalibrationTireTargetPressureId2_Type)GetHsKalibrierereignis_1_EE(self, 36)));

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId3(self, GetHsKalibrierereignis_1_EE(self, 37));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId3(self, (((Rdci_TpmsCalibrationActualTirePressureId3_Type)GetHsKalibrierereignis_1_EE(self, 38) << 8) + (Rdci_TpmsCalibrationActualTirePressureId3_Type)GetHsKalibrierereignis_1_EE(self, 39)));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId3(self, GetHsKalibrierereignis_1_EE(self, 40));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId3(self, (((Rdci_TpmsCalibrationTireTargetPressureId3_Type)GetHsKalibrierereignis_1_EE(self, 41) << 8) + (Rdci_TpmsCalibrationTireTargetPressureId3_Type)GetHsKalibrierereignis_1_EE(self, 42)));

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationPositionId4(self, GetHsKalibrierereignis_1_EE(self, 43));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTirePressureId4(self, (((Rdci_TpmsCalibrationActualTirePressureId4_Type)GetHsKalibrierereignis_1_EE(self, 44) << 8) + (Rdci_TpmsCalibrationActualTirePressureId4_Type)GetHsKalibrierereignis_1_EE(self, 45)));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationActualTireTemperatureId4(self, GetHsKalibrierereignis_1_EE(self, 46));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationTireTargetPressureId4(self, (((Rdci_TpmsCalibrationTireTargetPressureId4_Type)GetHsKalibrierereignis_1_EE(self, 47) << 8) + (Rdci_TpmsCalibrationTireTargetPressureId4_Type)GetHsKalibrierereignis_1_EE(self, 48)));

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsCalibrationData_TpmsCalibrationNoOfCalibrations(self, ucNoOfCalibrations);
   }
}

static void SendTPMSErfsActualTireDataSWC(Rte_Instance self){
   uint8   ucCurIndex;
   uint8   ucSuIndex;
   uint8   ucWiIndex;

   ucCurIndex = GETSelectedTyreIndexEE(self);

   if(ucCurIndex < GetLengthOfTyreListDM()){
      if(GetSaisonRaw(ucCurIndex) == CSEASON_SUMMER){
      ucSuIndex = ucCurIndex;
      ucWiIndex = GETSelectedWiTyreIndexEE(self);
      }
      else{
      ucWiIndex = ucCurIndex;
      ucSuIndex = GETSelectedSuTyreIndexEE(self);
      }
   }
   else{
      ucSuIndex = GETSelectedSuTyreIndexEE(self);
      ucWiIndex = GETSelectedWiTyreIndexEE(self);
   }

   if(ucSuIndex < TYRE_LIST_MAX_ELEMENTS){
      if(ucSuIndex == ucCurIndex){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, (Rdci_TpmsErfsActTireDimSummerMounted_Type)TRUE);
      }
      else{
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, (Rdci_TpmsErfsActTireDimSummerMounted_Type)FALSE);
      }

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self, (Rdci_TpmsErfsActTireDimSummerPosition_Type)ucSuIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self, (Rdci_TpmsErfsActTireDimSummerWidth_Type)GetReifenbreiteRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self, (Rdci_TpmsErfsActTireDimSummerCrossSection_Type)GetQuerschnittRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self, (Rdci_TpmsErfsActTireDimSummerDiameter_Type)GetDurchmesserRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self, (Rdci_TpmsErfsActTireDimSummerLoadIndex_Type)GetTragfaehigkeitRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self, (Rdci_TpmsErfsActTireDimSummerSpeedIndex_Type)GetGeschwIndexRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self, (Rdci_TpmsErfsActTireDimSummerSeason_Type)GetSaisonRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self, (Rdci_TpmsErfsActTireDimSummerCarcass_Type)GetKarkasseRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self, (Rdci_TpmsErfsActTireDimSummerRunflat_Type)GetReifentypRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self, (Rdci_TpmsErfsActTireDimSummerMountedInFactory_Type)GetWerksauslieferungRaw(ucSuIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup0_Type)((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucSuIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup0_Type)((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucSuIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup2_Type)((GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucSuIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup2_Type)((GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucSuIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureFaGroup1_Type)((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucSuIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self, (Rdci_TpmsErfsActTireDimSummerTargetPressureRaGroup1_Type)((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucSuIndex) - 80) / 4));
   }
   else{
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMounted(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerPosition(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerWidth(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCrossSection(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerDiameter(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerLoadIndex(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSpeedIndex(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerSeason(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerCarcass(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerRunflat(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerMountedInFactory(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup0(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup0(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup2(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup2(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureFaGroup1(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimSummerTargetPressureRaGroup1(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
   }

   if(ucWiIndex < TYRE_LIST_MAX_ELEMENTS){
      if(ucWiIndex == ucCurIndex){
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, (Rdci_TpmsErfsActTireDimWinterMounted_Type)TRUE);
      }
      else{
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, (Rdci_TpmsErfsActTireDimWinterMounted_Type)FALSE);
      }

      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self, (Rdci_TpmsErfsActTireDimWinterPosition_Type)ucWiIndex);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self, (Rdci_TpmsErfsActTireDimWinterWidth_Type)GetReifenbreiteRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self, (Rdci_TpmsErfsActTireDimWinterCrossSection_Type)GetQuerschnittRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self, (Rdci_TpmsErfsActTireDimWinterDiameter_Type)GetDurchmesserRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self, (Rdci_TpmsErfsActTireDimWinterLoadIndex_Type)GetTragfaehigkeitRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self, (Rdci_TpmsErfsActTireDimWinterSpeedIndex_Type)GetGeschwIndexRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self, (Rdci_TpmsErfsActTireDimWinterSeason_Type)GetSaisonRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self, (Rdci_TpmsErfsActTireDimWinterCarcass_Type)GetKarkasseRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self, (Rdci_TpmsErfsActTireDimWinterRunflat_Type)GetReifentypRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self, (Rdci_TpmsErfsActTireDimWinterMountedInFactory_Type)GetWerksauslieferungRaw(ucWiIndex));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup0_Type)((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucWiIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup0_Type)((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucWiIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup2_Type)((GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucWiIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup2_Type)((GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucWiIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureFaGroup1_Type)((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucWiIndex) - 80) / 4));
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self, (Rdci_TpmsErfsActTireDimWinterTargetPressureRaGroup1_Type)((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucWiIndex) - 80) / 4));
   }
   else{
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMounted(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterPosition(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterWidth(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCrossSection(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterDiameter(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterLoadIndex(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSpeedIndex(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterSeason(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterCarcass(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterRunflat(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterMountedInFactory(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup0(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup0(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup2(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup2(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureFaGroup1(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
      Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TpmsErfsActualTireData_TpmsErfsActTireDimWinterTargetPressureRaGroup1(self, TpmsTireMountState_Funktionsschnittstelle_ist_nicht_verfuegbar);
   }
}

static void SendTPMSTireMileageDataSWC(Rte_Instance self){
   uint8   ucLoop;

   uint8   ucQrIx;
   uint32  ulCurMileKm, ulSavMileKm;

   uint8   ucTireMileagePosition;
   uint8   ucTireMileageId;
   uint64  u64TireMileageLastAssemblyDate, u64TireMileageLastDisassemblyDate;
   uint32  ulTireMileageLastAssemblyVehicleMileage, ulTireMileageLastDisassemblyVehicleMileage;

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self, (Rdci_TireMileagePositionId1_Type)TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self, (Rdci_TireMileageInventoryNoId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self, (Rdci_TireMileageLastAssemblyDateId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self, (Rdci_TireMileageLastAssemblyVehicleMileageId1_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self, (Rdci_TireMileageLastDisassemblyDateId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self, (Rdci_TireMileageTotalTireMileageOnVehicleId1_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self, (Rdci_TireMileagePositionId2_Type)TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self, (Rdci_TireMileageInventoryNoId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self, (Rdci_TireMileageLastAssemblyDateId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self, (Rdci_TireMileageLastAssemblyVehicleMileageId2_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self, (Rdci_TireMileageLastDisassemblyDateId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self, (Rdci_TireMileageTotalTireMileageOnVehicleId2_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self, (Rdci_TireMileagePositionId3_Type)TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self, (Rdci_TireMileageInventoryNoId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self, (Rdci_TireMileageLastAssemblyDateId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self, (Rdci_TireMileageLastAssemblyVehicleMileageId3_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self, (Rdci_TireMileageLastDisassemblyDateId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self, (Rdci_TireMileageTotalTireMileageOnVehicleId3_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self, (Rdci_TireMileagePositionId4_Type)TpmsSensorPosition_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self, (Rdci_TireMileageInventoryNoId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self, (Rdci_TireMileageLastAssemblyDateId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self, (Rdci_TireMileageLastAssemblyVehicleMileageId4_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self, (Rdci_TireMileageLastDisassemblyDateId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self, (Rdci_TireMileageTotalTireMileageOnVehicleId4_Type)TpmsMileage_Funktionsschnittstelle_ist_nicht_verfuegbar);

   ucTireMileageId = 0;
   for(ucQrIx = 0; ucQrIx < cMaxQRCodeSets; ucQrIx++){
      ulCurMileKm = GETulMileKmEE(self);

      if((GETTyreMountedFlagEE(self, ucQrIx) & 0x0F) == cTyreMountedFlag){
      ucTireMileagePosition = (GETTyreMountedFlagEE(self, ucQrIx) & (uint8)0xF0);
      for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
          if((ucTireMileagePosition & (uint8)(0x10 << ucLoop)) != 0x00){
          ucTireMileagePosition = ucLoop;
        }
      }

      u64TireMileageLastAssemblyDate = 0;
      for(ucLoop = 0; ucLoop < cDateSize; ucLoop++){
        u64TireMileageLastAssemblyDate += (uint64)((uint64)GETTyreRuntimeDataEE(self, ucQrIx, (cMountedDateIx + ucLoop)) << (((cDateSize - ucLoop) - 1) * 8));
      }

      ulTireMileageLastAssemblyVehicleMileage = 0;
      for(ucLoop = 0; ucLoop < cKmSize; ucLoop++){
        ulTireMileageLastAssemblyVehicleMileage += (uint32)((uint32)GETTyreRuntimeDataEE(self, ucQrIx, (cMountedKmIx + ucLoop)) << (((cKmSize - ucLoop) - 1) * 8));
      }

      u64TireMileageLastDisassemblyDate = 0;
      for(ucLoop = 0; ucLoop < cDateSize; ucLoop++){
        u64TireMileageLastDisassemblyDate += (uint64)((uint64)GETTyreRuntimeDataEE(self, ucQrIx, (cUnmountedDateIx + ucLoop)) << (((cDateSize - ucLoop) - 1) * 8));
      }

      ulTireMileageLastDisassemblyVehicleMileage = 0;
      for(ucLoop = 0; ucLoop < cKmSize; ucLoop++){
        ulTireMileageLastDisassemblyVehicleMileage += (uint32)((uint32)GETTyreRuntimeDataEE(self, ucQrIx, (cUnmountedKmIx + ucLoop)) << (((cKmSize - ucLoop) - 1) * 8));
      }

      ulSavMileKm = 0;
      for(ucLoop = 0; ucLoop < cKmSize; ucLoop++){
        ulSavMileKm += ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, ucQrIx, (cMountedKmIx + ucLoop)) << (((cKmSize - ucLoop) - 1) * 8));
      }

      if(ulCurMileKm >= ulSavMileKm){
        ulCurMileKm = (ulCurMileKm - ulSavMileKm);

        ulSavMileKm = 0;
        for(ucLoop = 0; ucLoop < cKmSize; ucLoop++){
          ulSavMileKm += ((Rdci_MILE_KM_Type)GETTyreRuntimeDataEE(self, ucQrIx, (cRuntimeKmIx + ucLoop)) << (((cKmSize - ucLoop) - 1) * 8));
        }

        ulSavMileKm += ulCurMileKm;
      }
      else{
        ulSavMileKm = TpmsMileage_Funktion_meldet_Fehler;
      }

      switch(ucTireMileageId){
      case (uint8)0:
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId1(self, (Rdci_TireMileagePositionId1_Type)ucTireMileagePosition);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId1(self, (Rdci_TireMileageInventoryNoId1_Type)ucQrIx);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId1(self, (Rdci_TireMileageLastAssemblyDateId1_Type)u64TireMileageLastAssemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId1(self, (Rdci_TireMileageLastAssemblyVehicleMileageId1_Type)ulTireMileageLastAssemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId1(self, (Rdci_TireMileageLastDisassemblyDateId1_Type)u64TireMileageLastDisassemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId1(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId1_Type)ulTireMileageLastDisassemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId1(self, (Rdci_TireMileageTotalTireMileageOnVehicleId1_Type)ulSavMileKm);
        break;

      case (uint8)1:
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileagePositionId2(self, (Rdci_TireMileagePositionId2_Type)ucTireMileagePosition);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageInventoryNoId2(self, (Rdci_TireMileageInventoryNoId2_Type)ucQrIx);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyDateId2(self, (Rdci_TireMileageLastAssemblyDateId2_Type)u64TireMileageLastAssemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastAssemblyVehicleMileageId2(self, (Rdci_TireMileageLastAssemblyVehicleMileageId2_Type)ulTireMileageLastAssemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyDateId2(self, (Rdci_TireMileageLastDisassemblyDateId2_Type)u64TireMileageLastDisassemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageLastDisassemblyVehicleMileageId2(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId2_Type)ulTireMileageLastDisassemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart1_TireMileageTotalTireMileageOnVehicleId2(self, (Rdci_TireMileageTotalTireMileageOnVehicleId2_Type)ulSavMileKm);
        break;

      case (uint8)2:
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId3(self, (Rdci_TireMileagePositionId3_Type)ucTireMileagePosition);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId3(self, (Rdci_TireMileageInventoryNoId3_Type)ucQrIx);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId3(self, (Rdci_TireMileageLastAssemblyDateId3_Type)u64TireMileageLastAssemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId3(self, (Rdci_TireMileageLastAssemblyVehicleMileageId3_Type)ulTireMileageLastAssemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId3(self, (Rdci_TireMileageLastDisassemblyDateId3_Type)u64TireMileageLastDisassemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId3(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId3_Type)ulTireMileageLastDisassemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId3(self, (Rdci_TireMileageTotalTireMileageOnVehicleId3_Type)ulSavMileKm);
        break;

         default:
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileagePositionId4(self, (Rdci_TireMileagePositionId4_Type)ucTireMileagePosition);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageInventoryNoId4(self, (Rdci_TireMileageInventoryNoId4_Type)ucQrIx);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyDateId4(self, (Rdci_TireMileageLastAssemblyDateId4_Type)u64TireMileageLastAssemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastAssemblyVehicleMileageId4(self, (Rdci_TireMileageLastAssemblyVehicleMileageId4_Type)ulTireMileageLastAssemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyDateId4(self, (Rdci_TireMileageLastDisassemblyDateId4_Type)u64TireMileageLastDisassemblyDate);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageLastDisassemblyVehicleMileageId4(self, (Rdci_TireMileageLastDisassemblyVehicleMileageId4_Type)ulTireMileageLastDisassemblyVehicleMileage);
        Rte_IWrite_RCyclicRDCiTask_PpFrPdu_TireMileageDataPart2_TireMileageTotalTireMileageOnVehicleId4(self, (Rdci_TireMileageTotalTireMileageOnVehicleId4_Type)ulSavMileKm);
        break;
      }

      ucTireMileageId++;
      }
   }
}

static void SendTPMSQrCodeDataSWC(Rte_Instance self){
   uint8   ucLoop;
   uint8   ucQrIx;

   uint8 ucQrCodeInventoryNo, ucQrCodeTireType, ucQrCodePosition, ucQrCodeMountingState;
   uint64 u64QrCodeRubberSerialNoPartA, u64QrCodeTireDimensions, u64QrCodeDotNo;
   uint32 ulQrCodeRubberSerialNoPartB;
   uint16 ushQrCodeDotProdDate;

   uint8 ucOffset, ucPrev, ucCur, ucQrDataCnt;

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId1(self, (Rdci_QrCodeDotNoId1_Type)TpmsQrCodeDotNo_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId2(self, (Rdci_QrCodeDotNoId2_Type)TpmsQrCodeDotNo_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self, (Rdci_QrCodeDotProdDateId1_Type)TpmsQrCodeDotProdDate_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self, (Rdci_QrCodeDotProdDateId2_Type)TpmsQrCodeDotProdDate_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self, (Rdci_QrCodeInventoryNoId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self, (Rdci_QrCodeInventoryNoId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self, (Rdci_QrCodeMountingStateId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self, (Rdci_QrCodeMountingStateId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId1(self, (Rdci_QrCodePositionId1_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId2(self, (Rdci_QrCodePositionId2_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self, (Rdci_QrCodeRubberSerialNoPartAId1_Type)TpmsQrCodeTireSerialNoPartA_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self, (Rdci_QrCodeRubberSerialNoPartAId2_Type)TpmsQrCodeTireSerialNoPartA_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self, (Rdci_QrCodeRubberSerialNoPartBId1_Type)TpmsQrCodeTireSerialNoPartB_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self, (Rdci_QrCodeRubberSerialNoPartBId2_Type)TpmsQrCodeTireSerialNoPartB_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self, (Rdci_QrCodeTireDimensionsId1_Type)TpmsQrCodeTireDim_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self, (Rdci_QrCodeTireDimensionsId2_Type)TpmsQrCodeTireDim_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self, (Rdci_QrCodeTireTypeId1_Type)TpmsQrCodeTireType_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self, (Rdci_QrCodeTireTypeId2_Type)TpmsQrCodeTireType_Signal_unbefuellt);

  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self, (Rdci_QrCodeDotNoId3_Type)TpmsQrCodeDotNo_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self, (Rdci_QrCodeDotNoId4_Type)TpmsQrCodeDotNo_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self, (Rdci_QrCodeDotProdDateId3_Type)TpmsQrCodeDotProdDate_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self, (Rdci_QrCodeDotProdDateId4_Type)TpmsQrCodeDotProdDate_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self, (Rdci_QrCodeInventoryNoId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self, (Rdci_QrCodeInventoryNoId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self, (Rdci_QrCodeMountingStateId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self, (Rdci_QrCodeMountingStateId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId3(self, (Rdci_QrCodePositionId3_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId4(self, (Rdci_QrCodePositionId4_Type)TpmsQrCodeInventoryNo_Funktionsschnittstelle_ist_nicht_veLCK47P);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self, (Rdci_QrCodeRubberSerialNoPartAId3_Type)TpmsQrCodeTireSerialNoPartA_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self, (Rdci_QrCodeRubberSerialNoPartAId4_Type)TpmsQrCodeTireSerialNoPartA_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self, (Rdci_QrCodeRubberSerialNoPartBId3_Type)TpmsQrCodeTireSerialNoPartB_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self, (Rdci_QrCodeRubberSerialNoPartBId4_Type)TpmsQrCodeTireSerialNoPartB_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self, (Rdci_QrCodeTireDimensionsId3_Type)TpmsQrCodeTireDim_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self, (Rdci_QrCodeTireDimensionsId4_Type)TpmsQrCodeTireDim_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self, (Rdci_QrCodeTireTypeId3_Type)TpmsQrCodeTireType_Signal_unbefuellt);
  Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self, (Rdci_QrCodeTireTypeId4_Type)TpmsQrCodeTireType_Signal_unbefuellt);

   ucQrDataCnt = 0;

   for(ucQrIx = 0; ucQrIx < cMaxQRCodeSets; ucQrIx++){
      if((GETTyreMountedFlagEE(self, ucQrIx) & 0x0F) == cTyreMountedFlag){
      ucQrCodeInventoryNo = (ucQrIx + 1);
      u64QrCodeRubberSerialNoPartA = (uint64)0x00;
      ulQrCodeRubberSerialNoPartB = (uint32)0x00;
      for(ucLoop = 0; ucLoop<(cTyreOEMSize - 8); ucLoop++){
        ucOffset = (uint8)(2 - (ucLoop / 4));
        ucOffset += ucLoop;
        ucPrev = GETTyreOEMQrCodeDataEE(self, ucQrIx, (ucOffset - 1));
        ucCur = GETTyreOEMQrCodeDataEE(self, ucQrIx, (ucOffset));
        ulQrCodeRubberSerialNoPartB += (uint32)((uint32)GetOemIdDS(ucPrev, ucCur, ucLoop) << ((((cTyreOEMSize - 8) - ucLoop) - 1) * 8));
      }
      for(ucLoop = 3; ucLoop<cTyreOEMSize; ucLoop++){
        ucOffset = (uint8)(2 - (ucLoop / 4));
        ucOffset += ucLoop;
        ucPrev = GETTyreOEMQrCodeDataEE(self, ucQrIx, (ucOffset - 1));
        ucCur = GETTyreOEMQrCodeDataEE(self, ucQrIx, (ucOffset));
        u64QrCodeRubberSerialNoPartA += (uint64)((uint64)GetOemIdDS(ucPrev, ucCur, ucLoop) << (((cTyreOEMSize - ucLoop) - 1) * 8));
      }
      u64QrCodeDotNo = (uint64)((uint64)(GETTyreOEMQrCodeDataEE(self, ucQrIx, 1) & 0x0F) << 2);
      u64QrCodeDotNo |= (uint64)((uint64)(GETTyreOEMQrCodeDataEE(self, ucQrIx, 2) & 0xC0) >> 6);
      u64QrCodeDotNo <<= 48;
      for(ucLoop = 1; ucLoop<(cTyreDOTSize - 1); ucLoop++){
        u64QrCodeDotNo += (uint64)((uint64)GETTyreDOTQrCodeDataEE(self, ucQrIx, ucLoop) << ((((cTyreDOTSize - 1) - ucLoop) -1) * 8));
      }
      ushQrCodeDotProdDate = (uint16)0x00;
      for(ucLoop = 6; ucLoop < cTyreDOTSize; ucLoop++){
        ushQrCodeDotProdDate += (uint16)((uint16)GETTyreDOTQrCodeDataEE(self, ucQrIx, ucLoop) << (((cTyreDOTSize - ucLoop) - 1) * 8));
      }
      u64QrCodeTireDimensions = (uint64)0x00;
      for(ucLoop = 0; ucLoop<cTyreDimSize; ucLoop++){
        u64QrCodeTireDimensions += (uint64)((uint64)GETTyreDimQrCodeDataEE(self, ucQrIx, ucLoop) << (((cTyreDimSize - ucLoop) - 1) * 8));
      }
      ucQrCodeTireType = ((GETTyreOEMQrCodeDataEE(self, ucQrIx, 1) & 0x10) << 2);
      ucQrCodeTireType |= (GETTyreOEMQrCodeDataEE(self, ucQrIx, 1) & 0x20);
      ucQrCodeTireType |= ((GETTyreOEMQrCodeDataEE(self, ucQrIx, 1) & 0x40) >> 2);
      ucQrCodeTireType |= (GETTyreOEMQrCodeDataEE(self, ucQrIx, 10) & 0x08);
      ucQrCodeTireType |= ((GETTyreOEMQrCodeDataEE(self, ucQrIx, 0) & 0x03) << 1);
      ucQrCodeTireType |= (uint8)((GETTyreOEMQrCodeDataEE(self, ucQrIx, 1) & 0x80) >> 7);
      ucQrCodePosition = (GETTyreMountedFlagEE(self, ucQrIx) & (uint8)0xF0);
      for(ucLoop = 0; ucLoop<cAnzRad; ucLoop++){
          if((ucQrCodePosition & (uint8)(0x10 << ucLoop)) != 0x00){
          ucQrCodePosition = ucLoop;
        }
      }
      ucQrCodeMountingState = 0x01;
      ucQrCodeMountingState |= (uint8)((GETTyreOEMQrCodeDataEE(self, ucQrIx, 0) & 0xFC) >> 1);
      switch(ucQrDataCnt){
        case (uint8)0:{
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId1(self, (Rdci_QrCodeDotNoId1_Type)u64QrCodeDotNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId1(self, (Rdci_QrCodeDotProdDateId1_Type)ushQrCodeDotProdDate);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId1(self, (Rdci_QrCodeInventoryNoId1_Type)ucQrCodeInventoryNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId1(self, (Rdci_QrCodeMountingStateId1_Type)ucQrCodeMountingState);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId1(self, (Rdci_QrCodePositionId1_Type)ucQrCodePosition);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId1(self, (Rdci_QrCodeRubberSerialNoPartAId1_Type)u64QrCodeRubberSerialNoPartA);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId1(self, (Rdci_QrCodeRubberSerialNoPartBId1_Type)ulQrCodeRubberSerialNoPartB);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId1(self, (Rdci_QrCodeTireDimensionsId1_Type)u64QrCodeTireDimensions);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId1(self, (Rdci_QrCodeTireTypeId1_Type)ucQrCodeTireType);
            ucQrDataCnt++;
            break;
        }

        case (uint8)1:{
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotNoId2(self, (Rdci_QrCodeDotNoId1_Type)u64QrCodeDotNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeDotProdDateId2(self, (Rdci_QrCodeDotProdDateId1_Type)ushQrCodeDotProdDate);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeInventoryNoId2(self, (Rdci_QrCodeInventoryNoId1_Type)ucQrCodeInventoryNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeMountingStateId2(self, (Rdci_QrCodeMountingStateId1_Type)ucQrCodeMountingState);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodePositionId2(self, (Rdci_QrCodePositionId1_Type)ucQrCodePosition);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartAId2(self, (Rdci_QrCodeRubberSerialNoPartAId1_Type)u64QrCodeRubberSerialNoPartA);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeRubberSerialNoPartBId2(self, (Rdci_QrCodeRubberSerialNoPartBId1_Type)ulQrCodeRubberSerialNoPartB);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireDimensionsId2(self, (Rdci_QrCodeTireDimensionsId1_Type)u64QrCodeTireDimensions);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData_QrCodeTireTypeId2(self, (Rdci_QrCodeTireTypeId1_Type)ucQrCodeTireType);
            ucQrDataCnt++;
            break;
        }

        case (uint8)2:{
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId3(self, (Rdci_QrCodeDotNoId1_Type)u64QrCodeDotNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId3(self, (Rdci_QrCodeDotProdDateId1_Type)ushQrCodeDotProdDate);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId3(self, (Rdci_QrCodeInventoryNoId1_Type)ucQrCodeInventoryNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId3(self, (Rdci_QrCodeMountingStateId1_Type)ucQrCodeMountingState);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId3(self, (Rdci_QrCodePositionId1_Type)ucQrCodePosition);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId3(self, (Rdci_QrCodeRubberSerialNoPartAId1_Type)u64QrCodeRubberSerialNoPartA);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId3(self, (Rdci_QrCodeRubberSerialNoPartBId1_Type)ulQrCodeRubberSerialNoPartB);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId3(self, (Rdci_QrCodeTireDimensionsId1_Type)u64QrCodeTireDimensions);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId3(self, (Rdci_QrCodeTireTypeId1_Type)ucQrCodeTireType);
            ucQrDataCnt++;
            break;
        }

        default:{
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotNoId4(self, (Rdci_QrCodeDotNoId1_Type)u64QrCodeDotNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeDotProdDateId4(self, (Rdci_QrCodeDotProdDateId1_Type)ushQrCodeDotProdDate);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeInventoryNoId4(self, (Rdci_QrCodeInventoryNoId1_Type)ucQrCodeInventoryNo);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeMountingStateId4(self, (Rdci_QrCodeMountingStateId1_Type)ucQrCodeMountingState);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodePositionId4(self, (Rdci_QrCodePositionId1_Type)ucQrCodePosition);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartAId4(self, (Rdci_QrCodeRubberSerialNoPartAId1_Type)u64QrCodeRubberSerialNoPartA);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeRubberSerialNoPartBId4(self, (Rdci_QrCodeRubberSerialNoPartBId1_Type)ulQrCodeRubberSerialNoPartB);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireDimensionsId4(self, (Rdci_QrCodeTireDimensionsId1_Type)u64QrCodeTireDimensions);
            Rte_IWrite_RCyclicRDCiTask_PpFrPdu_QrCodeData2_QrCodeTireTypeId4(self, (Rdci_QrCodeTireTypeId1_Type)ucQrCodeTireType);
            break;
        }
      }
      }
   }
}

void GetNvmWriteAttemptCounters(uint8* pChar){
   uint8 i;
   for(i=0; i<cAttemptCounterSize; i++){
      pChar[i] = aucNvmSaveAttempts[i];
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

