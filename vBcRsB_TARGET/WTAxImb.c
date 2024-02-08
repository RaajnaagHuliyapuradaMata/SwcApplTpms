#include "Std_Types.hpp"

#include "Tpms_Rte_Data_Type.hpp"
#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"
#include "statemanager.hpp"
#include "statisticsX.hpp"
#include "state_bzX.hpp"

static uint8 aucIsoPresMemory[ucSumWEc ];
static uint16 ushAxImbSuppresionCounter;
static boolean bAxImbSuppresionCounter_Started;
static boolean timerExpired;

#define U16_CNT_MAX_VAL ((uint16)600)
#define U8_MIN_NB_OF_RxTelInCurentState_FOR_AX_IMB      ((uint8)10)

void Init_AxImbSuppressionCounter(
   void){
   ushAxImbSuppresionCounter = 0;
   bAxImbSuppresionCounter_Started = FALSE;
   timerExpired = FALSE;
}

void Start_AxImbSuppressionCounter(
   void){
   bAxImbSuppresionCounter_Started = TRUE;
}

void Increment_AxImbSuppressionCounter(
   void){
   if((bAxImbSuppresionCounter_Started == TRUE) && (timerExpired != TRUE)){
      if(ushAxImbSuppresionCounter < U16_CNT_MAX_VAL){
         ushAxImbSuppresionCounter++;
      }
      else{
         timerExpired = TRUE;
      }
   }
}

