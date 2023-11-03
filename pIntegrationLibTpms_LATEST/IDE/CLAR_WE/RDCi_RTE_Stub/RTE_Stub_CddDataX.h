

#ifndef _RTE_STUB_CDDDATA_X_H
#define _RTE_STUB_CDDDATA_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#define cMaxReElements  7

#define cRecEleIx_Slot0 0
#define cRecEleIx_Slot1 1
#define cRecEleIx_Slot2 2
#define cRecEleIx_Slot3 3
#define cRecEleIx_FR    4
#define cRecEleIx_RID   5
#define cRecEleIx_Alive 6

typedef struct{
  ImpTypeRecCddRdcData  tRecCddRdcData;

  uint16                ushPabs_iso_hPa;
  sint16                sshTabs_iso_K;

  uint16                ushPlast_rel_hPa;
  sint16                sshTlast_celsius;

  boolean               bAliveError;
  boolean               bInputIsochor;
  boolean               bBatteryEmpty;

  boolean               bTyrIdFromFile;
  boolean               bSuppIdFromFile;
  boolean               bPckgIdFromFile;
  boolean               bDt1PressureFromFile;
  boolean               bDt2TemperatureFromFile;
  boolean               bWuDataFromFile;
}RdcDataType;

extern void PutTimerTicks( uint32 ulTimerTicks);

extern uint32 ulGetTimerTicks(void);

extern uint32 ulGetTRdcRfWriteCounter(void);

extern uint32 ulGetTRdcRfReadCounter(void);

extern void InitRecCddRdcData(void);

extern ImpTypeRecCddRdcData * ptGetRecCddRdcDataPtr( uint8 ucIx);

extern RdcDataType * ptGetRdcDataPtr(uint8 ucRe);

extern void PutRecCddRdcData( uint8 ucRe);

extern uint16 ushGetTelCountCddRdcDataPtr( uint8 ucRe);

extern uint8 ucGetNextValidAliveCounter( uint8 ucAliveStartValue);

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Receive_CddAbsData(P2VAR(ImpTypeRecCddAbsData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));
FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Receive_CddRdcData( P2VAR(ImpTypeRecCddRdcData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR));

#ifdef __cplusplus
}
#endif

#endif
