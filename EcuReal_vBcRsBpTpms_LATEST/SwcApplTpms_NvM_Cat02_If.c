/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat02_If.c                                        */
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
void    PUTucReErrorStatusEE   (uint8 ucData);
uint8   GETucReErrorStatusEE   (void);
void    PUTucReHeatUpStatusEE  (uint8 ucData);
uint8   GETucReHeatUpStatusEE  (void);
void    PUTusFolgeAusfallCntEE (uint16 ucValue, uint8 ucSlot);
uint16  GETusFolgeAusfallCntEE (uint8 ucSlot);
void    PUTushGutEmpfCntEE     (uint16 uiData, uint8 ucSlot);
uint16  GETushGutEmpfCntEE     (uint8 ucSlot);
void    PUTushMissedCntEE      (uint16 uiData, uint8 ucSlot);
uint16  GETushMissedCntEE      (uint8 ucSlot);
void    PUTbHfIntLatchEE       (uint8 ucData);
boolean GETbHfIntLatchEE       (void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
void    PUTbRadwechselEE       (uint8 ucData);
#endif

void PUTucReErrorStatusEE(uint8 ucData){
  WriteMember2Blocks (2,1,&ucData);
}

uint8 GETucReErrorStatusEE(void){
  uint8  l_ucaData   [NVM_CAT02_IDX01_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (2,1,l_ucaData);
  return(l_ucaData[0]);
}

void PUTucReHeatUpStatusEE(uint8 ucData){
  WriteMember2Blocks (2,2, &ucData);
}

uint8 GETucReHeatUpStatusEE(void){
  uint8  l_ucaData   [NVM_CAT02_IDX02_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (2,2,l_ucaData );
  return(l_ucaData[0]);
}

void PUTusFolgeAusfallCntEE(uint16 ucValue,uint8 ucSlot){
  uint8 l_ucaData [NVM_CAT02_IDX03_REAL_SIZE];
  ReadBlock2Member (2,3,l_ucaData );
  l_ucaData[(2U*ucSlot)+0U] = ((uint8) ( 0xFF & (ucValue >> 8U) ) );
  l_ucaData[(2U*ucSlot)+1U] = ((uint8) ( 0xFF & (ucValue >> 0U) ) );
  WriteMember2Blocks (2,3,l_ucaData );
}

uint16 GETusFolgeAusfallCntEE(uint8 ucSlot){
  uint8 LocalCnt;
  uint8 l_ucaData [NVM_CAT02_IDX03_REAL_SIZE];
  uint16 l_uiRet;
  for( LocalCnt=0; LocalCnt < NVM_CAT02_IDX03_REAL_SIZE; LocalCnt++){
    l_ucaData[LocalCnt] = 0;
  }
  ReadBlock2Member (2,3,l_ucaData );
  l_uiRet = ((((uint16)l_ucaData[(2U*ucSlot)+0U] << 8U) & 0xFF00U)+
             (((uint16)l_ucaData[(2U*ucSlot)+1U] << 0U) & 0x00FFU) );
  return(l_uiRet);
}

void PUTushGutEmpfCntEE(uint16 uiData,uint8 ucSlot){
  uint8  l_ucaData   [NVM_CAT02_IDX04_REAL_SIZE];
  ReadBlock2Member (2,4,l_ucaData );
  l_ucaData[(2U*ucSlot)+0U] = ((uint8) ( 0xFF & (uiData >> 8U) ) );
  l_ucaData[(2U*ucSlot)+1U] = ((uint8) ( 0xFF & (uiData >> 0U) ) );
  WriteMember2Blocks (2,4,l_ucaData );
}

uint16 GETushGutEmpfCntEE(uint8 ucSlot){
  uint8 LocalCnt;
  uint8  l_ucaData   [NVM_CAT02_IDX04_REAL_SIZE];
  uint16 l_uiRet;
  for( LocalCnt=0; LocalCnt < NVM_CAT02_IDX04_REAL_SIZE; LocalCnt++){
    l_ucaData[LocalCnt] = 0;
  }
  ReadBlock2Member (2,4,l_ucaData );
  l_uiRet = ((((uint16)l_ucaData[(2U*ucSlot)+0U] << 8U) & 0xFF00U)+
              (((uint16)l_ucaData[(2U*ucSlot)+1U] << 0U) & 0x00FFU) );
  return (l_uiRet);
}

void PUTushMissedCntEE(uint16 uiData,uint8 ucSlot){
  uint8  l_ucaData   [NVM_CAT02_IDX05_REAL_SIZE];
  ReadBlock2Member (2,5,l_ucaData );
  l_ucaData[(2U*ucSlot)+0U] = ((uint8) ( 0xFF & (uiData >> 8U) ) );
  l_ucaData[(2U*ucSlot)+1U] = ((uint8) ( 0xFF & (uiData >> 0U) ) );
  WriteMember2Blocks (2,5,l_ucaData );
}

uint16 GETushMissedCntEE(uint8 ucSlot ){
  uint8 LocalCnt;
  uint8 l_ucaData [NVM_CAT02_IDX05_REAL_SIZE];
  uint16 l_uiRet;
  for( LocalCnt=0; LocalCnt < NVM_CAT02_IDX05_REAL_SIZE; LocalCnt++){
    l_ucaData[LocalCnt] = 0;
  }
  ReadBlock2Member (2,5,l_ucaData );
  l_uiRet = ((((uint16)l_ucaData[(2U*ucSlot)+0U] << 8U) & 0xFF00U)+
             (((uint16)l_ucaData[(2U*ucSlot)+1U] << 0U) & 0x00FFU) );
  return (l_uiRet);
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
void PUTbRadwechselEE(uint8 ucData){
  WriteMember2Blocks (2,6,&ucData);
}
#endif

void PUTbHfIntLatchEE(uint8 ucData){
WriteMember2Blocks (2,7,&ucData);
}

boolean GETbHfIntLatchEE(void){
  uint8  l_ucaData   [NVM_CAT02_IDX07_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (2,7,l_ucaData);
  return(l_ucaData[0]);
}

void NvM2_PutEOLRoutineStatusEE(uint8 ucData){
  WriteMember2Blocks (CATEGORY2,INDEX8,&ucData);
}

uint8 NvM2_GetEOLRoutineStatusEE(void){
  uint8 l_ucaData [NVM_CAT02_IDX08_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (CATEGORY2,INDEX8,l_ucaData);
  return(l_ucaData[0]);
}

void NvM2_PutEOLRoutineActiveEE(uint8 ucData){
  WriteMember2Blocks (CATEGORY2,INDEX9,&ucData);
}

uint8 NvM2_GetEOLRoutineActiveEE(void){
  uint8 l_ucaData [NVM_CAT02_IDX09_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (CATEGORY2,INDEX9,l_ucaData);
  return(l_ucaData[0]);
}

void NvM2_PutDiagUsedToDeleteDTCEE(uint8 ucData){
  WriteMember2Blocks (CATEGORY2,INDEX10,&ucData);
}

uint8 NvM2_GetDiagUsedToDeleteDTCEE(void){
  uint8 l_ucaData [NVM_CAT02_IDX10_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (CATEGORY2,INDEX10,l_ucaData);
  return(l_ucaData[0]);
}

void NvM2_PutDTCSingleActiveStatusEE(uint8* u8BufferForStatus){
  WriteMember2Blocks (CATEGORY2,INDEX11,u8BufferForStatus);
}

void NvM2_GetDTCSingleActiveStatusCEE(uint8* u8BufferForStatus){
  uint8 LocalCnt;
  uint8  u8Data [NVM_CAT02_IDX11_REAL_SIZE];
  for( LocalCnt=0; LocalCnt < NVM_CAT02_IDX11_REAL_SIZE; LocalCnt++){
   u8Data[LocalCnt] = 0;
  }
  ReadBlock2Member (CATEGORY2, INDEX11, u8Data );
  u8BufferForStatus[0] = u8Data[0];
  u8BufferForStatus[1] = u8Data[1];
  u8BufferForStatus[2] = u8Data[2];
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

