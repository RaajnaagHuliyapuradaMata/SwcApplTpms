#pragma once
/******************************************************************************/
/* File   : SwcApplTpms_NvM.hpp                                               */
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
#define NVM_CATEGORY_01                  0U
#define NVM_CATEGORY_02                  1U
#define NVM_CATEGORY_03                  2U
#define NVM_CATEGORY_04                  3U
#define NVM_CATEGORY_05                  4U
#define NVM_CATEGORY_06                  5U
#define NVM_CATEGORY_07                  6U
#define NVM_CATEGORY_08                  7U
#define NVM_CATEGORY_09                  8U
#define NVM_CATEGORY_10                  9U
#define NVM_CAT01_NUMBER_OF_MEMBERS 10U
#define NVM_CAT01_IDX01_REAL_SIZE    1U
#define NVM_CAT01_IDX02_REAL_SIZE   25U
#define NVM_CAT01_IDX03_REAL_SIZE    4U
#define NVM_CAT01_IDX04_REAL_SIZE    1U
#define NVM_CAT01_IDX05_REAL_SIZE    2U
#define NVM_CAT01_IDX06_REAL_SIZE    8U
#define NVM_CAT01_IDX07_REAL_SIZE    5U
#define NVM_CAT01_IDX08_REAL_SIZE    1U
#define NVM_CAT01_IDX09_REAL_SIZE    1U
#define NVM_CAT01_IDX10_REAL_SIZE    4U

#define NVM_CAT01_SIZE_BYTES (NVM_CAT01_IDX01_REAL_SIZE + \
                              NVM_CAT01_IDX02_REAL_SIZE + \
                              NVM_CAT01_IDX03_REAL_SIZE + \
                              NVM_CAT01_IDX04_REAL_SIZE + \
                              NVM_CAT01_IDX05_REAL_SIZE + \
                              NVM_CAT01_IDX06_REAL_SIZE + \
                              NVM_CAT01_IDX07_REAL_SIZE + \
                              NVM_CAT01_IDX08_REAL_SIZE + \
                              NVM_CAT01_IDX09_REAL_SIZE + \
                              NVM_CAT01_IDX10_REAL_SIZE)

#define NVM_CAT02_IDX01              0U
#define NVM_CAT02_IDX02              1U
#define NVM_CAT02_IDX03              2U
#define NVM_CAT02_IDX04              3U
#define NVM_CAT02_IDX05              4U
#define NVM_CAT02_IDX06              5U
#define NVM_CAT02_IDX07              6U
#define NVM_CAT02_IDX08              7U
#define NVM_CAT02_IDX09              8U
#define NVM_CAT02_IDX10              9U
#define NVM_CAT02_IDX11             10U
#define NVM_CAT02_IDX12             11U

#define NVM_CAT02_NUMBER_OF_MEMBERS 12U

#define NVM_CAT02_IDX01_REAL_SIZE    1U
#define NVM_CAT02_IDX02_REAL_SIZE    1U
#define NVM_CAT02_IDX03_REAL_SIZE   10U
#define NVM_CAT02_IDX04_REAL_SIZE   10U
#define NVM_CAT02_IDX05_REAL_SIZE   10U
#define NVM_CAT02_IDX06_REAL_SIZE    1U
#define NVM_CAT02_IDX07_REAL_SIZE    1U
#define NVM_CAT02_IDX08_REAL_SIZE    1U
#define NVM_CAT02_IDX09_REAL_SIZE    1U
#define NVM_CAT02_IDX10_REAL_SIZE    1U
#define NVM_CAT02_IDX11_REAL_SIZE    3U
#define NVM_CAT02_IDX12_REAL_SIZE   12U

#define NVM_CAT02_SIZE_BYTES (NVM_CAT02_IDX01_REAL_SIZE + \
                              NVM_CAT02_IDX02_REAL_SIZE + \
                              NVM_CAT02_IDX03_REAL_SIZE + \
                              NVM_CAT02_IDX04_REAL_SIZE + \
                              NVM_CAT02_IDX05_REAL_SIZE + \
                              NVM_CAT02_IDX06_REAL_SIZE + \
                              NVM_CAT02_IDX07_REAL_SIZE + \
                              NVM_CAT02_IDX08_REAL_SIZE + \
                              NVM_CAT02_IDX09_REAL_SIZE + \
                              NVM_CAT02_IDX10_REAL_SIZE + \
                              NVM_CAT02_IDX11_REAL_SIZE + \
                              NVM_CAT02_IDX12_REAL_SIZE)

#define NVM_CAT03_IDX01              0U
#define NVM_CAT03_IDX02              1U
#define NVM_CAT03_NUMBER_OF_MEMBERS 11U
#define NVM_CAT03_IDX01_REAL_SIZE   16U
#define NVM_CAT03_IDX02_REAL_SIZE    4U
#define NVM_CAT03_IDX03_REAL_SIZE   25U
#define NVM_CAT03_IDX04_REAL_SIZE    2U
#define NVM_CAT03_IDX05_REAL_SIZE    1U
#define NVM_CAT03_IDX06_REAL_SIZE    1U
#define NVM_CAT03_IDX07_REAL_SIZE    1U
#define NVM_CAT03_IDX08_REAL_SIZE    1U
#define NVM_CAT03_IDX09_REAL_SIZE   41U
#define NVM_CAT03_IDX10_REAL_SIZE    2U
#define NVM_CAT03_IDX11_REAL_SIZE    2U

#define NVM_CAT03_SIZE_BYTES (NVM_CAT03_IDX01_REAL_SIZE + \
                              NVM_CAT03_IDX02_REAL_SIZE + \
                              NVM_CAT03_IDX03_REAL_SIZE + \
                              NVM_CAT03_IDX04_REAL_SIZE + \
                              NVM_CAT03_IDX05_REAL_SIZE + \
                              NVM_CAT03_IDX06_REAL_SIZE + \
                              NVM_CAT03_IDX07_REAL_SIZE + \
                              NVM_CAT03_IDX08_REAL_SIZE + \
                              NVM_CAT03_IDX09_REAL_SIZE + \
                              NVM_CAT03_IDX10_REAL_SIZE + \
                              NVM_CAT03_IDX11_REAL_SIZE)

#define NVM_CAT04_IDX01              0U
#define NVM_CAT04_IDX02              1U
#define NVM_CAT04_IDX03              2U
#define NVM_CAT04_IDX04              3U
#define NVM_CAT04_IDX05              4U

#define NVM_CAT04_NUMBER_OF_MEMBERS 5U

#define NVM_CAT04_IDX01_REAL_SIZE    1U
#define NVM_CAT04_IDX02_REAL_SIZE    1U
#define NVM_CAT04_IDX03_REAL_SIZE    1U
#define NVM_CAT04_IDX04_REAL_SIZE    1U
#define NVM_CAT04_IDX05_REAL_SIZE   16U

#define NVM_CAT04_SIZE_BYTES (NVM_CAT04_IDX01_REAL_SIZE + \
                              NVM_CAT04_IDX02_REAL_SIZE + \
                              NVM_CAT04_IDX03_REAL_SIZE + \
                              NVM_CAT04_IDX04_REAL_SIZE + \
                              NVM_CAT04_IDX05_REAL_SIZE)

#define NVM_CAT05_IDX01              0U
#define NVM_CAT05_IDX02              1U
#define NVM_CAT05_IDX03              2U
#define NVM_CAT05_IDX04              3U
#define NVM_CAT05_IDX05              4U
#define NVM_CAT05_IDX06              5U
#define NVM_CAT05_IDX07              6U
#define NVM_CAT05_IDX08              7U
#define NVM_CAT05_IDX09              8U
#define NVM_CAT05_IDX10              9U

#define NVM_CAT05_NUMBER_OF_MEMBERS 10U

#define NVM_CAT05_IDX01_REAL_SIZE    1U
#define NVM_CAT05_IDX02_REAL_SIZE    1U
#define NVM_CAT05_IDX03_REAL_SIZE    1U
#define NVM_CAT05_IDX04_REAL_SIZE    1U
#define NVM_CAT05_IDX05_REAL_SIZE    1U
#define NVM_CAT05_IDX06_REAL_SIZE    1U
#define NVM_CAT05_IDX07_REAL_SIZE    1U
#define NVM_CAT05_IDX08_REAL_SIZE    1U
#define NVM_CAT05_IDX09_REAL_SIZE    1U
#define NVM_CAT05_IDX10_REAL_SIZE   39U

#define NVM_CAT05_SIZE_BYTES  (NVM_CAT05_IDX01_REAL_SIZE + \
                               NVM_CAT05_IDX02_REAL_SIZE + \
                               NVM_CAT05_IDX03_REAL_SIZE + \
                               NVM_CAT05_IDX04_REAL_SIZE + \
                               NVM_CAT05_IDX05_REAL_SIZE + \
                               NVM_CAT05_IDX06_REAL_SIZE + \
                               NVM_CAT05_IDX07_REAL_SIZE + \
                               NVM_CAT05_IDX08_REAL_SIZE + \
                               NVM_CAT05_IDX09_REAL_SIZE + \
                               NVM_CAT05_IDX10_REAL_SIZE)

#define NVM_CAT06_NUMBER_OF_MEMBERS 9U
#define NVM_CAT06_IDX01_REAL_SIZE   1U
#define NVM_CAT06_IDX02_REAL_SIZE   1U
#define NVM_CAT06_IDX03_REAL_SIZE   1U
#define NVM_CAT06_IDX04_REAL_SIZE   1U
#define NVM_CAT06_IDX05_REAL_SIZE   1U
#define NVM_CAT06_IDX06_REAL_SIZE   1U
#define NVM_CAT06_IDX07_REAL_SIZE   1U
#define NVM_CAT06_IDX08_REAL_SIZE   1U
#define NVM_CAT06_IDX09_REAL_SIZE   40U

#define NVM_CAT06_SIZE_BYTES       (NVM_CAT06_IDX01_REAL_SIZE + \
                                    NVM_CAT06_IDX02_REAL_SIZE + \
                                    NVM_CAT06_IDX03_REAL_SIZE + \
                                    NVM_CAT06_IDX04_REAL_SIZE + \
                                    NVM_CAT06_IDX05_REAL_SIZE + \
                                    NVM_CAT06_IDX06_REAL_SIZE + \
                                    NVM_CAT06_IDX07_REAL_SIZE + \
                                    NVM_CAT06_IDX08_REAL_SIZE + \
                                    NVM_CAT06_IDX09_REAL_SIZE)

#define NVM_CAT07_NUMBER_OF_MEMBERS 1U
#define NVM_CAT07_IDX01_REAL_SIZE   24U
#define NVM_CAT07_SIZE_BYTES       (NVM_CAT07_IDX01_REAL_SIZE)
#define NVM_CAT08_NUMBER_OF_MEMBERS 1U
#define NVM_CAT08_IDX01_REAL_SIZE   24U
#define NVM_CAT08_SIZE_BYTES       (NVM_CAT08_IDX01_REAL_SIZE)
#define NVM_CAT09_NUMBER_OF_MEMBERS 1U
#define NVM_CAT09_IDX01_REAL_SIZE   32U
#define NVM_CAT09_SIZE_BYTES       (NVM_CAT09_IDX01_REAL_SIZE)
#define NVM_CAT10_IDX01              0U
#define NVM_CAT10_IDX02              1U
#define NVM_CAT10_IDX03              2U
#define NVM_CAT10_IDX04              3U
#define NVM_CAT10_NUMBER_OF_MEMBERS 4U
#define NVM_CAT10_IDX01_REAL_SIZE   1U
#define NVM_CAT10_IDX02_REAL_SIZE   1U
#define NVM_CAT10_IDX03_REAL_SIZE   1U
#define NVM_CAT10_IDX04_REAL_SIZE   1U

#define NVM_CAT10_SIZE_BYTES       (NVM_CAT10_IDX01_REAL_SIZE + \
                                    NVM_CAT10_IDX02_REAL_SIZE + \
                                    NVM_CAT10_IDX03_REAL_SIZE + \
                                    NVM_CAT10_IDX04_REAL_SIZE  )

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
extern void ReadBlock2Member         (uint8 ui8Categ, uint8 ui8Member, uint8 * pui8Target);
extern void WriteMember2Blocks       (uint8 ui8Categ, uint8 ui8Member, uint8 * pui8Target);
extern void InitEEAll                (void);
extern void EE_InconsistencyHandling (uint16 uiNvmCategoryConsistence);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

