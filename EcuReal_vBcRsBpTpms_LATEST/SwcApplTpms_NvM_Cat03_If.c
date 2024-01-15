/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat03_If.c                                        */
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

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "WallocX.hpp"

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
void NvM3_PUTucAutolocationFailedCounter(uint8 ucCounterValue){
  WriteMember2Blocks(CATEGORY3, INDEX5, &ucCounterValue);
}

uint8 NvM3_GETucAutolocationFailedCounter(void){
  uint8 l_ucaData[NVM_CAT03_IDX05_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member(CATEGORY3, INDEX5, l_ucaData);
  return (l_ucaData[0]);
}

void NvM3_PUTHistoryIdsInEE(uint32 *ulData){
  WriteMember2Blocks(CATEGORY3, cHistorySet1, (uint8*)ulData);
}

void NvM3_GETHistoryIdsFromEE(uint32 *ulData){
  ReadBlock2Member(CATEGORY3, cHistorySet1, (uint8*)ulData );
}

void NvM3_PUTHistoryWPInEE(uint8 *ucData){
  WriteMember2Blocks(CATEGORY3, cHistoryWPSet1, ucData);
}

void NvM3_GETHistoryWPFromEE(uint8 *ucData){
  ReadBlock2Member (CATEGORY3, cHistoryWPSet1, ucData );
}

void NvM3_PUTWAParametersInEE(WAParameter sWheelAllocParamData){
  WriteMember2Blocks(CATEGORY3, cWAParameter, (uint8*)&sWheelAllocParamData);
}

void NvM3_GETWAParametersFromEE(WAParameter *sWheelAllocParamData){
  ReadBlock2Member (CATEGORY3, cWAParameter, (uint8*)sWheelAllocParamData);
}

void NvM3_PUTABSTicksInEE(WAABSTicksInOneRevolution sABSTicks){
  WriteMember2Blocks(CATEGORY3, cWAABSTicksInOneRevolution, (uint8*)&sABSTicks);
}

void NvM3_GETABSTicksFromEE(WAABSTicksInOneRevolution *sABSTicks){
  ReadBlock2Member(CATEGORY3, cWAABSTicksInOneRevolution, (uint8*)sABSTicks);
}

void GetWADataEE(unsigned char ucId, unsigned char *pRamAdr){
  if((ucId>0) && (ucId<5)){
    ReadBlock2Member (CATEGORY3,ucId , pRamAdr);
  }
}

void PutWADataEE(unsigned char ucId, unsigned char *pRamAdr){
  if((ucId>0) && (ucId<5)){
    WriteMember2Blocks (CATEGORY3, ucId,pRamAdr);
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

