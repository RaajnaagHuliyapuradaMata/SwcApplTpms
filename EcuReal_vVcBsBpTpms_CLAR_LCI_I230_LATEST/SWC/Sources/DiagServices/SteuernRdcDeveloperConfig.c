

#include "SteuernRdcDeveloperConfig.h"

#include "StatusRdcDeveloperDataLesenX.h"

uint8 ucPutSteuernRdcDeveloperConfigDS(uint8 ucCommand, const uint8* ucData)
{
   uint8 ucRetVal = cRetError;

   if(ucCommand == cSteuernRdcDeveloperConfigRdcCommand_0){
      ucRetVal = ucPutDeveloperDataMuxChannelDS(ucData[0]);
   }

   return ucRetVal;
}

