
#ifndef  BUSMSG_H
#define BUSMSG_H

#ifdef IBTCM_SW_ANPASSUNGEN
#else
   #include "Std_Types.hpp"
#endif

#include "busmsgX.hpp"

#define GETbNoWarnPartSurvVL()  ( GETbNoWarnPartSurv(BUSMSG_TYRE_VL) )
#define GETbNoWarnPartSurvVR()  ( GETbNoWarnPartSurv(BUSMSG_TYRE_VR) )
#define GETbNoWarnPartSurvHL()  ( GETbNoWarnPartSurv(BUSMSG_TYRE_HL) )
#define GETbNoWarnPartSurvHR()  ( GETbNoWarnPartSurv(BUSMSG_TYRE_HR) )

#endif
