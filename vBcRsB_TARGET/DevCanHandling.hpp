#ifndef DevCanHandling_H
#define DevCanHandling_H

//TBD: Headers include needed?
#include "SwcApplTpms_DevCanMessages.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"
#include "global.hpp"

extern void    DCH_CheckCanDebugRequest        (const Type_SwcApplTpms_stMessageCan* CanDebugRequestMsg);
extern void    DCH_GetCanDebugResponseData     (      Type_SwcApplTpms_stMessageCan* CanDebugResponseMsg);
extern uint8   DCH_MultiplexMsgGetActiveStatus (uint8 ui8_MultiplexNr);
extern boolean DCH_IsContinousAPCReadingActive (void);
extern void    DCH_Init                        (void);
extern boolean DCH_IsCanDebugEnabled           (void);
extern boolean DCH_IsDeveloperModeActive       (void);
extern uint8   DCH_SubmultiplexConfigGetStatus (void);

#pragma PRQA_NO_SIDE_EFFECTS DCH_IsContinousAPCReadingActive
#pragma PRQA_NO_SIDE_EFFECTS DCH_IsCanDebugEnabled
#pragma PRQA_NO_SIDE_EFFECTS DCH_SubmultiplexConfigGetStatus

#endif
