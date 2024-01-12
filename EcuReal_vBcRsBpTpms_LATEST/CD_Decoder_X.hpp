#pragma once
/******************************************************************************/
/* File   : CD_Decoder_X.hpp                                                  */
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
#include "iTPMS_Interface.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cTelTypeAK35def                                                       0U
#define cTelTypeStandstill                                                 0x90U
#define cTelTypeHufStatusLearn                                             0xA3U
#define cTelTypeHufStatus                                                  0x83U
#define cTelTypeRotatS                                                     0xE7U
#define cTelTypeAK35defLMA                                                 0x20U
#define cTelTypeSchraderFP                                                 0x80U
#define cTelTypeG4Std                                                      0xA5U
#define cTelTypeHufLfResponse                                              0x03U
#define cMaxAK35DataBytes                                                    14U
#define cWsTelBufferSize                                                     12U

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   unsigned char ucTType[2];
}PreBufHeader;

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

typedef struct {
  unsigned char aucHeader[sizeof(PreBufHeader)];
  unsigned char aucTelDat[cMaxAK35DataBytes];
  unsigned char ucAvg;
  unsigned long ulTimeStamp;
}PreBufStructure;

typedef union prebuffer{
  PreBufHeader Header;
  PreBufStructure Struc;
  PreBufAK35def AK35def;
  PreBufHufStatus HufStatus;
  PreBufG4Std G4Std;
  PreBufContiFP ContiFP;
  PreBufRotatS RotatS;
  PreBufHufLfResponse LfResponse;
  PreBufSchraderFp SchraderType;
}tPreBuf;

typedef struct{
  tsWS_RxDataIn RxDataIn;
  unsigned short ushVehSpeed;
}tRxRotatSBuf;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void (*fpDecoder) (unsigned short usParF);
extern unsigned short ushLaRiTi;

#define cSeriesTelsOfInterest {cTelTypeRotatS, cTelTypeAK35def, cTelTypeAK35defLMA, cTelTypeHufStatusLearn, cTelTypeHufStatus, cTelTypeHufLfResponse, cTelTypeSchraderFP, cTelTypeStandstill}
extern unsigned char ucGetLen4Cmd(unsigned char ucCmd);
extern unsigned char ucTelOfInterest(unsigned char ucCurTT);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

