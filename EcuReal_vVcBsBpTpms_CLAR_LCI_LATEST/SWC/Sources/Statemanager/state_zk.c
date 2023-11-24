

#include "state_zk.h"

static uint16 ushZustandskennung = 0;
static uint8 ucIdChanged = 0;

void InitZK(void)
{
  ClearBitZustandskennungZK( cZK_ALLE_BITS);
}

void SetBitZustandskennungZK( uint16 ushBitMask)
{
   ushZustandskennung |= ushBitMask;
}

void ClearBitZustandskennungZK( uint16 ushBitMask)
{
   ushZustandskennung &= ~ushBitMask;
}

boolean bGetBitZustandskennungZK( uint16 ushBitMask)
{
   return (boolean) ((ushZustandskennung & ushBitMask) != 0);
}

uint16 ushGetZustandskennungZK( uint16 ushBitMask)
{
   return (ushZustandskennung & ushBitMask);
}

void SetWpChangedBitZK( uint8 ucWP)
{

  switch (ucWP)
  {
    case (uint8) 0:
    {
      ushZustandskennung |= cPOS_CHANGED_VL;
      break;
    }
    case (uint8) 1:
    {
      ushZustandskennung |= cPOS_CHANGED_VR;
      break;
    }
    case (uint8) 2:
    {
      ushZustandskennung |= cPOS_CHANGED_HL;
      break;
    }
    case (uint8) 3:
    {
      ushZustandskennung |= cPOS_CHANGED_HR;
      break;
    }
    default:
    {
      ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL| cPOS_CHANGED_HR);
      break;
    }
  }
}

uint8 ucGetWpChangedBitsZK(void)
{
  uint8 retVal = 0;
  if( (ushZustandskennung & cPOS_CHANGED_VL) != 0)
  {
    retVal |= 0x01;
  }
  if( (ushZustandskennung & cPOS_CHANGED_VR) != 0)
  {
    retVal |= 0x02;
  }
  if( (ushZustandskennung & cPOS_CHANGED_HL) != 0)
  {
    retVal |= 0x04;
  }
  if( (ushZustandskennung & cPOS_CHANGED_HR) != 0)
  {
    retVal |= 0x08;
  }
  return (retVal);
}

void ClearWpChangedBitsZK(void)
{
  ushZustandskennung &= ~(cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL| cPOS_CHANGED_HR);
}

void SetIdChangedBitsZK( uint8 ucChangedBits)
{
  ucIdChanged |= ucChangedBits;
}

uint8 ucGetIdChangedBitsZK(void)
{
  return ucIdChanged;
}

void ClearIdChangedBitsZK(void)
{
  ucIdChanged = 0;
}

