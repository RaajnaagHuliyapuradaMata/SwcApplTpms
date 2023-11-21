

#include "RdcAnlernenLokalisierungLesen.h"

#include "WAllocX.h"
#include "FPA_X.h"

void GetRdcAnlernenLokalisierungLesenDS( uint8* pucData)
{
  uint8 ucLoop;
  uint32 ulDWord;

  for( ucLoop = 0; ucLoop < (cSumWE - 4); ucLoop++)
  {
    ulDWord = ulGetZOMID( ucLoop);
    pucData[((ucLoop * 15) +  0)] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
    pucData[((ucLoop * 15) +  1)] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
    pucData[((ucLoop * 15) +  2)] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
    pucData[((ucLoop * 15) +  3)] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

    pucData[((ucLoop * 15) +  4)] = ucGetZomToothTelCtCorrLearnBit( ucLoop);
    pucData[((ucLoop * 15) +  5)] = ucGetZomToothTelCtCorrNoLearnBit( ucLoop);
    pucData[((ucLoop * 15) +  6)] = ucGetZomToothTelCtrNoCorr( ucLoop);
    pucData[((ucLoop * 15) +  7)] = ucGetZomToothTelCtNoLearnMode( ucLoop);
    pucData[((ucLoop * 15) +  8)] = ucGetZomDeltaMin( ucLoop);
    pucData[((ucLoop * 15) +  9)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_FL);
    pucData[((ucLoop * 15) + 10)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_FR);
    pucData[((ucLoop * 15) + 11)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_RL);
    pucData[((ucLoop * 15) + 12)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_RR);
    pucData[((ucLoop * 15) + 13)] = ucGetZomLearnProbeCt( ucLoop);
    pucData[((ucLoop * 15) + 14)] = ucGetZomAbsoluteProbeCt( ucLoop);
  }
}

