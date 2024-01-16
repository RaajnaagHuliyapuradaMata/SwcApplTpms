#pragma once
/******************************************************************************/
/* File   : WnTypePar.hpp                                                     */
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
#include "USWarn.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cUSWAlgo_ParaByte0_EU                             ((unsigned char) 0x02)
#define cUSWAlgo_ParaByte1_EU                             ((unsigned char) 0x10)
#define cUSWAlgo_TResLimit_EU                             ((unsigned char)   25)
#define cUSWAlgo_HighPressThres                           ((unsigned char) 0xAE)
#define cUSWAlgo_AxImbSetThres                            ((unsigned char) 0x0E)
#define cUSWAlgo_AxImbResThres                            ((unsigned char) 0x06)
#define cUSWAlgo_ParaByte0_NAR                            ((unsigned char) 0x01)
#define cUSWAlgo_ParaByte1_NAR                            ((unsigned char) 0xE0)
#define cUSWAlgo_TResLimit_NAR                            ((unsigned char)   25)
#define cUSWAlgo_ParaByte0_ROW                            ((unsigned char) 0x01)
#define cUSWAlgo_ParaByte1_ROW                            ((unsigned char) 0xA2)
#define cUSWAlgo_TResLimit_ROW                            ((unsigned char)   25)
#define E_EU_KO_LEG                                       ((uint8)         0x01)
#define E_US_LEG_NON_EXTRA_LOAD_TIRES                     ((uint8)         0x02)
#define E_US_LEG_EXTRA_LOAD_TIRES                         ((uint8)         0x03)
#define E_PRC_LEG                                         ((uint8)         0x04)
#define E_INVALID_LEG                                     ((uint8)         0x05)

#ifdef WITH_UNUSED_WARNINGS
#define cAllWT_function   {bPMinDR, bAxImb, bFT, bDHW, bHardTDR, bHiP, bLowP, bEuF}
#define cWT_WNvector_map  {ucPMinc, ucAxImbc, ucFTc, ucDHWc, ucHardTc, ucHiPc, ucLowPc, ucEuFc}
#define ucPMinIxc         (unsigned char) 0
#define ucDHWIxc          (unsigned char) 3
#define ucSoftTIxc        (unsigned char) 6
#define ucAxImbIxc        (unsigned char) 1
#define ucFTIxc           (unsigned char) 2
#define ucHardTIxc        (unsigned char) 4
#define ucHardTVIxc       (unsigned char) 5
#define ucHiPIxc          (unsigned char) 5
#define ucEuFIxc          (unsigned char) 7
#define ucHWMaskc         (unsigned char) 0xAB
#define ucWWMaskc         (unsigned char) 0x40
#else
#define cAllWT_function   {&bPMinDR, &bEuF, &bTW, &bDHW,}
#define cWT_WNvector_map  {ucPMinc, ucEuFc, ucTWc, ucDHWc}
#define ucPMinIxc         (unsigned char) 0
#define ucDHWIxc          (unsigned char) 3
#define ucHiPIxc          (unsigned char) 4
#define ucEuFIxc          (unsigned char) 1
#define ucTWxc            (unsigned char) 2
#define ucHWMaskc         (unsigned char) 0x1F
#define ucWWMaskc         (unsigned char) 0x02
#endif

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
extern void          ResetM1Pressure (unsigned char i);
extern unsigned char bPMinDR         (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bAxImb          (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bDHW            (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bFT             (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bHardTDR        (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bLowP           (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bTSB            (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bEuF            (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bHiP            (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
extern unsigned char bTW             (struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char bHardTVDR(struct LocalWarnDat* ptLWD, unsigned char ucWarnCfg);
#endif
extern void Init_AxImbSuppressionCounter      (void);
extern void Start_AxImbSuppressionCounter     (void);
extern void Increment_AxImbSuppressionCounter (void);

#ifndef pb_ModulTest_02062003
#else
extern void PrintPMinCfg(void);
extern void PrintDHWCfg(void);
extern void PrintPFactorCfg(void);
extern void PrintFTCfg(void);
extern void PrintHTCfg(void);
extern void PrintHTVCfg(void);
extern void PrintSTCfg(void);
extern void PrintTSCfg(void);
#endif

#ifdef WITH_UNUSED_WARNINGS
static const unsigned char ucMaxWarnTypeWNc = 8;
#else
static const unsigned char ucMaxWarnTypeWNc = 4;
#endif


#ifdef pb_ModulTest_02062003
extern unsigned char  ucHystPMinc;
extern unsigned char  ucNegHystDHWc;
extern unsigned char  ucDifDHWc;
extern unsigned char  ucUSFactorPFc;
extern unsigned char  ucEUFactorPFc;
extern unsigned char  ucAdOnPFc;
extern unsigned char  ucNegHystPFc;
extern unsigned char  ucHystPFc;
extern unsigned char  ucThresFTc;
extern unsigned char  ucHystFTc;
extern unsigned char  ucThresHTc;
extern   signed char  scTDropHTc;
extern unsigned short ushMDropHTc;
extern unsigned char  ucHystHTc;
extern unsigned char  ucThresHTVc;
extern   signed char  scTDropHTVc;
extern unsigned short ushMDropHTVc;
extern unsigned char  ucSpeedLevelHTVc;
extern unsigned char  ucHystHTVc;
extern unsigned char  ucNegHystHTVc;
extern unsigned char  ucThresSTc;
extern   signed char  scTMaxSTc;
extern unsigned char  ucHystSTc;
extern unsigned char  ucNegHystSTc;
extern unsigned char  ucThresDefTSc;
extern   signed char  scTMaxTSc;
extern unsigned char  ucThresTSc;
extern unsigned char  uc05Dropc;
extern unsigned char  ucHyst05c;
extern unsigned char  ucFrikModec;
extern   signed char  scTResLimitc;
extern unsigned char  ucFilterTimeSTc;
extern unsigned char  ucTimeFilterPrescInMSc;
extern unsigned short ushCallFreqInMSWTc;
#else
#define ushCallFreqInMSWTc                                                  1000
#define ucHystPMinc                         (unsigned char)  0
#define ucNegHystPMinc                      (unsigned char)  (100 / ucPResInMBarc)
#define ucNegHystDHWc                       (unsigned char)  (150 / ucPResInMBarc)
#define ucDifDHWc                           (unsigned char)  (200 / ucPResInMBarc)
#define ucUSFactorPFc                       (unsigned char)  25
#define ucEUFactorPFc                       (unsigned char)  16
#define ucAdOnPFc                           (unsigned char)  4
#define ucNegHystPFc                        (unsigned char)  (150 / ucPResInMBarc)
#define ucHystPFc                           (unsigned char)  0
#define ucThresFTc                          (unsigned char)  (1400 / ucPResInMBarc)
#define ucHystFTc                           (unsigned char)  (200 / ucPResInMBarc)
#define ucThresHTc                          (unsigned char)  (500 / ucPResInMBarc)
#define scTDropHTc                          (  signed char)  40
#define ushMDropHTc                         (unsigned short) ((4.3 * ushGSFc) / ucPResInMBarc)
#define ucHystHTc                           (unsigned char)  (0 / ucPResInMBarc)
#define ucNegHystHTc                        (unsigned char)  (150 / ucPResInMBarc)
#define ucThresHTVc                         (unsigned char)  (400 / ucPResInMBarc)
#define ucSpeedLevelHTVc                    (unsigned char)  160
#define ucHystHTVc                          (unsigned char)  (0 / ucPResInMBarc)
#define ucNegHystHTVc                       (unsigned char)  (150 / ucPResInMBarc)
#define ucThresDefTSc                       (unsigned char)  (100 / ucPResInMBarc)
#define scTMaxTSc                           (  signed char)  30
#define ucThresTSc                          (unsigned char)  (300 / ucPResInMBarc)
#define ucNegHystwarmc                      (unsigned char)  (150 / ucPResInMBarc)
#define ucThresLowPc                        (unsigned char)  (1800 / ucPResInMBarc)
#define scTDropHTVc                         (signed char)    40
#define ushMDropHTVc                        (unsigned short) ((4.3 * ushGSFc) / ucPResInMBarc)
#define ucEuFactorEuFc                      (unsigned char)  20
#define ucThresLimitEuFc                    (unsigned char)  (150 / ucPResInMBarc)
#define u8_EU_MinPrs_mBar                   ((uint16)        1500U)
#define u8_EU_MinPrs_digits                 ((uint8)         (u8_EU_MinPrs_mBar / ucPResInMBarc))
#define u8_EU_Offroad_Press_mBar            ((uint16)        1600U)
#define u8_EU_Offroad_Press_digits          ((uint8)         (u8_EU_Offroad_Press_mBar / ucPResInMBarc))
#define u8_US_NonExtra_MinPrs_mBar          ((uint16)        1400U)
#define u8_US_Extra_MinPrs_mBar             ((uint16)        1600U)
#define u8_US_NonExtra_MinPrs_digits        ((uint8)         (u8_US_NonExtra_MinPrs_mBar / ucPResInMBarc))
#define u8_US_Extra_MinPrs_digits           ((uint8)         (u8_US_Extra_MinPrs_mBar / ucPResInMBarc))
#define u8_US_NonExtra_Offroad_Press_mBar   ((uint16)        1600U)
#define u8_US_Extra_Offroad_Press_mBar      ((uint16)        1800U)
#define u8_Us_NonExtra_Offroad_Press_digits ((uint8)         (u8_US_NonExtra_Offroad_Press_mBar / ucPResInMBarc))
#define u8_Us_Extra_Offroad_Press_digits    ((uint8)         (u8_US_Extra_Offroad_Press_mBar / ucPResInMBarc))
#define u8_US_Tolerance                     ((uint8)         4)
#define u8_US_Resolution                    ((uint8)         1)
#define u8_US_30Percent                     ((uint8)         30)
#define u8_US_25Percent                     ((uint8)         25)
#define u8_US_5Percent                      ((uint8)         5)
#define u8_PRC_Percent                      ((uint8)         25U)
#define u8_PRC_Tolerance_mBar               ((uint8)         100U)
#define u8_PRC_MinPrs_mBar                  ((uint16)        1500U)
#define u8_PRC_Tolerance_digits             ((uint8)         (u8_PRC_Tolerance_mBar / ucPResInMBarc))
#define u8_PRC_Percent_calc                 ((uint8)         (100U - u8_PRC_Percent))
#define u8_PRC_MinPrs_digits                ((uint8)         (u8_PRC_MinPrs_mBar / ucPResInMBarc))
#define u8_PRC_Offroad_Press_mBar           ((uint16)        1600U)
#define u8_PRC_Offroad_Press_digits         ((uint8)         (u8_PRC_Offroad_Press_mBar / ucPResInMBarc))
#define ucFrikModec                         (unsigned char)  1
#define scTResLimitc                        (signed char)    25
#define ucFilterTimeSTc                     (unsigned char)  54
#define ucTimeFilterPrescInMSc              ((unsigned char) (10000 / ushCallFreqInMSWTc))
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

