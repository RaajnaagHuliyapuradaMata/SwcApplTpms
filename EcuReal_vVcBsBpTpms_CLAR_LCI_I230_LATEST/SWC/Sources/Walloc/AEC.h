#ifdef AEC_INT
void SetFrontBack(unsigned char ucFrontIx, unsigned char ucBackIx);
void SetFBPACM(unsigned char ucFrontIx, unsigned char ucBackIx,unsigned char ucWrong);
void SetFBACM(unsigned char ucFrontID, unsigned char ucBackID,unsigned char ucWrong);
void ResetBadWayCheck(void);
#else if
#ifdef CONCEPT4
extern unsigned short ushMofID(unsigned char ucIx);
extern unsigned short ushDistInMSec(unsigned char ucIx1, unsigned char ucIx2);
extern unsigned char ucGetBiggerM(unsigned char ucIx1,unsigned char ucIx2);
extern unsigned short ushGetTruECt(tRFTelType * ptInputWA, unsigned char ucIx);
extern void Concept4Op2(unsigned char ucIx, unsigned short ushCurECt);
#endif
extern void Concept5pb8(unsigned char ucID, tRFTelType * ptInputWA);
extern unsigned char ucEarlyEnd(unsigned char ucIx);
extern void SetFrontBack(unsigned char ucFrontIx, unsigned char ucBackIx);
extern void SetFBPACM(unsigned char ucFrontIx, unsigned char ucBackIx,unsigned char ucWrong);
extern void SetFBACM(unsigned char ucFrontID, unsigned char ucBackID,unsigned char ucWrong);
extern void ResetACM(void);
extern void CtACM(unsigned char ucID1, unsigned char ucID2);
extern unsigned char ucAutoACM(void);
extern unsigned char ucEarlyEnd(unsigned char ucIx);
unsigned char ucAutoACM(void);
extern unsigned char ucDirectionDetection(unsigned char ucLeRiMinDistance);
extern unsigned char ucAxisDetection(void);
extern unsigned char ucWPConsistent(void);
extern void BadWayCheck(unsigned char ucPeaks, unsigned short ushTime);
extern void ResetBadWayCheck(void);
extern void PutushMaxAxDist(unsigned short ushVal);
extern void PutushMinAxDist(unsigned short ushVal);
#endif
