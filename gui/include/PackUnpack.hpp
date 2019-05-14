#ifndef __UPAP_H__
#define __UPAP_H__

#define Z_OVERLORD_SPEED	2

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
}val64;

extern unsigned int aTableCrc32[];
extern uniDataInfo uniDInfo;
extern val64 rax;

BOOL CheckFileSignature(uniDataInfo Info);
unsigned int CheckCrc32 (size_t iLenFile, void* pAddress, void* table);
unsigned int CheckSum(size_t iNumByte, void* pAddress);
BOOL Decompression(size_t iUnzip, size_t iLenFile, void* pAddressIn, void* pAddressOut);
BOOL Compression(size_t iLenIn, size_t iLenOut, void* pAddressIn, void* pAddressOut);

#endif // __UPAP_H__