/******************************************************************************/
/* File   : IDOM.c                                                            */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Tpms_Rte_Data_Type.hpp"
#include "IDOM_IF.hpp"
#include "CfgSwcApplTpms_IDOM.hpp"
#include "IDOM_X.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucDynOffsCalc                                           ((uint8)  0x80U)
#define ucTimeBreakc                                            ((uint8)  0x10U)
#define ucRFinTimec                                             ((uint8)  0x08U)
#define ucRFintEVsetc                                           ((uint8)  0x04U)
#define ucRFintNFFc                                             ((uint8)  0x02U)
#define ucRFintc                                                ((uint8)  0x01U)
#define ushMaxOLCtc                                             ((uint16)   600)
#define ushMaxULCtc                                             ((uint16)   600)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static uint8  ucIDOMState;
static uint16 ushOffset = 0;
static uint16 ushOLCt   = 0;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
uint8 GETucOffset(void){
   return ((uint8)(0x00FF & (ushOffset)));
}

void IDOM(void){
   tIDOMInput tInput;
   tInput.u16CurBaseLevel = 0;
   tInput.u8ApplState = 0;
   tInput.u16MaxFFCtVal = 0;
   GetIDOMInput(
      &tInput);
   if(tInput.u16CurBaseLevel > 0){
      if((ucIDOMState & ucDynOffsCalc ) > 0){
         if(tInput.u16CurBaseLevel < ushOffset){
            ushOffset = (ushOffset / 2) + (tInput.u16CurBaseLevel / 2);
         }
      }
   }
   switch(ucIDOMState & (ucRFintc | ucRFintNFFc | ucTimeBreakc | ucRFinTimec )){
      case 0:
         if(tInput.u16CurBaseLevel > (ushOffset + GetParaOverlaps())){
            if(tInput.u8ApplState > (unsigned char)0){
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
         if(tInput.u16CurBaseLevel > (ushOffset + GetParaOverlaps())){
            ushOLCt = ushMaxULCtc;
            if(tInput.u16MaxFFCtVal >= ucMaxFF4RFInterference){
               ushOLCt = 0;
               ucIDOMState |= ucRFintNFFc;
               StartIDOMAlarm(
                  tInput.u16MaxFFCtVal);
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
         if(tInput.u16MaxFFCtVal < ucMaxFF4RFInterference){
            ucIDOMState &= ~(ucRFintc | ucRFintNFFc );
         }
         else{
            if(tInput.u8ApplState == (unsigned char)0){
               ucIDOMState |= ucTimeBreakc;
               BreakIDOMAlarm();
            }
         }
         break;
      case (ucRFintc | ucRFintNFFc | ucRFinTimec ):
         if(tInput.u16MaxFFCtVal < ucMaxFF4RFInterference){
            ucIDOMState &= ~(ucRFintc | ucRFintNFFc | ucRFinTimec );
            StopIDOMAlarm();
         }
         break;
      case (ucRFintc | ucRFintNFFc | ucTimeBreakc ):
         if(tInput.u8ApplState > (uint8)0){
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

