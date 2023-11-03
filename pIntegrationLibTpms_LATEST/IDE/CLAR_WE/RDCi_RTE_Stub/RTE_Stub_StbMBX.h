

#ifndef _RTE_STUB_STBMB_X_H
#define _RTE_STUB_STBMB_X_H

#ifdef __cplusplus
extern "C"
{
#endif

extern void PutStbMBTime(StbMB_SystemTimeType *);
extern void PutStbMBSyncState(StbMB_SyncStatusType *);

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetAbsoluteTime( P2VAR(StbMB_SystemTimeType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetGlobalTime( P2VAR(StbMB_TickType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetSyncState( P2VAR(StbMB_SyncStatusType, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Call_StbMB_GetTickDuration( P2VAR(uint32, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));

#ifdef __cplusplus
}
#endif

#endif
