#include "abs_lin.h"
#include "FPA_X.h"

static uint8 ucAbsState;
static tABS_DATA tAbsDataBuff[cAbsBufferSize];
static uint16 ushLinAbsData [4];
static uint8 ucAbsIndex;
static uint32 ushAbsTickDiff200msOffset;
static  uint8 ucPreviousOverflowCntVl;
static  uint8 ucPreviousOverflowCntVr;
static  uint8 ucPreviousOverflowCntHl;
static  uint8 ucPreviousOverflowCntHr;
static  uint8 ucCurrentOverflowCntVl;
static  uint8 ucCurrentOverflowCntVr;
static  uint8 ucCurrentOverflowCntHl;
static  uint8 ucCurrentOverflowCntHr;
static uint16 ushRollReference;
static uint16 ushRollCounter;
static boolean bRollDetectionActive;
static boolean bStopBit;
static uint8 ucStopCounter = 0;

#if(cABS_DEBUG_MODE == 1)
static uint16 ushDebugAbsTimeDiff     = 0;
static uint16 ushDebugRfTimeStamp     = 0;
static uint16 ushDebugRfTimeStampDiff = 0;
static uint16 ushDebugAbs2RfTimeDiff  = 0;
static uint16 ushDebugAbsCntVlDiff    = 0;
static uint16 ushDebugAbsCntVrDiff    = 0;
static uint16 ushDebugAbsCntHlDiff    = 0;
static uint16 ushDebugAbsCntHrDiff    = 0;
static uint16 ushDebugDivisor         = 0;
static uint16 ushDebugAbsCntVlLin     = 0;
static uint16 ushDebugAbsCntVrLin     = 0;
static uint16 ushDebugAbsCntHlLin     = 0;
static uint16 ushDebugAbsCntHrLin     = 0;
static uint8  ucDebugError            = 0;
#endif

void InitABS(void)
{
  uint8 ucLoop;

  for ( ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++)
  {
    tAbsDataBuff[ucLoop].ushAbsTimeStamp = (uint16) 0;

    tAbsDataBuff[ucLoop].ushAbsCntVl = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntVr = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntHl = (uint16) 0;
    tAbsDataBuff[ucLoop].ushAbsCntHr = (uint16) 0;
	  tAbsDataBuff[ucLoop].ucOverflowCntVl = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntVr = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntHl = (uint8) 0;
    tAbsDataBuff[ucLoop].ucOverflowCntHr = (uint8) 0;
  }

  ucPreviousOverflowCntVl = 0;
  ucPreviousOverflowCntVr = 0;
  ucPreviousOverflowCntHl = 0;
  ucPreviousOverflowCntHr = 0;

  ucCurrentOverflowCntVl = 0;
  ucCurrentOverflowCntVr = 0;
  ucCurrentOverflowCntHl = 0;
  ucCurrentOverflowCntHr = 0;

  ucAbsState = cABS_STATE_INIT;
  ucAbsIndex = 0;
  ushAbsTickDiff200msOffset = 0;

  ushRollReference = 0;
  ushRollCounter = 0;
  bRollDetectionActive = FALSE;
}

void PutABS(uint16 ushTime, const uint16* ushCnt)
{
	uint8 ucAbsIndexPrev;
	uint8 ucTempDiff;
	uint8 ucAbsIndex200msOffset;

  #ifdef SIG_SIZE_ONEBYTE
  uint16 ushTempdiff = 0xFFFFU;
  #endif

	if(ucAbsState == cABS_STATE_INIT)
  {
  	tAbsDataBuff[ucAbsIndex].ushAbsTimeStamp = ushTime;
    tAbsDataBuff[ucAbsIndex].ushAbsCntVl = ushCnt[0];
		tAbsDataBuff[ucAbsIndex].ushAbsCntVr = ushCnt[1];
		tAbsDataBuff[ucAbsIndex].ushAbsCntHl = ushCnt[2];
		tAbsDataBuff[ucAbsIndex].ushAbsCntHr = ushCnt[3];

		ucAbsState = ccABS_STATE_LinABS_ERR;
	}
	else
  {

		if(ucAbsIndex == 0)
		{
    	ucAbsIndexPrev = cAbsBufferSize - 1;
    }
		else
		{
    	ucAbsIndexPrev = ucAbsIndex-1;
    }

    ucAbsIndex %= (uint8)cAbsBufferSize;
		tAbsDataBuff[ucAbsIndex].ushAbsTimeStamp = ushTime;

		if(ushCnt[0] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntVl)
		{
			ucCurrentOverflowCntVl++;
		}

		tAbsDataBuff[ucAbsIndex].ucOverflowCntVl  = ucCurrentOverflowCntVl;
		tAbsDataBuff[ucAbsIndex].ushAbsCntVl = ushCnt[0];

		if(ushCnt[1] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntVr)
		{
			ucCurrentOverflowCntVr++;
		}
		tAbsDataBuff[ucAbsIndex].ucOverflowCntVr = ucCurrentOverflowCntVr;
		tAbsDataBuff[ucAbsIndex].ushAbsCntVr = ushCnt[1];

		if(ushCnt[2] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntHl)
		{
			ucCurrentOverflowCntHl++;
		}
		tAbsDataBuff[ucAbsIndex].ucOverflowCntHl = ucCurrentOverflowCntHl;
		tAbsDataBuff[ucAbsIndex].ushAbsCntHl = ushCnt[2];

		if(ushCnt[3] < tAbsDataBuff[ucAbsIndexPrev].ushAbsCntHr)
		{
			ucCurrentOverflowCntHr++;
		}
		tAbsDataBuff[ucAbsIndex].ucOverflowCntHr  = ucCurrentOverflowCntHr;
		tAbsDataBuff[ucAbsIndex].ushAbsCntHr = ushCnt[3];

	}

	ucTempDiff = (uint8) (200 / cAbsSignalPeriodicity);

  if(ucAbsIndex >= ucTempDiff)
  {
    ucAbsIndex200msOffset = ucAbsIndex - ucTempDiff;
  }
  else
  {
    ucAbsIndex200msOffset = (uint8)((cAbsBufferSize - ucTempDiff) + ucAbsIndex);
  }

  #ifdef SIG_SIZE_ONEBYTE
  if(tAbsDataBuff[ucAbsIndex].ucOverflowCntVl >= tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl)
  {
    ushTempdiff = tAbsDataBuff[ucAbsIndex].ucOverflowCntVl - tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl;
  }
  else
  {
    ushTempdiff = ((0xFFU + tAbsDataBuff[ucAbsIndex].ucOverflowCntVl) - tAbsDataBuff[ucAbsIndex200msOffset].ucOverflowCntVl) + 1;
  }
  #endif

  if(tAbsDataBuff[ucAbsIndex].ushAbsCntVl >= tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl)
  {
    ushAbsTickDiff200msOffset = (uint16)(tAbsDataBuff[ucAbsIndex].ushAbsCntVl - tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl);
  }
  else
  {
    ushAbsTickDiff200msOffset = (uint16)((uint32)((uint32)(cAbsOverflowValue + tAbsDataBuff[ucAbsIndex].ushAbsCntVl) - (uint32)tAbsDataBuff[ucAbsIndex200msOffset].ushAbsCntVl) + cAbsOverflowCorrection);
  }

  #ifdef SIG_SIZE_ONEBYTE
  ushAbsTickDiff200msOffset = (uint16) (ushAbsTickDiff200msOffset + (ushTempdiff * cAbsOverflowValue));

  #endif

	RollDetectionABS();
	ucAbsIndex++;
}

uint8 ucGetLinABS( uint16* ushCnt)
{
	uint8 ucRet;

	if( ucAbsState == ccABS_STATE_LinABS_AVL)
	{
    ushCnt[0] = ushLinAbsData[0];
    ushCnt[1] = ushLinAbsData[1];
    ushCnt[2] = ushLinAbsData[2];
    ushCnt[3] = ushLinAbsData[3];

    ucRet = cABS_OK;
  }
  else
  {
    ucRet = cABS_ERROR;
  }

  return ucRet;
}

uint8 ucGetLinStatusABS(void)
{
  return ucAbsState;
}

uint8 ucLinABS( uint16 ushRfTimeStamp)
{
  uint8 ucRet;
  uint8 ucABSIndex1, ucABSIndex2, ucLoop;
  uint16 ushAbsCntVlDiff, ushAbsCntVrDiff, ushAbsCntHlDiff, ushAbsCntHrDiff;
  uint8 ucOverflowOffset, ucTempOverflowCntIdx,  i;

  ucABSIndex1 = 0xFF;
  for (ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++)
  {
	  if(tAbsDataBuff[ucLoop].ushAbsTimeStamp < ushRfTimeStamp)
    {

		  if(ucABSIndex1 == 0xFF)
			{
        ucABSIndex1 = ucLoop;
      }
		  else
      {
			  if(tAbsDataBuff[ucLoop].ushAbsTimeStamp > tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp)
				{
          ucABSIndex1 = ucLoop;
        }
		  }
	  }
  }

  if(ucABSIndex1 != 0xFF)
  {

	  if(ucABSIndex1 == (cAbsBufferSize - 1))
    {
		  ucABSIndex2 = 0;
    }
	  else
    {
		  ucABSIndex2 = ucABSIndex1 + 1;
    }

#if(cABS_DEBUG_MODE == 1)
		if( tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp > ushRfTimeStamp)
		{

			ushDebugAbs2RfTimeDiff = (cTimeOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp) + ushRfTimeStamp + 1;
		}
    else
    {
			ushDebugAbs2RfTimeDiff = ushRfTimeStamp - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp;
		}

		if( tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp > tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp)
		{

			ushDebugAbsTimeDiff = (cTimeOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp) + tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp + 1;
		}
    else
    {
			ushDebugAbsTimeDiff = tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp - tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp;
		}
#endif

		if( tAbsDataBuff[ucABSIndex1].ushAbsCntVl > tAbsDataBuff[ucABSIndex2].ushAbsCntVl)
		{

			ushAbsCntVlDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntVl) + tAbsDataBuff[ucABSIndex2].ushAbsCntVl + cAbsOverflowCorrection;
		}
    else
    {
			ushAbsCntVlDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntVl - tAbsDataBuff[ucABSIndex1].ushAbsCntVl;
		}

		if( ushAbsCntVlDiff > 600)
		{

#if(cABS_DEBUG_MODE == 1)
			ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTVL;
#endif
			ucAbsState = ccABS_STATE_LinABS_ERR;
			return cABS_ERROR;
		}

		if( tAbsDataBuff[ucABSIndex1].ushAbsCntVr > tAbsDataBuff[ucABSIndex2].ushAbsCntVr)
		{

			ushAbsCntVrDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntVr) + tAbsDataBuff[ucABSIndex2].ushAbsCntVr + cAbsOverflowCorrection;
		}
    else
    {
			ushAbsCntVrDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntVr - tAbsDataBuff[ucABSIndex1].ushAbsCntVr;
		}

		if( ushAbsCntVrDiff > 600)
		{

#if(cABS_DEBUG_MODE == 1)
			ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTVR;
#endif
			ucAbsState = ccABS_STATE_LinABS_ERR;
			return cABS_ERROR;
		}

		if( tAbsDataBuff[ucABSIndex1].ushAbsCntHl > tAbsDataBuff[ucABSIndex2].ushAbsCntHl)
		{

			ushAbsCntHlDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntHl) + tAbsDataBuff[ucABSIndex2].ushAbsCntHl + cAbsOverflowCorrection;
		}
    else
    {
			ushAbsCntHlDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntHl - tAbsDataBuff[ucABSIndex1].ushAbsCntHl;
		}

		if( ushAbsCntHlDiff > 600)
		{

#if(cABS_DEBUG_MODE == 1)
			ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTHL;
#endif
			ucAbsState = ccABS_STATE_LinABS_ERR;
			return cABS_ERROR;
		}

		if( tAbsDataBuff[ucABSIndex1].ushAbsCntHr > tAbsDataBuff[ucABSIndex2].ushAbsCntHr)
		{

			ushAbsCntHrDiff = (cAbsOverflowValue - tAbsDataBuff[ucABSIndex1].ushAbsCntHr) + tAbsDataBuff[ucABSIndex2].ushAbsCntHr + cAbsOverflowCorrection;
		}
    else
    {
			ushAbsCntHrDiff = tAbsDataBuff[ucABSIndex2].ushAbsCntHr - tAbsDataBuff[ucABSIndex1].ushAbsCntHr;
		}

		if( ushAbsCntHrDiff > 600)
		{

#if(cABS_DEBUG_MODE == 1)
			ucDebugError |= cDEBUG_ERROR_OVERFLOW_ABSCNTHR;
#endif
			ucAbsState = ccABS_STATE_LinABS_ERR;
			return cABS_ERROR;
		}

		ushLinAbsData[0] = tAbsDataBuff[ucABSIndex1].ushAbsCntVl + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntVl, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntVl);
		ushLinAbsData[1] = tAbsDataBuff[ucABSIndex1].ushAbsCntVr + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntVr, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntVr);
		ushLinAbsData[2] = tAbsDataBuff[ucABSIndex1].ushAbsCntHl + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntHl, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntHl);
		ushLinAbsData[3] = tAbsDataBuff[ucABSIndex1].ushAbsCntHr + ushCalcABS( ushRfTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex1].ushAbsCntHr, tAbsDataBuff[ucABSIndex2].ushAbsTimeStamp, tAbsDataBuff[ucABSIndex2].ushAbsCntHr);
#ifdef ABS_SIG_SIZE_ONEBYTE
		ushLinAbsData[0] = (uint8) ushLinAbsData[0];
		ushLinAbsData[1] = (uint8) ushLinAbsData[1];
		ushLinAbsData[2] = (uint8) ushLinAbsData[2];
		ushLinAbsData[3] = (uint8) ushLinAbsData[3];
#endif

		if(ushLinAbsData[0] < tAbsDataBuff[ucABSIndex1].ushAbsCntVl)
		{
    	ucTempOverflowCntIdx = ucABSIndex2;
    }
		else
		{
    	ucTempOverflowCntIdx = ucABSIndex1;
    }
    ucOverflowOffset = (uint8)((tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl >= ucPreviousOverflowCntVl) ?
      (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl - ucPreviousOverflowCntVl) :
      (((0xFFU - ucPreviousOverflowCntVl) + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl) + 1));
		for (i=0; i<ucOverflowOffset; i++)
    {
			RebuildABSRef(0);
		}
		ucPreviousOverflowCntVl = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVl;

		if(ushLinAbsData[1] < tAbsDataBuff[ucABSIndex1].ushAbsCntVr)
    {
			ucTempOverflowCntIdx = ucABSIndex2;
		}
    else
		{
    	ucTempOverflowCntIdx = ucABSIndex1;
    }
		ucOverflowOffset = (uint8)((tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr >= ucPreviousOverflowCntVr) ?
      (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr - ucPreviousOverflowCntVr) :
      (((0xFFU - ucPreviousOverflowCntVr) + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr) + 1));
		for (i=0; i<ucOverflowOffset; i++)
    {
			RebuildABSRef(1);
		}
		ucPreviousOverflowCntVr = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntVr;

		if(ushLinAbsData[2] < tAbsDataBuff[ucABSIndex1].ushAbsCntHl)
    {
			ucTempOverflowCntIdx = ucABSIndex2;
    }
		else
    {
			ucTempOverflowCntIdx = ucABSIndex1;
    }
		ucOverflowOffset = (uint8)((tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl >= ucPreviousOverflowCntHl) ?
      (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl - ucPreviousOverflowCntHl) :
      (((0xFFU - ucPreviousOverflowCntHl) + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl) + 1));
		for (i=0; i<ucOverflowOffset; i++)
    {
			RebuildABSRef(2);
		}
		ucPreviousOverflowCntHl = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHl;

		if(ushLinAbsData[3] < tAbsDataBuff[ucABSIndex1].ushAbsCntHr)
    {
			ucTempOverflowCntIdx = ucABSIndex2;
    }
		else
    {
			ucTempOverflowCntIdx = ucABSIndex1;
    }
		ucOverflowOffset = (uint8)((tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr >= ucPreviousOverflowCntHr) ?
      (tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr - ucPreviousOverflowCntHr) :
      (((0xFFU - ucPreviousOverflowCntHr) + tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr) + 1));
		for (i=0; i<ucOverflowOffset; i++)
    {
			RebuildABSRef(3);
		}
		ucPreviousOverflowCntHr = tAbsDataBuff[ucTempOverflowCntIdx].ucOverflowCntHr;

		ucRet = cABS_OK;
		ucAbsState = ccABS_STATE_LinABS_AVL;
	}
  else
  {
		ucRet = cABS_ERROR;
		ucAbsState = ccABS_STATE_LinABS_ERR;
	}

	return ucRet;
}

void EnableRollDetectionABS(void)
{
  bRollDetectionActive = TRUE;
}

void DisableRollDetectionABS(void)
{
  if(bRollDetectionActive == TRUE)
  {
    bRollDetectionActive = FALSE;
    bStopBit = FALSE;
    ushRollCounter = 0;
  }
}

static boolean bCarStandStillABS(void)
{
  static boolean bStop = TRUE;

	if(ushAbsTickDiff200msOffset < 1)
  {
		if(bStop == FALSE)
    {
      ucStopCounter++;
      ushRollReference = tAbsDataBuff[ucAbsIndex].ushAbsCntVl;
    }
    bStop = TRUE;
  }
  else
  {
		bStop = FALSE;
	}

  return bStop;
}

static void RollDetectionABS(void)
{
  uint16 ushTempdiff;

  if(bRollDetectionActive == TRUE)
  {

    if(bStopBit == TRUE)
    {

      if(tAbsDataBuff[ucAbsIndex].ushAbsCntVl >= ushRollReference)
      {
        ushTempdiff = tAbsDataBuff[ucAbsIndex].ushAbsCntVl - ushRollReference;
      }
      else
      {
        ushTempdiff = ((cAbsOverflowValue + tAbsDataBuff[ucAbsIndex].ushAbsCntVl) - ushRollReference) + cAbsOverflowCorrection;
      }

      ushRollCounter += ushTempdiff;
      ushRollReference = tAbsDataBuff[ucAbsIndex].ushAbsCntVl;

      if(bCarStandStillABS() == TRUE)
      {
        if(ushRollCounter > 8)
        {
          ReNewABSRef();
          ushRollCounter = 0;
        }
      }
    }

    else
    {
      if(bCarStandStillABS() == TRUE)
      {
        bStopBit = TRUE;
      }
    }
  }
}

static uint16 ushCalcABS( uint16 ushRfTimeStamp, uint16 ush1stAbsTimeStamp, uint16 ush1stAbsCnt,
                                                 uint16 ush2ndAbsTimeStamp, uint16 ush2ndAbsCnt)
{
  uint16 ushAbs2RfTimeDiff;
  uint16 ushAbsTimeDiff;
  uint16 ushAbsCntDiff;
  uint32 ulInterpol;
  uint16 retVal;

  if( ush1stAbsTimeStamp > ushRfTimeStamp)
  {

    ushAbs2RfTimeDiff = (cTimeOverflowValue - ush1stAbsTimeStamp) + ushRfTimeStamp + 1;
  }
  else
  {
    ushAbs2RfTimeDiff = ushRfTimeStamp - ush1stAbsTimeStamp;
  }

  if( ush1stAbsTimeStamp > ush2ndAbsTimeStamp)
  {

    ushAbsTimeDiff = (cTimeOverflowValue - ush1stAbsTimeStamp) + ush2ndAbsTimeStamp + 1;
  }
  else
  {
    ushAbsTimeDiff = ush2ndAbsTimeStamp - ush1stAbsTimeStamp;
  }

  if( ush1stAbsCnt > ush2ndAbsCnt)
  {

    ushAbsCntDiff = (cAbsOverflowValue - ush1stAbsCnt) + ush2ndAbsCnt + cAbsOverflowCorrection;
  }
  else
  {
    ushAbsCntDiff = ush2ndAbsCnt - ush1stAbsCnt;
  }

  if(ushAbsTimeDiff == 0)
  {

    retVal = 0;
  }

  else
  {
    ulInterpol = ((uint32)ushAbsCntDiff * 10) * (uint32)ushAbs2RfTimeDiff;
    ulInterpol = ((ulInterpol / (uint32)ushAbsTimeDiff) + 5) / 10;
    retVal = ((uint16)ulInterpol);
  }

  return (retVal);
}

uint16 ushGetLinABSValue(uint8 ucIndex)
{
  if(ucIndex < 4)
  {
    return ushLinAbsData[ucIndex];
  }
  else
  {
    return 0;
  }
}

uint8 ucGetStopCounter(void)
{
  return ucStopCounter;
}

void GetLastAbsTicks(tABS_DATA* ushLastAbsVals)
{
  ushLastAbsVals->ushAbsTimeStamp = tAbsDataBuff[ucAbsIndex - 1].ushAbsTimeStamp;
  ushLastAbsVals->ushAbsCntVl     = tAbsDataBuff[ucAbsIndex - 1].ushAbsCntVl % 96;
  ushLastAbsVals->ushAbsCntVr     = tAbsDataBuff[ucAbsIndex - 1].ushAbsCntVr % 96;
  ushLastAbsVals->ushAbsCntHl     = tAbsDataBuff[ucAbsIndex - 1].ushAbsCntHl % 96;
  ushLastAbsVals->ushAbsCntHr     = tAbsDataBuff[ucAbsIndex - 1].ushAbsCntHr % 96;
}

