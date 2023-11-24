#pragma once

# ifdef __cplusplus
extern "C"
{
# endif

#include "HS_KalibrierereignisX.h"

#define cCalEvPlausiFailed          (uint8)0
#define cCalEvPlausiSuccessful      (uint8)1
#define cCalEvManPlausiFailed       (uint8)2
#define cCalEvManPlausiSuccessful   (uint8)3
#define cCalEvInvalid               (uint8)0xff

#ifdef __cplusplus
}
#endif
