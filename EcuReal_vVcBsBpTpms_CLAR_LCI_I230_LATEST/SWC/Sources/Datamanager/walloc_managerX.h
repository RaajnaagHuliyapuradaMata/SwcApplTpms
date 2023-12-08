#ifndef _wallox_manager_X_H
#define _wallox_manager_X_H
/******************************************************************************/
/* File   : walloc_managerX.h                                                 */
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
#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cWatoContinue FALSE
#define cWatoRestart  TRUE

#define cCalOnErFinishIsInactive     (uint8)0xffu
#define cCalOnErFinishIsActive       (uint8)0x00
#define cCalOnErFinishTriggerPlausi  (uint8)0x0f

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
extern void SetAbsDataWAM( ImpTypeRecCddAbsData absData);
extern void ProcessAllocationWAM(Rte_Instance self, ImpTypeRecCddRdcData rdcData);
extern void SetVehicleSpeedWAM(Rte_Instance self, Rdci_V_VEH_Type vspeed);
extern void SetGearWAM( Rdci_WMOM_DRV_4_Type wmomDriveInfo);
extern void WatoTickWAM(Rte_Instance self);
extern void WatoRunWAM(Rte_Instance self, boolean bRestart);
extern void WatoStopWAM(void);
extern void StartLearnLocateWAM(Rte_Instance self);
extern void ContinueLearnWAM(Rte_Instance self);
extern void ContinueLocateWAM(Rte_Instance self);
extern uint16 ushGetWatoTimeoutValueWAM(void);
extern uint16 ushGetInvalidAbsTstmpCounterWAM(void);
extern uint8 ucGetInvalidRdcTstmpCounterWAM(void);
extern boolean bAllocationIsActive(Rte_Instance self);
extern uint16* GetPointerToAbsCountersWAM(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

