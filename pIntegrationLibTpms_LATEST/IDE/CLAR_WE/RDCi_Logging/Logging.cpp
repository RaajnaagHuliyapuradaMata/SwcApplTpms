/******************************************************************************/
/* File   : Logging.cpp                                                       */
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "RTE_Type.h"
#include "Logging.h"
#include "DataManagerX.h"
#include "WallocX.h"
#include "State_BzX.h"
#include "State_FzzX.h"
#include "State_ZkX.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"

#ifdef _EcuVirtual
#include "EcuVirtual_stdio.h"
#else
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
static uint32  ulLogBufferPointer = 0;
static uint8   aucLogBuffer[LENGTH_OF_LOG_BUFFER];

static boolean bStartLOG = FALSE;
static boolean bEventLOG = FALSE;

static uint8   *pucFilenameLOG = nullptr;
static uint8   ucSetLOG = 0;

static uint8   ucLastRecEventZomPos = cSumWE;

static unsigned long long ullTimeFromFile = 0;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void    AddToBufferLOG( uint8 * , uint16);

void StartLOG( uint8 ucFilename[], uint8 ucLogSet)
{
  pucFilenameLOG     = ucFilename;
  ucSetLOG           = ucLogSet;

  ulLogBufferPointer = 0;
  ullTimeFromFile    = 0;
  bEventLOG          = FALSE;
  bStartLOG          = TRUE;
}

void StopLOG(void)
{
  static const uint8 ucTitleRec[] = { "SysTime;RecEvent;RDC_MES_TSTMP;SUPP_ID;TYR_ID;PCKG_ID;RDC_DT_1 (pressure);RDC_DT_2 (temperature);RDC_DT_3;RDC_DT_4;RDC_DT_5;RDC_DT_6;RDC_DT_7 (RSSI);RDC_DT_8;ALIV_RDC_DT_PCK_1;ALIV_RDC_DT_PCK_2;RDC_SYNC_TSTMP_LO;RDC_SYNC_TSTMP_HI;HistSlot;HistWp;BZ;FZZ;ZK;v [km/h];TA [°C];TAv [°C];pAmb [hPa];UnAip;UnTemp;PWFakt;PWFlast;Parking time [s];TAinit [°C];" };
  static const uint8 ucTitleWhl[] = { "WarnOut;WGrpA;WGrpB;WGrpC;WGrpD;WGrpE;WGrpF;WGrpG;WGrpH;WarnOut VL; WarnTonnage VL;WarnAirmass VL;WarnVector VL;SetLevel VL (Ppanne) [hPa];ResetLevel VL (Ppanne) [hPa];SetLevel VL (Pmin) [hPa];ResetLevel VL (Pmin) [hPa];SetLevel VL (Pwarn) [hPa];ResetLevel VL (Pwarn) [hPa];SetLevel VL (PwarnTol) [hPa];ResetLevel VL (PwarnTol) [hPa];SetLevel VL (Pvorw) [hPa];ResetLevel VL (Pvorw) [hPa];SetLevel VL (Pdhw) [hPa];ResetLevel VL (Pdhw) [hPa];SetLevel VL (FT) [hPa];ResetLevel VL (FT) [hPa];LongDelay VL;ShortDelay VL;pRef VL (DHW) [hPa];pLast VL (DHW) [hPa];tCnt VL (DHW);tCntLatch VL (DHW);pSollKalt VL [hPa];TSollKalt VL [°C];pSollWarm VL [hPa];TSollWarm VL [°C];mSoll VL;pAmp VL [hPa];WarnOut VR; WarnTonnage VR;WarnAirmass VR;WarnVector VR;SetLevel VR (Ppanne) [hPa];ResetLevel VR (Ppanne) [hPa];SetLevel VR (Pmin) [hPa];ResetLevel VR (Pmin) [hPa];SetLevel VR (Pwarn) [hPa];ResetLevel VR (Pwarn) [hPa];SetLevel VR (PwarnTol) [hPa];ResetLevel VR (PwarnTol) [hPa];SetLevel VR (Pvorw) [hPa];ResetLevel VR (Pvorw) [hPa];SetLevel VR (Pdhw) [hPa];ResetLevel VR (Pdhw) [hPa];SetLevel VR (FT) [hPa];ResetLevel VR (FT) [hPa];LongDelay VR;ShortDelay VR;pRef VR (DHW) [hPa];pLast VR (DHW) [hPa];tCnt VR (DHW);tCntLatch VR (DHW);pSollKalt VR [hPa];TSollKalt VR [°C];pSollWarm VR [hPa];TSollWarm VR [°C];mSoll VR;pAmp VR [hPa];WarnOut HL; WarnTonnage HL;WarnAirmass HL;WarnVector HL;SetLevel HL (Ppanne) [hPa];ResetLevel HL (Ppanne) [hPa];SetLevel HL (Pmin) [hPa];ResetLevel HL (Pmin) [hPa];SetLevel HL (Pwarn) [hPa];ResetLevel HL (Pwarn) [hPa];SetLevel HL (PwarnTol) [hPa];ResetLevel HL (PwarnTol) [hPa];SetLevel HL (Pvorw) [hPa];ResetLevel HL (Pvorw) [hPa];SetLevel HL (Pdhw) [hPa];ResetLevel HL (Pdhw) [hPa];SetLevel HL (FT) [hPa];ResetLevel HL (FT) [hPa];LongDelay HL;ShortDelay HL;pRef HL (DHW) [hPa];pLast HL (DHW) [hPa];tCnt HL (DHW);tCntLatch HL (DHW);pSollKalt HL [hPa];TSollKalt HL [°C];pSollWarm HL [hPa];TSollWarm HL [°C];mSoll HL;pAmp HL [hPa];WarnOut HR; WarnTonnage HR;WarnAirmass HR;WarnVector HR;SetLevel HR (Ppanne) [hPa];ResetLevel HR (Ppanne) [hPa];SetLevel HR (Pmin) [hPa];ResetLevel HR (Pmin) [hPa];SetLevel HR (Pwarn) [hPa];ResetLevel HR (Pwarn) [hPa];SetLevel HR (PwarnTol) [hPa];ResetLevel HR (PwarnTol) [hPa];SetLevel HR (Pvorw) [hPa];ResetLevel HR (Pvorw) [hPa];SetLevel HR (Pdhw) [hPa];ResetLevel HR (Pdhw) [hPa];SetLevel HR (FT) [hPa];ResetLevel HR (FT) [hPa];LongDelay HR;ShortDelay HR;pRef HR (DHW) [hPa];pLast HR (DHW) [hPa];tCnt HR (DHW);tCntLatch HR (DHW);pSollKalt HR [hPa];TSollKalt HR [°C];pSollWarm HR [hPa];TSollWarm HR [°C];mSoll HR;pAmp HR [hPa];" };
  static const uint8 ucTitleWal[] = { "TelAll;TelLearn;TelAlloc;DistStd[0];DistStd[1];DistStd[2];DistStd[3];MVdN[0];MVdN[1];MVdN[2];MVdN[3];MVdN2[0];MVdN2[1];MVdN2[2];MVdN2[3];DistShdw[0];DistShdw[1];DistShdw[2];DistShdw[3];DeltaSum1[0];DeltaSum1[1];DeltaSum1[2];DeltaSum1[3];DeltaSum2[0];DeltaSum2[1];DeltaSum2[2];DeltaSum2[3];RelCmp[0];RelCmp[1];RelCmp[2];RelCmp[3];DeltaMin;LinABS[0];LinABS[1];LinABS[2];LinABS[3];" };
  static const uint8 ucTitleOut[] = { "CCM_fKL;CCM_vKL;AvlPTyr VL [bar-kPa-psi];AvlPTyr VR [bar-kPa-psi];AvlPTyr HL [bar-kPa-psi];AvlPTyr HR [bar-kPa-psi];AvlTTyr VL [°C-°F];AvlTTyr VR [°C-°F];AvlTTyr HL [°C-°F];AvlTTyr HR [°C-°F];TarPTyr VL [bar-kPa-psi];TarPTyr VR [bar-kPa-psi];TarPTyr HL [bar-kPa-psi];TarPTyr HR [bar-kPa-psi];StTyreINFO;StTyreTPL;StTyreTFAI;TyrSelAct;Donut;L_OL_TYP_TYR;SLCTN_SUTR_AVLB;SLCTN_WITR_AVLB;TAR_P_LOCO_TPCT;TYR_SEA_TPCT;OP_IDR_MSGC;MAN_SLCTN;CRdciMaxCorTime [sec];CRdciCorHoldOffTime [sec];CRdciMaxCorRcp [hPa];CRdciResetPlausi;CRdciDispReset;CRdciErfsEnable;pLast VL [hPa];Tlast VL [°C];pLast VR [hPa];Tlast VR [°C];pLast HL [hPa];Tlast HL [°C];pLast HR [hPa];Tlast HR [°C];pSollKalt VL [hPa];TSollKalt VL [°C];pSollWarm VL [hPa];TSollWarm VL [°C];mSoll VL;pAmp VL [hPa];pSollKalt VR [hPa];TSollKalt VR [°C];pSollWarm VR [hPa];TSollWarm VR [°C];mSoll VR;pAmp VR [hPa];pSollKalt HL [hPa];TSollKalt HL [°C];pSollWarm HL [hPa];TSollWarm HL;mSoll HL;pAmp HL [hPa];pSollKalt HR [hPa];TSollKalt HR [°C];pSollWarm HR [hPa];TSollWarm HR [°C];mSoll HR;pAmp HR [hPa];pInit(Tinit) VL [hPa];Tinit VL [°C];pInit(Tinit) VR [hPa];Tinit VR [°C];pInit(Tinit) HL [hPa];Tinit HL [°C];pInit(Tinit) HR [hPa];Tinit HR [°C];MaxCoolingTime [sec];CoolAvlPkalt VL [hPa];CoolAvlTkalt VL [°C];CoolAvlPwarm VL [hPa];CoolAvlTwarm VL [°C];CoolAvlP_t VL [hPa];CoolAvlT_t VL [°C];CoolTarPkalt VL [hPa];CoolTarTkalt VL [°C];CoolTarP_t VL [hPa];CoolTarPwarm VL [hPa];CoolAvlPkalt VR [hPa];CoolAvlTkalt VR [°C];CoolAvlPwarm VR [hPa];CoolAvlTwarm VR [°C];CoolAvlP_t VR [hPa];CoolAvlT_t VR [°C];CoolTarPkalt VR [hPa];CoolTarTkalt VR [°C];CoolTarPwarm VR [hPa];CoolTarP_t VR [hPa];CoolAvlPkalt HL [hPa];CoolAvlTkalt HL [°C];CoolAvlPwarm HL [hPa];CoolAvlTwarm HL [°C];CoolAvlP_t HL [hPa];CoolAvlT_t HL [°C];CoolTarPkalt HL [hPa];CoolTarTkalt HL [°C];CoolTarPwarm HL [hPa];CoolTarP_t HL [hPa];CoolAvlPkalt HR [hPa];CoolAvlTkalt HR [°C];CoolAvlPwarm HR [hPa];CoolAvlTwarm HR [°C];CoolAvlP_t HR [hPa];CoolAvlT_t HR [°C];CoolTarPkalt HR [hPa];CoolTarTkalt HR [°C];CoolTarPwarm HR [hPa];CoolTarP_t HR [hPa];ElapsedCoolingTime [sec];TimeTicks [sec];CoolingCaptTime [sec];" };
  static const uint8 ucTitleDtc[] = { "DT_PCKG_MsgTio [sec];DT_PCKG_SigErrTio [sec];DT_PCKG_AlivErrBadCnt;DT_PCKG_AlivErrGoodCnt;A_TEMP_MsgTio [sec];A_TEMP_SigErrTio [sec];EINHEITEN_MsgTio [sec];EINHEITEN_SigErrTio [sec];CON_VEH_MsgTio [sec];CON_VEH_CrcErrBadCnt;CON_VEH_AlivErrBadCnt;CON_VEH_SigErrTio [sec];RELATIVZEIT_MsgTio [sec];RELATIVZEIT_SigErrTio [sec];DT_PT_1_MsgTio [sec];DT_PT_1_SigErrTio [sec];FZZSTD_SigErrTio [sec];KILOMETERSTAND_SigErrTio [sec];NMEARawData2Part2_MsgTio [sec];NMEARawData2Part2_SigErrTio [sec];NMEARawData2Part3_MsgTio [sec];NMEARawData2Part3_SigErrTio [sec];UHRZEIT_DATUM_SigErrTio [sec];WMOM_DRV_4_MsgTio [sec];WMOM_DRV_4_SigErrTio [sec];V_VEH_MsgTio [sec];V_VEH_CrcErrTio;V_VEH_AlivErrBadCnt;V_VEH_SigQualErrTio [sec];" };
  static const uint8 ucTitleDbg[] = { "DBG_SUPP1_00 (MUX#1);DBG_SUPP1_01;DBG_SUPP1_02;DBG_SUPP1_03;DBG_SUPP1_04;DBG_SUPP1_05;DBG_SUPP1_06;DBG_SUPP1_07;DBG_SUPP1_08;DBG_SUPP1_09;DBG_SUPP1_10;DBG_SUPP1_11;DBG_SUPP1_12;DBG_SUPP1_13;DBG_SUPP1_14;DBG_SUPP1_15;DBG_SUPP2_00 (MUX#2);DBG_SUPP2_01;DBG_SUPP2_02;DBG_SUPP2_03;DBG_SUPP2_04;DBG_SUPP2_05;DBG_SUPP2_06;DBG_SUPP2_07;DBG_SUPP2_08;DBG_SUPP2_09;DBG_SUPP2_10;DBG_SUPP2_11;DBG_SUPP2_12;DBG_SUPP2_13;DBG_SUPP2_14;DBG_SUPP2_15;" };

  static const uint8 ucTitleEnd[] = { "\n" };
  uint8  ucTitle[sizeof(ucTitleRec) + sizeof(ucTitleWhl) + sizeof(ucTitleWal) + sizeof(ucTitleOut) + sizeof(ucTitleDtc) + sizeof(ucTitleDbg) + sizeof(ucTitleEnd)] = {0};
  uint16 ushRealTitleSize = 0;

  strcat_s((char*)ucTitle, sizeof(ucTitle), (char*) ucTitleRec);
  ushRealTitleSize += (sizeof(ucTitleRec) - 1);

  if((ucSetLOG & LOG_SET_WHL) == LOG_SET_WHL)
  {
    strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleWhl);
    ushRealTitleSize += (sizeof(ucTitleWhl) - 1);
  }

  if((ucSetLOG & LOG_SET_WAL) == LOG_SET_WAL)
  {
    strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleWal);
    ushRealTitleSize += (sizeof(ucTitleWal) - 1);
  }

  if((ucSetLOG & LOG_SET_OUT) == LOG_SET_OUT)
  {
    strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleOut);
    ushRealTitleSize += (sizeof(ucTitleOut) - 1);
  }

  if((ucSetLOG & LOG_SET_DTC) == LOG_SET_DTC)
  {
    strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleDtc);
    ushRealTitleSize += (sizeof(ucTitleDtc) - 1);
  }

  if((ucSetLOG & LOG_SET_DBG) == LOG_SET_DBG)
  {
    strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleDbg);
    ushRealTitleSize += (sizeof(ucTitleDbg) - 1);
  }

  strcat_s((char*)ucTitle, sizeof(ucTitle), (char*)ucTitleEnd);
  ushRealTitleSize += (sizeof(ucTitleEnd) - 1);

  if( bEventLOG == TRUE)
  {

    PutInitWhlToBufferLOG();
    PutInitWalToBufferLOG();
    PutInitOutToBufferLOG();
    PutInitDtcToBufferLOG();
    PutInitDbgToBufferLOG();

    PutNewLineToBufferLOG();
  }

  FILE* fStream;
  const char mode[] = "w";

  if( fopen_s( &fStream, (const char *) pucFilenameLOG, mode) == 0)
  {
    if( fStream != NULL)
    {

      fwrite( ucTitle, sizeof(uint8), ushRealTitleSize, fStream);
      fwrite( aucLogBuffer, sizeof(uint8), ulLogBufferPointer, fStream);

      fclose( fStream);
    }
  }

  bEventLOG      = FALSE;
  bStartLOG      = FALSE;
}

void PutTimeFromFileLOG( unsigned long long ullTime)
{
  ullTimeFromFile = ullTime;
}

void AddOffsetToTimeLOG( unsigned long long ullTimeOffset)
{
  ullTimeFromFile += ullTimeOffset;
}

boolean bLineBufferEmptyLOG(void)
{
  return !bEventLOG;
}

void PutInitRecToBufferLOG(void)
{
  static const uint8 ucInitLineRec[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {

      AddToBufferLOG( (uint8 *) ucInitLineRec, sizeof(ucInitLineRec) - 1);
      ucLastRecEventZomPos = cSumWE;
    }
  }
}

void PutInitWhlToBufferLOG(void)
{
  static const uint8 ucInitLineWhl[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {
      if((ucSetLOG & LOG_SET_WHL) == LOG_SET_WHL)
      {

        AddToBufferLOG( (uint8 *) ucInitLineWhl, sizeof(ucInitLineWhl) - 1);
      }
    }
  }
}

void PutInitWalToBufferLOG(void)
{
  static const uint8 ucInitLineWal[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {
      if((ucSetLOG & LOG_SET_WAL) == LOG_SET_WAL)
      {

        AddToBufferLOG( (uint8 *) ucInitLineWal, sizeof(ucInitLineWal) - 1);
      }
    }
  }
}

void PutInitOutToBufferLOG(void)
{
  static const uint8 ucInitLineOut[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {
      if((ucSetLOG & LOG_SET_OUT) == LOG_SET_OUT)
      {

        AddToBufferLOG( (uint8 *) ucInitLineOut, sizeof(ucInitLineOut) - 1);
      }
    }
  }
}

void PutInitDtcToBufferLOG(void)
{
  static const uint8 ucInitLineDtc[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {
      if((ucSetLOG & LOG_SET_DTC) == LOG_SET_DTC)
      {

        AddToBufferLOG( (uint8 *) ucInitLineDtc, sizeof(ucInitLineDtc) - 1);
      }
    }
  }
}

void PutInitDbgToBufferLOG(void)
{
  static const uint8 ucInitLineDbg[] = { "=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();=NV();" };

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {
      if((ucSetLOG & LOG_SET_DBG) == LOG_SET_DBG)
      {

        AddToBufferLOG( (uint8 *) ucInitLineDbg, sizeof(ucInitLineDbg) - 1);
      }
    }
  }
}

void PutRfDataToBufferLOG( ImpTypeRecCddRdcData *tRfData)
{
  uint8  ucHistSlot;
  uint32 ulID;

  if( bStartLOG == TRUE)
  {
    if( bEventLOG == TRUE)
    {

      PutInitWhlToBufferLOG();
      PutInitWalToBufferLOG();
      PutInitOutToBufferLOG();
      PutInitDtcToBufferLOG();
      PutInitDbgToBufferLOG();

      PutNewLineToBufferLOG();
    }

    bEventLOG = TRUE;

    PutUnsignedLongLongToBufferLOG( ullTimeFromFile);

    if( tRfData == NULL)
    {

      PutInitRecToBufferLOG();

      ucLastRecEventZomPos = cSumWE;
    }else{
      PutByteToBufferLOG( ucGetRdcEventCounterDM());
      PutWordToBufferLOG( tRfData->RDC_MES_TSTMP);
      PutByteToBufferLOG( tRfData->SUPP_ID);
      PutDwordToBufferLOG( tRfData->TYR_ID);
      PutByteToBufferLOG( tRfData->PCKG_ID);
      PutByteToBufferLOG( tRfData->RDC_DT_1);
      PutByteToBufferLOG( tRfData->RDC_DT_2);
      PutByteToBufferLOG( tRfData->RDC_DT_3);
      PutByteToBufferLOG( tRfData->RDC_DT_4);
      PutByteToBufferLOG( tRfData->RDC_DT_5);
      PutByteToBufferLOG( tRfData->RDC_DT_6);
      PutByteToBufferLOG( tRfData->RDC_DT_7);
      PutByteToBufferLOG( tRfData->RDC_DT_8);
      PutByteToBufferLOG( tRfData->ALIV_RDC_DT_PCK_1);
      PutByteToBufferLOG( tRfData->ALIV_RDC_DT_PCK_2);
      PutDwordToBufferLOG( tRfData->RDC_SYNC_TSTMP_LO);
      PutDwordToBufferLOG( tRfData->RDC_SYNC_TSTMP_HI);

      ulID = tRfData->TYR_ID + ((uint32)tRfData->SUPP_ID << 28);
      ucHistSlot = ucGetColOfID( &ulID);
      PutByteToBufferLOG( ucHistSlot);
      PutByteToBufferLOG( ucGetWPOfColWAL( ucHistSlot));

      ucLastRecEventZomPos = ucGetZOMPosOfID(&ulID);
    }

    PutWordToBufferLOG( ushGetBetriebszustandBZ( 0xFFFF));
    PutWordToBufferLOG( ushGetFahrzeugzustandFZZ( 0xFFFF));
    PutWordToBufferLOG( ushGetZustandskennungZK( 0xFFFF));

    PutWordToBufferLOG( GETushSpeedFZZ());
    PutSignedByteToBufferLOG( GETscOutdoorTemperatureFZZ());
    PutSignedByteToBufferLOG( GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC));
    PutWordToBufferLOG( (uint16) GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC) * 25);

    PutByteToBufferLOG( GETucUnAipEE( Rte_Inst_CtApHufTpmsSWC));
    PutByteToBufferLOG( GETucUnTempEE( Rte_Inst_CtApHufTpmsSWC));

    PutByteToBufferLOG( ucGetStatusConditionVehicleFZZ());
    PutByteToBufferLOG( ucGetStatusLastConditionVehicleFZZ());

    PutDwordToBufferLOG( ulGetStopTimeDM());

    PutSignedByteToBufferLOG( GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC));
  }else{
    ucLastRecEventZomPos = cSumWE;
  }
}

uint8 GetLastRecEventZomPos(void)
{
  return ucLastRecEventZomPos;
}

void PutNewLineToBufferLOG(void)
{

  uint8 aucChar[2];

  if( bEventLOG == TRUE)
  {

    aucChar[0] = 10;
    AddToBufferLOG( aucChar, 1);

    bEventLOG = FALSE;

  }
}

static void AddToBufferLOG( uint8 * pucArray, uint16 ushLen)
{

  if( ulLogBufferPointer < (uint32)(LENGTH_OF_LOG_BUFFER - ushLen - 10))
  {

    memcpy( &aucLogBuffer[ulLogBufferPointer], pucArray, ushLen);
    ulLogBufferPointer += ushLen;
  }
}

void PutByteToBufferLOG( uint8 ucByte)
{
  uint8 ucLoop;
  uint8 ucBcdChar[MAX_CHAR_BYTE + 2];

  if( bEventLOG == TRUE)
  {
    ucBcdChar[0] = ' ';

    ucLoop = MAX_CHAR_BYTE;

    do
    {
      ucBcdChar[ucLoop] = (ucByte % 10) + 0x30;
      ucByte /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_BYTE + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_BYTE + 2);
  }
}

void PutSignedByteToBufferLOG( sint8 scByte)
{
  uint8 ucLoop, ucByte;
  uint8 ucBcdChar[MAX_CHAR_BYTE + 2];

  if( bEventLOG == TRUE)
  {
    if( scByte < 0)
    {

      ucByte = (uint8) (256 - scByte);
      ucBcdChar[0] = '-';
    }else{
      ucByte = (uint8) scByte;
      ucBcdChar[0] = ' ';
    }

    ucLoop = MAX_CHAR_BYTE;

    do
    {
      ucBcdChar[ucLoop] = (ucByte % 10) + 0x30;
      ucByte /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_BYTE + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_BYTE + 2);
  }
}

void PutWordToBufferLOG( uint16 ushWord)
{
  uint8 ucLoop;
  uint8 ucBcdChar[MAX_CHAR_WORD + 2];

  if( bEventLOG == TRUE)
  {
    ucBcdChar[0] = ' ';

    ucLoop = MAX_CHAR_WORD;

    do
    {
      ucBcdChar[ucLoop] = (ushWord % 10) + 0x30;
      ushWord /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_WORD + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_WORD + 2);
  }
}

void PutSignedWordToBufferLOG( sint16 sshWord)
{
  uint8  ucLoop;
  uint16 ushWord;
  uint8 ucBcdChar[MAX_CHAR_WORD + 2];

  if( bEventLOG == TRUE)
  {
    if( sshWord < 0)
    {

      ushWord = (uint16) (65536 - sshWord);
      ucBcdChar[0] = '-';
    }else{
      ushWord = (uint16) sshWord;
      ucBcdChar[0] = ' ';
    }

    ucLoop = MAX_CHAR_WORD;

    do
    {
      ucBcdChar[ucLoop] = (ushWord % 10) + 0x30;
      ushWord /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_WORD + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_WORD + 2);
  }
}

void PutDwordToBufferLOG( uint32 ulDword)
{
  uint8 ucLoop;
  uint8 ucBcdChar[MAX_CHAR_DWORD + 2];

  if( bEventLOG == TRUE)
  {
    ucBcdChar[0] = ' ';

    ucLoop = MAX_CHAR_DWORD;

    do
    {
      ucBcdChar[ucLoop] = (ulDword % 10) + 0x30;
      ulDword /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_DWORD + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_DWORD + 2);
  }
}

void PutSignedDwordToBufferLOG( sint32 slDword)
{
  uint8  ucLoop;
  uint32 ulDword;
  uint8  ucBcdChar[MAX_CHAR_DWORD + 2];

  if( bEventLOG == TRUE)
  {
    if( slDword < 0)
    {

      ulDword = (uint32) (4294967296 - slDword);
      ucBcdChar[0] = '-';
    }else{
      ulDword = (uint32) slDword;
      ucBcdChar[0] = ' ';
    }

    ucLoop = MAX_CHAR_DWORD;

    do
    {
      ucBcdChar[ucLoop] = (ulDword % 10) + 0x30;
      ulDword /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_DWORD + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_DWORD + 2);
  }
}

void PutUnsignedLongLongToBufferLOG( unsigned long long ullLongLong)
{
  uint8 ucLoop;
  uint8 ucBcdChar[MAX_CHAR_LONG_LONG + 2];

  if( bEventLOG == TRUE)
  {
    ucBcdChar[0] = ' ';

    ucLoop = MAX_CHAR_LONG_LONG;

    do
    {
      ucBcdChar[ucLoop] = (ullLongLong % 10) + 0x30;
      ullLongLong /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_LONG_LONG + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_LONG_LONG + 2);
  }
}

void PutSignedLongLongToBufferLOG( signed long long sllLongLong)
{
  uint8               ucLoop;
  unsigned long long  ullLongLong;
  uint8               ucBcdChar[MAX_CHAR_LONG_LONG + 2];

  if( bEventLOG == TRUE)
  {
    if( sllLongLong < 0)
    {

      ullLongLong = (((unsigned long long) sllLongLong ^ 0xFFFFFFFFFFFFFFFFu) + 1);
      ucBcdChar[0] = '-';
    }else{
      ullLongLong = (unsigned long long) sllLongLong;
      ucBcdChar[0] = ' ';
    }

    ucLoop = MAX_CHAR_LONG_LONG;

    do
    {
      ucBcdChar[ucLoop] = (ullLongLong % 10) + 0x30;
      ullLongLong /= 10;
      ucLoop--;
    }while( ucLoop > 0);

    ucBcdChar[MAX_CHAR_LONG_LONG + 1] = ';';
    AddToBufferLOG( ucBcdChar, MAX_CHAR_LONG_LONG + 2);
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

