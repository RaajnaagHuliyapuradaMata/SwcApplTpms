

#if !defined(EA_A709813F_B0B0_4903_A37E_B11DDE5BE46E__INCLUDED_)
#define EA_A709813F_B0B0_4903_A37E_B11DDE5BE46E__INCLUDED_

#include "Tpms_Rte_Data_Type.hpp"

extern void IDOM(void);
extern void InitIDOM(void);
extern uint8 GETucOffset(void);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char GETbStoersender(void);
#endif

extern boolean GETbStoersenderFf(void);
extern boolean GETbStoersenderZeit(void);
extern void SetRFinTime(void);

#endif

