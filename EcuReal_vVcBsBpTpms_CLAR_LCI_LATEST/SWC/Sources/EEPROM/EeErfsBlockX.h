#ifndef _ee_erfs_block_X_H
#define _ee_erfs_block_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"

extern void    InitErfsBlockEE(Rte_Instance self);
extern uint8   GETucErfsInitializerEE(Rte_Instance self);
extern void    PUTucErfsInitializerEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedSeasonEE(Rte_Instance self);
extern void    PUTSelectedSeasonEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedLoadStateEE(Rte_Instance self);
extern void    PUTSelectedLoadStateEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedSuTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedSuTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedWiTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedWiTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETSelectedAutoTyreIndexEE(Rte_Instance self);
extern void    PUTSelectedAutoTyreIndexEE(Rte_Instance self, uint8 x);
extern uint8   GETAutomaticSelectionFailedStatusEE(Rte_Instance self);
extern void    PUTAutomaticSelectionFailedStatusEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreSelectionActiveEE(Rte_Instance self);
extern void    PUTTyreSelectionBckgrdEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreSelectionBckgrdEE(Rte_Instance self);
extern void    PUTTyreSelectionActiveEE(Rte_Instance self, uint8 x);
extern uint8   GETPlausiInitErrorEE(Rte_Instance self);
extern void    PUTPlausiInitErrorEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreChangedEE(Rte_Instance self);
extern void    PUTTyreChangedEE(Rte_Instance self, uint8 x);
extern uint8   GETStManSelectionEE(Rte_Instance self);
extern void    PUTStManSelectionEE(Rte_Instance self, uint8 x);
extern uint8   GETIdrMessageEE(Rte_Instance self);
extern void    PUTIdrMessageEE(Rte_Instance self, uint8 x);
extern uint8   GETInvalidTyreListEE(Rte_Instance self);
extern void    PUTInvalidTyreListEE(Rte_Instance self, uint8 x);
extern uint8   GETStSelectTyreEE(Rte_Instance self);
extern void    PUTStSelectTyreEE(Rte_Instance self, uint8 x);
extern uint8   GETUseSavedHistRidDataCtEE(Rte_Instance self);
extern void    PUTUseSavedHistRidDataCtEE(Rte_Instance self, uint8 x);
extern uint8   GETTyreDimDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void    PUTTyreDimDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8   GETTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x);
extern void    PUTTyreDOTDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 y);
extern uint8   GETCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 Season);
extern void    PUTCurErfsTyreDataEE(Rte_Instance self, uint8 i, uint8 x, uint8 Season);
extern void    SetErfsBlockWriteMeEE(void);
extern boolean bGetErfsBlockWriteMeEE(void);
extern void    ClearErfsBlockWriteMeEE(void);

#ifdef __cplusplus
}
#endif

#endif
