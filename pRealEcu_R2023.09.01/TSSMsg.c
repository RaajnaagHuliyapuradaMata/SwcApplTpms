

#include "USWarnX.hpp"
#include "global.hpp"
#include "tssmsg.hpp"
#include "eeiface.hpp"
#include "WnTypePar.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

#ifdef IBTCM_SW_ANPASSUNGEN
#include "Tpms_Rte_Data_Type.hpp"
#else
#endif
#ifndef pb_TestTssMsg_300103

#else
#include <stdio.h>
#endif

static unsigned char ucFilIdWarn(unsigned char ucIdX, unsigned char ucWPos);
static void Warnings2Msg(const struct TssMsg *ptWarnInfo);
static void GenMsgForPosition(uint8 ucWP, uint8 ucWE);
static void TSSMsgOut(const unsigned char *ptData);
static unsigned char ucTSSMsgService(unsigned char * pucData);
static void TSSMsgInit(unsigned char * pucStatus, const unsigned char * pucIniDat);

#define ucTssInitializedc  0x01

cSTATIC const unsigned char ucPosDepWarnc = 0x80;

#define ushHWNoPosc ((unsigned short) 0x0001)
#define ushHWPosFLc ((unsigned short) 0x0002)
#define ushHWPosFRc ((unsigned short) 0x0004)
#define ushHWPosRLc ((unsigned short) 0x0008)
#define ushHWPosRRc ((unsigned short) 0x0010)
#define ushHWPosSTc ((unsigned short) 0x0020)
#define ushWWPosFLc ((unsigned short) 0x0040)
#define ushWWPosFRc ((unsigned short) 0x0080)
#define ushWWPosRLc ((unsigned short) 0x0100)
#define ushWWPosRRc ((unsigned short) 0x0200)
#define ushWWPosSTc ((unsigned short) 0x0400)
#define ushWWNoPosc ((unsigned short) 0x0800)

const unsigned short aushHWPosc[ucSumWEc] = {ushHWPosFLc, ushHWPosFRc, ushHWPosRLc, ushHWPosRRc};
const unsigned short aushWWPosc[ucSumWEc] = {ushWWPosFLc, ushWWPosFRc, ushWWPosRLc, ushWWPosRRc};

cSTATIC unsigned char aucWnValidTM[2];

#define ucMsgMaskc 0xF8

unsigned short ushWarnOutTM;

unsigned char aucWheelPosWarn[ucMaxPosc + 1];

cSTATIC unsigned char aucWarnAtPosTM[ucMaxPosc + 1];
cSTATIC unsigned char aucWPosTM[ucMaxPosc + 1];

cSTATIC unsigned char ucFilterActive;

static unsigned char ucFilIdWarn(unsigned char ucIdX, unsigned char ucWPos)
{
  static const unsigned char ucSTWnAllc = 0x10;
  static const unsigned char ucSTWnActivec = 0x08;
  static const unsigned char ucNonMaskWnTMc = 0x01;

  unsigned char i,ucWnValid,ucRet=0;

  ucWnValid =  aucWnValidTM[ucIxMsCfgc];

  if( ucIdX <= ucSumWEc )
  {
   if( ucIdX == ucSumWEc )
   {
      for( i = 0; i < ucSumWEc; i++)
      {
        if( (ucFilterActive & ucBitNoc[i]) == 0 )
        {
          ucRet |= (aucWarnAtPosTM[i] & (((unsigned char) ~ucWnValid) ) );
        }
      }
   }
   else{
      if( (ucFilterActive & ucBitNoc[ucIdX]) == 0 )
      {
        ucRet = aucWarnAtPosTM[ucIdX] & ((unsigned char) ~(ucWnValid));
        if( ucWPos == ucWPSTc )
        {
          if( (aucWnValidTM[ucIxWnCfgc] & ucSTWnActivec) ==  ucSTWnActivec)
          {
            if((aucWnValidTM[ucIxWnCfgc] & ucSTWnAllc) != ucSTWnAllc)
            {
              ucRet &= ucNonMaskWnTMc;
            }
          }
          else{
            ucRet = 0;
          }
        }
        else{

        }
      }
   }
  }
  else{
   ucRet = 0xff;
  }
  return( ucRet );
}

static void Warnings2Msg(const struct TssMsg *ptWarnInfo)
{
  unsigned char i,ucHelp;

  aucWarnAtPosTM[ucSumWEc] = 0;
  for(i=0;i<ucSumWEc;i++)
  {
    aucWarnAtPosTM[ucSumWEc] |= aucWarnAtPosTM[i];
  }

  ushWarnOutTM = 0;

  if(((unsigned char) (ptWarnInfo->ucSystemState & ucPosDepWarnc)) == ucPosDepWarnc )
  {
    aucWheelPosWarn[ucSumWEc] = 0;
   for(i=0;i<ucSumWEc;i++)
   {
      ucHelp = aucWPosTM[i];
      switch(ucHelp)
      {
      case (unsigned short) ucWPFLc:
        GenMsgForPosition(ucWPFLc, i);
        break;
      case (unsigned short) ucWPFRc:
        GenMsgForPosition(ucWPFRc, i);
        break;
      case (unsigned short) ucWPRLc:
        GenMsgForPosition(ucWPRLc, i);
        break;
      case (unsigned short) ucWPRRc:
        GenMsgForPosition(ucWPRRc, i);
        break;
      case (unsigned short) ucWPSTc:
        aucWheelPosWarn[ucWPSTc] = aucWarnAtPosTM[i];
        if((ucFilIdWarn(i,ucWPSTc) & ucHWMaskc) > 0)
        {
          ushWarnOutTM &= (unsigned short) ~ushHWPosSTc;
          ushWarnOutTM |= ushWWPosSTc;
        }
        else{
          ushWarnOutTM &= (unsigned short) ~ushWWPosSTc;
          ushWarnOutTM &= (unsigned short) ~ushHWPosSTc;
        }
        break;
      default:
        {
          if(ucFilIdWarn(i,ucWPUNc) >  0)
          {
            aucWheelPosWarn[ucSumWEc] = aucWarnAtPosTM[ucSumWEc];
            if((ucFilIdWarn(ucSumWEc,ucWPUNc) & ucHWMaskc) > 0 )
            {
              ushWarnOutTM |= ushHWNoPosc;
            }
            else{
              ushWarnOutTM &= (unsigned short) ~ushHWNoPosc;
              if((ucFilIdWarn(ucSumWEc,ucWPUNc) & ucWWMaskc) > 0)
              {
                ushWarnOutTM |= ushWWNoPosc;
              }
              else{
                ushWarnOutTM &= (unsigned short) ~ushWWNoPosc;
              }
            }
          }
        }
        break;
      }
   }
  }
  else{
   for(i=0;i<ucSumWEc;i++)
   {
      aucWheelPosWarn[i] = 0;
   }
    aucWheelPosWarn[ucSumWEc] = aucWarnAtPosTM[ucSumWEc];
   if((ucFilIdWarn(ucSumWEc,ucWPUNc) & ucHWMaskc) > 0 )
   {
      ushWarnOutTM |= ushHWNoPosc;
   }
   else{
      ushWarnOutTM &= (unsigned short) ~ushHWNoPosc;
      if((ucFilIdWarn(ucSumWEc,ucWPUNc) & ucWWMaskc) > 0)
      {
        ushWarnOutTM |= ushWWNoPosc;
      }
      else{
        ushWarnOutTM &= (unsigned short) ~ushWWNoPosc;
      }
   }
  }
}

static void GenMsgForPosition(uint8 ucWP, uint8 ucWE)
{
  aucWheelPosWarn[ucWP] = aucWarnAtPosTM[ucWE];
  if((ucFilIdWarn(ucWE,ucWP) & ucHWMaskc) > 0)
  {
   ushWarnOutTM |= aushHWPosc[ucWP];
   ushWarnOutTM &= (unsigned short) ~aushWWPosc[ucWP];
  }
  else{
   ushWarnOutTM &= (unsigned short) ~aushHWPosc[ucWP];
   if((ucFilIdWarn(ucWE,ucWP) & ucWWMaskc) > 0)
   {
      ushWarnOutTM |= aushWWPosc[ucWP];
   }
   else{
      ushWarnOutTM &= (unsigned short) ~aushWWPosc[ucWP];
   }
  }
}

static void TSSMsgOut(const unsigned char *ptData)
{
  struct TssMsg tTssMsg;
  static const unsigned char ucKL15Onc = 0x01;

  tTssMsg.ucId = ptData[0];
  tTssMsg.ucPos = ptData[1];
  tTssMsg.ucSystemState = ptData[2];
  tTssMsg.ucWarning = ptData[3];

  if(tTssMsg.ucId < ucSumWEc)
  {
    aucWarnAtPosTM[tTssMsg.ucId] = tTssMsg.ucWarning;
    aucWPosTM[tTssMsg.ucId] = tTssMsg.ucPos;
   if((tTssMsg.ucSystemState & ucKL15Onc) == ucKL15Onc)
   {
      Warnings2Msg( &tTssMsg);
   }
  }
}

static unsigned char ucTSSMsgService(unsigned char * pucData)
{
  unsigned char i, ucRet = 0;
  struct TssMsg tMsg;

  switch(*pucData)
  {
  case (unsigned short) ucNewPositionsc:
   {
      pucData++;
      for(i=0;i<ucSumWEc;i++)
      {
        if(pucData[i] >= ucWPSTc)
        {
          break;
        }
      }
      if( i == ucSumWEc)
      {
        aucWPosTM[ucSumWEc] = 0;
        for(i=0;i<ucSumWEc;i++)
        {
          aucWPosTM[i] = pucData[i];
        }
        tMsg.ucId = ucSumWEc;
        tMsg.ucSystemState = ucPosDepWarnc;
        Warnings2Msg(&tMsg);
        ucRet = 0;
      }
      else{
        ucRet = 0xff;
        for(i = 0;i < (ucSumWEc + 1);i++)
        {
          aucWPosTM[i] = ucWPUNc;
        }
        tMsg.ucId = ucSumWEc;
        tMsg.ucSystemState = 0;
        Warnings2Msg(&tMsg);
      }
   }
   break;
  case (unsigned short) ucClearPosc:
   {
      for(i = 0;i < (ucSumWEc + 1);i++)
      {
        aucWPosTM[i] = ucWPUNc;
      }
      tMsg.ucId = ucSumWEc;
      tMsg.ucSystemState = 0;
      Warnings2Msg(&tMsg);
   }
   break;
  case (unsigned short) ucClearWarnOfIdc:
   if(pucData[1] == ucSumWEc)
   {
      for(i=0;i < (ucSumWEc + 1);i++)
      {
        aucWPosTM[i] = ucWPUNc;
        aucWarnAtPosTM[i] = 0;
        aucWheelPosWarn[i] = 0;
      }
      ushWarnOutTM = 0;
      ucFilterActive = 0;
   }
   else{
      i = pucData[1];
      if(i < (ucMaxPosc + 1))
      {
        if((ucFilIdWarn(i, aucWPosTM[i]) > 0) && ((ushWarnOutTM & (ushWWNoPosc | ushHWNoPosc)) > (unsigned short)0))
        {
          ucRet = 1;
        }
        else{
          if((ucFilIdWarn(i, aucWPosTM[i]) > 0) && ((ushWarnOutTM & NEGATE_USHORT(ushWWNoPosc | ushHWNoPosc)) > (unsigned short)0))
          {
            ucRet = ucPosDepWarnc;
          }
          else{
            ucRet = 0;
          }
        }
        if(ucFilIdWarn(i, aucWPosTM[i]) > 0)
        {
          aucWarnAtPosTM[i] = 0;
          ucFilterActive &= (unsigned char)~ucBitNoc[i];
          tMsg.ucId = ucSumWEc;
          tMsg.ucSystemState = ucRet;
          Warnings2Msg(&tMsg);
          aucWPosTM[i] = ucWPUNc;
        }
      }
   }
   ucRet = 0;
   break;
  case (unsigned short) ucPutWarnVectorSetc:
   {
      pucData++;
      for(i=0;i<ucSumWEc;i++)
      {
        aucWarnAtPosTM[i] = pucData[i];
      }
   }
   break;
  case (unsigned short) ucGetWarnVectorsIdc:
   {
      ucRet = ucFilterActive;
      ucFilterActive = 0;
      for(i=0;i<ucSumWEc;i++)
      {
        pucData[i] = ucFilIdWarn(i,aucWPosTM[i]);
      }
      ucFilterActive = ucRet;
      ucRet = 0;
   }
   break;

  case (unsigned short) ucGetPosOfIdc:
   {
        if(pucData[1] < ucSumWEc)
       {
        pucData[0] = aucWPosTM[ pucData[1] ];
        }
        else{
        pucData[0] = ucSumWEc;
        }

      ucRet = 0;
   }
   break;

  case (unsigned short) ucGetIdcOfPos:
   {
      //initialize the return value
      pucData[0] = ucSumWEc;

      for(i=0; i<ucSumWEc; i++)
      {
        // if requested position is found in aucWPosTM
        if(pucData[1] == aucWPosTM[i])
        {
          // return the ID of the found position
          pucData[0] = i;
        }
      }

      ucRet = 0;

   }
   break;

  default:
   ucRet = 0xff;
   break;
  }
  return ( ucRet );
}

static void TSSMsgInit(unsigned char * pucStatus, const unsigned char * pucIniDat)
{
  unsigned char i;
  static const unsigned char ucTSStateMaskc = 0x03;
  static const unsigned char ucWnValidDefc = 0x28;
  static const unsigned char ucMsValidDefc = 0x00;

  GetDataEE(ucTsIdTMc, pucStatus);
  if( (*pucStatus & ucTSStateMaskc) == ucTssInitializedc)
  {

    GetDataEE(ucCbIdTMc,aucWnValidTM);
   for( i = 0; i < (ucSumWEc + 1);i++)
   {
      aucWPosTM[i] = ucWPUNc;
      aucWarnAtPosTM[i] = 0;
      aucWheelPosWarn[i] = 0;
   }
   ushWarnOutTM = 0;
   ucFilterActive = 0;
  }
  else{

   if((pucIniDat[0] == 0) && (pucIniDat[1] == 0))
   {
      aucWnValidTM[ucIxWnCfgc] = ucWnValidDefc;
      aucWnValidTM[ucIxMsCfgc] = ucMsValidDefc;
   }
   else{
      aucWnValidTM[ucIxWnCfgc] = pucIniDat[0];
      aucWnValidTM[ucIxMsCfgc] = pucIniDat[1];
   }
   PutDataEE(ucCbIdTMc, aucWnValidTM);
    *pucStatus |= ucTssInitializedc;
   PutDataEE(ucTsIdTMc, pucStatus);
   for(i = 0;i < (ucSumWEc + 1);i++)
   {
      aucWPosTM[i] = ucWPUNc;
      aucWarnAtPosTM[i] = 0;
      aucWheelPosWarn[i] = 0;
   }
   ushWarnOutTM = 0;
   ucFilterActive = 0;
  }
}

unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData)
{

  static unsigned char ucTSSMsgStateTM = 0;

  unsigned char ucRet = 0;

  switch( ucAction )
  {
   case (unsigned short) ucPorInitc:
      {
        TSSMsgInit(&ucTSSMsgStateTM, ptData);
        ucRet = ucTSSMsgStateTM;
      }
      break;
   case (unsigned short) ucTssMsgOutc :

      TSSMsgOut(ptData);
      break;
   case (unsigned short) ucDiagServicec:

      ucRet = ucTSSMsgService(ptData);
      break;
    default:
      ucRet = 0xff;
      break;
  }
  return(ucRet);
}

void WrWnValidTMc(struct ParaSubSet *pucData)
{
  if(pucData->ucAccess == ucWrWnValidTMc)
  {
   if((aucWnValidTM[ucIxWnCfgc] != pucData->ucParaByte[ucIxWnCfgc]) ||
      (aucWnValidTM[ucIxMsCfgc] != pucData->ucParaByte[ucIxMsCfgc]))
   {
      aucWnValidTM[ucIxWnCfgc] = pucData->ucParaByte[ucIxWnCfgc];
      aucWnValidTM[ucIxMsCfgc] = (pucData->ucParaByte[ucIxMsCfgc] & 0x0FE);
      PutDataEE(ucCbIdTMc, aucWnValidTM);
   }
  }
}

void RdWnValidTMc(struct ParaSubSet *pucData)
{
  if(pucData->ucAccess == ucRdWnValidTMc)
  {
    pucData->ucParaByte[ucIxWnCfgc] |= (aucWnValidTM[ucIxWnCfgc] & ucMsgMaskc);
    pucData->ucParaByte[ucIxMsCfgc] = 0;
    pucData->ucParaByte[ucIxMsCfgc] |= aucWnValidTM[ucIxMsCfgc];
  }
}

void DCM_InvIf_WarnVectReadHistoryStatus(uint8 u8_Possition, uint8 *u8_WarningValue)
{
  *u8_WarningValue = aucWheelPosWarn[u8_Possition];
}

#ifndef pb_ModulTest_02062003

#else
void ResetTSSMsg(void){
   unsigned char ucLoop;
   const unsigned char ucInitValuec = 0;

   for(ucLoop = 0;ucLoop < (unsigned char) sizeof(aucWnValidTM); ucLoop++)
      aucWnValidTM[ucLoop] = ucInitValuec;
   ushWarnOutTM = (unsigned short) ucInitValuec;
   for(ucLoop = 0; ucLoop < (ucMaxPosc + 1); ucLoop++)
   {
        aucWheelPosWarn[ucLoop] = ucInitValuec;
        aucWarnAtPosTM[ucLoop] = ucInitValuec;
        aucWPosTM[ucLoop] = 8;
   }
   ucFilterActive = 0;
}
#endif

