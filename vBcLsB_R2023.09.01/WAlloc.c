#define WALLOC_INT

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.hpp"
  #include "SwcApplTpms_Rte.hpp"
  #include "WallocX.hpp"
  #include "Walloc_IF.hpp"
  #include "walloc.hpp"
  #include "FPA.hpp"
  #include "CfgSwcApplTpms.hpp"
  #include "procdatx.hpp"
  #include "state_bzX.hpp"
  #include "statemanagerX.hpp"
  #include "global.hpp"
  #include "uswarn_Ifx.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
  #include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#if(defined HUF_DEBUG) && (defined WIN32)
  #include "debug.hpp"
#endif
#else
  #include "WallocX.hpp"
  #include "Walloc_IF.hpp"
  #include "walloc.hpp"
  #include "FPA.hpp"
  #include "procdatx.hpp"
  #include "SwcApplTpms_NvM_If.hpp"
#endif

#ifdef pb_ModulTest_050104

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "modultest.hpp"

#else

#endif

static const unsigned char ucWACtrlFixc = 0x01;
static const unsigned char ucWACtrlBreakc = 0x02;

static unsigned char ucWAState;

static unsigned long aulHistoryID[cMaxLR];
static unsigned char aucHistoryWP[cMaxLR];

#define cWPER 0x10

static unsigned char ucNrOfTOs;

static unsigned short ushHistProtecTimeCnt; //counts the commutative driving time for the first minutes to protect history IDs
#ifdef pb_Debug4MB_010404
static unsigned char ucRightRSDistDG;
static unsigned char ucLeftRSDistDG;
#endif

WAABSTicksInOneRevolution tABSTicksOneRevol;

#ifdef DETECT_SYMC_WALLOC_DTC
  static uint8 sm_ucWPConsistentErrCnt  = 0;
  static uint8 sm_ucAxisDetectionErrCnt = 0;
  static uint8 sm_ucDirDetectionErrCnt  = 0;
#ifdef BUILD_WITH_UNUSED_FUNCTION
  void  IncWPConsistentError(void);
#endif //BUILD_WITH_UNUSED_FUNCTION
  void  IncAxisDetectionError(void);
#ifdef G_USE_ROTATION_DIRECTION
  void  IncDirDetectionError(void);
#endif //#ifdef G_USE_ROTATION_DIRECTION
  uint8 CheckForDetailed_ZO_Error(void);
#endif

static unsigned short ushIDSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt
   ,                                    unsigned char ucSlots2Search);
static unsigned char ucNrOfBitSet(unsigned short ushTarget);

static boolean bCheckIfNewTelAllowed(struct InputWA *ptInputWA, unsigned char ucIx);

//static boolean bGetHistProtecTimeOver();
//#pragma PRQA_NO_SIDE_EFFECTS bGetHistProtecTimeOver

static void CheckAndMarkNewIdER(unsigned char ucIx);

static boolean bGetZomPotentStatusOfID(unsigned char ucIx);
#pragma PRQA_NO_SIDE_EFFECTS bGetZomPotentStatusOfID

static boolean bGetZomOwnStatusOfID(unsigned char ucIx);
#pragma PRQA_NO_SIDE_EFFECTS bGetZomOwnStatusOfID

static unsigned char ucGetHistoryState(void);
#pragma PRQA_NO_SIDE_EFFECTS ucGetHistoryState

static void SetWActiveState(unsigned char ucVal);
static unsigned char ucGetWActiveState(void);
static void SetERState(unsigned char ucVal);
static void SetZOState(unsigned char ucVal);
static unsigned char ucGetZOState(void);
static void SetWAStateZOChange(unsigned char ucChangedPos);
#ifdef BUILD_WITH_UNUSED_FUNCTION
static void ClearAxis(unsigned char ucIx);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static void SetPair2OtherAxis(unsigned char uc1st, unsigned char uc2nd);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static void SetPair2ECUAxis(unsigned char uc1st, unsigned char uc2nd);
#endif

#ifdef G_USE_ROTATION_DIRECTION
static void ResetSpin(unsigned char ucIx);
static void SetLeftSpin(unsigned char ucIx);
static void SetRightSpin(unsigned char ucIx);
#endif //G_USE_ROTATION_DIRECTION

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetSpinDir(unsigned char ucIx);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetAxis(unsigned char ucIx);
#endif
#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucSetWP(unsigned char ucEcuPosition);
#endif
static void ResetWP(void);
static void PutulID(unsigned char ucIx,unsigned long *p2ID);
//static unsigned char ucGetZOMWP(unsigned char ucIx);
#ifdef BUILD_WITH_UNUSED_FUNCTION
static void ResetAxis(void);
#endif
static unsigned char ucGetFreeZOMPos(void);
static unsigned char ucStartWA(void);
static unsigned char ucLowestProbe(unsigned short ushException);
#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucAxisDetection(unsigned char ucMinRssiDistance, unsigned char ucMinVariationDistance);
#endif
#ifdef G_USE_ROTATION_DIRECTION
static unsigned char ucDirectionDetection(unsigned char ucLeRiMinDistance);
#endif //G_USE_ROTATION_DIRECTION
#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucWPConsistent(void);
#endif
static unsigned short ushCheckERState(unsigned char ucZomID);
static unsigned char ucCheckWheelPos(void);
static void SafeData(struct InputWA *ptInputWA, unsigned char ucIx);
static void DriveDir(unsigned char * pucStatus);
static unsigned char ucActualize(struct InputWA *ptInputWA, WAParameter *ptWAPar);
static void RestoreHistory(void);
static unsigned short ushSumPotenAndERWheels(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetMeanVariation( unsigned char ucIx);
#endif

static void SetWActiveState(unsigned char ucVal)
{
  if(ucVal == 0)
  {
   ucWAState &= NEGATE_UCHAR(cWAStateActive);
  }
  else{
   ucWAState |= cWAStateActive;
  }
}

static unsigned char ucGetWActiveState(void){
  return(((ucWAState & cWAStateActive) == cWAStateActive) ? (unsigned char) 1:(unsigned char) 0);
}

static void SetERState(unsigned char ucVal)
{
  if(ucVal == 0)
  {
   ucWAState &= NEGATE_UCHAR(cWAStateER);
  }
  else{
   ucWAState |= cWAStateER;
  }
}

unsigned char ucGetERState(void){
  return( ((ucWAState & cWAStateER) == cWAStateER) ? (unsigned char) 1:(unsigned char) 0);
}

static void SetZOState(unsigned char ucVal)
{
  if(ucVal == 0)
  {
   ucWAState &= NEGATE_UCHAR(cWAStateZO);
  }
  else{
   ucWAState |= cWAStateZO;
  }
}

static unsigned char ucGetZOState(void){
  return( ((ucWAState & cWAStateZO) == cWAStateZO) ? (unsigned char) 1:(unsigned char) 0);
}

static void SetWAStateZOChange(unsigned char ucChangedPos)
{
  ucWAState &= 0x0F;
  ucWAState |= ucChangedPos;
}

void ClearZOM(unsigned char ucIx)
{
  unsigned char i,j;

  if(ucIx > cSumWE)
  {

  }
  else{
   if(ucIx == (unsigned char) cSumWE)
   {
      for(i = 0; i < ucIx; i++)
      {
        for(j = 0; j < (unsigned char) sizeof(struct ZOMSlot);j++)
        {
          *((unsigned char *) &tZOM[i] + j) = 0;
        }
      }
   }
   else{
      for(j = 0; j < (unsigned char) sizeof(struct ZOMSlot);j++)
      {
        *((unsigned char *) &tZOM[ucIx] + j) = 0;
      }
   }

  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
static void ClearAxis(unsigned char ucIx)
{
  if(ucIx <= cMaxLR)
  {
   if(ucIx == cMaxLR)
   {
      for(ucIx = 0; ucIx < cMaxLR; ucIx++)
      {
        tZOM[ucIx].ucStatus &= cNoAxis;
      }
   }
   else{
        tZOM[ucIx].ucStatus &= cNoAxis;
   }
  }
  else{

  }
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
static void SetPair2OtherAxis(unsigned char uc1st, unsigned char uc2nd)
{
    tZOM[uc1st].ucStatus &= NEGATE_UCHAR(cECUAxis);
    tZOM[uc2nd].ucStatus &= NEGATE_UCHAR(cECUAxis);
    tZOM[uc1st].ucStatus |= cOtherAxis;
    tZOM[uc2nd].ucStatus |= cOtherAxis;
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
static void SetPair2ECUAxis(unsigned char uc1st, unsigned char uc2nd)
{
    tZOM[uc1st].ucStatus &= NEGATE_UCHAR(cOtherAxis);
    tZOM[uc2nd].ucStatus &= NEGATE_UCHAR(cOtherAxis);
    tZOM[uc1st].ucStatus |= cECUAxis;
    tZOM[uc2nd].ucStatus |= cECUAxis;
}
#endif

#ifdef G_USE_ROTATION_DIRECTION
static void ResetSpin(unsigned char ucIx)
{
  if(ucIx <= cMaxLR)
  {
   if(ucIx == cMaxLR)
   {
      for(ucIx = 0; ucIx < cMaxLR; ucIx++)
      {
        tZOM[ucIx].ucStatus &= cNoSpin;
      }
   }
   else{
      tZOM[ucIx].ucStatus &= cNoSpin;
   }
  }
  else{

  }
}

static void SetLeftSpin(unsigned char ucIx)
{
  if( ucIx < cMaxLR)
  {
    tZOM[ucIx].ucStatus &= NEGATE_UCHAR(cRightSpin);
    tZOM[ucIx].ucStatus |= cLeftSpin;
  }
  else{

  }
}

static void SetRightSpin(unsigned char ucIx)
{
  if( ucIx < cMaxLR)
  {
    tZOM[ucIx].ucStatus &= NEGATE_UCHAR(cLeftSpin);
    tZOM[ucIx].ucStatus |= cRightSpin;
  }
  else{

  }
}
#endif //G_USE_ROTATION_DIRECTION

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetSpinDir(unsigned char ucIx)
{
  if( ucIx < cMaxLR)
  {
    return ((unsigned char) (tZOM[ucIx].ucStatus & (NEGATE_UCHAR(cNoSpin))));
  }
  else{
    return ( (unsigned char) 0);
  }
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetAxis(unsigned char ucIx)
{
  if( ucIx < cMaxLR)
  {
    return ((unsigned char) (tZOM[ucIx].ucStatus & (NEGATE_UCHAR(cNoAxis))));
  }
  else{
    return ( (unsigned char) 0);
  }
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucSetWP(unsigned char ucEcuPosition)
{
  unsigned char i, ucRet = 1;
  for(i = 0; i < cMaxLR; i++)
  {
    tZOM[i].ucStatus &= cNoWPos;
   switch(tZOM[i].ucStatus)
   {
   case 0x50:
      {
        if(ucEcuPosition == ucECUPosFront)
        {
          tZOM[i].ucStatus |= cWP_FR;
        }
        else{
          tZOM[i].ucStatus |= cWP_RR;
        }
      }
      break;
   case 0x60:
      {
        if(ucEcuPosition == ucECUPosFront)
        {
          tZOM[i].ucStatus |= cWP_RR;
        }
        else{
          tZOM[i].ucStatus |= cWP_FR;
        }
      }
      break;
   case 0x90:
      {
        if(ucEcuPosition == ucECUPosFront)
        {
          tZOM[i].ucStatus |= cWP_FL;
        }
        else{
          tZOM[i].ucStatus |= cWP_RL;
        }
      }
      break;
   case 0xA0:
      {
        if(ucEcuPosition == ucECUPosFront)
        {
          tZOM[i].ucStatus |= cWP_RL;
        }
        else{
          tZOM[i].ucStatus |= cWP_FL;
        }
      }
      break;
    default:
      {

        ucRet = 0;
        break;
      }
   }
  }
  return(ucRet);
}
#endif

static void ResetWP(void){
  unsigned char i;

  for(i = 0; i < cMaxLR; i++)
  {
    tZOM[i].ucStatus &= cNoWPos;
  }
}

unsigned long ulGetZOMID(unsigned char ucIx)
{
  if(ucIx < cSumWE)
  {
    return (tZOM[ucIx].ulID);
  }
  else{
    return ( (unsigned char) 0);
  }
}

unsigned long ulGetID(unsigned char ucIx)
{
  if(ucIx < cMaxLR)
  {
    return (aulHistoryID[ucIx]);
  }
  else{
    return ( (unsigned char) 0);
  }
}

static void PutulID(unsigned char ucIx,unsigned long *p2ID)
{
  if(ucIx < cSumWE)
  {
    tZOM[ucIx].ulID = *p2ID;
  }
}

unsigned char ucGetProbeCt(unsigned char ucIx)
{
  if(ucIx < cSumWE)
  {
    return (tZOM[ucIx].ucProbeCt);
  }
  else{
    return ( (unsigned char) 0);
  }
}

unsigned char ucGetZOMWP(unsigned char ucIx)
{
  uint8 u8ReturnValue;
  if(ucIx < cMaxLR)
  {
   switch(tZOM[ucIx].ucStatus & (0xFF & ~cNoWPos))
   {
      case 0x01:
      {
        u8ReturnValue = 0U;
        break;
      }
      case 0x02:
      {
        u8ReturnValue = 1U;
        break;
      }
      case 0x04:
      {
        u8ReturnValue = 2U;
        break;
      }
      case 0x08:
      {
        u8ReturnValue = 3U;
        break;
      }
      default:
      {
        u8ReturnValue = 4U;
        break;
      }
   }
  }
  else{
   u8ReturnValue = 4U;
  }
  return u8ReturnValue;
}

void SetZOMWP(unsigned char ucIx,unsigned char ucWP)
{
  if(ucIx < cMaxLR)
  {
    tZOM[ucIx].ucStatus &= cNoWPos;
   if(ucWP < cMaxLR)
   {
      tZOM[ucIx].ucStatus |= (unsigned char) (0x01 << ucWP);
   }
  }
}

unsigned short ushGetMeanRssiSum( unsigned char ucIx ){
  unsigned long ulTmp;

  if(ucIx < cSumWE){
   if(tZOM[ucIx].ucProbeCt != 0){
      ulTmp = ((((unsigned long)tZOM[ucIx].ushRssiSum * 10) / tZOM[ucIx].ucProbeCt) + (unsigned char)5) / (unsigned char)10;
   }
   else{
      ulTmp = 0U;
   }
  }
  else{
   ulTmp = 0U;
  }
  return ((unsigned short)ulTmp);
}

unsigned char ucGetRssiDifference(unsigned char ucFirstIx, unsigned char ucSecondIx)
{
  unsigned char ucFirstRssi = 0;
  unsigned char ucSecondRssi = 0;

  ucFirstRssi = (unsigned char)ushGetMeanRssiSum(ucFirstIx);
  ucSecondRssi = (unsigned char)ushGetMeanRssiSum(ucSecondIx);

  if(ucFirstRssi > ucSecondRssi)
  {
    return ucFirstRssi - ucSecondRssi;
  }
  else{
    return ucSecondRssi - ucFirstRssi;
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned char ucGetMeanVariation( unsigned char ucIx)
{
  unsigned long ulTmp;

  if(ucIx < cSumWE)
  {
   ulTmp = (((unsigned long) (tZOM[ucIx].ushVariation * 10) / tZOM[ucIx].ucProbeCt) + (unsigned char) 5) / (unsigned char) 10;
    return ( (unsigned char) (0xFF & ulTmp) );
  }
  else{
    return ( (unsigned char) 0);
  }
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
static void ResetAxis(void){
  unsigned char i;
  for(i = 0; i < cSumWE; i++)
  {
    tZOM[i].ucStatus &= cNoAxis;
    tZOM[i].ushRssiSum = 0;
    tZOM[i].ushVariation = 0;
    tZOM[i].ucProbeCt = 0;
  }
  SetERState(0);
}
#endif

unsigned char ucGetZOMPosOfID(unsigned long *pt2ID)
{
  unsigned char i;
  for(i = 0; i < cSumWE; i++)
  {
   if(*pt2ID == tZOM[i].ulID)
   {
      break;
   }
  }
  return(i);
}

static boolean bGetZomPotentStatusOfID(unsigned char ucIx)
{
  if(tZOM[ucIx].bPotNewID == 0x01U)
  {
    return TRUE;
  }
  else{
    return FALSE;
  }
}

static boolean bGetZomOwnStatusOfID(unsigned char ucIx)
{
  if(tZOM[ucIx].bOwnID == 0x01U)
  {
    return TRUE;
  }
  else{
    return FALSE;
  }
}

unsigned char ucGetColOfID(unsigned long *pt2ID)
{
  unsigned char i;
  for(i = 0; i < cMaxLR; i++)
  {
   if(*pt2ID == aulHistoryID[i])
   {
      break;
   }
  }
  return(i);
}

unsigned char ucGetWPOfCol(unsigned char ucIx)
{
  if(ucIx < cMaxLR)
  {
    return (aucHistoryWP[ucIx]);
  }
  else{
    return ((unsigned char) 4);
  }
}

unsigned char ucGetIndexOfHistoryWP(unsigned char ucWPNumber)
{
   unsigned char i;
   for(i = 0; i < cMaxLR; i++)
   {
   	if(ucWPNumber == aucHistoryWP[i])
   	{
   		break;
   	}
   }
   return i;
}

static unsigned char ucGetFreeZOMPos(void){
  unsigned char i;
  for(i = 0; i < cSumWE; i++)
  {
   if(tZOM[i].ulID == (unsigned long) 0)
   {
      break;
   }
  }
  return(i);
}

static unsigned char ucStartWA(void){
  unsigned char i, ucRet = 0;

  for(i = 0; i < cSumWE; i++)
  {
   if(tZOM[i].ucProbeCt > 0)
   {
      ucRet++;
   }
  }
  ucRet  =  (ucRet == cMaxLR) ? (unsigned char) 1:(unsigned char) 0;
  return(ucRet);
}

void AlignZOM(unsigned short ushERSlot)
{
  unsigned char i, j, k, ucCt = 0;

  for(i = 0; i < cSumWE; i++)
  {
   if((((unsigned short ) (1<<i)) & ushERSlot) > 0)
   {
      ucCt++;
   }
   else{
      for(j = i+1; j < cSumWE; j++)
      {
        if((((unsigned short ) (1<<j)) & ushERSlot) > 0)
        {
          ucCt++;
          for(k = 0; k < (unsigned char) sizeof(struct ZOMSlot); k++)
          {
            *(((unsigned char *) &tZOM[i]) + k) = *(((unsigned char *) &tZOM[j]) + k);
          }
          ushERSlot |= (1<<i);
          ushERSlot &= ~(1<<j);
          ClearZOM(j);
          break;
        }
      }
   }
   if(ucCt == cMaxLR)
   {
      break;
   }
  }
}

static unsigned char ucLowestProbe(unsigned short ushException)
{
  unsigned char i, ucMinIx = 0x80;

  for( i = 0; i < cSumWE; i++)
  {
   if(((unsigned short )(0x01<<i) & ushException) == 0)
   {

      if(ucMinIx == 0x80)
      {
        ucMinIx = i;
      }
      else{
        if(ucGetProbeCt(i) < ucGetProbeCt(ucMinIx))
        {
          ucMinIx = i;
        }
      }
   }
  }

  return( (ucMinIx & 0x7F) );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

static unsigned char ucAxisDetection(unsigned char ucMinRssiDistance, unsigned char ucMinVariationDistance)
{
  unsigned char i, ucLeIx = 0, ucRiIx = 0, aucLeft[2], aucRight[2];
  aucLeft[0] = 0;
  aucLeft[1] = 0;
  aucRight[0] = 0;
  aucRight[1] = 0;
  for(i = 0; i < cMaxLR; i++)
  {
   if(ucGetSpinDir(i) == cRightSpin)
   {
      aucRight[ucRiIx] = i;
      ucRiIx++;
   }
   else{
      aucLeft[ucLeIx] = i;
      ucLeIx++;
   }
  }
  if(ushGetMeanRssiSum(aucRight[0]) < ushGetMeanRssiSum(aucRight[1]))
  {
   i = aucRight[1];
    aucRight[1] = aucRight[0];
    aucRight[0] = i;
  }
  if(ushGetMeanRssiSum(aucLeft[0]) < ushGetMeanRssiSum(aucLeft[1]))
  {
   i = aucLeft[1];
    aucLeft[1] = aucLeft[0];
    aucLeft[0] = i;
  }
#ifdef pb_Debug4MB_010404
  ucLeftRSDistDG = ushGetMeanRssiSum(aucLeft[0]) - ushGetMeanRssiSum(aucLeft[1]);
  ucRightRSDistDG = ushGetMeanRssiSum(aucRight[0]) - ushGetMeanRssiSum(aucRight[1]);
#endif
  if( (ushGetMeanRssiSum(aucRight[0]) - ushGetMeanRssiSum(aucRight[1])) >= ucMinRssiDistance)
  {
   if( (ushGetMeanRssiSum(aucLeft[0]) - ushGetMeanRssiSum(aucLeft[1])) >= ucMinRssiDistance)
   {

      SetPair2OtherAxis(aucLeft[1], aucRight[1]);
      SetPair2ECUAxis(aucLeft[0], aucRight[0]);
      i = 1;
   }
   else{
      ClearAxis(cMaxLR);
      i = 0;
   }
  }
  else{
   ClearAxis(cMaxLR);
   i = 0;
  }
  return(i);
}
#endif

#ifdef G_USE_ROTATION_DIRECTION
static unsigned char ucDirectionDetection(unsigned char ucLeRiMinDistance)
{
  unsigned char i, ucRet = 0, ucLeSum = 0, ucRiSum = 0;
  void (* fpt2SetLeRiSpin) (unsigned char FuncPointer);

  for(i = 0; i < cMaxLR; i++)
  {
   if(tZOM[i].ucRightCt > tZOM[i].ucLeftCt)
   {
      if((tZOM[i].ucRightCt - tZOM[i].ucLeftCt) >= ucLeRiMinDistance)
      {
        SetRightSpin(i);
        ucRet |= (((unsigned char) 1) << i);
        ucRiSum++;
      }
      else{
        ResetSpin(i);
      }
   }
   else{
      if((tZOM[i].ucLeftCt - tZOM[i].ucRightCt) >= ucLeRiMinDistance)
      {
        SetLeftSpin(i);
        ucRet |= (((unsigned char) 1) << i);
        ucLeSum++;
      }
      else{
        ResetSpin(i);
      }
   }
  }
  if((ucRiSum > 2) || (ucLeSum > 2))
  {
   for(i = 0; i < cMaxLR; i++)
   {
      ResetSpin(i);
      tZOM[i].ucLeftCt = 0;
      tZOM[i].ucRightCt = 0;
   }
   ucRet = 0;
  }
  else{
   if(ucRet != 0x0F)
   {
      if(( ucRiSum == 2 ) || ( ucLeSum == 2 ))
      {
        if(ucRiSum == 2)
          {fpt2SetLeRiSpin = SetLeftSpin;}
        else{fpt2SetLeRiSpin = SetRightSpin;}
        for(i = 0; i < cMaxLR; i++)
        {
          if((ucRet & (((unsigned char) 1) << i)) == 0)
          {
            if((tZOM[i].ucLeftCt > 0) && (tZOM[i].ucRightCt >0))   // really unknown and not only reset
            {
                fpt2SetLeRiSpin(i);
                ucRet |= (((unsigned char) 1) << i);
            }
          }
        }
      }
   }
  }
  return(ucRet);
}
#endif //G_USE_ROTATION_DIRECTION

#ifdef BUILD_WITH_UNUSED_FUNCTION

static unsigned char ucWPConsistent(void){
  unsigned char j,ucRet = 0;

  for(j = 1; j < 4;j++)
  {
   if( ucGetSpinDir(0) == ucGetSpinDir(j) )
   {
      if( ucGetAxis(0) != ucGetAxis(j) )
      {
        ucRet = j;
        break;
      }
   }
  }
  if(ucRet > 1)
  {
   switch(ucRet)
   {
   case 2:
      {
        ucRet = 1;
        j = 3;
      }
      break;
   case 3:
      {
        ucRet = 1;
        j = 2;
      }
      break;
    default:
      ucRet = 0;
      break;
   }
   if(ucRet > 0)
   {
      if(ucGetSpinDir(0) != ucGetSpinDir(ucRet))
      {
        if( ucGetSpinDir(ucRet) == ucGetSpinDir(j) )
        {
          if( ucGetAxis(ucRet) != ucGetAxis(j) )
          {
            ucRet = 1;
          }
          else{
            ucRet = 0;
          }
        }
        else{
          ucRet = 0;
        }
      }
      else{
        ucRet = 0;
      }
   }
   else{
      ucRet = 0;
   }
  }
  return(ucRet);
}
#endif

unsigned char ucSumCtID(unsigned char ucMinCt, unsigned char ucMinRssi)
{
  unsigned char i, ucCt= 0;

  for( i = 0; i < cSumWE; i++)
  {
   if((ucGetProbeCt(i) >= ucMinCt) &&
    ( ushGetMeanRssiSum(i) >= ucMinRssi))
   {
      ucCt++;
   }
  }
  return(ucCt);
}

static unsigned short ushCheckERState(unsigned char ucZomID)
{
  unsigned short ushRet = 0;
  unsigned char i;

  //check and mark ID as ER, based on amount of receive events, RSSI-level and procentual counter difference to other IDs
  CheckAndMarkNewIdER(ucZomID);

  //#3.13 Check ER wheels number
  ushRet = ushSumPotenAndERWheels();

  if(ucSumCtID(tWAPar.ucMinCt4ZomReset, tWAPar.ucMinERMeanRssiLevel) > cMaxLR)
  {
   ClearZOM(cSumWE);
   ushRet = 0;
  }

  if(ucNrOfBitSet(ushRet) == cMaxLR)
  {
   for(i = 0; i < cSumWE; i++) //#3.14 Switch mark of all potential new wheel sensor to own wheel sensor
   {
      if(tZOM[i].bPotNewID == 0x01U)
      {
        tZOM[i].bPotNewID = FALSE;
        tZOM[i].bOwnID = TRUE;
      }
   }
  }
  else{
   ushRet = 0;
  }

  return(ushRet);
}

static void CheckAndMarkNewIdER(unsigned char ucIx)
{
  unsigned char i, ucRet = 0;
  boolean bHistID;

  for(i = 0; i < cMaxLR; i++)
  {
   if(aulHistoryID[i] == ulGetZOMID(ucIx)) //#3.4 compare with History
   {
      if(ucGetProbeCt(ucIx) >= tWAPar.ucMinCt4HistER) // #3.5  compare with minimum number of received telegrams needed for ER
      {
        //#3.12 mark as own wheel/ER
        tZOM[ucIx].bOwnID = TRUE;
      }
      bHistID = TRUE;
      break;
   }
   else{
      bHistID = FALSE;
   }
  }

  if(FALSE == bHistID)
  {//not a history wheel
    //#3.6 Check if there is a history and commutative driving time
   if((FALSE == ucGetHistoryState()) || (TRUE == bGetHistProtecTimeOver()))
   {
      for(i = 0; i < cSumWE; i++)
      {
        tZOM[i].bPotNewID = TRUE; //#3.7 Mark potential new IDs

        if(!((tZOM[i].ucProbeCt >= tWAPar.ucMinCt4ER) && (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt))) //#3.8 Rx events of new ID
        {
          tZOM[i].bPotNewID = FALSE;
        }

        if(tZOM[i].bPotNewID == TRUE)
        {
          //#3.10 Determine and compare percent differences
          if((tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 4]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]]) < tWAPar.ucnMinA) // 15% between the max and min abs relative counter value
          {
            tZOM[i].bPotNewID = FALSE;
            if(ushGetMeanRssiSum(i) > tWAPar.ucMinERMeanRssiLevel){
              tZOM[i].bPotNewID = TRUE;
            }
          }
          if(ushGetMeanRssiSum(i) < tWAPar.ucMinERMeanRssiLevel){
            tZOM[i].bPotNewID = FALSE;
          }
        }
      }
   }
  }
}

static unsigned short ushSumPotenAndERWheels(void){
  unsigned char i;
  unsigned short ushRet = 0;
  for(i = 0; i < cSumWE; i++)
  {
   if((TRUE == (bGetZomPotentStatusOfID(i))) || (TRUE == (bGetZomOwnStatusOfID(i))))
   {
      ushRet |= (unsigned short)(1 << i);
   }
  }
  return ushRet;
}

static unsigned char ucCheckWheelPos(void){
  unsigned short ushRet = 0;
#ifdef FPA
  //New APC algorithm
#ifdef G_USE_ROTATION_DIRECTION
  ucDirectionDetection(tWAPar.ucLeRiMinDistance);
#endif //G_USE_ROTATION_DIRECTION
  ushRet = ucConceptFixPos0();
  if(ushRet == 0)
  {
    ResetWP();
  }
#else
//old Y400 algorithm
  if( ucDirectionDetection(tWAPar.ucLeRiMinDistance) == 0x0F )
  {
   ucSumCtID(tWAPar.ucMinCt4AxAnalysis, (unsigned char) 0, &ushRet);
   if( 0x000F == (ushRet & 0x000F) )
   {
      ushRet = 0;
      if(ucAxisDetection(tWAPar.ucMinRssiDistance, tWAPar.ucMinVariationDistance) == 1)
      {
        if(ucWPConsistent() == 1)
        {

          if(ucSetWP(tWAPar.ucEcuPosition) == 1)
          {
            ushRet = 1;
          }
          else{

            ResetWP();
          }
        }
        else{
          ResetAxis();
#ifdef DETECT_SYMC_WALLOC_DTC
        IncWPConsistentError();
#endif

        }
      }
      else{
        ResetWP();
#ifdef DETECT_SYMC_WALLOC_DTC
        IncAxisDetectionError();
#endif
      }
   }
   else{
      ushRet = 0;
   }
  }
  else{
    ResetWP();
#ifdef DETECT_SYMC_WALLOC_DTC
    IncDirDetectionError();
#endif
  }
#endif
  return((unsigned char) ushRet);
}

static unsigned char ucNrOfBitSet(unsigned short ushTarget)
{
  unsigned char i, ucHits= 0;

  for(i = 0; i < 16; i ++)
  {
   if((ushTarget & (1<<i)) > 0)
   {
      ucHits++;
   }
  }
  return (ucHits);
}

static unsigned short ushIDSetInHist(unsigned long *ptHistSet, unsigned char ucMinProbeCt
   ,                                    unsigned char ucSlots2Search)
{
  unsigned char i,j;
  unsigned short ushRet = 0;

  for( i = 0; i < cMaxLR; i++)
  {
   if(ptHistSet[i] == cInitHistID)
   {
      ushRet = 0;
      break;
   }
   else{
      for( j = 0; j < ucSlots2Search; j++)
      {
        if((ptHistSet[i] == ulGetZOMID(j)) && (ucGetProbeCt(j) >= ucMinProbeCt ))
        {
          ushRet |= (1<<j);
          break;
        }
        else{
          if(ulGetZOMID(j) == (unsigned long) 0)
          {
            break;
          }
        }
      }
   }
  }
  return (ushRet);
}

static void SafeData(struct InputWA *ptInputWA, unsigned char ucIx)
{
  if(ucIx < cSumWE)
  {

   if(tZOM[ucIx].ulID >(unsigned long) 0)
   {
      tZOM[ucIx].ushVariation += (tZOM[ucIx].ucLastRssi > ptInputWA->ucRssi) ? (tZOM[ucIx].ucLastRssi - ptInputWA->ucRssi):(ptInputWA->ucRssi - tZOM[ucIx].ucLastRssi);
   }
   else{
      tZOM[ucIx].ulID = ptInputWA->ulID;
   }
    tZOM[ucIx].ucLastRssi = ptInputWA->ucRssi;
    tZOM[ucIx].ucSkipNewTelTimerInSec = 9;

   if( (tZOM[ucIx].ucProbeCt < (unsigned char) 255))
#ifdef G_USE_ROTATION_DIRECTION
      &&  (tZOM[ucIx].ucLeftCt  < (unsigned char)255)
      &&  (tZOM[ucIx].ucRightCt < (unsigned char)255))
#endif //G_USE_ROTATION_DIRECTION
   {
      if( ((unsigned short) 65535 - tZOM[ucIx].ushRssiSum) > ptInputWA->ucRssi ){
        tZOM[ucIx].ushRssiSum += ptInputWA->ucRssi;
        tZOM[ucIx].ucProbeCt++;
#ifdef G_USE_ROTATION_DIRECTION
        if( (ptInputWA->ucStatus & cIDStateSpinLeft) == cIDStateSpinLeft)
        {
          tZOM[ucIx].ucLeftCt++;
        }
        if( (ptInputWA->ucStatus & cIDStateSpinRight) == cIDStateSpinRight)
        {
          tZOM[ucIx].ucRightCt++;
        }
#endif //G_USE_ROTATION_DIRECTION

        if( (tZOM[ucIx].ucProbeCt == (unsigned char) 255))
#ifdef G_USE_ROTATION_DIRECTION
           || (tZOM[ucIx].ucLeftCt  == (unsigned char) 255)
           || (tZOM[ucIx].ucRightCt == (unsigned char) 255)    )
#endif //G_USE_ROTATION_DIRECTION
        {
          tWAPar.ucWACtrl |= ucWACtrlFixc;
        }
      }
      else{
        tWAPar.ucWACtrl |= ucWACtrlFixc;
      }
   }
   else{
      tWAPar.ucWACtrl |= ucWACtrlFixc;
   }
  }
  else{
  }
}

static void DriveDir(unsigned char * pucStatus)
{

  if(((*pucStatus) & cIDStateSpinning) > 0)
  {
   if(((*pucStatus) & cIDStateSpinning) != cIDStateSpinning)
   {
      if(((*pucStatus) & cIDStateNoDrvInfo) == cIDStateNoDrvInfo)
      {
        *pucStatus |= cIDStateSpinning;
      }
      else{
        if(((*pucStatus) & cIDStateDrvBack) == cIDStateDrvBack)
        {
          *pucStatus = (unsigned char) ~ (*pucStatus);
        }
      }
   }
  }

 *pucStatus &= cIDStateSpinning;
}

static unsigned char ucActualize(struct InputWA *ptInputWA, WAParameter *ptWAPar)
{
  unsigned char ucRetVal = cSumWE;
  unsigned char ucIx = cSumWE;
  boolean bTelAllowed = FALSE;
  unsigned char ucNewAPCData = FALSE;

  ucIx = ucGetZOMPosOfID(&ptInputWA->ulID);

  bTelAllowed = bCheckIfNewTelAllowed(ptInputWA, ucIx);

  if(TRUE == bTelAllowed)
  {

    DriveDir((unsigned char *) &(ptInputWA->ucStatus));

   if(ucIx < cSumWE)
   {
      if(ptInputWA->ucRssi > 0)
      {
        SafeData(ptInputWA, ucIx);
      }
      else{
        bTelAllowed = FALSE;
      }
   }
   else{
      ucIx = ucGetFreeZOMPos();
      if(ucIx < cSumWE)
      {
        if(ptInputWA->ucRssi >= ptWAPar->ucMinRssiLevel)
        {
          SafeData(ptInputWA, ucIx);
        }
        else{
          bTelAllowed = FALSE;
        }
      }
      else{
        if(ucGetERState() == 0)
        {
          ucIx = ucLowestProbe(ushIDSetInHist(aulHistoryID, (unsigned char) 1, cSumWE));
          //if(ucIx < cSumWE)      //SSC, 17.10.2017, WBT-finding:commented out because ucLowestProbe() returns always a valid value < 8. It means that if RSSI level is high enough the new ID will replace the ID in ZOM slot
          //{
            if(ptInputWA->ucRssi >= ptWAPar->ucMinRssiLevel)
            {
              ClearZOM(ucIx);
              SafeData(ptInputWA, ucIx);
            }
            else{
              bTelAllowed = FALSE;
            }
          //}
          //else
          //{
          //  bTelAllowed = FALSE;
          //}
        }
        else{
          bTelAllowed = FALSE;
        }
      }
   }
  }
  else{
   bTelAllowed = FALSE;
  }

  if(ucIx < cSumWE)
  {
   ucNewAPCData = CounterPreparation(ucIx, pGetCurTel());
  }
  else{

  }

  if((FALSE != bTelAllowed)||(FALSE != ucNewAPCData))
  {

   ucRetVal = ucIx;
  }
  else{

   ucRetVal = cSumWE;
  }

  return (ucRetVal);
}

unsigned char ucSetHistory(unsigned char ucType)
{
  unsigned char i,j, ucRet = 0x0f;

  GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
  GetWADataEE(cHistoryWPSet1, aucHistoryWP );
  for(i = 0; i < cMaxLR; i++)
  {
   for(j = 0; j < cMaxLR; j++)
   {
      if( aulHistoryID[i] == ulGetZOMID(j) )
      {
        ucRet &= (NEGATE_UCHAR((0x01 << j)));
        if(ucType == cWAStateZO)
        {
          if(ucGetZOMWP(j) == aucHistoryWP[i])
          {

          }
          else{
            aucHistoryWP[i] = ucGetZOMWP(j);
            ucRet |= (unsigned char) (0x10 << i);
          }
        }
        break;
      }
   }
   if( j == cMaxLR )
   {
      aucHistoryWP[i] = ucGetZOMWP(j);
      ucRet |= (unsigned char) (0x10 << i);
   }
  }
  if(ucRet > 0)
  {
   if(ucType == cWAStateZO)
   {
      ucRet &= (unsigned char) 0xF0;
   }
   else{
      ucType = ucRet & 0xF0;
      for(i = 0; i < cMaxLR; i++)
      {
        if((ucRet & (0x01 << i)) > 0)
        {
          for( j = 0; j < cMaxLR; j++)
          {
            if((ucRet & ((unsigned char) (0x10 << j))) > 0)
            {
              if(ulGetZOMID(i) != 0x00000000)
              {
                aulHistoryID[j] = ulGetZOMID(i);
              }
              else{
                aulHistoryID[j] = cInitHistID;
              }
              ucRet &= (NEGATE_UCHAR((0x10 << j)));
              break;
            }
          }
        }
      }
      ucRet = ucType;
   }
   PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
   PutWADataEE(cHistoryWPSet1, aucHistoryWP);
  }
  return (ucRet);
}

static void RestoreHistory(void){
  unsigned char i,j,ucCt = 0;

  if(aulHistoryID[0] < cInitHistID)
  {
   if( ucGetERState() == 1 )
   {
      for( i = 0; i < cMaxLR; i++)
      {
        for( j = 0; j < cMaxLR; j++ )
        {
          if((aulHistoryID[j] == ulGetZOMID(i)) && (aucHistoryWP[j] < 4) )
          {
            SetZOMWP(i,aucHistoryWP[j]);
            ucCt++;
          }
        }
      }
   }
   else{
      for( i = 0; i < cMaxLR; i++)
      {
        PutulID(i,&aulHistoryID[i]);
        if(aucHistoryWP[i] < 4)
        {
          SetZOMWP(i, aucHistoryWP[i]);
          ucCt++;
        }
      }
      SetERState(1);
   }
   if(ucCt < cMaxLR)
   {
      for( i = 0; i < cMaxLR; i++)
      {
        SetZOMWP(i, cWPER);
      }
   }
   else{
      SetZOState(1);
   }
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void InitHistory(void){
  unsigned char i;

   for(i = 0; i < cMaxLR; i++)
   {
      aulHistoryID[i] = cInitHistID;
      aucHistoryWP[i] = cNoWPos;
   }
   PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
   PutWADataEE(cHistoryWPSet1, aucHistoryWP);
}
#endif //BUILD_WITH_UNUSED_FUNCTION

unsigned char  ucLearnID(struct InputWA *ptInputWA)
{
  unsigned short ushHelp;
  unsigned char ucCurID;

  if(ucGetZOState() == 1)
  {

  }
  else{
   if((tWAPar.ucWACtrl & ucWACtrlFixc) > 0)
   {
      RestoreHistory();
   }
   else{
      if((tWAPar.ucWACtrl & ucWACtrlBreakc) == 0)
      {

        ucCurID = ucActualize(ptInputWA, &tWAPar);
        if( ucCurID < cSumWE)
        {
          if(ucGetWActiveState() == 0)
          {
            if( ucStartWA() == 1 )
            {
              SetWActiveState(1);
              StartWATO(tWAPar.WATOTimeInSec);
            }
          }

          if(ucGetERState() == 0)
          {
            ushHelp = ushCheckERState(ucCurID);
            if(ushHelp > 0)
            {
              SetERState(1);
              AlignZOM(ushHelp);
              SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateER));
              //check if any ER IDs did change compared to history, if yes - delete old warning vector from old ID
              ResetOldWarningsByNewEr(ucWAState, cMaxLR);
#if(defined HUF_DEBUG) && (defined WIN32)
              print("\n\nEigenrad erreicht!\n");
              print("ID 1: %10u\n",m_aulHistoryID[0]);
              print("ID 2: %10u\n",m_aulHistoryID[1]);
              print("ID 3: %10u\n",m_aulHistoryID[2]);
              print("ID 4: %10u\n",m_aulHistoryID[3]);
              print("\n");
#endif
              if(ucCheckWheelPos() == 1)     //(#4.0)
              {
                CancelWATO();
                SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO));
                SetZOState(1);
              }
            }
          }
          else{
            if(ucCheckWheelPos() == 1)       //(#4.0)
            {
              CancelWATO();
              SetWAStateZOChange(ucSetHistory((unsigned char)cWAStateZO));
              SetZOState(1);
#if(defined HUF_DEBUG) && (defined WIN32)
              print("\n\nZugeordnet erreicht!\n");
              print("ID 1: %10u, Pos: %u\n",m_aulHistoryID[0],m_aucHistoryWP[0]);
              print("ID 2: %10u, Pos: %u\n",m_aulHistoryID[1],m_aucHistoryWP[1]);
              print("ID 3: %10u, Pos: %u\n",m_aulHistoryID[2],m_aucHistoryWP[2]);
              print("ID 4: %10u, Pos: %u\n",m_aulHistoryID[3],m_aucHistoryWP[3]);
              print("\n");
#endif
            }
          }
        }
        else{

        }
      }
   }
  }
  return(ucWAState);
}

unsigned char ucWATO(void){
  unsigned short ushHelp = 0;
  unsigned char ucRet = 0;

  if(ucGetZOState() < 1)
  {

   ushHelp = ushIDSetInHist(aulHistoryID, tWAPar.ucMinCt4HistER, cSumWE);
   if(cMaxLR == ucNrOfBitSet(ushHelp))
   {
      if(ucGetERState() < 1)
      {
        AlignZOM(ushHelp);
        SetERState(1);
      }
#ifdef ZWANGSZUORDNUNG_NACH_TO
      if(ucNrOfTOs >= (tWAPar.ucTimeoutAutoLoc - 1))//-> Zwangszuordnung nach ZO-Timeout
      {
        RestoreHistory();
      }
#else
      RestoreHistory(); //-> Zwangszuordnung nach ca. 1 Minute
#endif
   }
   if(ucGetZOState() != 0)
   {
      CancelWATO();
      SaveDebugAllocType(0x80);
   }
   else{
      if(ucNrOfTOs >= (tWAPar.ucTimeoutAutoLoc - 1))
      {
        if(ucGetERState() < 1)
        {
          if(ucGetFreeZOMPos() > cMaxLR)
          {
            ucRet = 5;
          }
          else{
            if(ucGetFreeZOMPos() < cMaxLR)
            {
              ucRet = 9;
            }
            else{
              ucRet = 1;
            }
          }
        }
        else //-> Timeout ZO Error!
        {
#ifdef DETECT_SYMC_WALLOC_DTC
          ucRet = CheckForDetailed_ZO_Error();
#else
          ucRet = 2;
#endif
        }
      }
      else{
        StartWATO(tWAPar.WATOTimeInSec);
      }
   }
  }
  else{
   CancelWATO();
  }

  if(ucNrOfTOs < 0xFF)
  {
   ucNrOfTOs++;
  }

  return (ucRet);
}

uint8 ucSetID(uint32 *pt2ID, uint8 *pt2Pos)
{
  uint8 u8IndexFromPos, u8IndexFromID, ucStoredIDPosition, u8ReturnValue;
  u8ReturnValue = 0;
  if((pt2ID[0] == (uint32) 0x00000000U) || (pt2ID[0] == cInitHistID))
  {
    ResetHistoryToDefault();
    (void) WAInit();
   u8ReturnValue = 0x0F;
  }
  else{
    GetWADataEE(cHistorySet1, (uint8 *) aulHistoryID);
    GetWADataEE(cHistoryWPSet1, aucHistoryWP);
   if(pt2Pos[0] < cMaxLR)
   {
      u8IndexFromID = ucGetColOfID(pt2ID);
      if( u8IndexFromID == cMaxLR )
      {
        for(u8IndexFromPos = 0; u8IndexFromPos < cMaxLR; u8IndexFromPos++)
        {
          if(pt2Pos[0] == aucHistoryWP[u8IndexFromPos])
          {
            break;
          }
        }
        if(u8IndexFromPos == cMaxLR)
        {
          ucStoredIDPosition = pt2Pos[0];
          aulHistoryID[ucStoredIDPosition] = pt2ID[0];
          aucHistoryWP[ucStoredIDPosition] = pt2Pos[0];
          u8ReturnValue |= (0x10 << pt2Pos[0]);
        }
        else{
          aulHistoryID[u8IndexFromPos] = pt2ID[0];
          aucHistoryWP[u8IndexFromPos] = pt2Pos[0];
          u8ReturnValue |= (0x10 << pt2Pos[0]);
        }
        if(ucGetZOState() == 1)
        {
          ucStoredIDPosition = ucGetZOMPosOfID(&pt2ID[0]);
          tZOM[ucStoredIDPosition].ulID = pt2ID[0];
          SetZOMWP(ucStoredIDPosition, pt2Pos[0]);
          u8ReturnValue |= (1 << ucStoredIDPosition);
        }
        else{
          u8ReturnValue |= (1 << pt2Pos[0]);
        }
      }
      else{
        if(pt2Pos[0] == aucHistoryWP[u8IndexFromID])
        {
          u8ReturnValue = 0;
        }
        else{
          for(u8IndexFromPos = 0; u8IndexFromPos < cMaxLR; u8IndexFromPos++)
          {
            if(pt2Pos[0] == aucHistoryWP[u8IndexFromPos])
            {
              break;
            }
          }
          if(u8IndexFromPos < cMaxLR)
          {
            ucStoredIDPosition = aucHistoryWP[u8IndexFromID];
            aucHistoryWP[u8IndexFromID] = pt2Pos[0];
            aucHistoryWP[u8IndexFromPos] = ucStoredIDPosition;
            u8ReturnValue |= (0x10 << pt2Pos[0]);
          }
          else{
   		  if(cMaxLR <= aucHistoryWP[u8IndexFromID])
   		  {
   			  aucHistoryWP[u8IndexFromID] = pt2Pos[0];
   			  u8ReturnValue |= (0x10 << pt2Pos[0]);
   		  }
          }

          if(ucGetZOState() == 1)
          {
            ucStoredIDPosition = ucGetZOMPosOfID(&pt2ID[0]);
            tZOM[ucStoredIDPosition].ulID = pt2ID[0];
            SetZOMWP(ucStoredIDPosition, pt2Pos[0]);
            u8ReturnValue |= (1 << ucStoredIDPosition);
          }
          else{
            u8ReturnValue |= (1 << pt2Pos[0]);
          }
        }
      }

      if(u8ReturnValue > 0)
      {
        PutWADataEE(cHistorySet1, (uint8 *) aulHistoryID);
        PutWADataEE(cHistoryWPSet1, aucHistoryWP);
      }
   }
   else{

      u8ReturnValue = 0;
   }
  }
  return u8ReturnValue;
}

#if 0
unsigned char ucSetID(unsigned long *pt2ID, unsigned char *pt2Pos, unsigned char ucSum)
{
  unsigned char i, j, ucRet = 0, ucHelp;
  unsigned long ulBufID;

  ucSum = (ucSum > cMaxLR) ? cMaxLR:ucSum;

  if((pt2ID[0] == (unsigned long) 0) || (pt2ID[0] == cInitHistID))
  {
   for( i = 0; i < cMaxLR; i++)
   {
      aulHistoryID[i] = cInitHistID;
      aucHistoryWP[i] = 4;
   }
   PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
   PutWADataEE(cHistoryWPSet1, aucHistoryWP);
    WAInit();
   ucRet = 0x0F;
  }
  else{
    GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
    GetWADataEE(cHistoryWPSet1, aucHistoryWP);
   if((aulHistoryID[0] == cInitHistID) && (ucSum == 1))
   {
      for(i = 0; i < cMaxLR; i++)
      {
        aulHistoryID[i] = i + 1;
        if( pt2Pos[0] > 3 )
        {
          aucHistoryWP[i] = 4;
        }
        else{
          aucHistoryWP[i] = i;
        }
      }
   }

   ucHelp = 0x0f;
   for(i = 0; i < ucSum; i++)
   {
      for(j = 0; j < cMaxLR; j++)
      {
        if(pt2ID[i] == aulHistoryID[j])
        {
          ucHelp &= (NEGATE_UCHAR( (0x01 << j) ));
          break;
        }
      }
   }

   for(i = 0; i < ucSum; i++)
   {
      for(j = 0; j < cMaxLR; j++)
      {
        if(pt2ID[i] == aulHistoryID[j])
        {
          break;
        }
      }
      pt2Pos[i] = (pt2Pos[i] < (unsigned char) 9) ? pt2Pos[i]:4;
      if(j == cMaxLR)
      {
        if( pt2Pos[i] > cWheelPos_RR)
        {
          if( pt2Pos[i] == (unsigned char) 4 )
          {
            ucRet = 0;
            i = ucSum;
          }
          else{
            ucHelp = pt2Pos[i] - (unsigned char) 5;
            aulHistoryID[ucHelp] = pt2ID[i];
            aucHistoryWP[ucHelp] = (unsigned char) 4;
            ucRet |= (0x10 << ucHelp);
            SetZOState(0);
          }
        }
        else{
          for(j = 0; j < cMaxLR; j++)
          {
            if(pt2Pos[i] == aucHistoryWP[j])
            {
              break;
            }
          }
          if( j == cMaxLR )
          {
            for(j = 0; j < cMaxLR; j++)
            {
              if((ucHelp & (unsigned char)(0x01 << j)) > 0)
              {
                ucHelp =  (unsigned char) (ucHelp & NEGATE_UCHAR( (0x01 << j) ));

                break;
              }
            }
          }

          ulBufID = aulHistoryID[j];
          aulHistoryID[j] = pt2ID[i];
          aucHistoryWP[j] = pt2Pos[i];

          if(ucGetZOState() == 1)
          {
            ucHelp = ucGetZOMPosOfID(&ulBufID);
            tZOM[ucHelp].ulID = pt2ID[i];
            SetZOMWP(ucHelp, pt2Pos[i]);
            ucRet |= (1 << ucHelp);
          }
          else{
            ucRet |= (1 << pt2Pos[i]);
          }
        }
      }
      else{
        if(aucHistoryWP[j] == pt2Pos[i])
        {

        }
        else{
          if( pt2Pos[i] > cWheelPos_RR)
          {
            if( pt2Pos[i] == (unsigned char) 4 )
            {
              ucRet = 0;
              i = ucSum;
            }
            else{
              aulHistoryID[j] = (unsigned long) i + 1;
              aucHistoryWP[j] = (unsigned char) 4;
              ucHelp = pt2Pos[i] - (unsigned char) 5;
              aulHistoryID[ucHelp] = pt2ID[i];
              aucHistoryWP[ucHelp] = (unsigned char) 4;
              ucRet |= (0x10 << ucHelp);
              SetZOState(0);
            }
          }
          else{
            ucHelp = j;
            for(j = 0; j < cMaxLR; j++)
            {
              if(pt2Pos[i] == aucHistoryWP[j])
              {
                aucHistoryWP[j] = aucHistoryWP[ucHelp];
                break;
              }
            }
            aucHistoryWP[ucHelp] = pt2Pos[i];
            if(ucGetZOState() == 1)
            {
              SetZOMWP(j, aucHistoryWP[j]);
              SetZOMWP(ucHelp, pt2Pos[i]);
              ucRet |= (unsigned char) (0x10 << pt2Pos[i]);
              ucRet |= (unsigned char) (0xFF & (0x10 << aucHistoryWP[j]));
            }
            else{
              ucRet |= (unsigned char) (1 << pt2Pos[i]);
            }
          }
        }
      }
   }
   if(ucRet > 0)
   {
      PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
      PutWADataEE(cHistoryWPSet1, aucHistoryWP);
   }
   if(ucGetZOState() == 0)
   {
      WAInit();
      ucRet = 0x0f;
   }
  }
  return (ucRet);
}
#endif

static unsigned char ucGetHistoryState(void){
  unsigned char i, ucRet = 0;
  if(aulHistoryID[0] < cInitHistID)
  {
   ucRet |= (cHiStateER | cHiStateZG);
   for(i = 0; i < cMaxLR; i++)
   {
      if(aucHistoryWP[i] > cWheelPos_RR)
      {
        ucRet &= ~cHiStateZG;
      }
   }
  }
  return (ucRet);
}

unsigned char WAInit(void){
  unsigned char i;

  SetZOState(0);
  SetERState(0);
  SetWActiveState(0);
  SetWAStateZOChange(0);
  CancelWATO();
  ClearZOM(cSumWE);
  ResetAllocType();

#ifdef pb_Debug4MB_010404
 ucRightRSDistDG = 0;
 ucLeftRSDistDG = 0;
#endif

  //reset error counter
  ResetAllocErrorCnt();
  //sm_ucWPConsistentErrCnt = 0;
  //sm_ucAxisDetectionErrCnt = 0;
  //sm_ucDirDetectionErrCnt = 0;

  GetWADataEE(cWAABSTicksInOneRevolution, (unsigned char *)&tABSTicksOneRevol);
  GetWADataEE(cWAParameter, (unsigned char *) &tWAPar);
  if((tWAPar.ucEcuPosition != ucECUPosFront) && (tWAPar.ucEcuPosition != ucECUPosRear) && (tWAPar.ucEcuPosition != ucECUPosNeutral))
  {
    tWAPar.ucWACtrl = ucDefWACtrl;
    tWAPar.ucMinRssiLevel = ucDefMinRssiLevel;
    tWAPar.ucMinRssiDistance = ucDefMinRssiDistance;
    tWAPar.ucMinVariationDistance = ucDefMinVariationDistance;
    tWAPar.ucLeRiMinDistance = ucDefLeRiMinDistance;
    tWAPar.ucEcuPosition = ucECUPosNeutral; //TODO: for serial software the default value should be Neutral Decide and change befor the freeze!!!
    //tWAPar.ucEcuPosition = ucECUPosFront;
    //tWAPar.ucEcuPosition = ucECUPosRear;
    //tWAPar.ucMinCt4AxAnalysis = ucDefMinCt4AxAnalysis;
    tWAPar.ucMinCt4ER = ucDefMinCt4ER;
    tWAPar.ucMinCt4HistER = ucDefMinCt4HistER;
    tWAPar.ucMinCt4ZomReset = ucDefMinCt4ZomReset;
    tWAPar.ucMinERMeanRssiLevel = ucDefMinERMeanRssiLevel;
    tWAPar.WATOTimeInSec = ucDefWATOTimeInSec;
    tWAPar.ucTimeoutAutoLoc = ucDefTimeoutAutoLoc;
    tWAPar.ucMinTimeProtectER = ucDefMinTimeProtectER;
    tWAPar.ucnMinRxTGRF = ucnDefMinRxTGRF;
    tWAPar.ucNewMinCntEvt = ucDefNewMinCntEvt;
    tWAPar.ucnRelValMinDiff = ucDefnRelValMinDiff;
    tWAPar.ucnRelValMidDiff = ucDefnRelValMidDiff;
    tWAPar.ucnRelValCompetDiff = ucDefnRelValCompetDiff;
    tWAPar.ucMaxZOnorm = ucDefMaxZOnorm;
    tWAPar.ucnMinA = ucDefnMinA;
    tWAPar.ucMinSpeedAutoLearnStart = ucDefMinSpeedAutoLearnStart;
    tWAPar.ucOffsetOverlapsGXe = ucDefOffsetOverlapsGXe;
    tWAPar.ucnVweight = ucDefnVweight;
    tWAPar.ucMinOffsetGXe = ucDefMinOffsetGXe;
    tWAPar.ucSufficientRssiDistance = ucDefSufficientRssiDistance;

   for(i = 0; i < cMaxLR; i++)
   {
      aulHistoryID[i] = cInitHistID;
      aucHistoryWP[i] = cNoWPos;
   }
   PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
   PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
   PutWADataEE(cHistoryWPSet1, aucHistoryWP);
  }
  else{
    GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
    GetWADataEE(cHistoryWPSet1, aucHistoryWP);
   if((tWAPar.ucWACtrl & ucWACtrlFixc) > 0)
   {
      RestoreHistory();
   }
    tWAPar.ucWACtrl &= ~ucWACtrlBreakc;
  }
  ucNrOfTOs = 0;

  ushHistProtecTimeCnt = 0; //init history protection time to 0 at start of WA

#ifdef FPA
  Very1stABSTickIinit();
#endif
  return (ucGetHistoryState());
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
void WrWAPara( WAParameter *pPara2WrIn)
{
  if((tWAPar.ucEcuPosition == ucECUPosFront) || (tWAPar.ucEcuPosition == ucECUPosRear) || (tWAPar.ucEcuPosition == ucECUPosNeutral))
  {
    tWAPar.ucWACtrl = pPara2WrIn->ucWACtrl;
    tWAPar.ucMinRssiLevel = pPara2WrIn->ucMinRssiLevel;
    tWAPar.ucMinRssiDistance = pPara2WrIn->ucMinRssiDistance;
    tWAPar.ucMinVariationDistance = pPara2WrIn->ucMinVariationDistance;
    tWAPar.ucLeRiMinDistance = pPara2WrIn->ucLeRiMinDistance;
    tWAPar.ucEcuPosition = pPara2WrIn->ucEcuPosition;
    //tWAPar.ucMinCt4AxAnalysis = pPara2WrIn->ucMinCt4AxAnalysis;
    tWAPar.ucMinCt4ER = pPara2WrIn->ucMinCt4ER;
    tWAPar.ucMinCt4HistER = pPara2WrIn->ucMinCt4HistER;
    tWAPar.ucMinERMeanRssiLevel = pPara2WrIn->ucMinERMeanRssiLevel;
    tWAPar.WATOTimeInSec = pPara2WrIn->WATOTimeInSec;
    tWAPar.ucTimeoutAutoLoc = pPara2WrIn->ucTimeoutAutoLoc;
    tWAPar.ucMinTimeProtectER = pPara2WrIn->ucMinTimeProtectER;
    tWAPar.ucnMinRxTGRF = pPara2WrIn->ucnMinRxTGRF;
    tWAPar.ucNewMinCntEvt = pPara2WrIn->ucNewMinCntEvt;
    tWAPar.ucnRelValMinDiff = pPara2WrIn->ucnRelValMinDiff;
    tWAPar.ucnRelValMidDiff = pPara2WrIn->ucnRelValMidDiff;
    tWAPar.ucnRelValCompetDiff = pPara2WrIn->ucnRelValCompetDiff;
    tWAPar.ucMaxZOnorm = pPara2WrIn->ucMaxZOnorm;
    tWAPar.ucnMinA = pPara2WrIn->ucnMinA;
    tWAPar.ucMinSpeedAutoLearnStart = pPara2WrIn->ucMinSpeedAutoLearnStart;
    tWAPar.ucOffsetOverlapsGXe = pPara2WrIn->ucOffsetOverlapsGXe;
    tWAPar.ucnVweight = pPara2WrIn->ucnVweight;
    tWAPar.ucMinOffsetGXe = pPara2WrIn->ucMinOffsetGXe;
    tWAPar.ucSufficientRssiDistance = pPara2WrIn->ucSufficientRssiDistance;
   PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
  }
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
unsigned char ucGetWATOTimeInSec(void){
  return(tWAPar.WATOTimeInSec);
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef BUILD_WITH_UNUSED_FUNCTION
void RdWAPara( WAParameter *pPara2RdOut)
{
  pPara2RdOut->ucWACtrl = tWAPar.ucWACtrl;
  pPara2RdOut->ucMinRssiLevel = tWAPar.ucMinRssiLevel;
  pPara2RdOut->ucMinRssiDistance = tWAPar.ucMinRssiDistance;
  pPara2RdOut->ucMinVariationDistance = tWAPar.ucMinVariationDistance;
  pPara2RdOut->ucLeRiMinDistance = tWAPar.ucLeRiMinDistance;
  pPara2RdOut->ucEcuPosition = tWAPar.ucEcuPosition;
  //pPara2RdOut->ucMinCt4AxAnalysis = tWAPar.ucMinCt4AxAnalysis;
  pPara2RdOut->ucMinCt4ER = tWAPar.ucMinCt4ER;
  pPara2RdOut->ucMinCt4HistER = tWAPar.ucMinCt4HistER;
  pPara2RdOut->ucMinERMeanRssiLevel = tWAPar.ucMinERMeanRssiLevel;
  pPara2RdOut->WATOTimeInSec = tWAPar.WATOTimeInSec;
  pPara2RdOut->ucTimeoutAutoLoc = tWAPar.ucTimeoutAutoLoc;
  pPara2RdOut->ucMinTimeProtectER = tWAPar.ucMinTimeProtectER;
  pPara2RdOut->ucnMinRxTGRF = tWAPar.ucnMinRxTGRF;
  pPara2RdOut->ucNewMinCntEvt = tWAPar.ucNewMinCntEvt;
  pPara2RdOut->ucnRelValMinDiff = tWAPar.ucnRelValMinDiff;
  pPara2RdOut->ucnRelValMidDiff = tWAPar.ucnRelValMidDiff;
  pPara2RdOut->ucnRelValCompetDiff = tWAPar.ucnRelValCompetDiff;
  pPara2RdOut->ucMaxZOnorm = tWAPar.ucMaxZOnorm;
  pPara2RdOut->ucnMinA = tWAPar.ucnMinA;
  pPara2RdOut->ucMinSpeedAutoLearnStart = tWAPar.ucMinSpeedAutoLearnStart;
  pPara2RdOut->ucOffsetOverlapsGXe = tWAPar.ucOffsetOverlapsGXe;
  pPara2RdOut->ucnVweight = tWAPar.ucnVweight;
  pPara2RdOut->ucMinOffsetGXe = tWAPar.ucMinOffsetGXe;
  pPara2RdOut->ucSufficientRssiDistance = tWAPar.ucSufficientRssiDistance;
}
#endif

unsigned char * GETpucStartAdrWP(void){
  return (aucHistoryWP);
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
void ChangeWAPara(void){
 static WAParameter tWAPara2Change;
 static unsigned char ucWAParaAccess = (unsigned char) 1;

 if((unsigned char) 1 == ucWAParaAccess)
 {
    RdWAPara((WAParameter *) &tWAPara2Change);
   ucWAParaAccess = 0;
 }
 else if((unsigned char) 2 == ucWAParaAccess)
 {
    WrWAPara((WAParameter *) &tWAPara2Change);
    RdWAPara((WAParameter *) &tWAPara2Change);
   ucWAParaAccess = 0;
 }
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void SetWAModeFix(void){
  tWAPar.ucWACtrl |= ucWACtrlFixc;
  PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
}

void SetWAModeLearn(void){
  tWAPar.ucWACtrl &= ~ucWACtrlFixc;
  PutWADataEE(cWAParameter, (unsigned char *) &tWAPar );
}

#ifdef DETECT_SYMC_WALLOC_DTC

#ifdef BUILD_WITH_UNUSED_FUNCTION
void IncWPConsistentError(void){
  if(sm_ucWPConsistentErrCnt < 250)
  {
   sm_ucWPConsistentErrCnt++;
  }
}
#endif // BUILD_WITH_UNUSED_FUNCTION
void IncAxisDetectionError(void){
  if(sm_ucAxisDetectionErrCnt < 250)
  {
   sm_ucAxisDetectionErrCnt++;
  }
}
#ifdef G_USE_ROTATION_DIRECTION
void IncDirDetectionError(void){
  if(sm_ucDirDetectionErrCnt < 250)
  {
   sm_ucDirDetectionErrCnt++;
  }
}
#endif //G_USE_ROTATION_DIRECTION

uint8 CheckForDetailed_ZO_Error(void){
  uint8 l_ucRet = 0;

  //if((sm_ucWPConsistentErrCnt  == 0)&&
  if((sm_ucAxisDetectionErrCnt == 0)&&
      (sm_ucDirDetectionErrCnt  == 0)  )
  {
    l_ucRet = 2; //-> ZO error, maybe nothing received!
  }
  else

  if(sm_ucWPConsistentErrCnt > sm_ucAxisDetectionErrCnt)
  {
   if(sm_ucWPConsistentErrCnt > sm_ucDirDetectionErrCnt)
   {
      //l_ucRet = 6; //-> WP constistence error
   }
   else{
      l_ucRet = 3; //-> direction detection error
   }
  }
  else{
   if(sm_ucAxisDetectionErrCnt > sm_ucDirDetectionErrCnt)
   {
      l_ucRet = 4; //-> axis detection error
   }
   else{
      l_ucRet = 3; //-> direction detection error
   }
  }
  return(l_ucRet);
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION

unsigned char  ucCheckHistRxEv(void){
   unsigned short ushRet = ushIDSetInHist(aulHistoryID,(unsigned char) 2,cSumWE);

   if(cMaxLR == ucNrOfBitSet(ushRet))
        return ((unsigned char) 1);
   else
        return ((unsigned char) 0);
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void IncrHistProtectTimer(void){
  if(ushHistProtecTimeCnt < (tWAPar.ucMinTimeProtectER * 60 * 5))  // *5 because of the call of the function every 200ms
  {
   if(ushHistProtecTimeCnt < 0xFFFF) //overflow protection
   {
      ushHistProtecTimeCnt++;
   }
  }
}

boolean bGetHistProtecTimeOver(void){
  if(ushHistProtecTimeCnt < (tWAPar.ucMinTimeProtectER * 60 * 5))
  {
    return FALSE;
  }
  else{
    return TRUE;
  }
}

static boolean bCheckIfNewTelAllowed(struct InputWA *ptInputWA, unsigned char ucIx)
{
  boolean bTelAllowed = TRUE;

  if(cMaxLR > ucGetColOfID(&ptInputWA->ulID))
  {

   if(0 == (ptInputWA->ucStatus & (cIDStateM4 |cIDStateDrive)))
   {
      bTelAllowed = FALSE;
   }
   else{

   }
  }
  else{

   if(0 == (ptInputWA->ucStatus & cIDStateM4))
   {
      bTelAllowed = FALSE;
   }
   else{

   }
  }

  if((TRUE == bTelAllowed)&&(ucIx < cSumWE))
  {

   if(0 != tZOM[ucIx].ucSkipNewTelTimerInSec)
   {
      bTelAllowed = FALSE;
   }
  }

  return bTelAllowed;
}

void WALLOC_UpdateTelegramSkipTimer(void){
  unsigned char ucIdx = 0;

  for(ucIdx = 0; ucIdx < cSumWE; ucIdx++)
  {
   if(0 != tZOM[ucIdx].ucSkipNewTelTimerInSec)
   {
      tZOM[ucIdx].ucSkipNewTelTimerInSec--;
   }
  }
}

unsigned char WALLOC_ucGetMinSpeedAutoLearnStart(void){
  return tWAPar.ucMinSpeedAutoLearnStart;
}

void ResetHistoryToDefault(void){
  uint8 LocalLoopCnt;
  for(LocalLoopCnt = 0; LocalLoopCnt < cMaxLR; LocalLoopCnt++)
  {
    aulHistoryID[LocalLoopCnt] = cInitHistID;
    aucHistoryWP[LocalLoopCnt] = cNoWPos;
  }

  PutWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
  PutWADataEE(cHistoryWPSet1, aucHistoryWP);
}

unsigned char ucGetABSTicksFullRevolFrontAx(void){
  if(tABSTicksOneRevol.ucFrontAxisABSTicks > 0)
  {
    return tABSTicksOneRevol.ucFrontAxisABSTicks;
  }
  else{
    return (unsigned char) cDefaultABSCountNr;
  }
}

unsigned char ucGetABSTicksFullRevolRearAx(void){
  if(tABSTicksOneRevol.ucRearAxisABSTicks > 0)
  {
    return tABSTicksOneRevol.ucRearAxisABSTicks;
  }
  else{
    return (unsigned char) cDefaultABSCountNr;
  }
}

uint8 DCM_InvIf_ZomStatusGetFromMemory(uint8 u8_ZomPossition)
{
  if(u8_ZomPossition < cSumWE)
  {
    return (tZOM[u8_ZomPossition].ucStatus);
  }
  else{
    return ( (unsigned char) 0);
  }
}

void DCM_InvIf_ZomWuIDGetFromMemory(uint8 u8_ZomPossition, uint8 *u8_IDValue)
{
  uint32 LocalZomIDValue;
  LocalZomIDValue = ulGetZOMID(u8_ZomPossition);

  u8_IDValue[0] = (uint8)((LocalZomIDValue >> 24) & 0x000000FF);
  u8_IDValue[1] = (uint8)((LocalZomIDValue >> 16) & 0x000000FF);
  u8_IDValue[2] = (uint8)((LocalZomIDValue >> 8) & 0x000000FF);
  u8_IDValue[3] = (uint8)(LocalZomIDValue  & 0x000000FF);
}

void DCM_InvIf_HistoryIDReadValue(uint8 u8_Possition, uint8 *u8_IDValue)
{
  uint32 LocalHistIDValue;
  LocalHistIDValue = ulGetID(u8_Possition);

  u8_IDValue[0] = (uint8)((LocalHistIDValue >> 24) & 0x000000FF);
  u8_IDValue[1] = (uint8)((LocalHistIDValue >> 16) & 0x000000FF);
  u8_IDValue[2] = (uint8)((LocalHistIDValue >> 8) & 0x000000FF);
  u8_IDValue[3] = (uint8)(LocalHistIDValue  & 0x000000FF);
}

uint8 DCM_InvIf_AutoLocGetTimeoutCntValue(void){
  return ucNrOfTOs;
}

void DCM_InvIf_HistoryWPReadValue(uint8 u8_Possition, uint8 *u8_WPValue)
{
  *u8_WPValue = ucGetWPOfCol(u8_Possition);
}

uint8 DCM_InvIf_ZomTelCntGetFromMemory(uint8 u8_ZomPossition)
{
  return ucGetProbeCt(u8_ZomPossition);
}

uint8 DCM_InvIf_ZomPosCurrIDGetValue(void){
  uint32 LocalIdValue;
  LocalIdValue = ulGetReDataIdPD();
  return ucGetZOMPosOfID(&LocalIdValue);
}

void UpdateHistoryFromRAMWIthTheOneFromNVM(void){
  GetWADataEE(cHistorySet1, (unsigned char *) aulHistoryID);
  GetWADataEE(cHistoryWPSet1, aucHistoryWP );
}

// ___________________________________public control__________________________________________________________END

#ifdef pb_ModulTest_050104
void TESTPrintWAStatus(void){
  printf("\n ucWAStatus:");
  printf("\n 0x%02X",ucWAState);
}

void TESTPrintHistory(void){
  unsigned char i;
  printf("\n");
  for(i = 0; i < cMaxLR; i++)
    printf(" HistID[%d];",i);
  printf("\n");
  for(i = 0; i < cMaxLR; i++)
    printf(" %lu;",aulHistoryID[i]);
  printf("\n");
  for(i = 0; i < cMaxLR; i++)
    printf(" %u;",aucHistoryWP[i]);
}

void TESTPrintWAParameters(void){
  printf("\n WAParameterset :");
  printf("\n ucWACtrl; ucMinRssiLevel; ucMinRssiDistance; ucMinVariationDistance; ucLeRiMinDistance; ucEcuPosition;ucMinCt4AxAnalysis;ucMinCt4ER;ucMinCt4HistER;ucMinERMeanRssiLevel;WATOTimeInSec;");
  printf("\n %d; %d; %d; %d; %d; 0x%02X; %d; %d; %d; %d; %d",tWAPar.ucWACtrl, tWAPar.ucMinRssiLevel, tWAPar.ucMinRssiDistance, tWAPar.ucMinVariationDistance
   ,         tWAPar.ucLeRiMinDistance, tWAPar.ucEcuPosition, tWAPar.ucMinCt4AxAnalysis, tWAPar.ucMinCt4ER, tWAPar.ucMinCt4HistER, tWAPar.ucMinERMeanRssiLevel, tWAPar.WATOTimeInSec);
}

void TESTPrintZOM(unsigned char ucStart, unsigned char ucWidth)
{
  unsigned char i;

  printf("\n cont.;");
  for(i = ucStart; i < ucWidth;i++)
    printf(" ID[%d];",i);
  printf("\n ID;");
  for(i = ucStart; i < ucWidth;i++)
    printf(" %u;",tZOM[i].ulID );
  printf("\n Status;");
  for(i = ucStart; i < ucWidth;i++)
    printf(" 0x%02X;",tZOM[i].ucStatus );
  printf("\n ucProbeCt;");
  for(i = ucStart; i < ucWidth;i++)
    printf(" %d;",tZOM[i].ucProbeCt );
  printf("\n ucLeftCt");
  for(i = ucStart; i < ucWidth;i++)
    printf(" %d;",tZOM[i].ucLeftCt );
  printf("\n ucRightCt;");
  for(i = ucStart; i < ucWidth;i++)
    printf(" %d;",tZOM[i].ucRightCt );
  printf("\n PosCter;");
#ifdef CONCEPT4
  for(i = ucStart; i < ucWidth;i++)
    printf(" %d;",tZOM[i].ucFCt );
#endif
  printf("\n ushSensoRev;");
}
void TESTPrintZOMHL(unsigned char ucStart, unsigned char ucWidth)
{
  unsigned char i;

  for(i = ucStart; i < ucWidth;i++)
   printf(";ID[%d];Status[%d];   ucProbeCt[%d];ucLeftCt[%d];ucRightCt[%d];   StartTime/ms[%d];LogTime/ms[%d];LastLogTime/ms[%d];LogTime/65s[%d];   LECt;SECt; FrontCt[%d];   RECt1[%d]; RECt2[%d]; SdFB[%d]; SdTFB[%d]; dT[%d]",i,i,i,i,i,i,i,i,i,i,i,i,i,i,i,i,i);
}
void TESTPrintZOMAsLine(unsigned char ucStart, unsigned char ucWidth)
{
  unsigned char i;
  for(i = ucStart; i < ucWidth;i++)
      printf(";%lu;0x%02X;%d;%d;%d;%d; %d;%d;%d;%d;%d;%d;%d;%d;%d;%d",tZOM[i].ulID,tZOM[i].ucStatus
   ,     tZOM[i].ucProbeCt,tZOM[i].ucLeftCt,tZOM[i].ucRightCt,
#ifdef CONCEPT4
      tZOM[i].ushStarTi,tZOM[i].ushLogTime,i , tZOM[i].ucStarTiHi
   ,     tZOM[i].ushLECt , tZOM[i].ushSECt ,tZOM[i].ucFCt
   ,    i , i ,i ,i );
#else
      0,0,0,0,0,0,0,0,0);
#endif
}
unsigned char TESTGetucWAState(void){
  return ucWAState;
}
void TESTPrintCompleteWAData()
{
  TESTPrintWAStatus();
  TESTPrintWAParameters();
  TESTPrintHistory();
  TESTPrintZOM(0, cSumWE);
}
void TESTPrintInputWA(tRFTelType *ptInputWA)
{
  if( ptInputWA->Header.ucTType == 0xA1)
      printf("\n %d; %d; %d", ptInputWA->AKplus.ulID ,ptInputWA->AKplus.ucFrameID ,ptInputWA->AKplus.ucT );
  else if(ptInputWA->Header.ucTType == 0xE2)
      printf("\n %d; %d; 0x%02X; %d; %d; %d",ptInputWA->RLplus.ulID ,ptInputWA->RLplus.ucFrameID , ptInputWA->RLplus.ucSpin , ptInputWA->RLplus.ucXEdgCt , ptInputWA->RLplus.ucSCtTotal , ptInputWA->RLplus.ucXSCtEn );
}
unsigned char TESTucGetToTime(void){
  return(tWAPar.WATOTimeInSec);
}
void TESTLoadHistory(unsigned long * aulID, unsigned char * aucTmpWP)
{
  unsigned char i;

  for(i = 0; i < cMaxLR; i++)
  {
    m_aulHistoryID[i] = aulID[i];
    m_aucHistoryWP[i] = aucTmpWP[i];
  }
  PutWADataEE(cHistorySet1, (unsigned char *) m_aulHistoryID);
  PutWADataEE(cHistoryWPSet1, m_aucHistoryWP);
}
void TESTResetWallocRAM(void){
  unsigned short j;
  printf("\n ___COMMENT: RESET  RAM");
  for(j = 0; j < ((unsigned char) sizeof(struct ZOMSlot) * cSumWE); j++)
    *((unsigned char *) tZOM + j) = 0;
  ucWAState = 0;
  for(j = 0; j < (unsigned char) sizeof(WAParameter); j++)
    *((unsigned char *) &tWAPar + j) = 0;

  for(j = 0; j < cMaxLR; j++)
  {
    aulHistoryID[j] = 0;
    aucHistoryWP[j] = 0;
  }
}

void TESTPrintCAZOM_HL(unsigned char ucStart, unsigned char ucWidth)
{
  unsigned char i;

  for(i = ucStart; i < ucWidth;i++)
     printf("ID[%d];Status[%d];ucProbeCt[%d];ucLefCt[%d];ucRiCt[%d];ushMeanRS[%d];",i,i,i,i,i,i);
}
void TESTPrintCAZOMAsLine(unsigned char ucStart, unsigned char ucWidth)
{
  unsigned char i;
  for(i = ucStart; i < ucWidth;i++)
    printf("%lu;0x%02X;%d;%d;%d;%d;",tZOM[i].ulID,tZOM[i].ucStatus,tZOM[i].ucProbeCt,tZOM[i].ucLeftCt ,tZOM[i].ucRightCt ,(tZOM[i].ucProbeCt > 0) ? (unsigned short) (tZOM[i].ushRssiSum /tZOM[i].ucProbeCt):0);
}
void TESTPrintCAZOMSummary(unsigned char i)
{
  if(i < 4)
  {
      printf("%lu;0x%02X;%d;%d;%d;%d;",tZOM[i].ulID,tZOM[i].ucStatus,tZOM[i].ucProbeCt,tZOM[i].ucLeftCt ,tZOM[i].ucRightCt ,(tZOM[i].ucProbeCt > 0) ? (unsigned short) (tZOM[i].ushRssiSum /tZOM[i].ucProbeCt):0);
  }
  else
    printf(" %d; %d; %d; %d;%d; %d;",0,0,0,0,0,0);
}
unsigned char TESTucGetZOMStatus(unsigned char ucIx)
{
  return (tZOM[ucIx].ucStatus);
}
static void TESTSetSpinByID(void){
  unsigned char i;

  for( i = 0; i < cMaxLR; i++)
   if((ucGetGRatIDIx((unsigned long *) &tZOM[i].ulID) == 0)  || (ucGetGRatIDIx((unsigned long *) &tZOM[i].ulID) == 2))  //left spinning
      tZOM[i].ucStatus |= cLeftSpin;
   else if((ucGetGRatIDIx((unsigned long *) &tZOM[i].ulID) == 1)  || (ucGetGRatIDIx((unsigned long *) &tZOM[i].ulID) == 3)) // right spinning
      tZOM[i].ucStatus |= cRightSpin;
}
#endif

void ResetNrOfTOs(void){
  ucNrOfTOs = 0;
}

unsigned char ucCheckPotentialErInZom(void){
  unsigned char i, j;
  unsigned char ucRet = 0;
  unsigned char ucNrPotentialErZom= 0;
  unsigned char ucNrHistoryErZom = 0;

  //identify number of potential ERs in ZOM
  ucNrPotentialErZom = ucNrOfBitSet(ushSumPotenAndERWheels());

  //identify number of historical ERs in ZOM
  for(i = 0; i < cMaxLR; i++)
  {
   for(j = 0; j < cSumWE; j++)
   {
      if(aulHistoryID[i] == ulGetZOMID(j))
      {
        ucNrHistoryErZom++;
      }
   }
  }

  if(ucNrPotentialErZom < cMaxLR) //less then 4 IDs so we can't reach ER
  {
   if(ucNrHistoryErZom < ucNrPotentialErZom ) //we have also potential new sensors, so we can't distinguish which positions are missing and which are new
   {
      ucRet = 1; //use unspecific position by setting DTC
   }
  }

  return ucRet;
}

void ResetAllocErrorCnt(void){
  //reset error counter
  sm_ucWPConsistentErrCnt = 0;
  sm_ucAxisDetectionErrCnt = 0;
  sm_ucDirDetectionErrCnt = 0;
}
