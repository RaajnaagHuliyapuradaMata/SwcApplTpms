

#ifndef CTRL_H
#define CTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

static void ChangeWNParaSubSet(Rte_Instance self);

static uint8 ucUSWAlgoPara_WrParaByteWN(Rte_Instance self, const uint8* pucData);
static uint8 ucUSWAlgoPara_WrParaThresWN( const uint8* pucData);

#ifdef __cplusplus
}
#endif

#endif
