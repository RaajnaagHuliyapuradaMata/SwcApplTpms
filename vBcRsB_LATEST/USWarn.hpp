#pragma once
/******************************************************************************/
/* File   : USWarn.hpp                                                        */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucPResInMBarc                                     25
#define uc1Barc                                           ((unsigned char) 40)
#define uc100mBarc                                        4
#define ush273Kelvinc                                     273
#define sc0Gradc                                          0
#define sc20Gradc                                         20
#define sc40Gradc                                         40
#define ushGSFc                                           1024
#define ucIsoClearc                                       ((unsigned char) 0x20)
#define ucUSCodec                                         ((unsigned char) 0x04)
#define ucCtryMaskc                                       ((unsigned char) 0x0C)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct Byte{
   unsigned char Lo;
   unsigned char Hi;
};

union tWB16{
   struct Byte uc;
   unsigned short ush;
};

struct SollDat{
   unsigned char ucPSoll;
     signed char scTSoll;
   unsigned short ushMSoll;
};

struct HFTelIntern{
   unsigned char  ucId;
   unsigned char  ucP;
     signed char  scTWE;
   unsigned char  ucLifeTime;
   unsigned char  ucState;
   unsigned short ushVehicleSpeed;
     signed char  scTa;
     signed char  scTref;
   unsigned char  ucKLState;
};

union HFTelAccess{
  struct HFTelIntern tHF;
  unsigned char ucByte[(unsigned char) sizeof(struct HFTelIntern)];
};

struct LocalWarnDat{
  union HFTelAccess tHFD;
  struct SollDat tSD;
  unsigned char ucCurWarnLevel;
  unsigned char PWarm;
};

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
extern unsigned char  ucGetWarnBitWN (unsigned char  ucIdX, unsigned char  ucWarnTypeIx);
extern void           ClearWarnBitWN (unsigned char  ucIdX, unsigned char  ucWarnTypeIx);
extern unsigned char  ucSetWarnBitWN (unsigned char  ucIdX, unsigned char  ucWarnTypeIx);
extern unsigned char  ucPfT          (unsigned short ushM,  unsigned short ushTabs);
extern unsigned short ushMIso        (unsigned char  ucP,     signed char  scT);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

