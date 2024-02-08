/******************************************************************************/
/* File   : sila.c                                                            */
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
#include "SilaX.hpp"

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
STATIC tSilaStateType ucSilaState;
STATIC tSilaStateType ucSilaStateOut;
STATIC tSilaStateType ucSilaStateInt;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void SilaInit(void){
   ucSilaState    = SILA_STATE_NORMAL_OFF;
   ucSilaStateOut = SILA_STATE_NORMAL_OFF;
   ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}

void SilaPutState(tSilaStateType ucState){
   if(
         (SILA_STATE_MALFUNCTIONFLASH == ucSilaStateInt)
      && (SILA_STATE_PERMANENT_ON     == ucState)
   ){
   }
   else{
      ucSilaStateInt = ucState;
   }
}

tSilaStateType SilaGetState(void){
   return(ucSilaStateOut);
}

void SilaTask(void){
   ucSilaStateOut = ucSilaStateInt;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

