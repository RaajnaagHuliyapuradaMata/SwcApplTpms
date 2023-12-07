#ifndef Platform_Types_h
#define Platform_Types_h
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COMMONASR_CANOEEMU_IMPL_PLATFORMTYPES_VERSION                     0x0401
#define COMMONASR_CANOEEMU_IMPL_PLATFORMTYPES_RELEASE_VERSION               0x00
#define PLATFORM_VENDOR_ID                                                    1u

#define PLATFORM_AR_RELEASE_MAJOR_VERSION                                   (4u)
#define PLATFORM_AR_RELEASE_MINOR_VERSION                                   (0u)
#define PLATFORM_AR_RELEASE_PATCH_VERSION                                   (3u)
#define PLATFORM_SW_MAJOR_VERSION                                           (4u)
#define PLATFORM_SW_MINOR_VERSION                                           (1u)
#define PLATFORM_SW_PATCH_VERSION                                           (0u)
#define CPU_TYPE_8                                                             8
#define CPU_TYPE_16                                                           16
#define CPU_TYPE_32                                                           32
#define MSB_FIRST                                                              0
#define LSB_FIRST                                                              1
#define HIGH_BYTE_FIRST                                                        0
#define LOW_BYTE_FIRST                                                         1

#ifndef TRUE
#define TRUE                                                                   1
#endif

#ifndef FALSE
#define FALSE                                                                  0
#endif

#define CPU_TYPE                                                     CPU_TYPE_32
#define CPU_BIT_ORDER                                                  LSB_FIRST
#define CPU_BYTE_ORDER                                            LOW_BYTE_FIRST

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef unsigned char      boolean;
typedef signed char        sint8;
typedef unsigned char      uint8;
typedef signed short       sint16;
typedef unsigned short     uint16;
typedef signed long        sint32;
typedef unsigned long      uint32;
typedef signed long long 	sint64;
typedef unsigned long long uint64;
typedef signed char        sint8_least;
typedef unsigned char      uint8_least;
typedef signed short       sint16_least;
typedef unsigned short     uint16_least;
typedef signed long        sint32_least;
typedef unsigned long      uint32_least;
typedef float              float32;
typedef double             float64;

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

