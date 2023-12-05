

#ifndef _ee_global_functions_H
#define _ee_global_functions_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "EeGlobalFunctionsX.h"

#define cMinNvmMemReserve 5

#define cOfcCommonBlock      0x0001
#define cOfcDiagBlock1       0x0002
#define cOfcDiagBlock2       0x0004
#define cOfcErfsBlock        0x0008
#define cOfcErfsEcoBlock     0x0010
#define cOfcRidQrBlock1      0x0020
#define cOfcRidQrBlock2      0x0040
#define cOfcHistoryBlock     0x0080
#define cOfcWarnstatusBlock  0x0100
#define cOfcZomBlock1        0x0200
#define cOfcZomBlock2        0x0400

#ifdef __cplusplus
}
#endif

#endif

