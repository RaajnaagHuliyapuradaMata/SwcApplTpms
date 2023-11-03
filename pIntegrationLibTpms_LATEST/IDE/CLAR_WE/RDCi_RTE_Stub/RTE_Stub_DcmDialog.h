#ifndef __RTE_STUB_DCM_DIALOG_H
#define __RTE_STUB_DCM_DIALOG_H

private: System::Void buttonStatusRdcLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {

           ImpTypeArrayDcm_StatusRdcLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcLesen () - NRC = 0x{0:X2}\n", Error));

           if( Data[cucIxStatEigenraederBekannt]             == TRUE) { labelStatEigenraederBekanntValue->Text = "1";             }else{ labelStatEigenraederBekanntValue->Text = "0"; }
           if( Data[cucIxStatRadposErBekannt]                == TRUE) { labelStatRadposErBekanntValue->Text = "1";                }else{ labelStatRadposErBekanntValue->Text = "0"; }
           if( Data[cucIxStatKalAnforderungAktiv]            == TRUE) { labelStatKalAnforderungAktivValue->Text = "1";            }else{ labelStatKalAnforderungAktivValue->Text = "0"; }
           if( Data[cucIxStatRadZuordnungTimeout]            == TRUE) { labelStatRadZuordnungTimeoutValue->Text = "1";            }else{ labelStatRadZuordnungTimeoutValue->Text = "0"; }
           if( Data[cucIxStatBandmodeAktiv]                  == TRUE) { labelStatBandmodeAktivValue->Text = "1";                  }else{ labelStatBandmodeAktivValue->Text = "0"; }
           if( Data[cucIxStatTestEigenradFahrt]              == TRUE) { labelStatTestEigenradFahrtValue->Text = "1";              }else{ labelStatTestEigenradFahrtValue->Text = "0"; }
           if( Data[cucIxStatErFahrtVthresAkiv]              == TRUE) { labelStatErFahrtVthresAkivValue->Text = "1";              }else{ labelStatErFahrtVthresAkivValue->Text = "0"; }
           if( Data[cucIxStatBmTimeoutActive]                == TRUE) { labelStatBmTimeoutActiveValue->Text = "1";                }else{ labelStatBmTimeoutActiveValue->Text = "0"; }
           if( Data[cucIxStatHarteWarnungUnspezifischAktiv]  == TRUE) { labelStatHarteWarnungUnspezifischAktivValue->Text = "1";  }else{ labelStatHarteWarnungUnspezifischAktivValue->Text = "0"; }
           if( Data[cucIxStatHarteWarnungVlAktiv]            == TRUE) { labelStatHarteWarnungVlAktivValue->Text = "1";            }else{ labelStatHarteWarnungVlAktivValue->Text = "0"; }
           if( Data[cucIxStatHarteWarnungVrAktiv]            == TRUE) { labelStatHarteWarnungVrAktivValue->Text = "1";            }else{ labelStatHarteWarnungVrAktivValue->Text = "0"; }
           if( Data[cucIxStatHarteWarnungHlAktiv]            == TRUE) { labelStatHarteWarnungHlAktivValue->Text = "1";            }else{ labelStatHarteWarnungHlAktivValue->Text = "0"; }
           if( Data[cucIxStatHarteWarnungHrAktiv]            == TRUE) { labelStatHarteWarnungHrAktivValue->Text = "1";            }else{ labelStatHarteWarnungHrAktivValue->Text = "0"; }
           if( Data[cucIxStatKl15Ein]                        == TRUE) { labelStatKl15EinValue->Text = "1";                        }else{ labelStatKl15EinValue->Text = "0"; }
           if( Data[cucIxStatFzgFaehrt]                      == TRUE) { labelStatFzgFaehrtValue->Text = "1";                      }else{ labelStatFzgFaehrtValue->Text = "0"; }
           if( Data[cucIxStatErkennungAlleRe]                == TRUE) { labelStatErkennungAlleReValue->Text = "1";                }else{ labelStatErkennungAlleReValue->Text = "0"; }

           labelStatDtcInactiveValue->Text = System::String::Format("0x{0:X2}", Data[cucIxStatDtcInactive]);
         }

private: System::Void buttonStatusRdcMessdatenblock1_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8  ucDataBYTE;
           uint16 ushDataWORD;
           uint32 ulDataDWORD;

           ImpTypeArrayDcm_RdcMessdatenblock1ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcMessdatenblock1( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcMessdatenblock1 () - NRC = 0x{0:X2}\n", Error));

           labelMessdatenblockValue->Text = "1";

           if(Error == RTE_E_OK)
           {
             labelConditionDiagJob->Text = "RTE_E_OK";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(0,255,0);

             ulDataDWORD = ((uint32) (Data[cucIxStatReIdentifierWert + 0] << 24) + (uint32) (Data[cucIxStatReIdentifierWert + 1] << 16) + (uint32) (Data[cucIxStatReIdentifierWert + 2] << 8) + (uint32) Data[cucIxStatReIdentifierWert + 3]);
             if( (ulDataDWORD == 0x00000000u) || (ulDataDWORD == 0xFFFFFFFFu)) { labelStatReIdentifierValue->Text = "unknown"; }else{ labelStatReIdentifierValue->Text = System::String::Format( "{0}", ulDataDWORD); }

             ucDataBYTE = Data[cucIxStatRadPositionNr] & 0x0fu;
             if( ucDataBYTE > cRadPosHR) { labelStatRadPositionValue->Text = "unknown"; }else{ labelStatRadPositionValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = (Data[cucIxStatRadPositionNr] & 0xf0u) >> 4;
             if( ucDataBYTE >= cMaxQRCodeSets) { labelStatQrTabIndexValue->Text = "unknown"; }else{ labelStatQrTabIndexValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatLetzterReifendruckwertWert + 0] << 8) + (uint16) Data[cucIxStatLetzterReifendruckwertWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatReReifendruckValue->Text = "unknown"; }else{ labelStatReReifendruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatLetzterReifentemperaturwertWert];
             if( ucDataBYTE == 0xff) { labelStatReReifentemperaturValue->Text = "unknown"; }else{ labelStatReReifentemperaturValue->Text = System::String::Format( "{0}", (sint8) ucDataBYTE - 50); }

             ushDataWORD = ((uint16) (Data[cucIxStatSolldruckWert + 0] << 8) + (uint16) Data[cucIxStatSolldruckWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatSolldruckValue->Text = "unknown"; }else{ labelStatSolldruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatGutempfaengeWert + 0] << 8) + (uint16) Data[cucIxStatGutempfaengeWert + 1]);
             if( ushDataWORD == 0x0000u) { labelStatGutempfaengeValue->Text = "unknown"; }else{ labelStatGutempfaengeValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatAusbeuteWert];
             if( ucDataBYTE == 0x00u) { labelStatAusbeuteValue->Text = "unknown"; }else{ labelStatAusbeuteValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatRssiPegelWert + 0] << 8) + (uint16) Data[cucIxStatRssiPegelWert + 1]);
             if( ushDataWORD == 0x00u) { labelStatRssiPegelValue->Text = "unknown"; }else{ labelStatRssiPegelValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatRestlebensdauerWert + 0] << 8) + (uint16) Data[cucIxStatRestlebensdauerWert + 1]);
             if( ushDataWORD == (uint16) -999) { labelStatReRestlebensdauerValue->Text = "unknown"; }else{ labelStatReRestlebensdauerValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatRadelektronikStatus];
             if( ucDataBYTE == 0xFFu)   { labelStatReStatusValue->Text = "unknown"; }
             else if(ucDataBYTE == 0x00) { labelStatReStatusValue->Text = "OK";    }
             else if(ucDataBYTE == 0x01) { labelStatReStatusValue->Text = "Mute";    }
             else if(ucDataBYTE == 0x02) { labelStatReStatusValue->Text = "Defect";  }
             else if(ucDataBYTE == 0x03) { labelStatReStatusValue->Text = "Not rec"; }

             ucDataBYTE = Data[cucIxStatHarteWarnungAktiv];
             if( ucDataBYTE == 0xFFu) { labelStatHarteWarnungAktivValue->Text = "unknown"; }else{ labelStatHarteWarnungAktivValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatPosChanged];
             if( ucDataBYTE == 0xFFu) { labelStatPosChangedValue->Text = "unknown"; }else{ labelStatPosChangedValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatFolgeausfallWert];
             if( ucDataBYTE == 0x00u) { labelStatFolgeausfallValue->Text = "unknown"; }else{ labelStatFolgeausfallValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatReHersteller];
             if( ucDataBYTE == 0xFFu) { labelStatReHerstellerValue->Text = "unknown"; }else{ labelStatReHerstellerValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatRadelektronikSendemode];
             if( ucDataBYTE == 0xFFu) { labelStatReSendemodeValue->Text = "unknown"; }else{ labelStatReSendemodeValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatTelegrammtyp];
             if( ucDataBYTE == 0xFFu) { labelStatReTelegrammtypValue->Text = "unknown"; }else{ labelStatReTelegrammtypValue->Text = System::String::Format( "{0}", ucDataBYTE); }
           }
           else
           {
             labelConditionDiagJob->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }

         }

private: System::Void buttonStatusRdcMessdatenblock2_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8  ucDataBYTE;
           uint16 ushDataWORD;
           uint32 ulDataDWORD;

           ImpTypeArrayDcm_RdcMessdatenblock2ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcMessdatenblock2( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcMessdatenblock2 () - NRC = 0x{0:X2}\n", Error));

           labelMessdatenblockValue->Text = "2";

           if(Error == RTE_E_OK)
           {
             labelConditionDiagJob->Text = "RTE_E_OK";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(0,255,0);

             ulDataDWORD = ((uint32) (Data[cucIxStatReIdentifierWert + 0] << 24) + (uint32) (Data[cucIxStatReIdentifierWert + 1] << 16) + (uint32) (Data[cucIxStatReIdentifierWert + 2] << 8) + (uint32) Data[cucIxStatReIdentifierWert + 3]);
             if( (ulDataDWORD == 0x00000000u) || (ulDataDWORD == 0xFFFFFFFFu)) { labelStatReIdentifierValue->Text = "unknown"; }else{ labelStatReIdentifierValue->Text = System::String::Format( "{0}", ulDataDWORD); }

             ucDataBYTE = Data[cucIxStatRadPositionNr] & 0x0fu;
             if( ucDataBYTE > cRadPosHR) { labelStatRadPositionValue->Text = "unknown"; }else{ labelStatRadPositionValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = (Data[cucIxStatRadPositionNr] & 0xf0u) >> 4;
             if( ucDataBYTE >= cMaxQRCodeSets) { labelStatQrTabIndexValue->Text = "unknown"; }else{ labelStatQrTabIndexValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatLetzterReifendruckwertWert + 0] << 8) + (uint16) Data[cucIxStatLetzterReifendruckwertWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatReReifendruckValue->Text = "unknown"; }else{ labelStatReReifendruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatLetzterReifentemperaturwertWert];
             if( ucDataBYTE == 0xff) { labelStatReReifentemperaturValue->Text = "unknown"; }else{ labelStatReReifentemperaturValue->Text = System::String::Format( "{0}", (sint8) ucDataBYTE - 50); }

             ushDataWORD = ((uint16) (Data[cucIxStatSolldruckWert + 0] << 8) + (uint16) Data[cucIxStatSolldruckWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatSolldruckValue->Text = "unknown"; }else{ labelStatSolldruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatGutempfaengeWert + 0] << 8) + (uint16) Data[cucIxStatGutempfaengeWert + 1]);
             if( ushDataWORD == 0x0000u) { labelStatGutempfaengeValue->Text = "unknown"; }else{ labelStatGutempfaengeValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatAusbeuteWert];
             if( ucDataBYTE == 0x00u) { labelStatAusbeuteValue->Text = "unknown"; }else{ labelStatAusbeuteValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatRssiPegelWert + 0] << 8) + (uint16) Data[cucIxStatRssiPegelWert + 1]);
             if( ushDataWORD == 0x00u) { labelStatRssiPegelValue->Text = "unknown"; }else{ labelStatRssiPegelValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatRestlebensdauerWert + 0] << 8) + (uint16) Data[cucIxStatRestlebensdauerWert + 1]);
             if( ushDataWORD == (uint16) -999) { labelStatReRestlebensdauerValue->Text = "unknown"; }else{ labelStatReRestlebensdauerValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatRadelektronikStatus];
             if( ucDataBYTE == 0xFFu)   { labelStatReStatusValue->Text = "unknown"; }
             else if(ucDataBYTE == 0x00) { labelStatReStatusValue->Text = "OK";    }
             else if(ucDataBYTE == 0x01) { labelStatReStatusValue->Text = "Mute";    }
             else if(ucDataBYTE == 0x02) { labelStatReStatusValue->Text = "Defect";  }
             else if(ucDataBYTE == 0x03) { labelStatReStatusValue->Text = "Not rec"; }

             ucDataBYTE = Data[cucIxStatHarteWarnungAktiv];
             if( ucDataBYTE == 0xFFu) { labelStatHarteWarnungAktivValue->Text = "unknown"; }else{ labelStatHarteWarnungAktivValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatPosChanged];
             if( ucDataBYTE == 0xFFu) { labelStatPosChangedValue->Text = "unknown"; }else{ labelStatPosChangedValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatFolgeausfallWert];
             if( ucDataBYTE == 0x00u) { labelStatFolgeausfallValue->Text = "unknown"; }else{ labelStatFolgeausfallValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatReHersteller];
             if( ucDataBYTE == 0xFFu) { labelStatReHerstellerValue->Text = "unknown"; }else{ labelStatReHerstellerValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatRadelektronikSendemode];
             if( ucDataBYTE == 0xFFu) { labelStatReSendemodeValue->Text = "unknown"; }else{ labelStatReSendemodeValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatTelegrammtyp];
             if( ucDataBYTE == 0xFFu) { labelStatReTelegrammtypValue->Text = "unknown"; }else{ labelStatReTelegrammtypValue->Text = System::String::Format( "{0}", ucDataBYTE); }
           }
           else
           {
             labelConditionDiagJob->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }
         }

private: System::Void buttonStatusRdcMessdatenblock3_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8  ucDataBYTE;
           uint16 ushDataWORD;
           uint32 ulDataDWORD;

           ImpTypeArrayDcm_RdcMessdatenblock3ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcMessdatenblock3( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcMessdatenblock3 () - NRC = 0x{0:X2}\n", Error));

           labelMessdatenblockValue->Text = "3";

           if(Error == RTE_E_OK)
           {
             labelConditionDiagJob->Text = "RTE_E_OK";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(0,255,0);

             ulDataDWORD = ((uint32) (Data[cucIxStatReIdentifierWert + 0] << 24) + (uint32) (Data[cucIxStatReIdentifierWert + 1] << 16) + (uint32) (Data[cucIxStatReIdentifierWert + 2] << 8) + (uint32) Data[cucIxStatReIdentifierWert + 3]);
             if( (ulDataDWORD == 0x00000000u) || (ulDataDWORD == 0xFFFFFFFFu)) { labelStatReIdentifierValue->Text = "unknown"; }else{ labelStatReIdentifierValue->Text = System::String::Format( "{0}", ulDataDWORD); }

             ucDataBYTE = Data[cucIxStatRadPositionNr] & 0x0fu;
             if( ucDataBYTE > cRadPosHR) { labelStatRadPositionValue->Text = "unknown"; }else{ labelStatRadPositionValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = (Data[cucIxStatRadPositionNr] & 0xf0u) >> 4;
             if( ucDataBYTE >= cMaxQRCodeSets) { labelStatQrTabIndexValue->Text = "unknown"; }else{ labelStatQrTabIndexValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatLetzterReifendruckwertWert + 0] << 8) + (uint16) Data[cucIxStatLetzterReifendruckwertWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatReReifendruckValue->Text = "unknown"; }else{ labelStatReReifendruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatLetzterReifentemperaturwertWert];
             if( ucDataBYTE == 0xff) { labelStatReReifentemperaturValue->Text = "unknown"; }else{ labelStatReReifentemperaturValue->Text = System::String::Format( "{0}", (sint8) ucDataBYTE - 50); }

             ushDataWORD = ((uint16) (Data[cucIxStatSolldruckWert + 0] << 8) + (uint16) Data[cucIxStatSolldruckWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatSolldruckValue->Text = "unknown"; }else{ labelStatSolldruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatGutempfaengeWert + 0] << 8) + (uint16) Data[cucIxStatGutempfaengeWert + 1]);
             if( ushDataWORD == 0x0000u) { labelStatGutempfaengeValue->Text = "unknown"; }else{ labelStatGutempfaengeValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatAusbeuteWert];
             if( ucDataBYTE == 0x00u) { labelStatAusbeuteValue->Text = "unknown"; }else{ labelStatAusbeuteValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatRssiPegelWert + 0] << 8) + (uint16) Data[cucIxStatRssiPegelWert + 1]);
             if( ushDataWORD == 0x00u) { labelStatRssiPegelValue->Text = "unknown"; }else{ labelStatRssiPegelValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatRestlebensdauerWert + 0] << 8) + (uint16) Data[cucIxStatRestlebensdauerWert + 1]);
             if( ushDataWORD == (uint16) -999) { labelStatReRestlebensdauerValue->Text = "unknown"; }else{ labelStatReRestlebensdauerValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatRadelektronikStatus];
             if( ucDataBYTE == 0xFFu)   { labelStatReStatusValue->Text = "unknown"; }
             else if(ucDataBYTE == 0x00) { labelStatReStatusValue->Text = "OK";    }
             else if(ucDataBYTE == 0x01) { labelStatReStatusValue->Text = "Mute";    }
             else if(ucDataBYTE == 0x02) { labelStatReStatusValue->Text = "Defect";  }
             else if(ucDataBYTE == 0x03) { labelStatReStatusValue->Text = "Not rec"; }

             ucDataBYTE = Data[cucIxStatHarteWarnungAktiv];
             if( ucDataBYTE == 0xFFu) { labelStatHarteWarnungAktivValue->Text = "unknown"; }else{ labelStatHarteWarnungAktivValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatPosChanged];
             if( ucDataBYTE == 0xFFu) { labelStatPosChangedValue->Text = "unknown"; }else{ labelStatPosChangedValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatFolgeausfallWert];
             if( ucDataBYTE == 0x00u) { labelStatFolgeausfallValue->Text = "unknown"; }else{ labelStatFolgeausfallValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatReHersteller];
             if( ucDataBYTE == 0xFFu) { labelStatReHerstellerValue->Text = "unknown"; }else{ labelStatReHerstellerValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatRadelektronikSendemode];
             if( ucDataBYTE == 0xFFu) { labelStatReSendemodeValue->Text = "unknown"; }else{ labelStatReSendemodeValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatTelegrammtyp];
             if( ucDataBYTE == 0xFFu) { labelStatReTelegrammtypValue->Text = "unknown"; }else{ labelStatReTelegrammtypValue->Text = System::String::Format( "{0}", ucDataBYTE); }
           }
           else
           {
             labelConditionDiagJob->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }
         }

private: System::Void buttonStatusRdcMessdatenblock4_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8  ucDataBYTE;
           uint16 ushDataWORD;
           uint32 ulDataDWORD;

           ImpTypeArrayDcm_RdcMessdatenblock4ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcMessdatenblock4( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcMessdatenblock4 () - NRC = 0x{0:X2}\n", Error));

           labelMessdatenblockValue->Text = "4";

           if(Error == RTE_E_OK)
           {
             labelConditionDiagJob->Text = "RTE_E_OK";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(0,255,0);

             ulDataDWORD = ((uint32) (Data[cucIxStatReIdentifierWert + 0] << 24) + (uint32) (Data[cucIxStatReIdentifierWert + 1] << 16) + (uint32) (Data[cucIxStatReIdentifierWert + 2] << 8) + (uint32) Data[cucIxStatReIdentifierWert + 3]);
             if( (ulDataDWORD == 0x00000000u) || (ulDataDWORD == 0xFFFFFFFFu)) { labelStatReIdentifierValue->Text = "unknown"; }else{ labelStatReIdentifierValue->Text = System::String::Format( "{0}", ulDataDWORD); }

             ucDataBYTE = Data[cucIxStatRadPositionNr] & 0x0fu;
             if( ucDataBYTE > cRadPosHR) { labelStatRadPositionValue->Text = "unknown"; }else{ labelStatRadPositionValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = (Data[cucIxStatRadPositionNr] & 0xf0u) >> 4;
             if( ucDataBYTE >= cMaxQRCodeSets) { labelStatQrTabIndexValue->Text = "unknown"; }else{ labelStatQrTabIndexValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatLetzterReifendruckwertWert + 0] << 8) + (uint16) Data[cucIxStatLetzterReifendruckwertWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatReReifendruckValue->Text = "unknown"; }else{ labelStatReReifendruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatLetzterReifentemperaturwertWert];
             if( ucDataBYTE == 0xffu) { labelStatReReifentemperaturValue->Text = "unknown"; }else{ labelStatReReifentemperaturValue->Text = System::String::Format( "{0}", ucDataBYTE - 50); }

             ushDataWORD = ((uint16) (Data[cucIxStatSolldruckWert + 0] << 8) + (uint16) Data[cucIxStatSolldruckWert + 1]);
             if( ushDataWORD == (uint16) -9999) { labelStatSolldruckValue->Text = "unknown"; }else{ labelStatSolldruckValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatGutempfaengeWert + 0] << 8) + (uint16) Data[cucIxStatGutempfaengeWert + 1]);
             if( ushDataWORD == 0x0000u) { labelStatGutempfaengeValue->Text = "unknown"; }else{ labelStatGutempfaengeValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatAusbeuteWert];
             if( ucDataBYTE == 0x00u) { labelStatAusbeuteValue->Text = "unknown"; }else{ labelStatAusbeuteValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ushDataWORD = ((uint16) (Data[cucIxStatRssiPegelWert + 0] << 8) + (uint16) Data[cucIxStatRssiPegelWert + 1]);
             if( ushDataWORD == 0x00u) { labelStatRssiPegelValue->Text = "unknown"; }else{ labelStatRssiPegelValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ushDataWORD = ((uint16) (Data[cucIxStatRestlebensdauerWert + 0] << 8) + (uint16) Data[cucIxStatRestlebensdauerWert + 1]);
             if( ushDataWORD == (uint16) -999) { labelStatReRestlebensdauerValue->Text = "unknown"; }else{ labelStatReRestlebensdauerValue->Text = System::String::Format( "{0}", ushDataWORD); }

             ucDataBYTE = Data[cucIxStatRadelektronikStatus];
             if( ucDataBYTE == 0xFFu)   { labelStatReStatusValue->Text = "unknown"; }
             else if(ucDataBYTE == 0x00) { labelStatReStatusValue->Text = "OK";    }
             else if(ucDataBYTE == 0x01) { labelStatReStatusValue->Text = "Mute";    }
             else if(ucDataBYTE == 0x02) { labelStatReStatusValue->Text = "Defect";  }
             else if(ucDataBYTE == 0x03) { labelStatReStatusValue->Text = "Not rec"; }

             ucDataBYTE = Data[cucIxStatHarteWarnungAktiv];
             if( ucDataBYTE == 0xFFu) { labelStatHarteWarnungAktivValue->Text = "unknown"; }else{ labelStatHarteWarnungAktivValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatPosChanged];
             if( ucDataBYTE == 0xFFu) { labelStatPosChangedValue->Text = "unknown"; }else{ labelStatPosChangedValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatFolgeausfallWert];
             if( ucDataBYTE == 0x00u) { labelStatFolgeausfallValue->Text = "unknown"; }else{ labelStatFolgeausfallValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatReHersteller];
             if( ucDataBYTE == 0xFFu) { labelStatReHerstellerValue->Text = "unknown"; }else{ labelStatReHerstellerValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatRadelektronikSendemode];
             if( ucDataBYTE == 0xFFu) { labelStatReSendemodeValue->Text = "unknown"; }else{ labelStatReSendemodeValue->Text = System::String::Format( "{0}", ucDataBYTE); }

             ucDataBYTE = Data[cucIxStatTelegrammtyp];
             if( ucDataBYTE == 0xFFu) { labelStatReTelegrammtypValue->Text = "unknown"; }else{ labelStatReTelegrammtypValue->Text = System::String::Format( "{0}", ucDataBYTE); }
           }
           else
           {
             labelConditionDiagJob->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelConditionDiagJob->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }
         }

private: System::Void buttonStatusRdcVersion_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_StatusRdcVersionReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcVersion( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcVersion () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcAnlernenLokalisierungLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           static ImpTypeArrayDcm_RdcAnlernenLokalisierungLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcAnlernenLokalisierungLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcAnlernenLokalisierungLesen () - NRC = 0x{0:X2}\n", Error));

           if(Error == RTE_E_OK)
           {
             labelPalStatusNRC->Text = "RTE_E_OK";
             labelPalStatusNRC->BackColor = System::Drawing::Color::FromArgb(0,255,0);
           }else{
             labelPalStatusNRC->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelPalStatusNRC->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }

           numericUpDownPalStatusZOMSlot->Value = 1;
           numericUpDownPalStatusZOMSlot->Value = 0;
         }

private: System::Void numericUpDownPalStatusZOMSlot_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 *pucPalData;

            pucPalData = Stub_RdcAnlernenLokalisierungLesen_Output( (uint8) System::Decimal::ToByte( numericUpDownPalStatusZOMSlot->Value));

            if( pucPalData != NULL_PTR)
            {
              textBoxPalStatusByte0->Text  = System::String::Format( "{0}", pucPalData[0]);
              textBoxPalStatusByte1->Text  = System::String::Format( "{0}", pucPalData[1]);
              textBoxPalStatusByte2->Text  = System::String::Format( "{0}", pucPalData[2]);
              textBoxPalStatusByte3->Text  = System::String::Format( "{0}", pucPalData[3]);
              textBoxPalStatusByte4->Text  = System::String::Format( "{0}", pucPalData[4]);
              textBoxPalStatusByte5->Text  = System::String::Format( "{0}", pucPalData[5]);
              textBoxPalStatusByte6->Text  = System::String::Format( "{0}", pucPalData[6]);
              textBoxPalStatusByte7->Text  = System::String::Format( "{0}", pucPalData[7]);
              textBoxPalStatusByte8->Text  = System::String::Format( "{0}", pucPalData[8]);
              textBoxPalStatusByte9->Text  = System::String::Format( "{0}", pucPalData[9]);
              textBoxPalStatusByte10->Text = System::String::Format( "{0}", pucPalData[10]);
              textBoxPalStatusByte11->Text = System::String::Format( "{0}", pucPalData[11]);
           }
         }

private: System::Void buttonStatusRdcHsInaktivereignis_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsInaktivereignisReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           char aucDatUhr_2[18];
           char aucDatUhr_3[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsInaktivereignis( &Data);

           for ( i = 0; i < 8; i++)
           {
             aucDatUhr_1[i] = Data[i];
             aucDatUhr_2[i] = Data[cSizeInaktivereignis + i];
             aucDatUhr_3[i] = Data[(2 * cSizeInaktivereignis) + i];
           }

           aucDatUhr_1[8] = 0x20;
           aucDatUhr_2[8] = 0x20;
           aucDatUhr_3[8] = 0x20;

           for ( i = 9; i < 17; i++)
           {
             aucDatUhr_1[i] = Data[i - 1];
             aucDatUhr_2[i] = Data[cSizeInaktivereignis + i - 1];
             aucDatUhr_3[i] = Data[(2* cSizeInaktivereignis) + i - 1];
           }

           aucDatUhr_1[17] = 0;
           aucDatUhr_2[17] = 0;
           aucDatUhr_3[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);
           String^ sDatUhr_2 = gcnew String(aucDatUhr_2);
           String^ sDatUhr_3 = gcnew String(aucDatUhr_3);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsInaktivereignis - NRC = 0x{0:X2}\n", Error));
           textBoxDiagnosticNRC->AppendText(System::String::Format("IE1 ({0}) am ", Data[21]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[20]));

           textBoxDiagnosticNRC->AppendText(System::String::Format("IE2 ({0}) am ", Data[cSizeInaktivereignis + 21]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_2);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[cSizeInaktivereignis + 20]));

           textBoxDiagnosticNRC->AppendText(System::String::Format("IE3 ({0}) am ", Data[(2 * cSizeInaktivereignis) + 21]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_3);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[(2 * cSizeInaktivereignis) + 20]));
         }

private: System::Void buttonStatusRdcHsKalibrierereignis_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsKalibrierereignisReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           char aucDatUhr_2[18];
           char aucDatUhr_3[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsKalibrierereignis( &Data);

           for ( i = 0; i < 8; i++)
           {
             aucDatUhr_1[i] = Data[i + 2];
             aucDatUhr_2[i] = Data[cSizeKalibrierereignis + i + 2];
             aucDatUhr_3[i] = Data[(2 * cSizeKalibrierereignis) + i + 2];
           }

           aucDatUhr_1[8] = 0x20;
           aucDatUhr_2[8] = 0x20;
           aucDatUhr_3[8] = 0x20;

           for ( i = 9; i < 17; i++)
           {
             aucDatUhr_1[i] = Data[i + 1];
             aucDatUhr_2[i] = Data[cSizeKalibrierereignis + i + 1];
             aucDatUhr_3[i] = Data[(2 * cSizeKalibrierereignis) + i + 1];
           }

           aucDatUhr_1[17] = 0;
           aucDatUhr_2[17] = 0;
           aucDatUhr_3[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);
           String^ sDatUhr_2 = gcnew String(aucDatUhr_2);
           String^ sDatUhr_3 = gcnew String(aucDatUhr_3);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsKalibrierereignis - NRC = 0x{0:X2}\n", Error));
           textBoxDiagnosticNRC->AppendText(System::String::Format("KE1 ({0}) am ", Data[49]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[1]));

           textBoxDiagnosticNRC->AppendText(System::String::Format("KE2 ({0}) am ", Data[cSizeKalibrierereignis + 49]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_2);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[cSizeKalibrierereignis + 1]));

           textBoxDiagnosticNRC->AppendText(System::String::Format("KE3 ({0}) am ", Data[(2 * cSizeKalibrierereignis) + 49]));
           textBoxDiagnosticNRC->AppendText(sDatUhr_3);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Root cause {0}\n", Data[(2 * cSizeKalibrierereignis) + 1]));

         }

private: System::Void buttonStatusRdcHsWarnereignisRuecknahme_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignisRuecknahmeReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignisRuecknahme( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignisRuecknahme - NRC = 0x{0:X2}\n", Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));

         }

private: System::Void buttonStatusRdcHsWarnereignis1_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignis1ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignis1( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignis1 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusRdcHsWarnereignis2_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignis2ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignis2( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignis2 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusRdcHsWarnereignis3_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignis3ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignis3( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignis3 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusRdcHsWarnereignisWeich1_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignisWeich1ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignisWeich1( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignisWeich1 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusRdcHsWarnereignisWeich2_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignisWeich2ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignisWeich2( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignisWeich2 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusRdcHsWarnereignisWeich3_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcHsWarnereignisWeich3ReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;
           char aucDatUhr_1[18];
           uint8 i;

           Error = RTE_Stub_StatusRdcHsWarnereignisWeich3( &Data);

           for (i=0; i<8; i++)
           {
             aucDatUhr_1[i] = Data[i];
           }
           aucDatUhr_1[8] = 0x20;
           for (i=9; i<17; i++)
           {
             aucDatUhr_1[i] = Data[i-1];
           }
           aucDatUhr_1[17] = 0;

           String^ sDatUhr_1 = gcnew String(aucDatUhr_1);

           textBoxDiagnosticNRC->Clear();
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcHsWarnereignisWeich3 ({0}) - NRC = 0x{1:X2}\n", Data[50], Error));
           textBoxDiagnosticNRC->AppendText("Am ");
           textBoxDiagnosticNRC->AppendText(sDatUhr_1);
           textBoxDiagnosticNRC->AppendText(System::String::Format(" - Radposition {0}\n", Data[25]));
         }

private: System::Void buttonStatusReLesenDruckcodierung_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8  ucLoop;
           uint8  ucDataCount;
           uint16 ushDataPres;
           uint16 ushDataBatt;
           uint32 ulDataID;

           ImpTypeArrayDcm_StatusReLesenDruckcodierungReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusReLesenDruckcodierung( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusReLesenDruckcodierung () - NRC = 0x{0:X2}\n", Error));

           for( ucLoop = 0; ucLoop < cStatusReLesenDruckcodierungDataArraySize; ucLoop++)
           {
             ulDataID    = ((uint32) (Data[ucLoop * 9 + 0] << 24) + (uint32) (Data[ucLoop * 9 + 1] << 16) + (uint32) (Data[ucLoop * 9 + 2] << 8) + (uint32) Data[ucLoop * 9 + 3]);
             ushDataPres = ((uint16) (Data[ucLoop * 9 + 4] <<  8) + (uint16) (Data[ucLoop * 9 + 5] <<  0));
             ushDataBatt = ((uint16) (Data[ucLoop * 9 + 6] <<  8) + (uint16) (Data[ucLoop * 9 + 7] <<  0));
             ucDataCount = Data[ucLoop * 9 + 8];

             switch( ucLoop)
             {
             case 0:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe0->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe0->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe0->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe0->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe0->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe0->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe0->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe0->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 1:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe1->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe1->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe1->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe1->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe1->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe1->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe1->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe1->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 2:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe2->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe2->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe2->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe2->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe2->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe2->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe2->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe2->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 3:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe3->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe3->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe3->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe3->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe3->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe3->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe3->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe3->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 4:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe4->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe4->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe4->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe4->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe4->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe4->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe4->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe4->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 5:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe5->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe5->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe5->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe5->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe5->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe5->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe5->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe5->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 6:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe6->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe6->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe6->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe6->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe6->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe6->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe6->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe6->Text = System::String::Format( "{0}", ucDataCount); }
             break;

             case 7:
               if( (ulDataID    == 0x00000000u) || (ulDataID    == 0xFFFFFFFFu)) { textBoxDruckcodierungIdRe7->Text    = "unknown"; }else{ textBoxDruckcodierungIdRe7->Text    = System::String::Format( "0x{0:X8}", ulDataID); }
               if( (ushDataPres == 0x0000u)     || (ushDataPres == 0xFFFFu)) { textBoxDruckcodierungPresRe7->Text  = "unknown"; }else{ textBoxDruckcodierungPresRe7->Text  = System::String::Format( "{0}", ushDataPres); }
               if( (ushDataBatt == 0x0000u)     || (ushDataBatt == 0xFFFFu)) { textBoxDruckcodierungBattRe7->Text  = "unknown"; }else{ textBoxDruckcodierungBattRe7->Text  = System::String::Format( "{0}", ushDataBatt); }
               if( (ucDataCount == 0x00u)       || (ucDataCount == 0xFFu)) { textBoxDruckcodierungRecCtRe7->Text = "unknown"; }else{ textBoxDruckcodierungRecCtRe7->Text = System::String::Format( "{0}", ucDataCount); }
             break;
             }
           }
         }

private: System::Void buttonStatusRdcDeveloperDataLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_StatusRdcDeveloperDataLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcDeveloperDataLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcDeveloperDataLesen () - NRC = 0x{0:X2}\n", Error));

           if(Error == RTE_E_OK)
           {
             labelStatusDeveloperDataNRC->Text = "RTE_E_OK";
             labelStatusDeveloperDataNRC->BackColor = System::Drawing::Color::FromArgb(0,255,0);

             textBoxStatusDeveloperDataMUX->Text  = System::String::Format( "{0}", Data[0]);
             textBoxStatusDeveloperDataB0->Text  = System::String::Format( "0x{0:X2}", Data[1]);
             textBoxStatusDeveloperDataB1->Text  = System::String::Format( "0x{0:X2}", Data[2]);
             textBoxStatusDeveloperDataB2->Text  = System::String::Format( "0x{0:X2}", Data[3]);
             textBoxStatusDeveloperDataB3->Text  = System::String::Format( "0x{0:X2}", Data[4]);
             textBoxStatusDeveloperDataB4->Text  = System::String::Format( "0x{0:X2}", Data[5]);
             textBoxStatusDeveloperDataB5->Text  = System::String::Format( "0x{0:X2}", Data[6]);
             textBoxStatusDeveloperDataB6->Text  = System::String::Format( "0x{0:X2}", Data[7]);
             textBoxStatusDeveloperDataB7->Text  = System::String::Format( "0x{0:X2}", Data[8]);
             textBoxStatusDeveloperDataB8->Text  = System::String::Format( "0x{0:X2}", Data[9]);
             textBoxStatusDeveloperDataB9->Text  = System::String::Format( "0x{0:X2}", Data[10]);
             textBoxStatusDeveloperDataB10->Text = System::String::Format( "0x{0:X2}", Data[11]);
             textBoxStatusDeveloperDataB11->Text = System::String::Format( "0x{0:X2}", Data[12]);
             textBoxStatusDeveloperDataB12->Text = System::String::Format( "0x{0:X2}", Data[13]);
             textBoxStatusDeveloperDataB13->Text = System::String::Format( "0x{0:X2}", Data[14]);
             textBoxStatusDeveloperDataB14->Text = System::String::Format( "0x{0:X2}", Data[15]);
             textBoxStatusDeveloperDataB15->Text = System::String::Format( "0x{0:X2}", Data[16]);
             textBoxStatusDeveloperDataB16->Text = System::String::Format( "0x{0:X2}", Data[17]);
             textBoxStatusDeveloperDataB17->Text = System::String::Format( "0x{0:X2}", Data[18]);
             textBoxStatusDeveloperDataB18->Text = System::String::Format( "0x{0:X2}", Data[19]);
             textBoxStatusDeveloperDataB19->Text = System::String::Format( "0x{0:X2}", Data[20]);
           }else{
             labelStatusDeveloperDataNRC->Text = "DCM_E_CONDITIONSNOTCORRECT";
             labelStatusDeveloperDataNRC->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }
         }

private: System::Void buttonStatusRdcErfsAktReifenLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_StatusRdcErfsAktReifenLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcErfsAktReifenLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcErfsAktReifenLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcErfsEcoTabelleLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcErfsEcoTabelleLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcErfsEcoTabelleLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcErfsEcoTabelleLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcErfsAktReifenEcoLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_StatusRdcErfsAktReifenEcoLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcErfsAktReifenEcoLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcErfsAktReifenEcoLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcRidAktReifenQrCodeLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcRidAktReifenQrCodeLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_RdcRidAktReifenQrCodeLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("RdcRidAktReifenQrCodeLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcRidAlteReifenQrCodeLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcRidAlteReifenQrCodeLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_RdcRidAlteReifenQrCodeLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("RdcRidAlteReifenQrCodeLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcRidAktReifenLaufstreckeLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcRidAktReifenLaufstreckeLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_RdcRidAktReifenLaufstreckeLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("RdcRidAktReifenLaufstreckeLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcRidAlteReifenLaufstreckeLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_RdcRidAlteReifenLaufstreckeLesenReadDataType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_RdcRidAlteReifenLaufstreckeLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("RdcRidAlteReifenLaufstreckeLesen () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonStatusRdcExtParkSupervisionLesen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeArrayDcm_StatusRdcExtParkSupervisionLesenType Data;
           ImpTypeRefDcm_NegativeResponseCodeType Error;

           Error = RTE_Stub_StatusRdcExtParkSupervisionLesen( &Data);
           textBoxDiagnosticNRC->AppendText(System::String::Format("StatusRdcExtParkSupervisionLesen () - NRC = 0x{0:X2}\n", Error));

           switch ( Data[cucIxStatRdcExtParkSupConfigWert])
           {
             case 0:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 1:
               checkBoxDiagExtParkSupNotification->Checked = true;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 2:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = true;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 3:
               checkBoxDiagExtParkSupNotification->Checked = true;
               checkBoxDiagExtParkSupWarning->Checked = true;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 4:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = true;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 5:
               checkBoxDiagExtParkSupNotification->Checked = true;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = true;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 6:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = true;
               checkBoxDiagExtParkSupMobilityLoss->Checked = true;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 7:
               checkBoxDiagExtParkSupNotification->Checked = true;
               checkBoxDiagExtParkSupWarning->Checked = true;
               checkBoxDiagExtParkSupMobilityLoss->Checked = true;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             case 8:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = true;
               checkBoxDiagExtParkSupInvalidValue->Checked = false;
             break;

             default:
               checkBoxDiagExtParkSupNotification->Checked = false;
               checkBoxDiagExtParkSupWarning->Checked = false;
               checkBoxDiagExtParkSupMobilityLoss->Checked = false;
               checkBoxDiagExtParkSupNotActive->Checked = false;
               checkBoxDiagExtParkSupInvalidValue->Checked = true;
             break;
           }

           labelDiagExtParkSupTolTempCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupTolTempCompWert] * 10);
           labelDiagExtParkSupTolTempNonCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupTolTempNonCompWert] * 10);
           labelDiagExtParkSupMobilityLossThValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupMobilityLossThWert] * 100);
           labelDiagExtParkSupWarnPercentCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupWarnPercentCompWert]);
           labelDiagExtParkSupWarnPercentNonCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupWarnPercentNonCompWert]);
           labelDiagExtParkSupNotifPercentCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupNotifPercentCompWert]);
           labelDiagExtParkSupNotifPercentNonCompValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupNotifPercentNonCompWert]);
           labelDiagExtParkSupRefTempValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupRefTempWert + 0] * 256 + Data[cucIxStatRdcExtParkSupRefTempWert + 1]) - 50);
           labelDiagExtParkSupLastAmbPresValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupLastAmbPresWert] * 2 + 600);
           labelDiagExtParkSupRcpFrontValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupRcpFrontWert] * 100);
           labelDiagExtParkSupRcpRearValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupRcpRearWert] * 100);
           labelDiagExtParkSupQuFnTyrInfoValue->Text = System::String::Format( "0x{0:X2}", Data[cucIxStatRdcExtParkSupQuFnTyrInfoWert]);
           labelDiagExtParkSupQuTplValue->Text = System::String::Format( "0x{0:X2}", Data[cucIxStatRdcExtParkSupQuTplWert]);
           labelDiagExtParkSupIntWarnThFrontValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupIntWarnThFrontWert + 0] * 256 + Data[cucIxStatRdcExtParkSupIntWarnThFrontWert + 1]));
           labelDiagExtParkSupIntWarnThRearValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupIntWarnThRearWert + 0] * 256 + Data[cucIxStatRdcExtParkSupIntWarnThRearWert + 1]));
           labelDiagExtParkSupIntNotifThFrontValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupIntNotifThFrontWert + 0] * 256 + Data[cucIxStatRdcExtParkSupIntNotifThFrontWert + 1]));
           labelDiagExtParkSupIntNotifThRearValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupIntNotifThRearWert + 0] * 256 + Data[cucIxStatRdcExtParkSupIntNotifThRearWert + 1]));
           labelDiagExtParkSupActTirePressureFlValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupActTirePressureFlWert + 0] * 256 + Data[cucIxStatRdcExtParkSupActTirePressureFlWert + 1]));
           labelDiagExtParkSupActTirePressureFrValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupActTirePressureFrWert + 0] * 256 + Data[cucIxStatRdcExtParkSupActTirePressureFrWert + 1]));
           labelDiagExtParkSupActTirePressureRlValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupActTirePressureRlWert + 0] * 256 + Data[cucIxStatRdcExtParkSupActTirePressureRlWert + 1]));
           labelDiagExtParkSupActTirePressureRrValue->Text = System::String::Format( "{0}", (Data[cucIxStatRdcExtParkSupActTirePressureRrWert + 0] * 256 + Data[cucIxStatRdcExtParkSupActTirePressureRrWert + 1]));
           labelDiagExtParkSupActTireTempFlValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupActTireTempFlWert] - 50);
           labelDiagExtParkSupActTireTempFrValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupActTireTempFrWert] - 50);
           labelDiagExtParkSupActTireTempRlValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupActTireTempRlWert] - 50);
           labelDiagExtParkSupActTireTempRrValue->Text = System::String::Format( "{0}", Data[cucIxStatRdcExtParkSupActTireTempRrWert] - 50);
           labelDiagExtParkSupActiveCcm1Value->Text = System::String::Format( "0x{0:X4}", (Data[cucIxStatRdcExtParkSupActiveCcm1Wert + 0] * 256 + Data[cucIxStatRdcExtParkSupActiveCcm1Wert + 1]));
           labelDiagExtParkSupActiveCcm2Value->Text = System::String::Format( "0x{0:X4}", (Data[cucIxStatRdcExtParkSupActiveCcm2Wert + 0] * 256 + Data[cucIxStatRdcExtParkSupActiveCcm2Wert + 1]));
           labelDiagExtParkSupActiveCcm3Value->Text = System::String::Format( "0x{0:X4}", (Data[cucIxStatRdcExtParkSupActiveCcm3Wert + 0] * 256 + Data[cucIxStatRdcExtParkSupActiveCcm3Wert + 1]));
           labelDiagExtParkSupActiveCcm4Value->Text = System::String::Format( "0x{0:X4}", (Data[cucIxStatRdcExtParkSupActiveCcm4Wert + 0] * 256 + Data[cucIxStatRdcExtParkSupActiveCcm4Wert + 1]));
           labelDiagExtParkSupActiveCcm5Value->Text = System::String::Format( "0x{0:X4}", (Data[cucIxStatRdcExtParkSupActiveCcm5Wert + 0] * 256 + Data[cucIxStatRdcExtParkSupActiveCcm5Wert + 1]));
           labelDiagExtParkSupSleepDateValue->Text = System::String::Format(  "{0:X}{1:X}.{2:X}{3:X}.{4:X}{5:X}", (Data[cucIxStatRdcExtParkSupSleepDateWert  + 0] - 0x30), (Data[cucIxStatRdcExtParkSupSleepDateWert  + 1] - 0x30), (Data[cucIxStatRdcExtParkSupSleepDateWert  + 3] - 0x30), (Data[cucIxStatRdcExtParkSupSleepDateWert  + 4] - 0x30), (Data[cucIxStatRdcExtParkSupSleepDateWert  + 6] - 0x30), (Data[cucIxStatRdcExtParkSupSleepDateWert  + 7] - 0x30));
           labelDiagExtParkSupSleepTimeValue->Text = System::String::Format(  "{0:X}{1:X}:{2:X}{3:X}:{4:X}{5:X}", (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 0] - 0x30), (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 1] - 0x30), (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 3] - 0x30), (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 4] - 0x30), (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 6] - 0x30), (Data[cucIxStatRdcExtParkSupSleepTimeWert  + 7] - 0x30));
           labelDiagExtParkSupWakeupDateValue->Text = System::String::Format( "{0:X}{1:X}.{2:X}{3:X}.{4:X}{5:X}", (Data[cucIxStatRdcExtParkSupWakeupDateWert + 0] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupDateWert + 1] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupDateWert + 3] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupDateWert + 4] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupDateWert + 6] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupDateWert + 7] - 0x30));
           labelDiagExtParkSupWakeupTimeValue->Text = System::String::Format( "{0:X}{1:X}:{2:X}{3:X}:{4:X}{5:X}", (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 0] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 1] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 3] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 4] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 6] - 0x30), (Data[cucIxStatRdcExtParkSupWakeupTimeWert + 7] - 0x30));
         }

private: System::Void listBoxFunktionsnummer_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
         {
           listBoxAktionsnummerEinAus->Enabled = false;
           listBoxAktionsnummerSetReset->Enabled = false;
           listBoxAktionsnummerStartEnde->Enabled = false;

           if( listBoxFunktionsnummer->Text == "1: BANDMODE")
           {
             listBoxAktionsnummerEinAus->Enabled = true;
           }else if( listBoxFunktionsnummer->Text == "4: TEST_ER_FAHRT")
		       {
             listBoxAktionsnummerSetReset->Enabled = true;
           }else if( listBoxFunktionsnummer->Text == "8: CAL_REQUEST")
		       {
             listBoxAktionsnummerStartEnde->Enabled = true;
           }else{
           }
         }

private: System::Void buttonSteuernDigitalRdc_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;
           uint8 ucFunktionsnummer = 0;
           uint8 ucAktionsnummer = 0;

           if( listBoxFunktionsnummer->Text == "1: BANDMODE")
		       {
             if( listBoxAktionsnummerEinAus->Text == "0: AUS")
             {

               ucFunktionsnummer = cFunctionNo_BandmodeDS;
               ucAktionsnummer = cActionNo_BandmodeAusDS;
             }else if( listBoxAktionsnummerEinAus->Text == "1: EIN")
             {

               ucFunktionsnummer = cFunctionNo_BandmodeDS;
               ucAktionsnummer = cActionNo_BandmodeEinDS;
             }else{
             }
           }else if( listBoxFunktionsnummer->Text == "4: TEST_ER_FAHRT")
	         {
             if( listBoxAktionsnummerSetReset->Text == "0: RESET")
             {

               ucFunktionsnummer = cFunctionNo_TestErFahrtDS;
               ucAktionsnummer = cActionNo_TestErFahrtResetDS;
             }else if( listBoxAktionsnummerSetReset->Text == "1: SET")
             {

               ucFunktionsnummer = cFunctionNo_TestErFahrtDS;
               ucAktionsnummer = cActionNo_TestErFahrtSetDS;
             }else if( listBoxAktionsnummerSetReset->Text == "2: SET_NO_SPEED")
             {

               ucFunktionsnummer = cFunctionNo_TestErFahrtDS;
               ucAktionsnummer = cActionNo_TestErFahrtSetNoSpeedDS;
             }else{
             }
           }else if( listBoxFunktionsnummer->Text == "8: CAL_REQUEST")
	         {
             if( listBoxAktionsnummerStartEnde->Text == "0: END")
             {

               ucFunktionsnummer = cFunctionNo_CalRequestDS;
               ucAktionsnummer = cActionNo_CalRequestResetDS;
             }else if( listBoxAktionsnummerStartEnde->Text == "1: START")
             {

               ucFunktionsnummer = cFunctionNo_CalRequestDS;
               ucAktionsnummer = cActionNo_CalRequestSetDS;
             }else{
             }
           }else{
           }

           Error = RTE_Stub_SteuernDigitalRdc( ucFunktionsnummer, ucAktionsnummer);
           if( Error == DCM_E_REQUESTOUTOFRANGE)
           {
             labelConditionDiagJobBM->Text = "DCM_E_REQUESTOUTOFRANGE (0x31)";
             labelConditionDiagJobBM->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }else if( Error == DCM_E_CONDITIONSNOTCORRECT)
           {
             labelConditionDiagJobBM->Text = "DCM_E_CONDITIONSNOTCORRECT (0x22)";
             labelConditionDiagJobBM->BackColor = System::Drawing::Color::FromArgb(255,0,0);
           }else{
             labelConditionDiagJobBM->Text = "RTE_E_OK (0x00)";
             labelConditionDiagJobBM->BackColor = System::Drawing::Color::FromArgb(0,255,0);
           }

           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernDigitalRdc ({0} ; {1}) - NRC = 0x{2:X2}\n", ucFunktionsnummer, ucAktionsnummer, Error));
         }

private: System::Void buttonSteuernRadelektronikVorgeben_Click(System::Object^  sender, System::EventArgs^  e) {

           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;
           uint32 ulReID = 0;
           uint8 ucRadPos = cAnzRad;

           if( listBoxVorgabeRadposition->Text == "0: vorne links")
		       {
             ucRadPos = cRadPosVL;
           }else if( listBoxVorgabeRadposition->Text == "1: vorne rechts")
           {
             ucRadPos = cRadPosVR;
           }else if( listBoxVorgabeRadposition->Text == "2: hinten links")
           {
             ucRadPos = cRadPosHL;
           }else if( listBoxVorgabeRadposition->Text == "3: hinten rechts")
           {
             ucRadPos = cRadPosHR;
           }else{
             ucRadPos = cAnzRad;
           }

           ulReID = (uint32) System::Decimal::ToUInt32(numericUpDownVorgabeID->Value);

           Error = RTE_Stub_SteuernRadelektronikVorgeben( ulReID, ucRadPos);
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernRadelektronikVorgeben ({0} ; {1}) - NRC = 0x{2:X2}\n", ulReID, ucRadPos, Error));
         }

private: System::Void buttonSteuernRdcErfsEcoReifentabelleVorgeben_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;

           Error = RTE_Stub_SteuernRdcErfsEcoReifentabelleVorgeben();
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernRdcErfsEcoReifentabelleVorgeben () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonSteuernRdcErfsEcoNeueReifenVorgeben_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;

           Error = RTE_Stub_SteuernRdcErfsEcoNeueReifenVorgeben();
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernRdcErfsEcoNeueReifenVorgeben () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonSteuernRdcErfsEcoAktReifenPosVorgeben_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;

           Error = RTE_Stub_SteuernRdcErfsEcoAktReifenPosVorgeben();
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernRdcErfsEcoAktReifenPosVorgeben () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonSteuernRdcErfsDeveloperConfig_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;

           Error = RTE_Stub_SteuernRdcErfsDeveloperConfig();
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernErfsDeveloperConfig () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonSteuernRdcDeveloperConfig_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeRefDcm_NegativeResponseCodeType Error = RTE_E_OK;
           ImpTypeArrayDcm_SteuernRdcDeveloperConfigWriteDataType aucRdcTestData;

           uint8 ucLoop;

           for( ucLoop = 0; ucLoop < sizeof(aucRdcTestData); ucLoop++)
           {
             aucRdcTestData[ucLoop] = 0;
           }

           aucRdcTestData[0] = (uint8) System::Decimal::ToByte( numericUpDownSteuernRdcDeveloperConfigCommand->Value);
           aucRdcTestData[1] = (uint8) System::Decimal::ToByte( numericUpDownSteuernRdcDeveloperConfigTestData->Value);

           Error = RTE_Stub_SteuernRdcDeveloperConfig( &aucRdcTestData);
           textBoxDiagnosticNRC->AppendText(System::String::Format("SteuernRdcDeveloperConfig () - NRC = 0x{0:X2}\n", Error));
         }

private: System::Void buttonFsLoeschen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucLoop;

           for( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++)
           {
             if( tRDCiDtclist[ucLoop].ucType == cDemPrimaryType)
             {
               tRDCiDtclist[ucLoop].ucStatus = DEM_EVENT_STATUS_PASSED;

               InitDtcUwbData( ucLoop);
             }
           }
           WriteDtcListToNvmBlock();

           (void) RDCi_ROpInvDemErrorRdci1To3WrongWuMounted_InitMonitorForEvent_104         ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdci4WrongWuMounted_InitMonitorForEvent_105            ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciATempInvalid_InitMonitorForEvent_106               ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciATempTimeout_InitMonitorForEvent_107               ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciAutoLearningFailed_InitMonitorForEvent_109         ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciConVehAlive_InitMonitorForEvent_111                ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciConVehCrc_InitMonitorForEvent_112                  ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciConVehInvalid_InitMonitorForEvent_113              ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciConVehTimeout_InitMonitorForEvent_114              ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciEinheitenBn2020Invalid_InitMonitorForEvent_116     ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciEinheitenBn2020Timeout_InitMonitorForEvent_117     ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciErfsCodingDataInconsistent_InitMonitorForEvent_118 ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciGatewayOrAntennaError_InitMonitorForEvent_119      ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciOtherWuSensorType_InitMonitorForEvent_121          ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRdcDtPckg1Alive_InitMonitorForEvent_124            ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRdcDtPckg1Invalid_InitMonitorForEvent_125          ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRdcDtPckg1Timeout_InitMonitorForEvent_126          ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRelativzeitInvalid_InitMonitorForEvent_127         ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRelativzeitTimeout_InitMonitorForEvent_128         ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciRfExternalInterference_InitMonitorForEvent_129     ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciTpmsManufactoryMode_InitMonitorForEvent_131        ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciUnspecifiedWfcDefect_InitMonitorForEvent_132       ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciUnspecifiedWuMute_InitMonitorForEvent_133          ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciVVehAliveFailure_InitMonitorForEvent_134           ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciVVehCogInvalid_InitMonitorForEvent_135             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciVVehCogQualifier_InitMonitorForEvent_136           ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciVVehCrcFailure_InitMonitorForEvent_137             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciVVehTimeout_InitMonitorForEvent_138                ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuDefectFl_InitMonitorForEvent_140                 ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuDefectFr_InitMonitorForEvent_141                 ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuDefectRl_InitMonitorForEvent_142                 ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuDefectRr_InitMonitorForEvent_143                 ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuLocalisationFailed_InitMonitorForEvent_144       ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuLowBatteryFl_InitMonitorForEvent_145             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuLowBatteryFr_InitMonitorForEvent_146             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuLowBatteryRl_InitMonitorForEvent_147             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuLowBatteryRr_InitMonitorForEvent_148             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuMuteFl_InitMonitorForEvent_149                   ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuMuteFr_InitMonitorForEvent_150                   ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuMuteRl_InitMonitorForEvent_151                   ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWuMuteRr_InitMonitorForEvent_152                   ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
        }

private: System::Void buttonIsLoeschen_Click(System::Object^  sender, System::EventArgs^  e)
         {
           uint8 ucLoop;

           for( ucLoop = 0; ucLoop < cMaxErrorCount; ucLoop++)
           {
             if( tRDCiDtclist[ucLoop].ucType == cDemSecondaryType)
             {
               tRDCiDtclist[ucLoop].ucStatus = DEM_EVENT_STATUS_PASSED;

               InitDtcUwbData( ucLoop);
             }
           }
           WriteDtcListToNvmBlock();

           (void) RDCi_ROpInvDemErrorRdciAusfall_InitMonitorForEvent_108                    ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciBefuellhinweis_InitMonitorForEvent_110             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciDruckwarnung_InitMonitorForEvent_115               ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciKalibrierung_InitMonitorForEvent_120               ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciPannenwarnung_InitMonitorForEvent_122              ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
           (void) RDCi_ROpInvDemErrorRdciWarnruecknahme_InitMonitorForEvent_139             ( Rte_Inst_CtApHufTpmsSWC, DEM_INIT_MONITOR_CLEAR);
         }

#endif
