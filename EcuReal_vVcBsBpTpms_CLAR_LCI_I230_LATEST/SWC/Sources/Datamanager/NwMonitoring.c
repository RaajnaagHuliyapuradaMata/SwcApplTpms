

#include "nwmonitoring.h"

#include "state_fzzX.h"
#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "EeDiagBlockX.h"
#include "WuMonitoringX.h"
#include "WallocX.h"
#include "BandmodeX.h"

static uint32 ulNetworkErrors = cNetworkNoError;
static uint32 ulNetworkErrChangedFlags = cNetworkNoError;
static uint8 ucDpErrInd = 0xFF;

static tNwMonitoringData tNwMonitoring;

#ifdef _EcuVirtual
static uint32 FilterSubsequentErrorsNWM(uint32 ulErrorBits);

static uint8 CheckRDC_DT_PCKG12_AliveNWM(Rte_Instance self, uint8 ucAlive1, uint8 ucAlive2, uint8 DpNo);
static uint8 CheckRDC_DT_PCKG12_SignalNWM(Rte_Instance self, uint16 ushRdcMesTstmp, uint8 DpNo);
static uint8 CheckA_TEMP_SignalNWM(Rte_Instance self, Rdci_TEMP_EX_Type tempEx);
static uint8 CheckEINHEITEN_BN2020_SignalNWM(Rte_Instance self, Rdci_UN_AIP_Type unitAip, Rdci_UN_TEMP_Type unitTemp);
static uint8 CheckCON_VEH_SignalNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh);
static uint8 CheckCON_VEH_CrcNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh);
static uint8 CheckCON_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive);
static uint8 CheckBN2020_RELATIVZEIT_SignalNWM(Rte_Instance self, Rdci_T_SEC_COU_REL_Type relTime);
static uint8 CheckDT_PT_1_SignalNWM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type aip);
static uint8 CheckUHRZEIT_DATUM_SignalNWM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type timeDate);
static uint8 CheckWMOM_DRV_4_SignalNWM(Rte_Instance self, Rdci_WMOM_DRV_4_Type wmom);
static uint8 CheckKILOMETERSTAND_SignalNWM(Rte_Instance self, Rdci_MILE_KM_Type mileKm);
static uint8 CheckNMEARawData2Part2_SignalNWM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude);
static uint8 CheckNMEARawData2Part3_SignalNWM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters);
static uint8 CheckV_VEH_SigQualifNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh);
static uint8 CheckV_VEH_CrcNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh);
static uint8 CheckV_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive);
#else
#endif

void InitNWM(Rte_Instance self)
{
   uint32 ulLastNwmErrorState;
   uint32 j;

   tNwMonitoring.tMonA_TEMP.ucMsgTimeout = cA_TEMP_MSG_TOUT;
   tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout = cA_TEMP_SIG_TOUT;

   tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter = 0;
   tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter = 0;
   tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter = 0;
   tNwMonitoring.tMonCON_VEH.ucMsgTimeout = cCON_VEH_MSG_TOUT;

   tNwMonitoring.tMonDT_PT_1.ucMsgTimeout = cDT_PT_1_MSG_TOUT;
   tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout = cDT_PT_1_SIG_TOUT;

   tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout = cEINHEITEN_BN2020_MSG_TOUT;
   tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter = 0;

   tNwMonitoring.tMonRDC_DT_PCKG[0].ucAliveErrorCounter = 0;
   tNwMonitoring.tMonRDC_DT_PCKG[1].ucAliveErrorCounter = 0;
   tNwMonitoring.tMonRDC_DT_PCKG[0].ucAlvErrGoodCounter = 0;
   tNwMonitoring.tMonRDC_DT_PCKG[1].ucAlvErrGoodCounter = 0;
   tNwMonitoring.tMonRDC_DT_PCKG[0].ushMsgTimeout = cRDC_DT_PCKG12_MSG_TOUT;
   tNwMonitoring.tMonRDC_DT_PCKG[1].ushMsgTimeout = cRDC_DT_PCKG12_MSG_TOUT;
   tNwMonitoring.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;
   tNwMonitoring.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;

   tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout = cBN2020_RELATIVZEIT_MSG_TOUT;
   tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout = cBN2020_RELATIVZEIT_SIG_TOUT;

   tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout = cUHRZEIT_DATUM_SIG_TOUT_OFF;
   tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout = cKILOMETERSTAND_SIG_TOUT_OFF;

   tNwMonitoring.tMonNMEARawData2Part2.ucMsgTimeout = cNMEARawData2Part2_MSG_TOUT;
   tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout = cNMEARawData2Part2_SIG_TOUT;

   tNwMonitoring.tMonNMEARawData2Part3.ucMsgTimeout = cNMEARawData2Part3_MSG_TOUT;
   tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout = cNMEARawData2Part3_SIG_TOUT;

   tNwMonitoring.tMonWMOM_DRV_4.ucMsgTimeout = cWMOM_DRV_4_MSG_TOUT;
   tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout = cWMOM_DRV_4_SIG_TOUT;

   tNwMonitoring.tMonV_VEH.ucMsgTimeout = cV_VEH_MSG_TOUT;
   tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout = cV_VEH_ALIVE_TOUT;
   tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout = cV_VEH_CRC_TOUT;
   tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout = cV_VEH_SIGQUALIF_TOUT;
   ulLastNwmErrorState = GETulNwmErrorsEE(self);

   for(j=0; j<32; j++){
      if((ulLastNwmErrorState & (uint32)(1<<j)) == (uint32)(1<<j)){
      if((ulNetworkErrors & (uint32)(1<<j)) == 0){
        ulNetworkErrChangedFlags |= (uint32)(1<<j);
      }
      }
   }
   ulNetworkErrors |= ulLastNwmErrorState;
}

void TimerTickNWM(Rte_Instance self){
   static uint8 ucSecond = 10;
   if(bGetBandmodeBM() == TRUE){
    return;
   }
   if(bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == TRUE){
    return;
   }
   ucSecond--;
   switch(ucSecond){
  case (uint8)9:
      if(tNwMonitoring.tMonCON_VEH.ucMsgTimeout > 0){
      tNwMonitoring.tMonCON_VEH.ucMsgTimeout--;
      if(tNwMonitoring.tMonCON_VEH.ucMsgTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_CON_VEH_MsgMissing);
      }
      }
      break;
  case (uint8)0:
      ucSecond = (uint8)10;
      break;

   default:{
      break;
      }
   }

   if(ucGetStatusConditionVehicleFZZ() >= ST_CON_VEH_Pruefen_Analyse_Diagnose){
      switch(ucSecond){
      case (uint8)8:
      if(tNwMonitoring.tMonA_TEMP.ucMsgTimeout > 0){
        tNwMonitoring.tMonA_TEMP.ucMsgTimeout--;
          if(tNwMonitoring.tMonA_TEMP.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_A_TEMP_MsgMissing);
        }
      }
      if(tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout > 0){
        tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout--;
          if(tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_A_TEMP_SignalError);
        }
      }
      break;

      case (uint8)7:
      if(tNwMonitoring.tMonRDC_DT_PCKG[0].ushMsgTimeout > 0){
        tNwMonitoring.tMonRDC_DT_PCKG[0].ushMsgTimeout--;
          if(tNwMonitoring.tMonRDC_DT_PCKG[0].ushMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_MsgMissing);
          SetDataPackageErrorIndNWM(cDP_TO_SHIFT, cDataPackage12Ix);
        }
      }
      if(tNwMonitoring.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout > 0){
        tNwMonitoring.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout--;
          if(tNwMonitoring.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_SignalError);
          SetDataPackageErrorIndNWM(cDP_SE_SHIFT, cDataPackage12Ix);
        }
      }
      if(GETucFBD4CountEE(self) > 1){
          if(tNwMonitoring.tMonRDC_DT_PCKG[1].ushMsgTimeout > 0){
          tNwMonitoring.tMonRDC_DT_PCKG[1].ushMsgTimeout--;
          if(tNwMonitoring.tMonRDC_DT_PCKG[1].ushMsgTimeout == 0){
            SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_MsgMissing);
            SetDataPackageErrorIndNWM(cDP_TO_SHIFT, cDataPackage34Ix);
          }
        }
          if(tNwMonitoring.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout > 0){
          tNwMonitoring.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout--;
          if(tNwMonitoring.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout == 0){
            SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_SignalError);
            SetDataPackageErrorIndNWM(cDP_SE_SHIFT, cDataPackage34Ix);
          }
        }
      }
      break;

      case (uint8)6:
      if(tNwMonitoring.tMonDT_PT_1.ucMsgTimeout > 0){
        tNwMonitoring.tMonDT_PT_1.ucMsgTimeout--;
          if(tNwMonitoring.tMonDT_PT_1.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_DT_PT_1_MsgMissing);
        }
      }
      if(tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout > 0){
        tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout--;
          if(tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_DT_PT_1_SignalError);
        }
      }
      if(tNwMonitoring.tMonNMEARawData2Part2.ucMsgTimeout > 0){
        tNwMonitoring.tMonNMEARawData2Part2.ucMsgTimeout--;
          if(tNwMonitoring.tMonNMEARawData2Part2.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_NMEARawData2Part2_MsgMissing);
        }
      }
      if(tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout > 0){
        tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout--;
          if(tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_NMEARawData2Part2_SignalError);
        }
      }
      if(tNwMonitoring.tMonNMEARawData2Part3.ucMsgTimeout > 0){
        tNwMonitoring.tMonNMEARawData2Part3.ucMsgTimeout--;
          if(tNwMonitoring.tMonNMEARawData2Part3.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_NMEARawData2Part3_MsgMissing);
        }
      }
      if(tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout > 0){
        tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout--;
          if(tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_NMEARawData2Part3_SignalError);
        }
      }
      break;

      case (uint8)5:
      if(tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout > 0){
        tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout--;
          if(tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_EINHEITEN_MsgMissing);
        }
      }
      break;

      case (uint8)4:
      if(tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout > 0){
        tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout--;
          if(tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_RELATIVZEIT_MsgMissing);
        }
      }
      if(tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout > 0){
        tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout--;
          if(tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_RELATIVZEIT_SignalError);
        }
      }
      break;

      case (uint8)3:
      if((tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout != cUHRZEIT_DATUM_SIG_TOUT_OFF)
        && (tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout > 0)){
        tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout--;
          if(tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_UHRZEIT_DATUM_SignalError);
        }
      }
      if((tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout != cKILOMETERSTAND_SIG_TOUT_OFF)
        && (tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout > 0)){
        tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout--;
          if(tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout == 0){
          SetNetworkErrorNWM(self, cNetwork_KILOMETERSTAND_SignalError);
        }
      }
      break;

      default:
      break;
      }

      if(tNwMonitoring.tMonWMOM_DRV_4.ucMsgTimeout > 0){
      tNwMonitoring.tMonWMOM_DRV_4.ucMsgTimeout--;
      if(tNwMonitoring.tMonWMOM_DRV_4.ucMsgTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_WMOM_DRV_4_MsgMissing);
      }
      }
      if(tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout > 0){
      tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout--;
      if(tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_WMOM_DRV_4_SignalError);
      }
      }
      if(tNwMonitoring.tMonV_VEH.ucMsgTimeout > 0){
      tNwMonitoring.tMonV_VEH.ucMsgTimeout--;
      if(tNwMonitoring.tMonV_VEH.ucMsgTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_V_VEH_MsgMissing);
      }
      }
      if(tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout > 0){
      tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout--;
      if(tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_V_VEH_AliveError);
      }
      }
      if(tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout > 0){
      tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout--;
      if(tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_V_VEH_CrcError);
      }
      }
      if(tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout > 0){
      tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout--;
      if(tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout == 0){
        SetNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError);
      }
      }
   }
}

uint8 CheckRDC_DT_PCKG12_MsgNWM(Rte_Instance self, const ImpTypeRecCddRdcData* rdcData){
   uint8 ucRetVal = cNoError;
   uint8 i,DpIx;
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   if(0x34 == rdcData->DP_NO){
    PUTucFBD4CountEE(self, 2);
    DpIx = cDataPackage34Ix;
   }
   else{
    DpIx = cDataPackage12Ix;
   }
   tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ushMsgTimeout = cRDC_DT_PCKG12_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_MsgMissing) == TRUE){
      if(ResetDataPackageErrorIndNWM(self, cDP_TO_SHIFT, DpIx) == TRUE){
      ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_MsgMissing);
      }
    tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;
      for(i=0; i<cMaxLR; i++){
      if(bGetReMuteStatusBySlotWUM(i) == FALSE){
        ClearMuteWUM(self, i, ucGetWPOfColWAL(i));
      }
      }
   }
   else{
    (void)ResetDataPackageErrorIndNWM(self, cDP_TO_SHIFT, DpIx);
   }
   ucRetVal |= CheckRDC_DT_PCKG12_AliveNWM(self, rdcData->ALIV_RDC_DT_PCK_1, rdcData->ALIV_RDC_DT_PCK_2, rdcData->DP_NO);
   ucRetVal |= CheckRDC_DT_PCKG12_SignalNWM(self, rdcData->RDC_MES_TSTMP, rdcData->DP_NO);
   return ucRetVal;
}

uint8 CheckA_TEMP_MsgNWM(Rte_Instance self, Rdci_TEMP_EX_Type tempEx){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonA_TEMP.ucMsgTimeout = cA_TEMP_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_A_TEMP_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_A_TEMP_MsgMissing);
    tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout = cA_TEMP_SIG_TOUT;
   }
   return CheckA_TEMP_SignalNWM(self, tempEx);
}

uint8 CheckEINHEITEN_BN2020_MsgNWM(Rte_Instance self, Rdci_UN_AIP_Type unitAipData, Rdci_UN_TEMP_Type unitTempData){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout = cEINHEITEN_BN2020_MSG_TOUT;
  ClearNetworkErrorNWM(self, cNetwork_EINHEITEN_MsgMissing);
   return CheckEINHEITEN_BN2020_SignalNWM(self, unitAipData, unitTempData);
}

uint8 CheckCON_VEH_MsgNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh){
   uint8 retVal = cNoError;
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonCON_VEH.ucMsgTimeout = cCON_VEH_MSG_TOUT;
  ClearNetworkErrorNWM(self, cNetwork_CON_VEH_MsgMissing);
   retVal |= CheckCON_VEH_SignalNWM(self, conVeh);
   retVal |= CheckCON_VEH_CrcNWM(self, conVeh);
   retVal |= CheckCON_VEH_AliveNWM(self, conVeh.ALIV_CON_VEH);
   return retVal;
}

uint8 CheckV_VEH_MsgNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh){
   uint8 retVal = cNoError;
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonV_VEH.ucMsgTimeout = cV_VEH_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_V_VEH_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_V_VEH_MsgMissing);
    tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout = cV_VEH_SIGQUALIF_TOUT;
    tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout = cV_VEH_ALIVE_TOUT;
    tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout = cV_VEH_CRC_TOUT;
   }
   retVal |= CheckV_VEH_SigQualifNWM(self, vVeh);
   retVal |= CheckV_VEH_CrcNWM(self, vVeh);
   retVal |= CheckV_VEH_AliveNWM(self, vVeh.ALIV_V_VEH);
   return retVal;
}

uint8 CheckBN2020_RELATIVZEIT_MsgNWM(Rte_Instance self, Rdci_T_SEC_COU_REL_Type relTime){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout = cBN2020_RELATIVZEIT_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_RELATIVZEIT_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_RELATIVZEIT_MsgMissing);
    tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout = cBN2020_RELATIVZEIT_SIG_TOUT;
   }
   return (CheckBN2020_RELATIVZEIT_SignalNWM(self, relTime));
}

uint8 CheckDT_PT_1_MsgNWM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type aip){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonDT_PT_1.ucMsgTimeout = cDT_PT_1_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_DT_PT_1_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_DT_PT_1_MsgMissing);
    tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout = cDT_PT_1_SIG_TOUT;
   }
   return (CheckDT_PT_1_SignalNWM(self, aip));
}

uint8 CheckNMEARawData2Part2_MsgNWM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonNMEARawData2Part2.ucMsgTimeout = cNMEARawData2Part2_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_NMEARawData2Part2_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_NMEARawData2Part2_MsgMissing);
    tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout = cNMEARawData2Part2_SIG_TOUT;
   }
   return CheckNMEARawData2Part2_SignalNWM(self, GNSSPositionAltitude);
}

uint8 CheckNMEARawData2Part3_MsgNWM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonNMEARawData2Part3.ucMsgTimeout = cNMEARawData2Part3_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_NMEARawData2Part3_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_NMEARawData2Part3_MsgMissing);
    tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout = cNMEARawData2Part3_SIG_TOUT;
   }
   return CheckNMEARawData2Part3_SignalNWM(self, GNSSErrorAltitudeMeters);
}

uint8 CheckUHRZEIT_DATUM_MsgNWM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type timeDate){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   return ( CheckUHRZEIT_DATUM_SignalNWM(self, timeDate));
}

uint8 CheckWMOM_DRV_4_MsgNWM(Rte_Instance self, Rdci_WMOM_DRV_4_Type wmom){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   tNwMonitoring.tMonWMOM_DRV_4.ucMsgTimeout = cWMOM_DRV_4_MSG_TOUT;
   if(bGetNetworkErrorNWM(cNetwork_WMOM_DRV_4_MsgMissing) == TRUE){
    ClearNetworkErrorNWM(self, cNetwork_WMOM_DRV_4_MsgMissing);
    tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout = cWMOM_DRV_4_SIG_TOUT;
   }
   return CheckWMOM_DRV_4_SignalNWM(self, wmom);
}

uint8 CheckFZZSTD_MsgNWM( Rdci_ST_ILK_ERRM_FZM_Type fzzstd){
   uint8 ucRetVal = cNoError;
   if((fzzstd == ST_ILK_ERRM_FZM_Reserve)
   || (fzzstd == ST_ILK_ERRM_FZM_SignalUngueltig)){
      ucRetVal = cSignalError;
   }
   return ucRetVal;
}

uint8 CheckKILOMETERSTAND_MsgNWM(Rte_Instance self, Rdci_MILE_KM_Type mileKm){
   if(bGetBandmodeBM() == TRUE){
    return cNoError;
   }
   return CheckKILOMETERSTAND_SignalNWM(self, mileKm);
}

uint32 ulGetNetworkErrorsNWM(void){
   return FilterSubsequentErrorsNWM(ulNetworkErrors);
}

uint32 ulGetNetworkErrChangedFlagsNWM(void){
   return ulNetworkErrChangedFlags;
}

void ClearNetworkErrorNWM(Rte_Instance self, uint32 ulDtcBit){
   if((ulNetworkErrors & ulDtcBit) == ulDtcBit){
      ulNetworkErrors ^= ulDtcBit;
    PUTulNwmErrorsEE(self, ulNetworkErrors);
   }
}

void ClearNetworkErrChangedFlagNWM(uint32 ulDtcBit){
   if((ulNetworkErrChangedFlags & ulDtcBit) == ulDtcBit){
      ulNetworkErrChangedFlags ^= ulDtcBit;
   }
}

void ClearNetworkErrChangedFlagsNWM(void){
   ulNetworkErrChangedFlags = cNetworkNoError;
}

boolean bGetNetworkErrorNWM(uint32 ulDtcBit){
   if((ulNetworkErrors & ulDtcBit) == ulDtcBit){
    return TRUE;
   }
   else{
    return FALSE;
   }
}

void SetNetworkErrorNWM(Rte_Instance self, uint32 ulDtcBit){
   if((ulNetworkErrors & ulDtcBit) == 0){
      ulNetworkErrors |= ulDtcBit;
    PUTulNwmErrorsEE(self, ulNetworkErrors);
   }
}

void ClearErrorConditionsNWM(uint8 ucParamToClear){
   switch(ucParamToClear){
      case cPTC_A_TEMP_Missing:
    tNwMonitoring.tMonA_TEMP.ucMsgTimeout = cA_TEMP_MSG_TOUT;
      break;

      case cPTC_A_TEMP_Signal:
    tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout = cA_TEMP_SIG_TOUT;
      break;

      case cPTC_CON_VEH_Alive:
    tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter = 0;
      break;

      case cPTC_CON_VEH_Crc:
    tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter = 0;
      break;

      case cPTC_CON_VEH_Signal:
    tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter = 0;
      break;

      case cPTC_CON_VEH_Missing:
    tNwMonitoring.tMonCON_VEH.ucMsgTimeout = cCON_VEH_MSG_TOUT;
      break;

      case cPTC_EINHEITEN_Missing:
    tNwMonitoring.tMonEINH_BN2020.ucMsgTimeout = cEINHEITEN_BN2020_MSG_TOUT;
      break;

      case cPTC_EINHEITEN_Signal:
    tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter = 0;
      break;

      case cPTC_RELATIVZEIT_Missing:
    tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout = cBN2020_RELATIVZEIT_MSG_TOUT;
      break;

      case cPTC_RELATIVZEIT_Signal:
    tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout = cBN2020_RELATIVZEIT_SIG_TOUT;
      break;

      case cPTC_RDC_DT_Missing:
    tNwMonitoring.tMonRDC_DT_PCKG[0].ushMsgTimeout = cRDC_DT_PCKG12_MSG_TOUT;
    tNwMonitoring.tMonRDC_DT_PCKG[1].ushMsgTimeout = cRDC_DT_PCKG12_MSG_TOUT;
      break;

      case cPTC_RDC_DT_Signal:
    tNwMonitoring.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;
    tNwMonitoring.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;
      break;

      case cPTC_RDC_DT_Alive:
    tNwMonitoring.tMonRDC_DT_PCKG[0].ucAliveErrorCounter = 0;
    tNwMonitoring.tMonRDC_DT_PCKG[0].ucAlvErrGoodCounter = 0;
    tNwMonitoring.tMonRDC_DT_PCKG[1].ucAliveErrorCounter = 0;
    tNwMonitoring.tMonRDC_DT_PCKG[1].ucAlvErrGoodCounter = 0;
      break;

      case cPTC_V_VEH_Alive:
    tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout = cV_VEH_ALIVE_TOUT;
      break;

      case cPTC_V_VEH_Crc:
    tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout = cV_VEH_CRC_TOUT;
      break;

      case cPTC_V_VEH_Missing:
    tNwMonitoring.tMonV_VEH.ucMsgTimeout = cV_VEH_MSG_TOUT;
      break;

      case cPTC_V_VEH_SigQualif:
    tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout = cV_VEH_SIGQUALIF_TOUT;
      break;

      default:
      break;
   }
}

static uint8 CheckRDC_DT_PCKG12_AliveNWM(Rte_Instance self, uint8 ucAlive1, uint8 ucAlive2, uint8 DpNo){
   static uint8 ucLastAlive[2] = { 0x0Fu,0x0Fu };
   uint8 ucRetVal = cNoError;
   uint8 DpIx;
   boolean bAliveHasError;
   if(0x34 == DpNo){
    DpIx = cDataPackage34Ix;
   }
   else{
    DpIx = cDataPackage12Ix;
   }

   if((ucAlive1 != 0xf) && (ucAlive2 != 0xf)){
      if((ucAlive1 == ucAlive2) && (ucAlive1 != ucLastAlive[DpIx])){
      bAliveHasError = FALSE;
      ucLastAlive[DpIx] = ucAlive1;
      }
      else{
      bAliveHasError = TRUE;
      }
   }
   else{
    bAliveHasError = TRUE;
   }
   if(bAliveHasError == TRUE){
      ucRetVal = cAliveError;
    tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAlvErrGoodCounter = 0;
      if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_AliveError) == FALSE){
      if((bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == FALSE) && (ucGetStatusConditionVehicleFZZ() >= ST_CON_VEH_Pruefen_Analyse_Diagnose)){
          if(tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAliveErrorCounter < cRDC_DT_PCKG12_ALV_CNT){
          tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAliveErrorCounter++;
          if(tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAliveErrorCounter == cRDC_DT_PCKG12_ALV_CNT){
            SetNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_AliveError);
            SetDataPackageErrorIndNWM(cDP_AE_SHIFT, DpIx);
          }
        }
      }
      }
   }
   else{
      ucRetVal = cNoError;
    tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAliveErrorCounter = 0;
      if(bGetNetworkErrorNWM(cNetwork_RDC_DT_PCKG_AliveError) == TRUE){
      if(tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAlvErrGoodCounter < cRDC_DT_PCKG12_ALV_GOOD_CNT){
        tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAlvErrGoodCounter++;
          if(tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ucAlvErrGoodCounter == cRDC_DT_PCKG12_ALV_GOOD_CNT){
          if(ResetDataPackageErrorIndNWM(self, cDP_AE_SHIFT, DpIx) == TRUE){
            ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_AliveError);
          }
        }
      }
      }
      else{
      (void)ResetDataPackageErrorIndNWM(self, cDP_AE_SHIFT, DpIx);
      }
   }
   return ucRetVal;
}

static uint8 CheckRDC_DT_PCKG12_SignalNWM(Rte_Instance self, uint16 ushRdcMesTstmp, uint8 DpNo){
   uint8 ucRetVal = cSignalError;
   uint8 DpIx;
   if(0x34 == DpNo){
    DpIx = cDataPackage34Ix;
   }
   else{
    DpIx = cDataPackage12Ix;
   }
   if(ushRdcMesTstmp != 0xffffU){
    tNwMonitoring.tMonRDC_DT_PCKG[DpIx].ushSignalErrorTimeout = cRDC_DT_PCKG12_SIG_TOUT;
      if(ResetDataPackageErrorIndNWM(self, cDP_SE_SHIFT, DpIx) == TRUE){
      ClearNetworkErrorNWM(self, cNetwork_RDC_DT_PCKG_SignalError);
      }
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckA_TEMP_SignalNWM(Rte_Instance self, Rdci_TEMP_EX_Type tempEx){
   uint8 ucRetVal = cNoError;
   if(tempEx >= 0xfbu){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonA_TEMP.ucSignalErrorTimeout = cA_TEMP_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_A_TEMP_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckEINHEITEN_BN2020_SignalNWM(Rte_Instance self, Rdci_UN_AIP_Type unitAip, Rdci_UN_TEMP_Type unitTemp){
   uint8 ucRetVal = cNoError;
   if((unitAip == ePRESSURE_UNIT_INVALID) || (unitAip == 4) || (unitAip == 5) || (unitAip == 6)
    || (unitTemp == eTEMPERATURE_UNIT_INVALID)){
      ucRetVal = cSignalError;
      if(tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter < cEINHEITEN_BN2020_SIG_CNT){
      if((bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == FALSE) && (ucGetStatusConditionVehicleFZZ() >= ST_CON_VEH_Pruefen_Analyse_Diagnose)){
        tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter++;
          if(tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter == cEINHEITEN_BN2020_SIG_CNT){
          SetNetworkErrorNWM(self, cNetwork_EINHEITEN_SignalError);
        }
      }
      }
   }
   else{
    tNwMonitoring.tMonEINH_BN2020.ucSignalErrorCounter = 0;
    ClearNetworkErrorNWM(self, cNetwork_EINHEITEN_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckCON_VEH_SignalNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh){
   uint8 ucRetVal = cNoError;
   boolean bSignalIsBad = FALSE;
   if((conVeh.ST_CON_VEH == ST_CON_VEH_Signal_unbefuellt)
    || (conVeh.ST_CON_VEH == ST_CON_VEH_reserviert_0)
    || (conVeh.ST_CON_VEH == ST_CON_VEH_reserviert_13)
    || (conVeh.ST_CON_VEH == ST_CON_VEH_reserviert_14)
    || (conVeh.ST_CON_VEH == 4)
    || (conVeh.ST_CON_VEH == 6)
    || (conVeh.ST_CON_VEH == 9)
    || (conVeh.ST_CON_VEH == 11)
    ){
    bSignalIsBad = TRUE;
   }
   else if(conVeh.ST_CON_VEH == ST_CON_VEH_Fahren){
      if((conVeh.QU_ST_CON_VEH != QU_ST_CON_VEH_SignalwertGueltig)
      && (conVeh.QU_ST_CON_VEH != QU_ST_CON_VEH_SignalwertEingeschraenktGueltig)){
      bSignalIsBad = TRUE;
      }
      else{
      bSignalIsBad = FALSE;
      }
   }
   else{
    bSignalIsBad = FALSE;
   }
   if(bSignalIsBad == TRUE){
      ucRetVal = cSignalError;
      if(tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter < cCON_VEH_SIG_CNT){
      if(bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == FALSE){
        tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter++;
          if(tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter == cCON_VEH_SIG_CNT){
          SetNetworkErrorNWM(self, cNetwork_CON_VEH_SignalError);
        }
      }
      }
   }
   else{
    tNwMonitoring.tMonCON_VEH.ucSignalErrorCounter = 0;
    ClearNetworkErrorNWM(self, cNetwork_CON_VEH_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckCON_VEH_CrcNWM(Rte_Instance self, Rdci_CON_VEH_Type conVeh){
   uint8 ucRetVal = cNoError;
   if((conVeh.CRC_CON_VEH != E2E_STATUS_OK) && (conVeh.CRC_CON_VEH != E2E_STATUS_NO_NEW_DATA)){
      ucRetVal = cCrcError;
      if(tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter < cCON_VEH_CRC_CNT){
      if(bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == FALSE){
        tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter++;
          if(tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter == cCON_VEH_CRC_CNT){
          SetNetworkErrorNWM(self, cNetwork_CON_VEH_CrcError);
        }
      }
      }
   }
   else{
    tNwMonitoring.tMonCON_VEH.ucCrcErrorCounter = 0;
    ClearNetworkErrorNWM(self, cNetwork_CON_VEH_CrcError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckCON_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive){
   static uint8 ucLastAlive = 0xf;
   uint8 ucRetVal = cNoError;
   if((ucAlive == 0xf) || (ucAlive == ucLastAlive)){
      ucRetVal = cAliveError;
      if(tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter < cCON_VEH_ALV_CNT){
      if(bGetBitFahrzeugzustandFZZ(cNW_DTC_LOCKED) == FALSE){
        tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter++;
          if(tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter == cCON_VEH_ALV_CNT){
          SetNetworkErrorNWM(self, cNetwork_CON_VEH_AliveError);
        }
      }
      }
   }
   else{
    tNwMonitoring.tMonCON_VEH.ucAliveErrorCounter = 0;
    ClearNetworkErrorNWM(self, cNetwork_CON_VEH_AliveError);
      ucLastAlive = ucAlive;
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckV_VEH_SigQualifNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh){
   uint8 ucRetVal = cNoError;
   boolean bSignalIsBad = FALSE;
   if(vVeh.V_VEH_COG == 0xffffu){
    bSignalIsBad = TRUE;
   }
   else{
      if((vVeh.QU_V_VEH_COG != QU_V_VEH_COG_SignalwertIstGueltigUndAbgesichertUndPlausib52XXOP)
     && (vVeh.QU_V_VEH_COG != QU_V_VEH_COG_SignalwertIstGueltigZustandSlashStatusTemporaer)
     && (vVeh.QU_V_VEH_COG != QU_V_VEH_COG_SignalqualitaetBzwDotUeberwachungEingeschraeYWPFL4)
     ){
      bSignalIsBad = TRUE;
      }
   }
   if(bSignalIsBad == TRUE){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonV_VEH.ucSigQualifErrorTimeout = cV_VEH_SIGQUALIF_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_V_VEH_SigQualifError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckV_VEH_CrcNWM(Rte_Instance self, Rdci_V_VEH_Type vVeh){
   uint8 ucRetVal = cNoError;
   if((vVeh.CRC_V_VEH != E2E_STATUS_OK) && (vVeh.CRC_V_VEH != E2E_STATUS_NO_NEW_DATA)){
      ucRetVal = cCrcError;
   }
   else{
    tNwMonitoring.tMonV_VEH.ucCrcErrorTimeout = cV_VEH_CRC_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_V_VEH_CrcError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckV_VEH_AliveNWM(Rte_Instance self, uint8 ucAlive){
   static uint8 ucLastAlive = 0xf;
   uint8 ucRetVal = cNoError;
   if((ucAlive == 0xf) || (ucAlive == ucLastAlive)){
      ucRetVal = cAliveError;
   }
   else{
    tNwMonitoring.tMonV_VEH.ucAliveErrorTimeout = cV_VEH_ALIVE_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_V_VEH_AliveError);
      ucLastAlive = ucAlive;
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckBN2020_RELATIVZEIT_SignalNWM(Rte_Instance self, Rdci_T_SEC_COU_REL_Type relTime){
   uint8 ucRetVal = cNoError;
   if(relTime == 0xffffffffU){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonRELATIVZEIT.ucSignalErrorTimeout = cBN2020_RELATIVZEIT_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_RELATIVZEIT_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckWMOM_DRV_4_SignalNWM(Rte_Instance self, Rdci_WMOM_DRV_4_Type wmom){
   uint8 ucRetVal = cNoError;
   if((wmom.ST_DRVDIR_DVCH == 0x01) || (wmom.ST_DRVDIR_DVCH == 0x03) || (wmom.ST_DRVDIR_DVCH > GEAR_REVERSE)){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonWMOM_DRV_4.ucSignalErrorTimeout = cWMOM_DRV_4_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_WMOM_DRV_4_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckDT_PT_1_SignalNWM(Rte_Instance self, Rdci_AIP_ENG_DRV_Type aip){
   uint8  ucRetVal = cNoError;
   if((aip == 0) || (aip == 0xffu)){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonDT_PT_1.ucSignalErrorTimeout = cDT_PT_1_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_DT_PT_1_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckNMEARawData2Part2_SignalNWM(Rte_Instance self, Rdci_GNSSPositionAltitude_Type GNSSPositionAltitude){
   uint8 ucRetVal = cNoError;
   if(GNSSPositionAltitude > (Rdci_GNSSPositionAltitude_Type) 65530){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonNMEARawData2Part2.ucSignalErrorTimeout = cNMEARawData2Part2_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_NMEARawData2Part2_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckNMEARawData2Part3_SignalNWM(Rte_Instance self, Rdci_GNSSErrorAltitudeMeters_Type GNSSErrorAltitudeMeters){
   uint8 ucRetVal = cNoError;
   if(GNSSErrorAltitudeMeters > (Rdci_GNSSErrorAltitudeMeters_Type) 65000){
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonNMEARawData2Part3.ucSignalErrorTimeout = cNMEARawData2Part3_SIG_TOUT;
    ClearNetworkErrorNWM(self, cNetwork_NMEARawData2Part3_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckUHRZEIT_DATUM_SignalNWM(Rte_Instance self, Rdci_UHRZEIT_DATUM_Type timeDate){
   uint8 ucRetVal = cNoError;
   if((timeDate.DISP_DATE_DAY < 1)
  ||  (timeDate.DISP_DATE_DAY > 31)
  ||  (timeDate.DISP_DATE_MON < 1)
  ||  (timeDate.DISP_DATE_MON > 12)
  ||  (timeDate.DISP_DATE_WDAY < 1)
  ||  (timeDate.DISP_DATE_WDAY > 7)
  ||  (timeDate.DISP_DATE_YR == 0xffffu)
  ||  (timeDate.DISP_HR > 23)
  ||  (timeDate.DISP_MN > 59)
  ||  (timeDate.DISP_SEC > 59)
  ||  (timeDate.ST_DISP_CTI_DATE == 0xf)
  ){
      if(tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout == cUHRZEIT_DATUM_SIG_TOUT_OFF){
      tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout = cUHRZEIT_DATUM_SIG_TOUT;
      }
      ucRetVal = cSignalError;
   }
   else{
    tNwMonitoring.tMonUHRZEIT_DATUM.ushSignalErrorTimeout = cUHRZEIT_DATUM_SIG_TOUT_OFF;
    ClearNetworkErrorNWM(self, cNetwork_UHRZEIT_DATUM_SignalError);
      ucRetVal = cNoError;
   }
   return ucRetVal;
}

static uint8 CheckKILOMETERSTAND_SignalNWM(Rte_Instance self, Rdci_MILE_KM_Type mileKm){
   uint8 ucRetVal = cNoError;
   if(mileKm != 0xffffffU){
    tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout = cKILOMETERSTAND_SIG_TOUT_OFF;
    ClearNetworkErrorNWM(self, cNetwork_KILOMETERSTAND_SignalError);
      ucRetVal = cNoError;
   }
   else{
      if(tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout == cKILOMETERSTAND_SIG_TOUT_OFF){
      tNwMonitoring.tMonKILOMETERSTAND.ushSignalErrorTimeout = cKILOMETERSTAND_SIG_TOUT;
      }
      ucRetVal = cSignalError;
   }
   return ucRetVal;
}

static uint32 FilterSubsequentErrorsNWM(uint32 ulErrorBits){
   uint32 ulRetVal = ulErrorBits;
   static uint32 ulLastErrorState = 0;
   uint32 ulChanges;
   if((ulErrorBits & cNetwork_RDC_DT_PCKG_MsgMissing) == cNetwork_RDC_DT_PCKG_MsgMissing){
      ulRetVal &= ~(cNetwork_RDC_DT_PCKG_AliveError | cNetwork_RDC_DT_PCKG_SignalError);
   }
   if((ulErrorBits & cNetwork_A_TEMP_MsgMissing) == cNetwork_A_TEMP_MsgMissing){
      ulRetVal &= ~ cNetwork_A_TEMP_SignalError;
   }
   if((ulErrorBits & cNetwork_EINHEITEN_MsgMissing) == cNetwork_EINHEITEN_MsgMissing){
      ulRetVal &= ~ cNetwork_EINHEITEN_SignalError;
   }
   if((ulErrorBits & cNetwork_CON_VEH_MsgMissing) == cNetwork_CON_VEH_MsgMissing){
      ulRetVal &= ~ (cNetwork_CON_VEH_CrcError | cNetwork_CON_VEH_AliveError | cNetwork_CON_VEH_SignalError);
   }
   if((ulErrorBits & cNetwork_RELATIVZEIT_MsgMissing) == cNetwork_RELATIVZEIT_MsgMissing){
      ulRetVal &= ~ cNetwork_RELATIVZEIT_SignalError;
   }
   if((ulErrorBits & cNetwork_V_VEH_MsgMissing) == cNetwork_V_VEH_MsgMissing){
      ulRetVal &= ~ cNetwork_V_VEH_CrcError;
      ulRetVal &= ~ cNetwork_V_VEH_AliveError;
      ulRetVal &= ~ cNetwork_V_VEH_SigQualifError;
   }
   ulChanges = ulLastErrorState ^ ulRetVal;
   ulNetworkErrChangedFlags |= ulChanges;
   ulLastErrorState = ulRetVal;
   return ulRetVal;
}

boolean bPrio1ErrorIsSetNWM(void){
   boolean bRetVal = FALSE;
   uint32 ulPrio1Errors =    cNetwork_RDC_DT_PCKG_MsgMissing
                          | cNetwork_RDC_DT_PCKG_AliveError
                          | cNetwork_RDC_DT_PCKG_SignalError
                          | cNetwork_V_VEH_AliveError
                          | cNetwork_V_VEH_CrcError
                          | cNetwork_V_VEH_MsgMissing
                          | cNetwork_V_VEH_SigQualifError;
   if((ulNetworkErrors & ulPrio1Errors) == 0){
    bRetVal = FALSE;
   }
   else{
    bRetVal = TRUE;
   }
   return bRetVal;
}

boolean bRdcDataErrorIsSetNWM(void){
   boolean bRetVal = FALSE;
   uint32 ulRdcDataErrors =   cNetwork_RDC_DT_PCKG_MsgMissing
                           | cNetwork_RDC_DT_PCKG_AliveError
                           | cNetwork_RDC_DT_PCKG_SignalError;
   if((ulNetworkErrors & ulRdcDataErrors) == 0){
    bRetVal = FALSE;
   }
   else{
    bRetVal = TRUE;
   }
   return bRetVal;
}

boolean bSystemErrorIsSetNWM(void){
   boolean bSystemError = FALSE;
   if(bGetWheelUnitErrorWUM(cAllocGatewayOrAntennaError) == TRUE){
    bSystemError = TRUE;
   }
   else{
    bSystemError = bPrio1ErrorIsSetNWM();
   }
   return bSystemError;
}

boolean bRelativzeitMessageFailNWM(void){
   if((cBN2020_RELATIVZEIT_MSG_TOUT - tNwMonitoring.tMonRELATIVZEIT.ucMsgTimeout) > 2){
    return TRUE;
   }
   else{
    return FALSE;
   }
}

boolean ResetDataPackageErrorIndNWM(Rte_Instance self, uint8 ShiftValue, uint8 Ix){
   boolean bRet = FALSE;
   uint8 ucMask;
   if((Ix < 2) && (ShiftValue <= cDP_TO_SHIFT)){
      ucDpErrInd &= (uint8)((uint8)(0x01 << ((2 * ShiftValue) + Ix)) ^ 0xFF);
      if(GETucFBD4CountEE(self) > 1){
      ucMask = cDP_DUALERROR_MASK;
      }
      else{
      ucMask = cDP_SINGLERROR_MASK;
      }
      if((ucDpErrInd & (uint8)(ucMask << (2 * ShiftValue))) == 0){
      bRet = TRUE;
      }
   }
   return(bRet);
}

void SetDataPackageErrorIndNWM(uint8 ShiftValue, uint8 Ix){
   if((Ix < 2) && (ShiftValue <= cDP_TO_SHIFT)){
      ucDpErrInd |= (uint8)(0x01 << ((2 * ShiftValue)+Ix));
   }
}

uint8 GetDataPackageErrorIndNWM(Rte_Instance self, uint8 ShiftValue){
   uint8 ucRet = 0x00;
   if(ShiftValue <= cDP_TO_SHIFT){
      if((ucDpErrInd & (uint8)(0x01 << (2 * ShiftValue))) != 0){
      ucRet = 0x01;
      }
      if(GETucFBD4CountEE(self) > 1){
      if((ucDpErrInd & (uint8)(0x01 << ((2 * ShiftValue) + 1))) != 0){
        ucRet |= 0x02;
      }
      }
   }
   return(ucRet);
}

void GetNwMonitoringDataNWM(tNwMonitoringData* data){
  *data = tNwMonitoring;
}
