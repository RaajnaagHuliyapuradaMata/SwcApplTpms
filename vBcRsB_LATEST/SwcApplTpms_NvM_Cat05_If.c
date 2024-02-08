/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat05_If.c                                        */
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
void PUTucVarCodLegislationEE(uint8 ucData){
    WriteMember2Blocks(5,1, &ucData);
}

uint8 GETucVarCodLegislationEE(void){
   uint8  l_ucaData   [NVM_CAT05_IDX01_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,1,l_ucaData );
    return(l_ucaData[0]);
}

void NvM3_PUTucVarCodHighPressResetThresEE(uint8 ucData){
  WriteMember2Blocks(CATEGORY5,INDEX2, &ucData);
}

uint8 NvM3_GETucVarCodHighPressResetThresEE(void){
  uint8 l_ucaData[NVM_CAT05_IDX02_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member (CATEGORY5,INDEX2,l_ucaData );
  return(l_ucaData[0]);
}

void NvM3_PUTucVarCodTemperatureWarningThresEE(sint8 scData){
  WriteMember2Blocks(CATEGORY5, INDEX3, ((uint8 *) &scData));
}

sint8 NvM3_GETucVarCodTemperatureWarningThresEE(void){
  uint8 l_ucaData[NVM_CAT05_IDX03_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member(CATEGORY5, INDEX3, l_ucaData);
  return ((sint8) (l_ucaData[0]));
}

void NvM3_PUTucVarCodOffroadPlacardPress(uint8 ucData){
  WriteMember2Blocks(CATEGORY5, INDEX4, &ucData);
}

uint8 NvM3_GETucVarCodOffroadPlacardPress(void){
  uint8 l_ucaData[NVM_CAT05_IDX04_REAL_SIZE];
  l_ucaData[0] = 0;
  ReadBlock2Member(CATEGORY5, INDEX4, l_ucaData);
  return (l_ucaData[0]);
}

void PUTucVarCodPlacardPressEE(uint8 ucData){
    WriteMember2Blocks(5,5, &ucData);
}

uint8 GETucVarCodPlacardPressEE (void){
   uint8  l_ucaData[NVM_CAT05_IDX05_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,5,l_ucaData );
    return(l_ucaData[0]);
}

void PUTucVarCodMinPressThresEE(uint8 ucData){
    WriteMember2Blocks(5,6, &ucData);
}

uint8 GETucVarCodMinPressThresEE(void){
   uint8  l_ucaData[NVM_CAT05_IDX06_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,6,l_ucaData );
    return(l_ucaData[0]);
}

void PUTucVarCodHighPressThresEE(uint8 ucData){
    WriteMember2Blocks(5,7, &ucData);
}

uint8 GETucVarCodHighPressThresEE(void){
   uint8  l_ucaData   [NVM_CAT05_IDX07_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,7,l_ucaData );
    return(l_ucaData[0]);
}

void PUTucVarCodAxImbSetThresEE(uint8 ucData){
    WriteMember2Blocks(5,8, &ucData);
}

uint8 GETucVarCodAxImbSetThresEE(void){
   uint8  l_ucaData   [NVM_CAT05_IDX08_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,8,l_ucaData );
    return(l_ucaData[0]);
}

void PUTucVarCodAxImbResThresEE(uint8 ucData){
    WriteMember2Blocks(5,9, &ucData);
}

uint8 GETucVarCodAxImbResThresEE(void){
   uint8  l_ucaData   [NVM_CAT05_IDX09_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (5,9,l_ucaData );
    return(l_ucaData[0]);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

