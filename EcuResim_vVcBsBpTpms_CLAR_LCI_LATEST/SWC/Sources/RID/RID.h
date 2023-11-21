

#ifndef _rid_H
#define _rid_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "RID_X.h"

static void ConvertReDimToErfsCoding( uint8* pRidData);
static uint8 ConvertSpeedIndex( const uint8 ucIndexValue);
static uint8 SearchRIDBufSlot( const uint32 ReId);
static void SaveHistReRidDataRID( Rte_Instance self, const uint8 HisIx, const uint8 ZOMIx);
static void RestoreSavedReRidDataRID( Rte_Instance self, const uint8 HisIx);
static boolean CheckRidDataRID( Rte_Instance self, const uint8 Col1, const uint8 Col2, const uint8 Axis);
static uint8 CheckAxisRidDataRID( Rte_Instance self, uint8* pResData, const uint8 Axis);
static uint8 CompareHistReDimBufRID( uint8 Ix1, uint8 Ix2, uint8* pResData);
static boolean CompareSavedRidDataRID( const uint8 Col);
static void ResetTyreDOTOEDataOfReIdRID(const uint32 l_ulID);
static void ResetTyreDimDataOfReIdRID(const uint32 l_ulID);

#ifdef __cplusplus
}
#endif

#endif
