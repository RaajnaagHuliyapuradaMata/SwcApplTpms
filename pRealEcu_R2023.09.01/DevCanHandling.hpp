

#ifndef DevCanHandling_H
#define DevCanHandling_H

#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"

#include "global.hpp"

//! Check CAN debug reason and call the corresponding function.
extern void DCH_CheckCanDebugRequest(const tsCAN_Message* CanDebugRequestMsg);

//! Create and send a response message for CAN debug configuration
extern void DCH_GetCanDebugResponseData(tsCAN_Message* CanDebugResponseMsg);

//! Get a Multiplex ID number as parameter for which the status has to be checked and according to it enabled or disabled will be set.
extern uint8 DCH_MultiplexMsgGetActiveStatus(uint8 ui8_MultiplexNr);

//! Check if continuous APC data reading, also after auto-localization is finished, is enabled to be read.
extern boolean DCH_IsContinousAPCReadingActive(void);

//! Init the global variables and structures from the module.
extern void DCH_Init(void);

//! Return the CAN debug Configuration Status
extern boolean DCH_IsCanDebugEnabled(void);

//! Return the Developer Mode Configuration Status, if active forward all RF telegrams to TPMS module.
extern boolean DCH_IsDeveloperModeActive(void);

extern uint8 DCH_SubmultiplexConfigGetStatus(void);

#pragma PRQA_NO_SIDE_EFFECTS DCH_IsContinousAPCReadingActive
#pragma PRQA_NO_SIDE_EFFECTS DCH_IsCanDebugEnabled
#pragma PRQA_NO_SIDE_EFFECTS DCH_SubmultiplexConfigGetStatus

#endif
