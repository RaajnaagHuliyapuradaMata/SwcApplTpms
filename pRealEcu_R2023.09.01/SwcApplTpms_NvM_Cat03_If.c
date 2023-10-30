

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "WallocX.hpp"

//
//void NvM3_PUTucVarCodOffroadPlacardPress(uint8 ucData)
//{
//  WriteMember2Blocks(CATEGORY3, INDEX8, &ucData);
//}
//
//
//uint8 NvM3_GETucVarCodOffroadPlacardPress(void)
//{
//  uint8 l_ucaData[NVM_CAT03_IDX08_REAL_SIZE];
//
//  l_ucaData[0] = 0;
//
//  ReadBlock2Member(CATEGORY3, INDEX8, l_ucaData);
//
//  return (l_ucaData[0]);
//}

//RST NVM ok

void NvM3_PUTucAutolocationFailedCounter(uint8 ucCounterValue)
{
  WriteMember2Blocks(CATEGORY3, INDEX5, &ucCounterValue);
}

uint8 NvM3_GETucAutolocationFailedCounter(void){
  uint8 l_ucaData[NVM_CAT03_IDX05_REAL_SIZE];

  l_ucaData[0] = 0;

  ReadBlock2Member(CATEGORY3, INDEX5, l_ucaData);

  return (l_ucaData[0]);
}

//
//void NvM3_PUTucVarCodTemperatureWarningThresEE(sint8 scData)
//{
//  WriteMember2Blocks(CATEGORY3, INDEX6, ((uint8 *) &scData));
//}
//
//
//sint8 NvM3_GETucVarCodTemperatureWarningThresEE(void)
//{
//  uint8 l_ucaData[NVM_CAT03_IDX06_REAL_SIZE];
//
//  l_ucaData[0] = 0;
//
//  ReadBlock2Member(CATEGORY3, INDEX6, l_ucaData);
//
//  return ((sint8) (l_ucaData[0]));
//}

//
//void NvM3_PUTucVarCodHighPressResetThresEE(uint8 ucData)
//{
//  WriteMember2Blocks(CATEGORY3,INDEX5, &ucData);
//}
//
//
//uint8 NvM3_GETucVarCodHighPressResetThresEE(void)
//{
//  uint8 l_ucaData[NVM_CAT03_IDX05_REAL_SIZE];
//
//  l_ucaData[0] = 0;
//
//  ReadBlock2Member (CATEGORY3,INDEX5,l_ucaData );
//  return(l_ucaData[0]);
//}

void NvM3_PUTHistoryIdsInEE(uint32 *ulData)
{
  WriteMember2Blocks(CATEGORY3, cHistorySet1, (uint8*)ulData);
}

void NvM3_GETHistoryIdsFromEE(uint32 *ulData)
{
  ReadBlock2Member(CATEGORY3, cHistorySet1, (uint8*)ulData );
}

void NvM3_PUTHistoryWPInEE(uint8 *ucData)
{
  WriteMember2Blocks(CATEGORY3, cHistoryWPSet1, ucData);
}

void NvM3_GETHistoryWPFromEE(uint8 *ucData)
{
  ReadBlock2Member (CATEGORY3, cHistoryWPSet1, ucData );
}

void NvM3_PUTWAParametersInEE(WAParameter sWheelAllocParamData)
{
  WriteMember2Blocks(CATEGORY3, cWAParameter, (uint8*)&sWheelAllocParamData);
}

void NvM3_GETWAParametersFromEE(WAParameter *sWheelAllocParamData)
{
  ReadBlock2Member (CATEGORY3, cWAParameter, (uint8*)sWheelAllocParamData);
}

void NvM3_PUTABSTicksInEE(WAABSTicksInOneRevolution sABSTicks)
{
  WriteMember2Blocks(CATEGORY3, cWAABSTicksInOneRevolution, (uint8*)&sABSTicks);
}

void NvM3_GETABSTicksFromEE(WAABSTicksInOneRevolution *sABSTicks)
{
  ReadBlock2Member(CATEGORY3, cWAABSTicksInOneRevolution, (uint8*)sABSTicks);
}

void GetWADataEE(unsigned char ucId, unsigned char *pRamAdr)
{
  if((ucId>0) && (ucId<5)) // currently WA uses 3 categories: 1=IDs,2=WPs,3=parameters,4=ABSticks
  {
    ReadBlock2Member (CATEGORY3,ucId , pRamAdr);  // WA = Category 3 = const
  }
}

void PutWADataEE(unsigned char ucId, unsigned char *pRamAdr)
{
  if((ucId>0) && (ucId<5)) // currently WA uses 4 categories: 1=IDs,2=WPs,3=parameters,4=ABSticks
  {
    WriteMember2Blocks (CATEGORY3, ucId,pRamAdr);  // WA = Category 3 = const
  }
}

