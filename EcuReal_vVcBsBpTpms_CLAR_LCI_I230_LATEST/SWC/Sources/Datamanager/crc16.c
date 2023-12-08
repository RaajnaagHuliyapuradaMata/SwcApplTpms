/******************************************************************************/
/* File   : crc16.c                                                           */
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
#include "crc16.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cPOLY_16Bit 0x1021U
#define cPOLY_8Bit  0x2Fu

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
static uint16 ushCrc16;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
uint16 ushCalcCrc16( const uint8 *pucBuffer, uint16 ushLength)
{
   uint16 ushCount = 0;

   ushCrc16 = 0xffffU;

  while (ushCount < ushLength){
      updateCRC16(pucBuffer[ushCount]);
      ushCount++;
   }

   return ushCrc16;
}

static void updateCRC16(uint8 newByte)
{
      uint16 i;
      for(i = 0; i < 8; i++){
		  if((((ushCrc16 & 0x8000u) >> 8) ^ (uint16)(newByte & 0x80u)) > 0){
			  ushCrc16 = (ushCrc16 << 1)  ^ cPOLY_16Bit;
		  }
      else{
			  ushCrc16 = (ushCrc16 << 1);
		  }

		  newByte <<= 1;
	  }
}

uint8 ucCalcCrc8( const uint8 *pui8Buffer, uint8 ui8MessageLen)
{
   uint8 ui8CRC = 0xaa;

   uint8 ui8BitsInFirstByte = 8;

   do
  {
      uint8 ui8BitNumber = 0x00U;
      uint8 byteContent = (pui8Buffer[0] << (8 - ui8BitsInFirstByte));

      if(1U < ui8MessageLen){
      byteContent |= (pui8Buffer[1] >> ui8BitsInFirstByte);
      ui8BitNumber = 8U;
      }
      else{
      ui8BitNumber = ui8BitsInFirstByte;
      }

      ui8CRC ^= byteContent;
    do
      {
      if(0 != (0x80U & ui8CRC)){
        ui8CRC = (uint8)((ui8CRC << 1U) ^ cPOLY_8Bit);
      }
      else{
        ui8CRC = (uint8)(ui8CRC << 1U);
      }
      ui8BitNumber--;
      }
    while (0 != ui8BitNumber);

    pui8Buffer++;

      ui8MessageLen--;
   }
  while (0 != ui8MessageLen);

   return (ui8CRC);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

