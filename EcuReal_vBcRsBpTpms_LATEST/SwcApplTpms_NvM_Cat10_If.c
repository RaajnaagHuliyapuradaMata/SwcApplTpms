/******************************************************************************/
/* File   : SwcApplTpms_NvM_Cat10_If.c                                        */
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
#include "SwcApplTpms_NvM_If.hpp"
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
void NvM_WriteData_NvInitialized(uint8 ucData);
void NvM_ReadData_NvInitialized(uint8 *ucpData);
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_NvInitialized(uint8 ucData){
  WriteMember2Blocks  (10,1,&ucData );
}

void NvM_ReadData_NvInitialized(uint8 *ucpData){
  ReadBlock2Member (10,1,ucpData);
}
#endif

void NvM_WriteData_ECUDefect(uint8 ucData){
  WriteMember2Blocks  (10,2,&ucData );
}

void NvM_ReadData_ECUDefect(uint8 *ucpData){
  ReadBlock2Member (10,2,ucpData);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

