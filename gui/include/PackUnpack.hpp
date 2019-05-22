#ifndef __UPAP_H__
#define __UPAP_H__

#define Z_OVERLORD_SPEED	2

#define SAVESLOT	0x999
#define SAVEINFO	0x666
#define LANGRU		0x333

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
} UnionDataInfo, *pUnionDataInfo;

extern const unsigned int aConstTableCrc32 [0x100];

class CUnpackPack
{
public:
	CUnpackPack()
	{
	memset(&UnionDataInfoOne, 0, sizeof(UnionDataInfo));
	iFlagDefSave = 0;
	iFlagDefSaveLang = 0;
	}
	
	~CUnpackPack()
	{
		aBufferOne.~vector();
		aBufferTemp.~vector();
		memset(&UnionDataInfoOne, 0, sizeof(UnionDataInfo));
	}

	// public value
	unsigned int iFlagDefSave;
	unsigned int iFlagDefSaveLang;
	
	// function
	// При декомпресии UnionDataInfo заполняется автоматически.
	// При компрессии параметры берутся из UnionDataInfo, требуется корректировка в случае изменения параметров явно.
	
	int Compression(); //  Компрессия из aBufferTemp в aBufferOne. Вызыватся явно.
	int Decompression(); // Декомпрессия из aBufferOne в aBufferTemp. Вызыватся явно.
	int CheckFileSignature(void); // проверка файла на соответствие файлу сохранения. Запускает DefineTypeFile.
	int DefineTypeFile(); // определяет тип сейв файла. Вызывается явно после декомпрессии.

	
	//Get, Set
	vector <unsigned char> *lpGetBuffer(int numBuf); // 1 - aBufferOne, 2 - aBufferTemp
	pUnionDataInfo lpGetDataInfo();


private:
	vector <unsigned char> aBufferOne;
	vector <unsigned char> aBufferTemp;
	UnionDataInfo UnionDataInfoOne;
	
	// function
	int CheckCrc32(size_t iLenFile, vector <unsigned char> aBuf); // проверка crc32 по алгоритму разработчика. Явно не вызывается.
	int CheckSum(size_t iNumByte, vector <unsigned char> aBuf); // проверка sum по алгоритму разработчика. Явно не вызывается.
};

#endif // __UPAP_H__