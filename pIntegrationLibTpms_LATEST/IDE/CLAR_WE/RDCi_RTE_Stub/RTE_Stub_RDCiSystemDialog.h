#ifndef __RTE_STUB_RDCI_TASK_CONTROL_DIALOG_H
#define __RTE_STUB_RDCI_TASK_CONTROL_DIALOG_H

private: System::Void timerRDCiCyclicTask_Tick(System::Object^  sender, System::EventArgs^  e)
{
  uint8  ucWarnVectorId[cAnzRad];
  uint8  ucWarnVectorWt[ucMaxWarnTypeWNc];
  uint32 ulWarnOut;
  uint8  ucHistCol;
  uint8  ucSetLevel, ucResetLevel;
  uint8  ucLoop;
  uint8  ucPress, ucPcold, ucPwarm, ucPist_t, ucPamb, ucPsollCold, ucPsollWarm, ucPsoll_t;
  sint8  scTemp, scTcold, scTwarm, scTsollCold, scTist_t;
  uint8  ucTimState;
  uint16 ushTimCnt, ushMSoll;
  uint16 ushTemp1,ushTemp2;
  uint32 ulTemp;
  uint16 ushElapsedCoolingTime, ushTimeTicks;
  uint32 ulCoolingCaptTime;

  uint8 ucMarket;
  uint8 ucPlacard;

  static uint32 ulTimerTicks = 0;
  static uint8 ucTime1Second = 0;
  static uint16 ushTime30Second = 0;
  static uint8 ucTime100msecond = 0;

  static boolean bFklIsYellow = FALSE;
  static uint8   ucUwbRdcPosition = 0xff;
  static uint8 ToggleDpNo = 0;

  uint8 ucRefPresDHW;
  uint8 ucLastPresDHW;
  uint16 ushTimCntDHW;
  uint16 ushTimCountLatchDHW;

  uint8 ucDeltaTinitTh;
  uint8 ucDeltaTinitHyst;
  uint32 ulTinitOatTimeTicks;
  uint32 ulTinitOatTime;
  uint32 ulOATHelp = 0x00;
  boolean bCorrTinitEvent;

  uint8  ucTimerState;
  uint16 ushTimerCounter;

  uint8 aucNvmWriteAttemptCounters[cAttemptCounterSize];

  uint8 ucDtcNo;

  tCddRdcData * ptData;

  uint8 ucAliveCounterValue1, ucAliveCounterValue2;

  uint8 ucWheelPos = 0;
  uint8 aucDbgMsg[32];
  uint16* pushAbsCounters;

  tNwMonitoringData tNwMonData;

  Rdci_TAR_P_TYR_FLH_Type     TAR_P_TYR;
  Rdci_AVL_P_TYR_FLH_Type     AVL_P_TYR;
  Rdci_AVL_TEMP_TYR_FLH_Type  AVL_T_TYR;

  String^ sLabelPressureUnit;
  String^ sLabelTemperatureUnit;

  ImpTypeValFrBusState myBusState;
  Rdci_ST_ILK_ERRM_FZM_Type myFzzstd;
  Rdci_UHRZEIT_DATUM_Type myUhrzeitDatum;

  ulTimerTicks++;
  PutTimerTicks( ulTimerTicks);

  uint8  ucAipEngDrv;
  uint16 ushPositionAltitude;
  uint16 ushErrorAltitudeMeters;
  uint16 ushGpsTioTicks;
  uint8  ucAipGpsState;
  sint16 sshAltMeter;

  uint8   ucPermState;
  uint8 * pucNewWheelPosOfId;

  boolean bColor = FALSE;

  if(++ushTime30Second >= (30000 / timerRDCiCyclicTask->Interval))
  {
    if(checkBoxSendCyclicAliveTelegrams->Checked == TRUE)
    {

      ptData = ptGetRecCddRdcDataPtr( cRecEleIx_Alive);

      ucAliveCounterValue1 = ucGetNextValidAliveCounter( ptData->ALIV_RDC_DT_PCK_1);

      if( checkBoxAliveError->Checked == true)
      {
        ucAliveCounterValue2 = ucGetNextValidAliveCounter( ucAliveCounterValue1);
      }else{
        ucAliveCounterValue2 = ucAliveCounterValue1;
      }

      ptData->ALIV_RDC_DT_PCK_1 = ucAliveCounterValue1;
      ptData->ALIV_RDC_DT_PCK_2 = ucAliveCounterValue2;

      srand((uint16)(ulTimerTicks & 0xffff));

      ptData->RDC_DT_4 = ((uint16)rand()) % 20;
      if(ToggleDpNo == 0)
      {
      ptData->RDC_DT_6++;

      if(ptData->RDC_DT_6 == 0xfe)
      {
        ptData->RDC_DT_6 = 0x00;
      }

        ptData->DP_NO = 0x34;
        ToggleDpNo = 1;
      }
      else
      {
        ptData->DP_NO = 0x12;
        ToggleDpNo = 0;
      }

      PutRecCddRdcData( cRecEleIx_Alive);

      for( ucLoop = 0; ucLoop <= cAnzRad; ucLoop++)
      {
        ptData = ptGetRecCddRdcDataPtr( ucLoop);
        ptData->ALIV_RDC_DT_PCK_1 = ucAliveCounterValue1;
        ptData->ALIV_RDC_DT_PCK_2 = ucAliveCounterValue2;
      }

      textBoxCountFBD4Alive->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_Alive));

      if( radioButtonFBD4Alive->Checked == true)
      {
        numericUpDownDt4PalStatusHi->Value  = ptData->RDC_DT_4;
        numericUpDownDt6->Value             = ptData->RDC_DT_6;
      }

      numericUpDownAlive1->Value          = ptData->ALIV_RDC_DT_PCK_1;
      numericUpDownAlive2->Value          = ptData->ALIV_RDC_DT_PCK_2;

      if( TabRdcData->Visible == true)
      {
        if( radioButtonFBD4Alive->Checked == true)
        {

          panelREInputDataFrame->Visible = false;
          panelREInputDataFrame->Visible = true;
        }
      }
    }

    ushTime30Second = 0;
  }

  if(++ucTime1Second >= (1000 / timerRDCiCyclicTask->Interval))
  {

    if(ucGetColOfWP(0) < 4)
    { labelMuteFlTimerValue->Text = System::String::Format("{0} (FL)", ushGetMuteTimerValueWUM(ucGetColOfWP(0))); }
    else
    { labelMuteFlTimerValue->Text = System::String::Format("{0} (Slot 0)", ushGetMuteTimerValueWUM(0));              }

    if(ucGetColOfWP(1) < 4)
    { labelMuteFrTimerValue->Text = System::String::Format("{0} (FR)", ushGetMuteTimerValueWUM(ucGetColOfWP(1))); }
    else
    { labelMuteFrTimerValue->Text = System::String::Format("{0} (Slot 1)", ushGetMuteTimerValueWUM(1));              }

    if(ucGetColOfWP(2) < 4)
    { labelMuteRlTimerValue->Text = System::String::Format("{0} (RL)", ushGetMuteTimerValueWUM(ucGetColOfWP(2))); }
    else
    { labelMuteRlTimerValue->Text = System::String::Format("{0} (Slot 2)", ushGetMuteTimerValueWUM(2));              }

    if(ucGetColOfWP(3) < 4)
    { labelMuteRrTimerValue->Text = System::String::Format("{0} (RR)", ushGetMuteTimerValueWUM(ucGetColOfWP(3))); }
    else
    { labelMuteRrTimerValue->Text = System::String::Format("{0} (Slot 3)", ushGetMuteTimerValueWUM(3));              }

    if(ucGetColOfWP(0) < 4)
    { labelLoBatCounterFL->Text = System::String::Format("{0}", ucGetLoBatCounterValueWUM(ucGetColOfWP(0))); }
    else
    { labelLoBatCounterFL->Text = System::String::Format("no WP"); }

    if(ucGetColOfWP(1) < 4)
    { labelLoBatCounterFR->Text = System::String::Format("{0}", ucGetLoBatCounterValueWUM(ucGetColOfWP(1))); }
    else
    { labelLoBatCounterFR->Text = System::String::Format("no WP"); }

    if(ucGetColOfWP(2) < 4)
    { labelLoBatCounterRL->Text = System::String::Format("{0}", ucGetLoBatCounterValueWUM(ucGetColOfWP(2))); }
    else
    { labelLoBatCounterRL->Text = System::String::Format("no WP"); }

    if(ucGetColOfWP(3) < 4)
    { labelLoBatCounterRR->Text = System::String::Format("{0}", ucGetLoBatCounterValueWUM(ucGetColOfWP(3))); }
    else
    { labelLoBatCounterRR->Text = System::String::Format("no WP"); }

    labelGatewayTimerValue->Text = System::String::Format("{0}", ushGetGatewayAntennaTimerValueWUM());

    GetNwMonitoringDataNWM(&tNwMonData);

    labelConVehTimerValue->Text = System::String::Format("{0} sec", tNwMonData.tMonCON_VEH.ucMsgTimeout);
    labelATempTimerValue->Text = System::String::Format("{0} sec", tNwMonData.tMonA_TEMP.ucMsgTimeout);
    labelBn2020TimerValue->Text = System::String::Format("{0} sec", tNwMonData.tMonEINH_BN2020.ucMsgTimeout);
    if(tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout < tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout)
    {
      labelRdcDataTimerValue->Text = System::String::Format("{0} sec", tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout);
    }
    else
    {
      labelRdcDataTimerValue->Text = System::String::Format("{0} sec", tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout);
    }
    if(tNwMonData.tMonRDC_DT_PCKG[0].ucAliveErrorCounter < tNwMonData.tMonRDC_DT_PCKG[1].ucAliveErrorCounter)
    {
      labelRdcDataAliveCounter->Text = System::String::Format("{0}", tNwMonData.tMonRDC_DT_PCKG[0].ucAliveErrorCounter);
    }
    else
    {
      labelRdcDataAliveCounter->Text = System::String::Format("{0}", tNwMonData.tMonRDC_DT_PCKG[1].ucAliveErrorCounter);
    }

    labelRelativzeitTimeoutValue->Text = System::String::Format("{0} sec", tNwMonData.tMonRELATIVZEIT.ucMsgTimeout);

    GetNvmWriteAttemptCounters((uint8*)aucNvmWriteAttemptCounters);
    textBoxDiagBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cDiagBlock1] + aucNvmWriteAttemptCounters[cDiagBlock2]);
    textBoxHistoryBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cHistoBlock]);
    textBoxErfsBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cErfsBlock]);
    textBoxErfsEcoBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cErfsEcoBlock]);
    textBoxWarnstatusBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cWarnstatusBlock]);
    textBoxErfsTsaBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cErfsTsaBlock]);
    textBoxRidQrBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cRidQrBlock1] + aucNvmWriteAttemptCounters[cRidQrBlock2]);
    textBoxZomBlockSaveCounter->Text = System::String::Format("{0}", aucNvmWriteAttemptCounters[cZomblock1] + aucNvmWriteAttemptCounters[cZomblock2]);

    if(checkFRBusState->Checked == TRUE)
    {
      myBusState = FR_STATE_ACTIVE;
    }
    else
    {
      myBusState = FR_STATE_INACTIVE;
    }
    PutBusState(&myBusState);

    if(radioButtonFZZSTDFree->Checked == TRUE)
    {
      myFzzstd = ST_ILK_ERRM_FZM_Fehlerspeicherfreigabe;
    }
    else if(radioButtonFZZSTDLocked->Checked == TRUE)
    {
      myFzzstd = ST_ILK_ERRM_FZM_Fehlerspeichersperre;
    }
    else if(radioButtonFZZSTDInvalid->Checked == TRUE)
    {
      myFzzstd = ST_ILK_ERRM_FZM_SignalUngueltig;
    }
    PutStIlkErrmFzm( &myFzzstd);

    if( (ucGetActualStateWL() & 0x01) != 0)
    {

      if( (ucGetActualStateWL() & 0x30) == 0)
      {

        buttonFKL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
        buttonFKL->Text = "fKL";
        bFklIsYellow = TRUE;
      }else{

        buttonFKL->Text = System::String::Format("{0} sec", ushGetBlinkingTimeWL() / 10);

        if( bFklIsYellow == FALSE)
        {
          buttonFKL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
          bFklIsYellow = TRUE;
        }else{
          buttonFKL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          bFklIsYellow = FALSE;
        }
      }
    }else{

      buttonFKL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
      buttonFKL->Text = "fKL";
      bFklIsYellow = FALSE;
    }

    ucTime1Second = 0;

  }

  if(ucTime100msecond++ >= (100 / timerRDCiCyclicTask->Interval))
  {

    for( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++)
    {
      if( tRDCiDtclist[ucLoop].ucUwbUpdateState == TRUE)
      {
        ReadDtcUwbData( ucLoop);
      }

      switch ( ucLoop)
      {
        case cDemErrorRdciRfExternalInterference:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48069B->Enabled = false;
          }else{
            radioButton0x48069B->Enabled = true;
          }
        break;

        case cDemErrorRdciAutoLearningFailed:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48069E->Enabled = false;
          }else{
            radioButton0x48069E->Enabled = true;
          }
        break;

        case cDemErrorRdci4WrongWuMounted:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806A1->Enabled = false;
          }else{
            radioButton0x4806A1->Enabled = true;
          }
        break;

        case cDemErrorRdci1To3WrongWuMounted:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806A6->Enabled = false;
          }else{
            radioButton0x4806A6->Enabled = true;
          }
        break;

        case cDemErrorRdciWuMuteFl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806B8->Enabled = false;
          }else{
            radioButton0x4806B8->Enabled = true;
          }
        break;

        case cDemErrorRdciWuMuteFr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806DA->Enabled = false;
          }else{
            radioButton0x4806DA->Enabled = true;
          }
        break;

        case cDemErrorRdciWuMuteRl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806F0->Enabled = false;
          }else{
            radioButton0x4806F0->Enabled = true;
          }
        break;

        case cDemErrorRdciWuMuteRr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806F4->Enabled = false;
          }else{
            radioButton0x4806F4->Enabled = true;
          }
        break;

        case cDemErrorRdciWuDefectFl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4806FA->Enabled = false;
          }else{
            radioButton0x4806FA->Enabled = true;
          }
        break;

        case cDemErrorRdciWuDefectFr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480702->Enabled = false;
          }else{
            radioButton0x480702->Enabled = true;
          }
        break;

        case cDemErrorRdciWuDefectRl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48070F->Enabled = false;
          }else{
            radioButton0x48070F->Enabled = true;
          }
        break;

        case cDemErrorRdciWuLocalisationFailed:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48071F->Enabled = false;
          }else{
            radioButton0x48071F->Enabled = true;
          }
        break;

        case cDemErrorRdciWuDefectRr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480728->Enabled = false;
          }else{
            radioButton0x480728->Enabled = true;
          }
        break;

        case cDemErrorRdciWuLowBatteryFl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48077C->Enabled = false;
          }else{
            radioButton0x48077C->Enabled = true;
          }
        break;

        case cDemErrorRdciWuLowBatteryFr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48077D->Enabled = false;
          }else{
            radioButton0x48077D->Enabled = true;
          }
        break;

        case cDemErrorRdciWuLowBatteryRl:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48077E->Enabled = false;
          }else{
            radioButton0x48077E->Enabled = true;
          }
        break;

        case cDemErrorRdciWuLowBatteryRr:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x48077F->Enabled = false;
          }else{
            radioButton0x48077F->Enabled = true;
          }
        break;

        case cDemErrorRdciTpmsManufactoryMode:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480780->Enabled = false;
          }else{
            radioButton0x480780->Enabled = true;
          }
        break;

        case cDemErrorRdciUnspecifiedWfcDefect:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4809EA->Enabled = false;
          }else{
            radioButton0x4809EA->Enabled = true;
          }
        break;

        case cDemErrorRdciUnspecifiedWuMute:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x4809EB->Enabled = false;
          }else{
            radioButton0x4809EB->Enabled = true;
          }
        break;

        case cDemErrorRdciGatewayOrAntennaError:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480A46->Enabled = false;
          }else{
            radioButton0x480A46->Enabled = true;
          }
        break;

        case cDemErrorRdciOtherWuSensorType:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480ACD->Enabled = false;
          }else{
            radioButton0x480ACD->Enabled = true;
          }
        break;

        case cDemErrorRdciErfsCodingDataInconsistent:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480ACE->Enabled = false;
          }else{
            radioButton0x480ACE->Enabled = true;
          }
        break;

        case cDemErrorRdciAusfall:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480ACF->Enabled = false;
          }else{
            radioButton0x480ACF->Enabled = true;
          }
        break;

        case cDemErrorRdciBefuellhinweis:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480AD0->Enabled = false;
          }else{
            radioButton0x480AD0->Enabled = true;
          }
        break;

        case cDemErrorRdciDruckwarnung:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480AD1->Enabled = false;
          }else{
            radioButton0x480AD1->Enabled = true;
          }
        break;

        case cDemErrorRdciPannenwarnung:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480AD2->Enabled = false;
          }else{
            radioButton0x480AD2->Enabled = true;
          }
        break;

        case cDemErrorRdciWarnruecknahme:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480AD3->Enabled = false;
          }else{
            radioButton0x480AD3->Enabled = true;
          }
        break;

        case cDemErrorRdciKalibrierung:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480AD4->Enabled = false;
          }else{
            radioButton0x480AD4->Enabled = true;
          }
        break;

        case cDemErrorRdciPartialSystemAvailability:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480B02->Enabled = false;
          }else{
            radioButton0x480B02->Enabled = true;
          }
        break;

        case cDemErrorRdciSystemNotAvailable:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0x480B03->Enabled = false;
          }else{
            radioButton0x480B03->Enabled = true;
          }
        break;

        case cDemErrorRdciATempTimeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35428->Enabled = false;
          }else{
            radioButton0xD35428->Enabled = true;
          }
        break;

        case cDemErrorRdciATempInvalid:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3542C->Enabled = false;
          }else{
            radioButton0xD3542C->Enabled = true;
          }
        break;

        case cDemErrorRdciVVehCogInvalid:

          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD354BE->Enabled = false;
          }else{
            radioButton0xD354BE->Enabled = true;
          }
        break;

        case cDemErrorRdciConVehCrc:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD354FF->Enabled = false;
          }else{
            radioButton0xD354FF->Enabled = true;
          }
        break;

        case cDemErrorRdciConVehAlive:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35565->Enabled = false;
          }else{
            radioButton0xD35565->Enabled = true;
          }
        break;

        case cDemErrorRdciConVehTimeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3560C->Enabled = false;
          }else{
            radioButton0xD3560C->Enabled = true;
          }
        break;

        case cDemErrorRdciConVehInvalid:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3565E->Enabled = false;
          }else{
            radioButton0xD3565E->Enabled = true;
          }
        break;

        case cDemErrorRdciEinheitenBn2020Timeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3567D->Enabled = false;
          }else{
            radioButton0xD3567D->Enabled = true;
          }
        break;

        case cDemErrorRdciRdcDtPckg1Timeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35694->Enabled = false;
          }else{
            radioButton0xD35694->Enabled = true;
          }
        break;

        case cDemErrorRdciEinheitenBn2020Invalid:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35713->Enabled = false;
          }else{
            radioButton0xD35713->Enabled = true;
          }
        break;

        case cDemErrorRdciRdcDtPckg1Alive:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35720->Enabled = false;
          }else{
            radioButton0xD35720->Enabled = true;
          }
        break;

        case cDemErrorRdciRdcDtPckg1Invalid:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35777->Enabled = false;
          }else{
            radioButton0xD35777->Enabled = true;
          }
        break;

        case cDemErrorRdciRelativzeitTimeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD359DF->Enabled = false;
          }else{
            radioButton0xD359DF->Enabled = true;
          }
        break;

        case cDemErrorRdciRelativzeitInvalid:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD35AE9->Enabled = false;
          }else{
            radioButton0xD35AE9->Enabled = true;
          }
        break;

        case cDemErrorRdciVVehTimeout:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3673D->Enabled = false;
          }else{
            radioButton0xD3673D->Enabled = true;
          }
        break;

        case cDemErrorRdciVVehAliveFailure:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3673E->Enabled = false;
          }else{
            radioButton0xD3673E->Enabled = true;
          }
        break;

        case cDemErrorRdciVVehCrcFailure:
          if( tRDCiDtclist[ucLoop].ucStatus == DEM_EVENT_STATUS_PASSED)
          {
            radioButton0xD3673F->Enabled = false;
          }else{
            radioButton0xD3673F->Enabled = true;
          }
        break;
      } /* switch ( ucLoop) */
    } /* for( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++) */

    WriteDtcListToNvmBlock();

    if( tabPageUWB->Visible == true)
    {
      if( radioButton0x48069B->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRfExternalInterference;
      }else if( radioButton0x48069E->Checked == true)
      {
        ucDtcNo = cDemErrorRdciAutoLearningFailed;
      }else if( radioButton0x4806A1->Checked == true)
      {
        ucDtcNo = cDemErrorRdci4WrongWuMounted;
      }else if( radioButton0x4806A6->Checked == true)
      {
        ucDtcNo = cDemErrorRdci1To3WrongWuMounted;
      }else if( radioButton0x4806B8->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuMuteFl;
      }else if( radioButton0x4806DA->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuMuteFr;
      }else if( radioButton0x4806F0->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuMuteRl;
      }else if( radioButton0x4806F4->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuMuteRr;
      }else if( radioButton0x4806FA->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuDefectFl;
      }else if( radioButton0x480702->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuDefectFr;
      }else if( radioButton0x48070F->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuDefectRl;
      }else if( radioButton0x48071F->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuLocalisationFailed;
      }else if( radioButton0x480728->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuDefectRr;
      }else if( radioButton0x48077C->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuLowBatteryFl;
      }else if( radioButton0x48077D->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuLowBatteryFr;
      }else if( radioButton0x48077E->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuLowBatteryRl;
      }else if( radioButton0x48077F->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWuLowBatteryRr;
      }else if( radioButton0x480780->Checked == true)
      {
        ucDtcNo = cDemErrorRdciTpmsManufactoryMode;
      }else if( radioButton0x4809EA->Checked == true)
      {
        ucDtcNo = cDemErrorRdciUnspecifiedWfcDefect;
      }else if( radioButton0x4809EB->Checked == true)
      {
        ucDtcNo = cDemErrorRdciUnspecifiedWuMute;
      }else if( radioButton0x480A46->Checked == true)
      {
        ucDtcNo = cDemErrorRdciGatewayOrAntennaError;
      }else if( radioButton0x480ACD->Checked == true)
      {
        ucDtcNo = cDemErrorRdciOtherWuSensorType;
      }else if( radioButton0x480ACE->Checked == true)
      {
        ucDtcNo = cDemErrorRdciErfsCodingDataInconsistent;
      }else if( radioButton0x480ACF->Checked == true)
      {
        ucDtcNo = cDemErrorRdciAusfall;
      }else if( radioButton0x480AD0->Checked == true)
      {
        ucDtcNo = cDemErrorRdciBefuellhinweis;
      }else if( radioButton0x480AD1->Checked == true)
      {
        ucDtcNo = cDemErrorRdciDruckwarnung;
      }else if( radioButton0x480AD2->Checked == true)
      {
        ucDtcNo = cDemErrorRdciPannenwarnung;
      }else if( radioButton0x480AD3->Checked == true)
      {
        ucDtcNo = cDemErrorRdciWarnruecknahme;
      }else if( radioButton0x480AD4->Checked == true)
      {
        ucDtcNo = cDemErrorRdciKalibrierung;
      }else if( radioButton0x480B02->Checked == true)
      {
        ucDtcNo = cDemErrorRdciPartialSystemAvailability;
      }else if( radioButton0x480B03->Checked == true)
      {
        ucDtcNo = cDemErrorRdciSystemNotAvailable;
      }else if( radioButton0xD35428->Checked == true)
      {
        ucDtcNo = cDemErrorRdciATempTimeout;
      }else if( radioButton0xD3542C->Checked == true)
      {
        ucDtcNo = cDemErrorRdciATempInvalid;
      }else if( radioButton0xD354BE->Checked == true)
      {
        ucDtcNo = cDemErrorRdciVVehCogInvalid;

      }else if( radioButton0xD354FF->Checked == true)
      {
        ucDtcNo = cDemErrorRdciConVehCrc;
      }else if( radioButton0xD35565->Checked == true)
      {
        ucDtcNo = cDemErrorRdciConVehAlive;
      }else if( radioButton0xD3560C->Checked == true)
      {
        ucDtcNo = cDemErrorRdciConVehTimeout;
      }else if( radioButton0xD3565E->Checked == true)
      {
        ucDtcNo = cDemErrorRdciConVehInvalid;
      }else if( radioButton0xD3567D->Checked == true)
      {
        ucDtcNo = cDemErrorRdciEinheitenBn2020Timeout;
      }else if( radioButton0xD35694->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRdcDtPckg1Timeout;
      }else if( radioButton0xD35713->Checked == true)
      {
        ucDtcNo = cDemErrorRdciEinheitenBn2020Invalid;
      }else if( radioButton0xD35720->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRdcDtPckg1Alive;
      }else if( radioButton0xD35777->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRdcDtPckg1Invalid;
      }else if( radioButton0xD359DF->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRelativzeitTimeout;
      }else if( radioButton0xD35AE9->Checked == true)
      {
        ucDtcNo = cDemErrorRdciRelativzeitInvalid;
      }else if( radioButton0xD3673D->Checked == true)
      {
        ucDtcNo = cDemErrorRdciVVehTimeout;
      }else if( radioButton0xD3673E->Checked == true)
      {
        ucDtcNo = cDemErrorRdciVVehAliveFailure;
      }else if( radioButton0xD3673F->Checked == true)
      {
        ucDtcNo = cDemErrorRdciVVehCrcFailure;
      }else{
      }

      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
      {
        label0x1702_SAE_CODE_Value->Text           = "-";
      }else{
        label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                            ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                            ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
      }

      if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
      {
        label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
      }else{
        label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                        ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                        ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                        ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                        ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
      }

      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
      if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
      if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
          (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
      if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
      if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
      if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
    }

    ucTime100msecond = 0;
  }

  TriggerRunnableCyclicRDCiTask();

  /
	HistId0Val -> Text = System::String::Format("{0}", ulGetIDOfColWAL(0));
	HistId1Val -> Text = System::String::Format("{0}", ulGetIDOfColWAL(1));
	HistId2Val -> Text = System::String::Format("{0}", ulGetIDOfColWAL(2));
	HistId3Val -> Text = System::String::Format("{0}", ulGetIDOfColWAL(3));

  ucWheelPos = ucGetWPOfColWAL(0);
  HistPos0Val -> Text = System::String::Format("{0}", ucWheelPos);
  switch (ucWheelPos)
  {
    case 0: labelWPos0 -> Text = "RE 0 (VL)"; break;
    case 1: labelWPos0 -> Text = "RE 0 (VR)"; break;
    case 2: labelWPos0 -> Text = "RE 0 (HL)"; break;
    case 3: labelWPos0 -> Text = "RE 0 (HR)"; break;
    default: labelWPos0 -> Text = "RE 0 (no pos)"; break;
  }

  ucWheelPos = ucGetWPOfColWAL(1);
  HistPos1Val -> Text = System::String::Format("{0}", ucWheelPos);
  switch (ucWheelPos)
  {
    case 0: labelWPos1 -> Text = "RE 1 (VL)"; break;
    case 1: labelWPos1 -> Text = "RE 1 (VR)"; break;
    case 2: labelWPos1 -> Text = "RE 1 (HL)"; break;
    case 3: labelWPos1 -> Text = "RE 1 (HR)"; break;
    default: labelWPos1 -> Text = "RE 1 (no pos)"; break;
  }

  ucWheelPos = ucGetWPOfColWAL(2);
  HistPos2Val -> Text = System::String::Format("{0}", ucWheelPos);
  switch (ucWheelPos)
  {
    case 0: labelWPos2 -> Text = "RE 2 (VL)"; break;
    case 1: labelWPos2 -> Text = "RE 2 (VR)"; break;
    case 2: labelWPos2 -> Text = "RE 2 (HL)"; break;
    case 3: labelWPos2 -> Text = "RE 2 (HR)"; break;
    default: labelWPos2 -> Text = "RE 2 (no pos)"; break;
  }

  ucWheelPos = ucGetWPOfColWAL(3);
  HistPos3Val -> Text = System::String::Format("{0}", ucWheelPos);
  switch (ucWheelPos)
  {
    case 0: labelWPos3 -> Text = "RE 3 (VL)"; break;
    case 1: labelWPos3 -> Text = "RE 3 (VR)"; break;
    case 2: labelWPos3 -> Text = "RE 3 (HL)"; break;
    case 3: labelWPos3 -> Text = "RE 3 (HR)"; break;
    default: labelWPos3 -> Text = "RE 3 (no pos)"; break;
  }

  radioButtonRE0->Text = labelWPos0->Text;
  radioButtonRE1->Text = labelWPos1->Text;
  radioButtonRE2->Text = labelWPos2->Text;
  radioButtonRE3->Text = labelWPos3->Text;

  /

    switch (ucReifentyp)
    {
      case 0: TypVal->Text = "Runflat";    break;
      case 1: TypVal->Text = "Standard";   break;
		  case 2: TypVal->Text = "PAX";        break;
		  default: TypVal->Text = "ContiSeal";  break;
		}

    switch (ucSpeedIndex)
    {
      case 0: GeschwVal  -> Text = "L"; break;
		  case 1: GeschwVal  -> Text = "M"; break;
		  case 2: GeschwVal  -> Text = "N"; break;
		  case 3: GeschwVal  -> Text = "P"; break;
		  case 4: GeschwVal  -> Text = "Q"; break;
		  case 5: GeschwVal  -> Text = "R"; break;
		  case 6: GeschwVal  -> Text = "S"; break;
		  case 7: GeschwVal  -> Text = "T"; break;
		  case 8: GeschwVal  -> Text = "U"; break;
		  case 9: GeschwVal  -> Text = "H"; break;
		  case 10: GeschwVal  -> Text = "V"; break;
		  case 11: GeschwVal  -> Text = "VR"; break;
      case 12: GeschwVal  -> Text = "W"; break;
		  case 13: GeschwVal  -> Text = "ZR"; break;
		  default: GeschwVal  -> Text = "Y"; break;
		}

    switch (ucSaisonVal)
    {
      case 0: SaisonVal  -> Text = "Sommer"; break;
		  case 1: SaisonVal  -> Text = "Winter"; break;
		  default: SaisonVal  -> Text = "AllSeason"; break;
		}
	}
  /
  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 0);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 1);
  ushTemp1 = (((ushTemp1 >> 4) - 6) * 100) + (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Reifenbreite2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 1);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 2);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Querschnitt2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 2);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 3);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Durchmesser2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 3);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 4);
  ushTemp1 = ((uint16)(ushTemp1 & 0x0F) << 3) | (uint16)((ushTemp2 & 0xE0) >> 5);

  textRID_Tragfaehigkeit2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 4);
  ushTemp1 = (ushTemp1 & 0x1F) + 0x40;

  textRID_GeschwIndex2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0xC0) >> 6);

  textRID_Reifentyp2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x0C) >> 2);

  textRID_Saison2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x03));

  textRID_Karkasse2->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 0);
  textRID_DOT2 -> Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 0);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 1);
  ushTemp1 = (((ushTemp1 >> 4) - 6) * 100) + (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Reifenbreite3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 1);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 2);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Querschnitt3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 2);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 3);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Durchmesser3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 3);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 4);
  ushTemp1 = ((uint16)(ushTemp1 & 0x0F) << 3) | (uint16)((ushTemp2 & 0xE0) >> 5);

  textRID_Tragfaehigkeit3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 4);
  ushTemp1 = (ushTemp1 & 0x1F) + 0x40;

  textRID_GeschwIndex3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0xC0) >> 6);

  textRID_Reifentyp3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x0C) >> 2);

  textRID_Saison3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x03));

  textRID_Karkasse3->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 0);
  textRID_DOT3 -> Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 0);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 1);
  ushTemp1 = (((ushTemp1 >> 4) - 6) * 100) + (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Reifenbreite4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 1);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 2);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Querschnitt4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 2);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 3);
  ushTemp1 = (((ushTemp1 & 0x0F) - 6) * 10) + ((ushTemp2 >> 4) - 6);

  textRID_Durchmesser4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 3);
  ushTemp2 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 4);
  ushTemp1 = ((uint16)(ushTemp1 & 0x0F) << 3) | (uint16)((ushTemp2 & 0xE0) >> 5);

  textRID_Tragfaehigkeit4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 4);
  ushTemp1 = (ushTemp1 & 0x1F) + 0x40;

  textRID_GeschwIndex4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0xC0) >> 6);

  textRID_Reifentyp4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x0C) >> 2);

  textRID_Saison4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 5);
  ushTemp1 = (uint16)((ushTemp1 & 0x03));

  textRID_Karkasse4->Text = System::String::Format("{0}", ushTemp1);

  ushTemp1 = GETTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 0);
  textRID_DOT4 -> Text = System::String::Format("{0}", ushTemp1);
  /
              checkBoxPermutationFLcolNewIDrow->Checked = true;
            break;
          }
        break;

        case cRadPosVR:
          switch (pucNewWheelPosOfId[ucLoop])
          {
            case cRadPosVL:
              checkBoxPermutationFRcolFLrow->Checked = true;
              break;

            case cRadPosVR:
              checkBoxPermutationFRcolFRrow->Checked = true;
              break;

            case cRadPosHL:
              checkBoxPermutationFRcolRLrow->Checked = true;
              break;

            case cRadPosHR:
              checkBoxPermutationFRcolRRrow->Checked = true;
              break;

            default:
              checkBoxPermutationFRcolNewIDrow->Checked = true;
              break;
          }
        break;

        case cRadPosHL:
          switch (pucNewWheelPosOfId[ucLoop])
          {
            case cRadPosVL:
              checkBoxPermutationRLcolFLrow->Checked = true;
              break;

            case cRadPosVR:
              checkBoxPermutationRLcolFRrow->Checked = true;
              break;

            case cRadPosHL:
              checkBoxPermutationRLcolRLrow->Checked = true;
              break;

            case cRadPosHR:
              checkBoxPermutationRLcolRRrow->Checked = true;
              break;

            default:
              checkBoxPermutationRLcolNewIDrow->Checked = true;
              break;
          }
        break;

        case cRadPosHR:
          switch (pucNewWheelPosOfId[ucLoop])
          {
            case cRadPosVL:
              checkBoxPermutationRRcolFLrow->Checked = true;
              break;

            case cRadPosVR:
              checkBoxPermutationRRcolFRrow->Checked = true;
              break;

            case cRadPosHL:
              checkBoxPermutationRRcolRLrow->Checked = true;
              break;

            case cRadPosHR:
              checkBoxPermutationRRcolRRrow->Checked = true;
              break;

            default:
              checkBoxPermutationRRcolNewIDrow->Checked = true;
              break;
          }
        break;

        default:
        break;
      }
    }
  }
  else
  {
    checkBoxPermutationFLcolFLrow->Checked = false;
    checkBoxPermutationFRcolFLrow->Checked = false;
    checkBoxPermutationRLcolFLrow->Checked = false;
    checkBoxPermutationRRcolFLrow->Checked = false;
    checkBoxPermutationFLcolFRrow->Checked = false;
    checkBoxPermutationFRcolFRrow->Checked = false;
    checkBoxPermutationRLcolFRrow->Checked = false;
    checkBoxPermutationRRcolFRrow->Checked = false;
    checkBoxPermutationFLcolRLrow->Checked = false;
    checkBoxPermutationFRcolRLrow->Checked = false;
    checkBoxPermutationRLcolRLrow->Checked = false;
    checkBoxPermutationRRcolRLrow->Checked = false;
    checkBoxPermutationFLcolRRrow->Checked = false;
    checkBoxPermutationFRcolRRrow->Checked = false;
    checkBoxPermutationRLcolRRrow->Checked = false;
    checkBoxPermutationRRcolRRrow->Checked = false;
    checkBoxPermutationFLcolNewIDrow->Enabled = false;
    checkBoxPermutationFRcolNewIDrow->Enabled = false;
    checkBoxPermutationRLcolNewIDrow->Enabled = false;
    checkBoxPermutationRRcolNewIDrow->Enabled = false;

    checkBoxPermutationFLcolFLrow->Enabled = false;
    checkBoxPermutationFRcolFLrow->Enabled = false;
    checkBoxPermutationRLcolFLrow->Enabled = false;
    checkBoxPermutationRRcolFLrow->Enabled = false;
    checkBoxPermutationFLcolFRrow->Enabled = false;
    checkBoxPermutationFRcolFRrow->Enabled = false;
    checkBoxPermutationRLcolFRrow->Enabled = false;
    checkBoxPermutationRRcolFRrow->Enabled = false;
    checkBoxPermutationFLcolRLrow->Enabled = false;
    checkBoxPermutationFRcolRLrow->Enabled = false;
    checkBoxPermutationRLcolRLrow->Enabled = false;
    checkBoxPermutationRRcolRLrow->Enabled = false;
    checkBoxPermutationFLcolRRrow->Enabled = false;
    checkBoxPermutationFRcolRRrow->Enabled = false;
    checkBoxPermutationRLcolRRrow->Enabled = false;
    checkBoxPermutationRRcolRRrow->Enabled = false;
    checkBoxPermutationFLcolNewIDrow->Checked = false;
    checkBoxPermutationFRcolNewIDrow->Checked = false;
    checkBoxPermutationRLcolNewIDrow->Checked = false;
    checkBoxPermutationRRcolNewIDrow->Checked = false;
  }

  if( radioButtonRE0->Checked == true)
  {
    ucHistCol = 0;
  }else if(  radioButtonRE1->Checked == true)
  {
    ucHistCol = 1;
  }else if(  radioButtonRE2->Checked == true)
  {
    ucHistCol = 2;
  }else{
    ucHistCol = 3;
  }

  (void) ucGetWarnBitIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnVectorId);
  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    if( (ucWarnVectorId[ucHistCol] & (0x01 << ucLoop)) > 0)
    {
      ucWarnVectorWt[ucLoop] = 0x01;
    }else{
      ucWarnVectorWt[ucLoop] = 0x00;
    }
  }

  (void) ucGetWarnBitTonnageIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnVectorId);
  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    if( (ucWarnVectorId[ucHistCol] & (0x01 << ucLoop)) > 0)
    {
      ucWarnVectorWt[ucLoop] |= 0x02;
    }
  }

  (void) ucGetWarnBitAirMassIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnVectorId);
  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    if( (ucWarnVectorId[ucHistCol] & (0x01 << ucLoop)) > 0)
    {
      ucWarnVectorWt[ucLoop] |= 0x04;
    }
  }

  (void) ucGetWarnVectorIdExtIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnVectorId);
  for( ucLoop = 0; ucLoop < ucMaxWarnTypeWNc; ucLoop++)
  {
    if( (ucWarnVectorId[ucHistCol] & (0x01 << ucLoop)) > 0)
    {
      ucWarnVectorWt[ucLoop] |= 0x10;
    }
  }

  GetWarnThresDM( ucHistCol, cucIX_Ppanne, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_00->Text   = "invalid"; }else{ labelSetLevelWT_00->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_00->Text = "invalid"; }else{ labelResetLevelWT_00->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_00->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[0]);

  GetWarnThresDM( ucHistCol, cucIX_Pmin, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_01->Text   = "invalid"; }else{ labelSetLevelWT_01->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_01->Text = "invalid"; }else{ labelResetLevelWT_01->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_01->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[1]);

  GetWarnThresDM( ucHistCol, cucIX_Pwarn, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_02->Text   = "invalid"; }else{ labelSetLevelWT_02->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_02->Text = "invalid"; }else{ labelResetLevelWT_02->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_02->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[2]);

  GetWarnThresDM( ucHistCol, cucIX_PwarnTol, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_03->Text   = "invalid"; }else{ labelSetLevelWT_03->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_03->Text = "invalid"; }else{ labelResetLevelWT_03->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_03->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[3]);

  GetWarnThresDM( ucHistCol, cucIX_Pvorw, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_04->Text   = "invalid"; }else{ labelSetLevelWT_04->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_04->Text = "invalid"; }else{ labelResetLevelWT_04->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_04->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[4]);

  GetWarnThresDM( ucHistCol, cucIX_5, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_05->Text   = "invalid"; }else{ labelSetLevelWT_05->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_05->Text = "invalid"; }else{ labelResetLevelWT_05->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_05->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[5]);

  GetWarnThresDM( ucHistCol, cucIX_DHW, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_06->Text   = "invalid"; }else{ labelSetLevelWT_06->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_06->Text = "invalid"; }else{ labelResetLevelWT_06->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_06->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[6]);

  GetWarnThresDM( ucHistCol, cucIX_FT, &ucSetLevel, &ucResetLevel);
  if( ucSetLevel   == cInvalidREpressure) { labelSetLevelWT_07->Text   = "invalid"; }else{ labelSetLevelWT_07->Text   = System::String::Format("{0}", (uint16) ucSetLevel   * 25); }
  if( ucResetLevel == cInvalidREpressure) { labelResetLevelWT_07->Text = "invalid"; }else{ labelResetLevelWT_07->Text = System::String::Format("{0}", (uint16) ucResetLevel * 25); }

  labelWarningStateWT_07->Text = System::String::Format("{0,2:X2}", ucWarnVectorWt[7]);

  ulWarnOut = GETulWarnOutTM();
  labelWarningOutputGroup->Text = System::String::Format( "{0,8:X8}", ulWarnOut);

  if( (ulWarnOut & 0x00F00000) != 0)
  {

    checkBoxWarningGroupDFlatTire->Checked = true;
  }else{
    checkBoxWarningGroupDFlatTire->Checked = false;
  }

  if( bGetBefuellhinweisBT() == TRUE)
  {
    checkBoxWarningGroupCBefuellhinweis->Checked = true;
  }else{
    checkBoxWarningGroupCBefuellhinweis->Checked = false;
  }

  if( (ucGetBreakTireStateBT() & cBtWsBreakTirePw) == cBtWsBreakTirePw)
  {

    checkBoxWarningGroupAPannenwarnung->Checked = true;
    checkBoxWarningGroupBDruckwarnung->Checked = false;
  }else if( (ucGetBreakTireStateBT() & cBtWsBreakTireDw) == cBtWsBreakTireDw)
  {

    checkBoxWarningGroupAPannenwarnung->Checked = false;
    checkBoxWarningGroupBDruckwarnung->Checked = true;
  }else{

    checkBoxWarningGroupAPannenwarnung->Checked = false;
    checkBoxWarningGroupBDruckwarnung->Checked = false;
  }

  ulWarnOut = GETulWarnAttrOutTM();
  labelWarningAttrOutputGroup->Text = System::String::Format( "{0,8:X8}", ulWarnOut);

  labelWarningVectorSlot0->Text = System::String::Format( "{0,2:X2}", ucWarnVectorId[0]);
  labelWarningVectorSlot1->Text = System::String::Format( "{0,2:X2}", ucWarnVectorId[1]);
  labelWarningVectorSlot2->Text = System::String::Format( "{0,2:X2}", ucWarnVectorId[2]);
  labelWarningVectorSlot3->Text = System::String::Format( "{0,2:X2}", ucWarnVectorId[3]);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 0);
  labelPinitTinitSlot0->Text = System::String::Format("{0}", ((uint16) ucPcold * 25));
  labelTinitSlot0->Text = System::String::Format( "{0}", scTcold);
  labelPinitTreifenSlot0->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25));
  labelTreifenSlot0->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 1);
  labelPinitTinitSlot1->Text = System::String::Format("{0}", ((uint16) ucPcold * 25));
  labelTinitSlot1->Text = System::String::Format( "{0}", scTcold);
  labelPinitTreifenSlot1->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25));
  labelTreifenSlot1->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 2);
  labelPinitTinitSlot2->Text = System::String::Format("{0}", ((uint16) ucPcold * 25));
  labelTinitSlot2->Text = System::String::Format( "{0}", scTcold);
  labelPinitTreifenSlot2->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25));
  labelTreifenSlot2->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 3);
  labelPinitTinitSlot3->Text = System::String::Format("{0}", ((uint16) ucPcold * 25));
  labelTinitSlot3->Text = System::String::Format( "{0}", scTcold);
  labelPinitTreifenSlot3->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25));
  labelTreifenSlot3->Text = System::String::Format( "{0}", scTwarm);

  ucWheelPos = ucGetWPOfColWAL( 0);
  (void) ucGetWpPTSollUSWIF( &ucPress, &scTemp, ucWheelPos);
  if( ucPress == cInvalidREpressure) { labelPSollWpVal0->Text = "invalid"; }else{ labelPSollWpVal0->Text = System::String::Format( "{0}", ucPress * 25); }
  if( scTemp  == cInvalidREtemperature) { labelTSollWpVal0->Text = "invalid"; }else{ labelTSollWpVal0->Text = System::String::Format( "{0}", scTemp); }
  ucWheelPos = ucGetWPOfColWAL( 1);
  (void) ucGetWpPTSollUSWIF( &ucPress, &scTemp, ucWheelPos);
  if( ucPress == cInvalidREpressure) { labelPSollWpVal1->Text = "invalid"; }else{ labelPSollWpVal1->Text = System::String::Format( "{0}", ucPress * 25); }
  if( scTemp  == cInvalidREtemperature) { labelTSollWpVal1->Text = "invalid"; }else{ labelTSollWpVal1->Text = System::String::Format( "{0}", scTemp); }
  ucWheelPos = ucGetWPOfColWAL( 2);
  (void) ucGetWpPTSollUSWIF( &ucPress, &scTemp, ucWheelPos);
  if( ucPress == cInvalidREpressure) { labelPSollWpVal2->Text = "invalid"; }else{ labelPSollWpVal2->Text = System::String::Format( "{0}", ucPress * 25); }
  if( scTemp  == cInvalidREtemperature) { labelTSollWpVal2->Text = "invalid"; }else{ labelTSollWpVal2->Text = System::String::Format( "{0}", scTemp); }
  ucWheelPos = ucGetWPOfColWAL( 3);
  (void) ucGetWpPTSollUSWIF( &ucPress, &scTemp, ucWheelPos);
  if( ucPress == cInvalidREpressure) { labelPSollWpVal3->Text = "invalid"; }else{ labelPSollWpVal3->Text = System::String::Format( "{0}", ucPress * 25); }
  if( scTemp  == cInvalidREtemperature) { labelTSollWpVal3->Text = "invalid"; }else{ labelTSollWpVal3->Text = System::String::Format( "{0}", scTemp); }

  GetTimerValPWARN( 0, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelShortTimeSlot0->Text = "OFF";
  }else{
    labelShortTimeSlot0->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARN( 1, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelShortTimeSlot1->Text = "OFF";
  }else{
    labelShortTimeSlot1->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARN( 2, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelShortTimeSlot2->Text = "OFF";
  }else{
    labelShortTimeSlot2->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARN( 3, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelShortTimeSlot3->Text = "OFF";
  }else{
    labelShortTimeSlot3->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARNTOL( 0, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelLongTimeSlot0->Text = "OFF";
  }else{
    labelLongTimeSlot0->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARNTOL( 1, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelLongTimeSlot1->Text = "OFF";
  }else{
    labelLongTimeSlot1->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARNTOL( 2, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelLongTimeSlot2->Text = "OFF";
  }else{
    labelLongTimeSlot2->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPWARNTOL( 3, &ucTimerState, &ushTimerCounter);
  if( ushTimerCounter == cushWarnDelayTimerOffValue)
  {
    labelLongTimeSlot3->Text = "OFF";
  }else{
    labelLongTimeSlot3->Text = System::String::Format( "{0}", ushTimerCounter / 10);
  }

  GetTimerValPVORW( 0, &ucTimState, &ushTimCnt);
  if( ushTimCnt == 0xffff) { labelPvorwDelaySlot0->Text = "OFF"; }else{ labelPvorwDelaySlot0->Text = System::String::Format( "{0}", ushTimCnt / 10); }

  GetTimerValPVORW( 1, &ucTimState, &ushTimCnt);
  if( ushTimCnt == 0xffff) { labelPvorwDelaySlot1->Text = "OFF"; }else{ labelPvorwDelaySlot1->Text = System::String::Format( "{0}", ushTimCnt / 10); }

  GetTimerValPVORW( 2, &ucTimState, &ushTimCnt);
  if( ushTimCnt == 0xffff) { labelPvorwDelaySlot2->Text = "OFF"; }else{ labelPvorwDelaySlot2->Text = System::String::Format( "{0}", ushTimCnt / 10); }

  GetTimerValPVORW( 3, &ucTimState, &ushTimCnt);
  if( ushTimCnt == 0xffff) { labelPvorwDelaySlot3->Text = "OFF"; }else{ labelPvorwDelaySlot3->Text = System::String::Format( "{0}", ushTimCnt / 10); }

  GetTimerValDHW( 0, &ucRefPresDHW, &ucLastPresDHW, &ushTimCntDHW, &ushTimCountLatchDHW);
  if( ucRefPresDHW == cInvalidREpressure)  { labelPrefDHWSlot0->Text  = "0"; }else{ labelPrefDHWSlot0->Text  = System::String::Format( "{0}", ((uint16) ucRefPresDHW  * 25)); }
  if( ucLastPresDHW == cInvalidREpressure) { labelPlastDHWSlot0->Text = "0"; }else{ labelPlastDHWSlot0->Text = System::String::Format( "{0}", ((uint16) ucLastPresDHW * 25)); }
  labelTimeCounterDHWSlot0->Text = System::String::Format( "{0}", ushTimCntDHW / 10);
  labelTimeCounterLatchDHWSlot0->Text = System::String::Format( "{0}", ushTimCountLatchDHW / 10);

  GetTimerValDHW( 1, &ucRefPresDHW, &ucLastPresDHW, &ushTimCntDHW, &ushTimCountLatchDHW);
  if( ucRefPresDHW == cInvalidREpressure)  { labelPrefDHWSlot1->Text  = "0"; }else{ labelPrefDHWSlot1->Text  = System::String::Format( "{0}", ((uint16) ucRefPresDHW  * 25)); }
  if( ucLastPresDHW == cInvalidREpressure) { labelPlastDHWSlot1->Text = "0"; }else{ labelPlastDHWSlot1->Text = System::String::Format( "{0}", ((uint16) ucLastPresDHW * 25)); }
  labelTimeCounterDHWSlot1->Text = System::String::Format( "{0}", ushTimCntDHW / 10);
  labelTimeCounterLatchDHWSlot1->Text = System::String::Format( "{0}", ushTimCountLatchDHW / 10);

  GetTimerValDHW( 2, &ucRefPresDHW, &ucLastPresDHW, &ushTimCntDHW, &ushTimCountLatchDHW);
  if( ucRefPresDHW == cInvalidREpressure)  { labelPrefDHWSlot2->Text  = "0"; }else{ labelPrefDHWSlot2->Text  = System::String::Format( "{0}", ((uint16) ucRefPresDHW  * 25)); }
  if( ucLastPresDHW == cInvalidREpressure) { labelPlastDHWSlot2->Text = "0"; }else{ labelPlastDHWSlot2->Text = System::String::Format( "{0}", ((uint16) ucLastPresDHW * 25)); }
  labelTimeCounterDHWSlot2->Text = System::String::Format( "{0}", ushTimCntDHW / 10);
  labelTimeCounterLatchDHWSlot2->Text = System::String::Format( "{0}", ushTimCountLatchDHW / 10);

  GetTimerValDHW( 3, &ucRefPresDHW, &ucLastPresDHW, &ushTimCntDHW, &ushTimCountLatchDHW);
  if( ucRefPresDHW == cInvalidREpressure)  { labelPrefDHWSlot3->Text  = "0"; }else{ labelPrefDHWSlot3->Text  = System::String::Format( "{0}", ((uint16) ucRefPresDHW  * 25)); }
  if( ucLastPresDHW == cInvalidREpressure) { labelPlastDHWSlot3->Text = "0"; }else{ labelPlastDHWSlot3->Text = System::String::Format( "{0}", ((uint16) ucLastPresDHW * 25)); }
  labelTimeCounterDHWSlot3->Text = System::String::Format( "{0}", ushTimCntDHW / 10);
  labelTimeCounterLatchDHWSlot3->Text = System::String::Format( "{0}", ushTimCountLatchDHW / 10);

  ulTemp = ulGetStartedStateOfVklCCM();

                                        if((ulTemp & ((uint32)1 << cCcIX_Inactive)) > 0)
                                        {
                                          labelMMIInactive->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIInactive->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_ExternalInterference)) > 0)
                                        {
                                          labelMMIExternalInterference->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIExternalInterference->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        bColor = FALSE;

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFL)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFL->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFL->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFR)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFR->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFR->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRL)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRL->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRL->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRR)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRR->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRR->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTire)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTire->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTire->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if( TRUE == bColor)
                                        {
                                          labelMMIFlatTirePos->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTirePos->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        bColor = FALSE;

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFL_RSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFL_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFL_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFR_RSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFR_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFR_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRL_RSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRL_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRL_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRR_RSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRR_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRR_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTire_RSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTire_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTire_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if( TRUE == bColor)
                                        {
                                          labelMMIFlatTirePos_RSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTirePos_RSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        bColor = FALSE;

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFL_NoRSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFL_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFL_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireFR_NoRSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireFR_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireFR_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRL_NoRSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRL_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRL_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTireRR_NoRSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTireRR_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTireRR_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_FlatTire_NoRSC)) > 0)
                                        {
                                          bColor = TRUE;
                                          labelMMIFlatTire_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTire_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if( TRUE == bColor)
                                        {
                                          labelMMIFlatTirePos_NoRSC->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFlatTirePos_NoRSC->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_Befuellhinweis)) > 0)
                                        {
                                          labelMMIBefuellhinweis->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIBefuellhinweis->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_PlausiCheck)) > 0)
                                        {
                                          labelMMIPlausiCheck->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIPlausiCheck->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_Druckwarnung)) > 0)
                                        {
                                          labelMMIDruckwarnung->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIDruckwarnung->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1u << cCcIX_Lernphase)) > 0)
                                        {
                                          labelMMILernphase->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMILernphase->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1 << cCcIX_Reifenwechsel)) > 0)
                                        {
                                          labelMMIReifenwechsel->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIReifenwechsel->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1 << cCcIX_AutoSelFailed)) > 0)
                                        {
                                          labelMMIAutoSelFailed->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIAutoSelFailed->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1 << cCcIX_SpeedCcm2158)) > 0)
                                        {
                                          labelMMISpeedCcm2158->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMISpeedCcm2158->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if((ulTemp & ((uint32)1 << cCcIX_SpeedCcm2159)) > 0)
                                        {
                                          labelMMISpeedCcm2159->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMISpeedCcm2159->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

                                        if( (ucGetActualStateWL() & 0x01) != 0)
                                        {
                                          labelMMIFixLamp->ForeColor = System::Drawing::Color::FromArgb(0, 0, 0);
                                        }
                                        else
                                        {
                                          labelMMIFixLamp->ForeColor = System::Drawing::Color::FromArgb(160,160,160);
                                        }

  labelCddPortWriteCounter->Text = System::String::Format("{0}", ulGetTRdcRfWriteCounter());
  labelCddPortReadCounter->Text = System::String::Format("{0}", ulGetTRdcRfReadCounter());

  checkBoxRdciAutoLearningFailed->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciAutoLearningFailed].ucStatus);
  checkBoxRdci4WrongWuMounted->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdci4WrongWuMounted].ucStatus);
  checkBoxRdci1To3WrongWuMounted->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdci1To3WrongWuMounted].ucStatus);
  checkBoxRdciWuMuteFl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuMuteFl].ucStatus);
  checkBoxRdciWuMuteFr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuMuteFr].ucStatus);
  checkBoxRdciWuMuteRl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuMuteRl].ucStatus);
  checkBoxRdciWuMuteRr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuMuteRr].ucStatus);
  checkBoxRdciWuDefectFl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuDefectFl].ucStatus);
  checkBoxRdciWuDefectFr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuDefectFr].ucStatus);
  checkBoxRdciWuDefectRl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuDefectRl].ucStatus);
  checkBoxRdciWuDefectRr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuDefectRr].ucStatus);
  checkBoxRdciWuLocalisationFailed->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuLocalisationFailed].ucStatus);
  checkBoxRdciWuLowBatteryFl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuLowBatteryFl].ucStatus);
  checkBoxRdciWuLowBatteryFr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuLowBatteryFr].ucStatus);
  checkBoxRdciWuLowBatteryRl->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuLowBatteryRl].ucStatus);
  checkBoxRdciWuLowBatteryRr->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWuLowBatteryRr].ucStatus);
  checkBoxRdciUnspecifiedWfcDefect->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciUnspecifiedWfcDefect].ucStatus);
  checkBoxRdciUnspecifiedWuMute->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciUnspecifiedWuMute].ucStatus);
  checkBoxRdciGatewayOrAntennaError->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciGatewayOrAntennaError].ucStatus);
  checkBoxRdciOtherWuSensorType->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciOtherWuSensorType].ucStatus);

  checkBoxRdciTpmsManufactoryMode->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciTpmsManufactoryMode].ucStatus);
  checkBoxRdciRfExternalInterference->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRfExternalInterference].ucStatus);
  checkBoxRdciPartialSystemAvailability->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciPartialSystemAvailability].ucStatus);
  checkBoxRdciSystemNotAvailable->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciSystemNotAvailable].ucStatus);

  checkBoxRdciConVehTimeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciConVehTimeout].ucStatus);
  checkBoxRdciConVehAlive->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciConVehAlive].ucStatus);
  checkBoxRdciConVehCrc->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciConVehCrc].ucStatus);
  checkBoxRdciConVehInvalid->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciConVehInvalid].ucStatus);
  checkBoxRdciAtempTimeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciATempTimeout].ucStatus);
  checkBoxRdciAtempInvalid->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciATempInvalid].ucStatus);
  checkBoxRdciEinheitenBn2020Timeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciEinheitenBn2020Timeout].ucStatus);
  checkBoxRdciEinheitenBn2020Invalid->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciEinheitenBn2020Invalid].ucStatus);
  checkBoxRdciRdcDtPckg1Timeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRdcDtPckg1Timeout].ucStatus);
  checkBoxRdciRdcDtPckg1Alive->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRdcDtPckg1Alive].ucStatus);
  checkBoxRdciRdcDtPckg1Invalid->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRdcDtPckg1Invalid].ucStatus);
  checkBoxRdciRelativzeitTimeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRelativzeitTimeout].ucStatus);
  checkBoxRdciRelativzeitInvalid->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciRelativzeitInvalid].ucStatus);
  checkBoxRdciVVehTimeout->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciVVehTimeout].ucStatus);
  checkBoxRdciVVehCrc->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciVVehCrcFailure].ucStatus);
  checkBoxRdciVVehAlive->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciVVehAliveFailure].ucStatus);
  checkBoxRdciVVehInvalid->Checked = ( bActualDtcState( tRDCiDtclist[cDemErrorRdciVVehCogInvalid].ucStatus) | bActualDtcState( tRDCiDtclist[cDemErrorRdciVVehCogQualifier].ucStatus));

  checkBoxRdciKalibrierung->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciKalibrierung].ucStatus);
  checkBoxRdciAusfall->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciAusfall].ucStatus);
  checkBoxRdciBefuellhinweis->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciBefuellhinweis].ucStatus);
  checkBoxRdciDruckwarnung->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciDruckwarnung].ucStatus);
  checkBoxRdciPannenwarnung->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciPannenwarnung].ucStatus);
  checkBoxRdciWarnruecknahme->Checked = bActualDtcState( tRDCiDtclist[cDemErrorRdciWarnruecknahme].ucStatus);

  ushTemp1 = (uint16)ucGetWumActivityStatusWUM();
  if(ushTemp1 == cWUM_ENABLED)
  { labelWumActivityStatus->Text = "WUM Enabled"; }
  else if(ushTemp1 == cWUM_DISABLED)
  { labelWumActivityStatus->Text = "WUM Disabled"; }
  else if(ushTemp1 == cWUM_BM_DIENST_START)
  { labelWumActivityStatus->Text = "WUM Limited"; }
  else
  {}

  labelPbarValue->Text    = System::String::Format( "{0}", GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC) * 25);
  labelPminFzgValue->Text = System::String::Format( "{0}", ucGetPminFzgDM() * 25);

  if( ucGetPWarnMinDM()                            == cInvalidREpressure) { labelPminValue->Text         = "invalid"; }else{ labelPminValue->Text        = System::String::Format( "{0}", ucGetPWarnMinDM() * 25); }
  if( GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)  == cInvalidOutdoorTemperature) { labelTAinitValue->Text       = "invalid"; }else{ labelTAinitValue->Text      = System::String::Format( "{0}", GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)); }
  if( GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)    == cInvalidOutdoorTemperature) { labelTAmbValue->Text         = "invalid"; }else{ labelTAmbValue->Text        = System::String::Format( "{0}", GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)); }

  if( scGetTinitDM( 0)       == cInvalidREtemperature) { labelTinitValue0->Text       = "invalid"; }else{ labelTinitValue0->Text      = System::String::Format( "{0}", scGetTinitDM( 0)); }
  if( scGetTinitDM( 1)       == cInvalidREtemperature) { labelTinitValue1->Text       = "invalid"; }else{ labelTinitValue1->Text      = System::String::Format( "{0}", scGetTinitDM( 1)); }
  if( scGetTinitDM( 2)       == cInvalidREtemperature) { labelTinitValue2->Text       = "invalid"; }else{ labelTinitValue2->Text      = System::String::Format( "{0}", scGetTinitDM( 2)); }
  if( scGetTinitDM( 3)       == cInvalidREtemperature) { labelTinitValue3->Text       = "invalid"; }else{ labelTinitValue3->Text      = System::String::Format( "{0}", scGetTinitDM( 3)); }

  if( ucGetPinitTinitDM( 0)  == cInvalidREpressure) { labelPinitTinitValue0->Text  = "invalid"; }else{ labelPinitTinitValue0->Text = System::String::Format( "{0}", ucGetPinitTinitDM( 0)   * 25); }
  if( ucGetPinitTinitDM( 1)  == cInvalidREpressure) { labelPinitTinitValue1->Text  = "invalid"; }else{ labelPinitTinitValue1->Text = System::String::Format( "{0}", ucGetPinitTinitDM( 1)   * 25); }
  if( ucGetPinitTinitDM( 2)  == cInvalidREpressure) { labelPinitTinitValue2->Text  = "invalid"; }else{ labelPinitTinitValue2->Text = System::String::Format( "{0}", ucGetPinitTinitDM( 2)   * 25); }
  if( ucGetPinitTinitDM( 3)  == cInvalidREpressure) { labelPinitTinitValue3->Text  = "invalid"; }else{ labelPinitTinitValue3->Text = System::String::Format( "{0}", ucGetPinitTinitDM( 3)   * 25); }

  if( ucGetPSollMinCS( 0)  == 0) { labelPSollMinValue0->Text  = "invalid"; }else{ labelPSollMinValue0->Text = System::String::Format( "{0}", ucGetPSollMinCS( 0) * 25); }
  if( ucGetPSollMinCS( 1)  == 0) { labelPSollMinValue1->Text  = "invalid"; }else{ labelPSollMinValue1->Text = System::String::Format( "{0}", ucGetPSollMinCS( 1) * 25); }
  if( ucGetPSollMinCS( 2)  == 0) { labelPSollMinValue2->Text  = "invalid"; }else{ labelPSollMinValue2->Text = System::String::Format( "{0}", ucGetPSollMinCS( 2) * 25); }
  if( ucGetPSollMinCS( 3)  == 0) { labelPSollMinValue3->Text  = "invalid"; }else{ labelPSollMinValue3->Text = System::String::Format( "{0}", ucGetPSollMinCS( 3) * 25); }

  if( (ucGetRePressureRelDM( 0) == cInvalidREpressure) || (scGetReTemperatureCentDM( 0) == cInvalidREtemperature)) { labelPtolValueSlot0->Text       = "invalid"; }else{ labelPtolValueSlot0->Text      = System::String::Format( "{0}", ucGetPTolWN( GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC), ucGetRePressureRelDM( 0), scGetReTemperatureCentDM( 0)) * 25); }
  if( (ucGetRePressureRelDM( 1) == cInvalidREpressure) || (scGetReTemperatureCentDM( 1) == cInvalidREtemperature)) { labelPtolValueSlot1->Text       = "invalid"; }else{ labelPtolValueSlot1->Text      = System::String::Format( "{0}", ucGetPTolWN( GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC), ucGetRePressureRelDM( 1), scGetReTemperatureCentDM( 1)) * 25); }
  if( (ucGetRePressureRelDM( 2) == cInvalidREpressure) || (scGetReTemperatureCentDM( 2) == cInvalidREtemperature)) { labelPtolValueSlot2->Text       = "invalid"; }else{ labelPtolValueSlot2->Text      = System::String::Format( "{0}", ucGetPTolWN( GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC), ucGetRePressureRelDM( 2), scGetReTemperatureCentDM( 2)) * 25); }
  if( (ucGetRePressureRelDM( 3) == cInvalidREpressure) || (scGetReTemperatureCentDM( 3) == cInvalidREtemperature)) { labelPtolValueSlot3->Text       = "invalid"; }else{ labelPtolValueSlot3->Text      = System::String::Format( "{0}", ucGetPTolWN( GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC), ucGetRePressureRelDM( 3), scGetReTemperatureCentDM( 3)) * 25); }

  ucWheelPos = ucGetWPOfColWAL( 0);
  if( GetTarPTyrDisplayValueDM( ucWheelPos) > 530) { labelTarPTyrVal0->Text = " "; }else{ labelTarPTyrVal0->Text = System::String::Format( "{0}", GetTarPTyrDisplayValueDM( ucWheelPos) * 25); }
  ucWheelPos = ucGetWPOfColWAL( 1);
  if( GetTarPTyrDisplayValueDM( ucWheelPos) > 530) { labelTarPTyrVal1->Text = " "; }else{ labelTarPTyrVal1->Text = System::String::Format( "{0}", GetTarPTyrDisplayValueDM( ucWheelPos) * 25); }
  ucWheelPos = ucGetWPOfColWAL( 2);
  if( GetTarPTyrDisplayValueDM( ucWheelPos) > 530) { labelTarPTyrVal2->Text = " "; }else{ labelTarPTyrVal2->Text = System::String::Format( "{0}", GetTarPTyrDisplayValueDM( ucWheelPos) * 25); }
  ucWheelPos = ucGetWPOfColWAL( 3);
  if( GetTarPTyrDisplayValueDM( ucWheelPos) > 530) { labelTarPTyrVal3->Text = " "; }else{ labelTarPTyrVal3->Text = System::String::Format( "{0}", GetTarPTyrDisplayValueDM( ucWheelPos) * 25); }

  labelER_FINISH_Value->Text        = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cER_FINISH));
  labelTOO_MUCH_RE_Value->Text      = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cTOO_MUCH_RE));
  labelLOC_NOT_POSSIBLE_Value->Text = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cLOC_NOT_POSSIBLE));
  labelEIGENRAD_Value->Text         = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cEIGENRAD));
  labelZUGEORDNET_Value->Text       = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cZUGEORDNET));
  labelZWANGSZUORDNUNG_Value->Text  = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cZWANGSZUORDNUNG));
  labelHIST_PRELOAD_Value->Text     = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cHIST_PRELOAD));
  labelZO_FINISH_Value->Text        = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cZO_FINISH));
  labelLOC_INTERRUPTED_Value->Text  = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cLOC_INTERRUPTED));
  labelDTC_INACTIVE_Value->Text     = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cDTC_INACTIVE));
  labelTEILEIGENRAD_Value->Text     = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cTEILEIGENRAD));
  labelZO_TIMEOUT_Value->Text       = System::String::Format( "{0}", bGetBitBetriebszustandBZ( cZO_TIMEOUT));

  labelKL_15_EIN_Value->Text        = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cKL_15_EIN));
  labelRS_VTHRES_Value->Text        = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cRS_VTHRES));
  labelFAHRZEUG_FAEHRT_Value->Text  = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT));
  labelRUECKWAERTSFAHRT_Value->Text = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cRUECKWAERTSFAHRT));
  labelFAHRZEUG_LERNT_Value->Text   = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cFAHRZEUG_LERNT));
  labelMP_VTHRES_Value->Text        = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cMP_VTHRES));
  labelNW_DTC_LOCKED_Value->Text    = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cNW_DTC_LOCKED));
  labelTAMBIENT_RED_Value->Text     = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cTAMBIENT_RED));
  labelLONG_PARK_Value->Text        = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cLONG_PARK));
  labelBM_VTHRES_Value->Text        = System::String::Format( "{0}", bGetBitFahrzeugzustandFZZ( cBM_VTHRES));

  if( GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)    == cInvalidOutdoorTemperature) { labelTAinitWert->Text         = "invalid"; }else{ labelTAinitWert->Text         = System::String::Format( "{0}",      GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)); }
  if( GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)      == cInvalidOutdoorTemperature) { labelTAmbientWert->Text       = "invalid"; }else{ labelTAmbientWert->Text       = System::String::Format( "{0}",      GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)); }
  if( GETsshTAmbFiltValEE( Rte_Inst_CtApHufTpmsSWC) == cInvalidTemperatureWord) { labelTAmbientFilterWert->Text = "invalid"; }else{ labelTAmbientFilterWert->Text = System::String::Format( "{0:0.00}", (float) GETsshTAmbFiltValEE( Rte_Inst_CtApHufTpmsSWC) / 100); }
  numericUpDownTAmbientFilterFactorWert->Value = GETucTAmbFiltFactValEE( Rte_Inst_CtApHufTpmsSWC);

  if( bGetBitFahrzeugzustandFZZ( cTAMBIENT_RED) == TRUE)
  {
    checkBoxERK_TAMBIENT_RED->Checked = true;
  }else{
    checkBoxERK_TAMBIENT_RED->Checked = false;
  }

  if( GETucUnAipEE( Rte_Inst_CtApHufTpmsSWC) == ePRESSURE_UNIT_KPA)
  {
    sLabelPressureUnit = "kPa";
  }else if( GETucUnAipEE( Rte_Inst_CtApHufTpmsSWC) == ePRESSURE_UNIT_PSI)
  {
    sLabelPressureUnit = "psi";
  }else{
    sLabelPressureUnit = "bar";
  }

  if( GETucUnTempEE( Rte_Inst_CtApHufTpmsSWC) == eTEMPERATURE_UNIT_FAHRENHEIT)
  {
    sLabelTemperatureUnit = "°F";
  }else{
    sLabelTemperatureUnit = "°C";
  }

  labelValueCarStandStillTime->Text = System::String::Format( "{0}", ulGetStopTimeDM());
  labelMaxCoolingDownTime->Text = System::String::Format( "{0}", ushGetMaxCoolingDownTimeITY());
  labelCorHoldOffTime->Text = System::String::Format( "{0}", ushGetCorHoldOffTimeITY());

  GetAvlPTyreCoolingValITY( 0, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
  if( ucPcold == cInvalidREpressure) { labelAvlPTyrePkaltSlot0->Text = System::String::Format("{0}", ucPcold); }else{ labelAvlPTyrePkaltSlot0->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelAvlTTyreTkaltSlot0->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelAvlPTyrePwarmSlot0->Text = System::String::Format("{0}", ucPwarm); }else{ labelAvlPTyrePwarmSlot0->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelAvlTTyreTwarmSlot0->Text = System::String::Format( "{0}", scTwarm);
  if( ucPsollCold == cInvalidREpressure) { labelTarPTyrePkaltSlot0->Text = System::String::Format("{0}", ucPsollCold); }else{ labelTarPTyrePkaltSlot0->Text = System::String::Format("{0}", ((uint16) ucPsollCold * 25)); }
  labelTarPTyreTkaltSlot0->Text = System::String::Format( "{0}", scTsollCold);
  if( ucPsollWarm == cInvalidREpressure) { labelTarPTyrePwarmSlot0->Text = System::String::Format("{0}", ucPsollWarm); }else{ labelTarPTyrePwarmSlot0->Text = System::String::Format("{0}", ((uint16) ucPsollWarm * 25)); }

  GetAvlPTyreCoolingValITY( 1, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
  if( ucPcold == cInvalidREpressure) { labelAvlPTyrePkaltSlot1->Text = System::String::Format("{0}", ucPcold); }else{ labelAvlPTyrePkaltSlot1->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelAvlTTyreTkaltSlot1->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelAvlPTyrePwarmSlot1->Text = System::String::Format("{0}", ucPwarm); }else{ labelAvlPTyrePwarmSlot1->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelAvlTTyreTwarmSlot1->Text = System::String::Format( "{0}", scTwarm);
  if( ucPsollCold == cInvalidREpressure) { labelTarPTyrePkaltSlot1->Text = System::String::Format("{0}", ucPsollCold); }else{ labelTarPTyrePkaltSlot1->Text = System::String::Format("{0}", ((uint16) ucPsollCold * 25)); }
  labelTarPTyreTkaltSlot1->Text = System::String::Format( "{0}", scTsollCold);
  if( ucPsollWarm == cInvalidREpressure) { labelTarPTyrePwarmSlot1->Text = System::String::Format("{0}", ucPsollWarm); }else{ labelTarPTyrePwarmSlot1->Text = System::String::Format("{0}", ((uint16) ucPsollWarm * 25)); }

  GetAvlPTyreCoolingValITY( 2, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
  if( ucPcold == cInvalidREpressure) { labelAvlPTyrePkaltSlot2->Text = System::String::Format("{0}", ucPcold); }else{ labelAvlPTyrePkaltSlot2->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelAvlTTyreTkaltSlot2->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelAvlPTyrePwarmSlot2->Text = System::String::Format("{0}", ucPwarm); }else{ labelAvlPTyrePwarmSlot2->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelAvlTTyreTwarmSlot2->Text = System::String::Format( "{0}", scTwarm);
  if( ucPsollCold == cInvalidREpressure) { labelTarPTyrePkaltSlot2->Text = System::String::Format("{0}", ucPsollCold); }else{ labelTarPTyrePkaltSlot2->Text = System::String::Format("{0}", ((uint16) ucPsollCold * 25)); }
  labelTarPTyreTkaltSlot2->Text = System::String::Format( "{0}", scTsollCold);
  if( ucPsollWarm == cInvalidREpressure) { labelTarPTyrePwarmSlot2->Text = System::String::Format("{0}", ucPsollWarm); }else{ labelTarPTyrePwarmSlot2->Text = System::String::Format("{0}", ((uint16) ucPsollWarm * 25)); }

  GetAvlPTyreCoolingValITY( 3, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
  if( ucPcold == cInvalidREpressure) { labelAvlPTyrePkaltSlot3->Text = System::String::Format("{0}", ucPcold); }else{ labelAvlPTyrePkaltSlot3->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelAvlTTyreTkaltSlot3->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelAvlPTyrePwarmSlot3->Text = System::String::Format("{0}", ucPwarm); }else{ labelAvlPTyrePwarmSlot3->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelAvlTTyreTwarmSlot3->Text = System::String::Format( "{0}", scTwarm);
  if( ucPsollCold == cInvalidREpressure) { labelTarPTyrePkaltSlot3->Text = System::String::Format("{0}", ucPsollCold); }else{ labelTarPTyrePkaltSlot3->Text = System::String::Format("{0}", ((uint16) ucPsollCold * 25)); }
  labelTarPTyreTkaltSlot3->Text = System::String::Format( "{0}", scTsollCold);
  if( ucPsollWarm == cInvalidREpressure) { labelTarPTyrePwarmSlot3->Text = System::String::Format("{0}", ucPsollWarm); }else{ labelTarPTyrePwarmSlot3->Text = System::String::Format("{0}", ((uint16) ucPsollWarm * 25)); }

  if( (ulGetStopTimeDM() == 0) || (ulCoolingCaptTime == 0xffffffffu))
  {

    labelCoolingTicks->Text       = "- - -";
    labelElapsedCoolingTime->Text = "- - -";
    labelCoolingCaptTime->Text    = "- - -";
    labelCoolingTime->Text        = "- - -";
  }else{

    if( (ushTimeTicks == cCoolingIntervalInitVal))
    {
      labelCoolingTicks->Text       = "init";
    }else if( (ushTimeTicks == cCoolingIntervalResetVal))
    {
      labelCoolingTicks->Text       = "reset";
    }else{
      labelCoolingTicks->Text       = System::String::Format( "{0}", ushTimeTicks / 10);
    }

    labelElapsedCoolingTime->Text = System::String::Format( "{0}", ushElapsedCoolingTime);
    labelCoolingCaptTime->Text    = System::String::Format( "{0}", ulCoolingCaptTime);
    labelCoolingTime->Text        = System::String::Format( "{0}", (ulGetStopTimeDM() - ulCoolingCaptTime));
  }

  for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
  {
    ucHistCol = ucGetColOfWP( ucLoop);
    if( ucHistCol < cAnzRad)
    {
      switch( ucLoop)
      {
        case cRadPosVL:
          GetRDCiOutputDataAVL_P_TYR_FLH( &AVL_P_TYR);
          GetRDCiOutputDataAVL_T_TYR_FLH( &AVL_T_TYR);
          GetRDCiOutputDataTAR_P_TYR_FLH( &TAR_P_TYR);
        break;

        case cRadPosVR:
          GetRDCiOutputDataAVL_P_TYR_FRH( &AVL_P_TYR);
          GetRDCiOutputDataAVL_T_TYR_FRH( &AVL_T_TYR);
          GetRDCiOutputDataTAR_P_TYR_FRH( &TAR_P_TYR);
        break;

        case cRadPosHL:
          GetRDCiOutputDataAVL_P_TYR_RLH( &AVL_P_TYR);
          GetRDCiOutputDataAVL_T_TYR_RLH( &AVL_T_TYR);
          GetRDCiOutputDataTAR_P_TYR_RLH( &TAR_P_TYR);
        break;

        case cRadPosHR:
          GetRDCiOutputDataAVL_P_TYR_RRH( &AVL_P_TYR);
          GetRDCiOutputDataAVL_T_TYR_RRH( &AVL_T_TYR);
          GetRDCiOutputDataTAR_P_TYR_RRH( &TAR_P_TYR);
        break;
      }

      switch( ucHistCol)
      {
        case 0:
          if( AVL_P_TYR == cTyrePressureNotPresentValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot0->Text = "     ";
          }else if( AVL_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot0->Text = "-----";
          }else if( AVL_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot0->Text = "invalid";
          }else{
            labelAvlPTyreAVL_P_TYRSlot0->Text = System::String::Format("{0}{1}", AVL_P_TYR * 0.1, sLabelPressureUnit);
          }

          if( AVL_T_TYR == cTyreTemperatureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot0->Text = "-----";
          }else if( AVL_T_TYR == cTyreTemperatureInvalidValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot0->Text = "invalid";
          }else{
            labelAvlPTyreAVL_T_TYRSlot0->Text = System::String::Format("{0}{1}", AVL_T_TYR - 40, sLabelTemperatureUnit);
          }

          if( TAR_P_TYR == cTyrePressureFuncIfaceNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot0->Text = "     ";
          }else if( TAR_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot0->Text = "-----";
          }else if( TAR_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot0->Text = "invalid";
          }else{
            labelTarPTyreTAR_P_TYRSlot0->Text = System::String::Format("{0}{1}", TAR_P_TYR * 0.1, sLabelPressureUnit);
          }
        break;

        case 1:
          if( AVL_P_TYR == cTyrePressureNotPresentValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot1->Text = "     ";
          }else if( AVL_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot1->Text = "-----";
          }else if( AVL_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot1->Text = "invalid";
          }else{
            labelAvlPTyreAVL_P_TYRSlot1->Text = System::String::Format("{0}{1}", AVL_P_TYR * 0.1, sLabelPressureUnit);
          }

          if( AVL_T_TYR == cTyreTemperatureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot1->Text = "-----";
          }else if( AVL_T_TYR == cTyreTemperatureInvalidValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot1->Text = "invalid";
          }else{
            labelAvlPTyreAVL_T_TYRSlot1->Text = System::String::Format("{0}{1}", AVL_T_TYR - 40, sLabelTemperatureUnit);
          }

          if( TAR_P_TYR == cTyrePressureFuncIfaceNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot1->Text = "     ";
          }else if( TAR_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot1->Text = "-----";
          }else if( TAR_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot1->Text = "invalid";
          }else{
            labelTarPTyreTAR_P_TYRSlot1->Text = System::String::Format("{0}{1}", TAR_P_TYR * 0.1, sLabelPressureUnit);
          }
        break;

        case 2:
          if( AVL_P_TYR == cTyrePressureNotPresentValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot2->Text = "     ";
          }else if( AVL_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot2->Text = "-----";
          }else if( AVL_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot2->Text = "invalid";
          }else{
            labelAvlPTyreAVL_P_TYRSlot2->Text = System::String::Format("{0}{1}", AVL_P_TYR * 0.1, sLabelPressureUnit);
          }

          if( AVL_T_TYR == cTyreTemperatureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot2->Text = "-----";
          }else if( AVL_T_TYR == cTyreTemperatureInvalidValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot2->Text = "invalid";
          }else{
            labelAvlPTyreAVL_T_TYRSlot2->Text = System::String::Format("{0}{1}", AVL_T_TYR - 40, sLabelTemperatureUnit);
          }

          if( TAR_P_TYR == cTyrePressureFuncIfaceNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot2->Text = "     ";
          }else if( TAR_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot2->Text = "-----";
          }else if( TAR_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot2->Text = "invalid";
          }else{
            labelTarPTyreTAR_P_TYRSlot2->Text = System::String::Format("{0}{1}", TAR_P_TYR * 0.1, sLabelPressureUnit);
          }
        break;

        case 3:
          if( AVL_P_TYR == cTyrePressureNotPresentValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot3->Text = "     ";
          }else if( AVL_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot3->Text = "-----";
          }else if( AVL_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelAvlPTyreAVL_P_TYRSlot3->Text = "invalid";
          }else{
            labelAvlPTyreAVL_P_TYRSlot3->Text = System::String::Format("{0}{1}", AVL_P_TYR * 0.1, sLabelPressureUnit);
          }

          if( AVL_T_TYR == cTyreTemperatureNotAvailableValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot3->Text = "-----";
          }else if( AVL_T_TYR == cTyreTemperatureInvalidValueITY)
          {
            labelAvlPTyreAVL_T_TYRSlot3->Text = "invalid";
          }else{
            labelAvlPTyreAVL_T_TYRSlot3->Text = System::String::Format("{0}{1}", AVL_T_TYR - 40, sLabelTemperatureUnit);
          }

          if( TAR_P_TYR == cTyrePressureFuncIfaceNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot3->Text = "     ";
          }else if( TAR_P_TYR == cTyrePressureNotAvailableValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot3->Text = "-----";
          }else if( TAR_P_TYR == cTyrePressureInvalidValueITY)
          {
            labelTarPTyreTAR_P_TYRSlot3->Text = "invalid";
          }else{
            labelTarPTyreTAR_P_TYRSlot3->Text = System::String::Format("{0}{1}", TAR_P_TYR * 0.1, sLabelPressureUnit);
          }
        break;
      }
    }
  }

  if( GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)      == cInvalidOutdoorTemperature) { labelTAinitValueSRA->Text       = "invalid"; }else{ labelTAinitValueSRA->Text      = System::String::Format( "{0}", GETscTAinitValEE( Rte_Inst_CtApHufTpmsSWC)); }
  if( GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)        == cInvalidOutdoorTemperature) { labelTAmbValueSRA->Text         = "invalid"; }else{ labelTAmbValueSRA->Text        = System::String::Format( "{0}", GETscTAmbValEE( Rte_Inst_CtApHufTpmsSWC)); }

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 0);
  if( ucPcold == cInvalidREpressure) { labelPcoldSlot0SRA->Text = System::String::Format("{0}", ucPcold); }else{ labelPcoldSlot0SRA->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelTcoldSlot0SRA->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelPwarmSlot0SRA->Text = System::String::Format("{0}", ucPwarm); }else{ labelPwarmSlot0SRA->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelTwarmSlot0SRA->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 1);
  if( ucPcold == cInvalidREpressure) { labelPcoldSlot1SRA->Text = System::String::Format("{0}", ucPcold); }else{ labelPcoldSlot1SRA->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelTcoldSlot1SRA->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelPwarmSlot1SRA->Text = System::String::Format("{0}", ucPwarm); }else{ labelPwarmSlot1SRA->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelTwarmSlot1SRA->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 2);
  if( ucPcold == cInvalidREpressure) { labelPcoldSlot2SRA->Text = System::String::Format("{0}", ucPcold); }else{ labelPcoldSlot2SRA->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelTcoldSlot2SRA->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelPwarmSlot2SRA->Text = System::String::Format("{0}", ucPwarm); }else{ labelPwarmSlot2SRA->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelTwarmSlot2SRA->Text = System::String::Format( "{0}", scTwarm);

  (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, 3);
  if( ucPcold == cInvalidREpressure) { labelPcoldSlot3SRA->Text = System::String::Format("{0}", ucPcold); }else{ labelPcoldSlot3SRA->Text = System::String::Format("{0}", ((uint16) ucPcold * 25)); }
  labelTcoldSlot3SRA->Text = System::String::Format( "{0}", scTcold);
  if( ucPwarm == cInvalidREpressure) { labelPwarmSlot3SRA->Text = System::String::Format("{0}", ucPwarm); }else{ labelPwarmSlot3SRA->Text = System::String::Format("{0}", ((uint16) ucPwarm * 25)); }
  labelTwarmSlot3SRA->Text = System::String::Format( "{0}", scTwarm);

  GetInternalLowerDataSRA( &ucDeltaTinitTh, &ucDeltaTinitHyst, &ulTinitOatTimeTicks, &ulTinitOatTime, &bCorrTinitEvent);
  labelDeltaTinitLowerThValueSRA->Text   = System::String::Format( "{0}", ucDeltaTinitTh);
  labelDeltaTinitLowerHystValueSRA->Text = System::String::Format( "{0}", ucDeltaTinitHyst);
  if( ulTinitOatTimeTicks == 0xFFFFFFFFu) { numericUpDownTinitOatLowerTimeTicksValueSRA->Value = System::Decimal( UInt32( 0)); }else{ numericUpDownTinitOatLowerTimeTicksValueSRA->Value = System::Decimal( UInt32( ulTinitOatTimeTicks)); }
  if( ulTinitOatTime      == 0xFFFFFFFFu)
  {
    numericUpDownTinitOatLowerTimeValueSRAsec->Value      = System::Decimal( UInt32( 0));
    numericUpDownTinitOatLowerTimeValueSRAdays->Value     = System::Decimal( UInt32( 0));
    numericUpDownTinitOatLowerTimeValueSRAhours->Value    = System::Decimal( UInt32( 0));
    numericUpDownTinitOatLowerTimeValueSRAminutes->Value  = System::Decimal( UInt32( 0));
    numericUpDownTinitOatLowerTimeValueSRAseconds->Value  = System::Decimal( UInt32( 0));
  }
  else
  {
    ulTinitOatTime = 86400;
    numericUpDownTinitOatLowerTimeValueSRAsec->Value = System::Decimal(UInt32(ulTinitOatTime));
    ulOATHelp = (ulTinitOatTime / 86400);
    numericUpDownTinitOatLowerTimeValueSRAdays->Value = System::Decimal(UInt32(ulOATHelp));
    ulOATHelp = (ulTinitOatTime / 3600);
    numericUpDownTinitOatLowerTimeValueSRAhours->Value = System::Decimal(UInt32(ulOATHelp - ((System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24))));
    ulOATHelp = (ulTinitOatTime / 60);
    numericUpDownTinitOatLowerTimeValueSRAminutes->Value = System::Decimal(UInt32(ulOATHelp - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAhours->Value) * 60) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24 * 60)));
    numericUpDownTinitOatLowerTimeValueSRAseconds->Value = System::Decimal(UInt32(ulTinitOatTime - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAminutes->Value) * 60) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAhours->Value) * 3600) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24 * 3600)));
  }

  labelCorrTinitLowerEventValueSRA->Text = System::String::Format( "{0}", bCorrTinitEvent);

  GetInternalHigherDataSRA(&ucDeltaTinitTh, &ucDeltaTinitHyst, &ulTinitOatTimeTicks, &ulTinitOatTime, &bCorrTinitEvent);
  labelDeltaTinitHigherThValueSRA->Text   = System::String::Format( "{0}", ucDeltaTinitTh);
  labelDeltaTinitHigherHystValueSRA->Text = System::String::Format( "{0}", ucDeltaTinitHyst);
  if( ulTinitOatTimeTicks == 0xFFFFFFFFu) { numericUpDownTinitOatHigherTimeTicksValueSRA->Value = System::Decimal( UInt32( 0)); }else{ numericUpDownTinitOatHigherTimeTicksValueSRA->Value = System::Decimal( UInt32( ulTinitOatTimeTicks)); }
  if( ulTinitOatTime      == 0xFFFFFFFFu)
  {
    numericUpDownTinitOatHigherTimeValueSRAsec->Value     = System::Decimal( UInt32( 0));
    numericUpDownTinitOatHigherTimeValueSRAdays->Value    = System::Decimal( UInt32( 0));
    numericUpDownTinitOatHigherTimeValueSRAhours->Value   = System::Decimal( UInt32( 0));
    numericUpDownTinitOatHigherTimeValueSRAminutes->Value = System::Decimal( UInt32( 0));
    numericUpDownTinitOatHigherTimeValueSRAseconds->Value = System::Decimal( UInt32( 0));
  }
  else
  {
    ulTinitOatTime = 86400;
    numericUpDownTinitOatHigherTimeValueSRAsec->Value     = System::Decimal( UInt32( ulTinitOatTime));
    ulOATHelp = (ulTinitOatTime / 86400);
    numericUpDownTinitOatHigherTimeValueSRAdays->Value = System::Decimal(UInt32(ulOATHelp));
    ulOATHelp = (ulTinitOatTime / 3600);
    numericUpDownTinitOatHigherTimeValueSRAhours->Value = System::Decimal(UInt32(ulOATHelp - ((System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24))));
    ulOATHelp = (ulTinitOatTime / 60);
    numericUpDownTinitOatHigherTimeValueSRAminutes->Value = System::Decimal(UInt32(ulOATHelp - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAhours->Value) * 60) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24 * 60)));
    numericUpDownTinitOatHigherTimeValueSRAseconds->Value = System::Decimal(UInt32(ulTinitOatTime - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAminutes->Value) * 60) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAhours->Value) * 3600) - (System::Decimal::ToUInt32(numericUpDownTinitOatLowerTimeValueSRAdays->Value) * 24 * 3600)));
  }

  labelCorrTinitHigherEventValueSRA->Text = System::String::Format( "{0}", bCorrTinitEvent);

  if(*(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 (  Rte_Inst_CtApHufTpmsSWC) == comboBoxSelectMultiplexer->SelectedIndex)
  {
    aucDbgMsg[0] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[1] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[2] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[3] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[4] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[5] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[6] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[7] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[8] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[9] =  *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9 ( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[10] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[11] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[12] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[13] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[14] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[15] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[16] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[17] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[18] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[19] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[20] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[21] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[22] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[23] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[24] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[25] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[26] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[27] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[28] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[29] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[30] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30( Rte_Inst_CtApHufTpmsSWC);
    aucDbgMsg[31] = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31( Rte_Inst_CtApHufTpmsSWC);

    textBoxDbgMsg0 ->Text = System::String::Format("{0}", aucDbgMsg[0 ]);
    textBoxDbgMsg1 ->Text = System::String::Format("{0}", aucDbgMsg[1 ]);
    textBoxDbgMsg2 ->Text = System::String::Format("{0}", aucDbgMsg[2 ]);
    textBoxDbgMsg3 ->Text = System::String::Format("{0}", aucDbgMsg[3 ]);
    textBoxDbgMsg4 ->Text = System::String::Format("{0}", aucDbgMsg[4 ]);
    textBoxDbgMsg5 ->Text = System::String::Format("{0}", aucDbgMsg[5 ]);
    textBoxDbgMsg6 ->Text = System::String::Format("{0}", aucDbgMsg[6 ]);
    textBoxDbgMsg7 ->Text = System::String::Format("{0}", aucDbgMsg[7 ]);
    textBoxDbgMsg8 ->Text = System::String::Format("{0}", aucDbgMsg[8 ]);
    textBoxDbgMsg9 ->Text = System::String::Format("{0}", aucDbgMsg[9 ]);
    textBoxDbgMsg10->Text = System::String::Format("{0}", aucDbgMsg[10]);
    textBoxDbgMsg11->Text = System::String::Format("{0}", aucDbgMsg[11]);
    textBoxDbgMsg12->Text = System::String::Format("{0}", aucDbgMsg[12]);
    textBoxDbgMsg13->Text = System::String::Format("{0}", aucDbgMsg[13]);
    textBoxDbgMsg14->Text = System::String::Format("{0}", aucDbgMsg[14]);
    textBoxDbgMsg15->Text = System::String::Format("{0}", aucDbgMsg[15]);
    textBoxDbgMsg16->Text = System::String::Format("{0}", aucDbgMsg[16]);
    textBoxDbgMsg17->Text = System::String::Format("{0}", aucDbgMsg[17]);
    textBoxDbgMsg18->Text = System::String::Format("{0}", aucDbgMsg[18]);
    textBoxDbgMsg19->Text = System::String::Format("{0}", aucDbgMsg[19]);
    textBoxDbgMsg20->Text = System::String::Format("{0}", aucDbgMsg[20]);
    textBoxDbgMsg21->Text = System::String::Format("{0}", aucDbgMsg[21]);
    textBoxDbgMsg22->Text = System::String::Format("{0}", aucDbgMsg[22]);
    textBoxDbgMsg23->Text = System::String::Format("{0}", aucDbgMsg[23]);
    textBoxDbgMsg24->Text = System::String::Format("{0}", aucDbgMsg[24]);
    textBoxDbgMsg25->Text = System::String::Format("{0}", aucDbgMsg[25]);
    textBoxDbgMsg26->Text = System::String::Format("{0}", aucDbgMsg[26]);
    textBoxDbgMsg27->Text = System::String::Format("{0}", aucDbgMsg[27]);
    textBoxDbgMsg28->Text = System::String::Format("{0}", aucDbgMsg[28]);
    textBoxDbgMsg29->Text = System::String::Format("{0}", aucDbgMsg[29]);
    textBoxDbgMsg30->Text = System::String::Format("{0}", aucDbgMsg[30]);
    textBoxDbgMsg31->Text = System::String::Format("{0}", aucDbgMsg[31]);
  }

  GetAipGpsValDM_debug( Rte_Inst_CtApHufTpmsSWC, &ucAipEngDrv, &ushPositionAltitude, &ushErrorAltitudeMeters, &ushGpsTioTicks, &ucAipGpsState);
  if( ucAipEngDrv            == 0xffu) { labelAIP_ENG_DRV_Value->Text         = "- -"; }else{ labelAIP_ENG_DRV_Value->Text         = System::String::Format("{0}", ((uint16) ucAipEngDrv * 2 + 598)); }
  if( ushErrorAltitudeMeters == 0xffffu) { labelErrorAltitudeMeters_Value->Text = "- -"; }else{ labelErrorAltitudeMeters_Value->Text = System::String::Format("{0}", ((uint16) ushErrorAltitudeMeters / 100)); }

  labelGpsTioTicks_Value->Text                  = System::String::Format("{0}", (uint16) ushGpsTioTicks);
  labelAipGpsState_Value->Text                  = System::String::Format("{0,2:X2}", (uint8) ucAipGpsState);

  if( ushPositionAltitude    == 0xffffu)
  {
    labelPositionAltitude_Value->Text           = "- -";
    labelGpsPambHpa_Value->Text                 = "- -";
  }else{
    labelPositionAltitude_Value->Text           = System::String::Format("{0}", ((uint16) ushPositionAltitude / 10 - 1000));

    sshAltMeter                                 = (sint16) ((ushPositionAltitude + 5) / 10) - 1000;
    if( sshAltMeter < 0)
    {

      sshAltMeter = 0;
    }

    if( sshAltMeter < cAGS_2500Mtr)
    {
      labelGpsPambHpa_Value->Text               = System::String::Format( "{0}", (cAGS_Pat0Mtr - (((cAGS_Pat0Mtr - cAGS_Pat2500Mtr) * 4 * sshAltMeter) / 10000)));
    }
    else
    {
      labelGpsPambHpa_Value->Text               = System::String::Format( "{0}", (cAGS_Pat2500Mtr - (((cAGS_Pat2500Mtr - cAGS_Pat5000Mtr) * 4 * (sshAltMeter - cAGS_2500Mtr)) / 10000)));
    }
  }

  labelPambHpa_Value->Text                      = System::String::Format( "{0}", GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC) * 25);

  GetNwMonitoringDataNWM( &tNwMonData);
  labelAIP_ENG_DRV_MsgTimerValue->Text          = System::String::Format( "{0}", tNwMonData.tMonDT_PT_1.ucMsgTimeout);
  labelAIP_ENG_DRV_SigTimerValue->Text          = System::String::Format( "{0}", tNwMonData.tMonDT_PT_1.ucSignalErrorTimeout);
  labelPositionAltitude_MsgTimerValue->Text     = System::String::Format( "{0}", tNwMonData.tMonNMEARawData2Part2.ucMsgTimeout);
  labelPositionAltitude_SigTimerValue->Text     = System::String::Format( "{0}", tNwMonData.tMonNMEARawData2Part2.ucSignalErrorTimeout);
  labelErrorAltitudeMeters_MsgTimerValue->Text  = System::String::Format( "{0}", tNwMonData.tMonNMEARawData2Part3.ucMsgTimeout);
  labelErrorAltitudeMeters_SigTimerValue->Text  = System::String::Format( "{0}", tNwMonData.tMonNMEARawData2Part3.ucSignalErrorTimeout);

}

private: System::Void DelZOHistoryButton_Click(System::Object^  sender, System::EventArgs^  e)
{
  String^ filename;

  int strIndex = 0;

  filename = String::Concat(Application::StartupPath);
  strIndex = filename->LastIndexOf("\\");
  filename = filename->Remove(strIndex);
  filename = filename->Insert(strIndex, "\\NvmRdciZoHistoryBlock.txt");

  char* str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(filename);
  remove(str1);

  ucSetHistoryID( Rte_Inst_CtApHufTpmsSWC, 0, 0);
}

static boolean bActualDtcState( uint8 ucDtcStatus)
{
  boolean bRetVal = FALSE;

  switch ( ucDtcStatus)
  {
    case DEM_EVENT_STATUS_PASSED:
    case DEM_EVENT_STATUS_PREPASSED:
     bRetVal = FALSE;
    break;

    case DEM_EVENT_STATUS_FAILED:
    case DEM_EVENT_STATUS_PREFAILED:
     bRetVal = TRUE;
    break;
  }

  return bRetVal;
}

private: System::Void numericUpDownTAmbientFilterFactorWert_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
  PUTucTAmbFiltFactValEE( Rte_Inst_CtApHufTpmsSWC, (uint8) numericUpDownTAmbientFilterFactorWert->Value);
}

private: System::Void radioButton0x48069B_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRfExternalInterference;

           if( radioButton0x48069B->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48069E_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciAutoLearningFailed;

           if( radioButton0x48069E->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806A1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdci4WrongWuMounted;

           if( radioButton0x4806A1->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806A6_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdci1To3WrongWuMounted;

           if( radioButton0x4806A6->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806B8_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuMuteFl;

           if( radioButton0x4806B8->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806DA_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuMuteFr;

           if( radioButton0x4806DA->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806F0_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuMuteRl;

           if( radioButton0x4806F0->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806F4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuMuteRr;

           if( radioButton0x4806F4->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4806FA_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuDefectFl;

           if( radioButton0x4806FA->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480702_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuDefectFr;

           if( radioButton0x480702->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48070F_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuDefectRl;

           if( radioButton0x48070F->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48071F_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuLocalisationFailed;

           if( radioButton0x48071F->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480728_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuDefectRr;

           if( radioButton0x480728->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48077C_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuLowBatteryFl;

           if( radioButton0x48077C->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48077D_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuLowBatteryFr;

           if( radioButton0x48077D->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48077E_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuLowBatteryRl;

           if( radioButton0x48077E->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x48077F_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWuLowBatteryRr;

           if( radioButton0x48077F->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480780_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciTpmsManufactoryMode;

           if( radioButton0x480780->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4809EA_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciUnspecifiedWfcDefect;

           if( radioButton0x4809EA->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x4809EB_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciUnspecifiedWuMute;

           if( radioButton0x4809EB->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480A46_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciGatewayOrAntennaError;

           if( radioButton0x480A46->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480ACD_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciOtherWuSensorType;

           if( radioButton0x480ACD->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480ACE_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciErfsCodingDataInconsistent;

           if( radioButton0x480ACE->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480ACF_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciAusfall;

           if( radioButton0x480ACF->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480AD0_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciBefuellhinweis;

           if( radioButton0x480AD0->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480AD1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciDruckwarnung;

           if( radioButton0x480AD1->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480AD2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciPannenwarnung;

           if( radioButton0x480AD2->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480AD3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciWarnruecknahme;

           if( radioButton0x480AD3->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480AD4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciKalibrierung;

           if( radioButton0x480AD4->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480B02_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciPartialSystemAvailability;

           if( radioButton0x480B02->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0x480B03_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciSystemNotAvailable;

           if( radioButton0x480B03->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35428_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciATempTimeout;

           if( radioButton0xD35428->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3542C_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciATempInvalid;

           if( radioButton0xD3542C->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD354BE_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciVVehCogInvalid;

           if( radioButton0xD354BE->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD354FF_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciConVehCrc;

           if( radioButton0xD354FF->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35565_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciConVehAlive;

           if( radioButton0xD35565->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3560C_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciConVehTimeout;

           if( radioButton0xD3560C->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3565E_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciConVehInvalid;

           if( radioButton0xD3565E->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3567D_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciEinheitenBn2020Timeout;

           if( radioButton0xD3567D->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35694_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRdcDtPckg1Timeout;

           if( radioButton0xD35694->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35713_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciEinheitenBn2020Invalid;

           if( radioButton0xD35713->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35720_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRdcDtPckg1Alive;

           if( radioButton0xD35720->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35777_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRdcDtPckg1Invalid;

           if( radioButton0xD35777->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD359DF_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRelativzeitTimeout;

           if( radioButton0xD359DF->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD35AE9_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciRelativzeitInvalid;

           if( radioButton0xD35AE9->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3673D_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciVVehTimeout;

           if( radioButton0xD3673D->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3673E_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciVVehAliveFailure;

           if( radioButton0xD3673E->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

private: System::Void radioButton0xD3673F_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucDtcNo = cDemErrorRdciVVehCrcFailure;

           if( radioButton0xD3673F->Checked == true)
           {
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2] == 0xFFu))
             {
               label0x1702_SAE_CODE_Value->Text           = "-";
             }else{
               label0x1702_SAE_CODE_Value->Text           = System::String::Format( "0x{0:X4}", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[0]        <<  0) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[1]        <<  8) +
                                                                                                  ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1702_SAE_CODE[2]        << 16))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME                == 0xFFFFFFFFu) { label0x1768_KM_STAND_SUPREME_Value->Text                = "-"; }else{ label0x1768_KM_STAND_SUPREME_Value->Text                = System::String::Format( "{0} km",          tRDCiDtclist[ucDtcNo].tUwb.ul0x1768_KM_STAND_SUPREME); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[5] == 0xFFu))
             {
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = "-";
             }else{
               label0x1769_SYSTEMZEIT_SUPREME_Value->Text = System::String::Format( "{0} s", ( ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[0] <<  0) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[1] <<  8) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[2] << 16) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[3] << 24) +
                                                                                               ((uint32) tRDCiDtclist[ucDtcNo].tUwb.auc0x1769_SYSTEMZEIT_SUPREME[4] << 32))
);
             }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE == 0xFFu) { label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = "-"; }else{ label0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE_Value->Text = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x190D_FUNKTIONEN_REIFENDRUCKKONTROLLE); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR                == 0x7Fu) { label0x2805_AUSSENTEMPERATUR_Value->Text                = "-"; }else{ label0x2805_AUSSENTEMPERATUR_Value->Text                = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x2805_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG                == 0xFFu) { label0x2866_BETRIEBSSPANNUNG_Value->Text                = "-"; }else{ label0x2866_BETRIEBSSPANNUNG_Value->Text                = System::String::Format( "{0} V",           tRDCiDtclist[ucDtcNo].tUwb.uc0x2866_BETRIEBSSPANNUNG); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT         == 0xFFu) { label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = "-"; }else{ label0x2867_FAHRZEUGGESCHWINDIGKEIT_Value->Text         = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x2867_FAHRZEUGGESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER           == 0xFFu) { label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = "-"; }else{ label0x4100_RDC_SENSOR_HERSTELLER_Value->Text           = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4100_RDC_SENSOR_HERSTELLER); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR   == 0x7Fu) { label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x4101_RDC_REFERENZ_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4101_RDC_REFERENZ_AUSSENTEMPERATUR); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]            == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1]            == 0xFFu)) { label0x4102_RDC_AUSSENDRUCK_Value->Text                 = "-"; }else{ label0x4102_RDC_AUSSENDRUCK_Value->Text                 = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[0]    << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4102_RDC_AUSSENDRUCK[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1]         == 0xFFu)) { label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = "-"; }else{ label0x4103_RDC_REIFENDRUCK_VL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4103_RDC_REIFENDRUCK_VL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1]         == 0xFFu)) { label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = "-"; }else{ label0x4104_RDC_REIFENDRUCK_VR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4104_RDC_REIFENDRUCK_VR[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1]         == 0xFFu)) { label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = "-"; }else{ label0x4105_RDC_REIFENDRUCK_HL_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4105_RDC_REIFENDRUCK_HL[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1]         == 0xFFu)) { label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = "-"; }else{ label0x4106_RDC_REIFENDRUCK_HR_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4106_RDC_REIFENDRUCK_HR[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL         == 0x7Fu) { label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = "-"; }else{ label0x4107_RDC_REIFENTEMPERATUR_VL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4107_RDC_REIFENTEMPERATUR_VL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR         == 0x7Fu) { label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = "-"; }else{ label0x4108_RDC_REIFENTEMPERATUR_VR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4108_RDC_REIFENTEMPERATUR_VR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL         == 0x7Fu) { label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = "-"; }else{ label0x4109_RDC_REIFENTEMPERATUR_HL_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x4109_RDC_REIFENTEMPERATUR_HL); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR         == 0x7Fu) { label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = "-"; }else{ label0x410A_RDC_REIFENTEMPERATUR_HR_Value->Text         = System::String::Format( "{0} °C",          (sint8) tRDCiDtclist[ucDtcNo].tUwb.uc0x410A_RDC_REIFENTEMPERATUR_HR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR   == 0x7Fu) { label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = "-"; }else{ label0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR_Value->Text   = System::String::Format( "{0} °C",          tRDCiDtclist[ucDtcNo].tUwb.sc0x410B_RDC_AKTUELLE_AUSSENTEMPERATUR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS              == 0xFFu) { label0x410C_RDC_INAKTIV_STATUS_Value->Text              = "-"; }else{ label0x410C_RDC_INAKTIV_STATUS_Value->Text              = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410C_RDC_INAKTIV_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS         == 0xFFu) { label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = "-"; }else{ label0x410D_RDC_KALIBRIERUNG_STATUS_Value->Text         = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410D_RDC_KALIBRIERUNG_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS                      == 0xFFu) { label0x410E_RDC_STATUS_Value->Text                      = "-"; }else{ label0x410E_RDC_STATUS_Value->Text                      = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410E_RDC_STATUS); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION               == 0xFFu) { label0x410F_RDC_KONFIGURATION_Value->Text               = "-"; }else{ label0x410F_RDC_KONFIGURATION_Value->Text               = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x410F_RDC_KONFIGURATION); }

             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]         == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1]         == 0xFFu)) { label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = "-"; }else{ label0x4110_RDC_SOLLDRUCK_VORN_Value->Text              = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[0]   << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4110_RDC_SOLLDRUCK_VORN[1])); }
             if( (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0]       == 0xFFu) &&
                 (tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1]       == 0xFFu)) { label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = "-"; }else{ label0x4111_RDC_SOLLDRUCK_HINTEN_Value->Text            = System::String::Format( "{0} hPa",         ((tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[0] << 8) + tRDCiDtclist[ucDtcNo].tUwb.auc0x4111_RDC_SOLLDRUCK_HINTEN[1])); }

             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION                    == 0xFFu) { label0x4112_RDC_POSITION_Value->Text                    = "-"; }else{ label0x4112_RDC_POSITION_Value->Text                    = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x4112_RDC_POSITION); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR      == 0xFFu) { label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = "-"; }else{ label0x5008_SPANNUNGSMASTER_VERFUEGBAR_Value->Text      = System::String::Format( "{0}",             tRDCiDtclist[ucDtcNo].tUwb.uc0x5008_SPANNUNGSMASTER_VERFUEGBAR); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT                 == 0xFFu) { label0x500A_GESCHWINDIGKEIT_Value->Text                 = "-"; }else{ label0x500A_GESCHWINDIGKEIT_Value->Text                 = System::String::Format( "{0} km/h",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500A_GESCHWINDIGKEIT); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND               == 0xFFFFu) { label0x500B_FUNKTIONSZUSTAND_Value->Text                = "-"; }else{ label0x500B_FUNKTIONSZUSTAND_Value->Text                = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500B_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND       == 0xFFu) { label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = "-"; }else{ label0x500C_INTERNER_FUNKTIONSZUSTAND_Value->Text       = System::String::Format( "0x{0:X2}",        tRDCiDtclist[ucDtcNo].tUwb.uc0x500C_INTERNER_FUNKTIONSZUSTAND); }
             if( tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER           == 0xFFFFu) { label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = "-"; }else{ label0x500E_INTERNE_FEHLERNUMMER_Value->Text            = System::String::Format( "0x{0:X4}",        tRDCiDtclist[ucDtcNo].tUwb.ush0x500E_INTERNE_FEHLERNUMMER); }
           }
         }

#endif

