

#ifndef IDOM_IF_H
#define IDOM_IF_H
#include "Tpms_Rte_Data_Type.hpp"

#ifdef BUILD_WITH_UNUSED_DATA
#define ucVehMovesc (uint8) 1
#endif

typedef struct{
  unsigned char ucApplState;
  unsigned short ushMaxFFCtVal;
  unsigned short ushCurBaseLevel;
}tIDOMInput;

extern void StartIDOMAlarm(uint16 ushNrOfCurFF);
extern void StopIDOMAlarm(void);
extern void BreakIDOMAlarm(void);
extern void GetIDOMInput(tIDOMInput * pIDOMInput);
extern uint16 GetParaOffset(void);
extern uint16 GetParaOverlaps(void);

#endif

