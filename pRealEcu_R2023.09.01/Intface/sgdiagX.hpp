#ifndef _sgdiag_X_H
#define _sgdiag_X_H

#include "tss_stdx.hpp"
#include "sgdiag_CFG.hpp"

extern const uint8 ucReAusfallERRc[cAnzRad];

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern boolean GETbVBatLowDI(void);
extern boolean GETbVBatHighDI(void);
extern boolean GETbVBatSuspectDI(void);
extern boolean GETbStopVDiagDI(void);
extern boolean GETbRAMErrorDI(void);
extern boolean GETbROMErrorDI(void);
extern boolean GETbHfRecDemErrDI(void);
extern boolean GETbHfRecRssiErrDI(void);
extern boolean GETbWUFailedDI(void);
extern boolean GETbWUDefectDI(void);
extern void PUTbWUFailedDI(boolean bWUFailed);
extern void PUTbWUDefectDI(boolean bWUDefect);
extern boolean GETbVBatLowTxOffDI(void);
extern void SelfDiag(void);
extern void InitAfterKl15OnDI(void);
extern void StartCurrentDiagnostic(void);
extern void StopVDiag(void);
#endif

extern uint16 GETusMaxFolgeAusfallEE(void);

#endif

