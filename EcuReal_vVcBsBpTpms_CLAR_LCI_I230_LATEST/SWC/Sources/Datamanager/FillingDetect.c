

#include "FillingDetect.h"

#include "EeCommonBlockX.h"
#include "EeWarnStatusBlockX.h"
#include "state_bzX.h"
#include "state_fzzX.h"
#include "state_zkX.h"
#include "WnTypePar.h"
#include "HS_KalibrierereignisX.h"
#include "EeErfsBlockX.h"

void StartFillingDetectionFID(Rte_Instance self)
{
  uint8 i;
  uint8 ucStartFd = 0;
  uint16 ushSlope;

  if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE)
  {

    if(GETucFilDetActiveEE(self) == 0)
    {

      for (i=0; i<cAnzRad; i++)
      {
        if(GETucLastWuPressureEE(self, i) != cInvalidREpressure)
        {
          ucStartFd++;
        }
        if(GETscLastWuTemperatureEE(self, i) != cInvalidREtemperature)
        {
          ucStartFd++;
        }
      }

      if(ucStartFd == 8)
      {
        for (i=0; i<cAnzRad; i++)
        {

          ushSlope = ushMIso( GETucLastWuPressureEE(self, i), GETscLastWuTemperatureEE(self, i), GETucPAmbValEE(self));
          PUTushFilDetMIsoEE(self, ushSlope, i);
        }
        PUTucFilDetActiveEE(self, 1);
      }
    }
  }
}

boolean ProcessFillingDetectionFID(Rte_Instance self, uint8 ucSlot)
{
  uint8   i;
  sint8   scTakt;
  uint8   ucPakt;
  uint8   ucPerwartet;
  sint8   scPdiff;
  uint16  ushSteigung;
  boolean bRetVal = FALSE;
  uint8   ucSum;

  if(ucGetIdChangedBitsZK() > 0)
  {
    bRetVal = FALSE;
  }
  else
  {
    if(GETucFilDetActiveEE(self) > 0)
    {
      if(bGetBitBetriebszustandBZ(cER_FINISH) == TRUE)
      {
        if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT) == TRUE)
        {

          scTakt = GETscLastWuTemperatureEE(self, ucSlot);

          ushSteigung = GETushFilDetMIsoEE(self, ucSlot);

          ucPerwartet = ucPfT(ushSteigung, scTakt, GETucPAmbValEE(self));

          ucPakt = GETucLastWuPressureEE(self, ucSlot);

          scPdiff = (sint8)(ucPakt - ucPerwartet);

          PUTucFilDetRecFlag(self, 1, ucSlot);

          if(scPdiff >= 4)
          {
            for (i=0; i<cAnzRad; i++)
            {
              PUTucFilDetRecFlag(self, 0, i);
            }
            PUTucFilDetActiveEE(self, 0);
            bRetVal = TRUE;
          }
          else
          {

            ucSum = 0;
            for (i=0; i<cAnzRad; i++)
            {
              ucSum += GETucFilDetRecFlag(self, i);
            }

            if(ucSum == 4)
            {
              for (i=0; i<cAnzRad; i++)
              {
                PUTucFilDetRecFlag(self, 0, i);
              }
              PUTucFilDetActiveEE(self, 0);
            }
            bRetVal = FALSE;
          }
        }
      }
    }
  }
  return bRetVal;
}
