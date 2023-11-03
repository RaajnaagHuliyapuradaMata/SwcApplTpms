

#include "RTE_Stub_Ccm.h"

uint16 u16CCWritePos;
uint16 u16CCReadPos;

ImpTypeRecCcm_DISP_CC_BYPA_00 tCC_BYPA_00[CC_DATA_QUEUE_LENGTH];

FUNC(Std_ReturnType, RTE_CODE) Stub_Rte_Send_Ccm( P2CONST(ImpTypeRecCcm_DISP_CC_BYPA_00, AUTOMATIC, RTE_CTAPHUFTPMSSWC_APPL_DATA) data)
{

  static bool bLockPosition = false;
  uint16 queueFillStatus = 0;
  uint8 ucRet;

  if(0xffff == u16CCWritePos)
  {
    u16CCWritePos = 0;
    bLockPosition = false;
    queueFillStatus = 1;
  }
  else
  {
    if( ((u16CCWritePos + 1) % CC_DATA_QUEUE_LENGTH) == u16CCReadPos)
    {

      bLockPosition = true;
      queueFillStatus = 10;
    }
    else
    {

      u16CCWritePos++;
      u16CCWritePos %= CC_DATA_QUEUE_LENGTH;
      bLockPosition = false;

      if(u16CCWritePos > u16CCReadPos)
      {
        queueFillStatus = u16CCWritePos - u16CCReadPos;
      }
      else
      {
        queueFillStatus = 10 - (u16CCReadPos - u16CCWritePos);
      }
    }
  }

  if(false == bLockPosition)
  {

    tCC_BYPA_00[u16CCWritePos] = *data;
  }

  if( queueFillStatus > 1)
  {

    ucRet = RTE_E_OK;
  }else{
    ucRet = RTE_E_OK;
  }

  return ucRet;
}

uint8 Stub_GetCcmData( ImpTypeRecCcm_DISP_CC_BYPA_00 *ptOutputData)
{
  uint8 ucReturnValue = 0xFF;
  bool bReadQueueData = true;

  if( u16CCWritePos != 0xFFFF)
  {
    if( u16CCReadPos == 0xFFFF)
    {
      u16CCReadPos = 0;
    }
    else
    {
      if( u16CCReadPos == u16CCWritePos)
      {

        bReadQueueData = false;
      }
      else
      {

        u16CCReadPos++;
        u16CCReadPos %= CC_DATA_QUEUE_LENGTH;
      }
    }

    if( bReadQueueData == true)
    {
      *ptOutputData = tCC_BYPA_00[u16CCReadPos];
      ucReturnValue = 0x00;
    }
  }
  return ucReturnValue;

}

