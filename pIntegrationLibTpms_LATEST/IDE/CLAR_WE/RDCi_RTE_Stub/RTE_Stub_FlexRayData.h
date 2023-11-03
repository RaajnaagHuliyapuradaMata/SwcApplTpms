

#ifndef _RTE_STUB_FLEXRAYDATA_H
#define _RTE_STUB_FLEXRAYDATA_H

#include "Rte_CtApHufTpmsSWC_Type.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "Rte_Stub_FlexRayDataX.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define cIx_DISP_HR           ((uint8) 0x01)
#define cIx_DISP_MN           ((uint8) 0x02)
#define cIx_DISP_SEC          ((uint8) 0x04)
#define cIx_DISP_DATE_DAY     ((uint8) 0x08)
#define cIx_DISP_DATE_WDAY    ((uint8) 0x10)
#define cIx_DISP_DATE_MON     ((uint8) 0x20)
#define cIx_DISP_DATE_YR      ((uint8) 0x40)
#define cIx_ST_DISP_CTI_DATE  ((uint8) 0x80)

void PutSpeedData(Rdci_V_VEH_Type* data);

void PutUnitDataMile(uint8* data);
void PutUnitDataAip(uint8* data);
void PutUnitDataTemp(uint8* data);

void PutTemperatureData(uint8* data);

void PutDirectionData(Rdci_WMOM_DRV_4_Type* data);

void PutOpSlctnTyr(uint8* data);
void PutOpTarPLoco(uint8* data);
void PutOpTpct(uint8* data);
void PutOpTyrSeason(uint8* data);
void PutRqOl(uint8* data);

void PutOpIdrSlctn(uint8* data);
void PutStIdrMsgc(uint8* data);

void PutRelTime(Rdci_T_SEC_COU_REL_Type* data);
void PutAmbientPressure(Rdci_AIP_ENG_DRV_Type * data);
void PutPositionAltitude( Rdci_GNSSPositionAltitude_Type * data);
void PutErrorAltitudeMeters( Rdci_GNSSPositionAltitude_Type * data);

void PutTimeDate(Rdci_UHRZEIT_DATUM_Type* data);

void PutMileKm(Rdci_MILE_KM_Type* data);

void PutVehicleCondition(Rdci_CON_VEH_Type* data);

void PutBusState(uint8* ucBusState);

void PutStIlkErrmFzm(Rdci_ST_ILK_ERRM_FZM_Type *);

void PutStEnergFzm(Rdci_ST_ENERG_FZM_Type *);

#ifdef __cplusplus
}
#endif

#endif
