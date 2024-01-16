/******************************************************************************/
/* File   : WTAxImb.c                                                         */
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
#include "global.hpp"
#include "uswarn.hpp"
#include "WnTypePar.hpp"
#include "uswarn_ifx.hpp"
#include "statemanager.hpp"
#include "statisticsX.hpp"
#include "state_bzX.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define U16_CNT_MAX_VAL                                           ((uint16) 600)
#define U8_MIN_NB_OF_RxTelInCurentState_FOR_AX_IMB                ((uint8)   10)

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
static uint8   aucIsoPresMemory[ucSumWEc];
static uint16  ushAxImbSuppresionCounter;
static boolean bAxImbSuppresionCounter_Started;
static boolean timerExpired;


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

