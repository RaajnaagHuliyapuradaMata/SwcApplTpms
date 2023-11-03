

#ifndef UCSCS_H
#define UCSCS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wntypepar.h"

#define cucPambDef              ((uint8)    40)
#define cscTambDef              ((sint8)    20)

#define ushPMinInMBarEU         ((uint16) 1600)
#define ushPSollDefInMBarEU     ((uint16) 2000)
#define ucPMinDefEUc            ((uint8)    64)
#define ucPSollDefEUc           ((uint8)    80)
#define ucTSollDefEUc           ((uint8)    20)
#define ushMSollDefEUc          ((uint16)  419)

#define ushPMinInMBarUS         ((uint16) 1600)
#define ushPSollDefInMBarUS     ((uint16) 2000)
#define ucPMinDefUSc            ((uint8)    64)
#define ucPSollDefUSc           ((uint8)    80)
#define ucTSollDefUSc           ((uint8)    20)
#define ushMSollDefUSc          ((uint16)  419)

#define cIxForIdSpecDataStorage ((uint8)     0)
#define cIxForWpSpecDataStorage ((uint8)     1)

extern uint8  ucPutPMinCS( uint8 ucPMin, uint8 ucMode);
extern uint8  ucGetPSollCS( uint8 ucIdX, uint8 ucWheelPos);
extern sint8  scGetTSollCS( uint8 ucIdX, uint8 ucWheelPos);
extern uint16 ushGetMSollCS( uint8 ucIdX);
extern uint8  ucPutMSollCS( uint8 ucIdX, uint16 ushMSoll);
extern uint8  ucPutCalTabVectorCS( uint8 ucIdX, uint8 ucP, sint8 scT, uint8 ucWheelPos);
extern uint8  ucPutEnvDataCS( uint8 ucIdX, uint8 ucEnvPres, sint8 scEnvTemp);
extern uint8  ucGetPambCS( uint8 ucIdX);
extern sint8  scGetTambCS( uint8 ucIdX);
extern uint8  ucGetPSollMinCS( uint8 ucIdX);
extern uint8  ucGetPinitTreifenCS( uint8 ucIdX);
extern sint8  scGetTreifenCS( uint8 ucIdX);
extern uint8  ucPutPinitTreifenCS( uint8 ucIdX, sint8 scTreifen);
extern uint8  ucPutPSollMinCS( uint8 ucIdX, uint8 ucP, uint8 ucMode);

extern void   InitCS( uint8 ucInit);

#ifdef __cplusplus
}
#endif

#endif
