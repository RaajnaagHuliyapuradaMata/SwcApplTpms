/******************************************************************************/
/* File   : RdcErfsEcoServices.c                                              */
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
#include "RdcErfsEcoServicesX.h"

#include "ERFS_X.h"
#include "EeErfsBlockX.h"
#include "EeErfsEcoBlockX.h"
#include "EeCommonBlockX.h"
#include "DataManagerX.h"
#include "HS_KalibrierereignisX.h"
#include "InitializationX.h"
#include "state_bzX.h"
#include "InfotyreX.h"
#include "SeasRcpAdjX.h"

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
void GetStatusRdcErfsEcoTabLesenDS(uint8* pucData){
   uint8 ucElement;
   uint8 ucMember;
   uint8 ucOffset,ucIndex;

  pucData[0] = GetMaxTyreTablePos();

   for(ucElement = 0; ucElement < TYRE_LIST_MAX_ELEMENTS; ucElement++){
      ucOffset = (ucElement*TYRE_DATA_BYTES);

      for(ucMember = 0; ucMember < TYRE_DATA_BYTES; ucMember++){
      ucIndex = (1+ucOffset+ucMember);

      pucData[ucIndex] = GetTyreListMember(ucElement, ucMember);
      }
   }

   ucIndex++;
  pucData[ucIndex] = 0x00;
   ucIndex++;
  pucData[ucIndex] = 0x00;

}

void GetStatusRdcErfsAktReifenEcoLesenDS(Rte_Instance self, uint8* pucData){
   uint8 ucCurIndex,ucSuIndex, ucWiIndex;
   uint8 ucPtrIndex;

   ucCurIndex = GETSelectedTyreIndexEE(self);

   if(ucCurIndex < GetLengthOfTyreListDM()){

      if(GetSaisonRaw(ucCurIndex) == CSEASON_SUMMER){

      ucSuIndex = ucCurIndex;
      ucWiIndex = GETSelectedWiTyreIndexEE(self);
      }
      else{

      ucWiIndex = ucCurIndex;
      ucSuIndex = GETSelectedSuTyreIndexEE(self);
      }
   }
   else{

      ucSuIndex = GETSelectedSuTyreIndexEE(self);
      ucWiIndex = GETSelectedWiTyreIndexEE(self);
   }

   for(ucPtrIndex=0;ucPtrIndex<34;ucPtrIndex++){
    pucData[ucPtrIndex] = 0x00;
   }

   ucPtrIndex = 0;

   if(ucSuIndex < TYRE_LIST_MAX_ELEMENTS){

      if(ucSuIndex == ucCurIndex){
      pucData[ucPtrIndex] = (uint8)TRUE;
      }
      else{
      pucData[ucPtrIndex] = (uint8)FALSE;
      }
      ucPtrIndex++;

    pucData[ucPtrIndex] = ucSuIndex;
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetReifenbreiteRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetQuerschnittRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetDurchmesserRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetTragfaehigkeitRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetGeschwIndexRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetSaisonRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetKarkasseRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetReifentypRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetWerksauslieferungRaw(ucSuIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucSuIndex)-80)/4);
      ucPtrIndex++;
   }
   else{
      ucPtrIndex = 17;
   }

   if(ucWiIndex < TYRE_LIST_MAX_ELEMENTS){

      if(ucWiIndex == ucCurIndex){
      pucData[ucPtrIndex] = (uint8)TRUE;
      }
      else{
      pucData[ucPtrIndex] = (uint8)FALSE;
      }
      ucPtrIndex++;

    pucData[ucPtrIndex] = ucWiIndex;
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetReifenbreiteRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetQuerschnittRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetDurchmesserRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetTragfaehigkeitRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetGeschwIndexRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetSaisonRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetKarkasseRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetReifentypRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = GetWerksauslieferungRaw(ucWiIndex);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucWiIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucWiIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_ECO_LOAD, ucWiIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_ECO_LOAD, ucWiIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucWiIndex)-80)/4);
      ucPtrIndex++;

    pucData[ucPtrIndex] = ((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucWiIndex)-80)/4);
   }

}

void GetStatusRdcErfsAktReifenLesenDS(Rte_Instance self, uint8* pucData){
   uint8 ucElement;
   uint8 ucIndex;

   for(ucIndex = 0; ucIndex < 30; ucIndex++){
    pucData[ucIndex] = 0x00;
   }

   ucIndex = 0x00;

   ucElement = GETSelectedSuTyreIndexEE(self);

   if(ucElement < TYRE_LIST_MAX_ELEMENTS){

      if(ucElement == GETSelectedTyreIndexEE(self)){
        pucData[ucIndex] = (uint8)TRUE;
      }
      else{
        pucData[ucIndex] = (uint8)FALSE;
      }
      ucIndex++;

      pucData[ucIndex] = ucElement;
      ucIndex++;

      pucData[ucIndex] = GetReifenbreiteRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetQuerschnittRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetDurchmesserRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetTragfaehigkeitRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetGeschwIndexRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetSaisonRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetKarkasseRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetReifentypRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = GetWerksauslieferungRaw(ucElement);
      ucIndex++;

      pucData[ucIndex] = ((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucElement)-80)/4);
      ucIndex++;

      pucData[ucIndex] = ((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucElement)-80)/4);
      ucIndex++;

      pucData[ucIndex] = ((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucElement)-80)/4);
      ucIndex++;

      pucData[ucIndex] = ((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucElement)-80)/4);
      ucIndex++;
   }
   else{
      ucIndex = 15;
   }
   ucElement = GETSelectedWiTyreIndexEE(self);

   if(ucElement < TYRE_LIST_MAX_ELEMENTS){

      if(ucElement == GETSelectedTyreIndexEE(self)){
      pucData[ucIndex] = (uint8)TRUE;
      }
      else{
      pucData[ucIndex] = (uint8)FALSE;
      }
      ucIndex++;

    pucData[ucIndex] = ucElement;
      ucIndex++;

    pucData[ucIndex] = GetReifenbreiteRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetQuerschnittRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetDurchmesserRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetTragfaehigkeitRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetGeschwIndexRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetSaisonRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetKarkasseRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetReifentypRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = GetWerksauslieferungRaw(ucElement);
      ucIndex++;

    pucData[ucIndex] = ((GetFrontAxleSetPressTyreList(REQ_PART_LOAD, ucElement)-80)/4);
      ucIndex++;

    pucData[ucIndex] = ((GetRearAxleSetPressTyreList(REQ_PART_LOAD, ucElement)-80)/4);
      ucIndex++;

    pucData[ucIndex] = ((GetFrontAxleSetPressTyreList(REQ_FULL_LOAD, ucElement)-80)/4);
      ucIndex++;

    pucData[ucIndex] = ((GetRearAxleSetPressTyreList(REQ_FULL_LOAD, ucElement)-80)/4);
   }

}

uint8 ucPutSteuernRdcErfsEcoAktReifenposVorgebenDS(Rte_Instance self, const uint8* pucData){
   uint8 Position,i;
   uint8 Index = 0;
   uint8 ucRet = cRetOk;

   Position = pucData[Index];
   Index++;

   for(i=0; i<TYRE_DATA_BYTES; i++){
      if(pucData[Index] != GetTyreListMember(Position, i)){
      ucRet = cRetError;
      }
    Index++;
   }

   if(ucRet == cRetOk){
    SetStatusManSelectionDM(ST_MAN_SLCTN_Manuelle_Reifenauswahl);
    SetSelectedTyreIndexDM(Position);

      if(GetSeasonDM() == OP_TYR_SEA_TPCT_Winterreifen){
       SetWinterTyreIndexDM(Position);
      }
      else{
      if(GetSeasonDM() == OP_TYR_SEA_TPCT_Sommerreifen){
        SetSummerTyreIndexDM(Position);
      }
      else{
        ucRet = cRetError;
      }
      }
      if(ucRet == cRetOk){
      if(TRUE == bGetBitBetriebszustandBZ(cZUGEORDNET)){
        SetSolldruckDM(self, GetLoadStateDM(), Position);
        (void) ZoPlausiInitPressINIT(self, TRUE, Position);

        SetCalibrationRootCauseDS(self, cCalByDiag);
        (void)SaveCalibrationEventDS(self);

        StartSRA(self);

        NotificationITY(self, cNotifyRcpChangedITY, cAnzRad);

        PUTPlausiInitErrorEE(self, FALSE);

        PUTTyreChangedEE(self, FALSE);

        PUTAutomaticSelectionFailedStatusEE(self, FALSE);
        PUTStSelectTyreEE(self, ST_SLCTN_TYR_Auswahl);

        SaveCurrentTyreSelectionDM(self);
      }
      else{
        ucRet = cRetError;
      }
      }
   }
   return(ucRet);
}

uint8 ucPutSteuernRdcErfsEcoNeueReifenVorgebenDS(Rte_Instance self, const uint8* pucData){
   uint8 ucRet = cRetOk;

   PutErfsEcoNeuerReifenEE(self, &pucData[1]);

   return(ucRet);
}

uint8 ucPutSteuernRdcErfsEcoReifentabelleVorgebenDS(Rte_Instance self, const uint8* pucData, const uint8 ucElement){
   uint8 ucRet = cRetOk;

   if(ucElement <= TYRE_LIST_MAX_ELEMENTS){
    PutErfsEcoReifenTabelleEE(self, pucData, ucElement);
   }
   else{
      ucRet = cRetError;
   }

   return(ucRet);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

