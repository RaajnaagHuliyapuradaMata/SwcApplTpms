

#include "TmsManager.hpp"

static tsTPMS_Data Tms__Status;

extern void Tms_Init(void){
  Tms__Status.ucStatus = TMS__INIT_VALUE;
}

extern tsTPMS_Data *Tms_GetTmsStatusPointer(void){
  return &Tms__Status;
}

extern boolean Tms_IsTmsFunctioning(void){
  boolean BO_IsTmsFunctioning;

  if((Tms__Status.ucStatus & TMS__FUNCTIONING_BIT_MASK) != 0U)
  {
    BO_IsTmsFunctioning = TRUE;
  }
  else{
    BO_IsTmsFunctioning = FALSE;
  }

  return BO_IsTmsFunctioning;
}

extern boolean Tms_IsAutolocationFinished(void){
  boolean BO_IsAutolocationFinished;

  if((Tms__Status.ucStatus & TMS__AUTOLOCATION_BIT_MASK) != 0U)
  {
    BO_IsAutolocationFinished = TRUE;
  }
  else{
    BO_IsAutolocationFinished = FALSE;
  }

  return BO_IsAutolocationFinished;
}

extern boolean Tms_IsCyclicMessageEnabled(void){
  boolean BO_IsCyclicMessageEnabled;

  if((Tms__Status.ucStatus & TMS__CYCLIC_MESSAGE_BIT_MASK) != 0U)
  {
    BO_IsCyclicMessageEnabled = TRUE;
  }
  else{
    BO_IsCyclicMessageEnabled = FALSE;
  }

  return BO_IsCyclicMessageEnabled;
}

extern boolean Tms_IsAutolearnFinished(void){
  boolean BO_IsAutolearnFinished;

  if((Tms__Status.ucStatus & TMS__AUTOLEARN_BIT_MASK) != 0U)
  {
    BO_IsAutolearnFinished = TRUE;
  }
  else{
    BO_IsAutolearnFinished = FALSE;
  }

  return BO_IsAutolearnFinished;
}

extern boolean Tms_IsDeveloperModeActive(void){
  boolean BO_IsDeveloperModeActive;

  if((Tms__Status.ucStatus & TMS__DEVELOPER_MODE_BIT_MASK) != 0U)
  {
    BO_IsDeveloperModeActive = TRUE;
  }
  else{
    BO_IsDeveloperModeActive = FALSE;
  }

  return BO_IsDeveloperModeActive;
}
