#include "TAmbFilt.h"
#include "EeWarnstatusBlockX.h"
#include "EeCommonBlockX.h"
#include "CodingDataX.h"
#include "State_FzzX.h"

static TAmbientFilterValueType sshTAmbientFilterTAF;

void InitTAF(Rte_Instance self)
{
  sshTAmbientFilterTAF = GETsshTAmbFiltValEE(self);

  if( ucGetCRdciDtAmbPrewarnCD() < 254)
  {
    if( sshTAmbientFilterTAF == cInvalidTemperatureWord)
    {

      sshTAmbientFilterTAF = (GETscTAinitValEE(self) * 100);
      PUTsshTAmbFiltValEE(self, sshTAmbientFilterTAF);
      ClearBitFahrzeugzustandFZZ( cTAMBIENT_RED);
    }else{
      if( sshTAmbientFilterTAF < (sint16) ((sint16) (GETscTAinitValEE(self) - ucGetCRdciDtAmbPrewarnCD()) * 100))
      {
        SetBitFahrzeugzustandFZZ( cTAMBIENT_RED);
      }else{
        ClearBitFahrzeugzustandFZZ( cTAMBIENT_RED);
      }
    }
  }else{
    PUTsshTAmbFiltValEE(self, cInvalidTemperatureWord);
    PUTucTAmbFiltFactValEE(self, cTAmbientFilterFactorDefaultValue);
    SetBitFahrzeugzustandFZZ( cTAMBIENT_RED);
  }
}

void CyclicTAF(Rte_Instance self)
{
  sint8  scTAinit, scTAmbient, scTAmbFilt;
  uint8  ucTAmbientFactor;

  scTAinit             = GETscTAinitValEE(self);
  sshTAmbientFilterTAF = GETsshTAmbFiltValEE(self);
  scTAmbient           = GETscTAmbValEE(self);
  ucTAmbientFactor     = GETucTAmbFiltFactValEE(self);

  if( ucGetCRdciDtAmbPrewarnCD() < 254)
  {
    if( ucTAmbientFactor > 100)
    {

      ucTAmbientFactor = cTAmbientFilterFactorDefaultValue;
    }

    if( sshTAmbientFilterTAF == cInvalidTemperatureWord)
    {

      sshTAmbientFilterTAF = (scTAinit * 100);

      ClearBitFahrzeugzustandFZZ( cTAMBIENT_RED);
    }else{
      if( scTAmbient < scTAinit)
      {

        if( GETsshTAmbFiltValEE(self) < 0)
        {
          scTAmbFilt = (sint8) ((GETsshTAmbFiltValEE(self) - 50) / 100);
        }else{
          scTAmbFilt = (sint8) ((GETsshTAmbFiltValEE(self) + 50) / 100);
        }

        if( scTAmbient < scTAmbFilt)
        {
          sshTAmbientFilterTAF = (sint16) ((((sint16) ucTAmbientFactor * scTAmbient * 100) + ((sint16) (100 - ucTAmbientFactor) * sshTAmbientFilterTAF)) / 100);

          if( sshTAmbientFilterTAF < ((sint16) (GETscTAinitValEE(self) - (sint16) ucGetCRdciDtAmbPrewarnCD()) * 100))
          {
            SetBitFahrzeugzustandFZZ( cTAMBIENT_RED);
          }else{
            ClearBitFahrzeugzustandFZZ( cTAMBIENT_RED);
          }
        }else{
          sshTAmbientFilterTAF = (sint16) (scTAmbient * 100);

          SetBitFahrzeugzustandFZZ( cTAMBIENT_RED);
        }
      }else{
        sshTAmbientFilterTAF = (scTAmbient * 100);

        ClearBitFahrzeugzustandFZZ( cTAMBIENT_RED);
      }
    }

    PUTsshTAmbFiltValEE(self, sshTAmbientFilterTAF);
  }else{
    SetBitFahrzeugzustandFZZ( cTAMBIENT_RED);
  }
}

