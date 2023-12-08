#include "Ctrl.h"
#include "USWarn.h"

static tParaSubSet tPSSA;

uint8 ucPrewarnThresCfactor = 0;
uint8 ucPrewarnThresNCfactor = 0;
uint8 ucAlarmThresCfactor = 0;
uint8 ucAlarmThresNCfactor = 0;
uint8 ucPrewarnDelayMin = 0;
uint8 ucPanneThres = 0;
uint8 ucDpToIPmin = 0;
uint8 ucShortHoldTime = 0;
uint8 ucLongHoldTime = 0;
uint8 ucThCTol = 0;
uint8 ucThNCTol = 0;
uint8 ucSaturierungAktiv = 0;

static void ChangeWNParaSubSet(Rte_Instance self){
   if(tPSSA.ucAccess == ucRdParaSubSetc){
      (void) ucWarnManagerWN(self, ucDiagServicec, &tPSSA.ucAccess);
    tPSSA.ucAccess = ucRdWnValidTMc;
      (void) ucTPMSMsgManagerTM(self, ucDiagServicec, &tPSSA.ucAccess);
    tPSSA.ucAccess = 0;
   }
   if(tPSSA.ucAccess == ucWrParaSubSetc){
      (void) ucWarnManagerWN(self, ucDiagServicec,&tPSSA.ucAccess);
    tPSSA.ucAccess = ucWrWnValidTMc;
      (void) ucTPMSMsgManagerTM(self, ucDiagServicec, &tPSSA.ucAccess);
    tPSSA.ucAccess = ucRdParaSubSetc;
      (void) ucWarnManagerWN(self, ucDiagServicec,&tPSSA.ucAccess);
   }
}

uint8 ucUSWAlgoParaWN(Rte_Instance self, uint8 ucAction, const uint8* pucData){
   uint8 ucRet = 0;
   switch(ucAction){
      case ucWrParaBytec:
      ucRet = ucUSWAlgoPara_WrParaByteWN(self, pucData);
      break;

      case ucWrParaThresc:
      ucRet = ucUSWAlgoPara_WrParaThresWN( pucData);
      break;

      default:
      ucRet = 0xff;
      break;
   }

   return(ucRet);
}

static uint8 ucUSWAlgoPara_WrParaByteWN(Rte_Instance self, const uint8* pucData){
   uint8 ucReturn = 0;
   tPSSA.ucAccess = ucRdParaSubSetc;
  ChangeWNParaSubSet(self);
   tPSSA.ucParaByte[ucIxWnCfgc] = pucData[0];
   if((pucData[2] & cUSWAlgo_ParaByte1_EU) == cUSWAlgo_ParaByte1_EU){
    tPSSA.ucParaByte[ucIxWnCfgc] |= cUSWAlgo_ParaByte1_EU;
    tPSSA.ucParaByte[ucIxWnCfgc] &= (uint8) ~cUSWAlgo_ParaByte1_US;
   }
   else{
    tPSSA.ucParaByte[ucIxWnCfgc] |= cUSWAlgo_ParaByte1_US;
    tPSSA.ucParaByte[ucIxWnCfgc] &= (uint8) ~cUSWAlgo_ParaByte1_EU;
   }
   tPSSA.ucParaByte[ucIxMsCfgc] = pucData[1];
   tPSSA.ucAccess = ucWrParaSubSetc;
  ChangeWNParaSubSet(self);
   return ucReturn;
}

static uint8 ucUSWAlgoPara_WrParaThresWN( const uint8* pucData){
   uint8 ucResult = cRetOk;
   if(pucData[0] > 0){
      ucPrewarnThresCfactor = pucData[0];
   }
   else{
      if(ucPrewarnThresCfactor == 0){
      ucPrewarnThresCfactor = 17;
      }
      ucResult = cRetError;
   }
   if(pucData[1] > 0){
      ucPrewarnThresNCfactor = pucData[1];
   }
   else{
      if(ucPrewarnThresNCfactor == 0){
      ucPrewarnThresNCfactor = 20;
      }
      ucResult = cRetError;
   }
   if(pucData[2] > 0){
      ucAlarmThresCfactor = pucData[2];
   }
   else{
      if(ucAlarmThresCfactor == 0){
      ucAlarmThresCfactor = 20;
      }
      ucResult = cRetError;
   }

   if(pucData[3] > 0){
      ucAlarmThresNCfactor = pucData[3];
   }
   else{
      if(ucAlarmThresNCfactor == 0){
      ucAlarmThresNCfactor = 25;
      }
      ucResult = cRetError;
   }
   if(pucData[4] > 0){
      ucPrewarnDelayMin = pucData[4];
   }
   else{
      if(ucPrewarnDelayMin == 0){
      ucPrewarnDelayMin = 2;
      }
      ucResult = cRetError;
   }
   if(pucData[5] > 0){
      ucPanneThres = pucData[5];
   }
   else{
      if(ucPanneThres == 0){
      ucPanneThres = 60;
      }
      ucResult = cRetError;
   }
   ucDpToIPmin = pucData[6];
   ucShortHoldTime = pucData[7];
   ucLongHoldTime = pucData[8];
   ucThCTol = pucData[9];
   ucThNCTol = pucData[10];
   ucSaturierungAktiv = pucData[11];
   return ucResult;
}

void InitUSWAlgo(Rte_Instance self, const uint8* ptWPos){
   uint8 aucDgServWN[6], aucDgServTM[6], ucLoop;
  aucDgServWN[0] = ucEuroCodec;
   (void) ucWarnManagerWN(self, ucPorInitc, aucDgServWN);
  aucDgServTM[0] = 0x00;
  aucDgServTM[1] = 0x00;
  aucDgServTM[2] = 0x00;
   (void) ucTPMSMsgManagerTM(self, ucPorInitc, aucDgServTM);
   TimerWT(self, ucIniTimec);
  aucDgServWN[0] = ucGetWarnVectorsc;
  aucDgServWN[1] = ucWarnBitIxWNc;
   (void) ucWarnManagerWN(self, ucDiagServicec, aucDgServWN);
  aucDgServTM[0] = ucPutWarnVectorSetc;
  aucDgServTM[1] = ucWarnBitIxWNc;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    aucDgServTM[2 + ucLoop] = aucDgServWN[2 + ucLoop];
   }
   (void) ucTPMSMsgManagerTM(self, ucDiagServicec, aucDgServTM);
  aucDgServWN[0] = ucGetWarnVectorsc;
  aucDgServWN[1] = ucWarnBitTonnageIxWNc;
   (void) ucWarnManagerWN(self, ucDiagServicec, aucDgServWN);
  aucDgServTM[0] = ucPutWarnVectorSetc;
  aucDgServTM[1] = ucWarnBitTonnageIxWNc;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    aucDgServTM[2 + ucLoop] = aucDgServWN[2 + ucLoop];
   }
   (void) ucTPMSMsgManagerTM(self, ucDiagServicec, aucDgServTM);
  aucDgServTM[0] = ucNewPositionsc;
   for(ucLoop = 0; ucLoop < cAnzRad; ucLoop++){
    aucDgServTM[1 + ucLoop] = ptWPos[ucLoop];
   }
   (void) ucTPMSMsgManagerTM(self, ucDiagServicec, aucDgServTM);
}
