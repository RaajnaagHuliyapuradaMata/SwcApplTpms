#include "eRFS_X.h"

#include "datamanagerX.h"
#include "EeErfsBlockX.h"
#include "Crc16X.h"
#include "CodingDataX.h"

#define C2BAR_25MBAR_RES	((uint8)80)

STATIC uint8 ucMaxTyreTablePos;

TyreList_type TyreList[TYRE_LIST_MAX_ELEMENTS] = {0};
TyreList_type DiagTyreList[TYRE_LIST_MAX_ELEMENTS] = {0};

uint8 ucLoadStateOut = C2BIT_SIG_INVALID;
uint8 ucSeasonOut = C2BIT_SIG_INVALID;
uint8 ucLengthOfTyreList = CTLIST_INDEX_INVALID;
uint8 ucSLCTNTRIndex = CTLIST_INDEX_INVALID;
uint8 ucWITRIndex = CTLIST_INDEX_INVALID;
uint8 ucSUTRIndex = CTLIST_INDEX_INVALID;
uint8 ucIDRSLCTN = C2BIT_SIG_INVALID;
uint8 ucIDRMSGC = C2BIT_SIG_INVALID;
uint8 ucSTMANSLCTN = C2BIT_SIG_INVALID;

 uint8 GetMaxTyreTablePos(void)
 {
	return(ucMaxTyreTablePos);
 }

 void SetMaxTyreTablePos( const uint8 ucVal)
 {
	  ucMaxTyreTablePos = ucVal;
 }

 void SetTyreListMember( const uint8 Element,const uint8 Member,const uint8 Value)
 {
	  if((Element < TYRE_LIST_MAX_ELEMENTS) && (Member < TYRE_DATA_BYTES)){
      TyreList[Element].TyreData[Member] = Value;
      }
 }

 void SetDiagTyreListMember( const uint8 Element, const uint8 Member, const uint8 Value)
 {
	 if((Element < TYRE_LIST_MAX_ELEMENTS) && (Member < TYRE_DATA_BYTES))
   {
     DiagTyreList[Element].TyreData[Member] = Value;
   }
 }

 boolean CalcDiagTyreListCrcAndCompare( const uint8* Data)
 {
   uint16 CalcCrc16, FixCrc16;
   boolean bRet = FALSE;

   FixCrc16 = (uint16)Data[161];
   FixCrc16 |= (uint16)((uint16)Data[160] << 8);

   CalcCrc16 = ushCalcCrc16(Data, (TYRE_LIST_MAX_ELEMENTS*TYRE_DATA_BYTES));

   if(CalcCrc16 == FixCrc16)
   {
     bRet = TRUE;
   }

   return (bRet);
 }

boolean CheckTyreListConsistency(uint8 NofE, uint8 MaxIndex)
{
   uint8 i,j,ucCheckSum;
   boolean bRet = TRUE;

   if((NofE == TYRE_DATA_BYTES) && (MaxIndex < TYRE_LIST_MAX_ELEMENTS)){
      for(i = 0; i <= MaxIndex; i++)
	  {
		  ucCheckSum = 0x00;

      for(j = 0; j < (NofE - 1); j++)
		  {
			  ucCheckSum ^= TyreList[i].TyreData[j];
		  }
      if(ucCheckSum != TyreList[i].TyreData[NofE-1]){
        bRet = FALSE;
      }
	  }
   }
   else{
    bRet = FALSE;
   }
   return(bRet);
}

uint8 GetHighNibbleSetPressTyreList( const uint8 ReqLoadState, const uint8 SelTyreListRow)
{
	uint8 SetPressVal, Index;

	if(ReqLoadState == REQ_PART_LOAD){

		Index = 0x04;
	}
	else{
		if(ReqLoadState == REQ_FULL_LOAD){

			Index = 0x05;
		}
		else{

			Index = 0x06;
		}
	}

	SetPressVal = (uint8)((TyreList[SelTyreListRow].TyreData[Index] & 0xF0) >> 2);

	return(SetPressVal + C2BAR_25MBAR_RES);
}

uint8 GetLowNibbleSetPressTyreList( const uint8 ReqLoadState, const uint8 SelTyreListRow)
{
	uint8 SetPressVal, Index;

	if(ReqLoadState == REQ_PART_LOAD){

		Index = 0x04;
	}
	else{
		if(ReqLoadState == REQ_FULL_LOAD){

			Index = 0x05;
		}
		else{

			Index = 0x06;
		}
	}

	SetPressVal = (uint8)((TyreList[SelTyreListRow].TyreData[Index] & 0x0F) << 2);

	return(SetPressVal + C2BAR_25MBAR_RES);
}

uint8 GetReifenbreiteRaw( const uint8 TyreListRow)
{
	return((uint8)((TyreList[TyreListRow].TyreData[0] & 0xF8)>>3));
}

uint8 GetKarkasseRaw( const uint8 TyreListRow)
{
	return(((TyreList[TyreListRow].TyreData[0] & 0x06)>>1));
}

uint8 GetWerksauslieferungRaw( const uint8 TyreListRow)
{
	return((TyreList[TyreListRow].TyreData[0] & 0x01));
}

uint8 GetQuerschnittRaw( const uint8 TyreListRow)
{
	return((uint8)((TyreList[TyreListRow].TyreData[1] & 0xF8)>>3));
}

uint8 GetReifentypRaw( const uint8 TyreListRow)
{
	return(((TyreList[TyreListRow].TyreData[1] & 0x06)>>1));
}

uint8 GetDurchmesserRaw( const uint8 TyreListRow)
{
	return((uint8)((TyreList[TyreListRow].TyreData[2] & 0xF0)>>4));
}

uint8 GetGeschwIndexRaw( const uint8 TyreListRow)
{
	return( (TyreList[TyreListRow].TyreData[2] & 0x0F));
}

uint8 GetTragfaehigkeitRaw( const uint8 TyreListRow)
{
	return((uint8)((TyreList[TyreListRow].TyreData[3] & 0xFC)>>2));
}

uint8 GetSaisonRaw( const uint8 TyreListRow)
{
	return( (TyreList[TyreListRow].TyreData[3] & 0x03));
}

uint8 GetTyreListMember(uint8 Element, uint8 Member)
{
	return(TyreList[Element].TyreData[Member]);
}

uint8 CopyDiagTyreListToTyreList (Rte_Instance self)
{
	uint8 i,j, TyreListEntrySize;
   uint8 MaxTyreIndex = L_OL_TYP_TYR_SignalUngueltig;
   boolean bConCheck;

	TyreListEntrySize = GetSizeOfTyreListElementDM();

   for(i = 0; i < TYRE_LIST_MAX_ELEMENTS; i++){
		if(DiagTyreList[i].TyreData[0] != 0xFF)
	  {
			MaxTyreIndex = i;
      }
	  for(j = 0; j < TyreListEntrySize; j++){
			SetTyreListMember(i,j,DiagTyreList[i].TyreData[j]);
		}
	}

   bConCheck = CheckTyreListConsistency(TyreListEntrySize, MaxTyreIndex);

   if(bConCheck == TRUE)
	 {
     MaxTyreIndex += 1;
     PUTInvalidTyreListEE(self, FALSE);
	 }
   else
	 {
     MaxTyreIndex = L_OL_TYP_TYR_SignalUngueltig;
   }
   return(MaxTyreIndex);
}

