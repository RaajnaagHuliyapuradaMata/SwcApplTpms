#ifndef _RTE_STUB_RID_DIALOG_H
#define _RTE_STUB_RID_DIALOG_H
private: System::Void buttonRID_Daten1_Click(System::Object^  sender, System::EventArgs^  e)
{
   uint16 ushTempBuf;
   uint8 uc100er,uc10er,uc1er,ucData;

	 ushTempBuf = System::Decimal::ToUInt16 (RID_Reifenbreite->Value);

   uc100er = (ushTempBuf/100);
   uc10er =  (ushTempBuf - uc100er * 100)/10;
   uc1er =   (ushTempBuf - uc100er * 100 - uc10er * 10);

   ucData = ((uc100er + 6)<<4) | (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 0, ucData);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Querschnitt->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 1, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Durchmesser->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 2, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Tragfaehigkeit->Value);

   uc10er = ((ushTempBuf & 0xF8) >> 3);
   ucData |= uc10er;

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 3, ucData);

   uc1er = ((ushTempBuf & 0x07) << 5);

   ucData = uc1er;

   ushTempBuf = System::Decimal::ToUInt16 (RID_GeschwIndex->Value);

   uc10er = (ushTempBuf - 0x40);

   ucData |= uc10er;
   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 4, ucData);

   if(comboBoxRID_Reifentyp->Text == "0: Standard")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Reifentyp->Text == "2: RunFlat")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc100er = (ushTempBuf << 6);

   if(comboBoxRID_Saison->Text == "0: Allwetterreifen")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Saison->Text == "1: Sommer")
   {
     ushTempBuf = 0x01;
   }
   else if(comboBoxRID_Saison->Text == "2: Winter (M+S)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc10er = (ushTempBuf << 2);

   if(comboBoxRID_Karkasse->Text == "0: Normale Last")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Karkasse->Text == "1: Extra Last (XL)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x33;
   }

   uc1er = (uint8)ushTempBuf;

   ucData = (uc100er | uc10er | uc1er);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 5, ucData);

   ucData = System::Decimal::ToByte (RID_DOT1->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 0, ucData);
   ucData = System::Decimal::ToByte (RID_DOT2->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 1, ucData);
   ucData = System::Decimal::ToByte (RID_DOT3->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 2, ucData);
   ucData = System::Decimal::ToByte (RID_DOT4->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 3, ucData);
   ucData = System::Decimal::ToByte (RID_DOT5->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 4, ucData);
   ucData = System::Decimal::ToByte (RID_DOT6->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 5, ucData);
   ucData = System::Decimal::ToByte (RID_DOT7->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 6, ucData);
   ucData = System::Decimal::ToByte (RID_DOT8->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 0, 7, ucData);
}

private: System::Void buttonRID_Daten2_Click(System::Object^  sender, System::EventArgs^  e)
{
 uint16 ushTempBuf;
   uint8 uc100er,uc10er,uc1er,ucData;

	 ushTempBuf = System::Decimal::ToUInt16 (RID_Reifenbreite->Value);

   uc100er = (ushTempBuf/100);
   uc10er =  (ushTempBuf - uc100er * 100)/10;
   uc1er =   (ushTempBuf - uc100er * 100 - uc10er * 10);

   ucData = ((uc100er + 6)<<4) | (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 0, ucData);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Querschnitt->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 1, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Durchmesser->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 2, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Tragfaehigkeit->Value);

   uc10er = ((ushTempBuf & 0xF8) >> 3);
   ucData |= uc10er;

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 3, ucData);

   uc1er = ((ushTempBuf & 0x07) << 5);

   ucData = uc1er;

   ushTempBuf = System::Decimal::ToUInt16 (RID_GeschwIndex->Value);

   uc10er = (ushTempBuf - 0x40);

   ucData |= uc10er;
   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 4, ucData);

   if(comboBoxRID_Reifentyp->Text == "0: Standard")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Reifentyp->Text == "2: RunFlat")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc100er = (ushTempBuf << 6);

   if(comboBoxRID_Saison->Text == "0: Allwetterreifen")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Saison->Text == "1: Sommer")
   {
     ushTempBuf = 0x01;
   }
   else if(comboBoxRID_Saison->Text == "2: Winter (M+S)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc10er = (ushTempBuf << 2);

   if(comboBoxRID_Karkasse->Text == "0: Normale Last")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Karkasse->Text == "1: Extra Last (XL)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x33;
   }

   uc1er = (uint8)ushTempBuf;

   ucData = (uc100er | uc10er | uc1er);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 5, ucData);

   ucData = System::Decimal::ToByte (RID_DOT1->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 0, ucData);
   ucData = System::Decimal::ToByte (RID_DOT2->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 1, ucData);
   ucData = System::Decimal::ToByte (RID_DOT3->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 2, ucData);
   ucData = System::Decimal::ToByte (RID_DOT4->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 3, ucData);
   ucData = System::Decimal::ToByte (RID_DOT5->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 4, ucData);
   ucData = System::Decimal::ToByte (RID_DOT6->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 5, ucData);
   ucData = System::Decimal::ToByte (RID_DOT7->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 6, ucData);
   ucData = System::Decimal::ToByte (RID_DOT8->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 1, 7, ucData);
}
private: System::Void buttonRID_Daten3_Click(System::Object^  sender, System::EventArgs^  e)
{
  uint16 ushTempBuf;
   uint8 uc100er,uc10er,uc1er,ucData;

	 ushTempBuf = System::Decimal::ToUInt16 (RID_Reifenbreite->Value);

   uc100er = (ushTempBuf/100);
   uc10er =  (ushTempBuf - uc100er * 100)/10;
   uc1er =   (ushTempBuf - uc100er * 100 - uc10er * 10);

   ucData = ((uc100er + 6)<<4) | (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 0, ucData);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Querschnitt->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 1, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Durchmesser->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 2, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Tragfaehigkeit->Value);

   uc10er = ((ushTempBuf & 0xF8) >> 3);
   ucData |= uc10er;

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 3, ucData);

   uc1er = ((ushTempBuf & 0x07) << 5);

   ucData = uc1er;

   ushTempBuf = System::Decimal::ToUInt16 (RID_GeschwIndex->Value);

   uc10er = (ushTempBuf - 0x40);

   ucData |= uc10er;
   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 4, ucData);

   if(comboBoxRID_Reifentyp->Text == "0: Standard")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Reifentyp->Text == "2: RunFlat")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc100er = (ushTempBuf << 6);

   if(comboBoxRID_Saison->Text == "0: Allwetterreifen")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Saison->Text == "1: Sommer")
   {
     ushTempBuf = 0x01;
   }
   else if(comboBoxRID_Saison->Text == "2: Winter (M+S)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc10er = (ushTempBuf << 2);

   if(comboBoxRID_Karkasse->Text == "0: Normale Last")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Karkasse->Text == "1: Extra Last (XL)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x33;
   }

   uc1er = (uint8)ushTempBuf;

   ucData = (uc100er | uc10er | uc1er);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 5, ucData);

   ucData = System::Decimal::ToByte (RID_DOT1->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 0, ucData);
   ucData = System::Decimal::ToByte (RID_DOT2->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 1, ucData);
   ucData = System::Decimal::ToByte (RID_DOT3->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 2, ucData);
   ucData = System::Decimal::ToByte (RID_DOT4->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 3, ucData);
   ucData = System::Decimal::ToByte (RID_DOT5->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 4, ucData);
   ucData = System::Decimal::ToByte (RID_DOT6->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 5, ucData);
   ucData = System::Decimal::ToByte (RID_DOT7->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 6, ucData);
   ucData = System::Decimal::ToByte (RID_DOT8->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 2, 7, ucData);
}
private: System::Void buttonRID_Daten4_Click(System::Object^  sender, System::EventArgs^  e)
{
  uint16 ushTempBuf;
   uint8 uc100er,uc10er,uc1er,ucData;

	 ushTempBuf = System::Decimal::ToUInt16 (RID_Reifenbreite->Value);

   uc100er = (ushTempBuf/100);
   uc10er =  (ushTempBuf - uc100er * 100)/10;
   uc1er =   (ushTempBuf - uc100er * 100 - uc10er * 10);

   ucData = ((uc100er + 6)<<4) | (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 0, ucData);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Querschnitt->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 1, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Durchmesser->Value);

   uc10er = ushTempBuf/10;

   ucData |= (uc10er + 6);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 2, ucData);

   uc1er  = (ushTempBuf - uc10er * 10);

   ucData = ((uc1er + 6)<<4);

   ushTempBuf = System::Decimal::ToUInt16 (RID_Tragfaehigkeit->Value);

   uc10er = ((ushTempBuf & 0xF8) >> 3);
   ucData |= uc10er;

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 3, ucData);

   uc1er = ((ushTempBuf & 0x07) << 5);

   ucData = uc1er;

   ushTempBuf = System::Decimal::ToUInt16 (RID_GeschwIndex->Value);

   uc10er = (ushTempBuf - 0x40);

   ucData |= uc10er;
   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 4, ucData);

   if(comboBoxRID_Reifentyp->Text == "0: Standard")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Reifentyp->Text == "2: RunFlat")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc100er = (ushTempBuf << 6);

   if(comboBoxRID_Saison->Text == "0: Allwetterreifen")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Saison->Text == "1: Sommer")
   {
     ushTempBuf = 0x01;
   }
   else if(comboBoxRID_Saison->Text == "2: Winter (M+S)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x03;
   }

   uc10er = (ushTempBuf << 2);

   if(comboBoxRID_Karkasse->Text == "0: Normale Last")
   {
     ushTempBuf = 0x00;
   }
   else if(comboBoxRID_Karkasse->Text == "1: Extra Last (XL)")
   {
     ushTempBuf = 0x02;
   }
   else
   {
     ushTempBuf = 0x33;
   }

   uc1er = (uint8)ushTempBuf;

   ucData = (uc100er | uc10er | uc1er);

   PUTTyreDimDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 5, ucData);

   ucData = System::Decimal::ToByte (RID_DOT1->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 0, ucData);
   ucData = System::Decimal::ToByte (RID_DOT2->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 1, ucData);
   ucData = System::Decimal::ToByte (RID_DOT3->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 2, ucData);
   ucData = System::Decimal::ToByte (RID_DOT4->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 3, ucData);
   ucData = System::Decimal::ToByte (RID_DOT5->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 4, ucData);
   ucData = System::Decimal::ToByte (RID_DOT6->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 5, ucData);
   ucData = System::Decimal::ToByte (RID_DOT7->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 6, ucData);
   ucData = System::Decimal::ToByte (RID_DOT8->Value);
   PUTTyreDOTDataEE( Rte_Inst_CtApHufTpmsSWC, 3, 7, ucData);
}

private: System::Void RID_Reifenbreite_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{

}

#endif
