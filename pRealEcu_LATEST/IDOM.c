#include "Std_Types.hpp"

#include "Tpms_Rte_Data_Type.hpp"
#include "IDOM_IF.hpp"
#include "CfgSwcApplTpms_IDOM.hpp"
#include "IDOM_X.hpp"

#define ucDynOffsCalc (uint8) 0x80U
#define ucTimeBreakc (uint8) 0x10U
#define ucRFinTimec (unsigned char) 0x08
#define ucRFintEVsetc (unsigned char) 0x04
#define ucRFintNFFc (unsigned char) 0x02
#define ucRFintc (unsigned char) 0x01
#define ushMaxOLCtc ((unsigned short)600)
#define ushMaxULCtc ((unsigned short)600)

static uint8 ucIDOMState;
static uint16 ushOffset = 0;
static uint16 ushOLCt =  0;

uint8 GETucOffset(void){
   return ((uint8)(0x00FF & (ushOffset)));
}

void IDOM(void){
   tIDOMInput tInput;
   tInput.ushCurBaseLevel = 0;
   tInput.ucApplState = 0;
   tInput.ushMaxFFCtVal = 0;
   GetIDOMInput(
      &tInput);
   if(tInput.ushCurBaseLevel > 0){
      if((ucIDOMState & ucDynOffsCalc ) > 0){
         if(tInput.ushCurBaseLevel < ushOffset){
            ushOffset = (ushOffset / 2) + (tInput.ushCurBaseLevel / 2);
         }
      }
   }
   switch(ucIDOMState & (ucRFintc | ucRFintNFFc | ucTimeBreakc | ucRFinTimec )){
      case 0:
         if(tInput.ushCurBaseLevel > (ushOffset + GetParaOverlaps())){
            if(tInput.ucApplState > (unsigned char)0){
               ushOLCt++;
               if(ushOLCt > ushMaxOLCtc){
                  ucIDOMState |= ucRFintc;
                  ushOLCt = ushMaxULCtc;
               }
            }
         }
         else{
            ushOLCt = (unsigned char)0;
         }
         StopIDOMAlarm();
         break;
      case ucRFintc :
         if(tInput.ushCurBaseLevel > (ushOffset + GetParaOverlaps())){
            ushOLCt = ushMaxULCtc;
            if(tInput.ushMaxFFCtVal >= ucMaxFF4RFInterference){
               ushOLCt = 0;
               ucIDOMState |= ucRFintNFFc;
               StartIDOMAlarm(
                  tInput.ushMaxFFCtVal);
            }
         }
         else{
            if((unsigned char)0 == ushOLCt){
               ucIDOMState &= ~ucRFintc;
            }
            else{
               ushOLCt--;
            }
         }
         break;
      case (ucRFintc | ucRFintNFFc ):
         if(tInput.ushMaxFFCtVal < ucMaxFF4RFInterference){
            ucIDOMState &= ~(ucRFintc | ucRFintNFFc );
         }
         else{
            if(tInput.ucApplState == (unsigned char)0){
               ucIDOMState |= ucTimeBreakc;
               BreakIDOMAlarm();
            }
         }
         break;
      case (ucRFintc | ucRFintNFFc | ucRFinTimec ):
         if(tInput.ushMaxFFCtVal < ucMaxFF4RFInterference){
            ucIDOMState &= ~(ucRFintc | ucRFintNFFc | ucRFinTimec );
            StopIDOMAlarm();
         }
         break;
      case (ucRFintc | ucRFintNFFc | ucTimeBreakc ):
         if(tInput.ucApplState > (uint8)0){
            ucIDOMState &= ~ucTimeBreakc;
            StartIDOMAlarm(
               (uint16)0);
         }
         break;
      default:
         ucIDOMState &= ~(ucRFintc | ucRFintNFFc | ucTimeBreakc | ucRFinTimec );
         break;
   }
}

void InitIDOM(void){
   ucIDOMState = 0;
   ushOffset = GetParaOffset();
   ushOLCt = 0;
   if(ushOffset > 0U){
      ucIDOMState &= ~ucDynOffsCalc;
   }
   else{
      ucIDOMState |= ucDynOffsCalc;
      ushOffset = (uint16) ucDefOffsetInRSSIc;
   }
   StopIDOMAlarm();
}

boolean GETbStoersenderFf(void){
   return ((boolean)(ucRFintNFFc == (ucIDOMState & ucRFintNFFc )));
}

boolean GETbStoersenderZeit(void){
   return ((boolean)(ucRFinTimec == (ucIDOMState & ucRFinTimec )));
}

void SetRFinTime(void){
   ucIDOMState |= ucRFinTimec;
}

