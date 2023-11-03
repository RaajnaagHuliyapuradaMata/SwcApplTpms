/******************************************************************************/
/* File   : FPA.c                                                             */
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
#include "FPA.h"
#include "WallocX.h"
#include "Walloc_IF.h"
#include "abs_linX.h"

#if defined( TESSY) || defined( QAC_MISRA_CHECK)
  #undef WIN32
#else
  #ifdef WIN32
  #include "stdio.h"
  #endif
#endif

#ifdef _EcuVirtual
#include "EcuVirtual_stdio.h"
#else
#endif

#ifdef FPA
/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cFPARefWidth (uint8) 1
#define cRE15_4_2    (uint8) 0
#define cHSrange     (uint8) 1
#define cLSrange     (uint8) 2
#define cIFS         (uint8) 3
#define RE1562

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
static uint8 ucRefPointResetCounter = 0;
static uint8 ucAllocDeltaMin = cDELTAMIN;
static uint8 ucAllocAbsoluteMin = cABSOLUTEMIN;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static uint16 (*fp2ushABSingleTick) (uint8);

void SetAllocMinDeltaValueFPA(uint8 ucValue)
{
  if((ucValue >=3) && (ucValue <=7))
  {
    ucAllocDeltaMin = ucValue;
  }
  else
  {
    ucAllocDeltaMin = cDELTAMIN;
  }
}

uint8 ucGetAllocMinDeltaValueFPA(void)
{
  return ucAllocDeltaMin;
}

void SetAllocAbsoluteMinValueFPA(uint8 ucValue)
{
  if((ucValue >= 15) && (ucValue <= 18))
  {
    ucAllocAbsoluteMin = ucValue;
  }
  else
  {
    ucAllocAbsoluteMin = cABSOLUTEMIN;
  }
}

uint8 ucGetAllocAbsoluteMinValueFPA(void)
{
  return ucAllocAbsoluteMin;
}

uint8 ucTriggerFixPointAllocationFPA(uint8 ucZomIndex, const tRFTelType * ptInputWA)
{
  uint8 ucLocalisation = 0;

  fp2ushABSingleTick = (uint16(*)(uint8))0;

  if((ptInputWA->ContiFP.ucHeader.ucTType == cTelTypeContiFP) && ((uint8)((ptInputWA->ContiFP.ucHeader.ulID & 0xf0000000u) >> 28) == cSupplCodeConti))
  {
    if((ptInputWA->ContiFP.ucModeNCode & cLocSyncAngleMask) == cLocSyncAngle1)
    {
      if((ptInputWA->ContiFP.ucModeNCode & cLocSyncFrameMask) == cLocSyncFrame2)
      {
        fp2ushABSingleTick = ushGetABSingleTickFr2;
        ucLocalisation = 1;
      }
      else if((ptInputWA->ContiFP.ucModeNCode & cLocSyncFrameMask) == cLocSyncFrame3)
      {
        fp2ushABSingleTick = ushGetABSingleTickFr3;
        ucLocalisation = 1;
      }
      else
      {
        fp2ushABSingleTick = ushGetABSingleTick ;
        ucLocalisation = 1;
      }

      #ifdef Test_LOG_ENABLE
      tZOMInfo[ucZomIndex].ucToothTelCtCorrNoLearnBit++;
      #endif
    }
    else if((ptInputWA->ContiFP.ucModeNCode & cLocSyncAngleMask) == cLocSyncAngle2)
    {
      if((ptInputWA->ContiFP.ucModeNCode & cLocSyncFrameMask) == cLocSyncFrame2)
      {
        fp2ushABSingleTick = ushGetABSingleTickN90Fr2;
        ucLocalisation = 1;
      }
      else if((ptInputWA->ContiFP.ucModeNCode & cLocSyncFrameMask) == cLocSyncFrame3)
      {
        fp2ushABSingleTick = ushGetABSingleTickN90Fr3;
        ucLocalisation = 1;
      }
      else
      {
        fp2ushABSingleTick = ushGetABSingleTickN90;
        ucLocalisation = 1;
      }

      #ifdef Test_LOG_ENABLE
      tZOMInfo[ucZomIndex].ucToothTelCtCorrNoLearnBit++;
      #endif
    }
    else
    {
      #ifdef Test_LOG_ENABLE
      tZOMInfo[ucZomIndex].ucToothTelCtNoCorr++;
      #endif
    }
  }
  else if((ptInputWA->SchraderFP.ucHeader.ucTType == cTelTypeSELPAL) || (ptInputWA->SchraderFP.ucHeader.ucTType == cTelTypeSELPAL1)){
	  if(ptInputWA->SchraderFP.ucPAL == 0x0){
      #ifdef Test_LOG_ENABLE
		  tZOMInfo[ucZomIndex].ucToothTelCtNoLearnMode++;
		  tZOMInfo[ucZomIndex].ucABSComp[0] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[1] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[2] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[3] = 96;
      #endif
	  }
	  else if(ptInputWA->SchraderFP.ucPAL == 0x01){
      #ifdef Test_LOG_ENABLE
		  tZOMInfo[ucZomIndex].ucToothTelCtNoCorr++;
		  tZOMInfo[ucZomIndex].ucABSComp[0] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[1] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[2] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[3] = 96;
      #endif
	  }
	  else if(ptInputWA->SchraderFP.ucPAL == 0xFF)
    {
      #ifdef Test_LOG_ENABLE
		  tZOMInfo[ucZomIndex].ucToothTelCtNoCorr++;
		  tZOMInfo[ucZomIndex].ucABSComp[0] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[1] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[2] = 96;
		  tZOMInfo[ucZomIndex].ucABSComp[3] = 96;
      #endif
	  }
	  else
    {
      #ifdef Test_LOG_ENABLE
		  if(ptInputWA->Header.ucTType == cTelTypeSELPAL1)
      {
        tZOMInfo[ucZomIndex].ucToothTelCtCorrLearnBit++;
      }
		  else
			{
        tZOMInfo[ucZomIndex].ucToothTelCtCorrNoLearnBit++;
      }
      #endif

      fp2ushABSingleTick = ushGetABSingleTickPAL;
      ucLocalisation = 1;
    }
  }

  else if((ptInputWA->AK35def.ucHeader.ucTType == cTelTypeAK35def)
        || (ptInputWA->AK35def.ucHeader.ucTType == cTelTypeBeruLong)
        || (ptInputWA->AK35def.ucHeader.ucTType == cTelTypeBeruMed)
        || (ptInputWA->AK35def.ucHeader.ucTType == cTelTypeAK35defLMA)
        || (ptInputWA->AK35def.ucHeader.ucTType == cTelTypeG4Standard))
  {
    #ifdef Test_LOG_ENABLE
		tZOMInfo[ucZomIndex].ucABSComp[0] = 96;
		tZOMInfo[ucZomIndex].ucABSComp[1] = 96;
		tZOMInfo[ucZomIndex].ucABSComp[2] = 96;
		tZOMInfo[ucZomIndex].ucABSComp[3] = 96;
    #endif
    tZOMInfo[ucZomIndex].ucToothTelCtNoLearnMode++;
  }

  else
  {
  }

  if(ucLocalisation == 1)
  {
    if(ucGetLinStatusABS() == ccABS_STATE_LinABS_AVL)
    {
      GenerateAbsoluteCompareValuesFPA(ucZomIndex);

      #ifdef Test_LOG_ENABLE
	    tZOMInfo[ucZomIndex].ucABSComp[0] = (uint8)((fp2ushABSingleTick(0) + tZOMInfo[ucZomIndex].ushABSRefOffset [0]) % 96);
	    tZOMInfo[ucZomIndex].ucABSComp[1] = (uint8)((fp2ushABSingleTick(1) + tZOMInfo[ucZomIndex].ushABSRefOffset [1]) % 96);
	    tZOMInfo[ucZomIndex].ucABSComp[2] = (uint8)((fp2ushABSingleTick(2) + tZOMInfo[ucZomIndex].ushABSRefOffset [2]) % 96);
	    tZOMInfo[ucZomIndex].ucABSComp[3] = (uint8)((fp2ushABSingleTick(3) + tZOMInfo[ucZomIndex].ushABSRefOffset [3]) % 96);
      #endif

      #ifdef SPEEDWEIGHT
      if(ucGetSpeed() < cSPW_THRESHOLD)
      {
        GenerateAbsoluteCompareValuesFPA(ucZomIndex);
      }
      #endif
      ucLocalisation = ucLocateWheelPositionsFPA(FALSE);
    }
    else
    {
      ucLocalisation = 0;
    }
  }

  return (ucLocalisation);
}

#ifdef WIN32
static void Int2Bcd(uint32 ulValue, uint8* ucBcdChar, uint8 ucLength)
{
  uint8 ucLoop;

  for ( ucLoop = (ucLength - 1); ucLoop > 0; ucLoop--)
  {
    ucBcdChar[ucLoop - 1] = (ulValue % 10) + 0x30;
    ulValue /= 10;
  }
  ucBcdChar[ucLength - 1] = ';';
}
#endif

static void SetReferenceValuesFPA(uint8 ucSlot)
{
  uint8 i;

  for (i=0; i<cMaxLR; i++)
  {
    tZOM[ucSlot].ucABSRef[i] = (uint8)(fp2ushABSingleTick(i) % FULLTURNINABSTICKS);
  }
}

static void ClearAverageDistanceSumValuesFPA(uint8 ucSlot)
{
  uint8 i;
  for (i=0; i<cMaxLR; i++)
  {
    tZOM[ucSlot].ushMVdN[i] = 0;
    tZOM[ucSlot].ushMVdN2[i] = 0;
  }
}

static void GenerateAbsoluteCompareValuesFPA(uint8 ucSlot)
{

  #ifdef WIN32
  static FILE* fStream;
  static const char filename[] = "zo_statistik.csv";
  static boolean bFirst = TRUE;
  char line[110] = {"Slot; ID; WPos; CurTick; CurTooth; DistRefVal; dN1; dN2; AvgdN1; AvgdN2; Dev1; Dev2; CmpVal1; CmpVal2;"};
                   /
  uint16 ushDistRefVal;
  uint16 ushDistStandard;
  uint16 ushDistShadow;
  uint16 ushAvgDistStandard;
  uint16 ushAvgDistShadow;
  uint16 ushCurrDevStandard;
  uint16 ushCurrDevShadow;
  uint8  i;

  if(ucSlot < cSumWE)
  {

    if((tZOM[ucSlot].ucLocateProbeCt == 0) || (tZOM[ucSlot].ucResetABSRefFlag == 1))
    {
      SetReferenceValuesFPA(ucSlot);
      if(tZOM[ucSlot].ucLocateProbeCt == 0)
      {
        ClearAverageDistanceSumValuesFPA(ucSlot);
        tZOM[ucSlot].ucLocateProbeCt++;
      }
      tZOM[ucSlot].ucResetABSRefFlag = 0;
    }

    else
    {
      tZOM[ucSlot].ucStatus |= cMinStretch;
      tZOM[ucSlot].ucLocateProbeCt++;
      for (i=0; i<cMaxLR; i++)
      {

        ushCurrentTooth = fp2ushABSingleTick(i) % FULLTURNINABSTICKS;

        if(ushCurrentTooth < tZOM[ucSlot].ucABSRef[i])
        {
          ushDistRefVal = (ushCurrentTooth + FULLTURNINABSTICKS) - tZOM[ucSlot].ucABSRef[i];
        }
        else
        {
          ushDistRefVal = ushCurrentTooth - tZOM[ucSlot].ucABSRef[i];
        }

        if(ushDistRefVal > HALFTURNINABSTICKS)
        {
          ushDistStandard = ushDistRefVal - HALFTURNINABSTICKS;
        }
        else
        {
          ushDistStandard = ushDistRefVal + HALFTURNINABSTICKS;
        }

        ushDistShadow = (ushDistStandard + 48) % FULLTURNINABSTICKS;

        #ifdef Test_LOG_ENABLE
        tZOMInfo[ucSlot].ucDistanceStandard[i] = (uint8)ushDistStandard;
        tZOMInfo[ucSlot].ucDistanceStandard[i] = (uint8)ushDistStandard;
        #endif

        if(tZOM[ucSlot].ucLocateProbeCt > cFPARefWidth)
        {
          if(tZOM[ucSlot].ushMVdN[i] < (0xffffu - ushDistStandard))
          {
            tZOM[ucSlot].ushMVdN[i] += ushDistStandard;
            ushAvgDistStandard = tZOM[ucSlot].ushMVdN[i] / ((uint16)(tZOM[ucSlot].ucLocateProbeCt - cFPARefWidth));
          }

          if(tZOM[ucSlot].ushMVdN2[i] < (0xffffu - ushDistShadow))
          {
            tZOM[ucSlot].ushMVdN2[i] += ushDistShadow;
            ushAvgDistShadow = tZOM[ucSlot].ushMVdN2[i] / ((uint16)(tZOM[ucSlot].ucLocateProbeCt - cFPARefWidth));
          }
        }

        if(ushDistStandard > ushAvgDistStandard)
        {
          ushCurrDevStandard = ushDistStandard - ushAvgDistStandard;
        }
        else
        {
          ushCurrDevStandard = ushAvgDistStandard - ushDistStandard;
        }

        if(ushDistShadow > ushAvgDistShadow)
        {
          ushCurrDevShadow = ushDistShadow - ushAvgDistShadow;
        }
        else
        {
          ushCurrDevShadow = ushAvgDistShadow - ushDistShadow;
        }

        if(tZOM[ucSlot].ushPosCompVal[i] < (0xffffu - ushCurrDevStandard))
        {
          tZOM[ucSlot].ushPosCompVal[i] += ushCurrDevStandard;
        }

        if(tZOM[ucSlot].ushPosCompVal2[i] < (0xffffu - ushCurrDevShadow))
        {
          tZOM[ucSlot].ushPosCompVal2[i] += ushCurrDevShadow;
        }

        #ifdef WIN32
        if(bFirst == TRUE)
        {
          remove("zo_statistik.csv");
          fopen_s(&fStream, filename, "a");
          fwrite(line, sizeof(uint8), sizeof(line), fStream);
          fclose( fStream);
          fopen_s(&fStream, filename, "ab");
          line[0] = 13;
          line[1] = 10;
          fwrite(line, sizeof(uint8), 2, fStream);
          fclose(fStream);
          bFirst = FALSE;
        }

        for (j=0; j<sizeof(line); j++)
        {
          line[j] = 0x00;
        }
        ucPos = 0;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ucSlot, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 11;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ulGetIDOfColWAL(ucSlot), (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(i, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(fp2ushABSingleTick(i), (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushCurrentTooth, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushDistRefVal, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushDistStandard, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushDistShadow, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushAvgDistStandard, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushAvgDistShadow, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushCurrDevStandard, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(ushCurrDevShadow, (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(tZOM[ucSlot].ushPosCompVal[i], (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;
        ucLen = 6;
        if((ucPos + ucLen) < sizeof(line)) Int2Bcd(tZOM[ucSlot].ushPosCompVal2[i], (uint8*)&line[ucPos], ucLen);
        ucPos += ucLen;

        fopen_s(&fStream, filename, "a");
        fwrite(line, sizeof(uint8), ucPos, fStream);
        fclose( fStream);

        fopen_s(&fStream, filename, "ab");
        line[0] = 13;
        line[1] = 10;
        fwrite(line, sizeof(uint8), 2, fStream);
        fclose(fStream);

        #endif

      }
    }
  }
}

uint8 ucLocateWheelPositionsFPA(boolean bUseForcedAlloc)
{
  uint32 ulTmp;
  uint32 ulCmpSum;
  uint8  ucSort[4];
  boolean bLineIsClear;
  uint8  i, j, ucTmp, ucTmp2;
  uint8  ucRet = 0;
  uint8 ucUnusedWp;
  tIdEvaluation tIdEval = {0};

  #ifdef Test_LOG_ENABLE
  uint8  ucLocalRelCmpVal[cSumWE][cMaxLR];
  #else
  uint8  ucLocalRelCmpVal[cMaxLR][cMaxLR];
  #endif

  #ifdef Test_LOG_ENABLE
  for (i=0; i<cSumWE; i++)
  {
    for (j=0; j<cMaxLR; j++)
    {
      ucLocalRelCmpVal[i][j] = 25;
      tZOMInfo[i].ucRelCmpVal[j] = ucLocalRelCmpVal[i][j];
    }
  }
  #else
  for (i=0; i<cMaxLR; i++)
  {
    for (j=0; j<cMaxLR; j++)
    {
      ucRelCmpVal[i][j] = 25;
    }
  }
  #endif

  for (i=0; i<cMaxLR; i++)
  {
    tIdEval.tIdChar[i].ucAimsWheelPos = cWheelPos_NA;
  }

  #ifdef Test_LOG_ENABLE
  for (i=0; i<cSumWE; i++)
  #else
  for (i=0; i<cMaxLR; i++)
  #endif
  {

    ulCmpSum = ulCalcCompareSumFPA(i);

    if(ulCmpSum > 0)
    {

      for (j=0; j<cMaxLR; j++)
      {

        if(tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j])
        {
          if(tZOM[i].ushPosCompVal[j] > 0)
          {
            ulTmp =  (uint32) tZOM[i].ushPosCompVal[j] * 100;
            ulTmp /= ulCmpSum;
            ucLocalRelCmpVal[i][j] = (uint8) ulTmp;
          }
          else
          {
            ucLocalRelCmpVal[i][j] = (uint8) 1;
          }
        }

        else
        {
          if(tZOM[i].ushPosCompVal2[j] > 0)
          {
            ulTmp =  (uint32) tZOM[i].ushPosCompVal2[j] * 100;
            ulTmp /= ulCmpSum;
            ucLocalRelCmpVal[i][j] = (uint8) ulTmp;
          }
          else
          {
            ucLocalRelCmpVal[i][j] = (uint8) 1;
          }
        }

        if(0 == ucLocalRelCmpVal[i][j])
        {
          ucLocalRelCmpVal[i][j] = 1;
        }

        #ifdef Test_LOG_ENABLE
        tZOMInfo[i].ucRelCmpVal[j] = ucLocalRelCmpVal[i][j];
        #endif
      }
    }
  }

  for (i = 0; i < cMaxLR; i++)
  {
    bLineIsClear = TRUE;
    SortBiggest1st(ucLocalRelCmpVal[i], ucSort, cMaxLR);

    #ifdef Test_LOG_ENABLE
	  tZOMInfo[i].ucDeltaMin = (ucLocalRelCmpVal[i][ucSort[cMaxLR-2]] - ucLocalRelCmpVal[i][ucSort[cMaxLR-1]]);
    #endif

    if((ucLocalRelCmpVal[i][ucSort[cMaxLR-2]] - ucLocalRelCmpVal[i][ucSort[cMaxLR-1]]) < ucAllocDeltaMin)
    {
      bLineIsClear = FALSE;
      tIdEval.tIdChar[i].ucIsAmbigous = 1;
    }

    else if((tZOM[i].ucStatus & cMinStretch) != cMinStretch)
    {
      bLineIsClear = FALSE;
      tIdEval.tIdChar[i].ucIsAmbigous = 1;
    }

    else if(tZOM[i].ucLocateProbeCt < cMinCt4Dec)
    {
      bLineIsClear = FALSE;
      tIdEval.tIdChar[i].ucIsAmbigous = 1;
    }

    else
    {
      j = ucSort[cMaxLR-1];
      if(ucGetWPOfColWAL(ucGetColOfID(&tZOM[i].ulID)) != j)

      {
        if(ucLocalRelCmpVal[i][j] > ucAllocAbsoluteMin)
        {
          bLineIsClear = FALSE;
          tIdEval.tIdChar[i].ucIsAmbigous = 1;
        }
      }
    }

    if(bLineIsClear == TRUE)
    {
      for (j=0; j<cMaxLR; j++)
      {
        if(j == ucSort[cMaxLR-1])
        {
          tIdEval.tIdChar[i].ucAimsWheelPos = ucSort[cMaxLR-1];
        }
        else
        {
          ucLocalRelCmpVal[i][j] = 0;
        }
      }
    }
  }

  for (i=0; i<3; i++)
  {
    for (j=i+1; j<cMaxLR; j++)
    {
      if(tIdEval.tIdChar[i].ucAimsWheelPos == tIdEval.tIdChar[j].ucAimsWheelPos)
      {
        tIdEval.tIdChar[i].ucIsFighting = TRUE;
        tIdEval.tIdChar[j].ucIsFighting = TRUE;
      }
    }
  }

  for (i=0; i<cMaxLR; i++)
  {
    if((tIdEval.tIdChar[i].ucIsAmbigous ^ tIdEval.tIdChar[i].ucIsFighting) == 1)
    {
      tIdEval.tIdChar[i].ucIsAmbigousXorFighting = 1;
    }
  }

  for (i=0; i<cMaxLR; i++)
  {
    tIdEval.ucSumAmbigous += tIdEval.tIdChar[i].ucIsAmbigous;
    tIdEval.ucSumFighting += tIdEval.tIdChar[i].ucIsFighting;
    tIdEval.ucSumAmbXorFighting += tIdEval.tIdChar[i].ucIsAmbigousXorFighting;
  }

  if(tIdEval.ucSumAmbigous > 1)
  {
    ucRet = 0;
  }

  else if(tIdEval.ucSumFighting > 2)
  {
    ucRet = 0;
  }

  else if(tIdEval.ucSumAmbXorFighting > 2)
  {
    ucRet = 0;
  }

  else
  {

    if((tIdEval.ucSumAmbigous == 0) && (tIdEval.ucSumFighting == 0))
    {
      ucRet = 1;
    }

    else if(bUseForcedAlloc == TRUE)
    {

      ucUnusedWp = 0;
      i = 0;
      while (i < cMaxLR)
      {
        i = 0;
        while ((tIdEval.tIdChar[i].ucAimsWheelPos != ucUnusedWp) && (i < cMaxLR))
        {
          i++;
        }
        if(i < cMaxLR)
        {
          ucUnusedWp++;
        }
      }

      if((tIdEval.ucSumAmbigous == 0) && (tIdEval.ucSumFighting == 2))
      {

        i=0;
        j=0;

        while (tIdEval.tIdChar[i].ucIsFighting == 0)
        {
          i++;
          j++;
        }
        ucTmp = ucLocalRelCmpVal[i][tIdEval.tIdChar[i].ucAimsWheelPos];

        j++;
        while (tIdEval.tIdChar[j].ucIsFighting == 0)
        {
          j++;
        }
        ucTmp2 = ucLocalRelCmpVal[j][tIdEval.tIdChar[j].ucAimsWheelPos];

        if(ucTmp < ucTmp2)
        {
          if((ucTmp2 - ucTmp) > cDELTAFIGHT)
          {
            tIdEval.tIdChar[j].ucAimsWheelPos = ucUnusedWp;
            ucRet = 1;
          }
          else
          {
            ucRet = 0;
          }
        }
        else
        {
          if((ucTmp - ucTmp2) > cDELTAFIGHT)
          {
            tIdEval.tIdChar[i].ucAimsWheelPos = ucUnusedWp;
            ucRet = 1;
          }
          else
          {
            ucRet = 0;
          }
        }
      }

      else
      {

        i = 0;
        while (tIdEval.tIdChar[i].ucIsAmbigous == 0)
        {
          i++;
        }
        tIdEval.tIdChar[i].ucAimsWheelPos = ucUnusedWp;
        ucRet = 1;
      }
    }
    else
    {
      ucRet = 0;
    }
  }

  if(ucRet == 1)
  {
    for (i=0; i<cMaxLR; i++)
    {
      SetZOMWP(i, tIdEval.tIdChar[i].ucAimsWheelPos);
    }
  }

  return (ucRet);
}

uint8 ucLocateWheelPositionsPartialFPA(uint8 ucNoOfSlots)
{
  uint32 ulTmp;
  uint32 ulCmpSum;
  uint8  ucSort[4];
  uint8  i, j, ucTmp;
  uint8  ucRet = 0;
  uint8  ucCheckAllocConditions[cMaxLR];
  uint8  ucFailedIds;

  #ifdef Test_LOG_ENABLE
  uint8  ucLocalRelCmpVal[cSumWE][cMaxLR];
  #else
  uint8  ucLocalRelCmpVal[cMaxLR][cMaxLR];
  #endif

  #ifdef Test_LOG_ENABLE
  for (i=0; i<cSumWE; i++)
  {
    for (j=0; j<cMaxLR; j++)
    {
      ucLocalRelCmpVal[i][j] = 25;
      tZOMInfo[i].ucRelCmpVal[j] = ucLocalRelCmpVal[i][j];
    }
  }
  #else
  for (i=0; i<ucNoOfSlots; i++)
  {
    for (j=0; j<cMaxLR; j++)
    {
      ucRelCmpVal[i][j] = 25;
    }
  }
  #endif

  #ifdef Test_LOG_ENABLE
  for (i=0; i<cSumWE; i++)
  #else
  for (i=0; i<ucNoOfSlots; i++)
  #endif
  {

    ulCmpSum = ulCalcCompareSumFPA(i);

    if(ulCmpSum > 0)
    {

      for ( j = 0; j < cMaxLR; j++)
      {

        if(tZOM[i].ushPosCompVal[j] < tZOM[i].ushPosCompVal2[j])
        {
          if(tZOM[i].ushPosCompVal[j] > 0)
          {
            ulTmp =  (uint32) tZOM[i].ushPosCompVal[j] * 100;
            ulTmp /= ulCmpSum;
            ucLocalRelCmpVal[i][j] = (uint8) ulTmp;
          }
          else
          {
            ucLocalRelCmpVal[i][j] = (uint8) 1;
          }
        }

        else
        {
          if(tZOM[i].ushPosCompVal2[j] > 0)
          {
            ulTmp =  (uint32) tZOM[i].ushPosCompVal2[j] * 100;
            ulTmp /= ulCmpSum;
            ucLocalRelCmpVal[i][j] = (uint8) ulTmp;
          }
          else
          {
            ucLocalRelCmpVal[i][j] = (uint8) 1;
          }
        }

        if(ucLocalRelCmpVal[i][j] == 0)
        {
          ucLocalRelCmpVal[i][j] = 1;
        }

        #ifdef Test_LOG_ENABLE
        tZOMInfo[i].ucRelCmpVal[j] = ucLocalRelCmpVal[i][j];
        #endif
      }
    }
  }

  ucTmp = 0;
  for (i = 0; i < ucNoOfSlots; i++)
  {
    SortBiggest1st(ucLocalRelCmpVal[i], ucSort, cMaxLR);

    #ifdef Test_LOG_ENABLE
	  tZOMInfo[i].ucDeltaMin = (ucLocalRelCmpVal[i][ucSort[cMaxLR-2]] - ucLocalRelCmpVal[i][ucSort[cMaxLR-1]]);
    #endif

    if(ucLocalRelCmpVal[i][ucSort[cMaxLR-1]] <= ucAllocAbsoluteMin)
    {

      if((ucLocalRelCmpVal[i][ucSort[cMaxLR-2]] - ucLocalRelCmpVal[i][ucSort[cMaxLR-1]]) >= ucAllocDeltaMin)
      {

        ucTmp++;
        for ( j = 0; j < cMaxLR; j++)
        {
          if( j != ucSort[cMaxLR-1])
          {
            ucLocalRelCmpVal[i][j] = (uint8) 0;
          }
        }
      }
      else
      {

         ucTmp = 0;
      }
    }
    else
    {

      ucTmp = 0;
    }
  }

  if(ucTmp == ucNoOfSlots)
  {
    ucTmp = 0;
    for (i=0; i<ucNoOfSlots; i++)
    {
      for (j=0; j<cMaxLR; j++)
      {
        if(ucLocalRelCmpVal[i][j] > 0)
        {
          if((ucTmp & (uint8)(1 << j)) == 0)
          {
            ucTmp |= (uint8)(1 << j);
          }
        }
      }
    }
  }

  if(ucNrOfBitSet8(ucTmp) != ucNoOfSlots)
  {
    ucRet = 0;
  }

  else
  {

    ucFailedIds = 0;
    for (i = 0 ; i < ucNoOfSlots; i++)
    {
      if(((tZOM[i].ucStatus & cMinStretch) == cMinStretch)
        && (tZOM[i].ucLocateProbeCt >= cMinCt4Dec))
      {
        ucCheckAllocConditions[i] = 1;
      }
      else
      {
        ucCheckAllocConditions[i] = 0;
      }

      ucFailedIds += ucCheckAllocConditions[i];
    }

    if(ucFailedIds == ucNoOfSlots)
    {
      for (i = 0; i < ucNoOfSlots; i++)
      {
        for ( j = 0; j < cMaxLR; j++)
        {
          if(ucLocalRelCmpVal[i][j] > 0)
          {
            SetZOMWP(i,j);
          }
        }
      }

      ucRet = ucTmp ^ 0x0fu;
    }
    else
    {
      ucRet = 0;
    }
  }

  return (ucRet);
}

void RebuildABSRef(uint8 ucWP)
{
  uint8 i;

  for (i = 0; i < cSumWE ;i++)
  {
    if(tZOM[i].ucLocateProbeCt > 0)
    {
      #ifdef Test_LOG_ENABLE
		  tZOMInfo[i].ushABSRefOffset[ucWP] = (tZOMInfo[i].ushABSRefOffset[ucWP] + ucABSigOFL_MOD_ZAHN())%96;
      #endif

      if(tZOM[i].ucABSRef [ucWP] >= ucABSigOFL_MOD_ZAHN())
      {
        tZOM[i].ucABSRef [ucWP] -= ucABSigOFL_MOD_ZAHN();
      }
      else
      {
        tZOM[i].ucABSRef [ucWP] += ucMINUS_ABSigOFL_MOD_ZAHN();
      }
    }
  }
}

void ReNewABSRef(void)
{
  uint8 i;

  for (i = 0; i < cSumWE ;i++)
  {
	  if(tZOM[i].ucLocateProbeCt != 0)
    {
      tZOM[i].ucResetABSRefFlag = 1;
    }
  }
  ucRefPointResetCounter++;
}

static uint32 ulCalcCompareSumFPA(uint8 ucSlot)
{
  uint8 j;
  uint32 ulSum = 0;

  for (j=0; j<cMaxLR; j++)
  {
    if(tZOM[ucSlot].ushPosCompVal2[j] < tZOM[ucSlot].ushPosCompVal[j])
    {
      ulSum += tZOM[ucSlot].ushPosCompVal2[j];
    }
    else
    {
      ulSum += tZOM[ucSlot].ushPosCompVal[j];
    }
  }
  return ulSum;
}

static void SortBiggest1st(const uint8 *ptVal, uint8 *ptIx, uint8 ucMax)
{
  uint8 i,j, ucBuffer;

  for(i=0;i<ucMax;i++)
  {
    ptIx[i] = i;
  }

  for (i = 1; i < ucMax; i++)
  {
    for (j = i; j >= 1; j--)
    {
      if(ptVal[ptIx[j]] > ptVal[ptIx[j-1]])
      {
        ucBuffer = ptIx[j];
        ptIx[j] = ptIx[j-1];
        ptIx[j-1] = ucBuffer;
      }
      else
      {
        break;
      }
    }
  }
}

static uint8 ucABSigOFL_MOD_ZAHN(void)
{
  return (cAbsOverflowValue % FULLTURNINABSTICKS);
}

static uint8 ucMINUS_ABSigOFL_MOD_ZAHN(void)
{
  return (FULLTURNINABSTICKS - ucABSigOFL_MOD_ZAHN());
}

static uint16 ushGetABSingleTickPAL(uint8 ucIx)
{
  return ( ushGetABSingleTick (ucIx));
}

static uint16 ushGetABSingleTickFr2(uint8 ucIx){
   return (ushGetABSingleTick (ucIx)-((uint16) ucGetTDL100()));
}

static uint16 ushGetABSingleTickFr3(uint8 ucIx){
 return (ushGetABSingleTick (ucIx) - ushGetTDL210());
}

static uint16 ushGetABSingleTickN90(uint8 ucIx){
 return (ushGetABSingleTick (ucIx)- QUARTURNINABSTICKS);
}

static uint16 ushGetABSingleTickN90Fr2(uint8 ucIx){
  return (ushGetABSingleTick (ucIx)-((uint16) ucGetTDL100() + QUARTURNINABSTICKS));
}

static uint16 ushGetABSingleTickN90Fr3(uint8 ucIx){
  return (ushGetABSingleTick (ucIx)-(ushGetTDL210() + QUARTURNINABSTICKS));
}

static uint8 ucGetTDL100(void){
  uint16 ushVtmp;
  uint8 ucIx;
  static const uint8 cucTDL100atV[] = {6,12,18,24,30,36,42,48,55,61,67,73,79,85,91,97,103,109,115,121,127,133,139,145,152,158};
  ushVtmp =  (uint16) ucGetSpeed();
  ucIx = (uint8) ((((ushVtmp * 10)/5)+5)/10);
  if(ucIx > 0)
  {
    ucIx--;
    if(ucIx > (uint8) 25)
    {
      ucIx = (uint8) 25;
    }
  }

  return(cucTDL100atV[ucIx]);
}

static uint16 ushGetTDL210(void){
  uint16 ushVtmp;
  uint8 ucIx;
  static const uint16 cushTDL210atV[] = {13,25,38,51,64,76,89,102,115,127,140,153,165,178,191,204,216,229,242,255,267,280,293,305,318, 331};
  ushVtmp =  (uint16) ucGetSpeed();
  ucIx = (uint8) ((((ushVtmp * 10)/5)+5)/10);
  if(ucIx > 0)
  {
    ucIx--;
    if(ucIx > (uint8) 25)
    {
      ucIx = (uint8) 25;
    }
  }

  return(cushTDL210atV[ucIx]);
}

void CalcInfoZomMinDistFPA(void)
{
  uint8 i;
  uint8 ucSort[4];
  for (i = 0; i<cSumWE; i++)
  {
    if(tZOM[i].ucAbsoluteProbeCt > 0)
    {
      SortBiggest1st(tZOMInfo[i].ucRelCmpVal, ucSort, cMaxLR);
      tZOMInfo[i].ucDeltaMin = (tZOMInfo[i].ucRelCmpVal[ucSort[cMaxLR - 2]] - tZOMInfo[i].ucRelCmpVal[ucSort[cMaxLR - 1]]);
    }
  }
}

uint8 ucGetRefPointResetCounter(void){
  return ucRefPointResetCounter;
}

uint8 ucGetZomLowestMetricsValueFPA(uint8 ucSlot){
  uint8* pucSource;
  uint8  ucDest[4];
  uint8  ucRetVal = 0xff;
  if(ucSlot < 16){
    pucSource = tZOMInfo[ucSlot].ucRelCmpVal;
    SortBiggest1st((const uint8*)pucSource, ucDest, 4);
    ucRetVal = pucSource[ucDest[3]];
  }
  return ucRetVal;
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

