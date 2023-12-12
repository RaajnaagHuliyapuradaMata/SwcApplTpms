#ifndef EeHistoryBlockX_h
#define EeHistoryBlockX_h
/******************************************************************************/
/* File   : EeHistoryBlockX.h                                                 */
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
#include "WAllocX.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cNvmRdciZoHistoryWaIdSet_Size         ( (uint16) (cMaxLR * sizeof(uint32)))
#define cNvmRdciZoHistoryWaParam_Size         ( (uint16) sizeof(tWAParameter))

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct HistoryNvmBlock{
   uint8                       ucInitialized;
   uint32                      ulWAHistIDSet[cMaxLR];
   uint8                       ucWAHistWPSet[cMaxLR];
   uint8                       WAParamSet[sizeof(tWAParameter)];
   uint8                       ucAllocFailedCounter;
   uint8                       ucLowBat[cMaxLR];
   uint8                       ucRfIfStateMachine;
   uint16                      ushLastLocState;
   uint8                       Statusbar;
}tHistoryNvmBlockType;

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
extern void InitZoHistoryBlockEE(Rte_Instance self);
extern void ClearZoHistoryBlockUpdateFlagEE(void);
extern void SetZoHistoryBlockUpdateFlagEE( void) ;
extern boolean bGetZoHistoryBlockUpdateFlagEE(void);
extern uint8 GETucHistoryBlockInitializeEE(Rte_Instance self);
extern void PUTucHistoryBlockInitializeEE(Rte_Instance self, uint8 ucNvmInitialize);
extern uint8 GETucWAHistIDEE(Rte_Instance self, uint8 i);
extern void PUTucWAHistIDEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETucWAHistWPEE(Rte_Instance self, uint8 i);
extern void PUTucWAHistWPEE(Rte_Instance self, uint8 x, uint8 i);
extern uint8 GETtWAparamEE(Rte_Instance self, uint8 i);
extern void PUTtWAparamEE(Rte_Instance self, uint8 x, uint8 i);
extern uint16 GETLastLocStateEE (Rte_Instance self);
extern void PUTLastLocStateEE (Rte_Instance self, uint16 ushLastLocState);
extern uint8 GETucStatusbarEE(Rte_Instance self);
extern void PUTucStatusbarEE(Rte_Instance self, uint8 ucValue);
extern void PutAllocFailCounterToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCounter);
extern uint8 GetAllocFailCounterFromNvmZOMirrorblockEE(Rte_Instance self);
extern void PutCntLoBatToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCounter, uint8 ucCol);
extern uint8 GetCntLoBatFromNvmZOMirrorblockEE(Rte_Instance self, uint8 ucCol);
extern void PutRfIfStateMachineToNvmZOMirrorblockEE(Rte_Instance self, uint8 ucRfIfStateMachine);
extern uint8 GetRfIfStateMachineFromNvmZOMirrorblockEE(Rte_Instance self);
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

