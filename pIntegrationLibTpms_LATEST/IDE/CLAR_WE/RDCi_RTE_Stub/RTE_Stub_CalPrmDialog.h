#ifndef __RTE_STUB_CALPRM_DIALOG_H
#define __RTE_STUB_CALPRM_DIALOG_H

private: System::Void buttonPutCodingData2RdciAppl_Click(System::Object^  sender, System::EventArgs^  e)
         {
           ReInitRdciSWC();
         }

private: System::Void checkRDCi_aktiv_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkRDCi_aktiv->Checked == TRUE)
           {
             NvmDscCodierdatenAllgemein_WriteByte( C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_BYTE, C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_MASK, (uint8) AKTIV_RDC);
           }else{
             NvmDscCodierdatenAllgemein_WriteByte( C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_BYTE, C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_MASK, (uint8) DISABLE);
           }
         }

private: System::Void checkBoxCRdciTPrewarnNc_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciTPrewarnNc->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_PREWARN_NC_BYTE, C_RDCI_T_PREWARN_NC_MASK, (uint8) C_RDCI_T_PREWARN_NC_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_PREWARN_NC_BYTE, C_RDCI_T_PREWARN_NC_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciMaxThreshold_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciMaxThreshold->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_THRESHOLD_BYTE, C_RDCI_MAX_THRESHOLD_MASK, (uint8) C_RDCI_MAX_THRESHOLD_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_THRESHOLD_BYTE, C_RDCI_MAX_THRESHOLD_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciPrewarnEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciPrewarnEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_ENABLE_BYTE, C_RDCI_PREWARN_ENABLE_MASK, (uint8) C_RDCI_PREWARN_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_ENABLE_BYTE, C_RDCI_PREWARN_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciStatInit_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciStatInit->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_STAT_INIT_BYTE, C_RDCI_STAT_INIT_MASK, (uint8) C_RDCI_STAT_INIT_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_STAT_INIT_BYTE, C_RDCI_STAT_INIT_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciNumPrewarnDetect_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciNumPrewarnDetect->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_NUM_PREWARN_DETECT_BYTE, C_RDCI_NUM_PREWARN_DETECT_MASK, (uint8) C_RDCI_NUM_PREWARN_DETECT_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_NUM_PREWARN_DETECT_BYTE, C_RDCI_NUM_PREWARN_DETECT_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciPrewarnIgnition_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciPrewarnIgnition->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_IGNITION_BYTE, C_RDCI_PREWARN_IGNITION_MASK, (uint8) C_RDCI_PREWARN_IGNITION_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_IGNITION_BYTE, C_RDCI_PREWARN_IGNITION_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciPanneBefPos_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciPanneBefPos->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_BEF_POS_BYTE, C_RDCI_PANNE_BEF_POS_MASK, (uint8) C_RDCI_PANNE_BEF_POS_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_BEF_POS_BYTE, C_RDCI_PANNE_BEF_POS_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciFastDeflateEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciFastDeflateEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_FAST_DEFLATE_ENABLE_BYTE, C_RDCI_FAST_DEFLATE_ENABLE_MASK, (uint8) C_RDCI_FAST_DEFLATE_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_FAST_DEFLATE_ENABLE_BYTE, C_RDCI_FAST_DEFLATE_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciTyrIdFiltGw_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciTyrIdFiltGw->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TYR_ID_FILT_GW_BYTE, C_RDCI_TYR_ID_FILT_GW_MASK, (uint8) C_RDCI_TYR_ID_FILT_GW_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TYR_ID_FILT_GW_BYTE, C_RDCI_TYR_ID_FILT_GW_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciResetPlausi_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciResetPlausi->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RESET_PLAUSI_BYTE, C_RDCI_RESET_PLAUSI_MASK, (uint8) C_RDCI_RESET_PLAUSI_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RESET_PLAUSI_BYTE, C_RDCI_RESET_PLAUSI_MASK, (uint8) FALSE);
           }
         }

private: System::Void listBoxCRdciTpmsMarket_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
         {
		       uint8 ucMarket;

           if( listBoxCRdciTpmsMarket->Text == "0: EU")
           {
             ucMarket = EU;
           }else if( listBoxCRdciTpmsMarket->Text == "1: US")
           {
             ucMarket = US;
           }else if( listBoxCRdciTpmsMarket->Text == "2: China")
           {
             ucMarket = CHINA;
           }else if( listBoxCRdciTpmsMarket->Text == "3: Japan")
           {
             ucMarket = JAPAN;
           }else{
             ucMarket = UNDEFINED;
           }

           NvmDscCodierdatenRDCi_Activate( ucMarket);
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TPMS_MARKET_BYTE, C_RDCI_TPMS_MARKET_MASK, (uint8) (ucMarket << 2));
	       }

private: System::Void checkBoxCRdciSensorForeignAkRdk_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciSensorForeignAkRdk->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_FOREIGN_AK_RDK_BYTE, C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK, (uint8) C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_FOREIGN_AK_RDK_BYTE, C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciSensorLocSync_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciSensorLocSync->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_LOC_SYNC_BYTE, C_RDCI_SENSOR_LOC_SYNC_MASK, (uint8) C_RDCI_SENSOR_LOC_SYNC_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_LOC_SYNC_BYTE, C_RDCI_SENSOR_LOC_SYNC_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciErfsEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciErfsEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_ENABLE_BYTE, C_RDCI_ERFS_ENABLE_MASK, (uint8) C_RDCI_ERFS_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_ENABLE_BYTE, C_RDCI_ERFS_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciTrefSeasonalAdjustment_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciTrefSeasonalAdjustment->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_BYTE, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK, (uint8) C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_BYTE, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciDispReset_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciDispReset->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_RESET_BYTE, C_RDCI_DISP_RESET_MASK, (uint8) C_RDCI_DISP_RESET_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_RESET_BYTE, C_RDCI_DISP_RESET_MASK, (uint8) FALSE);
           }
         }

private: System::Void numericUpDownCRdciCorHoldOffTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_COR_HOLD_OFF_TIME_BYTE, C_RDCI_COR_HOLD_OFF_TIME_MASK, (uint8) (((System::Decimal::ToByte( numericUpDownCRdciCorHoldOffTime->Value)) / 5) << 5));
         }

private: System::Void numericUpDownCRdciTRefShift_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_REF_SHIFT_BYTE, C_RDCI_T_REF_SHIFT_MASK, (uint8) numericUpDownCRdciTRefShift->Value);
         }

private: System::Void numericUpDownCRdciUiaThC_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIA_TH_C_BYTE, C_RDCI_UIA_TH_C_MASK, (uint8) numericUpDownCRdciUiaThC->Value);
         }

private: System::Void numericUpDownCRdciUiwThC_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIW_TH_C_BYTE, C_RDCI_UIW_TH_C_MASK, (uint8) numericUpDownCRdciUiwThC->Value);
         }

private: System::Void numericUpDownCRdciUiaThNc_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIA_TH_NC_BYTE, C_RDCI_UIA_TH_NC_MASK, (uint8) numericUpDownCRdciUiaThNc->Value);
         }

private: System::Void numericUpDownCRdciUiwThNc_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIW_TH_NC_BYTE, C_RDCI_UIW_TH_NC_MASK, (uint8) numericUpDownCRdciUiwThNc->Value);
         }

private: System::Void numericUpDownCRdciPanneTh_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_TH_BYTE, C_RDCI_PANNE_TH_MASK, (uint8) (numericUpDownCRdciPanneTh->Value / 25));
         }

private: System::Void numericUpDownCRdciMinRcpFa_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MIN_RCP_FA_BYTE, C_RDCI_MIN_RCP_FA_MASK, (uint8) (numericUpDownCRdciMinRcpFa->Value / 25));
         }

private: System::Void numericUpDownCRdciMinRcpRa_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MIN_RCP_RA_BYTE, C_RDCI_MIN_RCP_RA_MASK, (uint8) (numericUpDownCRdciMinRcpRa->Value / 25));
         }

private: System::Void numericUpDownCRdciDeltaPLR_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DELTA_P_L_R_BYTE, C_RDCI_DELTA_P_L_R_MASK, (uint8) (numericUpDownCRdciDeltaPLR->Value / 25));
         }

private: System::Void numericUpDownCRdciPInitRangeMax_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_P_INIT_RANGE_MAX_BYTE, C_RDCI_P_INIT_RANGE_MAX_MASK, (uint8) (numericUpDownCRdciPInitRangeMax->Value / 25));
         }

private: System::Void numericUpDownCRdciTimeoutPrewarn_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TIMEOUT_PREWARN_BYTE, C_RDCI_TIMEOUT_PREWARN_MASK, (uint8) numericUpDownCRdciTimeoutPrewarn->Value);
         }

private: System::Void numericUpDownCRdciDtAmbPrewarn_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DT_AMB_PREWARN_BYTE, C_RDCI_DT_AMB_PREWARN_MASK, (uint8) numericUpDownCRdciDtAmbPrewarn->Value);
         }

private: System::Void numericUpDownCRdciDpToIPmin_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DP_TO_I_PMIN_BYTE, C_RDCI_DP_TO_I_PMIN_MASK, (uint8) (numericUpDownCRdciDpToIPmin->Value / 25));
         }

private: System::Void numericUpDownCRdciLearnLocateConfig_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint16 ushValue;

           ushValue = (uint16) System::Decimal::ToUInt16( numericUpDownCRdciLearnLocateConfig->Value);

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_0, C_RDCI_LEARN_LOCATE_CONFIG_MASK_0, ((ushValue >> 0) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_1, C_RDCI_LEARN_LOCATE_CONFIG_MASK_1, ((ushValue >> 8) & 0x00ffu));
         }

private: System::Void numericUpDownCRdciTrefSeasAdjConfig_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           uint32 ulValue;

           ulValue = (uint32) System::Decimal::ToUInt32( numericUpDownCRdciTrefSeasAdjConfig->Value);

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_0, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_0, ((ulValue >>  0) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_1, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_1, ((ulValue >>  8) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_2, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_2, ((ulValue >> 16) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_3, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_3, ((ulValue >> 24) & 0x00ffu));
         }

private: System::Void numericUpDownCRdciXminCoolTire_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_XMIN_COOL_TIRE_BYTE, C_RDCI_XMIN_COOL_TIRE_MASK, (uint8) numericUpDownCRdciXminCoolTire->Value);
         }

private: System::Void numericUpDownCRdciMaxCorTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_COR_TIME_BYTE, C_RDCI_MAX_COR_TIME_MASK, (uint8) numericUpDownCRdciMaxCorTime->Value);
         }

private: System::Void numericUpDownCRdciMaxCorRcp_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_COR_RCP_BYTE, C_RDCI_MAX_COR_RCP_MASK, (uint8) (numericUpDownCRdciMaxCorRcp->Value / 25));
         }

private: System::Void numericUpDownCRdciThCTol_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TH_C_TOL_BYTE, C_RDCI_TH_C_TOL_MASK, (uint8) (numericUpDownCRdciThCTol->Value / 10));
         }

private: System::Void numericUpDownCRdciThNCTol_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TH_NC_TOL_BYTE, C_RDCI_TH_NC_TOL_MASK, (uint8) (((System::Decimal::ToByte( numericUpDownCRdciThNCTol->Value)) / 10) << 4));
         }

private: System::Void numericUpDownCRdciLongHoldTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LONG_HOLD_TIME_BYTE, C_RDCI_LONG_HOLD_TIME_MASK, (uint8) (numericUpDownCRdciLongHoldTime->Value - 5));
         }

private: System::Void numericUpDownCRdciShortHoldTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SHORT_HOLD_TIME_BYTE, C_RDCI_SHORT_HOLD_TIME_MASK, (uint8) (System::Decimal::ToByte( numericUpDownCRdciShortHoldTime->Value - 1) << 4));
         }

private: System::Void numericUpDownCRdciDispConfTimeout_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_CONF_TIMEOUT_BYTE, C_RDCI_DISP_CONF_TIMEOUT_MASK, (uint8) (System::Decimal::ToByte( numericUpDownCRdciDispConfTimeout->Value) << 4));
         }

private: System::Void checkBoxCRdciEcoRcpEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciEcoRcpEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ECO_RCP_ENABLE_BYTE, C_RDCI_ECO_RCP_ENABLE_MASK, (uint8) C_RDCI_ECO_RCP_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ECO_RCP_ENABLE_BYTE, C_RDCI_ECO_RCP_ENABLE_MASK, (uint8) FALSE);
           }

         }

private: System::Void checkBoxCRdciRidEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciRidEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RID_ENABLE_BYTE, C_RDCI_RID_ENABLE_MASK, (uint8) C_RDCI_RID_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RID_ENABLE_BYTE, C_RDCI_RID_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void checkBoxCRdciDefaultLoadCond_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciDefaultLoadCond->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_LOAD_COND_BYTE, C_RDCI_DEFAULT_LOAD_COND_MASK, (uint8) C_RDCI_DEFAULT_LOAD_COND_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_LOAD_COND_BYTE, C_RDCI_DEFAULT_LOAD_COND_MASK, (uint8) FALSE);
           }
         }

private: System::Void listBoxCRdciErfsPlacardSource_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
         {
		       uint8 ucPlacard;

           ucPlacard = listBoxCRdciErfsPlacardSource->SelectedIndex;

           if( listBoxCRdciErfsPlacardSource->Text == "1: CAF_ERFS2_ECO_Block")
           {
             ucPlacard = CAF_ERFS2_ECO_BLOCK;
           }else if( listBoxCRdciErfsPlacardSource->Text == "2: BMW_Factory_HO")
           {
             ucPlacard = BMW_FACTORY_HO;
           }else if( listBoxCRdciErfsPlacardSource->Text == "3: Remote_Update")
           {
             ucPlacard = REMOTE_UPDATE;
           }else{
             ucPlacard = INVALID;
           }

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_PLACARD_SOURCE_BYTE, C_RDCI_ERFS_PLACARD_SOURCE_MASK, (uint8) (ucPlacard << 1));

         }

private: System::Void radioButtonManual_eRFS_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( radioButtonManual_eRFS->Checked == true)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_MENU_SEL_BYTE, C_RDCI_DEFAULT_MENU_SEL_MASK, (uint8) FALSE);
           }else{
           }
         }

private: System::Void radioButtonAutomatic_RID_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( radioButtonAutomatic_RID->Checked == true)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_MENU_SEL_BYTE, C_RDCI_DEFAULT_MENU_SEL_MASK, C_RDCI_DEFAULT_MENU_SEL_MASK);
           }else{
           }
         }

private: System::Void checkBoxCRdciSpeedCcmEnable_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
         {
           if( checkBoxCRdciSpeedCcmEnable->Checked == TRUE)
           {
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_ENABLE_BYTE, C_RDCI_T_PREWARN_NC_MASK, (uint8) C_RDCI_SPEED_CCM_ENABLE_MASK);
           }else{
             NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_ENABLE_BYTE, C_RDCI_SPEED_CCM_ENABLE_MASK, (uint8) FALSE);
           }
         }

private: System::Void numericUpDownCRdciSpeedCcmHyst_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_HYST_BYTE, C_RDCI_SPEED_CCM_HYST_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciSpeedCcmHyst->Value));
         }

private: System::Void numericUpDownCRdciSpeedCcmTh_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeValCRdciSpeedCcmTh SpeedCcmTh;

           SpeedCcmTh = (ImpTypeValCRdciSpeedCcmTh) System::Decimal::ToUInt16( numericUpDownCRdciSpeedCcmTh->Value);

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TH_BYTE_0, C_RDCI_SPEED_CCM_TH_MASK_0, ((SpeedCcmTh >> 0) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TH_BYTE_1, C_RDCI_SPEED_CCM_TH_MASK_1, ((SpeedCcmTh >> 8) & 0x00ffu));
         }

private: System::Void numericUpDownCRdciSpeedCcmPressOffsetFa_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeValCRdciSpeedCcmPressOffsetFa SpeedCcmPressOffsetFa;

           SpeedCcmPressOffsetFa = (ImpTypeValCRdciSpeedCcmTh) System::Decimal::ToInt16( numericUpDownCRdciSpeedCcmPressOffsetFa->Value);

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_0, ((SpeedCcmPressOffsetFa >> 0) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_1, ((SpeedCcmPressOffsetFa >> 8) & 0x00ffu));
         }

private: System::Void numericUpDownCRdciSpeedCcmPressOffsetRa_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           ImpTypeValCRdciSpeedCcmPressOffsetRa SpeedCcmPressOffsetRa;

           SpeedCcmPressOffsetRa = (ImpTypeValCRdciSpeedCcmTh) System::Decimal::ToInt16( numericUpDownCRdciSpeedCcmPressOffsetRa->Value);

           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_0, ((SpeedCcmPressOffsetRa >> 0) & 0x00ffu));
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_1, ((SpeedCcmPressOffsetRa >> 8) & 0x00ffu));
         }

private: System::Void numericUpDownCRdciSpeedCcmTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TIME_BYTE, C_RDCI_SPEED_CCM_TIME_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciSpeedCcmTime->Value));
         }

private: System::Void numericUpDownCRdciParkSupMobilityLossThresholdValue_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_BYTE, C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_MASK, (uint8) ((System::Decimal::ToUInt16( numericUpDownCRdciParkSupMobilityLossThresholdValue->Value) + 50) / 100));
         }

private: System::Void numericUpDownCRdciParkSupNotificationThresholdValueC_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciParkSupNotificationThresholdValueC->Value));
         }

private: System::Void numericUpDownCRdciParkSupNotificationThresholdValueNc_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciParkSupNotificationThresholdValueNc->Value));
         }

private: System::Void numericUpDownCRdciParkSupWarningThresholdValueC_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciParkSupWarningThresholdValueC->Value));
         }

private: System::Void numericUpDownCRdciParkSupWarningThresholdValueNc_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciParkSupWarningThresholdValueNc->Value));
         }

private: System::Void numericUpDownCRdciParkSupExtParkSupConfig_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_BYTE, C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_MASK, (uint8) System::Decimal::ToByte( numericUpDownCRdciParkSupExtParkSupConfig->Value));
         }

private: System::Void numericUpDownCRdciParkSupTolNoTempComp_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_MASK, (uint8) ((System::Decimal::ToByte( numericUpDownCRdciParkSupTolNoTempComp->Value) + 5) / 10));
         }

private: System::Void numericUpDownCRdciParkSupTolTempComp_ValueChanged(System::Object^  sender, System::EventArgs^  e)
         {
           NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_TOL_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_TEMP_COMP_MASK, (uint8) ((System::Decimal::ToByte( numericUpDownCRdciParkSupTolTempComp->Value) + 5) / 10));
         }
#endif
