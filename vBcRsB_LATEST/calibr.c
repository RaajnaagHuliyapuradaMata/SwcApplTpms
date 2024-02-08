/******************************************************************************/
/* File   : calibr.c                                                          */
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
#include "SwcApplTpms_NvM_If.hpp"
#include "statemanagerx.hpp"
#include "tss_stdx.hpp"
#include "calibrX.hpp"

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
void CalibrSetPressureCAL(void){
   uint8 u8Press;
   uint8 u8LocalVarCodPlacardPress;
   u8LocalVarCodPlacardPress = GETucVarCodPlacardPressEE();
   if((u8LocalVarCodPlacardPress >= cMINPOK) && (u8LocalVarCodPlacardPress <= cMAXPOK)){
      u8Press = u8LocalVarCodPlacardPress;
   }
   else{
      u8Press = 96;
      PUTucVarCodPlacardPressEE(
         u8Press);
   }
   InformWarnHandlerSM(
      0,
      u8Press,
      u8Press);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

