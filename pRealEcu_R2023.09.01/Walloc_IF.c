

#include "Walloc_IF.hpp"
#include "WAllocX.hpp"

#include "cd_decoder_x.hpp"

#ifdef pb_ModulTest_050104
#include "TDL analysis.hpp"
#endif

#ifdef IBTCM_SW_ANPASSUNGEN
    #include "iTpms_Interface.hpp"
    #include "SwcApplTpms_Rte.hpp"
    #include "SwcApplTpms_NvM.hpp"
    #include "SwcApplTpms_CAN_If.hpp"
    #include "statemanagerX.hpp"
    #include "abs_linX.hpp"
    #include "watcfX.hpp"
#else
    #include "eecatc_ifx.hpp"
    #include "eecate_ifx.hpp"
    #include "statemanagerX.hpp"
    #include "ReceiveX.hpp"
    #include "applmainX.hpp"
    #include "abs_linX.hpp"
#endif

#ifdef pb_ModulTest_050104
  unsigned char aucEEPROM[300];
  struct EepromCfg
  {
   unsigned char aucId[20];
   unsigned char aucLen[20];
  }tEepromCfg;

  static unsigned short ushTESTWayStretch[5];
  static signed short shTESTLenkwinkel;
  static unsigned char ucTESTSpeed;
  static unsigned short ushTESTABStick[5];
  static signed short shTEST_FW[4];

#endif

#ifdef pb_ModulTest_050104
  unsigned short ushAdrOfId(unsigned char ucId, unsigned char ucLen)
  {
   unsigned char i;
   unsigned short ushHelp = 0;
   for(i=0;i<20;i++)
      if(ucId == tEepromCfg.aucId[i]) break;
      else{
        if(tEepromCfg.aucLen[i] == 0)
        {
          tEepromCfg.aucId[i] = ucId;
          tEepromCfg.aucLen[i] = ucLen;
          break;
        }
        else
          ushHelp += tEepromCfg.aucLen[i];
      }
    return(ushHelp);
  }
#endif

void CancelWATO(void){
#ifdef pb_ModulTest_050104

#else
  StopWallocTOAlarm();
#endif
}

void StartWATO(unsigned char ucTimeInSec)
{
#ifdef pb_ModulTest_050104

#else
  if(ucTimeInSec > 0)
  {
    StartWallocTOAlarm(ucTimeInSec);
  }
#endif
}

#ifdef FPA

#ifdef BUILD_WITH_UNUSED_FUNCTION
unsigned char ucGetABSTick(unsigned short * p2aushABS)
{
    //  ACHTUNG: receive GetWayStrectch gibt 0 zurück wenn Ergbenis OK, andernfalls 0 !!!
#ifdef pb_ModulTest_050104
  if(ushTESTABStick[0] > 0)
  {
      p2aushABS[0] = ushTESTABStick[0];
      p2aushABS[1] = ushTESTABStick[1];
      p2aushABS[2] = ushTESTABStick[2];
      p2aushABS[3] = ushTESTABStick[3];
      //p2aushABS[4] = ushTESTABStick[4];
      return ((unsigned char) 1);
  }
  else
    return ((unsigned char) 0);
#else
  //TBD all this must be replaced with code providing high precision interpolated ABS ticks TBD

  uint8  ucRet;

  ucRet = GetLinABS( p2aushABS );

  if( ucRet == cABS_OK )
  {
   ucRet = (unsigned char) 1;
  }
  else{
   ucRet = (unsigned char) 0;
  }

  return ucRet;
#endif
}
#endif //BUILD_WITH_UNUSED_FUNCTION

unsigned short ushGetABSingleTick(unsigned char ucIx)
{
#ifdef pb_ModulTest_050104

      return( ((ushTESTABStick[ucIx] > 0) ? ushTESTABStick[ucIx]:1) );

#else
  //TBD all this must be replaced with code providing one high precision interpolated ABS tick TBD

  unsigned char LocalCnt;
  unsigned char  ucRet;
  unsigned short ushCnt[4];
  unsigned short ushCurrentAbsTick = 0;

  for(LocalCnt = 0; LocalCnt < 4; LocalCnt++)
  {
   ushCnt[LocalCnt] = 0;
  }

  ucRet = GetLinABS( ushCnt );

  if(ucRet == cABS_OK)
  {

   ushCurrentAbsTick = ushCnt[ucIx];
  }
  else{
   ushCurrentAbsTick = 0;
  }

  return ( ushCurrentAbsTick );
#endif
}
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
unsigned short ushGetLW(void){
#ifdef pb_ModulTest_050104
 signed short shTmp;
  if(shTESTLenkwinkel < 0)
  {
   shTmp = -1 * shTESTLenkwinkel;
    return ((unsigned short) shTmp);
   }
  else
    return ((unsigned short) shTESTLenkwinkel);
#else
  return(0);
#endif
}
#endif //BUILD_WITH_UNUSED_FUNCTION

#ifdef pb_ModulTest_050104
//____________________________________________________________pure TEST functionality_____________________________________________
unsigned char ucGetFW(signed short * p2shFW)
{
  p2shFW[0] = shTEST_FW[0];
  p2shFW[1] = shTEST_FW[1];
  p2shFW[2] = shTEST_FW[2];
  p2shFW[3] = shTEST_FW[3];
  return ((unsigned char) 1);
}

void ResetEEPROM(void){
   unsigned short ushLoop;
   const unsigned char ucInitValuec = 0;
   unsigned char *pt2Data = (unsigned char *) &tEepromCfg;

   for(ushLoop = 0; ushLoop < 300; ushLoop++)
   {
        aucEEPROM[ushLoop] = ucInitValuec;
   }
   for(ushLoop = 0; ushLoop < sizeof(tEepromCfg); ushLoop++)
   {
        *pt2Data = ucInitValuec;
        pt2Data++;
   }
}

void TESTPutWayStretch(unsigned short * p2WayStretch)
{
  ushTESTWayStretch[0] = p2WayStretch[0];
  ushTESTWayStretch[1] = p2WayStretch[1];
  ushTESTWayStretch[2] = p2WayStretch[2];
  ushTESTWayStretch[3] = p2WayStretch[3];
  ushTESTWayStretch[4] = p2WayStretch[4];
}

void TESTResetABStick(void){
  ushTESTABStick[0] = 0;
  ushTESTABStick[1] = 0;
  ushTESTABStick[2] = 0;
  ushTESTABStick[3] = 0;
  ushTESTABStick[4] = 0;
}
void TESTPutSingleABStick(unsigned short ushTickVal, unsigned char ucIx)
{
  if( ushTickVal < ushTESTABStick[ucIx]) // active overflow detection ( is placed in CAN receive task if modultest is not active )
  {
#ifdef FPA
    RebuildABSRef(ucIx);
    RebuildTDLABSRef(ucIx);
#endif
  }
  ushTESTABStick[ucIx] = ushTickVal;
}
void TESTPutLenkwinkel(signed short shLW)
{
  shTESTLenkwinkel = shLW;
}

void TESTPutSpeed(unsigned char ucCurSpeed)
{
  ucTESTSpeed = ucCurSpeed;
}

void TESTPutFW(signed short * p2FW)
{
  shTEST_FW[0] = p2FW[0];
  shTEST_FW[1] = p2FW[1];
  shTEST_FW[2] = p2FW[2];
  shTEST_FW[3] = p2FW[3];
}

#endif
