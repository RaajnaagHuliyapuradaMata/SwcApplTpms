/******************************************************************************/
/* File   : FBD_Manager.c                                                     */
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
#include "FBD_ManagerX.h"

#include "WAllocX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cFbdDataAllocDelay  10

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
static uint8 ucAllocationDelay = 0xFF;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void GetDataFBD(uint8 ucPos, uint32* pulTyreId, uint8* pucSuppId){
   uint32 ulId;
   uint8 ucSlot;
   ucSlot = ucGetColOfWP(ucPos);
   if(ucSlot < cMaxLR){
      ulId = (uint32) ulGetIDOfColWAL(ucSlot);
    *pulTyreId = (uint32) (ulId & 0x0FFFFFFFul);
    *pucSuppId = (uint8)  ((ulId & 0xF0000000ul) >> 28);
   }
}

void PmStartDataAllocTimerFBD(void){
   if(0xFF == ucAllocationDelay){
      ucAllocationDelay = cFbdDataAllocDelay;
   }
}

void PmStopDataAllocTimerFBD(void){
   ucAllocationDelay = 0x00;
}

uint8 PmDataAllocTimerTickFBD(void){
   uint8 ucRetVal = 0xff;
   if((ucAllocationDelay > 0) && (0xFF != ucAllocationDelay)){
      ucAllocationDelay--;
      ucRetVal = ucAllocationDelay;
   }
   return ucRetVal;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

