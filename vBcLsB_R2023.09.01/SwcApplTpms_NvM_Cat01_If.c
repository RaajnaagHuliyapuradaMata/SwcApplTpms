

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"

uint8 GETucResetWarnPressRefEE(uint8 ucIndex)
{
   uint8 LocalCnt;
   uint8  l_ucaData   [NVM_CAT01_IDX07_REAL_SIZE];
   ucIndex = (ucIndex < 5) ? ucIndex : (uint8) 4;

   for(LocalCnt=0;LocalCnt<NVM_CAT01_IDX07_REAL_SIZE; LocalCnt++)
   {
      l_ucaData[LocalCnt] = 0;
   }

    ReadBlock2Member (1,7,l_ucaData );

    return(l_ucaData[ucIndex]);
}

void PUTucResetWarnPressRefEE(uint8 ucIndex, uint8 ucData)
{
   uint8  l_ucaData   [NVM_CAT01_IDX07_REAL_SIZE];
   ucIndex = (ucIndex < 5) ? ucIndex : (uint8) 4;

    ReadBlock2Member (1,7,l_ucaData );

    l_ucaData[ucIndex] = ucData;

    WriteMember2Blocks (1,7,l_ucaData );
}

void PUTucPatmoEE(uint8 ucData)
{
    WriteMember2Blocks(1,8, &ucData);
}

uint8 GETucPatmoEE(void){
   uint8  l_ucaData   [NVM_CAT01_IDX08_REAL_SIZE];

    l_ucaData[0] = 0;

    ReadBlock2Member (1,8,l_ucaData );
    return(l_ucaData[0]);
}

// RST NVM ok

void PUTscAdaptedTrefEE(sint8 scData)
{
    WriteMember2Blocks(1,9,(uint8*)(&scData));
}

sint8 GETscAdaptedTrefEE(void){
   sint8  l_scaData   [NVM_CAT01_IDX09_REAL_SIZE];

    l_scaData[0] = 0;

    ReadBlock2Member (1,9,(uint8*)(l_scaData));
    return(l_scaData[0]);
}

//
//void PUTucVarCodPlacardPressEE(uint8 ucData)
//{
//    WriteMember2Blocks(1,9, &ucData);
//
//}
//
//
//uint8 GETucVarCodPlacardPressEE (void)
//{
//    uint8  l_ucaData   [NVM_CAT01_IDX09_REAL_SIZE];
//
//    l_ucaData[0] = 0;
//
//    ReadBlock2Member (1,9,l_ucaData );
//    return(l_ucaData[0]);
//
//}
//
//
//void PUTucVarCodMinPressThresEE(uint8 ucData)
//{
//    WriteMember2Blocks(1,10, &ucData);
//
//}
//
//
//uint8 GETucVarCodMinPressThresEE(void)
//{
//    uint8  l_ucaData   [NVM_CAT01_IDX10_REAL_SIZE];
//
//    l_ucaData[0] = 0;
//
//    ReadBlock2Member (1,10,l_ucaData );
//    return(l_ucaData[0]);
//
//}
//
//
//void PUTucVarCodHighPressThresEE(uint8 ucData)
//{
//    WriteMember2Blocks(1,11, &ucData);
//}
//
//
//uint8 GETucVarCodHighPressThresEE(void)
//{
//    uint8  l_ucaData   [NVM_CAT01_IDX11_REAL_SIZE];
//
//    l_ucaData[0] = 0;
//
//    ReadBlock2Member (1,11,l_ucaData );
//    return(l_ucaData[0]);
//
//}
//
//
//void PUTucVarCodAxImbSetThresEE(uint8 ucData)
//{
//    WriteMember2Blocks(1,12, &ucData);
//}
//
//
//uint8 GETucVarCodAxImbSetThresEE(void)
//{
//    uint8  l_ucaData   [NVM_CAT01_IDX12_REAL_SIZE];
//
//    l_ucaData[0] = 0;
//
//    ReadBlock2Member (1,12,l_ucaData );
//    return(l_ucaData[0]);
//
//}
//
//
//void PUTucVarCodAxImbResThresEE(uint8 ucData)
//{
//    WriteMember2Blocks(1,13, &ucData);
//}
//
//
//uint8 GETucVarCodAxImbResThresEE(void)
//{
//    uint8  l_ucaData   [NVM_CAT01_IDX13_REAL_SIZE];
//
//    l_ucaData[0] = 0;
//
//    ReadBlock2Member (1,13,l_ucaData );
//    return(l_ucaData[0]);
//
//}

