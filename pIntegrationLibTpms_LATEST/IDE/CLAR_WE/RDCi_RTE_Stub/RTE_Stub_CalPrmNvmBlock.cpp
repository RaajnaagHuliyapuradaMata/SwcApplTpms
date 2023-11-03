/******************************************************************************/
/* File   : RTE_Stub_CalPrmNvmBlock.cpp                                       */
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
#include "RTE_Stub_CalPrmNvmBlock.h"
#include "Rte_CtApHufTpmsSWC.h"

#include <stdio.h>
#include <string.h>

#include "crc16X.h"

#include "CodingDataX.h"

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
static const tCodingDataDeclCD tCodingDataRomCD[2] = {
                                                        {
                                                               TRUE,
                                                              FALSE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                              FALSE,
                                                               TRUE,
                                                               TRUE,
                                                              FALSE,
                                                         cMARKET_EU,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                                  3,
                                                                  0,
                                                                 20,
                                                                 17,
                                                                 25,
                                                                 20,
                                                                 60,
                                                                 80,
                                                                 80,
                                                                 32,
                                                                 32,
                                                                  2,
                                                                254,
                                                                  6,
                                                                  0,
                                                                  0,
                                                                 40,
                                                                120,
                                                                 28,
                                                                  6,
                                                                  4,
                                                                  3,
                                                                  4,
                                                               TRUE,
                                                              FALSE,
                                                                  1,
                                                               TRUE,
                                                                  8,
                                                               TRUE,
                                                                103,
                                                                 87,
                                                                 51,
                                                                116,
                                                                  0,
                                                                267,
                                                                  1,
                                                                 10,
                                                               -100,
                                                               -100,
                                                                  6,
                                                                 15,
                                                                 17,
                                                                 20,
                                                                  9,
                                                                 11,
                                                                 20,
                                                                 25
                                                        },
                                                        {
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                              FALSE,
                                                               TRUE,
                                                               TRUE,
                                                              FALSE,
                                                         cMARKET_US,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                               TRUE,
                                                                  3,
                                                                  0,
                                                                 25,
                                                                 22,
                                                                 25,
                                                                 20,
                                                                 60,
                                                                 80,
                                                                 80,
                                                                 32,
                                                                 32,
                                                                  2,
                                                                254,
                                                                  6,
                                                                  0,
                                                                  0,
                                                                 40,
                                                                120,
                                                                 28,
                                                                  3,
                                                                  1,
                                                                 14,
                                                                  7,
                                                               TRUE,
                                                              FALSE,
                                                                  1,
                                                               TRUE,
                                                                  8,
                                                               TRUE,
                                                                103,
                                                                 57,
                                                                 51,
                                                                116,
                                                                  0,
                                                                267,
                                                                  1,
                                                                 10,
                                                               -100,
                                                               -100,
                                                                  6,
                                                                 15,
                                                                 22,
                                                                 20,
                                                                  6,
                                                                  8,
                                                                 25,
                                                                 25
                                                        }
                                                  };

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static Std_ReturnType NvmDscCodierdatenAllgemein_ReadBlock(void);
static Std_ReturnType NvmDscCodierdatenAllgemein_WriteBlock(void);
static Std_ReturnType NvmDscCodierdatenRDCi_ReadBlock(void);
static Std_ReturnType NvmDscCodierdatenRDCi_WriteBlock(void);

struct{
  boolean bValidData;
  uint16  Chksum;
  uint16  Version;
  uint8   Data[50];
}NvmBlockDscCodierdatenRDCi[2];

struct{
  uint16 Chksum;
  uint16 Version;
  uint8 Data[61];
}NvmBlockDscCodierdatenAllgemein;

# ifdef __cplusplus
  extern "C"
  {
# endif

#ifdef __cplusplus
  }
#endif

void NVM_ReadAllCalPrmBlocks(void)
{
  (void) NvmDscCodierdatenAllgemein_ReadBlock();
  (void) NvmDscCodierdatenRDCi_ReadBlock();
}

void NVM_WriteAllCalPrmBlocks(void)
{
  NvmBlockDscCodierdatenAllgemein.Version = 0x0100;
  NvmBlockDscCodierdatenAllgemein.Chksum = ushCalcCrc16( (uint8 *) &NvmBlockDscCodierdatenAllgemein.Data, (uint16) sizeof(NvmBlockDscCodierdatenAllgemein.Data));
  (void) NvmDscCodierdatenAllgemein_WriteBlock();

  NvmBlockDscCodierdatenRDCi[EU].Version = 0x0200;
  NvmBlockDscCodierdatenRDCi[EU].Chksum = ushCalcCrc16( (uint8 *) &NvmBlockDscCodierdatenRDCi[EU].Data, (uint16) sizeof(NvmBlockDscCodierdatenRDCi[EU].Data));

  NvmBlockDscCodierdatenRDCi[US].Version = 0x0200;
  NvmBlockDscCodierdatenRDCi[US].Chksum = ushCalcCrc16( (uint8 *) &NvmBlockDscCodierdatenRDCi[US].Data, (uint16) sizeof(NvmBlockDscCodierdatenRDCi[US].Data));

  (void) NvmDscCodierdatenRDCi_WriteBlock();
}

static Std_ReturnType NvmDscCodierdatenAllgemein_ReadBlock(void)
{
  FILE* fStream;
  const char filename[] = "3000_DSC_CODIERDATEN_ALLGEMEIN.txt";
  const char mode[] = "rb";

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fread( &NvmBlockDscCodierdatenAllgemein, sizeof(uint8), sizeof(NvmBlockDscCodierdatenAllgemein), fStream);
    fclose( fStream);
  }else{

    NvmDscCodierdatenAllgemein_WriteByte( C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_BYTE, C_FUNKTION_REIFENPANNENERKENNUNG_AKTIV_MASK, (uint8) AKTIV_RDC);
  }

  return E_OK;
}

static Std_ReturnType NvmDscCodierdatenAllgemein_WriteBlock(void)
{
  FILE* fStream;
  const char filename[] = "3000_DSC_CODIERDATEN_ALLGEMEIN.txt";
  const char mode[] = "wb";

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fwrite( (uint8 *) &NvmBlockDscCodierdatenAllgemein, sizeof(uint8), sizeof(NvmBlockDscCodierdatenAllgemein), fStream);
    fclose( fStream);
  }

  return E_OK;
}

uint8 NvmDscCodierdatenAllgemein_ReadByte( uint8 ucIx, uint8 ucMask)
{
  return (NvmBlockDscCodierdatenAllgemein.Data[ucIx] & ucMask);
}

void NvmDscCodierdatenAllgemein_WriteByte( uint8 ucIx, uint8 ucMask, uint8 ucValue)
{
  if(ucIx < sizeof(NvmBlockDscCodierdatenAllgemein.Data))
  {
    if( ucMask == 0xff)
    {

      NvmBlockDscCodierdatenAllgemein.Data[ucIx] = ucValue;
    }else{
      if( ucValue == 0)
      {

        NvmBlockDscCodierdatenAllgemein.Data[ucIx] &= ~ucMask;
      }else{

        NvmBlockDscCodierdatenAllgemein.Data[ucIx] &= ~ucMask;
        NvmBlockDscCodierdatenAllgemein.Data[ucIx] |= ucValue;
      }
    }
  }
}

Std_ReturnType NvmDscCodierdatenRDCi_ReadBlock(void)
{
  uint8 i;

  FILE* fStream;
  const char filename[] = "3008_DSC_CODIERDATEN_RDCI.txt";
  const char mode[] = "rb";

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fread( &NvmBlockDscCodierdatenRDCi, sizeof(uint8), sizeof(NvmBlockDscCodierdatenRDCi), fStream);
    fclose( fStream);
  }else{
    NvmBlockDscCodierdatenRDCi[EU].bValidData = FALSE;
    NvmBlockDscCodierdatenRDCi[US].bValidData = FALSE;

    for( i = 0; i < 2; i++)
    {
      NvmBlockDscCodierdatenRDCi[i].bValidData = TRUE;

      if( tCodingDataRomCD[i].bCRdciTPrewarnNc             == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_PREWARN_NC_BYTE,                    C_RDCI_T_PREWARN_NC_MASK,                    C_RDCI_T_PREWARN_NC_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_PREWARN_NC_BYTE,                    C_RDCI_T_PREWARN_NC_MASK,                    (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciMaxThreshold           == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_THRESHOLD_BYTE,                   C_RDCI_MAX_THRESHOLD_MASK,                   C_RDCI_MAX_THRESHOLD_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_THRESHOLD_BYTE,                   C_RDCI_MAX_THRESHOLD_MASK,                   (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciPrewarnEnable          == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_ENABLE_BYTE,                  C_RDCI_PREWARN_ENABLE_MASK,                  C_RDCI_PREWARN_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_ENABLE_BYTE,                  C_RDCI_PREWARN_ENABLE_MASK,                  (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciStatInit               == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_STAT_INIT_BYTE,                       C_RDCI_STAT_INIT_MASK,                       C_RDCI_STAT_INIT_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_STAT_INIT_BYTE,                       C_RDCI_STAT_INIT_MASK,                       (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciNumPrewarnDetect       == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_NUM_PREWARN_DETECT_BYTE,              C_RDCI_NUM_PREWARN_DETECT_MASK,              C_RDCI_NUM_PREWARN_DETECT_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_NUM_PREWARN_DETECT_BYTE,              C_RDCI_NUM_PREWARN_DETECT_MASK,              (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciPrewarnIgnition        == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_IGNITION_BYTE,                C_RDCI_PREWARN_IGNITION_MASK,                C_RDCI_PREWARN_IGNITION_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PREWARN_IGNITION_BYTE,                C_RDCI_PREWARN_IGNITION_MASK,                (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciPanneBefPos            == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_BEF_POS_BYTE,                   C_RDCI_PANNE_BEF_POS_MASK,                   C_RDCI_PANNE_BEF_POS_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_BEF_POS_BYTE,                   C_RDCI_PANNE_BEF_POS_MASK,                   (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciFastDeflateEnable      == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_FAST_DEFLATE_ENABLE_BYTE,             C_RDCI_FAST_DEFLATE_ENABLE_MASK,             C_RDCI_FAST_DEFLATE_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_FAST_DEFLATE_ENABLE_BYTE,             C_RDCI_FAST_DEFLATE_ENABLE_MASK,             (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciTyrIdFiltGw            == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TYR_ID_FILT_GW_BYTE,                  C_RDCI_TYR_ID_FILT_GW_MASK,                  C_RDCI_TYR_ID_FILT_GW_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TYR_ID_FILT_GW_BYTE,                  C_RDCI_TYR_ID_FILT_GW_MASK,                  (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciResetPlausi            == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RESET_PLAUSI_BYTE,                    C_RDCI_RESET_PLAUSI_MASK,                    C_RDCI_RESET_PLAUSI_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RESET_PLAUSI_BYTE,                    C_RDCI_RESET_PLAUSI_MASK,                    (uint8) FALSE); }
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TPMS_MARKET_BYTE, C_RDCI_TPMS_MARKET_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciTpmsMarket << 2));
      if( tCodingDataRomCD[i].bCRdciSensorForeignAkRdk     == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_FOREIGN_AK_RDK_BYTE,           C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK,           C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_FOREIGN_AK_RDK_BYTE,           C_RDCI_SENSOR_FOREIGN_AK_RDK_MASK,           (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciSensorLocSync          == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_LOC_SYNC_BYTE,                 C_RDCI_SENSOR_LOC_SYNC_MASK,                 C_RDCI_SENSOR_LOC_SYNC_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SENSOR_LOC_SYNC_BYTE,                 C_RDCI_SENSOR_LOC_SYNC_MASK,                 (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciErfsEnable             == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_ENABLE_BYTE,                     C_RDCI_ERFS_ENABLE_MASK,                     C_RDCI_ERFS_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_ENABLE_BYTE,                     C_RDCI_ERFS_ENABLE_MASK,                     (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciTrefSeasonalAdjustment == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_BYTE, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_BYTE, C_RDCI_TREF_SEASONAL_ADJUSTMENT_ENABLE_MASK, (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciDispReset              == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_RESET_BYTE,                      C_RDCI_DISP_RESET_MASK,                      C_RDCI_DISP_RESET_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_RESET_BYTE,                      C_RDCI_DISP_RESET_MASK,                      (uint8) FALSE); }
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_COR_HOLD_OFF_TIME_BYTE, C_RDCI_COR_HOLD_OFF_TIME_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciCorHoldOffTime << 5));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_T_REF_SHIFT_BYTE, C_RDCI_T_REF_SHIFT_MASK, (uint8) tCodingDataRomCD[i].ucCRdciTRefShift);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIA_TH_C_BYTE, C_RDCI_UIA_TH_C_MASK, (uint8) tCodingDataRomCD[i].ucCRdciUiaThC);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIW_TH_C_BYTE, C_RDCI_UIW_TH_C_MASK, (uint8) tCodingDataRomCD[i].ucCRdciUiwThC);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIA_TH_NC_BYTE, C_RDCI_UIA_TH_NC_MASK, (uint8) tCodingDataRomCD[i].ucCRdciUiaThNc);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_UIW_TH_NC_BYTE, C_RDCI_UIW_TH_NC_MASK, (uint8) tCodingDataRomCD[i].ucCRdciUiwThNc);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PANNE_TH_BYTE, C_RDCI_PANNE_TH_MASK, (uint8) tCodingDataRomCD[i].ucCRdciPanneTh);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MIN_RCP_FA_BYTE, C_RDCI_MIN_RCP_FA_MASK, (uint8) tCodingDataRomCD[i].ucCRdciMinRcpFa);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MIN_RCP_RA_BYTE, C_RDCI_MIN_RCP_RA_MASK, (uint8) tCodingDataRomCD[i].ucCRdciMinRcpRa);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DELTA_P_L_R_BYTE, C_RDCI_DELTA_P_L_R_MASK, (uint8) tCodingDataRomCD[i].ucCRdciDeltaPLR);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_P_INIT_RANGE_MAX_BYTE, C_RDCI_P_INIT_RANGE_MAX_MASK, (uint8) tCodingDataRomCD[i].ucCRdciPInitRangeMax);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TIMEOUT_PREWARN_BYTE, C_RDCI_TIMEOUT_PREWARN_MASK, (uint8) tCodingDataRomCD[i].ucCRdciTimeoutPrewarn);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DT_AMB_PREWARN_BYTE, C_RDCI_DT_AMB_PREWARN_MASK, (uint8) tCodingDataRomCD[i].ucCRdciDtAmbPrewarn);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DP_TO_I_PMIN_BYTE, C_RDCI_DP_TO_I_PMIN_MASK, (uint8) tCodingDataRomCD[i].ucCRdciDpToIPmin);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_0, C_RDCI_LEARN_LOCATE_CONFIG_MASK_0, (uint8) tCodingDataRomCD[i].aucCRdciLearnLocateConfig[0]);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LEARN_LOCATE_CONFIG_BYTE_1, C_RDCI_LEARN_LOCATE_CONFIG_MASK_1, (uint8) tCodingDataRomCD[i].aucCRdciLearnLocateConfig[1]);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_XMIN_COOL_TIRE_BYTE, C_RDCI_XMIN_COOL_TIRE_MASK, (uint8) tCodingDataRomCD[i].ucCRdciXminCoolTire);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_COR_TIME_BYTE, C_RDCI_MAX_COR_TIME_MASK, (uint8) tCodingDataRomCD[i].ucCRdciMaxCorTime);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_MAX_COR_RCP_BYTE, C_RDCI_MAX_COR_RCP_MASK, (uint8) tCodingDataRomCD[i].ucCRdciMaxCorRcp);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TH_C_TOL_BYTE, C_RDCI_TH_C_TOL_MASK, (uint8) tCodingDataRomCD[i].ucCRdciThCTol);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TH_NC_TOL_BYTE, C_RDCI_TH_NC_TOL_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciThNCTol << 4));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_LONG_HOLD_TIME_BYTE, C_RDCI_LONG_HOLD_TIME_MASK, (uint8) tCodingDataRomCD[i].ucCRdciLongHoldTime);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SHORT_HOLD_TIME_BYTE, C_RDCI_SHORT_HOLD_TIME_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciShortHoldTime << 4));
      if( tCodingDataRomCD[i].bCRdciEcoRcpEnable           == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ECO_RCP_ENABLE_BYTE,                  C_RDCI_ECO_RCP_ENABLE_MASK,                  C_RDCI_ECO_RCP_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ECO_RCP_ENABLE_BYTE,                  C_RDCI_ECO_RCP_ENABLE_MASK,                  (uint8) FALSE); }
      if( tCodingDataRomCD[i].bCRdciDefaultLoadCond        == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_LOAD_COND_BYTE,               C_RDCI_DEFAULT_LOAD_COND_MASK,               C_RDCI_DEFAULT_LOAD_COND_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_LOAD_COND_BYTE,               C_RDCI_DEFAULT_LOAD_COND_MASK,               (uint8) FALSE); }
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_ERFS_PLACARD_SOURCE_BYTE, C_RDCI_ERFS_PLACARD_SOURCE_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciErfsPlacardSource << 1));
      if( tCodingDataRomCD[i].bCRdciDefaultMenuSel         == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_MENU_SEL_BYTE,                C_RDCI_DEFAULT_MENU_SEL_MASK,                C_RDCI_DEFAULT_MENU_SEL_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DEFAULT_MENU_SEL_BYTE,                C_RDCI_DEFAULT_MENU_SEL_MASK,                (uint8) FALSE); }
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_DISP_CONF_TIMEOUT_BYTE, C_RDCI_DISP_CONF_TIMEOUT_MASK, (uint8) (tCodingDataRomCD[i].ucCRdciDispConfTimeout << 4));
      if( tCodingDataRomCD[i].bCRdciRidEnable              == TRUE) { NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RID_ENABLE_BYTE,                      C_RDCI_RID_ENABLE_MASK,                      C_RDCI_RID_ENABLE_MASK); }else{ NvmDscCodierdatenRDCi_WriteByte( C_RDCI_RID_ENABLE_BYTE,                      C_RDCI_RID_ENABLE_MASK,                      (uint8) FALSE); }
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_0, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_0, (uint8) tCodingDataRomCD[i].aucCRdciTrefSeasAdjConfig[0]);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_1, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_1, (uint8) tCodingDataRomCD[i].aucCRdciTrefSeasAdjConfig[1]);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_2, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_2, (uint8) tCodingDataRomCD[i].aucCRdciTrefSeasAdjConfig[2]);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_TREF_SEAS_ADJ_CONFIG_BYTE_3, C_RDCI_TREF_SEAS_ADJ_CONFIG_MASK_3, (uint8) tCodingDataRomCD[i].aucCRdciTrefSeasAdjConfig[3]);

      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_ENABLE_BYTE, C_RDCI_SPEED_CCM_ENABLE_MASK, (uint8) tCodingDataRomCD[i].bCRdciSpeedCcmEnable);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TH_BYTE_0, C_RDCI_SPEED_CCM_TH_MASK_0, (uint8) ((tCodingDataRomCD[i].ushCRdciSpeedCcmTh >> 0) & 0x00FFu));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TH_BYTE_1, C_RDCI_SPEED_CCM_TH_MASK_1, (uint8) ((tCodingDataRomCD[i].ushCRdciSpeedCcmTh >> 8) & 0x00FFu));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_TIME_BYTE, C_RDCI_SPEED_CCM_TIME_MASK, (uint8) tCodingDataRomCD[i].ucCRdciSpeedCcmTime);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_HYST_BYTE, C_RDCI_SPEED_CCM_HYST_MASK, (uint8) tCodingDataRomCD[i].ucCRdciSpeedCcmHyst);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_0, (uint8) ((tCodingDataRomCD[i].sshCRdciSpeedCcmPressOffsetFa >> 0) & 0x00FFu));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_FA_MASK_1, (uint8) ((tCodingDataRomCD[i].sshCRdciSpeedCcmPressOffsetFa >> 8) & 0x00FFu));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_0, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_0, (uint8) ((tCodingDataRomCD[i].sshCRdciSpeedCcmPressOffsetRa >> 0) & 0x00FFu));
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_BYTE_1, C_RDCI_SPEED_CCM_PRESS_OFFSET_RA_MASK_1, (uint8) ((tCodingDataRomCD[i].sshCRdciSpeedCcmPressOffsetRa >> 8) & 0x00FFu));

      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_BYTE, C_RDCI_PARK_SUP_EXT_PARK_SUP_CONFIG_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupExtParkSupConfig);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_BYTE, C_RDCI_PARK_SUP_MOBILITY_LOSS_THRESHOLD_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupMobilityLossThValue);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_C_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupNotifThCValue);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_NOTIFICATION_THRESHOLD_VALUE_NC_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupNotifThNcValue);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_NO_TEMP_COMP_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupTolNoTempComp);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_TOL_TEMP_COMP_BYTE, C_RDCI_PARK_SUP_TOL_TEMP_COMP_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupTolTempComp);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_C_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupWarningThCValue);
      NvmDscCodierdatenRDCi_WriteByte( C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_BYTE, C_RDCI_PARK_SUP_WARNING_THRESHOLD_VALUE_NC_MASK, (uint8) tCodingDataRomCD[i].ucCRdciParkSupWarningThNcValue);

      NvmBlockDscCodierdatenRDCi[i].bValidData = FALSE;
    }

    NvmBlockDscCodierdatenRDCi[EU].bValidData = TRUE;
    NvmBlockDscCodierdatenRDCi[US].bValidData = FALSE;
  }

  return E_OK;
}

Std_ReturnType NvmDscCodierdatenRDCi_WriteBlock(void)
{
  FILE* fStream;
  const char filename[] = "3008_DSC_CODIERDATEN_RDCI.txt";
  const char mode[] = "wb";

  if( fopen_s(&fStream, filename, mode) == 0)
  {
    fwrite( (uint8 *) &NvmBlockDscCodierdatenRDCi, sizeof(uint8), sizeof(NvmBlockDscCodierdatenRDCi), fStream);
    fclose( fStream);
  }

  return E_OK;
}

uint8 NvmDscCodierdatenRDCi_ReadByte( uint8 ucIx, uint8 ucMask)
{
  uint8 ucRet;

  if( NvmBlockDscCodierdatenRDCi[US].bValidData == TRUE)
  {

    ucRet = NvmBlockDscCodierdatenRDCi[US].Data[ucIx] & ucMask;
  }else{

    ucRet = NvmBlockDscCodierdatenRDCi[EU].Data[ucIx] & ucMask;
  }

  return ucRet;
}

void NvmDscCodierdatenRDCi_WriteByte( uint8 ucIx, uint8 ucMask, uint8 ucValue)
{
  if( NvmBlockDscCodierdatenRDCi[US].bValidData == TRUE)
  {

    if(ucIx < sizeof(NvmBlockDscCodierdatenRDCi[US].Data))
    {
      if( ucMask == 0xff)
      {

        NvmBlockDscCodierdatenRDCi[US].Data[ucIx] = ucValue;
      }else{
        if( ucValue == 0)
        {

          NvmBlockDscCodierdatenRDCi[US].Data[ucIx] &= ~ucMask;
        }else{

          NvmBlockDscCodierdatenRDCi[US].Data[ucIx] &= ~ucMask;
          NvmBlockDscCodierdatenRDCi[US].Data[ucIx] |= ucValue;
        }
      }
    }
  }else{

    if(ucIx < sizeof(NvmBlockDscCodierdatenRDCi[EU].Data))
    {
      if( ucMask == 0xff)
      {

        NvmBlockDscCodierdatenRDCi[EU].Data[ucIx] = ucValue;
      }else{
        if( ucValue == 0)
        {

          NvmBlockDscCodierdatenRDCi[EU].Data[ucIx] &= ~ucMask;
        }else{

          NvmBlockDscCodierdatenRDCi[EU].Data[ucIx] &= ~ucMask;
          NvmBlockDscCodierdatenRDCi[EU].Data[ucIx] |= ucValue;
        }
      }
    }
  }
}

void NvmDscCodierdatenRDCi_Activate( uint8 ucMarket)
{
  if( ucMarket == US)
  {

    NvmBlockDscCodierdatenRDCi[US].bValidData = TRUE;
    NvmBlockDscCodierdatenRDCi[EU].bValidData = FALSE;
  }else{

    NvmBlockDscCodierdatenRDCi[EU].bValidData = TRUE;
    NvmBlockDscCodierdatenRDCi[US].bValidData = FALSE;
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

