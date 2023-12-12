/******************************************************************************/
/* File   : EeErfsTsaBlock.c                                                  */
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
#include "EeErfsTsaBlockX.h"

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
static boolean bBlockNeedsUpdate = FALSE;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitErfsTsaBlockEE(Rte_Instance self){
   uint8 i;
   for(i = 0; i < sizeof(ImpTypeArrayDcm_RdcErfsTsaDatenLesenReadDataType); i++){
      PutTsaDataEE(self, 0x00, i);
   }
}

uint8 GetTsaDataEE(Rte_Instance self, uint8 i){
   return(Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self)->Data[i]);
}

void PutTsaDataEE(Rte_Instance self, uint8 x, uint8 i){
   Rte_Pim_NvmRdciErfsTsaBlock_NVBlock_MirrorBlock(self)->Data[i] = (x);
}

void SetErfsTsaBlockWriteMeEE(void){
   bBlockNeedsUpdate = TRUE;
}

void ClearErfsTsaBlockWriteMeEE(void){
   bBlockNeedsUpdate = FALSE;
}

boolean bGetErfsTsaBlockWriteMeEE(void){
   return bBlockNeedsUpdate;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

