#include "Std_Types.hpp"

#include "USWarnX.hpp"
#include "global.hpp"
#include "uswarn.hpp"
#include "USCS.hpp"
#include "eeiface.hpp"
#include "USWTime.hpp"
#include "WnTypePar.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_NvM_If.hpp"

static unsigned char bGetX8BitWM(
   const unsigned char* ptByte,
   unsigned char ucBitNo);
static void ClearX8BitWM(
   unsigned char* ptByte,
   unsigned char ucBitNo);
static void SetX8BitWM(
   unsigned char* ptByte,
   unsigned char ucBitNo);
static void ClearWarntypeBit(
   unsigned char ucWType,
   unsigned char ucId,
   unsigned char ucMode);
static void InitWN(
   unsigned char ucInit,
   unsigned char ucIdX);
static unsigned char ucUSWDiagService(
   unsigned char* ptData);
static unsigned char ucGenWNVector(
   const unsigned char* ptData);

const unsigned char ucBitNoc[ucSumWEc ] = {
   1,
   2,
   4,
   8};

cSTATIC const unsigned char ucClearIdWarningc = 0x01;
cSTATIC const unsigned char ucClearWarningc = 0x10;
cSTATIC const unsigned char ucParaWritec = 0x20;
cSTATIC unsigned char ucWarnStateWN;

#define cMaiden 0x00
#define cInitialized  0x01
#define cInitSingleId 0x03

cSTATIC const unsigned char ucEuroCodec = 0x00;
cSTATIC const unsigned char ucXLc = 0x40;
cSTATIC unsigned char aucWarnBitsWN[8];
static unsigned char aucFrikBitWN[8];

cSTATIC union WDA{
   unsigned char ucByte[(unsigned char)sizeof(struct WD)];
   struct WD tWD;
} tWDA;

#ifdef pb_DebugWarnLevels_030203
struct Cmp{
   unsigned char ucPMinDR;
   unsigned char ucAxImb;
   unsigned char ucDHW;
   unsigned char ucHiP;
   unsigned char ucEuF;
};

cSTATIC union U{
   struct Cmp tCmp;
   unsigned char ucByte[(unsigned char)sizeof(struct Cmp)];
} tU;
#endif

unsigned char ucSetWarnBitWN(
   unsigned char ucIdX,
   unsigned char ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc )){
      if(bGetX8BitWM(
         &aucWarnBitsWN[ucWarnTypeIx],
         ucIdX) == 0){
         if((bGetX8BitWM(
            &aucFrikBitWN[ucWarnTypeIx],
            ucIdX) == 0) && (ucFrikModec == (unsigned char)1)){
            SetX8BitWM(
               &aucFrikBitWN[ucWarnTypeIx],
               ucIdX);
            return ((unsigned char)0);
         }
         else{
            ClearX8BitWM(
               &aucFrikBitWN[ucWarnTypeIx],
               ucIdX);
            SetX8BitWM(
               &aucWarnBitsWN[ucWarnTypeIx],
               ucIdX);
            PutDataEE(
               ucWarnTypeArrayIdWNc,
               aucWarnBitsWN);
            return ((unsigned char)1);
         }
      }
      else{
         return ((unsigned char)1);
      }
   }
   else{
      return ((unsigned char)0xff);
   }
}

void ClearWarnBitWN(
   unsigned char ucIdX,
   unsigned char ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc )){
      ClearX8BitWM(
         &aucFrikBitWN[ucWarnTypeIx],
         ucIdX);
      ClearX8BitWM(
         &aucWarnBitsWN[ucWarnTypeIx],
         ucIdX);
      PutDataEE(
         ucWarnTypeArrayIdWNc,
         aucWarnBitsWN);
   }
}

unsigned char ucGetWarnBitWN(
   unsigned char ucIdX,
   unsigned char ucWarnTypeIx){
   if((ucWarnTypeIx < ucMaxWarnTypeWNc) && (ucIdX < ucSumWEc )){
      return (bGetX8BitWM(
         &aucWarnBitsWN[ucWarnTypeIx],
         ucIdX));
   }
   else{
      return ((unsigned char)0xff);
   }
}

cSTATIC unsigned char bGetX8BitWM(
   const unsigned char* ptByte,
   unsigned char ucBitNo){
   if((*ptByte & ucBitNoc[ucBitNo]) == ucBitNoc[ucBitNo]){
      return (1);
   }
   else{
      return (0);
   }
}

cSTATIC void ClearX8BitWM(
   unsigned char* ptByte,
   unsigned char ucBitNo){
   if((*ptByte & ucBitNoc[ucBitNo]) > 0){
      *ptByte &= (unsigned char)~ucBitNoc[ucBitNo];
   }
}

cSTATIC void SetX8BitWM(
   unsigned char* ptByte,
   unsigned char ucBitNo){
   if((*ptByte & ucBitNoc[ucBitNo]) == 0){
      *ptByte |= ucBitNoc[ucBitNo];
   }
}

unsigned char ucPfT(
   unsigned short ushM,
   unsigned short ushTabs){
   unsigned long ulHelp;
   unsigned short ushHelp;
   ulHelp = (unsigned long)ushM * 10;
   ulHelp *= ushTabs;
   ulHelp /= ushGSFc;
   ulHelp += 5;
   ushHelp = (unsigned short)(0xFFFF & (ulHelp / 10));
   return ((unsigned char)(0xFF & ushHelp));
}

unsigned short ushMIso(
   unsigned char ucP,
   signed char scT){
   unsigned long ulHelp;
   unsigned short ushHelp;
   if(ucP == 0){
      ushHelp = 0;
   }
   else{
      ulHelp = (unsigned long) ushGSFc * 10;
      ulHelp *= (ucP + 40);
      ushHelp = (unsigned short)(0xFFFF & (scT + ush273Kelvinc));
      ulHelp = ulHelp / ((unsigned long)ushHelp);
      ulHelp += 5;
      ushHelp = (unsigned short)(ulHelp / 10);
   }
   return (ushHelp);
}

static void ClearWarntypeBit(
   unsigned char ucWType,
   unsigned char ucId,
   unsigned char ucMode
){
                unsigned char i;
   static const unsigned char ucClearMaskc = 0x10;
   if((ucMode & ucClearWarningc) == ucClearMaskc){
      for(i = 0; i < ucSumWEc ; i++){
         ClearWarnBitWN(
               i
            ,  ucWType
         );
         if(ucWType == ucDHWIxc){
            ResetM1Pressure(
               i);
         }
      }
   }
   if((ucMode & ucClearIdWarningc) == ucClearIdWarningc){
      ClearWarnBitWN(
            ucId
         ,  ucWType
      );
      if(ucWType == ucDHWIxc){
         ResetM1Pressure(
            ucId);
      }
   }
   return;
}

static void InitWN(
   unsigned char ucInit,
   unsigned char ucIdX){
   static const signed char scTResLimitDefc = 25;
   static const unsigned char ucReloadFilterc = 0x40;
   unsigned char ucRet, i;
   switch(ucInit){
      case (unsigned short) cMaiden: {
         ucRet = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         ucIdX = ucSumWEc;
         for(i = 0; i < ucMaxWarnTypeWNc; i++){
            ClearWarntypeBit(
               i,
               ucIdX,
               ucRet);
         }
         tWDA.tWD.scTResLimit = scTResLimitDefc;
      }
         break;

      case (unsigned short) cInitialized: {
         ucRet = (ucWarnStateWN & ucCtryMaskc ) | ucReloadFilterc;
         ucIdX = ucSumWEc;
         for(i = 0; i < ucMaxWarnTypeWNc; i++){
            ClearWarntypeBit(
               i,
               ucIdX,
               ucRet);
         }
      }
         break;

      case (unsigned short) cInitSingleId: {
         if(ucIdX <= ucSumWEc){
            ucRet = (ucIdX == ucSumWEc ) ? ucClearWarningc : ucClearIdWarningc;
            for(i = 0; i < ucMaxWarnTypeWNc; i++){
               ClearWarntypeBit(
                  i,
                  ucIdX,
                  ucRet);
            }
         }
         else{
         }
      }
         break;

      default:
         break;
   }
}

void RdParaSubSet(
   struct ParaSubSet* ptData){
   if(ptData->ucAccess == ucRdParaSubSetc){
      ptData->ucParaByte[ucIxWnCfgc] &= 0xF8;
      if((ucWarnStateWN & ucCtryMaskc ) == ucUSCodec){
         ptData->ucParaByte[ucIxWnCfgc] |= 0x01;
      }
      else{
         if((ucWarnStateWN & ucCtryMaskc ) == ucEuroCodec){
            ptData->ucParaByte[ucIxWnCfgc] |= 0x02;
         }
         else{
            ptData->ucParaByte[ucIxWnCfgc] &= NEGATE_UCHAR(
               0x03);
         }
      }
      if((ucWarnStateWN & ucIsoClearc ) == ucIsoClearc){
         ptData->ucParaByte[ucIxWnCfgc] |= 0x04;
      }
      ptData->scTResLimit = tWDA.tWD.scTResLimit;
      ptData->ucParaHighPressThres = tWDA.tWD.ucParaHighPressThres;
      ptData->ucParaHighPressResetThres = tWDA.tWD.ucParaHighPressResetThres;
      ptData->ucParaAxImbSetThres = tWDA.tWD.ucParaAxImbSetThres;
      ptData->ucParaAxImbResThres = tWDA.tWD.ucParaAxImbResThres;
   }
   else{
   }
}

void WrParaSubSet(
   struct ParaSubSet* ptData){
   unsigned char ucHelp;
   if(ptData->ucAccess == ucWrParaSubSetc){
      ucHelp =
            ((ptData->ucParaByte[ucIxWnCfgc] & 0x03) == 1) ? ucUSCodec : ucEuroCodec;
      if((ptData->ucParaByte[ucIxWnCfgc] & 0x04) == 0x04){
         ucHelp |= ucIsoClearc;
      }
      else{
         ucHelp &= NEGATE_UCHAR(
            ucIsoClearc);
      }
      if((ptData->ucParaByte[ucIxWnCfgc] & 0x40) == 0x40){
         ucHelp |= ucXLc;
      }
      else{
         ucHelp &= NEGATE_UCHAR(
            ucXLc);
      }
      GetDataEE(
         ucWsIdWNc,
         &ucWarnStateWN);
      if((ucWarnStateWN & (ucCtryMaskc + ucIsoClearc + ucXLc)) != ucHelp){
         if(((ucWarnStateWN & ucCtryMaskc ) != (ucHelp & ucCtryMaskc )) || (((ucWarnStateWN & ucXLc) == ucXLc) && ((ucHelp & ucXLc) == 0))){
            ucWarnStateWN &= NEGATE_UCHAR(
               ucCtryMaskc);
            ucWarnStateWN |= (ucCtryMaskc & ucHelp);
            if((ucWarnStateWN & ucCtryMaskc ) == ucUSCodec){
               InitCS(
                  cIxPMinUS);
            }
            else{
               InitCS(
                  cIxPMinEU);
            }
         }
         if((ucHelp & ucXLc) == ucXLc){
            InitCS(
               cIxPMinXL);
         }
         ucWarnStateWN &= NEGATE_UCHAR(
            ucXLc);
         ucWarnStateWN &= NEGATE_UCHAR(
            ucIsoClearc);
         ucWarnStateWN |= ucHelp;
         InitWN(
            (unsigned char) cMaiden,
            (unsigned char)0xFF);
         ucHelp = ucWarnStateWN | ucClearWarningc;
      }
      if(ptData->scTResLimit != tWDA.tWD.scTResLimit){
         ucHelp = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         tWDA.tWD.scTResLimit = ptData->scTResLimit;
      }
      if(ptData->ucParaHighPressThres != tWDA.tWD.ucParaHighPressThres){
         ucHelp = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         tWDA.tWD.ucParaHighPressThres = ptData->ucParaHighPressThres;
      }
      if(ptData->ucParaHighPressResetThres != tWDA.tWD.ucParaHighPressResetThres){
         ucHelp = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         tWDA.tWD.ucParaHighPressResetThres = ptData->ucParaHighPressResetThres;
      }
      if(ptData->ucParaAxImbSetThres != tWDA.tWD.ucParaAxImbSetThres){
         ucHelp = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         tWDA.tWD.ucParaAxImbSetThres = ptData->ucParaAxImbSetThres;
      }
      if(ptData->ucParaAxImbResThres != tWDA.tWD.ucParaAxImbResThres){
         ucHelp = (ucWarnStateWN & ucCtryMaskc ) | ucClearWarningc | ucParaWritec;
         tWDA.tWD.ucParaAxImbResThres = ptData->ucParaAxImbResThres;
      }
      if(ucHelp != (ucWarnStateWN & (NEGATE_UCHAR(
         cInitialized)))){
         PutDataEE(
            ucWsIdWNc,
            &ucWarnStateWN);
         PutDataEE(
            ucCdIdWNc,
            tCDA.ucByte);
         PutDataEE(
            ucWdIdWNc,
            tWDA.ucByte);
      }
   }
   else{
   }
}

static unsigned char ucUSWDiagService(
   unsigned char* ptData){
   unsigned short ushTmp;
   unsigned char i, k, ucRet;
   unsigned char ucWarnVectorMap[] = cWT_WNvector_map
   ;
   ucRet = 0;
   switch(*ptData){
      case (unsigned short) ucCfgPMinc :
         i = 0;
         if(ucPutPMinCS(
            ptData[1],
            i) > 0){
            PutDataEE(
               ucCdIdWNc,
               tCDA.ucByte);
         }
         else{
            ucRet = 0xff;
         }
         break;

      case (unsigned short) ucCfgReInitSinglec:
         ushTmp = ushMIso(
            ptData[2],
            (signed char)ptData[3]);
         if(ucPutCalTabVectorCS(
            ptData[1],
            ptData[2],
            (signed char)ptData[3],
            ushTmp) > 0){
            PutDataEE(
               ucCdIdWNc,
               tCDA.ucByte);
            ucRet = ucWarnStateWN;
         }
         else{
            ucRet = 0xff;
         }
         break;

      case (unsigned short) ucCfgPSollMinAtIdc:
         i = 0;
         if(ucPutPSollMinCS(
            ptData[1],
            ptData[2],
            i) > 0){
            if(ucGetPSollCS(
               ptData[1]) < ptData[2]){
               ushTmp = ushMIso(
                  ptData[2],
                  (signed char)20);
               if(ucPutCalTabVectorCS(
                  ptData[1],
                  ptData[2],
                  (signed char)20,
                  ushTmp) > 0){
                  PutDataEE(
                     ucCdIdWNc,
                     tCDA.ucByte);
                  ucRet = 0;
               }
               else{
                  ucRet = 0xff;
               }
            }
            else{
               PutDataEE(
                  ucCdIdWNc,
                  tCDA.ucByte);
               ucRet = 0;
            }
         }
         else{
            ucRet = 0xff;
         }
         break;

      case (unsigned short) ucResetWarnVectorc: {
         ptData++;
         InitWN(
            cInitSingleId,
            *ptData);
         ucRet = 0;
      }
         break;

      case (unsigned short)ucGetWarnVectorsc: {
         for(k = 0; k < ucSumWEc ; k++){
            ptData[k] = 0;
            for(i = 0; i < ucMaxWarnTypeWNc; i++){
               if(((uint8)0) < ucGetWarnBitWN(
                  k,
                  i)){
                  ptData[k] |= ucWarnVectorMap[i];
               }
            }
         }
         ucRet = 0;
      }
         break;

      default:
         break;
   }
   return (ucRet);
}

static unsigned char ucGenWNVector(
   const unsigned char* ptData){
   unsigned char (*const fpt2WnType[])(
      struct LocalWarnDat* LocalWD,
      unsigned char WarnState) = cAllWT_function;
      const unsigned char aucWnTypec[] = cWT_WNvector_map;
      struct LocalWarnDat tLWD;
      unsigned char i,
   ucRet = 0;
   tLWD.tHFD.tHF.ucId = 0;
   tLWD.tHFD.tHF.ucP = 0;
   tLWD.tHFD.tHF.scTWE = 0;
   tLWD.tHFD.tHF.scTa = 0;
   tLWD.tHFD.tHF.scTref = 0;
   tLWD.tHFD.tHF.ucKLState = 0;
   tLWD.tHFD.tHF.ucLifeTime = 0;
   tLWD.tHFD.tHF.ucState = 0;
   tLWD.tHFD.tHF.ushVehicleSpeed = 0;
   tLWD.ucCurWarnLevel = 0;
   for(i = 0; i < (unsigned char)sizeof(struct HFTelIntern); i++){
      tLWD.tHFD.ucByte[i] = *ptData;
      ptData++;
   }
   if(tLWD.tHFD.tHF.ucId < ucSumWEc){
      if(VehStateGetRoadmode() != 0){
         tLWD.tSD.ucPSoll = NvM3_GETucVarCodOffroadPlacardPress();
      }
      else{
         tLWD.tSD.ucPSoll = ucGetPSollCS(
            tLWD.tHFD.tHF.ucId);
      }
      tLWD.tSD.scTSoll = scGetTSollCS(
         tLWD.tHFD.tHF.ucId);
      tLWD.tSD.ushMSoll = ushGetMSollCS(
         tLWD.tHFD.tHF.ucId);
      tLWD.PWarm = ucGetPwarmCS(
         tLWD.tHFD.tHF.ucId);
      for(i = 0; i < ucMaxWarnTypeWNc; i++){
         if(fpt2WnType[i](
            &tLWD,
            ucWarnStateWN) > 0){
            ucRet |= aucWnTypec[i];
         }
         else{
            ucRet &= (unsigned char)~aucWnTypec[i];
         }
#ifdef pb_DebugWarnLevels_030203
         tU.ucByte[i] = tLWD.ucCurWarnLevel;
#endif
      }
   }
   return (ucRet);
}

unsigned char ucWarnManagerWN(
   unsigned char ucAction,
   unsigned char* ptData){
   static const unsigned char ucStateMaskc = 0x03;
   unsigned char ucRet;
   switch(ucAction){
      case (unsigned short) ucPorInitc: {
         GetDataEE(
            ucWsIdWNc,
            &ucWarnStateWN);
         if((ucWarnStateWN & ucStateMaskc) == (unsigned char) cInitialized){
            GetDataEE(
               ucCdIdWNc,
               tCDA.ucByte);
            GetDataEE(
               ucWdIdWNc,
               tWDA.ucByte);
            InitWN(
               (unsigned char) cInitialized,
               (unsigned char)0xFF);
            GetDataEE(
               ucWarnTypeArrayIdWNc,
               aucWarnBitsWN);
            ucRet = ucWarnStateWN;
         }
         else{
            ucWarnStateWN |= *ptData;
            if((*ptData & ucXLc) == ucXLc){
               InitCS(
                  cIxPMinXL);
            }
            else{
               if((*ptData & ucCtryMaskc ) == ucUSCodec){
                  InitCS(
                     cIxPMinUS);
               }
               else{
                  InitCS(
                     cIxPMinEU);
               }
            }
            InitWN(
               (unsigned char) cMaiden,
               (unsigned char)0xFF);
            PutDataEE(
               ucCdIdWNc,
               tCDA.ucByte);
            PutDataEE(
               ucWdIdWNc,
               tWDA.ucByte);
            PutDataEE(
               ucWarnTypeArrayIdWNc,
               aucWarnBitsWN);
            ucWarnStateWN |= cInitialized;
            PutDataEE(
               ucWsIdWNc,
               &ucWarnStateWN);
            ucRet = ucWarnStateWN;
         }
      }
         break;

      case (unsigned short) ucComparec:
         GetDataEE(
            ucWsIdWNc,
            &ucWarnStateWN);
         if((ucWarnStateWN & ucStateMaskc) != cInitialized){
            InitWN(
               (unsigned char) cMaiden,
               (unsigned char)0xFF);
            PutDataEE(
               ucCdIdWNc,
               tCDA.ucByte);
            PutDataEE(
               ucWdIdWNc,
               tWDA.ucByte);
            ucWarnStateWN |= cInitialized;
            PutDataEE(
               ucWsIdWNc,
               &ucWarnStateWN);
         }
         ucRet = ucGenWNVector(
            ptData);
         break;
      case (unsigned short) ucDiagServicec:

         ucRet = ucUSWDiagService(
            ptData);
         break;
      default:
         ucRet = 0xFF;
         break;
   }
   return (ucRet);
}

uint8 DCM_InvIf_AxImbWarnSetThresholdGetValue(
   void){
   return tU.tCmp.ucAxImb;
}

uint8 DCM_InvIf_DHWWarnSetThresholdGetValue(
   void){
   return tU.tCmp.ucDHW;
}

uint8 DCM_InvIf_EuFWarnSetThresholdGetValue(
   void){
   return tU.tCmp.ucEuF;
}

uint8 DCM_InvIf_FTWarnSetThresholdGetValue(
   void){
   return 0;
}

uint8 DCM_InvIf_HardTDRWarnSetThresholdGetValue(
   void){
   return 0;
}

uint8 DCM_InvIf_HiPWarnSetThresholdGetValue(
   void){
   return tU.tCmp.ucHiP;
}

uint8 DCM_InvIf_LowPWarnSetThresholdGetValue(
   void){
   return 0;
}

uint8 DCM_InvIf_PminDRWarnSetThresholdGetValue(
   void){
   return tU.tCmp.ucPMinDR;
}

