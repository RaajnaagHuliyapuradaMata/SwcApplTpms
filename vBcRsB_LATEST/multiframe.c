/******************************************************************************/
/* File   : multiframe.c                                                      */
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

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "multiframe.hpp"
#include "multiframeX.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void  InitOneSlotMF (uint8  ucSlot);
static uint8 ucSearchIdMF  (uint32 ulReID);

static void InitOneSlotMF(uint8 ucSlot){
   if(ucSlot < cMF_MAX_SLOT){
      tMultiFrameMF[ucSlot].ulReId = (uint32)0;
      tMultiFrameMF[ucSlot].ucLockTimeCounter = 0;
      tMultiFrameMF[ucSlot].ucFrameCounter = 0;
      tMultiFrameMF[ucSlot].ucTGCounter = 0;
   }
}

void TimeMF(void){
   uint8 ucSlot;
   for(ucSlot = 0; ucSlot < cMF_MAX_SLOT; ucSlot++){
      if(tMultiFrameMF[ucSlot].ucLockTimeCounter > 0){
         tMultiFrameMF[ucSlot].ucLockTimeCounter--;
      }
   }
}

uint8 ucCheckForMultiFrameMF(
   uint32 ulReID,
   uint8  ucTGCounter,
   uint8  u8MaxTimeFilter
){
   uint8  ucSlot;
   uint8  ucRet = cFT_MULTI_FRAME;
   ucSlot = ucSearchIdMF(ulReID);
   if(ucSlot < cMF_MAX_SLOT){
      if(
            (tMultiFrameMF[ucSlot].ucLockTimeCounter == 0)
         || (
                  (ucTGCounter != 0)
               && (tMultiFrameMF[ucSlot].ucTGCounter != ucTGCounter)
            )
      ){
         InitOneSlotMF(ucSlot);
         tMultiFrameMF[ucSlot].ucLockTimeCounter = u8MaxTimeFilter;
         tMultiFrameMF[ucSlot].ucFrameCounter++;
         tMultiFrameMF[ucSlot].ulReId = ulReID;
         tMultiFrameMF[ucSlot].ucTGCounter = ucTGCounter;
         ucRet = cFT_SINGLE_FRAME;
      }
      else{
         if(
               (tMultiFrameMF[ucSlot].ucFrameCounter < cMF_MAX_FRAMES)
            || (
                     (ucTGCounter != 0)
                  && (tMultiFrameMF[ucSlot].ucTGCounter == ucTGCounter)
               )
         ){
            tMultiFrameMF[ucSlot].ucFrameCounter++;
            ucRet = cFT_MULTI_FRAME;
         }
         else{
            ucRet = cFT_SINGLE_FRAME;
         }
      }
   }
   else{
      ucRet = cFT_SINGLE_FRAME;
   }
   return ucRet;
}

static uint8 ucSearchIdMF(uint32 ulReID){
   uint8 ucSlot;
   uint8 ucFreeSlot = cMF_MAX_SLOT;
   uint8 ucFreeSlotNoId = cMF_MAX_SLOT;
   uint8 ucRet = cMF_MAX_SLOT;
   for(
      ucSlot = 0;
      ((ucSlot < cMF_MAX_SLOT) && (ucRet == cMF_MAX_SLOT));
      ucSlot++
   ){
      if(tMultiFrameMF[ucSlot].ulReId == ulReID){
         ucRet = ucSlot;
      }
      else{
         if(tMultiFrameMF[ucSlot].ulReId == 0){
            if(ucFreeSlotNoId == cMF_MAX_SLOT){
               ucFreeSlotNoId = ucSlot;
            }
         }
         if(tMultiFrameMF[ucSlot].ucLockTimeCounter == 0){
            if(ucFreeSlot == cMF_MAX_SLOT){
               ucFreeSlot = ucSlot;
            }
         }
      }
   }
   if(ucRet == cMF_MAX_SLOT){
      if(ucFreeSlotNoId < cMF_MAX_SLOT){
         ucRet = ucFreeSlotNoId;
      }
      else{
         if(ucFreeSlot < cMF_MAX_SLOT){
            ucRet = ucFreeSlot;
         }
      }
   }
   return ucRet;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

