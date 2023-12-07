#include "TPMSMsg.h"
#include "eeiface.h"

#define ucTPMStateMaskc     ((uint8) 0x03)
#define ucWnValidDefc       ((uint8) 0x08)
#define ucMsValidDefc       ((uint8) 0x00)
#define ucTPMSInitializedc  ((uint8) 0x01)

static WarnConfigArrayType aucWnValidTM;
static uint32 ulWarnOutTM[cucWarnOutArrayDim];
static uint8 aucWarnAtPosTM[cAnzRad + 1][cucWarnOutArrayDim];
static uint8 aucWPosTM[cAnzRad + 1];

static uint8 ucFilterIdWarnTM(uint8 ucIdX){
   uint8 ucRet = 0;
   if(ucIdX < cAnzRad){
      ucRet = (aucWarnAtPosTM[ucIdX][cucWarnOutStateIx] & ((uint8) ~aucWnValidTM[ucIxMsCfgc]));
   }
   else{
      ucRet = 0xff;
   }
   return(ucRet);
}

static void Warnings2MsgTM( const tTPMSMsgData* ptWarnInfo){
  const uint8 aucWTGroup[] = cWT_Group_map;
   uint8 ucLoop, ucWTCount, ucWnState, ucWnAttr, ucBitOffset;
  aucWarnAtPosTM[cAnzRad][cucWarnOutStateIx] = 0;
  aucWarnAtPosTM[cAnzRad][cucWarnOutAttrIx] = 0;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    aucWarnAtPosTM[cAnzRad][cucWarnOutStateIx] |= aucWarnAtPosTM[ucLoop][cucWarnOutStateIx];
    aucWarnAtPosTM[cAnzRad][cucWarnOutAttrIx] |= aucWarnAtPosTM[ucLoop][cucWarnOutAttrIx];
   }
   ulWarnOutTM[cucWarnOutStateIx] = 0;
   ulWarnOutTM[cucWarnOutAttrIx] = 0;

   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(((uint8) (ptWarnInfo->ucSystemState & ucPosDepWarnc)) == ucPosDepWarnc){
      ucBitOffset = aucWPosTM[ucLoop];
      }
      else{
      ucBitOffset = ucLoop;
      }

      ucWnState = ucFilterIdWarnTM(ucLoop);
      if(ucWnState > 0){
      ucWnAttr = aucWarnAtPosTM[ucLoop][cucWarnOutAttrIx];
      for(ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++){
          if((aucWTGroup[ucWTCount] >= cucWT_GroupA) && (aucWTGroup[ucWTCount] <= cucWT_GroupH)){
          if((ucWnState & (uint8) (1 << ucWTCount)) != 0){
            ulWarnOutTM[cucWarnOutStateIx] |= (uint32) (1 << ((aucWTGroup[ucWTCount] * cAnzRad) + ucBitOffset));
          }

          if((ucWnAttr & (uint8) (1 << ucWTCount)) != 0){
            ulWarnOutTM[cucWarnOutAttrIx] |= (uint32) (1 << ((aucWTGroup[ucWTCount] * cAnzRad) + ucBitOffset));
          }
        }
      }
      }
   }
}

static void TPMSMsgOutTM( const uint8* ptData){
   tTPMSMsgData tTPMSMsg;
   tTPMSMsg = *((const tTPMSMsgData *) (const void *) ptData);
   if(tTPMSMsg.ucId < cAnzRad){
    aucWarnAtPosTM[tTPMSMsg.ucId][cucWarnOutStateIx] = tTPMSMsg.ucWarnState;
    aucWarnAtPosTM[tTPMSMsg.ucId][cucWarnOutAttrIx]  = tTPMSMsg.ucWarnAttr;
    aucWPosTM[tTPMSMsg.ucId] = tTPMSMsg.ucPos;
    Warnings2MsgTM( &tTPMSMsg);
   }
}

static void TPMSMsgInitTM(Rte_Instance self, uint8* pucStatus, const uint8* pucIniDat){
   uint8 i;
  GetDataEE(self, cucTsIdTM, pucStatus);
   if((*pucStatus & ucTPMStateMaskc) == ucTPMSInitializedc){
    GetDataEE(self, cucCbIdTM, aucWnValidTM);
      for(i = 0; i < (cAnzRad + 1); i++){
      aucWPosTM[i] = cRadPosUndef;
      aucWarnAtPosTM[i][cucWarnOutStateIx] = 0;
      aucWarnAtPosTM[i][cucWarnOutAttrIx] = 0;
      }
   }
   else{
      if((pucIniDat[0] == 0) && (pucIniDat[1] == 0)){
      aucWnValidTM[ucIxWnCfgc] = ucWnValidDefc;
      aucWnValidTM[ucIxMsCfgc] = ucMsValidDefc;
      }
      else{
      aucWnValidTM[ucIxWnCfgc] = pucIniDat[0];
      aucWnValidTM[ucIxMsCfgc] = pucIniDat[1];
      }
    PutDataEE(self, cucCbIdTM, aucWnValidTM, TRUE);
    *pucStatus |= ucTPMSInitializedc;
    PutDataEE(self, cucTsIdTM, pucStatus, TRUE);
      for(i = 0; i < (cAnzRad + 1); i++){
      aucWPosTM[i] = cRadPosUndef;
      aucWarnAtPosTM[i][cucWarnOutStateIx] = 0;
      aucWarnAtPosTM[i][cucWarnOutAttrIx] = 0;
      }
   }
   ulWarnOutTM[cucWarnOutStateIx] = 0;
   ulWarnOutTM[cucWarnOutAttrIx] = 0;
}

uint8 ucTPMSMsgManagerTM(Rte_Instance self, uint8 ucAction, uint8* pucData){
   uint8 ucRet = 0;

   switch(ucAction){
      case ucPorInitc:
      ucRet = ucTPMSMsgManager_PorInitTM(self, pucData);
      break;

      case ucTPMSMsgOutc:
      ucRet = ucTPMSMsgManager_MsgOutTM( pucData);
      break;

      case ucDiagServicec:
      ucRet = ucTPMSMsgManagerDsTM(self, pucData);
      break;

      default:
      ucRet = 0xff;
      break;
   }
   return(ucRet);
}

static uint8 ucTPMSMsgManager_PorInitTM(Rte_Instance self, const uint8* pucData){
   uint8 ucTPMSMsgMngrState = 0;
   TPMSMsgInitTM(self, &ucTPMSMsgMngrState, pucData);
   return(ucTPMSMsgMngrState);
}

static uint8 ucTPMSMsgManager_MsgOutTM( const uint8* pucData){
   TPMSMsgOutTM( pucData);
   return( 0);
}

static uint8 ucTPMSMsgManagerDsTM(Rte_Instance self, uint8* pucData){
   uint8 ucRet = 0;
   switch(pucData[0]){
      case ucNewPositionsc:
      ucRet = ucTPMSMsgManagerDs_NewPositionsTM( &pucData[1]);
      break;

      case ucClearPosc:
      ucRet = ucTPMSMsgManagerDs_ClearPosTM();
      break;

      case ucWrWnValidTMc:
      ucRet = ucTPMSMsgManagerDs_WrWnValidTM(self, pucData);
      break;

      case ucRdWnValidTMc:
      ucRet = ucTPMSMsgManagerDs_RdWnValidTM( pucData);
      break;

      case ucClearWarnOfIdc:
      ucRet = ucTPMSMsgManagerDs_ClearWarnOfIdTM( pucData[1]);
      break;

      case ucPutWarnVectorSetc:
      ucRet = ucTPMSMsgManagerDs_PutWarnVectorSetTM( &pucData[1]);
      break;

      case ucGetWarnVectorsIdc:
      ucRet = ucTPMSMsgManagerDs_GetWarnVectorsIdTM( pucData);
      break;

      default:
      ucRet = 0xff;
      break;
   }
   return(ucRet);
}

static uint8 ucTPMSMsgManagerDs_NewPositionsTM( const uint8* pucData){
   uint8        ucLoop, ucRet = 0;
   boolean      bWheelPosInvalidFlag = FALSE;
   tTPMSMsgData tMsg;
   for(ucLoop = 0; ((ucLoop < cAnzRad) && (bWheelPosInvalidFlag == FALSE)); ucLoop++){
      if(pucData[ucLoop] >= cRadPosUndef){
      bWheelPosInvalidFlag = TRUE;
      }
   }
   if(bWheelPosInvalidFlag == FALSE){
    aucWPosTM[cAnzRad] = 0;
      for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      aucWPosTM[ucLoop] = pucData[ucLoop];
      }
    tMsg.ucId = cAnzRad;
    tMsg.ucSystemState = ucPosDepWarnc;
    Warnings2MsgTM( &tMsg);
      ucRet = 0;
   }
   else{
      for(ucLoop = 0; ucLoop < (cAnzRad + 1); ucLoop++){
      aucWPosTM[ucLoop] = cRadPosUndef;
      }
    tMsg.ucId = cAnzRad;
    tMsg.ucSystemState = 0;
    Warnings2MsgTM( &tMsg);
      ucRet = 0xff;
   }
   return(ucRet);
}

static uint8 ucTPMSMsgManagerDs_ClearPosTM(void){
   uint8        ucLoop;
   tTPMSMsgData tMsg;
   for(ucLoop = 0; ucLoop < (cAnzRad + 1); ucLoop++){
    aucWPosTM[ucLoop] = cRadPosUndef;
   }
   tMsg.ucId = cAnzRad;
   tMsg.ucSystemState = 0;
  Warnings2MsgTM( &tMsg);
   return( 0);
}

static uint8 ucTPMSMsgManagerDs_ClearWarnOfIdTM(uint8 ucWheelPos){
   uint8        ucLoop, ucRet = 0;
   boolean      bWheelPosInvalidFlag = FALSE;
   tTPMSMsgData tMsg;
   if(ucWheelPos == cAnzRad){
      for(ucLoop = 0; ucLoop < (cAnzRad + 1); ucLoop++){
      aucWPosTM[ucLoop] = cRadPosUndef;
      aucWarnAtPosTM[ucLoop][cucWarnOutStateIx] = 0;
      aucWarnAtPosTM[ucLoop][cucWarnOutAttrIx] = 0;
      }
      ulWarnOutTM[cucWarnOutStateIx] = 0;
      ulWarnOutTM[cucWarnOutAttrIx] = 0;
   }
   else if(ucWheelPos < cAnzRad){
      for(ucLoop = 0; ((ucLoop < cAnzRad) && (bWheelPosInvalidFlag == FALSE)); ucLoop++){
      if(aucWPosTM[ucLoop] >= cRadPosUndef){
        bWheelPosInvalidFlag = TRUE;
      }
      }
      if((ucFilterIdWarnTM(ucWheelPos) > 0) && (ulWarnOutTM[cucWarnOutStateIx] > 0)){
      if(bWheelPosInvalidFlag == TRUE){
        ucRet = 1;
      }
      else{
        ucRet = ucPosDepWarnc;
      }
      }
      else{
      ucRet = 0;
      }
      if(ucFilterIdWarnTM(ucWheelPos) > 0){
      aucWarnAtPosTM[ucWheelPos][cucWarnOutStateIx] = 0;
      aucWarnAtPosTM[ucWheelPos][cucWarnOutAttrIx] = 0;
      tMsg.ucId = cAnzRad;
      tMsg.ucSystemState = ucRet;
      Warnings2MsgTM( &tMsg);
      aucWPosTM[ucWheelPos] = cRadPosUndef;
      }
   }
   else{
      ucRet = 0xFF;
   }
   return(ucRet);
}

static uint8 ucTPMSMsgManagerDs_PutWarnVectorSetTM( const uint8* pucData){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
      if(pucData[0] == ucWarnBitIxWNc){
      aucWarnAtPosTM[ucLoop][cucWarnOutStateIx] = pucData[1 + ucLoop];
      }
      else{
      aucWarnAtPosTM[ucLoop][cucWarnOutAttrIx]  = pucData[1 + ucLoop];
      }
   }
   return( 0);
}

static uint8 ucTPMSMsgManagerDs_GetWarnVectorsIdTM(uint8* pucData){
   uint8 ucLoop;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    pucData[ucLoop] = ucFilterIdWarnTM(ucLoop);
   }
   return 0;
}

static uint8 ucTPMSMsgManagerDs_WrWnValidTM(Rte_Instance self, const uint8* pucData){
  const uint8 ucNonMaskableWT[] = cWT_NonMaskable_map;
   uint8 ucWTCount, ucWTMask = 0;
   for(ucWTCount = 0; ucWTCount < ucMaxWarnTypeWNc; ucWTCount++){
      ucWTMask |= (uint8) (ucNonMaskableWT[ucWTCount] << ucWTCount);
   }
   if((aucWnValidTM[ucIxWnCfgc] != ((const tParaSubSet *) (const void *) pucData)->ucParaByte[ucIxWnCfgc]) ||
      (aucWnValidTM[ucIxMsCfgc] != ((const tParaSubSet *) (const void *) pucData)->ucParaByte[ucIxMsCfgc])){
    aucWnValidTM[ucIxWnCfgc] = ((const tParaSubSet *) (const void *) pucData)->ucParaByte[ucIxWnCfgc];
    aucWnValidTM[ucIxMsCfgc] = (((const tParaSubSet *) (const void *) pucData)->ucParaByte[ucIxMsCfgc] & (uint8) ~ucWTMask);
    PutDataEE(self, cucCbIdTM, aucWnValidTM, TRUE);
   }
   return( 0);
}

static uint8 ucTPMSMsgManagerDs_RdWnValidTM(uint8* pucData){
   ((tParaSubSet *) (void*) pucData)->ucParaByte[ucIxWnCfgc] |= aucWnValidTM[ucIxWnCfgc];
   ((tParaSubSet *) (void*) pucData)->ucParaByte[ucIxMsCfgc] = 0;
   ((tParaSubSet *) (void*) pucData)->ucParaByte[ucIxMsCfgc] |= aucWnValidTM[ucIxMsCfgc];
   return( 0);
}

uint32 GETulWarnOutTM(void){
   return ulWarnOutTM[cucWarnOutStateIx];
}

uint32 GETulWarnAttrOutTM(void){
   return ulWarnOutTM[cucWarnOutAttrIx];
}

uint8 GETucWarningGroupTM(uint8 ucWarningGroup){
  const uint32 aulWarningGroupMaskc[] = { 0x0000000Fu, 0x000000F0u, 0x00000F00u, 0x0000F000u, 0x000F0000u, 0x00F00000u, 0x0F000000u, 0xF0000000u };
   uint8 ucWarningGroupBits = 0x00;
   if(ucWarningGroup < ucMaxWTGroupc){
      ucWarningGroupBits = (uint8) (((ulWarnOutTM[cucWarnOutStateIx] & aulWarningGroupMaskc[ucWarningGroup]) >> (ucWarningGroup * cAnzRad)) | (((ulWarnOutTM[cucWarnOutAttrIx] & aulWarningGroupMaskc[ucWarningGroup]) >> (ucWarningGroup * cAnzRad)) << 4));
   }
   return ucWarningGroupBits;
}
