#include "crc16.h"

#define cPOLY_16Bit 0x1021U
#define cPOLY_8Bit  0x2Fu

static uint16 ushCrc16;

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
