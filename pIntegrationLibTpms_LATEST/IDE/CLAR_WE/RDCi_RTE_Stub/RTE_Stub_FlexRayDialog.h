#ifndef __RTE_STUB_FLEXRAY_DIALOG_H
#define __RTE_STUB_FLEXRAY_DIALOG_H

  private: System::Void SetFRDataTimer_Tick(System::Object^  sender, System::EventArgs^  e)
  {
    sint16  temperatureHex;
    Rdci_TEMP_EX_Type myTemperature = 0;
    PhySensorTyrePresType ucEnvPressureHex;
    uint16  speedHex;
    uint8   myUnitMileData;
    uint8   myUnitAipData;
    uint8   myUnitTempData;
    Rdci_MILE_KM_Type ulHelp;

    static Rdci_V_VEH_Type myV_VEH = {0};
    static Rdci_WMOM_DRV_4_Type myWmomData = {0};
    static Rdci_CON_VEH_Type vehCondition = {0xff};
    static uint8 ucTime1sec = 0;
    static uint8 ucTime100msec = 0;

    Rdci_UHRZEIT_DATUM_Type timeDate;
    Rdci_T_SEC_COU_REL_Type relTime;
    StbMB_SystemTimeType sysTime;
    StbMB_SyncStatusType syncState;

    uint16 ushGpsAltitude;
    uint16 ushGpsAltitudeError;

    if(++ucTime1sec >= (1000 / PutFRDataTimer->Interval))
    {

      SynchronizeSystemTimes(&timeDate, &relTime, &syncState, &sysTime);

      if(checkUhrzeitDatumInvalid->Checked == TRUE)
      {
        timeDate.DISP_DATE_MON = 35;
      }
      if(checkUhrzeitDatumMissing->Checked == FALSE)
      {
        PutTimeDate(&timeDate);
      }

      if(checkRelativzeitInvalid->Checked == TRUE)
      {
        relTime = 0xffffffff;
      }
      if(checkRelativzeitMissing->Checked == FALSE)
      {
        PutRelTime(&relTime);
      }

      PutStbMBTime(&sysTime);
      PutStbMBSyncState(&syncState);

      temperatureHex = System::Decimal::ToInt16(ValueTEMP_EX->Value);
      temperatureHex += 40;
      temperatureHex *= 2;
      if(checkATempInvalid->Checked == TRUE)
      {
        myTemperature = 0xff;
      }
      else
      {
        myTemperature = (uint8)(temperatureHex & 0xff);
      }

      if(checkATempMissing->Checked == FALSE)
      {
        PutTemperatureData(&myTemperature);
      }

      if(checkAipInvalid->Checked == TRUE)
      {
        ucEnvPressureHex = 0xff;
      }
      else if(checkBoxAipInit->Checked == TRUE)
      {
        ucEnvPressureHex = 0x00;
      }
      else
      {

        ucEnvPressureHex = (uint8) ((uint16) (((System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value) - 598) + 1) / 2));
      }

      if(checkAipMissing->Checked == FALSE)
      {
        PutAmbientPressure( &ucEnvPressureHex);
      }

      if(checkBoxGNSSPositionAltitudeInvalid->Checked == TRUE)
      {
        ushGpsAltitude = 0xffff;
      }
      else
      {

        ushGpsAltitude = (uint16) ((System::Decimal::ToInt16(numericUpDownGNSSPositionAltitude->Value) + 1000) * 10);
      }

      if(checkBoxGNSSErrorAltitudeMetersInvalid->Checked == TRUE)
      {
        ushGpsAltitudeError = 0xffff;
      }
      else
      {

        ushGpsAltitudeError = (uint16) (System::Decimal::ToInt16(numericUpDownGNSSErrorAltitudeMeters->Value) * 100);
      }

      if(checkBoxNMEARawData2Missing->Checked == FALSE)
      {
        PutPositionAltitude( &ushGpsAltitude);
        PutErrorAltitudeMeters( &ushGpsAltitudeError);
      }

      if(true == radioUnitMile->Checked)
      {
        myUnitMileData = 2;
      }
      else
      {
        myUnitMileData = 1;
      }

      if(true == radioUnitBar->Checked)
      {
        myUnitAipData = 1;
      }
      else if(true == radioUnitPsi->Checked)
      {
        myUnitAipData = 3;
      }
      else if(true == radioUnitKpa->Checked)
      {
        myUnitAipData = 2;
      }

      if(true == radioUnitCelsius->Checked)
      {
        myUnitTempData = 1;
      }
      else
      {
        myUnitTempData = 2;
      }

      if(checkUnitsInvalid->Checked == TRUE)
      {
        myUnitAipData = ePRESSURE_UNIT_INVALID;
        myUnitTempData = eTEMPERATURE_UNIT_INVALID;
        myUnitMileData = eMILEAGE_UNIT_INVALID;
      }

      if(checkUnitsMissing->Checked == FALSE)
      {
        PutUnitDataAip(&myUnitAipData);
        PutUnitDataTemp(&myUnitTempData);
        PutUnitDataMile(&myUnitMileData);
      }

      if(checkMileKmInvalid->Checked == TRUE)
      {
        ulHelp = 0xffffffu;
      }
      else
      {
        ulHelp = System::Decimal::ToInt32(mileageKilometer->Value);
      }
      PutMileKm(&ulHelp);

      ucTime1sec = 0;
    }

    if(++ucTime100msec >= (100 / PutFRDataTimer->Interval))
    {

      if(checkConVehAlive->Checked == FALSE)
      {
        vehCondition.ALIV_CON_VEH++;
      }
      if(vehCondition.ALIV_CON_VEH == 0xf)
      {
        vehCondition.ALIV_CON_VEH = 0;
      }

      if(checkConVehQualifier->Checked == TRUE)
      {
        vehCondition.QU_ST_CON_VEH = QU_ST_CON_VEH_SignalUnbefuellt;
      }
      else
      {
        vehCondition.QU_ST_CON_VEH = QU_ST_CON_VEH_SignalwertGueltig;
      }

      vehCondition.CRC_CON_VEH = (uint8) System::Decimal::ToUInt16(numericUpDownST_CON_VEH_E2E_CRC->Value);

      if(checkConVehInvalid->Checked == TRUE)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Signal_unbefuellt;
      }
      else if(radioButtonFahren->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Fahren;
      }
      else if(radioButtonParken->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Parken_BN_iO;
      }
      else if(radioButtonStandfunktionen->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Standfunktionen_Kunde_nicht_im_FZG;
      }
      else if(radioButtonWohnen->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Wohnen;
      }
      else if(radioButtonPAD->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Pruefen_Analyse_Diagnose;
      }
      else if(radioButtonFBHerstellen->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Fahrbereitschaft_herstellen;
      }
      else if(radioButtonFBBeenden->Checked == true)
      {
        vehCondition.ST_CON_VEH = ST_CON_VEH_Fahrbereitschaft_beenden;
      }

      if(checkConVehMissing->Checked == FALSE)
      {
        PutVehicleCondition(&vehCondition);
      }

      if(checkWmomInvalid->Checked == TRUE)
      {
        myWmomData.ST_DRVDIR_DVCH = ST_DRVDIR_DVCH_SignalUngueltig;
      }

      else if(radioGearForward->Checked == true)
      {
        myWmomData.ST_DRVDIR_DVCH = ST_DRVDIR_DVCH_FahrtrichtungswunschVorwaerts;
      }

      else if(radioGearNeutral->Checked == true)
      {
        myWmomData.ST_DRVDIR_DVCH = ST_DRVDIR_DVCH_KeinFahrtrichtungswunschVorhanden;
      }

      else if(radioGearReverse->Checked == true)
      {
        myWmomData.ST_DRVDIR_DVCH = ST_DRVDIR_DVCH_FahrtrichtungswunschRueckwaerts;
      }

      myWmomData.ALIV_WMOM_DRV_4++;
      myWmomData.ALIV_WMOM_DRV_4 %= 14;
      textWMOMAlive->Text = System::String::Format("{0}", myWmomData.ALIV_WMOM_DRV_4);

      myWmomData.CRC_WMOM_DRV_4 = (uint8) System::Decimal::ToUInt16(numericUpDownWMOM_DRV_4_CRC->Value);
      if(checkWmomMissing->Checked == FALSE)
      {
        PutDirectionData(&myWmomData);
      }

      speedHex = System::Decimal::ToUInt16(ValueV_VEH_COG->Value);
      speedHex = (uint16)((double)(speedHex) / 0.015625);
      if(checkVVehInvalid->Checked == TRUE)
      {
        myV_VEH.V_VEH_COG = 0xffff;
      }
      else
      {
        myV_VEH.V_VEH_COG = speedHex;
      }

      if(checkVVehAlive->Checked == FALSE)
      {
        myV_VEH.ALIV_V_VEH++;
      }
      myV_VEH.ALIV_V_VEH %= 14;
      textVAlive->Text = System::String::Format("{0}", myV_VEH.ALIV_V_VEH);

      myV_VEH.CRC_V_VEH = (uint8) System::Decimal::ToUInt16(numericUpDownV_VEH_CRC->Value);

      if(checkVVehQualifier->Checked == TRUE)
      {
        myV_VEH.QU_V_VEH_COG = QU_V_VEH_COG_SignalwertIstUngueltigZustandSlashStatusTemporaer;
      }
      else
      {
        myV_VEH.QU_V_VEH_COG = QU_V_VEH_COG_SignalwertIstGueltigUndAbgesichertUndPlausib52XXOP;
      }

      if(checkVVehMissing->Checked == FALSE)
      {
        PutSpeedData(&myV_VEH);
      }

      ucTime100msec = 0;
    }
  }

  private: System::Void checkBoxFRBusOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(checkBoxFRBusOff->Checked == FALSE)
    {
      PutFRDataTimer->Enabled = FALSE;
    }
    else
    {
      PutFRDataTimer->Enabled = TRUE;
    }

  }

  private: System::Void checkFRBusState_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    ImpTypeValFrBusState myBusState;

    if(checkFRBusState->Checked == FALSE)
    {
      myBusState = FR_STATE_INACTIVE;
    }
    else
    {
      myBusState = FR_STATE_ACTIVE;
    }
    PutBusState(&myBusState);
  }

  private: System::Void SliderTEMP_EX_Scroll(System::Object^  sender, System::EventArgs^  e)
  {
    ValueTEMP_EX->Value = SliderTEMP_EX->Value;
  }

  private: System::Void ValueTEMP_EX_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
    SliderTEMP_EX->Value = System::Decimal::ToInt16(ValueTEMP_EX->Value);
  }

  private: System::Void checkBoxSelTempExSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    SliderTEMP_EX->Enabled = !(checkBoxSelTempExSource->Checked);
    ValueTEMP_EX->Enabled = !(checkBoxSelTempExSource->Checked);
  }

  private: System::Void trackBarAIP_ENG_DRV_Scroll(System::Object^  sender, System::EventArgs^  e)
  {
    numericUpDownAIP_ENG_DRV->Value = trackBarAIP_ENG_DRV->Value;
  }

  private: System::Void numericUpDownAIP_ENG_DRV_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {

    trackBarAIP_ENG_DRV->Value = System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value);

  }

  private: System::Void checkBoxSelPressExSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    trackBarAIP_ENG_DRV->Enabled = !(checkBoxSelPressExSource->Checked);
    numericUpDownAIP_ENG_DRV->Enabled = !(checkBoxSelPressExSource->Checked);
  }

  private: System::Void checkAipInvalid_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if( checkAipInvalid->Checked == true)
    {
      checkBoxAipInit->Checked = false;
    }
  }

  private: System::Void checkBoxAipInit_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if( checkBoxAipInit->Checked == true)
    {
      checkAipInvalid->Checked = false;
    }
  }

  private: System::Void trackBarGNSSPositionAltitude_Scroll(System::Object^  sender, System::EventArgs^  e)
  {
    numericUpDownGNSSPositionAltitude->Value = trackBarGNSSPositionAltitude->Value;
  }

  private: System::Void numericUpDownGNSSPositionAltitude_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {

    trackBarGNSSPositionAltitude->Value = System::Decimal::ToInt16(numericUpDownGNSSPositionAltitude->Value);

  }

  private: System::Void trackBarGNSSErrorAltitudeMeters_Scroll(System::Object^  sender, System::EventArgs^  e)
  {
    numericUpDownGNSSErrorAltitudeMeters->Value = trackBarGNSSErrorAltitudeMeters->Value;
  }

  private: System::Void numericUpDownGNSSErrorAltitudeMeters_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
    trackBarGNSSErrorAltitudeMeters->Value = System::Decimal::ToUInt16(numericUpDownGNSSErrorAltitudeMeters->Value);

  }

  private: System::Void checkBoxSelNMEARawData2Source_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    trackBarGNSSPositionAltitude->Enabled = !(checkBoxSelNMEARawData2Source->Checked);
    numericUpDownGNSSPositionAltitude->Enabled = !(checkBoxSelNMEARawData2Source->Checked);

    trackBarGNSSErrorAltitudeMeters->Enabled = !(checkBoxSelNMEARawData2Source->Checked);
    numericUpDownGNSSErrorAltitudeMeters->Enabled = !(checkBoxSelNMEARawData2Source->Checked);
  }

  private: System::Void SliderV_VEH_COG_Scroll(System::Object^  sender, System::EventArgs^  e)
  {
    ValueV_VEH_COG->Value = SliderV_VEH_COG->Value;
  }

  private: System::Void ValueV_VEH_COG_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
    SliderV_VEH_COG->Value = System::Decimal::ToUInt16(ValueV_VEH_COG->Value);
  }

  private: System::Void checkBoxSelSpeedSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    SliderV_VEH_COG->Enabled = !(checkBoxSelSpeedSource->Checked);
    ValueV_VEH_COG->Enabled = !(checkBoxSelSpeedSource->Checked);
  }

  private: System::Void radioButtonParken_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonParken->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonWohnen->Enabled = TRUE;
        radioButtonStandfunktionen->Enabled = TRUE;
        radioButtonPAD->Enabled = FALSE;
        radioButtonFBHerstellen->Enabled = FALSE;
        radioButtonFBBeenden->Enabled = FALSE;
        radioButtonFahren->Enabled = FALSE;
      }

      PutAbsDataTimer->Stop();
      PutRdcDataTimer->Stop();
    }
  }

  private: System::Void radioButtonStandfunktionen_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonStandfunktionen->Checked == TRUE)
    {

      timerRDCiCyclicTask->Stop();
      PutFRDataTimer->Stop();
      GetOutputDataTimer->Stop();
      PutAbsDataTimer->Stop();
      PutRdcDataTimer->Stop();
      CanMessageTimer->Stop();

      DataTabInputControl->Enabled = false;

      TabFlexRayData->Enabled = false;
      TabRdcData->Enabled = false;
      TabAbsData->Enabled = false;
      tabPageCalPrm->Enabled = false;
      tabPageRDCiConfig->Enabled = false;
      tabPageDCM->Enabled = false;
      tabRID->Enabled = false;
      tabPageUWB->Enabled = false;

      groupBoxOutputDataTimer->Enabled = true;
      groupBoxFlexRayTimer->Enabled = true;

      groupBoxRDCiTaskTimer->Enabled = true;
      groupBoxDataSelection->Enabled = true;

      NVM_WriteAll();
      NVM_WriteAllCalPrmBlocks();
      NVM_WriteAllDTC();

      NVM_ReadAll();
      NVM_ReadAllCalPrmBlocks();
      NVM_ReadAllDTC();

      ReadDtcListFromNvmBlock();

      groupBoxOutputDataTimer->Enabled = false;
      groupBoxFlexRayTimer->Enabled = false;
      groupBoxCddTimer->Enabled = false;
      groupBoxRDCiTaskTimer->Enabled = false;
      groupBoxDataSelection->Enabled = false;

      DataTabInputControl->Enabled = true;

      TabFlexRayData->Enabled = true;
      TabRdcData->Enabled = true;
      TabAbsData->Enabled = true;
      tabPageCalPrm->Enabled = true;
      tabPageRDCiConfig->Enabled = true;
      tabPageDCM->Enabled = true;
      tabRID->Enabled = true;
      tabPageUWB->Enabled = true;

      if(true == checkBoxDataSelection->Checked)
      {

        CanMessageTimer->Interval = System::Decimal::ToInt32(CanMsgTimerInterval->Value);
        CanMessageTimer->Start();
      }else{

      }

      /* Set and start data output timer (collect data from "RTE") */
      GetOutputDataTimer->Interval = System::Decimal::ToInt32(OutputTimerInterval->Value);
      GetOutputDataTimer->Start();

      /* Set RDCi Cyclic Task timer */
      timerRDCiCyclicTask->Interval = System::Decimal::ToInt32(numericUpDownRDCiCyclicTask->Value);
      timerRDCiCyclicTask->Start();

      /* Set FlexRay timer */
      PutFRDataTimer->Interval = System::Decimal::ToInt32(FrTimerInterval->Value);
      PutFRDataTimer->Start();

      /* Read ABS and RF data from CAN message file */

      RDCi_RInitRDCiStartup_002( Rte_Inst_CtApHufTpmsSWC);

      /* Init the Flexray tab elements */
      /* ----------------------------- */

      InitRecCddRdcData();

    } /* if(radioButtonStandfunktionen->Checked == TRUE) */
  } /* private: System::Void radioButtonStandfunktionen_CheckedChanged(System::Object^  sender, System::EventArgs^  e)  */

  private: System::Void radioButtonWohnen_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonWohnen->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonParken->Enabled = TRUE;
        radioButtonStandfunktionen->Enabled = TRUE;
        radioButtonPAD->Enabled = TRUE;
        radioButtonFBHerstellen->Enabled = TRUE;
        radioButtonFBBeenden->Enabled = FALSE;
        radioButtonFahren->Enabled = FALSE;
      }

      /* Timer fuer fiktive ABS/RDC Werte Generator */
      if(false == checkBoxDataSelection->Checked)
      {
        /* Set and start ABS data timer */

        PutAbsDataTimer->Interval = System::Decimal::ToInt32(ABSRecEvSimInterval->Value);
        PutAbsDataTimer->Start();

        PutRdcDataTimer->Interval = System::Decimal::ToInt32(RDCRecEvSimInterval->Value) * 1000;
        PutRdcDataTimer->Start();
      }
    }
  }

  private: System::Void radioButtonPAD_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonPAD->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonParken->Enabled = FALSE;
        radioButtonStandfunktionen->Enabled = FALSE;
        radioButtonWohnen->Enabled = TRUE;
        radioButtonFBHerstellen->Enabled = TRUE;
        radioButtonFBBeenden->Enabled = FALSE;
        radioButtonFahren->Enabled = TRUE;
      }
    }
  }

  private: System::Void radioButtonFahren_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonFahren->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonParken->Enabled = FALSE;
        radioButtonStandfunktionen->Enabled = FALSE;
        radioButtonWohnen->Enabled = FALSE;
        radioButtonPAD->Enabled = FALSE;
        radioButtonFBHerstellen->Enabled = FALSE;
        radioButtonFBBeenden->Enabled = TRUE;
      }

    }
  }

  private: System::Void radioButtonFBHerstellen_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonFBHerstellen->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonParken->Enabled = FALSE;
        radioButtonStandfunktionen->Enabled = FALSE;
        radioButtonWohnen->Enabled = TRUE;
        radioButtonPAD->Enabled = FALSE;
        radioButtonFahren->Enabled = TRUE;
        radioButtonFBBeenden->Enabled = TRUE;
      }

    }
  }

  private: System::Void radioButtonFBBeenden_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    if(radioButtonFBBeenden->Checked == TRUE)
    {
      if( checkBoxSetPWFSource->Checked == false)
      {
        radioButtonParken->Enabled = FALSE;
        radioButtonStandfunktionen->Enabled = FALSE;
        radioButtonWohnen->Enabled = TRUE;
        radioButtonPAD->Enabled = TRUE;
        radioButtonFahren->Enabled = FALSE;
        radioButtonFBHerstellen->Enabled = TRUE;
      }

    }
  }

  private: System::Void checkBoxSelGearSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    radioGearForward->Enabled = !(checkBoxSelGearSource->Checked);
    radioGearNeutral->Enabled = !(checkBoxSelGearSource->Checked);
    radioGearReverse->Enabled = !(checkBoxSelGearSource->Checked);
  }

  private: System::Void checkBoxSetPWFSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    radioButtonStandfunktionen->Enabled = !(checkBoxSetPWFSource->Checked);
    radioButtonParken->Enabled          = !(checkBoxSetPWFSource->Checked);
    radioButtonWohnen->Enabled          = !(checkBoxSetPWFSource->Checked);
    radioButtonPAD->Enabled             = !(checkBoxSetPWFSource->Checked);
    radioButtonFBHerstellen->Enabled    = !(checkBoxSetPWFSource->Checked);
    radioButtonFBBeenden->Enabled       = !(checkBoxSetPWFSource->Checked);
    radioButtonFahren->Enabled          = !(checkBoxSetPWFSource->Checked);
  }

  private: System::Void Beladungsauswahl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{

		uint8 ucBeladung;
		if(Beladungsauswahl->Text == "fullload")
		{
			ucBeladung = REQ_FULL_LOAD;
		}
		else
		{
			if(Beladungsauswahl->Text == "partload")
			{
				ucBeladung = REQ_PART_LOAD;
			}
			else
			{
				if(Beladungsauswahl->Text == "ecoload")
				{
					ucBeladung = REQ_ECO_LOAD;
				}
				else
				{
					ucBeladung = C2BIT_SIG_INVALID;
				}
			}
		}

		PutOpTarPLoco(&ucBeladung);
	}

	private: System::Void SelectSeasonVal_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		uint8 ucSeason;
		if(SelectSeasonVal -> Text == "summer")
		{
			ucSeason = CSEASON_SUMMER;
		}
		else
		{
			if(SelectSeasonVal -> Text == "winter")
			{
				ucSeason = CSEASON_WINTER;
			}
			else
			{
				if(SelectSeasonVal -> Text == "no change")
				{
					ucSeason = CSEASON_NOCHANGE;
				}
				else
				{
					ucSeason = C2BIT_SIG_INVALID;
				}
			}
		}
		PutOpTyrSeason(&ucSeason);
	}

	private: System::Void SelectTyreListElement_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{

		uint8 ucHelp;

		ucHelp = System::Decimal::ToByte(SelectTyreListElement->Value);

		if((ucHelp == 0x3e) || (ucHelp == 0x40))
		{
			SelectTyreListElement->Value = 0x00;
			ucHelp = 0x00;
		}

		if((ucHelp < 20) || (ucHelp == 0x3c) || (ucHelp == 0x3d))
		{

		}
		else
		{
			SelectTyreListElement->Value = 0x3F;
			ucHelp = 20;
		}

		PutOpSlctnTyr(&ucHelp);
	}

  private: System::Void Status_IdrMessage_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
    uint8 ucHelp;

		ucHelp = System::Decimal::ToByte(Status_IdrMessage->Value);

		if(ucHelp > 0x03)
		{
			Status_IdrMessage->Value = 0x03;
			ucHelp = 0x03;
		}

		PutStIdrMsgc(&ucHelp);
  }

  private: System::Void operationIdrSelection_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
    uint8 ucHelp;

		ucHelp = System::Decimal::ToByte(operationIdrSelection->Value);

		if(ucHelp > 0x03)
		{
			operationIdrSelection->Value = 0x03;
			ucHelp = 0x03;
		}

		PutOpIdrSlctn(&ucHelp);
  }

    private: System::Void buttonSendSetDataToWarnHler_Click(System::Object^  sender, System::EventArgs^  e)
	{

		uint8 ucHelp = 0x01;
		PutOpTpct(&ucHelp);
    }

	private: System::Void buttonCancelSelection_Click(System::Object^  sender, System::EventArgs^  e)
	{
		uint8 ucHelp = 0x02;
		PutOpTpct(&ucHelp);
	}

	private: System::Void buttonRequestTyreList1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		uint8 ucHelp = TRUE;
		PutRqOl(&ucHelp);
	}

  private: System::Void checkBoxBedienungFahrwerkSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    Beladungsauswahl->Enabled            = !(checkBoxBedienungFahrwerkSource->Checked);
    SelectSeasonVal->Enabled             = !(checkBoxBedienungFahrwerkSource->Checked);
    SelectTyreListElement->Enabled       = !(checkBoxBedienungFahrwerkSource->Checked);
    buttonSendSetDataToWarnHler->Enabled = !(checkBoxBedienungFahrwerkSource->Checked);
    buttonCancelSelection->Enabled       = !(checkBoxBedienungFahrwerkSource->Checked);
    buttonRequestTyreList1->Enabled      = !(checkBoxBedienungFahrwerkSource->Checked);
    Status_IdrMessage->Enabled           = !(checkBoxBedienungFahrwerkSource->Checked);
    operationIdrSelection->Enabled       = !(checkBoxBedienungFahrwerkSource->Checked);
  }

  private: System::Void checkBoxSetUnitsSource_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
    radioUnitkmh->Enabled         = !(checkBoxSetUnitsSource->Checked);
    radioUnitMile->Enabled        = !(checkBoxSetUnitsSource->Checked);
    radioUnitCelsius->Enabled     = !(checkBoxSetUnitsSource->Checked);
    radioUnitFahrenheit->Enabled  = !(checkBoxSetUnitsSource->Checked);
    radioUnitBar->Enabled         = !(checkBoxSetUnitsSource->Checked);
    radioUnitPsi->Enabled         = !(checkBoxSetUnitsSource->Checked);
    radioUnitKpa->Enabled         = !(checkBoxSetUnitsSource->Checked);
  }

#endif
