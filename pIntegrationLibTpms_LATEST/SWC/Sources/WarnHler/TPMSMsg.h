

#ifndef TPMSMSG_H
#define TPMSMSG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

static uint8 ucFilterIdWarnTM( uint8 ucIdX);
static void Warnings2MsgTM( const tTPMSMsgData* ptWarnInfo);
static void TPMSMsgOutTM( const uint8* ptData);
static void TPMSMsgInitTM( Rte_Instance self, uint8* pucStatus, const uint8* pucIniDat);

static uint8 ucTPMSMsgManager_PorInitTM( Rte_Instance self, const uint8* pucData);
static uint8 ucTPMSMsgManager_MsgOutTM( const uint8* pucData);
static uint8 ucTPMSMsgManagerDsTM( Rte_Instance self, uint8* pucData);
static uint8 ucTPMSMsgManagerDs_NewPositionsTM( const uint8* pucData);
static uint8 ucTPMSMsgManagerDs_ClearPosTM(void);
static uint8 ucTPMSMsgManagerDs_WrWnValidTM( Rte_Instance self, const uint8* pucData);
static uint8 ucTPMSMsgManagerDs_RdWnValidTM( uint8* pucData);
static uint8 ucTPMSMsgManagerDs_ClearWarnOfIdTM( uint8 ucWheelPos);
static uint8 ucTPMSMsgManagerDs_PutWarnVectorSetTM( const uint8* pucData);
static uint8 ucTPMSMsgManagerDs_GetWarnVectorsIdTM( uint8* pucData);

#ifdef __cplusplus
}
#endif

#endif

