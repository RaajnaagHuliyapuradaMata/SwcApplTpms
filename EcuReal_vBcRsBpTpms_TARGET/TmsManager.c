/******************************************************************************/
/* File   : TmsManager.c                                                      */
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
#include "Std_Types.hpp"

#include "SilaX.hpp"
#include "state_bzx.hpp"
#include "DevCanHandling.hpp"

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
   boolean bFunctioning   : 1;
   boolean bAutoLearning  : 1;
   boolean bAutoLocation  : 1;
   boolean bCyclicMessage : 1;
   boolean bModeDeveloper : 1;
}Type_SwcApplTpms_stStatus;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static Type_SwcApplTpms_stStatus SwcApplTpms_stStatus;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
boolean SwcApplTpms_bIsFunctioning                           (void){return SwcApplTpms_stStatus.bFunctioning;}
boolean infSwcApplTpmsSwcServiceDem_bIsFinishedAutolocation  (void){return SwcApplTpms_stStatus.bAutoLocation;}
boolean infSwcApplTpmsSwcServiceComM_bIsEnabledMessageCyclic (void){return SwcApplTpms_stStatus.bCyclicMessage;}
boolean SwcApplTpms_bIsFinishedAutolearn                     (void){return SwcApplTpms_stStatus.bAutoLearning;}
boolean SwcApplTpms_bIsActiveModeDeveloper                   (void){return SwcApplTpms_stStatus.bModeDeveloper;}

void InfSwcApplTpmsSwcServiceOs_vInitFunction(void){
   SwcApplTpms_stStatus.bFunctioning   = 0;
   SwcApplTpms_stStatus.bAutoLearning  = 0;
   SwcApplTpms_stStatus.bAutoLocation  = 0;
   SwcApplTpms_stStatus.bCyclicMessage = 0;
   SwcApplTpms_stStatus.bModeDeveloper = 0;
}

void SwcApplTpms_vRunnableUpdateStatus(void){
   SwcApplTpms_stStatus.bFunctioning   = (SILA_STATE_MALFUNCTIONFLASH != SilaGetState()                                                 ) ? TRUE : FALSE;
   SwcApplTpms_stStatus.bAutoLearning  =  (TRUE == bGetBitBetriebszustandBZ(cER_FINISH)                                                 ) ? TRUE : FALSE;
   SwcApplTpms_stStatus.bAutoLocation  = ((TRUE == bGetBitBetriebszustandBZ(cWA_FINISH)) && (FALSE == DCH_IsContinousAPCReadingActive())) ? TRUE : FALSE;
   SwcApplTpms_stStatus.bCyclicMessage =  (TRUE == DCH_SubmultiplexConfigGetStatus()                                                    ) ? TRUE : FALSE;
   SwcApplTpms_stStatus.bModeDeveloper =  (TRUE == DCH_IsDeveloperModeActive()                                                          ) ? TRUE : FALSE;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

