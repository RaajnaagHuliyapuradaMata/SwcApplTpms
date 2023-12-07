#include "USCS.h"
#include "USWarn.h"

static const uint8 aucPMinCSc[]     = { ucPMinDefEUc,  ucPMinDefUSc  };
static const uint8 aucPSollMinCSc[] = { ucPSollDefEUc, ucPSollDefUSc };

tCalibrationTab tCDA;

uint8 ucGetPMinCS(void){
   return (tCDA.ucPMinAbs);
}

uint8 ucPutPMinCS(uint8 ucPMin, uint8 ucMode){
   uint8 ucRet;

   if(ucPMin >= aucPMinCSc[ucMode]){
    tCDA.ucPMinAbs = ucPMin;
      ucRet = 0xFF;
   }
   else{
    tCDA.ucPMinAbs = aucPMinCSc[ucMode];
      ucRet = 0;
   }
   return(ucRet);
}

uint8 ucGetPSollCS(uint8 ucIdX, uint8 ucWheelPos){
   uint8 ucRet;

   if(ucWheelPos < cRadPosUndef){
      ucRet = tCDA.aucPSoll[cIxForWpSpecDataStorage][ucWheelPos];
   }
   else{
      if(ucIdX < cAnzRad){
      ucRet = tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX];
      }
      else{
      ucRet = (uint8) 0xff;
      }
   }
   return ucRet;
}

sint8 scGetTSollCS(uint8 ucIdX, uint8 ucWheelPos){
   sint8 scRet;
   if(ucWheelPos < cRadPosUndef){
      scRet = tCDA.ascTSoll[cIxForWpSpecDataStorage][ucWheelPos];
   }
   else{
      if(ucIdX < cAnzRad){
      scRet = tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX];
      }
      else{
      scRet = (sint8) 127;
      }
   }
   return scRet;
}

uint16 ushGetMSollCS(uint8 ucIdX){
   uint16 ushRet;
   if(ucIdX < cAnzRad){
      ushRet = tCDA.aushMSoll[ucIdX];
   }
   else{
      ushRet = 0;
   }
   return ushRet;
}

uint8 ucGetPinitTreifenCS(uint8 ucIdX){
   uint8 ucRet;
   if(ucIdX < cAnzRad){
      ucRet = tCDA.aucPinitTreifen[ucIdX];
   }
   else{
      ucRet = (uint8) 0xff;
   }
   return ucRet;
}

sint8 scGetTreifenCS(uint8 ucIdX){
   sint8 scRet;
   if(ucIdX < cAnzRad){
      scRet = tCDA.ascTreifen[ucIdX];
   }
   else{
      scRet = 127;
   }
   return scRet;
}

uint8 ucPutPinitTreifenCS(uint8 ucIdX, sint8 scTreifen){
   uint8 ucRet = 0xff;
   sint8 scTDropPoint;
   uint8 ucPinitTDropPoint, ucPinitTreifen_l;
   uint8 ucParDrop = GetDropIsoCodVal();
   if(ucIdX < cAnzRad){
      if(scTreifen == 127){
      ucRet = (uint8) 0;
      }
      else{
      if(scGetTambCS(ucIdX) > 0){
        scTDropPoint = (scGetTambCS(ucIdX) + (sint8) (((ucParDrop >> 4) & 0x0fu) * 5));
      }
      else{
        scTDropPoint = (sint8) (((ucParDrop >> 4) & 0x0fu) * 5);
      }
      ucPinitTDropPoint = ucPfT( tCDA.aushMSoll[ucIdX], scTDropPoint, ucGetPambCS(ucIdX));
      ucPinitTreifen_l = ucPfT( tCDA.aushMSoll[ucIdX], scTreifen, ucGetPambCS(ucIdX));
      if(scTreifen > scTDropPoint){
        tCDA.aucPinitTreifen[ucIdX] = (ucPinitTreifen_l - (uint8) (((((ucPinitTreifen_l - ucPinitTDropPoint) * (uint16) (ucParDrop & 0x0fu) * 1000) / 1500) + 5) / 10));
      }
      else{
        tCDA.aucPinitTreifen[ucIdX] = ucPinitTreifen_l;
      }
      tCDA.ascTreifen[ucIdX]        = scTreifen;
      }
   }
   else{
      ucRet = (uint8) 0;
   }
   return ucRet;
}

uint8 ucPutCalTabVectorCS(uint8 ucIdX, uint8 ucP, sint8 scT, uint8 ucWheelPos){
   uint8 ucRet = 0xFF;
   if(ucIdX < cAnzRad){
      if(tCDA.aucPSollMin[ucIdX] == 0){
      tCDA.aucPSollMin[ucIdX] = aucPSollMinCSc[ ucGetUSEUCode() ];
      }
      if((ucP == cInvalidREpressure) || (scT == cInvalidREtemperature)){
      tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = tCDA.aucPSollMin[ucIdX];
      tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = tCDA.ascEnvTemp[ucIdX];
      if(ucWheelPos < cRadPosUndef){
        tCDA.aucPSoll[cIxForWpSpecDataStorage][ucWheelPos] = tCDA.aucPSollMin[ucIdX];
        tCDA.ascTSoll[cIxForWpSpecDataStorage][ucWheelPos] = tCDA.ascEnvTemp[ucIdX];
      }
      }
      else{
      if(ucP >= tCDA.aucPSollMin[ucIdX]){
          if(ucWheelPos < cRadPosUndef){
          tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = ucP;
          tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = scT;
          tCDA.aucPSoll[cIxForWpSpecDataStorage][ucWheelPos] = ucP;
          tCDA.ascTSoll[cIxForWpSpecDataStorage][ucWheelPos] = scT;
         }
         else{
          if(ucP >= tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX]){
            tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = ucP;
            tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = scT;
            }
            else{
            if(ucP == tCDA.aucPSollMin[ucIdX]){
              tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = ucP;
              tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = scT;
            }
          }
        }
      }
      else{
          if(ucWheelPos < cRadPosUndef){
          tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = tCDA.aucPSollMin[ucIdX];
          tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = scT;
          tCDA.aucPSoll[cIxForWpSpecDataStorage][ucWheelPos] = tCDA.aucPSollMin[ucIdX];
          tCDA.ascTSoll[cIxForWpSpecDataStorage][ucWheelPos] = scT;
         }
         else{
          tCDA.aucPSoll[cIxForIdSpecDataStorage][ucIdX] = tCDA.aucPSollMin[ucIdX];
          tCDA.ascTSoll[cIxForIdSpecDataStorage][ucIdX] = scT;
        }
      }
      }
   }
   else{
      ucRet = 0;
   }
   return ucRet;
}

uint8 ucPutEnvDataCS(uint8 ucIdX, uint8 ucEnvPres, sint8 scEnvTemp){
   uint8 ucRet = 0xff;
   if(ucIdX < cAnzRad){
    tCDA.aucEnvPres[ucIdX] = ucEnvPres;
    tCDA.ascEnvTemp[ucIdX] = scEnvTemp;
   }
   return ucRet;
}

uint8 ucGetPambCS(uint8 ucIdX){
   uint8 ucRet;
   if(ucIdX < cAnzRad){
      ucRet = tCDA.aucEnvPres[ucIdX];
   }
   else{
      ucRet = (uint8) 40;
   }
   return ucRet;
}

sint8 scGetTambCS(uint8 ucIdX){
   sint8 scRet;
   if(ucIdX < cAnzRad){
      scRet = tCDA.ascEnvTemp[ucIdX];
   }
   else{
      scRet = (sint8) 40;
   }
   return scRet;
}

uint8 ucPutMSollCS(uint8 ucIdX, uint16 ushMSoll){
   uint8 ucRet = 0xff;
   if(ucIdX < cAnzRad){
    tCDA.aushMSoll[ucIdX] = ushMSoll;
   }
   else{
      ucRet = 0;
   }
   return ucRet;
}

uint8 ucPutPSollMinCS(uint8 ucIdX, uint8 ucP, uint8 ucMode){
   uint8 ucRet;
   if(ucIdX < cAnzRad){
      if(ucP < aucPSollMinCSc[ucMode]){
      ucRet = 0;
      }
      else{
      tCDA.aucPSollMin[ucIdX] = ucP;
      ucRet = 0xff;
      }
   }
   else{
      ucRet = 0;
   }
   return (ucRet);
}

uint8 ucGetPSollMinCS(uint8 ucIdX){
   uint8 ucRet;
   if(ucIdX < cAnzRad){
      ucRet = tCDA.aucPSollMin[ucIdX];
   }
   else{
      ucRet = 0;
   }
   return (ucRet);
}

void InitCS(uint8 ucInit){
   uint8 i;
   switch(ucInit){
      case cIxPMinEU:
      tCDA.ucPMinAbs                              = ucPMinDefEUc;
      for(i = 0; i < cAnzRad; i++){
        tCDA.aucPSollMin[i]                       = ucPSollDefEUc;
        tCDA.aucPSoll[cIxForIdSpecDataStorage][i] = ucPSollDefEUc;
        tCDA.aucPSoll[cIxForWpSpecDataStorage][i] = ucPSollDefEUc;
        tCDA.ascTSoll[cIxForIdSpecDataStorage][i] = ucTSollDefEUc;
        tCDA.ascTSoll[cIxForWpSpecDataStorage][i] = ucTSollDefEUc;
        tCDA.aushMSoll[i]                         = ushMSollDefEUc;
        tCDA.aucPinitTreifen[i]                   = ucPSollDefEUc;
        tCDA.ascTreifen[i]                        = ucTSollDefEUc;
        tCDA.aucEnvPres[i]                        = cucPambDef;
        tCDA.ascEnvTemp[i]                        = cscTambDef;
      }
      break;

      case cIxPMinUS:
      tCDA.ucPMinAbs                              = ucPMinDefUSc;
      for(i = 0; i < cAnzRad; i++){
        tCDA.aucPSollMin[i]                       = ucPSollDefUSc;
        tCDA.aucPSoll[cIxForIdSpecDataStorage][i] = ucPSollDefUSc;
        tCDA.aucPSoll[cIxForWpSpecDataStorage][i] = ucPSollDefUSc;
        tCDA.ascTSoll[cIxForIdSpecDataStorage][i] = ucTSollDefUSc;
        tCDA.ascTSoll[cIxForWpSpecDataStorage][i] = ucTSollDefUSc;
        tCDA.aushMSoll[i]                         = ushMSollDefUSc;
        tCDA.aucPinitTreifen[i]                   = ucPSollDefUSc;
        tCDA.ascTreifen[i]                        = ucTSollDefUSc;
        tCDA.aucEnvPres[i]                        = cucPambDef;
        tCDA.ascEnvTemp[i]                        = cscTambDef;
      }
      break;

      default:
      tCDA.ucPMinAbs                              = ucPMinDefEUc;
      for(i = 0; i < cAnzRad; i++){
        tCDA.aucPSollMin[i]                       = ucPSollDefEUc;
        tCDA.aucPSoll[cIxForIdSpecDataStorage][i] = ucPSollDefEUc;
        tCDA.aucPSoll[cIxForWpSpecDataStorage][i] = ucPSollDefEUc;
        tCDA.ascTSoll[cIxForIdSpecDataStorage][i] = ucTSollDefEUc;
        tCDA.ascTSoll[cIxForWpSpecDataStorage][i] = ucTSollDefEUc;
        tCDA.aushMSoll[i]                         = ushMSollDefEUc;
        tCDA.aucPinitTreifen[i]                   = ucPSollDefEUc;
        tCDA.ascTreifen[i]                        = ucTSollDefEUc;
        tCDA.aucEnvPres[i]                        = cucPambDef;
        tCDA.ascEnvTemp[i]                        = cscTambDef;
      }
      break;
   }
   return;
}
