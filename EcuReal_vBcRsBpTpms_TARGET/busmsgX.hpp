#ifndef  BUSMSG_X_H
#define BUSMSG_X_H

#define BUSMSG_NUMBER_OF_TYRES    ( (uint8) 4 )
#define BUSMSG_TYRE_VL            ( (uint8) 0 )
#define BUSMSG_TYRE_VR            ( (uint8) 1 )
#define BUSMSG_TYRE_HL            ( (uint8) 2 )
#define BUSMSG_TYRE_HR            ( (uint8) 3 )
#define BUSMSG_WARN_UNKNOWN        ( (uint8) 0 )
#define BUSMSG_WARN_NOMINAL        ( (uint8) 1 )
#define BUSMSG_WARN_HARD           ( (uint8) 2 )
#define BUSMSG_WARN_SOFT           ( (uint8) 3 )
#define BUSMSG_WARN_PUNCTURE       ( (uint8) 4 )
#define BUSMSG_TEMPERATURE_NO_WARNING       ((uint8) 0U)
#define BUSMSG_TYREPRESS_VALID     ( (uint8) 0 )
#define BUSMSG_TYREPRESS_INVALID   ( (uint8) 1 )
#define BUSMSG_NUMBER_OF_TEXTFLAGS ( (uint8) 6 )
#define BUSMSG_TEXTFLAG_1          ( (uint8) 0 )
#define BUSMSG_TEXTFLAG_2          ( (uint8) 1 )
#define BUSMSG_TEXTFLAG_3          ( (uint8) 2 )
#define BUSMSG_TEXTFLAG_4          ( (uint8) 3 )
#define BUSMSG_TEXTFLAG_5          ( (uint8) 4 )
#define BUSMSG_TEXTFLAG_6          ( (uint8) 5 )
#define BUSMSG_GAP1_DEFAULT        ( (uint8) 0x3FU )
#define TPMIR_NO_INDICATION      0x00
#define TPMIR_AFTER_LEVEL_3      0x03
#define cInvalidPressureCAN      0xFF
#define cInvalidTemperatureCAN   0xFF

extern void BusMsgInit(void);
extern void BusMsgClr(void);
extern void BusMsgDoTeleFinished(void);
extern void BusMsgTemperatureClear(void);
extern void BusMsgDetermineTemperatures(void);
extern void BusMsgPutTemperature(uint8 ucId, uint8 ucTemperature);
extern uint8 BusMsgGetTemperature(uint8 ucId);
extern void  BusMsgPutTyrePressUncomp(uint8 ucId, uint8 ucpress);
extern uint8 BusMsgGetTyrePressUncomp(uint8 ucId);
extern void    BusMsgPutTemperatureWarning(uint8 ucId, boolean BO_IsTemperatureWarningActive);
extern boolean BusMsgGetTemperatureWarning(uint8 ucId);
extern void    BusMsgPutWarning(uint8 ucId, uint8 ucwarning);
extern uint8   BusMsgGetWarning(uint8 ucId);
extern void    BusMsgPutTyrePressValidVL(boolean bstate);
extern boolean BusMsgGetTyrePressValidVL(void);
extern void    BusMsgPutTyrePressValidVR(boolean bstate);
extern boolean BusMsgGetTyrePressValidVR(void);
extern void    BusMsgPutTyrePressValidHL(boolean bstate);
extern boolean BusMsgGetTyrePressValidHL(void);
extern void    BusMsgPutTyrePressValidHR(boolean bstate);
extern boolean BusMsgGetTyrePressValidHR(void);
extern void    BusMsgPutTextflag(uint8 ucId, boolean bstate);
extern boolean BusMsgGetTextflag(uint8 ucId);

#pragma PRQA_NO_SIDE_EFFECTS BusMsgGetTextflag

#endif

