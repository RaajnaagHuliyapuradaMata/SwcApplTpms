

#include "Rte_CtApHufTpmsSWC_Type.h"
#include "Rte_CtApHufTpmsSWC.h"

#include "RTE_Stub_DemServices.h"
#include "RTE_Stub_DcmServices.h"
#include "RTE_Stub_DtcNvmBlock.h"
#include "RTE_Stub_FlexRayDataX.h"
#include "RTE_Stub_StbMBX.h"

#include "DataManagerX.h"
#include "HS_InaktivEreignisX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "SecondaryDTCX.h"
#include "WAlloc_if.h"
#include "USCS.h"
#include "uswarn_ifX.h"

tRDCiDtcListDef tRDCiDtclist[cMaxErrorCount] =
{

   { 0x48069B, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48069E, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806A1, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806A6, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806B8, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806DA, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806F0, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806F4, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4806FA, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480702, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48070F, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48071F, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480728, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48077C, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48077D, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48077E, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x48077F, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480780, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4809EA, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x4809EB, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480A46, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480ACD, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480ACE, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0x000001E6u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480ACF, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x07DFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480AD0, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x07CFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480AD1, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x07CFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480AD2, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x07CFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480AD3, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x07CFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480AD4, DEM_EVENT_STATUS_PASSED, cDemSecondaryType, FALSE,             0x03EFFF86u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480B02, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF85001FFu, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0x480B03, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF85001FFu, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35428, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3542C, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD354BE, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD354FF, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35565, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3560C, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3565E, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3567D, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35694, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35713, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35720, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35777, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD359DF, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD35AE9, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3673D, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3673E, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } },
   { 0xD3673F, DEM_EVENT_STATUS_PASSED, cDemPrimaryType,   FALSE,             0xF80000C7u, { { 0xFFu, 0xFFu, 0xFFu }, 0xFFFFFFFFu, { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, 0xFFu, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0x7F, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFFu, 0xFFu, 0xFFu, 0xFFu, { 0xFFu, 0xFFu }, { 0xFFu, 0xFFu }, 0xFFu, 0xFFu, 0xFFu, 0xFFFFu, 0xFFu, 0xFFFFu } }
};

void ReadDtcListFromNvmBlock(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++)
  {

    tRDCiDtclist[ucLoop].ucStatus                                       = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) +  4));

    tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[0]                     = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 11));
    tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[1]                     = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 12));
    tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[2]                     = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 13));
    tRDCiDtclist[ucLoop].tUwb.ul0x1768_KM_STAND_SUPREME                 = (uint32) ((ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 14)) << 0) + (ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 15)) << 8) + (ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 16)) << 16) + (ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 17)) << 24));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 18));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 19));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 20));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 21));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 22));
    tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 23));
    tRDCiDtclist[ucLoop].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE  = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 24));
    tRDCiDtclist[ucLoop].tUwb.uc0x2805_AUSSENTEMPERATUR                 = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 25));
    tRDCiDtclist[ucLoop].tUwb.uc0x2866_BETRIEBSSPANNUNG                 = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 26));
    tRDCiDtclist[ucLoop].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT          = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 27));
    tRDCiDtclist[ucLoop].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER            = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 28));
    tRDCiDtclist[ucLoop].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR    = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 29));
    tRDCiDtclist[ucLoop].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]              = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 30));
    tRDCiDtclist[ucLoop].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]              = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 31));
    tRDCiDtclist[ucLoop].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 32));
    tRDCiDtclist[ucLoop].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 33));
    tRDCiDtclist[ucLoop].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 34));
    tRDCiDtclist[ucLoop].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 35));
    tRDCiDtclist[ucLoop].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 36));
    tRDCiDtclist[ucLoop].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 37));
    tRDCiDtclist[ucLoop].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 38));
    tRDCiDtclist[ucLoop].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 39));
    tRDCiDtclist[ucLoop].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL          = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 40));
    tRDCiDtclist[ucLoop].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR          = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 41));
    tRDCiDtclist[ucLoop].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL          = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 42));
    tRDCiDtclist[ucLoop].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR          = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 43));
    tRDCiDtclist[ucLoop].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR    = (sint8) ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 44));
    tRDCiDtclist[ucLoop].tUwb.uc0x410C_RDC_INAKTIV_STATUS               = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 45));
    tRDCiDtclist[ucLoop].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS          = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 46));
    tRDCiDtclist[ucLoop].tUwb.uc0x410E_RDC_STATUS                       = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 47));
    tRDCiDtclist[ucLoop].tUwb.uc0x410F_RDC_KONFIGURATION                = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 48));
    tRDCiDtclist[ucLoop].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 49));
    tRDCiDtclist[ucLoop].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]           = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 50));
    tRDCiDtclist[ucLoop].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]         = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 51));
    tRDCiDtclist[ucLoop].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]         = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 52));
    tRDCiDtclist[ucLoop].tUwb.uc0x4112_RDC_POSITION                     = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 53));
    tRDCiDtclist[ucLoop].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR       = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 54));
    tRDCiDtclist[ucLoop].tUwb.uc0x500A_GESCHWINDIGKEIT                  = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 55));
    tRDCiDtclist[ucLoop].tUwb.ush0x500B_FUNKTIONSZUSTAND                = (uint16) ((ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 56)) << 0) + (ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 57)) << 8));
    tRDCiDtclist[ucLoop].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND        = ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 58));
    tRDCiDtclist[ucLoop].tUwb.ush0x500E_INTERNE_FEHLERNUMMER            = (uint16) ((ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 59)) << 0) + (ucNvmDTC_ReadByte( (ucLoop * sizeof(tRDCiDtcListDef) + 60)) << 8));
  }
}

void WriteDtcListToNvmBlock(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++)
  {
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  0), (uint8) (tRDCiDtclist[ucLoop].ulDtc >>  0) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  1), (uint8) (tRDCiDtclist[ucLoop].ulDtc >>  8) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  2), (uint8) (tRDCiDtclist[ucLoop].ulDtc >> 16) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  3), (uint8) (tRDCiDtclist[ucLoop].ulDtc >> 24) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  4), tRDCiDtclist[ucLoop].ucStatus);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  5), tRDCiDtclist[ucLoop].ucType);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  6), tRDCiDtclist[ucLoop].ucUwbUpdateState);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  7), (uint8) (tRDCiDtclist[ucLoop].ulUwbMask >>  0) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  8), (uint8) (tRDCiDtclist[ucLoop].ulUwbMask >>  8) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) +  9), (uint8) (tRDCiDtclist[ucLoop].ulUwbMask >> 16) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 10), (uint8) (tRDCiDtclist[ucLoop].ulUwbMask >> 24) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 11), tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 12), tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 13), tRDCiDtclist[ucLoop].tUwb.auc0x1702_SAE_CODE[2]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 14), (uint8) (tRDCiDtclist[ucLoop].tUwb.ul0x1768_KM_STAND_SUPREME >>  0) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 15), (uint8) (tRDCiDtclist[ucLoop].tUwb.ul0x1768_KM_STAND_SUPREME >>  8) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 16), (uint8) (tRDCiDtclist[ucLoop].tUwb.ul0x1768_KM_STAND_SUPREME >> 16) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 17), (uint8) (tRDCiDtclist[ucLoop].tUwb.ul0x1768_KM_STAND_SUPREME >> 24) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 18), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 19), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 20), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 21), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 22), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 23), tRDCiDtclist[ucLoop].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 24), tRDCiDtclist[ucLoop].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 25), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x2805_AUSSENTEMPERATUR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 26), tRDCiDtclist[ucLoop].tUwb.uc0x2866_BETRIEBSSPANNUNG);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 27), tRDCiDtclist[ucLoop].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 28), tRDCiDtclist[ucLoop].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 29), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 30), tRDCiDtclist[ucLoop].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 31), tRDCiDtclist[ucLoop].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 32), tRDCiDtclist[ucLoop].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 33), tRDCiDtclist[ucLoop].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 34), tRDCiDtclist[ucLoop].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 35), tRDCiDtclist[ucLoop].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 36), tRDCiDtclist[ucLoop].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 37), tRDCiDtclist[ucLoop].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 38), tRDCiDtclist[ucLoop].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 39), tRDCiDtclist[ucLoop].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 40), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 41), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 42), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 43), (uint8) tRDCiDtclist[ucLoop].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 44), (uint8) tRDCiDtclist[ucLoop].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 45), tRDCiDtclist[ucLoop].tUwb.uc0x410C_RDC_INAKTIV_STATUS);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 46), tRDCiDtclist[ucLoop].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 47), tRDCiDtclist[ucLoop].tUwb.uc0x410E_RDC_STATUS);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 48), tRDCiDtclist[ucLoop].tUwb.uc0x410F_RDC_KONFIGURATION);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 49), tRDCiDtclist[ucLoop].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 50), tRDCiDtclist[ucLoop].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 51), tRDCiDtclist[ucLoop].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 52), tRDCiDtclist[ucLoop].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 53), tRDCiDtclist[ucLoop].tUwb.uc0x4112_RDC_POSITION);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 54), tRDCiDtclist[ucLoop].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 55), tRDCiDtclist[ucLoop].tUwb.uc0x500A_GESCHWINDIGKEIT);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 56), (uint8) (tRDCiDtclist[ucLoop].tUwb.ush0x500B_FUNKTIONSZUSTAND >>  0) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 57), (uint8) (tRDCiDtclist[ucLoop].tUwb.ush0x500B_FUNKTIONSZUSTAND >>  8) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 58), tRDCiDtclist[ucLoop].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 59), (uint8) (tRDCiDtclist[ucLoop].tUwb.ush0x500E_INTERNE_FEHLERNUMMER >>  0) & 0xFFu);
    NvmDTC_WriteByte( (ucLoop * sizeof(tRDCiDtcListDef) + 60), (uint8) (tRDCiDtclist[ucLoop].tUwb.ush0x500E_INTERNE_FEHLERNUMMER >>  8) & 0xFFu);
  }

  NVM_WriteAllDTC();

}

void InitDtcUwbData( uint8 ucDtcNo)
{
  uint8 ucLoop;

  tRDCiDtclist[ucDtcNo].ucUwbUpdateState                               = FALSE;

  for( ucLoop = 0; ucLoop < 3; ucLoop++)
  {
    tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[ucLoop]              = 0xFFu;
  }

  tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                 = 0xFFFFFFFFu;

  for( ucLoop = 0; ucLoop < 6; ucLoop++)
  {
    tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[ucLoop]    = 0xFFu;
  }

  tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE  = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                 = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                 = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT          = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER            = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR    = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]              = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]              = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL          = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR          = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL          = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR          = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR    = 0x7F;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS               = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS          = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                       = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION                = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]           = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]         = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]         = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                     = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR       = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                  = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND                = 0xFFFFu;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND        = 0xFFu;
  tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER            = 0xFFFFu;
}

static void ClearDtcUwbData( uint8 ucDtcNo)
{
  uint8 ucLoop;

  tRDCiDtclist[ucDtcNo].ucUwbUpdateState                               = FALSE;

  for( ucLoop = 0; ucLoop < 3; ucLoop++)
  {
    tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[ucLoop]              = 0;
  }

  tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                 = 0;

  for( ucLoop = 0; ucLoop < 6; ucLoop++)
  {
    tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[ucLoop]    = 0;
  }

  tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE  = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                 = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                 = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER            = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR    = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]              = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]              = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR    = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS               = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS          = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                       = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION                = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]           = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]         = 0;
  tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]         = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                     = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR       = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                  = 0;
  tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND                = 0;
  tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND        = 0;
  tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER            = 0;
}

void ReadDtcUwbData( uint8 ucDtcNo)
{
  uint8 ucLoop, ucHistId, ucPress;
  sint8 scTemp;
  uint32 ulSysTime;

  Rdci_MILE_KM_Type       ulMileKm;
  Rdci_AIP_ENG_DRV_Type   ucPamb;

  InitDtcUwbData( ucDtcNo);

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000001u) == 0x00000001u)
  {

  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000002u) == 0x00000002u)
  {
    (void) Stub_Rte_Read_MILE_KM( &ulMileKm);
    tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                 = ulMileKm;
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000004u) == 0x00000004u)
  {
    (void) Stub_Rte_Read_T_SEC_COU_REL( &ulSysTime);
    for( ucLoop = 0; ucLoop < 5; ucLoop++)
    {

      tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[ucLoop] = (uint8) (ulSysTime - (uint32) (ulSysTime / 10 * 10) & 0x0F);
      ulSysTime = (uint32) (ulSysTime / 10);

      tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[ucLoop] |= (uint8) ((ulSysTime - (uint32) (ulSysTime / 10 * 10) & 0x0F) << 4);
      ulSysTime = (uint32) (ulSysTime / 10);
    }
    tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] = 0;
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000008u) == 0x00000008u)
  {
    (void) RTE_Stub_UWB_FunktionenReifendruckkontrolle_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000020u) == 0x00000020u)
  {
    (void) RTE_Stub_UWB_RdcAktuelleAussentemperatur_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000040u) == 0x00000040u)
  {

  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000080u) == 0x00000080u)
  {
    tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT          = ucGetSpeed();
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000100u) == 0x00000100u)
  {
    (void) RTE_Stub_UWB_RdcSensorHersteller_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000200u) == 0x00000200u)
  {
    (void) RTE_Stub_UWB_RdcReferenzAussentemperatur_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000400u) == 0x00000400u)
  {
    (void) RTE_Stub_UWB_RdcAussendruck_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00000800u) == 0x00000800u)
  {
    (void) RTE_Stub_UWB_RdcReifendruckVl_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00001000u) == 0x00001000u)
  {
    (void) RTE_Stub_UWB_RdcReifendruckVr_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00002000u) == 0x00002000u)
  {
    (void) RTE_Stub_UWB_RdcReifendruckHl_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00004000u) == 0x00004000u)
  {
    (void) RTE_Stub_UWB_RdcReifendruckHr_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00008000u) == 0x00008000u)
  {
    (void) RTE_Stub_UWB_RdcReifentemperaturVl_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00010000u) == 0x00010000u)
  {
    (void) RTE_Stub_UWB_RdcReifentemperaturVr_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00020000u) == 0x00020000u)
  {
    (void) RTE_Stub_UWB_RdcReifentemperaturHl_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00040000u) == 0x00040000u)
  {
    (void) RTE_Stub_UWB_RdcReifentemperaturHr_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00080000u) == 0x00080000u)
  {
    tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR    = GETscOutdoorTemperatureFZZ();
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00100000u) == 0x00100000u)
  {
    (void) RTE_Stub_UWB_RdcInaktivStatus_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00200000u) == 0x00200000u)
  {
    (void) RTE_Stub_UWB_RdcKalibrierungStatus_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00400000u) == 0x00400000u)
  {
    (void) RTE_Stub_UWB_RdcStatus_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x00800000u) == 0x00800000u)
  {
    (void) RTE_Stub_UWB_RdcKonfiguration_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x01000000u) == 0x01000000u)
  {
    (void) RTE_Stub_UWB_RdcSolldruckVorn_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x02000000u) == 0x02000000u)
  {
    (void) RTE_Stub_UWB_RdcSolldruckHinten_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x04000000u) == 0x04000000u)
  {
    (void) RTE_Stub_UWB_RdcPosition_ReadData( &tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION);
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x08000000u) == 0x08000000u)
  {

  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x10000000u) == 0x10000000u)
  {
    tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                  = ucGetSpeed();
  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x20000000u) == 0x20000000u)
  {

  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x40000000u) == 0x40000000u)
  {

  }

  if( (tRDCiDtclist[ucDtcNo].ulUwbMask & 0x80000000u) == 0x80000000u)
  {

  }
}

static uint8 ucGetRdcSensorHersteller(void)
{
  uint8 i, ucValue;

  i = 0;
  while ((ucGetSuppIdOfColWAL(i) == TAB_RDC_RE_HERSTELLER_HUF) && (i < cMaxLR))
  {
    i++;
  }
  if(i == cMaxLR)
  {
    ucValue = TAB_RDC_RE_HERSTELLER_HUF;
  }
  else
  {
    ucValue = ucGetSuppIdOfColWAL(i);
  }

  if(bGetBitBetriebszustandBZ( cZO_FINISH) == FALSE)
  {
    ucValue |= 0x10;
  }
  else if(bGetBitBetriebszustandBZ( cZWANGSZUORDNUNG) == TRUE)
  {
    ucValue |= 0x10;
  }
  else {}

  return ucValue;
}

static void SaveDTC( uint8 ucDtcNo, ImpTypeRefDem_EventStatusType EventStatus)
{
  if( tRDCiDtclist[ucDtcNo].ucStatus != EventStatus)
  {
    tRDCiDtclist[ucDtcNo].ucStatus = EventStatus;

    if( EventStatus == DEM_EVENT_STATUS_FAILED)
    {
      tRDCiDtclist[ucDtcNo].ucUwbUpdateState = TRUE;

    }else{
      InitDtcUwbData( ucDtcNo);

      WriteDtcListToNvmBlock();
    }

  }
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_TpmsManufactoryModeInfo_GetEventStatus(P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciTpmsManufactoryMode].ucStatus == DEM_EVENT_STATUS_FAILED)
  { *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR; }
  else
  { *EventStatusByte = 0; }
  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_TpmsManufactoryMode_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciTpmsManufactoryMode, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_TpmsManufactoryMode_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciTpmsManufactoryMode, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_1To3WrongWuMountedInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdci1To3WrongWuMounted].ucStatus == DEM_EVENT_STATUS_FAILED)
  { *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT; }
  else
  { *EventStatusByte = 0; }
  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_1To3WrongWuMounted_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdci1To3WrongWuMounted, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_1To3WrongWuMounted_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdci1To3WrongWuMounted, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_4WrongWuMountedInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdci4WrongWuMounted].ucStatus == DEM_EVENT_STATUS_FAILED)
  { *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT; }
  else
  { *EventStatusByte = 0; }
  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_4WrongWuMounted_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdci4WrongWuMounted, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_4WrongWuMounted_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdci4WrongWuMounted, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_AutoLearningFailedInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciAutoLearningFailed].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_AutoLearningFailed_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciAutoLearningFailed, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_AutoLearningFailed_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciAutoLearningFailed, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_GatewayOrAntennaErrorInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciGatewayOrAntennaError].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_GatewayOrAntennaError_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciGatewayOrAntennaError, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_GatewayOrAntennaError_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciGatewayOrAntennaError, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_OtherWuSensorTypeInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciOtherWuSensorType].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_OtherWuSensorType_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciOtherWuSensorType, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_OtherWuSensorType_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciOtherWuSensorType, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RfExternalInterferenceInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRfExternalInterference].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RfExternalInterference_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRfExternalInterference, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RfExternalInterference_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRfExternalInterference, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWfcDefectInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciUnspecifiedWfcDefect].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWfcDefect_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciUnspecifiedWfcDefect, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWfcDefect_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciUnspecifiedWfcDefect, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWuMuteInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciUnspecifiedWuMute].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWuMute_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciUnspecifiedWuMute, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_UnspecifiedWuMute_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciUnspecifiedWuMute, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuDefectFl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuDefectFl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuDefectFl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuDefectFr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuDefectFr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectFr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuDefectFr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuDefectRl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuDefectRl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuDefectRl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuDefectRr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuDefectRr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuDefectRr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuDefectRr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLocalisationFailedInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuLocalisationFailed].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLocalisationFailed_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuLocalisationFailed, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLocalisationFailed_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuLocalisationFailed, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuLowBatteryFl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuLowBatteryFl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuLowBatteryFl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuLowBatteryFr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuLowBatteryFr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryFr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuLowBatteryFr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuLowBatteryRl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuLowBatteryRl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuLowBatteryRl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuLowBatteryRr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuLowBatteryRr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuLowBatteryRr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuLowBatteryRr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuMuteFl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuMuteFl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuMuteFl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuMuteFr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuMuteFr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteFr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuMuteFr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRlInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuMuteRl].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRl_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuMuteRl, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRl_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuMuteRl, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRrInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWuMuteRr].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRr_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWuMuteRr, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WuMuteRr_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWuMuteRr, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempInvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciATempInvalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempInvalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciATempInvalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempInvalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciATempInvalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempTimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciATempTimeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempTimeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciATempTimeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ATempTimeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciATempTimeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehAliveInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciConVehAlive].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehAlive_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciConVehAlive, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehAlive_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciConVehAlive, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehCrcInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciConVehCrc].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehCrc_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciConVehCrc, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehCrc_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciConVehCrc, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehInvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciConVehInvalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehInvalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciConVehInvalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehInvalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciConVehInvalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehTimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciConVehTimeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehTimeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciConVehTimeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ConVehTimeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciConVehTimeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020InvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciEinheitenBn2020Invalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020Invalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciEinheitenBn2020Invalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020Invalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciEinheitenBn2020Invalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020TimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciEinheitenBn2020Timeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020Timeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciEinheitenBn2020Timeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_EinheitenBn2020Timeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciEinheitenBn2020Timeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ErfsCodingDataInconsistentInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciErfsCodingDataInconsistent].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ErfsCodingDataInconsistent_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciErfsCodingDataInconsistent, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_ErfsCodingDataInconsistent_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciErfsCodingDataInconsistent, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1AliveInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRdcDtPckg1Alive].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Alive_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Alive, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Alive_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Alive, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1InvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRdcDtPckg1Invalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Invalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Invalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Invalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Invalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1TimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRdcDtPckg1Timeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Timeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Timeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RdcDtPckg1Timeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRdcDtPckg1Timeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitInvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRelativzeitInvalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitInvalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRelativzeitInvalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitInvalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRelativzeitInvalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitTimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciRelativzeitTimeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitTimeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciRelativzeitTimeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_RelativzeitTimeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciRelativzeitTimeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehAliveFailureInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciVVehAliveFailure].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehAliveFailure_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciVVehAliveFailure, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehAliveFailure_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciVVehAliveFailure, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogInvalidInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciVVehCogInvalid].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogInvalid_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciVVehCogInvalid, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogInvalid_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciVVehCogInvalid, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogQualifierInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciVVehCogQualifier].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogQualifier_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciVVehCogQualifier, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCogQualifier_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciVVehCogQualifier, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCrcFailureInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciVVehCrcFailure].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCrcFailure_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciVVehCrcFailure, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehCrcFailure_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciVVehCrcFailure, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehTimeoutInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciVVehTimeout].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehTimeout_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciVVehTimeout, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_VVehTimeout_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciVVehTimeout, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_KalibrierungInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciKalibrierung].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Kalibrierung_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciKalibrierung, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Kalibrierung_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciKalibrierung, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_AusfallInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciAusfall].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Ausfall_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciAusfall, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Ausfall_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciAusfall, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_PannenwarnungInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciPannenwarnung].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Pannenwarnung_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciPannenwarnung, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Pannenwarnung_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciPannenwarnung, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_PartialSystemAvailabilityInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciPartialSystemAvailability].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_PartialSystemAvailability_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciPartialSystemAvailability, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_PartialSystemAvailability_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciPartialSystemAvailability, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_SystemNotAvailableInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciSystemNotAvailable].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_SystemNotAvailable_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciSystemNotAvailable, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_SystemNotAvailable_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciSystemNotAvailable, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_DruckwarnungInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciDruckwarnung].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Druckwarnung_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciDruckwarnung, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Druckwarnung_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciDruckwarnung, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_BefuellhinweisInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciBefuellhinweis].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Befuellhinweis_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciBefuellhinweis, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Befuellhinweis_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciBefuellhinweis, EventStatus);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_WarnruecknahmeInfo_GetEventStatus( P2VAR(ImpTypeRefDem_UdsStatusByteType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) EventStatusByte)
{
  if(tRDCiDtclist[cDemErrorRdciWarnruecknahme].ucStatus == DEM_EVENT_STATUS_FAILED)
  {
    *EventStatusByte = DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDT | DEM_UDS_STATUS_WIR;
  }
  else
  {
    *EventStatusByte = 0;
  }

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Warnruecknahme_ResetEventStatus(void)
{
  SaveDTC( cDemErrorRdciWarnruecknahme, DEM_EVENT_STATUS_PASSED);

  return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_Dem_Warnruecknahme_SetEventStatus( ImpTypeRefDem_EventStatusType EventStatus)
{
  SaveDTC( cDemErrorRdciWarnruecknahme, EventStatus);

  return E_OK;
}
