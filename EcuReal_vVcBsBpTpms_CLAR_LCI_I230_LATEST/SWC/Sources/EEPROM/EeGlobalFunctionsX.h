

#ifndef _ee_global_functions_X_H
#define _ee_global_functions_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Rte_CtApHufTpmsSWC.h"

#define cDiagBlock1           0
#define cDiagBlock2           1
#define cHistoBlock           2
#define cErfsBlock            3
#define cErfsEcoBlock         4
#define cWarnstatusBlock      5
#define cErfsTsaBlock         6
#define cRidQrBlock1          7
#define cRidQrBlock2          8
#define cZomblock1            9
#define cZomblock2            10
#define cCommonBlock          11

#define cAttemptCounterSize   12

extern void CheckMemoryReserveEE(Rte_Instance self);

#ifdef __cplusplus
}
#endif

#endif

