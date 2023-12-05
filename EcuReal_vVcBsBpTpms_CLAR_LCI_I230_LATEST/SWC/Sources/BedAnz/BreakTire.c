#include "BreakTire.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "USWarn_ifX.h"
#include "DataManagerX.h"
#include "CodingDataX.h"
#include "WnTypePar.h"
#include "EeWarnStatusBlockX.h"
#include "WallocX.h"

static uint8  ucActBreakTireStateBT = cBtWsBreakTireInit;
static uint8  ucOldPrewarnStateBT   = 0;

void InitBT(Rte_Instance self)
{
  SetBreakTireStateBT(self);
  ucOldPrewarnStateBT = (GETucWarningGroupTM( cucWT_GrpPvorw) & (uint8) 0x0F);
}

void SetBreakTireStateBT(Rte_Instance self)
{

  ucActBreakTireStateBT = ucGetWarnOutStateBT(self);
}

uint8 ucGetWarnOutStateBT(Rte_Instance self)
{
  uint8 ucResult   = cBtWsBreakTireInit;
  uint8 ucResultLo = cBtWsBreakTireInit;
  uint8 ucResultHi = cBtWsBreakTireInit;
  uint8 ucHistSlot;
  uint8 ucWheelPos;

  uint8 ucBefuellhinweis;
  uint8 ucDruckwarnung;
  uint8 ucPannenwarnung;

  uint8 ucBitCounter;

  uint8 aucWarnVector[cAnzRad];
  uint8 aucWbitTonnage[cAnzRad];
  uint8 aucWbitAirMass[cAnzRad];

  (void) ucGetWarnBitIdIntIFH(self, aucWarnVector);
  ucPannenwarnung = 0;
  for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
  {
    if( (aucWarnVector[ucHistSlot] & cucWN_Ppanne) != 0)
    {
      ucPannenwarnung |= (uint8) (1 << ucHistSlot);
    }
  }
  ucDruckwarnung = 0;
  for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
  {
    if( (aucWarnVector[ucHistSlot] & (cucWN_Pmin | cucWN_Pwarn | cucWN_PwarnTol)) != 0)
    {
      ucDruckwarnung |= ((uint8) (1 << ucHistSlot) & 0x0fu);
    }
  }
  ucDruckwarnung &= (uint8) ~ucPannenwarnung;

  if( bGetCRdciFastDeflateEnableCD() == TRUE)
  {

    (void) ucGetWarnBitTonnageIdIntIFH(self, aucWbitTonnage);
    (void) ucGetWarnBitAirMassIdIntIFH(self, aucWbitAirMass);

    for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
    {
      if( (((aucWbitTonnage[ucHistSlot] & (cucWN_Pwarn | cucWN_Pmin)) | (aucWbitAirMass[ucHistSlot] & (cucWN_Pwarn | cucWN_Pmin))) & (uint8) ~(aucWbitTonnage[ucHistSlot] & cucWN_Ppanne)) != 0)
      {
        if( (aucWbitTonnage[ucHistSlot] & cucWN_DHW) != 0)
        {
          ucPannenwarnung |= ((uint8) (1 << ucHistSlot) & 0x0fu);
        }
      }
    }

    ucDruckwarnung &= (uint8) ~ucPannenwarnung;
  }else{

  }

  if( bGetCRdciPanneBefPosCD() == TRUE)
  {

    ucPannenwarnung |= ucDruckwarnung;

    ucDruckwarnung   = 0x00;
  }

  ucBefuellhinweis = 0;
  for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
  {
    if( (aucWarnVector[ucHistSlot] & cucWN_Pvorw) != 0)
    {
      ucBefuellhinweis |= (uint8) (1 << ucHistSlot);
    }
  }
  ucBefuellhinweis &= (uint8) ~(ucPannenwarnung | ucDruckwarnung);

  if( ucPannenwarnung != 0)
  {

    ucBitCounter = 0;
    for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
    {
      if( (ucPannenwarnung & (uint8) (0x01 << ucHistSlot)) != 0)
      {

        ucBitCounter++;
      }
    }

    ucResultHi = cBtWsBreakTirePw;

    if( ucBitCounter > 1)
    {
      ucResultHi |= cBtWsBreakTireMulti;
    }

    if( (ucDruckwarnung | ucBefuellhinweis) != 0)
    {
      ucResultHi |= cBtWsBreakTireTsb;
    }

    ucResultLo = (ucPannenwarnung & 0x0fu);
  }else if( ucDruckwarnung != 0)
  {

    ucBitCounter = 0;
    for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
    {
      if( (ucDruckwarnung & (uint8) (0x01 << ucHistSlot)) != 0)
      {

        ucBitCounter++;
      }
    }

    ucResultHi |= cBtWsBreakTireDw;

    if( ucBitCounter > 1)
    {
      ucResultHi |= cBtWsBreakTireMulti;
    }

    if( ucBefuellhinweis != 0)
    {
      ucResultHi |= cBtWsBreakTireTsb;
    }

    ucResultLo = (ucDruckwarnung & 0x0fu);
  }else{
    ucResultHi = cBtWsBreakTireInit;
    ucResultLo = cBtWsBreakTireInit;
  }

  ucResult = (ucResultHi & 0xf0u);
  if( ucResultLo != 0)
  {
    if( bGetBitBetriebszustandBZ( cZUGEORDNET) == TRUE)
    {
      for( ucHistSlot = 0; ucHistSlot < cAnzRad; ucHistSlot++)
      {
        ucWheelPos = ucGetWPOfColWAL( ucHistSlot);

        if( ucWheelPos < cAnzRad)
        {
          if( (ucResultLo & (uint8) (1 << ucHistSlot)) != 0)
          {
            ucResult |= ((uint8) (1 << ucWheelPos) & 0x0fu);
          }
        }
      }
    }else{
      ucResult |= (ucResultLo & 0x0fu);
    }
  }

  return ucResult;
}

uint8 ucGetBreakTireStateBT(void)
{
  return ( ucActBreakTireStateBT);
}

boolean bGetBefuellhinweisBT(void)
{
  boolean bRetVal = FALSE;
  uint8   ucPrewarnActState, ucPreWarnAttrBits;
  uint8   ucBitCounter, ucLoop;

  if( bGetCRdciPrewarnEnableCD() == TRUE)
  {
    ucPrewarnActState = (GETucWarningGroupTM( cucWT_GrpPvorw) & (uint8) 0x0F);
    if( bGetCRdciNumPrewarnDetectCD() == FALSE)
    {

      ucBitCounter = 0;
      for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
      {
        if( (ucPrewarnActState & (uint8) (0x01 << ucLoop)) != 0)
        {

          ucBitCounter++;
        }
      }

      if( ucBitCounter < 2)
      {
        ucPrewarnActState = 0x00;
      }
    }
    if( bGetCRdciFastDeflateEnableCD() == TRUE)
    {
      ucPrewarnActState &= (uint8)(~(GETucWarningGroupTM( cucWT_GrpDHW) & (uint8) 0x0F));
    }
    if( ucPrewarnActState == 0x00)
    {
      ucOldPrewarnStateBT = 0x00;
    }
    ucPreWarnAttrBits = ((GETucWarningGroupTM( cucWT_GrpPvorw) & (uint8) 0xF0) >> 4);
    if( (bGetCRdciPrewarnIgnitionCD() == FALSE) && (ucPrewarnActState != 0))
    {
      bRetVal = TRUE;
    }else if( (bGetCRdciPrewarnIgnitionCD() == TRUE) && (ucOldPrewarnStateBT != 0))
    {
      bRetVal = TRUE;
    }else{

      bRetVal = FALSE;
    }

    if( bRetVal == TRUE)
    {

      if( (bGetBitFahrzeugzustandFZZ( cTAMBIENT_RED) == FALSE) && ((ucPrewarnActState & (uint8) ~(uint8) ucPreWarnAttrBits) == 0))
      {
        bRetVal = FALSE;
      }
    }
  }else{
    bRetVal = FALSE;
  }

  return bRetVal;
}

void PwfChangeParken2WohnenBT(void)
{
  ucOldPrewarnStateBT = (GETucWarningGroupTM( cucWT_GrpPvorw) & (uint8) 0x0F);
}
