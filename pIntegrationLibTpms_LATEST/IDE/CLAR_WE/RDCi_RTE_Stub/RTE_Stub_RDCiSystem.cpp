

#include "RTE_Stub_RDCiSystem.h"
#include "RTE_Stub_Output.h"
#include "RTE_Stub_JumpTableX.h"

void TriggerRunnableCyclicRDCiTask(void)
{

  RDCi_RCyclicRDCiTask_001( Rte_Inst_CtApHufTpmsSWC);

  RTE_Stub_CyclicOutputFunction();
}

