/******************************************************************************/
/* File   : StatusReLesenDruckcodierung.c                                     */
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
#include "StatusReLesenDruckcodierungX.h"
#include "WAllocX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cRecCounterDefaultVal                         ((uint8)  0xff)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint32 ulReID;
   uint8  ucPres;
   uint8  ucBatt;
   uint8  ucRecCounter;
}StatusReLesenDruckcodierungDataType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static StatusReLesenDruckcodierungDataType tStatusReLesenDruckcodierungData[cStatusReLesenDruckcodierungDataArraySize] = {
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u },
   { 0u, 0u, 0u, 0u }
};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitStatusReLesenDruckcodierungDS(void){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cStatusReLesenDruckcodierungDataArraySize; ucLoop++){
    tStatusReLesenDruckcodierungData[ucLoop].ucPres       = 0u;
    tStatusReLesenDruckcodierungData[ucLoop].ucBatt       = 0u;
    tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter = 0u;
      if(ucLoop < cAnzRad){
      tStatusReLesenDruckcodierungData[ucLoop].ulReID     = ulGetIDOfColWAL(ucLoop);
      }
      else{
      tStatusReLesenDruckcodierungData[ucLoop].ulReID     = cInvalidREid;
      }
   }
}

void PutStatusReLesenDruckcodierungDataDS(uint32 ulId, uint8 ucPres, uint8 ucPresState, uint8 ucBatt)
{
   uint8   ucLoop;
   boolean bBreakLoop = FALSE;

   for(ucLoop = 0; ((ucLoop < cStatusReLesenDruckcodierungDataArraySize) && (bBreakLoop == FALSE)); ucLoop++){
      if(tStatusReLesenDruckcodierungData[ucLoop].ulReID == ulId){
      if(ucPresState == cPresSensorUnderflow){
        tStatusReLesenDruckcodierungData[ucLoop].ucPres = cInvalidREpressure;
      }
      else{
        tStatusReLesenDruckcodierungData[ucLoop].ucPres = ucPres;
      }

      tStatusReLesenDruckcodierungData[ucLoop].ucBatt = ucBatt;

      if(tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter < 254u){
        tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter++;
      }
      else{
        tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter = 1;
      }

      bBreakLoop = TRUE;
      }else if(tStatusReLesenDruckcodierungData[ucLoop].ulReID == cInvalidREid){
      tStatusReLesenDruckcodierungData[ucLoop].ulReID       = ulId;
      if(ucPresState == cPresSensorUnderflow){
        tStatusReLesenDruckcodierungData[ucLoop].ucPres = cInvalidREpressure;
      }
      else{
        tStatusReLesenDruckcodierungData[ucLoop].ucPres = ucPres;
      }
      tStatusReLesenDruckcodierungData[ucLoop].ucBatt       = ucBatt;
      tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter = 1;
      bBreakLoop = TRUE;
      }
      else{
      }
   }
}

void GetStatusReLesenDruckcodierungDS(uint8* pucData)
{
   uint8 ucLoop;

   for(ucLoop = 0; ucLoop < cStatusReLesenDruckcodierungDataArraySize; ucLoop++){
    pucData[(ucLoop * 9) + 0] = (uint8) ((tStatusReLesenDruckcodierungData[ucLoop].ulReID >> 24) & 0x000000ff);
    pucData[(ucLoop * 9) + 1] = (uint8) ((tStatusReLesenDruckcodierungData[ucLoop].ulReID >> 16) & 0x000000ff);
    pucData[(ucLoop * 9) + 2] = (uint8) ((tStatusReLesenDruckcodierungData[ucLoop].ulReID >>  8) & 0x000000ff);
    pucData[(ucLoop * 9) + 3] = (uint8) ((tStatusReLesenDruckcodierungData[ucLoop].ulReID >>  0) & 0x000000ff);

      if(tStatusReLesenDruckcodierungData[ucLoop].ucPres == cInvalidREpressure){
      pucData[(ucLoop * 9) + 4] = 0xffu;
      pucData[(ucLoop * 9) + 5] = 0xffu;
      }
      else{
      pucData[(ucLoop * 9) + 4] = (uint8) ((((uint16) tStatusReLesenDruckcodierungData[ucLoop].ucPres * 25) >> 8) & 0x00FFu);
      pucData[(ucLoop * 9) + 5] = (uint8) ((((uint16) tStatusReLesenDruckcodierungData[ucLoop].ucPres * 25) >> 0) & 0x00FFu);
      }

      if(tStatusReLesenDruckcodierungData[ucLoop].ucBatt == cInvalidBatteryLevel){
      pucData[(ucLoop * 9) + 6] = 0xffu;
      pucData[(ucLoop * 9) + 7] = 0xffu;
      }
      else{
      pucData[(ucLoop * 9) + 6] = (uint8) 0x00;
      pucData[(ucLoop * 9) + 7] = tStatusReLesenDruckcodierungData[ucLoop].ucBatt;
      }

    pucData[(ucLoop * 9) + 8] = tStatusReLesenDruckcodierungData[ucLoop].ucRecCounter;
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

