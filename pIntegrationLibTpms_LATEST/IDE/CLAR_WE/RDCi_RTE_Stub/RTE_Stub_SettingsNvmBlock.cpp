# ifdef __cplusplus
  extern "C"
  {
# endif

#ifdef __cplusplus
  }
#endif

/******************************************************************************/
/* File   : RTE_Stub_SettingsNvmBlock.cpp                                     */
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
#include "RTE_Stub_SettingsNvmBlock.h"
#include <stdio.h>

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

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
static const tRteStubSettingsDataDecl tRteStubSettingsDataROM = {
      10
   ,  true
   ,  10
   ,  100
   ,  10
   ,  7
   ,  10
   ,  true
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  false
   ,  true
   ,  false
   ,  false
   ,  true
   ,  true
   ,  false
   ,  false
   ,  false
};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
tRteStubSettingsDataDecl tRteStubSettingsDataRAM;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void NVM_ReadRteStubSettings(void){
  FILE* fStream;
  const char filename[] = "RteStubSettings.txt";
  const char mode[] = "rb";
  if( fopen_s(&fStream, filename, mode) == 0){
    fread( &tRteStubSettingsDataRAM, sizeof(uint8), sizeof(tRteStubSettingsDataRAM), fStream);
    fclose( fStream);
  }else{
    tRteStubSettingsDataRAM = tRteStubSettingsDataROM;
  }
}

void NVM_WriteRteStubSettings(void)
{
  FILE* fStream;
  const char filename[] = "RteStubSettings.txt";
  const char mode[] = "wb";

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fwrite( (uint8 *) &tRteStubSettingsDataRAM, sizeof(uint8), sizeof(tRteStubSettingsDataRAM), fStream);
    fclose( fStream);
  }
}

void NVM_SetDefaultRteStubSettings(void)
{
  tRteStubSettingsDataRAM = tRteStubSettingsDataROM;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

