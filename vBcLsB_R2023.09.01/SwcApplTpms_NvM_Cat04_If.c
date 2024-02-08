

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_CcpCrcFilter(uint8 ucData);
void NvM_ReadData_CcpCrcFilter(uint8* ucpData);
void NvM_WriteData_CcpIdFilter(uint8 ucData);
void NvM_ReadData_CcpIdFilter(uint8* ucpData);
void NvM_WriteData_CcpAnzIdFilter(uint8 ucAnzahl);
void NvM_ReadData_CcpAnzIdFilter(uint8* ucpData);
void NvM_WriteData_CcpOnOff(uint8 ucData);
void NvM_ReadData_CcpOnOff(uint8 *ucpData);
void NvM_WriteData_CcpFilterIds(const uint8 ucpData[]);
void NvM_ReadData_CcpFilterIds(uint8 ucpData[]);
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_CcpCrcFilter(uint8 ucData)
{
    WriteMember2Blocks (4,1,&ucData);
}

void NvM_ReadData_CcpCrcFilter(uint8 *ucpData)
{
    ReadBlock2Member (4,1,ucpData );
}

void NvM_WriteData_CcpIdFilter(uint8 ucData)
{
    WriteMember2Blocks (4,2, &ucData);
}

void NvM_ReadData_CcpIdFilter(uint8 *ucpData)
{
    ReadBlock2Member (4,2,ucpData );
}

void NvM_WriteData_CcpAnzIdFilter(uint8 ucAnzahl)
{
    WriteMember2Blocks (4,3,&ucAnzahl );
}

void NvM_ReadData_CcpAnzIdFilter(uint8 *ucpData)
{
    ReadBlock2Member (4,3,ucpData );
}

void NvM_WriteData_CcpOnOff(uint8 ucData)
{
    WriteMember2Blocks (4,4, &ucData);
}

void NvM_ReadData_CcpOnOff(uint8 *ucpData)
{
    ReadBlock2Member (4,4, ucpData );
}

void NvM_WriteData_CcpFilterIds(const uint8 ucpData[])
{
    WriteMember2Blocks (4,5,(uint8 *)ucpData );
}

void NvM_ReadData_CcpFilterIds(uint8 ucpData[])
{
    ReadBlock2Member (4,5,ucpData );
}
#endif

