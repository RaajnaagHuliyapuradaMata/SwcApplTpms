#ifndef COMPILER_H
#define COMPILER_H
/******************************************************************************/
/* File   : Compiler.h                                                        */
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
#include "Compiler_Cfg.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COMMONASR_CANOEEMU_IMPL_COMPABSTRACT_ANSI_VERSION                 0x0403
#define COMMONASR_CANOEEMU_IMPL_COMPABSTRACT_ANSI_RELEASE_VERSION           0x00

#define COMPILER_VENDOR_ID                                                    1u

#define COMPILER_AR_RELEASE_MAJOR_VERSION                                   (4u)
#define COMPILER_AR_RELEASE_MINOR_VERSION                                   (0u)
#define COMPILER_AR_RELEASE_PATCH_VERSION                                   (3u)

#define COMPILER_SW_MAJOR_VERSION                                           (4u)
#define COMPILER_SW_MINOR_VERSION                                           (3u)
#define COMPILER_SW_PATCH_VERSION                                           (0u)

#define _MICROSOFT_C_CANOE_
#define AUTOMATIC
#define TYPEDEF

#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

#define INLINE _inline
#define LOCAL_INLINE static _inline
#define FUNC(rettype, memclass) rettype memclass
#define FUNC_P2CONST(rettype, ptrclass, memclass) const memclass rettype ptrclass *
#define FUNC_P2VAR(rettype, ptrclass, memclass) memclass rettype ptrclass *
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * memclass
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * memclass
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype ptrclass * const memclass
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * const memclass
#define P2FUNC(rettype, ptrclass, fctname) rettype (ptrclass * fctname)

#ifdef _EcuVirtual
#ifndef CONST
#define CONST(type, memclass) const type memclass
#endif
#else
#define CONST(type, memclass) const type memclass
#endif

#define VAR(vartype, memclass) vartype memclass

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif

