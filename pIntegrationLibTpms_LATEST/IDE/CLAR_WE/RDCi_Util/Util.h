#ifndef _UTIL_H
#define _UTIL_H

#define TELE_FILTER_OFF 0
#define TELE_FILTER_HUF 1
#define TELE_FILTER_CONTI 2
#define TELE_FILTER_SCHRADER 4
#define TELE_FILTER_READ_ONLY 0xff

void SetReDataFromFileFlag( uint8 ucHistSlot, boolean bFlag);

void SetReMuteFlag( uint8 ucHistSlot, boolean bFlag);

unsigned char SetTeleFilter(unsigned char ucFilter);

#ifdef _EcuVirtual
void ReadStringFromStream(void);
#else
void ReadStringFromStream(unsigned char* myString, System::IO::Stream^ myStream, uint8 mySize);

long ReadLongIntFromStream(System::IO::Stream^ myStream);

long long ReadLongLongIntFromStream(System::IO::Stream^ myStream);

double ReadDoubleFromStream(System::IO::Stream^ myStream);

void ReadCompleteLineFromStream( System::IO::Stream^ myStream);

long ReadMessageFromFile(System::IO::Stream^ myStream, uint32 msgType, unsigned long long * pullTimestamp, void * FileData);
#endif

short SearchIDInList(long id);

void convertTemperatureRawToPhysical(unsigned char ucRawTemp, signed char *pscPhyTemp);

void SynchronizeSystemTimes( Rdci_UHRZEIT_DATUM_Type* timeDate, Rdci_T_SEC_COU_REL_Type* relTime, StbMB_SyncStatusType* syncState, StbMB_SystemTimeType* sysTime);

#endif
