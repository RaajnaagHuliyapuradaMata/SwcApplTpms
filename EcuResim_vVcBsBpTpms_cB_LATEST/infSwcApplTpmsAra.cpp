/******************************************************************************/
/* File   : infSwcApplTpmsAra.cpp                                             */
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
#include "Types_Std.hpp"

#include "infAraSwcApplTpms.hpp"
#include "infSwcApplTpmsAra.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   Type_infAraSwcApplTpms_stReceivers stReceivers;
   Type_infSwcApplTpmsAra_stSenders   stSenders;
}Type_SwcApplTpms_stContext;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static Type_SwcApplTpms_stContext SwcApplTpms_stContext = {
      Default_infAraSwcApplTpms_stReceivers
   ,  {0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}}
};

static Type_infSwcApplTpmsAra_stContext* infSwcApplTpmsAra_pstContext = ((Type_infSwcApplTpmsAra_stContext*)NULL_PTR);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SWCAPPLTPMS_CODE) infSwcApplTpmsAra_vInit(
   Type_infSwcApplTpmsAra_stContext* lpstContext
){
   //TBD: Component init complete
   infSwcApplTpmsAra_pstContext = lpstContext;
}

FUNC(void, SWCAPPLTPMS_CODE) infSwcApplTpmsAra_vRunnable(void){
   //TBD: Component init check
   //TBD: Component init check fail - report Det error

   //TBD: Delete test code - "Receivers"
   (void)infSwcApplTpmsAra_pstContext->get_rdci_coding_parameters (&SwcApplTpms_stContext.stReceivers.stParameterCodingTpms);
   (void)infSwcApplTpmsAra_pstContext->get_rdci_coding_erfs_caf   (&SwcApplTpms_stContext.stReceivers.stCodingErfsCaf);
         infSwcApplTpmsAra_pstContext->get_date_and_time          (&SwcApplTpms_stContext.stReceivers.eQualitySignalDateAndTime,         &SwcApplTpms_stContext.stReceivers.stDateAndTime);
         infSwcApplTpmsAra_pstContext->get_altitude               (&SwcApplTpms_stContext.stReceivers.eQualitySignalAltitude,            &SwcApplTpms_stContext.stReceivers.tAltitude, &SwcApplTpms_stContext.stReceivers.tErrorAltitude);
         infSwcApplTpmsAra_pstContext->get_atmospheric_pressure   (&SwcApplTpms_stContext.stReceivers.eQualitySignalPressureAtmospheric, &SwcApplTpms_stContext.stReceivers.tPressureAtmospheric);
         infSwcApplTpmsAra_pstContext->get_vehicle_gear           (&SwcApplTpms_stContext.stReceivers.eQualitySignalGearVehicle,         &SwcApplTpms_stContext.stReceivers.eGearVehicle);
   SwcApplTpms_stContext.stReceivers.eDtcSuppressionNetwork = infSwcApplTpmsAra_pstContext->get_network_dtc_suppression();
   SwcApplTpms_stContext.stReceivers.eStatusNetwork         = infSwcApplTpmsAra_pstContext->get_network_status();
         infSwcApplTpmsAra_pstContext->get_air_temperature        (&SwcApplTpms_stContext.stReceivers.eQualitySignalTemperatureAir,      &SwcApplTpms_stContext.stReceivers.tTemperatureAir);

         infSwcApplTpmsAra_pstContext->get_vehicle_state          (&SwcApplTpms_stContext.stReceivers.eQualitySignalStateVehicle,        &SwcApplTpms_stContext.stReceivers.eStateVehicle);
         infSwcApplTpmsAra_pstContext->get_vehicle_velocity       (&SwcApplTpms_stContext.stReceivers.eQualitySignalVelocityVehicle,     &SwcApplTpms_stContext.stReceivers.u16VelocityVehicle);
         infSwcApplTpmsAra_pstContext->get_odometer               (&SwcApplTpms_stContext.stReceivers.eQualitySignalOdometer,            &SwcApplTpms_stContext.stReceivers.u32Odometer);
         infSwcApplTpmsAra_pstContext->get_relative_time          (&SwcApplTpms_stContext.stReceivers.eQualitySignalTimeRelative,        &SwcApplTpms_stContext.stReceivers.u32TimeRelative);
         infSwcApplTpmsAra_pstContext->get_nvm_block_addresses    (&SwcApplTpms_stContext.stReceivers.stAddressesBlockNvM);
         infSwcApplTpmsAra_pstContext->get_nvm_block_error_status (0, &SwcApplTpms_stContext.stReceivers.aeListReqNvM[0]); //TBD: request vs status? (per block id - total len configured?)

   //TBD: Delete test code - "Senders"
         infSwcApplTpmsAra_pstContext->set_check_control_message    (&SwcApplTpms_stContext.stSenders.stCcm);
         infSwcApplTpmsAra_pstContext->set_tyre_current_data        (&SwcApplTpms_stContext.stSenders.stPressureLatestDisplay, &SwcApplTpms_stContext.stSenders.stTemperatureLatestDisplay);
         infSwcApplTpmsAra_pstContext->set_tyre_target_pressures    (&SwcApplTpms_stContext.stSenders.stPressureTarget);
         infSwcApplTpmsAra_pstContext->set_rdci_debug_msg           (&SwcApplTpms_stContext.stSenders.au8LogDevelopment[0]);
         infSwcApplTpmsAra_pstContext->set_tyre_status              (&SwcApplTpms_stContext.stSenders.stStatusTyre);
         infSwcApplTpmsAra_pstContext->set_fbd_control              (&SwcApplTpms_stContext.stSenders.stDataControlFbd);
         infSwcApplTpmsAra_pstContext->set_tyre_mileage             (&SwcApplTpms_stContext.stSenders.stDataMileageTyre);
         infSwcApplTpmsAra_pstContext->set_tyre_qr_code             (&SwcApplTpms_stContext.stSenders.stDataTyreCodeQR);
         infSwcApplTpmsAra_pstContext->set_tyre_last_internal_data  (&SwcApplTpms_stContext.stSenders.stDataTyreInternalLast);
         infSwcApplTpmsAra_pstContext->set_tyre_parking_supervision (&SwcApplTpms_stContext.stSenders.stTyreParkingSupervision);
         infSwcApplTpmsAra_pstContext->set_wheel_status_change      (&SwcApplTpms_stContext.stSenders.stStatusWheelChange);
         infSwcApplTpmsAra_pstContext->set_parking_monitoring       (&SwcApplTpms_stContext.stSenders.stMonitoringParking);
         infSwcApplTpmsAra_pstContext->set_calibration_data         (&SwcApplTpms_stContext.stSenders.stDataCalibration);
         infSwcApplTpmsAra_pstContext->set_erfs_actual_tyre_data    (&SwcApplTpms_stContext.stSenders.stDataTyreErfsActual);
         infSwcApplTpmsAra_pstContext->set_erfs_hmi_axle_tyre_data  (&SwcApplTpms_stContext.stSenders.stTyreAxleErfsHmi);
         infSwcApplTpmsAra_pstContext->set_erfs_hmi_status          (&SwcApplTpms_stContext.stSenders.stStatusErfs);
         infSwcApplTpmsAra_pstContext->set_tyre_pressure_level_data (&SwcApplTpms_stContext.stSenders.stIndicatorLevelPressure);
         infSwcApplTpmsAra_pstContext->set_erfs_hmi_notification    (&SwcApplTpms_stContext.stSenders.stNotificationErfsHmi);
   (void)infSwcApplTpmsAra_pstContext->set_dtc_event_status         (SwcServiceDem_eIdDtc_NONE, SwcApplTpms_stContext.stSenders.astListStatusEventDtc[SwcServiceDem_eIdDtc_NONE]); //TBD: What is returned?
   (void)infSwcApplTpmsAra_pstContext->set_nvm_write_block_request  (0); //TBD: What is returned?
         infSwcApplTpmsAra_pstContext->set_diagnostic_log_and_trace (0, 0);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

