#include "Statusbar.h"
#include "DatamanagerX.h"
#include "InfoTyreX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeErfsBlockX.h"
#include "State_BZX.h"
#include "State_FZZX.h"
#include "WuMonitoringX.h"
#include "CodingDataX.h"
#include "WallocX.h"
#include "Fpa_X.h"

static uint8 ucStateMachine = cNoDisplay;
static uint8 ucTickDelay = cTickOff;
static uint8 ucSbrActivityStatus = cSbrWaitAt_0;

void InitSBR(Rte_Instance self)
{

  if(GETTyreSelectionActiveEE(self) == FALSE)
  {
    if(GETucStatusbarEE(self) != QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens)
    {
      PUTucStatusbarEE(self, QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens);
      SetZoHistoryBlockUpdateFlagEE();
    }
    ucStateMachine = cNoDisplay;
  }
}

void ContinueSBR(Rte_Instance self)
{
  uint8 ucValue;

  ucValue = GETucStatusbarEE(self);

  if(bGetBitFahrzeugzustandFZZ(cLONG_PARK) == FALSE)
  {

    if(bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)
    {
      ucStateMachine = cSlowTo49;

      if(ucValue >= 50)
      {
        PUTucStatusbarEE(self, 1);
      }
    }
    else
    {
      ucStateMachine = cSlowTo99;

      if((ucValue < 50) || (ucValue >= 100))
      {
        PUTucStatusbarEE(self, 50);
      }
    }
  }

  else
  {

    if(((GETLastLocStateEE(self) & cER_FINISH) != cER_FINISH) && (ucValue < 50))
    {
      PUTucStatusbarEE(self, 1);
      ucStateMachine = cSlowTo49;
    }

    else
    {
      PUTucStatusbarEE(self, 50);
      ucStateMachine = cSlowTo99;
      ucSbrActivityStatus = cSbrWaitForEr;
    }
  }

  SetTickDelaySBR(self);
}

void StartSBR(Rte_Instance self)
{
  PUTucStatusbarEE(self, 0);
  ucSbrActivityStatus = cSbrWaitAt_0;
  SetTickDelaySBR(self);
  ucStateMachine = cSlowTo49;
}

void StatusbarTimerTickSBR(Rte_Instance self)
{
  Rdci_ST_TYR_Type statTyre;

  switch (ucStateMachine)
  {

    case cSlowTo49:

    if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
    {
      JumpTo254SBR(self);
    }

    else
    {
      if(bStatusbarActiveSBR() == TRUE)
      {
        if(bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)
        {
          if(GETucStatusbarEE(self) < 49)
          {
            if(ucCountTickDelay() == 0)
            {
              IncValueSBR(self);
              SetTickDelaySBR(self);
            }
          }
        }
        else
        {
          ucStateMachine = cFastTo50;
          ucTickDelay = cTickDelay_1sec;
        }
      }
    }
    break;

    case cFastTo50:
    GetStTyrITY(&statTyre.QU_FN_TYR_INFO, &statTyre.QU_TPL, &statTyre.QU_TFAI);
    if((statTyre.QU_TPL != cNoWarningActive) && (statTyre.QU_TPL != cWarningModuleNotReady))
    {
      JumpTo50SBR(self);
    }

    else if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
    {
      JumpTo254SBR(self);
    }

    else
    {
      JumpToNextDecadeSBR(self);
      if(GETucStatusbarEE(self) == 50)
      {

        if(bGetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE) == TRUE)
        {
          JumpTo254SBR(self);
        }
        else
        {
          ucStateMachine = cSlowTo99;
          SetTickDelaySBR(self);
        }
      }
      else
      {
        ucTickDelay = cTickDelay_1sec;
      }
    }
    break;

    case cSlowTo99:

    if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
    {
      JumpTo254SBR(self);
    }

    else if(bGetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE) == TRUE)
    {
      JumpTo254SBR(self);
    }

    else if(bGetBitBetriebszustandBZ(cLOC_INTERRUPTED) == TRUE)
    {
      ucStateMachine = cFastTo100;
      ucTickDelay = cTickDelay_1sec;
    }

    else
    {

      if(bGetBitBetriebszustandBZ(cER_FINISH) == FALSE)
      {
        ucSbrActivityStatus = cSbrWaitForEr;
      }

      if(bStatusbarActiveSBR() == TRUE)
      {
        if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE)
        {
          if(GETucStatusbarEE(self) < 99)
          {
            if(ucCountTickDelay() == 0)
            {
              IncValueSBR(self);
              SetTickDelaySBR(self);
            }
          }
        }
        else
        {
          ucStateMachine = cFastTo100;
          ucTickDelay = cTickDelay_1sec;
        }
      }
    }
    break;

    case cFastTo100:

    GetStTyrITY(&statTyre.QU_FN_TYR_INFO, &statTyre.QU_TPL, &statTyre.QU_TFAI);
    if((statTyre.QU_TPL != cNoWarningActive) && (statTyre.QU_TPL != cWarningModuleNotReady))
    {
      JumpTo100SBR(self);
    }

    else
    {
      JumpToNextDecadeSBR(self);
      if(GETucStatusbarEE(self) == 100)
      {
        ucStateMachine = cWait100;
      }
      ucTickDelay = cTickDelay_1sec;
    }
    break;

    case cWait100:
    PUTucStatusbarEE(self, QU_RDC_INIT_DISP_InitialisierungAbgeschlossen);
    SetZoHistoryBlockUpdateFlagEE();
    ucStateMachine = cFinish;
    ucTickDelay = cTickDelay_8sec;
    break;

    case cFinish:
    if(ucCountTickDelay() == 0)
    {
      PUTucStatusbarEE(self, QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens);
      SetZoHistoryBlockUpdateFlagEE();
      ucStateMachine = cNoDisplay;
    }
    break;

    default:
    break;
  }

}

void SetStatusBarActivityToGoSBR(void)
{
  if(ucSbrActivityStatus == cSbrWait)
  {
    if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
    {
      if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == FALSE)
      {
        ucSbrActivityStatus = cSbrGo;
      }
    }
  }
}

static boolean bStatusbarActiveSBR(void)
{
  boolean bRetVal = FALSE;
  boolean bTemp = TRUE;
  uint8 i;

  switch (ucSbrActivityStatus)
  {

    case cSbrWaitAt_0:
    if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == TRUE)
    {
      for (i=0; i<cMaxLR; i++)
      {
        if(ucGetZomAbsoluteProbeCt(i) == 0)
        {
          bTemp = FALSE;
        }
      }
      if(bTemp == TRUE)
      {
        ucSbrActivityStatus = cSbrGo;
        bRetVal = TRUE;
      }
    }
    break;

    case cSbrWaitForEr:
    if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE)
    {
      ucSbrActivityStatus = cSbrGo;
      bRetVal = TRUE;
    }
    break;

    case cSbrGo:
    if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
    {
      if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == FALSE)
      {
        ucSbrActivityStatus = cSbrWait;
      }
      bRetVal = TRUE;
    }
    break;

    case cSbrWait:
    if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == TRUE)
    {
      ucSbrActivityStatus = cSbrGo;
      bRetVal = TRUE;
    }
    break;

    default:
    break;
  }

  return bRetVal;
}

static void SetTickDelaySBR(Rte_Instance self)
{
  uint32* pulHistory;
  uint16 ushEigenrad;

  if(GETucStatusbarEE(self) < 50)
  {

    pulHistory = GetPointerToHistoryIdSetWAL();
    ushEigenrad = ushFindIdSetInZomWAL(pulHistory, 1, 16);
    if(ucNrOfBitSet16(ushEigenrad) == cMaxLR)
    {
      ucTickDelay = cTickDelay_1sec;
    }
    else
    {
      ucTickDelay = cTickDelay_4sec;
    }
  }

  else
  {

    if(bCheckAllocConditionSBR() == FALSE)
    {

      if(GETushSpeedFZZ() < (cSPW_THRESHOLD - 5))
      {
        ucTickDelay = cTickDelay_3sec;
      }

      else if(GETushSpeedFZZ() >= cSPW_THRESHOLD)
      {
        ucTickDelay = cTickDelay_5sec;
      }
      else
      {}
    }

    else
    {

      if(GETushSpeedFZZ() < (cSPW_THRESHOLD - 5))
      {
        ucTickDelay = cTickDelay_1sec;
      }

      else if(GETushSpeedFZZ() >= cSPW_THRESHOLD)
      {
        ucTickDelay = cTickDelay_2sec;
      }
      else
      {  }
    }
  }
}

static boolean bCheckAllocConditionSBR(void)
{
  boolean bRetVal = TRUE;
  uint8 i;

  for (i=0; i<cMaxLR; i++)
  {
    if(ucGetZomLocateProbeCt(i) < 14)
    {
      bRetVal = FALSE;
    }
  }
  return bRetVal;
}

static uint8 ucCountTickDelay(void)
{
  if(ucTickDelay > 0)
  {
    ucTickDelay--;
  }
  return ucTickDelay;
}

static void JumpToNextDecadeSBR(Rte_Instance self)
{
  uint8 ucVal = GETucStatusbarEE(self);

  if(ucVal < 100)
  {
    do
    {
      ucVal++;
    } while ((ucVal % 10) > 0);

    PUTucStatusbarEE(self, ucVal);
  }
}

static void JumpTo50SBR(Rte_Instance self)
{
  PUTucStatusbarEE(self, 50);
  SetZoHistoryBlockUpdateFlagEE();
  ucStateMachine = cSlowTo99;
  SetTickDelaySBR(self);
}

static void JumpTo100SBR(Rte_Instance self)
{
  PUTucStatusbarEE(self, 100);
  SetZoHistoryBlockUpdateFlagEE();
  ucStateMachine = cWait100;
  ucTickDelay = cTickDelay_1sec;
}

static void JumpTo254SBR(Rte_Instance self)
{
  PUTucStatusbarEE(self, QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens);
  SetZoHistoryBlockUpdateFlagEE();
  ucStateMachine = cNoDisplay;
  ucTickDelay = cTickOff;
}

static void IncValueSBR(Rte_Instance self)
{
  uint8 ucValue = GETucStatusbarEE(self);
  if(ucValue < 100)
  {
    ucValue++;
  }
  PUTucStatusbarEE(self, ucValue);
}

