/******************************************************************************/
/* File   : Walloc_IF.c                                                       */
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
#include "Std_Types.hpp"

#include "Walloc_IF.hpp"
#include "WAllocX.hpp"
#include "cd_decoder_x.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "statemanagerX.hpp"
#include "abs_linX.hpp"
#include "watcfX.hpp"

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
void CancelWATO(void){
  StopWallocTOAlarm();
}

void StartWATO(
   unsigned char ucTimeInSec){
   if(ucTimeInSec > 0){
    StartWallocTOAlarm(ucTimeInSec);
  }
}

#ifdef FPA
unsigned short ushGetABSingleTick(
   unsigned char ucIx){
  unsigned char LocalCnt;
  unsigned char  ucRet;
  unsigned short ushCnt[4];
  unsigned short ushCurrentAbsTick = 0;
   for(LocalCnt = 0; LocalCnt < 4; LocalCnt++){
   ushCnt[LocalCnt] = 0;
  }
  ucRet = GetLinABS( ushCnt );
   if(ucRet == cABS_OK){
   ushCurrentAbsTick = ushCnt[ucIx];
  }
  else{
   ushCurrentAbsTick = 0;
  }
  return ( ushCurrentAbsTick );
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

