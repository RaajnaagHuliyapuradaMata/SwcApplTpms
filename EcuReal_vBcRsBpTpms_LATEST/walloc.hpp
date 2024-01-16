#pragma once
/******************************************************************************/
/* File   : walloc.hpp                                                        */
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
#include "Tpms_Rte_Data_Type.hpp"

#define cInitialState (unsigned char) 0
#define cNoAxis (unsigned char) 0xCF
#define cECUAxis (unsigned char) 0x10
#define cFrontAxis (unsigned char) 0x10
#define cOtherAxis (unsigned char) 0x20
#define cBackAxis (unsigned char) 0x20
#define cNoSpin (unsigned char) 0x3F
#define cRightSpin (unsigned char) 0x40
#define cLeftSpin (unsigned char) 0x80
#define cWP_RR (unsigned char) 0x08
#define cWP_RL (unsigned char) 0x04
#define cWP_FR (unsigned char) 0x02
#define cWP_FL (unsigned char) 0x01
#define cNoWPos (unsigned char) 0xF0

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct ZOMSlot{
  unsigned long ulID;
  unsigned char ucStatus;
  unsigned char ucProbeCt;
  unsigned char ucLeftCt;
  unsigned char ucRightCt;
  unsigned short ushVariation;
  unsigned short ushRssiSum;
  unsigned char ucLastRssi;
  unsigned char ucSkipNewTelTimerInSec;

#ifdef FPA
  unsigned char ucABSRef[4];
  unsigned short ushMVdN[4];
  unsigned short ushPosCompVal[4];
  unsigned short ushMVdN2[4];
  unsigned short ushPosCompVal2[4];
  unsigned char ucRelCmpVal[4];
  unsigned char ucSort[4];
  unsigned char ucAlgoTelEvtCnt;
  unsigned char ucResetABSRefFlag;
  boolean  bPotNewID;
  boolean  bOwnID;
#endif
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
extern unsigned char ucGetERState(void);
extern unsigned char ucSumCtID(unsigned char ucMinCt, unsigned char ucMinRssi);
extern void SetZOMWP(unsigned char ucIx,unsigned char ucWP);
extern WAParameter tWAPar;
extern struct ZOMSlot tZOM[cSumWE];

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

