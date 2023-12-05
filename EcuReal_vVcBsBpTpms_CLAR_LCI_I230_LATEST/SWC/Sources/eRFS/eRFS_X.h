#ifndef eRFS_X_h
#define eRFS_X_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

#define TYRE_LIST_MAX_ELEMENTS		((uint8)0x14)
#define TYRE_DATA_BYTES				((uint8)0x08)
#define REQ_PART_LOAD				((uint8)0x00)
#define REQ_FULL_LOAD				((uint8)0x01)
#define REQ_ECO_LOAD				((uint8)0x02)
#define CSEASON_SUMMER			((uint8)0x00)
#define CSEASON_WINTER			((uint8)0x01)
#define CSEASON_NOCHANGE		((uint8)0x02)
#define C2BIT_SIG_INVALID		((uint8)0x03)
#define CTLIST_INDEX_INVALID	((uint8)0x3F)
#define CINIT_DISP_INVALID		((uint8)0xFF)
#define CNO_INIT_DISP			((uint8)0xFE)
#define CINIT_DISP_FINSH		((uint8)0xFD)
#define GetFrontAxleSetPressTyreList(a,b) GetHighNibbleSetPressTyreList((a),(b))
#define GetRearAxleSetPressTyreList(a,b)  GetLowNibbleSetPressTyreList((a),(b))

typedef struct TyreList_struc{
	uint8 TyreData[TYRE_DATA_BYTES];
}TyreList_type;

extern TyreList_type TyreList[TYRE_LIST_MAX_ELEMENTS];
extern TyreList_type DiagTyreList[TYRE_LIST_MAX_ELEMENTS];
extern uint8 ucLoadStateOut;
extern uint8 ucSeasonOut;
extern uint8 ucLengthOfTyreList;
extern uint8 ucSLCTNTRIndex;
extern uint8 ucWITRIndex;
extern uint8 ucSUTRIndex;
extern uint8 ucIDRSLCTN;
extern uint8 ucIDRMSGC;
extern uint8 ucSTMANSLCTN;

extern uint8 GetHighNibbleSetPressTyreList( const uint8 ReqLoadState, const uint8 SelTyreListRow);
extern uint8 GetLowNibbleSetPressTyreList( const uint8 ReqLoadState, const uint8 SelTyreListRow);
extern uint8 GetReifenbreiteRaw( const uint8 TyreListRow);
extern uint8 GetKarkasseRaw( const uint8 TyreListRow);
extern uint8 GetWerksauslieferungRaw( const uint8 TyreListRow);
extern uint8 GetQuerschnittRaw( const uint8 TyreListRow);
extern uint8 GetReifentypRaw( const uint8 TyreListRow);
extern uint8 GetDurchmesserRaw( const uint8 TyreListRow);
extern uint8 GetGeschwIndexRaw( const uint8 TyreListRow);
extern uint8 GetTragfaehigkeitRaw( const uint8 TyreListRow);
extern uint8 GetSaisonRaw( const uint8 TyreListRow);
extern uint8 GetMaxTyreTablePos(void);
extern void SetMaxTyreTablePos( const uint8 ucVal);
extern uint8 GetTyreListMember( uint8 Element, uint8 Member);
extern void SetTyreListMember( const uint8 Element, const uint8 Member, const uint8 Value);
extern void SetDiagTyreListMember( const uint8 Element, const uint8 Member, const uint8 Value);
extern uint8 CopyDiagTyreListToTyreList(Rte_Instance self);
extern boolean CheckTyreListConsistency( uint8 NofE, uint8 MaxIndex);
extern boolean CalcDiagTyreListCrcAndCompare( const uint8* Data);

#ifdef __cplusplus
}
#endif

#endif
