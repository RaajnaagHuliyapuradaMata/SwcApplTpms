
#ifndef UCSCS_H
#define UCSCS_H

extern unsigned char ucGetPMinCS(void);
extern unsigned char ucPutPMinCS(unsigned char ucPMin, unsigned char ucMode);
extern unsigned char ucGetPSollCS(unsigned char ucIdX);
extern unsigned short ushGetMSollCS(unsigned char ucIdX);
extern signed char scGetTSollCS(unsigned char ucIdX);
extern unsigned char ucPutCalTabVectorCS(unsigned char ucIdX, unsigned char ucP, signed char scT, unsigned short ushM);
extern unsigned char ucPutPSollMinCS(unsigned char ucIdX, unsigned char ucP, unsigned char ucMode);
extern void InitCS(unsigned char ucInit);
extern unsigned char ucGetPwarmCS(unsigned char ucIdX);
extern void PutPwarmCS(unsigned char Pwarm, unsigned char ucIdX);

#ifdef BUILD_WITH_UNUSED_FUNCTION
extern unsigned char ucGetPSollMinCS(unsigned char ucIdX);
#endif

#ifndef pb_ModulTest_02062003

#else
extern void ResetUSCS(void);
#endif

struct CT
{
  unsigned char ucPMinAbs;
  unsigned char aucPSollMin[ucSumWEc];
  unsigned char aucPSoll[ucSumWEc];
  signed char ascTSoll[ucSumWEc];
  unsigned short aushMSoll[ucSumWEc];
  unsigned char aucPWarm[ucSumWEc];
};

union CDA
{
  struct CT tCalTab;
  unsigned char ucByte[sizeof(struct CT)];
};

extern union CDA tCDA;

#endif
