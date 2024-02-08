#pragma once
/******************************************************************************/
/* File   : SwcApplTpms_CAN_If.hpp                                            */
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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define VEHSTATE_VEHICLE_SPEED_HYST_ID                                ((uint8)0)
#define VEHSTATE_REDIAG_ACTIVE_HYST_ID                                ((uint8)1)
#define VEH_IGN_OFF                                                ((uint8)0x00)
#define VEH_IGN_ON                                                 ((uint8)0x01)
#define VEH_IGN_UNKNOWN                                            ((uint8)0xFF)
#define cDriveDirStop                                                         2U
#define cDriveDirBackward                                                     1U
#define cDriveDirForward                                                      0U
#define cFMMOTMAXnotValid                                          ((uint8)0x00)
#define cFMMOTMAXmin                                               ((uint8)0x47)
#define cFMMOTMAXmax                                               ((uint8)0x8D)
#define RECEIVE_KL15_SUBSTVAL                               ((uint8)VEH_IGN_OFF)
#define RECEIVE_VEHSPEED_SUBSTVAL                                  ((uint16)275)
#define RECEIVE_TEMP_SUBSTVAL                                       ((sint16)40)
#define RECEIVE_TEMP20_SUBSTVAL                                      ((sint8)20)
#define RECEIVE_DIRECTION_SUBSTVAL                     ((uint8)cDriveDirForward)
#define RECEIVE_FMMOTMAX_SUBSTVAL                                   ((uint8)130)
#define RECEIVE_ABSPULSE_SUBSTVAL                                  ((uint8)0xFF)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef union{
   CAN_HMI_type                  sHMI;
   tsHMI_Temperature_RefPres     sHMI_Temperature_RefPres;
   Type_SwcApplTpms_stMessageCan sMsgsBytes;
}tuCAN_HMI_Data;

typedef union{
   CAN_TPMS_Software_ID_type     sTPMS_Software_ID;
   Type_SwcApplTpms_stMessageCan sMsgsBytes;
}tuCAN_TPMS_Software_ID_Data;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void    Init_CAN_Data                  (void);
extern void    VehStateInit                   (void);
extern void    VehStateGetKL15                (boolean* bpKL15);
extern boolean VehStateGetRoadmode            (void);
extern void    VehStateTriggerHysteresis      (uint8    signalHandle, uint16 actVelocity);
extern boolean VehStateGetVehicleRollingState (void);
extern boolean VehStateGetReDiagActiveState   (void);
extern uint8   ReceiveGetVehicleSpeed         (uint16*  pVehSpeed);
extern uint8   ReceiveGetDirection            (uint8*   pucDirection);
extern uint8   ReceiveGetOutdoorTemp          (sint16*  pODTemp);
extern uint8   ReceiveGetTrefTemperature      (sint8*   pODTemp);
extern boolean ReceiveGetVehicleSpeedValidity (void);
extern uint8   ReceiveGetFmmotmax             (uint8*   pucFmmotmaxPressure);
extern void    OperateAtmosphericPressure     (void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

