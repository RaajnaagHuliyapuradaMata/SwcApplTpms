

#ifdef IBTCM_SW_ANPASSUNGEN
#include "iTpms_Interface.hpp"
#else
#include "types.hpp"
#endif

#include "WallocX.hpp"
#include "Walloc_IF.hpp"
#include "global.hpp"

#ifdef G_USE_PART_ER

#define cInvalidTimerFactor  ((unsigned char)0xFF)

 static unsigned short ushPartErTimer;

 static unsigned char CheckSoftSkillsWA(const unsigned char, const unsigned char, unsigned char*);
 static unsigned char CheckHardSkillsWA(const unsigned char, const unsigned char, unsigned char*);

static unsigned char CheckSoftSkillsWA(const unsigned char cZomCol, const unsigned char cTimerFactor, unsigned char* pCount)
{
  unsigned char ucRet = 0x00;

  if(ucGetProbeCt(cZomCol) >= ((cTimerFactor * 50)/100))
  {
   ucRet = (1 << cZomCol);
    *pCount++;
  }
  else{
   ClearZOM(cZomCol);
  }
  return(ucRet);
}

static unsigned char CheckHardSkillsWA(const unsigned char cZomCol, const unsigned char cTimerFactor, unsigned char* pCount)
{
  unsigned char ucRet = 0x00;

  if(ucGetProbeCt(cZomCol) >= ((cTimerFactor * 80)/100))
  {
   ucRet = (1 << cZomCol);
    *pCount += 0x10;
  }
  else{
   ClearZOM(cZomCol);
  }
  return(ucRet);
}

void PartWalloc_Init(void){
  ushPartErTimer = 0U;
}

unsigned char CheckPartErCriteriaWA(const unsigned char cTimerFactor)
{
  unsigned char ZomCol;
  unsigned char HistCol;
  unsigned char ucHelp;
  unsigned char ucReturn = 0x00;
  unsigned char ucIdCt = 0x00;

  if(cTimerFactor != cInvalidTimerFactor)
  {

   for(ZomCol = 0; ZomCol < cSumWE; ZomCol++)
   {
      ucHelp = 0x00;

      for(HistCol = 0; HistCol < cMaxLR; HistCol++)
      {
        if(ulGetZOMID(ZomCol) == ulGetID(HistCol))
        {
          ucHelp = 0x01;
        }
      }

      if(ucHelp == 0x01) //If ID is in History use SoftSkills, if not in History use HardSkills
      {
        ucReturn |= CheckSoftSkillsWA(ZomCol, cTimerFactor, &ucIdCt);
      }
      else{
        ucReturn |= CheckHardSkillsWA(ZomCol, cTimerFactor, &ucIdCt);
      }
   }

   ucHelp = 0x00;

   if((ucIdCt & 0xF0) != 0x00)
   {

      for(ZomCol = 0; ZomCol < cSumWE; ZomCol++)
      {
        if((ucReturn & (0x01<<ZomCol)) != 0x00)
        {
          ucHelp++;
        }
      }

      if((ucHelp > 0x00) && (ucHelp < 0x04))
      {
        AlignZOM(ucReturn);
        (void)ucSetHistory((unsigned char)cWAStateER);
      }
      else{
        ucReturn = 0x00;
      }
   }
   else{

      ucReturn = 0x00;
   }
  }
  return(ucReturn);
}

unsigned char DecrPartErTimerWA(const unsigned char bTimerActive)
{
  unsigned char ucRet = 0x01;

  if(bTimerActive == 0x01)
  {
   if(ushPartErTimer > 0)
   {
      if(ushPartErTimer == 1)
      {
        ucRet = 0x00;
      }

      ushPartErTimer--;
   }
  }
  return(ucRet);
}

void SetPartErTimerWA(const unsigned char TimerFactor, const unsigned char TimeRes)
{
  if(TimerFactor != cInvalidTimerFactor)
  {

   if(TimerFactor/TimeRes < 2)
   {
      ushPartErTimer = (0xFFFF & (TimerFactor * (32768/TimeRes) ) );
   }
   else{

      ushPartErTimer = 0xFFFF;
   }
  }
  else{

   ushPartErTimer = 0x0000;
  }
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

boolean GetPartErTimerFinishWA(void){
  boolean bHelp = FALSE;

  if(ushPartErTimer == 0x00)
  {
   bHelp = TRUE;
  }
  return(bHelp);
}
#endif
#endif //G_USE_PART_ER
