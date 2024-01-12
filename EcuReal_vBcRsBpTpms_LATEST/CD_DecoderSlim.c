/******************************************************************************/
/* File   : CD_DecoderSlim.c                                                  */
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

#include "CD_Decoder_X.hpp"

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
unsigned char caucInterestingTelTypes[] = cSeriesTelsOfInterest;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
unsigned char ucGetLen4Cmd(unsigned char ucCmd);

unsigned char ucGetLen4Cmd(unsigned char ucCmd){
   uint8 u8ReturnValue = 0;
   switch(ucCmd){
      case cTelTypeRotatS:
      case cTelTypeAK35defLMA:
      case cTelTypeAK35def:
      case cTelTypeStandstill:
          u8ReturnValue = ((unsigned char) 7);
          break;
      case cTelTypeHufStatus:
      case cTelTypeHufStatusLearn:
          u8ReturnValue = ((unsigned char) 9);
          break;
      case cTelTypeHufLfResponse:
          u8ReturnValue = ((unsigned char) 10);
          break;
      case cTelTypeSchraderFP:
          u8ReturnValue = ((unsigned char)13);
          break;
      default:
          u8ReturnValue = ((unsigned char) 0x0);
          break;
   }
   return u8ReturnValue;
}

unsigned char ucTelOfInterest(unsigned char ucCurTT){
   unsigned char i;
   for(i = 0; i < sizeof(caucInterestingTelTypes); i++){
      if(ucCurTT == caucInterestingTelTypes[i]){
         return ((unsigned char) 1);
      }
   }
   return ((unsigned char) 0);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

