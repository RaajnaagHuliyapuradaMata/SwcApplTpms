

#include "SteuernRadelektronikVorgeben.h"

#include "WAllocX.h"
#include "uswarn_ifX.h"
#include "walloc_managerX.h"
#include "datamanagerX.h"
#include "state_bzX.h"
#include "state_zkX.h"
#include "WuMonitoringX.h"

#include "EeErfsBlockX.h"
#include "EeCommonBlockX.h"
#include "EeHistoryBlockX.h"
#include "EeWarnstatusBlockX.h"

#include "StatusbarX.h"
#include "InitializationX.h"
#include "SeasRcpAdjX.h"
#include "HS_KalibrierereignisX.h"

uint8 ucPutSteuernRadelektronikVorgebenDS( Rte_Instance self, uint32 ulReId, uint8 ucRadPos)
{
  uint8 ucRet;
  uint8 ucLoop;

  if( ucRadPos < cMaxLR)
  {
    if( ulReId == 0xFFFFFFFFu)
    {

      ucRet = 0xff;
    }
    else
    {
      ucRet = ucSetHistoryID( self, ulReId, ucRadPos);

      if( ucRet == 0)
      {
        ucRet = 0xff;
      }
      else
      {
        SetHistoryChangeBitsDM( self);
        InitBZ( self, FALSE);
        if(bGetBitBetriebszustandBZ(cZUGEORDNET) == TRUE)
        {
          if(GETTyreSelectionActiveEE(self) != TRUE)
          {
            SetBitBetriebszustandBZ(cZO_FINISH);
          }
          (void)ucSetAutolocErrorStatusWUM( self, cAUTOLOC_SUCCESSFUL);
        }
        if(bGetBitBetriebszustandBZ(cEIGENRAD) == TRUE)
        {
          if(GETTyreSelectionActiveEE(self) != TRUE)
          {
            SetBitBetriebszustandBZ(cER_FINISH);
          }
          SetAutoLearnErrorStatusWUM( self, cAUTOLEARN_SUCCESSFUL);
        }
        PUTLastLocStateEE( self, ushGetBetriebszustandBZ(cBZ_ALLE_BITS));
        ResetWUM( self, (ucRet & 0x0f), cWithoutLowBat, cWithoutWuRelatedDtcs);

        if( ulReId == (uint32) 0)
        {

          (void)ucSetPminFzgAsSetPressureUSWIF( self);

          ResetWUM( self, cAllSlots, cWithLowBat, cWithWuRelatedDtcs);
          (void)ucSetAutolocErrorStatusWUM( self, cAUTOLOC_SUCCESSFUL);
          PUTTyreSelectionBckgrdEE( self, TRUE);
          PUTTyreSelectionActiveEE( self, TRUE);
          SetCalibrationRootCauseDS( self, cCalByDiag);
          StartSBR( self);
          StartSRA( self);
          StartLearnLocateWAM( self);
          ClearLastReceivedReDataArraysDM();
          for (ucLoop = 0; ucLoop < cMaxLR; ucLoop++){
            PUTucLastWuPressureEE( self, cInvalidREpressure, ucLoop);
            PUTscLastWuTemperatureEE( self, cInvalidREtemperature, ucLoop);
            PUTucWheelSensorStatusToNvmMirrorEE( self, cRE_STATUS_NOT_REC, ucLoop);
            PUTucLastTelegramTypeToNvmMirrorEE( self, cInvalidTelType, ucLoop);
            PUTucLastSNRToNvmMirrorEE( self, cInvalidSignalToNoiseRatio, ucLoop);
            PUTushLastPalStatusEE( self, cInvalidRePalStatusMdb, ucLoop);
            PUTucTimeSinceLastRecEventToNvmMirrorEE( self, 0, ucLoop);
            PUTucLastBatteryStateToNvmMirrorEE( self, cInvalidBatteryLevel, ucLoop);
          }

          PUTucFBD4CountEE(self, 1);
        }

        ResetWarningsUSWIF( self);

        PUTucLastPosChangedInformationToNvmMirrorEE(self, ucGetIdChangedBitsZK() | ucGetWpChangedBitsZK());

        ucRet = 0x00;
      }
    }
  }
  else
  {

    ucRet = 0xff;
  }

  return ucRet;
}

