#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"

#define NOP_DELAY 1U

void Breakpoint(void);
void Nop(void);

void Breakpoint(void){
#ifdef HUF_DEBUG
  Nop();
#endif //HUF_DEBUG
}

void Nop(void){
#ifdef HUF_DEBUG
 uint8 ucLauf = 0U;

 while(ucLauf < NOP_DELAY)
 {
    ucLauf++;
 }
#endif //HUF_DEBUG
}

