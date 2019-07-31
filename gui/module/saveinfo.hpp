#ifndef __SAVEINFO_HPP__
#define __SAVEINFO_HPP__

///// error /////
#define ERR_SI_SAVECOUNT	-0x0008
////////////////

#define	SAVECOUNT0		-0x01 // метка ошибки
#define	SAVECOUNT1		0x0000
#define	SAVECOUNT2		0x0001
#define	SAVECOUNT3		0x0002
#define	SAVECOUNT4		0x0003
#define	SAVECOUNT5		0x0004
#define	SAVECOUNT6		0x0005
#define	SAVECOUNT7		0x0006
#define	SAVECOUNT8		0x0007
#define	SAVECOUNT9		0x0008
#define	SAVECOUNT10		0x0009

typedef struct
{
	struct
	{
	const unsigned int reserved 		= 0x01000000;
	const unsigned int const02 			= 0x0049534F;
	unsigned int numbersize 			= 0x00000000;
	unsigned int count 					= 0x00000000; // 0x0000xx00, 0x0082xx00
	const unsigned short int const01 	= 0x0101;
	const unsigned short int reserved02 = 0x0000; //выравнивание
	} header;
	
	struct
	{
	unsigned int iConst[10] = {0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009};
	//unsigned int iConst[10] = {0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009};
	unsigned int iConst2[3] = {0x00000100, 0x00000200, 0x00008200};
	unsigned int iOffset[10];
	} listfile;
	
	struct
	{
	vector <unsigned char> aDataSave [10];
	char iFlagSaveNum [10];
	} data;
	
	struct
	{
	unsigned int iCount [10];
	} count;
	
} SaveInfoStruct, *lpSaveInfoStruct;

class CSaveInfoOverlord
{
public:
	CSaveInfoOverlord();
	~CSaveInfoOverlord();
	void ClearClass(void);
//// class status ////////////////////////
	int SetErrorStatus (int iError);	//
	int GetErrorStatus (void);			//
	void ClearErrorStatus (void);		//
//// class status ////////////////////////

public:
	SaveInfoStruct SIS;
	int iFlagSaveCount = 0;
	
	// FUNCTION
	int InitVectorSI(int num);
	int DisassemblySI(void);				// Расщепляет saveinfo на отдельные записи. Вызывается явно
	void AssemblySI(void);					// Сборка saveinfo из отдельных записей. Вызывается явно
	unsigned char* StringConvert(int iNumVector, int iLanguage);
	float TimeDissambler(int iNumVector);
	//int TimeAssembler(int iNumVector);
	wchar_t* TimeConvector(int iTimeVal); 	//not used
	
	vector <unsigned char> *lpGetBuffer(void);//

private:
int iErrorStatus = 0;
unsigned char aTempOne [64];
wchar_t aTempTwo [32];

using offset = unsigned int;
vector <unsigned char> aBufferTemp;

char aErrorSI [sizeof(int)*4]
{
	-0x10, // failure dism time
	-0x11
};

offset iHead = 0xE;
offset iSave [10] = 
{
	iHead,
	iHead+0x2,
	iHead+0x6+0x8,
	iHead+0x6+0x8*2,
	iHead+0x6+0x8*3,
	iHead+0x6+0x8*4,
	iHead+0x6+0x8*5,
	iHead+0x6+0x8*6,
	iHead+0x6+0x8*7,
	iHead+0x6+0x8*8
};


unsigned char cPointerTimePos 			= 0x11;
unsigned char cPointerXPos 				= 0x12;
unsigned char cPointerYPos 				= 0x13;
unsigned char cPointerZPos 				= 0x14;
unsigned char cPointerUnknownOnePos 	= 0x16;

};

#endif // __SAVEINFO_HPP__