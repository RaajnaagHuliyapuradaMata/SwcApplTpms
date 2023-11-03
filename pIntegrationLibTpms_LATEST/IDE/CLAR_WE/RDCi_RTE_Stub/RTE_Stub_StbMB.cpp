

#include "RTE_Stub_StbMB.h"

StbMB_SystemTimeType      sysTime;
StbMB_SyncStatusType      sysTimeSyncState = STBM_STATE_NOT_SYNC;

 void PutStbMBTime(StbMB_SystemTimeType* data)
 {
   sysTime = *data;

 }

 void PutStbMBSyncState(StbMB_SyncStatusType* data)
 {
   sysTimeSyncState = *data;
 }

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetAbsoluteTime( P2VAR(StbMB_SystemTimeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) systemTime)
{
  *systemTime = sysTime;
  return 0;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetGlobalTime( P2VAR(StbMB_TickType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) ticks)
{
  *ticks = sysTime.ticks;
  return 0;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetSyncState( P2VAR(StbMB_SyncStatusType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) syncState)
{
  *syncState = sysTimeSyncState;
  return 0;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetTickDuration( P2VAR(uint32, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) tickDuration)
{
  *tickDuration = sysTime.tickDuration;
  return 0;
}
