#ifndef __UPAP_H__
#define __UPAP_H__

#define Z_OVERLORD_SPEED	2

#define SAVESLOT	0x999
#define SAVEINFO	0x666
#define LANGRU		0x333

#define	ERRORSAVECOUNT	0x0011
#define	SAVECOUNT1		0x0001
#define	SAVECOUNT2		0x0002
#define	SAVECOUNT3		0x0003
#define	SAVECOUNT4		0x0004
#define	SAVECOUNT5		0x0005
#define	SAVECOUNT6		0x0006
#define	SAVECOUNT7		0x0007
#define	SAVECOUNT8		0x0008
#define	SAVECOUNT9		0x0009
#define	SAVECOUNT10		0x0010

typedef union
{
	unsigned char i[30];
	struct
	{
		unsigned int iUnzip;				//4
		unsigned short int iSignature;		//6
		unsigned int iCrc32;				//10
		unsigned int iChecksum;				//14
		unsigned int iLenFile;				//18
		unsigned int iConst1;				//22
		unsigned int iConst2;				//26
		unsigned int iReserved;				//30
	} data;
} uniDataInfo, *puniDataInfo;

typedef union
{
unsigned char i[8];
long long rax;
	struct
	{
		unsigned int eax; // 4
		unsigned int edx; // 4
	} edx_eax;
} RegisterVal64, *pRegisterVal64;

extern unsigned int aTableCrc32[];
extern unsigned int iFlagDefSave;
extern unsigned int iFlagDefSaveLang;
extern unsigned int iFlagSaveCount;
extern uniDataInfo uniDInfo;

BOOL CheckFileSignature(puniDataInfo Info, void* aBuf, void* table);
BOOL Decompression(size_t iUnzip, size_t iLenFile, void* pAddressIn, void* pAddressOut, puniDataInfo Info);
BOOL Compression(size_t iLenIn, size_t iLenOut, void* pAddressIn, void* pAddressOut, puniDataInfo Info);
BOOL DefineTypeFile (void* aBuf, size_t len);

unsigned int CheckCrc32 (size_t iLenFile, void* pAddress, void* table);
unsigned int CheckSum(size_t iNumByte, void* pAddress);

#endif // __UPAP_H__