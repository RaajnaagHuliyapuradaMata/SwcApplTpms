#ifndef __RTE_STUB_DEM_SERVICES_H
#define __RTE_STUB_DEM_SERVICES_H

#include "Rte_Type.h"
#include "RTE_Stub_DemServicesX.h"

#ifdef __cplusplus
extern "C"
{
#endif

static void ClearDtcUwbData( uint8 ucDtcNo);
static uint8 ucGetRdcSensorHersteller(void);
static void SaveDTC( uint8 ucDtcNo, ImpTypeRefDem_EventStatusType EventStatus);

#ifdef __cplusplus
}
#endif

#endif
