#ifndef _state_bz_X_H
#define _state_bz_X_H

#define cER_FINISH                                              ((uint16)0x0001)
#define cTO_MUCH_RE                                             ((uint16)0x0002)
#define cER_LEARNING                                            ((uint16)0x0004)
#define cEIGENRAD                                               ((uint16)0x0008)
#define cZUGEORDNET                                             ((uint16)0x0010)
#define cWA_FINISH                                              ((uint16)0x0020)
#define cHIST_PRELOAD                                           ((uint16)0x0040)
#define cZO_FINISH                                              ((uint16)0x0080)
#define cWA_STARTED                                             ((uint16)0x0100)
#define cRESERVED_BIT9                                          ((uint16)0x0200)
#define cDTC_INACTIVE                                           ((uint16)0x0400)
#define cTEILEIGENRAD                                           ((uint16)0x0800)
#define cZO_TIMEOUT                                             ((uint16)0x1000)
#define cALL_ER_PRESSURE_RX                                     ((uint16)0x2000)
#define cSEND_RE_DATA_ON_CAN                                    ((uint16)0x4000)
#define cRESERVED_BIT15                                         ((uint16)0x8000)
#define cBZ_ALLE_BITS                                           ((uint16)0xffff)

extern void    InitBZ                    (void);
extern void    SetBitBetriebszustandBZ   (uint16 ushBitMask);
extern void    ClearBitBetriebszustandBZ (uint16 ushBitMask);
extern boolean bGetBitBetriebszustandBZ  (uint16 ushBitMask);
extern uint16  ushGetBetriebszustandBZ   (uint16 ushBitMask);
extern void    EvVehicleSpeedChangedBZ   (uint16 ushNewVehicleSpeed);

#pragma PRQA_NO_SIDE_EFFECTS bGetBitBetriebszustandBZ
#pragma PRQA_NO_SIDE_EFFECTS ushGetBetriebszustandBZ

#endif
