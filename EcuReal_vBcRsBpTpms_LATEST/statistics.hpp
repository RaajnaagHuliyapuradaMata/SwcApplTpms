#pragma once
/******************************************************************************/
/* File   : statistics.hpp                                                    */
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
#include "tss_stdx.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
  bitfield bWUFDActive              : 1;
  bitfield bActivateWUFDTimerRun    : 1;
  bitfield bProceedWUFDTimerRun     : 1;
  bitfield bDeactivateWUFDTimerRun  : 1;
  bitfield bExceedVThres            : 1;
  bitfield                          :11;
}WUFD;

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
void InitSTATISTICS(void);
uint8 ResetCounterInSlotSTATISTICS(uint8 ucSlot);
uint16 GETusFolgeAusfallCntSTATISTICS(uint8 ucSlot);
void PUTusFolgeAusfallCntSTATISTICS(uint16 ucFolgeAusfallCnt, uint8 ucSlot);
uint16 GETushGutEmpfCntSTATISTICS(uint8 ucSlot);
uint16 GETushMissedCntSTATISTICS(uint8 ucSlot);
uint8 GETucAusbeuteSTATISTICS(uint8 ucSlot);
void ReloadSTATISTICS(void);
void StoreSTATISTICS(void);
uint8 CountValidDatagramSTATISTICS(uint8 ucSlot);
uint8 CountInvalidDatagramSTATISTICS(uint8 ucSlot);
void ExceedVThresSTATISTICS(void);
void UnderrunVThresSTATISTICS(void);
void ActivateWUFDSTATISTICS(void);
void DeactivateWUFDSTATISTICS(void);
void ProceedWUFDSTATISTICS(void);
void CheckWUFDVThresSTATISTICS(void);
void MissedCntStatistics(void);
void PUTucMarkReceivedDatagramSTATISTICS(boolean Value, uint8 Col);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

