#ifndef _LOGGING_H
#define _LOGGING_H

#define LENGTH_OF_LOG_BUFFER  50000000

#define MAX_CHAR_BYTE   3
#define MAX_CHAR_WORD   5
#define MAX_CHAR_DWORD 10
#define MAX_CHAR_LONG_LONG 19

#define LOG_SET_WHL     1
#define LOG_SET_WAL     2
#define LOG_SET_OUT     4
#define LOG_SET_DTC     8
#define LOG_SET_DBG     16

extern void    StartLOG( uint8 ucFilename[], uint8 ucLogSet);
extern void    StopLOG(void);
extern void    PutTimeFromFileLOG( unsigned long long ullTime);
extern void    AddOffsetToTimeLOG( unsigned long long ullTimeOffset);
extern boolean bLineBufferEmptyLOG(void);

extern void PutRfDataToBufferLOG( ImpTypeRecCddRdcData *tRfData);
extern void PutInitRecToBufferLOG(void);
extern void PutInitWhlToBufferLOG(void);
extern void PutInitWalToBufferLOG(void);
extern void PutInitOutToBufferLOG(void);
extern void PutInitDtcToBufferLOG(void);
extern void PutInitDbgToBufferLOG(void);
extern void PutNewLineToBufferLOG(void);
extern void PutByteToBufferLOG( uint8 ucByte);
extern void PutSignedByteToBufferLOG( sint8 scByte);
extern void PutWordToBufferLOG( uint16 ushWord);
extern void PutSignedWordToBufferLOG( sint16 sshWord);
extern void PutDwordToBufferLOG( uint32 ulDword);
extern void PutSignedDwordToBufferLOG( sint32 slDword);
extern void PutUnsignedLongLongToBufferLOG( unsigned long long ullLongLong);
extern void PutSignedLongLongToBufferLOG( signed long long sllLongLong);

extern uint8 GetLastRecEventZomPos(void);

#endif
