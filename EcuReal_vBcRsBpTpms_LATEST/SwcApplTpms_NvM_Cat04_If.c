/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat04_If.c                                        */
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
#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_CcpCrcFilter   (      uint8  ucData);
void NvM_ReadData_CcpCrcFilter    (      uint8* ucpData);
void NvM_WriteData_CcpIdFilter    (      uint8  ucData);
void NvM_ReadData_CcpIdFilter     (      uint8* ucpData);
void NvM_WriteData_CcpAnzIdFilter (      uint8  ucAnzahl);
void NvM_ReadData_CcpAnzIdFilter  (      uint8* ucpData);
void NvM_WriteData_CcpOnOff       (      uint8  ucData);
void NvM_ReadData_CcpOnOff        (      uint8* ucpData);
void NvM_WriteData_CcpFilterIds   (const uint8  ucpData[]);
void NvM_ReadData_CcpFilterIds    (      uint8  ucpData[]);
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_CcpCrcFilter(uint8 ucData){
    WriteMember2Blocks (4,1,&ucData);
}

void NvM_ReadData_CcpCrcFilter(uint8 *ucpData){
    ReadBlock2Member (4,1,ucpData );
}

void NvM_WriteData_CcpIdFilter(uint8 ucData){
    WriteMember2Blocks (4,2, &ucData);
}

void NvM_ReadData_CcpIdFilter(uint8 *ucpData){
    ReadBlock2Member (4,2,ucpData );
}

void NvM_WriteData_CcpAnzIdFilter(uint8 ucAnzahl){
    WriteMember2Blocks (4,3,&ucAnzahl );
}

void NvM_ReadData_CcpAnzIdFilter(uint8 *ucpData){
    ReadBlock2Member (4,3,ucpData );
}

void NvM_WriteData_CcpOnOff(uint8 ucData){
    WriteMember2Blocks (4,4, &ucData);
}

void NvM_ReadData_CcpOnOff(uint8 *ucpData){
    ReadBlock2Member (4,4, ucpData );
}

void NvM_WriteData_CcpFilterIds(const uint8 ucpData[]){
    WriteMember2Blocks (4,5,(uint8 *)ucpData );
}

void NvM_ReadData_CcpFilterIds(uint8 ucpData[]){
    ReadBlock2Member (4,5,ucpData );
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

