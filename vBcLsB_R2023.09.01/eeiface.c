

#ifdef IBTCM_SW_ANPASSUNGEN
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#endif

#include "eeiface.hpp"
#include "global.hpp"

#if(defined pb_EeIfaceOnPc_200103) || (defined IBTCM_SW_ANPASSUNGEN)

#else
#include "eecatc_ifX.hpp"
#endif

#ifndef pb_EeIfaceOnPc_200103

#else
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

void GetDataEE(unsigned char ucId, unsigned char *pRamAdr)
{
  if((ucId>0)&&(ucId<7))
  {
    ReadBlock2Member (1, ucId , pRamAdr );
  }
}

void PutDataEE(unsigned char ucId, const unsigned char *pRamAdr)
{
  if((ucId>0)&&(ucId<7))
  {
      WriteMember2Blocks (1,ucId,(unsigned char *) pRamAdr );
  }
}

#ifndef pb_ModulTest_02062003

#else
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

void PRINT_EepromUsage(void){
   unsigned char i;
    printf("\n___TESTID:TC_900230 \n current EEPROM usage table :");
   for(i = 0; i < 6; i++)
        printf("\n ID%d : %03d bytes",tEepromCfg.aucId[i], tEepromCfg.aucLen[i]);
}

#endif
