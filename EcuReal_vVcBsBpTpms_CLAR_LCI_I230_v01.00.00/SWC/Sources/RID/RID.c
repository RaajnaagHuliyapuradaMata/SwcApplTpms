#include "RID.h"
#include "wallocX.h"
#include "datamanagerX.h"
#include "infotyreX.h"
#include "state_BzX.h"
#include "EeRidQrBlockX.h"
#include "EeErfsBlockX.h"
#include "RdcTsaServicesX.h"
#include "CodingDataX.h"
#include "eRFS_X.h"

#define cAutoFlagMask   ((uint8)(0x01))
#define cAllAutoFlags   ((uint8)(0x0F))
#define cManFlagMask    ((uint8)(0x10))
#define cAllManFlags    ((uint8)(0xF0))
#define cFrontAxis      ((uint8)(0x01))
#define cRearAxis       ((uint8)(0x02))
#define cDimDataChanged ((uint8)(0x01))
#define cDimDataHisUse  ((uint8)(0x10))
#define cOEM1Flag       ((uint8)(0x01))
#define cOEM2Flag       ((uint8)(0x10))

static uint32 TyreIdBufRID[cSumWE] = {0};
static uint8 TyreDimBufRID[cSumWE][cTyreDimSize];
static uint8 TyreDOTBufRID[cSumWE][cTyreDOTSize];
static uint8 TyreOEMBufRID[cSumWE][cTyreOEMSize];
static uint8 HistReDimBufRID[cAnzRad][cTyreDimSize] = {{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};
static uint8 HistReDOTBufRID[cAnzRad][cTyreDOTSize] = {{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},};
static uint8 HistReOEMBufRID[cAnzRad][cTyreOEMSize];
static uint8 ucRidManAutoFlag = 0x00;
static uint8 ucRidOem1Oem2Flag = 0x00;
static const uint8 cBufInitValRID = 0xFF;
static uint8 ResHistReDimDataFA[cTyreDimSize] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
static uint8 SavedDimDataChangedFlagRID = 0x00;

uint8 GetTyreDimDataRID(const uint8 HisIx, const uint8 x)
{
  return (HistReDimBufRID[HisIx][x]);
}

uint8 GetTyreDOTDataRID(const uint8 HisIx, const uint8 x)
{
  return (HistReDOTBufRID[HisIx][x]);
}

uint8 GetTyreOEMDataRID(const uint8 HisIx, const uint8 x)
{
  return (HistReOEMBufRID[HisIx][x]);
}

uint8 GetRidManAutoFLagRID(void)
{
  return(ucRidManAutoFlag);
}

void SaveTyreDimensionDataRID(ImpTypeRecCddRdcData tReData)
 {
	uint8 ucIdBufIx = cSumWE;
	uint32 l_ulID;

	l_ulID = (((uint32)tReData.SUPP_ID << 28)|(uint32)tReData.TYR_ID);

	ucIdBufIx = SearchRIDBufSlot(l_ulID);

	if(ucIdBufIx < cSumWE)
	{
		TyreDimBufRID[ucIdBufIx][0] = tReData.RDC_DT_1;
		TyreDimBufRID[ucIdBufIx][1] = tReData.RDC_DT_2;
		TyreDimBufRID[ucIdBufIx][2] = tReData.RDC_DT_3;
		TyreDimBufRID[ucIdBufIx][3] = tReData.RDC_DT_4;
		TyreDimBufRID[ucIdBufIx][4] = tReData.RDC_DT_5;
		TyreDimBufRID[ucIdBufIx][5] = tReData.RDC_DT_6;
	}
	else
	{
	}
 }

void SaveTyreDOTDataRID(ImpTypeRecCddRdcData tReData)
 {
	uint8 ucIdBufIx = cSumWE;
	uint32 l_ulID;

	l_ulID = (((uint32)tReData.SUPP_ID << 28)|(uint32)tReData.TYR_ID);

	ucIdBufIx = SearchRIDBufSlot(l_ulID);

	if(ucIdBufIx < cSumWE)
	{
		TyreDOTBufRID[ucIdBufIx][0] = tReData.RDC_DT_1;
		TyreDOTBufRID[ucIdBufIx][1] = tReData.RDC_DT_2;
		TyreDOTBufRID[ucIdBufIx][2] = tReData.RDC_DT_3;
		TyreDOTBufRID[ucIdBufIx][3] = tReData.RDC_DT_4;
		TyreDOTBufRID[ucIdBufIx][4] = tReData.RDC_DT_5;
		TyreDOTBufRID[ucIdBufIx][5] = tReData.RDC_DT_6;
		TyreDOTBufRID[ucIdBufIx][6] = tReData.RDC_DT_7;
		TyreDOTBufRID[ucIdBufIx][7] = tReData.RDC_DT_8;
	}
	else
	{
	}
 }

void SaveTyreOE1DataRID(ImpTypeRecCddRdcData tReData)
 {
	uint8 ucIdBufIx = cSumWE;
	uint32 l_ulID;

	l_ulID = (((uint32)tReData.SUPP_ID << 28)|(uint32)tReData.TYR_ID);

	ucIdBufIx = SearchRIDBufSlot(l_ulID);

	if(ucIdBufIx < cSumWE)
	{
		TyreOEMBufRID[ucIdBufIx][0] = tReData.RDC_DT_1;
		TyreOEMBufRID[ucIdBufIx][1] = tReData.RDC_DT_2;
		TyreOEMBufRID[ucIdBufIx][2] = tReData.RDC_DT_3;
		TyreOEMBufRID[ucIdBufIx][3] = tReData.RDC_DT_4;
		TyreOEMBufRID[ucIdBufIx][4] = tReData.RDC_DT_5;
		TyreOEMBufRID[ucIdBufIx][5] = tReData.RDC_DT_6;
	}
	else
	{
	}
 }

void SaveTyreOE2DataRID(ImpTypeRecCddRdcData tReData)
 {
	uint8 ucIdBufIx = cSumWE;
	uint32 l_ulID;

	l_ulID = (((uint32)tReData.SUPP_ID << 28)|(uint32)tReData.TYR_ID);

	ucIdBufIx = SearchRIDBufSlot(l_ulID);

	if(ucIdBufIx < cSumWE)
	{
		TyreOEMBufRID[ucIdBufIx][cTyreOEM1Size+0] = tReData.RDC_DT_1;
		TyreOEMBufRID[ucIdBufIx][cTyreOEM1Size+1] = tReData.RDC_DT_2;
		TyreOEMBufRID[ucIdBufIx][cTyreOEM1Size+2] = tReData.RDC_DT_3;
		TyreOEMBufRID[ucIdBufIx][cTyreOEM1Size+3] = tReData.RDC_DT_4;
		TyreOEMBufRID[ucIdBufIx][cTyreOEM1Size+4] = tReData.RDC_DT_5;
	}
	else
	{
	}
 }

static void ResetTyreDOTOEDataOfReIdRID(const uint32 l_ulID)
{
  uint8 i, ucIdBufIx = cSumWE;

  ucIdBufIx = SearchRIDBufSlot(l_ulID);

  if(ucIdBufIx < cSumWE)
  {
    for (i=0;i<cTyreDOTSize;i++)
    {
      TyreDOTBufRID[ucIdBufIx][i] = cBufInitValRID;
    }
    for (i=0;i<(cTyreOEM1Size+cTyreOEM2Size);i++)
    {
      TyreOEMBufRID[ucIdBufIx][i] = cBufInitValRID;
    }
  }
}

static void ResetTyreDimDataOfReIdRID(const uint32 l_ulID)
{
  uint8 i, ucIdBufIx = cSumWE;

  ucIdBufIx = SearchRIDBufSlot(l_ulID);

  if(ucIdBufIx < cSumWE)
  {
    for (i=0;i<cTyreDimSize;i++)
    {
      TyreDimBufRID[ucIdBufIx][i] = cBufInitValRID;
    }
  }
}

void CheckTyreStatusRID( Rte_Instance self, ImpTypeRecCddRdcData tReData)
{
  uint8  ucHisIx, Pos;
	uint32 l_ulID;

	l_ulID = (((uint32)tReData.SUPP_ID << 28)|(uint32)tReData.TYR_ID);

  ucHisIx = ucGetColOfID(&l_ulID);

  if(ucHisIx < cAnzRad)
  {

    if((tReData.RDC_DT_3 == 0xFC) || (tReData.RDC_DT_3 == 0xFD))
    {

      ResetTyreDimDataOfReIdRID(l_ulID);

      ResetTyreDOTOEDataOfReIdRID(l_ulID);

      DeleteRidDataOfHisColRID( self, (uint8) (0x01 << ucHisIx));

      Pos = ucGetWPOfColWAL(ucHisIx);

      if(Pos < cMaxLR)
      {
        ResetQRTyreMountedFlags( self, (uint8) (0x10 << Pos));
      }
    }
    else
    {

      if(tReData.RDC_DT_3 == 0xFE)
      {

        if(ushGetBetriebszustandBZ(cZO_FINISH|cLOC_INTERRUPTED|cZO_TIMEOUT) == 0x00)
        {

          if((ucRidManAutoFlag & (uint8)(cAutoFlagMask << ucHisIx)) == (uint8)(cAutoFlagMask << ucHisIx))
          {

            ResetTyreDOTOEDataOfReIdRID(l_ulID);

            DeleteRidDataOfHisColRID( self, (uint8)(0x01<<ucHisIx));
          }
        }

        Pos = ucGetWPOfColWAL(ucHisIx);

        if(Pos < cMaxLR)
        {
          ResetQRTyreMountedFlags( self, (uint8) (0x10 << Pos));
        }
      }
    }
  }

}

void InitRidDataRID( Rte_Instance self)
{
  uint8 i,j;
  boolean bTemp = FALSE;

  for (i = 0; i < cSumWE; i++)
  {
    TyreIdBufRID[i] = 0x00000000U;

    for (j = 0; j < cTyreDimSize; j++)
    {
      TyreDimBufRID[i][j] = cBufInitValRID;

      if(i<cAnzRad)
      {
        HistReDimBufRID[i][j] = cBufInitValRID;
      }
    }
  }
  for (i = 0; i < cSumWE; i++)
  {
    for (j = 0; j < cTyreDOTSize; j++)
    {
      TyreDOTBufRID[i][j] = cBufInitValRID;

      if(i<cAnzRad)
      {
        HistReDOTBufRID[i][j] = cBufInitValRID;
      }
    }
  }
  for (i = 0; i < cSumWE; i++)
  {
    for (j = 0; j < (cTyreOEMSize); j++)
    {
      TyreOEMBufRID[i][j] = cBufInitValRID;

      if(i<cAnzRad)
      {
        HistReOEMBufRID[i][j] = cBufInitValRID;
      }
    }
  }
  ucRidOem1Oem2Flag = 0x00;

  ucRidManAutoFlag = 0x00;

  for (i = 0; i < cAnzRad; i++)
  {

    for(j=0;j<cTyreDimSize;j++)
    {

      if(GETTyreDimDataEE( self, i, j) != cBufInitValRID)
      {
        bTemp = TRUE;
      }
    }

    if(bTemp == TRUE)
    {
      bTemp = FALSE;

      for(j=0;j<cTyreDOTSize;j++)
      {

        if(GETTyreDOTDataEE( self, i, j) != cBufInitValRID)
        {

          bTemp = TRUE;
        }
      }

      if(bTemp == TRUE)
      {
        ucRidManAutoFlag  |= (uint8)(cAutoFlagMask << i);
      }
      else
      {
        ucRidManAutoFlag  |= (uint8)(cManFlagMask << i);
      }
    }
  }
}

void SaveRidDataAndCompareRID( Rte_Instance self){
  uint32 ulHistID;
  uint8 i,j,ucIx,ucResCol;
  uint8 ResHistReDimDataRA[cTyreDimSize] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

  if(bGetCRdciRidEnableCD() == TRUE)
  {
    SavedDimDataChangedFlagRID = 0x00;
    ucRidManAutoFlag = 0x00;

    for (i=0; i < cAnzRad; i++)
    {
      ucIx = cSumWE;
      ulHistID = ulGetIDOfColWAL(i);

      for (j=0; j<cSumWE; j++)
      {
        if(ulHistID == TyreIdBufRID[j])
        {
          ucIx = j;
        }
      }

      if(ucIx < cSumWE)
      {
        SaveHistReRidDataRID( self, i, ucIx);
      }
      else
      {
        RestoreSavedReRidDataRID( self, i);
      }
    }

    (void)CheckAxisRidDataRID( self, &ResHistReDimDataFA[0], cFrontAxis);

    ucIx = 0x00;

    i = GETStManSelectionEE( self);
    j = CheckTyreChangedOnRearAxleDM();

    if((i == OP_IDR_SLCTN_Manuelle_Auswahl) && (j != TRUE))
    {
      ucIx = 0x01;

      for (i=0; i<cAnzRad; i++)
      {
        ucIx &= CompareSavedRidDataRID(i);
      }
    }

    if(ucIx == 0x00)
    {

      ucResCol = CheckAxisRidDataRID( self, &ResHistReDimDataRA[0], cRearAxis);

      if(ucResCol != cAnzRad)
      {
        ConvertReDimToErfsCoding(&ResHistReDimDataRA[0]);

        if(CompareReDimErfsDM( self, &ResHistReDimDataRA[0]) == FALSE)
        {

          DegradeToManSelectionDM( self, TRUE);
          PUTSelectedAutoTyreIndexEE( self, OP_SLCTN_TYR_AVLB_AndererReifen);
        }
      }
      else
      {

        if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
        {

          DegradeToManSelectionDM( self, FALSE);
          PUTSelectedAutoTyreIndexEE( self, OP_SLCTN_TYR_AVLB_AndererReifen);
        }
      }
    }
  }
}

uint8 SaveOemDataRID (void)
{
  uint32 ulHistID;
  uint8 i,j,ucIx;

  if(bGetCRdciRidEnableCD() == TRUE)
  {
    for (i=0; i < cAnzRad; i++)
    {
      if((ucRidOem1Oem2Flag & (uint8)((cOEM1Flag|cOEM2Flag) << i)) != (uint8)((cOEM1Flag|cOEM2Flag) << i))
      {
        ucIx = cSumWE;
        ulHistID = ulGetIDOfColWAL(i);

        for (j=0; j<cSumWE; j++)
        {
          if(ulHistID == TyreIdBufRID[j])
          {
            ucIx = j;
          }
        }

        if(ucIx < cSumWE)
        {
          for(j=0;j<(cTyreOEM1Size);j++)
          {
            if(TyreOEMBufRID[ucIx][j] != cBufInitValRID)
            {
              HistReOEMBufRID[i][j] = TyreOEMBufRID[ucIx][j];
              ucRidOem1Oem2Flag |= (uint8)(cOEM1Flag << i);
            }
          }

          for(j=cTyreOEM1Size;j<cTyreOEMSize;j++)
          {
            if(TyreOEMBufRID[ucIx][j] != cBufInitValRID)
            {
              HistReOEMBufRID[i][j] = TyreOEMBufRID[ucIx][j];
              ucRidOem1Oem2Flag |= (uint8)(cOEM2Flag << i);
            }
          }
        }
      }
    }
  }
  return (ucRidOem1Oem2Flag);
}

void DeleteRidDataOfHisColRID( Rte_Instance self, uint8 HisIx)
{
  uint8 i,j;

  for (j=0;j<cAnzRad;j++)
  {
    if((HisIx & (uint8)(0x01<<j)) != 0x00)
    {

      for(i=0;i<cTyreDimSize;i++)
      {
        HistReDimBufRID[j][i] = cBufInitValRID;

        PUTTyreDimDataEE( self, j, i, cBufInitValRID);
      }
      for(i=0;i<cTyreDOTSize;i++)
      {
        HistReDOTBufRID[j][i] = cBufInitValRID;

        PUTTyreDOTDataEE( self, j, i, cBufInitValRID);
      }
      for(i=0;i<(cTyreOEMSize);i++)
      {
        HistReOEMBufRID[j][i] = cBufInitValRID;
      }

      ucRidManAutoFlag &= (uint8)(0xFF^(uint8)((cAutoFlagMask|cManFlagMask) << j));

      ucRidOem1Oem2Flag &= (uint8)(0xFF^(uint8)((cOEM1Flag|cOEM2Flag) << j));
    }
  }
}

boolean GetReliableRSCInfoRID( Rte_Instance self, uint8 ucRadPos, boolean* bRSCInfoVal)
{
  uint8 HisCol;
  boolean bRet;

  if(ucRadPos < cRadPosUndef)
  {
    HisCol = ucGetColOfWP(ucRadPos);

    bRet = FALSE;
    *bRSCInfoVal = FALSE;

    if((ucRidManAutoFlag & (uint8)((cAutoFlagMask|cManFlagMask) << HisCol)) == (cAutoFlagMask << HisCol))
    {
      bRet = TRUE;

      if((GETTyreDimDataEE( self, HisCol, 5) & 0xC0) == 0x80)
      {
        *bRSCInfoVal = TRUE;
      }
    }
  }
  else
  {

    bRet = TRUE;
    *bRSCInfoVal = TRUE;

    if((ucRidManAutoFlag & cAllAutoFlags) != 0x00)
    {
      for (HisCol = 0; HisCol < cAnzRad;HisCol++)
      {

        if((ucRidManAutoFlag & (uint8)((cAutoFlagMask|cManFlagMask) << HisCol)) == (cAutoFlagMask << HisCol))
        {

          if((GETTyreDimDataEE( self, HisCol, 5) & 0xC0) != 0x80)
          {

            *bRSCInfoVal = FALSE;
          }
        }
      }

      if((*bRSCInfoVal == TRUE) && ((ucRidManAutoFlag & cAllAutoFlags) != 0x0F))
      {
        bRet = FALSE;
        *bRSCInfoVal = FALSE;
      }
    }
    else
    {

      bRet = FALSE;
      *bRSCInfoVal = FALSE;
    }
  }
  return(bRet);
}

boolean GetFAxisTyreDataRID(uint8* pRidData)
{
  boolean bRet = FALSE;
  uint8 i;

  for (i = 0; i < cTyreDimSize; i++)
  {
    if(ResHistReDimDataFA[i] != cBufInitValRID)
    {
      pRidData[i] = ResHistReDimDataFA[i];
      bRet = TRUE;
    }
  }

  if(bRet == TRUE)
  {
    ConvertReDimToErfsCoding(pRidData);
  }
  return(bRet);
}

boolean GetRAxisTyreDataRID( Rte_Instance self, uint8* pRidData)
{
  boolean bRet = FALSE;
  boolean bDim = TRUE;
  uint8 ucPosRL = cAnzRad;
  uint8 ucPosRR = cAnzRad;
  uint8 ucResPos = cAnzRad;
  uint8 ucMask;

  uint8 i,HisColRL,HisColRR;

  uint8 RearAxErfsData[2][cTyreDimSize] = {{0x00,0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00,0x00,0x00}};

  HisColRL = ucGetColOfWP(cRadPosHL);
  HisColRR = ucGetColOfWP(cRadPosHR);

  if(HisColRL < cAnzRad)
  {
    if(GETTyreDimDataEE( self, HisColRL, 0) != 0xFF)
    {
      ucPosRL = 0;
      ucResPos = ucPosRL;
    }
  }

  if(HisColRR < cAnzRad)
  {
    if(GETTyreDimDataEE( self, HisColRR, 0) != 0xFF)
    {
      ucPosRR = 1;
      if((GetRidManAutoFLagRID() & (cAutoFlagMask << cRadPosHR)) == (cAutoFlagMask << cRadPosHR))
      {
      ucResPos = ucPosRR;
      }
    }
  }

  if(GETSelectedAutoTyreIndexEE( self) != OP_SLCTN_TYR_AVLB_AndererReifen)
  {
    if(ucPosRL == 0)
    {
      for (i = 0; i < cTyreDimSize; i++)
      {
        RearAxErfsData[ucPosRL][i] = GETTyreDimDataEE( self, HisColRL, i);
      }
      ConvertReDimToErfsCoding(&RearAxErfsData[ucPosRL][0]);
    }

    if(ucPosRR == 1)
    {
      for (i = 0; i < cTyreDimSize; i++)
      {
        RearAxErfsData[ucPosRR][i] = GETTyreDimDataEE( self, HisColRR, i);
      }
      ConvertReDimToErfsCoding(&RearAxErfsData[ucPosRR][0]);
    }

    if(ucResPos < cAnzRad)
    {
      if((ucPosRL == 0) && (ucPosRR == 1))
      {

        for (i = 0; i < 4; i++)
        {
          if((i == 0) || (i == 1))
          {
            ucMask = 0xF8;
          }
          else if(i == 2)
          {
            ucMask = 0xF0;
          }
          else
          {
            ucMask = 0x03;
          }

          if((uint8)(RearAxErfsData[ucPosRL][i] & ucMask) != (uint8)(RearAxErfsData[ucPosRR][i] & ucMask))
          {
            bDim = FALSE;
          }
        }

        if(bDim == TRUE)
        {
          pRidData[0] = (uint8)(RearAxErfsData[ucResPos][0] & 0xF8);
          pRidData[1] = (uint8)(RearAxErfsData[ucResPos][1] & 0xF8);
          pRidData[2] = (uint8)(RearAxErfsData[ucResPos][2] & 0xF0);
          pRidData[3] = (uint8)(RearAxErfsData[ucResPos][3] & 0x03);

          if((RearAxErfsData[ucPosRL][0] & 0x06) == (RearAxErfsData[ucPosRR][0] & 0x06))
          {
            pRidData[0] |= (RearAxErfsData[ucPosRL][0] & 0x06);
          }
          else
          {

            pRidData[0] |= 0x06;
          }

          if((RearAxErfsData[ucPosRL][1] & 0x06) == (RearAxErfsData[ucPosRR][1] & 0x06))
          {
            pRidData[1] |= (RearAxErfsData[ucPosRL][1] & 0x06);
          }
          else
          {

            pRidData[1] |= 0x06;
          }

          if((RearAxErfsData[ucPosRL][2] & 0x0F) <= (RearAxErfsData[ucPosRR][2] & 0x0F))
          {
            pRidData[2] |= (RearAxErfsData[ucPosRL][2] & 0x0F);
          }
          else
          {
            pRidData[2] |= (RearAxErfsData[ucPosRR][2] & 0x0F);
          }

          if((RearAxErfsData[ucPosRL][3] & 0xFC) <= (RearAxErfsData[ucPosRR][3] & 0xFC))
          {
            pRidData[3] |= (uint8)(RearAxErfsData[ucPosRL][3] & 0xFC);
          }
          else
          {
            pRidData[3] |= (uint8)(RearAxErfsData[ucPosRR][3] & 0xFC);
          }
        }
        else
        {
          pRidData[0] = (RearAxErfsData[ucResPos][0]);
          pRidData[1] = (RearAxErfsData[ucResPos][1]);
          pRidData[2] = (RearAxErfsData[ucResPos][2]);
          pRidData[3] = (RearAxErfsData[ucResPos][3]);
        }
      }
      else
      {
        pRidData[0] = (RearAxErfsData[ucResPos][0]);
        pRidData[1] = (RearAxErfsData[ucResPos][1]);
        pRidData[2] = (RearAxErfsData[ucResPos][2]);
        pRidData[3] = (RearAxErfsData[ucResPos][3]);
      }
      bRet = TRUE;
    }
  }
  return(bRet);
}

void CheckDefaultSerNumAndReplaceRID(uint8 HisIx)
{
  uint8 i, ucOffset, ucPrev, ucCur;
  boolean bDefault = TRUE;
  uint32 ulReId;

  for (i=0;i<cTyreOEMSize;i++)
  {
    ucOffset = (uint8)(2-(i/4));
    ucOffset += i;

    ucPrev = GetTyreOEMDataRID(HisIx,(ucOffset - 1));
    ucCur = GetTyreOEMDataRID(HisIx,(ucOffset));

    if(GetOemIdDS(ucPrev, ucCur, i) != 0x2A)
    {
      bDefault = FALSE;
    }
  }

  if(bDefault == TRUE)
  {

    ulReId = ulGetIDOfColWAL(HisIx);
    ulReId *= 16;

    HistReOEMBufRID[HisIx][6] = (uint8)((ulReId >> 24) & 0xFF);
    HistReOEMBufRID[HisIx][7] = (uint8)((ulReId >> 16) & 0xFF);
    HistReOEMBufRID[HisIx][8] = (uint8)((ulReId >> 8) & 0xFF);

    HistReOEMBufRID[HisIx][9] &= 0x0F;
    HistReOEMBufRID[HisIx][9] |= (uint8)(ulReId & 0xF0);

    HistReOEMBufRID[HisIx][3] = HistReDOTBufRID[HisIx][2];
    HistReOEMBufRID[HisIx][4] = HistReDOTBufRID[HisIx][6];
    HistReOEMBufRID[HisIx][5] = HistReDOTBufRID[HisIx][7];
  }
}

boolean CheckRearAxisRidDataAvailRID(void)
{
  boolean bRet = FALSE;
  uint8 Tmp1,Tmp2;
  uint32 ulReId1,ulReId2;

  if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
  {
    Tmp1 = ucGetColOfWP(cRadPosHL);
    Tmp2 = ucGetColOfWP(cRadPosHR);

    ulReId1 = ulGetIDOfColWAL(Tmp1);
    ulReId2 = ulGetIDOfColWAL(Tmp2);

    Tmp1 = 0x00;

    for (Tmp2=0;Tmp2<cSumWE;Tmp2++)
    {
      if(ulReId1 == TyreIdBufRID[Tmp2])
      {
        Tmp1++;
      }
      if(ulReId2 == TyreIdBufRID[Tmp2])
      {
        Tmp1++;
      }
    }

    if(Tmp1 == 2)
    {
      bRet = TRUE;
    }
  }
  return(bRet);
}

static void SaveHistReRidDataRID( Rte_Instance self, const uint8 HisIx, const uint8 ZOMIx)
{
  uint8 i;
  boolean bTemp = FALSE;

  for(i=0;i<cTyreDimSize;i++)
  {
    if(TyreDimBufRID[ZOMIx][i] != cBufInitValRID)
    {
      HistReDimBufRID[HisIx][i] = TyreDimBufRID[ZOMIx][i];

      if(HistReDimBufRID[HisIx][i] != GETTyreDimDataEE( self, HisIx, i))
      {
        SavedDimDataChangedFlagRID |= (uint8)(cDimDataChanged << HisIx);

        PUTTyreDimDataEE( self, HisIx, i, TyreDimBufRID[ZOMIx][i]);
      }
    }
    else
    {
       HistReDimBufRID[HisIx][i] = GETTyreDimDataEE( self, HisIx, i);

       SavedDimDataChangedFlagRID |= (uint8)(cDimDataHisUse << HisIx);

    }

  }
  for(i=0;i<cTyreDOTSize;i++)
  {
    if(TyreDOTBufRID[ZOMIx][i] != cBufInitValRID)
    {
      HistReDOTBufRID[HisIx][i] = TyreDOTBufRID[ZOMIx][i];
      PUTTyreDOTDataEE( self, HisIx, i, TyreDOTBufRID[ZOMIx][i]);
    }
    else
    {

      if((SavedDimDataChangedFlagRID & (uint8)(cDimDataChanged << HisIx)) == (uint8)(cDimDataChanged << HisIx))
      {

        PUTTyreDOTDataEE( self, HisIx, i, cBufInitValRID);
      }
      HistReDOTBufRID[HisIx][i] = GETTyreDOTDataEE( self, HisIx, i);
    }

  }

  for(i=0;i<cTyreDimSize;i++)
  {

    if(HistReDimBufRID[HisIx][i] != cBufInitValRID)
    {

      bTemp = TRUE;
    }
  }

  if(bTemp == TRUE)
  {
    bTemp = FALSE;

    for(i=0;i<cTyreDOTSize;i++)
    {

      if(HistReDOTBufRID[HisIx][i] != cBufInitValRID)
      {

        bTemp = TRUE;
      }
    }

    if(bTemp == TRUE)
    {
      ucRidManAutoFlag  |= (uint8)(cAutoFlagMask << HisIx);
    }
    else
    {
      ucRidManAutoFlag  |= (uint8)(cManFlagMask << HisIx);
    }
  }
}

static void RestoreSavedReRidDataRID( Rte_Instance self, const uint8 HisIx)
{
  uint8 i;
  boolean bTemp = FALSE;

  for(i=0;i<cTyreDimSize;i++)
  {
    HistReDimBufRID[HisIx][i] = GETTyreDimDataEE( self, HisIx, i);

    SavedDimDataChangedFlagRID |= (uint8)(cDimDataHisUse << HisIx);

  }
  for(i=0;i<cTyreDOTSize;i++)
  {
    HistReDOTBufRID[HisIx][i] = GETTyreDOTDataEE( self, HisIx, i);
  }

  for(i=0;i<cTyreDimSize;i++)
  {

    if(HistReDimBufRID[HisIx][i] != cBufInitValRID)
    {

      bTemp = TRUE;
    }
  }

  if(bTemp == TRUE)
  {
    bTemp = FALSE;

    for(i=0;i<cTyreDOTSize;i++)
    {

      if(HistReDOTBufRID[HisIx][i] != cBufInitValRID)
      {

        bTemp = TRUE;
      }
    }

    if(bTemp == TRUE)
    {
      ucRidManAutoFlag  |= (uint8)(cAutoFlagMask << HisIx);
    }
    else
    {
      ucRidManAutoFlag  |= (uint8)(cManFlagMask << HisIx);
    }
  }
}

static uint8 CheckRidDataRID( Rte_Instance self, const uint8 Col1, const uint8 Col2, const uint8 Axis)
{
  uint8 ResCol, CountVal, NibbleOffset;
  uint8 Pos1, Pos2;

  ResCol = cAnzRad;

  if(((SavedDimDataChangedFlagRID & (uint8)(cDimDataChanged << Col1)) == (uint8)(cDimDataChanged << Col1)) &&
      ((SavedDimDataChangedFlagRID & (uint8)(cDimDataHisUse << Col2)) == (uint8)(cDimDataHisUse << Col2)))
  {
    DeleteRidDataOfHisColRID( self, (uint8)(0x01 << Col2));

    ResCol = Col1;
  }
  else
  {

    if(((SavedDimDataChangedFlagRID & (uint8)(cDimDataChanged << Col2)) == (uint8)(cDimDataChanged << Col2)) &&
        ((SavedDimDataChangedFlagRID & (uint8)(cDimDataHisUse << Col1)) == (uint8)(cDimDataHisUse << Col1)))
    {
      DeleteRidDataOfHisColRID( self, (uint8)(0x01 << Col1));

      ResCol = Col2;
    }
  }

  if(Axis == cRearAxis)
  {
    NibbleOffset = 0;
  }
  else
  {
    NibbleOffset = 4;
  }

  if(((SavedDimDataChangedFlagRID & (uint8)(cDimDataHisUse << Col1)) != 0x00) && ((SavedDimDataChangedFlagRID & (uint8)(cDimDataHisUse << Col2)) != 0x00))
  {
    CountVal = ((GETUseSavedHistRidDataCtEE( self) >> NibbleOffset) & 0x0F);

    if(CountVal < 10)
    {
      if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
      {
        PUTUseSavedHistRidDataCtEE( self, GETUseSavedHistRidDataCtEE( self) + (0x01 << NibbleOffset));
      }
    }
    else
    {
      DeleteRidDataOfHisColRID( self, ((uint8)(0x01<<Col1) | (uint8)(0x01<<Col2)));

      Pos1 = ucGetWPOfColWAL(Col1);
      Pos2 = ucGetWPOfColWAL(Col2);

      if((Pos1 < cMaxLR) && (Pos2 < cMaxLR))
      {
        ResetQRTyreMountedFlags( self, ((uint8) (0x10 << Pos1) | (uint8) (0x10 << Pos2)));
      }
      ResCol = cAnzRad;
    }
  }
  else
  {
    CountVal = GETUseSavedHistRidDataCtEE( self) & (uint8)(~(uint8)(0x0F << NibbleOffset));
    PUTUseSavedHistRidDataCtEE( self, CountVal);
  }

  return(ResCol);
}

static boolean CompareSavedRidDataRID (const uint8 Col)
{
  boolean bComp = TRUE;

  if((SavedDimDataChangedFlagRID & (uint8)(cDimDataChanged << Col)) == (uint8)(cDimDataChanged << Col))
	{
		bComp = FALSE;
  }
  return(bComp);
}

static uint8 CheckAxisRidDataRID( Rte_Instance self, uint8* pResData, const uint8 Axis)
{
  uint8 Col1, Col2, ResCol;

  if(Axis == cRearAxis)
  {
    Col1 = ucGetColOfWP(cRadPosHL);
    Col2 = ucGetColOfWP(cRadPosHR);
  }
  else
  {
    Col1 = ucGetColOfWP(cRadPosVL);
    Col2 = ucGetColOfWP(cRadPosVR);
  }

  (void)CheckRidDataRID( self, Col1, Col2, Axis);

  ResCol = CompareHistReDimBufRID(Col1, Col2, pResData);

  return(ResCol);
}

static uint8 CompareHistReDimBufRID(uint8 Ix1, uint8 Ix2, uint8* pResData)
{
  uint8 i,ValueIx1,ValueIx2,Seas = 0;
  uint8 ResCol = Ix1;
  uint8 Mask;

  if(HistReDimBufRID[Ix1][0] == cBufInitValRID)
  {
    Ix1 = cAnzRad;
    ResCol = Ix2;
  }

  if(HistReDimBufRID[Ix2][0] == cBufInitValRID)
  {
    Ix2 = cAnzRad;
    ResCol = Ix1;
  }

  if((Ix1 != cAnzRad) && (Ix2 != cAnzRad))
  {

    for(i = 0; i < cTyreDimSize; i++)
    {
      switch (i)
      {
        case (uint8)0:
        case (uint8)1:
        case (uint8)2:
        {

          if(HistReDimBufRID[Ix1][i] != HistReDimBufRID[Ix2][i])
          {
            ResCol = cAnzRad;
          }
          else
          {

            pResData[i] = HistReDimBufRID[Ix1][i];
          }
          break;
        }
        case (uint8)3:
        {
          Mask = 0xF0;

          if((HistReDimBufRID[Ix1][i] & Mask) != (HistReDimBufRID[Ix2][i] & Mask))
          {
            ResCol = cAnzRad;
          }
          else
          {

            pResData[i] = (HistReDimBufRID[Ix1][i] & Mask);
          }
          break;
        }
        case (uint8)5:
        {
          Mask = 0x0C;

          if(HistReDimBufRID[Ix1][i] != HistReDimBufRID[Ix2][i])
          {

            if((HistReDimBufRID[Ix1][i] & Mask) != (HistReDimBufRID[Ix2][i] & Mask))
            {
              ResCol = cAnzRad;
            }
            else
            {

              pResData[i] = (HistReDimBufRID[Ix1][i] & Mask);
            }
          }
          else
          {

              pResData[i] = HistReDimBufRID[Ix1][i];
          }

          Seas = ((HistReDimBufRID[Ix1][i] & Mask) >> 2);
          break;
        }
        default:
        {
          break;
        }
      }
    }

    if(ResCol != cAnzRad)
    {

      i = 3;

      ValueIx1 = (uint8)((HistReDimBufRID[Ix1][i] & 0x0F) << 3) | (uint8)((HistReDimBufRID[Ix1][i+1] & 0xE0) >> 5);
      ValueIx2 = (uint8)((HistReDimBufRID[Ix2][i] & 0x0F) << 3) | (uint8)((HistReDimBufRID[Ix2][i+1] & 0xE0) >> 5);

      if(ValueIx1 <= ValueIx2)
      {
        pResData[i] |= (ValueIx1 >> 3);
        pResData[i+1] = (ValueIx1 << 5);
      }
      else
      {
        pResData[i] |= (ValueIx2 >> 3);
        pResData[i+1] = (ValueIx2 << 5);
      }

      i = 4;

      ValueIx1 = (HistReDimBufRID[Ix1][i] & 0x1F);
      ValueIx2 = (HistReDimBufRID[Ix2][i] & 0x1F);

      if(Seas == 0x01)
      {

        if(ValueIx1 <= ValueIx2)
        {
          pResData[i] |= ValueIx1;
        }
        else
        {
          pResData[i] |= ValueIx2;
        }
      }
      else
      {

        if(ValueIx1 >= ValueIx2)
        {
          pResData[i] |= ValueIx1;
        }
        else
        {
          pResData[i] |= ValueIx2;
        }
      }
    }
    else
    {
      if((ucRidManAutoFlag & ((uint8)(cAutoFlagMask << Ix1) | (uint8)(cAutoFlagMask << Ix2))) == (uint8)(cAutoFlagMask << Ix1))
      {
        ResCol = Ix1;
      }
      else
      {
        if((ucRidManAutoFlag & ((uint8)(cAutoFlagMask << Ix1) | (uint8)(cAutoFlagMask << Ix2))) == (uint8)(cAutoFlagMask << Ix2))
        {
          ResCol = Ix2;
        }
      }

      if(ResCol != cAnzRad)
      {

        for (i=0;i<cTyreDimSize;i++)
        {
          pResData[i] = HistReDimBufRID[ResCol][i];
        }
      }
      else
      {

        for (i=0;i<cTyreDimSize;i++)
        {
          pResData[i] = 0xFF;
        }
      }
    }
  }
  else
  {

    if(ResCol != cAnzRad)
    {

      for (i=0;i<cTyreDimSize;i++)
      {
        pResData[i] = HistReDimBufRID[ResCol][i];
      }
    }
  }
  return(ResCol);
}

static void ConvertReDimToErfsCoding (uint8* pRidData)
{
	uint16 ushTemp;
	uint8 Breite,Karkasse,Werk,Querschnitt,Reifentyp,Durchmesser,GeschwIx,LoadIx,Saison;

	ushTemp = (((pRidData[0] >> 4) - 6) * 100) + (((pRidData[0] & 0x0F) - 6) * 10) + ((pRidData[1] >> 4) - 6);

	Breite = (uint8)((ushTemp - 95)/10);

	Karkasse = ((pRidData[5] & 0x02) >> 1);

	Werk = 0x00;

	ushTemp = (((pRidData[1] & 0x0F) - 6) * 10) + ((pRidData[2] >> 4) - 6);

	Querschnitt = (uint8)((ushTemp - 10)/5);

	ushTemp = (uint16)((pRidData[5] & 0xC0) >> 6);
	if(ushTemp == 0x00)
	{

		Reifentyp = 0x01;
	}
	else
	{

		Reifentyp = 0x00;
	}

	ushTemp = (((pRidData[2] & 0x0F) - 6) * 10) + ((pRidData[3] >> 4) - 6);

	Durchmesser = (uint8)(ushTemp - 12);

	ushTemp = (pRidData[4] & 0x1F) + 0x40;

	GeschwIx = ConvertSpeedIndex((uint8)ushTemp);

	ushTemp = ((uint16)(pRidData[3] & 0x0F) << 3) | (uint16)((pRidData[4] & 0xE0) >> 5);

	LoadIx = (uint8)(ushTemp -75);

	ushTemp = (uint16)((pRidData[5] & 0x0C) >> 2);

  	if(ushTemp == 1)
	{

		Saison = CSEASON_SUMMER;
	}
	else
	{

		Saison = CSEASON_WINTER;
	}

	pRidData[0] =  (Breite << 3);
	pRidData[0] |=  (Karkasse << 1);
	pRidData[0] |=  (Werk & 0x01);

	pRidData[1] =  (Querschnitt << 3);
	pRidData[1] |=  (Reifentyp << 1);
	pRidData[1] |= 0x00;

	pRidData[2] = (Durchmesser << 4);
	pRidData[2] |= (GeschwIx & 0x0F);
	pRidData[3] = (LoadIx << 2);
	pRidData[3] |= (Saison & 0x03);
}

static uint8 ConvertSpeedIndex (const uint8 ucIndexValue)
{
	uint8 ConvIndex;

	switch (ucIndexValue)
	{
		case (uint8)'H':
		{
			ConvIndex = IDX_V_TYP_TYR_H;
			break;
		}
		case (uint8)'L':
		{
			ConvIndex = IDX_V_TYP_TYR_L;
			break;
		}
		case (uint8)'M':
		{
			ConvIndex = IDX_V_TYP_TYR_M;
			break;
		}
		case (uint8)'N':
		{
			ConvIndex = IDX_V_TYP_TYR_N;
			break;
		}
		case (uint8)'P':
		{
			ConvIndex = IDX_V_TYP_TYR_P;
			break;
		}
		case (uint8)'Q':
		{
			ConvIndex = IDX_V_TYP_TYR_Q;
			break;
		}
		case (uint8)'R':
		{
			ConvIndex = IDX_V_TYP_TYR_R;
			break;
		}
		case (uint8)'S':
		{
			ConvIndex = IDX_V_TYP_TYR_S;
			break;
		}
		case (uint8)'T':
		{
			ConvIndex = IDX_V_TYP_TYR_T;
			break;
		}
		case (uint8)'U':
		{
			ConvIndex = IDX_V_TYP_TYR_U;
			break;
		}
		case (uint8)'V':
		{
			ConvIndex = IDX_V_TYP_TYR_V;
			break;
		}
		case (uint8)'W':
		{
			ConvIndex = IDX_V_TYP_TYR_W;
			break;
		}
		case (uint8)'Y':
		{
			ConvIndex = IDX_V_TYP_TYR_Y;
			break;
		}
		default:
		{
			ConvIndex = IDX_V_TYP_TYR_ZR;
			break;
		}
	}
	return(ConvIndex);
}

static uint8 SearchRIDBufSlot(const uint32 ReId)
{
	uint8 ZomCol,i;
	uint8 ucIdBufIx = cSumWE;

	for (i=0; i< cSumWE; i++)
	{
		if(TyreIdBufRID[i] == ReId)
		{
			ucIdBufIx = i;
		}
	}

  if(ucIdBufIx == cSumWE)
	{
		for (i=0; i< cSumWE; i++)
		{

			if(TyreIdBufRID[i] == 0x00000000U)
			{
				if(ucIdBufIx == cSumWE)
				{
					ucIdBufIx = i;
					TyreIdBufRID[ucIdBufIx] = ReId;
				}
			}
		}
	}

  if(ucIdBufIx == cSumWE)
	{

	  for (i=0; i< cSumWE; i++)
    {
      ZomCol = ucGetZOMPosOfID((const uint32*)&TyreIdBufRID[i]);

      if(ZomCol == cSumWE)
	    {
		    TyreIdBufRID[i] = 0x00000000U;
	    }
    }

    for (i=0; i< cSumWE; i++)
		{

			if(TyreIdBufRID[i] == 0x00000000U)
			{
				if(ucIdBufIx == cSumWE)
				{
					ucIdBufIx = i;
					TyreIdBufRID[ucIdBufIx] = ReId;
				}
			}
		}
  }
	return (ucIdBufIx);
}

