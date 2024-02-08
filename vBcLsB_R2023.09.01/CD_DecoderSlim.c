

#define CD_DecoderOwn
#include "CD_Decoder_X.hpp"

unsigned char caucInterestingTelTypes[] = cSeriesTelsOfInterest;

unsigned char ucGetLen4Cmd(unsigned char ucCmd);

unsigned char ucGetLen4Cmd(unsigned char ucCmd)
 {
   uint8 u8ReturnValue = 0;

   switch(ucCmd)
   {
      case cTelTypeRotatS:
      case cTelTypeAK35defLMA: // AK STD telegram
      case cTelTypeAK35def:
      case cTelTypeStandstill:
          u8ReturnValue = ((unsigned char) 7);
          break;
      case cTelTypeHufStatus:
      case cTelTypeHufStatusLearn:
          u8ReturnValue = ((unsigned char) 9);
          break;
      case cTelTypeHufLfResponse:
          u8ReturnValue = ((unsigned char) 10);
          break;
      case cTelTypeSchraderFP:
          u8ReturnValue = ((unsigned char)13);
          break;
      default:      // ERROR
          u8ReturnValue = ((unsigned char) 0x0);
          break;
   }
    return u8ReturnValue;
 }

unsigned char ucTelOfInterest(unsigned char ucCurTT)
{
  unsigned char i;

  for(i = 0; i < sizeof(caucInterestingTelTypes); i++)
  {
   if(ucCurTT == caucInterestingTelTypes[i])
   {
      return ((unsigned char) 1);
   }
  }

  return ((unsigned char) 0);
}
