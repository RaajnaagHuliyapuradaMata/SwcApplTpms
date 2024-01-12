/******************************************************************************/
/* File   : state_zk.c                                                        */
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

#include "tss_stdx.hpp"
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "state_zkx.hpp"
#include "statemanagerX.hpp"

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
static uint16 ushZustandskennung;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void InitZK(void){
   ClearBitZustandskennungZK(
      cZK_ALLE_BITS);
}

void ClearBitZustandskennungZK(
   uint16 ushBitMask){
   ushZustandskennung &= ~ushBitMask;
}

boolean bGetBitZustandskennungZK(
   uint16 ushBitMask){
   return (boolean)((ushZustandskennung & ushBitMask) != 0);
}

void SetChangedBit4WP(
   uint8 ucWP){
   switch(ucWP){
      case (uint8)0: {
         ushZustandskennung |= cPOS_CHANGED_VL;
         break;
      }
      case (uint8)1: {
         ushZustandskennung |= cPOS_CHANGED_VR;
         break;
      }
      case (uint8)2: {
         ushZustandskennung |= cPOS_CHANGED_HL;
         break;
      }
      case (uint8)3: {
         ushZustandskennung |= cPOS_CHANGED_HR;
         break;
      }
      default: {
         ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL | cPOS_CHANGED_HR);
         break;
      }
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

