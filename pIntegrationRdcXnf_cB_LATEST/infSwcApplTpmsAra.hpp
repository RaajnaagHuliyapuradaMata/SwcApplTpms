#pragma once
/******************************************************************************/
/* File   : infSwcApplTpmsAra.hpp                                             */
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
#include "CfgSwcApplTpms.hpp"

#include "Types_SwcServiceDem.hpp" //Move to SwcApplDem.cpp

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 Type_infSwcApplTpmsAra_stCcm;
typedef uint8 Type_infSwcApplTpmsAra_stPressure;
typedef uint8 Type_infSwcApplTpmsAra_stTemperature;
typedef uint8 Type_infSwcApplTpmsAra_stStatusTyre;
typedef uint8 Type_infSwcApplTpmsAra_stDataControlFbd;
typedef uint8 Type_infSwcApplTpmsAra_stDataMileageTyre;
typedef uint8 Type_infSwcApplTpmsAra_stDataTyreCodeQR;
typedef uint8 Type_infSwcApplTpmsAra_stDataTyreInternalLast;
typedef uint8 Type_infSwcApplTpmsAra_stTyreParkingSupervision;
typedef uint8 Type_infSwcApplTpmsAra_stStatusWheelChange;
typedef uint8 Type_infSwcApplTpmsAra_stMonitoringParking;
typedef uint8 Type_infSwcApplTpmsAra_stDataCalibration;
typedef uint8 Type_infSwcApplTpmsAra_stDataTyreErfsActual;
typedef uint8 Type_infSwcApplTpmsAra_stTyreAxleErfsHmi;
typedef uint8 Type_infSwcApplTpmsAra_stStatusErfs;
typedef uint8 Type_infSwcApplTpmsAra_stIndicatorLevelPressure;
typedef uint8 Type_infSwcApplTpmsAra_stNotificationErfsHmi;
typedef uint8 Type_infSwcApplTpmsAra_stStatusEventDtc;

typedef struct{
   Type_infSwcApplTpmsAra_stCcm                    stCcm;
   Type_infSwcApplTpmsAra_stPressure               stPressureTarget;
   Type_infSwcApplTpmsAra_stPressure               stPressureLatestDisplay;
   Type_infSwcApplTpmsAra_stTemperature            stTemperatureLatestDisplay;
   uint8                                           au8LogDevelopment[CfgSwcApplTpms_dSizeLogDevelopment];
   Type_infSwcApplTpmsAra_stStatusTyre             stStatusTyre;
   Type_infSwcApplTpmsAra_stDataControlFbd         stDataControlFbd;
   Type_infSwcApplTpmsAra_stDataMileageTyre        stDataMileageTyre;
   Type_infSwcApplTpmsAra_stDataTyreCodeQR         stDataTyreCodeQR;
   Type_infSwcApplTpmsAra_stDataTyreInternalLast   stDataTyreInternalLast;
   Type_infSwcApplTpmsAra_stTyreParkingSupervision stTyreParkingSupervision;
   Type_infSwcApplTpmsAra_stStatusWheelChange      stStatusWheelChange;
   Type_infSwcApplTpmsAra_stMonitoringParking      stMonitoringParking;
   Type_infSwcApplTpmsAra_stDataCalibration        stDataCalibration;
   Type_infSwcApplTpmsAra_stDataTyreErfsActual     stDataTyreErfsActual;
   Type_infSwcApplTpmsAra_stTyreAxleErfsHmi        stTyreAxleErfsHmi;
   Type_infSwcApplTpmsAra_stStatusErfs             stStatusErfs;
   Type_infSwcApplTpmsAra_stIndicatorLevelPressure stIndicatorLevelPressure;
   Type_infSwcApplTpmsAra_stNotificationErfsHmi    stNotificationErfsHmi;
   Type_infSwcApplTpmsAra_stStatusEventDtc         astListStatusEventDtc[CfgSwcApplTpms_dNumberStatusEventDtc];
}Type_infSwcApplTpmsAra_stSenders;

typedef enum{
      infSwcApplTpmsAra_eStatusApi_OK
   ,  infSwcApplTpmsAra_eStatusApi_NOK
   ,  infSwcApplTpmsAra_eStatusApi_PENDING = 10u
}Type_infSwcApplTpmsAra_eStatusApi;

typedef struct{
   FUNC(Type_infSwcApplTpmsAra_eStatusApi, SWCAPPLTPMS_CODE) (*get_rdci_coding_parameters)(
      CONSTP2VAR(Type_infAraSwcApplTpms_stParameterCodingTpms, SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrstParameterCodingTpms
   );

   FUNC(Type_infSwcApplTpmsAra_eStatusApi, SWCAPPLTPMS_CODE) (*get_rdci_coding_erfs_caf)(
      CONSTP2VAR(Type_infAraSwcApplTpms_stCodingErfsCaf,       SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrstCodingErfsCaf
   );

   FUNC(void, SWCAPPLTPMS_CODE) (*get_date_and_time)(
         CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
      ,  CONSTP2VAR(Type_infAraSwcApplTpms_stDateAndTime,      SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrstDateAndTime
   );

   FUNC(void, SWCAPPLTPMS_CODE) (*get_altitude)(
         CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
      ,  CONSTP2VAR(Type_System_tDistance_m_f32,               SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrtAltitude
      ,  CONSTP2VAR(Type_System_tDistance_m_f32,               SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrtErrorAltitude
   );

   FUNC(void, SWCAPPLTPMS_CODE) (*get_atmospheric_pressure)(
         CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
      ,  CONSTP2VAR(Type_System_tPressure_mbar_u16,            SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrtPressureAtmospheric
   );

   FUNC(void, SWCAPPLTPMS_CODE) (*get_vehicle_gear)(
         CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
      ,  CONSTP2VAR(Type_infAraSwcApplTpms_eGearVehicle,       SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreGearVehicle
   );

   FUNC(Type_infAraSwcApplTpms_eDtcSuppressionNetwork, SWCAPPLTPMS_CODE) (*get_network_dtc_suppression)(void);
   FUNC(Type_infAraSwcApplTpms_eStatusNetwork,         SWCAPPLTPMS_CODE) (*get_network_status         )(void);

   FUNC(void, SWCAPPLTPMS_CODE) (*get_air_temperature)(
         CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
      ,  CONSTP2VAR(Type_System_tTemperature_DegC_s16,         SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptrtTemperatureAir
   );

   FUNC(void, SWCAPPLTPMS_CODE) (*get_relative_time)(
      CONSTP2VAR(Type_infAraSwcApplTpms_eQualitySignal,     SWCAPPLTPMS_APPL_DATA, AUTOMATIC) lcptreQualitySignal
		   , uint32*                                const
   );

   void                                  (*get_vehicle_state            )(Type_infAraSwcApplTpms_eQualitySignal*           const, Type_infAraSwcApplTpms_eStateVehicle*  const              );
   void                                  (*get_vehicle_velocity         )(Type_infAraSwcApplTpms_eQualitySignal*           const, uint16*                                const              );
   void                                  (*get_odometer                 )(Type_infAraSwcApplTpms_eQualitySignal*           const, uint32*                                const              );
   void                                  (*get_nvm_block_addresses      )(Type_infAraSwcApplTpms_stAddressesBlockNvM*      const                                                            );
   void                                  (*get_nvm_block_error_status   )(Dtms_nvm_block_ids_et,                                  Type_infAraSwcApplTpms_eReqNvM*        const              );
   void                                  (*set_check_control_message    )(Type_infSwcApplTpmsAra_stCcm*                    const                                                            );
   void                                  (*set_tyre_current_data        )(Type_infSwcApplTpmsAra_stPressure*               const, Type_infSwcApplTpmsAra_stTemperature*  const              );
   void                                  (*set_tyre_target_pressures    )(Type_infSwcApplTpmsAra_stPressure*               const                                                            );
   void                                  (*set_rdci_debug_msg           )(uint8* development_log_p                                                                                          );
   void                                  (*set_tyre_status              )(Type_infSwcApplTpmsAra_stStatusTyre*             const                                                            );
   void                                  (*set_fbd_control              )(Type_infSwcApplTpmsAra_stDataControlFbd*         const                                                            );
   void                                  (*set_tyre_mileage             )(Type_infSwcApplTpmsAra_stDataMileageTyre*        const                                                            );
   void                                  (*set_tyre_qr_code             )(Type_infSwcApplTpmsAra_stDataTyreCodeQR*         const                                                            );
   void                                  (*set_tyre_last_internal_data  )(Type_infSwcApplTpmsAra_stDataTyreInternalLast*   const                                                            );
   void                                  (*set_tyre_parking_supervision )(Type_infSwcApplTpmsAra_stTyreParkingSupervision* const                                                            );
   void                                  (*set_wheel_status_change      )(Type_infSwcApplTpmsAra_stStatusWheelChange*      const                                                            );
   void                                  (*set_parking_monitoring       )(Type_infSwcApplTpmsAra_stMonitoringParking*      const                                                            );
   void                                  (*set_calibration_data         )(Type_infSwcApplTpmsAra_stDataCalibration*        const                                                            );
   void                                  (*set_erfs_actual_tyre_data    )(Type_infSwcApplTpmsAra_stDataTyreErfsActual*     const                                                            );
   void                                  (*set_erfs_hmi_axle_tyre_data  )(Type_infSwcApplTpmsAra_stTyreAxleErfsHmi*        const                                                            );
   void                                  (*set_erfs_hmi_status          )(Type_infSwcApplTpmsAra_stStatusErfs*             const                                                            );
   void                                  (*set_tyre_pressure_level_data )(Type_infSwcApplTpmsAra_stIndicatorLevelPressure* const                                                            );
   void                                  (*set_erfs_hmi_notification    )(Type_infSwcApplTpmsAra_stNotificationErfsHmi*    const                                                            );
   uint8                                 (*set_dtc_event_status         )(Type_SwcServiceDem_eIdDtc,                              Type_infSwcApplTpmsAra_stStatusEventDtc                   );
   uint8                                 (*set_nvm_write_block_request  )(Dtms_nvm_block_ids_et                                                                                             );
   void                                  (*set_diagnostic_log_and_trace )(uint8,                                                  uint16                                                    );
}Type_infSwcApplTpmsAra_stContext;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define Rdci_START_SEC_VAR_INIT_UNSPECIFIED //TBD: MemMap
#include "MemMapSwcApplTpms.hpp"
extern uint8 rdci_flag;
#define Rdci_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMapSwcApplTpms.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void infSwcApplTpmsAra_vInit(
   Type_infSwcApplTpmsAra_stContext* lpstContext
);

extern void infSwcApplTpmsAra_vRunnable(void);


/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

