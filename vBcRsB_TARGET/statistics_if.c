#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "statistics_if.hpp"
#include "statemanagerX.hpp"
#include "wallocX.hpp"
#include "IDOM_X.hpp"
#include "REDiagX.hpp"
#include "State_FzzX.hpp"
#include "REDiag_if.hpp"

#define FIRST_30SEC_NOT_PASSED   30U

void SetRecCounterInEE(
   uint16 ushValue,
   uint8 ucSlot){
   PUTushGutEmpfCntEE(
      ushValue,
      ucSlot);
}

void SetMissCounterInEE(
   uint16 ushValue,
   uint8 ucSlot){
   PUTushMissedCntEE(
      ushValue,
      ucSlot);
}

void SetFailCounterInEE(
   uint16 ucValue,
   uint8 ucSlot){
   PUTusFolgeAusfallCntEE(
      ucValue,
      ucSlot);
}

uint16 GetRecCounterInEE(
   uint8 ucSlot){
   return (GETushGutEmpfCntEE(
      ucSlot));
}

uint16 GetMissCounterInEE(
   uint8 ucSlot){
   return (GETushMissedCntEE(
      ucSlot));
}

uint16 GetFailCounterInEE(
   uint8 ucSlot){
   return (GETusFolgeAusfallCntEE(
      ucSlot));
}

boolean CarIsDriving(
   void){
   return (bGetBitFahrzeugzustandFZZ(
      cFAHRZEUG_FAEHRT) == TRUE);
}

boolean ReDiagActive(
   void){
   return (bGetBitFahrzeugzustandFZZ(
      cRS_VTHRES) == TRUE);
}

boolean RfInterferenceActive(
   void){
   return (GETbStoersenderFf());
}

boolean CheckWUFDErr(
   uint16 CounterValue,
   uint8 ucIx){
   boolean bError = FALSE;
   if(CounterValue < FIRST_30SEC_NOT_PASSED){
      ResetWUFailedErrRD(
         ucIx);
   }
   else{
      bError = SetWUFailedErrRD(
         CounterValue,
         ucIx);
   }
   return (bError);
}
