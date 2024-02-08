

#include "statisticsX.hpp"
#include "statemanagerx.hpp"
#include "wallocx.hpp"
#include "procdatx.hpp"
#include "calibrX.hpp"

#include "State_FzzX.hpp"
#include "SwcApplTpms_Diag.hpp"
#include "SwcApplTpms_LearnEOL.hpp"
#include "SwcApplTpms_DTC_If.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "statisticsX.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "watcfX.hpp"

#define cWSReceivedTGLimit      1U

static uint8 EOL__ucTimerTGReceptionCheck = 120;
static boolean EOL__bIsEOLRoutineRunning = FALSE;

static boolean EOL_GetRoutineRunningStatus(void);
static void EOL__PutRoutineRunningStatus( boolean boNewStatus );
static boolean EOL__CheckReceivedTG(void);
static void EOL__CheckServiceStart(void);

static boolean EOL__CheckReceivedTG(void)
{
  uint8 ucHistCol;
  uint8 ucReturn;
  uint8 ucCt;

  ucReturn = FALSE;
  ucCt = 0;

  for(ucHistCol = 0; ucHistCol < cAnzRad; ucHistCol++)
  {
   if(GETushGutEmpfCntSTATISTICS( ucHistCol ) >= cWSReceivedTGLimit)
   {
      switch(ucGetZOMWP(ucHistCol))
      {
        case cRadPosVL:
        {
          DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_FL);
          ucCt++;
        }
        break;
        case cRadPosVR:
        {
          DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_FR);
          ucCt++;
        }
        break;
        case cRadPosHL:
        {
          DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_RL);
          ucCt++;
        }
        break;
        case cRadPosHR:
        {
          DeleteCurrentErrorERR(cZO_ERR_WS_MISSING_RR);
          ucCt++;
        }
        break;
        default:
          break;
      }
   }
   else{

   }
  }

  if(ucCt >= cAnzRad)
  {
    EOL_PutStatusEOLRoutine( EOL_ROUT_FINISHED_SUCCESSFULLY );

   ucReturn = TRUE;
  }
  else{

  }

  return (ucReturn);
}

static void EOL__CheckServiceStart(void){
  if(EOL_GetRoutineRunningStatus() == FALSE)
  {
    EOL__PutRoutineRunningStatus( TRUE );

    InitSTATISTICS();
  }
  else{

  }
}

static void EOL__PutRoutineRunningStatus( boolean boNewStatus )
{
  EOL__bIsEOLRoutineRunning = boNewStatus;
}

static boolean EOL_GetRoutineRunningStatus(void)
{
  return EOL__bIsEOLRoutineRunning;
}

void EOL_InitLearnRoutine(void)
{
  if( EOL_GetStatusEOLRoutine() > EOL_ROUT_ENDED_WITH_ERROR )
  {
    EOL_PutStatusEOLRoutine( EOL_ROUT_NEVER_STARTED );
  }
  else{

  }

  EOL__PutRoutineRunningStatus(FALSE);

  if( EOL_GetEOLRoutineActive() == EOL_ROUTINE_ACTIVE )
  {

    StopWallocTOAlarm();

    SetWAModeFix();
    (void)WAInit();

    EOL_PutStatusEOLRoutine( EOL_ROUT_RUNNING );

   CancelAlarmAlEOLRoutineTimerOS();
    SetRelAlarmAlEOLRoutineTimerOS( 1, 1 );
  }
  else{
#ifdef BUILD_WITH_UNUSED_FUNCTION
   if(GETbTransportModeEE() == FALSE)
   {

      SetWAModeLearn();
      (void)WAInit();
   }
#endif

    SetWAModeLearn();
    (void)WAInit();
  }
}

uint8 EOL_StartLearnRoutine( uint8 ucLearnRoutineTimeoutValue )
{
  uint8 ucRet;

  if( ucLearnRoutineTimeoutValue == 0 )
  {
    EOL_PutStatusEOLRoutine( EOL_ROUT_START_WRONG_PARAM );
   ucRet = RET_ERROR;
  }
  else{

    EOL_PutEOLRoutineActive(EOL_ROUTINE_ACTIVE);

    StopWallocTOAlarm();

    SetWAModeFix();
    (void)WAInit();

    SetCurrentErrorERR( cZO_ERR_WS_MISSING_FL );
    SetCurrentErrorERR( cZO_ERR_WS_MISSING_FR );
    SetCurrentErrorERR( cZO_ERR_WS_MISSING_RL );
    SetCurrentErrorERR( cZO_ERR_WS_MISSING_RR );

    EOL__ucTimerTGReceptionCheck = ucLearnRoutineTimeoutValue;

    EOL_PutStatusEOLRoutine( EOL_ROUT_RUNNING );

   CancelAlarmAlEOLRoutineTimerOS();
    SetRelAlarmAlEOLRoutineTimerOS( 1, 1 );

   ucRet = RET_OK;
  }

  return( ucRet );
}

void EOL_ResetLearnRoutine(void)
{
  if( ( EOL_GetStatusEOLRoutine() ) == EOL_ROUT_RUNNING )
  {
    EOL_PutStatusEOLRoutine( EOL_ROUT_STOPPED_ON_REQUEST );
  }
  else{

  }

  if( EOL_GetEOLRoutineActive() == EOL_ROUTINE_ACTIVE )
  {
   if( ( EOL_GetStatusEOLRoutine() ) == EOL_ROUT_FINISHED_SUCCESSFULLY )
   {

      DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_FL );
      DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_FR );
      DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_RL );
      DeleteCurrentErrorERR( cZO_ERR_WS_MISSING_RR );
   }
   else{

   }

    EOL_PutEOLRoutineActive( EOL_ROUTINE_INACTIVE );
    EOL__PutRoutineRunningStatus(FALSE);

   CancelAlarmAlEOLRoutineTimerOS();
  }
  else{

  }

  SetWAModeLearn();
  (void)WAInit();
}

boolean EOL_CheckPeriodicLearnRoutineStatus(void)
{
  uint8 ucHelp;
  boolean bRet = FALSE;
  boolean bCheckConditions = FALSE;

  EOL__CheckServiceStart();

  if(EOL_GetRoutineRunningStatus() == TRUE)
  {
   if(bGetBitFahrzeugzustandFZZ( cKL_15_EIN ) == TRUE)
   {
      ucHelp = EOL__CheckReceivedTG();

      if( ucHelp == TRUE)
      {

        (void)EOL_ResetLearnRoutine();

        bRet = TRUE;
      }
      else{

      }

      if( EOL__ucTimerTGReceptionCheck == 0u )
      {
        EOL_PutStatusEOLRoutine( EOL_ROUT_ENDED_WITH_ERROR );

        (void)EOL_ResetLearnRoutine();
      }
      else{

        EOL__ucTimerTGReceptionCheck--;
      }
   }
   else{

   }
  }
  else{

  }

  return (bRet);
}

void EOL_PutStatusEOLRoutine(uint8 u8NewStatus)
{
  NvM2_PutEOLRoutineStatusEE(u8NewStatus);
}

uint8 EOL_GetStatusEOLRoutine(void)
{
  return NvM2_GetEOLRoutineStatusEE();
}

uint8 EOL_GetEOLRoutineActive(void)
{
  return NvM2_GetEOLRoutineActiveEE();
}

void EOL_PutEOLRoutineActive( uint8 ucNewStatus )
{
  NvM2_PutEOLRoutineActiveEE(ucNewStatus);
}

