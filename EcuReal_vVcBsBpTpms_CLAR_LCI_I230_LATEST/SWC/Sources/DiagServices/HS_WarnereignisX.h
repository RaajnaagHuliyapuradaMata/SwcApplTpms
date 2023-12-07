#ifndef _hs_warnereignis_X_H
#define _hs_warnereignis_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void InitFastaWarnEventsDS(Rte_Instance self);
extern void ProcessFastaWarnEventsDS(Rte_Instance self);
extern void CountDrivenKilometersWithWarningDS(Rte_Instance self);
extern void ReadWarnereignisRuecknahmeDS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_1_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_2_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignis_3_DS(Rte_Instance self, uint8* paucData);
extern void ReadWarnereignisWeich_1_DS(Rte_Instance self, uint8* aucData);
extern void ReadWarnereignisWeich_2_DS(Rte_Instance self, uint8* aucData);
extern void ReadWarnereignisWeich_3_DS(Rte_Instance self, uint8* aucData);

#ifdef __cplusplus
}
#endif

#endif

