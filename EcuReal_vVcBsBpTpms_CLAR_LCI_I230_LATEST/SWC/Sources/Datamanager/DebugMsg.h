

#ifndef _debugmsg_H
#define _debugmsg_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "DebugMsgX.h"

#define EV_SPEC_DATA_SIZE  39
#define START_MPX_ID_SYS_SPEC_DATA  2

#define NO_OF_EV_SPEC_DATASETS 15

#define TRANSMIT_EVENT_SPEC_DATA  (uint8)0
#define TRANSMIT_SYS_SPEC_DATA    (uint8)1
#define REPEAT_EVENT_SPEC_DATA    (uint8)2

#define SPEC_NORM   0
#define SPEC_MIRR   1

#define cNoDataAvailable      0x00
#define cDataAvailable        0x01

static uint8 CreateSetOfEventSpecificData16DBG( ImpTypeRecCddRdcData rdcData);

static uint8 CreateSetOfEventSpecificData32DBG( const ImpTypeRecCddRdcData* rdcData);

static uint8 ucSelectNextEventSpecificDataSetDBG(void);

static void GetNextEventSpecificDataBlock32DBG(uint8* pucBuffer, uint8* ucMuxID, uint8* ucTransmitState);

static uint8 GetNextSystemSpecificDataBlockDBG(Rte_Instance self, uint8* pucBuffer);

static uint8 GetNextSystemSpecificDataBlock16DBG(uint8* pucBuffer);

static uint8 GetNextSystemSpecificDataBlock32DBG(Rte_Instance self, uint8* pucBuffer);

#ifdef __cplusplus
}
#endif

#endif
