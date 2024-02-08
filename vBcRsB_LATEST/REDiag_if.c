/******************************************************************************/
/* File   : REDiag_if.c                                                       */
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
#include "SwcApplTpms_DTC_If.hpp"
#include "CfgSwcApplTpms.hpp"
#include "tss_stdx.hpp"
#include "REDiag_if.hpp"

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
const uint8 ucWUDefectERRc[cAnzRad + 1] = {
   cZO_ERR_WS_DEFECT_FL,
   cZO_ERR_WS_DEFECT_FR,
   cZO_ERR_WS_DEFECT_RL,
   cZO_ERR_WS_DEFECT_RR,
   cZO_ERR_WS_DEFECT_XX
};

const uint8 ucWUFailERRc[cAnzRad + 1] = {
   cZO_ERR_WS_MISSING_FL,
   cZO_ERR_WS_MISSING_FR,
   cZO_ERR_WS_MISSING_RL,
   cZO_ERR_WS_MISSING_RR,
   cZO_ERR_WS_MISSING_XX };

#ifdef js_ReHighTemperatureDiag_230312
const uint8 ucWUTemperatureERRc[cAnzRad + 1] = {
   cZO_ERR_WS_OVERTEMPERATURE_FL,
   cZO_ERR_WS_OVERTEMPERATURE_FR,
   cZO_ERR_WS_OVERTEMPERATURE_RL,
   cZO_ERR_WS_OVERTEMPERATURE_RR,
   cZO_ERR_WS_OVERTEMPERATURE_XX };
#endif

const uint8 ucWULowLifeTimeERRc[cAnzRad + 1] = {
   cZO_ERR_WS_BATTERY_LOW_FL,
   cZO_ERR_WS_BATTERY_LOW_FR,
   cZO_ERR_WS_BATTERY_LOW_RL,
   cZO_ERR_WS_BATTERY_LOW_RR,
   cZO_ERR_WS_BATTERY_LOW_XX };

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
uint16 MaxFailCounterInEE(void){
   return(GETusMaxFolgeAusfallEE());
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

