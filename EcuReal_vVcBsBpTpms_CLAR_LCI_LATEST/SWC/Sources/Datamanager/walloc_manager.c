#include "walloc_manager.h"
#include "datamanagerX.h"
#include "InitializationX.h"
#include "state_fzzX.h"
#include "state_bzX.h"
#include "State_ZKX.h"
#include "abs_linX.h"
#include "wallocX.h"
#include "FPA_X.h"
#include "eRFS_X.h"
#include "RID_X.h"
#include "uswarn_ifX.h"
#include "EeHistoryBlockX.h"
#include "EeDiagBlockX.h"
#include "EeErfsBlockX.h"
#include "EeCommonBlockX.h"
#include "EeWarnstatusBlockX.h"
#include "EeZomBlockX.h"
#include "WuMonitoringX.h"
#include "Hs_KalibrierereignisX.h"
#include "Hs_WarnereignisX.h"
#include "StatusbarX.h"
#include "rdctsaservicesX.h"
#include "BandmodeX.h"
#include "CodingDataX.h"
#include "DebugMsgX.h"

static uint8  ucWatoTimeoutValue = ucDefWATOTime;
static uint8  ucWatoState = WATO_STATE_STOP;
static boolean bErAndZoAtOnce = TRUE;
static uint16 ushCountInvalidAbsTstmp = 0;
static uint8  ucCountInvalidRdcTstmp = 0;
static uint16 ushAbsTicks[4];
static uint8  ucCalOnErFinish = cCalOnErFinishIsInactive;
static uint8  ucTGCountAtCalOnErFinish[cMaxLR] = {0xffu, 0xffu, 0xffu, 0xffu};

void SetVehicleSpeedWAM(Rte_Instance self, Rdci_V_VEH_Type vspeed)
{
  uint16 ushSpeed;

  SetDrivingDirectionWAM();

  ushSpeed = vspeed.V_VEH_COG >> 6;
  SETSpeedFZZ(ushSpeed);

  CountDrivenKilometersWithWarningDS(self);
}

void SetGearWAM(Rdci_WMOM_DRV_4_Type wmomDriveInfo)
{
  if(wmomDriveInfo.ST_DRVDIR_DVCH != 0xf)
  {
    SetGearFZZ(wmomDriveInfo.ST_DRVDIR_DVCH);
    SetDrivingDirectionWAM();
  }
}

static void SetDrivingDirectionWAM(void)
{
  static uint8  ucResetAbsRef = cResRefPoint_NoAction;

  if((GETucGearFZZ() == GEAR_REVERSE))
  {
    SetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
    ucResetAbsRef |= cResRefPoint_DDBackOk;

    if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
    {
      ucResetAbsRef |= cResetRefPoint_SpeedOk;
    }
  }

  else
  {
    ClearBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
    if(ucResetAbsRef == (cResRefPoint_DDBackOk | cResetRefPoint_SpeedOk))
    {
      ReNewABSRef();
    }
    ucResetAbsRef = cResRefPoint_NoAction;
  }
}

void SetAbsDataWAM(ImpTypeRecCddAbsData absData)
{
	uint32 ulTempTimeStmp;
  #if(WORKAROUND_STBMB == 1)
  uint32 ulTempLO, ulTempHI;
  #endif
  uint16 ushTimeStmp;

  uint8 ucCheckAbsQualifier;

  if((absData.ABS_SYNC_TSTMP_LO == 0xffffffffu) && (absData.ABS_SYNC_TSTMP_HI == 0xffffffffu))
  {

    if(ushCountInvalidAbsTstmp < 0xffffu)
    {
      ushCountInvalidAbsTstmp++;
    }
  }

  else
  {

    #if(WORKAROUND_STBMB == 1)
      ulTempLO = (uint32)((uint32)absData.ABS_SYNC_TSTMP_LO >> 2);
      ulTempLO = ulTempLO / (uint32)1000000;
      ulTempHI = (uint32)((uint32)absData.ABS_SYNC_TSTMP_HI * (uint32)1000);
      ulTempTimeStmp = ulTempHI + ulTempLO;
    #else
      ulTempTimeStmp = ((uint32)(absData.ABS_SYNC_TSTMP_HI * (uint32)1000) + (uint32)(absData.ABS_SYNC_TSTMP_LO / (uint32)1000000));
    #endif
      ushTimeStmp = (uint16)(ulTempTimeStmp & 0xffffU);

    #ifdef ABS_SIG_SIZE_ONEBYTE
	    ushTESTABStick[0] = (uint8)tWheelPlsMsg.WhlPlsCnt_FL;
	    ushTESTABStick[1] = (uint8)tWheelPlsMsg.WhlPlsCnt_FR;
	    ushTESTABStick[2] = (uint8)tWheelPlsMsg.WhlPlsCnt_RL;
	    ushTESTABStick[3] = (uint8)tWheelPlsMsg.WhlPlsCnt_RR;
    #else
	    ushAbsTicks[0] = absData.ABS_EDGE_CNT_FL;
	    ushAbsTicks[1] = absData.ABS_EDGE_CNT_FR;
	    ushAbsTicks[2] = absData.ABS_EDGE_CNT_RL;
	    ushAbsTicks[3] = absData.ABS_EDGE_CNT_RR;
    #endif

    ucCheckAbsQualifier = 0;
    if(absData.ABS_QU_SIG_FL == 0)
    {
      ucCheckAbsQualifier++;
    }
    if(absData.ABS_QU_SIG_FR == 0)
    {
      ucCheckAbsQualifier++;
    }
    if(absData.ABS_QU_SIG_RL == 0)
    {
      ucCheckAbsQualifier++;
    }
    if(absData.ABS_QU_SIG_RR == 0)
    {
      ucCheckAbsQualifier++;
    }

    if(ucCheckAbsQualifier == cMaxLR)
    {

      PutABS(ushTimeStmp, ushAbsTicks);

      if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == FALSE)
      {
        EnableRollDetectionABS();
      }
      else
      {
        DisableRollDetectionABS();
      }
    }
  }
}

void ProcessAllocationWAM(Rte_Instance self, ImpTypeRecCddRdcData rdcData)
{
  uint32      ulTempTimeStmp;
  #if(WORKAROUND_STBMB == 1)
  uint32 ulTempLO, ulTempHI;
  #endif
  uint16      ushTimeStmp, ushlookBackTime;
  tRFTelType  inputWA;
  boolean     bUseTelegramForWalloc = FALSE;

  inputWA.Header.ucTType = rdcData.PCKG_ID;
  inputWA.Header.ulID = (uint32)((uint32)rdcData.TYR_ID | ((uint32)rdcData.SUPP_ID << 28));

  inputWA.Header.ucAvg = rdcData.RDC_DT_7;

  if(bLearningWheelPosActiveWAM(cFAHRZEUG_LERNT) == TRUE)
  {

    #if(WORKAROUND_STBMB == 1)
    ulTempLO = (uint32)((uint32)rdcData.RDC_SYNC_TSTMP_LO >> 2);
    ulTempLO = ulTempLO / (uint32)1000000;
    ulTempHI = (uint32)((uint32)rdcData.RDC_SYNC_TSTMP_HI * (uint32)1000);
    ulTempTimeStmp = ulTempHI + ulTempLO;
    #else
    ulTempTimeStmp = ((uint32)((uint32)rdcData.RDC_SYNC_TSTMP_HI * (uint32)1000) + (uint32)((uint32)rdcData.RDC_SYNC_TSTMP_LO / (uint32)1000000));
    #endif
    ushTimeStmp = (uint16)(ulTempTimeStmp & 0xffffU);

    if((rdcData.PCKG_ID == cTelTypeSELPAL) || (rdcData.PCKG_ID == cTelTypeSELPAL1))
    {

      inputWA.SchraderFP.ucP = rdcData.RDC_DT_1;
      inputWA.SchraderFP.ucT = rdcData.RDC_DT_2;
      inputWA.SchraderFP.ucPAL = rdcData.RDC_DT_3;
      inputWA.SchraderFP.ushStatusField = ((uint16)rdcData.RDC_DT_4 << 8) + rdcData.RDC_DT_5;
      inputWA.SchraderFP.ucCRC8 = rdcData.RDC_DT_8;

      if((rdcData.RDC_SYNC_TSTMP_LO == 0xffffffffu) && (rdcData.RDC_SYNC_TSTMP_HI == 0xffffffffu))
      {
        inputWA.SchraderFP.ucPAL = 0xff;
        if(ucCountInvalidRdcTstmp < 255)
        {
          ucCountInvalidRdcTstmp++;
        }
      }

      if((rdcData.RDC_MES_TSTMP / 10) > cMaxTelegramRetention)
      {
        inputWA.SchraderFP.ucPAL = 0xff;
      }

      if((inputWA.SchraderFP.ucPAL >= 2) && (inputWA.SchraderFP.ucPAL < 255))
      {

        ushlookBackTime = (rdcData.RDC_DT_3 - 2) * 5;
        ushlookBackTime += rdcData.RDC_MES_TSTMP / 10;

	      if(ushTimeStmp < ushlookBackTime)
	      {
		      (void)ucLinABS(((0xFFFFU - ushlookBackTime) + ushTimeStmp) + 1);
	      }
	      else
	      {
		      (void)ucLinABS(ushTimeStmp - ushlookBackTime);
	      }
      }

      bUseTelegramForWalloc = TRUE;
    }

    else if(rdcData.PCKG_ID == cTelTypeContiFP)
    {

      inputWA.ContiFP.ucP = rdcData.RDC_DT_1;
      inputWA.ContiFP.ucT = rdcData.RDC_DT_2;
      inputWA.ContiFP.ucBat = rdcData.RDC_DT_3;
      inputWA.ContiFP.ucAcc = rdcData.RDC_DT_4;
      inputWA.ContiFP.ucModeNCode = rdcData.RDC_DT_5;
      inputWA.ContiFP.ucCRC8 = rdcData.RDC_DT_8;

      if((rdcData.RDC_SYNC_TSTMP_LO == 0xffffffffu) && (rdcData.RDC_SYNC_TSTMP_HI == 0xffffffffu))
      {
        inputWA.ContiFP.ucModeNCode = cLocSyncNoAngleNoFrame;
        if(ucCountInvalidRdcTstmp < 255)
        {
          ucCountInvalidRdcTstmp++;
        }
      }

	    if((rdcData.RDC_MES_TSTMP / 10) > cMaxTelegramRetention)
      {
        inputWA.ContiFP.ucModeNCode &= cLocSyncNoAngleNoFrame;
      }

      if(((inputWA.ContiFP.ucModeNCode & cLocSyncAngleMask) == cLocSyncAngle1)
        || ((inputWA.ContiFP.ucModeNCode & cLocSyncAngleMask) == cLocSyncAngle2))
      {
        ushlookBackTime = rdcData.RDC_MES_TSTMP / 10;

        if(ushTimeStmp < ushlookBackTime)
	      {
		      (void)ucLinABS(((0xFFFFU - ushlookBackTime) + ushTimeStmp) + 1);
	      }
	      else
	      {
		      (void)ucLinABS(ushTimeStmp - ushlookBackTime);
	      }
      }

      bUseTelegramForWalloc = TRUE;
    }

    else if((rdcData.PCKG_ID == cTelTypeAK35def) || (rdcData.PCKG_ID == cTelTypeAK35defLMA) || (rdcData.PCKG_ID == cTelTypeBeruLong)
          || (rdcData.PCKG_ID == cTelTypeBeruMed) || (rdcData.PCKG_ID == cTelTypeG4Standard))
    {

      inputWA.AK35def.ucPressure = rdcData.RDC_DT_1;
      inputWA.AK35def.ucTemperature = rdcData.RDC_DT_2;
      inputWA.AK35def.ucCRC8 = rdcData.RDC_DT_8;

      bUseTelegramForWalloc = TRUE;
    }

    else
    {
      bUseTelegramForWalloc = FALSE;
    }

    if(bUseTelegramForWalloc == TRUE)
    {
      SetLearnStateWAM(self, ucLearnID(self, &inputWA));
    }
  }

  else
  {
  }

  (void) CreateSetOfEventSpecificDataDBG(&rdcData);
  SetStatusBarActivityToGoSBR();
}

static boolean bLearningWheelPosActiveWAM(uint8 ucSpeedThreshold)
{
  boolean bLearnActive = FALSE;
  boolean bSpeedCondition = FALSE;

  if((bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == TRUE) && (ucSpeedThreshold == cFAHRZEUG_LERNT))
  {
    bSpeedCondition = TRUE;
  }
  else if((bGetBitFahrzeugzustandFZZ(cRS_VTHRES) == TRUE) && (ucSpeedThreshold == cRS_VTHRES))
  {
    bSpeedCondition = TRUE;
  }
  else {}

  if(ucGetStatusConditionVehicleFZZ() != ST_CON_VEH_Fahren)
  {
    bLearnActive = FALSE;
  }

  else if(bGetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT) == TRUE)
  {
    bLearnActive = FALSE;
  }

  else if(bGetBandmodeBM() == TRUE)
  {
    bLearnActive = FALSE;
  }

  else if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
  {
    bLearnActive = FALSE;
  }

  else if(bGetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE) == TRUE)
  {
    bLearnActive = FALSE;
  }

  else if(bGetBitBetriebszustandBZ(cLOC_INTERRUPTED) == TRUE)
  {
    bLearnActive = FALSE;
  }

  else if(bSpeedCondition == TRUE)
  {
	  if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE)
	  {
	    bLearnActive = TRUE;
    }
    else
    {
      bLearnActive = FALSE;
	  }
  }
  else
  {
	  bLearnActive = FALSE;
  }

  return( bLearnActive);
}

static void SetLearnStateWAM(Rte_Instance self, uint8 ucWAState){
   uint8 i;
   if((bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE) && ((ucWAState & cWAStateZO) == cWAStateZO)){
      if(cWAStateER == (ucWAState & cWAStateER)){
         SetBitBetriebszustandBZ(cEIGENRAD | cZUGEORDNET);
         SetBitBetriebszustandBZ(cZO_FINISH | cER_FINISH);
         SetAutoLearnErrorStatusWUM(self, cAUTOLEARN_SUCCESSFUL);
         ClearBitBetriebszustandBZ(cTEILEIGENRAD);
         (void) ucSetAutolocErrorStatusWUM(self, cAUTOLOC_SUCCESSFUL);
         SetHistoryChangeBitsDM(self);
         (void)NewPositionsUSWIF(self);
         (void)ucCfgPSollMinUSWIF(self);
         if(TRUE == bErAndZoAtOnce){
            if(ucGetIdChangedBitsZK() > 0){
               ResetWUM(self, ucGetIdChangedBitsZK(), cWithoutLowBat, cWithoutWuRelatedDtcs);
               DeleteRidDataOfHisColRID(self, 0x0F);
               CopyPressAndTempFromZOMDM(self);
               if(TRUE == GETTyreSelectionActiveEE(self)){
                  (void) ErPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cEIGENRAD), TRUE);
               }
            }
            for(i=0; i<cMaxLR; i++){
               ClearMuteWUM(self, i, i);
            }
         }
         SwitchUnspecificToSpecificErrorsWUM(self);
         PUTucLastPosChangedInformationToNvmMirrorEE(self, ucGetIdChangedBitsZK() | ucGetWpChangedBitsZK());
         PUTLastLocStateEE(self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
         SetStWheelTypeChangedAtLocDM(ucGetIdChangedBitsZK(), ucGetWpChangedBitsZK());
         SaveRidDataAndCompareRID(self);
         i = GETTyreSelectionBckgrdEE(self);
         i |= GETTyreSelectionActiveEE(self);
         if(TRUE == i){
            SetSolldruckDM(self, GETSelectedLoadStateEE(self), GETSelectedTyreIndexEE(self));
            (void) ZoPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cZUGEORDNET), GETSelectedTyreIndexEE(self));
            (void) SaveCalibrationEventDS(self);
            PUTTyreSelectionActiveEE(self, FALSE);
            if(FALSE == bGetBitBetriebszustandBZ(cZWANGSZUORDNUNG)){
               if(0x00 == GETucPermutationStateFromNvmEE(self)){
                  PUTTyreSelectionBckgrdEE(self, FALSE);
               }
            }
         }
         else{
            CheckTyreChangedDM(self);
         }
      }
   }
   else if(FALSE == (bGetBitBetriebszustandBZ(cER_FINISH)) && (cWAStateER == (ucWAState & cWAStateER))){
      SetBitBetriebszustandBZ(cEIGENRAD);
      SetBitBetriebszustandBZ(cER_FINISH);
      SetAutoLearnErrorStatusWUM(self, cAUTOLEARN_SUCCESSFUL);
      if(TRUE == bGetBitBetriebszustandBZ(cTEILEIGENRAD)){
         ClearHistoryWPs(self);
         SwitchSpecificToUnspecificErrorsWUM(self);
         for(i=0; i<cMaxLR; i++){
            ClearMuteWUM(self, i, i);
         }
         ClearBitBetriebszustandBZ(cTEILEIGENRAD);
      }
      bErAndZoAtOnce = FALSE;
      (void) NewPositionsUSWIF(self);
      (void) ucCfgPSollMinUSWIF(self);
      if((ucWAState & 0xf0u) > 0){
         SetHistoryChangeBitsDM(self);
         ResetWUM(self, ucGetIdChangedBitsZK(), cWithLowBat, cWithoutWuRelatedDtcs);
         DeleteRidDataOfHisColRID(self, 0x0F);
         if(ucNrOfBitSet8(ucGetIdChangedBitsZK()) > 1){
            ClearBitBetriebszustandBZ(cZUGEORDNET);
            SwitchSpecificToUnspecificErrorsWUM(self);
            (void)ucSetPminFzgAsSetPressureUSWIF(self);
         }
         CopyPressAndTempFromZOMDM(self);
      }
      PUTucLastPosChangedInformationToNvmMirrorEE(self, ucGetIdChangedBitsZK());
      PUTLastLocStateEE(self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
      if(TRUE == GETTyreSelectionActiveEE(self)){
         (void) ErPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cEIGENRAD), TRUE);
      }
      else{
         if(FALSE == GETTyreSelectionBckgrdEE(self)){
            CheckTyreChangedDM(self);
         }
         else{
            ReStorePinitTinitDM(self);
         }
      }
   }
   else{
   }
   if(TRUE == bGetBitBetriebszustandBZ(cER_FINISH)){
      if(FALSE == bGetLocalisationPossibilityWUM()){
         SetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE);
         ClearHistoryWPs(self);
         ClearBitBetriebszustandBZ(cZUGEORDNET);
         SwitchSpecificToUnspecificErrorsWUM(self);
         SetWheelUnitErrorWUM(self, cAllocWuLocalisationFailed);
         PUTLastLocStateEE(self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
         if(TRUE == GETTyreSelectionActiveEE(self)){
            (void)SaveCalibrationEventDS(self);
            PUTTyreSelectionActiveEE(self, FALSE);
         }
      }
      else if(cWAStateBreak == (ucWAState & cWAStateBreak)){
         SetBitBetriebszustandBZ(cLOC_INTERRUPTED);
         SaveRidDataAndCompareRID(self);
         if(TRUE == GETTyreSelectionActiveEE(self)){
            SetSolldruckDM(self, GETSelectedLoadStateEE(self), GETSelectedTyreIndexEE(self));
            (void) ZoPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cZUGEORDNET), GETSelectedTyreIndexEE(self));
            (void)NewPositionsUSWIF(self);
            (void)ucCfgPSollMinUSWIF(self);
            (void)SaveCalibrationEventDS(self);
            PUTTyreSelectionActiveEE(self, FALSE);
         }
      }
      else{
         if(TRUE == GETTyreSelectionActiveEE(self)){
            ProcessCalOnErFinishWAM();
            if(cCalOnErFinishTriggerPlausi == ucCalOnErFinish){
               (void) ErPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cEIGENRAD), TRUE);
               ucCalOnErFinish = cCalOnErFinishIsInactive;
            }
         }
      }
   }
}

void WatoTickWAM(Rte_Instance self){
   uint8 ucWaErrorCode;
   uint8 ucOpenWheelPositions = 0;
   if(TRUE == bLearningWheelPosActiveWAM(cFAHRZEUG_LERNT)){
      TickAbsoluteLearnTimerWAL();
      TickSingleRELearnTimerWAL();
   }
   switch(ucWatoState){
      case WATO_STATE_HALT:
         if(TRUE == bLearningWheelPosActiveWAM(cRS_VTHRES)){
            ucWatoState = WATO_STATE_RUN;
         }
         break;

      case WATO_STATE_RUN:
         if(FALSE == bLearningWheelPosActiveWAM(cRS_VTHRES)){
            ucWatoState = WATO_STATE_HALT;
         }
         break;

      case WATO_STATE_STOP:
      default:
         return;
         break;
   }
   if(WATO_STATE_RUN == ucWatoState){
      ucWatoTimeoutValue--;
      PUTWatoEE(self, ucWatoTimeoutValue);
      PutWATOTimeWAL(ucWatoTimeoutValue);
      if(0 == ucWatoTimeoutValue){
         ucWatoState = WATO_STATE_STOP;
         ucWaErrorCode = ucWATO(self, &ucOpenWheelPositions);
         if(ucWaErrorCode > 0){
            SetBitBetriebszustandBZ(cZO_TIMEOUT);
            if(0x01 == (ucWaErrorCode & 0x01)){
               SetAutoLearnErrorStatusWUM(self, cAUTOLEARN_FAILED);
               if(0x08 == (ucWaErrorCode & 0x08)){
                  if(ucOpenWheelPositions > 0){
                     SetHistoryChangeBitsDM(self);
                     ResetWUM(self, ucGetIdChangedBitsZK(), cWithLowBat, cWithoutWuRelatedDtcs);
                     ClearWheelUnitErrorWUM(self, cAllocUnspecifiedWuMute);
                     if(0x01 == (ucOpenWheelPositions & 0x01)){SetWheelUnitErrorWUM(self, cAllocWuMuteFl);}
                     if(0x02 == (ucOpenWheelPositions & 0x02)){SetWheelUnitErrorWUM(self, cAllocWuMuteFr);}
                     if(0x04 == (ucOpenWheelPositions & 0x04)){SetWheelUnitErrorWUM(self, cAllocWuMuteRl);}
                     if(0x08 == (ucOpenWheelPositions & 0x08)){SetWheelUnitErrorWUM(self, cAllocWuMuteRr);}
                     ClearBitBetriebszustandBZ(cZUGEORDNET);
                     SetBitBetriebszustandBZ(cTEILEIGENRAD);
                  }
               }
               else if(0x10 == (ucWaErrorCode & 0x10)){
               }
               else if(0x04 == (ucWaErrorCode & 0x04)){
                  SetBitBetriebszustandBZ(cTOO_MUCH_RE);
               }
               else{
               }
            }
            else if(0x02 == (ucWaErrorCode & 0x02)){
               if((ucGetHistoryState() & (cHiStateZG | cHiStateER)) != (cHiStateZG | cHiStateER)){
                  SetWheelUnitErrorWUM(self, cAllocWuLocalisationFailed);
               }
               else{
                  if(ucSetAutolocErrorStatusWUM(self, cAUTOLOC_FAILED) < cXCLOC_FALSE){
                  }
                  else{
                     ClearHistoryWPs(self);
                     ClearBitBetriebszustandBZ(cZUGEORDNET);
                     SwitchSpecificToUnspecificErrorsWUM(self);
                  }
               }
            }
            else{
            }
            PUTLastLocStateEE(self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
            SaveRidDataAndCompareRID(self);
            if(TRUE == GETTyreSelectionActiveEE(self)){
               SetSolldruckDM(self, GETSelectedLoadStateEE(self), GETSelectedTyreIndexEE(self));
               (void) ErPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cEIGENRAD), TRUE);
               (void) ZoPlausiInitPressINIT(self, bGetBitBetriebszustandBZ(cZUGEORDNET), GETSelectedTyreIndexEE(self));
               (void)SaveCalibrationEventDS(self);
               PUTTyreSelectionActiveEE(self, FALSE);
            }
         }
         else{
            SetBitBetriebszustandBZ(cZWANGSZUORDNUNG);
            SetLearnStateWAM(self, ucGetWAState());
         }
      }
   }
}

void WatoRunWAM(Rte_Instance self, boolean bRestart)
{
  if(bRestart == cWatoRestart)
  {
    ucWatoTimeoutValue = ucDefWATOTime;
    PUTWatoEE(self, ucWatoTimeoutValue);
    PutWATOTimeWAL(ucWatoTimeoutValue);
  }
  else
  {
    ucWatoTimeoutValue = GETWatoEE(self);
    PutWATOTimeWAL(ucWatoTimeoutValue);
  }

  if(bLearningWheelPosActiveWAM(cRS_VTHRES) == TRUE)
  {
    ucWatoState = WATO_STATE_RUN;
  }
  else
  {
    ucWatoState = WATO_STATE_HALT;
  }
}

void WatoStopWAM(void)
{
  ucWatoState = WATO_STATE_STOP;
}

void StartLearnLocateWAM(Rte_Instance self)
{
  PUTLastLocStateEE(self, 0);
  ClearBitBetriebszustandBZ(cER_FINISH | cZO_FINISH);

  ClearBitBetriebszustandBZ(cTOO_MUCH_RE | cZO_TIMEOUT | cLOC_NOT_POSSIBLE | cZWANGSZUORDNUNG | cLOC_INTERRUPTED);

  bErAndZoAtOnce = TRUE;
  ClearIdChangedBitsZK();
  ClearWpChangedBitsZK();

  (void)InitWAL(self, cRestartLearnLocate);
  SetAllocMinDeltaValueFPA(ucGetCRdciLearnLocateConfigCD(0));
  SetAllocAbsoluteMinValueFPA(ucGetCRdciLearnLocateConfigCD(1));
  WatoRunWAM(self, cWatoRestart);

  ucCalOnErFinish = cCalOnErFinishIsInactive;
}

void ContinueLocateWAM(Rte_Instance self)
{
  SetbackLocateProbeCountersWAL();
  ClearReDriveModeStateWAL();
  ClearBitBetriebszustandBZ(cLOC_INTERRUPTED);
  WatoRunWAM(self, cWatoRestart);
  StartCalOnErFinishWAM();
}

void ContinueLearnWAM(Rte_Instance self)
{
  SetbackLearnProbeCountersWAL();
  ClearReDriveModeStateWAL();
  ClearBitBetriebszustandBZ(cLOC_INTERRUPTED);
  WatoRunWAM(self, cWatoRestart);
}

uint16 ushGetWatoTimeoutValueWAM(void)
{
  return (uint16)ucWatoTimeoutValue * 5;
}

static void StartCalOnErFinishWAM(void)
{
  uint8 i;

  for (i=0; i<cMaxLR; i++)
  {
    ucTGCountAtCalOnErFinish[i] = ucGetZomAbsoluteProbeCt(i);
  }
  ucCalOnErFinish = cCalOnErFinishIsActive;
}

static void ProcessCalOnErFinishWAM(void)
{
  uint8 i;

  if(ucCalOnErFinish != cCalOnErFinishIsInactive)
  {
    for (i=0; i<cMaxLR; i++)
    {
      if((ucGetZomAbsoluteProbeCt(i) - ucTGCountAtCalOnErFinish[i]) >= 1)
      {
        ucCalOnErFinish |= (uint8)(1<<i);
      }
    }
  }
}

boolean bAllocationIsActive(Rte_Instance self)
{
  boolean bRetVal = FALSE;
  if(GETLastLocStateEE(self) == (cZO_FINISH | cER_FINISH))
  {
    bRetVal = FALSE;
  }
  else
  {
    if(bLearningWheelPosActiveWAM(cFAHRZEUG_LERNT) == TRUE)
    {
      bRetVal = TRUE;
    }
  }
  return bRetVal;
}

uint16 ushGetInvalidAbsTstmpCounterWAM(void)
{
  return ushCountInvalidAbsTstmp;
}

uint8 ucGetInvalidRdcTstmpCounterWAM(void)
{
  return ucCountInvalidRdcTstmp;
}

uint16* GetPointerToAbsCountersWAM(void)
{
  return ushAbsTicks;
}

