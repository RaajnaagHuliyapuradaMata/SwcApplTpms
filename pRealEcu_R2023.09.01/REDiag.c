

#include "REDiag_if.hpp"
#include "CfgSwcApplTpms.hpp"
#include "statemanagerX.hpp"
#include "REDiagX.hpp"

 static const uint8 cMaxWUDefectCnt = 250;

#ifdef js_ReHighTemperatureDiag_230312
 static const uint8 cMaxWUOverTempCnt = 250;
#endif

 static const uint8 cMaxWULowLifeTimeCnt = 250;

 static uint8 ucCntWUDefect[4];

#ifdef js_ReHighTemperatureDiag_230312
 static uint8 ucCntWUOverTemp[4];
#endif

 static uint8 ucCntLowLifeTime[4];

 void ResetWUFailedErrRD(uint8 ucIx)
{
  //SetEventEvDiagEvalOS();
   EvalWUNoRecSM(ucIx);
}

 boolean SetWUFailedErrRD(uint16 CounterValue, uint8 ucIx)
{
  boolean bErrState = FALSE;

  if( CounterValue >= MaxFailCounterInEE())
  {

    //PUTbWUFailedDI(TRUE);
    //SetEventEvDiagEvalOS();
    EvalWUNoRecSM(ucIx);
   bErrState = TRUE;
  }
  return (bErrState);
}

void CntWUDefectRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   if(ucCntWUDefect[ZomPos] < cMaxWUDefectCnt)
   {
      ucCntWUDefect[ZomPos]++;
   }
    //SetEventEvDiagEvalOS();
    EvalWUDefektSM(ZomPos);
  }
}

void ResetWUDefectRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   ucCntWUDefect[ZomPos] = 0;
    //SetEventEvDiagEvalOS();
    EvalWUDefektSM(ZomPos);
  }
}

uint8 GetWUDefectRD(uint8 ZomPos)
{
  return(ucCntWUDefect[ZomPos]);
}

#ifdef js_ReHighTemperatureDiag_230312

void CntWUHighTempRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   if(ucCntWUOverTemp[ZomPos] < cMaxWUOverTempCnt)
   {
      ucCntWUOverTemp[ZomPos]++;
   }
    //SetEventEvDiagEvalOS();
    EvalWUHighTempSM();
  }
}

void ResetWUHighTempRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   ucCntWUOverTemp[ZomPos] = 0;
    //SetEventEvDiagEvalOS();
    EvalWUHighTempSM();
  }
}

uint8 GetWUHighTempRD(uint8 ZomPos)
{
  return(ucCntWUOverTemp[ZomPos]);
}
#endif

void CntWULowLifeTimeRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   if(ucCntLowLifeTime[ZomPos] < cMaxWULowLifeTimeCnt)
   {
      ucCntLowLifeTime[ZomPos]++;
   }
    //SetEventEvDiagEvalOS();
    EvalWULowLifeTimeSM(ZomPos);
  }
}

void ResetWULowLifeTimeRD(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   ucCntLowLifeTime[ZomPos] = 0;
    //SetEventEvDiagEvalOS();
    EvalWULowLifeTimeSM(ZomPos);
  }
}

void ResetWULowLifeTimeCounter(uint8 ZomPos)
{
  if(ZomPos < cAnzRad)
  {
   ucCntLowLifeTime[ZomPos] = 0;
  }
}

uint8 GetWULowLifeTimeRD(uint8 ZomPos)
{
  return(ucCntLowLifeTime[ZomPos]);
}
