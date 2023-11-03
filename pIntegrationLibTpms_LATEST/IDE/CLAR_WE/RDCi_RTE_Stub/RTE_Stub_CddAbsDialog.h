#ifndef __RTE_STUB_CDD_ABS_DIALOG_H
#define __RTE_STUB_CDD_ABS_DIALOG_H

private: System::Void PutAbsDataTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
  static tCddAbsData myData = {0};
  static uint32 myTimestamp = 0;

  if( checkBoxDataSelection->Checked == false)
  {

    if(GETushSpeedFZZ() > 0)
    {
      myData.ABS_EDGE_CNT_FL+=1;
      if(myData.ABS_EDGE_CNT_FL == 65535)
        myData.ABS_EDGE_CNT_FL = 0;
      myData.ABS_EDGE_CNT_FR+=2;
      myData.ABS_EDGE_CNT_RL+=3;
      myData.ABS_EDGE_CNT_RR+=4;
    }
    myData.ABS_QU_SIG_FL = 0;
    myData.ABS_QU_SIG_FR = 0;
    myData.ABS_QU_SIG_RL = 0;
    myData.ABS_QU_SIG_RR = 0;

    myTimestamp++;
    myData.ABS_SYNC_TSTMP_LO = (myTimestamp % 100) * 10 * 1000;
    myData.ABS_SYNC_TSTMP_HI = myTimestamp / 100;
    PutCddAbsData(&myData);
  }
}

private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
  unsigned char myString[100];

  OpenDataFile_rst = gcnew OpenFileDialog;

  OpenDataFile_rst->InitialDirectory = "C:\\_ECU2\\BMW\\@Test\\@STUB";
  OpenDataFile_rst->Filter = "txt files (*.txt)|*.txt|csv files (*.csv)|*.csv|All files (*.*)|*.*";
  OpenDataFile_rst->FilterIndex = 1;
  OpenDataFile_rst->RestoreDirectory = true;

  if( OpenDataFile_rst->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
      if( (myStream = OpenDataFile_rst->OpenFile()) != nullptr)
      {
        fileStreamIsOpen = 1;
        ReadStringFromStream(myString, myStream, sizeof(myString));
        checkBoxDataSelection->Enabled = true;
        checkBoxDataSelection->Checked = true;
        labelFilename->Text = OpenDataFile_rst->FileName;

      }
  }
}

private: System::Void CanMessageTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{

  static uint8 ToggleDpNo = 0;
  RdcDataType * ptData;

  Rdci_WMOM_DRV_4_Type myWMOM_DRV_4_Data = {0};

  tCddAbsData absData = {0};
  tCddRdcData rdcData = {0};

  Rdci_V_VEH_Type speedData = {0};
  Rdci_TEMP_EX_Type temperatureData = 0;
  Rdci_AIP_ENG_DRV_Type pressureData = 0;

  BedienungFahrwerkRecType tBedienungFahrwerk;
  EinheitenBn2020RecType tEinheitenBn2020;

  GpsAltitudeType tGpsAltitude;

  tCodingDataDeclCD tCodingData;

  uint16 ushTemp;

  uint8 direction = 0x03;
  uint8 ucPwfData;

  uint32 tyrID = 0xffffffff;
  unsigned long long ullMsgTimestamp = 0xffffffff;
  short checkID = 0;
  signed char scTemperature;
  uint16 ushAmbientPressure;

  uint8 ucHistSlot;

  uint32 msgType = 0;

  (void)SetTeleFilter(TELE_FILTER_OFF);
  if(checkBoxUseHufTelegrams->Checked == TRUE)
  {
    (void)SetTeleFilter(TELE_FILTER_HUF);
  }
  if(checkBoxUseSchraderTelegrams->Checked == TRUE)
  {
    (void)SetTeleFilter(TELE_FILTER_SCHRADER);
  }
  if(checkBoxUseContiTelegrams->Checked == TRUE)
  {
    (void)SetTeleFilter(TELE_FILTER_CONTI);
  }

  lastStreamPosition = myStream->Position;

  msgType = (uint32) ReadLongIntFromStream(myStream);

  switch ( msgType)
  {

    case 0:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &absData);

      if(numericNoOfABSMsgs->Value < numericNoOfABSMsgs->Maximum)
      {
        numericNoOfABSMsgs->Value++;
      }

      pbarABSQueueLevel->Value = PutCddAbsData( &absData);
      numericABSTimestamps->Value = (unsigned long long) ullMsgTimestamp;
    break;

    case 1:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &speedData);

      if(checkBoxSelSpeedSource->Checked == true)
      {
        checkVVehMissing->Checked = false;

        if(numericNoOfSpeedMsgs->Value < numericNoOfSpeedMsgs->Maximum)
        {
          numericNoOfSpeedMsgs->Value++;
        }

        if( speedData.V_VEH_COG > (uint16) (numericFileInputSpeed->Maximum / (Decimal) 0.015625))
        {

          numericFileInputSpeed->Value = (uint16) numericFileInputSpeed->Maximum;
          ValueV_VEH_COG->Value = numericFileInputSpeed->Value;
          SliderV_VEH_COG->Value = System::Decimal::ToUInt16( ValueV_VEH_COG->Value);
        }else{

          numericFileInputSpeed->Value = (uint16) (speedData.V_VEH_COG * 0.015625);
          ValueV_VEH_COG->Value = numericFileInputSpeed->Value;
          SliderV_VEH_COG->Value = System::Decimal::ToUInt16( ValueV_VEH_COG->Value);
        }
      }
    break;

    case 2:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &temperatureData);

      if(checkBoxSelTempExSource->Checked == true)
      {
        checkATempMissing->Checked = false;

        if(numericNoOfTemperatureMsgs->Value < numericNoOfTemperatureMsgs->Maximum)
        {
          numericNoOfTemperatureMsgs->Value++;
        }

        if( temperatureData > (Rdci_TEMP_EX_Type) ((numericFileInputTemp->Maximum + 40) * 2))
        {

          numericFileInputTemp->Value = (sint8) numericFileInputTemp->Maximum;
          ValueTEMP_EX->Value = numericFileInputTemp->Value;
          SliderTEMP_EX->Value = System::Decimal::ToInt16(numericFileInputTemp->Value);
        }else{

          numericFileInputTemp->Value = (sint8) (temperatureData / 2 - 40);
          ValueTEMP_EX->Value = numericFileInputTemp->Value;
          SliderTEMP_EX->Value = System::Decimal::ToInt16(numericFileInputTemp->Value);
        }
      }else{

      }
    break;

    case 3:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &direction);

      if(checkBoxSelGearSource->Checked == true)
      {
				checkWmomMissing->Checked = false;

        if(numericNoOfGearMsgs->Value < numericNoOfGearMsgs->Maximum)
        {
          numericNoOfGearMsgs->Value++;
        }

        switch ( direction)
        {
          case ST_DRVDIR_DVCH_FahrtrichtungswunschVorwaerts:
            radioGearForward->Checked = TRUE;
            labelFileInputGear->Text = "forward";
          break;

          case ST_DRVDIR_DVCH_FahrtrichtungswunschRueckwaerts:
            radioGearReverse->Checked = TRUE;
            labelFileInputGear->Text = "reverse";
          break;

          default:
            radioGearNeutral->Checked = TRUE;
            labelFileInputGear->Text = "neutral";
            direction = ST_DRVDIR_DVCH_KeinFahrtrichtungswunschVorhanden;
          break;
        }

        myWMOM_DRV_4_Data.ST_DRVDIR_DVCH = direction;
      }else{

      }
    break;

    case 4:

      if( ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &rdcData) == 0)
      {

        if(numericNoOfRFMsgs->Value < numericNoOfRFMsgs->Maximum)
        {
          numericNoOfRFMsgs->Value++;
        }

        numericRDCTimestamps->Value = (unsigned long long) ullMsgTimestamp;

        if( (rdcData.PCKG_ID == cTelTypeTyreDOT) || (rdcData.PCKG_ID == cTelTypeTyreDIM) || (rdcData.PCKG_ID == cTelTypeTyreDataOE1) || (rdcData.PCKG_ID == cTelTypeTyreDataOE2) || (rdcData.PCKG_ID == cTelTypeTyreStatus))
        {

          ptData = ptGetRdcDataPtr( cRecEleIx_RID);

          ptData->tRecCddRdcData.RDC_MES_TSTMP     = rdcData.RDC_MES_TSTMP;
          ptData->tRecCddRdcData.SUPP_ID           = rdcData.SUPP_ID;
          ptData->tRecCddRdcData.TYR_ID            = rdcData.TYR_ID;
          ptData->tRecCddRdcData.PCKG_ID           = rdcData.PCKG_ID;
          ptData->tRecCddRdcData.RDC_DT_1          = rdcData.RDC_DT_1;
          ptData->tRecCddRdcData.RDC_DT_2          = rdcData.RDC_DT_2;
          ptData->tRecCddRdcData.RDC_DT_3          = rdcData.RDC_DT_3;
          ptData->tRecCddRdcData.RDC_DT_4          = rdcData.RDC_DT_4;
          ptData->tRecCddRdcData.RDC_DT_5          = rdcData.RDC_DT_5;
          ptData->tRecCddRdcData.RDC_DT_6          = rdcData.RDC_DT_6;
          ptData->tRecCddRdcData.RDC_DT_7          = rdcData.RDC_DT_7;
          ptData->tRecCddRdcData.RDC_DT_8          = rdcData.RDC_DT_8;
          ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_1 = rdcData.ALIV_RDC_DT_PCK_1;
          ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_2 = rdcData.ALIV_RDC_DT_PCK_2;
          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_LO = rdcData.RDC_SYNC_TSTMP_LO;
          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_HI = rdcData.RDC_SYNC_TSTMP_HI;

          tyrID = rdcData.TYR_ID | (rdcData.SUPP_ID << 28);         /* complete ID (Tyr ID and Supplier ID)             */
          ucHistSlot = ucGetColOfID( (const uint32 *) &tyrID);     /* History-Slot des empfangenen Telegramms besorgen */

          switch( ucHistSlot)
          {
            case cRecEleIx_Slot0:
              textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_RID));
              if( checkBoxMuteRE0->Checked == false)
              {
                PutRecCddRdcData( cRecEleIx_RID);
              }
            break;

            case cRecEleIx_Slot1:
              textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_RID));
              if( checkBoxMuteRE1->Checked == false)
              {
                PutRecCddRdcData( cRecEleIx_RID);
              }
            break;

            case cRecEleIx_Slot2:
              textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_RID));
              if( checkBoxMuteRE2->Checked == false)
              {
                PutRecCddRdcData( cRecEleIx_RID);
              }
            break;

            case cRecEleIx_Slot3:
              textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_RID));
              if( checkBoxMuteRE3->Checked == false)
              {
                PutRecCddRdcData( cRecEleIx_RID);
              }
            break;

            default:
              textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_RID));
              PutRecCddRdcData( cRecEleIx_RID);
            break;
          }

          if( TabRdcData->Visible == true)
          {
            if( radioButtonRID->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
          }
        }else if( rdcData.PCKG_ID == cTelTypeAlive)
        {

          ptData = ptGetRdcDataPtr( cRecEleIx_Alive);

          ptData->tRecCddRdcData.RDC_MES_TSTMP     = rdcData.RDC_MES_TSTMP;
          ptData->tRecCddRdcData.SUPP_ID           = rdcData.SUPP_ID;
          ptData->tRecCddRdcData.TYR_ID            = rdcData.TYR_ID;
          ptData->tRecCddRdcData.PCKG_ID           = rdcData.PCKG_ID;
          ptData->tRecCddRdcData.RDC_DT_1          = rdcData.RDC_DT_1;
          ptData->tRecCddRdcData.RDC_DT_2          = rdcData.RDC_DT_2;
          ptData->tRecCddRdcData.RDC_DT_3          = rdcData.RDC_DT_3;
          ptData->tRecCddRdcData.RDC_DT_4          = rdcData.RDC_DT_4;
          ptData->tRecCddRdcData.RDC_DT_5          = rdcData.RDC_DT_5;
          ptData->tRecCddRdcData.RDC_DT_6          = rdcData.RDC_DT_6;
          ptData->tRecCddRdcData.RDC_DT_7          = rdcData.RDC_DT_7;
          ptData->tRecCddRdcData.RDC_DT_8          = rdcData.RDC_DT_8;
          ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_1 = rdcData.ALIV_RDC_DT_PCK_1;
          ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_2 = rdcData.ALIV_RDC_DT_PCK_2;
          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_LO = rdcData.RDC_SYNC_TSTMP_LO;
          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_HI = rdcData.RDC_SYNC_TSTMP_HI;
          if(ToggleDpNo == 0)
          {
            ptData->tRecCddRdcData.DP_NO = 0x34;
            ToggleDpNo = 1;
          }
          else
          {
            ptData->tRecCddRdcData.DP_NO = 0x12;
            ToggleDpNo = 0;
          }

          PutRecCddRdcData( cRecEleIx_Alive);
          textBoxCountFBD4Alive->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( cRecEleIx_Alive));

          if( TabRdcData->Visible == true)
          {
            if( radioButtonFBD4Alive->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
          }
        }else{
          tyrID = rdcData.TYR_ID | (rdcData.SUPP_ID << 28);         /* complete ID (Tyr ID and Supplier ID)             */
          ucHistSlot = ucGetColOfID( (const uint32 *) &tyrID);     /* History-Slot des empfangenen Telegramms besorgen */

          ptData = ptGetRdcDataPtr( ucHistSlot);

          if( ptData->bSuppIdFromFile == TRUE)
          {
            ptData->tRecCddRdcData.SUPP_ID = rdcData.SUPP_ID;
            ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_2 = rdcData.ALIV_RDC_DT_PCK_2;
          } /* if( ptData->bSuppIdFromFile == TRUE) */

          if( ptData->bTyrIdFromFile == TRUE)
          {
            ptData->tRecCddRdcData.TYR_ID = rdcData.TYR_ID;
            ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_1 = rdcData.ALIV_RDC_DT_PCK_1;
          } /* if( ptData->bTyrIdFromFile == TRUE) */

          if( ptData->bPckgIdFromFile == TRUE)
          {
            ptData->tRecCddRdcData.PCKG_ID = rdcData.PCKG_ID;
          } /* if( ptData->bPckgIdFromFile == TRUE) */

          if( ptData->bDt1PressureFromFile == TRUE)
          {
            ptData->tRecCddRdcData.RDC_DT_1 = rdcData.RDC_DT_1;
          } /* if( ptData->bDt1PressureFromFile == TRUE) */

          if( ptData->bDt2TemperatureFromFile == TRUE)
          {
            ptData->tRecCddRdcData.RDC_DT_2 = rdcData.RDC_DT_2;
          } /* if( ptData->bDt2TemperatureFromFile == TRUE) */

          if( ptData->bWuDataFromFile == TRUE)
          {
            ptData->tRecCddRdcData.RDC_DT_3 = rdcData.RDC_DT_3;
            ptData->tRecCddRdcData.RDC_DT_4 = rdcData.RDC_DT_4;
            ptData->tRecCddRdcData.RDC_DT_5 = rdcData.RDC_DT_5;
            ptData->tRecCddRdcData.RDC_DT_6 = rdcData.RDC_DT_6;
            ptData->tRecCddRdcData.RDC_DT_7 = rdcData.RDC_DT_7;
            ptData->tRecCddRdcData.RDC_DT_8 = rdcData.RDC_DT_8;
            ptData->tRecCddRdcData.RDC_MES_TSTMP = rdcData.RDC_MES_TSTMP;
          } /* if( ptData->bWuDataFromFile == TRUE) */

          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_LO = rdcData.RDC_SYNC_TSTMP_LO;
          ptData->tRecCddRdcData.RDC_SYNC_TSTMP_HI = rdcData.RDC_SYNC_TSTMP_HI;

          switch( ucHistSlot)
          {
            case cRecEleIx_Slot0:
              textBoxCountRE0->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucHistSlot));
              if( checkBoxMuteRE0->Checked == false)
              {
                PutRecCddRdcData( ucHistSlot);
              }
            break;

            case cRecEleIx_Slot1:
              textBoxCountRE1->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucHistSlot));
              if( checkBoxMuteRE1->Checked == false)
              {
                PutRecCddRdcData( ucHistSlot);
              }
            break;

            case cRecEleIx_Slot2:
              textBoxCountRE2->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucHistSlot));
              if( checkBoxMuteRE2->Checked == false)
              {
                PutRecCddRdcData( ucHistSlot);
              }
            break;

            case cRecEleIx_Slot3:
              textBoxCountRE3->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucHistSlot));
              if( checkBoxMuteRE3->Checked == false)
              {
                PutRecCddRdcData( ucHistSlot);
              }
            break;

            default:
              textBoxCountREx->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucHistSlot));
              PutRecCddRdcData( ucHistSlot);
            break;
          }

          if( TabRdcData->Visible == true)
          {

            if( radioButtonRE0->Checked == true)
            {
              if( ucHistSlot == cRecEleIx_Slot0)
              {

                panelREInputDataFrame->Visible = false;
                panelREInputDataFrame->Visible = true;
              }
            }else if( radioButtonRE1->Checked == true)
            {
              if( ucHistSlot == cRecEleIx_Slot1)
              {

                panelREInputDataFrame->Visible = false;
                panelREInputDataFrame->Visible = true;
              }
            }else if( radioButtonRE2->Checked == true)
            {
              if( ucHistSlot == cRecEleIx_Slot2)
              {

                panelREInputDataFrame->Visible = false;
                panelREInputDataFrame->Visible = true;
              }
            }else if( radioButtonRE3->Checked == true)
            {
              if( ucHistSlot == cRecEleIx_Slot3)
              {

                panelREInputDataFrame->Visible = false;
                panelREInputDataFrame->Visible = true;
              }
            }else{
              if( ucHistSlot == cRecEleIx_FR)
              {

                panelREInputDataFrame->Visible = false;
                panelREInputDataFrame->Visible = true;
              }
            }
          } /* if( TabRdcData->Visible == true) */

          if(tyrID != 0xffffffff)
          {

            /* Show IDs in textbox and show the pressures of ID places 0..3 */
            checkID = SearchIDInList(tyrID);
            if((checkID & 0x100) == 0x100)
            {
              textRecognizedIDs->AppendText(System::String::Format("{0}\n", tyrID));
              checkID &= 0xff;
            }

            switch (checkID)
            {
              case 0:
                if( rdcData.RDC_DT_1 > 1) { numericPressureRE1->Value = (long) ((rdcData.RDC_DT_1 - 2) * 25); }else{ numericPressureRE1->Value = 0; }
                convertTemperatureRawToPhysical((uint8)rdcData.RDC_DT_2, &scTemperature);
                labelTempRE1->Text = System::String::Format("{0}°C", scTemperature);
              break;

              case 1:
                if( rdcData.RDC_DT_1 > 1) { numericPressureRE2->Value = (long) ((rdcData.RDC_DT_1 - 2) * 25); }else{ numericPressureRE2->Value = 0; }
                convertTemperatureRawToPhysical((uint8)rdcData.RDC_DT_2, &scTemperature);
                labelTempRE2->Text = System::String::Format("{0}°C", scTemperature);
              break;

              case 2:
                if( rdcData.RDC_DT_1 > 1) { numericPressureRE3->Value = (long) ((rdcData.RDC_DT_1 - 2) * 25); }else{ numericPressureRE3->Value = 0; }
                convertTemperatureRawToPhysical((uint8)rdcData.RDC_DT_2, &scTemperature);
                labelTempRE3->Text = System::String::Format("{0}°C", scTemperature);
              break;

              case 3:
                if( rdcData.RDC_DT_1 > 1) { numericPressureRE4->Value = (long) ((rdcData.RDC_DT_1 - 2) * 25); }else{ numericPressureRE4->Value = 0; }
                convertTemperatureRawToPhysical((uint8)rdcData.RDC_DT_2, &scTemperature);
                labelTempRE4->Text = System::String::Format("{0}°C", scTemperature);
              break;

              default: break;
            }
          }
        } /* if( (rdcData.PCKG_ID == ... */
      } /* if( ReadMessageFromFile( myStream, msgType, &msgTimestamp, (void *) &rdcData) == 0) */
    break;

    case 5:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &pressureData);

      if(checkBoxSelPressExSource->Checked == true)
      {
        checkAipMissing->Checked = false;

        if(numericNoOfAmbientPressureMsgs->Value < numericNoOfAmbientPressureMsgs->Maximum)
        {
          numericNoOfAmbientPressureMsgs->Value++;
        }

        ushAmbientPressure = (uint16) pressureData * 2 + 598;

        if( ushAmbientPressure < (uint16) numericFileInputAmbPres->Minimum)
        {

          numericFileInputAmbPres->Value = (uint16) numericFileInputAmbPres->Minimum;
          numericUpDownAIP_ENG_DRV->Value = numericFileInputAmbPres->Value;
          trackBarAIP_ENG_DRV->Value = System::Decimal::ToUInt16(numericFileInputAmbPres->Value);
        }else if( ushAmbientPressure > (uint16) numericFileInputAmbPres->Maximum)
        {

          numericFileInputAmbPres->Value = (uint16) numericFileInputAmbPres->Maximum;
          numericUpDownAIP_ENG_DRV->Value = numericFileInputAmbPres->Value;
          trackBarAIP_ENG_DRV->Value = System::Decimal::ToUInt16(numericFileInputAmbPres->Value);
        }else{

          numericFileInputAmbPres->Value = (uint16) ushAmbientPressure;
          numericUpDownAIP_ENG_DRV->Value = numericFileInputAmbPres->Value;
          trackBarAIP_ENG_DRV->Value = System::Decimal::ToUInt16(numericFileInputAmbPres->Value);
        }
      }else{

      }
    break;

    case 6:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &ucPwfData);

      if(checkBoxSetPWFSource->Checked == true)
      {
				checkConVehMissing->Checked = false;

        if(numericNoOfPwfMsgs->Value < numericNoOfPwfMsgs->Maximum)
        {
          numericNoOfPwfMsgs->Value++;
        }

        switch ( ucPwfData)
        {
          case ST_CON_VEH_Parken_BN_iO:
            radioButtonParken->Checked = true;
            labelFileInputPWF->Text = "Parken";
          break;

          case ST_CON_VEH_Standfunktionen_Kunde_nicht_im_FZG:
            if( radioButtonStandfunktionen->Checked == false)
            {

              radioButtonStandfunktionen->Checked = true;
              labelFileInputPWF->Text = "Standfunktion";
            }
          break;

          case ST_CON_VEH_Wohnen:
            radioButtonWohnen->Checked = true;
            labelFileInputPWF->Text = "Wohnen";
          break;

          case ST_CON_VEH_Pruefen_Analyse_Diagnose:
            radioButtonPAD->Checked = true;
            labelFileInputPWF->Text = "PAD";
          break;

          case ST_CON_VEH_Fahrbereitschaft_herstellen:
            radioButtonFBHerstellen->Checked = true;
            labelFileInputPWF->Text = "Fahrbereitschaft herstellen";
          break;

          case ST_CON_VEH_Fahren:
            radioButtonFahren->Checked = true;
            labelFileInputPWF->Text = "Fahren";
          break;

          case ST_CON_VEH_Fahrbereitschaft_beenden:
            radioButtonFBBeenden->Checked = true;
            labelFileInputPWF->Text = "Fahrbereitschaft beenden";
          break;

          case ST_CON_VEH_Signal_unbefuellt:
            checkConVehInvalid->Checked = true;
            labelFileInputPWF->Text = "ungueltig";
          break;

          default:

            if( checkConVehInvalid->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Signal_unbefuellt;
              labelFileInputPWF->Text = "ungueltig";
            }else if( radioButtonParken->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Parken_BN_iO;
              labelFileInputPWF->Text = "Parken";
            }else if( radioButtonStandfunktionen->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Standfunktionen_Kunde_nicht_im_FZG;
              labelFileInputPWF->Text = "Standfunktion";
            }else if( radioButtonWohnen->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Wohnen;
              labelFileInputPWF->Text = "Wohnen";
            }else if( radioButtonPAD->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Pruefen_Analyse_Diagnose;
              labelFileInputPWF->Text = "PAD";
            }else if( radioButtonFBHerstellen->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Fahrbereitschaft_herstellen;
              labelFileInputPWF->Text = "Fahrbereitschaft herstellen";
            }else if( radioButtonFahren->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Fahren;
              labelFileInputPWF->Text = "Fahren";
            }else if( radioButtonFBBeenden->Checked == true)
            {
              ucPwfData = ST_CON_VEH_Fahrbereitschaft_beenden;
              labelFileInputPWF->Text = "Fahrbereitschaft beenden";
            }else{
            }
          break;
        }
      }else{

      }
    break;

    case 7:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &tBedienungFahrwerk);

      if(checkBoxBedienungFahrwerkSource->Checked == true)
      {

        if(numericUpDownNoOfBedienungFahrwerkMsgs->Value < numericUpDownNoOfBedienungFahrwerkMsgs->Maximum)
        {
          numericUpDownNoOfBedienungFahrwerkMsgs->Value++;
        }

        SelectSeasonVal->SetSelected( tBedienungFahrwerk.OpTyrSeaTpct, TRUE);
        Beladungsauswahl->SetSelected( tBedienungFahrwerk.OpTarPLocoTpct, TRUE);

        if( tBedienungFahrwerk.OpSlctnTyrAvlb < SelectTyreListElement->Maximum)
        {
          SelectTyreListElement->Value  = System::Decimal::ToUInt16( tBedienungFahrwerk.OpSlctnTyrAvlb);
        }else{
          SelectTyreListElement->Value  = SelectTyreListElement->Maximum;
        }

        if( tBedienungFahrwerk.OpIdrMsg < Status_IdrMessage->Maximum)
        {
          Status_IdrMessage->Value      = System::Decimal::ToUInt16( tBedienungFahrwerk.OpIdrMsg);
        }else{
          Status_IdrMessage->Value      = Status_IdrMessage->Maximum;
        }

        if( tBedienungFahrwerk.OpIdrSlctn < operationIdrSelection->Maximum)
        {
          operationIdrSelection->Value  = System::Decimal::ToUInt16( tBedienungFahrwerk.OpIdrSlctn);
        }else{
          operationIdrSelection->Value      = operationIdrSelection->Maximum;
        }

        PutRqOl( &tBedienungFahrwerk.RqOlTpct);
        PutOpTpct( &tBedienungFahrwerk.OpTpct);
      }else{

      }
    break;

    case 8:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &tEinheitenBn2020);

      if(checkBoxSetUnitsSource->Checked == true)
      {
 				checkUnitsMissing->Checked = false;

        if(numericUpDownNoOfEinheitenBn2020Msgs->Value < numericUpDownNoOfEinheitenBn2020Msgs->Maximum)
        {
          numericUpDownNoOfEinheitenBn2020Msgs->Value++;
        }

        switch( tEinheitenBn2020.UnTemp)
        {
        case UN_TEMP_Default:
          break;

        case UN_TEMP_DegreeC:
          radioUnitCelsius->Checked = true;
          break;

        case UN_TEMP_DegreeF:
          radioUnitFahrenheit->Checked = true;
          break;

        default:
          break;
        }

        switch( tEinheitenBn2020.UnMile)
        {
        case UN_MILE_Default:
          break;

        case UN_MILE_Kilometer:
          radioUnitkmh->Checked = true;
          break;

        case UN_MILE_Meilen:
          radioUnitMile->Checked = true;
          break;

        default:
          break;
        }

        switch( tEinheitenBn2020.UnAip)
        {
        case UN_AIP_Default:
        case UN_AIP_bar:
          radioUnitBar->Checked = true;
          break;

        case UN_AIP_kPa:
          radioUnitKpa->Checked = true;
          break;

        case UN_AIP_psi:
          radioUnitPsi->Checked = true;
          break;

        default:
          break;
        }

      }else{

      }
    break;

    case 9:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &tGpsAltitude);

      if(checkBoxSelNMEARawData2Source->Checked == true)
      {
        checkBoxNMEARawData2Missing->Checked = false;

        if(numericUpDownNoOfGpsMessages->Value < numericUpDownNoOfGpsMessages->Maximum)
        {
          numericUpDownNoOfGpsMessages->Value++;
        }

        if( tGpsAltitude.PositionAltitude == 0xffff)
        {

          checkBoxGNSSPositionAltitudeInvalid->Checked = true;
          numericUpDownFileInputAltitudeMeters->Hexadecimal = true;
          numericUpDownFileInputAltitudeMeters->Value = (Rdci_GNSSPositionAltitude_Type) tGpsAltitude.PositionAltitude;
        }
        else
        {

          checkBoxGNSSPositionAltitudeInvalid->Checked = false;
          numericUpDownFileInputAltitudeMeters->Hexadecimal = false;
          numericUpDownFileInputAltitudeMeters->Value = System::Decimal::ToInt16( tGpsAltitude.PositionAltitude / 10 - 1000);
          numericUpDownGNSSPositionAltitude->Value = numericUpDownFileInputAltitudeMeters->Value;
        }

        if( tGpsAltitude.ErrorAltitudeMeters == 0xffff)
        {

          checkBoxGNSSErrorAltitudeMetersInvalid->Checked = true;
          numericUpDownFileInputErrorAltitudeMeters->Hexadecimal = true;
          numericUpDownFileInputErrorAltitudeMeters->Value = (Rdci_GNSSErrorAltitudeMeters_Type) tGpsAltitude.ErrorAltitudeMeters;
        }
        else
        {

          checkBoxGNSSErrorAltitudeMetersInvalid->Checked = false;
          numericUpDownFileInputErrorAltitudeMeters->Hexadecimal = false;
          numericUpDownFileInputErrorAltitudeMeters->Value = System::Decimal::ToUInt16( tGpsAltitude.ErrorAltitudeMeters / 100);
          numericUpDownGNSSPositionAltitude->Value = numericUpDownFileInputAltitudeMeters->Value;
        }

      }else{

      }
    break;

    case 20:

      (void) ReadMessageFromFile( myStream, msgType, &ullMsgTimestamp, (void *) &tCodingData);

      ushTemp = tCodingData.ucCRdciCorHoldOffTime * 5;

      if( ushTemp < numericUpDownCRdciCorHoldOffTime->Minimum)
      {
        ushTemp = (uint16) numericUpDownCRdciCorHoldOffTime->Minimum;
      }
      else
      {
        if( ushTemp > numericUpDownCRdciCorHoldOffTime->Maximum)
        {
          ushTemp = (uint16) numericUpDownCRdciCorHoldOffTime->Maximum;
        }
      }

      numericUpDownCRdciCorHoldOffTime->Value = ushTemp;

      ushTemp = tCodingData.ucCRdciMaxCorTime;

      if( ushTemp < numericUpDownCRdciMaxCorTime->Minimum)
      {
        ushTemp = (uint16) numericUpDownCRdciMaxCorTime->Minimum;
      }
      else
      {
        if( ushTemp > numericUpDownCRdciMaxCorTime->Maximum)
        {
          ushTemp = (uint16) numericUpDownCRdciMaxCorTime->Maximum;
        }
      }

      numericUpDownCRdciMaxCorTime->Value = (uint16) ushTemp;

      ushTemp = tCodingData.ucCRdciMaxCorRcp * 25;

      if( ushTemp < numericUpDownCRdciMaxCorRcp->Minimum)
      {
        ushTemp = (uint16) numericUpDownCRdciMaxCorRcp->Minimum;
      }
      else
      {
        if( ushTemp > numericUpDownCRdciMaxCorRcp->Maximum)
        {
          ushTemp = (uint16) numericUpDownCRdciMaxCorRcp->Maximum;
        }
      }

      numericUpDownCRdciMaxCorRcp->Value = (uint16) ushTemp;

      ReInitRdciSWC();
    break;

    default:

    break;
  }

  PutTimeFromFileLOG( ullMsgTimestamp);

  fileLineSize = System::Math::Max((myStream->Position - lastStreamPosition), fileLineSize);
  if((myStream->Position + fileLineSize) >= myStream->Length)
  {
    myStream->Close();
    fileStreamIsOpen = 0;

    CanMessageTimer->Stop();
    checkBoxDataSelection->Checked = false;
    checkBoxDataSelection->Enabled = false;
  }
}

private: System::Void checkBoxDataSelection_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucLoop;
            uint8         ucTabIx;
            RdcDataType * ptData;

            if( checkBoxDataSelection->Checked == true)
            {

              for( ucLoop = 0; ucLoop < cMaxReElements; ucLoop++)
              {
                ptData = ptGetRdcDataPtr( ucLoop);

                ptData->bTyrIdFromFile          = TRUE;
                ptData->bSuppIdFromFile         = TRUE;
                ptData->bPckgIdFromFile         = TRUE;
                ptData->bDt1PressureFromFile    = TRUE;
                ptData->bDt2TemperatureFromFile = TRUE;
                ptData->bWuDataFromFile         = TRUE;
              }

              checkBoxTyrIdFromFile->Checked = true;
              checkBoxTyrIdFromFile->Enabled = true;

              checkBoxSuppIdFromFile->Checked = true;
              checkBoxSuppIdFromFile->Enabled = true;

              checkBoxPckgIdFromFile->Checked = true;
              checkBoxPckgIdFromFile->Enabled = true;

              checkBoxDt1PressureFromFile->Checked = true;
              checkBoxDt1PressureFromFile->Enabled = true;

              checkBoxDt2TemperatureFromFile->Checked = true;
              checkBoxDt2TemperatureFromFile->Enabled = true;

              checkBoxWuDataFromFile->Checked = true;
              checkBoxWuDataFromFile->Enabled = true;

              checkBoxSelTempExSource->Checked = true;
              checkBoxSelTempExSource->Enabled = true;
              checkATempMissing->Checked = true;

              checkBoxSelPressExSource->Checked = true;
              checkBoxSelPressExSource->Enabled = true;
              checkAipMissing->Checked = true;

              checkBoxSelSpeedSource->Checked = true;
              checkBoxSelSpeedSource->Enabled = true;
              checkVVehMissing->Checked = true;

              checkBoxSelNMEARawData2Source->Checked = true;
              checkBoxSelNMEARawData2Source->Enabled = true;
              checkBoxNMEARawData2Missing->Checked = true;

              checkBoxSelGearSource->Checked = true;
              checkBoxSelGearSource->Enabled = true;
              checkWmomMissing->Checked = true;

              checkBoxSetPWFSource->Checked = true;
              checkBoxSetPWFSource->Enabled = true;
              checkConVehMissing->Checked = true;

              checkBoxBedienungFahrwerkSource->Checked = true;
              checkBoxBedienungFahrwerkSource->Enabled = true;

              checkBoxSetUnitsSource->Checked = true;
              checkBoxSetUnitsSource->Enabled = true;
              checkUnitsMissing->Checked = true;

              checkBoxMuteRE0->Enabled = true;
              checkBoxMuteRE1->Enabled = true;
              checkBoxMuteRE2->Enabled = true;
              checkBoxMuteRE3->Enabled = true;

              buttonWheelUnitDataAcceptance->Enabled = false;

              checkBoxSendCyclicAliveTelegrams->Enabled = true;
              checkBoxSendCyclicAliveTelegrams->Checked = false;

              checkBoxAliveError->Enabled = false;
              checkBoxAliveError->Checked = false;
            }else{
              for( ucLoop = 0; ucLoop < cMaxReElements; ucLoop++)
              {
                ptData = ptGetRdcDataPtr( ucLoop);

                ptData->bTyrIdFromFile          = FALSE;
                ptData->bSuppIdFromFile         = FALSE;
                ptData->bPckgIdFromFile         = FALSE;
                ptData->bDt1PressureFromFile    = FALSE;
                ptData->bDt2TemperatureFromFile = FALSE;
                ptData->bWuDataFromFile         = FALSE;
              }

              checkBoxTyrIdFromFile->Checked = false;
              checkBoxTyrIdFromFile->Enabled = false;

              checkBoxSuppIdFromFile->Checked = false;
              checkBoxSuppIdFromFile->Enabled = false;

              checkBoxPckgIdFromFile->Checked = false;
              checkBoxPckgIdFromFile->Enabled = false;

              checkBoxDt1PressureFromFile->Checked = false;
              checkBoxDt1PressureFromFile->Enabled = false;

              checkBoxDt2TemperatureFromFile->Checked = false;
              checkBoxDt2TemperatureFromFile->Enabled = false;

              checkBoxWuDataFromFile->Checked = false;
              checkBoxWuDataFromFile->Enabled = false;

              checkBoxSelTempExSource->Checked = false;
              checkBoxSelTempExSource->Enabled = false;
              checkATempMissing->Checked = false;

              checkBoxSelPressExSource->Checked = false;
              checkBoxSelPressExSource->Enabled = false;
              checkAipMissing->Checked = false;

              checkBoxSelNMEARawData2Source->Checked = false;
              checkBoxSelNMEARawData2Source->Enabled = false;
              checkBoxNMEARawData2Missing->Checked = false;

              checkBoxSelSpeedSource->Checked = false;
              checkBoxSelSpeedSource->Enabled = false;
              checkVVehMissing->Checked = false;

              checkBoxSelGearSource->Checked = false;
              checkBoxSelGearSource->Enabled = false;
              checkWmomMissing->Checked = false;

              checkBoxSetPWFSource->Checked = false;
              checkBoxSetPWFSource->Enabled = false;
              checkConVehMissing->Checked = false;

              checkBoxBedienungFahrwerkSource->Checked = false;
              checkBoxBedienungFahrwerkSource->Enabled = false;

              checkBoxSetUnitsSource->Checked = false;
              checkBoxSetUnitsSource->Enabled = false;
              checkUnitsMissing->Checked = false;

              checkBoxMuteRE0->Enabled = false;
              checkBoxMuteRE1->Enabled = false;
              checkBoxMuteRE2->Enabled = false;
              checkBoxMuteRE3->Enabled = false;

              buttonWheelUnitDataAcceptance->Enabled = true;

              checkBoxSendCyclicAliveTelegrams->Enabled = true;
              checkBoxSendCyclicAliveTelegrams->Checked = true;

              if(radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }
              else if(radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }
              else if(radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }
              else if(radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }
              else if(radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }
              else if(radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }
              else
              {
                ucTabIx = cRecEleIx_Alive;
              }

              if( ucTabIx == cRecEleIx_Alive)
              {
                checkBoxAliveError->Enabled = false;
                checkBoxAliveError->Checked = false;
              }
              else
              {
                ptData = ptGetRdcDataPtr( ucTabIx);

                checkBoxAliveError->Enabled = true;
                checkBoxAliveError->Checked = ptData->bAliveError;
              }

            }

         }

private: System::Void buttonClearData_Click(System::Object^  sender, System::EventArgs^  e)
         {
           numericPressureRE1->Value = (long) 0;
           labelTempRE1->Text = "";

           numericPressureRE2->Value = (long) 0;
           labelTempRE2->Text = "";

           numericPressureRE3->Value = (long) 0;
           labelTempRE3->Text = "";

           numericPressureRE4->Value = (long) 0;
           labelTempRE4->Text = "";

           textRecognizedIDs->Text = "";

           (void) SearchIDInList( 0xFFFFFFFFu);
         }
#endif
