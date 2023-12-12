

#include "SteuernRdcDeveloperConfigX.h"

#include "StatusRdcDeveloperDataLesenX.h"

#define cSteuernRdcDeveloperConfigRdcCommand_0  ((uint8) 0)

uint8 ucPutSteuernRdcDeveloperConfigDS(uint8 ucCommand, const uint8* ucData)
{
   uint8 ucRetVal = cRetError;

   if(ucCommand == cSteuernRdcDeveloperConfigRdcCommand_0){
      ucRetVal = ucPutDeveloperDataMuxChannelDS(ucData[0]);
   }

   return ucRetVal;
}

