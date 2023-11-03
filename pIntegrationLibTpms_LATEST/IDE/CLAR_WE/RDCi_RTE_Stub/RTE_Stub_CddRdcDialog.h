#ifndef __RTE_STUB_CDD_RDC_DIALOG_H
#define __RTE_STUB_CDD_RDC_DIALOG_H

  private: System::Void PutRdcDataTimer_Tick(System::Object^  sender, System::EventArgs^  e)
  {

  }

private: System::Void buttonWheelUnitDataAcceptance_Click(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);

            PutRdcDataTimer->Stop();

            numericUpDownRdcMesTstmp->Value = (uint16) ulGetTimerTicks();

            ptData->ALIV_RDC_DT_PCK_1 = ucGetNextValidAliveCounter( ptData->ALIV_RDC_DT_PCK_1);

            if( checkBoxAliveError->Checked == true)
            {
              ptData->ALIV_RDC_DT_PCK_2 = ucGetNextValidAliveCounter( ptData->ALIV_RDC_DT_PCK_1);
            }else{
              ptData->ALIV_RDC_DT_PCK_2 = ptData->ALIV_RDC_DT_PCK_1;
            }

            numericUpDownAlive1->Value   = (unsigned char) ptData->ALIV_RDC_DT_PCK_1;
            numericUpDownAlive2->Value   = (unsigned char) ptData->ALIV_RDC_DT_PCK_2;

            ptData->RDC_DT_8 = 0;
            PutRecCddRdcData( ucTabIx);
            numericUpDownDt8Crc->Value = ptData->RDC_DT_8;

            switch( ucTabIx)
            {
              case cRecEleIx_Slot0:
                textBoxCountRE0->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              case cRecEleIx_Slot1:
                textBoxCountRE1->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              case cRecEleIx_Slot2:
                textBoxCountRE2->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              case cRecEleIx_Slot3:
                textBoxCountRE3->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              case cRecEleIx_FR:
                textBoxCountREx->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              case cRecEleIx_RID:
                textBoxCountRID->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));
              break;

              default:
                textBoxCountFBD4Alive->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucTabIx));

                numericUpDownDt4PalStatusHi->Value  = ptData->RDC_DT_4;

                ptData->RDC_DT_6++;
                if(ptData->RDC_DT_6 >= 0xfe)
                {
                  ptData->RDC_DT_6 = 0x00;
                }

                numericUpDownDt6->Value             = ptData->RDC_DT_6;
                numericUpDownAlive1->Value          = ptData->ALIV_RDC_DT_PCK_1;
                numericUpDownAlive2->Value          = ptData->ALIV_RDC_DT_PCK_2;
              break;
            }

            PutRdcDataTimer->Start();
         }

private: System::Void numericUpDownAlive1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->ALIV_RDC_DT_PCK_1 = (unsigned char) numericUpDownAlive1->Value;
         }

private: System::Void numericUpDownAlive2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->ALIV_RDC_DT_PCK_2 = (unsigned char) numericUpDownAlive2->Value;
         }

private: System::Void checkBoxAliveError_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            RdcDataType * ptData;

            if( checkBoxAliveError->Enabled == true)
            {
              if( radioButtonRE0->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_Slot0);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else if( radioButtonRE1->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_Slot1);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else if( radioButtonRE2->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_Slot2);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else if( radioButtonRE3->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_Slot3);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else if( radioButtonREx->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_FR);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else if( radioButtonRID->Checked == true)
              {
                ptData = ptGetRdcDataPtr(cRecEleIx_RID);

                ptData->bAliveError = checkBoxAliveError->Checked;
              }else{
                ptData = ptGetRdcDataPtr(cRecEleIx_Alive);

                ptData->bAliveError = false;
              }
            }
         }

private: System::Void numericUpDownTyrId_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            uint32 ulTyrId = (uint32) (System::Decimal::ToUInt32( numericUpDownTyrId->Value) & 0x0fffffff);

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);

            ptData->TYR_ID = ulTyrId;

            ulTyrId  |= (uint32) ((ptData->SUPP_ID & 0x0f) << 28);

            labelSuppAndTyrIdDez->Text = System::String::Format( "{0}", ulTyrId);
            labelSuppAndTyrIdHex->Text = System::String::Format( "0x{0:X8}", ulTyrId);
         }

private: System::Void checkBoxTyrIdFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bTyrIdFromFile = checkBoxTyrIdFromFile->Checked;

            if( checkBoxTyrIdFromFile->Checked == true)
            {
              numericUpDownTyrId->Enabled = false;
              numericUpDownAlive1->Enabled = false;

              checkBoxAliveError->Enabled = false;
              checkBoxAliveError->Checked = false;
            }else{
              numericUpDownTyrId->Enabled = true;
              numericUpDownAlive1->Enabled = true;

              if( ptData->bSuppIdFromFile == FALSE)
              {

                if( ucTabIx == cRecEleIx_Alive)
                {
                  checkBoxAliveError->Enabled = false;
                  checkBoxAliveError->Checked = false;
                }
                else
                {
                  checkBoxAliveError->Enabled = true;
                  checkBoxAliveError->Checked = ptData->bAliveError;
                }

              }else{
                checkBoxAliveError->Enabled = false;
                checkBoxAliveError->Checked = false;
              }
            }
         }

private: System::Void listBoxSuppId_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);

            if( listBoxSuppId->Text == "Autonet")
            {
              ptData->SUPP_ID = cSupplCodeAutonet;
              numericUpDownSuppId->Enabled = false;
            }else if( listBoxSuppId->Text == "Huf")
            {
              ptData->SUPP_ID = cSupplCodeHuf;
              numericUpDownSuppId->Enabled = false;
            }else if( listBoxSuppId->Text == "Conti")
            {
              ptData->SUPP_ID = cSupplCodeConti;
              numericUpDownSuppId->Enabled = false;
            }else if( listBoxSuppId->Text == "Schrader")
            {
              ptData->SUPP_ID = cSupplCodeSchrader;
              numericUpDownSuppId->Enabled = false;
            }else if( listBoxSuppId->Text == "unbekannt")
            {
              ptData->SUPP_ID = cSupplCodeUnknown;
              numericUpDownSuppId->Enabled = false;
            }else if( listBoxSuppId->Text == "unused")
            {
              ptData->SUPP_ID = cSupplCodeUnused;
              numericUpDownSuppId->Enabled = false;
            }else{
              numericUpDownSuppId->Enabled = true;
            }

            numericUpDownSuppId->Value = ptData->SUPP_ID;
         }

private: System::Void numericUpDownSuppId_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);

            ptData->SUPP_ID = (uint8) numericUpDownSuppId->Value;

            labelSuppAndTyrIdDez->Text = System::String::Format( "{0}", ((ptData->TYR_ID & 0x0fffffff) | ((ptData->SUPP_ID & 0x0f) << 28)));
            labelSuppAndTyrIdHex->Text = System::String::Format( "0x{0:X8}", ((ptData->TYR_ID & 0x0fffffff) | ((ptData->SUPP_ID & 0x0f) << 28)));
         }

private: System::Void checkBoxSuppIdFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bSuppIdFromFile = checkBoxSuppIdFromFile->Checked;

            if( checkBoxSuppIdFromFile->Checked == true)
            {
              numericUpDownSuppId->Enabled = false;
              listBoxSuppId->Enabled = false;
              numericUpDownAlive2->Enabled = false;

              checkBoxAliveError->Enabled = false;
              checkBoxAliveError->Checked = false;
            }else{
              if( listBoxSuppId->Text == "generic")
              {
                numericUpDownSuppId->Enabled = true;
              }else{
                numericUpDownSuppId->Enabled = false;
              }

              listBoxSuppId->Enabled = true;
              numericUpDownAlive2->Enabled = true;

              if( ptData->bTyrIdFromFile == FALSE)
              {

                if( ucTabIx == cRecEleIx_Alive)
                {
                  checkBoxAliveError->Enabled = false;
                  checkBoxAliveError->Checked = false;
                }
                else
                {
                  checkBoxAliveError->Enabled = true;
                  checkBoxAliveError->Checked = ptData->bAliveError;
                }

              }else{
                checkBoxAliveError->Enabled = false;
                checkBoxAliveError->Checked = false;
              }
            }
         }

private: System::Void listBoxPckgId_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

            numericUpDownPckgId->Enabled = false;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRdcDataPtr( ucTabIx);

            if( (ptData->bWuDataFromFile == FALSE))
            {
              if( listBoxPckgId->Text == "AK STD")
              {
                numericUpDownDt3PalLbt->Value = 0x00;
                numericUpDownDt4PalStatusHi->Value = 0x00;
                numericUpDownDt5PalStatusLo->Value = 0x00;
                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeAK35def;
              }else if( listBoxPckgId->Text == "PAL")
              {
                numericUpDownDt3PalLbt->Value = 0x00;

                if( numericUpDownDt3PalLbt->Value == 0)
                {
                  numericUpDownDt4PalStatusHi->Value = 0xA0;
                }else{
                  numericUpDownDt4PalStatusHi->Value = 0x60;
                }

                if( ptData->bBatteryEmpty == TRUE)
                {
                  numericUpDownDt5PalStatusLo->Value = (0x01 << 2);
                }else{
                  numericUpDownDt5PalStatusLo->Value = (0x0B << 2);
                }

                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeSELPAL;
              }else if( listBoxPckgId->Text == "PAL LB")
              {
                numericUpDownDt3PalLbt->Value = 0x00;

                if( numericUpDownDt3PalLbt->Value == 0)
                {
                  numericUpDownDt4PalStatusHi->Value = 0xA0;
                }else{
                  numericUpDownDt4PalStatusHi->Value = 0x60;
                }

                if( ptData->bBatteryEmpty == TRUE)
                {
                  numericUpDownDt5PalStatusLo->Value = (0x01 << 2);
                }else{
                  numericUpDownDt5PalStatusLo->Value = (0x0B << 2);
                }

                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeSELPAL1;
              }else if( listBoxPckgId->Text == "LOC SYNC")
              {
                if( ptData->bBatteryEmpty == TRUE)
                {
                  numericUpDownDt3PalLbt->Value = 12;
                }else{
                  numericUpDownDt3PalLbt->Value = 0x7f;
                }

                numericUpDownDt4PalStatusHi->Value = 0x00;
                numericUpDownDt5PalStatusLo->Value = 0x00;
                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeContiFP;
              }else if( listBoxPckgId->Text == "BERU long")
              {
                numericUpDownDt3PalLbt->Value = 0x00;
                numericUpDownDt4PalStatusHi->Value = 0x00;
                numericUpDownDt5PalStatusLo->Value = 0x00;
                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeBeruLong;
              }else if( listBoxPckgId->Text == "BERU med")
              {
                numericUpDownDt3PalLbt->Value = 0x00;
                numericUpDownDt4PalStatusHi->Value = 0x00;
                numericUpDownDt5PalStatusLo->Value = 0x00;
                numericUpDownDt6->Value = 0x00;
                numericUpDownDt7Rssi->Value = 0x00;
                numericUpDownDt8Crc->Value = 0x00;

                ptData->tRecCddRdcData.PCKG_ID = cTelTypeBeruMed;
              }else{
                numericUpDownPckgId->Enabled = true;
              }
            }

            numericUpDownPckgId->Value = (uint8) ptData->tRecCddRdcData.PCKG_ID;
          }

private: System::Void numericUpDownPckgId_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
         }

private: System::Void checkBoxPckgIdFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bPckgIdFromFile = checkBoxPckgIdFromFile->Checked;

            listBoxPckgId->Enabled = !(checkBoxPckgIdFromFile->Checked);
         }

private: System::Void checkBoxInputIsochor_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;
            Decimal dIsochorenSteigung;
            RdcDataType * ptData;

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
            else {
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRdcDataPtr(ucTabIx);

            ptData->bInputIsochor = checkBoxInputIsochor->Checked;

            if( checkBoxInputIsochor->Enabled == true)
            {
              switch (ucTabIx)
              {
                case cRecEleIx_Slot0:
                case cRecEleIx_Slot1:
                case cRecEleIx_Slot2:
                case cRecEleIx_Slot3:
                case cRecEleIx_FR:
                  if((ptData->tRecCddRdcData.RDC_DT_1 > cReAkPresUnderflow) && (ptData->tRecCddRdcData.RDC_DT_1 < cReAkPresOverflow) && (ptData->tRecCddRdcData.RDC_DT_2 > cReAkTempUnderflow) && (ptData->tRecCddRdcData.RDC_DT_2 < cReAkTempOverflow))
                  {

                    ptData->ushPabs_iso_hPa = (((((((ptData->tRecCddRdcData.RDC_DT_1 + 38) * 25) - 1000) + System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value)) * 10 + 125) / 250) * 25);
                    ptData->sshTabs_iso_K   = ((ptData->tRecCddRdcData.RDC_DT_2 - 52) + 273);

                    numericUpDownPabsWert->Hexadecimal = false;
                    numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                    numericUpDownTabsWert->Hexadecimal = false;
                    numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
                  }
                  else {

                    ptData->ushPabs_iso_hPa = (uint16) (((numericUpDownPabsWert->Maximum * 10 + 125) / 250) * 25);
                    ptData->sshTabs_iso_K   = (sint16) numericUpDownTabsWert->Maximum;

                    numericUpDownPabsWert->Hexadecimal = true;
                    numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                    numericUpDownTabsWert->Hexadecimal = true;
                    numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
                  }
                break;

                default:
                  ptData->ushPabs_iso_hPa = (uint16) (((numericUpDownPabsWert->Maximum * 10 + 125) / 250) * 25);
                  ptData->sshTabs_iso_K = (sint16)numericUpDownTabsWert->Maximum;

                  numericUpDownPabsWert->Hexadecimal = true;
                  numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                  numericUpDownTabsWert->Hexadecimal = true;
                  numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
                break;
              }
            }else{
              ptData->ushPabs_iso_hPa = (uint16) (((numericUpDownPabsWert->Maximum * 10 + 125) / 250) * 25);
              ptData->sshTabs_iso_K = (sint16) numericUpDownTabsWert->Maximum;

              numericUpDownPabsWert->Hexadecimal = true;
              numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

              numericUpDownTabsWert->Hexadecimal = true;
              numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
            }
         }

private: System::Void numericUpDownDt1Pressure_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            static boolean bSuppressValueChangedEvent = FALSE;

            float  fIsochorensteigung;
            uint16 ushPamb_hPa;
            uint16 ushPress_rel_hPa;
            uint16 ushPress_abs_hPa;
            sint16 sshTemp_abs_K;
            sint16 sshTisoShift_celsius;

            uint8 ucTabIx;
            Decimal dIsochorenSteigung;
            RdcDataType * ptData;

            if( bSuppressValueChangedEvent == FALSE)
            {
              bSuppressValueChangedEvent = TRUE;

              if( (numericUpDownDt1Pressure->Value % 25) != 0)
              {

                ushPress_rel_hPa = (uint16) ((numericUpDownDt1Pressure->Value * 10 + 125) / 250) * 25;
                numericUpDownDt1Pressure->Value = ushPress_rel_hPa;
              }

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRdcDataPtr( ucTabIx);

              ushPamb_hPa      = (uint16) System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value);
              ushPress_rel_hPa = (uint16) System::Decimal::ToUInt16(numericUpDownDt1Pressure->Value);
              ushPress_abs_hPa = ((((ushPress_rel_hPa + ushPamb_hPa) * 10 + 125) / 250) * 25);
              sshTemp_abs_K = (sint16) (System::Decimal::ToInt16(numericUpDownDt2Temperature->Value) + 273);
              fIsochorensteigung = ((float) ptData->ushPabs_iso_hPa / ptData->sshTabs_iso_K);

              if( (radioButtonDt1PressureSensorOk->Checked == true) && (radioButtonDt2TemperatureSensorOk->Checked == true))
              {

                if( checkBoxInputIsochor->Checked == true)
                {

                  sshTisoShift_celsius = (sint16) ((((float) ushPress_abs_hPa * 10 + 5) / (fIsochorensteigung * 10)) - 273);

                  if(sshTisoShift_celsius < numericUpDownDt2Temperature->Minimum)
                  {
                    sshTisoShift_celsius = (sint16) numericUpDownDt2Temperature->Minimum;
                  }else if(sshTisoShift_celsius > numericUpDownDt2Temperature->Maximum)
                  {
                    sshTisoShift_celsius = (sint16) numericUpDownDt2Temperature->Maximum;
                  }else{
                  }

                  if(sshTisoShift_celsius != numericUpDownDt2Temperature->Value)
                  {
                    numericUpDownDt2Temperature->Value = sshTisoShift_celsius;
                  }

                  ushPress_abs_hPa = ((uint16) ((((float) (sshTisoShift_celsius + 273) * fIsochorensteigung) * 10 + 125) / 250) * 25);

                  if(ushPress_abs_hPa > ushPamb_hPa)
                  {
                    ushPress_rel_hPa = (uint16) (((ushPress_abs_hPa - ushPamb_hPa) * 10 + 125) / 250) * 25;
                  }
                  else
                  {
                    ushPress_rel_hPa = 0;
                  }

                  if(ushPress_rel_hPa != numericUpDownDt1Pressure->Value)
                  {
                    numericUpDownDt1Pressure->Value = ushPress_rel_hPa;
                  }
                }else{
                  ptData->ushPabs_iso_hPa = ushPress_abs_hPa;
                  ptData->sshTabs_iso_K   = sshTemp_abs_K;

                  numericUpDownPabsWert->Hexadecimal = false;
                  numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                  numericUpDownTabsWert->Hexadecimal = false;
                  numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
                }
              }

              if( ushPress_abs_hPa < 1000)
              {

                numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Minimum;
                radioButtonDt1PressureSensorUnderflow->Checked = true;
              }else if( ushPress_abs_hPa > 7300)
              {

                numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Maximum;
                radioButtonDt1PressureSensorOverflow->Checked = true;
              }else{
                if( ((numericUpDownDt1Pressure->Value == numericUpDownDt1Pressure->Minimum) && (ptData->tRecCddRdcData.RDC_DT_1 == cReAkPresUnderflow)) ||
                    ((numericUpDownDt1Pressure->Value == numericUpDownDt1Pressure->Maximum) && (ptData->tRecCddRdcData.RDC_DT_1 == cReAkPresOverflow)))
                {

                }else{

                  ptData->tRecCddRdcData.RDC_DT_1 = (uint8) (((ushPress_abs_hPa - 1000) / 25) + 2);
                  radioButtonDt1PressureSensorOk->Checked = true;
                }
              }

              trackBarDt1Pressure->Value = System::Decimal::ToUInt16(numericUpDownDt1Pressure->Value);
            }

            bSuppressValueChangedEvent = FALSE;
         }

private: System::Void trackBarDt1Pressure_Scroll(System::Object^  sender, System::EventArgs^  e)
         {

            numericUpDownDt1Pressure->Value = trackBarDt1Pressure->Value;
         }

private: System::Void radioButtonDt1PressureSensorOk_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint16 ushPamb_hPa;
            uint16 ushPress_rel_hPa;
            uint16 ushPress_abs_hPa;
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt1PressureSensorOk->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);

              ushPamb_hPa      = (uint16) System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value);
              ushPress_rel_hPa = (uint16) System::Decimal::ToUInt16(numericUpDownDt1Pressure->Value);
              ushPress_abs_hPa = ((((ushPress_rel_hPa + ushPamb_hPa) * 10 + 125) / 250) * 25);

              if( ushPress_abs_hPa < 1000)
              {

                numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Minimum;
                radioButtonDt1PressureSensorUnderflow->Checked = true;
              }else if( ushPress_abs_hPa > 7300)
              {

                numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Maximum;
                radioButtonDt1PressureSensorOverflow->Checked = true;
              }else{

                ptData->RDC_DT_1 = (uint8) (((ushPress_abs_hPa - 1000) / 25) + 2);

                numericUpDownDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,255,255);
                trackBarDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,192,128);
              }
            }
         }

private: System::Void radioButtonDt1PressureSensorDefect_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt1PressureSensorDefect->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_1 = cReAkPresError;

              numericUpDownDt1Pressure->Enabled = false;
              trackBarDt1Pressure->Enabled = false;

              numericUpDownDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,0,0);
              trackBarDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,0,0);
            }else{
              numericUpDownDt1Pressure->Enabled = true;
              trackBarDt1Pressure->Enabled = true;

            }
         }

private: System::Void radioButtonDt1PressureSensorUnderflow_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {

            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt1PressureSensorUnderflow->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_1 = cReAkPresUnderflow;

              numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Minimum;

              numericUpDownDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,255,0);
              trackBarDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,255,0);

            }
         }

private: System::Void radioButtonDt1PressureSensorOverflow_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {

            uint8  ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt1PressureSensorOverflow->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_1 = cReAkPresOverflow;

              numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Maximum;

              numericUpDownDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,255,0);
              trackBarDt1Pressure->BackColor = System::Drawing::Color::FromArgb(255,255,0);

            }
         }

private: System::Void checkBoxDt1PressureFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bDt1PressureFromFile = checkBoxDt1PressureFromFile->Checked;

            if( checkBoxDt1PressureFromFile->Checked == true)
            {
              numericUpDownDt1Pressure->Enabled = false;
              trackBarDt1Pressure->Enabled = false;
              panelDt1PressureSensorState->Enabled = false;

              checkBoxInputIsochor->Enabled = false;
              checkBoxInputIsochor->Checked = false;
            }else{
              numericUpDownDt1Pressure->Enabled = true;
              trackBarDt1Pressure->Enabled = true;
              panelDt1PressureSensorState->Enabled = true;

              if( ptData->bDt2TemperatureFromFile == FALSE)
              {

                if( ucTabIx == cRecEleIx_Alive)
                {
                  checkBoxInputIsochor->Enabled = false;
                  checkBoxInputIsochor->Checked = false;
                }
                else
                {
                  checkBoxInputIsochor->Enabled = true;
                  checkBoxInputIsochor->Checked = ptData->bInputIsochor;
                }

              }else{
                checkBoxInputIsochor->Enabled = false;
                checkBoxInputIsochor->Checked = false;
              }
            }
         }

private: System::Void numericUpDownDt2Temperature_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            static boolean bSuppressValueChangedEvent = FALSE;

            float  fIsochorensteigung;
            uint16 ushPamb_hPa;
            uint16 ushPress_rel_hPa;
            uint16 ushPress_abs_hPa;
            sint16 sshTemp_abs_K;
            uint16 ushPisoShift_rel_hPa;

            uint8         ucTabIx;
            Decimal       dIsochorenSteigung;
            RdcDataType * ptData;

            if( bSuppressValueChangedEvent == FALSE)
            {
              bSuppressValueChangedEvent = TRUE;

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              if( ucTabIx != cRecEleIx_Alive)
              {
                ptData = ptGetRdcDataPtr( ucTabIx);

                if( (radioButtonDt1PressureSensorOk->Checked == true) && (radioButtonDt2TemperatureSensorOk->Checked == true))
                {

                  ushPamb_hPa = (uint16) System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value);
                  ushPress_rel_hPa = (uint16) System::Decimal::ToUInt16(numericUpDownDt1Pressure->Value);
                  ushPress_abs_hPa = ((((ushPress_rel_hPa + ushPamb_hPa) * 10 + 125) / 250) * 25);
                  sshTemp_abs_K = (sint16) (System::Decimal::ToInt16(numericUpDownDt2Temperature->Value) + 273);
                  fIsochorensteigung = ((float) ptData->ushPabs_iso_hPa / ptData->sshTabs_iso_K);

                  if( checkBoxInputIsochor->Checked == true)
                  {

                    ushPisoShift_rel_hPa = ((uint16) ((((((float) sshTemp_abs_K * fIsochorensteigung) - ushPamb_hPa) * 10) + 125) / 250) * 25);

                    if( ushPisoShift_rel_hPa < numericUpDownDt1Pressure->Minimum)
                    {
                      ushPisoShift_rel_hPa = (uint16) numericUpDownDt1Pressure->Minimum;
                    }else if( ushPisoShift_rel_hPa > numericUpDownDt1Pressure->Maximum)
                    {
                      ushPisoShift_rel_hPa = (uint16) numericUpDownDt1Pressure->Maximum;
                    }else{
                    }

                    if( ushPisoShift_rel_hPa != numericUpDownDt1Pressure->Value)
                    {
                      numericUpDownDt1Pressure->Value = ushPisoShift_rel_hPa;
                    }
                  }else{
                    ptData->ushPabs_iso_hPa = ushPress_abs_hPa;
                    ptData->sshTabs_iso_K   = sshTemp_abs_K;

                    numericUpDownPabsWert->Hexadecimal = false;
                    numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                    numericUpDownTabsWert->Hexadecimal = false;
                    numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;
                  }
                }

                ptData->tRecCddRdcData.RDC_DT_2 =  (uint8) ((signed int) numericUpDownDt2Temperature->Value + 52);
              }

              trackBarDt2Temperature->Value = System::Decimal::ToInt16( numericUpDownDt2Temperature->Value);
            }

            bSuppressValueChangedEvent = FALSE;
         }

private: System::Void trackBarDt2Temperature_Scroll(System::Object^  sender, System::EventArgs^  e)
         {

            numericUpDownDt2Temperature->Value = trackBarDt2Temperature->Value;
         }

private: System::Void radioButtonDt2TemperatureSensorOk_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt2TemperatureSensorOk->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_2 = (uint8) ((signed char) numericUpDownDt2Temperature->Value + 52);

              numericUpDownDt2Temperature->Enabled = true;
              trackBarDt2Temperature->Enabled = true;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,255);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,192,128);
            }
         }

private: System::Void radioButtonDt2TemperatureSensorDefect_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt2TemperatureSensorDefect->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_2 = cReAkTempError;

              numericUpDownDt2Temperature->Enabled = false;
              trackBarDt2Temperature->Enabled = false;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,0,0);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,0,0);
            }else{
              numericUpDownDt2Temperature->Enabled = true;
              trackBarDt2Temperature->Enabled = true;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,255);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,192,128);
            }
         }

private: System::Void radioButtonDt2TemperatureSensorUnderflow_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            sint8 scTemp;
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt2TemperatureSensorUnderflow->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_2 = cReHufAkTempUnderflow;

              numericUpDownDt2Temperature->Enabled = false;
              trackBarDt2Temperature->Enabled = false;

              numericUpDownDt2Temperature->Value = numericUpDownDt2Temperature->Minimum;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,0);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }else{
              scTemp = GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, 0);

              if( scTemp == cInvalidREtemperature)
              {

              }else{
                numericUpDownDt2Temperature->Value = scTemp;
              }

              numericUpDownDt2Temperature->Enabled = true;
              trackBarDt2Temperature->Enabled = true;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,255);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,192,128);
            }
         }

private: System::Void radioButtonDt2TemperatureSensorOverflow_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            sint8 scTemp;
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonDt2TemperatureSensorOverflow->Checked == true)
            {

              if( radioButtonRE0->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot0;
              }else if( radioButtonRE1->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot1;
              }else if( radioButtonRE2->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot2;
              }else if( radioButtonRE3->Checked == true)
              {
                ucTabIx = cRecEleIx_Slot3;
              }else if( radioButtonREx->Checked == true)
              {
                ucTabIx = cRecEleIx_FR;
              }else if( radioButtonRID->Checked == true)
              {
                ucTabIx = cRecEleIx_RID;
              }else{
                ucTabIx = cRecEleIx_Alive;
              }

              ptData = ptGetRecCddRdcDataPtr( ucTabIx);
              ptData->RDC_DT_2 = cReHufAkTempOverflow;

              numericUpDownDt2Temperature->Enabled = false;
              trackBarDt2Temperature->Enabled = false;

              numericUpDownDt2Temperature->Value = numericUpDownDt2Temperature->Maximum;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,0);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }else{
              scTemp = GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, 0);

              if( scTemp == cInvalidREtemperature)
              {

              }else{
                numericUpDownDt2Temperature->Value = scTemp;
              }

              numericUpDownDt2Temperature->Enabled = true;
              trackBarDt2Temperature->Enabled = true;

              numericUpDownDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,255,255);
              trackBarDt2Temperature->BackColor = System::Drawing::Color::FromArgb(255,192,128);
            }
         }

private: System::Void checkBoxDt2TemperatureFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bDt2TemperatureFromFile = checkBoxDt2TemperatureFromFile->Checked;

            if( checkBoxDt2TemperatureFromFile->Checked == true)
            {
              numericUpDownDt2Temperature->Enabled = false;
              trackBarDt2Temperature->Enabled = false;
              panelDt2TemperatureSensorState->Enabled = false;

              checkBoxInputIsochor->Enabled = false;
              checkBoxInputIsochor->Checked = false;

            }else{
              numericUpDownDt2Temperature->Enabled = true;
              trackBarDt2Temperature->Enabled = true;
              panelDt2TemperatureSensorState->Enabled = true;

              if( ptData->bDt1PressureFromFile == FALSE)
              {

                if( ucTabIx == cRecEleIx_Alive)
                {
                  checkBoxInputIsochor->Enabled = false;
                  checkBoxInputIsochor->Checked = false;
                }
                else
                {
                  checkBoxInputIsochor->Enabled = true;
                  checkBoxInputIsochor->Checked = ptData->bInputIsochor;
                }

              }else{
                checkBoxInputIsochor->Enabled = false;
                checkBoxInputIsochor->Checked = false;
              }
            }
         }

private: System::Void numericUpDownDt3PalLbt_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_3 = (unsigned char) numericUpDownDt3PalLbt->Value;
         }

private: System::Void numericUpDownDt4PalStatusHi_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_4 = (unsigned char) numericUpDownDt4PalStatusHi->Value;
         }

private: System::Void numericUpDownDt5PalStatusLo_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_5 = (unsigned char) numericUpDownDt5PalStatusLo->Value;
         }

private: System::Void numericUpDownDt6_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_6 = (unsigned char) numericUpDownDt6->Value;
         }

private: System::Void numericUpDownDt7Rssi_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_7 = (unsigned char) numericUpDownDt7Rssi->Value;
         }

private: System::Void numericUpDownDt8Crc_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_DT_8 = (unsigned char) numericUpDownDt8Crc->Value;
         }

private: System::Void numericUpDownRdcMesTstmp_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8 ucTabIx;

            ImpTypeRecCddRdcData * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRecCddRdcDataPtr( ucTabIx);
            ptData->RDC_MES_TSTMP = (uint16) numericUpDownRdcMesTstmp->Value;
         }

private: System::Void checkBoxSetBatteryEmpty_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData = ptGetRdcDataPtr( ucTabIx);
            ptData->bBatteryEmpty = checkBoxSetBatteryEmpty->Checked;

            if( ucTabIx <= cRecEleIx_FR)
            {
              if( (numericUpDownPckgId->Value == cTelTypeSELPAL) || (numericUpDownPckgId->Value == cTelTypeSELPAL1))
              {
                if( checkBoxSetBatteryEmpty->Checked == true)
                {
                  numericUpDownDt5PalStatusLo->Value = (0x01 << 2);
                }else{
                  numericUpDownDt5PalStatusLo->Value = (0x0B << 2);
                }

                if( numericUpDownDt3PalLbt->Value == 0)
                {
                  numericUpDownDt4PalStatusHi->Value = 0xA0;
                }else{
                  numericUpDownDt4PalStatusHi->Value = 0x60;
                }

                ptData->tRecCddRdcData.RDC_DT_4 = (uint8) numericUpDownDt4PalStatusHi->Value;
                ptData->tRecCddRdcData.RDC_DT_5 = (uint8) numericUpDownDt5PalStatusLo->Value;
              }else if( numericUpDownPckgId->Value == cTelTypeContiFP)
              {
                if( checkBoxSetBatteryEmpty->Checked == true)
                {
                  numericUpDownDt3PalLbt->Value = 12;
                }else{
                  numericUpDownDt3PalLbt->Value = 0x7f;
                }

                ptData->tRecCddRdcData.RDC_DT_3 = (uint8) numericUpDownDt3PalLbt->Value;
              }
            }
         }

private: System::Void checkBoxWuDataFromFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8         ucTabIx;
            RdcDataType * ptData;

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

            ptData = ptGetRdcDataPtr(ucTabIx);
            ptData->bWuDataFromFile = checkBoxWuDataFromFile->Checked;

            numericUpDownDt3PalLbt->Enabled       = !(checkBoxWuDataFromFile->Checked);
            numericUpDownDt4PalStatusHi->Enabled  = !(checkBoxWuDataFromFile->Checked);
            numericUpDownDt5PalStatusLo->Enabled  = !(checkBoxWuDataFromFile->Checked);
            numericUpDownDt6->Enabled             = !(checkBoxWuDataFromFile->Checked);
            numericUpDownDt7Rssi->Enabled         = !(checkBoxWuDataFromFile->Checked);
            numericUpDownDt8Crc->Enabled          = !(checkBoxWuDataFromFile->Checked);
            numericUpDownRdcMesTstmp->Enabled     = !(checkBoxWuDataFromFile->Checked);
            checkBoxSetBatteryEmpty->Enabled      = !(checkBoxWuDataFromFile->Checked);
         }

private: System::Void checkBoxMuteRE0_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
         }

private: System::Void checkBoxMuteRE1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
         }

private: System::Void checkBoxMuteRE2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)         {
         }

private: System::Void checkBoxMuteRE3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
         }

private: System::Void radioButtonRE0_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonRE0->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonRE1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonRE1->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonRE2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonRE2->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonRE3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonRE3->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonREx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonREx->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonRID_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
            if( radioButtonRID->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;
            }
         }

private: System::Void radioButtonFBD4Alive_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {

            if( radioButtonFBD4Alive->Checked == true)
            {

              panelREInputDataFrame->Visible = false;
              panelREInputDataFrame->Visible = true;

            }
         }

private: System::Void panelREInputDataFrame_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
         {
            uint8  ucLoop;
            uint8  ucWheelPos;
            uint16 ushPamb_hPa;
            uint16 ushPress_abs_hPa;

            uint8         ucTabIx;
            Decimal       dIsochorenSteigung;
            RdcDataType * ptData;

            for( ucLoop = 0; ucLoop < cMaxReElements; ucLoop++)
            {
              if( ucLoop == cRecEleIx_Slot0) textBoxCountRE0->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_Slot1) textBoxCountRE1->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_Slot2) textBoxCountRE2->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_Slot3) textBoxCountRE3->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_FR)    textBoxCountREx->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_RID)   textBoxCountRID->Text       = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
              if( ucLoop == cRecEleIx_Alive) textBoxCountFBD4Alive->Text = System::String::Format( "{0}", ushGetTelCountCddRdcDataPtr( ucLoop));
            }

            for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
            {
              ucWheelPos  = ucGetWPOfColWAL( ucLoop);

              if( ucWheelPos == cRadPosVL)
              {
                if( ucLoop == cRecEleIx_Slot0) radioButtonRE0->Text = System::String::Format( "RE{0} (VL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot1) radioButtonRE1->Text = System::String::Format( "RE{0} (VL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot2) radioButtonRE2->Text = System::String::Format( "RE{0} (VL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot3) radioButtonRE3->Text = System::String::Format( "RE{0} (VL)", ucLoop);
              }else if( ucWheelPos == cRadPosVR)
              {
                if( ucLoop == cRecEleIx_Slot0) radioButtonRE0->Text = System::String::Format( "RE{0} (VR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot1) radioButtonRE1->Text = System::String::Format( "RE{0} (VR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot2) radioButtonRE2->Text = System::String::Format( "RE{0} (VR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot3) radioButtonRE3->Text = System::String::Format( "RE{0} (VR)", ucLoop);
              }else if( ucWheelPos == cRadPosHL)
              {
                if( ucLoop == cRecEleIx_Slot0) radioButtonRE0->Text = System::String::Format( "RE{0} (HL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot1) radioButtonRE1->Text = System::String::Format( "RE{0} (HL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot2) radioButtonRE2->Text = System::String::Format( "RE{0} (HL)", ucLoop);
                if( ucLoop == cRecEleIx_Slot3) radioButtonRE3->Text = System::String::Format( "RE{0} (HL)", ucLoop);
              }else if( ucWheelPos == cRadPosHR)
              {
                if( ucLoop == cRecEleIx_Slot0) radioButtonRE0->Text = System::String::Format( "RE{0} (HR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot1) radioButtonRE1->Text = System::String::Format( "RE{0} (HR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot2) radioButtonRE2->Text = System::String::Format( "RE{0} (HR)", ucLoop);
                if( ucLoop == cRecEleIx_Slot3) radioButtonRE3->Text = System::String::Format( "RE{0} (HR)", ucLoop);
              }else{
                if( ucLoop == cRecEleIx_Slot0) radioButtonRE0->Text = System::String::Format( "RE{0} (no pos)", ucLoop);
                if( ucLoop == cRecEleIx_Slot1) radioButtonRE1->Text = System::String::Format( "RE{0} (no pos)", ucLoop);
                if( ucLoop == cRecEleIx_Slot2) radioButtonRE2->Text = System::String::Format( "RE{0} (no pos)", ucLoop);
                if( ucLoop == cRecEleIx_Slot3) radioButtonRE3->Text = System::String::Format( "RE{0} (no pos)", ucLoop);
              }
            }

            if( radioButtonRE0->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot0;
            }else if( radioButtonRE1->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot1;
            }else if( radioButtonRE2->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot2;
            }else if( radioButtonRE3->Checked == true)
            {
              ucTabIx = cRecEleIx_Slot3;
            }else if( radioButtonREx->Checked == true)
            {
              ucTabIx = cRecEleIx_FR;
            }else if( radioButtonRID->Checked == true)
            {
              ucTabIx = cRecEleIx_RID;
            }else{
              ucTabIx = cRecEleIx_Alive;
            }

            ptData  = ptGetRdcDataPtr( ucTabIx);

            if( ptData != NULL)
            {
              checkBoxTyrIdFromFile->Checked          = ptData->bTyrIdFromFile;
              checkBoxSuppIdFromFile->Checked         = ptData->bSuppIdFromFile;
              checkBoxPckgIdFromFile->Checked         = ptData->bPckgIdFromFile;
              checkBoxDt1PressureFromFile->Checked    = ptData->bDt1PressureFromFile;
              checkBoxDt2TemperatureFromFile->Checked = ptData->bDt2TemperatureFromFile;
              checkBoxWuDataFromFile->Checked         = ptData->bWuDataFromFile;

              if( ucTabIx == cRecEleIx_Alive)
              {

                numericUpDownTyrId->Value   = (long) ptData->tRecCddRdcData.TYR_ID;
                numericUpDownTyrId->Enabled = false;
                numericUpDownAlive1->Value   = (unsigned char) ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_1;

                numericUpDownAlive1->Enabled = true;

                numericUpDownSuppId->Value   = (uint8) ptData->tRecCddRdcData.SUPP_ID;
                numericUpDownSuppId->Enabled = false;
                listBoxSuppId->SetSelected( 0, TRUE);
                listBoxSuppId->Enabled = false;
                numericUpDownAlive2->Value   = (unsigned char) ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_2;

                numericUpDownAlive2->Enabled = true;

                checkBoxAliveError->Enabled = true;

                numericUpDownPckgId->Value   = (uint8) ptData->tRecCddRdcData.PCKG_ID;
                numericUpDownPckgId->Enabled = false;
                listBoxPckgId->Enabled = false;

                radioButtonDt1PressureSensorOk->Checked = true;
                panelDt1PressureSensorState->Enabled    = false;
                numericUpDownDt1Pressure->Value   = (uint16) ptData->tRecCddRdcData.RDC_DT_1;
                numericUpDownDt1Pressure->Enabled = false;
                trackBarDt1Pressure->Enabled = false;

                radioButtonDt2TemperatureSensorOk->Checked = true;
                panelDt2TemperatureSensorState->Enabled    = false;
                numericUpDownDt2Temperature->Value   = (uint8) ptData->tRecCddRdcData.RDC_DT_2;
                numericUpDownDt2Temperature->Enabled = false;
                trackBarDt2Temperature->Enabled = false;

                checkBoxInputIsochor->Enabled = false;
                checkBoxInputIsochor->Checked = false;

                numericUpDownRdcMesTstmp->Value   = ptData->tRecCddRdcData.RDC_MES_TSTMP;
                numericUpDownRdcMesTstmp->Enabled = false;

                numericUpDownDt3PalLbt->Value   = ptData->tRecCddRdcData.RDC_DT_3;
                numericUpDownDt3PalLbt->Enabled = false;

                numericUpDownDt4PalStatusHi->Value   = ptData->tRecCddRdcData.RDC_DT_4;
                numericUpDownDt4PalStatusHi->Enabled = false;

                numericUpDownDt5PalStatusLo->Value   = ptData->tRecCddRdcData.RDC_DT_5;
                numericUpDownDt5PalStatusLo->Enabled = false;

                numericUpDownDt6->Value   = ptData->tRecCddRdcData.RDC_DT_6;

                numericUpDownDt7Rssi->Value   = ptData->tRecCddRdcData.RDC_DT_7;
                numericUpDownDt7Rssi->Enabled = false;

                numericUpDownDt8Crc->Value   = ptData->tRecCddRdcData.RDC_DT_8;
                numericUpDownDt8Crc->Enabled = false;

                checkBoxSetBatteryEmpty->Enabled = false;
              }else if( ucTabIx == cRecEleIx_RID)
              {
                listBoxPckgId->Enabled = true;

                checkBoxInputIsochor->Enabled = false;
                checkBoxInputIsochor->Checked = false;

              }else{

                if( checkBoxTyrIdFromFile->Checked == true)
                {
                  numericUpDownTyrId->Enabled = false;
                  numericUpDownAlive1->Enabled = false;
                }else{
                  numericUpDownTyrId->Enabled = true;
                  numericUpDownAlive1->Enabled = true;
                }

                numericUpDownTyrId->Value  = (long) ptData->tRecCddRdcData.TYR_ID;
                numericUpDownAlive1->Value = (unsigned char) ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_1;

                if( checkBoxSuppIdFromFile->Checked == true)
                {
                  listBoxSuppId->Enabled = false;
                  numericUpDownSuppId->Enabled = false;
                  numericUpDownAlive2->Enabled = false;
                  checkBoxAliveError->Enabled = false;
                  checkBoxAliveError->Checked = false;
                }else{
                  listBoxSuppId->Enabled = true;
                  numericUpDownSuppId->Enabled = false;
                  numericUpDownAlive2->Enabled = true;
                  checkBoxAliveError->Enabled = true;
                  checkBoxAliveError->Checked = ptData->bAliveError;
                }

                numericUpDownSuppId->Value = (uint8) ptData->tRecCddRdcData.SUPP_ID;

                switch( (uint8) ptData->tRecCddRdcData.SUPP_ID)
                {
                  case cSupplCodeUnused:
                    listBoxSuppId->SetSelected( 0, TRUE);
                  break;

                  case cSupplCodeAutonet:
                    listBoxSuppId->SetSelected( 1, TRUE);
                  break;

                  case cSupplCodeHuf:
                    listBoxSuppId->SetSelected( 2, TRUE);
                  break;

                  case cSupplCodeConti:
                    listBoxSuppId->SetSelected( 3, TRUE);
                  break;

                  case cSupplCodeSchrader:
                    listBoxSuppId->SetSelected( 4, TRUE);
                  break;

                  case cSupplCodeUnknown:
                    listBoxSuppId->SetSelected( 5, TRUE);
                  break;

                  default:
                    listBoxSuppId->SetSelected( 6, TRUE);

                    if( checkBoxSuppIdFromFile->Checked == false)
                    {
                      numericUpDownSuppId->Enabled = true;
                    }
                  break;
                }
                numericUpDownAlive2->Value   = (unsigned char) ptData->tRecCddRdcData.ALIV_RDC_DT_PCK_2;

                if( checkBoxPckgIdFromFile->Checked == true)
                {
                  listBoxPckgId->Enabled = false;
                  numericUpDownPckgId->Enabled = false;
                  numericUpDownPckgId->Enabled = false;
                }else{
                  listBoxPckgId->Enabled = true;
                  numericUpDownPckgId->Enabled = false;
                  numericUpDownPckgId->Enabled = true;
                }

                numericUpDownPckgId->Value = (uint8) ptData->tRecCddRdcData.PCKG_ID;

                switch( (uint8) ptData->tRecCddRdcData.PCKG_ID)
                {
                  case cTelTypeAK35def:
                    listBoxPckgId->SetSelected( 0, TRUE);
                  break;

                  case cTelTypeSELPAL:
                    listBoxPckgId->SetSelected( 1, TRUE);
                  break;

                  case cTelTypeSELPAL1:
                    listBoxPckgId->SetSelected( 2, TRUE);
                  break;

                  case cTelTypeContiFP:
                    listBoxPckgId->SetSelected( 3, TRUE);
                  break;

                  case cTelTypeBeruLong:
                    listBoxPckgId->SetSelected( 4, TRUE);
                  break;

                  case cTelTypeBeruMed:
                    listBoxPckgId->SetSelected( 5, TRUE);
                  break;

                  default:
                    listBoxPckgId->SetSelected( 6, TRUE);

                    if( checkBoxPckgIdFromFile->Checked == false)
                    {
                      numericUpDownPckgId->Enabled = true;
                    }
                  break;
                }

                if( (checkBoxDt1PressureFromFile->Checked == false) && (checkBoxDt2TemperatureFromFile->Checked == false))
                {
                  checkBoxInputIsochor->Enabled = true;
                  checkBoxInputIsochor->Checked = ptData->bInputIsochor;
                }else{
                  checkBoxInputIsochor->Enabled = false;
                  checkBoxInputIsochor->Checked = false;
                }

                if( checkBoxWuDataFromFile->Checked == true)
                {
                  numericUpDownRdcMesTstmp->Enabled  = false;
                  numericUpDownDt3PalLbt->Enabled = false;
                  numericUpDownDt4PalStatusHi->Enabled = false;
                  numericUpDownDt5PalStatusLo->Enabled = false;
                  numericUpDownDt6->Enabled = false;
                  numericUpDownDt7Rssi->Enabled = false;
                  numericUpDownDt8Crc->Enabled = false;
                  checkBoxSetBatteryEmpty->Enabled = false;
                }else{
                  numericUpDownRdcMesTstmp->Enabled  = true;
                  numericUpDownDt3PalLbt->Enabled = true;
                  numericUpDownDt4PalStatusHi->Enabled = true;
                  numericUpDownDt5PalStatusLo->Enabled = true;
                  numericUpDownDt6->Enabled = true;
                  numericUpDownDt7Rssi->Enabled = true;
                  numericUpDownDt8Crc->Enabled = true;
                  checkBoxSetBatteryEmpty->Enabled = true;
                }

                if( checkBoxDt1PressureFromFile->Checked == true)
                {
                  numericUpDownDt1Pressure->Enabled = false;
                  trackBarDt1Pressure->Enabled = false;
                  panelDt1PressureSensorState->Enabled = false;
                }else{
                  numericUpDownDt1Pressure->Enabled = true;
                  trackBarDt1Pressure->Enabled = true;
                  panelDt1PressureSensorState->Enabled = true;
                }

                if( ptData->tRecCddRdcData.RDC_DT_1 == cReAkPresError)
                {
                  radioButtonDt1PressureSensorDefect->Checked = true;
                }else if( ptData->tRecCddRdcData.RDC_DT_1 == cReAkPresUnderflow)
                {
                  radioButtonDt1PressureSensorUnderflow->Checked = true;
                }else if( ptData->tRecCddRdcData.RDC_DT_1 == cReAkPresOverflow)
                {
                  radioButtonDt1PressureSensorOverflow->Checked = true;
                }else{
                  ushPamb_hPa      = (uint16) System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value);
                  ushPress_abs_hPa = ((((uint16) ptData->tRecCddRdcData.RDC_DT_1 + 40) - 2) * 25);

                  if( ushPress_abs_hPa < 1000)
                  {

                    numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Minimum;
                    radioButtonDt1PressureSensorUnderflow->Checked = true;
                  }else if( ushPress_abs_hPa > 7300)
                  {

                    numericUpDownDt1Pressure->Value = numericUpDownDt1Pressure->Maximum;
                    radioButtonDt1PressureSensorOverflow->Checked = true;
                  }else if( ushPress_abs_hPa < ushPamb_hPa)
                  {
                    ptData->tRecCddRdcData.RDC_DT_1 = 0;
                    numericUpDownDt1Pressure->Value = 0;
                    radioButtonDt1PressureSensorOk->Checked = true;
                  }else{

                    ptData->tRecCddRdcData.RDC_DT_1 = (uint8) (((ushPress_abs_hPa - 1000) / 25) + 2);
                    numericUpDownDt1Pressure->Value = ((((ushPress_abs_hPa - ushPamb_hPa) * 10 + 125) / 250) * 25);
                    radioButtonDt1PressureSensorOk->Checked = true;
                  }
                }

                if( checkBoxDt1PressureFromFile->Checked == true)
                {
                  numericUpDownDt2Temperature->Enabled = false;
                  trackBarDt2Temperature->Enabled = false;
                  panelDt2TemperatureSensorState->Enabled = false;
                }else{
                  numericUpDownDt2Temperature->Enabled = true;
                  trackBarDt2Temperature->Enabled = true;
                  panelDt2TemperatureSensorState->Enabled = true;
                }

                if( ptData->tRecCddRdcData.RDC_DT_2 == cReAkTempError)
                {
                  radioButtonDt2TemperatureSensorDefect->Checked = true;
                }else if( ptData->tRecCddRdcData.RDC_DT_2 == cReAkTempUnderflow)
                {
                  radioButtonDt2TemperatureSensorUnderflow->Checked = true;
                }else if( ptData->tRecCddRdcData.RDC_DT_2 >= cReAkTempOverflow)
                {
                  radioButtonDt2TemperatureSensorOverflow->Checked = true;
                }else{
                  radioButtonDt2TemperatureSensorOk->Checked = true;
                  numericUpDownDt2Temperature->Value = (signed int) (ptData->tRecCddRdcData.RDC_DT_2 - 52);
                }

                if( checkBoxInputIsochor->Checked == false)
                {
                  if( (ptData->tRecCddRdcData.RDC_DT_1 > cReAkPresUnderflow) && (ptData->tRecCddRdcData.RDC_DT_1 < cReAkPresOverflow))
                  {
                    ptData->ushPabs_iso_hPa = (uint16) ((((System::Decimal::ToUInt16(numericUpDownDt1Pressure->Value) + System::Decimal::ToUInt16(numericUpDownAIP_ENG_DRV->Value)) * 10 + 125) / 250) * 25);
                  }

                  if( (ptData->tRecCddRdcData.RDC_DT_2 > cReAkTempUnderflow) && (ptData->tRecCddRdcData.RDC_DT_1 < cReAkTempOverflow))
                  {
                    ptData->sshTabs_iso_K   = (sint16) (System::Decimal::ToInt16(numericUpDownDt2Temperature->Value) + 273);
                  }
                }

                numericUpDownPabsWert->Hexadecimal = false;
                numericUpDownPabsWert->Value = (Decimal)ptData->ushPabs_iso_hPa;

                numericUpDownTabsWert->Hexadecimal = false;
                numericUpDownTabsWert->Value = (Decimal)ptData->sshTabs_iso_K;

                numericUpDownRdcMesTstmp->Value    = ptData->tRecCddRdcData.RDC_MES_TSTMP;
                numericUpDownDt3PalLbt->Value      = ptData->tRecCddRdcData.RDC_DT_3;
                numericUpDownDt4PalStatusHi->Value = ptData->tRecCddRdcData.RDC_DT_4;
                numericUpDownDt5PalStatusLo->Value = ptData->tRecCddRdcData.RDC_DT_5;
                numericUpDownDt6->Value            = ptData->tRecCddRdcData.RDC_DT_6;
                numericUpDownDt7Rssi->Value        = ptData->tRecCddRdcData.RDC_DT_7;
                numericUpDownDt8Crc->Value         = ptData->tRecCddRdcData.RDC_DT_8;
              }
            }
         }
#endif
