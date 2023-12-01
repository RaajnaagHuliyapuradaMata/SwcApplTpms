#ifndef _rdctsaservices_H
#define _rdctsaservices_H

# ifdef __cplusplus
extern "C"
{
# endif

#include "RdcTsaServicesX.h"

static uint8 CompareTyreSerNumRID(Rte_Instance self, uint8 HisIx);
static void SetTyreRuntimeDataDS(Rte_Instance self, const uint8* OldMountIx);
static void SaveRuntimeDataInEE(Rte_Instance self, const uint8 Ix, const uint8 StartIx, const uint8* Buffer, const uint8 Size);
static void GetLatestUnmountedQrDataEntries(Rte_Instance self, uint8* pUnmountEntryIndex);
static void SearchOldestUnmountEntryIndex(Rte_Instance self, uint8* pEntryIx, const uint8* OldMountIx);

#ifdef __cplusplus
}
#endif

#endif

