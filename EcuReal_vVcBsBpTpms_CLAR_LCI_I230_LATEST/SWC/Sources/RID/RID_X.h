#ifndef _rid_X_H
#define _rid_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define cTyreDimSize  ((uint8)6)
#define cTyreDOTSize  ((uint8)8)
#define cTyreOEM1Size ((uint8)6)
#define cTyreOEM2Size ((uint8)5)
#define cTyreOEMSize  (cTyreOEM1Size+cTyreOEM2Size)

extern void    SaveTyreDimensionDataRID( ImpTypeRecCddRdcData tReData);
extern void    SaveTyreDOTDataRID( ImpTypeRecCddRdcData tReData);
extern void    SaveTyreOE1DataRID( ImpTypeRecCddRdcData tReData);
extern void    SaveTyreOE2DataRID( ImpTypeRecCddRdcData tReData);
extern void    CheckTyreStatusRID(Rte_Instance self, ImpTypeRecCddRdcData tReData);
extern void    SaveRidDataAndCompareRID(Rte_Instance self);
extern void    SaveRidDataAndCompareInBmRID(void);
extern void    InitRidDataRID(Rte_Instance self);
extern void    DeleteRidDataOfHisColRID(Rte_Instance self, uint8 HisIx);
extern boolean GetReliableRSCInfoRID(Rte_Instance self, uint8 ucRadPos, boolean* bRSCInfoVal);
extern boolean GetFAxisTyreDataRID(uint8* pRidData);
extern boolean GetRAxisTyreDataRID(Rte_Instance self, uint8* pRidData);
extern boolean CheckRearAxisRidDataAvailRID(void);
extern uint8   GetTyreDimDataRID( const uint8 HisIx, const uint8 x);
extern uint8   GetTyreDOTDataRID( const uint8 HisIx, const uint8 x);
extern uint8   GetTyreOEMDataRID( const uint8 HisIx, const uint8 x);
extern void    CheckDefaultSerNumAndReplaceRID(uint8 HisIx);
extern uint8   SaveOemDataRID(void);
extern uint8   GetRidManAutoFLagRID(void);

#ifdef __cplusplus
}
#endif

#endif
