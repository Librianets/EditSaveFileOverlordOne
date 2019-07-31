#ifndef __UPAP_H__
#define __UPAP_H__

namespace OESD // OVERLORD EDITSAVEDATA
{

#define Z_OVERLORD_SPEED	2

#define SAVESLOT	0x22
#define SAVEINFO	0x11
#define LANGRU		0x44

#define E_LIBPACK_CHECKSUM 			-0x01 // Суммы не совпадают
#define E_LIBPACK_TYPEFILE 			-0x02 // Тип файла не установлен
#define E_LIBPACK_CHECKCRC32 		-0x03 // crc32 не совпадает
#define E_LIBPACK_DECOMPRESS 		-0x04 // Декомпрессия провалилась
#define E_LIBPACK_COMPRESS 			-0x05 // Компрессия провалилась
#define E_LIBPACK_CHECKCONST		-0x06 // Не найды константы в файле
#define E_LIBPACK_CHECKLANG			-0x07 // Переработать ansi or unicode

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
	unsigned int iUnzip;				//4 	0123
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
	int ClearClass();
//// class status ////////////////////////
	int SetErrorStatus (int iError);	//
	int GetErrorStatus (void);			//
	void ClearErrorStatus (void);		//
//// class status ////////////////////////
	
public:
	unsigned int iFlagDefSave;
	unsigned int iFlagDefSaveLang;
	
	// FUNCTION
	// При декомпресии UnionDataInfo заполняется автоматически.
	// При компрессии параметры берутся из UnionDataInfo, требуется корректировка в случае изменения параметров явно.
	
	int Compression(void); 				// Компрессия из aBufferTemp в aBufferOne. Вызыватся явно.
	int Decompression(void); 			// Декомпрессия из aBufferOne в aBufferTemp. Вызыватся явно.
	int CheckFileSignature(void); 	// проверка файла на соответствие файлу сохранения. Запускает DefineTypeFile.
	int DefineTypeFile(void); 			// определяет тип сейв файла. Вызывается явно после декомпрессии.
	
	vector <unsigned char> *lpGetBuffer(int numBuf); // 1 - aBufferOne, 2 - aBufferTemp
	pUnionDataInfo lpGetDataInfo();

private:
	int iErrorStatus = 0;
	vector <unsigned char> aBufferOne;
	vector <unsigned char> aBufferTemp;
	UnionDataInfo UnionDataInfoOne;
	
	// FUNCTION
	unsigned int CheckCrc32(size_t iLenFile, vector <unsigned char> aBuf); 	// проверка crc32 по алгоритму разработчика. Явно не вызывается.
	unsigned int CheckSum(size_t iNumByte, vector <unsigned char> aBuf); 	// проверка sum по алгоритму разработчика. Явно не вызывается.
};

} //namespace OESD // OVERLORD EDITSAVEDATA
#endif // __UPAP_H__