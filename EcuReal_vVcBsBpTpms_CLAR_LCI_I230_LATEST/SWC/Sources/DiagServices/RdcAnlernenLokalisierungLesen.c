/******************************************************************************/
/* File   : RdcAnlernenLokalisierungLesen.c                                   */
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
#include "RdcAnlernenLokalisierungLesenX.h"

#include "WAllocX.h"
#include "FPA_X.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

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
void GetRdcAnlernenLokalisierungLesenDS(uint8* pucData){
   uint8 ucLoop;
   uint32 ulDWord;

   for(ucLoop = 0; ucLoop < (cSumWE - 4); ucLoop++){
      ulDWord = ulGetZOMID(ucLoop);
    pucData[((ucLoop * 15) +  0)] = (uint8) ((ulDWord >> 24) & 0x000000FFu);
    pucData[((ucLoop * 15) +  1)] = (uint8) ((ulDWord >> 16) & 0x000000FFu);
    pucData[((ucLoop * 15) +  2)] = (uint8) ((ulDWord >>  8) & 0x000000FFu);
    pucData[((ucLoop * 15) +  3)] = (uint8) ((ulDWord >>  0) & 0x000000FFu);

    pucData[((ucLoop * 15) +  4)] = ucGetZomToothTelCtCorrLearnBit(ucLoop);
    pucData[((ucLoop * 15) +  5)] = ucGetZomToothTelCtCorrNoLearnBit(ucLoop);
    pucData[((ucLoop * 15) +  6)] = ucGetZomToothTelCtrNoCorr(ucLoop);
    pucData[((ucLoop * 15) +  7)] = ucGetZomToothTelCtNoLearnMode(ucLoop);
    pucData[((ucLoop * 15) +  8)] = ucGetZomDeltaMin(ucLoop);
    pucData[((ucLoop * 15) +  9)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_FL);
    pucData[((ucLoop * 15) + 10)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_FR);
    pucData[((ucLoop * 15) + 11)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_RL);
    pucData[((ucLoop * 15) + 12)] = ucGetZomAbsMetrics(ucLoop, cWheelPos_RR);
    pucData[((ucLoop * 15) + 13)] = ucGetZomLearnProbeCt(ucLoop);
    pucData[((ucLoop * 15) + 14)] = ucGetZomAbsoluteProbeCt(ucLoop);
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

