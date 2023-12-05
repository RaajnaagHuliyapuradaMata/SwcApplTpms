#ifndef _ee_erfs_tsa_block_X_H
#define _ee_erfs_tsa_block_X_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "tss_stdx.h"

#include "Rte_CtApHufTpmsSWC.h"

extern void InitErfsTsaBlockEE(Rte_Instance self);
extern uint8 GetTsaDataEE(Rte_Instance self, uint8 i);
extern void PutTsaDataEE(Rte_Instance self, uint8 x, uint8 i);
extern void    ClearErfsTsaBlockWriteMeEE(void);
extern boolean bGetErfsTsaBlockWriteMeEE(void);
extern void    SetErfsTsaBlockWriteMeEE(void);

#ifdef __cplusplus
}
#endif

#endif
