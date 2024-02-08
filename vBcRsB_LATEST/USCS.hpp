#pragma once
/******************************************************************************/
/* File   : USCS.hpp                                                          */
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

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
struct CT{
   unsigned char   ucPMinAbs;
   unsigned char   aucPSollMin[ucSumWEc];
   unsigned char   aucPSoll[ucSumWEc];
     signed char   ascTSoll[ucSumWEc];
   unsigned short  aushMSoll[ucSumWEc];
   unsigned char   aucPWarm[ucSumWEc];
};

union CDA{
  struct CT tCalTab;
  unsigned char ucByte[sizeof(struct CT)];
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern union CDA tCDA;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern unsigned char  ucGetPMinCS         (void);
extern unsigned char  ucPutPMinCS         (unsigned char ucPMin, unsigned char ucMode);
extern unsigned char  ucGetPSollCS        (unsigned char ucIdX);
extern unsigned short ushGetMSollCS       (unsigned char ucIdX);
extern   signed char  scGetTSollCS        (unsigned char ucIdX);
extern unsigned char  ucPutCalTabVectorCS (unsigned char ucIdX, unsigned char ucP, signed char scT, unsigned short ushM);
extern unsigned char  ucPutPSollMinCS     (unsigned char ucIdX, unsigned char ucP, unsigned char ucMode);
extern void           InitCS              (unsigned char ucInit);
extern unsigned char  ucGetPwarmCS        (unsigned char ucIdX);
extern void           PutPwarmCS          (unsigned char Pwarm, unsigned char ucIdX);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char  ucGetPSollMinCS     (unsigned char ucIdX);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

