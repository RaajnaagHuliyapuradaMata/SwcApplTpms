

#ifndef EEIFACE_H
#define EEIFACE_H

extern void GetDataEE(unsigned char ucId, unsigned char *pRamAdr);
extern void PutDataEE(unsigned char ucId, const unsigned char *pRamAdr);

#ifndef pb_ModulTest_02062003

#else
extern void ResetEEPROM(void);
extern void PRINT_EepromUsage(void);
#endif

#endif
