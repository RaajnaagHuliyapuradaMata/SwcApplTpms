#ifndef walloc_h
#define walloc_h

# ifdef __cplusplus
extern "C"
{
# endif

#include "WAllocX.h"

#define cWACtrlFixc   (uint8)0x01
#define cWACtrlBreakc (uint8)0x02
#define cWACtrlCyclic (uint8)0x04
#define cInitialState   (uint8) 0
#define cNoAxis         (uint8)0xCF
#define cFrontAxis      (uint8)0x10
#define cOtherAxis      (uint8)0x20
#define cBackAxis       (uint8)0x20
#define cNoSpin         (uint8)0x3F
#define cRightSpin      (uint8)0x40
#define cLeftSpin       (uint8)0x80
#define cNoWPos         (uint8)0xF0
#define cWP_RR          (uint8)0x08
#define cWP_RL          (uint8)0x04
#define cWP_FR          (uint8)0x02
#define cWP_FL          (uint8)0x01
#define cWuInDriveMode  (uint8)0xc0
#define cWPER 0x10
#define cFL (uint8) 0
#define cFR (uint8) 1
#define cRL (uint8) 2
#define cRR (uint8) 3
#define cTelegramLearnTimerValue  6
#define cMaxInvalidPermutation ((uint8) 4)

static boolean bSearchEigenraederWAL(uint16* ushErSlots);
static void DeleteForeignWheelsWAL(void);
static uint8 ucForceAutolocationWAL(Rte_Instance self);
static void PartialAllocationWAL(Rte_Instance self, uint16 ushSlots, uint8 ucNrOfErs, uint8* ucOpenPositions);
static boolean bFinishIfWheelsAreInDriveMode(void);
static uint8 ucSumCtID(uint8 ucMinCt, uint16 *ushRet);
static uint8 ucPutInZOM(const tRFTelType *ptInputWA);
static uint8 ucGetZOMWP(uint8 ucIx);
static uint8 ucSetHistory(Rte_Instance self, uint8 ucType);
static uint8 ucSetHistoryPartialWAL(Rte_Instance self, uint8 ucType, uint8 ucNoOfErs);
static uint8 ucIdsAreHistoricWAL(uint16 ushSlots);
static uint8 ucSearchWheelPositionsWAL(uint8 ucID, const tRFTelType * ptInputWA);
static uint8 ucGetFreeZOMPos(void);
static uint8 ucLowestProbe(uint16 ushException);
static void ClearZomWAL(uint8 ucIx);
static void SetWAStateZOChange(uint8 ucChangedPos);
static void PutIDToZOM(uint8 ucIx, const uint32 *p2ID);
static void AlignZomWAL(uint16 ushERSlot);
static void AlignInfoZomWAL(uint16 ushERSlot);
static void Put2Slot(const tRFTelType *ptInputWA, uint8 ucIx);
static void RestoreHistory(void);
static uint8 ucGetNextFreeCol(void);
static boolean bGetERState(void);
static boolean bGetZOState(void);

#ifdef AEC
static void ResetWP(void);
static void ResetAxis(void)
static uint8 ucSetWP(void);
static uint8 ucHWPfitSpin(uint8 ucWP, uint8 ucZOMIx);
#endif

static void SetNewWheelPosOfIdToDefaultValWAL(void);
static void SetNewWheelPosOfIdToUnchangedValWAL(void);
static uint8 ucCheckPermutationWAL(Rte_Instance self, const uint32 aulNewHistoryID[], const uint8 aucNewHistoryWP[]);

# ifdef __cplusplus
}
# endif

#endif
