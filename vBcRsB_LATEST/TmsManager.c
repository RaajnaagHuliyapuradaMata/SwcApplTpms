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

#include "TmsManager.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
static tsTPMS_Data Tms__Status;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void Tms_Init(void){
  Tms__Status.ucStatus = TMS__INIT_VALUE;
}

extern tsTPMS_Data *Tms_GetTmsStatusPointer(void){
  return &Tms__Status;
}

extern boolean Tms_IsTmsFunctioning(void){
  boolean BO_IsTmsFunctioning;
  if((Tms__Status.ucStatus & TMS__FUNCTIONING_BIT_MASK) != 0U){
    BO_IsTmsFunctioning = TRUE;
  }
  else{
    BO_IsTmsFunctioning = FALSE;
  }
  return BO_IsTmsFunctioning;
}

extern boolean Tms_IsAutolocationFinished(void){
  boolean BO_IsAutolocationFinished;
  if((Tms__Status.ucStatus & TMS__AUTOLOCATION_BIT_MASK) != 0U){
    BO_IsAutolocationFinished = TRUE;
  }
  else{
    BO_IsAutolocationFinished = FALSE;
  }
  return BO_IsAutolocationFinished;
}

extern boolean Tms_IsCyclicMessageEnabled(void){
  boolean BO_IsCyclicMessageEnabled;
  if((Tms__Status.ucStatus & TMS__CYCLIC_MESSAGE_BIT_MASK) != 0U){
    BO_IsCyclicMessageEnabled = TRUE;
  }
  else{
    BO_IsCyclicMessageEnabled = FALSE;
  }
  return BO_IsCyclicMessageEnabled;
}

extern boolean Tms_IsAutolearnFinished(void){
  boolean BO_IsAutolearnFinished;
  if((Tms__Status.ucStatus & TMS__AUTOLEARN_BIT_MASK) != 0U){
    BO_IsAutolearnFinished = TRUE;
  }
  else{
    BO_IsAutolearnFinished = FALSE;
  }
  return BO_IsAutolearnFinished;
}

extern boolean Tms_IsDeveloperModeActive(void){
  boolean BO_IsDeveloperModeActive;
  if((Tms__Status.ucStatus & TMS__DEVELOPER_MODE_BIT_MASK) != 0U){
    BO_IsDeveloperModeActive = TRUE;
  }
  else{
    BO_IsDeveloperModeActive = FALSE;
  }
  return BO_IsDeveloperModeActive;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

