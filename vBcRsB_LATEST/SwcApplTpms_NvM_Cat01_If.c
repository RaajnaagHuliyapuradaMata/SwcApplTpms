/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat01_If.c                                        */
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
uint8 GETucResetWarnPressRefEE(uint8 ucIndex){
   uint8 LocalCnt;
   uint8  l_ucaData   [NVM_CAT01_IDX07_REAL_SIZE];
   ucIndex = (ucIndex < 5) ? ucIndex : (uint8) 4;
   for(LocalCnt=0;LocalCnt<NVM_CAT01_IDX07_REAL_SIZE; LocalCnt++){
      l_ucaData[LocalCnt] = 0;
   }
    ReadBlock2Member (1,7,l_ucaData );
    return(l_ucaData[ucIndex]);
}

void PUTucResetWarnPressRefEE(uint8 ucIndex, uint8 ucData){
   uint8  l_ucaData   [NVM_CAT01_IDX07_REAL_SIZE];
   ucIndex = (ucIndex < 5) ? ucIndex : (uint8) 4;
    ReadBlock2Member (1,7,l_ucaData );
    l_ucaData[ucIndex] = ucData;
    WriteMember2Blocks (1,7,l_ucaData );
}

void PUTucPatmoEE(uint8 ucData){
    WriteMember2Blocks(1,8, &ucData);
}

uint8 GETucPatmoEE(void){
   uint8  l_ucaData   [NVM_CAT01_IDX08_REAL_SIZE];
    l_ucaData[0] = 0;
    ReadBlock2Member (1,8,l_ucaData );
    return(l_ucaData[0]);
}

void PUTscAdaptedTrefEE(sint8 scData){
    WriteMember2Blocks(1,9,(uint8*)(&scData));
}

sint8 GETscAdaptedTrefEE(void){
   sint8  l_scaData   [NVM_CAT01_IDX09_REAL_SIZE];
    l_scaData[0] = 0;
    ReadBlock2Member (1,9,(uint8*)(l_scaData));
    return(l_scaData[0]);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

