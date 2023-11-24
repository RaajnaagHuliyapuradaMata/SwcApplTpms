#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "tss_stdx.h"

#define cRESET_CDD     0x00
#define cPRESTART_CDD  0x01
#define cFSYNC_CDD     0x02
#define cSYNC_CDD      0x03
#define cREC_CDD       0x04
#define cPreSync (uint8) 0x05
#define cStart   (uint8) 0
#define cMeasure (uint8) 1
#define cConfirmManchestere (uint8) 2
#define cConfirmBiphase (uint8) 3
#define cNO_ERROR_CDD            0x00
#define cSHORT_SYNCBIT_CDD       0x01
#define cLONG_SYNCBIT_CDD        0x02
#define cCORR_OVERFLOW_CDD       0x04
#define cTO_SYREC_CDD            0x08
#define cBAD_CRC_CDD             0x20
#define cMIN_SYNCBIT_CDD         0x40
#define cMAX_SYNCBIT_CDD         0x80
#define cSHORTEL                 0x0C
#define cBITERRORINSYNC          0x03
#define cBAD_AK35_SYNC1          0x05
#define NEWDECOTTING

#ifndef cAUTOCOD
 #define cAK35ONLY
#endif

#define cBAUD_RATE_19200

#ifdef cBAUD_RATE_9600
#define cDECODING_TIMEOUT_CDD  0x0190
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
#else
#define cFASTLOAD_TIME_CDD 200
#endif
#endif

#ifdef cBAUD_RATE_19200
#define cDECODING_TIMEOUT_CDD  0x0190
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
#else
#define cFASTLOAD_TIME_CDD 100
#endif
#endif

#ifdef cBAUD_RATE_AUTOBOT
#define cDECODING_TIMEOUT_CDD  0x0190
#ifdef cATA5745
#define cFASTLOAD_TIME_CDD 12
#else
#define cFASTLOAD_TIME_CDD 190
#endif
#endif

#ifdef cG2TEL
#define cHF_TEL_SIZE              (uint8) 10
#else
#define cHF_TEL_SIZE              (uint8) 11
#endif

#define cHF_TEL_SIZE_G2           (uint8) 10
#define cHF_TEL_SIZE_SHORT        (uint8) 5
#define cNUM_RSSI_VALS_SHORT      (uint8) 2
#define cTelTypeContiFP           (uint8) 0x80
#define cTelTypeSELPAL            (uint8) 0x03
#define cTelTypeSELPAL1           (uint8) 0x23
#define cTelTypeAK35def           (uint8) 0x00
#define cTelTypeAK35defLMA        (uint8) 0x20
#define cTelTypeG4Standard        (uint8) 0xA5
#define cTelTypeBeruLong          (uint8) 0x88
#define cTelTypeBeruMed           (uint8) 0xA0
#define cTelTypeTyreDOT           (uint8) 0x40
#define cTelTypeTyreDIM           (uint8) 0x52
#define cTelTypeTyreDataOE1       (uint8) 0xCD
#define cTelTypeTyreDataOE2       (uint8) 0xCE
#define cTelTypeTyreStatus        (uint8) 0xCF
#define cTelTypeAlive             (uint8) 0xFF
#define cSupplCodeUnused          (uint8) 0x0
#define cSupplCodeAutonet         (uint8) 0x1
#define cSupplCodeHuf             (uint8) 0x2
#define cSupplCodeConti           (uint8) 0x3
#define cSupplCodeSchrader        (uint8) 0x5
#define cSupplCodeUnknown         (uint8) 0xf
#define TELTYPE_STANDARD          (uint8) 0
#define TELTYPE_ALLOCATABLE       (uint8) 1
#define TELTYPE_FOREIGN_SUPPLIER  (uint8) 2
#define TELTYPE_RID               (uint8) 4
#define TELTYPE_FBD4_ALIVE        (uint8) 8
#define TELTYPE_INVALID           (uint8) 255
#define DUAL_MOD
#define cMoTypeASK (uint8) 0
#define cMoTypeFSK (uint8) 1
#define c433 (uint8) 0
#define c315 (uint8) 1

#ifdef _M_IX86
#define cByteOffset2HiNibID 7
#else
#define cByteOffset2HiNibID 3
#endif

#define cMaxAK35DataBytes 13

typedef struct{
   uint8 ucTType;
   uint8 ucAvg;
   uint32 ulID;
}PreBufHeader;

typedef struct{
   PreBufHeader ucHeader;
   uint8 ucPressure;
   uint8 ucTemperature;
   uint8 ucCRC8;
}PreBufAK35def;

typedef struct{
   PreBufHeader ucHeader;
   uint8 ucP;
   uint8 ucT;
   uint8 ucPAL;
   uint16 ushStatusField;
   uint8 ucCRC8;
}PreBufSchraderFP;

typedef struct{
   PreBufHeader ucHeader;
   uint8 ucP;
   uint8 ucT;
   uint8 ucBat;
   uint8 ucAcc;
   uint8 ucModeNCode;
   uint8 ucCRC8;
}PreBufContiFP;

typedef union prebuffer{
  PreBufHeader Header;
  PreBufAK35def AK35def;
  PreBufSchraderFP SchraderFP;
  PreBufContiFP ContiFP;
}tPreBuf;

typedef tPreBuf tRFTelType;

 # ifdef __cplusplus
}
# endif
