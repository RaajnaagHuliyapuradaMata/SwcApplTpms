

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

#include "Rte_CtApHufTpmsSWC.h"
#include "datamanagerX.h"
#include "Util.h"
#include "RTE_Stub_FlexRayData.h"
#include "RTE_Stub_Output.h"
#include "RTE_Stub_CddData.h"
#include "cd_decoder_X.h"
#include "WAllocX.h"
#include "EeCommonBlockX.h"
#include "CodingDataX.h"

unsigned char SetTeleFilter(unsigned char ucFilter)
{
  static unsigned char ucTeleFilter;
  if(ucFilter != TELE_FILTER_READ_ONLY)
  {
    if(ucFilter == TELE_FILTER_OFF)
    {
      ucTeleFilter = TELE_FILTER_OFF;
    }

    else
    {
      ucTeleFilter |= ucFilter;
    }
  }
  return ucTeleFilter;
}

void ReadStringFromStream(unsigned char myString[], System::IO::Stream^ myStream, uint8 mySize)
{
  int ucChar, i = 0;
  boolean bReady = FALSE;

  myString[i] = 0;

  do
  {
    ucChar = myStream->ReadByte();

    if( (ucChar != '\n') && (ucChar != '\r') && (ucChar != '\t') && (ucChar != ' '))
    {
      if( (ucChar == ';') || (ucChar == ','))
      {
        myString[i] = 0;
        bReady = TRUE;
      }else{
        myString[i] = ucChar;

        if( i < (mySize - 1))
        {
          i++;
        }else{
          myString[0] = 0;
          i = 0;
        }
      }
    }else{
      myString[0] = 0;
      i = 0;
    }
  }
  while( bReady == FALSE);
}

long ReadLongIntFromStream(System::IO::Stream^ myStream)
{
  unsigned char myString[255];

  ReadStringFromStream(myString, myStream, sizeof(myString));
  return (atol((const char*)myString));
}

long long ReadLongLongIntFromStream(System::IO::Stream^ myStream)
{
  unsigned char myString[40];

  ReadStringFromStream(myString, myStream, sizeof(myString));

  #ifndef atoll

    return ( (long long) atof((const char*)myString));
  #else
    return ( atoll((const char*)myString));
  #endif
}

double ReadDoubleFromStream(System::IO::Stream^ myStream)
{
  unsigned char myString[40];

  ReadStringFromStream(myString, myStream, sizeof(myString));
  return (atof((const char*)myString));
}

void ReadCompleteLineFromStream( System::IO::Stream^ myStream)
{
  while( myStream->ReadByte() != '\n')
  {
  }
}

long ReadMessageFromFile(System::IO::Stream^ myStream, uint32 dataType, unsigned long long * pullTimestamp, void * FileData)
{
    uint32 ulRet = 0;
    uint8 direction = 0x03;
    uint32 ulTemp = 0;
    long long llTimestamp = 0;

    switch (dataType)
    {

      case 0:

        llTimestamp = ReadLongLongIntFromStream( myStream);
        ((tCddAbsData *) FileData)->ABS_SYNC_TSTMP_HI = (uint32) (llTimestamp / 1000000);

        ((tCddAbsData *) FileData)->ABS_SYNC_TSTMP_LO = (uint32) ((llTimestamp - ((tCddAbsData *) FileData)->ABS_SYNC_TSTMP_HI * 1000000) * 1000);

        ((tCddAbsData *) FileData)->ABS_EDGE_CNT_FL = (uint16)ReadLongIntFromStream(myStream);
        ((tCddAbsData *) FileData)->ABS_EDGE_CNT_FR = (uint16)ReadLongIntFromStream(myStream);
        ((tCddAbsData *) FileData)->ABS_EDGE_CNT_RL = (uint16)ReadLongIntFromStream(myStream);
        ((tCddAbsData *) FileData)->ABS_EDGE_CNT_RR = (uint16)ReadLongIntFromStream(myStream);

        ((tCddAbsData *) FileData)->ABS_SPIN_DIR_FL = direction;
        ((tCddAbsData *) FileData)->ABS_SPIN_DIR_FR = direction;
        ((tCddAbsData *) FileData)->ABS_SPIN_DIR_RL = direction;
        ((tCddAbsData *) FileData)->ABS_SPIN_DIR_RR = direction;

        ((tCddAbsData *) FileData)->ABS_QU_SIG_FL = 0x00;
        ((tCddAbsData *) FileData)->ABS_QU_SIG_FR = 0x00;
        ((tCddAbsData *) FileData)->ABS_QU_SIG_RL = 0x00;
        ((tCddAbsData *) FileData)->ABS_QU_SIG_RR = 0x00;

        *pullTimestamp = (llTimestamp / 1000);
        ulRet = 0;
      break;

      case 1:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);
        ((Rdci_V_VEH_Type *) FileData)->V_VEH_COG = (uint16) ReadLongIntFromStream( myStream);
        ulRet = 0;
      break;

      case 2:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);
        * ((Rdci_TEMP_EX_Type *) FileData) = (Rdci_TEMP_EX_Type) ReadLongIntFromStream( myStream);
        ulRet = 0;
      break;

      case 3:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);
        * (uint8 *) FileData = (uint8) ReadLongIntFromStream( myStream);
        ulRet = 0;
     break;

      case 4:

        llTimestamp = ReadLongLongIntFromStream( myStream);

        ((tCddRdcData *) FileData)->RDC_SYNC_TSTMP_HI = (uint32) (llTimestamp / 1000000);
        ((tCddRdcData *) FileData)->RDC_SYNC_TSTMP_LO = (uint32) ((llTimestamp - ((tCddRdcData *) FileData)->RDC_SYNC_TSTMP_HI * 1000000) * 1000);

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->ALIV_RDC_DT_PCK_1 = (uint8) (ulTemp & 0x0f);

        ((tCddRdcData *) FileData)->TYR_ID  = (uint32) ((ulTemp & 0xf0) >> 4);
        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->TYR_ID |= (uint32) (ulTemp << 4);
        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->TYR_ID |= (uint32) (ulTemp << 12);
        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->TYR_ID |= (uint32) (ulTemp << 20);

        ((tCddRdcData *) FileData)->RDC_DT_1 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_2 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_3 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_4 = (uint8) ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->ALIV_RDC_DT_PCK_2 = (uint8) (ulTemp & 0x0f);

        ((tCddRdcData *) FileData)->SUPP_ID = (uint8) ((ulTemp & 0xf0) >> 4);

        ((tCddRdcData *) FileData)->PCKG_ID = (uint8) ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_MES_TSTMP  = (uint16) ((ulTemp << 8) & 0xff00);
        ulTemp = ReadLongIntFromStream(myStream);
        ((tCddRdcData *) FileData)->RDC_MES_TSTMP |= (uint16) (ulTemp & 0x00ff);

        ((tCddRdcData *) FileData)->RDC_DT_5 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_6 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_7 = (uint8) ReadLongIntFromStream( myStream);
        ((tCddRdcData *) FileData)->RDC_DT_8 = (uint8) ReadLongIntFromStream( myStream);

        *pullTimestamp = (llTimestamp / 1000);

        if( ((tCddRdcData *) FileData)->PCKG_ID == cTelTypeAlive)
        {

          ulRet = 0;
        }else{

          if((SetTeleFilter(TELE_FILTER_READ_ONLY) == TELE_FILTER_OFF)
           || ((((tCddRdcData *) FileData)->SUPP_ID == cSupplCodeHuf) && ((SetTeleFilter(TELE_FILTER_READ_ONLY) & TELE_FILTER_HUF) == TELE_FILTER_HUF))
           || ((((tCddRdcData *) FileData)->SUPP_ID == cSupplCodeSchrader) && ((SetTeleFilter(TELE_FILTER_READ_ONLY) & TELE_FILTER_SCHRADER) == TELE_FILTER_SCHRADER))
           || ((((tCddRdcData *) FileData)->SUPP_ID == cSupplCodeConti) && ((SetTeleFilter(TELE_FILTER_READ_ONLY) & TELE_FILTER_CONTI) == TELE_FILTER_CONTI)))
          {
            ulRet = 0;
          }else{
            ulRet = 1;
          }
        }
      break;

      case 5:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);
        * ((Rdci_AIP_ENG_DRV_Type *) FileData) = (Rdci_AIP_ENG_DRV_Type) ReadLongIntFromStream( myStream);
        ulRet = 0;
      break;

      case 6:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);
        * ((uint8 *) FileData) = (uint8) ReadLongIntFromStream( myStream);
        ulRet = 0;
      break;

      case 7:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpTyrSeaTpct     = (Rdci_OP_TYR_SEA_TPCT_Type) (ulTemp & 0x03u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpTpct           = (Rdci_OP_TPCT_Type) (ulTemp & 0x03u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpIdrSlctn       = (Rdci_OP_IDR_SLCTN_Type) (ulTemp & 0x03u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpTarPLocoTpct   = (Rdci_OP_TAR_P_LOCO_TPCT_Type) (ulTemp & 0x03u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->RqOlTpct         = (Rdci_RQ_OL_TPCT_Type) (ulTemp & 0x03u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpSlctnTyrAvlb   = (Rdci_OP_SLCTN_TYR_AVLB_Type) (ulTemp & 0xffu);

        ulTemp = ReadLongIntFromStream( myStream);
        ((BedienungFahrwerkRecType *) FileData)->OpIdrMsg         = (Rdci_OP_IDR_MSGC_Type) (ulTemp & 0x03u);

        ulRet = 0;
      break;

      case 8:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);

        ulTemp = ReadLongIntFromStream( myStream);
        ((EinheitenBn2020RecType *) FileData)->UnTemp             = (Rdci_UN_TEMP_Type) (ulTemp & 0x30u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((EinheitenBn2020RecType *) FileData)->UnMile             = (Rdci_UN_MILE_Type) (ulTemp & 0xC0u);

        ulTemp = ReadLongIntFromStream( myStream);
        ((EinheitenBn2020RecType *) FileData)->UnAip              = (Rdci_UN_AIP_Type) (ulTemp & 0x03u);

        ulRet = 0;
      break;

      case 9:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);

        ((GpsAltitudeType *) FileData)->PositionAltitude    = (Rdci_GNSSPositionAltitude_Type)    ReadLongIntFromStream( myStream);
        ((GpsAltitudeType *) FileData)->ErrorAltitudeMeters = (Rdci_GNSSErrorAltitudeMeters_Type) ReadLongIntFromStream( myStream);
        ulRet = 0;
      break;

      case 20:

        *pullTimestamp = (ReadLongLongIntFromStream( myStream) / 1000);

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCodingDataDeclCD *) FileData)->ucCRdciCorHoldOffTime = (uint8) ulTemp;

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCodingDataDeclCD *) FileData)->ucCRdciMaxCorTime    = (uint8) ulTemp;

        ulTemp = ReadLongIntFromStream( myStream);
        ((tCodingDataDeclCD *) FileData)->ucCRdciMaxCorRcp    = (uint8) ulTemp;

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulTemp = ReadLongIntFromStream( myStream);

        ulRet = 0;
      break;

      default:

        *pullTimestamp = (unsigned long long) (ReadDoubleFromStream( myStream) / 1000);
        ReadCompleteLineFromStream( myStream);
        ulRet = 0;
      break;
    }

    return ulRet;
}

short SearchIDInList(long id)
{
  static long idList[16];
  short i = 0;
  short retVal = 16;

  if( id == 0xFFFFFFFFu)
  {
    for( i = 0; i < 16; i++)
    {
      idList[i] = 0;
    }
  }else{
    while (i < 16)
    {
      if(id == idList[i])
      {
        retVal = i;
        i = 16;
      }
      else
      {
        if(idList[i] == 0)
        {
          idList[i] = id;
          retVal = i | 0x100;
          i = 16;
        }
        else
        {
          i++;
        }
      }
    }
  }

  return retVal;
}

void convertTemperatureRawToPhysical(unsigned char ucRawTemp, signed char *pscPhyTemp)
{
  if( ucRawTemp == cReAkTempError)
  {

    *pscPhyTemp = cInvalidREtemperature;
  }else if( ucRawTemp < cReHufAkTempUnderflow)
  {

    *pscPhyTemp = (sint8) (cReHufAkTempUnderflow - 52);
  }else if( ucRawTemp > cReHufAkTempOverflow)
  {

    *pscPhyTemp = (sint8) (cReHufAkTempOverflow - 52);
  }else{

    *pscPhyTemp = (sint8) (ucRawTemp - 52);
  }
}

void SynchronizeSystemTimes( Rdci_UHRZEIT_DATUM_Type* timeDate, Rdci_T_SEC_COU_REL_Type* relTime, StbMB_SyncStatusType* syncState, StbMB_SystemTimeType* sysTime)
{
  time_t t;
  tm now;

  *syncState = STBM_STATE_NOT_SYNC;

  t = time(0);
  localtime_s(&now, &t);
  timeDate->DISP_DATE_DAY = now.tm_mday;
  timeDate->DISP_DATE_MON = now.tm_mon + 1;
  timeDate->DISP_DATE_WDAY = now.tm_wday;
  timeDate->DISP_DATE_YR = now.tm_year + 1900;
  timeDate->DISP_HR = now.tm_hour;
  timeDate->DISP_MN = now.tm_min;
  timeDate->DISP_SEC = now.tm_sec;
  timeDate->ST_DISP_CTI_DATE = 0x03;

  *relTime = (uint32)t;

  sysTime->systemTicks = (uint32)t;
  sysTime->tickDuration = 1;
  sysTime->systemTicksHi = 0;
  sysTime->ticks = 0;
  syncState = STBM_STATE_SYNC;

}

