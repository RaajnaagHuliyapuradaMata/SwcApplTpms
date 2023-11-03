#ifndef _RTE_STUB_WALLOC_DIALOG_H
#define _RTE_STUB_WALLOC_DIALOG_H

    private: System::Void checkBoxEigenrad_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
    {
      if( checkBoxEigenrad->Checked == true)
      {
        SetBitBetriebszustandBZ( cEIGENRAD);
      }else{
        ClearBitBetriebszustandBZ( cEIGENRAD);
        ClearBitBetriebszustandBZ( cZUGEORDNET);
      }
    }

    private: System::Void checkBoxZugeordnet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
    {
      if( checkBoxZugeordnet->Checked == true)
      {
        SetBitBetriebszustandBZ( cEIGENRAD);
        SetBitBetriebszustandBZ( cZUGEORDNET);
      }else{
        ClearBitBetriebszustandBZ( cZUGEORDNET);
      }
    }

#endif
