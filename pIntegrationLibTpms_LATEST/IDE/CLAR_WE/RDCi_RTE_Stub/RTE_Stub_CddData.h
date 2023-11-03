

#ifndef _RTE_STUB_CDDDATA_H
#define _RTE_STUB_CDDDATA_H

#include "Rte_CtApHufTpmsSWC_Type.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "RTE_Stub_CddDataX.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ABS_DATA_QUEUE_LENGTH 10
#define RDC_DATA_QUEUE_LENGTH 20

typedef ImpTypeRecCddAbsData tCddAbsData;
typedef ImpTypeRecCddRdcData tCddRdcData;

typedef struct
        {
          Rdci_OP_TYR_SEA_TPCT_Type     OpTyrSeaTpct;
          Rdci_OP_TPCT_Type             OpTpct;
          Rdci_OP_IDR_SLCTN_Type        OpIdrSlctn;
          Rdci_OP_TAR_P_LOCO_TPCT_Type  OpTarPLocoTpct;
          Rdci_RQ_OL_TPCT_Type          RqOlTpct;
          Rdci_OP_SLCTN_TYR_AVLB_Type   OpSlctnTyrAvlb;
          Rdci_OP_IDR_MSGC_Type         OpIdrMsg;
        } BedienungFahrwerkRecType;

typedef struct
        {
          Rdci_UN_TEMP_Type             UnTemp;
          Rdci_UN_MILE_Type             UnMile;
          Rdci_UN_AIP_Type              UnAip;
        } EinheitenBn2020RecType;

typedef struct
        {
          Rdci_GNSSPositionAltitude_Type    PositionAltitude;
          Rdci_GNSSErrorAltitudeMeters_Type ErrorAltitudeMeters;
        } GpsAltitudeType;

uint16 PutCddAbsData( tCddAbsData * data);

uint16 PutCddRdcData( tCddRdcData * data);

#ifdef __cplusplus
}
#endif

#endif
