#ifndef EeZomBlockX_h
#define EeZomBlockX_h
/******************************************************************************/
/* File   : EeZomBlockX.h                                                     */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "tss_stdx.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "WallocX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cNvmRdciZom1_Size                     ( (uint16) (8 * sizeof(struct ZOMSlot)))

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct ZomNvmBlock_1{
   uint8             ucInitialized;
   struct ZOMSlot    tZomSlot[8];
   uint8             ucWato;
   uint8             ucWaState;
   uint8             ucWaIdChangeBits;
   uint8             ucPermutationState;
}tZomNvmBlock1Type;

typedef struct ZomNvmBlock_2{
   uint8             ucInitialized;
   struct ZOMSlot    tZomSlot[8];
}tZomNvmBlock2Type;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
extern void InitZomBlock1EE(Rte_Instance self);
extern void InitZomBlock2EE(Rte_Instance self);
extern uint8 GETucZomBlock1InitializeEE(Rte_Instance self);
extern void  PUTucZomBlock1InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern uint8 GETucZomBlock2InitializeEE(Rte_Instance self);
extern void  PUTucZomBlock2InitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern void PUTZomToNvmEE(Rte_Instance self, const uint8 pRamAdr[], uint16 ucLen);
extern void GETZomFromNvmEE(Rte_Instance self, uint8 pRamAdr[], uint16 ucLen);
extern void  PUTWatoEE(Rte_Instance self, uint8 x);
extern uint8 GETWatoEE(Rte_Instance self);
extern void  PUTAllocStateToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETAllocStateFromNvmEE(Rte_Instance self);
extern void  PUTWaIdChangeBitsToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETIdChangeBitsFromNvmEE(Rte_Instance self);
extern void  PUTucPermutationStateToNvmEE(Rte_Instance self, uint8 x);
extern uint8 GETucPermutationStateFromNvmEE(Rte_Instance self);
extern void    SetZomBlock1UpdateFlagEE(void);
extern void    SetZomBlock2UpdateFlagEE(void);
extern void    ClearZomBlock1UpdateFlagEE(void);
extern void    ClearZomBlock2UpdateFlagEE(void);
extern boolean bGetZomBlock1UpdateFlagEE(void);
extern boolean bGetZomBlock2UpdateFlagEE(void);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

