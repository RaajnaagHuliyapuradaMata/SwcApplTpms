

#ifndef _tss_stdX_H
#define _tss_stdX_H

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.hpp"
  #include "CfgSwcApplTpms.hpp"
#else
  #include "CfgSwcApplTpms.hpp"
  #include "Types.hpp"
#endif

#define cAnzAnt       ( (uint8)  1 )
#define cAnzRad       ( (uint8)  4 )
#define cAnzAchse     ( (uint8)  2 )

#define cRadPosVL     ( (uint8) 0 )
#define cRadPosVR     ( (uint8) 1 )
#define cRadPosHL     ( (uint8) 2 )
#define cRadPosHR     ( (uint8) 3 )
#define cRadPosRR     ( (uint8) 4 )
#define cRadPosFR     ( (uint8) 5 )
#define cRadPosUndef  ( (uint8) 8 )

#define FREQUENCY_433MHZ  ( (uint8) 0x00 )
#define FREQUENCY_868MHZ  ( (uint8) 0x01 )
#define FREQUENCY_315MHZ  ( (uint8) 0x02 )

#define cInvalidREpressure     ( (uint8)    0xff )
#define cInvalidREtemperature  ( (sint8)    0x7f )
#define cInvalidRElifeTime     ( (uint8)    0x0f )
#define cInvalidREstate        ( (uint8)    0x00 )
#define cInvalidRSSIsum        ( (uint8)    0x00 )
#define cInvalidWheelDir       ( (uint8)    0xff )
#define cInvalidTelType        ( (uint8)    0xff )
#define cInvalidTransMode      ( (uint8)    0x00 )
#define cInvalidSensorDefect   ( (uint16)   0x00 )
#define cInvalidRollSwitch     ( (uint8)    0x00 )
#define cInvalidCntValue       ( (uint8)    0x00 )

#define cRetError    ( (uint8) 0x00 )
#define cRetOk       ( (uint8) 0x01 )

typedef struct{
  uint8 hi;
  uint8 lo;
}tWord;

typedef union
{
  uint32 ulLongAccess;
  uint16 ushWordAccess[2];
  uint8  ucByteAccess[4];
}tLong;

#endif

