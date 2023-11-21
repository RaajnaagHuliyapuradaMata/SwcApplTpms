#pragma once

#include "Std_Types.h"

typedef uint8  RawSensorTyrePresType;
typedef uint8  RawSensorTyreTempType;
typedef uint8  PhySensorTyrePresType;
typedef sint8  PhySensorTyreTempType;

#define cAnzAnt       ((uint8) 1)
#define cAnzRad       ((uint8) 4)
#define cAnzAchse     ((uint8) 2)
#define cRadPosVL     ((uint8) 0)
#define cRadPosVR     ((uint8) 1)
#define cRadPosHL     ((uint8) 2)
#define cRadPosHR     ((uint8) 3)
#define cRadPosUndef  ((uint8) 4)

#ifdef _EcuVirtual
#else
#ifndef NULL
#define NULL        ((void *)  0)
#endif
#endif

#define cNvmInitialized         ((uint8) 0xA8u)
#define FREQUENCY_433MHZ  ( (uint8) 0x00)
#define FREQUENCY_868MHZ  ( (uint8) 0x01)
#define FREQUENCY_315MHZ  ( (uint8) 0x02)
#define cMARKET_EU ((uint8) 0x00)
#define cMARKET_US ((uint8) 0x01)
#define cMARKET_RC ((uint8) 0x02)
#define cMARKET_J  ((uint8) 0x03)
#define cInvalidREid                ( (uint32)             0xffffffffu)
#define cInvalidREsuppId            ( (uint8)                    0xffu)
#define cInvalidREpressure          ( (PhySensorTyrePresType)    0xffu)
#define cInvalidREtemperature       ( (PhySensorTyreTempType)    0x7fu)
#define cInvalidRElifeTime          ( (uint8)                    0x00u)
#define cInvalidREstate             ( (uint8)                    0x00u)
#define cInvalidRSSIsum             ( (uint8)                    0x00u)
#define cInvalidWheelDir            ( (uint8)                    0xffu)
#define cInvalidTelType             ( (uint8)                    0xffu)
#define cInvalidTransMode           ( (uint8)                    0x00u)
#define cInvalidSensorDefect        ( (uint16)                 0x0000u)
#define cInvalidRollSwitch          ( (uint8)                    0x00u)
#define cInvalidRePalLookBackTime   ( (uint8)                    0xffu)
#define cInvalidRePalStatus         ( (uint8)                    0xffu)
#define cInvalidRePalStatusMdb      ( (uint16)                 0x0000u)
#define cInvalidOutdoorTemperature  ( (uint8)                    0x7fu)
#define cInvalidBatteryLevel        ( (uint8)                    0xffu)
#define cInvalidSignalToNoiseRatio  ( (uint8)                    0xffu)
#define cInvalidTemperatureWord     ( (sint16)                 0x7fffu)
#define cPresSensorOk               ( (uint8)                    0x00u)
#define cPresSensorError            ( (uint8)                    0x80u)
#define cPresSensorUnderflow        ( (uint8)                    0x81u)
#define cPresSensorOverflow         ( (uint8)                    0x82u)
#define cTempSensorOk               ( (uint8)                    0x00u)
#define cTempSensorError            ( (uint8)                    0x40u)
#define cTempSensorUnderflow        ( (uint8)                    0x41u)
#define cTempSensorOverflow         ( (uint8)                    0x42u)
#define cInitTemperature            ( (sint8) 20)
#define cInitAmbientPressure        ( (uint8) 40)
#define cMaxPressure                ( (uint8) 0xffu)
#define cRetError    ( (uint8) 0xFF)
#define cRetOk       ( (uint8) 0x00)
#define cDisable     ( (uint8) 0x00)
#define cEnable      ( (uint8) 0x01)
#define cMaskLoNibble ( (uint8) 0x0Fu)
#define cMaskHiNibble ( (uint8) 0xF0u)
