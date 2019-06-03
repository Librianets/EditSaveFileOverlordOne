#ifndef __UPAP_H__
#define __UPAP_H__

#include <stdio.h> 			// Language C
#include <string.h>			// Language C
#include <vector>			// Language C++
#include <zlib.h>			// ZLIB LIB
using std::vector;

#define Z_OVERLORD_SPEED	2

#define SAVESLOT	0x999
#define SAVEINFO	0x666
#define LANGRU		0x333

#define ERROR_CHECKSUM 			-0x000C
#define ERROR_CHECKCONST 		-0x0009
#define ERROR_CHECKCRC32 		-0x000A
#define ERROR_DECOMPRESS 		-0x000B
#define ERROR_COMPRESS 			-0x000D
#define ERROR_FAILCHECKCONST	-0x0012 //17
#define ERROR_FAILCHECKLANG		-0x0013 //18

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

typedef union
{
unsigned char i[32];
struct
{
	unsigned int iUnzip;				//4 0123
	unsigned int iCrc32;				//10	4567
	unsigned int iChecksum;				//14	891011
	unsigned int iLenFile;				//18	12131415
	unsigned int iConst1;				//22	16171819
	unsigned int iConst2;				//26	20212223
	unsigned int iReserved;				//30	24252627
	unsigned short int iSignature;		//6		2829
	unsigned short int RESERVED;		//Выравнивание
} data;
} UnionDataInfo, *pUnionDataInfo;

extern const unsigned int aConstTableCrc32 [0x100];

class CUnpackPack
{
public:
	CUnpackPack();
	~CUnpackPack();

	// public value
	unsigned int iFlagDefSave;
	unsigned int iFlagDefSaveLang;
	
	// function
	// При декомпресии UnionDataInfo заполняется автоматически.
	// При компрессии параметры берутся из UnionDataInfo, требуется корректировка в случае изменения параметров явно.
	
	int Compression(); // Компрессия из aBufferTemp в aBufferOne. Вызыватся явно.
	int Decompression(); // Декомпрессия из aBufferOne в aBufferTemp. Вызыватся явно.
	int CheckFileSignature(void); // проверка файла на соответствие файлу сохранения. Запускает DefineTypeFile.
	int DefineTypeFile(); // определяет тип сейв файла. Вызывается явно после декомпрессии.
	int ClearClass(); // исключительно для повышения управляемости

	//Get, Set
	vector <unsigned char> *lpGetBuffer(int numBuf); // 1 - aBufferOne, 2 - aBufferTemp
	pUnionDataInfo lpGetDataInfo();


private:
	vector <unsigned char> aBufferOne;
	vector <unsigned char> aBufferTemp;
	UnionDataInfo UnionDataInfoOne;
	
	// function
	unsigned int CheckCrc32(size_t iLenFile, vector <unsigned char> aBuf); // проверка crc32 по алгоритму разработчика. Явно не вызывается.
	unsigned int CheckSum(size_t iNumByte, vector <unsigned char> aBuf); // проверка sum по алгоритму разработчика. Явно не вызывается.
};

#endif // __UPAP_H__