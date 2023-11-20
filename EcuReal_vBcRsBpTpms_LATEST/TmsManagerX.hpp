#ifndef TMS_MANAGER_X_H
#define TMS_MANAGER_X_H

#include "iTpms_Interface.hpp"

extern void Tms_Init(void);
extern tsTPMS_Data *Tms_GetTmsStatusPointer(void);
extern boolean Tms_IsTmsFunctioning(void);
extern boolean Tms_IsAutolocationFinished(void);
extern boolean Tms_IsCyclicMessageEnabled(void);
extern boolean Tms_IsAutolearnFinished(void);
extern boolean Tms_IsDeveloperModeActive(void);

#endif
