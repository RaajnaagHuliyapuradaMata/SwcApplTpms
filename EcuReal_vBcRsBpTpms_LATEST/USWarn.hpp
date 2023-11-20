
#ifndef USWARNDEFH
#define USWARNDEFH

extern unsigned char  ucGetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern void ClearWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern unsigned char ucSetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern unsigned char ucPfT(unsigned short ushM, unsigned short ushTabs);
extern unsigned short ushMIso(unsigned char ucP, signed char scT);

#ifndef pb_ModulTest_02062003

#else
extern void PrintCalTab(void);
extern void PrintWarnCfg(void);
extern void PrintWarnLevels(void);
extern void PrintWarnLevelHeadLine(void);
extern void DeactivateFilters(void);
extern void PrintPfTHeadLine(void);
extern void PrintPfT( unsigned char , signed char );
extern void PrintPSollHeadLine(void);
extern void PrintPSoll(unsigned char, signed char);
extern void PrintCalData(void);
extern void ResetUSWarn(void);
extern void TESTUNITucCheckFrikWN(void);

#endif

struct Byte
{
  unsigned char Lo;
  unsigned char Hi;
};

union tWB16
{
  struct Byte uc;
  unsigned short ush;
};

struct SollDat
{
  unsigned char ucPSoll;
  signed char scTSoll;
  unsigned short ushMSoll;
};

struct HFTelIntern
{
  unsigned char ucId;
  unsigned char ucP;
  signed char scTWE;
  unsigned char ucLifeTime;
  unsigned char ucState;
  unsigned short ushVehicleSpeed;
  signed char scTa;
  signed char scTref;
  unsigned char ucKLState;
};

union HFTelAccess
{
  struct HFTelIntern tHF;
  unsigned char ucByte[(unsigned char) sizeof(struct HFTelIntern)];
};

struct LocalWarnDat
{
  union HFTelAccess tHFD;
  struct SollDat tSD;
  unsigned char ucCurWarnLevel;
  unsigned char PWarm;
};

#define ucPResInMBarc  25
#define uc1Barc (unsigned char) 40
#define uc100mBarc               4
#define ush273Kelvinc 273
#define sc0Gradc   0
#define sc20Gradc 20
#define sc40Gradc 40
#define ushGSFc 1024

#define ucIsoClearc (unsigned char) 0x20
#define ucUSCodec (unsigned char) 0x04
#define ucCtryMaskc (unsigned char) 0x0C

#endif
