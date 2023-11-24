

#ifndef _speed_ccm_X_H
#define _speed_ccm_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

#define cSCC_STATE_SPEED_CCM_ENABLED                ( (uint8) 0x01u)
#define cSCC_STATE_PWF_FAHREN                       ( (uint8) 0x02u)

#define cSCC_STATE_WP_KNOWN                         ( (uint8) 0x04u)
#define cSCC_STATE_P_TOO_LOW                        ( (uint8) 0x08u)
#define cSCC_STATE_V_TOO_HIGH                       ( (uint8) 0x10u)
#define cSCC_STATE_DISPLAY_CCM_2158                 ( (uint8) 0x20u)
#define cSCC_STATE_DISPLAY_CCM_2159                 ( (uint8) 0x40u)
#define cSCC_STATE_DISPLAY_CCM_2159_IN_CUR_DRIV_CYC ( (uint8) 0x80u)

extern void   InitSCC(void);
extern uint8  ucGetStateSCC( uint8 ucMask);
extern void   MainSCC( Rte_Instance self);

extern void   GetSpeedCcmValSCC_debug( uint8 * pucState, uint16 * pushSpeedVmaxTime, uint16 * pushSpeedCcmThFa, uint16 * pushSpeedCcmThRa);

#ifdef __cplusplus
}
#endif

#endif
