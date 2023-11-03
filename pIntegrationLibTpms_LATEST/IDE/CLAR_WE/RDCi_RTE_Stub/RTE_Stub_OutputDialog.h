#ifndef __RTE_STUB_OUTPUT_DIALOG_H
#define __RTE_STUB_OUTPUT_DIALOG_H

  private: System::Void GetOutputDataTimer_Tick(System::Object^  sender, System::EventArgs^  e)
  {
    uint8   ucLoop;
	  uint8   Index;

    uint8   ucWarnVectorExt[cAnzRad], ucWarnBitOutInt[cAnzRad], ucWarnBitTonnageInt[cAnzRad], ucWarnBitAirmassInt[cAnzRad];
    uint8   ucSetLevel, ucResetLevel;
    uint8   ucPresVal;
    sint8   scTempVal;
    uint16  ushPalStatus;
    uint8   ucBattStatus;
    uint8   ucTransmTrigger;
    uint8   ucTransmCounter;
    uint8   ucPcold, ucPwarm, ucPist_t, ucPamb, ucPsollCold, ucPsollWarm, ucPsoll_t;
    sint8   scTcold, scTwarm, scTsollCold, scTist_t;
    uint16  ushMSoll;
    uint16  ushElapsedCoolingTime, ushTimeTicks;
    uint32  ulCoolingCaptTime;

    uint8   ucRefPres, ucLastPres;
    uint16  ushTimCnt, ushTimCountLatch;

    uint8   ucDbgByte;
    uint32  ulDbgDword;

    uint32 ulID;
    uint8  ucHistoryIndex;
    uint8  ucZomIndex;

    uint16 ushPTyreFL, ushPTyreFR, ushPTyreRL, ushPTyreRR;
    uint16 ushTTyreFL, ushTTyreFR, ushTTyreRL, ushTTyreRR;
    uint8  ucStTyreINFO, ucStTyreTPL, ucStTyreTFAI;

    uint8  ucTimerState;
    uint16 ushTimerCounter;

    uint8  ucStateSCC;
    uint16 ushSpeedVmaxTimeSCC, ushSpeedCcmThFaSCC, ushSpeedCcmThRaSCC;

    static uint8   ucDbgSync = 0;

    static uint8  ucFrDbgDscSuppMux = 255;
    static boolean bLogWithoutDataSource = FALSE;

    static uint16 ushCcClearLampTimer = 0;

    tNwMonitoringData tNwMonData;

    ImpTypeRecCcm_DISP_CC_BYPA_00                           tCC_BYPA_00;
    Rdci_TAR_P_TYR_FLH_Type                                 TAR_P_TYR_FLH;
    Rdci_TAR_P_TYR_FRH_Type                                 TAR_P_TYR_FRH;
    Rdci_TAR_P_TYR_RLH_Type                                 TAR_P_TYR_RLH;
    Rdci_TAR_P_TYR_RRH_Type                                 TAR_P_TYR_RRH;

    Rdci_AVL_P_TYR_FLH_Type                                 AVL_P_TYR_FLH;
    Rdci_AVL_P_TYR_FRH_Type                                 AVL_P_TYR_FRH;
    Rdci_AVL_P_TYR_RLH_Type                                 AVL_P_TYR_RLH;
    Rdci_AVL_P_TYR_RRH_Type                                 AVL_P_TYR_RRH;

    Rdci_AVL_TEMP_TYR_FLH_Type                              AVL_TEMP_TYR_FLH;
    Rdci_AVL_TEMP_TYR_FRH_Type                              AVL_TEMP_TYR_FRH;
    Rdci_AVL_TEMP_TYR_RLH_Type                              AVL_TEMP_TYR_RLH;
    Rdci_AVL_TEMP_TYR_RRH_Type                              AVL_TEMP_TYR_RRH;

    Rdci_ST_TYR_Type                                        tST_TYR;

	  Rdci_L_OL_TYP_TYR_Type                                  L_OL_TYP_TYR;
	  Rdci_QU_RDC_INIT_DISP_Type                              QU_RDC_INIT_DISP;
	  Rdci_ST_SLCTN_SUTR_AVLB_Type                            ST_SLCTN_SUTR_AVLB;
	  Rdci_ST_SLCTN_TYR_Type                                  ST_SLCTN_TYR;
	  Rdci_ST_SLCTN_WITR_AVLB_Type                            ST_SLCTN_WITR_AVLB;
	  Rdci_ST_TAR_P_LOCO_TPCT_Type                            ST_TAR_P_LOCO_TPCT;
	  Rdci_ST_TYR_SEA_TPCT_Type                               ST_TYR_SEA_TPCT;

	  Rdci_OP_IDR_MSGC_Type                                   OP_IDR_MSGC;

	  Rdci_ST_MAN_SLCTN_Type                                  ST_MAN_SLCTN;

	  Rdci_CAC_SUTR_TYP_TYR_Type                              CAC_SUTR_TYP_TYR;
	  Rdci_IDX_LCC_SUTR_TYP_TYR_Type                          IDX_LCC_SUTR_TYP_TYR;
	  Rdci_IDX_V_SUTR_TYP_TYR_Type                            IDX_V_SUTR_TYP_TYR;
	  Rdci_RAD_SUTR_TYP_TYR_Type                              RAD_SUTR_TYP_TYR;
	  Rdci_RELA_SIDE_SUTR_TYP_TYR_Type                        RELA_SIDE_SUTR_TYP_TYR;
	  Rdci_RFL_SUTR_TYP_TYR_Type                              RFL_SUTR_TYP_TYR;
	  Rdci_SEA_SUTR_TYP_TYR_Type                              SEA_SUTR_TYP_TYR;
	  Rdci_WID_SUTR_TYP_TYR_Type                              WID_SUTR_TYP_TYR;

	  Rdci_CAC_WITR_TYP_TYR_Type                              CAC_WITR_TYP_TYR;
	  Rdci_IDX_LCC_WITR_TYP_TYR_Type                          IDX_LCC_WITR_TYP_TYR;
	  Rdci_IDX_V_WITR_TYP_TYR_Type                            IDX_V_WITR_TYP_TYR;
	  Rdci_RAD_WITR_TYP_TYR_Type                              RAD_WITR_TYP_TYR;
	  Rdci_RELA_SIDE_WITR_TYP_TYR_Type                        RELA_SIDE_WITR_TYP_TYR;
	  Rdci_RFL_WITR_TYP_TYR_Type                              RFL_WITR_TYP_TYR;
	  Rdci_SEA_WITR_TYP_TYR_Type                              SEA_WITR_TYP_TYR;
	  Rdci_WID_WITR_TYP_TYR_Type                              WID_WITR_TYP_TYR;

	  Rdci_CAC_TYP_TYR_Type                                   CAC_TYP_TYR;
	  Rdci_IDX_LCC_TYP_TYR_Type                               IDX_LCC_TYP_TYR;
	  Rdci_IDX_V_TYP_TYR_Type                                 IDX_V_TYP_TYR;
	  Rdci_RAD_TYP_TYR_Type                                   RAD_TYP_TYR;
	  Rdci_RELA_SIDE_TYP_TYR_Type                             RELA_SIDE_TYP_TYR;
	  Rdci_RFL_TYP_TYR_Type                                   RFL_TYP_TYR;
	  Rdci_SEA_TYP_TYR_Type                                   SEA_TYP_TYR;
	  Rdci_WID_TYP_TYR_Type                                   WID_TYP_TYR;
	  Rdci_ST_TYR_OL_ID_Type			                            ST_TYR_OL_ID;

	  Rdci_ST_SLCTN_BAX_TYP_TYR_Type                          ST_SLCTN_BAX_TYP_TYR;
	  Rdci_CAC_BAX_TYP_TYR_Type                               CAC_BAX_TYP_TYR;
	  Rdci_IDX_LCC_BAX_TYP_TYR_Type                           IDX_LCC_BAX_TYP_TYR;
	  Rdci_IDX_V_BAX_TYP_TYR_Type                             IDX_V_BAX_TYP_TYR;
	  Rdci_RAD_BAX_TYP_TYR_Type                               RAD_BAX_TYP_TYR;
	  Rdci_RELA_SIDE_BAX_TYP_TYR_Type                         RELA_SIDE_BAX_TYP_TYR;
	  Rdci_RFL_BAX_TYP_TYR_Type                               RFL_BAX_TYP_TYR;
	  Rdci_SEA_BAX_TYP_TYR_Type                               SEA_BAX_TYP_TYR;
	  Rdci_WID_BAX_TYP_TYR_Type                               WID_BAX_TYP_TYR;

	  Rdci_CAC_FTAX_TYP_TYR_Type                              CAC_FTAX_TYP_TYR;
	  Rdci_IDX_LCC_FTAX_TYP_TYR_Type                          IDX_LCC_FTAX_TYP_TYR;
	  Rdci_IDX_V_FTAX_TYP_TYR_Type                            IDX_V_FTAX_TYP_TYR;
	  Rdci_RAD_FTAX_TYP_TYR_Type                              RAD_FTAX_TYP_TYR;
	  Rdci_RELA_SIDE_FTAX_TYP_TYR_Type                        RELA_SIDE_FTAX_TYP_TYR;
	  Rdci_RFL_FTAX_TYP_TYR_Type                              RFL_FTAX_TYP_TYR;
	  Rdci_SEA_FTAX_TYP_TYR_Type                              SEA_FTAX_TYP_TYR;
	  Rdci_WID_FTAX_TYP_TYR_Type                              WID_FTAX_TYP_TYR;

    Rdci_StatusWheelTypeChangeDetection_Type                ST_WT_CHG_DET;
    Rdci_StatusWheelTypeChangePosition_Type                 ST_WT_CHG_POS;

    Rdci_LastReceivedAmbientPressure_Type                   LastReceivedAmbientPressure;
    Rdci_MobilityLossThresholdValue_Type                    MobilityLossThresholdValue;
    Rdci_NotificationThresholdValueC_Type                   NotificationThresholdValueC;
    Rdci_NotificationThresholdValueNc_Type                  NotificationThresholdValueNc;
    Rdci_RDCSystemReferenceTemp_Type                        RDCSystemReferenceTemp;
    Rdci_PwfChange_Type                                     PwfChange;
    Rdci_RelRecommendedColdInflationPressureFrontAxle_Type  RelRecommendedColdInflationPressureFrontAxle;
    Rdci_RelRecommendedColdInflationPressureRearAxle_Type   RelRecommendedColdInflationPressureRearAxle;
    Rdci_TolNoTempComp_Type                                 TolNoTempComp;
    Rdci_TolTempComp_Type                                   TolTempComp;
    Rdci_WarningThresholdValueC_Type                        WarningThresholdValueC;
    Rdci_WarningThresholdValueNc_Type                       WarningThresholdValueNc;
    Rdci_ExtParkSupConfig_Type                              ExtParkSupConfig;

    Rdci_UHRZEIT_DATUM_Type                                 timeDate;

    String^ sLabelWheelPosition;
    String^ sLabelPackageId;
    String^ sLabelSupplierId;
    String^ sLabelTyreId;
    String^ sLabelTyrePressure;
    String^ sLabelTyreTemperature;
    String^ sLabelPALlookBackTime;
    String^ sLabelPALstatus;
    String^ sLabelBasicState;
    String^ sLabelBatteryInfo;
    String^ sLabelTransmissionTrigger;
    String^ sLabelTransmissionCounter;
    String^ sLabelPressureUnit;
    String^ sLabelTemperatureUnit;

    String^ sLabelNO_CC_BYPA_00_Start;
    String^ sLabelNO_CC_BYPA_00_Blink;

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

    GetRDCiOutputDataTAR_P_TYR_FLH( &TAR_P_TYR_FLH);
    GetRDCiOutputDataTAR_P_TYR_FRH( &TAR_P_TYR_FRH);
    GetRDCiOutputDataTAR_P_TYR_RLH( &TAR_P_TYR_RLH);
    GetRDCiOutputDataTAR_P_TYR_RRH( &TAR_P_TYR_RRH);

    if( TAR_P_TYR_FLH == cTyrePressureFuncIfaceNotAvailableValueITY)
    {
      labelTarPTyreFL->Text = "     ";
    }else if( TAR_P_TYR_FLH == cTyrePressureNotAvailableValueITY)
    {
      labelTarPTyreFL->Text = "-----";
    }else if( TAR_P_TYR_FLH == cTyrePressureInvalidValueITY)
    {
      labelTarPTyreFL->Text = "invalid";
    }else{
      labelTarPTyreFL->Text = System::String::Format("{0}{1}", TAR_P_TYR_FLH * 0.1, sLabelPressureUnit);
    }

    if( TAR_P_TYR_FRH == cTyrePressureFuncIfaceNotAvailableValueITY)
    {
      labelTarPTyreFR->Text = "     ";
    }else if( TAR_P_TYR_FRH == cTyrePressureNotAvailableValueITY)
    {
      labelTarPTyreFR->Text = "-----";
    }else if( TAR_P_TYR_FRH == cTyrePressureInvalidValueITY)
    {
      labelTarPTyreFR->Text = "invalid";
    }else{
      labelTarPTyreFR->Text = System::String::Format("{0}{1}", TAR_P_TYR_FRH * 0.1, sLabelPressureUnit);
    }

    if( TAR_P_TYR_RLH == cTyrePressureFuncIfaceNotAvailableValueITY)
    {
      labelTarPTyreRL->Text = "     ";
    }else if( TAR_P_TYR_RLH == cTyrePressureNotAvailableValueITY)
    {
      labelTarPTyreRL->Text = "-----";
    }else if( TAR_P_TYR_RLH == cTyrePressureInvalidValueITY)
    {
      labelTarPTyreRL->Text = "invalid";
    }else{
      labelTarPTyreRL->Text = System::String::Format("{0}{1}", TAR_P_TYR_RLH * 0.1, sLabelPressureUnit);
    }

    if( TAR_P_TYR_RRH == cTyrePressureFuncIfaceNotAvailableValueITY)
    {
      labelTarPTyreRR->Text = "     ";
    }else if( TAR_P_TYR_RRH == cTyrePressureNotAvailableValueITY)
    {
      labelTarPTyreRR->Text = "-----";
    }else if( TAR_P_TYR_RRH == cTyrePressureInvalidValueITY)
    {
      labelTarPTyreRR->Text = "invalid";
    }else{
      labelTarPTyreRR->Text = System::String::Format("{0}{1}", TAR_P_TYR_RRH * 0.1, sLabelPressureUnit);
    }

    GetRDCiOutputDataAVL_T_TYR_FLH( &AVL_TEMP_TYR_FLH);
    GetRDCiOutputDataAVL_T_TYR_FRH( &AVL_TEMP_TYR_FRH);
    GetRDCiOutputDataAVL_T_TYR_RLH( &AVL_TEMP_TYR_RLH);
    GetRDCiOutputDataAVL_T_TYR_RRH( &AVL_TEMP_TYR_RRH);

    if( AVL_TEMP_TYR_FLH == cTyreTemperatureNotAvailableValueITY)
    {
      labelAvlTTyreFL->Text = "-----";
    }else if( AVL_TEMP_TYR_FLH == cTyreTemperatureInvalidValueITY)
    {
      labelAvlTTyreFL->Text = "invalid";
    }else{
      labelAvlTTyreFL->Text = System::String::Format("{0}{1}", AVL_TEMP_TYR_FLH - 40, sLabelTemperatureUnit);
    }

    if( AVL_TEMP_TYR_FRH == cTyreTemperatureNotAvailableValueITY)
    {
      labelAvlTTyreFR->Text = "-----";
    }else if( AVL_TEMP_TYR_FRH == cTyreTemperatureInvalidValueITY)
    {
      labelAvlTTyreFR->Text = "invalid";
    }else{
      labelAvlTTyreFR->Text = System::String::Format("{0}{1}", AVL_TEMP_TYR_FRH - 40, sLabelTemperatureUnit);
    }

    if( AVL_TEMP_TYR_RLH == cTyreTemperatureNotAvailableValueITY)
    {
      labelAvlTTyreRL->Text = "-----";
    }else if( AVL_TEMP_TYR_RLH == cTyreTemperatureInvalidValueITY)
    {
      labelAvlTTyreRL->Text = "invalid";
    }else{
      labelAvlTTyreRL->Text = System::String::Format("{0}{1}", AVL_TEMP_TYR_RLH - 40, sLabelTemperatureUnit);
    }

    if( AVL_TEMP_TYR_RRH == cTyreTemperatureNotAvailableValueITY)
    {
      labelAvlTTyreRR->Text = "-----";
    }else if( AVL_TEMP_TYR_RRH == cTyreTemperatureInvalidValueITY)
    {
      labelAvlTTyreRR->Text = "invalid";
    }else{
      labelAvlTTyreRR->Text = System::String::Format("{0}{1}", AVL_TEMP_TYR_RRH - 40, sLabelTemperatureUnit);
    }

    GetRDCiOutputDataAVL_P_TYR_FLH( &AVL_P_TYR_FLH);
    GetRDCiOutputDataAVL_P_TYR_FRH( &AVL_P_TYR_FRH);
    GetRDCiOutputDataAVL_P_TYR_RLH( &AVL_P_TYR_RLH);
    GetRDCiOutputDataAVL_P_TYR_RRH( &AVL_P_TYR_RRH);

    if( AVL_P_TYR_FLH == cTyrePressureNotPresentValueITY)
    {
      labelAvlPTyreFL->Text = "     ";
    }else if( AVL_P_TYR_FLH == cTyrePressureNotAvailableValueITY)
    {
      labelAvlPTyreFL->Text = "-----";
    }else if( AVL_P_TYR_FLH == cTyrePressureInvalidValueITY)
    {
      labelAvlPTyreFL->Text = "invalid";
    }else{
      labelAvlPTyreFL->Text = System::String::Format("{0}{1}", AVL_P_TYR_FLH * 0.1, sLabelPressureUnit);
    }

    if( AVL_P_TYR_FRH == cTyrePressureNotPresentValueITY)
    {
      labelAvlPTyreFR->Text = "     ";
    }else if( AVL_P_TYR_FRH == cTyrePressureNotAvailableValueITY)
    {
      labelAvlPTyreFR->Text = "-----";
    }else if( AVL_P_TYR_FRH == cTyrePressureInvalidValueITY)
    {
      labelAvlPTyreFR->Text = "invalid";
    }else{
      labelAvlPTyreFR->Text = System::String::Format("{0}{1}", AVL_P_TYR_FRH * 0.1, sLabelPressureUnit);
    }

    if( AVL_P_TYR_RLH == cTyrePressureNotPresentValueITY)
    {
      labelAvlPTyreRL->Text = "     ";
    }else if( AVL_P_TYR_RLH == cTyrePressureNotAvailableValueITY)
    {
      labelAvlPTyreRL->Text = "-----";
    }else if( AVL_P_TYR_RLH == cTyrePressureInvalidValueITY)
    {
      labelAvlPTyreRL->Text = "invalid";
    }else{
      labelAvlPTyreRL->Text = System::String::Format("{0}{1}", AVL_P_TYR_RLH * 0.1, sLabelPressureUnit);
    }

    if( AVL_P_TYR_RRH == cTyrePressureNotPresentValueITY)
    {
      labelAvlPTyreRR->Text = "     ";
    }else if( AVL_P_TYR_RRH == cTyrePressureNotAvailableValueITY)
    {
      labelAvlPTyreRR->Text = "-----";
    }else if( AVL_P_TYR_RRH == cTyrePressureInvalidValueITY)
    {
      labelAvlPTyreRR->Text = "invalid";
    }else{
      labelAvlPTyreRR->Text = System::String::Format("{0}{1}", AVL_P_TYR_RRH * 0.1, sLabelPressureUnit);
    }

    timeDate = GETtTimeDateEE( Rte_Inst_CtApHufTpmsSWC);

    if( Stub_GetCcmData( &tCC_BYPA_00) != 0xff)
    {

      if( tCC_BYPA_00.NO_CC_BYPA_00 == 0x0150)
      {

        if( tCC_BYPA_00.ST_CC_BYPA_00     == cCcStartStopState_Start) { sLabelNO_CC_BYPA_00_Start = "Start";       }else if( tCC_BYPA_00.ST_CC_BYPA_00     == cCcStartStopState_Stop) { sLabelNO_CC_BYPA_00_Start = "Stop";               }else{ sLabelNO_CC_BYPA_00_Start = "Invalid"; }
        if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Off)       { sLabelNO_CC_BYPA_00_Blink = "no blinking"; }else if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Slow) { sLabelNO_CC_BYPA_00_Blink = "blinking with 1 Hz"; }else if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Fast) { sLabelNO_CC_BYPA_00_Blink = "blinking with 3 Hz"; }else{ sLabelNO_CC_BYPA_00_Blink = "Invalid"; }

        textBoxNO_CC_BYPA_00->AppendText( System::String::Format( "fKL:\t{0:00}:{1:00}:{2:00} - 0x{3,4:X4} - {4} - {5}\n", timeDate.DISP_HR, timeDate.DISP_MN, timeDate.DISP_SEC, tCC_BYPA_00.NO_CC_BYPA_00, sLabelNO_CC_BYPA_00_Start, sLabelNO_CC_BYPA_00_Blink));
      }

      else if( tCC_BYPA_00.NO_CC_BYPA_00 != cCcInvalid)
      {

        if( tCC_BYPA_00.ST_CC_BYPA_00     == cCcStartStopState_Start) { sLabelNO_CC_BYPA_00_Start = "Start";       }else if( tCC_BYPA_00.ST_CC_BYPA_00     == cCcStartStopState_Stop) { sLabelNO_CC_BYPA_00_Start = "Stop";               }else{ sLabelNO_CC_BYPA_00_Start = "Invalid"; }
        if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Off)       { sLabelNO_CC_BYPA_00_Blink = "no blinking"; }else if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Slow) { sLabelNO_CC_BYPA_00_Blink = "blinking with 1 Hz"; }else if( tCC_BYPA_00.ST_IDC_CC_BYPA_00 == cCcBlinkState_Fast) { sLabelNO_CC_BYPA_00_Blink = "blinking with 3 Hz"; }else{ sLabelNO_CC_BYPA_00_Blink = "Invalid"; }

        textBoxNO_CC_BYPA_00->AppendText( System::String::Format( "vKL:\t{0:00}:{1:00}:{2:00} - 0x{3,4:X4} - {4} - {5}\n", timeDate.DISP_HR, timeDate.DISP_MN, timeDate.DISP_SEC, tCC_BYPA_00.NO_CC_BYPA_00, sLabelNO_CC_BYPA_00_Start, sLabelNO_CC_BYPA_00_Blink));
      }

      else
      {

      }

      ushCcClearLampTimer = 10000 / System::Decimal::ToInt32(OutputTimerInterval->Value);
    }else{

    }

    GetRDCiOutputDataST_TYR( &tST_TYR);
    labelST_TYR_INFO->Text = System::String::Format("{0,2:X2}", tST_TYR.QU_FN_TYR_INFO);
    labelST_TYR_TPL->Text = System::String::Format("{0,2:X2}", tST_TYR.QU_TPL);
    labelST_TYR_TFAI->Text = System::String::Format("{0,2:X2}", tST_TYR.QU_TFAI);

    if(GETTyreSelectionActiveEE( Rte_Inst_CtApHufTpmsSWC) == 1)
    {
      checkBoxFgrInit->Checked = TRUE;
    }
    else
    {
      checkBoxFgrInit->Checked = FALSE;
    }

    if(GETTyreSelectionBckgrdEE( Rte_Inst_CtApHufTpmsSWC) == 1)
    {
      checkBoxBgrInit->Checked = TRUE;
    }
    else
    {
      checkBoxBgrInit->Checked = FALSE;
    }
    switch (GETucCalibrationRootCauseEE( Rte_Inst_CtApHufTpmsSWC))
    {
      case cCalError:           labelCalRootCause->Text = "Cal failed";     break;
      case cCalOtherTyre:       labelCalRootCause->Text = "Cal other Tyre"; break;
      case cCalByHMI:           labelCalRootCause->Text = "Cal by HMI";     break;
      case cCalByDiag:          labelCalRootCause->Text = "Cal by Diag";    break;
      case cCalVirgin:          labelCalRootCause->Text = "Cal virgin";     break;
      case cCalFilDetRe0:       labelCalRootCause->Text = "Cal Fil Det 0";  break;
      case cCalFilDetRe1:       labelCalRootCause->Text = "Cal Fil Det 1";  break;
      case cCalFilDetRe2:       labelCalRootCause->Text = "Cal Fil Det 2";  break;
      case cCalFilDetRe3:       labelCalRootCause->Text = "Cal Fil Det 3";  break;
      case cCalNvmError:        labelCalRootCause->Text = "Cal Nvm Error";  break;
      case cCalRidNoStatusbar:  labelCalRootCause->Text = "Cal Rid no SBR"; break;
      case cCalRidStatusbar:    labelCalRootCause->Text = "Cal Rid w SBR";  break;
      case cCalSeaAdj:          labelCalRootCause->Text = "Cal Seas Adj";   break;
      case cCalRunning:         labelCalRootCause->Text = "Cal running";    break;
      case cCalInvalid:         labelCalRootCause->Text = "Cal Invalid";    break;
      default:                  labelCalRootCause->Text = "Error: not defined";    break;
    }

    Index = GETSelectedSuTyreIndexEE( Rte_Inst_CtApHufTpmsSWC);

	if(Index != CINIT_DISP_INVALID)
	{
		GetRDCiOutputDataCAC_SUTR(&CAC_SUTR_TYP_TYR);
		SUTR_KarkasseVal -> Text = System::String::Format("{0}", CAC_SUTR_TYP_TYR);
		GetRDCiOutputDataIDX_LCC_SUTR(&IDX_LCC_SUTR_TYP_TYR);
		SUTR_TragVal -> Text = System::String::Format("{0}", IDX_LCC_SUTR_TYP_TYR);
		GetRDCiOutputDataIDX_V_SUTR(&IDX_V_SUTR_TYP_TYR);
		SUTR_VIndexVal -> Text = System::String::Format("{0}", IDX_V_SUTR_TYP_TYR);
		GetRDCiOutputDataRAD_SUTR(&RAD_SUTR_TYP_TYR);
		SUTR_DurchmVal -> Text = System::String::Format("{0}", RAD_SUTR_TYP_TYR);
		GetRDCiOutputDataRELA_SIDE_SUTR(&RELA_SIDE_SUTR_TYP_TYR);
		SUTR_QuerVal-> Text = System::String::Format("{0}", RELA_SIDE_SUTR_TYP_TYR);
		GetRDCiOutputDataRFL_SUTR(&RFL_SUTR_TYP_TYR);
		SUTR_TypVal-> Text = System::String::Format("{0}", RFL_SUTR_TYP_TYR);
		GetRDCiOutputDataSEA_SUTR(&SEA_SUTR_TYP_TYR);
		SUTR_SaisonVal-> Text = System::String::Format("{0}", SEA_SUTR_TYP_TYR);
		GetRDCiOutputDataWID_SUTR(&WID_SUTR_TYP_TYR);
		SUTR_ReifenbreiteVal-> Text = System::String::Format("{0}", WID_SUTR_TYP_TYR);
	}

  Index = GETSelectedWiTyreIndexEE(Rte_Inst_CtApHufTpmsSWC);

	if(Index != CINIT_DISP_INVALID)
	{
		GetRDCiOutputDataCAC_WITR(&CAC_WITR_TYP_TYR);
    WITR_KarkasseVal->Text = System::String::Format("{0}",  CAC_WITR_TYP_TYR);
		GetRDCiOutputDataIDX_LCC_WITR(&IDX_LCC_WITR_TYP_TYR);
		WITR_TragVal -> Text = System::String::Format("{0}", IDX_LCC_WITR_TYP_TYR);
		GetRDCiOutputDataIDX_V_WITR(&IDX_V_WITR_TYP_TYR);
		WITR_VIndexVal -> Text = System::String::Format("{0}", IDX_V_WITR_TYP_TYR);
		GetRDCiOutputDataRAD_WITR(&RAD_WITR_TYP_TYR);
		WITR_DurchmVal -> Text = System::String::Format("{0}", RAD_WITR_TYP_TYR);
		GetRDCiOutputDataRELA_SIDE_WITR(&RELA_SIDE_WITR_TYP_TYR);
		WITR_QuerVal-> Text = System::String::Format("{0}", RELA_SIDE_WITR_TYP_TYR);
		GetRDCiOutputDataRFL_WITR(&RFL_WITR_TYP_TYR);
		WITR_TypVal-> Text = System::String::Format("{0}", RFL_WITR_TYP_TYR);
		GetRDCiOutputDataSEA_WITR(&SEA_WITR_TYP_TYR);
		WITR_SaisonVal-> Text = System::String::Format("{0}", SEA_WITR_TYP_TYR);
		GetRDCiOutputDataWID_WITR(&WID_WITR_TYP_TYR);
		WITR_ReifenbreiteVal-> Text = System::String::Format("{0}", WID_WITR_TYP_TYR);
	}

	GetRDCiOutputDataST_SLCTN_BAX_TYP_TYR(&ST_SLCTN_BAX_TYP_TYR);
	DisplayConfVal -> Text = System::String::Format("{0}", ST_SLCTN_BAX_TYP_TYR);

	Index = GETSelectedTyreIndexEE( Rte_Inst_CtApHufTpmsSWC);

	if(Index != CINIT_DISP_INVALID)
	{
		GetRDCiOutputDataCAC_BAX(&CAC_BAX_TYP_TYR);
		RATR_KarkasseVal -> Text = System::String::Format("{0}", CAC_BAX_TYP_TYR);
		GetRDCiOutputDataIDX_LCC_BAX(&IDX_LCC_BAX_TYP_TYR);
		RATR_TragVal -> Text = System::String::Format("{0}", IDX_LCC_BAX_TYP_TYR);
		GetRDCiOutputDataIDX_V_BAX(&IDX_V_BAX_TYP_TYR);
		RATR_VIndexVal -> Text = System::String::Format("{0}", IDX_V_BAX_TYP_TYR);
		GetRDCiOutputDataRAD_BAX(&RAD_BAX_TYP_TYR);
		RATR_DurchmVal -> Text = System::String::Format("{0}", RAD_BAX_TYP_TYR);
		GetRDCiOutputDataRELA_SIDE_BAX(&RELA_SIDE_BAX_TYP_TYR);
		RATR_QuerVal-> Text = System::String::Format("{0}", RELA_SIDE_BAX_TYP_TYR);
		GetRDCiOutputDataRFL_BAX(&RFL_BAX_TYP_TYR);
		RATR_TypVal-> Text = System::String::Format("{0}", RFL_BAX_TYP_TYR);
		GetRDCiOutputDataSEA_BAX(&SEA_BAX_TYP_TYR);
		RATR_SaisonVal-> Text = System::String::Format("{0}", SEA_BAX_TYP_TYR);
		GetRDCiOutputDataWID_BAX(&WID_BAX_TYP_TYR);
		RATR_ReifenbreiteVal-> Text = System::String::Format("{0}", WID_BAX_TYP_TYR);
	}

  if(Index != CINIT_DISP_INVALID)
	{
		GetRDCiOutputDataCAC_FTAX(&CAC_FTAX_TYP_TYR);
		FATR_KarkasseVal -> Text = System::String::Format("{0}", CAC_FTAX_TYP_TYR);
		GetRDCiOutputDataIDX_LCC_FTAX(&IDX_LCC_FTAX_TYP_TYR);
		FATR_TragVal -> Text = System::String::Format("{0}", IDX_LCC_FTAX_TYP_TYR);
		GetRDCiOutputDataIDX_V_FTAX(&IDX_V_FTAX_TYP_TYR);
		FATR_VIndexVal -> Text = System::String::Format("{0}", IDX_V_FTAX_TYP_TYR);
		GetRDCiOutputDataRAD_FTAX(&RAD_FTAX_TYP_TYR);
		FATR_DurchmVal -> Text = System::String::Format("{0}", RAD_FTAX_TYP_TYR);
		GetRDCiOutputDataRELA_SIDE_FTAX(&RELA_SIDE_FTAX_TYP_TYR);
		FATR_QuerVal-> Text = System::String::Format("{0}", RELA_SIDE_FTAX_TYP_TYR);
		GetRDCiOutputDataRFL_FTAX(&RFL_FTAX_TYP_TYR);
		FATR_TypVal-> Text = System::String::Format("{0}", RFL_FTAX_TYP_TYR);
		GetRDCiOutputDataSEA_FTAX(&SEA_FTAX_TYP_TYR);
		FATR_SaisonVal-> Text = System::String::Format("{0}", SEA_FTAX_TYP_TYR);
		GetRDCiOutputDataWID_FTAX(&WID_FTAX_TYP_TYR);
		FATR_ReifenbreiteVal-> Text = System::String::Format("{0}", WID_FTAX_TYP_TYR);
	}

	GetRDCiOutputDataOL_ID_TYTR(&ST_TYR_OL_ID);
	TyreList_IdVal -> Text = System::String::Format("{0}", ST_TYR_OL_ID);
	GetRDCiOutputDataCAC_TYTR(&CAC_TYP_TYR);
	TyreList_KarkasseVal -> Text = System::String::Format("{0}", CAC_TYP_TYR);
	GetRDCiOutputDataIDX_LCC_TYTR(&IDX_LCC_TYP_TYR);
	TyreList_TragVal -> Text = System::String::Format("{0}", IDX_LCC_TYP_TYR);
	GetRDCiOutputDataIDX_V_TYTR(&IDX_V_TYP_TYR);
	TyreList_VIndexVal -> Text = System::String::Format("{0}", IDX_V_TYP_TYR);
	GetRDCiOutputDataRAD_TYTR(&RAD_TYP_TYR);
	TyreList_DurchmVal -> Text = System::String::Format("{0}", RAD_TYP_TYR);
	GetRDCiOutputDataRELA_SIDE_TYTR(&RELA_SIDE_TYP_TYR);
	TyreList_QuerVal-> Text = System::String::Format("{0}", RELA_SIDE_TYP_TYR);
	GetRDCiOutputDataRFL_TYTR(&RFL_TYP_TYR);
	TyreList_TypVal-> Text = System::String::Format("{0}", RFL_TYP_TYR);
	GetRDCiOutputDataSEA_TYTR(&SEA_TYP_TYR);
	TyreList_SaisonVal-> Text = System::String::Format("{0}", SEA_TYP_TYR);
	GetRDCiOutputDataWID_TYTR(&WID_TYP_TYR);
	TyreList_ReifenbreiteVal-> Text = System::String::Format("{0}", WID_TYP_TYR);

	GetRDCiOutputDataLOL_TYP_TYR(&L_OL_TYP_TYR);
	STTR2_LengthOfTyreListVal -> Text = System::String::Format("{0}", L_OL_TYP_TYR);

  GetRDCiOutputDataQU_RDC_INIT_DISP(&QU_RDC_INIT_DISP);
	STTR2_InitDisplayVal -> Text = System::String::Format("{0}", QU_RDC_INIT_DISP);

  if(QU_RDC_INIT_DISP == QU_RDC_INIT_DISP_InitialisierungAbgeschlossen)
  {
    ProgressBarLearnLocate->Value = ProgressBarLearnLocate->Maximum;
    labelInitialisierungsbalken->Text = "Init abgeschlossen";
  }
  else if(QU_RDC_INIT_DISP == QU_RDC_INIT_DISP_KeineAnzeigeDesInitialierungsbalkens)
  {
    ProgressBarLearnLocate->Value = ProgressBarLearnLocate->Minimum;
    ProgressBarLearnLocate->Enabled = false;
    labelInitialisierungsbalken->Text = "Keine Anzeige des Init-Balkens";
  }
  else if(QU_RDC_INIT_DISP == QU_RDC_INIT_DISP_SignalUngueltig)
  {
    labelInitialisierungsbalken->Text = "UNGÜLTIG!";
  }
  else
  {
    ProgressBarLearnLocate->Enabled = true;
    ProgressBarLearnLocate->Value = QU_RDC_INIT_DISP;
    labelInitialisierungsbalken->Text = System::String::Format("{0}%", QU_RDC_INIT_DISP);
  }

	GetRDCiOutputDataST_SLCTN_SUTR_AVLB(&ST_SLCTN_SUTR_AVLB);
	STTR2_SummerTyreIndexVal -> Text = System::String::Format("{0}", ST_SLCTN_SUTR_AVLB);
	GetRDCiOutputDataST_SLCTN_WITR_AVLB(&ST_SLCTN_WITR_AVLB);
	STTR2_WinterTyreIndexVal -> Text = System::String::Format("{0}", ST_SLCTN_WITR_AVLB);
	GetRDCiOutputDataOP_IDR_MSGC(&OP_IDR_MSGC);
  STTR2_IdrMessagec -> Text = System::String::Format("{0}", OP_IDR_MSGC);
  GetRDCiOutputDataST_SLCTN_TYR(&ST_SLCTN_TYR);
  GetRDCiOutputDataST_MAN_SLCTN(&ST_MAN_SLCTN);
  STTYR2_StManSlctn -> Text = System::String::Format("{0}", ST_MAN_SLCTN);

	GetRDCiOutputDataST_TAR_P_LOCO_TPCT(&ST_TAR_P_LOCO_TPCT);
	STTR2_SelLoadStateVal -> Text = System::String::Format("{0}", ST_TAR_P_LOCO_TPCT);
	GetRDCiOutputDataST_TYR_SEA_TPCT(&ST_TYR_SEA_TPCT);
	STTR2_SelSeasonVal -> Text = System::String::Format("{0}", ST_TYR_SEA_TPCT);
  GetRDCiOutputDataStatusWheelTypeChangeDetection(&ST_WT_CHG_DET);
  STWTC_DetectionVal -> Text = System::String::Format("{0}", ST_WT_CHG_DET);

  GetRDCiOutputDataStatusWheelTypeChangePosition(&ST_WT_CHG_POS);
  STWTC_PositionVal -> Text = System::String::Format("{0}", ST_WT_CHG_POS);

  GetRDCiOutputDataLastReceivedAmbientPressure( &LastReceivedAmbientPressure);
  labelLastReceivedAmbientPressureValue->Text = System::String::Format("{0}", (LastReceivedAmbientPressure * 2 + 600));
  GetRDCiOutputDataMobilityLossThresholdValue( &MobilityLossThresholdValue);
  labelMobilityLossThresholdValueValue->Text = System::String::Format("{0}", MobilityLossThresholdValue);
  GetRDCiOutputDataNotificationThresholdValueC( &NotificationThresholdValueC);
  labelNotificationThresholdValueCValue->Text = System::String::Format("{0}", NotificationThresholdValueC);
  GetRDCiOutputDataNotificationThresholdValueNc( &NotificationThresholdValueNc);
  labelNotificationThresholdValueNcValue->Text = System::String::Format("{0}", NotificationThresholdValueNc);
  GetRDCiOutputDataRDCSystemReferenceTemp( &RDCSystemReferenceTemp);
  labelRDCSystemReferenceTempValue->Text = System::String::Format("{0}", (RDCSystemReferenceTemp - 50));
  GetRDCiOutputDataPwfChange( &PwfChange);
  labelPwfChangeValue->Text = System::String::Format("{0}", PwfChange);
  GetRDCiOutputDataRelRecommendedColdInflationPressureFrontAxle( &RelRecommendedColdInflationPressureFrontAxle);
  labelRelRecommendedColdInflationPressureFrontAxleValue->Text = System::String::Format("{0}", (RelRecommendedColdInflationPressureFrontAxle * 100));
  GetRDCiOutputDataRelRecommendedColdInflationPressureRearAxle( &RelRecommendedColdInflationPressureRearAxle);
  labelRelRecommendedColdInflationPressureRearAxleValue->Text = System::String::Format("{0}", (RelRecommendedColdInflationPressureRearAxle * 100));
  GetRDCiOutputDataTolNoTempComp( &TolNoTempComp);
  labelTolNoTempCompValue->Text = System::String::Format("{0}", (TolNoTempComp * 10));
  GetRDCiOutputDataTolTempComp( &TolTempComp);
  labelTolTempCompValue->Text = System::String::Format("{0}", (TolTempComp * 10));
  GetRDCiOutputDataWarningThresholdValueC( &WarningThresholdValueC);
  labelWarningThresholdValueCValue->Text = System::String::Format("{0}", WarningThresholdValueC);
  GetRDCiOutputDataWarningThresholdValueNc( &WarningThresholdValueNc);
  labelWarningThresholdValueNcValue->Text = System::String::Format("{0}", WarningThresholdValueNc);
  GetRDCiOutputDataExtParkSupConfig( &ExtParkSupConfig);
  labelExtParkSupConfigValue->Text = System::String::Format("{0}", ExtParkSupConfig);

  GetSpeedCcmValSCC_debug( &ucStateSCC, &ushSpeedVmaxTimeSCC, &ushSpeedCcmThFaSCC, &ushSpeedCcmThRaSCC);
  labelSpeedCcmStatusbyteWert->Text = System::String::Format("0x{0:X2}", ucStateSCC);
  if( ushSpeedVmaxTimeSCC == 0xffffu) { labelVmaxTimerWert->Text    = "- -"; }else{ labelVmaxTimerWert->Text    = System::String::Format("{0}", (ushSpeedVmaxTimeSCC / 10)); }
  if( ushSpeedCcmThFaSCC  == 0)       { labelPressureThFaWert->Text = "- -"; }else{ labelPressureThFaWert->Text = System::String::Format("{0}", ushSpeedCcmThFaSCC);         }
  if( ushSpeedCcmThRaSCC  == 0)       { labelPressureThRaWert->Text = "- -"; }else{ labelPressureThRaWert->Text = System::String::Format("{0}", ushSpeedCcmThRaSCC);         }

    for ( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
    {

      switch ( ucGetWPOfColWAL( ucLoop))
      {
        case cRadPosVL:
          sLabelWheelPosition = "front left";
        break;

        case cRadPosVR:
          sLabelWheelPosition = "front right";
        break;

        case cRadPosHL:
          sLabelWheelPosition = "rear left";
        break;

        case cRadPosHR:
          sLabelWheelPosition = "rear right";
        break;

        case cRadPosUndef:
          sLabelWheelPosition = "undefined";
        break;

        default:
          sLabelWheelPosition = "invalid";
        break;
      }

      switch ( ucGetRePckgIdDM( ucLoop))
      {
        case cTelTypeAK35def:
          sLabelPackageId = "AK";
        break;

        case cTelTypeAK35defLMA:
          sLabelPackageId = "AK L-Bit";
        break;

        case cTelTypeBeruLong:
          sLabelPackageId = "Beru Long";
        break;

        case cTelTypeBeruMed:
          sLabelPackageId = "Beru Med";
        break;

        case cTelTypeG4Standard:
          sLabelPackageId = "G4 Std";
        break;

        case cTelTypeSELPAL:
          sLabelPackageId = "PAL";
        break;

        case cTelTypeSELPAL1:
          sLabelPackageId = "PAL L-Bit";
        break;

        case cTelTypeContiFP:
          sLabelPackageId = "LOC SYNC";
        break;

        case cInvalidTelType:
          sLabelPackageId = "invalid";
        break;

        default:
          sLabelPackageId = "unknown";
        break;
      }

      switch ( ucGetReSuppIdDM( ucLoop))
      {
        case ( cSupplCodeHuf):
          sLabelSupplierId = "Huf";
        break;

        case ( cSupplCodeConti):
          sLabelSupplierId = "Conti";
        break;

        case ( cSupplCodeSchrader):
          sLabelSupplierId = "Schrader";
        break;

        case cInvalidREsuppId:
          sLabelSupplierId = "invalid";
        break;

        default:
          sLabelSupplierId = "unknown";
        break;
      }

      if( ulGetReIdDM( ucLoop) == cInvalidREid)
      {
        sLabelTyreId = "invalid";
      }else{
        sLabelTyreId = System::String::Format("{0}", ulGetReIdDM( ucLoop));
      }

      if( ucGetRePressureRelDM( ucLoop) == cInvalidREpressure)
      {
        sLabelTyrePressure = "invalid";
      }else{
        sLabelTyrePressure = System::String::Format("{0}bar", ucGetRePressureRelDM( ucLoop) * 0.025);
      }

      if( scGetReTemperatureCentDM( ucLoop) == cInvalidREtemperature)
      {
        sLabelTyreTemperature = "invalid";
      }else{
        sLabelTyreTemperature = System::String::Format("{0}°C", scGetReTemperatureCentDM( ucLoop));
      }

      if( ucGetRePalLookBackTimeDM( ucLoop) == cInvalidRePalLookBackTime)
      {
        sLabelPALlookBackTime = "invalid";
      }else{
        sLabelPALlookBackTime = System::String::Format("{0}ms", ucGetRePalLookBackTimeDM( ucLoop));
      }

      if( ushGetRePalStatusDM( ucLoop) == cInvalidRePalStatus)
      {
        sLabelPALstatus = "invalid";
        sLabelBasicState = "";
        sLabelBatteryInfo = "";
        sLabelTransmissionTrigger = "";
        sLabelTransmissionCounter = "";
      }
      else
      {
        sLabelPALstatus = System::String::Format("{0,4:X4}", ushGetRePalStatusDM( ucLoop));

        ushPalStatus = ushGetRePalStatusDM( ucLoop);
        switch ((ushPalStatus >> 13) & 0x7u)
        {
          case cREOff:
          sLabelBasicState = "Off";
          break;
          case cREStationary:
          sLabelBasicState = "Stationary";
          break;
          case cLearnWMotion:
          sLabelBasicState = "Lrn/w motion";
          break;
          case cLearnWoMotion:
          sLabelBasicState = "Lrn/wo motion";
          break;
          case cNormalDriveWMotion:
          sLabelBasicState = "Drv/w motion";
          break;
          case cNormalDriveWoMotion:
          sLabelBasicState = "Drv/wo motion";
          break;

          case 0:
          case 7:
          default:
          sLabelBasicState = "??";
          break;
        }

        ucBattStatus = ucGetReBatteryLevelDM( ucLoop);
        if(ucBattStatus == 0xff)
        {
          sLabelBatteryInfo = "??";
        }
        else
        {
          sLabelBatteryInfo = System::String::Format("{0}%", ucBattStatus);
        }

        ucTransmTrigger = (ushPalStatus >> 6) & 0x3u;
        switch (ucTransmTrigger)
        {
          case 0:
          default:
          sLabelTransmissionTrigger = "??";
          break;
          case 1:
          sLabelTransmissionTrigger = "Delta-P";
          break;
          case 2:
          sLabelTransmissionTrigger = "LF";
          break;
          case 3:
          sLabelTransmissionTrigger = "Scheduled";
        }

        ucTransmCounter = (ushPalStatus >> 8) & 0x1f;
        sLabelTransmissionCounter = System::String::Format("{0}", ucTransmCounter);
      }

      ulID = ulGetReIdDM(ucLoop) + ((uint32)ucGetReSuppIdDM(ucLoop) << 28);
      ucHistoryIndex = ucGetColOfID(&ulID);
      switch (ucHistoryIndex)
      {
        case 0:
        labelWheelPositionSlot0->Text = sLabelWheelPosition;
        labelPackageIdSlot0->Text = sLabelPackageId;
        labelSupplierIdSlot0->Text = sLabelSupplierId;
        labelTyreIdSlot0->Text = sLabelTyreId;
        labelTyrePressureSlot0->Text = sLabelTyrePressure;
        labelTyreTemperatureSlot0->Text = sLabelTyreTemperature;
        labelPALlookBackTimeSlot0->Text = sLabelPALlookBackTime;
        labelPALstatusSlot0->Text = sLabelPALstatus;
        labelBasicState_0->Text = sLabelBasicState;
        labelBatteryInfo_0->Text = sLabelBatteryInfo;
        labelTransmissionTrigger_0->Text = sLabelTransmissionTrigger;
        labelTransmissionCounter_0->Text = sLabelTransmissionCounter;
        break;

        case 1:
        labelWheelPositionSlot1->Text = sLabelWheelPosition;
        labelPackageIdSlot1->Text = sLabelPackageId;
        labelSupplierIdSlot1->Text = sLabelSupplierId;
        labelTyreIdSlot1->Text = sLabelTyreId;
        labelTyrePressureSlot1->Text = sLabelTyrePressure;
        labelTyreTemperatureSlot1->Text = sLabelTyreTemperature;
        labelPALlookBackTimeSlot1->Text = sLabelPALlookBackTime;
        labelPALstatusSlot1->Text = sLabelPALstatus;
        labelBasicState_1->Text = sLabelBasicState;
        labelBatteryInfo_1->Text = sLabelBatteryInfo;
        labelTransmissionTrigger_1->Text = sLabelTransmissionTrigger;
        labelTransmissionCounter_1->Text = sLabelTransmissionCounter;
        break;

        case 2:
        labelWheelPositionSlot2->Text = sLabelWheelPosition;
        labelPackageIdSlot2->Text = sLabelPackageId;
        labelSupplierIdSlot2->Text = sLabelSupplierId;
        labelTyreIdSlot2->Text = sLabelTyreId;
        labelTyrePressureSlot2->Text = sLabelTyrePressure;
        labelTyreTemperatureSlot2->Text = sLabelTyreTemperature;
        labelPALlookBackTimeSlot2->Text = sLabelPALlookBackTime;
        labelPALstatusSlot2->Text = sLabelPALstatus;
        labelBasicState_2->Text = sLabelBasicState;
        labelBatteryInfo_2->Text = sLabelBatteryInfo;
        labelTransmissionTrigger_2->Text = sLabelTransmissionTrigger;
        labelTransmissionCounter_2->Text = sLabelTransmissionCounter;
        break;

        case 3:
        labelWheelPositionSlot3->Text = sLabelWheelPosition;
        labelPackageIdSlot3->Text = sLabelPackageId;
        labelSupplierIdSlot3->Text = sLabelSupplierId;
        labelTyreIdSlot3->Text = sLabelTyreId;
        labelTyrePressureSlot3->Text = sLabelTyrePressure;
        labelTyreTemperatureSlot3->Text = sLabelTyreTemperature;
        labelPALlookBackTimeSlot3->Text = sLabelPALlookBackTime;
        labelPALstatusSlot3->Text = sLabelPALstatus;
        labelBasicState_3->Text = sLabelBasicState;
        labelBatteryInfo_3->Text = sLabelBatteryInfo;
        labelTransmissionTrigger_3->Text = sLabelTransmissionTrigger;
        labelTransmissionCounter_3->Text = sLabelTransmissionCounter;
        break;

      }
    }

    labelTimeRemaining->Text = System::String::Format("ZO Timeout: {0}", ucGetWATOTimeWAL() * 5);
    labelLearnTime->Text = System::String::Format("Learn time: {0}", ucGetLEARNTimeWAL() * 5);
    labelMinDistance->Text = System::String::Format("Dist: {0}", ucGetAllocMinDeltaValueFPA());

    if(bAllocationIsActive( Rte_Inst_CtApHufTpmsSWC) == true)
    {
      labelLearningNotActive->Text = "Lern/Loc aktiv";
      labelLearningNotActive->BackColor = System::Drawing::Color::FromArgb(0,255,0);
      labelLernLocActiveReason->Text = "";
    }
    else
    {
      labelLearningNotActive->Text = "Lern/Loc gestoppt";
      labelLearningNotActive->BackColor = System::Drawing::Color::FromArgb(255,0,0);

      if(ucGetStatusConditionVehicleFZZ() != ST_CON_VEH_Fahren)
      { labelLernLocActiveReason->Text = "Zustand ist nicht 'Fahren'.";         }

      else if(bGetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT) == TRUE)
      { labelLernLocActiveReason->Text = "Fahrzeug faehrt rueckwaerts.";           }

      else if(bGetBandmodeBM() == TRUE)
      { labelLernLocActiveReason->Text = "Bandmode aktiv.";                     }

      else if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
      { labelLernLocActiveReason->Text = "Zuordnungstimeout erreicht.";         }

      else if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_LERNT) == FALSE)
      { labelLernLocActiveReason->Text = "Geschwindigkeit kleiner 20km/h.";     }

      else if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
      { labelLernLocActiveReason->Text = "Zuordnung abgeschlossen oder short park.";            }

      else if(bGetBitBetriebszustandBZ(cLOC_NOT_POSSIBLE) == TRUE)
      { labelLernLocActiveReason->Text = "Mehr als 1 RE nicht lokalisierbar.";  }

      else if(bGetBitBetriebszustandBZ(cLOC_INTERRUPTED) == TRUE)
      { labelLernLocActiveReason->Text = "Radelektroniken sind im drive mode.";  }

    }

    labelFirstEmptySlotValue->Text = "";

    for (ucLoop = 0; ucLoop < cSumWE; ucLoop++)
    {
      switch ( ucLoop)
      {
        case 0:

          textNoOfUsedPalTelegramsWL_0->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_0->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_0->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_0->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_0->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_0->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_0->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));

          textDistance0->Text = System::String::Format("{0}", ucGetZomDeltaMin(ucLoop));
          if(ucGetZomDeltaMin(ucLoop) >= ucGetAllocMinDeltaValueFPA())
          {
            textDistance0->BackColor = System::Drawing::Color::FromArgb(0,255,0);
          }
          else
          {
            textDistance0->BackColor = textDistance0->DefaultBackColor;
          }

          labelMinValSlot0VL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 0));
          labelMinValSlot0VR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 1));
          labelMinValSlot0HL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 2));
          labelMinValSlot0HR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 3));

          if((System::Convert::ToInt16(labelMinValSlot0VL->Text) < System::Convert::ToInt16(labelMinValSlot0VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0VL->Text) < System::Convert::ToInt16(labelMinValSlot0HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0VL->Text) < System::Convert::ToInt16(labelMinValSlot0HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot0VL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot0VL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot0VL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot0VL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot0VR->Text) < System::Convert::ToInt16(labelMinValSlot0VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0VR->Text) < System::Convert::ToInt16(labelMinValSlot0HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0VR->Text) < System::Convert::ToInt16(labelMinValSlot0HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot0VR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot0VR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot0VR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }
          }
          else
          {
            labelMinValSlot0VR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot0HL->Text) < System::Convert::ToInt16(labelMinValSlot0VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0HL->Text) < System::Convert::ToInt16(labelMinValSlot0VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0HL->Text) < System::Convert::ToInt16(labelMinValSlot0HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot0HL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot0HL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot0HL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }
          }
          else
          {
            labelMinValSlot0HL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot0HR->Text) < System::Convert::ToInt16(labelMinValSlot0VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0HR->Text) < System::Convert::ToInt16(labelMinValSlot0VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot0HR->Text) < System::Convert::ToInt16(labelMinValSlot0HL->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot0HR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot0HR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot0HR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }
          }
          else
          {
            labelMinValSlot0HR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }
        break;

        case 1:

          textNoOfUsedPalTelegramsWL_1->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_1->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_1->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_1->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_1->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_1->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_1->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));

          textDistance1->Text = System::String::Format("{0}", ucGetZomDeltaMin(ucLoop));
          if(ucGetZomDeltaMin(ucLoop) >= ucGetAllocMinDeltaValueFPA())
          {
            textDistance1->BackColor = System::Drawing::Color::FromArgb(0,255,0);
          }
          else
          {
            textDistance1->BackColor = textDistance0->DefaultBackColor;
          }

          labelMinValSlot1VL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 0));
          labelMinValSlot1VR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 1));
          labelMinValSlot1HL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 2));
          labelMinValSlot1HR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 3));

          if((System::Convert::ToInt16(labelMinValSlot1VL->Text) < System::Convert::ToInt16(labelMinValSlot1VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1VL->Text) < System::Convert::ToInt16(labelMinValSlot1HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1VL->Text) < System::Convert::ToInt16(labelMinValSlot1HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot1VL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot1VL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot1VL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot1VL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot1VR->Text) < System::Convert::ToInt16(labelMinValSlot1VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1VR->Text) < System::Convert::ToInt16(labelMinValSlot1HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1VR->Text) < System::Convert::ToInt16(labelMinValSlot1HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot1VR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot1VR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot1VR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot1VR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot1HL->Text) < System::Convert::ToInt16(labelMinValSlot1VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1HL->Text) < System::Convert::ToInt16(labelMinValSlot1VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1HL->Text) < System::Convert::ToInt16(labelMinValSlot1HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot1HL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot1HL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot1HL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot1HL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot1HR->Text) < System::Convert::ToInt16(labelMinValSlot1VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1HR->Text) < System::Convert::ToInt16(labelMinValSlot1VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot1HR->Text) < System::Convert::ToInt16(labelMinValSlot1HL->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot1HR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot1HR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot1HR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot1HR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }
        break;

        case 2:

          textNoOfUsedPalTelegramsWL_2->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_2->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_2->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_2->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_2->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_2->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_2->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));

          textDistance2->Text = System::String::Format("{0}", ucGetZomDeltaMin(ucLoop));
          if(ucGetZomDeltaMin(ucLoop) >= ucGetAllocMinDeltaValueFPA())
          {
            textDistance2->BackColor = System::Drawing::Color::FromArgb(0,255,0);
          }
          else
          {
            textDistance2->BackColor = textDistance0->DefaultBackColor;
          }

          labelMinValSlot2VL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 0));
          labelMinValSlot2VR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 1));
          labelMinValSlot2HL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 2));
          labelMinValSlot2HR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 3));

          if((System::Convert::ToInt16(labelMinValSlot2VL->Text) < System::Convert::ToInt16(labelMinValSlot2VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2VL->Text) < System::Convert::ToInt16(labelMinValSlot2HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2VL->Text) < System::Convert::ToInt16(labelMinValSlot2HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot2VL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot2VL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot2VL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }
          }
          else
          {
            labelMinValSlot2VL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot2VR->Text) < System::Convert::ToInt16(labelMinValSlot2VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2VR->Text) < System::Convert::ToInt16(labelMinValSlot2HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2VR->Text) < System::Convert::ToInt16(labelMinValSlot2HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot2VR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot2VR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot2VR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }
          }
          else
          {
            labelMinValSlot2VR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot2HL->Text) < System::Convert::ToInt16(labelMinValSlot2VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2HL->Text) < System::Convert::ToInt16(labelMinValSlot2VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2HL->Text) < System::Convert::ToInt16(labelMinValSlot2HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot2HL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot2HL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot2HL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot2HL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot2HR->Text) < System::Convert::ToInt16(labelMinValSlot2VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2HR->Text) < System::Convert::ToInt16(labelMinValSlot2VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot2HR->Text) < System::Convert::ToInt16(labelMinValSlot2HL->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot2HR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot2HR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot2HR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot2HR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }
        break;

        case 3:

          textNoOfUsedPalTelegramsWL_3->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_3->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_3->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_3->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_3->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_3->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_3->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));

          textDistance3->Text = System::String::Format("{0}", ucGetZomDeltaMin(ucLoop));
          if(ucGetZomDeltaMin(ucLoop) >= ucGetAllocMinDeltaValueFPA())
          {
            textDistance3->BackColor = System::Drawing::Color::FromArgb(0,255,0);
          }
          else
          {
            textDistance3->BackColor = textDistance0->DefaultBackColor;
          }

          labelMinValSlot3VL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 0));
          labelMinValSlot3VR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 1));
          labelMinValSlot3HL->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 2));
          labelMinValSlot3HR->Text = System::String::Format("{0}", ucGetZomAbsMetrics(ucLoop, 3));

          if((System::Convert::ToInt16(labelMinValSlot3VL->Text) < System::Convert::ToInt16(labelMinValSlot3VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3VL->Text) < System::Convert::ToInt16(labelMinValSlot3HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3VL->Text) < System::Convert::ToInt16(labelMinValSlot3HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot3VL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot3VL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot3VL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot3VL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot3VR->Text) < System::Convert::ToInt16(labelMinValSlot3VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3VR->Text) < System::Convert::ToInt16(labelMinValSlot3HL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3VR->Text) < System::Convert::ToInt16(labelMinValSlot3HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot3VR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot3VR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot3VR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot3VR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot3HL->Text) < System::Convert::ToInt16(labelMinValSlot3VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3HL->Text) < System::Convert::ToInt16(labelMinValSlot3VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3HL->Text) < System::Convert::ToInt16(labelMinValSlot3HR->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot3HL->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot3HL->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot3HL->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot3HL->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }

          if((System::Convert::ToInt16(labelMinValSlot3HR->Text) < System::Convert::ToInt16(labelMinValSlot3VL->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3HR->Text) < System::Convert::ToInt16(labelMinValSlot3VR->Text))
            &&(System::Convert::ToInt16(labelMinValSlot3HR->Text) < System::Convert::ToInt16(labelMinValSlot3HL->Text)))
          {
            if(System::Convert::ToInt16(labelMinValSlot3HR->Text) <= ucGetAllocAbsoluteMinValueFPA())
            {
              labelMinValSlot3HR->BackColor = System::Drawing::Color::FromArgb(0,255,0);
            }
            else
            {
              labelMinValSlot3HR->BackColor = System::Drawing::Color::FromArgb(255,255,0);
            }

          }
          else
          {
            labelMinValSlot3HR->BackColor = System::Drawing::Color::FromArgb(255,192,128);
          }
        break;

        case 4:

          textNoOfUsedPalTelegramsWL_4->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_4->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_4->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_4->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_4->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_4->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_4->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));
        break;

        case 5:

          textNoOfUsedPalTelegramsWL_5->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_5->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_5->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_5->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_5->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_5->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_5->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));
        break;

        case 6:

          textNoOfUsedPalTelegramsWL_6->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_6->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_6->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_6->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_6->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_6->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_6->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));
        break;

        case 7:

          textNoOfUsedPalTelegramsWL_7->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrLearnBit(ucLoop));
          textNoOfUsedPalTelegramsWOL_7->Text = System::String::Format("{0}", ucGetZomToothTelCtCorrNoLearnBit(ucLoop));
          textNoOfTelWOCorr_7->Text = System::String::Format("{0}", ucGetZomToothTelCtrNoCorr(ucLoop));
          textNoOfTelWOLMode_7->Text = System::String::Format("{0}", ucGetZomToothTelCtNoLearnMode(ucLoop));
          textNoOfTelsAbsolute_7->Text = System::String::Format("{0}", ucGetZomAbsoluteProbeCt(ucLoop));
          textNoOfTelsUsedForLearn_7->Text = System::String::Format("{0}", ucGetZomLearnProbeCt(ucLoop));
          textNoOfFpaUsedTels_7->Text = System::String::Format("{0}", ucGetZomLocateProbeCt(ucLoop));
        break;
      }

      if( labelFirstEmptySlotValue->Text == "")
      {
        if( ulGetZOMID( ucLoop) == 0)
        {
          labelFirstEmptySlotValue->Text = System::String::Format("{0}", ucLoop);
        }
      }
    }

    if( ucLogging > 0)
    {
      if( checkBoxDataSelection->Checked == false)
      {

        AddOffsetToTimeLOG( (unsigned long long) System::Decimal::ToInt64( GetOutputDataTimer->Interval));
      }

      if( bLineBufferEmptyLOG() == TRUE)
      {
        PutRfDataToBufferLOG( NULL);
      }

      if(checkBoxLogWHL->Checked == TRUE)
      {
         PutDwordToBufferLOG( GETulWarnOutTM());

         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupA));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupB));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupC));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupD));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupE));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupF));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupG));
         PutByteToBufferLOG( GETucWarningGroupTM( cucWT_GroupH));

        (void) ucGetWarnBitIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnBitOutInt);
        (void) ucGetWarnBitTonnageIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnBitTonnageInt);
        (void) ucGetWarnBitAirMassIdIntIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnBitAirmassInt);
        (void) ucGetWarnVectorIdExtIFH( Rte_Inst_CtApHufTpmsSWC, ucWarnVectorExt);

        for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
        {
          ucHistoryIndex = ucGetColOfWP( ucLoop);
          if( ucHistoryIndex >= cAnzRad)
          {
            ucHistoryIndex = ucLoop;
          }

            PutByteToBufferLOG( ucWarnBitOutInt[ucHistoryIndex]);
            PutByteToBufferLOG( ucWarnBitTonnageInt[ucHistoryIndex]);
            PutByteToBufferLOG( ucWarnBitAirmassInt[ucHistoryIndex]);
            PutByteToBufferLOG( ucWarnVectorExt[ucHistoryIndex]);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_Ppanne, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_Pmin, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_Pwarn, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_PwarnTol, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_Pvorw, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_DHW, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetWarnThresDM( ucHistoryIndex, cucIX_FT, &ucSetLevel, &ucResetLevel);
            PutWordToBufferLOG( ucSetLevel * 25);
            PutWordToBufferLOG( ucResetLevel * 25);

                                                          GetTimerValPWARN( ucHistoryIndex, &ucTimerState, &ushTimerCounter);
            PutWordToBufferLOG( ushTimerCounter);

                                                          GetTimerValPWARNTOL( ucHistoryIndex, &ucTimerState, &ushTimerCounter);
            PutWordToBufferLOG( ushTimerCounter);

                                                          GetTimerValDHW( ucHistoryIndex, &ucRefPres, &ucLastPres, &ushTimCnt, &ushTimCountLatch);
            PutWordToBufferLOG( ucRefPres * 25);
            PutWordToBufferLOG( ucLastPres * 25);
            PutWordToBufferLOG( ushTimCnt);
            PutWordToBufferLOG( ushTimCountLatch);

                                                          (void) ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, ucHistoryIndex);
            PutWordToBufferLOG( ucPcold * 25);
            PutSignedByteToBufferLOG( scTcold);
            PutWordToBufferLOG( ucPwarm * 25);
            PutSignedByteToBufferLOG( scTwarm);
            PutWordToBufferLOG( ushMSoll);
            PutWordToBufferLOG( ucPamb * 25);
        }

      }

      if(checkBoxLogWAL->Checked == TRUE)
      {

        ucZomIndex = GetLastRecEventZomPos();

        if(ucZomIndex < cSumWE)
        {

           PutByteToBufferLOG( ucGetZomAbsoluteProbeCt(ucZomIndex));
           PutByteToBufferLOG( ucGetZomLearnProbeCt(ucZomIndex));
           PutByteToBufferLOG( ucGetZomLocateProbeCt(ucZomIndex));
           PutWordToBufferLOG( ucGetZomDistanceValue(0, ucZomIndex, 0));
           PutWordToBufferLOG( ucGetZomDistanceValue(0, ucZomIndex, 1));
           PutWordToBufferLOG( ucGetZomDistanceValue(0, ucZomIndex, 2));
           PutWordToBufferLOG( ucGetZomDistanceValue(0, ucZomIndex, 3));
           PutWordToBufferLOG( ucGetZomDistanceValue(1, ucZomIndex, 0));
           PutWordToBufferLOG( ucGetZomDistanceValue(1, ucZomIndex, 1));
           PutWordToBufferLOG( ucGetZomDistanceValue(1, ucZomIndex, 2));
           PutWordToBufferLOG( ucGetZomDistanceValue(1, ucZomIndex, 3));
           PutWordToBufferLOG( ushGetZomAbsRefValue(0, ucZomIndex, 0));
           PutWordToBufferLOG( ushGetZomAbsRefValue(0, ucZomIndex, 1));
           PutWordToBufferLOG( ushGetZomAbsRefValue(0, ucZomIndex, 2));
           PutWordToBufferLOG( ushGetZomAbsRefValue(0, ucZomIndex, 3));
           PutWordToBufferLOG( ushGetZomAbsRefValue(1, ucZomIndex, 0));
           PutWordToBufferLOG( ushGetZomAbsRefValue(1, ucZomIndex, 1));
           PutWordToBufferLOG( ushGetZomAbsRefValue(1, ucZomIndex, 2));
           PutWordToBufferLOG( ushGetZomAbsRefValue(1, ucZomIndex, 3));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 0, 0));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 1, 0));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 2, 0));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 3, 0));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 0, 1));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 1, 1));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 2, 1));
           PutWordToBufferLOG( ushGetZomDeltaSum(ucZomIndex, 3, 1));
           PutByteToBufferLOG( ucGetZomAbsMetrics(ucZomIndex, 0));
           PutByteToBufferLOG( ucGetZomAbsMetrics(ucZomIndex, 1));
           PutByteToBufferLOG( ucGetZomAbsMetrics(ucZomIndex, 2));
           PutByteToBufferLOG( ucGetZomAbsMetrics(ucZomIndex, 3));
           PutByteToBufferLOG( ucGetZomDeltaMin(ucZomIndex));
           PutByteToBufferLOG( ucGetZomAbsComp(ucZomIndex, 0));
           PutByteToBufferLOG( ucGetZomAbsComp(ucZomIndex, 1));
           PutByteToBufferLOG( ucGetZomAbsComp(ucZomIndex, 2));
           PutByteToBufferLOG( ucGetZomAbsComp(ucZomIndex, 3));

        }else{
          PutInitWalToBufferLOG();
        }
      }

      if(checkBoxLogOUT->Checked == TRUE)
      {
        ucDbgByte = ucGetActualStateWL();
        PutByteToBufferLOG( ucDbgByte);

        ulDbgDword = ulGetStartedStateOfVklCCM();
        PutDwordToBufferLOG( ulDbgDword);

        GetTyrePressureValueITY( Rte_Inst_CtApHufTpmsSWC, &ushPTyreFL, &ushPTyreFR, &ushPTyreRL, &ushPTyreRR);
        PutWordToBufferLOG( ushPTyreFL);
        PutWordToBufferLOG( ushPTyreFR);
        PutWordToBufferLOG( ushPTyreRL);
        PutWordToBufferLOG( ushPTyreRR);

        GetTyreTemperatureValueITY( Rte_Inst_CtApHufTpmsSWC, &ushTTyreFL, &ushTTyreFR, &ushTTyreRL, &ushTTyreRR);
        if( (ushTTyreFL >= cTyreTemperatureNotAvailableValueITY) || (ushTTyreFR >= cTyreTemperatureNotAvailableValueITY) || (ushTTyreRL >= cTyreTemperatureNotAvailableValueITY) || (ushTTyreRR >= cTyreTemperatureNotAvailableValueITY))
        {
          PutWordToBufferLOG( ushTTyreFL);
          PutWordToBufferLOG( ushTTyreFR);
          PutWordToBufferLOG( ushTTyreRL);
          PutWordToBufferLOG( ushTTyreRR);
        }else{
          PutSignedWordToBufferLOG( (sint16) (ushTTyreFL - cITYTyreTemperatureOffsetValue));
          PutSignedWordToBufferLOG( (sint16) (ushTTyreFR - cITYTyreTemperatureOffsetValue));
          PutSignedWordToBufferLOG( (sint16) (ushTTyreRL - cITYTyreTemperatureOffsetValue));
          PutSignedWordToBufferLOG( (sint16) (ushTTyreRR - cITYTyreTemperatureOffsetValue));
        }

        GetRelatedPressureValueITY( Rte_Inst_CtApHufTpmsSWC, &ushPTyreFL, &ushPTyreFR, &ushPTyreRL, &ushPTyreRR);
        PutWordToBufferLOG( ushGetMaxValueDM( ushPTyreFL, ushPTyreFR));
        PutWordToBufferLOG( ushGetMaxValueDM( ushPTyreFL, ushPTyreFR));
        PutWordToBufferLOG( ushGetMaxValueDM( ushPTyreRL, ushPTyreRR));
        PutWordToBufferLOG( ushGetMaxValueDM( ushPTyreRL, ushPTyreRR));

        GetStTyrITY( &ucStTyreINFO, &ucStTyreTPL, &ucStTyreTFAI);
        PutByteToBufferLOG( ucStTyreINFO);
        PutByteToBufferLOG( ucStTyreTPL);
        PutByteToBufferLOG( ucStTyreTFAI);

        PutByteToBufferLOG( GETTyreSelectionActiveEE( Rte_Inst_CtApHufTpmsSWC));

        PutByteToBufferLOG( GETucStatusbarEE( Rte_Inst_CtApHufTpmsSWC));

		    PutByteToBufferLOG( GetLengthOfTyreListDM());
        PutByteToBufferLOG( GetSummerTyreIndexDM());
		    PutByteToBufferLOG( GetWinterTyreIndexDM());
		    PutByteToBufferLOG( GetLoadStateDM());
		    PutByteToBufferLOG( GetSeasonDM());
		    PutByteToBufferLOG( GetIDRMessageCenterDM());
        PutByteToBufferLOG( GetStatusManSelectionDM());

        PutWordToBufferLOG( ushGetMaxCoolingDownTimeITY());
        PutWordToBufferLOG( ushGetCorHoldOffTimeITY());
        PutWordToBufferLOG( ucGetCRdciMaxCorRcpCD() * 25);
        PutByteToBufferLOG( bGetCRdciResetPlausiCD());
        PutByteToBufferLOG( bGetCRdciDispResetCD());
        PutByteToBufferLOG( bGetCRdciErfsEnableCD());

        for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
        {
          ucHistoryIndex = ucGetColOfWP( ucLoop);
          if( ucHistoryIndex < cAnzRad)
          {
            ucPresVal = GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucHistoryIndex);
            scTempVal = GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, ucHistoryIndex);
          }else{
            ucPresVal = GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop);
            scTempVal = GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop);
          }

          if( ucPresVal == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPresVal * 25);
          }

          PutSignedByteToBufferLOG( scTempVal);
        }

        for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
        {
          ucHistoryIndex = ucGetColOfWP( ucLoop);
          if( ucHistoryIndex < cAnzRad)
          {
            ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, ucHistoryIndex);
          }else{
            ucGetPTSollUSWIF( Rte_Inst_CtApHufTpmsSWC, &ucPcold, &scTcold, &ucPwarm, &scTwarm, &ushMSoll, &ucPamb, ucLoop);

          }

          if( ucPcold == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPcold * 25);
          }

          PutSignedByteToBufferLOG( scTcold);

          if( ucPwarm == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPwarm * 25);
          }

          PutSignedByteToBufferLOG( scTwarm);
          PutWordToBufferLOG( ushMSoll);
          PutWordToBufferLOG( ucPamb * 25);
        }

        for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
        {
          ucHistoryIndex = ucGetColOfWP( ucLoop);
          if( ucHistoryIndex < cAnzRad)
          {
            ucPcold = ucGetPinitTinitDM( ucHistoryIndex);
            scTcold = scGetTinitDM( ucHistoryIndex);
          }else{
            ucPcold = ucGetPinitTinitDM( ucLoop);
            scTcold = scGetTinitDM( ucLoop);
          }

          if( ucPcold < cInvalidREpressure)
          {
            PutWordToBufferLOG( ucPcold * 25);
          }else{
            PutWordToBufferLOG( ucPcold);
          }

          PutSignedByteToBufferLOG( scTcold);
        }

        PutWordToBufferLOG( ushGetMaxCoolingDownTimeITY());

        for( ucLoop = 0; ucLoop < cAnzRad; ucLoop++)
        {
          ucHistoryIndex = ucGetColOfWP( ucLoop);
          if( ucHistoryIndex < cAnzRad)
          {
            GetAvlPTyreCoolingValITY( ucHistoryIndex, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
          }else{
            GetAvlPTyreCoolingValITY( ucLoop, &ucPwarm, &scTwarm, &ucPcold, &scTcold, &ucPist_t, &scTist_t, &ucPsollWarm, &ucPsollCold, &scTsollCold, &ucPsoll_t, &ushElapsedCoolingTime, &ushTimeTicks, &ulCoolingCaptTime);
          }

          if( ucPcold == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPcold * 25);
          }

          PutSignedByteToBufferLOG( scTcold);

          if( ucPwarm == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPwarm * 25);
          }

          PutSignedByteToBufferLOG( scTwarm);

          if( ucPist_t == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPist_t * 25);
          }

          PutSignedByteToBufferLOG( scTist_t);

          if( ucPsollCold == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPsollCold * 25);
          }

          PutSignedByteToBufferLOG( scTsollCold);

          if( ucPsollWarm == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPsollWarm * 25);
          }

          if( ucPsoll_t == cInvalidREpressure)
          {
            PutWordToBufferLOG( 0xffffu);
          }else{
            PutWordToBufferLOG( ucPsoll_t * 25);
          }
        }

        PutWordToBufferLOG( ushElapsedCoolingTime);

        if( ushTimeTicks > cCoolingIntervalTicksVal)
        {
          PutWordToBufferLOG( ushTimeTicks);
        }else{
          PutWordToBufferLOG( ushTimeTicks / 10);
        }

        PutDwordToBufferLOG( ulCoolingCaptTime);

      }

      if(checkBoxLogDTC->Checked == TRUE)
      {

        GetNwMonitoringDataNWM( &tNwMonData);

        if(tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout < tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout)
        {
          PutWordToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[0].ushMsgTimeout);
        }
        else
        {
          PutWordToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[1].ushMsgTimeout);
        }

        if(tNwMonData.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout < tNwMonData.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout)
        {
          PutWordToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[0].ushSignalErrorTimeout);
        }
        else
        {
          PutWordToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[1].ushSignalErrorTimeout);
        }

        if(tNwMonData.tMonRDC_DT_PCKG[0].ucAliveErrorCounter < tNwMonData.tMonRDC_DT_PCKG[1].ucAliveErrorCounter)
        {
          PutByteToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[0].ucAliveErrorCounter);
        }
        else
        {
          PutByteToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[1].ucAliveErrorCounter);
        }

        if(tNwMonData.tMonRDC_DT_PCKG[0].ucAlvErrGoodCounter < tNwMonData.tMonRDC_DT_PCKG[1].ucAlvErrGoodCounter)
        {
          PutByteToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[0].ucAlvErrGoodCounter);
        }
        else
        {
          PutByteToBufferLOG(tNwMonData.tMonRDC_DT_PCKG[1].ucAlvErrGoodCounter);
        }

        PutByteToBufferLOG( tNwMonData.tMonA_TEMP.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonA_TEMP.ucSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonEINH_BN2020.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonEINH_BN2020.ucSignalErrorCounter);

        PutByteToBufferLOG( tNwMonData.tMonCON_VEH.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonCON_VEH.ucCrcErrorCounter);
        PutByteToBufferLOG( tNwMonData.tMonCON_VEH.ucAliveErrorCounter);
        PutByteToBufferLOG( tNwMonData.tMonCON_VEH.ucSignalErrorCounter);

        PutByteToBufferLOG( tNwMonData.tMonRELATIVZEIT.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonRELATIVZEIT.ucSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonDT_PT_1.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonDT_PT_1.ucSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonFZZSTD.ucSignalErrorCounter);

        PutWordToBufferLOG( tNwMonData.tMonKILOMETERSTAND.ushSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonNMEARawData2Part2.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonNMEARawData2Part2.ucSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonNMEARawData2Part3.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonNMEARawData2Part3.ucSignalErrorTimeout);

        PutWordToBufferLOG( tNwMonData.tMonUHRZEIT_DATUM.ushSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonWMOM_DRV_4.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonWMOM_DRV_4.ucSignalErrorTimeout);

        PutByteToBufferLOG( tNwMonData.tMonV_VEH.ucMsgTimeout);
        PutByteToBufferLOG( tNwMonData.tMonV_VEH.ucCrcErrorTimeout);
        PutByteToBufferLOG( tNwMonData.tMonV_VEH.ucAliveErrorTimeout);
        PutByteToBufferLOG( tNwMonData.tMonV_VEH.ucSigQualifErrorTimeout);
      }

      if(checkBoxLogDBG->Checked == TRUE)
      {
        if( ucFrDbgDscSuppMux != *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 (  Rte_Inst_CtApHufTpmsSWC))
        {

          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_1 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_2 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_3 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_4 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_5 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_6 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_7 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_8 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_9 ( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_10( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_11( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_12( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_13( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_14( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_15( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_16( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_17( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_18( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_19( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_20( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_21( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_22( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_23( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_24( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_25( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_26( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_27( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_28( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_29( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_30( Rte_Inst_CtApHufTpmsSWC));
          PutByteToBufferLOG( *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_2_RDCI_DATA_31( Rte_Inst_CtApHufTpmsSWC));

          ucFrDbgDscSuppMux = *(uint8 *)Rte_IWriteRef_RCyclicRDCiTask_PpFrPdu_FR_DBG_DSC_SUPP_1_RDCI_DATA_0 (  Rte_Inst_CtApHufTpmsSWC);
        }
        else
        {
          PutInitDbgToBufferLOG();
        }
      }

      PutNewLineToBufferLOG();

      if(ucLogging == 1)
      {
        if(fileStreamIsOpen == 0)
        {

          StopLOG();

          buttonLogging->Text = "Start Logging ...";
          OutputTimerInterval->Value = 10;
          ucLogging = 0;
        }
      }
    }
  }
#endif
