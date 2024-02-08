

#ifndef CDDECODER_X_H
#define CDDECODER_X_H

#include "iTPMS_Interface.hpp"

#define cTelTypeAK35def         0U
#define cTelTypeStandstill      0x90U
#define cTelTypeHufStatusLearn  0xA3U
#define cTelTypeHufStatus       0x83U
#define cTelTypeRotatS          0xE7U

#define cTelTypeAK35defLMA      0x20U

#define cTelTypeSchraderFP      0x80U
#define cTelTypeG4Std           0xA5U
#define cTelTypeHufLfResponse   0x03U

#define cMaxAK35DataBytes 14U

#define cWsTelBufferSize 12U

typedef struct{
   unsigned char ucTType[2];
}PreBufHeader;

// AK35
typedef struct{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned char ucID[4];
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucCRC8;
}PreBufAK35def;

typedef struct{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned char ucID[4];
   unsigned char ucPressure;
   unsigned char ucTemperature;
   unsigned char ucByte1Status;
   unsigned char ucByte2Status;
   unsigned char ucCRC8;
}PreBufHufStatus;

typedef struct{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned char ucID[4];
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucTelSentnEnergy;
   unsigned char ucCRC8;
}PreBufG4Std;
//SSC
typedef struct{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned char ucID[4];
   unsigned char ucSnRH;
   unsigned char ucRL;
   unsigned char ucCRC8;
}PreBufRotatS;

typedef struct{
  unsigned char ucHeader[sizeof(PreBufHeader)];
  unsigned char ucCmdID;
  unsigned char ucID[4];
  unsigned char ucPressure;
  unsigned char ucTemperature;
  unsigned char ucReserved;
  unsigned char ucByte1Status;
  unsigned char ucByte2Status;
  unsigned char ucCRC8;
}PreBufHufLfResponse;

typedef struct{
   unsigned char ucHeader[sizeof(PreBufHeader)];
   unsigned char ucCmdID;
   unsigned char ucID[4];
   unsigned char ucP;
   unsigned char ucT;
   unsigned char ucBat;
   unsigned char ucAcc;
   unsigned char ucModeNCode;
   unsigned char ucCRC8;
}PreBufContiFP;

typedef struct{
  unsigned char ucHeader[sizeof(PreBufHeader)];
  unsigned char ucCmdID;
  unsigned char ucID[4];
  unsigned char ucReserved1;
  unsigned char ucReserved2;
  unsigned char ucReserved3;
  unsigned char ucReserved4;
  unsigned char ucReserved5;
  unsigned char ucReserved6;
  unsigned char ucReserved7;
  unsigned char ucReserved8;
  unsigned char ucCRC8;
}PreBufSchraderFp;
typedef struct                                                  // common telegram structure
{
  unsigned char aucHeader[sizeof(PreBufHeader)];
  unsigned char aucTelDat[cMaxAK35DataBytes];
#ifdef IBTCM_SW_ANPASSUNGEN

#else
  unsigned char aucRSMesVal[6];
#endif
  unsigned char ucAvg;
  unsigned long ulTimeStamp;
}PreBufStructure;

//____________________________________all together: G3only,G36,AK35,AK4,AK35plus_______________________________
typedef union prebuffer
{
  PreBufHeader Header;
  PreBufStructure Struc;
  PreBufAK35def AK35def;
  PreBufHufStatus HufStatus;
  PreBufG4Std G4Std;
  PreBufContiFP ContiFP;
  PreBufRotatS RotatS;
  PreBufHufLfResponse LfResponse;
  PreBufSchraderFp SchraderType;
#ifdef IBTCM_SW_ANPASSUNGEN

#else
  unsigned char byte[sizeof(PreBufStructure)];   // longest struct + 2
#endif
}tPreBuf;

typedef struct{
  tsWS_RxDataIn RxDataIn;
  unsigned short ushVehSpeed;
}tRxRotatSBuf;

extern void (*fpDecoder) (unsigned short usParF);
extern unsigned short ushLaRiTi;

// Y400 with BMW APC demo system WS's and new APC WS's
#define cSeriesTelsOfInterest {cTelTypeRotatS, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeHufStatusLearn, cTelTypeHufStatus, cTelTypeHufLfResponse, cTelTypeSchraderFP, cTelTypeStandstill}

extern unsigned char ucGetLen4Cmd(unsigned char ucCmd);

extern unsigned char ucTelOfInterest(unsigned char ucCurTT);

#endif
