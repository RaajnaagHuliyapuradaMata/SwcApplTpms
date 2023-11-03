

#ifndef _RTE_STUB_CCM_X_H
#define _RTE_STUB_CCM_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#define CC_DATA_QUEUE_LENGTH 5

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Send_Ccm( P2CONST(ImpTypeRecCcm_DISP_CC_BYPA_00, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA));

extern uint8 Stub_GetCcmData( ImpTypeRecCcm_DISP_CC_BYPA_00 *);

#ifdef __cplusplus
}
#endif

#endif
