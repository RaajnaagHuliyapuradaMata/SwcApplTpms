/******************************************************************************/
/* File   : EeErfsEcoBlock.c                                                  */
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
#include "EeErfsEcoBlockX.h"

#include "erfs_X.h"

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
void PutErfsEcoNeuerReifenEE(Rte_Instance self, const uint8* pucData){
   uint8 i;

   for(i = 0; i < TYRE_DATA_BYTES; i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[i];
   }
}

void PutErfsEcoReifenTabelleEE(Rte_Instance self, const uint8* pucData, const uint8 ucElement)
{
   uint8 i, Index;

   Index = (ucElement*TYRE_DATA_BYTES);

   if(ucElement < TYRE_LIST_MAX_ELEMENTS){
      for(i=0; i<TYRE_DATA_BYTES ;i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[Index+i];
      }
   }
   else{

      for(i = 0; i < 2; i++){
      Rte_Pim_NvmRdciErfsEcoBlock_NVBlock_MirrorBlock(self)->Data[i] = pucData[Index+i];
      }
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

