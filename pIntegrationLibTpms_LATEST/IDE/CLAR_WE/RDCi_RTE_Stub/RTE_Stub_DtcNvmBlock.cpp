/******************************************************************************/
/* File   : RTE_Stub_DtcNvmBlock.cpp                                          */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "RTE_Stub_DtcNvmBlock.h"
#include "RTE_Stub_DemServicesX.h"
#include "Rte_CtApHufTpmsSWC.h"

#include <stdio.h>
#include <string.h>

#include "crc16X.h"

#ifdef _EcuVirtual
#include "EcuVirtual_stdio.h"
#else
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct{
  uint16 Chksum;
  uint16 Version;
  uint8 Data[cMaxErrorCount * sizeof(tRDCiDtcListDef)];
}NvmBlockDtc;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void NVM_ReadAllDTC(void)
{
  FILE* fStream;
  const char filename[] = "NvmRdciDTC.txt";
  const char mode[] = "rb";
  uint32 ulLoop;

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fread( &NvmBlockDtc, sizeof(uint8), sizeof(NvmBlockDtc), fStream);
    fclose( fStream);
  }else{
    NvmBlockDtc.Chksum  = 0xFFFFu;
    NvmBlockDtc.Version = 0xFFFFu;

    for( ulLoop = 0; ulLoop < (cMaxErrorCount * sizeof(tRDCiDtcListDef)); ulLoop++)
    {
      NvmBlockDtc.Data[ulLoop] = 0xFFu;
    }
  }
}

void NVM_WriteAllDTC(void)
{
  FILE* fStream;
  const char filename[] = "NvmRdciDTC.txt";
  const char mode[] = "wb";
  static uint16 ushLastCrc;

  NvmBlockDtc.Version = 0x0100;
  NvmBlockDtc.Chksum = ushCalcCrc16( (uint8 *) &NvmBlockDtc.Data, (uint16) sizeof(NvmBlockDtc.Data));

  if(NvmBlockDtc.Chksum != ushLastCrc)
  {
    if( fopen_s(&fStream, filename, mode) == 0)
    {
      fwrite( (uint8 *) &NvmBlockDtc, sizeof(uint8), sizeof(NvmBlockDtc), fStream);
      fclose( fStream);
    }
    ushLastCrc = NvmBlockDtc.Chksum;
  }
}

uint8 ucNvmDTC_ReadByte( uint32 ulIx)
{
  return NvmBlockDtc.Data[ulIx];
}

void NvmDTC_WriteByte( uint32 ulIx, uint8 ucNvmByte)
{
  if(ulIx < sizeof(NvmBlockDtc.Data))
  {
    NvmBlockDtc.Data[ulIx] = ucNvmByte;
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

