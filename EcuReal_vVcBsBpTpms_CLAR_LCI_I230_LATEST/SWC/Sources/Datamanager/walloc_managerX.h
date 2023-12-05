#ifndef _wallox_manager_X_H
#define _wallox_manager_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cWatoContinue FALSE
#define cWatoRestart  TRUE

#define cCalOnErFinishIsInactive     (uint8)0xffu
#define cCalOnErFinishIsActive       (uint8)0x00
#define cCalOnErFinishTriggerPlausi  (uint8)0x0f

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

#endif
