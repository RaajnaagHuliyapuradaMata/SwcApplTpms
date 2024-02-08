

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_DTC_If.hpp"
#include "statisticsX.hpp"
#include "REDiagX.hpp"
#include "WallocX.hpp"
#include "statemanagerX.hpp"
#include "SwcApplTpms_NvM_If.hpp"

#define BITS_IN_BYTE  8U
#define DTC_ARRAY_SIZE ((uint8) (((E_TPMS_ERROR_MAX_NUMBER - 1)/BITS_IN_BYTE) + 1))

uint8 DTC_IsDTCInActiveState[DTC_ARRAY_SIZE];

uint8 DTC_StatusOfDTC;

void Init_DTC(void);
void SetCurrentErrorERR(uint8 ucCurrentExtErrorIndex);
void ResetCurrentErrorERR(uint8 ucCurrentExtErrorIndex);
void DeleteCurrentErrorERR(uint8 ucCurrentExtErrorIndex);

void DTC_SaveActiveStatustoEE(void){
  NvM2_PutDTCSingleActiveStatusEE(DTC_IsDTCInActiveState);
  NvM2_PutDiagUsedToDeleteDTCEE(DTC_StatusOfDTC);
}

void DTC_RestoreActiveStatusfromEE(void){
  NvM2_GetDTCSingleActiveStatusCEE(DTC_IsDTCInActiveState);
  DTC_StatusOfDTC = NvM2_GetDiagUsedToDeleteDTCEE();
}

boolean DTC_GetActiveStatusOfDTC(uint8 u8DTCNumber)
{
  uint8 u8ByteValue;
  uint8 u8BitFromCurrentByte;
  uint8 bLocalActiveStatus = FALSE;

  if(u8DTCNumber == 0)
  {
   u8ByteValue = 0;
   u8BitFromCurrentByte = 0;
  }
  else{
   u8ByteValue = u8DTCNumber / BITS_IN_BYTE;
   u8BitFromCurrentByte = (u8DTCNumber % BITS_IN_BYTE);
  }

  bLocalActiveStatus = ( TRUE  & (DTC_IsDTCInActiveState[u8ByteValue] >> u8BitFromCurrentByte) );

  return bLocalActiveStatus;
}

void DTC_SetDTCActiveStatus(uint8 u8DTCToSet)
{
  uint8 u8ByteValue;
  uint8 u8BitFromCurrentByte;
  if(u8DTCToSet == 0)
  {
   u8ByteValue = 0;
   u8BitFromCurrentByte = 0;
  }
  else{
   u8ByteValue = u8DTCToSet / BITS_IN_BYTE;
   u8BitFromCurrentByte = (u8DTCToSet % BITS_IN_BYTE);
  }

  DTC_IsDTCInActiveState[u8ByteValue] = (DTC_IsDTCInActiveState[u8ByteValue] | (uint8)(0x01 << u8BitFromCurrentByte));
}

void DTC_DeleteDTCActiveStatus(uint8 u8DTCToDelete)
{
  uint8 u8ByteValue;
  uint8 u8BitFromCurrentByte;
  if(u8DTCToDelete == 0)
  {
   u8ByteValue = 0;
   u8BitFromCurrentByte = 0;
  }
  else{
   u8ByteValue = (uint8)(u8DTCToDelete / BITS_IN_BYTE);
   u8BitFromCurrentByte = (uint8)(u8DTCToDelete % BITS_IN_BYTE);
  }
  DTC_IsDTCInActiveState[u8ByteValue] = (DTC_IsDTCInActiveState[u8ByteValue] & (uint8)((uint8)(0x01 << u8BitFromCurrentByte) ^ 0xFF));
}

void Init_DTC(void){
}

void SetCurrentErrorERR(uint8 ucCurrentExtErrorIndex)
{
  enum_TPMSErrorType enErrorType = E_TPMS_ERROR_MAX_NUMBER;

  enErrorType = (enum_TPMSErrorType)ucCurrentExtErrorIndex;

  if( enErrorType < E_TPMS_ERROR_MAX_NUMBER )
  {
   ClientIf_SetCurrentErrorERR(enErrorType);
    DTC_SetDTCActiveStatus(enErrorType);
    DTC_StatusOfDTC |= cDTC_STATE_CHANGED;
  }
  else{

  }
}

void ResetCurrentErrorERR(uint8 ucCurrentExtErrorIndex)
{
  enum_TPMSErrorType enErrorType = E_TPMS_ERROR_MAX_NUMBER;

  enErrorType = (enum_TPMSErrorType)ucCurrentExtErrorIndex;

  if( enErrorType < E_TPMS_ERROR_MAX_NUMBER )
  {
   ClientIf_ResetCurrentErrorERR(enErrorType);
  }
  else{

  }
}

void DeleteCurrentErrorERR(uint8 ucCurrentExtErrorIndex)
{
  enum_TPMSErrorType enErrorType = E_TPMS_ERROR_MAX_NUMBER;

  enErrorType = (enum_TPMSErrorType)ucCurrentExtErrorIndex;

  if( enErrorType < E_TPMS_ERROR_MAX_NUMBER )
  {
   ClientIf_DeleteCurrentErrorERR(enErrorType);
    DTC_DeleteDTCActiveStatus(enErrorType);
    DTC_StatusOfDTC |= cDTC_STATE_CHANGED;
  }
  else{

  }
}

void HufIf_GetStatusErrorERR(uint8 eErrorType)  // function parameter not needed for the moment
{
  DTC_StatusOfDTC |= cDTC_WAS_DELETED_TROUGH_DIAG;
  DTC_DeleteDTCActiveStatus(eErrorType);

  switch(eErrorType)
  {
   case E_TPMS_ERROR_AUTOLOCATION_FAILED:
        NvM3_PUTucAutolocationFailedCounter(ucDefAutolocationFailedCounterInit);
        break;
    default:

  }
//  NvM2_PutDiagUsedToDeleteDTCEE(cDTC_WAS_DELETED_TROUGH_DIAG);
// NOTE!  Don't need the reset of counters, when a DTC is deleted, this should be reset imediatly until it will be
// cleared by returning condition.
// This is from specification for DTC received by SYMC.
//  InitSTATISTICS();
//  SM_ResetStatusForSpeedValueInUse(); //reset counter for substitute speed signal in use
//  ResetAllocErrorCnt();
//  ResetNrOfTOs(); //reset WATO couter to prevent direct setting of allocation DTCs
//
//  for(LocalLoop = 0; LocalLoop < cAnzRad ; LocalLoop++)
//  {
//    ResetWUDefectRD(LocalLoop);
//    ResetWULowLifeTimeRD(LocalLoop);
//    ResetWUHighTempRD(LocalLoop);
//  }
}

