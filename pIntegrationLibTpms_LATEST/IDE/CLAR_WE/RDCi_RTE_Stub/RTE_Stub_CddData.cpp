

#include "RTE_Stub_CddData.h"

#include "RTE_Stub_Dialog.h"
#include "Logging.h"
#include "crc16X.h"

#ifdef _EcuVirtual
#else
using namespace RDCi;
#endif

tCddAbsData CddAbsData[ABS_DATA_QUEUE_LENGTH];
tCddRdcData CddRdcData[RDC_DATA_QUEUE_LENGTH];

uint16 u16AbsQueueWritePos = 0xFFFF;
uint16 u16RdcQueueWritePos = 0xFFFF;
uint16 u16AbsQueueReadPos  = 0xFFFF;
uint16 u16RdcQueueReadPos  = 0xFFFF;

#ifdef _EcuVirtual
#else
static uint16 ushWheelUnitPressureValue = 0xFFFF;
static sint16 shWheelUnitTemperatureValue = 0x7FFF;
#endif

static uint32 ulRdcTimerTicks = 0;
static uint32 ulRdcRfWriteCounter = 0;
static uint32 ulRdcRfReadCounter = 0;

static RdcDataType tRdcData[cMaxReElements];

static uint16 ushRecEvent[cMaxReElements] = { 0, 0, 0, 0, 0, 0 };

uint16 PutCddAbsData( tCddAbsData* data)
{
  static bool bLockPosition = false;
  uint16 queueFillStatus = 0;

  if(0xffff == u16AbsQueueWritePos)
  {
    u16AbsQueueWritePos = 0;
    bLockPosition = false;
    queueFillStatus = 1;
    u16AbsQueueReadPos = ABS_DATA_QUEUE_LENGTH - 1;
  }
  else
  {
    if( ((u16AbsQueueWritePos + 1) % ABS_DATA_QUEUE_LENGTH) == u16AbsQueueReadPos)
    {

      bLockPosition = true;
      queueFillStatus = ABS_DATA_QUEUE_LENGTH;
    }
    else
    {

      u16AbsQueueWritePos++;
      u16AbsQueueWritePos %= ABS_DATA_QUEUE_LENGTH;
      bLockPosition = false;

      if(u16AbsQueueWritePos > u16AbsQueueReadPos)
      {
        queueFillStatus = u16AbsQueueWritePos - u16AbsQueueReadPos;
      }
      else
      {
        queueFillStatus = ABS_DATA_QUEUE_LENGTH - (u16AbsQueueReadPos - u16AbsQueueWritePos);
      }
    }
  }

  if(false == bLockPosition)
  {

    CddAbsData[u16AbsQueueWritePos] = *data;
  }

  return (uint16) queueFillStatus;
}

uint16 PutCddRdcData( tCddRdcData * data)
{
  static bool bLockPosition = false;
  uint16 queueFillStatus = 0;

  if( u16RdcQueueWritePos == 0xFFFF)
  {
    u16RdcQueueWritePos = 0;
    bLockPosition = false;
    queueFillStatus = 1;
    u16RdcQueueReadPos = RDC_DATA_QUEUE_LENGTH - 1;
  }
  else
  {
    if(((u16RdcQueueWritePos + 1) % RDC_DATA_QUEUE_LENGTH) == u16RdcQueueReadPos)
    {

      bLockPosition = true;
      queueFillStatus = RDC_DATA_QUEUE_LENGTH;
    }
    else
    {

      u16RdcQueueWritePos++;
      u16RdcQueueWritePos %= RDC_DATA_QUEUE_LENGTH;
      bLockPosition = false;

      if( u16RdcQueueReadPos == 0xFFFF)
      {
        queueFillStatus = u16RdcQueueWritePos;
      }else{
        if(u16RdcQueueWritePos > u16RdcQueueReadPos)
        {
          queueFillStatus = u16RdcQueueWritePos - u16RdcQueueReadPos;
        }
        else
        {
          queueFillStatus = RDC_DATA_QUEUE_LENGTH - (u16RdcQueueReadPos - u16RdcQueueWritePos);
        }
      }
    }
  }

  if( bLockPosition == false)
  {

    uint8 aucBuffer[15];
    uint8 ucLength;

    aucBuffer[0] = data->PCKG_ID;
    aucBuffer[1] = (data->SUPP_ID << 4) | (uint8)(((data->TYR_ID & 0x0f000000) >> 24));
    aucBuffer[2] = (uint8)((data->TYR_ID & 0x00ff0000) >> 16);
    aucBuffer[3] = (uint8)((data->TYR_ID & 0x0000ff00) >> 8);
    aucBuffer[4] = (uint8)(data->TYR_ID & 0x000000ff);
    aucBuffer[5] = data->RDC_DT_1;
    aucBuffer[6] = data->RDC_DT_2;
    aucBuffer[7] = data->RDC_DT_3;
    aucBuffer[8] = data->RDC_DT_4;
    aucBuffer[9] = data->RDC_DT_5;

    switch (data->PCKG_ID)
    {
      case cTelTypeAK35def:
      case cTelTypeAK35defLMA:
        ucLength = 7;
      break;

      case cTelTypeBeruMed:
      case cTelTypeG4Standard:
        ucLength = 8;
      break;

      case cTelTypeSELPAL:
      case cTelTypeSELPAL1:
      case cTelTypeContiFP:
      case cTelTypeBeruLong:
      case cTelTypeTyreDataOE2:
      case cTelTypeTyreStatus:
        ucLength = 10;
      break;

      case cTelTypeTyreDataOE1:
      case cTelTypeTyreDIM:
        ucLength = 11;
      break;

      case cTelTypeAlive:
        ucLength = 0;
      break;

      default:
        ucLength = 0;
      break;
    }

    if( ((data->RDC_DT_8 == 0) || (data->RDC_DT_8 == 0xff)) && (ucLength > 0))
    {
      data->RDC_DT_8 = ucCalcCrc8(aucBuffer, ucLength);
    }

    CddRdcData[u16RdcQueueWritePos] = *data;

    PutRfDataToBufferLOG( data);

    ulRdcRfWriteCounter++;
  }

  return (uint16) queueFillStatus;
}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Receive_CddAbsData( P2VAR(ImpTypeRecCddAbsData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) data)
{
  uint8 ucReturnValue = 0xFF;
  bool bReadQueueData = true;

  if( u16AbsQueueWritePos != 0xFFFF)
  {

    {
      if( u16AbsQueueReadPos == u16AbsQueueWritePos)
      {

        bReadQueueData = false;
      }
      else
      {

        u16AbsQueueReadPos++;
        u16AbsQueueReadPos %= ABS_DATA_QUEUE_LENGTH;
      }
    }

    if( bReadQueueData == true)
    {
      *data = CddAbsData[u16AbsQueueReadPos];
      ucReturnValue = 0x00;
    }
  }
  return ucReturnValue;

}

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Receive_CddRdcData( P2VAR(ImpTypeRecCddRdcData, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_VAR) data)
{
  uint8 ucReturnValue = 0xFF;
  bool  bReadQueueData = true;

  if( u16RdcQueueWritePos != 0xFFFF)
  {

    {
      if( u16RdcQueueReadPos == u16RdcQueueWritePos)
      {

        bReadQueueData = false;
      }
      else
      {

        u16RdcQueueReadPos++;
        u16RdcQueueReadPos %= RDC_DATA_QUEUE_LENGTH;
      }
    }

    if( bReadQueueData == true)
    {
      *data = CddRdcData[u16RdcQueueReadPos];

      ulRdcRfReadCounter++;

      ucReturnValue = 0x00;
    }
  }

  return ucReturnValue;
}

void PutTimerTicks( uint32 ulTimerTicks)
{
  ulRdcTimerTicks = ulTimerTicks;
}

uint32 ulGetTimerTicks(void)
{
  return ulRdcTimerTicks;
}

uint32 ulGetTRdcRfWriteCounter(void)
{
  return ulRdcRfWriteCounter;
}

uint32 ulGetTRdcRfReadCounter(void)
{
  return ulRdcRfReadCounter;
}

void InitRecCddRdcData(void)
{
  uint8 ucLoop;

  for( ucLoop = 0; ucLoop < cMaxReElements; ucLoop++)
  {
    ushRecEvent[ucLoop] = 0;

    switch( ucLoop)
    {
      case cRecEleIx_Slot0:
      case cRecEleIx_Slot1:
      case cRecEleIx_Slot2:
      case cRecEleIx_Slot3:

        tRdcData[ucLoop].tRecCddRdcData.RDC_MES_TSTMP       = (0x00000000u * 1000) + (0x000F4240u / 1000000);

        tRdcData[ucLoop].tRecCddRdcData.SUPP_ID             = (uint8) ((ulGetIDOfColWAL( ucLoop) & 0xf0000000u) >> 28);

        tRdcData[ucLoop].tRecCddRdcData.TYR_ID              = (long) (ulGetIDOfColWAL( ucLoop) & 0x0fffffffu);

        if( ucGetRePckgIdDM( ucLoop) == cInvalidTelType)
        {
          tRdcData[ucLoop].tRecCddRdcData.PCKG_ID           = cTelTypeSELPAL;
        }else{
          tRdcData[ucLoop].tRecCddRdcData.PCKG_ID           = ucGetRePckgIdDM( ucLoop);
        }

        if( GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) == cInvalidREpressure)
        {
          tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1          = ((80 + GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC)) - 38);
        }else{
          if( ((uint16) GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) + (uint16) GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC)) < 40)
          {

            tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1        = cReAkPresUnderflow;
          }else if( (((uint16) GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) + (uint16) GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC)) - 40) > (uint16) 252)
          {

            tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1        = cReAkPresOverflow;
          }else{
            tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1        = (GETucLastWuPressureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) + GETucPAmbValEE( Rte_Inst_CtApHufTpmsSWC)) - 38;
          }
        }

        if( GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) == cInvalidREtemperature)
        {
          tRdcData[ucLoop].tRecCddRdcData.RDC_DT_2          = 20 + 52;
        }else{
          tRdcData[ucLoop].tRecCddRdcData.RDC_DT_2          = (uint8) GETscLastWuTemperatureEE( Rte_Inst_CtApHufTpmsSWC, ucLoop) + 52;
        }

        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_3            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_4            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_5            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_6            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_7            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_8            = 0x00u;

        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_1   = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_2   = 0x00u;

        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_LO   = 0x000F4240u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_HI   = 0x00000000u;
      break;

      case cRecEleIx_FR:
      case cRecEleIx_RID:
        tRdcData[ucLoop].tRecCddRdcData.RDC_MES_TSTMP       = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.SUPP_ID             = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.TYR_ID              = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.PCKG_ID             = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_2            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_3            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_4            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_5            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_6            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_7            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_8            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_1   = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_2   = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_LO   = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_HI   = 0x00000000u;
      break;

      case cRecEleIx_Alive:
        tRdcData[ucLoop].tRecCddRdcData.RDC_MES_TSTMP       = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.SUPP_ID             = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.TYR_ID              = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.PCKG_ID             = cTelTypeAlive;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_1            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_2            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_3            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_4            = 0x25;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_5            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_6            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_7            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_DT_8            = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_1   = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.ALIV_RDC_DT_PCK_2   = 0x00u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_LO   = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.RDC_SYNC_TSTMP_HI   = 0x00000000u;
        tRdcData[ucLoop].tRecCddRdcData.DP_NO               = 0x34;
      break;
    }
  }
}

RdcDataType * ptGetRdcDataPtr(uint8 ucRe)
{
  if(ucRe < cMaxReElements)
  {
    return &tRdcData[ucRe];
  }
  else {
    return NULL;
  }
}

ImpTypeRecCddRdcData * ptGetRecCddRdcDataPtr( uint8 ucRe)
{
  if( ucRe < cMaxReElements)
  {
    return &tRdcData[ucRe].tRecCddRdcData;
  }else{
    return NULL;
  }
}

void PutRecCddRdcData( uint8 ucRe)
{

  ImpTypeRecCddRdcData * ptData;

  ptData = ptGetRecCddRdcDataPtr( ucRe);

  ushRecEvent[ucRe]++;

  if( PutCddRdcData( ptData) == (uint16) false)
  {

  }
}

uint16 ushGetTelCountCddRdcDataPtr( uint8 ucRe)
{
  return ushRecEvent[ucRe];
}

uint8 ucGetNextValidAliveCounter( uint8 ucAliveStartValue)
{
  uint8 ucAliveCounter;

  if( ucAliveStartValue < 0x0E)
  {
    ucAliveCounter = ucAliveStartValue + 1;
  }else{

    ucAliveCounter = 0;
  }

  return ucAliveCounter;
}
